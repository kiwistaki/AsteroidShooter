//////////////////////////////////////////////////////////////////////////////
/// @file CompteurAffichage.h
/// @author Martin Bisson
/// @date 2007-03-09
/// @version 1.0 
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_COMPTEURAFFICHAGE_H__
#define __UTILITAIRE_COMPTEURAFFICHAGE_H__


namespace utilitaire {
   

   ///////////////////////////////////////////////////////////////////////////
   /// @class CompteurAffichage
   /// @brief Classe qui gere le compte des affichages par secondes ("FPS").
   ///
   /// @author Martin Bisson
   /// @date 2007-03-09
   ///////////////////////////////////////////////////////////////////////////
   class CompteurAffichage
   {
   public:
      /// Obtient l'instance unique de la classe.
      static CompteurAffichage* obtenirInstance();
      /// Libere l'instance unique de la classe.
      static void libererInstance();

      /// Obtient le dernier nombre calcule d'affichages par seconde.
      inline int obtenirAffichagesSeconde() const;

      /// Indique qu'un affichage vient de se produire.
      void signalerAffichage();
      /// Reinitialise le compteur d'affichage.
      void reinitialiser();

   private:
      /// Constructeur par defaut.
      CompteurAffichage();
      /// Destructeur.
      ~CompteurAffichage();
      /// Constructeur copie.  Declare mais non defini pour eviter qu'il soit
      /// genere par le compilateur.
      CompteurAffichage(const CompteurAffichage&);
      /// Operateur d'assignation.  Declare mais non defini pour eviter qu'il
      /// soit genere par le compilateur.
      CompteurAffichage& operator =(const CompteurAffichage&);

      /// Pointeur vers l'instance unique de la classe.
      static CompteurAffichage* instance_;

      /// Nombre de millisecondes entre les rafraichissements du nombre d'affichages.
      static const int TEMPS_RAFRAICHISSEMENT = 1000;

      /// Nombre d'affichages dans la derniere seconde.
      int nbAffichagesSeconde_;

      /// Derniere lecture du temps.
      int derniereLecture_;

      /// Compte des affichages.
      int compte_;

   };




   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline int CompteurAffichage::obtenirAffichagesSeconde() const
   ///
   /// Cette fonction retourne le dernier nombre d'affichages par seconde
   /// calcule par le compteur.
   ///
   /// @return Le nombre d'affichages par seconce le plus recent.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline int CompteurAffichage::obtenirAffichagesSeconde() const
   {
      return nbAffichagesSeconde_;
   }


} // Fin de l'espace de nom utilitaire.


#endif // __UTILITAIRE_COMPTEURAFFICHAGE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
