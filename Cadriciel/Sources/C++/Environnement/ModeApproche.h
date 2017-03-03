
///////////////////////////////////////////////////////////////////
/// @file ModeApproche.h
/// @author FloppyDisketeers
/// @date 2014-02-25
/// @version 1.0
///
/// @addgroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////
#ifndef MODE_APPROCHE_H
#define MODE_APPROCHE_H

#include "EtatJoueurVirtuel.h"

/** @class ModeApproche
 *  @brief La classe ModeApproche permet d'implementer le mode d'approche
 *  du vaisseau virtuel.
 *
 *	Cette classe contiendra des méthodes qui le changement d'etats, un vecteur des
 *  elements de jeu qui seront des obstacles et l'asteroide cible.
 */
class ModeApproche : public EtatJoueurVirtuel
{
public:
	/**
	 *  Constructeur par parametre
	 */
	ModeApproche(Asteroide *asteroideCible);

	/**
	 * Destructeur
	 */
	virtual ~ModeApproche() {}

	/**
	 * Update
	 * @param: le vaisseau virtuel,
	 * @param: deltaT
	 */
	virtual void update(VaisseauVirtuel &vaisseauVirtuel, float deltaT);

	/**
	 * Getter du mode d'etat
	 * @return: le mode
	 */
	virtual const Mode getEtat() const;

	/**
	 * Getter de l'asteroide vise par le joueur virtuel
	 * @return: l'asteroide
	 */
	virtual Asteroide*	getAsteroideCible() const;

	virtual void		setAstNull();

private:
	Asteroide *asteroideCible_;

	aiVector3D	directionVaisseauAAsteroide_;
	aiVector3D  posAsteroide_;
	aiVector3D	posVaisseau_;

	float		angle_;
	float		angleTmp_;
	float		coordonneX_;
	float		coordonneY_;

	vector<ElementJeuAbstrait*> obstacles_;

	float	    compteurEviterObs_;
	bool		obstacle_;
};

#endif
///////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////