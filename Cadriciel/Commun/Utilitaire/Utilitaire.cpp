///////////////////////////////////////////////////////////////////////////////
/// @file Utilitaire.cpp
/// @author DGI
/// @date 2005-06-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "Utilitaire.h"

#include <windows.h>
#include <iostream>


namespace utilitaire {


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void afficherErreur(const std::string& message)
	///
	/// Cette fonction affiche une message d'erreur.
	///
	/// @param[in] message : La chaîne decrivant l'erreur.
	///
	/// @return Aucune
	///
	////////////////////////////////////////////////////////////////////////
	void afficherErreur(const std::string& message)
	{
		#ifdef WIN32
				MessageBoxA(0, message.c_str(), "Erreur", MB_OK | MB_ICONERROR);
		#else
				std::cerr << message << std::endl;
		#endif
	}

	void afficherInformations(const std::string& message)
	{
		#ifdef WIN32
				MessageBoxA(0, message.c_str(), "Informations", MB_OK | MB_ICONINFORMATION);
		#else
				std::cout << message << std::endl;
		#endif
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool EGAL_ZERO(double nombre)
	///
	/// Fonction pour savoir si un double est egal a zero.
	///
	/// @param[in] nombre : Valeur a verifier.
	///
	/// @return true si nombre est egal a 0, false autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool EGAL_ZERO(double nombre)
	{
		return (nombre < EPSILON) && (-nombre < EPSILON);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double RAD_TO_DEG(double angleRad)
	///
	/// Cette fonction convertit les angles de radians en degres.
	///
	/// @param[in] angleRad : L'angle en radians a convertir.
	///
	/// @return L'angle converti en degres
	///
	////////////////////////////////////////////////////////////////////////
	double RAD_TO_DEG(double angleRad) 
	{
		return angleRad * 57.2957795130823208767981548141052;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double DEG_TO_RAD(double angleDeg)
	///
	/// Cette fonction convertit les angles de degres en radians.
	///
	/// @param[in] angleDeg : L'angle en degres a convertir.
	///
	/// @return L'angle converti en radians.
	///
	////////////////////////////////////////////////////////////////////////
	double DEG_TO_RAD(double angleDeg)
	{
		return angleDeg * 0.0174532925199432957692369076848861;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn float KMH_TO_MS( float kmh )
	///
	/// Fonction de conversion des km/h en m/s.
	///
	/// @param[in] kmh : Valeur en kilometres / heure.
	///
	/// @return float => vitesse en metres par seconde.
	///
	////////////////////////////////////////////////////////////////////////
	float KMH_TO_MS( float kmh )
	{
		return (kmh * 1000.0f / 3600.0f);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn float MS_TO_KMH( float ms )
	///
	/// Fonction de conversion des m/s en km/h.
	///
	/// @param[in] ms : Valeur en metres / seconde.
	///
	/// @return float => vitesse en kilometres / heure.
	///
	////////////////////////////////////////////////////////////////////////
	float MS_TO_KMH( float ms )
	{
		return (ms * 3.6f);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn int SIGN( float nombre )
	///
	/// Fonction pour connaître le signe d'un nombre.
	///
	/// @param[in] nombre : Valeur dont on veut trouver le signe.
	///
	/// @return int => 1 si positif, -1 si negatif, 0 si = 0.
	///
	////////////////////////////////////////////////////////////////////////
	float SIGN( float nombre )
	{
		if (nombre == 0.0f) {
			return 0.0f;
		}
		else if (nombre > 0.0f) {
			return  1.0f;
		}
		else {
			return -1.0f;
		}
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn float ABS( float nombre )
	///
	/// Fonction qui retourne la valeur absolue.
	///
	/// @param[in] nombre : Valeur dont on veut trouver la valeur absolue.
	///
	/// @return float => la valeur absolue du nombre.
	///
	////////////////////////////////////////////////////////////////////////
	float ABS( float nombre )
	{
		return (SIGN(nombre) * nombre);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool DANS_INTERVALLE( double valeur, double borneMin, double borneMax ) 
	///
	/// Cette fonction verifie si une valeur est dans un intervalle.
	///
	/// @param[in] valeur   : La valeur a verifier.
	/// @param[in] borneMin : La borne inferieure de l'intervalle.
	/// @param[in] borneMax : La borne superieure de l'intervalle.
	///
	/// @return Vrai si la valeur est dans l'intervalle, faux autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool DANS_INTERVALLE( double valeur, double borneMin, double borneMax ) 
	{
		return (valeur >= borneMin) && (valeur <= borneMax);
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool DANS_LIMITESXY( double x, double xMin, double xMax, double y, double yMin, double yMax )
	///
	/// Cette fonction verifie si un point 2d est dans un carre.
	///
	/// @param[in] x    : Coordonnee x du point.
	/// @param[in] xMin : La borne inferieure en x.
	/// @param[in] xMax : La borne superieure en x.
	/// @param[in] y    : Coordonnee y du point.
	/// @param[in] yMin : La borne inferieure en y.
	/// @param[in] yMax : La borne superieure en y.
	///
	/// @return Vrai si le point (x,y) est dans le carre, faux autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool DANS_LIMITESXY( double x, double xMin, double xMax,
		double y, double yMin, double yMax ) 
	{
		return (DANS_INTERVALLE( x, xMin, xMax ) && DANS_INTERVALLE( y, yMin, yMax ));
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn double CUtilitaire::ecrasement( double a, double b )
	///
	/// Cette fonction calcule le rapport d'ecrasement pour un rectangle de
	/// longueur @a a et largeur @a b.
	///   - si a = b, le rapport est 1
	///   - le rapport est toujours positif et plus grand que 1.
	///
	/// @param[in] a : Valeur a rapprocher.
	/// @param[in] b : Point limite du rapprochement.
	///
	/// @return Le rapport @a r  de @a a /  @a b
	///
	////////////////////////////////////////////////////////////////////////
	double ecrasement( double a, double b )
	{
		double r = a / b;
		// Le rapport doit etre toujours positif.
		if (r < 1.0)
			r = 1.0 / r;

		return r;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn bool fichierExiste( const std::string &nomDuFichier )
	///
	/// Cette fonction verifie si un fichier d'un certain nom donne existe.
	///
	/// @param [in] nomDuFichier : Le nom du fichier dont on veut verifier
	///                            l'existence.
	///
	/// @return Vrai si le fichier existe, faux autrement.
	///
	////////////////////////////////////////////////////////////////////////
	bool fichierExiste( const std::string& nomDuFichier )
	{
		std::ifstream ficin;
		ficin.open( nomDuFichier.c_str() );
		bool fail = ficin.fail();
		if ( !fail ) ficin.close();
		return !fail;
	}


	////////////////////////////////////////////////////////////////////////
	///
	/// @fn void appliquerMatrice( const Vecteur3& point, const double mat[])
	///
	/// Cette fonction multiplie le point par une matrice de transformation
	/// donnee et retourne le resultat.
	///
	/// @param [in] point : Le point a transformer.
	/// @param [in] mat   : La matrice de transformation.
	///
	/// @return Le point transforme.
	///
	////////////////////////////////////////////////////////////////////////
	Vecteur3 appliquerMatrice( const Vecteur3& point, const double mat[] )
	{
		// Calculer la multiplication entre la matrice et le point.
		Vecteur3 pointTransforme(
			mat[0] * point[0] + mat[4] * point[1] + mat[ 8] * point[2] + mat[12],
			mat[1] * point[0] + mat[5] * point[1] + mat[ 9] * point[2] + mat[13],
			mat[2] * point[0] + mat[6] * point[1] + mat[10] * point[2] + mat[14]
		);
		const double w = mat[3] * point[0] + mat[7] * point[1] +
			mat[11] * point[2] + mat[15];

		// Retour des coordonnees homogenes vers la 3D.
		pointTransforme /= w;

		return pointTransforme;
	}


}; // Fin de l'espace de nom utilitaire.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
