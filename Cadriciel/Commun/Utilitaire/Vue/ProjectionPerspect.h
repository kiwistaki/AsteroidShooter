#ifndef __UTILITAIRE_PROJECTIONPERSPECT_H__
#define __UTILITAIRE_PROJECTIONPERSPECT_H__

#include "Projection.h"

namespace vue {
	
	class ProjectionPerspect : public Projection {
	
	public:

	  ProjectionPerspect(int xMinCloture, int xMaxCloture,
						int yMinCloture, int yMaxCloture,
						double zAvant,  double zArriere,
						double zoomInMax, double zoomOutMax,
						double incrementZoom,
                        double xMinFenetre, double xMaxFenetre,
                        double yMinFenetre, double yMaxFenetre);

	  /// Destructeur virtuel vide.
      virtual ~ProjectionPerspect() {}

      /// Zoom in, c'est-a-dire un agrandissement.
      virtual void zoomerIn();

      /// Zoom out, c'est-a-dire un rapetissement.
      virtual void zoomerOut();

      /// Modification de la clôture.
      virtual void redimensionnerFenetre( const Vecteur2i& coinMin, const Vecteur2i& coinMax );

      /// Application de la projection.
      virtual void appliquer() const;

	  virtual Vecteur4 getDimensionsFenetre()const { return Vecteur4(xMinFenetre_ , xMaxFenetre_ , yMinFenetre_ , yMaxFenetre_); }


	private :

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

};


#endif // __UTILITAIRE_PROJECTIONPERSPECT_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
