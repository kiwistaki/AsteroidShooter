//////////////////////////////////////////////////////////////////////////////
/// @file GestionnaireCollision.cpp
/// @author FloppyDisketeers
/// @date 2014-03-07
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "GestionnaireCollision.h"

#include "../ElementObjet/Accelerateur.h"
#include "../ElementObjet/Asteroide.h"
#include "../ElementObjet/Barriere.h"
#include "../ElementObjet/Portail.h"
#include "../ElementObjet/Projectile.h"
#include "../ElementObjet/Station.h"
#include "../ElementObjet/Vaisseau.h"
#include "../ElementObjet/VaisseauVirtuel.h"
#include "../ElementObjet/VaisseauJoueur.h"

#include "QuadTree.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireCollision::GestionnaireCollision(vector<ElementJeuAbstrait*>& vecteurElementsJeu, vector<Asteroide*>& vecteurAsteroides)
///
/// Constructeur par param�tres
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
GestionnaireCollision::GestionnaireCollision(vector<ElementJeuAbstrait*>& vecteurElementsJeu, vector<Asteroide*>& vecteurAsteroides, vector<Projectile*>& vecteurProjectiles)
		: conteneurElementsJeu_(vecteurElementsJeu), conteneurAsteroide_(vecteurAsteroides), conteneurProjectile_(vecteurProjectiles), quadTree_(NULL)
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireCollision::~GestionnaireCollision()
///
/// Destructeur
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
GestionnaireCollision::~GestionnaireCollision(){
	detruireQuadTree();
}

