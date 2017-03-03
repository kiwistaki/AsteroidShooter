////////////////////////////////////////////////////////////////////////////////////
/// @file VueOrtho.cpp
/// @author DGI
/// @date 2006-12-16
/// @version 1.0
///
/// @addtogroup utilitaire Utilitaire
/// @{
////////////////////////////////////////////////////////////////////////////////////

#include "Utilitaire.h"
#include "VueOrtho.h"

namespace vue {


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn VueOrtho::VueOrtho(const Camera& camera, int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture, double zAvant, double zArriere, double zoomInMax, double zoomOutMax, double incrementZoom, double xMinFenetre, double xMaxFenetre, double yMinFenetre, double yMaxFenetre)
   ///
   /// Constructeur d'une vue orthogonale.  Ne fait que creer les objets
   /// Projection et Camera correspondant.
   ///
   /// @param[in] camera        : Camera a utiliser au depart pour cette vue.
   /// @param[in] xMinCloture   : coordonnee minimale en @a x de la clôture.
   /// @param[in] xMaxCloture   : coordonnee maximale en @a x de la clôture.
   /// @param[in] yMinCloture   : coordonnee minimale en @a y de la clôture.
   /// @param[in] yMaxCloture   : coordonnee maximale en @a y de la clôture.
   /// @param[in] zAvant        : distance du plan avant (en @a z).
   /// @param[in] zArriere      : distance du plan arriere (en @a z).
   /// @param[in] zoomInMax     : facteur de zoom in maximal.
   /// @param[in] zoomOutMax    : facteur de zoom out maximal.
   /// @param[in] incrementZoom : distance du plan arriere (en @a z).
   /// @param[in] xMinFenetre   : coordonnee minimale en @a x de la fenetre
   ///                            virtuelle.
   /// @param[in] xMaxFenetre   : coordonnee maximale en @a x de la fenetre
   ///                            virtuelle.
   /// @param[in] yMinFenetre   : coordonnee minimale en @a y de la fenetre
   ///                            virtuelle.
   /// @param[in] yMaxFenetre   : coordonnee maximale en @a y de la fenetre
   ///                            virtuelle.
   /// 
   /// @return Aucune (constructeur).
   ///
   ////////////////////////////////////////////////////////////////////////
   VueOrtho::VueOrtho(const Camera& camera,
                      int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture,
                      double zAvant,  double zArriere,
                      double zoomInMax, double zoomOutMax,
                      double incrementZoom,
                      double xMinFenetre, double xMaxFenetre,
                      double yMinFenetre, double yMaxFenetre) :
      Vue(camera),
      projection_(xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
                  zAvant, zArriere, zoomInMax, zoomOutMax,
                  incrementZoom,
                  xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre)
   {
   }

