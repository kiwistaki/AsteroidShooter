//////////////////////////////////////////////////////////////////////////////
/// @file Vue.h
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VUE_H__
#define __UTILITAIRE_VUE_H__


#include "Camera.h"
#include "../Plan3D.h"

namespace vue {
	enum TypeVue_t {
		ORTHOGONALE,
		PERSPECTIVE,
	};

   class Projection;


   ////////////////////////////////////////////////////////////////////////
   /// @class Vue
   /// @brief Classe presentant l'interface commune a toutes les vues.
   ///
   /// Cette classe definit l'interface que devront implanter chacune des
   /// vues, c'est-a-dire comme reagir a certains evenements pour modifier
   /// la vue.  Chaque vue concrete sera generalement composee d'une camera
   /// (classe Camera) et d'une projection (classe Projection).
   ///
   /// Elle offre egalement certaines fonctionnalites communes a toutes les
   /// vues, comme la possibilite de trouver a quel point correspond, en
   /// coordonnees virtuelles, un point donne en coordonnees de clôture.
   ///
   /// @author Martin Bisson
   /// @date 2006-12-16
   ////////////////////////////////////////////////////////////////////////
   class Vue
   {
   public:
      /// Constructeur a partir d'une camera
      Vue(const Camera& camera);
      /// Destructeur virtuel vide.
      virtual ~Vue() {}

      /// Conversion de coordonnees de clôture a coordonnees virtuelles
      bool convertirClotureAVirtuelle(int x, int y, Vecteur3& point) const;
      /// Conversion de coordonnees de clôture a coordonnees virtuelles sur un plan donne
      bool convertirClotureAVirtuelle(int x, int y, const math::Plan3D& plan, Vecteur3& point) const;

      /// Obtient la camera associee a cette vue.
      inline Camera& obtenirCamera();
      /// Obtient la camera associee a cette vue (version constante).
      inline const Camera& obtenirCamera() const;
	  /// Obtenir les coins maximum des coins
	  virtual void obtenirCoinsMax(int& coinMaxX, int& coinMaxY) const = 0;

	  /**
	   * Retourne le plan avant de la caméra
	   */
	  virtual math::Plan3D getPlanAvant() const = 0;

      // Obtention de la projection
      virtual const Projection& obtenirProjection() const = 0;

      /// Application de la projection
	  /// @param direct Si est à true, on applique directement la projection
      virtual void appliquerProjection(bool direct=false) const = 0;
      /// Application de la camera
      virtual void appliquerCamera() const = 0;

      /// Modification de la clotûre
      virtual void redimensionnerFenetre( const Vecteur2i& coinMin,
                                          const Vecteur2i& coinMax ) = 0;

      /// Zoom in, c'est-a-dire un agrandissement.
      virtual void zoomerIn() = 0;
      /// Zoom out, c'est-a-dire un rapetissement.
      virtual void zoomerOut() = 0;
      /// Zoom in elastique
      virtual void zoomerInElastique(const Vecteur2i& coin1,
                                     const Vecteur2i& coin2) = 0;
      /// Zoom out elastique
      virtual void zoomerOutElastique(const Vecteur2i& coin1,
                                      const Vecteur2i& coin2) = 0;

      /// Deplacement dans le plan XY par rapport a la vue
      virtual void deplacerXY(double deplacementX, double deplacementY) = 0;
      /// Deplacement dans le plan XY par rapport a la vue
      virtual void deplacerXY(const Vecteur2i& deplacement) = 0;
      /// Deplacement selon l'axe des Z par rapport a la vue
      virtual void deplacerZ(double deplacement) = 0;
      /// Rotation selon les axes des X et des Y par rapport a la vue
      virtual void rotaterXY(double rotationX, double rotationY) = 0;
      /// Rotation selon les axes des X et des Y par rapport a la vue
      virtual void rotaterXY(const Vecteur2i& rotation) = 0;
      /// Rotation selon l'axe des Z par rapport a la vue
      virtual void rotaterZ(double rotation) = 0;

      /// Animation de la vue en fonction du temps
      virtual void animer(double temps);

	  /**
	   * Retourne le type de la vue
	   */
	  virtual TypeVue_t getType() const = 0;

	  virtual double getTheta() const = 0;
	  virtual double getPhi() const = 0;
	  virtual double getDistance() const = 0;
	  
   protected:
      /// Camera utilisee pour cette vue
      Camera camera_;


   };


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Camera& Vue::obtenirCamera()
   ///
   /// Cette fonction retourne la camera associee a cette vue.
   ///
   /// @return La camera associee a cet objet.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline Camera& Vue::obtenirCamera()
   {
      return camera_;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Camera& Vue::obtenirCamera() const
   ///
   /// Cette fonction retourne la camera associee a cette vue (version
   /// constante).
   ///
   /// @return La camera associee a cet objet.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline const Camera& Vue::obtenirCamera() const
   {
      return camera_;
   }


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_VUE_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
