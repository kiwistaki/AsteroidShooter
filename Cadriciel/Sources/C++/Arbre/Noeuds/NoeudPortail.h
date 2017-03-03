/**
* @file NoeudPortail.h
* @author The FloppyDisketeers
* @date 2014-01-27
* @version 1.0
*
* @addtogroup inf2990 INF2990
* @{
*/
#ifndef NOEUD_PORTAIL_H
#define NOEUD_PORTAIL_H

#include "NoeudAbstrait.h"

/**
* @class NoeudPortail
* @brief Cette classe permet d'afficher un portail grace a l'arbre de rendu
*/
class NoeudPortail : public NoeudAbstrait {
public:
	/**
	* Constructeur. Creer la liste d'affichage pour le portail
	* @param type Le type du noeud
	*/
	NoeudPortail(const std::string& type);

	/**
	* Constructeur par copie
	* @param src L'objet que l'on veut copier
	*/
	NoeudPortail(const NoeudPortail& src);

	/**
	* Destructeur
	*/
	~NoeudPortail();

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