//////////////////////////////////////////////////////////////////////////////
/// @file Carte.cpp
/// @author FloppyDisketeers
/// @date 2014-01-25
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "Carte.h"

#include "../ElementObjet/Accelerateur.h"
#include "../ElementObjet/Asteroide.h"
#include "../ElementObjet/Barriere.h"
#include "../ElementObjet/Portail.h"
#include "../ElementObjet/Projectile.h"
#include "../ElementObjet/Station.h"
#include "../ElementObjet/Vaisseau.h"
#include "../ElementObjet/PositionDepart.h"
#include "../ElementObjet/VaisseauVirtuel.h"
#include "../ElementObjet/VaisseauJoueur.h"
#include "FoncteurType.h"

#include <cstdlib>
#include <ctime>

#include "FacadeModele.h"
#include "Vue.h"
#include "GestionnaireXML.h"
#include "GestionnaireSon.h"
#include "GestionnaireAnimation.h"

#include "../Arbre/ArbreRenduINF2990.h"

#include "../../../Commun/Utilitaire/Utilitaire.h"

#define NBMAXASTEROIDE 100
// Message d'erreur
const string erreurStationSpatialMin = "Erreur, il n'y a aucune station spatial sur la carte.";
const string erreurNbStationSpatial = "Erreur, le nombre de station spatial a sauver est plus grand que le nombre de station spatial present sur la carte.";
const string erreurNiveauDiffNonDefini = "Erreur, le niveau de difficulte n'est pas defini.";

