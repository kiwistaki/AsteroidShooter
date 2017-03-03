///////////////////////////////////////////////////////////////////////////////
/// @file Camera.cpp
/// @author DGI
/// @date 2006-12-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////

#include <windows.h>
#include <GL/glu.h>
#include "Utilitaire.h"
#include "Camera.h"


namespace vue {


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Camera::Camera(const Vecteur3& position, const Vecteur3& pointVise, const Vecteur3& directionHautCamera, const Vecteur3& directionHautMonde)
   ///
   /// Constructeur de la camera a partir des coordonnees cartesiennes.
   ///
   /// @param[in]  position            : position de la camera.
   /// @param[in]  pointVise           : point vise.
   /// @param[in]  directionHautCamera : direction du haut de la camera.
   /// @param[in]  directionHautMonde  : direction du haut du monde de la
   ///                                   camera.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   Camera::Camera( const Vecteur3& position,
                   const Vecteur3& pointVise,
                   const Vecteur3& directionHautCamera,
                   const Vecteur3& directionHautMonde) :
					position_(position),
                    pointVise_(pointVise),
                    directionHaut_(directionHautCamera),
                    directionHautMonde_(directionHautMonde)
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void Camera::deplacerXY( double deplacementX, double deplacementY )
   ///
   /// Deplace la camera dans le plan perpendiculaire a la direction visee
   ///
   /// @param[in]  deplacementX : Deplacement sur l'axe horizontal du plan de
   ///                            la camera.
   /// @param[in]  deplacementY : Deplacement sur l'axe vertical du plan de la
   ///                            camera.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////////
   void Camera::deplacerXY(double deplacementX, double deplacementY)
   {
	   position_[0]+= deplacementX;
	   position_[1]+= deplacementY;
	   pointVise_[0]+= deplacementX;
	   pointVise_[1]+= deplacementY;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void Camera::deplacerZ( double deplacement, bool bougePointVise )
   ///
   /// Deplace la camera dans l'axe de la direction visee.
   ///
   /// @param[in]  deplacement    : Deplacement sur l'axe de la direction visee
   /// @param[in]  bougePointVise : Si vrai, le point de vise est egalement
   ///                              deplace.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////////
   void Camera::deplacerZ(double deplacement, bool bougePointVise)
   {
	   position_[2]+= deplacement;
	   if(bougePointVise){
		   //a Implementer
	   }
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void Camera::tournerXY( double rotationX, double rotationY, bool empecheInversion )
   ///
   /// Rotation de la camera autour de sa position (et donc deplacement du
   /// point vise en gardant la position fixe.
   ///
   /// @param[in] rotationX        : Modification de l'angle de rotation du
   ///                               point vise par rapport a la position.
   /// @param[in] rotationY        : Modification de l'angle d'elevation du
   ///                               point vise par rapport a la position.
   /// @param[in] empecheInversion : Si vrai, la rotation n'est pas effectuee
   ///                               si elle amenerait une inversion de la
   ///                               camera.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////////
   void Camera::tournerXY(double rotationX, double rotationY, bool empecheInversion /*=true*/)                  
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void Camera::orbiterXY( double rotationX, double rotationY, bool empecheInversion )
   ///
   /// Rotation de la camera autour de son point de vise (et donc deplacement
   /// de la position en gardant le point de vise fixe.
   ///
   /// @param[in]  rotationX        : Modification de l'angle de rotation de la
   ///                                position par rapport au point de vise.
   /// @param[in]  rotationY        : Modification de l'angle d'elevation de la
   ///                                position par rapport au point de vise.
   /// @param[in]  empecheInversion : Si vrai, la rotation n'est pas effectue
   ///                                si elle amenerait une inversion de la
   ///                                camera.
   ///
   ///  @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////////
   void Camera::orbiterXY(double rotationX, double rotationY, bool empecheInversion /*=true*/)
   {
   
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void Camera::positionner() const
   ///
   /// Positionne la camera dans la scene a l'aide de gluLookAt().
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void Camera::positionner() const
   {
      gluLookAt( position_[0]      , position_[1]      , position_[2],
                 pointVise_[0]     , pointVise_[1]     , pointVise_[2],
                 directionHaut_[0] , directionHaut_[1] , directionHaut_[2] );
   }


   void Camera::positionnerOrbite(double theta, double phi, double distance) {
	  position_[0] = distance*sin(phi)*cos(theta);
	  position_[1] = distance*sin(phi)*sin(theta);
	  position_[2] = distance*cos(phi);

	  positionner();
   }

   Camera& Camera::operator=(Camera &camera){

      this->position_ = camera.position_;
      this->pointVise_ = camera.pointVise_;
      this->directionHaut_ = camera.directionHaut_;
      this->directionHautMonde_ = camera.directionHautMonde_;

	  return *this;
   }

}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
