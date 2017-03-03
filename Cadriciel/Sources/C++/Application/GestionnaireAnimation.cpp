//////////////////////////////////////////////////////////////////////////////
/// @file GestionnaireAnimation.cpp
/// @author FloppyDisketeers
/// @date 2014-01-25
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include "GestionnaireAnimation.h"
#include "FacadeModele.h"
int GestionnaireAnimation::compteurStation_ = 0;
int GestionnaireAnimation::compteurAsteroid1_ = 0;
int GestionnaireAnimation::compteurAsteroid2_ = 0;
SINGLETON_DECLARATION_CPP(GestionnaireAnimation);

/*
 * Constructeur
 */
GestionnaireAnimation::GestionnaireAnimation() {
	
	animationStationEnCours_ = false;
	animationAsteroid1EnCours_ = false;
	animationAsteroid2EnCours_ = false;

	rayonStation_ = 0.0f;
	rayonAsteroide1_ = 0.0f;
	rayonAsteroide2_ = 0.0f;

   	bitmap_ = FreeImage_Load(FIF_PNG, "./animation/animationStation2.png", PNG_DEFAULT);
   	if (bitmap_) {
	// Si le chargement de l'image a reussi
		largeurPixel_ = FreeImage_GetWidth(bitmap_); 
		hauteurPixel_= FreeImage_GetHeight(bitmap_); 
		
		BYTE* textures = new BYTE[4 * largeurPixel_ * hauteurPixel_];
		BYTE* pixels = (BYTE*)FreeImage_GetBits(bitmap_);

		// Chargement des pixels pour la texture 
		for(int j = 0; j < (largeurPixel_*hauteurPixel_); j++){
			textures[j*4+0]= pixels[j*4+2];
			textures[j*4+1]= pixels[j*4+1];
			textures[j*4+2]= pixels[j*4+0];
			textures[j*4+3]= pixels[j*4+3];
		}
 
		//Now generate the OpenGL texture object 
		glGenTextures(1, &textureID_);
		glBindTexture(GL_TEXTURE_2D, textureID_);
		glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA, largeurPixel_, hauteurPixel_, 0, GL_RGBA,GL_UNSIGNED_BYTE,(GLvoid*)textures );
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

/*
 * Destructeur
 */
GestionnaireAnimation::~GestionnaireAnimation(){
		FreeImage_Unload(bitmap_);
};

void GestionnaireAnimation::setPositionStationX(float x){
	xStation_ = x;
}
void GestionnaireAnimation::setPositionStationY(float y){
	yStation_ = y;
}
void GestionnaireAnimation::setPositionAsteroid1X(float x){
	xAsteroid1_ = x;
}
void GestionnaireAnimation::setPositionAsteroid1Y(float y){
	yAsteroid1_ = y;
}
void GestionnaireAnimation::setPositionAsteroid2X(float x){
	xAsteroid2_ = x;
}
void GestionnaireAnimation::setPositionAsteroid2Y(float y){
	yAsteroid2_ = y;
}
void GestionnaireAnimation::setAnimationStationEnCours(bool valeur){
	animationStationEnCours_ = valeur;
}
void GestionnaireAnimation::setAnimationAsteroid1EnCours(bool valeur){
	animationAsteroid1EnCours_ = valeur;
}
void GestionnaireAnimation::setAnimationAsteroid2EnCours(bool valeur){
	animationAsteroid2EnCours_ = valeur;
}

/*
 * animer()
 * L'animation d'explosion en général
 */
void GestionnaireAnimation::animer(int compteur, float x, float y, float rayon){

	float theta, phi;

	if(FacadeModele::obtenirInstance()->isModeOrtho()){
		theta = 0.0f;
		phi = 0.0f;
	}else{
		theta = (float) FacadeModele::obtenirInstance()->obtenirVue()->getTheta();
		theta+=90.0f;
		phi = (float) FacadeModele::obtenirInstance()->obtenirVue()->getPhi();
	}

		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glPushMatrix();
			glTranslatef(x, y, 0.0f);
			glRotatef(theta, 0.0f, 0.0f, 1.0f );
			glRotatef(phi, 1.0f, 0.0f, 0.0f );
			glScalef(200.0f * rayon/38.0f, 200.0f * rayon/38.0f , 1.0f);
			glBindTexture(GL_TEXTURE_2D, textureID_);
			glBegin (GL_QUADS);
			glTexCoord2f((float)(compteur/48.0f), 0.0f);
			glVertex3f (-0.5f, -0.5f, 0.0f);
			glTexCoord2f((float)(1.0f+compteur)/48.0f , 0.0f);
			glVertex3f (0.5f, -0.5f, 0.0f);
			glTexCoord2f((float)(1.0f+compteur)/48.0f , 1.0f);
			glVertex3f (0.5f, 0.5f, 0.0f);
			glTexCoord2f((float)(compteur/48.0f) , 1.0f);
			glVertex3f (-0.5f, 0.5f, 0.0f);
 			glEnd ();
			glPopMatrix();
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_2D);
}
/*
 * animationStation()
 */
void GestionnaireAnimation::animationStation(){
	
	animer(compteurStation_, this->getPositionStationX(), this->getPositionStationY(), rayonStation_);
	compteurStation_++;
	if( (compteurStation_ % 48) == 0){
		animationStationEnCours_ = false;
		compteurStation_ = 0;
	}
}

/*
 * animationAsteroid1()
 */
void GestionnaireAnimation::animationAsteroid1(){

	animer(compteurAsteroid1_, this->getPositionAsteroid1X(), this->getPositionAsteroid1Y(), rayonAsteroide1_);
	compteurAsteroid1_++;
	if( (compteurAsteroid1_ % 48) == 0){
		animationAsteroid1EnCours_ = false;
		compteurAsteroid1_ = 0;
	}
}

/*
 * animationAsteroid2()
 */
void GestionnaireAnimation::animationAsteroid2(){

	animer(compteurAsteroid2_, this->getPositionAsteroid2X(), this->getPositionAsteroid2Y(), rayonAsteroide2_);
	compteurAsteroid2_++;
	if( (compteurAsteroid2_ % 48) == 0){
		animationAsteroid2EnCours_ = false;
		compteurAsteroid2_ = 0;
	}
}

void GestionnaireAnimation::interrompreAnimation(){

	compteurStation_ = 0;
	compteurAsteroid1_ = 0;
	compteurAsteroid2_ = 0;

	
	animationStationEnCours_ = false;
	animationAsteroid1EnCours_ = false;
	animationAsteroid2EnCours_ = false;
}
