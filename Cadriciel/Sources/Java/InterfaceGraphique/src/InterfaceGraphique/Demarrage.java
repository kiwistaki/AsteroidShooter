package InterfaceGraphique;

import java.awt.Canvas;
import java.awt.EventQueue;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.lang.reflect.InvocationTargetException;
import java.util.Timer;
import java.util.TimerTask;
import javax.swing.SwingUtilities;

public class Demarrage implements Runnable {

	private MenuPrincipal 					menuPrincipal;
	private Instructions 					fenetreInstructions;
	private FenetreConfigurationDiverses 	fenetreConfiguration;
	private FenetreCommune 					fenetreCommune;
	private InterfaceGenerique 				interfaceGenerique;
	private ModeJeu							modeJeu = ModeJeu.AUCUN;

	static private final int 				TEMPS_INTER_AFFICHAGE = 20;

	/**
	 * M�thode d'ex�cution principale
	 * @param Aucuns param�tres
	 * @return void 
	 */
	public static void main(String args[]){

		// Tests unitaires
		if (args.length >= 1 && args[0].equals("testsC++")) {

			// Ex�cution des tests C++
			int resultat = fctC_executerTests();
			System.exit(resultat);

		} else {
			// Cr�ation de l'unique instance du contr�leur
			final Demarrage instance = new Demarrage();

			// Cr�ation et affichage de la fen�tre principale
			EventQueue.invokeLater(instance);
		}
	}

	public Demarrage() {
		super();
	}

	/**
	 * D�marrage du thread principale
	 * @param Aucuns param�tres
	 * @return void
	 */
	@Override
	public void run() {
		configurationEnvironnement();
		fctC_initialiser();
		constructionFenetres();
		InputManager.getInstance().setMainWindow(this);
		activerMinuterie();
	}

	/**
	 * Retourne l'interface courante du jeu
	 */
	public InterfaceGenerique getInterfaceJeu() {
		return interfaceGenerique;
	}

	/**
	 * M�thode priv�e permettant d'effectuer la configuration des param�tres d'OpenGL et du Canvas
	 * @param Aucuns param�tres
	 * @return void
	 */
	private void configurationOpenGL(){
		fctC_initialiserOpenGL(fenetreCommune.getCanvas());
	}

	/**
	 * M�thode priv�e permettant d'effectuer des modifications g�n�rales sur l'environnement Java / Am�lioration Performances
	 * @param Aucuns param�tres
	 * @return void
	 */
	private void configurationEnvironnement(){
		System.setProperty("sun.java2d.noddraw", Boolean.TRUE.toString()); //Am�liore la performance de Java Swing/Repaint �NORM�MENT
		//System.setProperty("awt.useSystemAAFontSettings","on");
		//System.setProperty("swing.aatext", "true");

		System.setProperty("sun.awt.noerasebackground", "true"); // Permet d'�viter les flickers dans le canvas lors du repositionnement/redimensionnement.

	}

	/**
	 * M�thode priv�e permettant de construire les fen�tres nec�ssaires au programme
	 * @param Aucuns param�tres
	 * @return void
	 */
	private void constructionFenetres() {
		menuPrincipal = new MenuPrincipal();
		menuPrincipal.setVisible(true);

		fenetreInstructions = new Instructions();
		fenetreInstructions.setVisible(false);

		fenetreConfiguration = new FenetreConfigurationDiverses();
		fenetreConfiguration.setVisible(false);
		
		fenetreCommune = new FenetreCommune();
		fenetreCommune.setVisible(false);
		fenetreCommune.pack();

		configurationOpenGL();

		InputManager.getInstance().attachToCanvas(fenetreCommune.getCanvas());
		
		float[] config = fctC_chargerConfiguration();
		if((int)config[19] != 0){
			fenetreConfiguration.setToucheJ1Prop((int)config[0]);
			fenetreConfiguration.setToucheJ1RotAnti((int)config[1]);
			fenetreConfiguration.setToucheJ1Rot((int)config[2]);
			fenetreConfiguration.setToucheJ1Man((int)config[3]);
			fenetreConfiguration.setToucheJ1Tir((int)config[4]);
			
			fenetreConfiguration.setToucheJ2Prop((int)config[5]);
			fenetreConfiguration.setToucheJ2RotAnti((int)config[6]);
			fenetreConfiguration.setToucheJ2Rot((int)config[7]);
			fenetreConfiguration.setToucheJ2Man((int)config[8]);
			fenetreConfiguration.setToucheJ2Tir((int)config[9]);
			
			fenetreConfiguration.setDureeJeu(config[10]);
			fenetreConfiguration.setPointDeVieStation((int)config[11]);
			
			fenetreConfiguration.setApparitionAsteroide((int)config[12]);
			fenetreConfiguration.setChangementMode((int)config[13]);
			fenetreConfiguration.setEclairage((int)config[14]);
			fenetreConfiguration.setCibleJoueur((int)config[15]);
			fenetreConfiguration.setCadreDepart((int)config[16]);
			fenetreConfiguration.setZonePassage((int)config[17]);
			fenetreConfiguration.setAttractionPort((int)config[18]);
		}
	}

