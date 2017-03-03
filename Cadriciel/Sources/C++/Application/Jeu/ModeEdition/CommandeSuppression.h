/**
 * @file CommandeSuppression.h
 * @author The FloppyDisketeers
 * @date 2014-01-22
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef COMMANDE_SUPPRESSION_H
#define COMMANDE_SUPPRESSION_H

#include <vector>

#include "CommandeModeEdition.h"
#include "../../Carte.h"
#include "../../../ElementObjet/Portail.h"

using namespace std;

// Forward class declaration
class ElementJeuAbstrait;

/**
 * @class CommandeSuppression
 * @brief La classe CommandeSuppression permet d'enlever un objet sur la carte.
 */
class CommandeSuppression : public CommandeModeEdition {
	public:
		/**
		 * Constructeur
		 * @param vue La vue du jeu. Utilise pour transformer les points de l'ecran dans l'espace de la camera
		 * @param carte La carte sur laquelle ajouter l'objet.
		 * @param objetsSelectionnes Une reference vers un vecteur qui contiendra les objets selectionnes
		 */
											CommandeSuppression(const vue::Vue& vue, Carte& carte,
																vector<ElementJeuAbstrait*>& objetsSelectionnes);

		/**
		 * Destructeur
		 */
		virtual								~CommandeSuppression();

		/**
		 * Execute la commande. Supprime un ou plusieurs objets de la carte
		 * courante.
		 * @param mouseX	La position X de la souris
		 * @param mouseY	La position Y de la souris
		 * @param bouton	L'etat des boutons de la souris
		 * @param touche	Touche du clavier appuyee	
		 */
		virtual void						executer(int mouseX, int mouseY, int boutton, int touche);

	private:
		/** Reference vers la carte sur laquelle ajouter le nouvel objet */
		Carte&								carte_;

		/** Reference vers une liste d'elements de jeu. Permet de modifier les
		 * objets selectionnes. */
		vector<ElementJeuAbstrait*>&		objetsSelectionnes_;

		/** La vue du jeu pour transformer la position de la souris dans
		 * l'espace de la camera. */
		const vue::Vue&	vue_;
};

#endif

/**
 * @}
 */