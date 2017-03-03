///////////////////////////////////////////////////////////////////////////
/// @file Asteroide.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////////////
#ifndef ASTEROID_H_
#define ASTEROID_H_

#include "ElementJeuAbstrait.h"
#include "NoeudAsteroide.h"
#include "AideCollision.h"
#include "Station.h"
#include "Barriere.h"

// Forward class declaration
class ArbreRenduINF2990;

/** @class Asteroide
 *  @brief Cette classe qui permet de creer des asteroides
 *
 *	La classe Asteroid contiendra un pointeur vers un noeudAsteroid afin que celle-ci s'occupe
 *	de la texture de l'asteroid.
 */
class Asteroide: public ElementJeuAbstrait
{
public:
	/// Constructeur
								Asteroide();
	/// Constructeur par parametres
	/// @param cadreDepart Vecteur4(xMin, xMax, yMin, yMax) du cadre de depart
	/// @param zonePassage Vecteur4(xMin, xMax, yMin, yMax) de la zone de passage
								Asteroide(Vecteur4f cadreDepart, Vecteur4f zonePassage);

	/// Constructeur par parametres
	/// @param positionDepart La position de depart
	/// @param taille La taille de l'element
	/// @param directionVitesse La vitesse de l'element
	/// @param poids Le poids de l'element
								Asteroide(Vecteur3f positionDepart,
										  Vecteur3f taille, Vecteur3f directionVitesse, float poids, unsigned int pointDeVie);

	///	Constructeur par copie
	/// @param asteroide L'element a copier
								Asteroide(const Asteroide& asteroide);

	/// Destructeur
	virtual					   ~Asteroide();

	/// Permet d'obtenir les points de vie
	/// @return Le nombre de point de vie
	virtual inline int			getPointDeVie(){ return pointDeVie_;}

	/// Permet de definir le nombre de points de vie
	/// @param pointDeVie Le nombre de points de vie
	void						setPointDeVie(int pointDeVie);

	/// Permet d'obtenir le type de l'element
	virtual Type				getType();

	/// Mise a jour
	virtual void				update(float deltaT);

	/// Permet de verifier la collision entre les types d'objets concernés et de les traiter
	virtual bool				checkCollision(ElementJeuAbstrait* ElementJeuAbstrait);
	virtual bool				checkCollision(Accelerateur* accelerateur) { return false; }
	virtual bool				checkCollision(Asteroide* asteroide);
	virtual bool				checkCollision(Barriere* barriere);
	virtual bool				checkCollision(Portail* portail);
	virtual bool				checkCollision(Projectile* projectile);
	virtual bool				checkCollision(Station* station);
	virtual bool				checkCollision(Vaisseau* vaisseau);

	virtual void				traiterCollision(ElementJeuAbstrait* elementAbstrait);
	virtual void				traiterCollision(Accelerateur* accelerateur) {}
	virtual	void				traiterCollision(Asteroide* asteroide);
	virtual	void				traiterCollision(Barriere* barriere);
	virtual	void				traiterCollision(Portail* portail);
	virtual	void				traiterCollision(Projectile* projectile);
	virtual	void				traiterCollision(Station* station);
	virtual	void				traiterCollision(Vaisseau* vaisseau);

	/// Permet de cloner l'element
	virtual ElementJeuAbstrait* clone() const;

	inline bool					canBeAttracted(){return canBeAttracted_;}
	void						setCanBeAttracted(bool canBeAttracted);

	virtual	float				getRayon();

	// Permet de determiner si un asteroide est cible du joueur virtuel
	// @param estCible Si l'asteroide est cible ou non
	void setCible(bool estCible);


	void						setToBeDeleted( bool toBeDeleted ){ toBeDeleted_ = toBeDeleted; };
	bool						isToBeDeleted(){ return toBeDeleted_;}

protected:

private:
	int							genererTailleAsteroide();

	int							pointDeVie_;
	NoeudAsteroide*				noeud_;

	/** Le rayon moyen de l'astéroïde (pour les collisions) */
	float						rayon_;

	bool						canBeAttracted_;	// Si l'objet peut etre encore attire par le portail.

	int							compteurAxe_;
	float						rotationX_;
	float						rotationY_;
	float						rotationZ_;

	float						incX;
	float						incY;
	float						incZ;

	float						randomFloat(float a, float b); 

	bool						toBeDeleted_; // Sert à marquer l'asteroide pour le détruire lors du prochain tour dans Carte::update()

	/** Tableau qui contient nos valeur de la loi normale utilisée */
	static const float			tabValeursNormale[];
	static const int			sizeOfTableauNormal;
	static const int			pointDeVieMax;


	
};

#endif
///////////////////////////////////////////////////////////////////////////
///@}
//////////////////////////////////////////////////////////////////////////