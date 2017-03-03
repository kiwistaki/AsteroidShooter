/////////////////////////////////////////////////////////////////////////////////
/// @file Vue.cpp
/// @author DGI
/// @date 2006-12-18
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
/////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <GL/glu.h>

#include "Vue.h"
#include "Plan3D.h"
#include "Droite3D.h"


namespace vue {


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Vue::Vue(const Camera& camera)
   ///
   /// Ce constructeur permet d'assigner la camera de cette vue.
   ///
   /// @param[in] camera : La camera associee a cette vue.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   Vue::Vue(const Camera& camera)
      : camera_(camera)
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn bool Vue::convertirClotureAVirtuelle(int x, int y, const math::Plan3D& plan, Vecteur3& point) const
   ///
   /// Cette fonction permet de transformer un point (donne en coordonnees
   /// d'affichage) en coordonnees virtuelles etant donne un certain plan sur
   /// lequel doit se trouver le point.  Elle utilise les fonction d'OpenGL
   /// donc cette fonction s'applique peu importe la position de la camera.
   ///
   /// @param[in]      x     : La position @a X du point en coordonnee
   ///                         d'affichage.
   /// @param[in]      y     : La position @a Y du point en coordonnee
   ///                         d'affichage.
   /// @param[in]      plan  : Le plan sur lequel on veut trouver la position
   ///                         correspondante en virtuel.
   /// @param[in, out] point : point transforme @a (x,y) le @a z est le meme
   ///                         que le plan
   ///
   /// @return Faux s'il est impossible de convertir le point en virtuel
   ///         puisque le plan est parallele a la direction de la camera, vrai
   ///         autrement.
   ///
   ////////////////////////////////////////////////////////////////////////////
   bool Vue::convertirClotureAVirtuelle(int x, int y, const math::Plan3D& plan, Vecteur3& point) const
   {
      //Initialisation de variables.
      const GLdouble MinZ = 0.0;
      const GLdouble MaxZ = 1.0;

      // Lire la matrice de modelisation et de visualisation.
      GLdouble matriceModelisation[16];
      glGetDoublev ( GL_MODELVIEW_MATRIX, matriceModelisation );

      // Lire la matrice de projection.
      GLdouble matriceProjection[16];
      glGetDoublev ( GL_PROJECTION_MATRIX, matriceProjection );

      // Lire la clôture.
      GLint cloture[4];
      glGetIntegerv ( GL_VIEWPORT, cloture );

      // Premier point.
      Vecteur3 point1;
      gluUnProject(
         x, cloture[3] - y, MinZ,
         matriceModelisation, matriceProjection, cloture,
         &point1[0], &point1[1], &point1[2]
      );

      // Deuxieme point.
      Vecteur3 point2;
      gluUnProject(
         x, cloture[3] - y, MaxZ,
         matriceModelisation, matriceProjection, cloture,
         &point2[0], &point2[1], &point2[2]
      );

      // On construit la droite.
      math::Droite3D DroiteCoupe( point1, point2 );

      return DroiteCoupe.intersection( plan, point );
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn bool Vue::convertirClotureAVirtuelle(int x, int y, Vecteur3& point) const
   ///
   /// Cette fonction permet de transformer un point (donne en coordonnees
   /// d'affichage) en coordonnees virtuelles dans le plan XY.
   ///
   /// @param[in]      x     : La position @a X du point en coordonnee
   ///                         d'affichage.
   /// @param[in]      y     : La position @a Y du point en coordonnee
   ///                         d'affichage.
   /// @param[in, out] point : point transforme @a (x,y) le @a z est le meme
   ///                         que le plan
   ///
   /// @return Faux s'il est impossible de convertir le point en virtuel
   ///         puisque le plan est parallele a la direction de la camera.
   ///
   ////////////////////////////////////////////////////////////////////////////
   bool Vue::convertirClotureAVirtuelle(int x, int y, Vecteur3& point) const
   {
      const math::Plan3D plan(Vecteur3(0,0,1), Vecteur3(0,0,0));
      return convertirClotureAVirtuelle(x, y, plan, point);
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void Vue::animer(double temps)
   ///
   /// Cette fonction permet de faire evoluer la vue en fonction du temps, par
   /// exemple lorsque cette derniere se deplace par rapport a un objet en
   /// fonction du temps.
   ///
   /// @param[in]  temps double : L'intervalle de temps pour lequel realiser
   ///                            l'animation.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////////
   void Vue::animer(double temps)
   {
   }



}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
