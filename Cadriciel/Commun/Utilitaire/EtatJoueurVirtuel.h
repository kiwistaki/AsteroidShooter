
///////////////////////////////////////////////////////////////////
/// @file EtatJoueurVirtuel.h
/// @author FloppyDisketeers
/// @date 2014-02-25
/// @version 1.0
///
/// @addgroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////
#ifndef ETATJOUEURVIRTUEL_H
#define ETATJOUEURVIRTUEL_H

#include "../../Sources/C++/ElementObjet/Asteroide.h"
#include "../../Sources/C++/ElementObjet/VaisseauVirtuel.h"
#include "Carte.h"
#include "../Application/FacadeModele.h"

/** @class EtatJoueurVirtuel
 *  @brief La classe EtatJoueurVirtuel permet d'implementer les differents mode
 *  du vaisseau virtuel.
 *
 *	Cette classe contiendra des méthodes qui le changement d'etats.
 */
class EtatJoueurVirtuel
{
public:

	/**
	 *  Constructeur
	 */
	EtatJoueurVirtuel();

	/**
	 * Destructeur
	 */
	virtual ~EtatJoueurVirtuel() {}

	/**
	 * Update, méthode virtuelle
	 * @param: le vaisseau virtuel,
	 * @param: deltaT
	 */
	virtual void update(VaisseauVirtuel &vaisseauVirtuel, float deltaT) = 0;

	/**
	 * Getter du mode d'etat
	 * @return: le mode
	 */
	virtual const Mode getEtat() const = 0;

	/**
	 * Getter de l'asteroide vise par le joueur virtuel
	 * @return: l'asteroide
	 */
	virtual Asteroide* getAsteroideCible() const = 0;

	virtual void       setAstNull() = 0;

protected:
	Carte *carte_;
	double minX_; 
	double minY_; 
	double maxX_; 
	double maxY_; 

	double distancePasserModeAttaque_;
};

#endif
///////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////