////////////////////////////////////////////////////////////////////////
///
/// @fn Carte::Carte(string nom)
///
/// Constructeur
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Carte::Carte(string nom, ArbreRenduINF2990* arbreRendu) : nom_(nom), arbreRendu_(arbreRendu), nbMaxAsteroides_(NBMAXASTEROIDE), gestionnaireCollision_(conteneurElementsJeu_, conteneurAsteroide_, conteneurProjectile_)
{
	xMinZoneJeu_			= 0;
	xMaxZoneJeu_			= 0;
	yMinZoneJeu_			= 0;
	yMaxZoneJeu_			= 0;
	
	xMinCadreDepart_		= 0;
	xMaxCadreDepart_		= 0;
	yMinCadreDepart_		= 0;
	yMaxCadreDepart_		= 0;

	nbMinDeStationASauver_	= 1;
	frequenceAsteroides_	= 1.0f;
	accelerationBonus_		= 10;
	difficulte_				= -1;
	tempsCourant_			= 0.0f;
	joueur1_ = NULL;
	joueur2_ = NULL;

	nombreStations_ = 0;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Carte::Carte(Carte &carte)
///
/// Constructeur par copie
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Carte::Carte(Carte &carte):nbMaxAsteroides_(NBMAXASTEROIDE), gestionnaireCollision_(carte.getVecteurElement(), carte.getVecteurAsteroide(), carte.conteneurProjectile_)
{
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Carte::~Carte()
///
/// Destructeur
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Carte::~Carte()
{
	for(vector<ElementJeuAbstrait*>::iterator it = conteneurElementsJeu_.begin(); it != conteneurElementsJeu_.end(); ++it) {	
		delete (*it);
	}
	conteneurElementsJeu_.clear();

	for(vector<Asteroide*>::iterator it = conteneurAsteroide_.begin(); it != conteneurAsteroide_.end(); ++it) {	
		delete (*it);
	}
	conteneurAsteroide_.clear();

	for(vector<Projectile*>::iterator it = conteneurProjectile_.begin(); it != conteneurProjectile_.end(); ++it) {	
		delete (*it);
	}
	conteneurProjectile_.clear();

	delete joueur1_;
	delete joueur2_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::creerAsteroide()
///
/// Methode qui permet d'ajouter un element (usine)
///
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
Asteroide* Carte::creerAsteroide()
{	
	// On cree l'asteroide
	Asteroide* asteroide = new Asteroide( Vecteur4(xMinCadreDepart_,xMaxCadreDepart_,
												  yMinCadreDepart_,yMaxCadreDepart_),
										 Vecteur4(xMinZonePassage_,xMaxZonePassage_,
												  yMinZonePassage_,yMaxZonePassage_) );	
	conteneurAsteroide_.push_back(asteroide);

	return asteroide;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ajouterProjectile(Projectile* proj)
///
/// Methode qui permet d'ajouter un projectile
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::ajouterProjectile(Projectile* proj)
{
	conteneurProjectile_.push_back(proj);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::creerElementXML(TiXmlElement& element)
///
/// Methode qui permet d'ajouter un element avec un noeud XML
///
/// @param[in] TiXmlElement& element
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::creerElementParXML(TiXmlElement& element)
{
	int type;
	element.QueryIntAttribute("type", &type);

	ElementJeuAbstrait* elementJeu;

	Vecteur3 position2;
	float pos2X = 0.0;
	float pos2Y = 0.0;

	switch (type) {
	case ACCELERATEUR:
		elementJeu = new Accelerateur();
		break;

	case BARRIERE:
		elementJeu = new Barriere();
		break;

	case PORTAIL:
		elementJeu = new Portail();
		int idFrere;
		element.QueryIntAttribute("idFrere", &idFrere);
		DYNAMIC_CAST<Portail*>(elementJeu)->setIdFrere((unsigned long)idFrere);
		break;

	case STATION:
		elementJeu = new Station();
		nombreStations_ += 1;
		break;

	case POSITIONDEPART:
		elementJeu = new PositionDepart();
		break;

	default: 
		break;
	}

	// On set la position de l'objet
	Vecteur3 positionVirtuelle;
	double posX = 0.0;
	double posY = 0.0;
	element.QueryDoubleAttribute("posX", &posX);
	element.QueryDoubleAttribute("posY", &posY);
	positionVirtuelle[0] = posX;
	positionVirtuelle[1] = posY;
	elementJeu->setPositionActuelle(positionVirtuelle);
	
	// On set l'axe
	Vecteur3f axe;
	double axeX, axeY, axeZ;
	element.QueryDoubleAttribute("axeX", &axeX);
	element.QueryDoubleAttribute("axeY", &axeY);
	element.QueryDoubleAttribute("axeZ", &axeZ);
	axe[0] = (float)axeX;
	axe[1] = (float)axeY;
	axe[2] = (float)axeZ;
	elementJeu->setAxe(axe);

	// On set l'angle de l'objet
	double angle;
	element.QueryDoubleAttribute("angle", &angle);
	elementJeu->setAngle((float)angle);

	// On set la taille
	Vecteur3 taille;
	double tailleX, tailleY, tailleZ;
	element.QueryDoubleAttribute("tailleX", &tailleX);
	element.QueryDoubleAttribute("tailleY", &tailleY);
	element.QueryDoubleAttribute("tailleZ", &tailleZ);
	taille[0] = tailleX;
	taille[1] = tailleY;
	taille[2] = tailleZ;
	elementJeu->setTaille(taille);
	
	// On set le id
	int id;
	element.QueryIntAttribute("id", &id);
	elementJeu->setId((unsigned long)id);

	conteneurElementsJeu_.push_back(elementJeu);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::creerBarriere(Vecteur3 position1, Vecteur3 position2)
///
/// Methode qui permet d'ajouter une barrière
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::creerBarriere(Vecteur3 positionPremierClick, Vecteur3 positionDeuxiemeClick)
{
	Barriere* barriere = new Barriere();
	barriere->positionBarriere(positionPremierClick, positionDeuxiemeClick);
	conteneurElementsJeu_.push_back(barriere);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::effacerElement()
///
/// Methode qui permet d'effacer un element
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::effacerElement(ElementJeuAbstrait* element)
{
	// On ne peut pas effacer une position de depart
	if (element->getType() == POSITIONDEPART) {
		return;
	}

	for(vector<ElementJeuAbstrait*>::iterator it = conteneurElementsJeu_.begin(); it != conteneurElementsJeu_.end(); ++it) {
		if(element == *it) {
			// On détruit le pointeur a la position it
			conteneurElementsJeu_.erase(it);
			
			// On détruit l'élément
			delete element;
			element = NULL;

			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::effacerElement()
///
/// Methode qui permet d'effacer des éléments d'un certain type
///
/// @param element Le type d'élément a supprimer
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::effacerElementsType(int type)
{
	for(int i = (int)conteneurElementsJeu_.size() - 1; i >= 0; --i){
		if(conteneurElementsJeu_[i]->getType() == type) {
			delete conteneurElementsJeu_[i];
			conteneurElementsJeu_.erase(conteneurElementsJeu_.begin() + i);
		}
	}
}

void Carte::changerVisibilitePositionDepart(bool visible)
{
	for(int i = (int)conteneurElementsJeu_.size() - 1; i >= 0; --i){
		if(conteneurElementsJeu_[i]->getType() == POSITIONDEPART) {
			DYNAMIC_CAST<PositionDepart*>(conteneurElementsJeu_[i])->setVisible(visible);
		}
	}
}
////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::update()
///
/// Methode qui permet d'updater la carte
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::update(float deltaT) {
	//---------------------------------Astéroïdes-----------------------------------------

	tempsCourant_ += deltaT;

	// S'assurer d'avoir la bonne frequence d'apparition
	// et le bon nombre d'asteroides.
	if(tempsCourant_ > frequenceAsteroides_ && conteneurAsteroide_.size() <= nbMaxAsteroides_)
	{
		tempsCourant_ = 0;
		Asteroide* asteroideTemp = Carte::creerAsteroide();

		//Si il y a collision avec le nouvel astéroide, on le marque et on le supprime dès qu'on y arrive dans le vecteur
		for(int i = (int)conteneurAsteroide_.size() - 1; i >= 0; i--){

			if (asteroideTemp->checkCollision(conteneurAsteroide_[i]) && asteroideTemp->getId()!=conteneurAsteroide_[i]->getId()){
				asteroideTemp->setToBeDeleted(true);
			}

			if(conteneurAsteroide_[i]->isToBeDeleted()){
				conteneurAsteroide_[i]->setPointDeVie(0);
				conteneurAsteroide_[i]->setToBeDeleted(false);
				asteroidesADetruire_.insert(i);
			}
		}
		//---------------------------------------------------------------------------------------------------------------
	}
	
	// Verifier si l'asteroide se trouve a l'exterieur de la zone si oui la detruire
	if(conteneurAsteroide_.size() > 0){
		for(int i = (int)conteneurAsteroide_.size() - 1; i >= 0; --i)
		{
			// car indexation des elements et ajout d'un offset a cause des problemes d'arrondissement
			if (conteneurAsteroide_[i]->getPositionActuelle()[0] < xMinCadreDepart_-5 
			 || conteneurAsteroide_[i]->getPositionActuelle()[0] > xMaxCadreDepart_+5
			 || conteneurAsteroide_[i]->getPositionActuelle()[1] < yMinCadreDepart_-5
			 || conteneurAsteroide_[i]->getPositionActuelle()[1] > yMaxCadreDepart_+5
			 || (conteneurAsteroide_[i]->getPointDeVie() <= 0) ) // Et verifier s'il vient de mourir, mais il n'y a pas d'animation...
			{
				if (modeCoop_ && joueurVirtuel_) {
					if (DYNAMIC_CAST<Vaisseau*>(joueur2_)->getAstCible() == conteneurAsteroide_[i])
						joueur2_->setAstCibleNull();
				}

				// SON
				if((conteneurAsteroide_[i]->getPointDeVie() <= 0) ){
					GestionnaireSon::obtenirInstance()->jouerSon(EXPLOAST);
					/// ANIMATION
					if(!GestionnaireAnimation::obtenirInstance()->getAnimationAsteroid1EnCours()){

						GestionnaireAnimation::obtenirInstance()->setAnimationAsteroid1EnCours(true);
						GestionnaireAnimation::obtenirInstance()->setPositionAsteroid1X(conteneurAsteroide_[i]->getPositionActuelle().x);
						GestionnaireAnimation::obtenirInstance()->setPositionAsteroid1Y(conteneurAsteroide_[i]->getPositionActuelle().y);
						GestionnaireAnimation::obtenirInstance()->setRayonAsteroide1(conteneurAsteroide_[i]->getRayon());

					}else if(!GestionnaireAnimation::obtenirInstance()->getAnimationAsteroid2EnCours()){

						GestionnaireAnimation::obtenirInstance()->setAnimationAsteroid2EnCours(true);
						GestionnaireAnimation::obtenirInstance()->setPositionAsteroid2X(conteneurAsteroide_[i]->getPositionActuelle().x);
						GestionnaireAnimation::obtenirInstance()->setPositionAsteroid2Y(conteneurAsteroide_[i]->getPositionActuelle().y);
						GestionnaireAnimation::obtenirInstance()->setRayonAsteroide2(conteneurAsteroide_[i]->getRayon());
					}
				}

				conteneurAsteroide_[i]->setPointDeVie(0);
				asteroidesADetruire_.insert(i);
			}
		}
	}
	//--------------------------------------------------------------------------------------

	// Verifier si les projectiles sortent des bounds
	if(conteneurProjectile_.size() > 0){
		for(int i = (int)conteneurProjectile_.size() - 1; i >= 0; --i)
		{
			// car indexation des elements et ajout d'un offset a cause des problemes d'arrondissement
			if (conteneurProjectile_[i]->getPositionActuelle()[0] < xMinCadreDepart_+10 
			 || conteneurProjectile_[i]->getPositionActuelle()[0] > xMaxCadreDepart_-10
			 || conteneurProjectile_[i]->getPositionActuelle()[1] < yMinCadreDepart_+10
			 || conteneurProjectile_[i]->getPositionActuelle()[1] > yMaxCadreDepart_-10
			 || (conteneurProjectile_[i]->getDeathSentence() == true) ) // si le projectile doit mourir.			
			 {
				delete conteneurProjectile_[i];
				// Erase l'element du conteneur avec le reverse iterator... etrange
				conteneurProjectile_.erase( conteneurProjectile_.begin() + i );
			}
		}
	}
	//--------------------------------------------------------------------------------------
	
	// Verifier si la station est morte
	if(conteneurElementsJeu_.size() > 0){
		for(int i = (int)conteneurElementsJeu_.size() - 1; i >= 0; --i)
		{
			// car indexation des elements et ajout d'un offset a cause des problemes d'arrondissement
			if ( conteneurElementsJeu_[i]->getPointDeVie() <= 0 ) // Et verifier s'il vient de mourir, mais il n'y a pas d'animation...
			{
				// SON 
				GestionnaireSon::obtenirInstance()->jouerSon(EXPLOSTAT);
				// ANIMATION
				GestionnaireAnimation::obtenirInstance()->setAnimationStationEnCours(true);
				GestionnaireAnimation::obtenirInstance()->setPositionStationX(conteneurElementsJeu_[i]->getPositionActuelle().x);
				GestionnaireAnimation::obtenirInstance()->setPositionStationY(conteneurElementsJeu_[i]->getPositionActuelle().y);
				GestionnaireAnimation::obtenirInstance()->setRayonStation(conteneurElementsJeu_[i]->getRayon());

				elementsADetruire_.insert(i);
			}
		}

	}
	//--------------------------------------------------------------------------------------
	
	//-----Vérification des bounds de chacun des vaisseaux par-rapport à la zone de jeu------
		//Joueur #1
	if (joueur1_) {
		joueur1_->update(deltaT);
		aiVector3D direction = joueur1_->getDirectionVitesse();
		aiVector3D vitesse = joueur1_->getVitesse();

		math::BoiteEnglobanteOrientee boite = joueur1_->getBoiteEnglobanteOrientee();
		float dx = boite.getMoitieLongueur();
		float dy = boite.getMoitieHauteur();

		if( ((joueur1_->getPositionActuelle()[0] - dx) <= xMinZoneJeu_ && ((direction * aiVector3D(-1.0f, 0.0f, 0.0f)) > 0.0f || vitesse[0] * direction[0] < 0.0f)) ||
			((joueur1_->getPositionActuelle()[0] + dx) >= xMaxZoneJeu_ && ((direction * aiVector3D( 1.0f, 0.0f, 0.0f)) > 0.0f ||  vitesse[0] * direction[0] < 0.0f)) )
		{
			joueur1_->collisionZoneJeu('x');
		}
		
		if( ((joueur1_->getPositionActuelle()[1] - dy) <= yMinZoneJeu_ && ((direction * aiVector3D(0.0f, -1.0f, 0.0f)) > 0.0f || vitesse[1] * direction[1] < 0.0f)) ||
			((joueur1_->getPositionActuelle()[1] + dy) >= yMaxZoneJeu_ && ((direction * aiVector3D( 0.0f, 1.0f, 0.0f)) > 0.0f || vitesse[1] * direction[1] < 0.0f)) )
		{
			joueur1_->collisionZoneJeu('y');
		}

		//On vérifie si le vaisseau du joueur1 pointe vers un coins. Si oui, on bloque ses mouvements

		if(	   (boite.getCoins()[1][0] < xMinZoneJeu_ && boite.getCoins()[2][1] > yMaxZoneJeu_)
			|| (boite.getCoins()[2][0] > xMaxZoneJeu_ && boite.getCoins()[1][1] > yMaxZoneJeu_)
			|| (boite.getCoins()[2][0] < xMinZoneJeu_ && boite.getCoins()[1][1] < yMinZoneJeu_)
			|| (boite.getCoins()[1][0] > xMaxZoneJeu_ && boite.getCoins()[2][1] < yMinZoneJeu_) ){
			joueur1_->setBlocked(true);
		}else{
			joueur1_->setBlocked(false);
		}
	}

		//Joueur #2
	if (joueur2_) {
		joueur2_->update(deltaT);
		aiVector3D direction = joueur2_->getDirectionVitesse();
		aiVector3D vitesse = joueur2_->getVitesse();

		math::BoiteEnglobanteOrientee boite = joueur2_->getBoiteEnglobanteOrientee();
		float dx = boite.getMoitieLongueur();
		float dy = boite.getMoitieHauteur();

		if( ((joueur2_->getPositionActuelle()[0] - dx) <= xMinZoneJeu_ && ((direction * aiVector3D(-1.0f, 0.0f, 0.0f)) > 0.0f || vitesse[0] * direction[0] < 0.0f)) ||
			((joueur2_->getPositionActuelle()[0] + dx) >= xMaxZoneJeu_ && ((direction * aiVector3D( 1.0f, 0.0f, 0.0f)) > 0.0f  ||  vitesse[0] * direction[0] < 0.0f)) )
		{
			joueur2_->collisionZoneJeu('x');
		}
		
		if( ((joueur2_->getPositionActuelle()[1] - dy) <= yMinZoneJeu_ && ((direction * aiVector3D(0.0f, -1.0f, 0.0f)) > 0.0f || vitesse[1] * direction[1] < 0.0f)) ||
				  ((joueur2_->getPositionActuelle()[1] + dy) >= yMaxZoneJeu_ && ((direction * aiVector3D( 0.0f, 1.0f, 0.0f)) > 0.0f || vitesse[1] * direction[1] < 0.0f)) )
		{
			joueur2_->collisionZoneJeu('y');
		}
	}

	//----------------------------------------------------------------------------------------
	

	for (size_t i = 0; i < conteneurElementsJeu_.size(); i++) {
		conteneurElementsJeu_[i]->update(deltaT);
	}

	for (size_t i = 0; i < conteneurAsteroide_.size(); i++) {
		conteneurAsteroide_[i]->update(deltaT);
	}

	for (size_t i = 0; i < conteneurProjectile_.size(); i++) {
		conteneurProjectile_[i]->update(deltaT);
	}

	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->animer(deltaT);
	
	//On vérifie (rempli le vecteur d'objet a traiter) et on traite les collisions.
	gestionnaireCollision_.checkCollisions();
	gestionnaireCollision_.traiterCollisions();

	
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int Carte::getNbStationSpatial() const
///
/// Methode qui retourne le nombre de station spatial de la carte
///
/// @return nbDeStation : le nombre de station sur la carte.
///
////////////////////////////////////////////////////////////////////////
unsigned int Carte::getNbStationSpatial() 
{
	return Station::getNbStation();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int Carte::getNbMinStationASauver() const
///
/// Methode qui retourne le nombre minimal de station a sauver de la destruction des astéroides
///
/// @return nbStationMinASauver.
///
////////////////////////////////////////////////////////////////////////
unsigned int Carte::getNbMinStationASauver() const
{
	return nbMinDeStationASauver_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::setNbMinStationASauver(unsigned int nbStation)
///
/// Methode qui permet de modifier le nombre minimal de station a sauver
///
/// @param[in] nbStation : nb de station a sauver
/// 
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::setNbMinStationASauver(unsigned int nbStationMin)
{
	nbMinDeStationASauver_ = nbStationMin;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn float Carte::getFrequenceAsteroides() const
///
/// Methode qui retourne la frequence d'apparition des astéroides 
///
/// @return frequenceAsteroide.
///
////////////////////////////////////////////////////////////////////////
float Carte::getFrequenceAsteroides() const
{
	return frequenceAsteroides_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::setFrequenceAsteroides(float frequence)
///
/// Methode qui permet de modifier la frequence d'apparition des asteroides
///
/// @param[in] frequence : frequence d'apparition des asteroides
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::setFrequenceAsteroides(float frequence)
{
	frequenceAsteroides_ = frequence;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int Carte::getAccelerationBonus() const
///
/// Methode qui retourne l'acceleration fournie par les bonus accelerateurs
///
/// @return accelerationBonus.
///
////////////////////////////////////////////////////////////////////////
unsigned int Carte::getAccelerationBonus() const
{
	return accelerationBonus_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::setAccelerationBonus(unsigned int acceleration)
///
/// Methode qui permet de modifier l'acceleration fournie par les bonus
///
/// @param[in] acceleration : valeur des bonus d'acceleration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::setAccelerationBonus(unsigned int acceleration)
{
	accelerationBonus_ = acceleration;

}

////////////////////////////////////////////////////////////////////////
///
/// @fn int Carte::getDifficulte() const
///
/// Methode qui retourne la difficulte
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
int Carte::getDifficulte() const
{
	return difficulte_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::setDifficulte(int difficulte)
///
/// Methode qui permet de modifier la difficulte du jeu
///
/// @param[in] acceleration : valeur des bonus d'acceleration
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::setDifficulte(int difficulte)
{
	difficulte_ = difficulte;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn string Carte::getNom() const
///
/// Methode qui retourne le nom de la carte
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
string Carte::getNom() const
{
	return nom_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::setNom(const string nouveauNom)
///
/// Methode qui set le nom de la carte
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Carte::setNom(const string nouveauNom)
{
	nom_ = nouveauNom;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::setZoneJeu(const float largeurZone)
///
/// Methode Setter des limites de la zone de jeu qui doivent respecter le ratio.
/// Ces parametres doivent etre convertis dans la zone virtuelle
///
/// @param[in] largeurZone : largeur de la zone de jeu.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void Carte::setZoneJeu(const float largeurZone)
{
	float hauteurZone = largeurZone/RATIO;

	xMinZoneJeu_ = -largeurZone/2.0f;
	xMaxZoneJeu_ =  largeurZone/2.0f;
	yMinZoneJeu_ = -hauteurZone/2.0f;
	yMaxZoneJeu_ =  hauteurZone/2.0f;

	Carte::setCadreDepart(largeurZone, hauteurZone);
	Carte::setZonePassage(largeurZone, hauteurZone);

	Vecteur2f cadreX = getCadreDepartX();
	Vecteur2f cadreY = getCadreDepartY();

	Vecteur2f coinHautGauche(cadreX[0], cadreY[1]);
	Vecteur2f coinBasDroite(cadreX[1], cadreY[0]);
	gestionnaireCollision_.initialiserQuadTree(coinHautGauche, coinBasDroite);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::setCadreDepart(const float& largeurZone, const float& hauteurZone)
///
/// Setter des limites du cadre de depart. La largeur du cadre de depart correspond
/// a la 1.3*largeurZoneJeu et la hauteur du cadre = hauteurZone+0.3*largeurZone.
///
/// @param[in] largeurZone : largeur de la zone de jeu.
/// @param[in] hauteurZone : hauteur de la zone de jeu.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void Carte::setCadreDepart(const float& largeurZone, const float& hauteurZone)
{
	xMinCadreDepart_ = -(1.3f*largeurZone/2.0f);
	xMaxCadreDepart_ =  (1.3f*largeurZone/2.0f);
	yMinCadreDepart_ = -( (hauteurZone+0.3f*largeurZone)/2.0f );
	yMaxCadreDepart_ =  ( (hauteurZone+0.3f*largeurZone)/2.0f );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::setZonePassage(const float& largeurZone, const float& hauteurZone)
///
/// Setter des limites de la zone de passage.
///
/// @param[in] largeurZone : largeur de la zone de jeu.
/// @param[in] hauteurZone : hauteur de la zone de jeu.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void Carte::setZonePassage(const float& largeurZone, const float& hauteurZone)
{
	xMinZonePassage_ = -(0.7f*largeurZone)/2.0f;
	xMaxZonePassage_ =  (0.7f*largeurZone)/2.0f;
	yMinZonePassage_ = -( (hauteurZone - 0.3f*largeurZone)/2.0f) ;
	yMaxZonePassage_ =  ( (hauteurZone - 0.3f*largeurZone)/2.0f) ;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur2 Carte::getZoneJeuX() const
///
/// Methode qui retourne la cloture minimal et maximale de la 
/// zone de jeu dans l'axe des x.
///
/// @return Vecteur2
///
////////////////////////////////////////////////////////////////////////
Vecteur2f Carte::getZoneJeuX() const
{
	return Vecteur2f(xMinZoneJeu_, xMaxZoneJeu_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur2 Carte::getZoneJeuX() const
///
/// Methode qui retourne la cloture minimal et maximale de la 
/// zone de jeu dans l'axe des y.
///
/// @return Vecteur2
///
////////////////////////////////////////////////////////////////////////
Vecteur2f Carte::getZoneJeuY() const
{
	return Vecteur2f(yMinZoneJeu_, yMaxZoneJeu_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur2 Carte::getCadreDepartX() const
///
/// Methode qui retourne la cloture minimal et maximale du 
/// cadre de depart dans l'axe des x.
///
/// @return Vecteur2
///
////////////////////////////////////////////////////////////////////////
Vecteur2f Carte::getCadreDepartX() const
{
	return Vecteur2f(xMinCadreDepart_, xMaxCadreDepart_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Vecteur2 Carte::getCadreDepartY() const
///
/// Methode qui retourne la cloture minimal et maximale du 
/// cadre de depart dans l'axe des x.
///
/// @return Vecteur2
///
////////////////////////////////////////////////////////////////////////
Vecteur2f Carte::getCadreDepartY() const
{
	return Vecteur2f(yMinCadreDepart_, yMaxCadreDepart_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn vector<ElementJeuAbstrait*>& Carte::getVecteurElement()
///
/// Methode qui retourne la le conteneur des elements
///
/// @return Vecteur2
///
////////////////////////////////////////////////////////////////////////
vector<ElementJeuAbstrait*>& Carte::getVecteurElement() 
{
	return conteneurElementsJeu_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vector<ElementJeuAbstrait*>& Carte::getVecteurElement()
///
/// Methode qui retourne la le conteneur des elements
///
/// @return Vecteur2
///
////////////////////////////////////////////////////////////////////////
vector<Asteroide*>& Carte::getVecteurAsteroide() 
{
	return conteneurAsteroide_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn vector<ElementJeuAbstrait*>& Carte::getVecteurElement()
///
/// Methode qui retourne le conteneur de projectile
///
/// @return Vecteur2
///
////////////////////////////////////////////////////////////////////////
vector<Projectile*>& Carte::getVecteurProjectile()
{
	return conteneurProjectile_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool GestionnaireXML::niveauDeDifficulteDefini() const
///
/// Methode qui verifie si le niveau de difficulte a ete defini lors de la sauvegarde
///
/// @return Bool
///
////////////////////////////////////////////////////////////////////////
bool Carte::sauvegardeOk() const
{
	if (Station::getNbStation() < 1) {
		utilitaire::afficherErreur(erreurStationSpatialMin);

	} else if (nbMinDeStationASauver_ > Station::getNbStation()) {
		utilitaire::afficherErreur(erreurNbStationSpatial);

	} else if (difficulte_ == -1) {
		utilitaire::afficherErreur(erreurNiveauDiffNonDefini);

	} else {
		// Il y a au moin une station spatial, le nombre de station spatial est adequat, le niveau de difficulte est definie 
		return true;	
	}

	return false;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::ajouterElement(ElementJeuAbstrait* element)
///
/// Methode qui permet d'ajouter un element dans le conteneur
///
/// @return Bool
///
////////////////////////////////////////////////////////////////////////
void Carte::ajouterElement(ElementJeuAbstrait* element)
{
	conteneurElementsJeu_.push_back(element);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn Carte& Carte::operator=(Carte &carte)
///
/// Opérateur d'assignation
///
/// @return Carte& 
///
////////////////////////////////////////////////////////////////////////
Carte& Carte::operator=(Carte &carte)
{
	// On verifie que la carte a copier nest pas la meme
	if (&carte != this)
	{	
		// Detruire les éléments present dans la carte
		for (size_t i = 0; i < conteneurElementsJeu_.size(); i++) {
			delete conteneurElementsJeu_[i];
		}
		conteneurElementsJeu_.clear();

		this->detruireProjectiles();
		this->detruireAsteroides();
		this->detruireQuadTree();

		// Copie des elements 
		vector<ElementJeuAbstrait*> conteneurNouvelleCarte = carte.getVecteurElement();
		for (size_t i = 0; i < conteneurNouvelleCarte.size(); i++) {
			ElementJeuAbstrait* elementJeu = conteneurNouvelleCarte[i]->clone();
			conteneurElementsJeu_.push_back(elementJeu);
		}

		delete joueur1_;
		delete joueur2_;

		this->joueur1_ = carte.joueur1_;
		this->joueur2_ = carte.joueur2_;

		this->nom_ = carte.nom_;

		this->xMinZoneJeu_ = carte.xMinZoneJeu_;
		this->xMaxZoneJeu_ = carte.xMaxZoneJeu_;
		this->yMinZoneJeu_ = carte.yMinZoneJeu_;
		this->yMaxZoneJeu_ = carte.yMaxZoneJeu_;

		this->xMinCadreDepart_ = carte.xMinCadreDepart_;
		this->xMaxCadreDepart_ = carte.xMaxCadreDepart_;
		this->yMinCadreDepart_ = carte.yMinCadreDepart_;
		this->yMaxCadreDepart_ = carte.yMaxCadreDepart_;

		this->xMinZonePassage_ = carte.xMinZonePassage_;
		this->xMaxZonePassage_ = carte.xMaxZonePassage_;
		this->yMinZonePassage_ = carte.yMinZonePassage_;
		this->yMaxZonePassage_ = carte.yMaxZonePassage_;

		this->nbMinDeStationASauver_ = carte.nbMinDeStationASauver_;
		this->frequenceAsteroides_ = carte.frequenceAsteroides_;
		this->accelerationBonus_ = carte.accelerationBonus_;
		this->difficulte_ = carte.difficulte_;
		this->arbreRendu_ = carte.arbreRendu_;
		this->tempsCourant_ = carte.tempsCourant_;

		this->modeCoop_ = carte.modeCoop_;
		this->joueurVirtuel_ = carte.joueurVirtuel_;
		this->nombreStations_ = carte.nombreStations_;

		this->associerFreresPortails();
	}

	return *this;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::dessinerCadreZoneDeJeu()
///
/// Pour dessiner le contour de la zone de jeu.
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Carte::dessinerCadreZoneDeJeu()
{
	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
		glBegin(GL_LINE_LOOP);
			glColor3f( 0.0, 1.0, 0.0);
			glVertex3i((int)xMinZoneJeu_, (int)yMinZoneJeu_ , 0);
			glVertex3i((int)xMaxZoneJeu_, (int)yMinZoneJeu_ , 0);
			glVertex3i((int)xMaxZoneJeu_, (int)yMaxZoneJeu_ , 0);
			glVertex3i((int)xMinZoneJeu_, (int)yMaxZoneJeu_ , 0);
		glEnd();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glPopAttrib();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::dessinerCadreDepart()
///
/// Pour dessiner le contour du cadre de depart
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void Carte::dessinerCadreDepart()
{
	glPushAttrib(GL_CURRENT_BIT | GL_COLOR_BUFFER_BIT);

	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
		glBegin(GL_LINE_LOOP);
			//glColor3f( 1.0, 0.0, 0.0);
			glVertex2i((int)xMinCadreDepart_, (int)yMinCadreDepart_);
			glVertex2i((int)xMaxCadreDepart_, (int)yMinCadreDepart_);
			glVertex2i((int)xMaxCadreDepart_, (int)yMaxCadreDepart_);
			glVertex2i((int)xMinCadreDepart_, (int)yMaxCadreDepart_);
		glEnd();
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_LIGHTING);

	glPopAttrib();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn float Carte::getLargeur() const
///
/// Methode qui retourne la largeur de la zone de jeu
///
/// @return float : largeur de la carte
///
////////////////////////////////////////////////////////////////////////
float Carte::getLargeur() const
{
	return abs(xMaxZoneJeu_ - xMinZoneJeu_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn float Carte::getLargeur() const
///
/// Methode qui permet de set le joueur 1 a joueur reel ou joueur virtuel
///
/// @return float : largeur de la carte
///
////////////////////////////////////////////////////////////////////////
void Carte::setJoueur1(ModeJoueur mode)
{
	delete joueur1_;
	if(mode == VIRTUEL){
		joueur1_ = new VaisseauVirtuel();
	} else if (mode == REEL){
		joueur1_ = new VaisseauJoueur();
	}

	gestionnaireCollision_.addJoueur(joueur1_);

	joueur1_->setFacteurAcceleration(accelerationBonus_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Carte::setJoueur2(ModeJoueur mode)
///
/// Methode qui permet de set le joueur 2 a joueur reel ou joueur virtuel
///
/// @return 
///
////////////////////////////////////////////////////////////////////////
void Carte::setJoueur2(ModeJoueur mode)
{
	delete joueur2_;
	if(mode == VIRTUEL){
		joueur2_ = new VaisseauVirtuel(false);
	} else if (mode == REEL){
		joueur2_ = new VaisseauJoueur(false);
	} 

	gestionnaireCollision_.addJoueur(joueur2_);

	
	joueur2_->setFacteurAcceleration(accelerationBonus_);
}

Vecteur4f Carte::getCoinsZonePassage() const
{
	return Vecteur4f((float) xMinZonePassage_,
					 (float) xMaxZonePassage_,
					 (float) yMinZonePassage_,
					 (float) yMaxZonePassage_);
}

float Carte::getLargeurZonePassage() const
{
	return abs(xMaxZonePassage_ - xMinZonePassage_);
}

Vecteur4f Carte::getCoinsCadreDepart() const
{
	return Vecteur4f((float) xMinCadreDepart_,
					 (float) xMaxCadreDepart_,
					 (float) yMinCadreDepart_,
					 (float) yMaxCadreDepart_);
}

/// Methode qui permet de recuperer le joueur 1
Vaisseau* Carte::getJoueur1()
{
	return joueur1_;
}

/// Methode qui permet de recuperer le joueur 2
Vaisseau* Carte::getJoueur2()
{
	return joueur2_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn aiVector3D Carte::getPosDepartJoueur(int joueur) const
///
/// Methode qui retourne la position depart du joueurX
///
/// @param[in] int joueur
///
/// @return aiVector3D : position de depart du joueur
///
////////////////////////////////////////////////////////////////////////
aiVector3D Carte::getPosDepartJoueur(int joueur) const
{
	vector<ElementJeuAbstrait*>::const_iterator it;
	for(it = conteneurElementsJeu_.begin(); it != conteneurElementsJeu_.end(); it++){
		if((*it)->getType() == POSITIONDEPART){
			if((*it)->getId() == joueur){
				return (*it)->getPositionActuelle();
			}
		}
	}
	return (0.0f,0.0f,0.0f);
}

void Carte::echangerPositionDepartPourVaisseau()
{
	joueur1_->setPositionActuelle(getPosDepartJoueur(1));
	if (modeCoop_)
		joueur2_->setPositionActuelle(getPosDepartJoueur(2));

	changerVisibilitePositionDepart(false);
}

void Carte::echangerVaisseauPourPositionDepart()
{
	delete joueur1_;
	delete joueur2_;

	joueur1_ = NULL;
	joueur2_ = NULL;

	changerVisibilitePositionDepart(true);
}

void Carte::definirModeJoueurs(bool modeCoop, bool joueur2Virtuel)
{
	modeCoop_ = modeCoop;
	joueurVirtuel_ = joueur2Virtuel;
}

void Carte::detruireAsteroides()
{
	for (unsigned int i = 0; i < conteneurAsteroide_.size(); i++)
	{
		delete conteneurAsteroide_[i];
	}
	
	conteneurAsteroide_.clear();
}

void Carte::detruireProjectiles()
{
	for (unsigned int i = 0; i < conteneurProjectile_.size(); i++)
	{
		delete conteneurProjectile_[i];
	}
	
	conteneurProjectile_.clear();
}

void Carte::detruireObjets() {
	for (set<int, greater<int>>::iterator it = elementsADetruire_.begin();
		 it != elementsADetruire_.end(); ++it)
	{
		int idx = *it;

		if (conteneurElementsJeu_[idx]->getType() == STATION) {
			nombreStations_ -= 1;
		}

		delete conteneurElementsJeu_[idx];
		conteneurElementsJeu_.erase(conteneurElementsJeu_.begin() + idx);
	}
	elementsADetruire_.clear();

	for (set<int, greater<int>>::iterator it = asteroidesADetruire_.begin();
		 it != asteroidesADetruire_.end(); ++it)
	{
		int idx = *it;
		delete conteneurAsteroide_[idx];
		conteneurAsteroide_.erase(conteneurAsteroide_.begin() + idx);
	}
	asteroidesADetruire_.clear();
}


void Carte::associerFreresPortails() {
	for (size_t i = 0; i < conteneurElementsJeu_.size(); i++) {
		ElementJeuAbstrait* elem1 = conteneurElementsJeu_[i];

		if (elem1->getType() == PORTAIL) {
			Portail* portail1 = DYNAMIC_CAST<Portail*>(elem1);

			for (size_t j = i; j < conteneurElementsJeu_.size(); j++) {
				ElementJeuAbstrait* elem2 = conteneurElementsJeu_[j];

				if (elem2->getType() == PORTAIL) {
					if (portail1->getIdFrere() == DYNAMIC_CAST<Portail*>(elem2)->getId()) {
						Portail* portail2 = DYNAMIC_CAST<Portail*>(elem2);

						portail1->setFrere(portail2);
						portail2->setFrere(portail1);

						break;
					}
				}
			}
		}
	}
}

void Carte::detruireQuadTree() {
	gestionnaireCollision_.detruireQuadTree();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Carte::joueurIsProcheCadre()
///
/// Methode qui retourne vrai si le joueur est proche du cadre
///
/// @param[in] aucun
///
/// @return bool : vrai si le joueur est proche du cadre
///
////////////////////////////////////////////////////////////////////////
bool Carte::joueurIsProcheCadre(){
	bool isNearCadre = false;
	float const offSetCadre = 200.0f;

	if (joueur1_) {
		math::BoiteEnglobanteOrientee boite = joueur1_->getBoiteEnglobanteOrientee();
		float dx = boite.getMoitieLongueur();
		float dy = boite.getMoitieHauteur();

		if( ((joueur1_->getPositionActuelle()[0] - dx) <= xMinZoneJeu_ + offSetCadre) ||
			((joueur1_->getPositionActuelle()[0] + dx) >= xMaxZoneJeu_ - offSetCadre) ||
			((joueur1_->getPositionActuelle()[1] - dy) <= yMinZoneJeu_ + offSetCadre) ||
			((joueur1_->getPositionActuelle()[1] + dy) >= yMaxZoneJeu_ - offSetCadre) )
		{
			isNearCadre = true;
		}
	}

	if (joueur2_) {
		math::BoiteEnglobanteOrientee boite = joueur2_->getBoiteEnglobanteOrientee();
		float dx = boite.getMoitieLongueur();
		float dy = boite.getMoitieHauteur();

		if( ((joueur2_->getPositionActuelle()[0] - dx) <= xMinZoneJeu_ + offSetCadre) ||
			((joueur2_->getPositionActuelle()[0] + dx) >= xMaxZoneJeu_ - offSetCadre) ||
			((joueur2_->getPositionActuelle()[1] - dy) <= yMinZoneJeu_ + offSetCadre) ||
			((joueur2_->getPositionActuelle()[1] + dy) >= yMaxZoneJeu_ - offSetCadre) )
		{
			isNearCadre = true;
		}
	}

	return isNearCadre;
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////