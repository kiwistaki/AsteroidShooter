/**
 * @file CommandeSelection.h
 * @author The FloppyDisketeers
 * @date 2014-01-21
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef COMMANDE_SELECTION_H
#define COMMANDE_SELECTION_H

#include "CommandeModeEdition.h"
#include "../../Carte.h"
#include "../../../../../Commun/Utilitaire/Vue/Vue.h"
#include "../../../../../Commun/Utilitaire/LignePointillee.h"
#include "../../../../../Commun/Utilitaire/Vecteur.h"

#include <set>
#include <vector>
using namespace std;

#include <windows.h>
#include <GL/gl.h>

// Forward class declaration
class ElementJeuAbstrait;

/**
 * @class CommandeSelection
 * @brief La classe CommandeSelection permet de selectionner dans la carte des objets
 * de deux manieres differentes: de facon ponctuelle (un seul objet est
 * selectionne en cliquant dessus) ou avec une selection elastique (plusieurs
 * objets sont selectionnes).
 */
class CommandeSelection : public CommandeModeEdition {
	public:
		/**
		 * Constructeur
		 * @param vue La vue du jeu. Utilise pour transformer les points de l'ecran dans l'espace de la camera
		 * @param carte La carte sur laquelle ajouter l'objet.
		 * @param objetsSelectionnes Une reference vers un vecteur qui contiendra les objets selectionnes
		 */
										CommandeSelection(const vue::Vue& vue, Carte& carte,
														  vector<ElementJeuAbstrait*>& objetsSelectionnes);

		/**
		 * Destructeur
		 */
		virtual						   ~CommandeSelection();

		/**
		 * Execute la commande. Permet de selectionner des objets de 2
		 * manieres: soit de facon ponctuelle (1 objet) ou avec un rectangle
		 * de selection, pour avoir plusieurs objets.
		 * @param mouseX	La position X de la souris
		 * @param mouseY	La position Y de la souris
		 * @param bouton	L'etat des boutons de la souris
		 * @param touche	Touche du clavier appuyee	
		 */
		virtual	void					executer(int mouseX, int mouseY, int boutton, int touche);

	private:
		/** La carte qui contient tous les objets */
		Carte&							carte_;

		/** Reference vers une liste d'elements de jeu. Permet de retourner les
		 * objets selectionnes. */
		vector<ElementJeuAbstrait*>&	objetsSelectionnes_;

		/** Le bouton gauche de la souris est enfonce ? */
		bool							mouseClicked_;

		/** La position en X de la souris lorsqu'on a commence a cliquer */
		int								clickedPositionX_;

		/** La position en Y de la souris lorsqu'on a commence a cliquer */
		int								clickedPositionY_;

		/** Ensemble d'objets qui seront selectionnes si on relache le bouton de la souris */
		set<ElementJeuAbstrait*>		objetsSelectionnables_;

		/** Parametres pour les lignes pointillees */
		aidegl::LignePointillee			parametresPointillee_;

		/** Est-on en selection ponctuelle (false) ou elastique (true) */
		bool							modeSelection_;

		/** Liste d'objets qui sont presentement dans le rectangle elastique */
		set<ElementJeuAbstrait*>		objetsRectangleElastique_;

		/** Liste d'objets dont la selection a ete inverse (mode elastique) */
		set<ElementJeuAbstrait*>		objetsInverses_;

		/**
		 * Effectue une selection ponctuelle (un objet). Ne modifie pas tout de
		 * suite le vecteur d'objets selectionnes.
		 */
		void							selectionPonctuelle();

		/**
		 * Effectue une selection ponctuelle a l'aide de la vue orthogonale.
		 * Cette fonction utilise les boites englobantes orientees.
		 */
		void							selectionPonctuelleOrthogonale();

		/**
		 * Effectue une selection ponctuelle a l'aide de la vue perspective.
		 * Cette fonction utilise la fonction gluPickMatrix pour y parvenir.
		 */
		void							selectionPonctuellePerspective();

		/**
		 * Effectue une selection elastique (plusieurs objets). Ne modifie pas
		 * tout de suite le vecteur d'objets selectionnes.
		 * @param pointClique Le point où on a initialement clique
		 * @param pointSouris Le point où le souris se trouve presentement
		 */
		void							selectionElastique(const Vecteur3& pointClique,
														   const Vecteur3& pointSouris);
		/**
		 * Effectue une selection elastique à l'aide de la vue orthogonale.
		 * Cette fonction utilise les boites englobantes orientees.
		 * @param pointClique Le point où on a initialement clique
		 * @param pointSouris Le point où le souris se trouve presentement
		 */
		void							selectionElastiqueOrthogonale(const Vecteur3& pointClique,
																	  const Vecteur3& pointSouris);

		/**
		 * Effectue une selection elastique à l'aide de la vue perspective.
		 * Cette fonction utilise les boites englobantes orientees.
		 * @param pointClique Le point où on a initialement clique
		 * @param pointSouris Le point où le souris se trouve presentement
		 */
		void							selectionElastiquePerspective(const Vecteur3& pointClique,
																	  const Vecteur3& pointSouris);

		/**
		 * Affiche le rectangle elastique
		 * @param pointClique Le point où on a initialement clique
		 * @param pointSouris Le point où le souris se trouve presentement
		 */
		void							afficherRectangleElastique(const Vecteur3& pointClique,
																   const Vecteur3& pointSouris) const;

		/**
		 * Affiche le rectangle elastique en vue orthogonale
		 * @param pointClique Le point où on a initialement clique
		 * @param pointSouris Le point où la souris de trouve présentement
		 */
		void							afficherRectangleElastiqueOrthogonale(const Vecteur3& pointClique,
																			  const Vecteur3& pointSouris) const;

		/**
		 * Affiche le rectangle elastique en vue orthogonale
		 * @param pointClique Le point où on a initialement clique
		 * @param pointSouris Le point où la souris de trouve présentement
		 */
		void							afficherRectangleElastiquePerspective(const Vecteur3& pointClique,
																			  const Vecteur3& pointSouris) const;

		/**
		 * Verifie si le rectangle elastique recouvre la boite englobante
		 * @param pointClique Le point auquel on a clique en premier
		 * @param pointSouris Le point sur lequel la souris est presentement
		 * @param coinMin Le coin minimum de la boite englobante
		 * @param coinMax Le coin maximum de la boite englobante
		 * @return true si le rectangle elastique recouvre la boite englobante,
		 * false sinon.
		 */
		bool							rectangleCouvreBoite(const Vecteur3& pointClique,
															 const Vecteur3& pointSouris,
															 const Vecteur3& coinMin,
															 const Vecteur3& coinMax) const;

		/** La vue du jeu pour transformer la position de la souris dans
		 * l'espace de la camera. */
		const vue::Vue&	vue_;
};

#endif

/**
 * @}
 */