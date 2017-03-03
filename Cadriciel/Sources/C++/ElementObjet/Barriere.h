///////////////////////////////////////////////////////////////////////////
/// @file Barriere.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef BARRIERE_H_
#define BARRIERE_H_

#include "ElementJeuAbstrait.h"
#include "NoeudBarriere.h"
#include "AideCollision.h"

// Forward class declaratoin
class ArbreRenduINF2990;

/** @class Barriere
 *  @brief Cette classe qui permet de creer des barrieres
 *
 *	La classe Barriere contiendra un pointeur vers un noeudBarriere afin que celle-ci s'occupe
 *	de la texture de la barriere.
 */
class Barriere: public ElementJeuAbstrait
{
public:
	/// Constructeur
								Barriere();

	/// Constructeur par parametres
	/// @param positionDepart La position de depart
	/// @param taille La taille de l'element
	/// @param directionVitesse La vitesse de l'element
	/// @param poids Le poids de l'element
								Barriere(Vecteur3f position1, Vecteur3f position2, 
										 Vecteur3f taille, Vecteur3f directionVitesse, float poids);
								Barriere(const Barriere& barriere);

	/// Destructeur
	virtual					   ~Barriere();

	/// Check Collision
	virtual bool				checkCollision(ElementJeuAbstrait* element);
	virtual bool				checkCollision(Accelerateur* accelerateur) { return false; }
	virtual bool				checkCollision(Asteroide* asteroide);
	virtual bool				checkCollision(Barriere* barriere) { return false; }
	virtual bool				checkCollision(Portail* portail) { return false; }
	virtual bool				checkCollision(Projectile* projectile);
	virtual bool				checkCollision(Station* station) { return false; }
	virtual bool				checkCollision(Vaisseau* vaisseau);
	/// Permet au joueur virtuel de ne pas tirer sur une barrier
	virtual bool				checkCollisionJoueurVirtuel(Vaisseau* joueurVirtuel);

	// Traiter collision
	virtual void				traiterCollision(ElementJeuAbstrait* element);
	virtual void				traiterCollision(Accelerateur* accelerateur) {}
	virtual void				traiterCollision(Asteroide* asteroide);
	virtual void				traiterCollision(Barriere* barriere) {}
	virtual void				traiterCollision(Portail* portail) {}
	virtual void				traiterCollision(Projectile* projectile);
	virtual void				traiterCollision(Station* station) {}
	virtual void				traiterCollision(Vaisseau* vaisseau);

	/// Permet d'obtenir le type de l'element
	virtual Type				getType();

	/// Mise a jour
	virtual void				update(float deltaT);

	/// Permet de cloner l'element
	virtual ElementJeuAbstrait* clone() const;

	void						positionBarriere(Vecteur3f position1, Vecteur3f position2);
	Vecteur3f					getPositionPt1();
	Vecteur3f					getPositionPt2();

protected:

private:
	NoeudBarriere*				noeud_;
};

#endif
///////////////////////////////////////////////////////////////////////////
///@}
//////////////////////////////////////////////////////////////////////////