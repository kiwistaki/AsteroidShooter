package InterfaceGraphique;

import java.awt.Canvas;
import java.awt.MouseInfo;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.awt.event.MouseMotionListener;
import java.awt.event.MouseWheelEvent;
import java.awt.event.MouseWheelListener;
import java.io.File;
import java.io.IOException;
import java.util.HashSet;

import javax.swing.JDialog;
import javax.swing.JOptionPane;
import javax.swing.JFileChooser;
import javax.swing.filechooser.FileNameExtensionFilter;
import javax.swing.filechooser.FileView;
import javax.swing.Timer;

import java.net.URL;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.UnsupportedAudioFileException;

public class InputManager implements MouseListener, KeyListener, MouseWheelListener, MouseMotionListener {

	private static InputManager	singleton_ = null;
	private int 				currentClickedMouseButton_;
	private int					currentPressedMouseButton_;
	private int					currentScrolledMouseWheel_;
	private int					currentTypedKey_;
	private int					currentPressedKey_;
	private Canvas				canvas_;
	private Demarrage			fenetreDemarrage_;
	private boolean				montrerConfigurationZoneJeu_;
	private boolean				modePause_;
	private boolean				estOrtho_;
	private HashSet<Integer>	keysPressed_;

	private FenetreConfigurationCampagne fcc_; // YOLO

	public int					coop_ = 0;
	public int					joueur2_ = 0;
	public String				nomFichier_ = "";

	private boolean				lumiereAmbianteAllumee_ = true;
	private boolean				lumiereDiffuseAllumee_ = true;
	private boolean				lumiereSpotAllumee_ = true;
	
	private Clip clip;

	private InputManager() {
		currentClickedMouseButton_ = currentPressedMouseButton_ = -1;
		currentTypedKey_ = currentPressedKey_ = -1;
		currentScrolledMouseWheel_ = 0;
		montrerConfigurationZoneJeu_ = false;
		modePause_ = false;
		estOrtho_ = true;
		keysPressed_ = new HashSet<Integer>();
		contructSon();
	}

	public static InputManager getInstance() {
		if (singleton_ == null) {
			singleton_ = new InputManager();
		}

		return singleton_;
	}

	/**
	 * Permet d'ajouter les listeners au Canvas
	 */
	public void attachToCanvas(Canvas canvas) {
		canvas_ = canvas;
		canvas_.addMouseListener(this);
		canvas_.addKeyListener(new GestionnaireClavier(this));
		canvas_.addMouseWheelListener(this);
		canvas_.addMouseMotionListener(this);
	}

	/**
	 * Réinitialise les touches appuyées
	 */
	public void clearTouchesAppuyees() {
		keysPressed_.clear();
	}

	/**
	 * Permet de lier la fenetre de démarrage au InputManager, permettant ainsi de manipuler les fenetres.
	 * @param fenetre
	 */
	public void setMainWindow(Demarrage fenetre){
		fenetreDemarrage_ = fenetre;
	}

	/**
	 * Permet de vérifier si une touche du clavier a été appuyée puis relâchée
	 * @param key La touche que l'on veut vérifier
	 * @return true si elle a été appuyée puis relâchée, false sinon
	 */
	public boolean isKeyTyped(int key) {
		return (key == currentTypedKey_);
	}

	/**
	 * Permet de vérifier si une touche du clavier a été appuyée
	 * @param key La touche que l'on veut vérifier
	 * @return true si elle a été appuyée, false sinon
	 */	
	public boolean isKeyPressed(int key) {
		return (key == currentPressedKey_);
	}

	/**
	 * Permet de vérifier si un bouton de la souris a été appuyée puis relâchée
	 * @param button Le bouton que l'on veut vérifier
	 * @return true si elle a été appuyée puis relâchée, false sinon
	 */		
	public boolean isMouseButtonPressed(int button) {
		return (button == currentPressedMouseButton_);
	}

	/**
	 * Permet de vérifier si un bouton de la souris a été appuyée
	 * @param button Le bouton que l'on veut vérifier
	 * @return true si elle a été appuyée, false sinon
	 */		
	public boolean isMouseButtonClicked(int button) {
		return (button == currentClickedMouseButton_);
	}