	public void constructionFenetreEdition() {
		interfaceGenerique = new InterfaceEdition(fenetreCommune);
		fenetreCommune.pack();
		fenetreCommune.getCanvas().requestFocus();
	}

	public void constructionFenetrePartieRapide() {
		interfaceGenerique = new InterfacePartieRapide(fenetreCommune);
		fenetreCommune.pack();
		fenetreCommune.getCanvas().requestFocus();
	}
	
	public void constructionFenetreCampagne() {
		interfaceGenerique = new InterfaceCampagne(fenetreCommune);
		fenetreCommune.pack();
		fenetreCommune.getCanvas().requestFocus();
	}

	public void constructionFenetreTest() {
		interfaceGenerique = new InterfaceTest(fenetreCommune);
		fenetreCommune.getCanvas().requestFocus();
	}

	/**
	 * M�thode priv�e permettant de configurer localement des �couteurs d'�v�nements de fen�tres
	 * @param Aucuns param�tres
	 * @return void
	 */
	private void configurationListeners() {
		fenetreCommune.addComponentListener(new ComponentAdapter() {
			@Override
			public void componentHidden(ComponentEvent arg0) {
				menuPrincipal.setVisible(true);
			}
		});			
	}

	/**
	 * Retourne l'objet de type MenuPrincipal appartenenant � cette classe
	 * @param Aucuns param�tres
	 * @return menuPrincipale	L'instance unique du menu principal de l'application
	 */
	public MenuPrincipal getMenuPrincipal() {
		return menuPrincipal;
	}

	/**
	 * Retourne l'objet de type InterfaceEdition appartenent � cette classe.
	 * @param Aucuns param�tres
	 * @return fenetre	L'instance unique de l'interface d'�dition de l'application
	 */
	public FenetreCommune getFenetreJeu() {
		return fenetreCommune;
	}

	/**
	 * Retourne l'objet de type Instructions appartenent � cette classe.
	 * @param Aucuns param�tres
	 * @return fenetreInstructions	L'instance unique de l'interface d'aide de l'application
	 */
	public Instructions getFenetreInstructions() {
		return fenetreInstructions;
	}

	public FenetreConfigurationDiverses getFenetreConfiguration() {
		return fenetreConfiguration;
	}

	public ModeJeu getModeJeu() {
		return modeJeu;
	}

	public void setModeJeu(ModeJeu mode) {
		modeJeu = mode;
	}

	/////////////////////////
	//                     //
	//  FONCTIONS NATIVES  //
	//                     //
	/////////////////////////

	/**
	 * Initialisation statique de la classe qui charge la librairie C++ contenant
	 * l'implantation des fonctions natives.
	 */
	static {
		System.loadLibrary("DLL/INF2990");
	}

	/**
	 * Fonction qui initialise un contexte OpenGL dans la fen�tre identifi�e par
	 * le canvas AWT pass� en param�tre.  Cette fonction doit �tre la premi�re �
	 * �tre appel�e, car la cr�ation de l'objet du mod�le C++ s'attend � avoir un
	 * contexte OpenGL valide.
	 *
	 * @param   canvas   Le canvas dans lequel cr�er le contexte OpenGL.
	 */
	public static native void fctC_initialiserOpenGL( Canvas canvas );

	/**
	 * Initialise le jeu (arbre de rendu)
	 */
	public static native void fctC_initialiser();

	/**
	 * Initialise le mode �dition
	 */
	public static native void fctC_initialiserModeEdition();

	/**
	 * Initialise le mode partie rapide
	 */
	public static native void fctC_initialiserModePartieRapide(int coop, int joueur2, String nomFichier);
	
