//////////////////////////////////////////////////////////////////////////////
/// @file FacadeModele.h
/// @author DGI
/// @date 2005-06-15
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_FACADEMODELE_H__
#define __APPLICATION_FACADEMODELE_H__

#ifdef _DEBUG
#	define DYNAMIC_CAST dynamic_cast
#else
#	define DYNAMIC_CAST dynamic_cast
#endif

#include <windows.h>
#include <string>
#include <vector>
#include <map>
#include <memory>

#include "Vecteur.h"

#include "Carte.h"

#include "../../../Commun/Utilitaire/BoiteEnvironnement.h"
#include "../AffichageTexte/Phont.h"

class ArbreRenduINF2990;
class JeuAbstrait;
class NoeudAbstrait;

using namespace std;

namespace vue {
   class Vue;
}

enum ModeJeu_t {
	EDITION,
	PARTIE_RAPIDE,
	CAMPAGNE,
	TEST
};

/// Enum des commandes des joueur 1 et 2 pour mode jeu
enum Commandes { J1ROT, J1ROTANTI, J1MANOEUVRE, J1PROP, J1TIR, J2ROT, J2ROTANTI, J2MANOEUVRE, J2PROP, J2TIR };

///////////////////////////////////////////////////////////////////////////
/// @class FacadeModele
/// @brief Classe qui constitue une interface (une facade) sur l'ensemble
///        du modele et des classes qui le composent.
///
/// @author Martin Bisson
/// @date 2007-02-20
///////////////////////////////////////////////////////////////////////////
class FacadeModele
{
public:
   /// Obtient l'instance unique de la classe.

   static FacadeModele*				obtenirInstance();

   /// Libere l'instance unique de la classe.
   static void						libererInstance();

   /// Cree un contexte OpenGL et initialise celui-ci.
   /// @param hWnd Les parametres d'initialisation
   void								initialiserOpenGL(HWND hWnd);

   /// Charge la configuration a partir d'un fichier XML.
   /// @param nomFichier Le nom du fichier duquel charger la configuration
   void								chargerConfiguration(string nomFichier);

   /// Enregistre la configuration courante dans un fichier XML.
   /// @param nomFichier Le nom du fichier ou enregistrer la configuration
   void								enregistrerConfiguration(string nomFichier) const;

   /// Libere le contexte OpenGL.
   void								libererOpenGL();

   /// Affiche le contenu du modele.
   void								afficher(bool enPause) const;

   /// Affiche la base du contenu du modele.
   void								afficherBase() const;

   /// Initialise l'eclairage
   void								positionnerLumieres() const;

   /**
    * Permet de recevoir l'input de l'application Java
	* @param mouseX Position en X de la souris
	* @param mouseY position en Y de la souris
	* @param boutton Boutton clique avec la souris
	* @param touche Touche appuyee avec la souris
	* @param scroll Scroll avec le wheel de la souris
	*/
   void								recevoirInput(int mouseX, int mouseY, int boutton, int touche, int scroll);
	
   /// Retourne la vue courante.
   inline vue::Vue*					obtenirVue();

   /// Retourne l'arbre de rendu.
   inline const ArbreRenduINF2990*	obtenirArbreRenduINF2990() const;

   /// Retourne l'arbre de rendu.
   inline ArbreRenduINF2990*		obtenirArbreRenduINF2990();

   /**
    * Initialise les parties non graphiques (pas rapport a la fenetre)
	*/
   void								initialiser();

   /**
   * Initialise le mode edition
   */
   void								initialiserModeEdition();

   /**
    * Initialise une partie rapide
    */
   void								initialiserPartieRapide(string nomCarte, bool modeCoop, bool joueur2Virtuel);

   /**
   * Initialise la campagne
   */
   void								initialiserModeCampagne(bool modeCoop, bool joueur2Virtuel, vector<string> cartes);

   /**
   * Methode qui retourne les informations sur la prochaine partie
   * @return Le string des informations sur la prochaine partie
   */
   string							obtenirInformations();

   /**
   * Methode qui initialise la prochaine partie de la campagne
   */
   void								prochainePartie();

