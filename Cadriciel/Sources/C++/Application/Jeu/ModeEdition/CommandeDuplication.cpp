#include "CommandeDuplication.h"
#include "../../../../../Commun/Utilitaire/BoiteEnglobanteOrientee.h"

#include "../../FacadeModele.h"

CommandeDuplication::CommandeDuplication(const vue::Vue& vue, Carte& carte,
										 const vector<ElementJeuAbstrait*>& objetsSelectionnes) : vue_(vue),
																								  carte_(carte),
																								  objetsSelectionnes_(objetsSelectionnes),
																								  clic_(false)
{
	for (unsigned int i = 0; i < objetsSelectionnes_.size(); i++) // Parcourir les elements selectionnes
	{
		ElementJeuAbstrait* elemCourant = objetsSelectionnes_[i]; // Obtenir l'element courant

		if (elemCourant->getType() != POSITIONDEPART)
		{
			if (elemCourant->getType() == PORTAIL) // Si l'element est un portail
			{
				if (DYNAMIC_CAST<Portail*>(elemCourant)->getFrere()->getSelectionne()) // Si son frere est selectionne aussi
				{
					ElementJeuAbstrait* clone = elemCourant->clone(); // Cloner l'element courant
					memoriserLiensParente(elemCourant, clone); // Memoriser le lien parent/clone
					etampes_.push_back(clone); // Inserer le clone dans le vecteur d'etampes
					carte_.ajouterElement(clone); // Ajouter le clone a la carte
				}
			}
			else
			{
				ElementJeuAbstrait* clone = elemCourant->clone(); // Cloner l'element courant
				etampes_.push_back(clone); // Inserer le clone dans le vecteur d'etampes
				carte_.ajouterElement(clone); // Ajouter le clone a la carte
			}
		}
	}

	for (unsigned int i = 0; i < etampes_.size(); i++) // Parcourir les etampes
	{
		ElementJeuAbstrait* clone1 = etampes_[i]; // Obtenir le clone courant

		if (clone1->getType() == PORTAIL) // Si le clone est un portail
		{
			if (DYNAMIC_CAST<Portail*>(clone1)->getFrere() == NULL) // Si le portail n'a pas de frere
			{
				map<ElementJeuAbstrait*, ElementJeuAbstrait*>::const_iterator parent1 = cloneParent_.find(clone1); // Trouver son parent
				
				if (parent1 != cloneParent_.end()) // Si le parent est trouve
				{
					Portail* parent2 = DYNAMIC_CAST<Portail*>(parent1->second)->getFrere(); // Trouver le frere du parent
					map<ElementJeuAbstrait*, ElementJeuAbstrait*>::const_iterator clone2 = parentClone_.find(parent2); // Trouver le clone du frere du parent

					if (clone2 != parentClone_.end()) // Si le clone du frere du parent est trouve
						rendreFreres(clone1, clone2->second); // Definir comme freres
				}
			}
		}	
	}
}

CommandeDuplication::~CommandeDuplication()
{
	for (unsigned int i = 0; i < etampes_.size(); i++) // Parcourir les etampes
	{
		ElementJeuAbstrait* elemCourant = etampes_[i]; // Obtenir l'etampe courante
		carte_.effacerElement(elemCourant); // La supprimer de la carte
	}

	etampes_.clear(); // Vider le vecteur d'etampes
}