	 /// Obtenir les coins maximum des coins
	void VueOrtho::obtenirCoinsMax(int& coinMaxX, int& coinMaxY) const
	{
		coinMaxX = projection_.obtenirDimensionCloture()[0];
		coinMaxY = projection_.obtenirDimensionCloture()[1];
	}

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn const ProjectionOrtho& VueOrtho::obtenirProjection() const
   ///
   /// Retourne la projection orthogonale associee a cette vue.
   ///
   /// @return La projection orthogonale associee a cette vue.
   ///
   ////////////////////////////////////////////////////////////////////////
   const ProjectionOrtho& VueOrtho::obtenirProjection() const
   {
      return projection_;
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::appliquerProjection() const
   ///
   /// Applique la matrice de projection correspondant a cette vue.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::appliquerProjection(bool direct) const
   {
	  if (!direct) {
		projection_.mettreAJourProjection();
	  } else {
		  projection_.appliquer();
	  }
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::appliquerCamera() const
   ///
   /// Applique la matrice correspondant a cette vue selon la position de
   /// la camera (eventuellement un gluLookAt()).
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::appliquerCamera() const
   {
      camera_.positionner();
   }

   math::Plan3D VueOrtho::getPlanAvant() const {
	   Vecteur3 normale(0.0, 0.0, -1.0);
	   Vecteur3 point = camera_.getPosition() + normale * projection_.getZAvant();
	   return math::Plan3D(normale, point);
   }

   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::redimensionnerFenetre( const Vecteur2i& coinMin, const Vecteur2i& coinMax )
   ///
   /// Permet d'ajuster les coordonnees de la fenetre virtuelle en fonction
   /// d'un redimensionnement de la fenetre.
   ///
   /// @param[in]  coinMin : Coin contenant les coordonnees minimales de la
   ///                       nouvelle clôture.
   /// @param[in]  coinMax : Coin contenant les coordonnees maximales de la
   ///                       nouvelle clôture.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::redimensionnerFenetre( const Vecteur2i& coinMin,
                                         const Vecteur2i& coinMax )
   {
      projection_.redimensionnerFenetre(coinMin, coinMax);
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::zoomerIn()
   ///
   /// Permet de faire un zoom in selon l'increment de zoom.
   /// 
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::zoomerIn()
   {
      projection_.zoomerIn();
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::zoomerOut()
   ///
   /// Permet de faire un zoom out selon l'increment de zoom.
   /// 
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::zoomerOut()
   {
      projection_.zoomerOut();
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::zoomerInElastique(const Vecteur2i& coin1, const Vecteur2i& coin2)
   ///
   /// Permet de faire un zoom in elastique.
   /// 
   /// @param[in]  coin1 : Coin contenant les coordonnees du premier coin du
   ///                     rectangle.
   /// @param[in]  coin2 : Coin contenant les coordonnees du second coin du
   ///                     rectangle.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::zoomerInElastique(const Vecteur2i& coin1,
                                    const Vecteur2i& coin2)
   {
      projection_.zoomerIn(coin1, coin2);
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::zoomerOutElastique(const Vecteur2i& coin1, const Vecteur2i& coin2)
   ///
   /// Permet de faire un zoom out elastique.
   /// 
   /// @param[in]  coin1 : Coin contenant les coordonnees du premier coin du
   ///                     rectangle.
   /// @param[in]  coin2 : Coin contenant les coordonnees du second coin du
   ///                     rectangle.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::zoomerOutElastique(const Vecteur2i& coin1,
                                     const Vecteur2i& coin2)
   {
      projection_.zoomerOut(coin1, coin2);
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::deplacerXY(double deplacementX, double deplacementY)
   ///
   /// @param[in]  deplacementX : Deplacement en pourcentage de la largeur.
   /// @param[in]  deplacementY : Deplacement en pourcentage de la hauteur.
   ///
   /// Permet de faire un "pan" d'un certain pourcentage.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::deplacerXY(double deplacementX, double deplacementY)
   {
      projection_.translater(deplacementX, deplacementY);

	  Vecteur4 dimensions = projection_.getDimensionsFenetre();
	  double largeurFenetre( dimensions[1]-dimensions[0] );
	  //camera_.deplacerXY(largeurFenetre * deplacementX / 2.0f, largeurFenetre * deplacementY / 2.0f);
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::deplacerXY(const Vecteur2i& deplacement)
   ///
   /// Permet de faire un "pan" equivalent a la distance du deplacement
   /// specifie en coordonnees de clôture.
   ///
   /// @param[in]  deplacement : Deplacement en coordonnees de clôture
   ///                           (pixels).
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::deplacerXY(const Vecteur2i& deplacement)
   {
      projection_.translater(deplacement);

	  Vecteur4 dimensions = projection_.getDimensionsFenetre();
	  double largeurFenetre( dimensions[1]-dimensions[0] );
	  //camera_.deplacerXY(largeurFenetre * (double)deplacement[0] / 2.0f, largeurFenetre * (double)deplacement[1] / 2.0f);
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::deplacerZ(double deplacement)
   ///
   /// Ne fait rien, car se deplacer dans l'axe de la profondeur n'a pas
   /// vraiment de signification avec une vue orthogonale.
   ///
   /// @param[in]  deplacement : Deplacement selon l'axe Z.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::deplacerZ(double deplacement)
   {

   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::rotaterXY(double rotationX, double rotationY)
   ///
   /// Permet de faire une rotation de la camera autour du point vers
   /// lequel elle regarde en modifiant l'angle de rotation et l'angle
   /// d'elevation.
   ///
   /// Une rotation de 100% correspondant a 360 degres en X (angle de
   /// rotation) ou 180 degres en Y (angle d'elevation).
   ///
   /// @param[in]  rotationX : Rotation en pourcentage de la largeur.
   /// @param[in]  rotationY : Rotation en pourcentage de la hauteur.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::rotaterXY(double rotationX, double rotationY)
   {
      camera_.orbiterXY(rotationX * 360, rotationY * 180);
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::rotaterXY(const Vecteur2i& rotation)
   ///
   /// Permet de faire une rotation de la camera autour du point vers
   /// lequel elle regarde en modifiant l'angle de rotation et l'angle
   /// d'elevation.
   ///
   /// Un deplacement de la taille de la fenetre correspond a 100%.
   ///
   /// @param[in]  rotation : Rotation en coordonnees de clotûre (pixels).
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::rotaterXY(const Vecteur2i& rotation)
   {
      const Vecteur2i dimensions = projection_.obtenirDimensionCloture();
      rotaterXY(rotation[0] / (double) dimensions[0],
                rotation[1] / (double) dimensions[1]);
   }


   ////////////////////////////////////////////////////////////////////////
   ///
   /// @fn void VueOrtho::rotaterZ(double rotation)
   ///
   /// Ne fait rien, car tourner autour de l'axe de la profondeur
   /// correspondrait a un rouli et n'est pas souhaitable pour cette vue.
   ///
   /// @param[in]  rotation : Rotation selon l'axe Z.
   ///
   /// @return Aucune.
   ///
   ////////////////////////////////////////////////////////////////////////
   void VueOrtho::rotaterZ(double rotation)
   {
   }


}; // Fin du namespace vue.


///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