   /**
   * Initialise le mode test
   */
   void								initialiserModeTest();

   /// Anime la scene.
   // @param temps Le temps d'animation
   void								animer(float temps);

   /// Methode qui permet d'appeler une commande
   // @param numeroOutil Le numero de l'outil a utiliser
   void								setCommande(int numeroOutil);

   /// Methode qui permet de recuperer le nom de la carte
   string							getNomCarteActuelle();

   /**
    * Retourne la carte actuelle
	*/
   inline Carte*					getCarte();
   inline void						setCarte(Carte* carte) { carte_ = carte; }

	/**
	 * Fonction qui permet de changer la position, l'angle de rotation et la
	 * taille de l'objet presentement selectionne. S'il n'y a pas d'objets
	 * selectionnes ou s'il y en a plus d'un, la fonction ne fera rien.
	 * @param posX		La nouvelle position en X
	 * @param posY		La nouvelle position en Y 
	 * @param posZ		La nouvelle position en Z
	 * @param angle		Le nouvel angle de rotation
	 * @param scaleX	La nouvelle taille en X
	 * @param scaleY	La nouvelle taille en Y
	 * @param scaleZ	La nouvelle taille en Z
	 */
	void							setPositionAngleScaleObjetSelectionne(float posX, float posY, float posZ,
																		  float angle, float scaleX, float scaleY,
																		  float scaleZ);

	/**
	 * Retourne la position, l'angle, la taille et le type de l'objet dans un tableau de 8
	 * floats.
	 * @param floats Un tableau de floats
	 * @return true s'il n'y a qu'un seul objet selectionne, false sinon.
	 */
	bool							getPositionAngleScaleTypeObjetSelectionne(float floats[]);

	/**
	 * Retourne les touches, la dureeDeJeu et les points de vies des stations dans un tableau de 12
	 * floats.
	 * @param floats Un tableau de floats
	 */
	void							getTouchesDureeJeuPointDeVie(float floats[]);

	/**
	 * Fonction qui retourne le nombre d'objets selectionnes
	 * @return Le nombre d'objets selectionnes
	 */
	size_t							getNombreObjetsSelectionnes();

	/// Methode qui permet de map la commande a une touche spécifique pour le mode Jeu
	void							mapCommande(int commande, int touche);
	inline map<int,int>*			getMapCommandes() { return &mapCommandesJoueur_;}

	/**
	 * Permet de passer plusieurs touches pour le mouvement des joueurs
	 * @param touches Un tableau contenant toutes les touches appuyées
	 */
	void							recevoirMultipleInput(const vector<int>& touches);
	inline const vector<int>&		getTouchesAppuyees() const { return touchesAppuyees_; }

	/// Permet de recuperer le temps de jeu
	inline void						setDureeJeu(double duree) {dureeDeJeu_ = duree;}
	inline double					getDureeJeu() { return dureeDeJeu_;}

	/// Permet d'obtenir les points de vies des stations
	inline void						setPtsVieStation(int ptsVie) {ptsDeVieStation_ = ptsVie;}
	inline int						getPtsDeVieStation(){ return ptsDeVieStation_;}

	inline void						setTempsJeu(int temps) { tempsJeu_ = temps; }
	inline int						getTempsJeu() const { return tempsJeu_; }

	inline void						setStatutJeu(int statut) { statutJeu_ = statut; }
	inline int						getStatutJeu() const { return statutJeu_; }

	/// Setter les plus gros grandeur du canvas.
	void							setCanvasSizeMax(float largeurMaxCanvas, float hauteurMaxCanvas); 

	/// Méthode permettant de changer le type de vue du mode en cours
	void							setTypeDeVue(bool estOrtho);
	
	/// -------------------- METHODES D'ECLAIRAGE --------------------
	/// Methode qui permet d'activer la lumiere ambiante
	void							allumerLumiereAmbiante();

	/// Methode qui permet d'eteindre la lumiere ambiante
	void							eteindreLumiereAmbiante();

	/// Methode qui permet d'activer la lumiere diffuse
	void							allumerLumiereDiffuse();

