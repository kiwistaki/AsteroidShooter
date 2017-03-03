///////////////////////////////////////////////////////////////////////////////
/// @file AideCollision.h
/// @brief Ce fichier contient la declaration de l'espace de nom aidecollision.
///
/// Il contient les declarations de fonctions utiles pour le calcul des forces
/// causees par les collisions.
///
/// @author Martin Bisson
/// @date 2007-01-10
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_AIDECOLLISION_H__
#define __UTILITAIRE_AIDECOLLISION_H__


#include <Vecteur.h>


/// Espace de nom contenant des fonctions utiles pour le calcul des forces
/// causees par les collisions.
namespace aidecollision {


   /// Type de collisions possibles avec un segment.
   enum Collision {
      COLLISION_AUCUNE = 0 ,
      COLLISION_SEGMENT_PREMIERPOINT ,
      COLLISION_SEGMENT ,
      COLLISION_SEGMENT_DEUXIEMEPOINT ,
      COLLISION_SPHERE ,
      COLLISION_ARC
   };

   /// Structure contenant les informations d'une collision.
   class DetailsCollision {
   public:
      /// Type de collision.
      Collision type;
      /// Direction de la collision.
      Vecteur3  direction;
      /// Enfoncement de l'objet a l'interieur de la collision.
      double    enfoncement;
   };

   /// Calcule la collision d'un objet circulaire avec un segment de droite.
   DetailsCollision calculerCollisionSegment(
      const Vecteur2& point1,
      const Vecteur2& point2,
      const Vecteur2& position,
      double          rayon,
      bool            collisionAvecPoints = true
      );

   /// Calcule la collision d'un objet spherique avec un segment de droite.
   DetailsCollision calculerCollisionSegment(
      const Vecteur3& point1,
      const Vecteur3& point2,
      const Vecteur3& position,
      double          rayon,
      bool            collisionAvecPoints = true
      );

   /// Calcule la collision d'un objet circulaire avec un cercle.
   DetailsCollision calculerCollisionCercle(
      const Vecteur2& centreCercle,
      double          rayonCercle,
      const Vecteur2& positionObjet,
      double          rayonObjet
      );

   /// Calcule la collision d'un objet circulaire avec un arc de cercle.
   DetailsCollision calculerCollisionArc(
      const Vecteur2& centreCercle,
      const Vecteur2& pointArc1,
      const Vecteur2& pointArc2,
      const Vecteur2& positionObjet,
      double          rayonObjet
      );

   /// Calcule la collision d'un objet spherique avec une sphere.
   DetailsCollision calculerCollisionSphere(
      const Vecteur3& centreSphere,
      double          rayonSphere,
      const Vecteur3& positionObjet,
      double          rayonObjet
      );

   /// Calcule la force en deux dimensions a partir d'une collision.
   Vecteur2 calculerForceRebondissement2D(
      const DetailsCollision& details,
      double constanteRebondissement
      );

   /// Calcule la force en trois dimensions a partir d'une collision.
   Vecteur3 calculerForceRebondissement3D(
      const DetailsCollision& details,
      double constanteRebondissement
      );

   /// Calcule la force d'amortissement en deux dimensions au cours d'une
   /// collision.
   Vecteur2 calculerForceAmortissement2D(
      const DetailsCollision& details,
      const Vecteur2& vitesse,
      double constanteAmortissement
      );

   /// Calcule la force d'amortissement en trois dimensions au cours d'une
   /// collision.
   Vecteur3 calculerForceAmortissement3D(
      const DetailsCollision& details,
      const Vecteur3& vitesse,
      double constanteAmortissement
      );

   /// Calcule la force en deux dimensions causee par la collision d'un objet
   /// circulaire avec un segment de droite.
   Vecteur2 calculerCollisionSegment(
      const Vecteur2&   point1,
      const Vecteur2&   point2,
      const Vecteur2&   position,
      double            rayon,
      bool              collisionAvecPoints,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const Vecteur2&   vitesse,
      DetailsCollision* retourDetails = 0
      );

   /// Calcule la force en trois dimensions causee par la collision d'un objet
   /// spherique avec un segment de droite.
   Vecteur3 calculerCollisionSegment(
      const Vecteur3&   point1,
      const Vecteur3&   point2,
      const Vecteur3&   position,
      double            rayon,
      bool              collisionAvecPoints,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const Vecteur3&   vitesse,
      DetailsCollision* retourDetails = 0
      );

   /// Calcule la force en deux dimensions causee par la collision d'un objet
   /// circulaire avec un cercle.
   Vecteur2 calculerCollisionCercle(
      const Vecteur2&   centreCercle,
      double            rayonCercle,
      const Vecteur2&   positionObjet,
      double            rayonObjet,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const Vecteur2&   vitesse,
      DetailsCollision* retourDetails = 0
      );

   /// Calcule la force en trois dimensions causee par la collision d'un objet
   /// spherique avec une sphere.
   Vecteur3 calculerCollisionSphere(
      const Vecteur3&   centreSphere,
      double            rayonSphere,
      const Vecteur3&   positionObjet,
      double            rayonObjet,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const Vecteur3&   vitesse,
      DetailsCollision* retourDetails = 0
      );

   /// Calcule la combinaison de deux constantes de rebondissement.
   double calculerCombinaisonRebondissement(
      double constante1, double constante2
      );

   /// Calcule la combinaison de deux constantes d'amortissement.
   double calculerCombinaisonAmortissement(
      double constante1, double constante2
      );

   /**
    * Calcule l'intersection entre un point et un triangle
	* @param point Le point avec lequel on veut tester l'intersection
	* @param p1 Le premier sommet du triangle
	* @param p2 Le second sommet du triangle
	* @param p3 Le troisieme sommet du triangle
	* @return true si le point est dans le triangle, false sinon
	*/
   bool calculerIntersectionPointTriangle(const Vecteur3f& point, const Vecteur3f& p1,
										  const Vecteur3f& p2, const Vecteur3f& p3);


} // Fin de l'espace de nom aidecollision.


#endif // __UTILITAIRE_AIDECOLLISION_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
