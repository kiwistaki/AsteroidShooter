//////////////////////////////////////////////////////////////////////////////
/// @file Projection.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_PROJECTION_H__
#define __UTILITAIRE_PROJECTION_H__


#include "Vecteur.h"

namespace vue {
   ////////////////////////////////////////////////////////////////////////
   /// @class Projection
   /// @brief Classe contrôlant la projection du monde a la fenetre.
   ///
   /// Cette classe offre certaines fonctionnalites commune a chacun des types
   /// de projection (isometrique, perspective, etc.).  Elle definit une
   /// interface que doivent implanter les types concrets de projection,
   /// c'est-a-dire permettre de modifier le facteur de zoom par exemple.
   ///
   /// @author Martin Bisson
   /// @date 2006-12-15
   ////////////////////////////////////////////////////////////////////////
   class Projection
   {
   public:
      /// Constructeur.
      Projection(int xMinCloture, int xMaxCloture,
                 int yMinCloture, int yMaxCloture,
                 double zAvant,  double zArriere,
                 double zoomInMax, double zoomOutMax,
                 double incrementZoom, bool estPerspective);

      /// Destructeur virtuel vide.
      virtual ~Projection() {}

      /// Zoom in, c'est-a-dire un agrandissement.
      virtual void zoomerIn() = 0;
      /// Zoom out, c'est-a-dire un rapetissement.
      virtual void zoomerOut() = 0;
      /// Modification de la clôture.
      virtual void redimensionnerFenetre( const Vecteur2i& coinMin,
                                          const Vecteur2i& coinMax ) = 0;
      /// Application de la projection.
      virtual void appliquer() const = 0;


      /// Application de la fenetre de clôture (appel a glViewport).
      void mettreAJourCloture() const;
      /// Application de la projection.
      void mettreAJourProjection() const;

      /// Obtention des dimensions de la fenetre de clotûre.
      inline Vecteur2i obtenirDimensionCloture() const;
      /// Obtention des coordonnees de la fenetre de clôture.
      inline void obtenirCoordonneesCloture(
         int& xMin, int& xMax, int& yMin, int& yMax
         ) const;

      /// Verification de si la projection est perspective.
      inline bool estPerspective() const;

	  double getIncrementZoom(){ return incrementZoom_;}

	  virtual Vecteur4 getDimensionsFenetre() const { return Vecteur4(0,0,0,0); }
	  
	  inline double getZAvant() const { return zAvant_; }
   protected:
      /// Coordonnee inferieur de la clôture en X.
      int xMinCloture_;
      /// Coordonnee superieur de la clôture en X.
      int xMaxCloture_;
      /// Coordonnee inferieur de la clôture en Y.
      int yMinCloture_;
      /// Coordonnee superieur de la clôture en Y.
      int yMaxCloture_;
	  
      /// Avant du volume de visualisation.
      double zAvant_;
      /// Arriere du volume de visualisation.
      double zArriere_;

      /// Facteur maximal de zoom in.
      double zoomInMax_;
      /// Facteur maximal de zoom out.
      double zoomOutMax_;
      /// Increment des zooms.
      double incrementZoom_;
      /// Vrai si la projection est perspective.
      bool   estPerspective_;
   };




   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur2i Projection::obtenirDimensionCloture() const
   ///
   /// Cette fonction retourne les dimensions de la fenetre de clôture
   /// associee a cette projection.
   ///
   /// @return Les dimensions de la fenetre de clôture.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline Vecteur2i Projection::obtenirDimensionCloture() const
   {
      return Vecteur2i(xMaxCloture_ - xMinCloture_, yMaxCloture_ - yMinCloture_);
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void Projection::obtenirCoordonneesCloture(int& xMin, int& xMax, int& yMin, int& yMax) const
   ///
   /// Cette fonction retourne les coordonnees de la fenetre de clôture
   /// associee a cette projection.
   ///
   /// @param[out]  xMin : La variable qui contiendra l'abcsisse minimale.
   /// @param[out]  xMax : La variable qui contiendra l'abcsisse maximale.
   /// @param[out]  yMin : La variable qui contiendra l'ordonnee minimale.
   /// @param[out]  yMax : La variable qui contiendra l'ordonnee maximale.
   ///
   /// @return Les coordonnees de la fenetre de clôture.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline void Projection::obtenirCoordonneesCloture(
      int& xMin, int& xMax, int& yMin, int& yMax
      ) const
   {
      xMin = xMinCloture_;
      xMax = xMaxCloture_;
      yMin = yMinCloture_;
      yMax = yMaxCloture_;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline bool Projection::estPerspective() const
   ///
   /// Cette fonction retourne vrai si la projection est une projection
   /// perspective.
   ///
   /// @return Vrai si la projection est une projection perspective.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline bool Projection::estPerspective() const
   {
      return estPerspective_;
   }


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_PROJECTION_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
