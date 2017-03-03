/**
 * @file CommandeZoomLoupe.h
 * @author The FloppyDisketeers
 * @date 2014-01-21
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef COMMANDE_ZOOM_LOUPE_H
#define COMMANDE_ZOOM_LOUPE_H

#include "CommandeModeEdition.h"
#include "../../../../../Commun/Utilitaire/Vue/ProjectionOrtho.h"
#include "../../../../../Commun/Utilitaire/Vecteur.h"
#include "../../../../../Commun/Utilitaire/AideGL.h"
#include "../../../../../Commun/Utilitaire/LignePointillee.h"


/**
 * @interface CommandeZoomLoupe
 * @brief L'interface CommandeZoomLoupe permet de zoomer en creant
 * un rectangle elastique en mode edition.
 */
class CommandeZoomLoupe : public CommandeModeEdition
{
	public:
		/**
		 * Constructeur
		 * @param vue La vue du jeu. Utilise pour transformer les points de l'ecran dans l'espace de la camera
		 */
						CommandeZoomLoupe(vue::Vue& vue);

		/// Destructeur
		virtual		   ~CommandeZoomLoupe() {}

		/**
		 * Fonction a implementer dans les classes derivees. Execute l'action
		 * que la commande doit effectuer
		 * @param mouseX	La position X de la souris
		 * @param mouseY	La position Y de la souris
		 * @param bouton	L'etat des boutons de la souris
		 * @param touche	Touche du clavier appuyee	
		 */
		virtual void	executer(int mouseX, int mouseY, int boutton, int touche);

	private:
		/// Le bouton gauche de la souris est enfonce ?
		bool			mouseClicked_;
		/// La position en X de la souris lorsqu'on a commence a cliquer
		int				clickedPositionX_;
		/// La position en Y de la souris lorsqu'on a commence a cliquer
		int				clickedPositionY_;
	
		/// La position initiale du click de du rectangle
		Vecteur3		coinInitialRectangle_;
		/// Le parametre a envoye qui n'est pas virtuelle
		Vecteur3		coinInitialRectangleNonVirtuelle_;
		/// La position courante du rectangle
		Vecteur3		coinCourantRectangle_;
		/// Le parametre a envoye qui n'est pas virtuelle
		Vecteur3		coinCourantRectangleNonVirtuelle_;
		/// Est-on en selection ponctuelle (false) ou elastique (true)
		bool			modeRectangle_;

		/** La vue du jeu pour transformer la position de la souris dans
		 *  l'espace de la camera.
		 */
		vue::Vue&		vue_;


		
		
/////////////////////////////////////////////////////////////////////////////////////////////////////////
		/**
		 * Parametres pour les lignes pointillees 
		 */
		aidegl::LignePointillee	parametresPointillee_;

		/**
		 * Affiche le rectangle elastique
		 * @param pointClique Le point où on a initialement clique
		 * @param pointSouris Le point où le souris se trouve presentement
		 */
		void					afficherRectangleElastique(const Vecteur3& pointClique,
														   const Vecteur3& pointSouris);

};

#endif

/**
 * @}
 */