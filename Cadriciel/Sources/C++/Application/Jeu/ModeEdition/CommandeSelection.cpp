#include "CommandeSelection.h"

#include "../../../ElementObjet/ElementJeuAbstrait.h"
#include "../../../../../Commun/Utilitaire/AideGL.h"
#include "../../FacadeModele.h"
#include "../../../Arbre/ArbreRenduINF2990.h"
#include "../../../../../Commun/Utilitaire/Plan3D.h"
#include "../../../../../Commun/Utilitaire/Vue/Projection.h"

#include <queue>
using namespace std;

CommandeSelection::CommandeSelection(const vue::Vue& vue,
									 Carte& carte,
									 vector<ElementJeuAbstrait*>& objetsSelectionnes) : vue_(vue),
																						carte_(carte),
																						objetsSelectionnes_(objetsSelectionnes),
																						modeSelection_(false)
{
	mouseClicked_ = false;
	clickedPositionX_ = 0;
	clickedPositionY_ = 0;
}

CommandeSelection::~CommandeSelection() {
}

void CommandeSelection::executer(int mouseX, int mouseY, int boutton, int touche) {
	mouseX_ = mouseX;
	mouseY_ = mouseY;
	touche_ = touche;

	if (boutton == 1) {
		if (!mouseClicked_) {
			clickedPositionX_ = mouseX;
			clickedPositionY_ = mouseY;
		}
		mouseClicked_ = true;

		// Definition d'un clic: si le clic reste a ± 3 pixels du point clique,
		// alors on effectue une selection ponctuelle. Sinon, on fais une
		// selection elastique.
		if ((mouseX >= (clickedPositionX_ - 3) && mouseX <= (clickedPositionX_ + 3)) &&
			(mouseY >= (clickedPositionY_ - 3) && mouseY <= (clickedPositionY_ + 3)))
		{
			modeSelection_ = false;
		} else {
			modeSelection_ = true;

			int dx = clickedPositionX_ - mouseX_;
			int dy = clickedPositionY_ - mouseY_;

			// Condition pour le rectangle elastique
			if (dx != 0 && dy != 0 && (abs(dx) > 3 || abs(dy) > 3)) {

				// Transformation de la cloture a la fenetre virtuelle
				Vecteur3 pointClique(clickedPositionX_, clickedPositionY_);
				Vecteur3 pointSouris(mouseX_, mouseY_);
				afficherRectangleElastique(pointClique, pointSouris);
			}
		}

	} else {
		// Si on relache le bouton 
		if (mouseClicked_) {
			mouseClicked_ = false;

			set<ElementJeuAbstrait*>::iterator it;

			// On ajoute la selection ponctuelle
			if (!modeSelection_) {
				// On effectue la selection ponctuelle seulement lorsqu'on a
				// fait un clique simple
				selectionPonctuelle();

				// On deselectionne tous les objets
				if (touche_ != 17) {
					for (size_t i = 0; i < objetsSelectionnes_.size(); i++) {
						objetsSelectionnes_[i]->setSelectionne(false);
					}
					objetsSelectionnes_.clear();
				}

				// On ajoute tous les objets
				for (it = objetsSelectionnables_.begin(); it != objetsSelectionnables_.end(); ++it) {
					if (touche_ == 17) {
						(*it)->inverserSelection();
					} else {
						(*it)->setSelectionne(true);
					}

					if ((*it)->getSelectionne()) {
						objetsSelectionnes_.push_back(*it);
					} else {
						// Un peu gettho mais ca fonctionne. De toute facon la vitesse est pas si
						// importante en mode edition
						for (size_t i = 0; i < objetsSelectionnes_.size(); i++) {
							if (objetsSelectionnes_[i] == *it) {
								objetsSelectionnes_.erase(objetsSelectionnes_.begin() + i);
								break;
							}
						}
					}
				}

				objetsSelectionnables_.clear();
			} else {

				int dx = clickedPositionX_ - mouseX_;
				int dy = clickedPositionY_ - mouseY_;

				// Condition pour le rectangle elastique
				if (dx != 0 && dy != 0 && (abs(dx) > 3 || abs(dy) > 3)) {

					// Transformation de la cloture a la fenetre virtuelle
					Vecteur3 pointClique(clickedPositionX_, clickedPositionY_);
					Vecteur3 pointSouris(mouseX_, mouseY_);

					selectionElastique(pointClique, pointSouris);
				}

				// Si on appuie pas sur controle
				if (touche_ != 17) {
					// On deselectionne tous les objets
					for (size_t i = 0; i < objetsSelectionnes_.size(); i++) {
						objetsSelectionnes_[i]->setSelectionne(false);
					}

					objetsSelectionnes_.clear();
				}

				// On ajoute tous les objets. Si on appuie sur controle, il
				// faut inverser la selection
				for (it = objetsRectangleElastique_.begin(); it != objetsRectangleElastique_.end(); ++it) {
					if (touche_ == 17) {
						(*it)->inverserSelection();

						if ((*it)->getSelectionne()) {
							objetsSelectionnes_.push_back(*it);
						} else {
							// Un peu gettho mais ca fonctionne. De toute facon la vitesse est pas si
							// importante en mode edition
							for (size_t i = 0; i < objetsSelectionnes_.size(); i++) {
								if (objetsSelectionnes_[i] == *it) {
									objetsSelectionnes_.erase(objetsSelectionnes_.begin() + i);
									break;
								}
							}
						}
					} else {
						(*it)->setSelectionne(true);
						objetsSelectionnes_.push_back(*it);
					}
				}

				objetsRectangleElastique_.clear();
			}
		}
	}
}