	/**
	 * Retourne la position courante de la souris
	 */
	public Point getMousePosition() {
		Point mousePosition = MouseInfo.getPointerInfo().getLocation();
		int x = mousePosition.x;
		int y = mousePosition.y;

		if (canvas_ != null && canvas_.isShowing()) {
			Point canvasPosition = canvas_.getLocationOnScreen();
			x -= canvasPosition.x;
			y -= canvasPosition.y;
		}

		return new Point(x, y);
	}

	/**
	 * Retourne le scroll de la souris. Positif (vers le bas), negatif (vers le haut)
	 */
	public int getCurrentScrolledMouseWheel(){
		// Solution temporaire pour reset le currentScrolled wheel pour pas que
		// ca continue de scroll...
		int scroll = currentScrolledMouseWheel_;		
		currentScrolledMouseWheel_ = 0;
		return scroll;
	}

	/**
	 * Retourne la touche du clavier qui est présentemment appuyé
	 */
	public int getCurrentPressedKey() {
		return currentPressedKey_;
	}

	/**
	 * Retourne le boutton de la souris qui est présentemment appuyé
	 */
	public int getCurrentPressedButton() {
		return currentPressedMouseButton_;
	}

	/**
	 * Retourne toutes les touches qui sont appuyées
	 */
	public HashSet<Integer> getPressedKeys() {
		return keysPressed_;
	}

	@Override
	public void keyTyped(KeyEvent e) {
		currentTypedKey_ = e.getKeyCode();
	}

	@Override
	public void keyPressed(KeyEvent e) {
		int keycode = e.getKeyCode();
		currentPressedKey_ = keycode;
		keysPressed_.add(keycode);
	}

	@Override
	public void keyReleased(KeyEvent e) {
		currentTypedKey_ = currentPressedKey_ = -1;
		keysPressed_.remove(e.getKeyCode());
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		currentClickedMouseButton_ = e.getButton();
	}

	@Override
	public void mousePressed(MouseEvent e) {
		currentPressedMouseButton_ = e.getButton();

	}

	@Override
	public void mouseReleased(MouseEvent e) {
		currentClickedMouseButton_ = currentPressedMouseButton_ = -1;
	}

	@Override
	public void mouseEntered(MouseEvent e) {
	}

	@Override
	public void mouseExited(MouseEvent e) {
	}

