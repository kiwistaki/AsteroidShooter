///////////////////////////////////////////////////////////////////////////////
/// @file UsineNoeud.h
/// @author Martin Bisson
/// @date 2007-01-28
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_USINES_USINENOEUD_H__
#define __ARBRE_USINES_USINENOEUD_H__


#include <string>


class NoeudAbstrait;


///////////////////////////////////////////////////////////////////////////
/// @class UsineNoeud
/// @brief Classe de base abstraite des usines qui seront utilisees pour
///        creer les differents noeuds de l'arbre de rendu.
///
/// @author Martin Bisson
/// @date 2007-01-28
///////////////////////////////////////////////////////////////////////////
class UsineNoeud
{
public:
   /// Destructeur vide declare virtuel pour les classes derivees.
   inline virtual ~UsineNoeud() {}

   /// Fonction a surcharger pour la creation d'un noeud.
   virtual NoeudAbstrait* creerNoeud() const = 0;

   /// Retourne le nom associe a l'usine
   inline const std::string& obtenirNom() const;


protected:
   /// Constructeur qui prend le nom associe a l'usine.
   UsineNoeud(const std::string& nom) : nom_(nom) {}


private:
   /// Le nom associe a l'usine
   std::string nom_;


};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline const std::string& UsineNoeud::obtenirNom() const
///
/// Cette fonction retourne une chaîne representante le nom associe a
/// l'usine.
///
/// @return Le nom associe a l'usine.
///
////////////////////////////////////////////////////////////////////////
inline const std::string& UsineNoeud::obtenirNom() const
{
   return nom_;
}


#endif // __ARBRE_USINES_USINENOEUD_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
