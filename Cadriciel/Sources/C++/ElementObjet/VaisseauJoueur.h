///////////////////////////////////////////////////////////////////
/// @file VaisseauJoueur.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0
///
/// @addgroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////
#ifndef VAISSEAU_JOUEUR_H_
#define VAISSEAU_JOUEUR_H_

#include "Vaisseau.h"
#include "NoeudVaisseau.h"

// Forward class declaration
class ArbreRenduINF2990;

/** 
 *  @class VaisseauJoueur
 *  @brief La classe Vaisseau permet la creation d'un objet Vaisseau.
 *
 *	Cette classe contiendra un noeud de type NoeudVaisseau qui gerera
 *  la texture et la modelisation de l'objet Vaisseau.
 */
class VaisseauJoueur: public Vaisseau
{
public:
	/// Constructeur
	/// @param joueur1 Si cette valeur a est true, alors c'est le joueur 1, false sinon
					VaisseauJoueur(bool joueur1=true);

	/// Constructeur par parametres
	/// @param positionDepart La position de depart
	/// @param taille La taille de l'element
	/// @param directionVitesse La vitesse de l'element
	/// @param poids Le poids de l'element
	/// @param joueur1 Si cette valeur a est true, alors c'est le joueur 1, false sinon
					VaisseauJoueur( Vecteur3f positionDepart,
							 Vecteur3f taille, Vecteur3f directionVitesse, float poids,
							 bool joueur1=true);
					VaisseauJoueur(const VaisseauJoueur& vaisseau);

	/// Destructeur
	virtual		   ~VaisseauJoueur();

	/// Permet d'obtenir le type de l'element
	virtual Type	getType();

	/// Mise a jour
	virtual void	update(float deltaT);

	/// Permet de cloner l'element
	virtual			ElementJeuAbstrait* clone() const;

	virtual bool	checkCollision(ElementJeuAbstrait* element) { return Vaisseau::checkCollision(element); }
	virtual bool	checkCollision(Accelerateur* accelerateur) { return Vaisseau::checkCollision(accelerateur); }
	virtual bool	checkCollision(Asteroide* asteroide) { return Vaisseau::checkCollision(asteroide); }
	virtual bool	checkCollision(Barriere* barriere) { return Vaisseau::checkCollision(barriere); }
	virtual bool	checkCollision(Portail* portail) { return Vaisseau::checkCollision(portail); }
	virtual bool	checkCollision(Projectile* projectile) { return Vaisseau::checkCollision(projectile); }
	virtual bool	checkCollision(Station* station) { return Vaisseau::checkCollision(station); }
	virtual bool	checkCollision(Vaisseau* vaisseau) { return Vaisseau::checkCollision(vaisseau); }

	virtual void	traiterCollision(ElementJeuAbstrait* element) { Vaisseau::traiterCollision(element); }
	virtual void	traiterCollision(Accelerateur* accelerateur) { Vaisseau::traiterCollision(accelerateur); }
	virtual void	traiterCollision(Asteroide* asteroide) { Vaisseau::traiterCollision(asteroide); }
	virtual void	traiterCollision(Barriere* barriere) { Vaisseau::traiterCollision(barriere); }
	virtual void	traiterCollision(Portail* portail) { Vaisseau::traiterCollision(portail); }
	virtual void	traiterCollision(Projectile* projectile) { Vaisseau::traiterCollision(projectile); }
	virtual void	traiterCollision(Station* station) { Vaisseau::traiterCollision(station); }
	virtual void	traiterCollision(Vaisseau* vaisseau) { Vaisseau::traiterCollision(vaisseau); }

	virtual Asteroide*	getAstCible() {return NULL;}
	virtual	void		setAstCibleNull() {;}

protected:

private:
};

#endif
///////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////