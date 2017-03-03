//////////////////////////////////////////////////////////////////////////////
/// @file GestionnaireCollision.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_GESTIONNAIRECOLLISION_H__
#define __APPLICATION_GESTIONNAIRECOLLISION_H__

#include <iostream>
#include <string>

#include "../ElementObjet/ElementJeuAbstrait.h"

using namespace std;

// Forward class declaration
class QuadTree;

/**
 * @class GestionnaireCollision
 * @brief Classe qui se charge de verifier les collisions et d'appeler 
 *        leur traitement.
 *
 * @author FloppyDisketeers
 * @date 2014-01-21
 */
class GestionnaireCollision
{
public:
	/**
	* Constructeur
	*/
	GestionnaireCollision(vector<ElementJeuAbstrait*>& vecteurElementsJeu, vector<Asteroide*>& vecteurAsteroides, vector<Projectile*>& vecteurProjectiles);
		 
	/**
	* Destructeur
	*/
	~GestionnaireCollision();
	
	/**
	 * Initialise le quad tree avec les dimensions du cadre de départ
	 * @param coinHautGauche Le coin supérieur gauche du quad tree
	 * @param coinBasDroite Le coin inférieur droit du quad tree
	 */
	void							initialiserQuadTree(const Vecteur2f& coinHautGauche,
														const Vecteur2f& coinBasGauche);

	/**
	* Getter / Setter
	*/
	vector<Asteroide*>&				getConteneurAsteroides();
	
	vector<ElementJeuAbstrait*>&	getConteneurElementsJeu();

	void							setConteneurAsteroides(vector<Asteroide*>& asteroides);

	void							setConteneurElementJeu(vector<ElementJeuAbstrait*>& elementsJeu);

	void addJoueur(Vaisseau* vaisseau);


	/**
	* Collisions
	*/

	//Permet de répertorier l'ensemble des collision dans le jeu
	void							checkCollisions();

	//Méthode appelée après la détection des collisions. Elle appelle les méthode "traiterCollision" des objets appropriés
	void							traiterCollisions();

	void							detruireQuadTree();

private:
	/// Conteneur des éléments de la carte
	vector<ElementJeuAbstrait*>&	conteneurElementsJeu_;

	/// Conteneur des asteroides
	vector<Asteroide*>&				conteneurAsteroide_;

	/// Conteneur des asteroides
	vector<Projectile*>&			conteneurProjectile_;

	/// Conteneur temporaire des paires d'éléments qui sont en collision
	vector<pair<ElementJeuAbstrait*,ElementJeuAbstrait*>> conteneurElementATraiter_;
/// Conteneur des vaisseaux
	vector<Vaisseau*>				conteneurVaisseaux_;

	/**
	 * QuadTree, permet de réduire les collisions à traiter en regardant
	 * seulement les objets qui sont dans le même noeud de l'arbre que l'objet
	 * pour lequel on veut regarder une collision.
	 */
	QuadTree*						quadTree_;
};
#endif // __APPLICATION_GESTIONNAIRECOLLISION_H__
 
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////