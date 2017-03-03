////////////////////////////////////////////////////////////////////////////////////
/// @file ProjectionOrtho.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_PROJECTIONORTHO_H__
#define __UTILITAIRE_PROJECTIONORTHO_H__

#include "Projection.h"

namespace vue 
{
   ////////////////////////////////////////////////////////////////////////
   /// @class ProjectionOrtho
   /// @brief Classe implantant une projection orthogonale.
   ///
   /// Cette classe implante l'interface de projection definie par la
   /// classe de base Projection et ajoute certaines fonctionnalitees
   /// specifiques a la projection orthogonale, comme le zoom autour d'un
   /// point en particulier et le zoom elastique.
   ///
   /// @author Martin Bisson
   /// @date 2006-12-15
   ////////////////////////////////////////////////////////////////////////
   class ProjectionOrtho : public Projection
   {
   public:
      /// Constructeur.
      ProjectionOrtho(int xMinCloture, int xMaxCloture,
                      int yMinCloture, int yMaxCloture,
                      double zAvant,  double zArriere,
                      double zoomInMax, double zoomOutMax,
                      double incrementZoom,
                      double xMinFenetre, double xMaxFenetre,
                      double yMinFenetre, double yMaxFenetre);

      /// Zoom in, c'est-a-dire un agrandissement.
      virtual void zoomerIn();
      /// Zoom out, c'est-a-dire un rapetissement.
      virtual void zoomerOut();
      /// Modification de la clôture.
      virtual void redimensionnerFenetre( const Vecteur2i& coinMin,
                                          const Vecteur2i& coinMax );
      /// Application de la projection.
      virtual void appliquer() const;

      /// Zoom out elastique, sur un rectangle.
      void zoomerOut( const Vecteur2i& coin1, const Vecteur2i& coin2);
      /// Zoom in elatique, sur un rectangle.
      void zoomerIn( const Vecteur2i& coin1, const Vecteur2i& coin2);

      /// Translater la fenetre virtuelle d'un pourcentage en @a X ou en @a Y
      void translater( double deplacementX, double deplacementY );
      /// Translater la fenetre virtuelle d'un vecteur
      void translater( const Vecteur2i& deplacement );
      /// Centrer la fenetre virtuelle sur un point
      void centrerSurPoint( const Vecteur2i& pointCentre );

      /// Obtenir les coordonnees de la fenetre virtuelle.
      inline void obtenirCoordonneesFenetreVirtuelle(
         double& xMin, double& xMax, double& yMin, double& yMax
         ) const;

	  virtual Vecteur4 getDimensionsFenetre()const { return Vecteur4(xMinFenetre_ , xMaxFenetre_ , yMinFenetre_ , yMaxFenetre_); }

   private:
      /// Ajuste la fenetre virtuelle pour respecter le rapport d'aspect.
      void ajusterRapportAspect();
      /// Convertir des coordonnees entre la fenetre de clôture et la fenetre
      /// virtuelle.
      void convertirClotureAVirtuelle(int i, int j, double& x, double& y) const;

      /// Borne inferieure en X de la fenetre virtuelle.
      double xMinFenetre_;
      /// Borne superieure en X de la fenetre virtuelle.
      double xMaxFenetre_;
      /// Borne inferieure en Y de la fenetre virtuelle.
      double yMinFenetre_;
      /// Borne superieure en Y de la fenetre virtuelle.
      double yMaxFenetre_;

	  bool	 premiereRedimensionnement_;
};

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void ProjectionOrtho::obtenirCoordonneesFenetreVirtuelle(double& xMin, double& xMax, double& yMin, double& yMax) const
   ///
   /// Cette fonction retourne les coordonnees de la fenetre virtuelle
   /// associee a cette projection.
   ///
   /// @param[out]  xMin : La variable qui contiendra l'abcsisse minimale.
   /// @param[out]  xMax : La variable qui contiendra l'abcsisse maximale.
   /// @param[out]  yMin : La variable qui contiendra l'ordonnee minimale.
   /// @param[out]  yMax : La variable qui contiendra l'ordonnee maximale.
   ///
   /// @return Les coordonnees de la fenetre virtuelle.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline void ProjectionOrtho::obtenirCoordonneesFenetreVirtuelle(
      double& xMin, double& xMax, double& yMin, double& yMax
      ) const
   {
      xMin = xMinFenetre_;
      xMax = xMaxFenetre_;
      yMin = yMinFenetre_;
      yMax = yMaxFenetre_;
   }


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_PROJECTIONORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
