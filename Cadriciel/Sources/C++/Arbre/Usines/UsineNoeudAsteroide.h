/**
 * @file UsineNoeudAsteroide.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef USINE_NOEUD_ASTEROIDE_H
#define USINE_NOEUD_ASTEROIDE_H

#include "UsineNoeud.h"
#include "NoeudAsteroide.h"

/**
 * @class UsineNoeudAsteroide
 * @brief Cette classe permet de creer un NoeudAsteroide
 */
class UsineNoeudAsteroide : public UsineNoeud {
	public:
	   /// Constructeur par parametres.
	   inline UsineNoeudAsteroide(const std::string& nom);

	   /// Fonction a surcharger pour la creation d'un noeud.
	   inline virtual NoeudAbstrait* creerNoeud() const;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudAsteroide::UsineNoeudAsteroide(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudAsteroide::UsineNoeudAsteroide(const std::string& nom) 
		: UsineNoeud(nom) {
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudAsteroide::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudAsteroide::creerNoeud() const
{
   return new NoeudAsteroide(obtenirNom());
}

#endif

/**
 * @}
 */