	/**
	 * Initialise le mode campagne
	 */
	public static native void fctC_initialiserModeCampagne(int coop, int joueur2, Object[] cartes);
	
	/**
	 * Methode qui obtient un string des informations sur la prochaine partie
	 * @return Le string d'informations
	 */
	public static native String fctC_obtenirInformationsPartie();

	/**
	 * Initialise le mode test
	 */
	public static native void fctC_initialiserModeTest();

	/**
	 * Fonction qui lib�re le contexte OpenGL dans la fen�tre identifi�e par le
	 * canvas AWT pass� en param�tre.  Cette fonction doit �tre la derni�re �
	 * �tre appel�e, car elle lib�re �galement l'objet du mod�le C++.
	 *
	 * @param   canvas   Le canvas dans lequel cr�er le contexte OpenGL.
	 */
	public static native void fctC_libererOpenGL( Canvas canvas );

	/**
	 * Fonction qui affiche la sc�ne dans la fen�tre identifi�e par le canvas AWT
	 * pass� en param�tre.
	 *
	 * @param canvas	Le canvas dans lequel cr�er le contexte OpenGL.
	 * @param enPause 	Est-ce que le jeu est en pause? (gettho)
	 */
	public static native void fctC_dessinerOpenGL( Canvas canvas, boolean enPause);

	/**
	 * Fonction qui doit �tre appel�e lorsque la fen�tre est redimensionn�e afin
	 * d'ajuster les param�tres de la machine � �tats d'OpenGL pour correspondre
	 * aux nouvelles dimensions de la fen�tre.
	 *
	 * @param   largeur   La nouvelle largeur de la fen�tre.
	 * @param   hauteur   La nouvelle hauteur de la fen�tre.
	 */
	public static native void fctC_redimensionnerFenetre(int largeur, int hauteur);

	/**
	 * Fonction qui anime le jeu d'un certain intervalle de temps.
	 * 
	 * Elle vise � �tre appel�e de nombreuses fois par seconde.  Elle effectue
	 * les diff�rents calculs de physique et effectue un affichage.
	 *
	 * @param   temps   L'intervalle de temps � utiliser pour les diff�rents
	 *                  calculs.  On vise � faire correspondre cet invervalle de
	 *                  temps au temps entre deux appels � la fonction.
	 */
	public static native void fctC_animer(float temps);

	/**
	 * Fonction qui applique un zoom avant sur le pr�sent volume de vision.
	 */
	public static native void fctC_zoomIn();

	/**
	 * Fonction qui applique un zoom arri�re sur le pr�sent volume de vision.
	 */
	public static native void fctC_zoomOut();

	/**
	 * Fonction qui retourne le nombre moyen d'affichage par secondes.
	 */
	public static native int obtenirAffichagesParSeconde();

	/**
	 * Fonction qui ex�cute les jeux de tests unitaires C++.
	 */
	public static native int fctC_executerTests();

	/**
	 * Fonction qui envoie l'input du code Java vers le C++
	 * @param x Position en x de la souris
	 * @param y Position en y de la souris
	 * @param bouton Le bouton sur lequel on a appuy� sur la souris
	 * @param touche La touche sur laquel on a appuy� sur le clavier
	 */
	public static native void fctC_envoyerInput(int x, int y, int bouton, int touche, int scroll);
	
	/**
	 * Fonction qui collecte les informations sur la largeur et la hauteur du canvas maximal
	 */
	public static native void fctC_setCanvasSizeMax(float largeurMaxCadre, float hauteurMaxCadre);


	//////////////////////////////////////////////////////////////////////////
	// Fonctions JNI pour la barre d'outils
	//////////////////////////////////////////////////////////////////////////

	/**
	 * Fonction qui demande d'utiliser la commande de d�placement
	 */
	public static native void fctC_setCommandeDeplacement();

	/**
	 * Fonction qui demande d'utiliser la commande de duplication
	 */
	public static native void fctC_setCommandeDuplication();

	/**
	 * Fonction qui demande d'utiliser la commande de zoom avec la loupe
	 */
	public static native void fctC_setCommandeZoomLoupe();

	/**
	 * Fonction qui demande d'utiliser la commande de mise � �chelle
	 */
	public static native void fctC_setCommandeMiseAEchelle();

	/**
	 * Fonction qui demande d'utiliser la commande de rotation
	 */
	public static native void fctC_setCommandeRotation();

