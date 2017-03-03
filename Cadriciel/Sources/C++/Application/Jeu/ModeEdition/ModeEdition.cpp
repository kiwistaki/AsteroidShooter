/**
 * @file ModeEdition.cpp
 * @author Vincent Longpre
 * @date 2014-01-26
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */

#include "ModeEdition.h"
#include "CommandeAjoutStationSpatial.h"
#include "CommandeAjoutAccelerateur.h"
#include "CommandeAjoutBarriere.h"
#include "CommandeAjoutPortail.h"
#include "CommandeDeplacement.h"
#include "CommandeSelection.h"
#include "CommandeRotation.h"
#include "CommandeMiseAEchelle.h"
#include "CommandeDuplication.h"
#include "CommandeZoomLoupe.h"
#include "CommandeSuppression.h"

#include "assimp.hpp"
#include "aiMatrix4x4.h"
#include "aiVector3D.h"

#include "../../AffichageDebogage.h"
#include "../../../Application/FacadeModele.h"
#include "../../../Arbre/ArbreRenduINF2990.h"

ModeEdition::ModeEdition(Carte& carte, vue::Vue* vue) : JeuAbstrait(carte, vue), commande_(NULL) {
	commandeCourante_ = AUCUNE;
	commandePrecendente_ = AUCUNE;
	// Etablie les limites de la zone de jeu.
	carte_.setZoneJeu(3600);
	pourcentageDeplacement_ = 0.1f;
}

ModeEdition::~ModeEdition() {
	delete commande_;

	for(int i = 0; i < objetsSelectionnes_.size(); i++){
		objetsSelectionnes_[i]->setSelectionne(false);
	}
}

void ModeEdition::setCommand(int numeroOutil) {
	commandePrecendente_ = commandeCourante_;
	commandeCourante_ = (ListeOutils)numeroOutil;

	delete commande_;

	switch (numeroOutil) {
		case DEPLACEMENT :
			commande_ = new CommandeDeplacement(*vue_, carte_, objetsSelectionnes_);
			break;
		case SELECTION :
			commande_ = new CommandeSelection(*vue_, carte_, objetsSelectionnes_);
			break;
		case ROTATION :	
			commande_ = new CommandeRotation(*vue_, carte_, objetsSelectionnes_);
			break;
		case MISE_A_ECHELLE :
			commande_ = new CommandeMiseAEchelle(*vue_, carte_, objetsSelectionnes_);
			break;
		case DUPLICATION :
			commande_ = new CommandeDuplication(*vue_, carte_, objetsSelectionnes_);
			break;
		case ZOOM :
			commande_ = new CommandeZoomLoupe(*vue_);
			break;
		case CREATION_BARRIERE_PROTECT :
			commande_ = new CommandeAjoutBarriere(*vue_, carte_);
			break;
		case CREATION_PORTAIL :
			commande_ = new CommandeAjoutPortail(*vue_, carte_);
			break;
		case CREATION_BONUS_ACCEL :
			commande_ = new CommandeAjoutAccelerateur(*vue_, carte_);
			break;
		case CREATION_STATION_SPATIALE :
			commande_ = new CommandeAjoutStationSpatial(*vue_, carte_);
			break;
		case SUPPRESSION :
			commande_ = new CommandeSuppression(*vue_, carte_, objetsSelectionnes_);
			break;
		default:
			commande_ = 0;
			commandePrecendente_ = commandeCourante_;
			commandeCourante_ = AUCUNE;
			break;
	}
}
	
void ModeEdition::unsetCommand() {
	commandeCourante_ = AUCUNE;
	delete commande_;
	commande_ = NULL;
}

void ModeEdition::update(float deltaT) {

	if (commandeCourante_ != AUCUNE){
		commande_->executer(mouseX_, mouseY_, boutton_, touche_);
	}

	carte_.dessinerCadreZoneDeJeu();

	JeuAbstrait::update(deltaT);

	const vector<ElementJeuAbstrait*>& elements = carte_.getVecteurElement();
	for (size_t i = 0; i < elements.size(); i++) {
		elements[i]->update(deltaT);
	}

	// Update des boites englobantes
	FacadeModele::obtenirInstance()->obtenirArbreRenduINF2990()->animer(deltaT);
}

void ModeEdition::setPositionAngleScaleObjetSelectionne(float posX, float posY, float posZ,
														float angle, float scaleX, float scaleY,
														float scaleZ)
{
	if (objetsSelectionnes_.size() == 1) {
		objetsSelectionnes_[0]->setPositionActuelle(Vecteur3f(posX, posY, posZ));
		objetsSelectionnes_[0]->setAxe(Vecteur3f(0.0f, 0.0f, 1.0f));
		objetsSelectionnes_[0]->setAngle(angle);
		objetsSelectionnes_[0]->setTaille(Vecteur3f(scaleX, scaleY, scaleZ));
	}
}

/**
 * @}
 */