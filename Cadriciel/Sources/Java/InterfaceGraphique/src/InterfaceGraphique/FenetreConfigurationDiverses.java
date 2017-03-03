package InterfaceGraphique;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.WindowEvent;
import java.util.HashSet;

import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextArea;
import javax.swing.JToggleButton;
import javax.swing.SwingConstants;
import javax.swing.WindowConstants;

import java.awt.Font;

public class FenetreConfigurationDiverses extends JFrame {

	private static final long serialVersionUID = 1L;
	private final int		DUREE_PARTIE_MIN = 30; 
	private final int		DUREE_PARTIE_MAX = 300;
	
	private final int		POINTS_VIE_MIN = 1;
	private final int		POINTS_VIE_MAX = 20;
	
	// Valeurs par défauts
	private final String 	DEFAUT_JOUEUR1_HORAIRE = "D";
	private final String 	DEFAUT_JOUEUR1_ANTIHORAIRE = "A";
	private final String 	DEFAUT_JOUEUR1_MANOEUVRE = "S";
	private final String 	DEFAUT_JOUEUR1_PROPULSION = "W";
	private final String 	DEFAUT_JOUEUR1_TIR = "Espace";
	
	private final String 	DEFAUT_JOUEUR2_HORAIRE = "6";
	private final String 	DEFAUT_JOUEUR2_ANTIHORAIRE = "4";
	private final String 	DEFAUT_JOUEUR2_MANOEUVRE = "5";
	private final String 	DEFAUT_JOUEUR2_PROPULSION = "8";
	private final String 	DEFAUT_JOUEUR2_TIR = "0"; 
	
	private final int		DEFAUT_PARTIE_DUREE = 60;
	
	private final int		DEFAUT_POINTS_VIE = 5;
	
	// Texte
	@SuppressWarnings("unused")
	private JLabel			valeurActuelle_;
	private JTextArea		valeurRotationJ1_;
	private JTextArea		valeurRotationAntiJ1_;
	private JTextArea		valeurManoeuvreJ1_;
	private JTextArea		valeurPropulsionJ1_;
	private JTextArea		valeurTirJ1_;
	private JTextArea		valeurRotationJ2_;
	private JTextArea		valeurRotationAntiJ2_;
	private JTextArea		valeurManoeuvreJ2_;
	private JTextArea		valeurPropulsionJ2_;
	private JTextArea		valeurTirJ2_;
	
	private JLabel			toucheJoueur1_;
	private JLabel			toucheJoueur2_;
	
	private JLabel 			rotationHoraire_;
	private JLabel 			rotationAntihoraire_;
	private JLabel 			manoeuvre_;
	private JLabel 			propulsion_;
	private JLabel 			tir_;
	private JLabel 			rotationHoraire2_;
	private JLabel 			rotationAntihoraire2_;
	private JLabel 			manoeuvre2_;
	private JLabel 			propulsion2_;
	private JLabel 			tir2_;
	
	private Integer 		KeyrotationHoraire_;
	private Integer 		KeyrotationAntihoraire_;
	private Integer 		Keymanoeuvre_;
	private Integer 		Keypropulsion_;
	private Integer 		Keytir_;
	private Integer 		KeyrotationHoraire2_;
	private Integer 		KeyrotationAntihoraire2_;
	private Integer 		Keymanoeuvre2_;
	private Integer 		Keypropulsion2_;
	private Integer 		Keytir2_;
	
	private JLabel			optionJeu_;
	private JLabel			dureePartie_;
	private JLabel			pointsVieStation_;
	private JSlider			sliderDureeJeu_;
	private JSlider			sliderPointVieStation_;
	
	@SuppressWarnings("unused")
	private JLabel			debogage_;
	private JLabel			affichageConsole_;
	private JLabel			identificateurs_;
	
	
	// Case pour le changement de touche de jeu
	private JToggleButton	toucheRotationHoraireJ1_;
	private JToggleButton	toucheRotationAntihoraireJ1_;
	private JToggleButton	toucheManoeuvreJ1_;
	private JToggleButton	touchePropulsionJ1_;
	private JToggleButton	toucheTirJ1_;
	private JToggleButton	toucheRotationHoraireJ2_;
	private JToggleButton	toucheRotationAntihoraireJ2_;
	private JToggleButton	toucheManoeuvreJ2_;
	private JToggleButton	touchePropulsionJ2_;
	private JToggleButton	toucheTirJ2_;
	
	// Options de débogage
	private JCheckBox		chkApparitionAsteroide_;
	private JCheckBox		chkAttractionPortail_;
	private JCheckBox		chkChangementMode_;
	private JCheckBox		chkEclairage_;
	private JCheckBox		chkCibleJoueur_;
	private JCheckBox		chkCadreDepart_;
	private JCheckBox		chkZonePassage_;
	
	// Boutons de la fenêtre
	private JButton 		btnSauvegarder_;
	private JButton 		btnDefautJ1_;
	private JButton 		btnDefautJ2_;
	
	// Composantes graphiques
	private JPanel 			contentPane;
	private GroupLayout		layout;
	
	// Attributs de la fenêtre
	private Dimension 		screenSize;
	private int				largeurEcran;
	private int				hauteurEcran;
	private int				largeurFenetre;
	private int				hauteurFenetre;
	
	private HashSet<Integer>		toucheRentrer_;
	
	final private Dimension DIMENSION_MIN_BTN = new Dimension(10,15);
	final private Dimension DIMENSION_MAX_BTN = new Dimension(40,40);
	

	final private Dimension DIMENSION_MIN_SAISIE = new Dimension(10,15);
	final private Dimension DIMENSION_MAX_SAISIE = new Dimension(6000,40);
	

	final private Dimension DIMENSION_MIN_LABEL = new Dimension(160,10);
	final private Dimension DIMENSION_MAX_LABEL = new Dimension(250,30);
	
	
	
