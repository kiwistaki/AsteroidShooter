//////////////////////////////////////////////////////////////////////////////
/// @file ModeEdition.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_MODEEDITION_H__
#define __APPLICATION_MODEEDITION_H__

#include <vector>

#include "../JeuAbstrait.h"
#include "CommandeModeEdition.h"
#include "../../Carte.h"

/// Forward class declaration
class ElementJeuAbstrait;

using namespace std;

/// Enumerations des commandes 
enum ListeOutils {
	DEPLACEMENT,
	SELECTION,
	ROTATION,
	MISE_A_ECHELLE, 
	DUPLICATION,
	ZOOM,
	CREATION_BARRIERE_PROTECT,
	CREATION_PORTAIL,
	CREATION_BONUS_ACCEL,
	CREATION_STATION_SPATIALE,
	SUPPRESSION, 
	NOMBRE_COMMANDES,
	AUCUNE
};

///////////////////////////////////////////////////////////////////////////
/// @class ModeEdition
/// @brief Le mode edition permet a l'utilisateur d'ajouter, de modifier
///		   et de supprimer les objets (portails, bonus accelerateurs, 
///		   barrieres protectrices, stations, spatiales, positions de 
///		   depart) sur la zone de jeu. 
///		   Il est egalement possible modifier differentes constantes qui 
///		   affectent le comportement des objets.
///		   La zone de jeu creee peut etre sauvegardee dans un fichier XML.
///		   
/// @author FloppyDisketeers
/// @date 2014-01-21
///////////////////////////////////////////////////////////////////////////
class ModeEdition : public JeuAbstrait
{
public:
	/// Constructeur par defaut
									ModeEdition(Carte& carte, vue::Vue* vue);
	/// Destructeur
	virtual							~ModeEdition();
	/// Setter Unsetter pour la commande en cours
	void							setCommand(int numeroOutil);
	void							unsetCommand();
	/// Update recoit les informations et laisse le jeu analyser les donnees
	virtual void					update(float deltaT);

	/**
	 * Fonction qui permet de changer la position, l'angle de rotation et la
	 * taille de l'objet presentement selectionne. S'il n'y a pas d'objets
	 * selectionnes ou s'il y en a plus d'un, la fonction ne fera rien.
	 * @param posX La nouvelle position en X
	 * @param posY La nouvelle position en Y 
	 * @param posZ La nouvelle position en Z
	 * @param angle Le nouvel angle de rotation
	 * @param scaleX La nouvelle taille en X
	 * @param scaleY La nouvelle taille en Y
	 * @param scaleZ La nouvelle taille en Z
	 */
	void setPositionAngleScaleObjetSelectionne(float posX, float posY, float posZ,
											   float angle, float scaleX, float scaleY,
											   float scaleZ);

	/**
	 * Fonction qui retourne le nombre d'objets selectionnes
	 * @return Le nombre d'objets selectionnes
	 */
	inline vector<ElementJeuAbstrait*>& getObjetsSelectionnes() { return objetsSelectionnes_; }

private:
	/// Reference vers une liste d'elements de jeu. Permet de retourner les
	/// objets selectionnes.
	vector<ElementJeuAbstrait*> 	objetsSelectionnes_;
	/// Pointeur vers une commande en mode d'edition
	CommandeModeEdition*			commande_;
	/// Etat de la commande
	ListeOutils						commandeCourante_;
	ListeOutils						commandePrecendente_;

};

#endif // __APPLICATION_MODEEDITION_H__