void CommandeSelection::selectionPonctuelle() {
	if (vue_.getType() == vue::ORTHOGONALE) {
		selectionPonctuelleOrthogonale();
	} else if (vue_.getType() == vue::PERSPECTIVE) {
		selectionPonctuellePerspective();
	}
}

void CommandeSelection::selectionPonctuelleOrthogonale() {
	// On transforme le point dans l'espace de la clôture vers l'espace de la camera
	Vecteur3 positionVirtuelle;
	vue_.convertirClotureAVirtuelle(clickedPositionX_, clickedPositionY_, positionVirtuelle);

	// On itere a travers tous les objets pour savoir lequel on a selectionne
	// a partir de leur boite englobante
	const vector<ElementJeuAbstrait*>& objets = carte_.getVecteurElement();

	// Creation de la boite englobante orientee qui represente le rectangle elastique
	Vecteur3f positionRectangle((const float)positionVirtuelle[0], (const float)positionVirtuelle[1]);
	BoiteEnglobanteOrientee rectangleElastique(positionRectangle, positionRectangle + Vecteur3f(1.0f, 1.0f, 0.0f));

	for (size_t i = 0; i < objets.size(); i++) {
		const BoiteEnglobanteOrientee& obb = objets[i]->getBoiteEnglobanteOrientee();

		// On verifie si on est dans la boite englobante par rapport au plan XY
		if (rectangleElastique.calculerCollision(obb)) {
			// On selectionne qu'un seul objet si on appuie pas sur controle
			if (touche_ != 17) {
				objetsSelectionnables_.clear();
				objetsSelectionnables_.insert(objets[i]);
			} else {

				// Dans le cas contraire, on inverse la selection si on selectionne deja l'objet
				// et on l'ajoute si on ne l'a pas deja
				set<ElementJeuAbstrait*>::iterator it = objetsSelectionnables_.find(objets[i]);
				if (it != objetsSelectionnables_.end()) {
					(*it)->inverserSelection();
					objetsSelectionnables_.erase(it);
				} else {
					objetsSelectionnables_.insert(objets[i]);
				}
			}

			break;
		}
	}
}

void CommandeSelection::selectionPonctuellePerspective() {
	// On doit tout re-afficher l'arbre de rendu, mais en mode sélection en
	// assignant des noms uniques à chacun des objets.
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		const GLsizei taille = 500;
		GLuint tampon[taille];
		glSelectBuffer(taille, tampon);
		glRenderMode(GL_SELECT);

		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		gluPickMatrix(clickedPositionX_, viewport[3] - clickedPositionY_, 3, 3, viewport);
		vue_.appliquerProjection(true);
		glMatrixMode(GL_MODELVIEW);

		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->afficher(true);
		int nombreObjets = glRenderMode(GL_RENDER);

		GLuint* ptr = tampon;
		GLuint min = 0xffffffff;
		NoeudAbstrait* noeud = NULL;
		unsigned int idx = 0;

		for (int i = 0; i < nombreObjets; i++) {
			// On ignore le nombre de noms
			int numNames = *ptr; ptr++;
			if (numNames == 0) {
				ptr++; ptr++;
				continue;
			}

			unsigned int zMin = *ptr; ptr++; ptr++;
			if (zMin < min) {
				min = zMin;
				noeud = (NoeudAbstrait*)(*ptr);
			}

			ptr++;
		}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	if (noeud != NULL) {
		ElementJeuAbstrait* objet = NULL;
		const vector<ElementJeuAbstrait*>& objets = carte_.getVecteurElement();

		for (size_t i = 0; i < objets.size(); i++) {
			// Si le noeud appartient à cet objet
			if (objets[i]->getNoeudAbstrait() == noeud) {
				// On selectionne qu'un seul objet si on appuie pas sur controle
				if (touche_ != 17) {
					objetsSelectionnables_.clear();
					objetsSelectionnables_.insert(objets[i]);
				} else {

					// Dans le cas contraire, on inverse la selection si on selectionne deja l'objet
					// et on l'ajoute si on ne l'a pas deja
					set<ElementJeuAbstrait*>::iterator it = objetsSelectionnables_.find(objets[i]);
					if (it != objetsSelectionnables_.end()) {
						(*it)->inverserSelection();
						objetsSelectionnables_.erase(it);
					} else {
						objetsSelectionnables_.insert(objets[i]);
					}
				}

				break;
			}
		}


	}
}

