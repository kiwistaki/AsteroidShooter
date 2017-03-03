///////////////////////////////////////////////////////////////////////////
/// @file Portail.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef PORTAIL_H_
#define PORTAIL_H_

#include "ElementJeuAbstrait.h"
#include "NoeudPortail.h"

// Forward class declaration
class ArbreRenduINF2990;

/** @class Portail
 *  @brief Cette classe qui permet de creer des Portails
 *
 *	La classe Portail contiendra un pointeur vers un noeudPortail afin que celle-ci s'occupe
 *	de la texture de la Portail.
 */
class Portail: public ElementJeuAbstrait{
public:
	/// Constructeur
								Portail();

	/// Constructeur par parametres
	/// @param positionDepart La position de depart
	/// @param taille La taille de l'element
	/// @param directionVitesse La vitesse de l'element
	/// @param poids Le poids de l'element
								Portail( Vecteur3f positionDepart,
										Vecteur3f taille, Vecteur3f directionVitesse, float poids);
								Portail(const Portail& portail);

	/// Destructeur
	virtual					   ~Portail();

	/// Permet d'obtenir le type de l'element
	virtual Type				getType();

	/// Mise a jour
	virtual void				update(float deltaT);

	/// Permet de cloner l'element
	virtual ElementJeuAbstrait* clone() const;

	inline Portail*				getFrere() const { return frere_; }
	void						setFrere(Portail* frere);

	inline unsigned long		getIdFrere() const { return idFrere_; }
	void						setIdFrere(unsigned long id) { idFrere_ = id; }

	/// Permet de verifier la collision entre les types d'objets concernés et de les traiter
	virtual bool				checkCollision(ElementJeuAbstrait* element);
	virtual bool				checkCollision(Accelerateur* accelerateur) { return false;}
	virtual bool				checkCollision(Asteroide* asteroide);
	virtual bool				checkCollision(Barriere* barriere) { return false; }
	virtual bool				checkCollision(Portail* portail) { return false; }
	virtual bool				checkCollision(Projectile* projectile);
	virtual bool				checkCollision(Station* station) { return false; }
	virtual bool				checkCollision(Vaisseau* vaisseau);
	virtual bool				checkCollisionJoueurVirtuel(Vaisseau* joueurVirtuel);

	virtual void				traiterCollision(ElementJeuAbstrait* elementAbstrait);
	virtual	void				traiterCollision(Asteroide* asteroide);
	virtual	void				traiterCollision(Projectile* projectile);
	virtual	void				traiterCollision(Vaisseau* vaisseau);

	virtual void				traiterCollision(Accelerateur* accelerateur) {}
	virtual void				traiterCollision(Barriere* barriere) {}
	virtual void				traiterCollision(Portail* portail) {}
	virtual void				traiterCollision(PositionDepart* positionDepart) {}
	virtual void				traiterCollision(Station* station) {}

	virtual float				getRayon();

private:
	NoeudPortail*				noeud_;	// Le noeud de rendu
	Portail*					frere_;	// Le portail frere

	/** L'identifiant du frère */
	unsigned long				idFrere_;

	// Le rayon moyen du portail (pour les collisions)
	float						rayon_;
};

#endif
///////////////////////////////////////////////////////////////////////////
///@}
//////////////////////////////////////////////////////////////////////////