void CommandeDuplication::executer(int mouseX, int mouseY, int bouton, int touche)
{
	// Debouncer
	if (bouton == 1)
		clic_ = true;

	if (!clic_ && etampes_.size() > 0) // Si on ne fait que deplacer la souris et que le vecteur d'etampes n'est pas vide
	{
		// Conversion de l'input (changement de systeme de coordonnees)
		Vecteur3 positionSouris;
		vue_.convertirClotureAVirtuelle(mouseX, mouseY, positionSouris);

		aiVector3D centre = trouverCentre(etampes_); // Trouver le centre des etampes

		for (unsigned int i = 0; i < etampes_.size(); i++) // Parcourir les etampes
		{
			ElementJeuAbstrait* elemCourant = etampes_[i]; // Obtenir l'etampe courante

			// Calculer la difference de position entre le centre et l'element courant
			aiVector3D posElemCourant = elemCourant->getPositionActuelle(); // Obtenir la position de l'element courant
			float diffCentreX = posElemCourant.x - centre.x; // Difference en X
			float diffCentreY = posElemCourant.y - centre.y; // Difference en Y

			// Calculer la nouvelle position
			Vecteur3f nouvellePos((float) positionSouris[0] + diffCentreX, (float) positionSouris[1] + diffCentreY, posElemCourant.z);
			elemCourant->setPositionActuelle(nouvellePos); // Definir la nouvelle position
		}
	}
	else if (bouton == -1 && clic_) // Si on clique
	{
		if (validerPositionElements(etampes_))
		{
			for (unsigned int i = 0; i < etampes_.size(); i++) // Parcourir les etampes
			{
				ElementJeuAbstrait* elemCourant = etampes_[i]; // Obtenir l'etampe courante
				ElementJeuAbstrait* clone = elemCourant->clone(); // Cloner l'etampe

				if (elemCourant->getType() == PORTAIL) // Si l'etampe courante est un portail
					memoriserLiensParente(elemCourant, clone); // Memoriser le lien parent/clone

				carte_.ajouterElement(clone); // Ajouter le clone a la carte
			}

			// Lier les portails clones freres
			for (unsigned int i = 0; i < carte_.getVecteurElement().size(); i++) // Parcourir les elements de la carte
			{
				ElementJeuAbstrait* clone1 = carte_.getVecteurElement()[i]; // Obtenir le clone courant

				if (clone1->getType() == PORTAIL) // Si le clone est un portail
				{
					map<ElementJeuAbstrait*, ElementJeuAbstrait*>::const_iterator parent1 = cloneParent_.find(clone1); // Trouver son parent
				
					if (parent1 != cloneParent_.end()) // Si le parent est trouve
					{
						Portail* parent2 = DYNAMIC_CAST<Portail*>(parent1->second)->getFrere(); // Trouver le frere du parent
						map<ElementJeuAbstrait*, ElementJeuAbstrait*>::const_iterator clone2 = parentClone_.find(parent2); // Trouver le clone du frere du parent

						if (clone2 != parentClone_.end()) // Si le clone du frere du parent est trouve
							rendreFreres(clone1, clone2->second); // Definir comme freres
					}
				}
			}
		}

		clic_ = false;
	}
}

aiVector3D CommandeDuplication::trouverCentre(vector<ElementJeuAbstrait*> elements)
{
	ElementJeuAbstrait* premier = elements[0]; // Obtenir le premier element
	aiVector3D posPremier = premier->getPositionActuelle(); // Obtenir la position du premier element

	// Definir le min/max en X et Y a la position du premier objet
	float xMin = posPremier.x;
	float xMax = posPremier.x;

	float yMin = posPremier.y;
	float yMax = posPremier.y;

	// Trouver le X min/max et Y min/max
	for (unsigned int i = 1; i < elements.size(); i++)
	{
		ElementJeuAbstrait* elemCourant = elements[i]; // Obtenir l'element courant
		aiVector3D posElemCourant = elemCourant->getPositionActuelle(); // Obtenir la position de l'element courant

		if (posElemCourant.x < xMin)
			xMin = posElemCourant.x;
		else
			if (posElemCourant.x > xMax)
				xMax = posElemCourant.x;

		if (posElemCourant.y < yMin)
			yMin = posElemCourant.y;
		else
			if (posElemCourant.y > yMax)
				yMax = posElemCourant.y;		
	}

	float largeurX = (xMax - xMin) / 2.0f; // Calculer la coordonnee X du centre des elements
	float centreX = xMin + largeurX;
	float hauteurY = (yMax - yMin) / 2.0f; // Calculer la coordonnee Y du centre des elements
	float centreY = yMin + hauteurY;

	return aiVector3D(centreX, centreY, 0);
}

void CommandeDuplication::memoriserLiensParente(ElementJeuAbstrait* parent, ElementJeuAbstrait* clone)
{
	// Memoriser les liens parent/clone
	pair<ElementJeuAbstrait*, ElementJeuAbstrait*> parentClone(parent, clone);
	pair<ElementJeuAbstrait*, ElementJeuAbstrait*> cloneParent(clone, parent);
	parentClone_.insert(parentClone);
	cloneParent_.insert(cloneParent);
}

void CommandeDuplication::rendreFreres(ElementJeuAbstrait* frere1, ElementJeuAbstrait* frere2)
{
	// Definir comme freres
	DYNAMIC_CAST<Portail*>(frere1)->setFrere(DYNAMIC_CAST<Portail*>(frere2));
	DYNAMIC_CAST<Portail*>(frere2)->setFrere(DYNAMIC_CAST<Portail*>(frere1));
}

bool CommandeDuplication::validerPositionElement(ElementJeuAbstrait* elem, Vecteur3& position)
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

bool CommandeDuplication::validerPositionElements(vector<ElementJeuAbstrait*> elements)
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		ElementJeuAbstrait* elemCourant = elements[i];
		aiVector3D posCourante = elemCourant->getPositionActuelle();
		Vecteur3 pos(posCourante.x, posCourante.y, posCourante.z);

		if (!validerPositionElement(elemCourant, pos))
			return false;
	}

	return true;
}