/**
 * @file CommandeAjoutBarriere.h
 * @author The FloppyDisketeers
 * @date 2014-01-22
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef COMMANDE_AJOUT_BARRIERE_H
#define COMMANDE_AJOUT_BARRIERE_H

#include "CommandeModeEdition.h"

#include "../../Carte.h"

/**
 * @class CommandeAjoutBarriere
 * @brief La classe CommandeAjout permet d'ajouter une barriere sur la carte.
 */
class CommandeAjoutBarriere : public CommandeModeEdition {
	public:
		/**
		 * Constructeur
		 * @param vue	La vue du jeu. Utilise pour transformer les points de l'ecran dans l'espace de la camera
		 * @param carte La carte sur laquelle ajouter l'objet.
		 */
						CommandeAjoutBarriere(const vue::Vue& vue,
											  Carte& carte);

		/**
		 * Destructeur
		 */
		virtual		   ~CommandeAjoutBarriere();

		/**
		 * Execute la commande. Ajoute un nouvel objet a la position souhaite
		 * sur la carte.
		 * @param mouseX	La position X de la souris
		 * @param mouseY	La position Y de la souris
		 * @param bouton	L'etat des boutons de la souris
		 * @param touche	Touche du clavier appuyee	
		 */
		virtual void	executer(int mouseX, int mouseY, int boutton, int touche);

	private:
		/** La position en X de la souris lorsqu'on a commence a cliquer */
		int				clickedPositionX_;

		/** La position en Y de la souris lorsqu'on a commence a cliquer */
		int				clickedPositionY_;

		/** Type de l'objet a ajouter */
		Type		    type_;

		/** Reference vers la carte sur laquelle ajouter le nouvel objet */
		Carte&			carte_;

		/** Le bouton gauche de la souris est enfonce ? */
		bool			mousePremierClicked_;

		/** Le deuxieme click de la souris **/
		bool			mouseDeuxiemeClick_;

		/** Le click est relacher */
		bool			mouseClickRelacher_;

		/** La vue du jeu pour transformer la position de la souris dans
		 * l'espace de la camera. */
		const vue::Vue&	vue_;

		/**
		* Methode qui valide si une position est a l'interieur de la zone de jeu
		* @author Vincent Longpre
		*/
		bool validerPosition(Vecteur3& position);

		/**
		 * Affiche un X rouge au dessus du curseur
		 * @positionSouris La position de la souris dans l'espace de la camera
		 */
		void			afficheCurseurRouge(const Vecteur3& positionSouris) const;
};

#endif

/**
 * @}
 */