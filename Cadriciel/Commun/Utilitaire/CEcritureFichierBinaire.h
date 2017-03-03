////////////////////////////////////////////////////////////////////////////////////
/// @file CEcritureFichierBinaire.h
/// @author DGI
/// @date 2005-10-15
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_CECRITUREFICHIERBINAIRE_H__
#define __UTILITAIRE_CECRITUREFICHIERBINAIRE_H__


#include <iostream>
#include <fstream>


///////////////////////////////////////////////////////////////////////////
/// @class CEcritureFichierBinaire
/// @brief Cette classe contient des methodes < permettant d'ecrire
///        dans un fichier binaire des variables string, double,
///        float, int, unsigned int, char, bool.
///
/// @author DGI-2990
/// @date 2005-10-15
///////////////////////////////////////////////////////////////////////////
class CEcritureFichierBinaire: public std::ofstream
{
public:
   /// Constructeur par defaut.
   CEcritureFichierBinaire();
   /// Constructeur par parametre.
   CEcritureFichierBinaire(
      const char* nomFichier, openmode mode = std::ios::out | std::ios::binary
      );

   /// Surcharge de l'operateur pour le type @em std::string.
   friend CEcritureFichierBinaire& operator< ( CEcritureFichierBinaire& out, const std::string& s );
   /// Surcharge de l'operateur pour le type @em double.
   friend CEcritureFichierBinaire& operator< ( CEcritureFichierBinaire& out, const double& x );
   /// Surcharge de l'operateur pour le type @em float.
   friend CEcritureFichierBinaire& operator< ( CEcritureFichierBinaire& out, const float& x );
   /// Surcharge de l'operateur pour le type @em int.
   friend CEcritureFichierBinaire& operator< ( CEcritureFichierBinaire& out, const int& x );
   /// Surcharge de l'operateur pour le type @em unsigned @em int.
   friend CEcritureFichierBinaire& operator< ( CEcritureFichierBinaire& out, const unsigned int& x );
   /// Surcharge de l'operateur pour le type @em char.
   friend CEcritureFichierBinaire& operator< ( CEcritureFichierBinaire& out, const char& x );
   /// Surcharge de l'operateur pour le type @em bool.
   friend CEcritureFichierBinaire& operator< ( CEcritureFichierBinaire& out, const bool& x );

   /// Fonction pour inserer des caracteres vides dans le fichier.
   void null(int n);

};


#endif // __UTILITAIRE_CECRITUREFICHIERBINAIRE_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
