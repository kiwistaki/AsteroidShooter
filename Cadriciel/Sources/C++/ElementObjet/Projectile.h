///////////////////////////////////////////////////////////////////////////
/// @file Projectile.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "ElementJeuAbstrait.h"
#include "NoeudProjectile.h"

// Forward class declaration
class ArbreRenduINF2990;

/** @class Projectile
 *  @brief Cette classe qui permet de creer des Projectiles
 *
 *	La classe Projectile contiendra un pointeur vers un noeudProjectile afin que celle-ci s'occupe
 *	de la texture de la Projectile.
 */
class Projectile: public ElementJeuAbstrait
{
public:
	/// Constructeur
								Projectile();

	/// Constructeur par parametres
	/// @param positionDepart La position de depart
	/// @param taille La taille de l'element
	/// @param directionVitesse La vitesse de l'element
	/// @param poids Le poids de l'element
								Projectile(aiVector3D positionDepart,
										   aiVector3D taille, aiVector3D directionVitesse, float poids);
								Projectile(const Projectile& projectile);

	/// Destructeur
	virtual					   ~Projectile();

	/// Permet d'obtenir le type de l'element
	virtual Type				getType();

	/// Mise a jour
	virtual void				update(float deltaT);

	/// Permet de verifier la collision entre les types d'objets concernés et de les traiter
	virtual bool				checkCollision(ElementJeuAbstrait* element);
	virtual bool				checkCollision(Accelerateur* accelerateur) { return false; }
	virtual bool				checkCollision(Asteroide* asteroide);
	virtual bool				checkCollision(Barriere* barriere);
	virtual bool				checkCollision(Portail* portail);
	virtual bool				checkCollision(Projectile* projectile) { return false; }
	virtual bool				checkCollision(Station* station);
	virtual bool				checkCollision(Vaisseau* vaisseau);

	virtual void				traiterCollision(ElementJeuAbstrait* elementAbstrait);
	virtual void				traiterCollision(Barriere* barriere);
	virtual	void				traiterCollision(Portail* portail);
	virtual void				traiterCollision(Station* station);

	virtual void				traiterCollision(Accelerateur* accelerateur) {}
	virtual void				traiterCollision(Asteroide* asteroide);
	virtual void				traiterCollision(PositionDepart* positionDepart) {}
	virtual void				traiterCollision(Projectile* projectile) {}
	virtual void				traiterCollision(Vaisseau* vaisseau);
	
	// Permet de verifier si le projectile doit disparaitre
	inline bool					getDeathSentence() {return mustLeaveThisWorld_;}
	void						mustDie();

	/// Permet de cloner l'element
	virtual ElementJeuAbstrait*	clone() const;

	inline bool					canBeAttracted(){return canBeAttracted_;}
	void						setCanBeAttracted(bool canBeAttracted);

protected:

private:
	NoeudProjectile*			noeud_;

	bool						canBeAttracted_;		// Si l'objet peut etre encore attire par le portail.
	bool						mustLeaveThisWorld_;	// Quand le projectile va disparaitre
};

#endif
///////////////////////////////////////////////////////////////////////////
///@}
//////////////////////////////////////////////////////////////////////////