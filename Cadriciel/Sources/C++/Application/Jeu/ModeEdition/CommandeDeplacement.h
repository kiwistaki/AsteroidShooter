/**
 * @file CommandeDeplacement.h
 * @author The FloppyDisketeers
 * @date 2014-01-22
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef COMMANDE_DEPLACEMENT_H
#define COMMANDE_DEPLACEMENT_H

#include <vector>

#include "CommandeModeEdition.h"
#include "../../Carte.h"

using namespace std;

// Forward class declaration
class ElementJeuAbstrait;

/**
 * @class CommandeDeplacement
 * @brief La classe CommandeDeplacement permet de modifier la position dans l'espace d'un ou de plusieurs objets selectionnes.
 */
class CommandeDeplacement : public CommandeModeEdition {
	public:
		/**
		 * Constructeur
		 * @param vue La vue du jeu. Utilise pour transformer les points de l'ecran dans l'espace de la camera
		 * @param carte La carte sur laquelle ajouter l'objet.
		 * @param objetsSelectionnes Une reference vers un vecteur qui contiendra les objets selectionnes
		 */
											CommandeDeplacement(const vue::Vue& vue, Carte& carte,
																const vector<ElementJeuAbstrait*>& objetsSelectionnes);

		/**
		 * Destructeur
		 */
		virtual							   ~CommandeDeplacement();

		/**
		 * Execute la commande. Deplace les objets selectionnes a partir du
		 * mouvement de la souris.
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
		/** La vue du jeu pour transformer la position de la souris dans
		 * l'espace de la camera. */
		const vue::Vue&	vue_;

		// Memorisation des coordonnes de la souris
		float precedentePosXSouris_;
		float precedentePosYSouris_;

		/**
		* Methode qui valide si une position est a l'interieur de la zone de jeu
		* @author Vincent Longpre
		*/
		bool validerPositionElement(ElementJeuAbstrait* elem, Vecteur3f& position);

		/**
		* Methode qui valide si tous les elements sont inclus dans la zone de jeu
		*/
		bool validerPositionElements(vector<ElementJeuAbstrait*> elements, float diffX, float diffY);
};

#endif

/**
 * @}
 */