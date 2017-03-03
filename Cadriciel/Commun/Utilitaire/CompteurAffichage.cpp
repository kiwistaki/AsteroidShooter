//////////////////////////////////////////////////////////////////////////////
/// @file CompteurAffichage.cpp
/// @author Martin Bisson
/// @date 2007-03-09
/// @version 1.0 
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "CompteurAffichage.h"
#include <windows.h>


namespace utilitaire {


   /// Pointeur vers l'instance unique de la classe.
   CompteurAffichage* CompteurAffichage::instance_ = 0;


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn CompteurAffichage* CompteurAffichage::obtenirInstance()
   ///
   /// Cette fonction retourne un pointeur vers l'instance unique de la
   /// classe.  Si cette instance n'a pas ete creee, elle la cree.  Cette
   /// creation n'est toutefois pas necessairement "thread-safe", car
   /// aucun verrou n'est pris entre le test pour savoir si l'instance
   /// existe et le moment de sa creation.
   ///
   /// @return Un pointeur vers l'instance unique de cette classe.
   ///
   ////////////////////////////////////////////////////////////////////////
   CompteurAffichage* CompteurAffichage::obtenirInstance()
   {
      if (instance_ == 0)
         instance_ = new CompteurAffichage;

      return instance_;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void CompteurAffichage::libererInstance()
   ///
   /// Cette fonction libere l'instance unique de cette classe.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void CompteurAffichage::libererInstance()
   {
      delete instance_;
      instance_ = 0;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void CompteurAffichage::signalerAffichage()
   ///
   /// Cette fonction effectue le traitement necessaire lorsqu'un affichage
   /// est signalee, c'est-a-dire qu'elle incremente le compte et verifie
   /// si la limite de temps pour la mise a jour est depassee.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void CompteurAffichage::signalerAffichage()
   {
      compte_++;

      const int difference = GetTickCount() - derniereLecture_;
      if (difference >= TEMPS_RAFRAICHISSEMENT) {
         const float compte = (1000.0f * compte_) / ((float) difference);

         nbAffichagesSeconde_ = static_cast<int>(compte);
         derniereLecture_    += difference;
         compte_              = 0;
      }
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void CompteurAffichage::reinitialiser()
   ///
   /// Cette fonction reinitialise le compteur d'affichage a son etat
   /// initiale.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void CompteurAffichage::reinitialiser()
   {
      nbAffichagesSeconde_ = 0;
      derniereLecture_     = GetTickCount();
      compte_              = 0;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn CompteurAffichage::CompteurAffichage()
   ///
   /// Ce constructeur par defaut ne fait qu'initialiser les membres de
   /// du compteur.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////
   CompteurAffichage::CompteurAffichage()
   {
      reinitialiser();
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn CompteurAffichage::~CompteurAffichage()
   ///
   /// Ce destructeur ne fait rien, mais est quand meme declare afin de
   /// pouvoir etre declare prive pour l'implantation du patron singleton.
   ///
   /// @return Aucune (destructeur).
   ///
   ////////////////////////////////////////////////////////////////////////
   CompteurAffichage::~CompteurAffichage()
   {
   }


} // Fin de l'espace de nom utilitaire.


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