	/**
	 * Fonction qui demande d'utiliser la commande de s�lection
	 */
	public static native void fctC_setCommandeSelection();

	/**
	 * Fonction qui demande d'utiliser la commande de suppression
	 */
	public static native void fctC_setCommandeSuppression();

	/**
	 * Fonction qui permet de creer un BonusAccelerateur.
	 */
	public static native void fctC_creerBonus();

	/**
	 * Fonction qui permet de creer un Portail.
	 */
	public static native void fctC_creerPortail();

	/**
	 * Fonction qui permet de creer une Barriere.
	 */
	public static native void fctC_creerBarriere();

	/**
	 * Fonction qui permet de creer une station.
	 */
	public static native void fctC_creerStation();

	/**
	 * Fontion qui permet de remettre la commande � AUCUNE
	 */
	public static native void fctC_annulerCommande();
	/**
	 * Fonction qui permet d'enregistrer sous le nom courrant
	 */
	public static native boolean fctC_enregistrer();

	/**
	 * Fonction qui permet d'enregistrer dans un nouveau fichier
	 */
	public static native void fctC_enregistrerSous(String nomFichier);
	
	/**
	 * Fonction qui permet de modifier le type de vue en cours.
	 */
	public static native void fctC_changerModeVue(boolean estOrtho);

	/**
	 * Fonction qui sauvegarde les configurations de jeu
	 */
	public static native void fctC_sauvegardeConfiguration(int toucheJ1rot, int toucheJ1rotAnti, int toucheJ1man, int toucheJ1prop, int toucheJ1tir,
			int toucheJ2rot, int toucheJ2rotAnti, int toucheJ2man, int toucheJ2prop, int toucheJ2tir,
			double dureeJeu, int ptsVieStation, boolean apparatitionAsteroide, boolean changementMode, 
			boolean eclairage, boolean cibleJoueur, boolean cadreDepart, boolean zonePassage, boolean attractionPort);
	
	/**
	 * Fonction qui charge la configuration du jeu � partir d'un fichier XML
	 * @return Un tableau de 12 floats contenant les diverses configurations du jeu.
	 * Les options d'affichage de d�bogage ne sonts pas incluses car elles ne sont
	 * pas sauvegard�es sur disque
	 */
	public static native float[] fctC_chargerConfiguration();

	/**
	 * Fonction qui permet de sauvegarder les parametres de la campagne
	 */
	public static native void fctC_sauvegardeCampagne(int coop, int joueur2, Object[] cartes);
	
	/**
	 * Fonction qui permet de charger la campagne
	 * @return Un tableau de string contenant les cartes de la campagne
	 */
	public static native String[]  fctC_chargerCampagne();
	
	/**
	 * Fonction qui permet de charger un fichier
	 */
	public static native void fctC_charger(String nomFichier);

	/**
	 * Fonction qui envoie les propri�t�s de la zone de jeu � la carte courante
	 * et qui enregistre la carte dans son fichier XML.
	 * @param frequenceAsteroide La fr�quence d'apparition des ast�ro�des, en
	 * millisecondes. La valeur minimum est de 500 (2 ast�ro�des / seconde) et la
	 * valeur maximum est de 3000 (1 ast�ro�de / 3 secondes).
	 * @param nombreStations Le nombre de stations minimum � sauver pour gagner.
	 * @param bonusAcceleration Le bonus de vitesse que donne le bonus
	 * d'acc�l�ration
	 * @param coteDifficulte La cote de difficulte de la carte, 1 �tant le plus
	 * facile et 4 le plus difficile.
	 */
	public static native void fctC_setProprietesZoneJeu(int frequenceAsteroide,
			int nombreStations,
			int bonusAcceleration,
			int coteDifficulte);

	/**
	 * Fonction qui re�oit les propri�t�s de la zone de jeu de la carte courante
	 * @return Un tableau de 4 entiers repr�sentant la fr�quence d'apparition des
	 * ast�ro�des, le nombre de stations minimum � sauver, le bonus d'acc�l�ration et
	 * la cote de difficult�, respectivement.
	 */
	public static native int[] fctC_getProprietesZoneJeu();

