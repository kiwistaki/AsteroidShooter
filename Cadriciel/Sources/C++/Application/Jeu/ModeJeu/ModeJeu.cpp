/**
* @file ModeJeu.cpp
* @author FLOPPY DISKETEERS
* @date 2014-01-26
* @version 1.0
*
* @addtogroup inf2990 INF2990
* @{
*/

#include "ModeJeu.h"
#include "aiVector3D.h"
#include "FacadeModele.h"
#include "GestionnaireSon.h"

ModeJeu::ModeJeu(Carte& carte, vue::Vue* vue) : JeuAbstrait(carte, vue)
{
	traitementInitial();
}

ModeJeu::~ModeJeu()
{
	carte_.changerVisibilitePositionDepart(true);
}

void ModeJeu::update(float deltaT)
{
	tempsJeu_ -= deltaT;
	FacadeModele::obtenirInstance()->setTempsJeu((int)tempsJeu_);
	FacadeModele::obtenirInstance()->setStatutJeu(0);

	bool resteDuTemps = tempsJeu_ > 0.0f;
	bool resteAssezDeStations = carte_.getNombreStations() >= carte_.getNbMinStationASauver();

	if (resteDuTemps) // S'il reste du temps
	{
		int coinMaxX, coinMaxY, longeurTexte;
		FacadeModele::obtenirInstance()->obtenirVue()->obtenirCoinsMax(coinMaxX, coinMaxY);
		Phont& monPhont = FacadeModele::obtenirInstance()->phontTexte_;
		longeurTexte = monPhont.getTextLength("Temps restant: 00:00");
		monPhont.print(coinMaxX, coinMaxY, (coinMaxX-longeurTexte) / 2, coinMaxY-36, true, "%s%2.2i:%2.2i", "Temps restant: ", (int) (tempsJeu_/60.0f), (int) tempsJeu_%60);
		
		if (resteAssezDeStations) // Et qu'il y a assez de stations
		{
			// Continuer la partie
			carte_.update(deltaT);
			logiqueVaisseaux(deltaT);
			carte_.detruireObjets();
		}
		else // Sinon
		{
			FacadeModele::obtenirInstance()->setStatutJeu(-1); // La partie est perdue
		}
	}
	else // S'il ne reste plus de temps
	{
		if (resteAssezDeStations) // Mais qu'il reste assez de stations
		{
			FacadeModele::obtenirInstance()->setStatutJeu(1); // La partie est gagnee
		}
		else // Sinon
		{
			FacadeModele::obtenirInstance()->setStatutJeu(-1); // La partie est perdue
		}
	}

	
	JeuAbstrait::update(deltaT);
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void ModeJeu::logiqueVaisseaux(float deltaT)
///
/// Methode qui s'occupe de la logique des vaisseaux Joueurs
///
/// @param float deltaT
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void ModeJeu::logiqueVaisseaux(float deltaT)
{
	const vector<int>& touches = FacadeModele::obtenirInstance()->getTouchesAppuyees();
	bool joueur1ToucheManoeuvre = false;
	bool joueur2ToucheManoeuvre = false;

	for (size_t i = 0; i < touches.size(); i++) {
		int touche = touches[i];


		/*---------------------------JOUEUR1-----------------------------*/
		if(joueur_1->isControlable()) {
			// ROTATION HORAIRE
			if( touche == (*commandesJoueur_)[J1ROT] ){
				joueur_1->virage(deltaT, -1);
			} 

			// ROTATION ANTI-HORAIRE
			else if(touche == (*commandesJoueur_)[J1ROTANTI]) {
				joueur_1->virage(deltaT, 1);

			}  

			// MANOEUVRE
			if(touche == (*commandesJoueur_)[J1MANOEUVRE]) {
				if(!manoeuvreJoueur1_) {
					manoeuvreJoueur1_ = true;
					joueur_1->manoeuvre();
				} 

				joueur1ToucheManoeuvre = true;
			} 

			// PROPULSION
			if(touche == (*commandesJoueur_)[J1PROP]) {
				joueur_1->seDeplacer(deltaT);

			}

			// TIR
			if(touche == (*commandesJoueur_)[J1TIR]) {
				joueur_1->attaquer(joueur_1->getDirectionVitesse(), joueur_1->getPositionActuelle(), deltaT);

			} 
		}

		/*-------------------------FIN-JOUEUR1---------------------------*/

		/*---------------------------JOUEUR2-----------------------------*/
		if(carte_.getModeCoop() && !carte_.getJoueur2Virtuel()) {
			if(joueur_2->isControlable()){
				// ROTATION HORAIRE
				if(touche == (*commandesJoueur_)[J2ROT]) {
					joueur_2->virage(deltaT, -1);		 

				}  
				// ROTATION ANTI-HORAIRE
				else if(touche == (*commandesJoueur_)[J2ROTANTI]) {
					joueur_2->virage(deltaT, 1);		

				}  

				// MANOEUVRE
				if(touche == (*commandesJoueur_)[J2MANOEUVRE]) {
					if(!manoeuvreJoueur2_) {
						manoeuvreJoueur2_ = true;
						joueur_2->manoeuvre();
					} 

					joueur2ToucheManoeuvre = false;
				}  

				// PROPULSION
				if(touche == (*commandesJoueur_)[J2PROP]) {
					joueur_2->seDeplacer(deltaT);

				}  

				// TIR
				if(touche == (*commandesJoueur_)[J2TIR]) {
					joueur_2->attaquer(joueur_2->getDirectionVitesse(), joueur_2->getPositionActuelle(), deltaT);
				}
			}
		}
		/*-------------------------FIN-JOUEUR2---------------------------*/
	}

	// Pour empecher deffectuer un million de rotation en appuyant une foi sur la touche
	if(manoeuvreJoueur1_ && !joueur1ToucheManoeuvre){
		manoeuvreJoueur1_ = false;
	}

	if(manoeuvreJoueur2_ && !joueur2ToucheManoeuvre){
		manoeuvreJoueur2_ = false;
	}
}

void ModeJeu::traitementInitial()
{
	// Etablie les limites de la zone de jeu.
	carte_.setZoneJeu(3600);

	// joueur1
	carte_.setJoueur1(REEL);
	joueur_1 = carte_.getJoueur1();
	joueur_1->setPositionActuelle(carte_.getPosDepartJoueur(1));

	if(carte_.getModeCoop()) {
		if (carte_.getJoueur2Virtuel()) {
			carte_.setJoueur2(VIRTUEL);
		} else {
			carte_.setJoueur2(REEL);
		}

		joueur_2 = carte_.getJoueur2();
		joueur_2->setPositionActuelle(carte_.getPosDepartJoueur(2));
	}

	manoeuvreJoueur1_ = false;
	manoeuvreJoueur2_ = false;

	// On recupere la map de commandes
	commandesJoueur_ = FacadeModele::obtenirInstance()->getMapCommandes();

	carte_.changerVisibilitePositionDepart(false);

	tempsJeu_ = (float)FacadeModele::obtenirInstance()->getDureeJeu();
	FacadeModele::obtenirInstance()->setTempsJeu((int)tempsJeu_);
	FacadeModele::obtenirInstance()->setStatutJeu(0);
}

/**
* @}
*/