package InterfaceGraphique;

import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;
import java.awt.Toolkit;
import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.JButton;
import javax.swing.WindowConstants;
import java.awt.Font;
import java.awt.Color;
import java.awt.Insets;
import javax.swing.border.BevelBorder;

/**
 * @author Sacha L-Roussel
 * Classe du menu principal. Ceui-ci ne contient que les boutons permettant d'accer aux différentes fonctions du jeux.
 */

@SuppressWarnings("serial")
public class MenuPrincipal extends JFrame {

	//Composantes graphique
	private JPanel contentPane;

	//Variables de taille/positionnement
	private Dimension screenSize;
	private int largeurEcran;
	private int hauteurEcran;
	private static int largeurFenetre;
	private static int hauteurFenetre;
	private int tailleChar;

	//Composantes graphiques
	private JButton btnPartieRapide;
	private JButton btnCampagne;
	private JButton btnEdition;
	private JButton btnConfiguration;	
	private JButton btnQuitter; 
	
	/**
	 * Constructeur par défaut du menu; On fixe les composantes graphiques de la fenetre ainsi que leur écouteurs d'action.
	 * @param Aucuns paramètres
	 * @return Rien
	 */
	public MenuPrincipal() {
		//Propriétés de la fenêtre

		setTitle("PolyAst\u00E9ro\u00EFde");
		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

		//On va chercher la taille de l'ecran afin de déterminer la taille et la position optimale de notre fenetre, peu importe l'ecran
		screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		largeurEcran = (int) screenSize.getWidth();
		hauteurEcran = (int) screenSize.getHeight();

		largeurFenetre = (int) (largeurEcran/3);
		hauteurFenetre = (int) (hauteurEcran/2);

		setBounds(largeurEcran/2 - largeurFenetre/2, hauteurEcran/2 - hauteurFenetre/2, largeurFenetre, hauteurFenetre);

		setResizable(false);

		//On dessine le background qu'on va chercher dans le package Images.
		contentPane = new JPanel(){
			public void paintComponent(Graphics g) {
				super.paintComponent(g);
				Graphics2D g2d = (Graphics2D) g;
				
				g2d.setRenderingHint(RenderingHints.KEY_INTERPOLATION, RenderingHints.VALUE_INTERPOLATION_BILINEAR);
			    g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING,RenderingHints.VALUE_ANTIALIAS_ON); 
			    g2d.setRenderingHint(RenderingHints.KEY_TEXT_ANTIALIASING,RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
				
				Image img = Toolkit.getDefaultToolkit().getImage(MenuPrincipal.class.getResource("/Images/background1.jpg"));
				g2d.drawImage(img, -25, -40,this); 

				
				Image titre = Toolkit.getDefaultToolkit().getImage(MenuPrincipal.class.getResource("/Images/titre1.png"));

				int largeurTitre = 6*getWidth()/8;
				int hauteurTitre = getHeight()/9;
				g2d.drawImage(titre, getWidth()/2 - largeurTitre/2 + 20, getHeight()/10, largeurTitre, hauteurTitre , this);
			}
		};

		setContentPane(contentPane);
		contentPane.setLayout(null);

		int facteurCorrectionLargeur;

		//Taille des caractères selon la resolution de l'écran
		if(largeurEcran >= 2500){
			tailleChar = 20;
			facteurCorrectionLargeur = 25;
		}else if(largeurEcran >= 1900){
			tailleChar = 18;
			facteurCorrectionLargeur = 35;
		}else{
			tailleChar = 14;
			facteurCorrectionLargeur = 30;
		}
		
		//Composantes de la fenêtre		
		//Boutons------------------------------------

		//Gestionnaire d'action qui fait le traitement afin d'appeler la bonne méthode parmis celles dans la classe démarrage.
		GestionnaireBoutons gestionnaire = new GestionnaireBoutons(InputManager.getInstance());

		int largeurBtn = largeurFenetre/6+facteurCorrectionLargeur;
		int hauteurBtn = hauteurFenetre/12;


		btnPartieRapide = new JButton("Partie Rapide");
		btnPartieRapide.setMargin(new Insets(2, 6, 2, 6));
		btnPartieRapide.setBounds(largeurFenetre/4, hauteurFenetre/3, largeurBtn, hauteurBtn);
		btnPartieRapide.setEnabled(true);
		btnPartieRapide.setBorder(new BevelBorder(BevelBorder.RAISED, null, null, null, null));
		btnPartieRapide.setOpaque(false);
		btnPartieRapide.setFont(new Font("Magneto", Font.BOLD, tailleChar));
		btnPartieRapide.setForeground(new Color(25,100,180));
		btnPartieRapide.addActionListener(gestionnaire);
		btnPartieRapide.setActionCommand("PartieRapide");
		btnPartieRapide.setFocusable(false);
		btnPartieRapide.setToolTipText("Démarrer une partie rapide seul ou en équipe");
		contentPane.add(btnPartieRapide);

		btnCampagne = new JButton("Campagne");
		btnCampagne.setMargin(new Insets(2, 6, 2, 6));
		btnCampagne.setBounds(3*largeurFenetre/4 - largeurBtn, hauteurFenetre/3, largeurBtn, hauteurBtn);
		btnCampagne.setEnabled(true);
		btnCampagne.setBorder(new BevelBorder(BevelBorder.RAISED, null, null, null, null));
		btnCampagne.setOpaque(false);
		btnCampagne.setFont(new Font("Magneto", Font.BOLD, tailleChar));;
		btnCampagne.setForeground(new Color(25,100,180));
		btnCampagne.addActionListener(gestionnaire);
		btnCampagne.setActionCommand("Campagne");
		btnCampagne.setFocusable(false);
		btnCampagne.setToolTipText("Démarrer une campagne avec plusieurs cartes");
		contentPane.add(btnCampagne);

		btnEdition = new JButton();
		btnEdition.setText("\u00C9dition");
		btnEdition.setMargin(new Insets(2, 6, 2, 6));
		btnEdition.setBounds(largeurFenetre/4, hauteurFenetre/2, largeurBtn, hauteurBtn);
		btnEdition.setBorder(new BevelBorder(BevelBorder.RAISED, null, null, null, null));
		btnEdition.setOpaque(false);
		btnEdition.setForeground(new Color(25,100,180));
		btnEdition.addActionListener(gestionnaire);
		btnEdition.setActionCommand("FenetreEdition");
		btnEdition.setFont(new Font("Magneto", Font.BOLD, tailleChar));
		btnEdition.setFocusable(false);
		btnEdition.setToolTipText("Créer et modifier des cartes de jeu");
		contentPane.add(btnEdition);

		btnConfiguration = new JButton("Configuration");
		btnConfiguration.setMargin(new Insets(2, 6, 2, 6));
		btnConfiguration.setBounds(3*largeurFenetre/4 - largeurBtn, hauteurFenetre/2, largeurBtn, hauteurBtn);
		btnConfiguration.setEnabled(true);
		btnConfiguration.setBorder(new BevelBorder(BevelBorder.RAISED, null, null, null, null));
		btnConfiguration.setOpaque(false);
		btnConfiguration.setFont(new Font("Magneto", Font.BOLD, tailleChar));
		btnConfiguration.setForeground(new Color(25,100,180));
		btnConfiguration.addActionListener(gestionnaire);
		btnConfiguration.setActionCommand("Configuration");
		btnConfiguration.setFocusable(false);
		btnConfiguration.setToolTipText("Modifier les paramètres de jeu et de débogage");
		contentPane.add(btnConfiguration);

		btnQuitter = new JButton("Quitter");
		btnQuitter.setMargin(new Insets(2, 6, 2, 6));
		btnQuitter.setBounds((largeurFenetre/2)-largeurBtn/2, (int) (hauteurFenetre*0.7), largeurBtn, hauteurBtn);
		btnQuitter.setBorder(new BevelBorder(BevelBorder.RAISED, null, null, null, null));
		btnQuitter.setOpaque(false);
		btnQuitter.setFont(new Font("Magneto", Font.BOLD, tailleChar));
		btnQuitter.setForeground(new Color(25,100,180));
		btnQuitter.addActionListener(gestionnaire);
		btnQuitter.setActionCommand("Quitter");
		btnQuitter.setFocusable(false);
		btnQuitter.setToolTipText("Quitter le jeu");
		contentPane.add(btnQuitter);
		//--------------------------------------


	}

}

