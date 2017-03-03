#include <algorithm>

#include "CommandeSuppression.h"
#include "../../FacadeModele.h"

CommandeSuppression::CommandeSuppression(const vue::Vue& vue,
										 Carte& carte,
										 vector<ElementJeuAbstrait*>& objetsSelectionnes) :
										 vue_(vue),
										 carte_(carte),
										 objetsSelectionnes_(objetsSelectionnes)
{
}

CommandeSuppression::~CommandeSuppression() {
}

void CommandeSuppression::executer(int mouseX, int mouseY, int boutton, int touche)
{
	if(objetsSelectionnes_.size() > 0)
	{
		for (unsigned int i = 0; i < objetsSelectionnes_.size(); i++) // Parcourir les objets selectionnes
		{
			ElementJeuAbstrait* elemCourant = objetsSelectionnes_[i];

			if (elemCourant->getType() == PORTAIL) // Si l'element est un portail
			{
				Portail* frere = DYNAMIC_CAST<Portail*>(elemCourant)->getFrere(); // Obtenir son frere

				if (frere != NULL)
				{
					// Retirer le lien entre les deux freres
					frere->setFrere(NULL);
					DYNAMIC_CAST<Portail*>(elemCourant)->setFrere(NULL);

					if (!frere->getSelectionne()) // Si le frere n'est pas selectionne
						carte_.effacerElement(frere); // Effacer le frere de la carte
				}
			}
			
			carte_.effacerElement(elemCourant); // Effacer l'element courant
		}
		
		objetsSelectionnes_.clear(); // Vider le vecteur des elements selectionnes
	}
}