	/// Methode qui permet d'eteindre la lumiere diffuse
	void							eteindreLumiereDiffuse();

	/// Methode qui permet d'activer la lumiere spot
	void							allumerLumiereSpot();

	/// Methode qui permet d'eteindre la lumiere spot
	void							eteindreLumiereSpot();
	/// --------------------------------------------------------------

	Phont							phontTexte_;
	Phont							phontVie_;

	inline bool						isModeEdition(){return estModeEdition_;}

	bool							isModeOrtho(){ return estOrtho_; }

private:
   /// Constructeur par defaut.
							FacadeModele();
   /// Destructeur.
							~FacadeModele();
   /// Constructeur copie.  Declare mais non defini pour eviter qu'il soit
   /// genere par le compilateur.
							FacadeModele(const FacadeModele&);
   /// Operateur d'assignation.  Declare mais non defini pour eviter qu'il
   /// soit genere par le compilateur.
   FacadeModele&			operator=(const FacadeModele&);

   /// Pointeur vers l'instance unique de la classe.
   static FacadeModele*		instance_;

   /// Poignee ("handle") vers la fenetre où l'affichage se fait.
   HWND						hWnd_;
   /// Poignee ("handle") vers le contexte OpenGL.
   HGLRC					hGLRC_;
   /// Poignee ("handle") vers le "device context".
   HDC						hDC_;

   /// Vue courante de la scene.
   vue::Vue*				vue_;
   /// Arbre de rendu contenant les differents objets de la scene.
   ArbreRenduINF2990*		arbre_;

   /** JeuAbstrait pour les differents mode de jeu */
   JeuAbstrait*				jeu_;

   /** Carte pour les elements de jeux */
   Carte*					carte_;

   float					tempsDelta_;

	/** Map des commandes des joueurs 1 et 2 : map<Commandes, touche> pour le mode Jeu*/
	map<int, int>			mapCommandesJoueur_;

	/** Tableau de touches appuyées */
	vector<int>				touchesAppuyees_;

	/// Attribut pour la duree de jeu
	double					dureeDeJeu_;

	/// Attribut des points de vies des station
	int						ptsDeVieStation_;

	/**
	 * Temps courant en seconde du jeu
	 */
	int						tempsJeu_;

	/**
	 * Statut du jeu:
	 * -1 : partie perdue
	 *  0 : partie en cours
	 *  1 : partie gagné
	 *  2 : campagne gagnée
	 */
	int						statutJeu_;

	// Le plus gros size que le canvas peut avoir en x et y
	float					canvasMaxX_;
	float					canvasMaxY_;

	// La skybox
	utilitaire::BoiteEnvironnement *skybox_;
	bool					estModeEdition_;
	bool					estOrtho_;

	// Eclairage
	bool					lumiereAmbiante_;
	bool					lumiereDiffuse_;
	bool					lumiereSpot_;
};




////////////////////////////////////////////////////////////////////////
///
/// @fn inline vue::Vue* FacadeModele::obtenirVue()
///
/// Cette fonction retourne la vue qui est presentement utilisee pour
/// voir la scene.
///
/// @return La vue courante.
///
////////////////////////////////////////////////////////////////////////
inline vue::Vue* FacadeModele::obtenirVue()
{
   return vue_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
///
/// Cette fonction retourne l'arbre de rendu de la scene (version constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scene.
///
////////////////////////////////////////////////////////////////////////
inline const ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990() const
{
   return arbre_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
///
/// Cette fonction retourne l'arbre de rendu de la scene (version non constante
/// de la fonction).
///
/// @return L'arbre de rendu de la scene.
///
////////////////////////////////////////////////////////////////////////
inline ArbreRenduINF2990* FacadeModele::obtenirArbreRenduINF2990()
{
   return arbre_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn inline Carte* FacadeModele::getCarte()
///
/// Cette fonction retourne la carte actuelle.
///
/// @return La carte du jeu.
///
////////////////////////////////////////////////////////////////////////
inline Carte* FacadeModele::getCarte() {
	return carte_;
}

#endif // __APPLICATION_FACADEMODELE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////

