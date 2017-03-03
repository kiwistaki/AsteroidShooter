/**
 * @file UsineNoeudProjectile.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef USINE_NOEUD_PROJECTILE_H
#define USINE_NOEUD_PROJECTILE_H

#include "UsineNoeud.h"
#include "NoeudProjectile.h"

/**
 * @class UsineNoeudProjectile
 * @brief Cette classe permet d'afficher un portail grace a l'arbre de rendu
 */
class UsineNoeudProjectile : public UsineNoeud {
	public:
	   /// Constructeur par parametres.
	   inline UsineNoeudProjectile(const std::string& nom);

	   /// Fonction a surcharger pour la creation d'un noeud.
	   inline virtual NoeudAbstrait* creerNoeud() const;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudProjectile::UsineNoeudProjectile(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudProjectile::UsineNoeudProjectile(const std::string& nom) 
		: UsineNoeud(nom) {
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudProjectile::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudProjectile::creerNoeud() const
{
   return new NoeudProjectile(obtenirNom());
}

#endif

/**
 * @}
 */