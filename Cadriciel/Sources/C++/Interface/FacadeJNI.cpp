///////////////////////////////////////////////////////////////////////////////
/// @file FacadeJNI.cpp
/// @author Martin Bisson
/// @date 2007-08-14
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#include "jawt_md.h"
#include "JAWT_Info.h"
#include "FreeImage.h"

#include "FacadeJNI.h"
#include "Vecteur.h"
#include "FacadeModele.h"
#include "Vue.h"
#include "AideGL.h"
#include "ArbreRenduINF2990.h"
#include "CompteurAffichage.h"
#include "UtilitaireINF2990.h"
#include "GestionnaireXML.h"
#include "AffichageDebogage.h"
#include "Jeu\ModeJeu\ModeJeu.h"
#include "GestionnaireSon.h"

#include "BancTests.h"

#include "../Application/Jeu/ModeEdition/ModeEdition.h"

#include <windows.h>
#include <GL/gl.h>
#include <vector>

#pragma warning(disable: 4800) // Warning de conversion jboolean to bool

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1initialiserOpenGL(JNIEnv* env, jclass, jobject canvas)
///
/// Cette fonction initialise un contexte OpenGL dans la fenetre
/// identifiee par le canvas AWT passe en parametre.  Cette fonction doit
/// etre la premiere a etre appelee, car la creation de l'objet du modele
/// C++ s'attend a avoir un contexte OpenGL valide.
///
/// @param[in] env    : L'environnement Java.
/// @param[in] canvas : Le canvas dans lequel creer le contexte OpenGL.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1initialiserOpenGL
  (JNIEnv* env, jclass, jobject canvas)
{
   // Obtenir la poignee ("handle") vers la fenetre.
   JAWT_Info info(env, canvas);
   HWND hWnd = (HWND)info.getHWND();
	
   // On pourrait lancer une exception a la place...
   if(hWnd == 0)
      return;

	FacadeModele::obtenirInstance()->initialiserOpenGL(hWnd);
}

JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1initialiser
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->initialiser();
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_initialiserModeEdition
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1initialiserModeEdition
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->initialiserModeEdition();
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_initialiserModePartieRapide
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1initialiserModePartieRapide

  (JNIEnv * env, jclass, jint modeCoop, jint joueur2, jstring nomFichierJava)
{
	string nomFichierC = utilitaire::obtenirChaineISO(env, nomFichierJava);
	FacadeModele::obtenirInstance()->initialiserPartieRapide(nomFichierC,modeCoop,joueur2);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_initialiserModeCampagne
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1initialiserModeCampagne
  (JNIEnv * env, jclass, jint modeCoop, jint joueur2Virtuel, jobjectArray cartes)
{
	// Vecteur final contenant le noms des cartes a utiliser pour la campagne
	vector<string> nomCartes;
	unsigned int nbCartes = env->GetArrayLength(cartes); // Obtenir le nombre de cartes

	for (unsigned int i = 0; i < nbCartes; i++) // Parcourir chacun des noms de carte
	{
		// Convertir en string le nom de la carte et l'inserer dans le vecteur
		jstring nomCarte = (jstring) env->GetObjectArrayElement(cartes, i);
		nomCartes.push_back(utilitaire::obtenirChaineISO(env, nomCarte));
	}

	FacadeModele::obtenirInstance()->initialiserModeCampagne(modeCoop, joueur2Virtuel, nomCartes);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_obtenirInformationsPartie
 * Signature: ()V
 */
JNIEXPORT jstring JNICALL Java_InterfaceGraphique_Demarrage_fctC_1obtenirInformationsPartie
  (JNIEnv *env, jclass)
{
	return env->NewStringUTF(FacadeModele::obtenirInstance()->obtenirInformations().c_str());
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_initialiserModeTest
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1initialiserModeTest
	(JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->initialiserModeTest();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1libererOpenGL(JNIEnv* env, jclass, jobject canvas)
///
/// Cette fonction libere le contexte OpenGL dans la fenetre identifiee
/// par le canvas AWT passe en parametre.  Cette fonction doit etre la
/// derniere a etre appelee, car elle libere egalement l'objet du modele
/// C++.
///
/// @param[in] env    : L'environnement Java.
/// @param[in] canvas : Le canvas dans lequel creer le contexte OpenGL.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1libererOpenGL
  (JNIEnv* env, jclass, jobject canvas)
{
   // Ce code verouille le canvas et ne doit donc pas etre enleve, meme s'il
   // semble inutile a premiere vue.
   JAWT_Info info(env, canvas);
   HWND hWnd = (HWND)info.getHWND();

   // On pourrait lancer une exception a la place...
   if(hWnd == 0)
      return;

   FacadeModele::obtenirInstance()->libererOpenGL();
	
	
   // Desinitialisation de la facade.  Le fait de le faire apres la
   // desinitialisation du contexte OpenGL aura pour consequence que la
   // liberation des listes d'affichages, par exemple, sera faite une fois que
   // le contexte n'existera plus, et sera donc sans effet.
   FacadeModele::libererInstance();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1dessinerOpenGL(JNIEnv* env, jclass, jobject canvas)
///
/// Cette fonction affiche la scene dans la fenetre identifiee par le
/// canvas AWT passe en parametre.
///
/// @param[in] env    : L'environnement Java.
/// @param[in] canvas : Le canvas dans lequel creer le contexte OpenGL.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1dessinerOpenGL
  (JNIEnv* env, jclass, jobject canvas, jboolean enPause)
{
   // Ce code verouille le canvas et ne doit donc pas etre enleve, meme s'il
   // semble inutile a premiere vue.
   JAWT_Info info(env, canvas);
   HWND hWnd = (HWND)info.getHWND();

   if(hWnd == 0)
      return;

   // Affiche la scene.
   FacadeModele::obtenirInstance()->afficher(enPause);

   // Temporaire: pour detecter les erreurs OpenGL
   aidegl::verifierErreurOpenGL();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1redimensionnerFenetre(JNIEnv*, jclass, jint largeur, jint hauteur)
///
/// Cette fonction doit etre appelee lorsque la fenetre est
/// redimensionnee afin d'ajuster les parametres de la machine a etats
/// d'OpenGL pour correspondre aux nouvelles dimensions de la fenetre.
///
/// @param[in] largeur : La nouvelle largeur de la fenetre.
/// @param[in] hauteur : La nouvelle hauteur de la fenetre.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1redimensionnerFenetre
  (JNIEnv*, jclass, jint largeur, jint hauteur)
{
   FacadeModele::obtenirInstance()->obtenirVue()->redimensionnerFenetre(
      Vecteur2i(0,0),
      Vecteur2i(largeur, hauteur)
      );
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1animer(JNIEnv*, jclass, jfloat temps)
///
/// Cette fonction effectue les differents calculs d'animations
/// necessaires pour le mode jeu, tel que les differents calculs de
/// physique du jeu.
///
/// @param[in] temps : Intervalle de temps sur lequel effectuer le calcul.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1animer
  (JNIEnv*, jclass, jfloat temps)
{
   FacadeModele::obtenirInstance()->animer(temps);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1zoomIn(JNIEnv*, jclass)
///
/// Cette fonction applique un zoom avant sur le present volume de vision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1zoomIn
  (JNIEnv*, jclass)
{
   FacadeModele::obtenirInstance()->obtenirVue()->zoomerIn();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1zoomOut(JNIEnv*, jclass)
///
/// Cette fonction applique un zoom arriere sur le present volume de vision.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1zoomOut
  (JNIEnv*, jclass)
{
   FacadeModele::obtenirInstance()->obtenirVue()->zoomerOut();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_InterfaceGraphique_Demarrage_obtenirAffichagesParSeconde(JNIEnv*, jclass)
///
/// Cette fonction permet d'obtenir le nombre d'affichages par seconde.
///
/// @return Le nombre d'affichage par seconde.
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_InterfaceGraphique_Demarrage_obtenirAffichagesParSeconde
  (JNIEnv*, jclass)
{
   return utilitaire::CompteurAffichage::obtenirInstance()->obtenirAffichagesSeconde();
}




////////////////////////////////////////////////////////////////////////
///
/// @fn JNIEXPORT jint JNICALL Java_InterfaceGraphique_Demarrage_fctC_1executerTests(JNIEnv*, jclass)
///
/// Cette fonction permet d'executer l'ensemble des tests unitaires
///
/// @return 0 si tous les tests ont reussi, 1 si au moins un test a echoue
///
////////////////////////////////////////////////////////////////////////
JNIEXPORT jint JNICALL Java_InterfaceGraphique_Demarrage_fctC_1executerTests
  (JNIEnv *, jclass)
{
   bool reussite = BancTests::obtenirInstance()->executer();

   // Visual Studio interprete le code de retour 0 comme une reussite et le code
	// de retour 1 comme un echec. Nous transmettons le code de retour a Java
	// qui le transmet directement comme code de sortie du programme.
   return reussite ? 0 : 1;
}

/**
 * Permet de recevoir l'input de l'application Java
 * @param mouseX Position en X de la souris
 * @param mouseY position en Y de la souris
 * @param boutton Boutton clique avec la souris
 * @param touche Touche appuyee avec la souris
 * @param scroll avec le wheel de la souris
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1envoyerInput
  (JNIEnv *, jclass, jint mouseX, jint mouseY, jint boutton, jint touche, jint scroll)
{
	FacadeModele::obtenirInstance()->recevoirInput(mouseX, mouseY, boutton, touche, scroll);
}

JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1setCanvasSizeMax
  (JNIEnv *, jclass, jfloat maxCanvasX, jfloat maxCanvasY)
{
	FacadeModele::obtenirInstance()->setCanvasSizeMax(maxCanvasX, maxCanvasY);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_setCommandeDeplacement
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1setCommandeDeplacement
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(DEPLACEMENT);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_setCommandeDuplication
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1setCommandeZoomLoupe
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(ZOOM);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_setCommandeDuplication
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1setCommandeDuplication
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(DUPLICATION);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_setCommandeMiseAEchelle
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1setCommandeMiseAEchelle
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(MISE_A_ECHELLE);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_setCommandeRotation
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1setCommandeRotation
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(ROTATION);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_setCommandeSelection
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1setCommandeSelection
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(SELECTION);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_setCommandeSuppression
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1setCommandeSuppression
	(JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(SUPPRESSION);	
}

JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1creerStation
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(CREATION_STATION_SPATIALE);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_creerBonus
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1creerBonus
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(CREATION_BONUS_ACCEL);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_creerPortail
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1creerPortail
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(CREATION_PORTAIL);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_creerBarriere
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1creerBarriere
  (JNIEnv *, jclass)
{
	FacadeModele::obtenirInstance()->setCommande(CREATION_BARRIERE_PROTECT);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_annulerCommande
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1annulerCommande
  (JNIEnv *, jclass){
	  FacadeModele::obtenirInstance()->setCommande(AUCUNE);
}


/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_enregistrer
 * Signature: ()V
 */
JNIEXPORT jboolean JNICALL Java_InterfaceGraphique_Demarrage_fctC_1enregistrer
  (JNIEnv *, jclass)
{
	string nomFichier = FacadeModele::obtenirInstance()->getNomCarteActuelle();
	// Si le nom ne contient pas .xml on le rajoute
	string stringXML = ".xml";
	if(nomFichier.substr(nomFichier.find_last_of(".") + 1) != "xml" ) {
		nomFichier += stringXML;
	}

	if(nomFichier == GestionnaireXML::obtenirInstance()->getNomCarteDefaut()) {
		// On ne peut pas enregistrer la carte par defaut
		return false;
	} else {
		FacadeModele::obtenirInstance()->enregistrerConfiguration(nomFichier);
		return true;
	}
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_enregistrerSous
 * Signature: (Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1enregistrerSous
  (JNIEnv *env, jclass, jstring nomFichierJava)
{
	string nomFichierC = utilitaire::obtenirChaineISO(env, nomFichierJava);
	
	// Si le nom ne contient pas .xml on le rajoute
	string stringXML = ".xml";
	if(nomFichierC.substr(nomFichierC.find_last_of(".") + 1) != "xml") {
		nomFichierC += stringXML;
	}
	string nomCarteDefaut = "carteDefaut.xml";
	// si la fin du path ne contient pas carteDefaut.xml
	// .rfind retourne npos s'il n'y a pas de match
	if(nomFichierC.rfind(nomCarteDefaut) == std::string::npos){
		FacadeModele::obtenirInstance()->enregistrerConfiguration(nomFichierC);
	} else {
		// Envoyer un message pour dire qu'on ne peu pas sauvegarder la carte par defaut?
	}
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_changerModeVue
 * Signature: (Z)V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1changerModeVue
  (JNIEnv *, jclass, jboolean estOrtho)
{
	FacadeModele::obtenirInstance()->setTypeDeVue(estOrtho);
}


/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_charger
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1charger
  (JNIEnv *env, jclass, jstring nomFichierJava)
{
	string nomFichierC = utilitaire::obtenirChaineISO(env, nomFichierJava);

	// Si le nom ne contient pas .xml on le rajoute
	string stringXML = ".xml";
	if(nomFichierC.substr(nomFichierC.find_last_of(".") + 1) != "xml") {
		nomFichierC += stringXML;
	}

	FacadeModele::obtenirInstance()->chargerConfiguration(nomFichierC);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_setProprietesZoneJeu
 * Signature: (IIII)V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1setProprietesZoneJeu
  (JNIEnv *, jclass, jint frequenceAsteroide, jint nombreStations, jint bonusAcceleration, jint coteDifficulte)
{
	Carte* carte = FacadeModele::obtenirInstance()->getCarte();
	carte->setNbMinStationASauver((unsigned int)nombreStations);
	carte->setAccelerationBonus((unsigned int)bonusAcceleration);
	carte->setDifficulte(coteDifficulte - 1);

	float frequence = frequenceAsteroide / 1000.0f;
	carte->setFrequenceAsteroides(frequence);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_getProprietesZoneJeu
 * Signature: ()[I
 */
JNIEXPORT jintArray JNICALL Java_InterfaceGraphique_Demarrage_fctC_1getProprietesZoneJeu
  (JNIEnv* env, jclass)
{
	Carte* carte = FacadeModele::obtenirInstance()->getCarte();

	jintArray result;
	result = env->NewIntArray(4);

	if (result == NULL) {
		return NULL;
	}

	jint ints[4];

	float frequenceAsteroide = carte->getFrequenceAsteroides();
	long frequence = (long)(frequenceAsteroide * 1000.0f) - 500;
	ints[0] = frequence;
	ints[1] = carte->getNbMinStationASauver();
	ints[2] = carte->getAccelerationBonus();
	ints[3] = carte->getDifficulte() + 1;

	env->SetIntArrayRegion(result, 0, 4, ints);
	return result;
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fct_setPositionAngleScale
 * Signature: (FFFFFFF)V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1setPositionAngleScale
  (JNIEnv *, jclass, jfloat posX, jfloat posY, jfloat posZ, jfloat angle, jfloat scaleX, jfloat scaleY, jfloat scaleZ)
{
	FacadeModele::obtenirInstance()->setPositionAngleScaleObjetSelectionne(posX, posY, posZ, angle, scaleX, scaleY, scaleZ);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_getPositionAngleScale
 * Signature: ()[F
 */
JNIEXPORT jfloatArray JNICALL Java_InterfaceGraphique_Demarrage_fctC_1getPositionAngleScaleType
  (JNIEnv *env, jclass cls)
{
	jfloatArray result;
	result = env->NewFloatArray(8);

	if (result == NULL) {
		return NULL;
	}

	jfloat floats[8];
	float getFloats[8];
	if (!FacadeModele::obtenirInstance()->getPositionAngleScaleTypeObjetSelectionne(getFloats)) {
		return NULL;
	}

	for (unsigned int i = 0; i < 8; i++) {
		floats[i] = getFloats[i];
	}

	env->SetFloatArrayRegion(result, 0, 8, floats);
	return result;
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_getNombreObjetsSelectionnes
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_InterfaceGraphique_Demarrage_fctC_1getNombreObjetsSelectionnes
  (JNIEnv *, jclass)
{
	return (int)FacadeModele::obtenirInstance()->getNombreObjetsSelectionnes();
}

JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1sauvegardeConfiguration
  (JNIEnv *, jclass, jint toucheJ1rot, jint toucheJ1rotAnti, jint toucheJ1man, jint toucheJ1prop, jint toucheJ1tir, jint toucheJ2rot, jint toucheJ2rotAnti, jint toucheJ2man, jint toucheJ2prop, jint toucheJ2tir,
  jdouble dureeJeu, jint ptsVieStation, jboolean apparitionAsteroide, jboolean changementMode, jboolean eclairage, jboolean cibleJoueur, jboolean cadreDepart, jboolean zonePassage, jboolean attractionPort){

	    FacadeModele::obtenirInstance()->mapCommande(J1ROT, toucheJ1rot);
		FacadeModele::obtenirInstance()->mapCommande(J1ROTANTI, toucheJ1rotAnti);
		FacadeModele::obtenirInstance()->mapCommande(J1MANOEUVRE, toucheJ1man);
		FacadeModele::obtenirInstance()->mapCommande(J1PROP, toucheJ1prop);
		FacadeModele::obtenirInstance()->mapCommande(J1TIR, toucheJ1tir);

		FacadeModele::obtenirInstance()->mapCommande(J2ROT, toucheJ2rot);
		FacadeModele::obtenirInstance()->mapCommande(J2ROTANTI, toucheJ2rotAnti);
		FacadeModele::obtenirInstance()->mapCommande(J2MANOEUVRE, toucheJ2man);
		FacadeModele::obtenirInstance()->mapCommande(J2PROP, toucheJ2prop);
		FacadeModele::obtenirInstance()->mapCommande(J2TIR, toucheJ2tir);

		AffichageDebogage::obtenirInstance()->setAfficherApparitionAsteroide(apparitionAsteroide);
		AffichageDebogage::obtenirInstance()->setAfficherChangementModeJoueurVirtuel(changementMode);
		AffichageDebogage::obtenirInstance()->setAfficherModificationEclairage(eclairage);

		AffichageDebogage::obtenirInstance()->setAfficherRayonAttraction(attractionPort);
		AffichageDebogage::obtenirInstance()->setAfficherAsteroideCible(cibleJoueur);
		AffichageDebogage::obtenirInstance()->setAfficherZonePassage(zonePassage);
		AffichageDebogage::obtenirInstance()->setAfficherCadreDepart(cadreDepart);

		GestionnaireXML::obtenirInstance()->sauvegarderConfiguration(toucheJ1prop, toucheJ1rotAnti, toucheJ1rot, toucheJ1man, toucheJ1tir,
																	 toucheJ2prop, toucheJ2rotAnti, toucheJ2rot, toucheJ2man, toucheJ2tir,
																	 dureeJeu, ptsVieStation, apparitionAsteroide, changementMode, eclairage,
																	 cibleJoueur, cadreDepart, zonePassage, attractionPort);

		FacadeModele::obtenirInstance()->setDureeJeu(dureeJeu);
		FacadeModele::obtenirInstance()->setPtsVieStation(ptsVieStation);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_chargerConfiguration
 * Signature: ()[F
 */
JNIEXPORT jfloatArray JNICALL Java_InterfaceGraphique_Demarrage_fctC_1chargerConfiguration
  (JNIEnv *env, jclass cls)
{
	int
	toucheJoueur1Propulsion, toucheJoueur1TournerGauche,
    toucheJoueur1TournerDroite, toucheJoueur1Manoeuvre,
    toucheJoueur1Tir, toucheJoueur2Propulsion,
    toucheJoueur2TournerGauche, toucheJoueur2TournerDroite,
    toucheJoueur2Manoeuvre, toucheJoueur2Tir,
    pointsDeVieStation;

	double dureeJeu;

	bool apparitionAsteroide, changementMode, eclairage, cibleJoueur,
		 cadreDepart, zonePassage, attractionPort, fichierExiste;

	GestionnaireXML::obtenirInstance()->chargerConfiguration(toucheJoueur1Propulsion, toucheJoueur1TournerGauche,
															 toucheJoueur1TournerDroite, toucheJoueur1Manoeuvre,
															 toucheJoueur1Tir, toucheJoueur2Propulsion,
															 toucheJoueur2TournerGauche, toucheJoueur2TournerDroite,
															 toucheJoueur2Manoeuvre, toucheJoueur2Tir, 
															 dureeJeu, pointsDeVieStation, apparitionAsteroide,
															 changementMode, eclairage, cibleJoueur,
															 cadreDepart, zonePassage, attractionPort, fichierExiste );

	jfloatArray result;
	result = env->NewFloatArray(20);

	if (result == NULL) {
		return NULL;
	}

	jfloat floats[20];
	floats[0] = (jfloat)toucheJoueur1Propulsion;
	floats[1] = (jfloat)toucheJoueur1TournerGauche;
	floats[2] = (jfloat)toucheJoueur1TournerDroite;
	floats[3] = (jfloat)toucheJoueur1Manoeuvre;
	floats[4] = (jfloat)toucheJoueur1Tir;
	floats[5] = (jfloat)toucheJoueur2Propulsion;
	floats[6] = (jfloat)toucheJoueur2TournerGauche;
	floats[7] = (jfloat)toucheJoueur2TournerDroite;
	floats[8] = (jfloat)toucheJoueur2Manoeuvre;
	floats[9] = (jfloat)toucheJoueur2Tir;
	floats[10] = (jfloat)dureeJeu;
	floats[11] = (jfloat)pointsDeVieStation;
	floats[12] = (jfloat)apparitionAsteroide;
	floats[13] = (jfloat)changementMode;
	floats[14] = (jfloat)eclairage;
	floats[15] = (jfloat)cibleJoueur;
	floats[16] = (jfloat)cadreDepart;
	floats[17] = (jfloat)zonePassage;
	floats[18] = (jfloat)attractionPort;
	floats[19] = (jfloat)fichierExiste;

	env->SetFloatArrayRegion(result, 0, 20, floats);
	return result;

}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_sauvegardeCampagne
 * Signature: (II[Ljava/lang/Object;)V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1sauvegardeCampagne
  (JNIEnv * env, jclass, jint coop, jint joueur2, jobjectArray listeCarte){;

	vector<string> listeDeCarte;
	unsigned int nbCartes = env->GetArrayLength(listeCarte); // Obtenir le nombre de cartes

	for (unsigned int i = 0; i < nbCartes; i++) // Parcourir chacun des noms de carte
	{
		// Convertir en string le nom de la carte et l'inserer dans le vecteur
		jstring nomCarte = (jstring) env->GetObjectArrayElement(listeCarte, i);
		listeDeCarte.push_back(utilitaire::obtenirChaineISO(env, nomCarte));
	}
	
	GestionnaireXML::obtenirInstance()->sauvegarderConfigCampagne(coop, joueur2, listeDeCarte);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_chargerCampagne
 * Signature: ()[Ljava/lang/String;

 */
JNIEXPORT jobjectArray JNICALL Java_InterfaceGraphique_Demarrage_fctC_1chargerCampagne
  (JNIEnv * env, jclass classC){
	  bool modeCoop, joueur2Virtuel, fichier;
	  vector<string> listeCarte;

	  GestionnaireXML::obtenirInstance()->chargerConfigCampagne( modeCoop, joueur2Virtuel, fichier, listeCarte);

	jobjectArray result;
	result = env->NewObjectArray((jsize) listeCarte.size(), classC,NULL);

	if (result == NULL) {
		return NULL;
	}
	const int size = (int) listeCarte.size();
	jobject strings;

	if(modeCoop){
		strings = env->NewStringUTF("1");
	} else {
		strings = env->NewStringUTF("0");
	}
	env->SetObjectArrayElement(result, 0, strings);

	if(joueur2Virtuel){
		strings = env->NewStringUTF("1");
	} else {
		strings = env->NewStringUTF("0");
	}
	env->SetObjectArrayElement(result, 1, strings);

	if(fichier){
		strings = env->NewStringUTF("1");
	} else {
		strings = env->NewStringUTF("0");
	}
	env->SetObjectArrayElement(result, 2, strings);

	for(int i = 3; i < size + 3; i++){
		strings = env->NewStringUTF(listeCarte[i].c_str());
		env->SetObjectArrayElement(result, i, strings);
	}

	return result;
}


/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_multipleInputVaisseau
 * Signature: ([II)V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1multipleInputVaisseau
  (JNIEnv * env, jclass, jintArray touches, jint tailleTableau)
{
	jint* arr = env->GetIntArrayElements(touches, 0);
	vector<int> touchesVaisseau;

	for (int i = 0; i < tailleTableau; i++) {
		touchesVaisseau.push_back(arr[i]);
	}

	FacadeModele::obtenirInstance()->recevoirMultipleInput(touchesVaisseau);
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_getTempsPartie
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_InterfaceGraphique_Demarrage_fctC_1getTempsPartie
  (JNIEnv *, jclass)
{
	return FacadeModele::obtenirInstance()->getTempsJeu();
}

/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_getStatutPartie
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_InterfaceGraphique_Demarrage_fctC_1getStatutPartie
  (JNIEnv *, jclass)
{
	return FacadeModele::obtenirInstance()->getStatutJeu();
}


/*
 * Class:     InterfaceGraphique_Demarrage
 * Method:    fctC_estDansLeMenuPrincipal
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1estDansLeMenuPrincipal
  (JNIEnv *, jclass)
{
	GestionnaireSon::obtenirInstance()->arreterMusique();
}


JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1allumerLumiereAmbiante
  (JNIEnv *, jclass)
{ FacadeModele::obtenirInstance()->allumerLumiereAmbiante(); }

JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1eteindreLumiereAmbiante
  (JNIEnv *, jclass)
{ FacadeModele::obtenirInstance()->eteindreLumiereAmbiante(); }

JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1allumerLumiereDiffuse
  (JNIEnv *, jclass)
{ FacadeModele::obtenirInstance()->allumerLumiereDiffuse(); }

JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1eteindreLumiereDiffuse
  (JNIEnv *, jclass)
{ FacadeModele::obtenirInstance()->eteindreLumiereDiffuse(); }

JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1allumerLumiereSpot
  (JNIEnv *, jclass)
{ FacadeModele::obtenirInstance()->allumerLumiereSpot(); }

JNIEXPORT void JNICALL Java_InterfaceGraphique_Demarrage_fctC_1eteindreLumiereSpot
  (JNIEnv *, jclass)
{ FacadeModele::obtenirInstance()->eteindreLumiereSpot(); }

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////