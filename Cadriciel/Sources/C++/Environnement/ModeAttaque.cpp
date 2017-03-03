///////////////////////////////////////////////////////////////////
/// @file ModeAttaque.cpp
/// @author FloppyDisketeers
/// @date 2014-02-25
/// @version 1.0
///
/// @addgroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////

#include "ModeAttaque.h"
#include "ModeApproche.h"
#include "ModeRecherche.h"
#include "../Application/AffichageDebogage.h"
#include <limits>

#include "../../../Commun/Utilitaire/Utilitaire.h"

ModeAttaque::ModeAttaque(Asteroide *asteroideCible, aiVector3D directionVaisseauAAsteroide) : asteroideCible_(asteroideCible)
{
	directionVaisseauAAsteroide_ = directionVaisseauAAsteroide;
	compteurTemps_ = 0;

	joueur1 = FacadeModele::obtenirInstance()->getCarte()->getJoueur1();

	direction = aiVector3D(0);
	posAsteroide = aiVector3D(0);
	angle_ = 0;

	tempsPourOrientation_ = 1.0f;

	// Comme ça on se ré-oriente tout de suite
	compteurTempsOrientation_ = tempsPourOrientation_;

	attaquer_ = false;
}

void ModeAttaque::update(VaisseauVirtuel &vaisseauVirtuel, float deltaT)
{
	attaquer_ = true;

	vaisseauVirtuel.decelerer(deltaT);

	if(asteroideCible_ != 0) {
		if(asteroideCible_->getPointDeVie() > 0) {
			// On recalcul la position de l'asteroide
			posAsteroide = asteroideCible_->getPositionActuelle();
			directionVaisseauAAsteroide_ = posAsteroide - vaisseauVirtuel.getPositionActuelle();

			// Calcul de la trajectoire de tire
			directionATirer_ = directionVaisseauAAsteroide_; // Moins bonne précision de tire, mais plus sécuritaire
			//directionATirer_ = directionVaisseauAAsteroide_ + asteroideCible_->getDirectionVitesse()*asteroideCible_->getModuleVitesse(); // Meilleur précision de tir, mais peut causer des attaques sur des stations

			// -----------------------------ORIENTATION------------------------------- //
			// On se ré-oriente à chaque fois

			if(abs(directionVaisseauAAsteroide_.x) > 0){
				angle_ = (float)(utilitaire::RAD_TO_DEG(atan2(directionVaisseauAAsteroide_.y, directionVaisseauAAsteroide_.x)) - 90);
			}
			vaisseauVirtuel.setAngle(angle_);
			// Calcul de la nouvelle direction
			direction.x = (float)cos(utilitaire::DEG_TO_RAD(angle_ + 90));
			direction.y = (float)sin(utilitaire::DEG_TO_RAD(angle_ + 90));
			vaisseauVirtuel.setDirectionVitesse(direction.Normalize());
			// ---------------------------FIN_ORIENTATION----------------------------- //

			// ------------------------------OBSTACLES-------------------------------- //
			// Verifier que l'on ne tire pas sur le vaisseau du joueur 1
			if(joueur1->intersectionTirVaisseau(vaisseauVirtuel.getPositionActuelle() ,directionATirer_.Normalize())) {
				attaquer_ = false;
			}
		
			// Verifier que l'on ne tire pas sur une station spatial ou sur une barriere
			obstacles_ = FacadeModele::obtenirInstance()->getCarte()->getVecteurElement();
			vector<ElementJeuAbstrait*>::iterator it;
			for(it = obstacles_.begin(); it != obstacles_.end(); it++) {
				int type = (*it)->getType(); 

				// On verifie que l'on ne tire pas sur une station
				if(type == STATION) {
					if((*it)->checkCollisionJoueurVirtuel(&vaisseauVirtuel)) {
						attaquer_ = false;
					} 
				}

				// On verifie que l'on ne tire pas sur une barriere
				if(attaquer_){
					if(type == BARRIERE) {
						if(((*it)->getPositionActuelle() - vaisseauVirtuel.getPositionActuelle()).Length() < directionVaisseauAAsteroide_.Length()) {
							if((*it)->checkCollisionJoueurVirtuel(&vaisseauVirtuel)) {
								attaquer_ = false;
							} 
						}
					}

					// On verifie que l'on ne tire pas sur un portail
					if(type == PORTAIL) {
						if((*it)->checkCollisionJoueurVirtuel(&vaisseauVirtuel)) {
							attaquer_ = false;
						} 
					}
				}	
			}
			// ----------------------------FIN_OBSTACLES------------------------------ //

			if (attaquer_) {
				// On attaque!
				vaisseauVirtuel.attaquer(directionATirer_.Normalize(), vaisseauVirtuel.getPositionActuelle(), deltaT);	
			}
	
			// Verifier que l'asteroide est ds les bounds
			if( posAsteroide[0] < minX_ || 
					posAsteroide[0] > maxX_ || 
					posAsteroide[1] < minY_ || 
					posAsteroide[1] > maxY_ ) {
				// L'asteroide est a l'exterieur de la zone de jeu;
				vaisseauVirtuel.decelerer(deltaT);
				AffichageDebogage::obtenirInstance()->afficherChangementModeJoueurVirtuel(RECHERCHE);
				asteroideCible_->setCible(false);
				vaisseauVirtuel.setEtat(new ModeRecherche());
				return;
			}

		} else {
			vaisseauVirtuel.decelerer(deltaT);
			AffichageDebogage::obtenirInstance()->afficherChangementModeJoueurVirtuel(RECHERCHE);
			vaisseauVirtuel.setEtat(new ModeRecherche());
			return;
		}

		if(directionVaisseauAAsteroide_.Length() > distancePasserModeAttaque_) {
			vaisseauVirtuel.decelerer(deltaT);
			AffichageDebogage::obtenirInstance()->afficherChangementModeJoueurVirtuel(APPROCHE);
			vaisseauVirtuel.setEtat(new ModeApproche(asteroideCible_));	
			return;
		}
	} else {
			vaisseauVirtuel.decelerer(deltaT);
			AffichageDebogage::obtenirInstance()->afficherChangementModeJoueurVirtuel(RECHERCHE);
			vaisseauVirtuel.setEtat(new ModeRecherche());
			return;
	}
}

const Mode ModeAttaque::getEtat() const
{
	return ATTAQUE;
}

///////////////////////////////////////////////////////////////////
///
/// @fn Asteroide* ModeAttaque::getAsteroideCible() const
///
/// Methode qui permet de retourner l'asteroide cible
///
/// @return Pointeur vers l'asteroide
///
///////////////////////////////////////////////////////////////////
Asteroide* ModeAttaque::getAsteroideCible() const
{
	return asteroideCible_;
}

void ModeAttaque::setAstNull()
{
	asteroideCible_ = 0;
}

///////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////