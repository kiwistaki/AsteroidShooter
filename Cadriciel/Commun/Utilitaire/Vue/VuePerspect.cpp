#include "Utilitaire.h"
#include "VuePerspect.h"
#include <Windows.h>
#include <gl/GL.h>

const float MAXPHI = 80.0f, MINPHI = 10.0f, DISTMIN = 400.0f, DISTMAX = 6000.0f;

namespace vue{

	 VuePerspect::VuePerspect(const Camera& camera,
							  int xMinCloture, int xMaxCloture, int yMinCloture, int yMaxCloture,
							  double zAvant,  double zArriere,
							  double zoomInMax, double zoomOutMax,
							  double incrementZoom,
							  double xMinFenetre, double xMaxFenetre,
							  double yMinFenetre, double yMaxFenetre) :
							  Vue(camera),
							  projection_(xMinCloture, xMaxCloture, yMinCloture, yMaxCloture,
										  zAvant, zArriere, zoomInMax, zoomOutMax, incrementZoom,
										  xMinFenetre, xMaxFenetre, yMinFenetre, yMaxFenetre)
							 
   {
	   //theta_ = DEG2RAD(-90.0);
	   //phi_ = DEG2RAD(60.0);
	   //distance_ = 4500.0;

	   float x = (float) camera.obtenirPosition()[0];
	   float y = (float) camera.obtenirPosition()[1];
	   float z = (float) camera.obtenirPosition()[2];
	   
	   distance_ = sqrt( (x*x) + (y*y) + (z*z) );
	   theta_ = atan(y/x);
	   phi_ = acosf(z/distance_);
	  
	   camera_.positionnerOrbite(theta_, phi_, distance_);
	  
   }

	/// Obtenir les coins maximum des coins
	void VuePerspect::obtenirCoinsMax(int& coinMaxX, int& coinMaxY) const
	{
		coinMaxX = projection_.obtenirDimensionCloture()[0];
		coinMaxY = projection_.obtenirDimensionCloture()[1];
	}

	// Obtention de la projection
    const Projection& VuePerspect::obtenirProjection() const{
		return projection_;	
	}

    /// Application de la projection
    void VuePerspect::appliquerProjection(bool direct) const{
		if (!direct) {
			projection_.mettreAJourProjection();
		} else {
			projection_.appliquer();
		}
	}

   math::Plan3D VuePerspect::getPlanAvant() const {
	   Vecteur3 normale(camera_.obtenirPointVise() - camera_.obtenirPosition());
	   normale.normaliser();

	   Vecteur3 point = camera_.obtenirPointVise() + normale * projection_.getZAvant();

	   return math::Plan3D(normale, point);
   }

    /// Application de la camera
    void VuePerspect::appliquerCamera() const{
		camera_.positionner();
	}

    /// Modification de la clotûre
    void VuePerspect::redimensionnerFenetre( const Vecteur2i& coinMin, const Vecteur2i& coinMax ){

		Vecteur2i avant = projection_.obtenirDimensionCloture();
		
		projection_.redimensionnerFenetre(coinMin, coinMax);

		Vecteur2i apres = projection_.obtenirDimensionCloture();
		
		//Distance parcourue par le coins de l'écran
		float delta = ( sqrt( ((float) apres[0]*apres[0]) + ((float) apres[1]*apres[1])) -
						sqrt( ((float) avant[0]*avant[0]) + ((float) avant[1]*avant[1])) ) ;

		distance_ += delta;
				
	    camera_.positionnerOrbite(theta_, phi_, distance_);
	}

    /// Zoom in, c'est-a-dire un agrandissement.
    void VuePerspect::zoomerIn(){
		if(distance_ > DISTMIN)
			distance_ = distance_  - (float) projection_.getIncrementZoom();

		camera_.positionnerOrbite(theta_, phi_, distance_);
	}

    /// Zoom out, c'est-a-dire un rapetissement.
    void VuePerspect::zoomerOut(){		

		if(distance_ < DISTMAX)
			distance_ = distance_  + (float) projection_.getIncrementZoom();

		camera_.positionnerOrbite(theta_, phi_, distance_);

	}

    /// Zoom in elastique
    void VuePerspect::zoomerInElastique(const Vecteur2i& coin1, const Vecteur2i& coin2){
		//Goat?
	}

    /// Zoom out elastique
    void VuePerspect::zoomerOutElastique(const Vecteur2i& , const Vecteur2i&){
		//Goat?
	}

    /// Deplacement dans le plan XY par rapport a la vue
    void VuePerspect::deplacerXY(double deplacementX, double deplacementY){
		deplacerXY(Vecteur2i((int)deplacementX, (int)deplacementY));
	}

    /// Deplacement dans le plan XY par rapport a la vue
    void VuePerspect::deplacerXY(const Vecteur2i& deplacement){

		phi_ -= (deplacement[1]) / 60.0f;
		
		theta_ -= (-deplacement[0]) / 60.0f;

		verifierAngles();

		camera_.positionnerOrbite(theta_, phi_, distance_);
	}

	void VuePerspect::verifierAngles(){

		if ( RAD2DEG(phi_) > MAXPHI ){
			phi_ = DEG2RAD(MAXPHI);

		}else if (  RAD2DEG(phi_) < MINPHI ){
			phi_ = DEG2RAD(MINPHI);
		}

	}

    /// Deplacement selon l'axe des Z par rapport a la vue
    void VuePerspect::deplacerZ(double deplacement){

	}

    /// Rotation selon les axes des X et des Y par rapport a la vue
    void VuePerspect::rotaterXY(double rotationX, double rotationY){
		camera_.orbiterXY(rotationX * 360, rotationY * 180);
	}

    /// Rotation selon les axes des X et des Y par rapport a la vue
    void VuePerspect::rotaterXY(const Vecteur2i& rotation){
		const Vecteur2i dimensions = projection_.obtenirDimensionCloture();
		rotaterXY(rotation[0] / (double) dimensions[0], rotation[1] / (double) dimensions[1]);
	}

    /// Rotation selon l'axe des Z par rapport a la vue
    void VuePerspect::rotaterZ(double rotation){

	}

};

///////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////