	/**
	 * Methode qui permet l'affichage de la fenetre de configuration
	 * @param aucun
	 * @return void
	 */
	public FenetreConfigurationDiverses() {

		setDefaultCloseOperation(WindowConstants.HIDE_ON_CLOSE);
				
		// Pour revenir au menu principal
		addWindowListener(new java.awt.event.WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				InputManager.getInstance().MenuPrincipal();
			}
		});
		
		KeyrotationHoraire_ = new Integer(KeyEvent.VK_D);
		KeyrotationAntihoraire_= new Integer(KeyEvent.VK_A);
		Keymanoeuvre_= new Integer(KeyEvent.VK_S);
		Keypropulsion_= new Integer(KeyEvent.VK_W);
		Keytir_= new Integer(KeyEvent.VK_SPACE);
		KeyrotationHoraire2_= new Integer(KeyEvent.VK_NUMPAD6);
		KeyrotationAntihoraire2_= new Integer(KeyEvent.VK_NUMPAD4);
		Keymanoeuvre2_= new Integer(KeyEvent.VK_NUMPAD5);
		Keypropulsion2_= new Integer(KeyEvent.VK_NUMPAD8);
		Keytir2_= new Integer(KeyEvent.VK_NUMPAD0);
		
		//Gestionnaire d'action qui fait le traitement afin d'appeler la bonne méthode parmis celles dans la classe démarrage.
		GestionnaireBoutons gestionnaire = new GestionnaireBoutons(InputManager.getInstance());
		toucheRentrer_ = new HashSet<Integer>();
		toucheRentrer_.add(KeyrotationHoraire_);	toucheRentrer_.add(KeyrotationAntihoraire_);
		toucheRentrer_.add(Keymanoeuvre_);	toucheRentrer_.add(Keypropulsion_);
		toucheRentrer_.add(Keytir_);	toucheRentrer_.add(KeyrotationHoraire2_);
		toucheRentrer_.add(KeyrotationAntihoraire2_);	toucheRentrer_.add(Keymanoeuvre2_);
		toucheRentrer_.add(Keypropulsion2_);	toucheRentrer_.add(Keytir2_);
				
		toucheJoueur1_ = new JLabel("Touches du clavier pour le joueur 1 : ");
		toucheJoueur1_.setMinimumSize(DIMENSION_MIN_LABEL);
		toucheJoueur1_.setMaximumSize(DIMENSION_MAX_LABEL);
		toucheJoueur1_.setFont(new Font("Tahoma", Font.BOLD, 13));
		
		toucheJoueur2_ = new JLabel("Touches du clavier pour le joueur 2 : ");
		toucheJoueur2_.setMinimumSize(DIMENSION_MIN_LABEL);
		toucheJoueur2_.setMaximumSize(DIMENSION_MAX_LABEL);
		toucheJoueur2_.setFont(new Font("Tahoma", Font.BOLD, 13));
		
		valeurActuelle_ = new JLabel("Valeur Actuelle");
		valeurRotationJ1_ = new JTextArea(DEFAUT_JOUEUR1_HORAIRE);
		valeurRotationJ1_.setMinimumSize(DIMENSION_MIN_SAISIE);
		valeurRotationJ1_.setMaximumSize(DIMENSION_MAX_SAISIE);
		valeurRotationJ1_.setEnabled(false);
		valeurRotationJ1_.setBackground(Color.WHITE);
		valeurRotationJ1_.setDisabledTextColor(new Color(50,50,50));
		valeurRotationJ1_.addKeyListener(new KeyAdapter(){
			public void keyPressed (KeyEvent e){
				if(checkDoublon(e.getKeyCode(), KeyrotationHoraire_)){
					if(e.getKeyCode()== KeyEvent.VK_SPACE){
						valeurRotationJ1_.setText("Espace");
					}else{
						valeurRotationJ1_.setText((e.getKeyChar()+"").toUpperCase());
					}
				}
				KeyrotationHoraire_ = e.getKeyCode();
				valeurRotationJ1_.setEnabled(false);
				toucheRotationHoraireJ1_.setSelected(false);
				toucheRotationHoraireJ1_.setEnabled(true);
			}
		});
		valeurRotationAntiJ1_ = new JTextArea(DEFAUT_JOUEUR1_ANTIHORAIRE);
		valeurRotationAntiJ1_.setMinimumSize(DIMENSION_MIN_SAISIE);
		valeurRotationAntiJ1_.setMaximumSize(DIMENSION_MAX_SAISIE);
		valeurRotationAntiJ1_.setBackground(Color.WHITE);
		valeurRotationAntiJ1_.setEnabled(false);
		valeurRotationAntiJ1_.setDisabledTextColor(new Color(50,50,50));
		valeurRotationAntiJ1_.addKeyListener(new KeyAdapter(){
			public void keyPressed (KeyEvent e){
				if(checkDoublon(e.getKeyCode(), KeyrotationAntihoraire_)){
					if(e.getKeyChar()==' '){
						valeurRotationAntiJ1_.setText("Espace");
					}else{
						valeurRotationAntiJ1_.setText((e.getKeyChar()+"").toUpperCase());
					}
				}
				KeyrotationAntihoraire_ = e.getKeyCode();
				valeurRotationAntiJ1_.setEnabled(false);
				toucheRotationAntihoraireJ1_.setSelected(false);
				toucheRotationAntihoraireJ1_.setEnabled(true);
			}
		});
		valeurManoeuvreJ1_ = new JTextArea(DEFAUT_JOUEUR1_MANOEUVRE);
		valeurManoeuvreJ1_.setMinimumSize(DIMENSION_MIN_SAISIE);
		valeurManoeuvreJ1_.setMaximumSize(DIMENSION_MAX_SAISIE);
		valeurManoeuvreJ1_.setBackground(Color.WHITE);
		valeurManoeuvreJ1_.setEnabled(false);
		valeurManoeuvreJ1_.setDisabledTextColor(new Color(50,50,50));
		valeurManoeuvreJ1_.addKeyListener(new KeyAdapter(){
			public void keyPressed (KeyEvent e){
				if(checkDoublon(e.getKeyCode(), Keymanoeuvre_)){
					if(e.getKeyChar()==' '){
						valeurManoeuvreJ1_.setText("Espace");
					}else{
						valeurManoeuvreJ1_.setText((e.getKeyChar()+"").toUpperCase());
					}
				}
				Keymanoeuvre_ = e.getKeyCode();
				valeurManoeuvreJ1_.setEnabled(false);
				toucheManoeuvreJ1_.setSelected(false);
				toucheManoeuvreJ1_.setEnabled(true);
			}
		});
		valeurPropulsionJ1_ = new JTextArea(DEFAUT_JOUEUR1_PROPULSION);
		valeurPropulsionJ1_.setMinimumSize(DIMENSION_MIN_SAISIE);
		valeurPropulsionJ1_.setMaximumSize(DIMENSION_MAX_SAISIE);
		valeurPropulsionJ1_.setBackground(Color.WHITE);
		valeurPropulsionJ1_.setEnabled(false);
		valeurPropulsionJ1_.setDisabledTextColor(new Color(50,50,50));
		valeurPropulsionJ1_.addKeyListener(new KeyAdapter(){
			public void keyPressed (KeyEvent e){
				if(checkDoublon(e.getKeyCode(), Keypropulsion_)){
					if(e.getKeyChar()==' '){
						valeurPropulsionJ1_.setText("Espace");
					}else{
						valeurPropulsionJ1_.setText((e.getKeyChar()+"").toUpperCase());
					}
				}
				Keypropulsion_ = e.getKeyCode();
				valeurPropulsionJ1_.setEnabled(false);
				touchePropulsionJ1_.setSelected(false);
				touchePropulsionJ1_.setEnabled(true);
			}
		});
		valeurTirJ1_ = new JTextArea(DEFAUT_JOUEUR1_TIR);
		valeurTirJ1_.setMinimumSize(DIMENSION_MIN_SAISIE);
		valeurTirJ1_.setMaximumSize(DIMENSION_MAX_SAISIE);
		valeurTirJ1_.setBackground(Color.WHITE);
		valeurTirJ1_.setEnabled(false);
		valeurTirJ1_.setDisabledTextColor(new Color(50,50,50));
		valeurTirJ1_.addKeyListener(new KeyAdapter(){
			public void keyPressed (KeyEvent e){
				if(checkDoublon(e.getKeyCode(), Keytir_)){
					if(e.getKeyChar()==' '){
						valeurTirJ1_.setText("Espace");
					}else{
						valeurTirJ1_.setText((e.getKeyChar()+"").toUpperCase());
					}
				}
				Keytir_ = e.getKeyCode();
				valeurTirJ1_.setEnabled(false);
				toucheTirJ1_.setSelected(false);
				toucheTirJ1_.setEnabled(true);
			}
		});
		valeurRotationJ2_ = new JTextArea(DEFAUT_JOUEUR2_HORAIRE);
		valeurRotationJ2_.setMinimumSize(DIMENSION_MIN_SAISIE);
		valeurRotationJ2_.setMaximumSize(DIMENSION_MAX_SAISIE);
		valeurRotationJ2_.setBackground(Color.WHITE);
		valeurRotationJ2_.setEnabled(false);
		valeurRotationJ2_.setDisabledTextColor(new Color(50,50,50));
		valeurRotationJ2_.addKeyListener(new KeyAdapter(){
			public void keyPressed (KeyEvent e){
				if(checkDoublon(e.getKeyCode(), KeyrotationHoraire2_)){
					if(e.getKeyChar()==' '){
						valeurRotationJ2_.setText("Espace");
					}else{
						valeurRotationJ2_.setText((e.getKeyChar()+"").toUpperCase());
					}
				}
				KeyrotationHoraire2_ = e.getKeyCode();
				valeurRotationJ2_.setEnabled(false);
				toucheRotationHoraireJ2_.setSelected(false);
				toucheRotationHoraireJ2_.setEnabled(true);
			}
		});
		valeurRotationAntiJ2_ = new JTextArea(DEFAUT_JOUEUR2_ANTIHORAIRE);
		valeurRotationAntiJ2_.setMinimumSize(DIMENSION_MIN_SAISIE);
		valeurRotationAntiJ2_.setMaximumSize(DIMENSION_MAX_SAISIE);
		valeurRotationAntiJ2_.setBackground(Color.WHITE);
		valeurRotationAntiJ2_.setEnabled(false);
		valeurRotationAntiJ2_.setDisabledTextColor(new Color(50,50,50));
		valeurRotationAntiJ2_.addKeyListener(new KeyAdapter(){
			public void keyPressed (KeyEvent e){
				if(checkDoublon(e.getKeyCode(), KeyrotationAntihoraire2_)){
					if(e.getKeyChar()==' '){
						valeurRotationAntiJ2_.setText("Espace");
					}else{
						valeurRotationAntiJ2_.setText((e.getKeyChar()+"").toUpperCase());
					}
				}
				KeyrotationAntihoraire2_ = e.getKeyCode();
				valeurRotationAntiJ2_.setEnabled(false);
				toucheRotationAntihoraireJ2_.setSelected(false);
				toucheRotationAntihoraireJ2_.setEnabled(true);
			}
		});
		valeurManoeuvreJ2_ = new JTextArea(DEFAUT_JOUEUR2_MANOEUVRE);
		valeurManoeuvreJ2_.setMinimumSize(DIMENSION_MIN_SAISIE);
		valeurManoeuvreJ2_.setMaximumSize(DIMENSION_MAX_SAISIE);
		valeurManoeuvreJ2_.setBackground(Color.WHITE);
		valeurManoeuvreJ2_.setEnabled(false);
		valeurManoeuvreJ2_.setDisabledTextColor(new Color(50,50,50));
		valeurManoeuvreJ2_.addKeyListener(new KeyAdapter(){
			public void keyPressed (KeyEvent e){
				if(checkDoublon(e.getKeyCode(), Keymanoeuvre2_)){
					if(e.getKeyChar()==' '){
						valeurManoeuvreJ2_.setText("Espace");
					}else{
						valeurManoeuvreJ2_.setText((e.getKeyChar()+"").toUpperCase());
					}
				}
				Keymanoeuvre2_ = e.getKeyCode();
				valeurManoeuvreJ2_.setEnabled(false);
				toucheManoeuvreJ2_.setSelected(false);
				toucheManoeuvreJ2_.setEnabled(true);
			}
		});
		valeurPropulsionJ2_ = new JTextArea(DEFAUT_JOUEUR2_PROPULSION);
		valeurPropulsionJ2_.setMinimumSize(DIMENSION_MIN_SAISIE);
		valeurPropulsionJ2_.setMaximumSize(DIMENSION_MAX_SAISIE);
		valeurPropulsionJ2_.setBackground(Color.WHITE);
		valeurPropulsionJ2_.setEnabled(false);
		valeurPropulsionJ2_.setDisabledTextColor(new Color(50,50,50));
		valeurPropulsionJ2_.addKeyListener(new KeyAdapter(){
			public void keyPressed (KeyEvent e){
				if(checkDoublon(e.getKeyCode(), Keypropulsion2_)){
					if(e.getKeyChar()==' '){
						valeurPropulsionJ2_.setText("Espace");
					}else{
						valeurPropulsionJ2_.setText((e.getKeyChar()+"").toUpperCase());
					}
				}
				Keypropulsion2_ = e.getKeyCode();
				valeurPropulsionJ2_.setEnabled(false);
				touchePropulsionJ2_.setSelected(false);
				touchePropulsionJ2_.setEnabled(true);
			}
		});
		valeurTirJ2_ = new JTextArea(DEFAUT_JOUEUR2_TIR);
		valeurTirJ2_.setMinimumSize(DIMENSION_MIN_SAISIE);
		valeurTirJ2_.setMaximumSize(DIMENSION_MAX_SAISIE);
		valeurTirJ2_.setBackground(Color.WHITE);
		valeurTirJ2_.setEnabled(false);
		valeurTirJ2_.setDisabledTextColor(new Color(50,50,50));
		valeurTirJ2_.addKeyListener(new KeyAdapter(){
			public void keyPressed (KeyEvent e){
				if(checkDoublon(e.getKeyCode(), Keytir2_)){
					if(e.getKeyChar()==' '){
						valeurTirJ2_.setText("Espace");
					}else{
						valeurTirJ2_.setText((e.getKeyChar()+"").toUpperCase());
					}
				}
				Keytir2_ = e.getKeyCode();
				valeurTirJ2_.setEnabled(false);
				toucheTirJ2_.setSelected(false);
				toucheTirJ2_.setEnabled(true);
			}
		});
		
		rotationHoraire_ = new JLabel("  Rotation horaire");
		rotationHoraire_.setMaximumSize(DIMENSION_MAX_LABEL);
		rotationHoraire_.setMinimumSize(DIMENSION_MIN_LABEL);
		rotationAntihoraire_ = new JLabel("  Rotation antihoraire");
		rotationAntihoraire_.setMaximumSize(DIMENSION_MAX_LABEL);
		rotationAntihoraire_.setMinimumSize(DIMENSION_MIN_LABEL);
		manoeuvre_ = new JLabel("  Manoeuvre de 180 degrés");
		manoeuvre_.setMaximumSize(DIMENSION_MAX_LABEL);
		manoeuvre_.setMinimumSize(DIMENSION_MIN_LABEL);
		propulsion_ = new JLabel("  Propulsion");
		propulsion_.setMaximumSize(DIMENSION_MAX_LABEL);
		propulsion_.setMinimumSize(DIMENSION_MIN_LABEL);
		tir_ = new JLabel("  Tir");
		tir_.setMaximumSize(DIMENSION_MAX_LABEL);
		tir_.setMinimumSize(DIMENSION_MIN_LABEL);
		rotationHoraire2_ = new JLabel("  Rotation horaire");
		rotationHoraire2_.setMaximumSize(DIMENSION_MAX_LABEL);
		rotationHoraire2_.setMinimumSize(DIMENSION_MIN_LABEL);
		rotationAntihoraire2_ = new JLabel("  Rotation antihoraire");
		rotationAntihoraire2_.setMaximumSize(DIMENSION_MAX_LABEL);
		rotationAntihoraire2_.setMinimumSize(DIMENSION_MIN_LABEL);
		manoeuvre2_ = new JLabel("  Manoeuvre de 180 degrés");
		manoeuvre2_.setMaximumSize(DIMENSION_MAX_LABEL);
		manoeuvre2_.setMinimumSize(DIMENSION_MIN_LABEL);
		propulsion2_ = new JLabel("  Propulsion");
		propulsion2_.setMaximumSize(DIMENSION_MAX_LABEL);
		propulsion2_.setMinimumSize(DIMENSION_MIN_LABEL);
		tir2_ = new JLabel("  Tir");
		tir2_.setMaximumSize(DIMENSION_MAX_LABEL);
		tir2_.setMinimumSize(DIMENSION_MIN_LABEL);
		
		toucheRotationHoraireJ1_ = new JToggleButton();
		toucheRotationHoraireJ1_.setMinimumSize(DIMENSION_MIN_BTN);
		toucheRotationHoraireJ1_.setMaximumSize(DIMENSION_MAX_BTN);
		toucheRotationHoraireJ1_.setToolTipText("Cliquez et appuyez sur la touche désirée");
		toucheRotationHoraireJ1_.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				valeurRotationJ1_.setEnabled(true);
				valeurRotationJ1_.requestFocus();
				valeurRotationJ1_.selectAll();
				toucheRotationHoraireJ1_.setEnabled(false);
			}
		});
		toucheRotationHoraireJ1_.setFocusable(false);
		
		toucheRotationAntihoraireJ1_ = new JToggleButton();
		toucheRotationAntihoraireJ1_.setMinimumSize(DIMENSION_MIN_BTN);
		toucheRotationAntihoraireJ1_.setMaximumSize(DIMENSION_MAX_BTN);
		toucheRotationAntihoraireJ1_.setToolTipText("Cliquez et appuyez sur la touche désirée");
		toucheRotationAntihoraireJ1_.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				valeurRotationAntiJ1_.setEnabled(true);
				valeurRotationAntiJ1_.requestFocus();
				valeurRotationAntiJ1_.selectAll();
				toucheRotationAntihoraireJ1_.setEnabled(false);
			}
		});
		toucheRotationAntihoraireJ1_.setFocusable(false);
		
		toucheManoeuvreJ1_ = new JToggleButton();
		toucheManoeuvreJ1_.setMinimumSize(DIMENSION_MIN_BTN);
		toucheManoeuvreJ1_.setMaximumSize(DIMENSION_MAX_BTN);
		toucheManoeuvreJ1_.setToolTipText("Cliquez et appuyez sur la touche désirée");
		toucheManoeuvreJ1_.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				valeurManoeuvreJ1_.setEnabled(true);
				valeurManoeuvreJ1_.requestFocus();
				valeurManoeuvreJ1_.selectAll();
				toucheManoeuvreJ1_.setEnabled(false);
			}
		});
		toucheManoeuvreJ1_.setFocusable(false);
		
		touchePropulsionJ1_ = new JToggleButton();
		touchePropulsionJ1_.setMinimumSize(DIMENSION_MIN_BTN);
		touchePropulsionJ1_.setMaximumSize(DIMENSION_MAX_BTN);
		touchePropulsionJ1_.setToolTipText("Cliquez et appuyez sur la touche désirée");
		touchePropulsionJ1_.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				valeurPropulsionJ1_.setEnabled(true);
				valeurPropulsionJ1_.requestFocus();
				valeurPropulsionJ1_.selectAll();
				touchePropulsionJ1_.setEnabled(false);
			}
		});
		touchePropulsionJ1_.setFocusable(false);
		
		toucheTirJ1_ = new JToggleButton();
		toucheTirJ1_.setMinimumSize(DIMENSION_MIN_BTN);
		toucheTirJ1_.setMaximumSize(DIMENSION_MAX_BTN);
		toucheTirJ1_.setToolTipText("Cliquez et appuyez sur la touche désirée");
		toucheTirJ1_.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				valeurTirJ1_.setEnabled(true);
				valeurTirJ1_.requestFocus();
				valeurTirJ1_.selectAll();
				toucheTirJ1_.setEnabled(false);
			}
		});
		toucheTirJ1_.setFocusable(false);
		
		toucheRotationHoraireJ2_ = new JToggleButton();
		toucheRotationHoraireJ2_.setMinimumSize(DIMENSION_MIN_BTN);
		toucheRotationHoraireJ2_.setMaximumSize(DIMENSION_MAX_BTN);
		toucheRotationHoraireJ2_.setToolTipText("Cliquez et appuyez sur la touche désirée");
		toucheRotationHoraireJ2_.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				valeurRotationJ2_.setEnabled(true);
				valeurRotationJ2_.requestFocus();
				valeurRotationJ2_.selectAll();
				toucheRotationHoraireJ2_.setEnabled(false);
			}
		});
		toucheRotationHoraireJ2_.setFocusable(false);
		
		toucheRotationAntihoraireJ2_ = new JToggleButton();
		toucheRotationAntihoraireJ2_.setMinimumSize(DIMENSION_MIN_BTN);
		toucheRotationAntihoraireJ2_.setMaximumSize(DIMENSION_MAX_BTN);
		toucheRotationAntihoraireJ2_.setToolTipText("Cliquez et appuyez sur la touche désirée");
		toucheRotationAntihoraireJ2_.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				valeurRotationAntiJ2_.setEnabled(true);
				valeurRotationAntiJ2_.requestFocus();
				valeurRotationAntiJ2_.selectAll();
				toucheRotationAntihoraireJ2_.setEnabled(false);
			}
		});
		toucheRotationAntihoraireJ2_.setFocusable(false);
		
		toucheManoeuvreJ2_ = new JToggleButton();
		toucheManoeuvreJ2_.setMinimumSize(DIMENSION_MIN_BTN);
		toucheManoeuvreJ2_.setMaximumSize(DIMENSION_MAX_BTN);
		toucheManoeuvreJ2_.setToolTipText("Cliquez et appuyez sur la touche désirée");
		toucheManoeuvreJ2_.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				valeurManoeuvreJ2_.setEnabled(true);
				valeurManoeuvreJ2_.requestFocus();
				valeurManoeuvreJ2_.selectAll();
				toucheManoeuvreJ2_.setEnabled(false);
			}
		});
		toucheManoeuvreJ2_.setFocusable(false);
		
		touchePropulsionJ2_ = new JToggleButton();
		touchePropulsionJ2_.setMinimumSize(DIMENSION_MIN_BTN);
		touchePropulsionJ2_.setMaximumSize(DIMENSION_MAX_BTN);
		touchePropulsionJ2_.setToolTipText("Cliquez et appuyez sur la touche désirée");
		touchePropulsionJ2_.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				valeurPropulsionJ2_.setEnabled(true);
				valeurPropulsionJ2_.requestFocus();
				valeurPropulsionJ2_.selectAll();
				touchePropulsionJ2_.setEnabled(false);
			}
		});
		touchePropulsionJ2_.setFocusable(false);
		
		toucheTirJ2_ = new JToggleButton();
		toucheTirJ2_.setMinimumSize(DIMENSION_MIN_BTN);
		toucheTirJ2_.setMaximumSize(DIMENSION_MAX_BTN);
		toucheTirJ2_.setToolTipText("Cliquez et appuyez sur la touche désirée");
		toucheTirJ2_.addActionListener(new ActionListener(){
			public void actionPerformed (ActionEvent e){
				valeurTirJ2_.setEnabled(true);
				valeurTirJ2_.requestFocus();
				valeurTirJ2_.selectAll();
				toucheTirJ2_.setEnabled(false);
			}
		});
		toucheTirJ2_.setFocusable(false);
		
		// Option de Jeu
		optionJeu_ = new JLabel("Options de jeu : ");
		optionJeu_.setFont(new Font("Tahoma", Font.BOLD, 13));
		optionJeu_.setMinimumSize(DIMENSION_MIN_LABEL);
		optionJeu_.setMaximumSize(DIMENSION_MAX_LABEL);
		
		dureePartie_ = new JLabel("  Durée d'une partie en secondes");
		dureePartie_.setMinimumSize(DIMENSION_MIN_LABEL);
		dureePartie_.setMaximumSize(DIMENSION_MAX_LABEL);
		pointsVieStation_ = new JLabel("  Points de vie des stations");
		pointsVieStation_.setMinimumSize(DIMENSION_MIN_LABEL);
		pointsVieStation_.setMaximumSize(DIMENSION_MAX_LABEL);
		sliderDureeJeu_ = new JSlider();
		sliderDureeJeu_.setOpaque(false);
		sliderDureeJeu_.setPaintTicks(true);
		sliderDureeJeu_.setPaintLabels(true);
		sliderDureeJeu_.setMinimum(DUREE_PARTIE_MIN);
		sliderDureeJeu_.setMaximum(DUREE_PARTIE_MAX);
		sliderDureeJeu_.setMajorTickSpacing(30);
		sliderDureeJeu_.setMinorTickSpacing(15);
		sliderDureeJeu_.setValue(DEFAUT_PARTIE_DUREE);
		sliderDureeJeu_.addChangeListener(new DureeJeuListener());
		
		sliderPointVieStation_ = new JSlider();
		sliderPointVieStation_.setOpaque(false);
		sliderPointVieStation_.setPaintTicks(true);
		sliderPointVieStation_.setPaintLabels(true);
		sliderPointVieStation_.setMinimum(POINTS_VIE_MIN);
		sliderPointVieStation_.setMaximum(POINTS_VIE_MAX);
		sliderPointVieStation_.setMajorTickSpacing(2);
		sliderPointVieStation_.setMinorTickSpacing(1);
		sliderPointVieStation_.setValue(DEFAUT_POINTS_VIE);
		sliderPointVieStation_.addChangeListener(new PointVieStationListener());
		
		// Option de debogage
		debogage_ = new JLabel("Options de débogage");
		affichageConsole_ = new JLabel("Options d'affichage à la console : ");
		affichageConsole_.setMinimumSize(DIMENSION_MIN_LABEL);
		affichageConsole_.setMaximumSize(DIMENSION_MAX_LABEL);
		affichageConsole_.setFont(new Font("Tahoma", Font.BOLD, 13));
		
		identificateurs_ = new JLabel("Identificateurs visuels : ");
		identificateurs_.setMinimumSize(DIMENSION_MIN_LABEL);
		identificateurs_.setMaximumSize(DIMENSION_MAX_LABEL);
		identificateurs_.setFont(new Font("Tahoma", Font.BOLD, 13));
		
		//Initialisation des checkBox
		chkApparitionAsteroide_ = new JCheckBox("Apparition d'un astéroïde  ");
		chkApparitionAsteroide_.setOpaque(false);
		chkApparitionAsteroide_.setHorizontalTextPosition(SwingConstants.LEFT);
		
		chkChangementMode_ = new JCheckBox("Changement de mode  ");
		chkChangementMode_.setOpaque(false);
		chkChangementMode_.setHorizontalTextPosition(SwingConstants.LEFT);
		
		chkEclairage_ = new JCheckBox("Activation/désactivation d'un éclairage  ");
		chkEclairage_.setOpaque(false);
		chkEclairage_.setHorizontalTextPosition(SwingConstants.LEFT);
		
		chkCibleJoueur_ = new JCheckBox("Cible du joueur  ");
		chkCibleJoueur_.setOpaque(false);
		chkCibleJoueur_.setHorizontalTextPosition(SwingConstants.LEFT);
		
		chkCadreDepart_ = new JCheckBox("Cadre de départ  ");
		chkCadreDepart_.setOpaque(false);
		chkCadreDepart_.setHorizontalTextPosition(SwingConstants.LEFT);
		
		chkZonePassage_ = new JCheckBox("Zone de passage  ");
		chkZonePassage_.setOpaque(false);
		chkZonePassage_.setHorizontalTextPosition(SwingConstants.LEFT);
		
		chkAttractionPortail_ = new JCheckBox("Limite d'attraction des portails  ");
		chkAttractionPortail_.setOpaque(false);
		chkAttractionPortail_.setHorizontalTextPosition(SwingConstants.LEFT);
		
		 // Initialisation du bouton Sauvegarder
		btnSauvegarder_ = new JButton("Sauvegarder");
		btnSauvegarder_.addActionListener(gestionnaire);
		btnSauvegarder_.setActionCommand("SauvegardeConfiguration");
		
		btnDefautJ1_ = new JButton("Défaut");
		btnDefautJ1_.setToolTipText("Cliquez pour remettre les valeurs suggérées");
		btnDefautJ1_.addActionListener(new BoutonDefautJ1Listener());
		btnDefautJ1_.setFocusable(false);
		btnDefautJ2_ = new JButton("Défaut");
		btnDefautJ2_.setToolTipText("Cliquez pour remettre les valeurs suggérées");
		btnDefautJ2_.addActionListener(new BoutonDefautJ2Listener());
		btnDefautJ2_.setFocusable(false);
		
		// Attributs de la fenêtre
		screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		largeurEcran = (int) screenSize.getWidth();
		hauteurEcran = (int) screenSize.getHeight();

		largeurFenetre = (int) (largeurEcran/3);
		hauteurFenetre = (int) (hauteurEcran/2);
		
	
		setResizable(true);
		
		
		setSize(largeurFenetre*5/3, hauteurFenetre*15/8);
		//setTitle("Fenetre de configuration des parametres");
		
		
		contentPane = new JPanel();
		contentPane.setBackground(new Color(200, 210, 220));
		layout = new GroupLayout(contentPane);
		contentPane.setLayout(layout);
		setContentPane(contentPane);
		
		layout.setAutoCreateGaps(true);
		layout.setAutoCreateContainerGaps(true);
		layout.setHorizontalGroup(
				layout.createParallelGroup()
					.addGroup(layout.createSequentialGroup()
							.addComponent(toucheJoueur1_)
							//.addComponent(valeurActuelle_ )
							)
					.addGroup(layout.createSequentialGroup()
							.addComponent(rotationHoraire_)
							.addComponent(toucheRotationHoraireJ1_)
							.addComponent(valeurRotationJ1_)
							)
					.addGroup(layout.createSequentialGroup()
							.addComponent(rotationAntihoraire_)
							.addComponent(toucheRotationAntihoraireJ1_)
							.addComponent(valeurRotationAntiJ1_)
							)
					.addGroup(layout.createSequentialGroup()
							.addComponent(manoeuvre_)
							.addComponent(toucheManoeuvreJ1_)
							.addComponent(valeurManoeuvreJ1_)
							)
					.addGroup(layout.createSequentialGroup()
							.addComponent(propulsion_)
							.addComponent(touchePropulsionJ1_)
							.addComponent(valeurPropulsionJ1_)
							)
					.addGroup(layout.createSequentialGroup()
							.addComponent(tir_)
							.addComponent(toucheTirJ1_)
							.addComponent(valeurTirJ1_)
							)
					.addComponent(btnDefautJ1_, Alignment.TRAILING)
					.addGroup(layout.createSequentialGroup()
							.addComponent(toucheJoueur2_)
							)
					.addGroup(layout.createSequentialGroup()
							.addComponent(rotationHoraire2_)
							.addComponent(toucheRotationHoraireJ2_)
							.addComponent(valeurRotationJ2_)
							)
					.addGroup(layout.createSequentialGroup()
							.addComponent(rotationAntihoraire2_)
							.addComponent(toucheRotationAntihoraireJ2_)
							.addComponent(valeurRotationAntiJ2_)
							)
					.addGroup(layout.createSequentialGroup()
							.addComponent(manoeuvre2_)
							.addComponent(toucheManoeuvreJ2_)
							.addComponent(valeurManoeuvreJ2_)
							)
					.addGroup(layout.createSequentialGroup()
							.addComponent(propulsion2_)
							.addComponent(touchePropulsionJ2_)
							.addComponent(valeurPropulsionJ2_)
							)
					.addGroup(layout.createSequentialGroup()
							.addComponent(tir2_)
							.addComponent(toucheTirJ2_)
							.addComponent(valeurTirJ2_)
							)
					.addComponent(btnDefautJ2_, Alignment.TRAILING)
					.addComponent(optionJeu_)
				    .addGroup(layout.createSequentialGroup()
				    		.addComponent(dureePartie_)
				    		.addComponent(sliderDureeJeu_)
				    		)
				    .addGroup(layout.createSequentialGroup()
				    		.addComponent(pointsVieStation_)
				    		.addComponent(sliderPointVieStation_)
				    		)
				    //.addComponent(debogage_)
				    .addComponent(affichageConsole_)
				    .addComponent(chkApparitionAsteroide_, Alignment.TRAILING)
				    .addComponent(chkChangementMode_, Alignment.TRAILING)
				    .addComponent(chkEclairage_, Alignment.TRAILING)
				    .addComponent(identificateurs_)
				    .addComponent(chkCibleJoueur_, Alignment.TRAILING)
				    .addComponent(chkCadreDepart_, Alignment.TRAILING)
				    .addComponent(chkZonePassage_, Alignment.TRAILING)
				    .addComponent(chkAttractionPortail_, Alignment.TRAILING)
					.addComponent(btnSauvegarder_)
				);
		layout.setVerticalGroup(
				layout.createSequentialGroup()
				.addGroup(layout.createParallelGroup()
						.addComponent(toucheJoueur1_)
						//.addComponent(valeurActuelle_ )
						)
				.addGroup(layout.createParallelGroup()
						.addComponent(rotationHoraire_)
						.addComponent(toucheRotationHoraireJ1_,Alignment.CENTER)
						.addComponent(valeurRotationJ1_)
						)
				.addGroup(layout.createParallelGroup()
						.addComponent(rotationAntihoraire_)
						.addComponent(toucheRotationAntihoraireJ1_,Alignment.CENTER)
						.addComponent(valeurRotationAntiJ1_)
						)
				.addGroup(layout.createParallelGroup()
						.addComponent(manoeuvre_)
						.addComponent(toucheManoeuvreJ1_,Alignment.CENTER)
						.addComponent(valeurManoeuvreJ1_)
						)
				.addGroup(layout.createParallelGroup()
						.addComponent(propulsion_)
						.addComponent(touchePropulsionJ1_,Alignment.CENTER)
						.addComponent(valeurPropulsionJ1_)
						)
				.addGroup(layout.createParallelGroup()
						.addComponent(tir_)
						.addComponent(toucheTirJ1_,Alignment.CENTER)
						.addComponent(valeurTirJ1_)
						)
				.addComponent(btnDefautJ1_)
				.addGroup(layout.createParallelGroup()
							.addComponent(toucheJoueur2_)
							)
				.addGroup(layout.createParallelGroup()
							.addComponent(rotationHoraire2_)
							.addComponent(toucheRotationHoraireJ2_,Alignment.CENTER)
							.addComponent(valeurRotationJ2_)
							)
				.addGroup(layout.createParallelGroup()
							.addComponent(rotationAntihoraire2_)
							.addComponent(toucheRotationAntihoraireJ2_,Alignment.CENTER)
							.addComponent(valeurRotationAntiJ2_)
							)
				.addGroup(layout.createParallelGroup()
							.addComponent(manoeuvre2_)
							.addComponent(toucheManoeuvreJ2_,Alignment.CENTER)
							.addComponent(valeurManoeuvreJ2_)
							)
				.addGroup(layout.createParallelGroup()
							.addComponent(propulsion2_)
							.addComponent(touchePropulsionJ2_,Alignment.CENTER)
							.addComponent(valeurPropulsionJ2_)
							)
				.addGroup(layout.createParallelGroup()
							.addComponent(tir2_)
							.addComponent(toucheTirJ2_,Alignment.CENTER)
							.addComponent(valeurTirJ2_)
							)
				.addComponent(btnDefautJ2_)
				.addComponent(optionJeu_)
				.addGroup(layout.createParallelGroup()
						.addComponent(dureePartie_)
						.addComponent(sliderDureeJeu_)
						)
				.addGroup(layout.createParallelGroup()
						.addComponent(pointsVieStation_)
						.addComponent(sliderPointVieStation_)
						)
				//.addComponent(debogage_)
				.addComponent(affichageConsole_)
				.addComponent(chkApparitionAsteroide_)
				.addComponent(chkChangementMode_)
				.addComponent(chkEclairage_)
				.addComponent(identificateurs_)
				.addComponent(chkCibleJoueur_)
				.addComponent(chkCadreDepart_)
				.addComponent(chkZonePassage_)
				.addComponent(chkAttractionPortail_)
				.addComponent(btnSauvegarder_)
				);
		
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize(); // Obtenir les dimensions de l'ecran
		
		setSize(screenSize.width/3 , (int) (screenSize.height /1.2));
		
		setBounds((screenSize.width - getWidth()) / 2,
				  (screenSize.height - getHeight() - 20) / 2,
				  getWidth(), getHeight()); // Definir les dimensions de la fenetre
		
		
	}
	public boolean checkDoublon(Integer e, Integer valeurActuelle){
		if(!toucheRentrer_.contains(e)){
			toucheRentrer_.remove(valeurActuelle);
			toucheRentrer_.add(e);
			return true;
		}else{
			return false;
		}
	}
	
	// Setters
	public void setToucheJ1Rot(int touche) { 
		KeyrotationHoraire_ = touche;
		valeurRotationJ1_.setText(KeyEvent.getKeyText(touche));
		}
	public void setToucheJ1RotAnti(int touche) { 
		KeyrotationAntihoraire_ = touche;
		valeurRotationAntiJ1_.setText(KeyEvent.getKeyText(touche));
		}
	public void setToucheJ1Man(int touche) { 
		Keymanoeuvre_ = touche;
		valeurManoeuvreJ1_.setText(KeyEvent.getKeyText(touche));
		}
	public void setToucheJ1Prop(int touche) { 
		Keypropulsion_ = touche;
		valeurPropulsionJ1_.setText(KeyEvent.getKeyText(touche));
	}
	public void setToucheJ1Tir(int touche) { 
		Keytir_ = touche;
		valeurTirJ1_.setText(KeyEvent.getKeyText(touche));
	}
	
	public void setToucheJ2Rot(int touche) { 
		KeyrotationHoraire2_ = touche;
		valeurRotationJ2_.setText(KeyEvent.getKeyText(touche));
	}
	public void setToucheJ2RotAnti(int touche) { 
		KeyrotationAntihoraire2_ = touche;
		valeurRotationAntiJ2_.setText(KeyEvent.getKeyText(touche));
	}
	public void setToucheJ2Man(int touche) { 
		Keymanoeuvre2_ = touche;
		valeurManoeuvreJ2_.setText(KeyEvent.getKeyText(touche));
	}
	public void setToucheJ2Prop(int touche) { 
		Keypropulsion2_ = touche;
		valeurPropulsionJ2_.setText(KeyEvent.getKeyText(touche));
	}
	public void setToucheJ2Tir(int touche) { 
		Keytir2_ = touche;
		valeurTirJ2_.setText(KeyEvent.getKeyText(touche));
	}
	
	public void setDureeJeu(double duree) { sliderDureeJeu_.setValue((int)duree); }
	public void setPointDeVieStation(int ptsVie) { sliderPointVieStation_.setValue(ptsVie); }
	public void setApparitionAsteroide(int b){ 
		if(b==0)
			chkApparitionAsteroide_.setSelected(false);
		else
			chkApparitionAsteroide_.setSelected(true);
	}
	public void setChangementMode(int b){
		if(b==0)
			chkChangementMode_.setSelected(false);
		else
			chkChangementMode_.setSelected(true);
	}
	public void setEclairage(int b){ 
		if(b==0)
			chkEclairage_.setSelected(false);
		else
			chkEclairage_.setSelected(true);
	}
	public void setCibleJoueur(int b){ 
		if(b==0)
			chkCibleJoueur_.setSelected(false);
		else
			chkCibleJoueur_.setSelected(true);
	}
	public void setZonePassage(int b){ 
		if(b==0)
			chkZonePassage_.setSelected(false);
		else
			chkZonePassage_.setSelected(true);
	}
	public void setCadreDepart(int b){ 
		if(b==0)
			chkCadreDepart_.setSelected(false);
		else
			chkCadreDepart_.setSelected(true);
	}
	public void setAttractionPort(int b){ 
		if(b==0)
			chkAttractionPortail_.setSelected(false);
		else
			chkAttractionPortail_.setSelected(true);
	}
	
	//pour les chiffres sur le numpad
	public int getToucheJ1Rot(){ 
		return KeyrotationHoraire_;
		}
	public int getToucheJ1RotAnti(){
		return KeyrotationAntihoraire_;
		}
	public int getToucheJ1Man(){ 
		return Keymanoeuvre_;
		}
	public int getToucheJ1Prop(){ 
		return Keypropulsion_;
		}
	public int getToucheJ1Tir(){
		return Keytir_;
		}
	public int getToucheJ2Rot(){ 
		return KeyrotationHoraire2_;
		}
	public int getToucheJ2RotAnti(){ 
		return KeyrotationAntihoraire2_;
		}
	public int getToucheJ2Man(){
		return Keymanoeuvre2_;
		}
	public int getToucheJ2Prop(){
		return Keypropulsion2_;
		}
	public int getToucheJ2Tir(){
		return Keytir2_;
		}
	public double getDureeJeu(){ return sliderDureeJeu_.getValue(); }
	public int getPointDeVieStation(){return sliderPointVieStation_.getValue();}
	public boolean getCheckApparitionAsteroide(){ return chkApparitionAsteroide_.isSelected();}
	public boolean getCheckChangementMode(){ return chkChangementMode_.isSelected();}
	public boolean getCheckEclairage(){ return chkEclairage_.isSelected();}
	public boolean getCheckCibleJoueur(){ return chkCibleJoueur_.isSelected();}
	public boolean getCheckCadreDepart(){ return chkCadreDepart_.isSelected();}
	public boolean getCheckZonePassage(){ return chkZonePassage_.isSelected();}
	public boolean getCheckAttractionPortail(){ return chkAttractionPortail_.isSelected();}
	
