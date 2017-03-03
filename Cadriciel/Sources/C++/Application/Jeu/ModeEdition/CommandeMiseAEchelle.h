/**
 * @file CommandeMiseAEchelle.h
 * @author The FloppyDisketeers
 * @date 2014-01-22
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef COMMANDE_MISE_A_ECHELLE_H
#define COMMANDE_MISE_A_ECHELLE_H

#include "CommandeModeEdition.h"
#include "../../Carte.h"

#include <vector>
using namespace std;

// Forward class declaration
class ElementJeuAbstrait;

/**
 * @class CommandeMiseAEchelle
 * @brief La classe CommandeMiseAEchelle permet de redimensionner un ou plusieurs objets selectionnes.
 */
class CommandeMiseAEchelle : public CommandeModeEdition {
	public:
		/**
		 * Constructeur
		 * @param vue La vue du jeu. Utilise pour transformer les points de l'ecran dans l'espace de la camera
		 * @param carte La carte sur laquelle ajouter l'objet.
		 * @param objetsSelectionnes Une reference vers un vecteur qui contiendra les objets selectionnes
		 */
											CommandeMiseAEchelle(const vue::Vue& vue, Carte& carte,
																const vector<ElementJeuAbstrait*>& objetsSelectionnes);

		/**
		 * Destructeur
		 */
		virtual							   ~CommandeMiseAEchelle();

		/**
		 * Execute la commande. Redimensionne le ou les objets selectionnes a
		 * partir du mouvement de la souris.
		 * @param mouseX	La position X de la souris
		 * @param mouseY	La position Y de la souris
		 * @param bouton	L'etat des boutons de la souris
		 * @param touche	Touche du clavier appuyee	
		 */
		virtual void						executer(int mouseX, int mouseY, int boutton, int touche);

	private:
		Carte& carte_;

		/** Reference vers une liste d'elements de jeu. Permet de modifier les
		 * objets selectionnes. */
		const vector<ElementJeuAbstrait*>&	objetsSelectionnes_;

		float precedentePosYSouris_;

		/** La vue du jeu pour transformer la position de la souris dans
		 * l'espace de la camera. */
		const vue::Vue&	vue_;

		// Facteur constant de division du delta de la souris
		float facteurMiseAEchelle_;

		// Taille constante minimale qu'un objet peut prendre
		float minTaille_;

		/**
		* Methode qui valide si une position est a l'interieur de la zone de jeu
		* @author Vincent Longpre
		*/
		bool validerPositionElement(ElementJeuAbstrait* elem, const aiVector3D& taille);

		/**
		* Methode qui valide si tous les elements sont inclus dans la zone de jeu
		*/
		bool validerPositionElements(vector<ElementJeuAbstrait*> elements, float diffY);
};

#endif

/**
 * @}
 */