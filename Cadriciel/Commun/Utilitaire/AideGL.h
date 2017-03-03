///////////////////////////////////////////////////////////////////////////////
/// @file AideGL.h
/// @brief Ce fichier contient la declaration de l'espace de nom aidegl.
///
/// Il contient les declarations de fonctions utiles pour effectuer certaines
/// taches OpenGL qui reviennent d'un projet a l'autre.
///
/// @author Martin Bisson
/// @date 2007-01-20
///
/// @addtogroup utilitaire Utilitaire
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __UTILITAIRE_AIDEGL_H__
#define __UTILITAIRE_AIDEGL_H__


#include <windows.h>
#include <GL/gl.h>
#include <string>

#include "Vecteur.h"


/// Espace de nom contenant des fonctions utiles pour effectuer certaines
/// taches OpenGL qui reviennent d'un projet a l'autre.
namespace aidegl {


   /// Cree un contexte OpenGL dans la fenetre donnee.
   bool creerContexteGL(HWND hwnd, HDC& hDC, HGLRC& hRC);
   /// Detruit un contexte OpenGL.
   bool detruireContexteGL(HWND hwnd, HDC hDC, HGLRC hRC);

   /// Initialise le mode de rendu du rectangle elastique.
   void initialiserRectangleElastique(
      const Vecteur2i& point,
      unsigned short   patron = 0x3333,
      int              facteur = 1
      );
   /// Met a jour le rectangle elastique (suite a un deplacement).
   void mettreAJourRectangleElastique(
      const Vecteur2i& pointAncrage,
      const Vecteur2i& pointAvant,
      const Vecteur2i& pointApres
      );
   /// Termine le mode de rendu du rectangle elastique.
   void terminerRectangleElastique(
      const Vecteur2i& pointAncrage,
      const Vecteur2i& pointFinal
      );


   /// Affiche un rectangle subdivise par un nombre de subdivision.
   void afficherRectangle(
      const Vecteur3& point1, const Vecteur3& point2,
      const Vecteur3& point3, const Vecteur3& point4,
      int divisionS, int divisionT
      );

   /// Affiche un rectangle subdivise d'un intervalle.
   void afficherRectangleIntervalle(
      const Vecteur3& point1, const Vecteur3& point2,
      const Vecteur3& point3, const Vecteur3& point4,
      double deltaS, double deltaT
      );


   /// Drapeau pour afficher le nom du code d'erreur.
   static const int AFFICHE_ERREUR_CODE           = (1 << 0);
   /// Drapeau pour afficher la chaîne de gluErrorString.
   static const int AFFICHE_ERREUR_GLUERRORSTRING = (1 << 1);
   /// Drapeau pour afficher la description du code d'erreur.
   static const int AFFICHE_ERREUR_DESCRIPTION    = (1 << 2);
   /// Drapeau pour afficher toutes les informations.
   static const int AFFICHE_ERREUR_TOUT           =
      AFFICHE_ERREUR_CODE           |
      AFFICHE_ERREUR_GLUERRORSTRING |
      AFFICHE_ERREUR_DESCRIPTION;
   /// Drapeau pour afficher meme s'il n'y a pas d'erreur.
   static const int AFFICHE_ERREUR_AUCUNE         = (1 << 3);

   /// Retourne une chaîne correspondant au code d'erreur OpenGL.
   std::string obtenirMessageErreur(
      GLenum codeErreur, int drapeau = AFFICHE_ERREUR_TOUT
      );

   /// Verifie s'il y a une erreur OpenGL.
   void verifierErreurOpenGL(int drapeau = AFFICHE_ERREUR_TOUT);


   /// Charge une texture OpenGL a partir d'un fichier image.
   bool glLoadTexture(const std::string& nomFichier, unsigned int& idTexture, bool genererTexture=true);

   /// Cree une texture a partir des pixels en memoire.
   void glCreateTexture(
      unsigned char* data, int x, int y, int bpp, int pitch, unsigned int& ID, bool genererTexture=true
      );


} // Fin de l'espace de nom aidegl


#endif // __UTILITAIRE_AIDEGL_H__


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
