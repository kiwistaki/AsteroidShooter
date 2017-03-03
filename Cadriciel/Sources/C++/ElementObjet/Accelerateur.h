///////////////////////////////////////////////////////////////////////////
/// @file Accelerateur.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef ACCELERATEUR_H_
#define ACCELERATEUR_H_

#include "ElementJeuAbstrait.h"
#include "NoeudAccelerateur.h"

// Forward class declaration
class ArbreRenduINF2990;

/** @class Accelerateur
 *  @brief Cette classe qui permet de creer des accelerateurs
 *
 *	La classe Accelerateur contiendra un pointeur vers un noeudAccelerateur afin que celle-ci s'occupe
 *	de la texture de l'accelerateur.
 */
class Accelerateur: public ElementJeuAbstrait
{
public:
	/// Constructeur
	Accelerateur();

	/// Constructeur par parametres
	/// @param positionDepart La position de depart
	/// @param taille La taille de l'element
	/// @param directionVitesse La vitesse de l'element
	/// @param poids Le poids de l'element
								Accelerateur(Vecteur3f positionDepart,
											 Vecteur3f taille, Vecteur3f directionVitesse, float poids);
	/// Constructeur par copie
								Accelerateur(const Accelerateur& accelerateur);

	/// Destructeur
	virtual					   ~Accelerateur();

	/// Retourne le type de l'element
	virtual Type				getType();

	/// Mise a jour
	virtual void				update(float deltaT);

	/// Permet de cloner l'element
	virtual ElementJeuAbstrait*	clone() const;

	/// Permet de verifier la collision entre un accelerateur et un vaisseau ainsi que de la traiter
	virtual bool				checkCollision(Vaisseau* vaisseau);

	virtual bool				checkCollision(ElementJeuAbstrait* element);
	virtual bool				checkCollision(Accelerateur* accelerateur) { return false; }
	virtual bool				checkCollision(Asteroide* asteroide) { return false; }
	virtual bool				checkCollision(Barriere* barriere) { return false; }
	virtual bool				checkCollision(Portail* portail) { return false; }
	virtual bool				checkCollision(Projectile* projectile) { return false; }
	virtual bool				checkCollision(Station* station) { return false; }

	virtual	void				traiterCollision(Vaisseau* vaisseau);

	virtual void				traiterCollision(ElementJeuAbstrait* element) {}
	virtual void				traiterCollision(Accelerateur* accelerateur) {}
	virtual void				traiterCollision(Asteroide* asteroide) {}
	virtual void				traiterCollision(Barriere* barriere) {}
	virtual void				traiterCollision(Portail* portail) {}
	virtual void				traiterCollision(PositionDepart* positionDepart) {}
	virtual void				traiterCollision(Projectile* projectile) {}
	virtual void				traiterCollision(Station* station) {}

	static const double			TEMPS_DINACTIVITE;



protected:

private:
	NoeudAccelerateur*			noeud_;
	double						tempsAvantActif_;
	bool						isActif_;
};

#endif
///////////////////////////////////////////////////////////////////////////
///@}
//////////////////////////////////////////////////////////////////////////