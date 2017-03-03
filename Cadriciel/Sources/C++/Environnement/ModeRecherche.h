
///////////////////////////////////////////////////////////////////
/// @file ModeRecherche.h
/// @author FloppyDisketeers
/// @date 2014-02-25
/// @version 1.0
///
/// @addgroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////
#ifndef MODE_RECHERCHE_H
#define MODE_RECHERCHE_H

#include "EtatJoueurVirtuel.h"
#include <vector>

/** @class ModeRecherche
 *  @brief La classe ModeRecherche permet d'implementer le mode de recherche
 *  du vaisseau virtuel.
 *
 *	Cette classe contiendra des méthodes qui le changement d'etats, un vecteur des
 *  elements de jeu qui seront des obstacles et l'asteroide cible.
 */
class ModeRecherche : public EtatJoueurVirtuel
{
public:
	/**
	 *  Constructeur par parametre
	 */
	ModeRecherche();

	/**
	 * Destructeur
	 */
	virtual ~ModeRecherche() {}

	/**
	 * Update
	 * @param: le vaisseau virtuel,
	 * @param: deltaT
	 */
	virtual void		update(VaisseauVirtuel &vaisseauVirtuel, float deltaT);

	/**
	 * Getter du mode d'etat
	 * @return: le mode
	 */
	virtual const		Mode getEtat() const;
	
	/**
	 * Getter de l'asteroide vise par le joueur virtuel
	 * @return: l'asteroide
	 */
	virtual Asteroide*	getAsteroideCible() const;

	/**
	 * Méthode qui permet de trouver un asteroide a detruire
	 * @return: bool
	 */
	bool				trouverAsteroideCible();

	virtual	void		setAstNull();

private:
	vector<ElementJeuAbstrait*> vecteurElement_;
	vector<Asteroide*> vecteurAsteroide_;

	float		distanceStationACible_;
	float		distanceVaisseauACible_;

	float		tempsAttente_;
	float		compteurTemps_;

	aiVector3D	posVaisseau_;

	Asteroide *asteroideCible_;
};

#endif
///////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////