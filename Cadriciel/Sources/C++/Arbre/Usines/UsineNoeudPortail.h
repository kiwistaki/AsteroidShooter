/**
 * @file UsineNoeudPortail.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef USINE_NOEUD_PORTAIL_H
#define USINE_NOEUD_PORTAIL_H

#include "UsineNoeud.h"
#include "NoeudPortail.h"

/**
 * @class UsineNoeudPortail
 * @brief Cette classe permet d'afficher un portail grace a l'arbre de rendu
 */
class UsineNoeudPortail : public UsineNoeud {
	public:
	   /// Constructeur par parametres.
	   inline UsineNoeudPortail(const std::string& nom);

	   /// Fonction a surcharger pour la creation d'un noeud.
	   inline virtual NoeudAbstrait* creerNoeud() const;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudPortail::UsineNoeudPortail(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudPortail::UsineNoeudPortail(const std::string& nom) 
		: UsineNoeud(nom) {
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPortail::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPortail::creerNoeud() const
{
   return new NoeudPortail(obtenirNom());
}

#endif

/**
 * @}
 */