///////////////////////////////////////////////////////////////////////////
/// @file Station.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef STATION_H_
#define STATION_H_

#include "ElementJeuAbstrait.h"
#include "Vaisseau.h"
#include "NoeudStation.h"

// Forward class declaration
class ArbreRenduINF2990;

/** @class Station
 *  @brief Classe permettant la creation d'une station spatiale
 *
 *	Cette classe contiendra un pointeur de NoeudStation qui gerera
 *	la texture et la modelisation de cette classe.
 */
class Station: public ElementJeuAbstrait
{
public:
	/// Constructeur
						Station();

	/// Constructeur par parametres
	/// @param positionDepart La position de depart
	/// @param taille La taille de l'element
	/// @param directionVitesse La vitesse de l'element
	/// @param poids Le poids de l'element
						Station( Vecteur3f positionDepart,
								Vecteur3f taille, Vecteur3f directionVitesse, float poids,
								unsigned int pointDeVie);
						Station(const Station& station);

	/// Destructeur
	virtual			   ~Station();
	
	virtual inline int	getPointDeVie(){ return pointDeVie_;}
	void				setPointDeVie(int pointDeVie);

	/// Permet d'obtenir le type de l'element
	virtual	Type		getType();

	/// Mise a jour
	virtual void		update(float deltaT);

	/// Permet de cloner l'element
	virtual				ElementJeuAbstrait* clone() const;

	static unsigned int	getNbStation();

	/// Methode qui permet au joueur virtuel d'éviter les stations spatiales
	virtual bool		checkCollision(ElementJeuAbstrait* element);
	virtual bool		checkCollisionJoueurVirtuel(Vaisseau* joueurVirtuel);
	virtual bool		checkCollision(Accelerateur* accelerateur) { return false; }
	virtual bool		checkCollision(Asteroide* asteroide);
	virtual bool		checkCollision(Barriere* barriere) { return false; }
	virtual bool		checkCollision(Portail* portail) { return false; }
	virtual bool		checkCollision(Projectile* projectile);
	virtual bool		checkCollision(Station* station) { return false; }
	virtual bool		checkCollision(Vaisseau* vaisseau);

	virtual void		traiterCollision(ElementJeuAbstrait* element);
	virtual	void		traiterCollision(Projectile* projectile);

	virtual void		traiterCollision(Accelerateur* accelerateur) {}
	virtual void		traiterCollision(Asteroide* asteroide);
	virtual void		traiterCollision(Barriere* barriere) {}
	virtual void		traiterCollision(Portail* portail) {}
	virtual void		traiterCollision(PositionDepart* positionDepart) {}
	virtual void		traiterCollision(Station* station) {}
	virtual void		traiterCollision(Vaisseau* vaisseau);

	/// Affiche les textes superposes
	virtual void		afficherTexte();

private:
	int					pointDeVie_;
	NoeudStation*		noeud_;
	static unsigned int	nbStation_;
	static const float	VITESSE_ROTATION;

};

#endif
/////////////////////////////////////////////////////////////////////////
///@}
/////////////////////////////////////////////////////////////////////////