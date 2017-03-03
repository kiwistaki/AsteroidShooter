package InterfaceGraphique;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.MouseInfo;
import java.awt.Toolkit;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;

import javax.swing.ButtonGroup;
import javax.swing.JMenu;
import javax.swing.JLayeredPane;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.KeyStroke;

/**
 * @author Sacha L-Roussel
 * 
 *Classe qui définit l'interface d'édition du programme; Celle-ci permet de créer et d'éditer des cartes de jeux
 *composée de Station Spatiale, de vaisseaux, d'astéroïde, de barrière et de bonus.
 */
public class InterfaceEdition extends InterfaceGenerique {
	private BarreOutils barreOutils;

	private JMenuBar menuBar;
	private final ButtonGroup buttonGroup = new ButtonGroup();

	private PanelProprietes panelProprietes;
	private boolean panelProprietesShown = false;
	
	private FenetreConfigurationZoneJeu configurationZoneJeu;

	private FenetreCommune fenetre_;
	
	private JRadioButtonMenuItem  btnVueOrtho;
	private JRadioButtonMenuItem  btnVueOrbite;

	/**
	 * Constructeur par défaut de la classe InterfaceEdition.
	 * On y créer les composantes graphiques de l'interface.
	 * @param fenetreDemarrage La fenêtre de démarrage à passer pour la fenêtre
	 * de configuration de la zone de jeu
	 * @return Rien
	 */
	public InterfaceEdition(FenetreCommune fenetre) {
		fenetre_ = fenetre;
		fenetre_.reinitialiserFenetre();
		
		contentPane_ = (JLayeredPane)fenetre.getContentPane();
		canvas_ = fenetre.getCanvas();
		
		fenetre.addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(ComponentEvent arg0) {
				barreOutils.setBounds(2, contentPane_.getHeight()/2 - barreOutils.getHeight()/2 + 3, barreOutils.getWidth(), barreOutils.getHeight());

				if (panelProprietesShown) {
					panelProprietes.setBounds(contentPane_.getWidth()/2 - panelProprietes.getWidth()/2, contentPane_.getHeight() - panelProprietes.getHeight() , panelProprietes.getWidth(), panelProprietes.getHeight());
				} else {
					panelProprietes.setBounds(fenetre_.getWidth()/2 - panelProprietes.getWidth()/2, contentPane_.getHeight() - 15, panelProprietes.getWidth(), panelProprietes.getHeight());
				}
				
				redimensionnerCanvas();
			}
		});

		//Propriétés de la fenêtre
		fenetre_.setTitle("\u00C9dition");

		//Gestionnaire d'action qui fait le traitement afin d'appeler la bonne méthode parmis celles dans la classe démarrage.
		GestionnaireBoutons gestionnaire = new GestionnaireBoutons(InputManager.getInstance());
		
		//Barre d'outils ---------------------------------------------------------------
		barreOutils = new BarreOutils();
		barreOutils.setBounds(0, 0, barreOutils.getLargeurBoutons(), barreOutils.getNbBoutons()*barreOutils.getHauteurBoutons()+barreOutils.getNbBoutons());
		contentPane_.add(barreOutils);
		
		//Panel d'options ---------------------------------------------------------------
		panelProprietes = new PanelProprietes();
		panelProprietes.setEnabled(false);
		contentPane_.add(panelProprietes);
		panelProprietes.setBounds(contentPane_.getWidth()/2 - panelProprietes.getWidth()/2, fenetre_.getHeight() - panelProprietes.getHeight() , 600, 95);
		contentPane_.moveToFront(panelProprietes);
		
		//Menu Supérieur
		menuBar = new JMenuBar();
		fenetre_.setJMenuBar(menuBar);
		
		//Fichier
		JMenu menuFichier = new JMenu("Fichier");
		menuBar.add(menuFichier);

		JMenuItem btnNouveau = new JMenuItem("Nouveau");
		btnNouveau.setAccelerator(KeyStroke.getKeyStroke('N', Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
		btnNouveau.addActionListener(gestionnaire);
		btnNouveau.setActionCommand("Nouveau");
		menuFichier.add(btnNouveau);

		JMenuItem btnOuvrir = new JMenuItem("Ouvrir");
		btnOuvrir.setAccelerator(KeyStroke.getKeyStroke('O', Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
		btnOuvrir.addActionListener(gestionnaire);
		btnOuvrir.setActionCommand("Ouvrir");
		menuFichier.add(btnOuvrir);

		JMenuItem btnEnregistrer = new JMenuItem("Enregistrer");
		btnEnregistrer.setAccelerator(KeyStroke.getKeyStroke('S', Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
		btnEnregistrer.addActionListener(gestionnaire);
		btnEnregistrer.setActionCommand("Enregistrer");
		menuFichier.add(btnEnregistrer);

		JMenuItem btnEnregistrerSous = new JMenuItem("Enregistrer sous...");
		btnEnregistrerSous.addActionListener(gestionnaire);
		btnEnregistrerSous.setActionCommand("EnregistrerSous");
		menuFichier.add(btnEnregistrerSous);

		JMenuItem btnProprietes = new JMenuItem("Propriétés");
		btnProprietes.addActionListener(gestionnaire);
		btnProprietes.setActionCommand("Proprietes");
		menuFichier.add(btnProprietes);

		JMenuItem btnModeTest = new JMenuItem("Mode test");
		btnModeTest.addActionListener(gestionnaire);
		btnModeTest.setActionCommand("ModeTest");
		menuFichier.add(btnModeTest);

		JMenuItem btnMenuPrinc = new JMenuItem("Menu principal");
		btnMenuPrinc.setAccelerator(KeyStroke.getKeyStroke('Q', Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
		btnMenuPrinc.addActionListener(gestionnaire);
		btnMenuPrinc.setActionCommand("MenuPrincipal");
		menuFichier.add(btnMenuPrinc);

		//Édition
		JMenu menuEdition = new JMenu("Édition");
		menuBar.add(menuEdition);

		JMenuItem btnSupprimer = new JMenuItem("Supprimer");
		btnSupprimer.setAccelerator(KeyStroke.getKeyStroke("DELETE"));
		btnSupprimer.addActionListener(gestionnaire);
		btnSupprimer.setActionCommand("Supprimer");
		menuEdition.add(btnSupprimer);

		//Outils		
		JMenu menuOutils = new JMenu("Outils");
		menuBar.add(menuOutils);

		JMenuItem btnSelection = new JMenuItem("Sélection");
		btnSelection.addActionListener(gestionnaire);
		btnSelection.setActionCommand("Selection");
		menuOutils.add(btnSelection);

		JMenuItem btnDeplacement = new JMenuItem("Déplacement");
		btnDeplacement.addActionListener(gestionnaire);
		btnDeplacement.setActionCommand("Deplacement");
		menuOutils.add(btnDeplacement);

		JMenuItem btnRotation = new JMenuItem("Rotation");
		btnRotation.addActionListener(gestionnaire);
		btnRotation.setActionCommand("Rotation");
		menuOutils.add(btnRotation);

		JMenuItem btnMiseAEchelle = new JMenuItem("Mise à échelle");
		btnMiseAEchelle.addActionListener(gestionnaire);
		btnMiseAEchelle.setActionCommand("MiseAEchelle");
		menuOutils.add(btnMiseAEchelle);

		JMenuItem btnDuplication = new JMenuItem("Duplication");
		btnDuplication.addActionListener(gestionnaire);
		btnDuplication.setActionCommand("Duplication");
		menuOutils.add(btnDuplication);
		
		//Sous-menu création
		JMenu btnCreationObjet= new JMenu("Création");
		menuOutils.add(btnCreationObjet);

		JMenuItem btnBonusAcc = new JMenuItem("Bonus accélérateur");
		btnBonusAcc.addActionListener(gestionnaire);
		btnBonusAcc.setActionCommand("CreationBonus");
		btnCreationObjet.add(btnBonusAcc);

		JMenuItem btnPortails = new JMenuItem("Portails");
		btnPortails.addActionListener(gestionnaire);
		btnPortails.setActionCommand("CreationPortails");
		btnCreationObjet.add(btnPortails);

		JMenuItem btnBarriere = new JMenuItem("Barrière protectrice");
		btnBarriere.addActionListener(gestionnaire);
		btnBarriere.setActionCommand("CreationBarriere");
		btnCreationObjet.add(btnBarriere);

		JMenuItem btnStation = new JMenuItem("Station spatiale");
		btnStation.addActionListener(gestionnaire);
		btnStation.setActionCommand("CreationStation");
		btnCreationObjet.add(btnStation);
		//-----------------

		JMenuItem btnZoom = new JMenuItem("Zoom");
		btnZoom.addActionListener(gestionnaire);
		btnZoom.setActionCommand("Zoom");
		menuOutils.add(btnZoom);
		
		//Vues
		JMenu menuVues = new JMenu("Vues");
		menuBar.add(menuVues);

		btnVueOrtho = new JRadioButtonMenuItem ("Orthographique");
		buttonGroup.add(btnVueOrtho);
		btnVueOrtho.setSelected(true);
		btnVueOrtho.addActionListener(gestionnaire);
		btnVueOrtho.setActionCommand("ChangerVueOrthographique");
		menuVues.add(btnVueOrtho);

		btnVueOrbite = new JRadioButtonMenuItem ("Orbite");
		buttonGroup.add(btnVueOrbite);
		btnVueOrbite.addActionListener(gestionnaire);
		btnVueOrbite.setActionCommand("ChangerVueOrbite");
		menuVues.add(btnVueOrbite);
	
		//Informations
		JMenu menuInformations = new JMenu("Informations");
		menuBar.add(menuInformations);

		JMenuItem btnAide = new JMenuItem("Aide");
		btnAide.addActionListener(gestionnaire);
		btnAide.setActionCommand("Aide");
		menuInformations.add(btnAide);
		//---------------------------------------------------------------------------------
		
		// Fenêtre de configuration de la zone de jeu
		configurationZoneJeu = new FenetreConfigurationZoneJeu();

		definirCanvas();
		definirTailleFenetreMinimum();
	}

	/**
	 * Retourne l'instance de la barre d'outils contenue dans l'interface d'edition
	 * @param Aucuns paramètres
	 * @return barreOutils	Objet de type BarreOutils.
	 */
	public BarreOutils getBarreOutils(){
		return this.barreOutils;
	}

	/**
	 * Retourne l'instance du panel de modification des paramètres des propriétés des éléments
	 * @param Aucuns paramètres
	 * @return panelProprietes	Objet de type PanelProprietes
	 */
	public PanelProprietes getPanelProprietes(){
		return this.panelProprietes;
	}

	/**
	 * Permet de changer l'état du panel des propriétés - Cette méthode le cache si il est visible et inversement
	 * @param Aucuns paramètres
	 * @return void
	 */
	public void showPanelProprietes(boolean etat){
		if(etat){
			panelProprietesShown = true;
			panelProprietes.setLocation(contentPane_.getWidth()/2 - panelProprietes.getWidth()/2, contentPane_.getHeight() - panelProprietes.getHeight());
		}else{
			panelProprietesShown = false;
			panelProprietes.setLocation(panelProprietes.getX(), contentPane_.getHeight() - 15);
		}
	}

	public boolean isPanelProprietesShown() {
		return panelProprietesShown;
	}
	
	public void montrerConfigurationZoneJeu(boolean val) {
		configurationZoneJeu.setVisible(val);
		configurationZoneJeu.setLocation(MouseInfo.getPointerInfo().getLocation());
		configurationZoneJeu.setAlwaysOnTop(val);
		
		if (val) {
			int proprietes[] = Demarrage.fctC_getProprietesZoneJeu();
			configurationZoneJeu.setProprietes(proprietes[0], proprietes[1], proprietes[2], proprietes[3]);
		}
	}
	
	/**
	 * Méthode qui définit l'état de base du canvas de dessin
	 * @param Aucun
	 * @return void
	 */
	protected void definirCanvas() {
		canvas_.setSize(contentPane_.getWidth() - barreOutils.getWidth() - 20, (int) ((contentPane_.getWidth() - barreOutils.getWidth())/aspectRatio_));
		canvas_.setLocation(contentPane_.getWidth()/2 - canvas_.getWidth()/2, contentPane_.getHeight()/2 - canvas_.getHeight()/2);
		canvas_.setBackground(new Color(200, 20, 200));
		canvas_.setIgnoreRepaint(true); // Permet d'éviter le flickering // voir aussi la méthode dans configuration() de la classe démarrage
	}
	
	/**
	 * Méthode qui calcule et définit les dimensions minimum de la fenêtre
	 * @param Aucun
	 * @return void
	 */
	private void definirTailleFenetreMinimum() {
		int largeurMinimumFenetre = 0;
		int hauteurMinimumFenetre = 0;
		
		largeurMinimumFenetre = panelProprietes.getWidth();
		hauteurMinimumFenetre = barreOutils.getHeight() + barreOutils.getHauteurBoutons() + 15;

		fenetre_.setMinimumSize(new Dimension(largeurMinimumFenetre, hauteurMinimumFenetre));
	}
	
	/**
	 * Méthode qui calcule les nouvelles dimensions
	 * @param Aucun
	 * @return void
	 */
	protected void redimensionnerCanvas() {
		int newCanvasWidth = 0;
		int newCanvasHeight = 0;

		//On calcul la nouvelle taille en respectant le ratio d'aspect selon la largeur de la fenêtre
		newCanvasWidth = contentPane_.getWidth() - barreOutils.getWidth() - 10;
		newCanvasHeight = (int) (newCanvasWidth/aspectRatio_);

		//On vérifie si l'état courant fait en sorte de faire dépasser le canvas de la fenetre, si oui on modifie le
		//changement afin de calculer le ration d'aspect selon la hauteur de la fenêtre.
		if (newCanvasHeight + 10 > contentPane_.getHeight()) {
			newCanvasHeight = contentPane_.getHeight() - 10;
			newCanvasWidth = (int) (newCanvasHeight*aspectRatio_);
		}

		canvas_.setSize(newCanvasWidth, newCanvasHeight);
		canvas_.setLocation(contentPane_.getWidth()/2 + barreOutils.getWidth()/2 - canvas_.getWidth()/2, contentPane_.getHeight()/2 - canvas_.getHeight()/2);

		Demarrage.fctC_redimensionnerFenetre(newCanvasWidth, newCanvasHeight);
	}
	
	public void run(float temps) {						
		int scroll = envoyerInput();
		
		int key = InputManager.getInstance().getCurrentPressedKey();
		
		// A savoir comment verifier les combinaisons de Key
		if(scroll < 0 || key == KeyEvent.VK_EQUALS){
			Demarrage.fctC_zoomIn();
		} else if (scroll > 0 || key == KeyEvent.VK_MINUS){
			Demarrage.fctC_zoomOut();
		}
		
		Demarrage.fctC_animer(temps);
		Demarrage.fctC_dessinerOpenGL(canvas_, false);
		
		//Permet de se servir du panel de configuration des objets individuels
		if (Demarrage.fctC_getNombreObjetsSelectionnes() == 1) {
			InputManager.getInstance().setParametrePanneauConfig();
			getPanelProprietes().setEnabled(true);
			
			if(!isPanelProprietesShown())
				showPanelProprietes(true);
		} else {
			getPanelProprietes().setEnabled(false);
			
			if (isPanelProprietesShown())
				showPanelProprietes(false);
		}
	}
	
	@Override
	public void setBoutonOrtho(boolean estOrtho){
		
		btnVueOrbite.setSelected(!estOrtho);
		btnVueOrtho.setSelected(estOrtho);
	
	}

	@Override
	public void resetButtons(){
		barreOutils.getButtonGroup().clearSelection();
	}
}
