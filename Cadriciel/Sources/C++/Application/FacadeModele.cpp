///////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.cpp
/// @author Martin Bisson
/// @date 2007-05-22
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////


// Commentaire Doxygen mis sur la première page de la documentation Doxygen.
/**

@mainpage Projet intégrateur de deuxième année -- INF2990

@li <a href="../javadoc/index.html">Documentation Javadoc de la partie Java.</a>
*/

#include <windows.h>
#include "../../../Commun/Externe/GLEW/include/GL/glew.h"
#include <GL/GL.h>
#include <cassert>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <sstream>

#include "FreeImage.h"

#include "FacadeModele.h"

#include "VueOrtho.h"
#include "VuePerspect.h"
#include "Camera.h"
#include "Projection.h"

#include "Utilitaire.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"

#include "ConfigScene.h"
#include "GestionnaireXML.h"
#include "GestionnaireSon.h"

#include "../../../Commun/Utilitaire/BoiteEnvironnement.h"

// Remlacement de EnveloppeXML/XercesC par TinyXML
// Julien Gascon-Samson, été 2011
#include "tinyxml.h"

#include "CompteurAffichage.h"

#include "Jeu/ModeEdition/ModeEdition.h"
#include "Jeu/ModeJeu/ModePartieRapide.h"
#include "Jeu/ModeJeu/ModeCampagne.h"
#include "Jeu/ModeJeu/ModeTest.h"
#include "Jeu/JeuAbstrait.h"
#include "GestionnaireAnimation.h"

#include "Carte.h"
#include "../Arbre/Modeles/GestionnaireAsteroide.h"
#include "AffichageDebogage.h"

#include "../AffichageTexte/FreeType.h"

#define ZONE_JEU_HAUTEUR (3600.0f/16.0f*9.0f)

/// Pointeur vers l'instance unique de la classe.
FacadeModele* FacadeModele::instance_ = 0;

