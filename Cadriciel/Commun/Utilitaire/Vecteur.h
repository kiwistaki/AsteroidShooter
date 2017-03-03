///////////////////////////////////////////////////////////////////////////////
/// @file Vecteur.h
/// @author Alex Duru
/// @author Ionut Alexandrescu
/// @author Martin Bisson
/// @author Jean-Francois Perusse
/// @date 2005-06-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_VECTEUR_H__
#define __UTILITAIRE_VECTEUR_H__


#include <iostream>
#include <cmath>

// Les fichiers binaires
#include "CLectureFichierBinaire.h"
#include "CEcritureFichierBinaire.h"


///////////////////////////////////////////////////////////////////////////
/// @class Vecteur
///
///        Definition d'une classe generique pour les vecteurs.
///
///        Cette classe generique implante des vecteurs en n dimensions.
///        Le type du vecteur est aussi generique (double, float, int,...).
///        Les fonctions communes definies sont:
///        - [] pour la lecture et l'ecriture
///        - conversion double/float ou int/float
///        - norme du vecteur
///        - si le vecteur est nul
///        - operateur =
///        - operateur ==
///        - operateur +=
///        - operateur -=
///        - normalisation du vecteur
///        - operateur *= (multiplication par un scalaire)
///        - operateur /= (division par un scalaire)
///        - operateur +
///        - operateur -
///        - operateur * (multiplication par un scalaire)
///        - operateur / (division par un scalaire)
///        - produit scalaire
///        - la reflexion du vecteur @a u par rapport a l'espace vectoriel orthogonal
///        - projection du vecteur @a u sur l'espace vectoriel orthogonal
///        - projection du vecteur @a u sur une droite
///        - operateur << (sortie texte)
///        - operateur >> (entree texte)
///        - operateur <  (sortie binaire)
///        - operateur >  (entree binaire)
///
/// @author Alex Duru
/// @author Ionut Alexandrescu
/// @author Martin Bisson
/// @author Jean-Francois Perusse.
/// @date 2006-02-23
///////////////////////////////////////////////////////////////////////////
template <class T = double, const int N = 3>
class Vecteur
{
public:
   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur()
   ///
   /// Constructeur par defaut qui ne fait rien.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur()
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur ( const Vecteur<T2, N>& u )
   ///
   /// Constructeur "copie" a partir d'un autre type de vecteur.
   ///
   /// @param[in] u : Le vecteur a copier.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   template<class T2>
   inline Vecteur ( const Vecteur<T2, N>& u )
   {
      for ( int i = 0; i < N; i++ ) {
         vect[i] = static_cast<T>(u[i]);
      }
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline T& operator[] ( const int& i )
   ///
   /// Operateur de lecture d'une composante ( @a x: 0, @a y: 1, @a z: 2 ...)
   ///
   /// @param[in] i : ( @a x: 0, @a y: 1, @a z: 2 ...)
   ///
   /// @return La composante ( @a x ou @a y ou @a z ...)
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline T& operator[] ( const int& i )
   {
      return vect[i];
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const T& operator[] ( const int& i ) const
   ///
   /// Operateur de lecture d'une composante sans la modifier ( @a x: 0, @a y: 1, @a z: 2 ...)
   ///
   /// @param[in] i : ( @a x: 0, @a y: 1, @a z: 2 ...)
   ///
   /// @return La composante ( @a x ou @a y ou @a z ...)
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const T& operator[] ( const int& i ) const
   {
      return vect[i];
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline T norme2() const
   ///
   /// Cette fonction calcule le carre de la norme du vecteur
   /// ( ( x*x + y*y +...) ).
   ///
   /// @return Le carre de la norme du vecteur.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline T norme2() const
   {
      T n2 = 0;
      T pow2;
      for ( int i = 0; i < N; i++ ) {
         pow2  = vect[i];
         pow2 *= pow2;
         n2   += pow2;
      }

      return ( n2 );
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline T norme() const
   ///
   /// Cette fonction calcule la norme du vecteur ( sqrt ( x*x + y*y +...) ).
   ///
   /// @return La norme du vecteur.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline T norme() const
   {
      return sqrt( norme2() );
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline bool estNul() const
   ///
   /// Cette fonction teste si le vecteur est nul.
   ///
   /// @return @a true si le vecteur est nul, @a false dans le cas contraire.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline bool estNul() const
   {
      return (norme() == 0);
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur<T, N>& operator= ( const Vecteur<T, N>& v )
   ///
   /// Surcharge de l'operateur d'assignation.
   ///
   /// @param[in] v : Le vecteur a assigner.
   ///
   /// @return La reference vers l'objet assigne afin de respecter la
   ///         semantique de l'operateur d'assignation C++.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const Vecteur<T, N>& operator= ( const Vecteur<T, N>& v )
   {
      for ( int i = 0; i < N; i++ ) {
         vect[i] = v.vect[i];
      }
      return *this;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline bool operator == ( const Vecteur<T, N>& v ) const
   ///
   /// Surcharge de l'operateur d'egalite.
   ///
   /// @param[in] v : Le vecteur dont on verifie l'egalite.
   ///
   /// @return Vrai si les vecteurs sont egaux, faux autrement.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline bool operator == ( const Vecteur<T, N>& v ) const
   {
      for ( int i = 0; i < N; i++ ) {
         if ( vect[i] != v.vect[i] )
            return false;
      }
      return true;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur<T, N>& operator += ( const Vecteur<T, N>& u )
   ///
   /// Surcharge de l'operateur d'ajout a un vecteur.
   ///
   /// @param[in] u : Le vecteur a ajouter.
   ///
   /// @return La reference vers l'objet assigne afin de respecter la
   ///         semantique de l'operateur d'ajout C++.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const Vecteur<T, N>& operator += ( const Vecteur<T, N>& u )
   {
      for ( int i = 0; i < N; i++ ) {
         vect[i] += u.vect[i];
      }
      return *this;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur<T, N>& operator -= ( const Vecteur<T, N>& u )
   ///
   /// Surcharge de l'operateur de retrait d'un vecteur.
   ///
   /// @param[in] u : Le vecteur a retirer.
   ///
   /// @return La reference vers l'objet assigne afin de respecter la
   ///         semantique de l'operateur de retrait C++.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const Vecteur<T, N>& operator -= ( const Vecteur<T, N>& u )
   {
      for ( int i = 0; i < N; i++ ) {
         vect[i] -= u.vect[i];
      }
      return *this;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void normaliser()
   ///
   /// Cette fonction normalise le vecteur.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline void normaliser()
   {
      const T n = norme();
      if ( n != 0 )
         ( *this ) /= n;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur<T, N>& operator*= ( const T k )
   ///
   /// Surcharge de l'operateur de mise a l'echelle par un facteur.
   ///
   /// @param[in] k : Le facteur de mise a l'echelle.
   ///
   /// @return La reference vers l'objet assigne afin de respecter la
   ///         semantique de l'operateur de mise a l'echelle C++.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const Vecteur<T, N>& operator*= ( const T k )
   {
      for ( int i = 0; i < N; i++ ) {
         vect[i] *= k;
      }
      return *this;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur<T, N>& operator /= ( const T k )
   ///
   /// Surcharge de l'operateur de division par un facteur.
   ///
   /// @param[in] k : Le facteur de division.
   ///
   /// @return La reference vers l'objet assigne afin de respecter la
   ///         semantique de l'operateur de division C++.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const Vecteur<T, N>& operator /= ( const T k )
   {
      for ( int i = 0; i < N; i++ ) {
         vect[i] /= k;
      }
      return *this;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur<T, N> operator+ ( const Vecteur<T, N>& v ) const
   ///
   /// Surcharge de l'operateur d'addition.
   ///
   /// @param[in] v : Le vecteur a additionner.
   ///
   /// @return La somme des deux vecteurs.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur<T, N> operator+ ( const Vecteur<T, N>& v ) const
   {
      Vecteur<T, N> r ( *this );
      r += v;
      return r;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur<T, N> operator- ( const Vecteur<T, N>& v ) const
   ///
   /// Surcharge de l'operateur de soustraction.
   ///
   /// @param[in] v : Le vecteur a soustraire.
   ///
   /// @return Le vecteur a soustraire.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur<T, N> operator- ( const Vecteur<T, N>& v ) const
   {
      Vecteur<T, N> r ( *this );
      r -= v;
      return r;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur<T, N> operator* ( const T k ) const
   ///
   /// Surcharge de l'operateur de multiplication par un scalaire.
   ///
   /// @param[in] k : Le facteur de multiplication.
   ///
   /// @return Le vecteur multiplie par le scalaire.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur<T, N> operator* ( const T k ) const
   {
      Vecteur<T, N> r ( *this );
      r *= k;
      return r;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline friend Vecteur<T, N> operator* ( const T k , const Vecteur<T,N>& v)
   ///
   /// Surcharge de l'operateur de multiplication d'un scalaire par un vecteur.
   ///
   /// @param[in] k : Le facteur de multiplication.
   /// @param[in] v : Le vecteur a multiplier.
   ///
   /// @return Le vecteur multiplie par un scalaire.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline friend Vecteur<T, N> operator* ( const T k , const Vecteur<T,N>& v)
   {
      return v * k;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur<T, N> operator / ( const T k ) const
   ///
   /// Surcharge de l'operateur de division par un scalaire.
   ///
   /// @param[in] k : Facteur de division.
   ///
   /// @return Le vecteur divise par le scalaire.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur<T, N> operator / ( const T k ) const
   {
      Vecteur<T, N> r ( *this );
      r /= k;
      return r;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur<T, N> operator >> ( const Vecteur<T,N>& dir ) const
   ///
   /// Surcharge de l'operateur de projection d'un vecteur sur un autre.
   ///
   /// @param[in] dir : La direction sur laquelle projeter.
   ///
   /// @return La projection du vecteur sur l'autre.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur<T, N> operator >> ( const Vecteur<T,N>& dir ) const
   {
      T k = produitScalaire(*this, dir) / produitScalaire(dir, dir);
      Vecteur<T, N> r ( dir );
      r *= k;
      return r;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline friend T produitScalaire ( const Vecteur<T, N>& u, const Vecteur<T, N>& v )
   ///
   /// Cette fonction calcule le produit scalaire entre deux vecteurs.
   ///
   /// @param[in] u : Le premier vecteur du produit scalaire.
   /// @param[in] v : Le second vecteur du produit scalaire.
   ///
   /// @return Le produit scalaire des deux vecteurs.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline friend T produitScalaire ( const Vecteur<T, N>& u, const Vecteur<T, N>& v )
   {
      T r = 0;
      for ( int i = 0; i < N; i++ ) {
         r += u.vect[i] * v.vect[i];
      }
      return r;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline friend Vecteur<T, N> calculerReflexion( const Vecteur<T, N>& u, const Vecteur<T, N>& n )
   ///
   /// Cette fonction calcule la reflexion du vecteur @a u par rapport a
   /// l'espace vectoriel orthogonal a @a n (@a n doit etre normalise).
   ///
   /// @param[in] u : Le vecteur a reflechir.
   /// @param[in] n : La normale par rapport a laquelle faire la reflexion.
   ///
   /// @return Le vecteur reflechi.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline friend Vecteur<T, N> calculerReflexion(
      const Vecteur<T, N>& u, const Vecteur<T, N>& n
      )
   {
      return u - n * ( 2 * produitScalaire ( u, n ) );
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline friend Vecteur<T, N> calculerProjectionPlan(const Vecteur<T, N>& u, const Vecteur<T, N>& n)
   ///
   /// Cette fonction calcule la projection du vecteur @a u sur l'espace
   /// vectoriel orthogonal a @a n (@a n doit etre normalise).
   ///
   /// @param[in] u : Le vecteur a projeter.
   /// @param[in] n : La normale par rapport a laquelle faire la projection.
   ///
   /// @return Le vecteur projete.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline friend Vecteur<T, N> calculerProjectionPlan(
      const Vecteur<T, N>& u, const Vecteur<T, N>& n
      )
   {
      return u - n * ( produitScalaire ( u, n ) );
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline friend Vecteur<T, N> calculerProjectionDroite(const Vecteur<T, N>& u, const Vecteur<T, N>& dir)
   ///
   /// Cette fonction calcule la projection du vecteur @a u sur une droite de
   /// direction @a dir passant par l'origine.  Pour calculer la projection sur
   /// une droite ne passant pas par l'origine, calculer d'abord la difference.
   ///
   /// @param[in] u   : Le vecteur a projeter.
   /// @param[in] dir : La direction de la droite sur laquelle projeter.
   ///
   /// @return Le vecteur projete.
   ///
  ////////////////////////////////////////////////////////////////////////////
   inline friend Vecteur<T, N> calculerProjectionDroite(
      const Vecteur<T, N>& u, const Vecteur<T, N>& dir
      )
   {
      return dir * ( produitScalaire ( dir, u ) );
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline friend std::ostream& operator<< ( std::ostream& out, const Vecteur<T, N>& v )
   ///
   /// Surcharge de l'operateur d'extraction de flux de sortie pour
   /// l'affichage.
   ///
   /// @param[in] out : Le flux de sortie.
   /// @param[in] v   : Le vecteur a afficher.
   ///
   /// @return Le flux de sortie.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline friend std::ostream& operator<< (
      std::ostream& out, const Vecteur<T, N>& v
      )
   {
      for ( int i = 0; i < N; i++ ) {
         out << v[i];
         if ( i < N - 1 ) out << ' ';
      }
      return out;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline friend std::istream& operator>> ( std::istream& in, Vecteur<T, N>& v )
   ///
   /// Surcharge de l'operateur d'extraction de flux d'entree.
   ///
   /// @param[in] in : Le flux d'entree.
   /// @param[in] v  : Le vecteur lu.
   ///
   /// @return Le flux d'entree.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline friend std::istream& operator>> (
      std::istream& in, Vecteur<T, N>& v
 )
   {
      for ( int a = 0; a < N; a++ ) {
         in >> v[a];
      }
      return in;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline friend CEcritureFichierBinaire& operator< ( CEcritureFichierBinaire& out, const Vecteur<T, N>& r )
   ///
   /// Surcharge de l'operateur de sortie dans un fichier binaire.
   ///
   /// @param[in] out : Le fichier binaire de sortie.
   /// @param[in] r   : Le vecteur a ecrire.
   ///
   /// @return Le fichier binaire de sortie.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline friend CEcritureFichierBinaire& operator< (
      CEcritureFichierBinaire& out, const Vecteur<T, N>& r
      )
   {
      for ( int a = 0; a < N; a++ ) {
         out < r[a];
      }
      return out;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline friend CLectureFichierBinaire& operator> (CLectureFichierBinaire& in, Vecteur<T, N>& r)
   ///
   /// Surcharge de l'operateur de lecture dans un fichier binaire.
   ///
   /// @param[in] in : Le fichier binaire d'entree.
   /// @param[in] r  : Le vecteur a lire.
   ///
   /// @return Le fichier binaire d'entree.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline friend CLectureFichierBinaire& operator> (
      CLectureFichierBinaire& in, Vecteur<T, N>& r
      )
   {
      for ( int a = 0; a < N; a++ ) {
         in > r[a];
      }
      return in;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur<T, N> operator- () const
   ///
   /// Surcharge de l'operateur unaire de negation.
   ///
   /// @return L'oppose du vecteur.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur<T, N> operator- () const
   {
      Vecteur<T, N> r;
      for ( int i = 0; i < N; i++ ) {
         r[i] = - ( *this ) [i];
      }
      return r;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn template <const int N2> inline Vecteur<T, N2> convertir() const
   ///
   /// Cette fonction convertit entre les vecteurs de differentes dimensions.
   ///
   /// @return Le vecteur converti.
   ///
   ////////////////////////////////////////////////////////////////////////////
   template <const int N2>
   inline Vecteur<T, N2> convertir() const
   {
      return convertir<T, N2>();
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn template <class T2, const int N2> inline Vecteur<T2, N2> convertir() const
   ///
   /// Cette fonction convertit entre les vecteurs de differentes dimensions
   /// et de differents types.
   ///
   /// @return Le vecteur converti.
   ///
   ////////////////////////////////////////////////////////////////////////////
   template <class T2, const int N2>
   inline Vecteur<T2, N2> convertir() const
   {
      Vecteur<T2, N2> nouveauVecteur;
      if (N2 <= N) {
         for (int i = 0 ; i < N2; ++i)
            nouveauVecteur[i] = static_cast<T2>(vect[i]);
      }
      else {
         int i;
         for (i = 0; i < N; ++i)
            nouveauVecteur[i] = static_cast<T2>(vect[i]);
         for (i = N; i < N2; ++i)
            nouveauVecteur[i] = 0;
      }

      return nouveauVecteur;
   }


protected:
   /// Le vecteur generique de dimension @a N.
   T vect[N];


};




///////////////////////////////////////////////////////////////////////////
/// @class Vecteur2D
///
///        Classe generique pour implanter des vecteurs en 2D.
///
///        Cette classe generique est definie pour les vecteurs de dimension 2.
///        Les operations necessaires sont definies, soient:
///        - le constructeur de la classe ;
///        - operateur = ;
///        - calcul de l'angle de rotation ;
///        - rotation du vecteur .
///
/// @author Alex Duru
/// @author Ionut Alexandrescu
/// @author Martin Bisson
/// @date 2006-02-23
///////////////////////////////////////////////////////////////////////////
template<class T>
class Vecteur2D: public Vecteur<T, 2>
{
public:
   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur2D( const Vecteur2D<T2>& u )
   ///
   /// Constructeur avec conversion.
   ///
   /// @param[in] u : Le vecteur a copier dans le nouveau vecteur.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   template<class T2>
   inline Vecteur2D( const Vecteur2D<T2>& u )
      : Vecteur<T, 2> ( u )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur2D( const T x = 0, const T y = 0 )
   ///
   /// Constructeur par parametres.
   ///
   /// @param[in] x : La coordonnee en @a x.
   /// @param[in] y : La coordonnee en @a y.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur2D( const T x = 0, const T y = 0 )
   {
      vect[0] = x;
      vect[1] = y;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur2D ( const Vecteur<T, 2>& v )
   ///
   /// Constructeur copie.
   ///
   /// @param[in] v : Le vecteur a copier dans le nouveau vecteur.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur2D ( const Vecteur<T, 2>& v )
      : Vecteur<T, 2> ( v )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur2D& operator= ( const Vecteur<T, 2>& v )
   ///
   /// Surcharge de l'operateur d'assignation.
   ///
   /// @param[in] v : Le vecteur a copier.
   ///
   /// @return La reference vers l'objet assigne afin de respecter la
   ///         semantique de l'operateur d'assignation C++.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const Vecteur2D& operator= ( const Vecteur<T, 2>& v )
   {
      Vecteur<T, 2>::operator= ( v );
      return *this;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline T angle() const
   ///
   /// Cette fonction calcule l'angle du vecteur par rapport a l'axe des X
   /// positifs dans le sens anti-horaire.
   ///
   /// @return L'angle du vecteur par rapport a l'axe des X dans le sens
   ///         anti-horaire.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline T angle() const
   {
      return atan2 ( vect[1], vect[0] );
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur2D tourner(const T angle) const
   ///
   /// Cette fonction retourne un nouveau vecteur ayant effectue une rotation
   /// d'un angle donne dans le sens anti-horaire.
   ///
   /// @param[in] angle : L'angle duquel faire tourner le vecteur.
   ///
   /// @return Le vecteur apres la rotation.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur2D tourner(const T angle) const
   {
      const T cosAngle = cos(angle);
      const T sinAngle = sin(angle);
      return Vecteur2D(
         vect[0] * cosAngle + vect[1] * -sinAngle,
         vect[0] * sinAngle + vect[1] * cosAngle
         );
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur2D tournerPiSur2() const
   ///
   /// Cette fonction retourne un nouveau vecteur ayant effectue une rotation
   /// d'un angle de Pi sur 2 dans le sens anti-horaire.
   ///
   /// @return Le vecteur apres la rotation.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur2D tournerPiSur2() const
   {
      return Vecteur2D(-(*this)[1], (*this)[0]);
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur2D tournerMoinsPiSur2() const
   ///
   /// Cette fonction retourne un nouveau vecteur ayant effectue une rotation
   /// d'un angle de Pi sur 2 dans le sens horaire.
   ///
   /// @return Le vecteur apres la rotation.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur2D tournerMoinsPiSur2() const
   {
      return Vecteur2D((*this)[1], -(*this)[0]);
   }


};




///////////////////////////////////////////////////////////////////////////
/// @class Vecteur3D
///
///        Classe generique pour implanter des vecteurs en 3D.
///
///        Cette classe generique est definie pour les vecteurs de dimension 3.
///        Les operations necessaires sont definies, soient:
///        - les constructeurs ;
///        - operateur = ;
///        - calcul de l'angle de rotation ;
///        - calcul de l'angle de elevation ;
///        - transformation du vecteur en coordonees spheriques ;
///        - le produit vectoriel.
///
/// @author Alex Duru
/// @author Ionut Alexandrescu
/// @author Martin Bisson
/// @date 2006-02-23
///////////////////////////////////////////////////////////////////////////
template<class T>
class Vecteur3D: public Vecteur<T, 3>
{
public:
   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur3D ( const Vecteur3D<T2>& u )
   ///
   /// Constructeur avec conversion.
   ///
   /// @param[in] u : Le vecteur a copier dans le nouveau vecteur.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   template<class T2>
   inline Vecteur3D ( const Vecteur3D<T2>& u )
      : Vecteur<T, 3> ( u )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur3D ( const T x = 0, const T y = 0, const T z = 0 )
   ///
   /// Constructeur par parametres.
   ///
   /// @param[in] x : La coordonnee en @a x.
   /// @param[in] y : La coordonnee en @a y.
   /// @param[in] z : La coordonnee en @a z.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur3D ( const T x = 0, const T y = 0, const T z = 0 )
   {
      vect[0] = x;
      vect[1] = y;
      vect[2] = z;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur3D ( const Vecteur<T, 3>& v1, const Vecteur<T, 3>& v2 )
   ///
   /// Constructeur a partir de deux points.  Le vecteur construit est dirige
   /// du premier vers le second.
   ///
   /// @param[in] v1 : Le premier vecteur (source).
   /// @param[in] v2 : Le second vecteur (destination).
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur3D ( const Vecteur<T, 3>& v1, const Vecteur<T, 3>& v2 )
      : Vecteur<T, 3> ( v2 - v1 )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur3D ( const Vecteur<T, 3>& v )
   ///
   /// Constructeur copie.
   ///
   /// @param[in] v : Le vecteur a copier dans le nouveau vecteur.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur3D ( const Vecteur<T, 3>& v )
      : Vecteur<T, 3> ( v )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur3D& operator= ( const Vecteur<T, 3>& v )
   ///
   /// Surcharge de l'operateur d'assignation.
   ///
   /// @param[in] v : Le vecteur a copier.
   ///
   /// @return La reference vers l'objet assigne afin de respecter la
   ///         semantique de l'operateur d'assignation C++.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const Vecteur3D& operator= ( const Vecteur<T, 3>& v )
   {
      Vecteur<T, 3>::operator= ( v );
      return *this;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline T lireTheta() const
   ///
   /// Cette fonction calcule l'angle de rotation (@a xy) du vecteur 3D.
   ///
   /// @return L'angle de rotation du vecteur 3D.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline T lireTheta() const
   {
      Vecteur2D<T> xy ( vect[0], vect[1] );
      return xy.angle();
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline T lirePhi() const
   ///
   /// Cette fonction calcule l'angle d'elevation du vecteur 3D.  Le vecteur
   /// dirige vers l'axe des Z positifs, k, (0,0,1), aura comme angle 0.
   ///
   /// @return L'angle d'elevation du vecteur 3D.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline T lirePhi() const
   {
      Vecteur2D<T> xy ( vect[0], vect[1] );
      Vecteur2D<T> zr ( vect[2], xy.norme() );
      return zr.angle();
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void lireCoordSpheriques ( T& r, T& phi, T& theta ) const
   ///
   /// Cette fonction retourne les coordonnees spheriques du vecteur via les
   /// parametres passes en reference.
   ///
   /// @param[out] r     : Le rayon des coordonnees spheriques.
   /// @param[out] phi   : L'angle d'elevation des coordonnees spheriques.
   /// @param[out] theta : L'angle de rotation des coordonnees spheriques.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline void lireCoordSpheriques ( T& r, T& phi, T& theta ) const
   {
      r     = norme();
      theta = lireTheta();
      phi   = lirePhi();
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline void assignerCoordSpheriques ( const T r, const T phi, const T theta )
   ///
   /// Cette fonction assigne les coordonnees du vecteur qui sont donnees en
   /// coordonnees spheriques.
   ///
   /// @param[in] r     : Le rayon des coordonnees spheriques.
   /// @param[in] phi   : L'angle d'elevation des coordonnees spheriques.
   /// @param[in] theta : L'angle de rotation des coordonnees spheriques.
   ///
   /// @return Aucune.
   ///
   ///////////////////////////////////////////////////////////////////////////////
   inline void assignerCoordSpheriques ( const T r, const T phi, const T theta )
   {
      // Calcul de la position a partir des coordonnees spheriques
      vect[0] = r * sin(phi) * cos(theta);
      vect[1] = r * sin(phi) * sin(theta);
      vect[2] = r * cos(phi);
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline friend Vecteur3D produitVectoriel ( const Vecteur3D& A, const Vecteur3D& B )
   ///
   /// Cette fonction calcule le produit vectoriel des deux vecteurs.
   ///
   /// @param[in] A : Le premier vecteur du produit.
   /// @param[in] B : Le second vecteur du produit.
   ///
   /// @return Le produit vectoriel des deux vecteurs.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline friend Vecteur3D produitVectoriel (
      const Vecteur3D& A, const Vecteur3D& B
      )
   {
      return Vecteur3D(
         A[1] * B[2] - A[2] * B[1],
         A[2] * B[0] - A[0] * B[2],
         A[0] * B[1] - A[1] * B[0]
      );
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur3D tourner(const T angle, const Vecteur3D& axe) const
   ///
   /// Cette fonction calcule la rotation d'un vecteur autour d'un axe
   /// arbitraire.
   ///
   /// @param[in] angle : L'angle de rotation, en radians.
   /// @param[in] axe   : L'axe de rotation (vecteur unitaire).
   ///
   /// @return Le vecteur apres la rotation.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur3D tourner(const T angle, const Vecteur3D& axe) const
   {
      const T cosAngle = cos(angle);
      const T sinAngle = sin(angle);
      const T unMoinsCosAngle = 1 - cosAngle;

      return Vecteur3D(
         // Calcul de la composante X
         (cosAngle + unMoinsCosAngle * axe[0] * axe[0])          * vect[0] +
         (unMoinsCosAngle * axe[0] * axe[1] - axe[2] * sinAngle) * vect[1] +
         (unMoinsCosAngle * axe[0] * axe[2] + axe[1] * sinAngle) * vect[2],
         // Calcul de la composante Y
         (unMoinsCosAngle * axe[0] * axe[1] + axe[2] * sinAngle) * vect[0] +
         (cosAngle + unMoinsCosAngle * axe[1] * axe[1])          * vect[1] +
         (unMoinsCosAngle * axe[1] * axe[2] - axe[0] * sinAngle) * vect[2],
         // Calcul de la composante Z
         (unMoinsCosAngle * axe[0] * axe[2] - axe[1] * sinAngle) * vect[0] +
         (unMoinsCosAngle * axe[1] * axe[2] + axe[0] * sinAngle) * vect[1] +
         (cosAngle + unMoinsCosAngle * axe[2] * axe[2])          * vect[2]
      );
   }


};




///////////////////////////////////////////////////////////////////////////
/// @class Vecteur4D
///
///        Classe generique pour implanter des vecteurs en 4D.
///
///        Cette classe generique est definie pour les vecteurs de dimension 4.
///        Les operations necessaires sont definies, soient:
///        - les constucteurs
///        - operateur d'egalite
///
/// @author Alex Duru
/// @author Ionut Alexandrescu
/// @date 2006-02-23
///////////////////////////////////////////////////////////////////////////
template<class T>
class Vecteur4D: public Vecteur<T, 4>
{
public:
   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur4D ( const Vecteur4D<T2>& u )
   ///
   /// Constructeur avec conversion.
   ///
   /// @param[in] u : Le vecteur a copier dans le nouveau vecteur.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   template<class T2>
   inline Vecteur4D ( const Vecteur4D<T2>& u )
      : Vecteur<T, 4> ( u )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur4D ( const T x = 0, const T y = 0, const T z = 0, const T w = 0 )
   ///
   /// Constructeur par parametres.
   ///
   /// @param[in] x : La coordonnee en @a x.
   /// @param[in] y : La coordonnee en @a y.
   /// @param[in] z : La coordonnee en @a z.
   /// @param[in] w : La coordonnee en @a w.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur4D ( const T x = 0, const T y = 0, const T z = 0, const T w = 0 )
   {
      vect[0] = x;
      vect[1] = y;
      vect[2] = z;
      vect[3] = w;
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline Vecteur4D ( const Vecteur<T, 4>& v )
   ///
   /// Constructeur copie.
   ///
   /// @param[in] v : Le vecteur a copier dans le nouveau vecteur.
   ///
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline Vecteur4D ( const Vecteur<T, 4>& v )
      : Vecteur<T, 4> ( v )
   {
   }


   ////////////////////////////////////////////////////////////////////////////
   ///
   /// @fn inline const Vecteur4D& operator= ( const Vecteur<T, 4>& v )
   ///
   /// Surcharge de l'operateur d'assignation.
   ///
   /// @param[in] v : Le vecteur a copier.
   ///
   /// @return La reference vers l'objet assigne afin de respecter la
   ///         semantique de l'operateur d'assignation C++.
   ///
   ////////////////////////////////////////////////////////////////////////////
   inline const Vecteur4D& operator= ( const Vecteur<T, 4>& v )
   {
      Vecteur<T, 4>::operator= ( v );
      return *this;
   }


};




/// Definition de type de vecteur a 2 coordonnees de type double.
typedef Vecteur2D<double> Vecteur2;
/// Definition de type de vecteur a 3 coordonnees de type double.
typedef Vecteur3D<double> Vecteur3;
/// Definition de type de vecteur a 4 coordonnees de type double.
typedef Vecteur4D<double> Vecteur4;

/// Definition de type de vecteur a 2 coordonnees de type float.
typedef Vecteur2D<float> Vecteur2f;
/// Definition de type de vecteur a 3 coordonnees de type float.
typedef Vecteur3D<float> Vecteur3f;
/// Definition de type de vecteur a 4 coordonnees de type float.
typedef Vecteur4D<float> Vecteur4f;

/// Definition de type de vecteur a 2 coordonnees de type int.
typedef Vecteur2D<int> Vecteur2i;
/// Definition de type de vecteur a 3 coordonnees de type int.
typedef Vecteur3D<int> Vecteur3i;
/// Definition de type de vecteur a 4 coordonnees de type int.
typedef Vecteur4D<int> Vecteur4i;


#endif // __UTILITAIRE_VECTEUR_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