	@Override
	public void mouseDragged(MouseEvent arg0) {
		if (fenetreDemarrage_.getModeJeu() == ModeJeu.MODE_EDITION) {
			if(Demarrage.fctC_getNombreObjetsSelectionnes() == 1 && ((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getPanelProprietes().isEnabled()){
				setParametrePanneauConfig();
			}
		}
	}

	@Override
	public void mouseMoved(MouseEvent arg0) {
	}

	/**
	 * Permet de vérifier si un scroll up ou un scroll down a ete effectue
	 * Un scroll vers le bas est un int positif, et un scroll vers le haut
	 * est un int negatif.
	 */	
	@Override
	public void mouseWheelMoved(MouseWheelEvent e) {
		currentScrolledMouseWheel_ = e.getWheelRotation();
	}


	///////////////////////////////////////
	//			         				 //
	//	Méthodes Clavier				 //
	//	Appelées par GestionnaireClavier //
	//	(Par réflexion)					 //
	//									 //
	///////////////////////////////////////

	/**
	 * Fonction appelée lorsque la touche "f" est appuyée.  Elle affiche le
	 * nombre d'affichages par seconde.
	 */
	public void appuyer_f() {
		JOptionPane.showMessageDialog(null, Demarrage.obtenirAffichagesParSeconde() + "FPS");
	}

	/**
	 * Raccourci déplacement
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_d() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(1).doClick();
	}

	/**
	 * Raccourci sélection
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_s() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(0).doClick();
	}

	/**
	 * Raccourci rotation
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_r() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(2).doClick();
	}

	/**
	 * Raccourci Mise a echelle
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_e() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(3).doClick();
	}

	/**
	 * Raccourci Duplication
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_c() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(4).doClick();
	}

	/**
	 * Raccourci Zoom
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_z() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(5).doClick();
	}

	/**
	 * Raccourci création barriere
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_m() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(8).doClick();
	}

	/**
	 * Raccourci création portail
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_p() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(9).doClick();
	}

	/**
	 * Raccourci création bonus
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_b() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(7).doClick();
	}

	/**
	 * Raccourci création station
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_g() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(6).doClick();
	}

	/**
	 * Raccourci mode test
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_t() {
		ModeTest();
	}

	/**
	 * Raccourci vue camera orthographique
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_1() {
		ChangerVueOrthographique();
	}

	/**
	 * Raccourci vue camera orbite
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_2() {
		ChangerVueOrbite();
	}

	/**
	 * Raccourci mode pause
	 * @param Aucun
	 * @return void
	 */
	public void appuyer_ESC(){
		if(modePause_){
			modePause_ = false;
		}else{
			modePause_ = true;
		}
	}

	public void appuyer_backspace() {
		if (fenetreDemarrage_.getModeJeu() == ModeJeu.MODE_TEST) {
			Demarrage.fctC_initialiserModeTest();
		} else if (fenetreDemarrage_.getModeJeu() == ModeJeu.MODE_PARTIE_RAPIDE) {
			Demarrage.fctC_initialiserModePartieRapide(coop_, joueur2_, nomFichier_);
		}
	}

	public void appuyer_j() {
		if (lumiereAmbianteAllumee_) {
			Demarrage.fctC_eteindreLumiereAmbiante();
		} else {
			Demarrage.fctC_allumerLumiereAmbiante();
		}

		lumiereAmbianteAllumee_ = !lumiereAmbianteAllumee_;
	}

	public void appuyer_k() {
		if (lumiereDiffuseAllumee_) {
			Demarrage.fctC_eteindreLumiereDiffuse();
		} else {
			Demarrage.fctC_allumerLumiereDiffuse();
		}

		lumiereDiffuseAllumee_ = !lumiereDiffuseAllumee_;
	}

	public void appuyer_l() {
		if (fenetreDemarrage_.getModeJeu() != ModeJeu.MODE_EDITION) {
			if (lumiereSpotAllumee_) {
				Demarrage.fctC_eteindreLumiereSpot();
			} else {
				Demarrage.fctC_allumerLumiereSpot();
			}

			lumiereSpotAllumee_ = !lumiereSpotAllumee_;
		}
	}

	///////////////////////////////////////
	//			         				 //
	//	Méthodes Boutons				 //
	//	Appelées par GestionnaireBoutons //
	//	(Par réflexion)					 //
	//									 //
	///////////////////////////////////////

	/**
	 * Fonction appelée lorsque l'élément PartieRapide du menu est actionné.
	 */
	public void PartieRapide() {
		modePause_ = false;

		SauvegardeConfiguration();

		Object[] optionsCoop = { "Solo", "Cooperatif" };
		coop_ = JOptionPane.showOptionDialog(fenetreDemarrage_.getMenuPrincipal(),
				"Voulez-vous jouer en mode solo ou cooperatif?", 
				"Options", 
				JOptionPane.YES_NO_CANCEL_OPTION,
				JOptionPane.QUESTION_MESSAGE, 
				null,
				optionsCoop,
				optionsCoop[1]);

		if (coop_ != JOptionPane.CLOSED_OPTION) {
			if (coop_ == 1) {
				Object[] optionsVirtuel = { "Humain", "Virtuel" } ;
				joueur2_ = JOptionPane.showOptionDialog(fenetreDemarrage_.getMenuPrincipal(),
						"Voulez-vous que le joueur 2 soit contrôlé par un humain ou par un joueur virtuel?", 
						"OptionJoueur2", 
						JOptionPane.YES_NO_CANCEL_OPTION,
						JOptionPane.QUESTION_MESSAGE, 
						null,
						optionsVirtuel,
						optionsVirtuel[1]);	
			} 

			if (joueur2_ != JOptionPane.CLOSED_OPTION) {

				String property = System.getProperty("user.dir");
				JFileChooser fenetreFichier = new JFileChooser(property + "/zones");
				fenetreFichier.setFileView(new FileView() {
					@Override
					public Boolean isTraversable(File f) {
						return (f.isDirectory() && f.getName().equals("zones"));
					}
				});

				fenetreFichier.setFileFilter(new FileNameExtensionFilter("Cartes PolyAstéroïdes (.xml)", "xml"));

				int valeurRetour = fenetreFichier.showOpenDialog(null);
				if (valeurRetour == JFileChooser.APPROVE_OPTION) {
					nomFichier_ = fenetreFichier.getSelectedFile().getPath();
				}

				if (nomFichier_ == null || (nomFichier_ != null && ("".equals(nomFichier_)))) {
					//Si l'entrée est vide ou null, on fait rien...
					//fenetreDemarrage_.setModeJeu(ModeJeu.MODE_PARTIE_RAPIDE);
				} else {
					fenetreDemarrage_.constructionFenetrePartieRapide();
					fenetreDemarrage_.getFenetreJeu().resetPosition();
					fenetreDemarrage_.getFenetreJeu().setVisible(true);
					fenetreDemarrage_.getMenuPrincipal().setVisible(false);

					Demarrage.fctC_initialiserModePartieRapide(coop_, joueur2_, nomFichier_);

					fenetreDemarrage_.setModeJeu(ModeJeu.MODE_PARTIE_RAPIDE);
				}	
			}
		}
	}

	/**
	 * Fonction appelée lorsque l'élément Campagne du menu est actionné.
	 */
	public void Campagne() {
		modePause_ = false;

		SauvegardeConfiguration();
		fcc_ = new FenetreConfigurationCampagne();
		//String[] config = Demarrage.fctC_chargerCampagne();
		/*if((String)config[3] != "0"){
			int coop = Integer.parseInt((String)config[0]);
			int joueur2= Integer.parseInt((String)config[1]);
			String[] carte = new String[config.length-3];
			for(int i = 3; i < config.length;i++){
				carte[i-3] = (String)config[i];
			}
			fcc_.setModeCoop(coop);
			fcc_.setJoueur2Virtuel(joueur2);
			fcc_.setCartesCampagne(carte);
		}*/
		fenetreDemarrage_.getMenuPrincipal().setVisible(false);
		fcc_.setVisible(true);
	}

	/**
	 * Fonction appelée lorsque la configuration de la campagne est terminée
	 */
	public void ConfigurationCampagne() {
		Object[] cartes = fcc_.getListeCartesChoisies();

		if (cartes.length > 0) {
			fcc_.setVisible(false);
			fenetreDemarrage_.constructionFenetreCampagne();
			fenetreDemarrage_.getFenetreJeu().resetPosition();
			fenetreDemarrage_.getFenetreJeu().setVisible(true);

			int coop = fcc_.getModeCoop();
			int joueur2 = fcc_.getJoueur2Virtuel();

			Demarrage.fctC_initialiserModeCampagne(coop, joueur2, cartes);

			JOptionPane pane = new JOptionPane(Demarrage.fctC_obtenirInformationsPartie(), JOptionPane.INFORMATION_MESSAGE);
			final JDialog dialog = pane.createDialog("Informations sur la prochaine partie");

			Timer timer = new Timer(5000, new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent arg0) {
					dialog.setVisible(false);
					dialog.dispose();
				}
			});
			timer.setRepeats(false);
			timer.start();

			dialog.setVisible(true);

			fenetreDemarrage_.setModeJeu(ModeJeu.MODE_CAMPAGNE);
			//Demarrage.fctC_sauvegardeCampagne(coop, joueur2, cartes);
		} else {
			JOptionPane.showMessageDialog(null, "Vous devez choisir au moins une carte pour commencer la campagne.");
		}
	}

