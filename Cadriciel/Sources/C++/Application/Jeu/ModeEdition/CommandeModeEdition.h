/**
 * @file CommandeModeEdition.h
 * @author The FloppyDisketeers
 * @date 2014-01-21
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef COMMANDE_MODE_EDITION_H
#define COMMANDE_MODE_EDITION_H

#include "../../../../../Commun/Utilitaire/Vue/Vue.h"

/**
 * @interface CommandeModeEdition
 * @brief L'interface CommandeModeEdition permet de definir les commandes qui peuvent etres executes sur les differents objets en mode edition.
 */
class CommandeModeEdition {
	public:
		/**
		 * Constructeur
		 */
						CommandeModeEdition() {}
		/**
		 * Destructeur
		 */
		virtual		   ~CommandeModeEdition() {}

		/**
		 * Fonction a implementer dans les classes derivees. Execute l'action
		 * que la commande doit effectuer
		 * @param mouseX	La position X de la souris
		 * @param mouseY	La position Y de la souris
		 * @param bouton	L'etat des boutons de la souris
		 * @param touche	Touche du clavier appuyee	
		 */
		virtual void	executer(int mouseX, int mouseY, int boutton, int touche) = 0;

	protected:
		/** Position en X de la souris */
		int				mouseX_;

		/** Position en Y de la souris */
		int				mouseY_;

		/** Derniere position en X de la souris */
		int				lastMouseX_;

		/** Derniere position en Y de la souris */
		int				lastMouseY_;

		/** Boutton presentement clique avec la souris */
		int				boutton_;

		/** Touche presentement appuye avec le clavier */
		int				touche_;
};

#endif

/**
 * @}
 */