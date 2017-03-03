////////////////////////////////////////////////////////////////////////////////////
/// @file Projection.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <GL/gl.h>
#include "Projection.h"
#include "../EtatOpenGL.h"
#include <string>
using namespace std;

namespace vue {


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Projection::Projection(int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant,  double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, bool estPerspective)
   ///
   /// Constructeur d'une projection.  Ne fait qu'assigner les variables
   /// membres.
   ///
   /// @param[in] xMinCloture    : coordonnee minimale en @a x de la clôture.
   /// @param[in] xMaxCloture    : coordonnee maximale en @a x de la clôture.
   /// @param[in] yMinCloture    : coordonnee minimale en @a y de la clôture.
   /// @param[in] yMaxCloture    : coordonnee maximale en @a y de la clôture.
   /// @param[in] zAvant         : distance du plan avant (en @a z).
   /// @param[in] zArriere       : distance du plan arriere (en @a z).
   /// @param[in] zoomInMax      : facteur de zoom in maximal.
   /// @param[in] zoomOutMax     : facteur de zoom out maximal.
   /// @param[in] incrementZoom  : distance du plan arriere (en @a z).
   /// @param[in] estPerspective : vrai si la projection est perspective.
   /// 
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////
   Projection::Projection(int xMinCloture, int xMaxCloture,
                          int yMinCloture, int yMaxCloture,
                          double zAvant,  double zArriere,
                          double zoomInMax, double zoomOutMax,
                          double incrementZoom, bool estPerspective) :
      xMinCloture_(xMinCloture),
      xMaxCloture_(xMaxCloture),
      yMinCloture_(yMinCloture),
      yMaxCloture_(yMaxCloture),
      zAvant_(zAvant),
      zArriere_(zArriere),
      zoomInMax_(zoomInMax),
      zoomOutMax_(zoomOutMax),
      incrementZoom_(incrementZoom),
      estPerspective_(estPerspective)
   {
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void Projection::mettreAJourCloture() const
   ///
   /// Specifie la clôture de la fenetre a l'aide de la fonction glViewport()
   /// dans la machine a etats d'OpenGL.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void Projection::mettreAJourCloture() const
   {
      glViewport( xMinCloture_, 
                  yMinCloture_,
                  GLint( xMaxCloture_ - xMinCloture_ ), 
                  GLint( yMaxCloture_ - yMinCloture_ ) );
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void Projection::mettreAJourProjection() const
   ///
   /// Specifie la matrice de projection dans la machine a etats d'OpenGL.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void Projection::mettreAJourProjection() const
   {
      // Sauvegarde du mode courant de matrice.
      GLint mode;
      glGetIntegerv(GL_MATRIX_MODE, &mode);

      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();

      // Application de la projection.
      appliquer();
	  EtatOpenGL etat;
	  string state = etat.obtenirChaineGlProjectionMatrix();
      glMatrixMode(mode);
   }
   
}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
