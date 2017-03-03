///////////////////////////////////////////////////////////////////////////
/// @file PositionDepart.h
/// @author FloppyDisketeers
/// @date 2014-01-29
/// @version 1.0
///
/// @addtogroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef __POSITION_DEPART_H__
#define __POSITION_DEPART_H__

#include "ElementJeuAbstrait.h"
#include "NoeudPositionDepart.h"

// Forward class declaration
class ArbreRenduINF2990;

/** @class PositionDepart
 *  @brief Cette classe  permet de creer des position de depart
 *
 *	La classe PositionDepart est afficher seulement en mode edition. Il y aura deux position
 *  de depart pour les deux joueurs. Les positions de depart peuvent etre deplacer mais non effacer
 */
class PositionDepart: public ElementJeuAbstrait
{
public:
	/// Constructeur
								PositionDepart();

	/// Constructeur par parametres
	/// @param positionDepart La position de depart
	/// @param taille La taille de l'element
	/// @param directionVitesse La vitesse de l'element
	/// @param poids Le poids de l'element
								PositionDepart( Vecteur3f positionDepart, Vecteur3f taille, 
												Vecteur3f directionVitesse, unsigned int poids);
								PositionDepart(const PositionDepart& positionDepart);

	/// Destructeur
	virtual					   ~PositionDepart();

	/// Permet d'obtenir le type de l'element
	virtual Type				getType();

	/// Mise a jour
	virtual void				update(float deltaT);

	/// Permet de cloner l'element
	virtual ElementJeuAbstrait* clone() const;

	/**
	* Methode qui definit la visibilite d'un element
	* @param visible Si l'element doit etre visible ou non
	*/
	void inline					setVisible(bool visible) { noeud_->assignerAffiche(visible); }

	virtual bool	checkCollision(ElementJeuAbstrait* element) { return false; }
	virtual bool	checkCollision(Accelerateur* accelerateur) { return false; }
	virtual bool	checkCollision(Asteroide* asteroide) { return false; }
	virtual bool	checkCollision(Barriere* barriere) { return false; }
	virtual bool	checkCollision(Portail* portail) { return false; }
	virtual bool	checkCollision(Projectile* projectile) { return false; }
	virtual bool	checkCollision(Station* station) { return false; }
	virtual bool	checkCollision(Vaisseau* vaisseau) { return false; }

	virtual void	traiterCollision(ElementJeuAbstrait* element) {}
	virtual void	traiterCollision(Accelerateur* accelerateur) {}
	virtual void	traiterCollision(Asteroide* asteroide) {}
	virtual void	traiterCollision(Barriere* barriere) { }
	virtual void	traiterCollision(Portail* portail) { }
	virtual void	traiterCollision(Projectile* projectile) { }
	virtual void	traiterCollision(Station* station) { }
	virtual void	traiterCollision(Vaisseau* vaisseau) { }

private:
	NoeudPositionDepart*		noeud_;
};

#endif // __POSITION_DEPART_H__

///////////////////////////////////////////////////////////////////////////
///@}
//////////////////////////////////////////////////////////////////////////