///////////////////////////////////////////////////////////////////////////////
/// @file AideCollision.cpp
/// @brief Ce fichier contient l'implantation de l'espace de nom aidecollision.
///
/// Il contient les implantations de fonctions utiles pour le calcul des forces
/// causees par les collisions.
///
/// @author Martin Bisson
/// @date 2007-01-10
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////

#include "AideCollision.h"


namespace aidecollision {


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn DetailsCollision calculerCollisionSegment(
   ///        const Vecteur2& point1,
   ///        const Vecteur2& point2,
   ///        const Vecteur2& position,
   ///        double          rayon,
   ///        bool            collisionAvecPoints
   ///        );
   ///
   /// Cette fonction calcule l'intersection d'un cercle, identifie par son
   /// centre et son rayon, avec un segment de droite, identifie par les 
   /// coordonnees de chacune de ses extremites.
   ///
   /// Elle ne fait qu'appeler la version 3D de cette meme fonction.
   ///
   /// @param[in] point1              : Premiere extremite du segment de
   ///                                  droite.
   /// @param[in] point2              : Seconde extremite du segment de
   ///                                  droite.
   /// @param[in] position            : Centre du cercle.
   /// @param[in] rayon               : Rayon du cercle.
   /// @param[in] collisionAvecPoints : Vrai si on veut les collisions avec
   ///                                  les extremites.
   ///
   /// @return Structure contenant de l'information sur la collision.
   ///
   ////////////////////////////////////////////////////////////////////////
   DetailsCollision calculerCollisionSegment(
      const Vecteur2& point1,
      const Vecteur2& point2,
      const Vecteur2& position,
      double          rayon,
      bool            collisionAvecPoints //= true
      )
   {
      return calculerCollisionSegment(
         point1.convertir<3>(),
         point2.convertir<3>(),
         position.convertir<3>(),
         rayon,
         collisionAvecPoints
         );
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn DetailsCollision calculerCollisionSegment(
   ///        const Vecteur3& point1,
   ///        const Vecteur3& point2,
   ///        const Vecteur3& position,
   ///        double          rayon,
   ///        bool            collisionAvecPoints
   ///        );
   ///
   /// Cette fonction calcule l'intersection d'une sphere, identifiee par son
   /// centre et son rayon, avec un segment de droite, identifie par les 
   /// coordonnees de chacune de ses extremites.
   ///
   /// @param[in] point1              : Premiere extremite du segment de
   ///                                  droite.
   /// @param[in] point2              : Seconde extremite du segment de
   ///                                  droite.
   /// @param[in] position            : Centre de la sphere.
   /// @param[in] rayon               : Rayon de la sphere.
   /// @param[in] collisionAvecPoints : Vrai si on veut les collisions avec
   ///                                  les extremites.
   ///
   /// @return Structure contenant de l'information sur la collision.
   ///
   ////////////////////////////////////////////////////////////////////////
   DetailsCollision calculerCollisionSegment(
      const Vecteur3& point1,
      const Vecteur3& point2,
      const Vecteur3& position,
      double          rayon,
      bool            collisionAvecPoints //= true
      )
   {
      // Valeur de retour.
      DetailsCollision detailsCollision;
      detailsCollision.type = COLLISION_AUCUNE;

      // On calcule la projection de la position de la sphere sur le vecteur
      // du segment de droite.
      const Vecteur3 segment = point2 - point1;
      const double ratio = produitScalaire(position - point1, segment) /
                           segment.norme2();

      if (collisionAvecPoints) {
         if (ratio < 0.0) {
            // On est du côte du premier point.
            const Vecteur3 directionCollision = position - point1;
            const double distance = directionCollision.norme();
            if (distance < rayon) {
               detailsCollision.type = COLLISION_SEGMENT_PREMIERPOINT;
               detailsCollision.direction = directionCollision / distance;
               detailsCollision.enfoncement = rayon - distance;
            }
         }
         else if (ratio > 1.0) {
            // On est du côte du second point.
            const Vecteur3 directionCollision = position - point2;
            const double distance = directionCollision.norme();
            if (distance < rayon) {
               detailsCollision.type = COLLISION_SEGMENT_DEUXIEMEPOINT;
               detailsCollision.direction = directionCollision / distance;
               detailsCollision.enfoncement = rayon - distance;
            }
         }
      }

      if (ratio >= 0.0 && ratio <= 1.0) {
         // On est sur le segment de droite.
         Vecteur3f pointPerpendiculaire = (1 - ratio) * point1 + ratio * point2;
         const Vecteur3 directionCollision = position - pointPerpendiculaire;
         const double distance = directionCollision.norme();
         if (distance < rayon) {
            detailsCollision.type = COLLISION_SEGMENT;
            detailsCollision.direction = directionCollision / distance;
            detailsCollision.enfoncement = rayon - distance;
         }
      }

      return detailsCollision;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn DetailsCollision calculerCollisionCercle(
   ///        const Vecteur2& centreCercle,
   ///        double          rayonCercle,
   ///        const Vecteur2& positionObjet,
   ///        double          rayonObjet
   ///        );
   ///
   /// Cette fonction calcule l'intersection d'un cercle avec un autre
   /// cercle, chacun identifie par son centre et son rayon.
   ///
   /// Elle ne fait qu'appeler la version 3D de cette meme fonction.
   ///
   /// @param[in] centreCercle  : Centre du cercle avec lequel on teste la
   ///                            collision.
   /// @param[in] rayonCercle   : Rayon du cercle avec lequel on teste la
   ///                            collision.
   /// @param[in] positionObjet : Position de l'objet peut-etre en collision.
   /// @param[in] rayonObjet    : Rayon de l'objet peut-etre en collision.
   ///
   /// @return Structure contenant de l'information sur la collision.
   ///
   ////////////////////////////////////////////////////////////////////////
   DetailsCollision calculerCollisionCercle(
      const Vecteur2& centreCercle,
      double          rayonCercle,
      const Vecteur2& positionObjet,
      double          rayonObjet
      )
   {
      return calculerCollisionSphere(
         centreCercle.convertir<3>(),
         rayonCercle,
         positionObjet.convertir<3>(),
         rayonObjet
         );
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn DetailsCollision calculerCollisionArc(
   ///        const Vecteur2& centreCercle,
   ///        const Vecteur2& pointArc1,
   ///        const Vecteur2& pointArc2,
   ///        const Vecteur2& positionObjet,
   ///        double          rayonObjet
   ///        );
   ///
   /// Cette fonction calcule l'intersection d'un cercle identifie par
   /// son centre et son rayon, avec un arc de cercle identifie par ses
   /// deux extremites et son centre.
   ///
   /// @param[in] centreCercle  : Centre de l'arc avec lequel on teste
   ///                            la collision.
   /// @param[in] pointArc1     : Premiere extremite de l'arc avec lequel on
   ///                            teste la collision.
   /// @param[in] pointArc2     : Seconde extremite de l'arc avec lequel on
   ///                            teste la collision.
   /// @param[in] positionObjet : Position de l'objet peut-etre en collision.
   /// @param[in] rayonObjet    : Rayon de l'objet peut-etre en collision.
   ///
   /// @return Structure contenant de l'information sur la collision.
   ///
   ////////////////////////////////////////////////////////////////////////
   DetailsCollision calculerCollisionArc(
      const Vecteur2& centreCercle,
      const Vecteur2& pointArc1,
      const Vecteur2& pointArc2,
      const Vecteur2& positionObjet,
      double          rayonObjet
      )
   {
      // Valeur de retour.
      DetailsCollision detailsCollision;
      detailsCollision.type = COLLISION_AUCUNE;

      // Rayon de l'arc de cercle.
      double rayonCercle = (pointArc1 - centreCercle).norme();

      detailsCollision.direction = (positionObjet - centreCercle).convertir<3>();
      detailsCollision.enfoncement = rayonCercle + rayonObjet -
                                     detailsCollision.direction.norme();

      if (detailsCollision.enfoncement > 0) {
         Vecteur3 direction1 = (pointArc1 - centreCercle).convertir<3>();
         Vecteur3 direction2 = (pointArc2 - centreCercle).convertir<3>();

         // On verifie si la direction est situee a l'interieur de l'arc a
         // l'aide de produits vectoriels.
         double sensExtremites = produitVectoriel(direction1, direction2)[2];
         double sens1          = produitVectoriel(direction1, detailsCollision.direction)[2];
         double sens2          = produitVectoriel(detailsCollision.direction, direction2)[2];

         if ( ((sens1 > 0.0) == (sensExtremites > 0.0)) &&
              ((sens1 > 0.0) == (sens2 > 0.0)) ) {
            detailsCollision.type = COLLISION_ARC;
         }
      }

      return detailsCollision;      
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn DetailsCollision calculerCollisionSphere( const Vecteur3& centreSphere, double rayonSphere, const Vecteur3& positionObjet, double rayonObjet );
   ///
   /// Cette fonction calcule l'intersection d'une sphere avec une autre
   /// sphere, chacune identifiee par son centre et son rayon.
   ///
   /// @param[in] centreSphere  : Centre de la sphere avec laquelle on teste la
   ///                            collision.
   /// @param[in] rayonSphere   : Rayon de la sphere avec laquelle on teste la
   ///                            collision.
   /// @param[in] positionObjet : Position de l'objet peut-etre en collision.
   /// @param[in] rayonObjet    : Rayon de l'objet peut-etre en collision.
   ///
   /// @return Structure contenant de l'information sur la collision.
   ///
   ////////////////////////////////////////////////////////////////////////
   DetailsCollision calculerCollisionSphere(
      const Vecteur3& centreSphere,
      double          rayonSphere,
      const Vecteur3& positionObjet,
      double          rayonObjet
      )
   {
      // Valeur de retour
      DetailsCollision detailsCollision;

      detailsCollision.direction = positionObjet - centreSphere;
      detailsCollision.enfoncement = rayonSphere + rayonObjet -
                                     detailsCollision.direction.norme();

      if (detailsCollision.enfoncement > 0)
         detailsCollision.type = COLLISION_SPHERE;
      else
         detailsCollision.type = COLLISION_AUCUNE;

      return detailsCollision;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Vecteur2 calculerForceRebondissement2D(
   ///        const DetailsCollision& details,
   ///        double constanteRebondissement
   ///        );
   ///
   /// Cette fonction calcule la force causee par une collision a partir
   /// de la loi des ressorts qui stipule que la force est proportionnelle
   /// a une constante caracterisant le ressort (dans ce cas l'objet sur
   /// lequel on rebondit) et a l'etirement ou la compression du ressort
   /// (dans ce cas l'enfoncement).
   ///
   ///
   /// @param[in] details                 : Details de la collision.
   /// @param[in] constanteRebondissement : Constante de rebondissement de
   ///                                      l'objet.
   ///
   /// @return Force causee par la collision, en deux dimensions.
   ///
   ////////////////////////////////////////////////////////////////////////
   Vecteur2 calculerForceRebondissement2D(
      const DetailsCollision& details,
      double constanteRebondissement
      )
   {
      if (details.type == COLLISION_AUCUNE) {
         // Pas de collision, donc pas de force
         return Vecteur2(0, 0);
      }
      else {
         // Collision: application de la loi des ressorts
         return details.enfoncement * constanteRebondissement *
            details.direction.convertir<2>();
      }
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Vecteur3 calculerForceRebondissement3D(
   ///        const DetailsCollision& details,
   ///        double constanteRebondissement
   ///        );
   ///
   /// Cette fonction calcule la force causee par une collision a partir
   /// de la loi des ressorts qui stipule que la force est proportionnelle
   /// a une constante caracterisant le ressort (dans ce cas l'objet sur
   /// lequel on rebondit) et a l'etirement ou la compression du ressort
   /// (dans ce cas l'enfoncement).
   ///
   /// @param[in] details                 : Details de la collision.
   /// @param[in] constanteRebondissement : Constante de rebondissement de
   ///                                      l'objet.
   ///
   /// @return Force causee par la collision, en trois dimensions.
   ///
   ////////////////////////////////////////////////////////////////////////
   Vecteur3 calculerForceRebondissement3D(
      const DetailsCollision& details,
      double constanteRebondissement
      )
   {
      if (details.type == COLLISION_AUCUNE) {
         // Pas de collision, donc pas de force.
         return Vecteur3(0, 0, 0);
      }
      else {
         // Collision: application de la loi des ressorts.
         return (float) (details.enfoncement * constanteRebondissement) *
            details.direction;
      }
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Vecteur2 calculerForceAmortissement2D(
   ///        const DetailsCollision& details,
   ///        const Vecteur2& vitesse,
   ///        double constanteAmortissement
   ///        );
   ///
   /// Cette fonction calcule une force d'amortissement proportionnelle a
   /// la vitesse et dans sa direction, causee par une collision.
   ///
   /// Elle ne fait qu'appeler la version 3D de cette meme fonction.
   ///
   /// @param[in] details                : Details de la collision.
   /// @param[in] vitesse                : Vitesse de l'objet en collision.
   /// @param[in] constanteAmortissement : Constante d'amortissement de
   ///                                     l'objet.
   ///
   /// @return Force causee par la collision, en deux dimensions.
   ///
   ////////////////////////////////////////////////////////////////////////
   Vecteur2 calculerForceAmortissement2D(
      const DetailsCollision& details,
      const Vecteur2& vitesse,
      double constanteAmortissement
      )
   {
      return calculerForceAmortissement3D(
         details, vitesse.convertir<3>(), constanteAmortissement
         ).convertir<2>();
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Vecteur3 calculerForceAmortissement3D(
   ///        const DetailsCollision& details,
   ///        const Vecteur3& vitesse,
   ///        double constanteAmortissement
   ///        );
   ///
   /// Cette fonction calcule une force d'amortissement proportionnelle a
   /// la vitesse et dans sa direction, causee par une collision.
   ///
   /// @param[in] details                : Details de la collision.
   /// @param[in] vitesse                : Vitesse de l'objet en collision.
   /// @param[in] constanteAmortissement : Constante d'amortissement de
   ///                                     l'objet.
   ///
   /// @return Force causee par la collision, en trois dimensions.
   ///
   ////////////////////////////////////////////////////////////////////////
   Vecteur3 calculerForceAmortissement3D(
      const DetailsCollision& details,
      const Vecteur3& vitesse,
      double constanteAmortissement
      )
   {
      if (details.type == COLLISION_AUCUNE) {
         // Pas de collision, donc pas de force.
         return Vecteur3(0, 0, 0);
      }
      else {
         // Collision: application d'un amortissement.
         const Vecteur3 vitesseCollision = vitesse >> details.direction;
         return vitesseCollision * -constanteAmortissement;
      }
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Vecteur2 calculerCollisionSegment(
   ///        const Vecteur2&   point1,
   ///        const Vecteur2&   point2,
   ///        const Vecteur2&   position,
   ///        double            rayon,
   ///        bool              collisionAvecPoints,
   ///        double            constanteRebondissement,
   ///        double            constanteAmortissement,
   ///        const Vecteur2&   vitesse,
   ///        DetailsCollision* retourDetails = 0
   ///        );
   ///
   /// Cette fonction calcule la force causee par la collision d'un cercle,
   /// identifie par son centre et son rayon, avec un segment de droite,
   /// identifie par les coordonnees de chacune de ses extremites.  Elle
   /// tient compte d'une force de rebondissement ainsi qu'une force
   /// d'amortissement.
   ///
   /// Elle ne fait qu'appeler la version 3D de cette meme fonction.
   ///
   /// @param[in]  point1                  : Premiere extremite du segment de
   ///                                       droite.
   /// @param[in]  point2                  : Seconde extremite du segment de
   ///                                       droite.
   /// @param[in]  position                : Centre du cercle.
   /// @param[in]  rayon                   : Rayon du cercle.
   /// @param[in]  collisionAvecPoints     : Vrai si on veut les collisions
   ///                                       avec les extremites.
   /// @param[in]  constanteRebondissement : Constante de rebondissement de
   ///                                       l'objet.
   /// @param[in]  constanteAmortissement  : Constante d'amortissement de
   ///                                       l'objet.
   /// @param[in]  vitesse                 : Vitesse de l'objet en collision.
   /// @param[out] retourDetails           : Pointeur pour retourner les
   ///                                       details de la collision.
   ///
   /// @return Force causee par la collision, en deux dimensions.
   ///
   ////////////////////////////////////////////////////////////////////////
   Vecteur2 calculerCollisionSegment(
      const Vecteur2&   point1,
      const Vecteur2&   point2,
      const Vecteur2&   position,
      double            rayon,
      bool              collisionAvecPoints,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const Vecteur2&   vitesse,
      DetailsCollision* retourDetails //= 0
      )
   {
      return calculerCollisionSegment(
         point1.convertir<3>(), point2.convertir<3>(),
         position.convertir<3>(), rayon,
         collisionAvecPoints,
         constanteRebondissement,
         constanteAmortissement,
         vitesse.convertir<3>(),
         retourDetails
         ).convertir<2>();
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Vecteur3 calculerCollisionSegment(
   ///        const Vecteur3&   point1,
   ///        const Vecteur3&   point2,
   ///        const Vecteur3&   position,
   ///        double            rayon,
   ///        bool              collisionAvecPoints,
   ///        double            constanteRebondissement,
   ///        double            constanteAmortissement,
   ///        const Vecteur3&   vitesse,
   ///        DetailsCollision* retourDetails = 0
   ///        );
   ///
   /// Cette fonction calcule la force causee par la collision d'un cercle,
   /// identifie par son centre et son rayon, avec un segment de droite,
   /// identifie par les coordonnees de chacune de ses extremites.  Elle
   /// tient compte d'une force de rebondissement ainsi qu'une force
   /// d'amortissement.
   ///
   /// @param[in]  point1                  : Premiere extremite du segment de
   ///                                       droite.
   /// @param[in]  point2                  : Seconde extremite du segment de
   ///                                       droite.
   /// @param[in]  position                : Centre du cercle.
   /// @param[in]  rayon                   : Rayon du cercle.
   /// @param[in]  collisionAvecPoints     : Vrai si on veut les collisions
   ///                                       avec les extremites.
   /// @param[in]  constanteRebondissement : Constante de rebondissement de
   ///                                       l'objet.
   /// @param[in]  constanteAmortissement  : Constante d'amortissement de
   ///                                       l'objet.
   /// @param[in]  vitesse                 : Vitesse de l'objet en collision.
   /// @param[out] retourDetails           : Pointeur pour retourner les
   ///                                       details de la collision.
   ///
   /// @return Force causee par la collision, en trois dimensions.
   ///
   ////////////////////////////////////////////////////////////////////////
   Vecteur3 calculerCollisionSegment(
      const Vecteur3&   point1,
      const Vecteur3&   point2,
      const Vecteur3&   position,
      double            rayon,
      bool              collisionAvecPoints,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const Vecteur3&   vitesse,
      DetailsCollision* retourDetails //= 0
      )
   {
      DetailsCollision details = calculerCollisionSegment(
         point1, point2,
         position, rayon,
         collisionAvecPoints
         );

      Vecteur3 force = calculerForceRebondissement3D(
         details, constanteRebondissement
         );
      force += calculerForceAmortissement3D(
         details, vitesse, constanteAmortissement
         );

      if (retourDetails)
         *retourDetails = details;

      return force;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Vecteur2 calculerCollisionCercle(
   ///        const Vecteur2&   centreCercle,
   ///        double            rayonCercle,
   ///        const Vecteur2&   positionObjet,
   ///        double            rayonObjet,
   ///        double            constanteRebondissement,
   ///        double            constanteAmortissement,
   ///        const Vecteur2&   vitesse,
   ///        DetailsCollision* retourDetails = 0
   ///        );
   ///
   /// Cette fonction calcule la force causee par la collision d'un
   /// cercle avec un autre cercle, chacun identifie par son centre
   /// et son rayon.  Elle tient compte d'une force de rebondissement
   /// ainsi qu'une force d'amortissement.
   ///
   /// Elle ne fait qu'appeler la version 3D de cette meme fonction.
   ///
   /// @param[in]  centreCercle            : Centre du cercle avec lequel on
   ///                                       teste la collision.
   /// @param[in]  rayonCercle             : Rayon du cercle avec lequel on
   ///                                       teste la collision.
   /// @param[in]  positionObjet           : Position de l'objet peut-etre en
   ///                                       collision.
   /// @param[in]  rayonObjet              : Rayon de l'objet peut-etre en
   ///                                       collision.
   /// @param[in]  constanteRebondissement : Constante de rebondissement de
   ///                                       l'objet.
   /// @param[in]  constanteAmortissement  : Constante d'amortissement de
   ///                                       l'objet.
   /// @param[in]  vitesse                 : Vitesse de l'objet en collision.
   /// @param[out] retourDetails           : Pointeur pour retourner les
   ///                                       details de la collision.
   ///
   /// @return Force causee par la collision, en deux dimensions.
   ///
   ////////////////////////////////////////////////////////////////////////
   Vecteur2 calculerCollisionCercle(
      const Vecteur2&   centreCercle,
      double            rayonCercle,
      const Vecteur2&   positionObjet,
      double            rayonObjet,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const Vecteur2&   vitesse,
      DetailsCollision* retourDetails //= 0
      )
   {
      return calculerCollisionSphere(
         centreCercle.convertir<3>(), rayonCercle,
         positionObjet.convertir<3>(), rayonObjet,
         constanteRebondissement,
         constanteAmortissement,
         vitesse.convertir<3>(),
         retourDetails
         ).convertir<2>();
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn Vecteur3 calculerCollisionSphere(
   ///        const Vecteur3&   centreSphere,
   ///        double            rayonSphere,
   ///        const Vecteur3&   positionObjet,
   ///        double            rayonObjet,
   ///        double            constanteRebondissement,
   ///        double            constanteAmortissement,
   ///        const Vecteur3&   vitesse,
   ///        DetailsCollision* retourDetails = 0
   ///        );
   ///
   /// Cette fonction calcule la force causee par la collision d'une
   /// sphere avec une autre sphere, chacune identifiee par son centre
   /// et son rayon.  Elle tient compte d'une force de rebondissement
   /// ainsi qu'une force d'amortissement.
   ///
   /// @param[in]  centreSphere            : Centre de la sphere avec laquelle
   ///                                       on teste la collision.
   /// @param[in]  rayonSphere             : Rayon de la sphere avec laquelle
   ///                                       on teste la collision.
   /// @param[in]  positionObjet           : Position de l'objet peut-etre en
   ///                                       collision.
   /// @param[in]  rayonObjet              : Rayon de l'objet peut-etre en
   ///                                       collision.
   /// @param[in]  constanteRebondissement : Constante de rebondissement de
   ///                                       l'objet.
   /// @param[in]  constanteAmortissement  : Constante d'amortissement de
   ///                                       l'objet.
   /// @param[in]  vitesse                 : Vitesse de l'objet en collision.
   /// @param[out] retourDetails           : Pointeur pour retourner les
   ///                                       details de la collision.
   ///
   /// @return Force causee par la collision, en trois dimensions.
   ///
   ////////////////////////////////////////////////////////////////////////
   Vecteur3 calculerCollisionSphere(
      const Vecteur3&   centreSphere,
      double            rayonSphere,
      const Vecteur3&   positionObjet,
      double            rayonObjet,
      double            constanteRebondissement,
      double            constanteAmortissement,
      const Vecteur3&   vitesse,
      DetailsCollision* retourDetails //= 0
      )
   {
      DetailsCollision details = calculerCollisionSphere(
         centreSphere, rayonSphere,
         positionObjet, rayonObjet
         );

      Vecteur3 force = calculerForceRebondissement3D(
         details, constanteRebondissement
         );
      force += calculerForceAmortissement3D(
         details, vitesse, constanteAmortissement
         );

      if (retourDetails)
         *retourDetails = details;

      return force;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn double calculerCombinaisonRebondissement(
   ///        double constante1, double constante2
   ///        );
   ///
   /// Cette fonction calcule la constante resultant de la combinaison de deux
   /// corps en collision possedant chacun leur constante de rebondissement.
   ///
   /// Elle utilise le modele de ressort en serie qui se compriment l'un
   /// l'autre.
   ///
   /// @param[in] constante1 : La constante du premier objet.
   /// @param[in] constante2 : La constante du second objet.
   ///
   /// @return Constante resultante pour les deux objets.
   ///
   ////////////////////////////////////////////////////////////////////////
   double calculerCombinaisonRebondissement(
      double constante1, double constante2
      )
   {
      return constante1 * constante2 / (constante1 + constante2);
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn double calculerCombinaisonAmortissement(
   ///        double constante1, double constante2
   ///        );
   ///
   /// Cette fonction calcule la constante resultant de la combinaison de deux
   /// corps en collision possedant chacun leur constante d'amortissement.
   ///
   /// @param[in] constante1 : La constante du premier objet.
   /// @param[in] constante2 : La constante du second objet.
   ///
   /// @return Constante resultante pour les deux objets.
   ///
   ////////////////////////////////////////////////////////////////////////
   double calculerCombinaisonAmortissement(
      double constante1, double constante2
      )
   {
      return constante1 + constante2;
   }

   bool calculerIntersectionPointTriangle(const Vecteur3f& point, const Vecteur3f& p1,
										  const Vecteur3f& p2, const Vecteur3f& p3)
   {
	   // Tire de http://www.blackpawn.com/texts/pointinpoly/
	   Vecteur3f v0 = p3 - p1;
	   Vecteur3f v1 = p2 - p1;
	   Vecteur3f v2 = point - p1;

	   float dot00 = produitScalaire(v0, v0);
	   float dot01 = produitScalaire(v0, v1);
	   float dot02 = produitScalaire(v0, v2);
	   float dot11 = produitScalaire(v1, v1);
	   float dot12 = produitScalaire(v1, v2);

	   // Coordonees barycentriques
	   float inv = 1.0f / (dot00 * dot11 - dot01 * dot01);
	   float u = (dot11 * dot02 - dot01 * dot12) * inv;
	   float v = (dot00 * dot12 - dot01 * dot02) * inv;

	   // Est-ce que le point est dans le triangle?
	   return (u >= 0.0f) && (v >= 0.0f) && (u + v < 1.0f);
   }

} // Fin de l'espace de nom aidecollision.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