	/**
	 * Fonction appelée lorsque l'élément Nouveau du menu est actionné.
	 */
	public void Nouveau() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().resetButtons();
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getPanelProprietes().resetValue();
		Demarrage.fctC_charger("zones/carteDefaut");
	}

	/**
	 * Fonction appelée lorsque l'élément Ouvrir du menu est actionné.
	 */
	public void Ouvrir() {

		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().resetButtons();

		String nomFichier = "";

		String property = System.getProperty("user.dir");
		JFileChooser fenetreFichier = new JFileChooser(property + "/zones");
		fenetreFichier.setFileView(new FileView() {
			@Override
			public Boolean isTraversable(File f) {
				return (f.isDirectory() && f.getName().equals("zones"));
			}
		});

		fenetreFichier.setFileFilter(new FileNameExtensionFilter("Cartes PolyAstéroïdes (.xml)", "xml"));

		int valeurRetour = fenetreFichier.showOpenDialog(null);
		if (valeurRetour == JFileChooser.APPROVE_OPTION) {
			nomFichier = fenetreFichier.getSelectedFile().getPath();
		}

		if(nomFichier == null || (nomFichier != null && ("".equals(nomFichier))))   
		{
			//Si l'entrée est vide ou null, on fait rien...
		}else{
			Demarrage.fctC_charger(nomFichier);
		}

	}

	/**
	 * Fonction appelée lorsque l'élément Enregistrer du menu est actionné.
	 */
	public void Enregistrer() {
		if (!Demarrage.fctC_enregistrer()) {
			// Si on essaie d'enregistrer la carte par defaut on demande a l'utilisateur d'entrer un nom de carte différent
			EnregistrerSous();
		} else {
			// La carte est enregistré normalement
		}
	}

	/**
	 * Fonction appelée lorsque l'élément EnregistrerSous du menu est actionné.
	 */
	public void EnregistrerSous() {
		String nomFichier = "";

		String property = System.getProperty("user.dir");
		JFileChooser fenetreFichier = new JFileChooser(property + "/zones");
		fenetreFichier.setFileView(new FileView() {
			@Override
			public Boolean isTraversable(File f) {
				return (f.isDirectory() && f.getName().equals("zones"));
			}
		});

		fenetreFichier.setFileFilter(new FileNameExtensionFilter("Cartes PolyAstéroïdes (.xml)", "xml"));

		/*
		JFileChooser fenetreFichier = new JFileChooser();
		FileNameExtensionFilter filtre = new FileNameExtensionFilter("Cartes PolyAstéroïde (xml)", "xml");
		fenetreFichier.setFileFilter(filtre);*/
		int valeurRetour = fenetreFichier.showSaveDialog(fenetreDemarrage_.getFenetreJeu());
		if (valeurRetour == JFileChooser.APPROVE_OPTION) {
			nomFichier = fenetreFichier.getSelectedFile().getPath();
		}
		// Ouvrir un textBox et demander a l'utilisateur de donner le nom du fichier

		if(nomFichier == null || (nomFichier != null && ("".equals(nomFichier))))   
		{
			//Si l'entrée est vide ou null, on fait rien...
		}else{
			Demarrage.fctC_enregistrerSous(nomFichier);
		}
	}

	/**
	 * Fonction appelée lorsque l'élément Proprietes du menu est actionné.
	 */
	public void Proprietes() {
		montrerConfigurationZoneJeu_ = !montrerConfigurationZoneJeu_;
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).montrerConfigurationZoneJeu(montrerConfigurationZoneJeu_);
	}

	/**
	 * Fonction appelée lorsque l'élément ModeTest du menu est actionné.
	 */
	public void ModeTest() {


		startSon();
		setSelectButton(10);

		modePause_ = false;

		SauvegardeConfiguration();

		fenetreDemarrage_.constructionFenetreTest();
		//fenetreDemarrage_.getFenetreJeu().resetPosition();
		fenetreDemarrage_.getFenetreJeu().setVisible(true);
		fenetreDemarrage_.getMenuPrincipal().setVisible(false);

		Demarrage.fctC_initialiserModeTest();

		fenetreDemarrage_.setModeJeu(ModeJeu.MODE_TEST);

		if(!estOrtho_){
			ChangerVueOrbite();	
		}
		
	}

	/**
	 * Fonction appelée lorsque l'élément MenuPrincipal du menu est actionné.
	 */
	public void MenuPrincipal() {

		fenetreDemarrage_.getFenetreJeu().resetPosition();
		fenetreDemarrage_.getFenetreJeu().setVisible(false);
		fenetreDemarrage_.getFenetreConfiguration().setVisible(false);
		fenetreDemarrage_.getMenuPrincipal().setVisible(true);
		fenetreDemarrage_.setModeJeu(ModeJeu.AUCUN);
		Demarrage.fctC_estDansLeMenuPrincipal();
	}

	/**
	 * Fonction appelée lorsque l'élément Configuration du menu est actionné.
	 */
	public void Configuration() {
		fenetreDemarrage_.getFenetreJeu().setVisible(false);
		fenetreDemarrage_.getFenetreConfiguration().setVisible(true);
		fenetreDemarrage_.getMenuPrincipal().setVisible(false);
	}

	/**
	 * Fonction appelée lorsque le bouton Sauvergarder du panneau de configuration est actionné.
	 */
	public void SauvegardeConfiguration() {
		Demarrage.fctC_sauvegardeConfiguration(fenetreDemarrage_.getFenetreConfiguration().getToucheJ1Rot(),
				fenetreDemarrage_.getFenetreConfiguration().getToucheJ1RotAnti(),
				fenetreDemarrage_.getFenetreConfiguration().getToucheJ1Man(),
				fenetreDemarrage_.getFenetreConfiguration().getToucheJ1Prop(),
				fenetreDemarrage_.getFenetreConfiguration().getToucheJ1Tir(),
				fenetreDemarrage_.getFenetreConfiguration().getToucheJ2Rot(),
				fenetreDemarrage_.getFenetreConfiguration().getToucheJ2RotAnti(),
				fenetreDemarrage_.getFenetreConfiguration().getToucheJ2Man(),
				fenetreDemarrage_.getFenetreConfiguration().getToucheJ2Prop(),
				fenetreDemarrage_.getFenetreConfiguration().getToucheJ2Tir(),
				fenetreDemarrage_.getFenetreConfiguration().getDureeJeu(),
				fenetreDemarrage_.getFenetreConfiguration().getPointDeVieStation(),
				fenetreDemarrage_.getFenetreConfiguration().getCheckApparitionAsteroide(),
				fenetreDemarrage_.getFenetreConfiguration().getCheckChangementMode(),
				fenetreDemarrage_.getFenetreConfiguration().getCheckEclairage(),
				fenetreDemarrage_.getFenetreConfiguration().getCheckCibleJoueur(),
				fenetreDemarrage_.getFenetreConfiguration().getCheckCadreDepart(),
				fenetreDemarrage_.getFenetreConfiguration().getCheckZonePassage(),
				fenetreDemarrage_.getFenetreConfiguration().getCheckAttractionPortail());

		//fenetreDemarrage_.getFenetreJeu().resetPosition();
		fenetreDemarrage_.getFenetreJeu().setVisible(false);
		fenetreDemarrage_.getFenetreConfiguration().setVisible(false);
		fenetreDemarrage_.getMenuPrincipal().setVisible(true);
	}

	/**
	 * Fonction appelée lorsque l'élément FenetreEdition du menu est actionné.
	 */
	public void FenetreEdition() {
		fenetreDemarrage_.constructionFenetreEdition();
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getPanelProprietes().resetValue();
		fenetreDemarrage_.getFenetreJeu().resetPosition();
		fenetreDemarrage_.getFenetreJeu().setVisible(true);
		fenetreDemarrage_.getMenuPrincipal().setVisible(false);

		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(11).setBorder(null);
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(11).setSelected(false);

		Demarrage.fctC_initialiserModeEdition();

		fenetreDemarrage_.setModeJeu(ModeJeu.MODE_EDITION);
	}

	/**
	 * Fonction appelée lorsque l'élément Supprimer du menu est actionné.
	 */
	public void Supprimer() {
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().resetButtons();
		Demarrage.fctC_setCommandeSuppression();
	}

	/**
	 * Fonction appelée lorsque l'élément Selection du menu est actionné.
	 */
	public void Selection() {		
		startSon();
		setSelectButton(0);
		Demarrage.fctC_setCommandeSelection();
	}

	/**
	 * Fonction appelée lorsque l'élément Deplacement du menu est actionné.
	 */
	public void Deplacement() {
		startSon();
		setSelectButton(1);
		Demarrage.fctC_setCommandeDeplacement();
	}


	/**
	 * Fonction appelée lorsque l'élément Rotation du menu est actionné.
	 */
	public void Rotation() {
		startSon();
		setSelectButton(2);
		Demarrage.fctC_setCommandeRotation();
	}

	/**
	 * Fonction appelée lorsque l'élément MiseAEchelle du menu est actionné.
	 */
	public void MiseAEchelle() {
		startSon();
		setSelectButton(3);
		Demarrage.fctC_setCommandeMiseAEchelle();
	}
	/**
	 * Fonction appelée lorsque l'élément Duplication du menu est actionné.
	 */
	public void Duplication() {
		startSon();
		setSelectButton(4);
		Demarrage.fctC_setCommandeDuplication();
	}

	/**
	 * Fonction appelée lorsque l'élément Zoom du menu est actionné.
	 */
	public void Zoom() {
		startSon();
		setSelectButton(5);
		Demarrage.fctC_setCommandeZoomLoupe();
	}


	/**
	 * Fonction appelée lorsque l'élément CreationBonus du menu est actionné.
	 */
	public void CreationBonus() {
		startSon();
		setSelectButton(7);
		Demarrage.fctC_creerBonus();
	}

	/**
	 * Fonction appelée lorsque l'élément CreationPortails du menu est actionné.
	 */
	public void CreationPortails() {
		startSon();
		setSelectButton(9);
		Demarrage.fctC_creerPortail();
	}

	/**
	 * Fonction appelée lorsque l'élément CreationBarriere du menu est actionné.
	 */
	public void CreationBarriere() {
		startSon();
		setSelectButton(8);
		Demarrage.fctC_creerBarriere();
	}

	/**
	 * Fonction appelée lorsque l'élément CreationStation du menu est actionné.
	 */
	public void CreationStation() {
		startSon();
		setSelectButton(6);
		Demarrage.fctC_creerStation();
	}

	/**
	 * Fonction appelée lorsque l'élément ChangerVueOrbitale du menu est actionné.
	 */
	public void ChangerVueOrbite() {
		Demarrage.fctC_changerModeVue(false);
		this.resetButtons();
		estOrtho_ = false;
		

		fenetreDemarrage_.getInterfaceJeu().setBoutonOrtho(estOrtho_);
	}

	/**
	 * Fonction appelée lorsque l'élément ChangerVueOrthographique du menu est actionné.
	 */
	public void ChangerVueOrthographique() {
		Demarrage.fctC_changerModeVue(true);
		estOrtho_ = true;
		this.resetButtons();
		fenetreDemarrage_.getInterfaceJeu().setBoutonOrtho(estOrtho_);
	}

	/**
	 * Fonction appelée lorsque l'élément Quitter du menu est actionné.
	 */
	public void Quitter() {

		System.exit(0);
		Demarrage.fctC_estDansLeMenuPrincipal();
	}

	/**
	 * Fonction appelée lorsque le bouton Aide de la barre d'outils est actionné.
	 */
	public void Aide() {
		fenetreDemarrage_.getFenetreInstructions().setVisible(true);
	}

	public void setParametrePanneauConfig(){
		PanelProprietes panel = ((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getPanelProprietes();
		panel.updateParameters();
	}

	public void fermerConfigurationZoneJeu() {
		montrerConfigurationZoneJeu_ = false;
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).montrerConfigurationZoneJeu(montrerConfigurationZoneJeu_);
	}

	private void setSelectButton(int pos){
		((InterfaceEdition) fenetreDemarrage_.getInterfaceJeu()).getBarreOutils().getButton(pos).setSelected(true);
	}

	public boolean getModePause(){ 
		return modePause_;
	}
	
   private void contructSon() {
	   
	      try {
	         URL url = this.getClass().getClassLoader().getResource("Sons/click.wav");
	         AudioInputStream audioIn = AudioSystem.getAudioInputStream(url);
	         clip = AudioSystem.getClip();
	         clip.open(audioIn);
	      } catch (UnsupportedAudioFileException e) {
	         e.printStackTrace();
	      } catch (IOException e) {
	         e.printStackTrace();
	      } catch (LineUnavailableException e) {
	         e.printStackTrace();
	      }
   }
   
   private void startSon(){

	   clip.setMicrosecondPosition(0);
	   clip.start();
   }
   
   public void resetButtons(){
	   fenetreDemarrage_.resetButtons(); 

	    if (fenetreDemarrage_.getModeJeu() == ModeJeu.MODE_EDITION) {
	    	Demarrage.fctC_annulerCommande();
	    }
   
   }
   
   
}
