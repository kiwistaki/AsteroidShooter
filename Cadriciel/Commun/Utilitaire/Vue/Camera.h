////////////////////////////////////////////////////////////////////////////////////
/// @file Camera.h
/// @author DGI
/// @date 2006-12-15
/// @version 1.0 
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_CAMERA_H__
#define __UTILITAIRE_CAMERA_H__

#define M_PI 3.1415926f
#include <math.h>

#define DEG2RAD(a) ((a) * M_PI / 180.0f)
#define RAD2DEG(a) ((a) * 180.0f / M_PI)

#include "Vecteur.h"


namespace vue {


   ///////////////////////////////////////////////////////////////////////////
   /// @class Camera
   /// @brief Classe representant une camera dans le monde en 3D.
   ///
   /// Cette camera encapsule les differentes operations qu'il est possible 
   /// de faire pour deplacer le point de vue de l'observateur a l'interieur
   /// de la scene en 3D.
   ///
   /// @author Martin Bisson
   /// @date 2006-12-15
   ///////////////////////////////////////////////////////////////////////////
   class Camera
   {
   public:
      /// Constructeur a partir des coordonnees cartesiennes.
      Camera( const Vecteur3& position,
              const Vecteur3& pointVise,
              const Vecteur3& directionHautCamera,
              const Vecteur3& directionHautMonde );

      /// Destructeur virtuel vide.
      virtual ~Camera() {}

      /// Assigner la position de la camera.
      inline void assignerPosition(const Vecteur3& position);
      /// Assigner le point vise de la camera.
      inline void assignerPointVise(const Vecteur3& pointVise);
      /// Assigner la direction du haut de la camera.
      inline void assignerDirectionHaut(const Vecteur3& directionHaut);


      /// Obtenir la position de la camera.
      inline const Vecteur3& obtenirPosition() const;
      /// Obtenir le point vise de la camera.
      inline const Vecteur3& obtenirPointVise() const;
      /// Obtenir la direction du haut de la camera.
      inline const Vecteur3& obtenirDirectionHaut() const;

      /// Deplacement dans le plan perpendiculaire a la direction visee.
      void deplacerXY(double deplacementX, double deplacementY);
      /// Deplacement dans l'axe de la direction visee.
      void deplacerZ(double deplacement, bool bougePointVise);
      /// Rotation de la camera autour de sa position.
      void tournerXY(double rotationX, double rotationY, bool empecheInversion = true);
      /// Rotation de la position de la camera autour de son point de vise.
      void orbiterXY(double rotationX, double rotationY, bool empecheInversion = true);

	  void setPosition(Vecteur3 pos){ position_ = pos; }
	  const Vecteur3& getPosition() const { return position_; }
	  Vecteur3& getPosition() { return position_; }

	  /// Positionner la camera (appel a gluLookAt).
      void positionner() const;
	  
	  //Applique les paramètres lié à la vue orbite sur le GluLookAt de la caméra
	  void positionnerOrbite(double theta, double phi, double distance);

	  Camera& operator=(Camera &camera);

   private:
      /// La position de la camera.
      Vecteur3 position_;
      /// La position du point vise par la camera.
      Vecteur3 pointVise_;
      /// La direction du haut de la camera.
      Vecteur3 directionHaut_;
      /// La direction du haut du monde de la camera.
      Vecteur3 directionHautMonde_;
	     };




   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void Camera::assignerPosition(const Vecteur3& position)
   ///
   /// Cette fonction permet d'assigner la position de la camera.
   ///
   /// @param[in] position : La nouvelle position de la camera.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline void Camera::assignerPosition(const Vecteur3& position)
   {
      position_ = position;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void Camera::assignerPointVise(const Vecteur3& pointVise)
   ///
   /// Cette fonction permet d'assigner le point de vise de la camera.
   ///
   /// @param[in] pointVise : Le nouveau point de vise de la camera.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline void Camera::assignerPointVise(const Vecteur3& pointVise)
   {
      pointVise_ = pointVise;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void Camera::assignerDirectionHaut(const Vecteur3& directionHaut)
   ///
   /// Cette fonction permet d'assigner la direction du haut de la camera.
   ///
   /// @param[in] directionHaut : La nouvelle direction du haut de la camera.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline void Camera::assignerDirectionHaut(const Vecteur3& directionHaut)
   {
      directionHaut_ = directionHaut;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur3& Camera::obtenirPosition() const
   ///
   /// Cette fonction permet d'obtenir la position de la camera.
   ///
   /// @return La position de la camera.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline const Vecteur3& Camera::obtenirPosition() const
   {
      return position_;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur3& Camera::obtenirPointVise() const
   ///
   /// Cette fonction permet d'obtenir le point de vise de la camera.
   ///
   /// @return Le point de vise de la camera.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline const Vecteur3& Camera::obtenirPointVise() const
   {
      return pointVise_;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur3& Camera::obtenirDirectionHaut() const
   ///
   /// Cette fonction permet d'obtenir la direction du haut de la camera.
   ///
   /// @return La direction du haut de la camera.
   ///
   ////////////////////////////////////////////////////////////////////////
   inline const Vecteur3& Camera::obtenirDirectionHaut() const
   {
      return directionHaut_;
   }


}; // Fin de l'espace de nom vue.


#endif // __UTILITAIRE_CAMERA_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
