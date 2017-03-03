/**
 * @file CommandeAjoutStationSpatial.h
 * @author The FloppyDisketeers
 * @date 2014-01-22
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef COMMANDE_AJOUTSTATIONSPATIAL_H
#define COMMANDE_AJOUTSTATIONSPATIAL_H

#include "CommandeModeEdition.h"

#include "../../Carte.h"

/**
 * @class CommandeAjoutStationSpatial
 * @brief La classe CommandeAjout permet d'ajouter une station spatial sur la carte.
 */
class CommandeAjoutStationSpatial : public CommandeModeEdition {
	public:
		/**
		 * Constructeur
		 * @param vue	La vue du jeu. Utilise pour transformer les points de l'ecran dans l'espace de la camera
		 * @param carte La carte sur laquelle ajouter l'objet.
		 */
						CommandeAjoutStationSpatial(const vue::Vue& vue,
													Carte& carte);

		/**
		 * Destructeur
		 */
		virtual		   ~CommandeAjoutStationSpatial();

		/**
		 * Execute la commande. Ajoute la station spatial a la position souhaite
		 * sur la carte.
		 * @param mouseX	La position X de la souris
		 * @param mouseY	La position Y de la souris
		 * @param bouton	L'etat des boutons de la souris
		 * @param touche	Touche du clavier appuyee	
		 */
		virtual void	executer(int mouseX, int mouseY, int boutton, int touche);

	private:
		/** La position en X de la souris lorsqu'on a commence a cliquer */
		int								clickedPositionX_;

		/** La position en Y de la souris lorsqu'on a commence a cliquer */
		int								clickedPositionY_;

		/** Type de l'objet a ajouter */
		Type		    type_;

		/** Reference vers la carte sur laquelle ajouter le nouvel objet */
		Carte&			carte_;

		/** Le bouton gauche de la souris est enfonce ? */
		bool			mouseClicked_;
		/** La vue du jeu pour transformer la position de la souris dans
		 * l'espace de la camera. */
		const vue::Vue&	vue_;

		/*Les attributs de la station spatial */
		/*ArbreRenduINF2990* arbreRendu_; 
		Vecteur3f positionDepart_;
		Vecteur3f taille_;
		Vecteur3f vitesse_;
		unsigned int poids_;
		unsigned int pointDeVie_;*/

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