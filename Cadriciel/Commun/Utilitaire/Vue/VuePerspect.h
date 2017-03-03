#ifndef __UTILITAIRE_VUEPERSPECT_H__
#define __UTILITAIRE_VUEPERSPECT_H__


#include "Vue.h"
#include "Camera.h"
#include "ProjectionPerspect.h"

namespace vue{

	class VuePerspect : public Vue{

	public :

	  VuePerspect(  const Camera& camera,
					int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture,
					double zAvant,  double zArriere,
					double zoomInMax, double zoomOutMax,
					double incrementZoom,
					double xMinFenetre, double xMaxFenetre,
					double yMinFenetre, double yMaxFenetre);

	  /// Obtenir les coins maximum des coins
	  virtual void obtenirCoinsMax(int& coinMaxX, int& coinMaxY) const;

      // Obtention de la projection
      virtual const Projection& obtenirProjection() const;

      /// Application de la projection
      virtual void appliquerProjection(bool direct=false) const;

      /// Application de la camera
      virtual void appliquerCamera() const;

	  virtual math::Plan3D getPlanAvant() const;

      /// Modification de la clotûre
      virtual void redimensionnerFenetre( const Vecteur2i& coinMin, const Vecteur2i& coinMax );

      /// Zoom in, c'est-a-dire un agrandissement.
      virtual void zoomerIn();

      /// Zoom out, c'est-a-dire un rapetissement.
      virtual void zoomerOut();

      /// Zoom in elastique
      virtual void zoomerInElastique(const Vecteur2i& coin1, const Vecteur2i& coin2);

      /// Zoom out elastique
      virtual void zoomerOutElastique(const Vecteur2i& , const Vecteur2i&);

      /// Deplacement dans le plan XY par rapport a la vue
      virtual void deplacerXY(double deplacementX, double deplacementY);

      /// Deplacement dans le plan XY par rapport a la vue
      virtual void deplacerXY(const Vecteur2i& deplacement);

      /// Deplacement selon l'axe des Z par rapport a la vue
      virtual void deplacerZ(double deplacement);

      /// Rotation selon les axes des X et des Y par rapport a la vue
      virtual void rotaterXY(double rotationX, double rotationY);

      /// Rotation selon les axes des X et des Y par rapport a la vue
      virtual void rotaterXY(const Vecteur2i& rotation);

      /// Rotation selon l'axe des Z par rapport a la vue
      virtual void rotaterZ(double rotation);

	  virtual TypeVue_t getType() const { return PERSPECTIVE; }

	  //	Retourne l'angle theta en degrés
	  virtual double getTheta() const { return RAD2DEG(theta_); }

	  //	Retourne l'angle phi en degrés
	  virtual double getPhi() const { return RAD2DEG(phi_); }

	  //	Retourne la distance par-rapport au centre
	  virtual double getDistance() const { return distance_; }

	private :

	  ProjectionPerspect projection_;

	  //Variable utiles pour la vue orbite
	  float theta_;
	  float phi_;
	  float distance_;

	  //Validité de la position de la caméra
	  void verifierAngles();

	};
};

#endif // __UTILITAIRE_VUEORTHO_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
