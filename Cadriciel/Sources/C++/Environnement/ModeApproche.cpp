///////////////////////////////////////////////////////////////////
/// @file ModeApproche.cpp
/// @author FloppyDisketeers
/// @date 2014-02-25
/// @version 1.0
///
/// @addgroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////

#include "ModeApproche.h"
#include "ModeAttaque.h"
#include "ModeRecherche.h"
#include "../ElementObjet/Station.h"
#include "../ElementObjet/Barriere.h"
#include "../Application/AffichageDebogage.h"
#include <limits>
#include "../../../Commun/Utilitaire/Utilitaire.h"


#define EPSILON numeric_limits<double>::epsilon()

ModeApproche::ModeApproche(Asteroide *asteroideCible) : asteroideCible_(asteroideCible)
{
	directionVaisseauAAsteroide_ = 0;
	posAsteroide_ = 0;
	posVaisseau_ = 0;
	angle_ = 0;
	angleTmp_ = 0;
	coordonneX_ = 0;
	coordonneY_ = 0;
	compteurEviterObs_ = 0;
	obstacle_ = false;
}

void ModeApproche::update(VaisseauVirtuel &vaisseauVirtuel, float deltaT)
{

	if(asteroideCible_ != 0) {
		// AB = B - A
		posAsteroide_ = asteroideCible_->getPositionActuelle();
		posVaisseau_ = vaisseauVirtuel.getPositionActuelle();
		directionVaisseauAAsteroide_ = posAsteroide_ - posVaisseau_;
		directionVaisseauAAsteroide_[2] = 0.0f;

		angle_ = vaisseauVirtuel.getAngle();

		// Si l'asteroide est a l'exterieur de la map on en cherche un nouveau
		if(posAsteroide_[0] < minX_ || 
			 posAsteroide_[0] > maxX_ || 
			 posAsteroide_[1] < minY_ || 
			 posAsteroide_[1] > maxY_ ) {

			AffichageDebogage::obtenirInstance()->afficherChangementModeJoueurVirtuel(RECHERCHE);
			asteroideCible_->setCible(false);
			vaisseauVirtuel.setEtat(new ModeRecherche());
			return;
		}

		if(distancePasserModeAttaque_ < directionVaisseauAAsteroide_.Length()){
			directionVaisseauAAsteroide_.Normalize();
			aiVector3D direction = vaisseauVirtuel.getDirectionVitesse();

			if(!obstacle_) {
				compteurEviterObs_ = 0;

			// TODO : s'assurer que l'on ne fonce pas ds un obstacle (station, barriere)
			obstacles_ = FacadeModele::obtenirInstance()->getCarte()->getVecteurElement();
			vector<ElementJeuAbstrait*>::iterator it;
			for(it = obstacles_.begin(); it != obstacles_.end(); it++) {
				if((*it)->getType() == STATION) {
					if(((*it)->getPositionActuelle() - vaisseauVirtuel.getPositionActuelle()).Length()  < distancePasserModeAttaque_) {
						if((*it)->checkCollisionJoueurVirtuel(&vaisseauVirtuel)) {
							obstacle_ = true;
							angle_+=90;
						} 
					}
				}

				if((*it)->getType() == BARRIERE){
					if((*it)->checkCollisionJoueurVirtuel(&vaisseauVirtuel)) {
						obstacle_ = true;
						aiVector3D pos = (*it)->getPositionActuelle();
						// La position de la barriere
						Vecteur3f posMilieu;	
						posMilieu[0] = pos.x;
						posMilieu[1] = pos.y;
						posMilieu[2] = pos.z;

						Vecteur3f vecteurBarrier = DYNAMIC_CAST<Barriere*>(*it)->getPositionPt1() - posMilieu;
						Vecteur3f vecteurPosAsteroide;
						vecteurPosAsteroide[0] = posAsteroide_.x;
						vecteurPosAsteroide[1] = posAsteroide_.y;
						vecteurPosAsteroide[2] = posAsteroide_.z;

						Vecteur3f barrierAAsteroide =  vecteurPosAsteroide - posMilieu;
					
						if(produitScalaire(vecteurBarrier, barrierAAsteroide) >= 0) {
							angle_+=90;
						} else {
							angle_-=90;
						}
					}
				} 
			}
		
			float incrementAngle = atan2(direction.x, direction.y) - atan2(directionVaisseauAAsteroide_.x, directionVaisseauAAsteroide_.y);
			angle_ += incrementAngle * deltaT * Vaisseau::VITESSE_ROTATION;

			} else {
				 compteurEviterObs_ += deltaT; 

				 if(compteurEviterObs_ >= 1){
					obstacle_ = false;
				 }
			}

			vaisseauVirtuel.setAngle(angle_);

			// Calcul de la nouvelle direction
			direction.x = (float)cos(utilitaire::DEG_TO_RAD(angle_ + 90));
			direction.y = (float)sin(utilitaire::DEG_TO_RAD(angle_ + 90));
			vaisseauVirtuel.setDirectionVitesse(direction);	

			vaisseauVirtuel.seDeplacer(deltaT);

		} else {

			AffichageDebogage::obtenirInstance()->afficherChangementModeJoueurVirtuel(ATTAQUE);
			vaisseauVirtuel.setEtat(new ModeAttaque(asteroideCible_, directionVaisseauAAsteroide_));
			return;
		}
	} else {

			AffichageDebogage::obtenirInstance()->afficherChangementModeJoueurVirtuel(RECHERCHE);
			vaisseauVirtuel.setEtat(new ModeRecherche());
			return;
	}
}

const Mode ModeApproche::getEtat() const
{
	return APPROCHE;
}


///////////////////////////////////////////////////////////////////
///
/// @fn Asteroide* ModeApproche::getAsteroideCible() const
///
/// Methode qui permet de retourner l'asteroide cible
///
/// @return Pointeur vers l'asteroide
///
///////////////////////////////////////////////////////////////////
Asteroide* ModeApproche::getAsteroideCible() const
{
	return asteroideCible_;
}

void ModeApproche::setAstNull()
{
	asteroideCible_ = 0;
}



///////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////