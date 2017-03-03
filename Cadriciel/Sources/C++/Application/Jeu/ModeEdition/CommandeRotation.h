/**
 * @file CommandeRotation.h
 * @author The FloppyDisketeers
 * @date 2014-01-22
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef COMMANDE_ROTATION_H
#define COMMANDE_ROTATION_H

#include "CommandeModeEdition.h"
#include "assimp.hpp"
#include "aiVector3D.h"
#include "../../Carte.h"

#include <vector>
using namespace std;

// Forward class declaration
class ElementJeuAbstrait;

/**
 * @class CommandeRotation
 * @brief La classe CommandeRotation permet d'effectuer une rotation sur un ou plusieurs objets selectionnes.
 */
class CommandeRotation : public CommandeModeEdition 
{
public:
	/**
		 * Constructeur
		 * @param vue La vue du jeu. Utilise pour transformer les points de l'ecran dans l'espace de la camera
		 * @param carte La carte sur laquelle ajouter l'objet.
		 * @param objetsSelectionnes Une reference vers un vecteur qui contiendra les objets selectionnes
		 */
										CommandeRotation(const vue::Vue& vue, Carte& carte,
														const vector<ElementJeuAbstrait*>& objetsSelectionnes);

	/**
	 * Destructeur
	 */
	virtual								~CommandeRotation();

	/**
	* Execute la commande. Effectue une rotation sur le ou les objets selectionnes a partir du mouvement de la souris.
	* @param mouseX	La position X de la souris
	* @param mouseY	La position Y de la souris
	* @param bouton	L'etat des boutons de la souris
	* @param touche	Touche du clavier appuyee	
	*/
	virtual void						executer(int mouseX, int mouseY, int boutton, int touche);

private:
	/** Reference vers la carte pour ajouter les nouveaux objets */
	Carte&										carte_;

	/** Reference vers une liste d'elements de jeu. Permet de modifier les
	 * objets selectionnes. */
	const vector<ElementJeuAbstrait*>&	objetsSelectionnes_;

	Vecteur3							precedentePosYSouris_;
	Vecteur3							actuellePosYSouris_;

	/** La vue du jeu pour transformer la position de la souris dans
	 * l'espace de la camera. */
	const vue::Vue&						vue_;

	/**
	 * Permet de trouver le centre d'un groupe d'element.
	 * Servira au centre de rotation pour ce meme groupe d'elements.
	 */ 
	aiVector3D							trouverCentre();

	/// Facteur de division pour la rotation groupe
	static const float					facteurDivision_;

	/**
	* Methode qui valide si une position est a l'interieur de la zone de jeu
	* @author Vincent Longpre
	*/
	bool validerPositionElement(ElementJeuAbstrait* elem, Vecteur3& position);

	/**
	* Methode qui valide si tous les elements sont inclus dans la zone de jeu
	*/
	bool validerPositionElements(vector<ElementJeuAbstrait*> elements, aiVector3D centre, aiMatrix4x4 matrice);
};

#endif

/**
* @}
*/