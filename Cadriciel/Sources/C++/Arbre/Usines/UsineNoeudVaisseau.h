/**
 * @file UsineNoeudVaisseau.h
 * @author The FloppyDisketeers
 * @date 2014-01-27
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef USINE_NOEUD_VAISSEAU_H
#define USINE_NOEUD_VAISSEAU_H

#include "UsineNoeud.h"
#include "NoeudVaisseau.h"

/**
 * @class UsineNoeudVaisseau
 * @brief Cette classe permet d'afficher un portail grace a l'arbre de rendu
 */
class UsineNoeudVaisseau : public UsineNoeud {
	public:
	   /// Constructeur par parametres.
	   inline UsineNoeudVaisseau(const std::string& nom);

	   /// Fonction a surcharger pour la creation d'un noeud.
	   inline virtual NoeudAbstrait* creerNoeud() const;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn UsineNoeudVaisseau::UsineNoeudVaisseau(const std::string& nom)
///
/// Ce constructeur ne fait qu'appeler la version de la classe et base
/// et donner des valeurs par defaut aux variables membres..
///
/// @param[in] nom   : Le nom de l'usine qui correspond au type de noeuds crees.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
inline UsineNoeudVaisseau::UsineNoeudVaisseau(const std::string& nom) 
		: UsineNoeud(nom) {
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* UsineNoeudVaisseau::creerNoeud() const
///
/// Cette fonction retourne un noeud nouvellement cree du type produit
/// par cette usine.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* UsineNoeudVaisseau::creerNoeud() const
{
   return new NoeudVaisseau(obtenirNom());
}

#endif

/**
 * @}
 */