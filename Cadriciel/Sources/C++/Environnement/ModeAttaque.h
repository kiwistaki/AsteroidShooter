
///////////////////////////////////////////////////////////////////
/// @file ModeAttaque.h
/// @author FloppyDisketeers
/// @date 2014-02-25
/// @version 1.0
///
/// @addgroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////
#ifndef MODE_ATTAQUE_H
#define MODE_ATTAQUE_H

#include "EtatJoueurVirtuel.h"

/** @class ModeAttaque
 *  @brief La classe ModeAttaque permet d'implementer le mode d'attaque
 *  du vaisseau virtuel.
 *
 *	Cette classe contiendra des méthodes qui le changement d'etats, un vecteur des
 *  elements de jeu qui seront des obstacles et l'asteroide cible.
 */
class ModeAttaque : public EtatJoueurVirtuel
{
public:
	/**
	 *  Constructeur par parametre
	 */
	ModeAttaque(Asteroide *asteroideCible, aiVector3D directionVaisseauAAsteroide);

	/**
	 * Destructeur
	 */
	virtual ~ModeAttaque() {}

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
	aiVector3D directionVaisseauAAsteroide_;
	aiVector3D directionATirer_;

	float tempPourUnTir_;
	float compteurTemps_;
	
	float tempsPourOrientation_;
	float compteurTempsOrientation_;

	Vaisseau *joueur1;

	double distanceDeTirRapprocher_;
	double distanceDeTirMoyen_;

	bool attaquer_;

	vector<ElementJeuAbstrait*> obstacles_;

	float angle_;
	aiVector3D direction;
	aiVector3D posAsteroide;
};

#endif
///////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////