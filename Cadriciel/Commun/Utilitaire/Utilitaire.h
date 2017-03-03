//////////////////////////////////////////////////////////////////////////////
/// @file Utilitaire.h
/// @author Martin Bisson
/// @date 2007-03-11
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_UTILITAIRE_H__
#define __UTILITAIRE_UTILITAIRE_H__

#include "Vecteur.h"

#include <sstream>


namespace utilitaire {


   /// Definition d'un type d'entier non signe.
   typedef unsigned int uint;

   /// Constante pour la difference entre deux nombres reels.
   static const double EPSILON( 0.00000001 );
   /// Constante PI.
   static const double PI( 3.1415926535897932384626433832795 );

   /// Constante PI divise par 2
   static const double PI_OVER_2(1.57079632679);

   /// Constante PI fois 2
   static const double PI_TIMES_2(6.28318530718);

   /// Le vecteur i (dirige vers l'axe des X positifs et unitaire).
   static Vecteur3 vi = Vecteur3( 1.0, 0.0, 0.0 );
   /// Le vecteur j (dirige vers l'axe des Y positifs et unitaire).
   static Vecteur3 vj = Vecteur3( 0.0, 1.0, 0.0 );
   /// Le vecteur k (dirige vers l'axe des Z positifs et unitaire).
   static Vecteur3 vk = Vecteur3( 0.0, 0.0, 1.0 );

   /// Fonction globale pour l'affichage d'erreur.
   void afficherErreur(const std::string& message);
   /// Fonction globale pour l'affichage d'informations
   void afficherInformations(const std::string& message);

   /// Pour convertir les angles de radians en degres.
   double RAD_TO_DEG( double AngleRad );
   /// Pour convertir les angles de degres en radians.
   double DEG_TO_RAD( double AngleDeg );

   /// Pour convertir les km/h en m/s.
   float KMH_TO_MS( float kmh );
   /// Pour convertir les m/s en km/h.
   float MS_TO_KMH( float ms );

   /// Fonction pour connaître le signe d'un nombre.
   float SIGN( float nombre );

   /// Fonction qui retourne la valeur absolue d'un nombre.
   float ABS( float nombre );

   /// Fonction pour savoir si un double est egal a zero.
   bool EGAL_ZERO(double Nombre);

   /// Pour savoir si un nombre est dans l'intervalle: [BorneMin, BorneMax].
   bool DANS_INTERVALLE( double Valeur, double BorneMin, double BorneMax );
   /// Fonction pour verifier si un Point 2d est dans un carre.
   bool DANS_LIMITESXY( double x, double xMin, double xMax,
                        double y, double yMin, double yMax );

   /// Calcule le rapport d'ecrasement
   double ecrasement( double a, double b);

   /// Verification de l'existance d'un fichier
   bool fichierExiste( const std::string& nomDuFichier );

   /// Applique une matrice de transformation a un point.
   Vecteur3 appliquerMatrice( const Vecteur3& point, const double mat[] );


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void borneSuperieure( T& valeur, const T& borne )
   ///
   /// Cette fonction s'assure que la valeur ne depasse pas la borne.
   ///
   /// @param[in,out] valeur : La valeur de l'expression a borner.
   /// @param[in]     borne  : La borne superieure.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   void borneSuperieure( T& valeur, const T& borne )
   {
      if ( valeur > borne )
         valeur = borne;
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void borneInferieure( T& valeur, const T& borne )
   ///
   /// Cette fonction s'assure que la valeur depasse la borne.
   ///
   /// @param[in,out] valeur : La valeur de l'expression a borner.
   /// @param[in]     borne  : La borne inferieure.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   template <class T>
   void borneInferieure( T& valeur, const T& borne )
   {
      if ( valeur < borne )
         valeur = borne;
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn static std::string convertirEnChaine(const T& valeur)
   ///
   /// @brief Conversion d'un type generique vers une chaîne de caracteres.
   ///
   /// Cette fonction convertit un type generique en une chaîne de
   /// caracteres.  Comme elle se sert de l'operateur << applique sur
   /// un ostringstream, elle devrait fonctionner pour toutes les classes
   /// qui definissent cet operateur pour les ostream&.
   ///
   /// @param[in] valeur    : Valeur template a convertir en chaîne de
   ///                        caracteres.
   /// @param[in] modifieur : Fonction utilisee pour la conversion de type
   ///                        particulier, par exemple std::hex ou std::oct
   ///                        pour les entiers.
   ///
   /// @return Chaîne representant le type.
   ///
   ////////////////////////////////////////////////////////////////////////
   template<typename T> static std::string convertirEnChaine(
      const T& valeur,
      std::ios_base& (*modifieur)(std::ios_base&) = 0
      )
   {
      std::ostringstream oss;

      // Application du modifieur s'il est specifie.
      if (modifieur)
         oss << modifieur;

      oss << valeur;
      return oss.str();
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn static bool convertirEnType(const std::string& chaine, T& valeur, std::ios_base& (*modifieur)(std::ios_base&) = 0)
   ///
   /// @brief Conversion d'une chaîne de caracteres vers un type generique.
   ///
   /// Cette fonction convertit une chaîne de caracteres en un type generique.
   /// Comme elle se sert de l'operateur >> applique sur un istringstream,
   /// elle devrait fonctionner pour toutes les classes qui definissent cet
   /// operateur pour les istream&.
   ///
   /// @param[in] chaine    : Chaîne a convertir.
   /// @param[in] valeur    : Valeur template qui contiendra la valeur contenu
   ///                        dans la chaîne.  Ne sera pas modifiee si la
   ///                        chaîne n'est pas valide.
   /// @param[in] modifieur : Fonction utilisee pour la conversion de type
   ///                        particulier, par exemple std::hex ou std::oct
   ///                        pour les entiers.
   ///
   /// @return Vrai si la conversion a reussi.
   ///
   ////////////////////////////////////////////////////////////////////////
   template<typename T> static bool convertirEnType(
      const std::string& chaine,
      T& valeur,
      std::ios_base& (*modifieur)(std::ios_base&) = 0
      )
   {
      std::istringstream iss(chaine);

      // Application du modifieur s'il est specifie.
      if (modifieur)
         iss >> modifieur;

      // Lecture de la valeur
      T temp;
      iss >> temp;

      // Pour que la conversion soit un succes, toute la chaîne doit avoir ete
      // convertie.  On ajoute donc le second test pour eviter qu'une chaîne
      // comme "123bidon" puisse etre acceptee et que toute la chaîne soit
      // utilisee pour que la conversion soit consideree comme reussie.
      const bool succes = ( (!iss.fail()) && (iss.peek() == EOF) );

      if (succes)
         valeur = temp;

      return succes;
   }


} // Fin du namespace utilitaire.

#endif // __UTILITAIRE_UTILITAIRE_H__

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
