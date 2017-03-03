//////////////////////////////////////////////////////////////////////////////
/// @file VueOrtho.h
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUEORTHO_H__
#define __UTILITAIRE_VUEORTHO_H__


#include "Vue.h"
#include "Camera.h"
#include "ProjectionOrtho.h"

namespace vue {


   ////////////////////////////////////////////////////////////////////////
   /// @class VueOrtho
   /// @brief Classe concrete de vue orthogonale.
   ///
   /// Cette classe implante le comportement attendu d'une vue orthogonale.
   ///
   /// @author Martin Bisson
   /// @date 2006-12-16
   ////////////////////////////////////////////////////////////////////////
   class VueOrtho : public Vue
   {
   public:
      // Constructeur.
      VueOrtho(const Camera& camera,
               int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture,
               double zAvant,  double zArriere,
               double zoomInMax, double zoomOutMax, 
               double incrementZoom,
               double xMinFenetre, double xMaxFenetre,
               double yMinFenetre, double yMaxFenetre);

	  /// Obtenir les coins maximum des coins
	  virtual void obtenirCoinsMax(int& coinMaxX, int& coinMaxY) const;

      /// Obtention de la projection.
      virtual const ProjectionOrtho& obtenirProjection() const;

      /// Application de la projection.
      virtual void appliquerProjection(bool direct=false) const;

      /// Application de la camera.
      virtual void appliquerCamera() const;

      /// Modification de la clotûre.
      virtual void redimensionnerFenetre( const Vecteur2i& coinMin,
                                          const Vecteur2i& coinMax );

	  virtual math::Plan3D getPlanAvant() const;

      /// Zoom in, c'est-a-dire un agrandissement.
      virtual void zoomerIn();
      /// Zoom out, c'est-a-dire un rapetissement.
      virtual void zoomerOut();
      /// Zoom in elastique.
      virtual void zoomerInElastique(const Vecteur2i& coin1,
                                     const Vecteur2i& coin2);
      /// Zoom out elastique.
      virtual void zoomerOutElastique(const Vecteur2i& coin1,
                                      const Vecteur2i& coin2);

      /// Deplacement dans le plan XY par rapport a la vue.
      virtual void deplacerXY(double deplacementX, double deplacementY);
      /// Deplacement dans le plan XY par rapport a la vue.
      virtual void deplacerXY(const Vecteur2i& deplacement);
      /// Deplacement selon l'axe des Z par rapport a la vue.
      virtual void deplacerZ(double deplacement);
      /// Rotation selon les axes des X et des Y par rapport a la vue.
      virtual void rotaterXY(double rotationX, double rotationY);
      /// Rotation selon les axes des X et des Y par rapport a la vue.
      virtual void rotaterXY(const Vecteur2i& rotation);
      /// Rotation selon l'axe des Z par rapport a la vue.
      virtual void rotaterZ(double rotation);

	  virtual TypeVue_t getType() const { return ORTHOGONALE; }

	  virtual double getTheta() const { return 0.0; }
	  virtual double getPhi() const { return 0.0; }
	  virtual double getDistance() const { return 0.0; }

   private:
      /// Projection utilisee pour cette vue.
      ProjectionOrtho projection_;

   };


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUEORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
