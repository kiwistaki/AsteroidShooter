/**
 * @file UsineNoeudPositionDepart.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef USINE_NOEUD_POSITION_DEPART_H
#define USINE_NOEUD_POSITION_DEPART_H

#include "UsineNoeud.h"
#include "NoeudPositionDepart.h"

/**
 * @class UsineNoeudPositionDepart
 * @brief Cette classe permet d'afficher une position de depart grace a l'arbre de rendu
 */
class UsineNoeudPositionDepart : public UsineNoeud {
	public:
	   /// Constructeur par parametres.
	   inline UsineNoeudPositionDepart(const std::string& nom);

	   /// Fonction a surcharger pour la creation d'un noeud.
	   inline virtual NoeudAbstrait* creerNoeud() const;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudPositionDepart::UsineNoeudPositionDepart(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudPositionDepart::UsineNoeudPositionDepart(const std::string& nom) 
		: UsineNoeud(nom) {
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudPositionDepart::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudPositionDepart::creerNoeud() const
{
   return new NoeudPositionDepart(obtenirNom());
}

#endif

/**
 * @}
 */