////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele* FacadeModele::obtenirInstance()
///
/// Cette fonction retourne un pointeur vers l'instance unique de la
/// classe.  Si cette instance n'a pas été créée, elle la crée.  Cette
/// création n'est toutefois pas nécessairement "thread-safe", car
/// aucun verrou n'est pris entre le test pour savoir si l'instance
/// existe et le moment de sa création.
///
/// @return Un pointeur vers l'instance unique de cette classe.
///
////////////////////////////////////////////////////////////////////////
FacadeModele* FacadeModele::obtenirInstance()
{
	if (instance_ == 0){
		instance_ = new FacadeModele;
	}

	return instance_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererInstance()
///
/// Cette fonction libère l'instance unique de cette classe.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererInstance()
{
	GestionnaireAsteroide::getInstance()->detruireAsteroides();

	delete instance_->carte_;
	instance_->carte_ = 0;
	delete instance_;
	instance_ = 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::FacadeModele()
///
/// Ce constructeur par défaut ne fait qu'initialiser toutes les
/// variables à une valeur nulle.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::FacadeModele()
	: hGLRC_(0), hDC_(0), hWnd_(0), vue_(0), arbre_(0), carte_(0), jeu_(0),
	tempsDelta_(0.0f), statutJeu_(0), estModeEdition_(false), estOrtho_(true),
	lumiereAmbiante_(true), lumiereDiffuse_(true), lumiereSpot_(true)
{
	srand((int)time(NULL));

	// Comme ça on randomize encore le seed
	rand();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn FacadeModele::~FacadeModele()
///
/// Ce destructeur libère les objets du modèle.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
FacadeModele::~FacadeModele()
{
	delete arbre_;
	delete vue_;
	delete jeu_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::initialiserOpenGL(HWND hWnd)
///
/// Cette fonction permet d'initialiser le contexte OpenGL.  Elle crée
/// un contexte OpenGL sur la fenêtre passée en paramètre, initialise
/// FreeImage (utilisée par le chargeur 3DS) et assigne des paramètres
/// du contexte OpenGL.
///
/// @param[in] hWnd : La poignée ("handle") vers la fenêtre à utiliser.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::initialiserOpenGL(HWND hWnd)
{
	hWnd_ = hWnd;
	bool succes = aidegl::creerContexteGL(hWnd_, hDC_, hGLRC_);
	assert(succes);

	// FreeImage, utilisée par le chargeur, doit être initialisée
	FreeImage_Initialise();

	// Desactiver la lumiere ambiante par defaut
	GLfloat zero[4] = { 0.0f, 0.0f, 0.0f, 1.0f};
	glLightModelfv( GL_LIGHT_MODEL_AMBIENT, zero );

	// Eclairage
	glEnable( GL_LIGHTING ); // Activer l'eclairage
	glEnable( GL_COLOR_MATERIAL ); // Activer les materiaux/couleurs
	glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE ); // Eclairer des 2 cotes

	// Qualite
	glShadeModel( GL_SMOOTH ); // Interpolation de Gouraud
	glHint( GL_LINE_SMOOTH_HINT, GL_NICEST );

	// Profondeur
	glEnable( GL_DEPTH_TEST );
	glEnable(GL_ALPHA_TEST);
	glBlendFunc (GL_SRC_ALPHA, GL_SRC_ALPHA);

	// images de la skybox
	string skyTexturePosX = "media/starfields_1024_2048_by_tbh_1138-d30dvm7.png";
	string skyTextureNegX = "media/starfields_1024_2048_by_tbh_1138-d30dvm7.png";
	string skyTexturePosY = "media/starfields_1024_2048_by_tbh_1138-d30dvm7.png";
	string skyTextureNegY = "media/starfields_1024_2048_by_tbh_1138-d30dvm7.png";
	string skyTexturePosZ = "media/starfields_1024_2048_by_tbh_1138-d30dvm7.png";
	string skyTextureNegZ = "media/starfields_1024_2048_by_tbh_1138-d30dvm7.png";

	// Skybox
	skybox_ = new utilitaire::BoiteEnvironnement(skyTexturePosX, skyTextureNegX, skyTexturePosY, skyTextureNegY, skyTexturePosZ, skyTextureNegZ);

	// Ne devrait pas arriver!
	if (glewInit() != GLEW_OK) {
		assert(false);
	}

	GestionnaireAsteroide::getInstance()->genererAsteroides(25, 8, 8, 8, 0.7f, 1.0f, 2.0f, 1.0f, 2.0f, 1.0f, 2.0f, 1.0f, 1.05f, 0.98f, 1.01f);
	phontTexte_.load("./media/", "v5prophit");
	phontVie_.load("./media/", "pf16");
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::chargerConfiguration() const
///
/// Cette fonction charge la configuration à partir d'un fichier XML si
/// ce dernier existe.  Sinon, le fichier de configuration est généré à
/// partir de valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::chargerConfiguration(string nomFichier)
{
	if(carte_ != 0)
		delete carte_;
	carte_ = GestionnaireXML::obtenirInstance()->chargerCarte(nomFichier);

	delete jeu_;
	jeu_ = new ModeEdition(*carte_, vue_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::enregistrerConfiguration() const
///
/// Cette fonction génère un fichier XML de configuration à partir de
/// valeurs par défaut directement dans le code.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::enregistrerConfiguration(string nomFichier) const
{
	GestionnaireXML::obtenirInstance()->sauvegarderCarte(nomFichier, *carte_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::libererOpenGL()
///
/// Cette fonction libère le contexte OpenGL et désinitialise FreeImage.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::libererOpenGL()
{
	utilitaire::CompteurAffichage::libererInstance();

	// On libère les instances des différentes configurations.
	ConfigScene::libererInstance();

	bool succes = aidegl::detruireContexteGL(hWnd_, hDC_, hGLRC_);
	assert(succes);

	FreeImage_DeInitialise();
	//FacadeModele::obtenirInstance()->lifeFormFont.clean();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficher() const
///
/// Cette fonction affiche le contenu de la scène.
///
/// @param enPause Est-ce que le jeu est en pause?
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficher(bool enPause) const
{
	// Efface l'ancien rendu
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );

	// Ne devrait pas être nécessaire
	vue_->appliquerProjection();

	// Positionne la caméra
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	vue_->appliquerCamera();

	// Afficher la skybox
	if(estOrtho_){
		double xMin = 0, xMax = 0, yMax = 0, yMin = 0;

		Vecteur4 coordone = vue_->obtenirProjection().getDimensionsFenetre();
		double milieuX = 0, milieuY = 0, milieuZ = 0;

		milieuX = coordone[0]; // Gauche
		milieuY = (coordone[2] + coordone[3]) / 2;

		Vecteur3 camera(milieuX, milieuY , 0);
		skybox_->afficher(camera, (coordone[3] - coordone[2]) / 2 );
		
		milieuX = (coordone[0] + coordone[1]) / 2; // Centre
		camera = Vecteur3(milieuX, milieuY , 0);
		skybox_->afficher(camera, (coordone[3] - coordone[2]) / 2 );
		
		milieuX = coordone[1]; // Droite
		camera = Vecteur3(milieuX, milieuY , 0);
		skybox_->afficher(camera, (coordone[3] - coordone[2]) / 2 );

	} else {
		//skybox_->afficher(Vecteur3(0,0,0), canvasMaxX_ * 4);

		Vecteur2i coordone = vue_->obtenirProjection().obtenirDimensionCloture();
		skybox_->afficher(vue_->obtenirCamera().obtenirPosition(), (coordone[1]) / 2);
	}
	
	positionnerLumieres();

	positionnerLumieres(); //Mettre avant de l'update du jeu pour éviter de faire disparaitre la lumière durant le repositionnement.

	// Afficher la scène
		afficherBase();

	// Update du jeu
	if (!enPause) {
		jeu_->update(tempsDelta_);
	}

	if(GestionnaireAnimation::obtenirInstance()->getAnimationStationEnCours()){
		GestionnaireAnimation::obtenirInstance()->animationStation();
	}

	if(GestionnaireAnimation::obtenirInstance()->getAnimationAsteroid1EnCours()){
		GestionnaireAnimation::obtenirInstance()->animationAsteroid1();
	}

	if(GestionnaireAnimation::obtenirInstance()->getAnimationAsteroid2EnCours()){
		GestionnaireAnimation::obtenirInstance()->animationAsteroid2();
	}

	// Compte de l'affichage
	utilitaire::CompteurAffichage::obtenirInstance()->signalerAffichage();

	// Échange les tampons pour que le résultat du rendu soit visible.
	::SwapBuffers( hDC_ );
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::afficherBase() const
///
/// Cette fonction affiche la base du contenu de la scène, c'est-à-dire
/// qu'elle met en place l'éclairage et affiche les objets.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::afficherBase() const
{
	// Afficher la scène.
	arbre_->afficher();
	// Afficher la cadre du zone de jeu et du cadre de depart
	AffichageDebogage::obtenirInstance()->afficherCadreDepart(carte_);
	AffichageDebogage::obtenirInstance()->afficherZonePassage(carte_);

	
}

void FacadeModele::positionnerLumieres() const
{
	float lum = 0.3f;

	glDisable(GL_LIGHT0);

	// Premiere lumiere
	if (lumiereAmbiante_) // Si la lumiere ambiante est activee
	{
		GLfloat lum1Ambiante[4] = { lum, lum, lum, 1.0f }; // Lumiere ambiante grise
		glLightfv(GL_LIGHT1, GL_AMBIENT, lum1Ambiante); // Activer la lumiere ambiante
		glEnable(GL_LIGHT1); // Activer la premiere lumiere
	}
	else // Sinon
	{
		glDisable(GL_LIGHT1); // Desactiver la lumiere
	}

	// Deuxieme lumiere
	if (lumiereDiffuse_) // Si la lumiere diffuse est activee
	{
		GLfloat lum2Directionnelle[4] = { lum, lum, lum, 1.0f }; // Lumiere directionnelle grise
		GLfloat lum2Position[4] = { 0.0f, -ZONE_JEU_HAUTEUR, ZONE_JEU_HAUTEUR, 0.0f }; // Positionnee a la hauteur du jeu

		glLightfv(GL_LIGHT2, GL_DIFFUSE, lum2Directionnelle);
		glLightfv(GL_LIGHT2, GL_POSITION, lum2Position);

		glEnable(GL_LIGHT2);
	}
	else // Sinon
	{
		glDisable(GL_LIGHT2); // Desactiver la lumiere
	}

	// Troisieme lumiere
	if (lumiereSpot_) // Si les spolights sont actives
	{
		aiVector3D pos1 = carte_->getJoueur1()->getPositionActuelle(); // Obtenir position du joueur 1
		aiVector3D dir1 = carte_->getJoueur1()->getDirectionVitesse(); // Obtenir direction du joueur 1

		GLfloat lum3Diffuse[4] = { 1.0f, 0.0f, 0.0f, 1.0f }; // Rouge-ish
		GLfloat lum3Position[4] = { pos1.x, pos1.y, pos1.z, 1.0f };
		GLfloat lum3Direction[3] = { dir1.x, dir1.y, dir1.z };
		GLfloat exposant = 4.0f;
		GLfloat cutoff = 15.0f;

		glLightfv(GL_LIGHT3, GL_DIFFUSE, lum3Diffuse);
		glLightfv(GL_LIGHT3, GL_POSITION, lum3Position);
		glLightfv(GL_LIGHT3, GL_SPOT_DIRECTION, lum3Direction);
		glLightf (GL_LIGHT3, GL_SPOT_EXPONENT, exposant);
		glLightf (GL_LIGHT3, GL_SPOT_CUTOFF, cutoff);

		glEnable(GL_LIGHT3);

		// Quatrieme lumiere
		if (carte_->getModeCoop()) // S'il y a un joueur virtuel
		{
			aiVector3D pos2 = carte_->getJoueur2()->getPositionActuelle(); // Obtenir position du joueur 2
			aiVector3D dir2 = carte_->getJoueur2()->getDirectionVitesse(); // Obtenir direction du joueur 2

			GLfloat lum4Diffuse[4] = { 0.0f, 0.0f, 1.0f, 1.0f }; // Blue-ish
			GLfloat lum4Position[4] = { pos2.x, pos2.y, pos2.z, 1.0f };
			GLfloat lum4Direction[3] = { dir2.x, dir2.y, dir2.z };
			GLfloat exposant = 4.0f;
			GLfloat cutoff = 15.0f;

			glLightfv(GL_LIGHT4, GL_DIFFUSE, lum4Diffuse);
			glLightfv(GL_LIGHT4, GL_POSITION, lum4Position);
			glLightfv(GL_LIGHT4, GL_SPOT_DIRECTION, lum4Direction);
			glLightf (GL_LIGHT4, GL_SPOT_EXPONENT, exposant);
			glLightf (GL_LIGHT4, GL_SPOT_CUTOFF, cutoff);

			glEnable(GL_LIGHT4);
		}		
	}
	else // Sinon
	{
		glDisable(GL_LIGHT3); // Desactiver la lumiere
		glDisable(GL_LIGHT4);
	}
}

void FacadeModele::recevoirInput(int mouseX, int mouseY, int boutton, int touche, int scroll) {
	jeu_->recevoirInputs(mouseX, mouseY, boutton, touche, scroll);	
}

void FacadeModele::initialiser() {

	// Initialisation de la configuration
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();

	carte_ = NULL;
}

void FacadeModele::initialiserModeEdition()
{
	eteindreLumiereSpot();

	if (carte_ == NULL)
	{
		delete arbre_;
		arbre_ = new ArbreRenduINF2990;
		arbre_->initialiser();
		carte_ = GestionnaireXML::obtenirInstance()->chargerCarteDefaut();
	}

	// On crée une vue.
	delete vue_;
	vue_ = new vue::VueOrtho(
		vue::Camera(Vecteur3(0, 0, 300), Vecteur3(0, 0, 0),
		Vecteur3(0, 1, 0)  , Vecteur3(0, 1, 0)),
		0, int(canvasMaxX_), 0, int(canvasMaxY_),
		1, 10000, 0.10, 4, 0.10,	// Anciennes valeurs de facteurs zooms sont 1 et 10000
		-250, 250, -ZONE_JEU_HAUTEUR/2.0f*1.15f, ZONE_JEU_HAUTEUR/2.0f*1.15f		// MODIFIER ICI SI ON COMMENCE PLUS LOIN
		);

	carte_->echangerVaisseauPourPositionDepart();
	carte_->detruireAsteroides();
	carte_->detruireProjectiles();

	delete jeu_;
	jeu_ = new ModeEdition(*carte_, vue_);
	estModeEdition_ = true;

	setTypeDeVue(true);

	// Pas de musique en mode edition!
	GestionnaireSon::obtenirInstance()->arreterMusique();
}

void FacadeModele::initialiserPartieRapide(string nomCarte, bool modeCoop, bool joueur2Virtuel)
{
	arbre_->deselectionnerTout();

	allumerLumiereSpot();
	GestionnaireAnimation::obtenirInstance()->interrompreAnimation();

	// Initialisation de la configuration
	//delete arbre_;
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();

	carte_ = GestionnaireXML::obtenirInstance()->chargerCarte(nomCarte);
	carte_->definirModeJoueurs(modeCoop, joueur2Virtuel);
	carte_->detruireAsteroides();

	// On crée une vue.
	delete vue_;
	vue_ = new vue::VueOrtho(
		vue::Camera(Vecteur3(0, 0, 300), Vecteur3(0, 0, 0),
		Vecteur3(0, 1, 0)  , Vecteur3(0, 1, 0)),
		0, int(canvasMaxX_), 0, int(canvasMaxY_),
		1, 1000, 0.10, 4, 0.10,	// Anciennes valeurs de facteurs zooms sont 1 et 10000
		-750, 750, -ZONE_JEU_HAUTEUR/2.0f*1.15f, ZONE_JEU_HAUTEUR/2.0f*1.15f
		);

	delete jeu_;
	jeu_ = new ModePartieRapide(*carte_, vue_);
	estModeEdition_ = false;

	setTypeDeVue(true);
	// La musique!
	GestionnaireSon::obtenirInstance()->jouerMusique();
}

void FacadeModele::initialiserModeCampagne(bool modeCoop, bool joueur2Virtuel, vector<string> cartes)
{
	arbre_->deselectionnerTout();

	allumerLumiereSpot();
	GestionnaireAnimation::obtenirInstance()->interrompreAnimation();

	// Initialisation de la configuration
	//delete arbre_;
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();

	// On crée une vue.
	delete vue_;
	vue_ = new vue::VueOrtho(
		vue::Camera(Vecteur3(0, 0, 300), Vecteur3(0, 0, 0),
		Vecteur3(0, 1, 0)  , Vecteur3(0, 1, 0)),
		0, int(canvasMaxX_), 0, int(canvasMaxY_),
		1, 10000, 0.10, 4, 0.10,	// Anciennes valeurs de facteurs zooms sont 1 et 10000
		-650, 650, -ZONE_JEU_HAUTEUR/2.0f*1.15f, ZONE_JEU_HAUTEUR/2.0f*1.15f		// MODIFIER ICI SI ON COMMENCE PLUS LOIN
		);

	delete carte_;
	carte_ = GestionnaireXML::obtenirInstance()->chargerCarteDefaut(); // Carte bidon, sera ecrasee

	delete jeu_;
	jeu_ = new ModeCampagne(*carte_, vue_, cartes, modeCoop, joueur2Virtuel);
	estModeEdition_ = false;

	setTypeDeVue(true);

	// La musique!
	GestionnaireSon::obtenirInstance()->jouerMusique();
}

void FacadeModele::setTypeDeVue(bool estOrtho){

	//On stock les informations importantes de la vue précédente
	Vecteur2i coinMin, coinMax;
	double xMinFenetre , xMaxFenetre , yMinFenetre , yMaxFenetre;
	xMinFenetre = vue_->obtenirProjection().getDimensionsFenetre()[0];
	xMaxFenetre = vue_->obtenirProjection().getDimensionsFenetre()[1];
	yMinFenetre = vue_->obtenirProjection().getDimensionsFenetre()[2];
	yMaxFenetre = vue_->obtenirProjection().getDimensionsFenetre()[3];
	vue_->obtenirCoinsMax(coinMax[0], coinMax[1]);

	vue::Camera ancienneCamera = vue_->obtenirCamera();

	//On supprime l'ancienne vue
	delete vue_;
	
	//On passe en mode vue orthographique en réutilisant les paramètres sauvegardés
	if(estOrtho){

		vue_ = new vue::VueOrtho(vue::Camera(Vecteur3(0, 0, 300), Vecteur3(0, 0, 0), Vecteur3(0, 1, 0), Vecteur3(0, 1, 0)),
			0, coinMax[0], 0, coinMax[1],
			1, 10000,
			0.10, 4,
			0.10,	
			xMinFenetre, xMaxFenetre,
			yMinFenetre, yMaxFenetre);

		estOrtho_ = true;

	}else /*On passe en mode vue orbite*/{

		vue_ = new vue::VuePerspect(vue::Camera(Vecteur3(1, -2500, 3500), Vecteur3(0, 0, 0), Vecteur3(0, 0, 1), Vecteur3(0, 0, 1)),
			0, coinMax[0], 0, coinMax[1],
			1, 100000,
			0.10, 4,
			50,	
			xMinFenetre, xMaxFenetre,
			yMinFenetre, yMaxFenetre);

		estOrtho_ = false;
	}


	vue_->redimensionnerFenetre(coinMin, coinMax);
	

	jeu_->setVue(vue_);
	jeu_->setPourcentageDeplacement(estOrtho_);
}

string FacadeModele::obtenirInformations()
{
	stringstream msg;
	msg << "Zone : " << carte_->getNom() << endl;
	msg << "Difficulté : ";

	switch (carte_->getDifficulte())
	{
	case 0 :
		msg << "Facile";
		break;
	case 1 :
		msg << "Normal";
		break;
	case 2 :
		msg << "Difficile";
		break;
	case 3 :
		msg << "IMPOSSIBRUUU";
		break;
	default:
		msg << "Aucune";
		break;
	}

	msg << endl;
	msg << "Durée : " << FacadeModele::obtenirInstance()->getTempsJeu() << " secondes" << endl;
	msg << "Nombre de stations à sauver : " << carte_->getNbMinStationASauver() << endl;

	return msg.str();
}

void FacadeModele::prochainePartie()
{
	// Initialisation de la configuration
	
	GestionnaireAnimation::obtenirInstance()->interrompreAnimation();
	arbre_ = new ArbreRenduINF2990;
	arbre_->initialiser();

	bool modeCoop = carte_->getModeCoop();
	bool joueur2Virtuel = carte_->getJoueur2Virtuel();

	dynamic_cast<ModeCampagne*>(jeu_)->prochaineCarte(modeCoop, joueur2Virtuel);
}

void FacadeModele::initialiserModeTest()
{
	arbre_->deselectionnerTout();

	allumerLumiereSpot();

	carte_->definirModeJoueurs(false, false);
	carte_->detruireAsteroides();
	carte_->detruireProjectiles();
	carte_->detruireQuadTree();

	// On crée une vue.
	vue_ = new vue::VueOrtho(
		vue::Camera(Vecteur3(0, 0, 300), Vecteur3(0, 0, 0),
		Vecteur3(0, 1, 0)  , Vecteur3(0, 1, 0)),
		0, int(canvasMaxX_), 0, int(canvasMaxY_),
		1, 1000, 0.10, 4, 0.10,	// Anciennes valeurs de facteurs zooms sont 1 et 10000
		-250, 250, -ZONE_JEU_HAUTEUR/2.0f*1.15f, ZONE_JEU_HAUTEUR/2.0f*1.15f		// MODIFIER ICI SI ON COMMENCE PLUS LOIN
		);

	delete jeu_;
	jeu_ = new ModeTest(*carte_, vue_);

	setTypeDeVue(true);

	// Pas de musique en mode test!
	GestionnaireSon::obtenirInstance()->arreterMusique();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::animer(float temps)
///
/// Cette fonction effectue les différents calculs d'animations
/// nécessaires pour le mode jeu, tel que les différents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::animer(float temps)
{
	tempsDelta_ = temps;

	// Update du gestionnaire de son
	GestionnaireSon::obtenirInstance()->update();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setCommande(int numeroOutil)
///
/// Methode qui permet de set une commande
///
/// @return string : le nom de la carte.
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setCommande(int numeroOutil)
{
	dynamic_cast<ModeEdition*>(jeu_)->setCommand(numeroOutil);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn string FacadeModele::getNomCarteActuelle()
///
/// Methode qui permet de récuperer le nom de la carte
///
/// @return string : le nom de la carte.
///
////////////////////////////////////////////////////////////////////////
string FacadeModele::getNomCarteActuelle()
{
	return carte_->getNom();
}

void FacadeModele::setPositionAngleScaleObjetSelectionne(float posX, float posY, float posZ,
	float angle, float scaleX, float scaleY,
	float scaleZ)
{
	DYNAMIC_CAST<ModeEdition*>(jeu_)->setPositionAngleScaleObjetSelectionne(posX, posY, posZ, angle, scaleX, scaleY, scaleZ);
}

bool FacadeModele::getPositionAngleScaleTypeObjetSelectionne(float floats[]) {
	if (getNombreObjetsSelectionnes() == 1) {
		ElementJeuAbstrait* element = DYNAMIC_CAST<ModeEdition*>(jeu_)->getObjetsSelectionnes()[0];
		aiVector3D position = element->getPositionActuelle();
		float angle = element->getAngle();
		aiVector3D taille = element->getTaille();

		floats[0] = position.x;
		floats[1] = position.y;
		floats[2] = position.z;

		floats[3] = angle;

		floats[4] = taille.x;
		floats[5] = taille.y;
		floats[6] = taille.z;

		floats[7] = (float)element->getType();

		return true;
	}

	return false;
}

size_t FacadeModele::getNombreObjetsSelectionnes() {
	return DYNAMIC_CAST<ModeEdition*>(jeu_)->getObjetsSelectionnes().size();
}

/*toucheJoueur1Propulsion, toucheJoueur1TournerGauche,
toucheJoueur1TournerDroite, toucheJoueur1Manoeuvre,
toucheJoueur1Tir, toucheJoueur2Propulsion,
toucheJoueur2TournerGauche, toucheJoueur2TournerDroite,
toucheJoueur2Manoeuvre, toucheJoueur2Tir, 
dureeJeu, pointsDeVieStation */
void FacadeModele::getTouchesDureeJeuPointDeVie(float floats[]) {
	floats[0] = (float)mapCommandesJoueur_[J1PROP];
	floats[1] = (float)mapCommandesJoueur_[J1ROTANTI];
	floats[2] = (float)mapCommandesJoueur_[J1ROT];
	floats[3] = (float)mapCommandesJoueur_[J1MANOEUVRE];
	floats[4] = (float)mapCommandesJoueur_[J1TIR];
	floats[5] = (float)mapCommandesJoueur_[J2PROP];
	floats[6] = (float)mapCommandesJoueur_[J2ROTANTI];
	floats[7] = (float)mapCommandesJoueur_[J2ROT];
	floats[8] = (float)mapCommandesJoueur_[J2MANOEUVRE];
	floats[9] = (float)mapCommandesJoueur_[J2TIR];
	floats[10] = (float)dureeDeJeu_;
	floats[11] = (float)ptsDeVieStation_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::mapCommande(int commande, int touche)
///
/// Methode qui permet de map la commande a une touche spécifique
///
/// @param[in] int commande, int touche
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::mapCommande(int commande, int touche)
{
	mapCommandesJoueur_[commande] = touche;
}

void FacadeModele::recevoirMultipleInput(const vector<int>& touches) {
	touchesAppuyees_ = touches;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void FacadeModele::setCanvasSizeMax(float largeurMaxCadre, float hauteurMaxCadre)
///
/// Methode qui permet de setter les grosseurs max du canvas.
///
/// @param[in] (float largeurMaxCanvas, float hauteurMaxCanvas)
///
/// @return Aucun
///
////////////////////////////////////////////////////////////////////////
void FacadeModele::setCanvasSizeMax(float largeurMaxCanvas, float hauteurMaxCanvas)
{
	canvasMaxX_ = largeurMaxCanvas;
	canvasMaxY_ = hauteurMaxCanvas;
}

void FacadeModele::allumerLumiereAmbiante()
{ lumiereAmbiante_ = true; }

void FacadeModele::eteindreLumiereAmbiante()
{ lumiereAmbiante_ = false; }

void FacadeModele::allumerLumiereDiffuse()
{ lumiereDiffuse_ = true; }

void FacadeModele::eteindreLumiereDiffuse()
{ lumiereDiffuse_ = false; }

void FacadeModele::allumerLumiereSpot()
{ lumiereSpot_ = true; }

void FacadeModele::eteindreLumiereSpot()
{ lumiereSpot_ = false; }

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////