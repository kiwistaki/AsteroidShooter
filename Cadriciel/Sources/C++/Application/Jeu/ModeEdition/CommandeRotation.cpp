#include "CommandeRotation.h"
#include "../../../ElementObjet/ElementJeuAbstrait.h"
#include "../../../../../Commun/Utilitaire/Utilitaire.h"

const float CommandeRotation::facteurDivision_ = 0.1f;

CommandeRotation::CommandeRotation(const vue::Vue& vue, Carte& carte,
								   const vector<ElementJeuAbstrait*>& objetsSelectionnes) : vue_(vue),
																							carte_(carte),
								                    										objetsSelectionnes_(objetsSelectionnes)
{
	precedentePosYSouris_[0] = 0;
	precedentePosYSouris_[1] = 0;
}

CommandeRotation::~CommandeRotation() {
}

void CommandeRotation::executer(int mouseX, int mouseY, int bouton, int touche)
{
	if (objetsSelectionnes_.size() > 1 && bouton == 1) // S'il y a plus qu'un element selectionne et que le bouton est appuye
	{
		vue_.convertirClotureAVirtuelle(0, mouseY, precedentePosYSouris_);
		// Calculer la difference entre la position actuelle de la souris et la precedente
		float differenceSouris = (float)(actuellePosYSouris_[1]-precedentePosYSouris_[1]);

		//Trouver le centre de rotation du groupe d'objets
		aiVector3D centreRotation = trouverCentre();

		//Matrice de rotation personnelle pour positionner l'objet decentre
		aiMatrix4x4 matriceRotation;
		aiMatrix4x4::RotationZ((float)utilitaire::DEG_TO_RAD(differenceSouris*facteurDivision_),
							   matriceRotation); 
		
		if (validerPositionElements(objetsSelectionnes_, centreRotation, matriceRotation))
		{
			for (unsigned int i = 0; i < objetsSelectionnes_.size(); ++i)
			{
				ElementJeuAbstrait* elemCourant = objetsSelectionnes_[i];
				aiVector3D pos = elemCourant->getPositionActuelle();

				pos -= centreRotation;
				pos = matriceRotation*pos;
				pos += centreRotation;
			
				elemCourant->setPositionActuelle(pos);
			}
		}

		//Ajuster la derniere position en Y a la position actuelle de la souris
		precedentePosYSouris_[1] = actuellePosYSouris_[1];

	}
	else if(objetsSelectionnes_.size() == 1 && bouton == 1) // S'il y a un seul element selectionne  et que le bouton est appuye
	{
		ElementJeuAbstrait* elemCourant = objetsSelectionnes_[0];

		// Convertir la position de la souris
		vue_.convertirClotureAVirtuelle(0, mouseY, precedentePosYSouris_);

		// Calculer la difference entre la position actuelle de la souris et la precedente
		float differenceY = (float)(actuellePosYSouris_[1] - precedentePosYSouris_[1]);
		
		elemCourant->setAxe(Vecteur3f(0.0f, 0.0f, 1.0f));
		elemCourant->setAngle(elemCourant->getAngle() + differenceY); // Ajouter la difference a l'angle de l'objet

		//Ajuster la derniere position en Y a la position actuelle de la souris
		precedentePosYSouris_[1] = actuellePosYSouris_[1];
	}

	vue_.convertirClotureAVirtuelle(0, mouseY, actuellePosYSouris_);
}

aiVector3D CommandeRotation::trouverCentre()
{
	ElementJeuAbstrait* premier = objetsSelectionnes_[0]; // Obtenir le premier element
	aiVector3D posPremier = premier->getPositionActuelle(); // Obtenir la position du premier element

	// Definir le min/max en X et Y a la position du premier objet
	float xMin = posPremier.x;
	float xMax = posPremier.x;

	float yMin = posPremier.y;
	float yMax = posPremier.y;

	// Trouver le X min/max et Y min/max
	for (unsigned int i = 1; i < objetsSelectionnes_.size(); i++)
	{
		ElementJeuAbstrait* elemCourant = objetsSelectionnes_[i]; // Obtenir l'element courant
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

bool CommandeRotation::validerPositionElement(ElementJeuAbstrait* elem, Vecteur3& position)
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

bool CommandeRotation::validerPositionElements(vector<ElementJeuAbstrait*> elements, aiVector3D centre, aiMatrix4x4 matrice)
{
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		ElementJeuAbstrait* elemCourant = elements[i];
		aiVector3D posCourante = elemCourant->getPositionActuelle();

		posCourante -= centre;
		posCourante = matrice*posCourante;
		posCourante += centre;

		Vecteur3 pos(posCourante.x, posCourante.y, posCourante.z);

		if (!validerPositionElement(elemCourant, pos))
			return false;
	}

	return true;
}