void CommandeSelection::selectionElastique(const Vecteur3& pointClique,
										   const Vecteur3& pointSouris)
{
	if (vue_.getType() == vue::ORTHOGONALE) {
		selectionElastiqueOrthogonale(pointClique, pointSouris);
	} else if (vue_.getType() == vue::PERSPECTIVE) {
		selectionElastiquePerspective(pointClique, pointSouris);
	}
}

void CommandeSelection::selectionElastiqueOrthogonale(const Vecteur3& pointClique,
													  const Vecteur3& pointSouris)
{
	// Test pour faire en sorte que les objets apparaissent comme
	// selectionnees au fur et a mesure.
	const vector<ElementJeuAbstrait*>& objets = carte_.getVecteurElement();

	Vecteur3 clic, souris;
	vue_.convertirClotureAVirtuelle((int) pointClique[0], (int) pointClique[1], clic);
	vue_.convertirClotureAVirtuelle((int) pointSouris[0], (int) pointSouris[1], souris);

	// Creation de la boite englobante orientee qui represente le rectangle elastique
	Vecteur3f basGauche(min((float)clic[0], (float)souris[0]), min((float)clic[1], (float)souris[1])),
			  hautDroit(max((float)clic[0], (float)souris[0]), max((float)clic[1], (float)souris[1]));
	BoiteEnglobanteOrientee rectangleElastique(basGauche, hautDroit);

	for (size_t i = 0; i < objets.size(); i++) {
		const BoiteEnglobanteOrientee& obb = objets[i]->getBoiteEnglobanteOrientee();

		set<ElementJeuAbstrait*>::iterator it = objetsRectangleElastique_.find(objets[i]);

		// On verifie si la boite englobante se trouve dans le rectangle elastique
		if (rectangleElastique.calculerCollision(obb)) {
			it = objetsRectangleElastique_.find(objets[i]);
			if (it == objetsRectangleElastique_.end()) {
				objetsRectangleElastique_.insert(objets[i]);
			}
		// Si on est pas dans la boite englobante
		} else {
			it = objetsRectangleElastique_.find(objets[i]);
			if (it != objetsRectangleElastique_.end()) {
				objetsRectangleElastique_.erase(it);
			}
		}
	}
}

void CommandeSelection::selectionElastiquePerspective(const Vecteur3& pointClique,
													  const Vecteur3& pointSouris)
{
	// Test pour faire en sorte que les objets apparaissent comme
	// selectionnees au fur et a mesure.
	const vector<ElementJeuAbstrait*>& objets = carte_.getVecteurElement();

	// Creation de la boite englobante orientee qui represente le rectangle elastique
	Vecteur3f basGauche(min((float)pointClique[0], (float)pointSouris[0]), min((float)pointClique[1], (float)pointSouris[1])),
			  hautDroit(max((float)pointClique[0], (float)pointSouris[0]), max((float)pointClique[1], (float)pointSouris[1]));
	float demiLargeur = (hautDroit[0] - basGauche[0]) / 2.0f;
	float demiHauteur = (hautDroit[1] - basGauche[1]) / 2.0f;
	float milieuX = basGauche[0] + demiLargeur;
	float milieuY = basGauche[1] + demiHauteur;

	set<const NoeudAbstrait*> objetsSelectionnes;

	// On doit tout re-afficher l'arbre de rendu, mais en mode sélection en
	// assignant des noms uniques à chacun des objets.
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		const GLsizei taille = 500;
		GLuint tampon[taille];
		glSelectBuffer(taille, tampon);
		glRenderMode(GL_SELECT);

		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);

		gluPickMatrix(milieuX, viewport[3] - milieuY, abs(hautDroit[0] - basGauche[0]), abs(hautDroit[1] - basGauche[1]), viewport);
		vue_.appliquerProjection(true);
		glMatrixMode(GL_MODELVIEW);

		FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->afficher(true);
		int nombreObjets = glRenderMode(GL_RENDER);

		GLuint* ptr = tampon;
		GLuint min = 0xffffffff;
		NoeudAbstrait* noeud = NULL;
		unsigned int idx = 0;

		for (int i = 0; i < nombreObjets; i++) {
			// On ignore le nombre de noms
			int numNames = *ptr; ptr++;
			if (numNames == 0) {
				ptr++; ptr++;
				continue;
			}

			ptr++; ptr++;
			objetsSelectionnes.insert((const NoeudAbstrait*)(*ptr));
			ptr++;
		}
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);

	for (size_t i = 0; i < objets.size(); i++) {

		set<const NoeudAbstrait*>::const_iterator it = objetsSelectionnes.find(objets[i]->getNoeudAbstrait());
		set<ElementJeuAbstrait*>::iterator s_it;

		if (it != objetsSelectionnes.cend()) {
				s_it = objetsRectangleElastique_.find(objets[i]);
				if (s_it == objetsRectangleElastique_.end()) {
					objetsRectangleElastique_.insert(objets[i]);
				}
		} else {
			s_it = objetsRectangleElastique_.find(objets[i]);
			if (s_it != objetsRectangleElastique_.end()) {
				objetsRectangleElastique_.erase(s_it);
			}
		}
	}
}

