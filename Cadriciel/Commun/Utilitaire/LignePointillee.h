///////////////////////////////////////////////////////////////////////////////
/// @file LignePointillee.h
/// @author Martin Bisson
/// @date 2007-01-28
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_LIGNEPOINTILLEE_H__
#define __UTILITAIRE_LIGNEPOINTILLEE_H__


#include <GL/gl.h>
#include "Vecteur.h"


namespace aidegl {


   ///////////////////////////////////////////////////////////////////////////
   /// @class LignePointillee
   /// @brief Classe qui gere l'affichage de lignes pointillees.
   ///
   /// @author Martin Bisson
   /// @date 2007-01-28
   ///////////////////////////////////////////////////////////////////////////
   class LignePointillee
   {
   public:
      /// Constructeur par defaut.
      LignePointillee();

      /// Debut du rendu de lignes.
      void commencer() const;

      /// Fin du rendu de lignes.
      void finir() const;

      /// Assigne la couleur des lignes.
      inline void assignerCouleur(const Vecteur4f& couleur);
      /// Assigne le facteur multiplicatif du pointille.
      inline void assignerFacteur(int facteur);
      /// Assigne le patron de pointille des lignes.
      inline void assignerPatron(unsigned short patron);


   private:
      /// Couleur des lignes.
      Vecteur4f      couleur_;
      /// Facteur multiplicatif du pointille.
      int            facteur_;
      /// Patron de pointille des lignes.
      unsigned short patron_;

   };



   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline LignePointillee::LignePointillee()
   ///
   /// Constructeur par defaut qui se contente d'initialiser les parametres
   /// du rendu de la ligne a des valeurs par defaut.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////
   inline LignePointillee::LignePointillee()
      : couleur_(1.0f, 1.0f, 1.0f, 1.0f) , facteur_(1) , patron_(0x3333)
   {
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void LignePointillee::commencer() const
   ///
   /// Cette fonction assigne les parametres necessaires pour le debut du
   /// rendu de la ligne dans la machine a etats OpenGL.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline void LignePointillee::commencer() const
   {
      // On sauvegarde les attributs de tracage
      const GLbitfield masque = GL_CURRENT_BIT | GL_LIGHTING_BIT;
      if (patron_ == 0xFFFF) {
         // Pas de pointille.
         glPushAttrib( masque );
      }
      else {
         // Pointille.
         glPushAttrib( masque | GL_LINE_BIT );
         glEnable( GL_LINE_STIPPLE );
         glLineStipple( facteur_, patron_ );
      }

      glDisable(GL_LIGHTING);
      glColor4f( couleur_[0], couleur_[1], couleur_[2], couleur_[3]);
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void LignePointillee::finir() const
   ///
   /// Cette fonction restaure les parametres d'avant le debut du trace
   /// des lignes.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline void LignePointillee::finir() const
   {
      // On retablit les attributs initiaux.
      glPopAttrib();
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void LignePointillee::assignerCouleur(const Vecteur4f& couleur)
   ///
   /// Cette fonction permet d'assigner la couleur utilisee pour dessiner
   /// les lignes.
   ///
   /// @param[in] couleur : La couleur des lignes.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline void LignePointillee::assignerCouleur(const Vecteur4f& couleur)
   {
      couleur_ = couleur;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void LignePointillee::assignerFacteur(int facteur)
   ///
   /// Cette fonction permet d'assigner le facteur multiplicatif du
   /// pointille utilise pour dessiner les lignes.
   ///
   /// @param[in] facteur : Le facteur multiplicatif.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline void LignePointillee::assignerFacteur(int facteur)
   {
      facteur_ = facteur;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void LignePointillee::assignerPatron(unsigned short patron)
   ///
   /// Cette fonction permet d'assigner le patron du pointille utilise pour
   /// dessiner les lignes.
   ///
   /// @param[in] patron : Le patron du pointille.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline void LignePointillee::assignerPatron(unsigned short patron)
   {
      patron_ = patron;
   }


} // Fin de l'espace de nom aidegl.


#endif // __UTILITAIRE_LIGNEPOINTILLEE_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
