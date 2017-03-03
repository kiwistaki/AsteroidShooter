/**
 * @file CommandeDuplication.h
 * @author The FloppyDisketeers
 * @date 2014-01-22
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef COMMANDE_DUPLICATION_H
#define COMMANDE_DUPLICATION_H

#include "CommandeModeEdition.h"
#include "../../Carte.h"
#include "../../../ElementObjet/Portail.h"

#include <vector>
#include <map>

using namespace std;

// Forward class declaration
class ElementJeuAbstrait;
 
/**
 * @class CommandeDuplication
 * @brief La classe CommandeDuplication permet de dupliquer un ou plusieurs objets selectionnes.
 */
class CommandeDuplication : public CommandeModeEdition {
	friend class CommandeDuplicationTest;

	public:
		/**
		 * Constructeur
		 * @param vue La vue du jeu. Utilise pour transformer les points de l'ecran dans l'espace de la camera
		 * @param carte La carte sur laquelle ajouter l'objet.
		 * @param objetsSelectionnes Une reference vers un vecteur qui contiendra les objets selectionnes
		 */
														CommandeDuplication(const vue::Vue& vue,
														Carte& carte,
														const vector<ElementJeuAbstrait*>& objetsSelectionnes);

		/**
		 * Destructeur
		 */
		virtual									   ~CommandeDuplication();

		/**
		 * Execute la commande. Duplique les objets selectionnes et les deplacent
		 * a partir du mouvement de la souris.
		 * @param mouseX	La position X de la souris
		 * @param mouseY	La position Y de la souris
		 * @param bouton	L'etat des boutons de la souris
		 * @param touche	Touche du clavier appuyee	
		 */
		virtual void								executer(int mouseX, int mouseY, int boutton, int touche);

	private:
		/** Reference vers la carte pour ajouter les nouveaux objets */
		Carte&										carte_;
		
		/** Reference vers une liste d'elements de jeu selectionnes */
		const vector<ElementJeuAbstrait*>&	objetsSelectionnes_;

		// Bouleen servant de debouncer au clic de souris
		bool clic_;
		
		/** La vue du jeu pour transformer la position de la souris dans
		 * l'espace de la camera. */
		const vue::Vue&	vue_;

		/**
		* @description Methode de travail privee permettant de trouver le centre d'un groupe d'elements selectionnes
		* @author Vincent Longpre
		*/
		aiVector3D trouverCentre(vector<ElementJeuAbstrait*> elements);

		// Vecteur d'element temporaires
		vector<ElementJeuAbstrait*> etampes_;

		// Maps permettant la duplication des portails
		map<ElementJeuAbstrait*, ElementJeuAbstrait*> parentClone_;
		map<ElementJeuAbstrait*, ElementJeuAbstrait*> cloneParent_;

		/**
		* @description Methode de travail qui memorise les liens parent/clone entre deux elements
		* @author Vincent Longpre
		*
		* @param L'element original qui a ete clone
		* @param Le clone de l'element original
		*/
		void memoriserLiensParente(ElementJeuAbstrait* parent, ElementJeuAbstrait* clone);

		/**
		* @description 
		* @author Vincent Longpre
		*
		* @param Le premier frere
		* @param Le deuxieme frere
		*/
		void rendreFreres(ElementJeuAbstrait* frere1, ElementJeuAbstrait* frere2);

		/**
		* Methode qui valide si une position est a l'interieur de la zone de jeu
		* @author Vincent Longpre
		*/
		bool validerPositionElement(ElementJeuAbstrait* elem, Vecteur3& position);

		/**
		* Methode qui valide si tous les elements sont inclus dans la zone de jeu
		*/
		bool validerPositionElements(vector<ElementJeuAbstrait*> elements);
};

#endif

/**
 * @}
 */