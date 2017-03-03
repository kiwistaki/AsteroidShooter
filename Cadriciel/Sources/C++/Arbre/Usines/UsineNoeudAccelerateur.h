/**
 * @file UsineNoeudAccelerateur.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef USINE_NOEUD_ACCELERATEUR_H
#define USINE_NOEUD_ACCELERATEUR_H

#include "UsineNoeud.h"
#include "NoeudAccelerateur.h"

/**
 * @class UsineNoeudAccelerateur
 * @brief Cette classe permet d'afficher un bonus accelerateur grace a l'arbre de rendu
 */
class UsineNoeudAccelerateur : public UsineNoeud {
	public:
	   /// Constructeur par parametres.
	   inline UsineNoeudAccelerateur(const std::string& nom);

	   /// Fonction a surcharger pour la creation d'un noeud.
	   inline virtual NoeudAbstrait* creerNoeud() const;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudAccelerateur::UsineNoeudAccelerateur(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudAccelerateur::UsineNoeudAccelerateur(const std::string& nom) 
		: UsineNoeud(nom) {
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudAccelerateur::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudAccelerateur::creerNoeud() const
{
   return new NoeudAccelerateur(obtenirNom());
}

#endif

/**
 * @}
 */