///////////////////////////////////////////////////////////////////////////
// ACTION LISTENERS
///////////////////////////////////////////////////////////////////////////
	private class DureeJeuListener implements ChangeListener {

		@Override
		public void stateChanged(ChangeEvent e) {
			//double dureeJeu = ((JSlider)e.getSource()).getValue();
		}
	
	}
	
	private class PointVieStationListener implements ChangeListener {

		@Override
		public void stateChanged(ChangeEvent e) {
			//int pointVieStation = ((JSlider)e.getSource()).getValue();
		}
	
	}
	
	private class BoutonDefautJ1Listener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			valeurRotationJ1_.setText(DEFAUT_JOUEUR1_HORAIRE);
			valeurRotationAntiJ1_.setText(DEFAUT_JOUEUR1_ANTIHORAIRE);
			valeurManoeuvreJ1_.setText(DEFAUT_JOUEUR1_MANOEUVRE);
			valeurPropulsionJ1_.setText(DEFAUT_JOUEUR1_PROPULSION);
			valeurTirJ1_.setText(DEFAUT_JOUEUR1_TIR);
			
			// Supprime les valeurs actuelles du HashSet
			toucheRentrer_.remove(KeyrotationHoraire_);	toucheRentrer_.remove(KeyrotationAntihoraire_);
			toucheRentrer_.remove(Keymanoeuvre_);	toucheRentrer_.remove(Keypropulsion_);
			toucheRentrer_.remove(Keytir_);

			KeyrotationHoraire_= KeyEvent.VK_D;
			KeyrotationAntihoraire_ =KeyEvent.VK_A;
			Keymanoeuvre_ = KeyEvent.VK_S;
			Keypropulsion_ = KeyEvent.VK_W;
			Keytir_ = KeyEvent.VK_SPACE;
			
		    // Ajoute les valeurs par defaut au HashSet
			toucheRentrer_.add(KeyrotationHoraire_); toucheRentrer_.add(KeyrotationAntihoraire_);
			toucheRentrer_.add(Keymanoeuvre_); toucheRentrer_.add(Keypropulsion_);
			toucheRentrer_.add(Keytir_);
			
		}
	}
	
	private class BoutonDefautJ2Listener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			valeurRotationJ2_.setText(DEFAUT_JOUEUR2_HORAIRE);
			valeurRotationAntiJ2_.setText(DEFAUT_JOUEUR2_ANTIHORAIRE);
			valeurManoeuvreJ2_.setText(DEFAUT_JOUEUR2_MANOEUVRE);
			valeurPropulsionJ2_.setText(DEFAUT_JOUEUR2_PROPULSION);
			valeurTirJ2_.setText(DEFAUT_JOUEUR2_TIR);
			
			// Supprime les valeurs actuelles du HashSet
			toucheRentrer_.remove(KeyrotationHoraire2_);
			toucheRentrer_.remove(KeyrotationAntihoraire2_);	toucheRentrer_.remove(Keymanoeuvre2_);
			toucheRentrer_.remove(Keypropulsion2_);	toucheRentrer_.remove(Keytir2_);
			
			KeyrotationHoraire2_= KeyEvent.VK_NUMPAD6;
			KeyrotationAntihoraire2_ =KeyEvent.VK_NUMPAD4;
			Keymanoeuvre2_ = KeyEvent.VK_NUMPAD5;
			Keypropulsion2_ = KeyEvent.VK_NUMPAD8;
			Keytir2_ = KeyEvent.VK_NUMPAD0;
			
			// Ajoute les valeurs par defaut au HashSet
			toucheRentrer_.add(KeyrotationHoraire2_); toucheRentrer_.add(KeyrotationAntihoraire2_);
			toucheRentrer_.add(Keymanoeuvre2_); toucheRentrer_.add(Keypropulsion2_);
			toucheRentrer_.add(Keytir2_);
		}
	}
		
}
