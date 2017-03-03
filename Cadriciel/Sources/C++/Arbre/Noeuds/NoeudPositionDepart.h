/**
* @file NoeudPositionDepart.h
* @author The FloppyDisketeers
* @date 2014-01-27
* @version 1.0
*
* @addtogroup inf2990 INF2990
* @{
*/
#ifndef NOEUD_POSITION_DEPART_H
#define NOEUD_POSITION_DEPART_H

#include "NoeudAbstrait.h"

/**
* @class NoeudPositionDepart
* @brief Cette classe permet d'afficher une position de depart grace a l'arbre de rendu
*/
class NoeudPositionDepart : public NoeudAbstrait {
public:
	/**
	* Constructeur. Creer la liste d'affichage pour la position de depart
	* @param type Le type du noeud
	*/
	NoeudPositionDepart(const std::string& type);

	/**
	* Constructeur par copie
	* @param src L'objet que l'on veut copier
	*/
	NoeudPositionDepart(const NoeudPositionDepart& src);

	/**
	* Destructeur
	*/
	~NoeudPositionDepart();

	/**
	* Animation du noeud
	*/
	virtual void	animer(float dt);

	/// Le dessin concret du noeud (pour le moment c'est temporaire
	virtual void	afficherConcret() const;
};

#endif

/**
* @}
*/