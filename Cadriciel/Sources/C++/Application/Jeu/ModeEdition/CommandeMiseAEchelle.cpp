#include "CommandeMiseAEchelle.h"
#include "../../../ElementObjet/ElementJeuAbstrait.h"

CommandeMiseAEchelle::CommandeMiseAEchelle(const vue::Vue& vue, Carte& carte,
											const vector<ElementJeuAbstrait*>& objetsSelectionnes) : vue_(vue), carte_(carte),
																								    objetsSelectionnes_(objetsSelectionnes)
{
	precedentePosYSouris_ = 0.0f;
	facteurMiseAEchelle_ = 100.0f;
	minTaille_ = 0.25f;
}

CommandeMiseAEchelle::~CommandeMiseAEchelle() {
}

void CommandeMiseAEchelle::executer(int mouseX, int mouseY, int bouton, int touche)
{
	// Conversion de l'input (changement de systeme de coordonnees)
	Vecteur3 positionSouris;
	vue_.convertirClotureAVirtuelle(mouseX, mouseY, positionSouris);

	if (bouton == 1)
	{
		if (objetsSelectionnes_.size() > 0)
		{
			// Calculer la difference entre la position actuelle de la souris et la precedente
			float diffY = (float)(positionSouris[1] - precedentePosYSouris_) / facteurMiseAEchelle_;

			if (validerPositionElements(objetsSelectionnes_, diffY))
			{
				for (int i = 0; i < objetsSelectionnes_.size(); i++) // Parcourir les elements selectionnes
				{
					ElementJeuAbstrait* elemCourant = objetsSelectionnes_[i]; // Obtenir l'element courant
					aiVector3D tailleCourante = elemCourant->getTaille(); // Obtenir la taille de l'element courant
			
					if (abs(diffY) < tailleCourante.x)
					{
						// Calcul des ratios d'aspect
						float ratioZX = tailleCourante.z / tailleCourante.x; // Calculer le ratio X/Z
						float ratioYZ = tailleCourante.y / tailleCourante.z; // Calculer le ratio Y/Z

						// Calcul des nouvelles tailles
						float nouvTailleX = tailleCourante.x + diffY; // Ajouter la difference a la taille en X de l'element
					
						if (elemCourant->getType() == BARRIERE) // Si l'element est une barriere, seulement redimensionner les X
						{
							elemCourant->setTaille(aiVector3D(nouvTailleX, elemCourant->getTaille().y, elemCourant->getTaille().z));
						}
						else
						{
							if (nouvTailleX > minTaille_)
							{
								float nouvTailleZ = nouvTailleX * ratioZX; // Calculer la nouvelle taille Z avec le ratio ZX
								float nouvTailleY = nouvTailleZ * ratioYZ; // Calculer la nouvelle taille Y avec le ratio YZ

								elemCourant->setTaille(aiVector3D(nouvTailleX, nouvTailleY, nouvTailleZ));
							}
						}
					}
				}
			}
		}
	}

	precedentePosYSouris_ = (float) positionSouris[1];
}

bool CommandeMiseAEchelle::validerPositionElement(ElementJeuAbstrait* elem, const aiVector3D& taille)
{
	elem->getBoiteEnglobanteOrientee().update(elem->getPositionActuelle(), elem->getAngle(), taille);
	float moitieLongueur = elem->getBoiteEnglobanteOrientee().getMoitieLongueur();
	float moitieHauteur = elem->getBoiteEnglobanteOrientee().getMoitieHauteur();

	float haut = (float) carte_.getZoneJeuY()[1]; // Bordure du haut
	float bas = (float) carte_.getZoneJeuY()[0]; // Bordure du bas
	float gauche = (float) carte_.getZoneJeuX()[0]; // Bordure de gauche
	float droite = (float) carte_.getZoneJeuX()[1]; // Bordure de droite

	bool okHaut = elem->getPositionActuelle()[1] + moitieHauteur < haut; // Si element plus bas que le haut
	bool okBas = elem->getPositionActuelle()[1] - moitieHauteur > bas; // Si element plus haut que le bas
	bool okGauche = elem->getPositionActuelle()[0] - moitieLongueur > gauche; // Si element a droite de la gauche
	bool okDroite = elem->getPositionActuelle()[0] + moitieLongueur < droite; // Si element a gauche de la droite

	if (okHaut && okBas && okGauche && okDroite)
		return true;
	else
		return false;
}

bool CommandeMiseAEchelle::validerPositionElements(vector<ElementJeuAbstrait*> elements, float diffY)
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		ElementJeuAbstrait* elemCourant = elements[i]; // Obtenir l'element courant
		aiVector3D tailleCourante = elemCourant->getTaille(); // Obtenir la taille de l'element courant
		aiVector3D nouvelleTaille = tailleCourante;

		if (abs(diffY) < tailleCourante.x)
		{
			// Calcul des ratios d'aspect
			float ratioZX = tailleCourante.z / tailleCourante.x; // Calculer le ratio X/Z
			float ratioYZ = tailleCourante.y / tailleCourante.z; // Calculer le ratio Y/Z

			// Calcul des nouvelles tailles
			float nouvTailleX = tailleCourante.x + diffY; // Ajouter la difference a la taille en X de l'element

			if (elemCourant->getType() == BARRIERE) // Si l'element est une barriere, seulement redimensionner les X
			{
				nouvelleTaille = aiVector3D(nouvTailleX, elemCourant->getTaille().y, elemCourant->getTaille().z);
			}
			else
			{
				if (nouvTailleX > minTaille_)
				{
					float nouvTailleZ = nouvTailleX * ratioZX; // Calculer la nouvelle taille Z avec le ratio ZX
					float nouvTailleY = nouvTailleZ * ratioYZ; // Calculer la nouvelle taille Y avec le ratio YZ

					nouvelleTaille = aiVector3D(nouvTailleX, nouvTailleY, nouvTailleZ);
				}
			}
		}

		/*ElementJeuAbstrait* elemTest = elemCourant->clone();
		elemTest->setTaille(nouvelleTaille);*/

		if (!validerPositionElement(elemCourant, nouvelleTaille))
			return false;
	}

	return true;
}