void CommandeSelection::afficherRectangleElastique(const Vecteur3& pointClique,
												   const Vecteur3& pointSouris) const
{
	if (vue_.getType() == vue::ORTHOGONALE) {
		afficherRectangleElastiqueOrthogonale(pointClique, pointSouris);
	} else if (vue_.getType() == vue::PERSPECTIVE) {
		afficherRectangleElastiquePerspective(pointClique, pointSouris);
	}
}

void CommandeSelection::afficherRectangleElastiqueOrthogonale(const Vecteur3& pointClique,
															  const Vecteur3& pointSouris) const
{
	Vecteur3 clic, souris;
	vue_.convertirClotureAVirtuelle((int) pointClique[0], (int) pointClique[1], clic);
	vue_.convertirClotureAVirtuelle((int) pointSouris[0], (int) pointSouris[1], souris);

	// On desactive les textures, sinon on arrive pas a bien afficher.
	glDisable(GL_TEXTURE_2D);

	parametresPointillee_.commencer();

	// On desactive le depth test pour affiche par dessus tout
	glDisable(GL_DEPTH_TEST);

	// XOR avec la couleur en dessous
	glLogicOp(GL_XOR);
	glEnable(GL_COLOR_LOGIC_OP);

	glPushMatrix();
		glBegin(GL_LINE_LOOP);
			glVertex2i((int)clic[0], (int)clic[1]);
			glVertex2i((int)clic[0], (int)souris[1]);
			glVertex2i((int)souris[0], (int)souris[1]);
			glVertex2i((int)souris[0], (int)clic[1]);
		glEnd();
	glPopMatrix();

	glDisable(GL_COLOR_LOGIC_OP);
	glEnable(GL_DEPTH_TEST);

	parametresPointillee_.finir();

	glEnable(GL_TEXTURE_2D);
}

void CommandeSelection::afficherRectangleElastiquePerspective(const Vecteur3& pointClique,
															  const Vecteur3& pointSouris) const
{
	// On desactive les textures, sinon on arrive pas a bien afficher.
	glDisable(GL_TEXTURE_2D);

	parametresPointillee_.commencer();

	// On desactive le depth test pour affiche par dessus tout
	glDisable(GL_DEPTH_TEST);

	// XOR avec la couleur en dessous
	glLogicOp(GL_XOR);
	glEnable(GL_COLOR_LOGIC_OP);
	
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
		glLoadIdentity();
		int viewport[4];
		glGetIntegerv(GL_VIEWPORT, viewport);
		glOrtho(0, viewport[2], viewport[3], 0, -1, 1);

		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
			glLoadIdentity();

			glBegin(GL_LINE_LOOP);
				glVertex2i((int)pointClique[0], (int)pointClique[1]);
				glVertex2i((int)pointClique[0], (int)pointSouris[1]);
				glVertex2i((int)pointSouris[0], (int)pointSouris[1]);
				glVertex2i((int)pointSouris[0], (int)pointClique[1]);
			glEnd();
		glPopMatrix();

		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	glDisable(GL_COLOR_LOGIC_OP);
	glEnable(GL_DEPTH_TEST);

	parametresPointillee_.finir();

	glEnable(GL_TEXTURE_2D);
}

bool CommandeSelection::rectangleCouvreBoite(const Vecteur3& pointClique,
											const Vecteur3& pointSouris,
											const Vecteur3& coinMin,
											const Vecteur3& coinMax) const
{
	Vecteur2 hautGauche(min(pointClique[0], pointSouris[0]), max(pointClique[1], pointSouris[1])),
			 basDroit(max(pointClique[0], pointSouris[0]), min(pointClique[1], pointSouris[1]));

	double left = max(hautGauche[0], coinMin[0]);
	double right = min(basDroit[0], coinMax[0]);
	double top = min(hautGauche[1], coinMax[1]);
	double bottom = max(basDroit[1], coinMin[1]);

	return (left < right && bottom < top);
}