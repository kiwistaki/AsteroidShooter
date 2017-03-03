#include "CommandeDeplacement.h"
#include "../../../ElementObjet/ElementJeuAbstrait.h"

CommandeDeplacement::CommandeDeplacement(const vue::Vue& vue, Carte& carte,
	const vector<ElementJeuAbstrait*>& objetsSelectionnes) : vue_(vue),
	carte_(carte),
	objetsSelectionnes_(objetsSelectionnes)
{
	precedentePosXSouris_ = 0.0f;
	precedentePosYSouris_ = 0.0f;
}

CommandeDeplacement::~CommandeDeplacement() {}

void CommandeDeplacement::executer(int mouseX, int mouseY, int bouton, int touche)
{
	// Conversion de l'input (changement de systeme de coordonnees)
	Vecteur3 positionSouris;
	vue_.convertirClotureAVirtuelle(mouseX, mouseY, positionSouris);

	if (bouton == 1)
	{
		if (objetsSelectionnes_.size() > 0)
		{
			// Calculer la difference entre la position actuelle de la souris et sa position precedente
			float diffX = (float) positionSouris[0] - precedentePosXSouris_; 
			float diffY = (float) positionSouris[1] - precedentePosYSouris_;

			if (validerPositionElements(objetsSelectionnes_, diffX, diffY))
			{
				for (unsigned int i = 0; i < objetsSelectionnes_.size(); i++) 
				{
					ElementJeuAbstrait* elemCourant = objetsSelectionnes_[i]; // Selectionner l'objet courant

					// Obtenir la position courante de l'element et calculer la nouvelle position avec la difference
					aiVector3D courantePosElem = elemCourant->getPositionActuelle();
					Vecteur3f nouvellePos(courantePosElem.x + diffX, courantePosElem.y + diffY, courantePosElem.z);

					// Definir la nouvelle position de l'element
					elemCourant->setPositionActuelle(nouvellePos);
				}
			}
		}
	}

	// Memoriser la position actuelles
	precedentePosXSouris_ = (float) positionSouris[0];
	precedentePosYSouris_ = (float) positionSouris[1];
}

bool CommandeDeplacement::validerPositionElement(ElementJeuAbstrait* elem, Vecteur3f& position)
{
	float moitieLongueur = elem->getBoiteEnglobanteOrientee().getMoitieLongueur();
	float moitieHauteur = elem->getBoiteEnglobanteOrientee().getMoitieHauteur();

	float haut = (float) carte_.getZoneJeuY()[1]; // Bordure du haut
	float bas = (float) carte_.getZoneJeuY()[0]; // Bordure du bas
	float gauche = (float) carte_.getZoneJeuX()[0]; // Bordure de gauche
	float droite = (float) carte_.getZoneJeuX()[1]; // Bordure de droite

	bool okHaut = position[1] + moitieHauteur < haut; // Si element plus bas que le haut
	bool okBas = position[1] - moitieHauteur > bas; // Si element plus haut que le bas
	bool okGauche = position[0] - moitieLongueur > gauche; // Si element a droite de la gauche
	bool okDroite = position[0] + moitieLongueur < droite; // Si element a gauche de la droite

	if (okHaut && okBas && okGauche && okDroite)
		return true;
	else
		return false;
}

bool CommandeDeplacement::validerPositionElements(vector<ElementJeuAbstrait*> elements, float diffX, float diffY)
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		ElementJeuAbstrait* elemCourant = elements[i]; // Obtenir l'element courant
		aiVector3D courantePosElem = elemCourant->getPositionActuelle(); // Obtenir sa position courante
		Vecteur3f nouvellePos(courantePosElem.x + diffX, courantePosElem.y + diffY, courantePosElem.z); // Calculer sa nouvelle position 

		if (!validerPositionElement(elemCourant, nouvellePos))
			return false;
	}

	return true;
}