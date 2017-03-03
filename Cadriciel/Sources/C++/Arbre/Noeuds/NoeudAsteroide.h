/**
* @file NoeudAsteroide.h
* @author The FloppyDisketeers
* @date 2014-01-27
* @version 1.0
*
* @addtogroup inf2990 INF2990
* @{
*/
#ifndef NOEUD_ASTEROIDE_H
#define NOEUD_ASTEROIDE_H

#include "NoeudAbstrait.h"

/**
* @class NoeudAsteroide
* @brief Cette classe permet d'afficher un asteroide grace a l'arbre de rendu
*/
class NoeudAsteroide : public NoeudAbstrait {
public:
	/**
	* Constructeur. Creer la liste d'affichage pour l'asteroide
	* @param type Le type du noeud
	*/
	NoeudAsteroide(const std::string& type);

	/**
	* Constructeur par copie
	* @param src L'objet que l'on veut copier
	*/
	NoeudAsteroide(const NoeudAsteroide& src);

	/**
	* Destructeur
	*/
	~NoeudAsteroide();

	// Permet de determiner que l'asteroide est la cible du joueur virtuel
	// @param estCible Si l'asteroide est la cible ou non
	void setCible(bool estCible);

	/**
	* Animation du noeud
	*/
	virtual void	animer(float dt);

	/// Le dessin concret du noeud (pour le moment c'est temporaire
	virtual void	afficherConcret() const;

	// Permet de definir le rayon de l'asteroide
	// @param rayon Le rayon de l'asteroide
	void setRayon(float rayon);

	// Permet d'obtenir le rayon de l'asteroide
	float getRayon() const;

	void setAngleX(float angle){ angleX_ = angle;}
	void setAngleY(float angle){ angleY_ = angle;}
	void setAngleZ(float angle){ angleZ_ = angle;}

	float getAngleX(){ return angleX_;}
	float getAngleY(){ return angleY_;}
	float getAngleZ(){ return angleZ_;}

private:
	bool estCible_;
	float rayon_;
	float angleX_;
	float angleY_;
	float angleZ_;
};

#endif

/**
* @}
*/