	/**
	 * Fonction qui permet de changer la position, l'angle de rotation et la
	 * taille de l'objet pr�sentement s�lectionn�. S'il n'y a pas d'objets
	 * s�lectionn�s ou s'il y en a plus d'un, la fonction ne fera rien.
	 * @param posX La nouvelle position en X
	 * @param posY La nouvelle position en Y 
	 * @param posZ La nouvelle position en Z
	 * @param angle Le nouvel angle de rotation
	 * @param scaleX La nouvelle taille en X
	 * @param scaleY La nouvelle taille en Y
	 * @param scaleZ La nouvelle taille en Z
	 */
	public static native void fctC_setPositionAngleScale(float posX, float posY, float posZ,
			float angle, float scaleX, float scaleY,
			float scaleZ);

	/**
	 * Fonction qui permet d'obtenir la position, l'angle de rotation et la
	 * taille de l'objet pr�sentement s�lectionn�. S'il n'y a pas d'objets
	 * s�lectionn�s ou s'il y en a plus d'un, la fonction ne fera rien.
	 * @return Un tableau de 8 floats qui contiennent, en ordre, la position
	 * en x, y et z, l'angle de rotation puis la taille en x, y et z.
	 * 
	 * Le dernier float repr�sente le type de l'objet. Il faut le convertir en
	 * int en on veut le comparer � l'enum TypeElementJeu.
	 */
	public static native float[] fctC_getPositionAngleScaleType();

	/**
	 * Fonction qui retourne le nombre d'objets s�lectionn�s
	 * @return Le nombre d'objets s�lectionn�s
	 */
	public static native int fctC_getNombreObjetsSelectionnes();
	
	/**
	 * Fonction qui retourne le nombre de secondes partie en cours
	 * @return Le nombre de secondes de la partie
	 */
	public static native int fctC_getTempsPartie();
	
	/**
	 * Fonction qui retourne un int disant si le jeu est en cours, si on a
	 * gagn� ou si on a perdu.
	 * @return -1 si on a perdu, 0 si la partie est en cours 1 si on a gagn�
	 */
	public static native int fctC_getStatutPartie();
	
	/**
	 * Fonction qui permet de savoir si l'utilisateur est dans le menue principal
	 */
	public static native void fctC_estDansLeMenuPrincipal();
	
	//////////////////////////////////////////////////////////////////////////
	// Fonctions JNI pour la modification de l'eclairage
	//////////////////////////////////////////////////////////////////////////
	/**
	 * Fonction qui permet d'allumer la lumiere ambiante
	 */
	public static native void fctC_allumerLumiereAmbiante();
	
	/**
	 * Fonction qui permet d'eteindre la lumiere ambiante
	 */
	public static native void fctC_eteindreLumiereAmbiante();
	
	/**
	 * Fonction qui permet d'allumer la lumiere diffuse
	 */
	public static native void fctC_allumerLumiereDiffuse();
	
	/**
	 * Fonction qui permet d'eteindre la lumiere diffuse
	 */
	public static native void fctC_eteindreLumiereDiffuse();

	/**
	 * Fonction qui permet d'allumer la lumiere spot
	 */
	public static native void fctC_allumerLumiereSpot();
	
	/**
	 * Fonction qui permet d'eteindre la lumiere spot
	 */
	public static native void fctC_eteindreLumiereSpot();
	
	
	
	//////////////////////////////////////////////////////////////////////////
	// Fonctions JNI pour le mouvement des vaisseaux
	//////////////////////////////////////////////////////////////////////////
	
	/**
	 * Envoie un tableau de touches appuy�es pour permettre au joueur de,
	 * par exemple, avancer et tirer en m�me temps.
	 * @param touches Un tableau d'entiers repr�sentant les touches appuy�es
	 * @param tailleTableau La taille du tableau
	 */
	public static native void fctC_multipleInputVaisseau(int[] touches, int tailleTableau);
	
	public void activerMinuterie() {
		Timer minuterie = new Timer();
		minuterie.scheduleAtFixedRate(new TimerTask() {
			public void run() {
				try {
					SwingUtilities.invokeAndWait(new Runnable() {
						public void run() {
							float temps = TEMPS_INTER_AFFICHAGE / 1000.0f;

							if (modeJeu != ModeJeu.AUCUN) {
								interfaceGenerique.run(temps);
							}
						}
					});
				}
				catch (InvocationTargetException ex) {
					ex.printStackTrace();
				}
				catch (InterruptedException ex) {
					ex.printStackTrace();
				}
			}
		}, 0, TEMPS_INTER_AFFICHAGE);
	}
	

	public void resetButtons(){
		interfaceGenerique.resetButtons();
	}
}
