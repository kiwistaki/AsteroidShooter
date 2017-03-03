/**
 * @file UsineNoeudBarriere.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef USINE_NOEUD_BARRIERE_H
#define USINE_NOEUD_BARRIERE_H

#include "UsineNoeud.h"
#include "NoeudBarriere.h"

/**
 * @class UsineNoeudBarriere
 * @brief Cette classe permet d'afficher une barriere protectrice grace a l'arbre de rendu
 */
class UsineNoeudBarriere : public UsineNoeud {
	public:
	   /// Constructeur par parametres.
	   inline UsineNoeudBarriere(const std::string& nom);

	   /// Fonction a surcharger pour la creation d'un noeud.
	   inline virtual NoeudAbstrait* creerNoeud() const;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudBarriere::UsineNoeudBarriere(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudBarriere::UsineNoeudBarriere(const std::string& nom) 
		: UsineNoeud(nom) {
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudBarriere::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudBarriere::creerNoeud() const
{
   return new NoeudBarriere(obtenirNom());
}

#endif

/**
 * @}
 */