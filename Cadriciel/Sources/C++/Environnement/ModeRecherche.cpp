///////////////////////////////////////////////////////////////////
/// @file ModeRecherche.cpp
/// @author FloppyDisketeers
/// @date 2014-02-25
/// @version 1.0
///
/// @addgroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////

#include "ModeRecherche.h"
#include "ModeAttaque.h"
#include "ModeApproche.h"
#include "../Application/AffichageDebogage.h"
#include <time.h>
#include <limits>

#define DISTANCE_CIBLE_IMPOSSIBLE 9999.0
#define AUCUNE_CIBLE 0

///////////////////////////////////////////////////////////////////
///
/// @fn ModeRecherche::ModeRecherche()
///
/// Constructeur
///
/// @return Aucun (Constructeur).
///
///////////////////////////////////////////////////////////////////
ModeRecherche::ModeRecherche() 
{
	distanceStationACible_ = DISTANCE_CIBLE_IMPOSSIBLE;	
	distanceVaisseauACible_ = -1;

	posVaisseau_ = -1;

	asteroideCible_ = AUCUNE_CIBLE;

	tempsAttente_ = 2;
	compteurTemps_ = 0;
}

///////////////////////////////////////////////////////////////////
///
/// @fn void ModeRecherche::update(VaisseauVirtuel &vaisseauVirtuel)
///
/// Methode de logique de l'état du joueurVirtuel en mode recherche
///
/// @param[in] VaisseauVirtuel &vaisseauVirtuel : le vaisseau du joueur virtuel
///
/// @return Aucun 
///
///////////////////////////////////////////////////////////////////
void ModeRecherche::update(VaisseauVirtuel &vaisseauVirtuel, float deltaT)
{
	// On recupere la pos du vaisseau
	posVaisseau_ = vaisseauVirtuel.getPositionActuelle();

	// Attendre 2 secondes avant de chercher la cible (pour réalisme)
	compteurTemps_ += deltaT;
	if(compteurTemps_ >= tempsAttente_) {
		compteurTemps_ = 0;

		// On recupere le vecteur d'asteroide et d'element
		vecteurAsteroide_ = carte_->getVecteurAsteroide();
		vecteurElement_ = carte_->getVecteurElement();

		// Trouver une cible
		if(trouverAsteroideCible()){
			if(distanceVaisseauACible_ < distancePasserModeAttaque_){
				// La distance de la cible est plus pe tite que la distance pour passer en mode attaque
				// On passe en mode attaque!
				AffichageDebogage::obtenirInstance()->afficherChangementModeJoueurVirtuel(ATTAQUE);
				vaisseauVirtuel.setEtat(new ModeAttaque(asteroideCible_, asteroideCible_->getPositionActuelle() - vaisseauVirtuel.getPositionActuelle()));		
			} else {
				// La distance de la cible n'est pas plus grande
				// On s'approche de l'astéroide
				AffichageDebogage::obtenirInstance()->afficherChangementModeJoueurVirtuel(APPROCHE);
				vaisseauVirtuel.setEtat(new ModeApproche(asteroideCible_));	
			}
		} else {
			asteroideCible_ = AUCUNE_CIBLE;
		}
	}
}

bool ModeRecherche::trouverAsteroideCible()
{
	aiVector3D posStation;
	aiVector3D posAsteroide;
	float distanceAsteroideAStation;	

	for(vector<ElementJeuAbstrait*>::iterator it1 = vecteurElement_.begin(); it1 != vecteurElement_.end(); ++it1){
		if((*it1)->getType() == STATION){  
			posStation = (*it1)->getPositionActuelle();
			
			for(vector<Asteroide*>::iterator it2 = vecteurAsteroide_.begin(); it2 != vecteurAsteroide_.end(); ++it2){
				posAsteroide = (*it2)->getPositionActuelle();
					
				if( posAsteroide[0] < minX_ || 
				    posAsteroide[0] > maxX_ || 
				    posAsteroide[1] < minY_ || 
					posAsteroide[1] > maxY_ ) { // L'asteroide est a l'exterieur de la zone de jeu;
				} else {
					// Calcul de la distance entre la station et l'asteroide
					distanceAsteroideAStation = (posAsteroide - posStation).Length();

					// Si la distance entre l'asteroide et la station courrante est plus petite que la distance final actuelle
					// On remplace la distance final par la distance calculer
					if(distanceAsteroideAStation < distanceStationACible_){
						distanceStationACible_ = distanceAsteroideAStation;

						// Calcul de la distance entre le vaisseau et l'asteroide
						distanceVaisseauACible_ = (posAsteroide - posVaisseau_).Length();

						// On recupere l'asteroide cible
						asteroideCible_ = (*it2);
					}
				}
			}
		} 
	}

	if(asteroideCible_ == AUCUNE_CIBLE){
		return false;
	} else {
		asteroideCible_->setCible(true);
		return true;
	}
	return false;
}

///////////////////////////////////////////////////////////////////
///
/// @fn const Etat ModeRecherche::getEtat() const
///
/// Methode qui permet de determiner l'état actuel du vaisseau virtuel
///
/// @return Etat : enum de l'état du vaisseau 
///
///////////////////////////////////////////////////////////////////
const Mode ModeRecherche::getEtat() const
{
	return RECHERCHE;
}

///////////////////////////////////////////////////////////////////
///
/// @fn Asteroide* ModeRecherche::getAsteroideCible() const
///
/// Methode qui permet de retourner l'asteroide cible
///
/// @return Pointeur vers l'asteroide
///
///////////////////////////////////////////////////////////////////
Asteroide* ModeRecherche::getAsteroideCible() const
{
	return asteroideCible_;
}

void ModeRecherche::setAstNull()
{
	asteroideCible_ = 0;
}

///////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////