void GestionnaireCollision::initialiserQuadTree(const Vecteur2f& coinHautGauche, const Vecteur2f& coinBasDroite) {
	delete quadTree_;
	quadTree_ = new QuadTree(coinHautGauche, coinBasDroite);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireCollision::getConteneurAsteroides()
///
/// Retourne la r�f�rence vers le conteneur d'ast�roides
///
/// @return vector<Asteroide*>&
///
////////////////////////////////////////////////////////////////////////
vector<Asteroide*>&	GestionnaireCollision::getConteneurAsteroides(){
	return conteneurAsteroide_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireCollision::getConteneurElementsJeu()
///
/// Retourne la r�f�rence vers le conteneur des �l�ments contenu dans la carte
///
/// @return vector<ElementJeuAbstrait*>& 
///
////////////////////////////////////////////////////////////////////////
vector<ElementJeuAbstrait*>& GestionnaireCollision::getConteneurElementsJeu(){
	return conteneurElementsJeu_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireCollision::setConteneurAsteroides(vector<Asteroide*>& asteroides)
///
/// Sp�cifie la r�f�rence vers le conteneur d'ast�roides utilis�
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void GestionnaireCollision::setConteneurAsteroides(vector<Asteroide*>& asteroides){
	conteneurAsteroide_ = asteroides;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireCollision::setConteneurElementJeu(vector<ElementJeuAbstrait*>& elementsJeu)
///
/// Sp�cifie la r�f�rence vers le conteneur d'�l�ments de la carte utilis�
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void GestionnaireCollision::setConteneurElementJeu(vector<ElementJeuAbstrait*>& elementsJeu){
	conteneurElementsJeu_ = elementsJeu;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void GestionnaireCollision::addJoueur(Vaisseau* vaisseau)
///
/// Ajoute le joueur dans le vecteur
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void GestionnaireCollision::addJoueur(Vaisseau* vaisseau){
	conteneurVaisseaux_.push_back(vaisseau);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireCollision::checkCollisions()
///
/// V�rifie la pr�sence de collision(s) dans la carte et rempli le conteneur d'objet � traiter en cons�quence
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void GestionnaireCollision::checkCollisions(){
	
	// On popule le quad tree avec les nouvelles positions
	for (size_t i = 0; i < conteneurAsteroide_.size(); i++) {
		quadTree_->inserer(conteneurAsteroide_[i]);
	}

	for (size_t i = 0; i < conteneurElementsJeu_.size(); i++) {
		quadTree_->inserer(conteneurElementsJeu_[i]);
	}

	for (size_t i = 0; i < conteneurProjectile_.size(); i++) {
		quadTree_->inserer(conteneurProjectile_[i]);
	}

	for (size_t i = 0; i < conteneurVaisseaux_.size(); i++) {
		quadTree_->inserer(conteneurVaisseaux_[i]);
	}

	ElementJeuAbstrait* current;
	ElementJeuAbstrait* next;

	map<ElementJeuAbstrait*, set<ElementJeuAbstrait*>> dejaVus;

	//Vaisseaux
	for (size_t i = 0; i < conteneurVaisseaux_.size(); i++) {
		current = conteneurVaisseaux_[i];

		set<ElementJeuAbstrait*> objets = quadTree_->retrieve(current);
		set<ElementJeuAbstrait*>::iterator it = objets.begin();

		for (; it != objets.end(); ++it) {
			next = *it;

			if (current != next) {
				// Permet de garder toujours le m�me ordre
				ElementJeuAbstrait* plusPetitPtr = min(current, next);
				ElementJeuAbstrait* plusGrandPtr = max(current, next);

				// On v�rifie si on a pas d�j� effectuer cette pair de collisions
				map<ElementJeuAbstrait*, set<ElementJeuAbstrait*>>::iterator it = dejaVus.find(plusPetitPtr);
				bool dejaVu = false;

				if (it != dejaVus.end()) {
					set<ElementJeuAbstrait*>::iterator s_it = it->second.find(plusGrandPtr);
					if (s_it != it->second.end()) {
						dejaVu = true;
					}

				} else {
					dejaVus[plusPetitPtr] = set<ElementJeuAbstrait*>();
				}

				if (!dejaVu && current->checkCollision(next)) {
					conteneurElementATraiter_.push_back(make_pair(current, next));

					// Pour se rappeller qu'on a d�j� fait cette collision
					dejaVus[plusPetitPtr].insert(plusGrandPtr);
				}
			}
		}
	}

	/*
	//Collisions vaisseau - vaisseau 
	for (size_t i = 0; i < conteneurVaisseaux_.size(); i++) {
		current = conteneurVaisseaux_[i];

		set<ElementJeuAbstrait*> objets = quadTree_->retrieve(current);
		set<ElementJeuAbstrait*>::iterator it = objets.begin();

		for (; it != objets.end(); ++it) {
			next = *it;

			if (current != next) {
				// Permet de garder toujours le m�me ordre
				ElementJeuAbstrait* plusPetitPtr = min(current, next);
				ElementJeuAbstrait* plusGrandPtr = max(current, next);

				// On v�rifie si on a pas d�j� effectuer cette pair de collisions
				map<ElementJeuAbstrait*, set<ElementJeuAbstrait*>>::iterator it = dejaVus.find(plusPetitPtr);
				bool dejaVu = false;

				if (it != dejaVus.end()) {
					set<ElementJeuAbstrait*>::iterator s_it = it->second.find(plusGrandPtr);
					if (s_it != it->second.end()) {
						dejaVu = true;
					}

				} else {
					dejaVus[plusPetitPtr] = set<ElementJeuAbstrait*>();
				}

				if (!dejaVu && current->checkCollision(next)) {
					conteneurElementATraiter_.push_back(make_pair(current, next));

					// Pour se rappeller qu'on a d�j� fait cette collision
					dejaVus[plusPetitPtr].insert(plusGrandPtr);
				}
			}
		}
	}*/


	// Asteroides
	for (size_t i = 0; i < conteneurAsteroide_.size(); i++) {
		current = conteneurAsteroide_[i];

		set<ElementJeuAbstrait*> objets = quadTree_->retrieve(current);
		set<ElementJeuAbstrait*>::iterator it = objets.begin();

		for (; it != objets.end(); ++it) {
			next = *it;

			if (current != next) {
				// Permet de garder toujours le m�me ordre
				ElementJeuAbstrait* plusPetitPtr = min(current, next);
				ElementJeuAbstrait* plusGrandPtr = max(current, next);

				// On v�rifie si on a pas d�j� effectuer cette pair de collisions
				map<ElementJeuAbstrait*, set<ElementJeuAbstrait*>>::iterator it = dejaVus.find(plusPetitPtr);
				bool dejaVu = false;

				if (it != dejaVus.end()) {
					set<ElementJeuAbstrait*>::iterator s_it = it->second.find(plusGrandPtr);
					if (s_it != it->second.end()) {
						dejaVu = true;
					}

				} else {
					dejaVus[plusPetitPtr] = set<ElementJeuAbstrait*>();
				}

				if (!dejaVu && current->checkCollision(next)) {
					conteneurElementATraiter_.push_back(make_pair(current, next));

					// Pour se rappeller qu'on a d�j� fait cette collision
					dejaVus[plusPetitPtr].insert(plusGrandPtr);
				}
			}
		}
	}



	// ElementJeuAbstraits
	
	for (size_t i = 0; i < conteneurElementsJeu_.size(); i++) {
		current = conteneurElementsJeu_[i];
		set<ElementJeuAbstrait*> objets = quadTree_->retrieve(current);
		set<ElementJeuAbstrait*>::iterator it = objets.begin();

		for (; it != objets.end(); ++it) {
			next = *it;

			if (current != next) {
				// Permet de garder toujours le m�me ordre
				ElementJeuAbstrait* plusPetitPtr = min(current, next);
				ElementJeuAbstrait* plusGrandPtr = max(current, next);

				// On v�rifie si on a pas d�j� effectuer cette pair de collisions
				map<ElementJeuAbstrait*, set<ElementJeuAbstrait*>>::iterator it = dejaVus.find(plusPetitPtr);
				bool dejaVu = false;

				if (it != dejaVus.end()) {
					set<ElementJeuAbstrait*>::iterator s_it = it->second.find(plusGrandPtr);
					if (s_it != it->second.end()) {
						dejaVu = true;
					}

				} else {
					dejaVus[plusPetitPtr] = set<ElementJeuAbstrait*>();
				}


				if (!dejaVu && current->checkCollision(next)) {
					conteneurElementATraiter_.push_back(make_pair(current, next));

					// Pour se rappeller qu'on a d�j� fait cette collision
					dejaVus[plusPetitPtr].insert(plusGrandPtr);
				}
			}
		}
	}



	// Projectiles
	for (size_t i = 0; i < conteneurProjectile_.size(); i++) {
		current = conteneurProjectile_[i];
		set<ElementJeuAbstrait*> objets = quadTree_->retrieve(current);
		set<ElementJeuAbstrait*>::iterator it = objets.begin();

		for (; it != objets.end(); ++it) {
			next = *it;

			if (current != next) {
				// Permet de garder toujours le m�me ordre
				ElementJeuAbstrait* plusPetitPtr = min(current, next);
				ElementJeuAbstrait* plusGrandPtr = max(current, next);

				// On v�rifie si on a pas d�j� effectuer cette pair de collisions
				map<ElementJeuAbstrait*, set<ElementJeuAbstrait*>>::iterator it = dejaVus.find(plusPetitPtr);
				bool dejaVu = false;

				if (it != dejaVus.end()) {
					set<ElementJeuAbstrait*>::iterator s_it = it->second.find(plusGrandPtr);
					if (s_it != it->second.end()) {
						dejaVu = true;
					}

				} else {
					dejaVus[plusPetitPtr] = set<ElementJeuAbstrait*>();
				}

				if (!dejaVu && current->checkCollision(next)) {
					conteneurElementATraiter_.push_back(make_pair(current, next));

					// Pour se rappeller qu'on a d�j� fait cette collision
					dejaVus[plusPetitPtr].insert(plusGrandPtr);
				}
			}
		}
	}

	//quadTree_->afficher();

	// On vide le quad tree pour la prochaine it�ration
	quadTree_->clear();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn GestionnaireCollision::traiterCollisions()
///
/// Appel le traitement des collision pr�c�dement d�tect�es (par checkCollision())
///
/// @return void
///
////////////////////////////////////////////////////////////////////////
void GestionnaireCollision::traiterCollisions(){


	for(int i = 0; i < conteneurElementATraiter_.size(); ++i){
		conteneurElementATraiter_[i].first->traiterCollision(conteneurElementATraiter_[i].second);
	}

	//On vide le conteneur apres les avoir trait�s
	conteneurElementATraiter_.clear();
}

void GestionnaireCollision::detruireQuadTree() {
	conteneurVaisseaux_.clear();
	delete quadTree_;
	quadTree_ = NULL;
}