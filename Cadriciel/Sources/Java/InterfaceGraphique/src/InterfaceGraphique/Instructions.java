/**
 * Projet integrateur du programme Sciences informatiques et mathematiques
 * Fenetre d'aide expliquant l'application
 * 
 * @version 1.0 - 9 fŽvrier 2012 
 * @author Simon Plante, Anthony Guay et Sacha Licatese-Roussel
 */
//Simon Plante	17 septembre	creation de la classe Instructions
//Les textes ont ete ecrits par Anthony Guay

package InterfaceGraphique;

import java.awt.BorderLayout;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GridLayout;
import javax.swing.ImageIcon;
import javax.swing.JEditorPane;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.ScrollPaneConstants;
import javax.swing.SwingConstants;
import javax.swing.border.EmptyBorder;

public class Instructions extends JFrame {

	private static final long serialVersionUID = 1L;

	private JPanel contentPane;
	private JTabbedPane tabbedPane;

	private double largeurEcran = java.awt.Toolkit.getDefaultToolkit().getScreenSize().getWidth(),
			hauteurEcran = java.awt.Toolkit.getDefaultToolkit().getScreenSize().getHeight();
	private int largeur = (int) (largeurEcran/2.5),hauteur = (int) (hauteurEcran/1.4);

	private Font font = new Font("Lucida Grande", Font.BOLD, 16);


	/**
	 * Creation de la fenetre d'instructions
	 */
	public Instructions() {

		setResizable(false);
		setTitle("Instructions");
		setVisible(false);
		setPreferredSize(new Dimension((int)(largeurEcran-(largeurEcran/2 + largeur/2)), (int)(hauteurEcran-(hauteurEcran/2 + hauteur/2))));
		setBounds((int)(largeurEcran-(largeurEcran/2 + largeur/2)), (int)(hauteurEcran-(hauteurEcran/2 + hauteur/2)), largeur, hauteur);

		contentPane = new JPanel();
		contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
		setContentPane(contentPane);
		contentPane.setLayout(new BorderLayout(0, 0));

		//section pour les instructions de l'application
		tabbedPane = new JTabbedPane(JTabbedPane.TOP);
		contentPane.add(tabbedPane, BorderLayout.CENTER);

		JPanel panelConsignes = new JPanel();
		tabbedPane.addTab("Instructions", null, panelConsignes, null);
		panelConsignes.setLayout(new BorderLayout(0, 0));

		JEditorPane txtrBienvenueDansSchmatix = new JEditorPane();
		txtrBienvenueDansSchmatix.setContentType("text/html");
		txtrBienvenueDansSchmatix.setEditable(false);
		txtrBienvenueDansSchmatix.setText("<html><b><h1 align=center>PolyAst\u00E9ro\u00EFde - Mode \u00C9dition</h1></b><br><br>\r\n\r\nLe mode d'\u00E9dition de PolyAst\u00E9ro\u00EFde vous permet de cr\u00E9er vos propres niveaux et de les tester, \u00E0 l'aide de diff\u00E9rents outils. <br><br><br><br>\r\n\r\n\r\n<b>Fonctionnement g\u00E9n\u00E9ral</b><br><br><br>\r\n\r\n- \u00C0 gauche de l'\u00E9cran se trouve une barre d'outils contenant tout ce que vous avez besoin pour construire les niveaux. Vous y trouverez les diff\u00E9rentes commandes de contr\u00F4le des \u00E9l\u00E9ments ainsi que les \u00E9l\u00E9ments de jeu: Station spatiale, Bonus acc\u00E9l\u00E9rateur, Portails, Barri\u00E8re.<br><br><br>\r\n\r\n- Au centre se trouve la zone d'affichage du niveau. Vous pouvez y naviguer \u00E0 l'aide des fl\u00EAches du clavier ou en modifiant la position de la cam\u00E9ra \u00E0 l'aide d'un clic et d'un d\u00E9placement de souris.<br><br><br>\r\n\r\n- Au bas de l'\u00E9cran, on retrouve un panneau de configuration d'objet. Celui-ci apparait automatiquement lors de la s\u00E9lection unique d'un \u00E9l\u00E9ment de\r\n jeu et permettera de configurer manuellement la position, la rotation ainsi que la mise \u00E0 l'\u00E9chelle de l'objet s\u00E9lectionn\u00E9.<br><br><br>\r\n\r\n- Finalement, on retrouve une barre de menu en haut de l'\u00E9cran. Celle-ci offre la totalit\u00E9 des fonctionnalit\u00E9s du mode d'\u00E9dition. On y retrouve donc diff\u00E9rents menu;\r\nFichiers, \u00C9dition, Outils, Vues et Informations.\r\n");
		panelConsignes.add(txtrBienvenueDansSchmatix, BorderLayout.CENTER);

		JScrollPane scrollConsignes = new JScrollPane(txtrBienvenueDansSchmatix);
		panelConsignes.add(scrollConsignes);
		scrollConsignes.getVerticalScrollBar().setUnitIncrement(12);

		txtrBienvenueDansSchmatix.setCaretPosition(0);

		
		//section pour la description de chaque element
		JPanel panelElementIntermediaire = new JPanel();

		panelElementIntermediaire.setLayout(new BorderLayout(0, 0));
		tabbedPane.addTab("Informations sur les Éléments", null, panelElementIntermediaire, null);

		JPanel panelElement = new JPanel();
		panelElementIntermediaire.add(panelElement, BorderLayout.CENTER);
		panelElement.setLayout(new GridLayout(0, 3, -40, 5));

		JScrollPane scrollElement = new JScrollPane(panelElement);
		scrollElement.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_AS_NEEDED);
		scrollElement.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_AS_NEEDED);
		panelElementIntermediaire.add(scrollElement);
		scrollElement.getVerticalScrollBar().setUnitIncrement(16);

		JLabel lblImgSelect= new JLabel(new ImageIcon(getClass().getResource("/Images/icon_select.png")));
		panelElement.add(lblImgSelect);

		JLabel lblSelection = new JLabel(" Sélection   ");
		lblSelection.setHorizontalAlignment(SwingConstants.CENTER);
		lblSelection.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblSelection);
		lblSelection.setFont(font);

		JTextArea txtSelection = new JTextArea();
		panelElement.add(txtSelection);
		txtSelection.setWrapStyleWord(true);
		txtSelection.setText("Outil permettant de s\u00E9lectionner des \u00E9l\u00E9ments. CTRL-S");
		txtSelection.setLineWrap(true);
		txtSelection.setEditable(false);

		JLabel lblImgDeplacement = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_move.png")));
		panelElement.add(lblImgDeplacement);

		JLabel lblDeplacement = new JLabel(" Déplacement   ");
		lblDeplacement.setHorizontalAlignment(SwingConstants.CENTER);
		lblDeplacement.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblDeplacement);
		lblDeplacement.setFont(font);

		JTextArea txtrLaDelEst = new JTextArea();
		panelElement.add(txtrLaDelEst);
		txtrLaDelEst.setWrapStyleWord(true);
		txtrLaDelEst.setText("Outil de déplacement des éléments. À utiliser suite à une sélection. CTRL-D ");
		txtrLaDelEst.setLineWrap(true);
		txtrLaDelEst.setEditable(false);

		JLabel lblImgRotate = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_rotate.png")));
		panelElement.add(lblImgRotate);

		JLabel lblRotate = new JLabel(" Rotation   ");
		lblRotate.setHorizontalAlignment(SwingConstants.CENTER);
		lblRotate.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblRotate);
		lblRotate.setFont(font);

		JTextArea txtRotate = new JTextArea();
		panelElement.add(txtRotate);
		txtRotate.setWrapStyleWord(true);
		txtRotate.setText("Permet d'effectuer une rotation sur le ou les éléments sélecionné(s). Si plusieurs éléments sont sélectionnés, on effectue une rotation à partir de leur centre de rotation commun. CTRL-R");
		txtRotate.setLineWrap(true);
		txtRotate.setEditable(false);

		JLabel lblImgResize = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_resize.png")));
		panelElement.add(lblImgResize);

		JLabel lblResize = new JLabel(" Mise à l'échelle   ");
		lblResize.setHorizontalAlignment(SwingConstants.CENTER);
		lblResize.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblResize);
		lblResize.setFont(font);

		JTextArea txtResize = new JTextArea();
		panelElement.add(txtResize);
		txtResize.setWrapStyleWord(true);
		txtResize.setText("Permet de modifier la taille d'un ou plusieurs élément(s) sélectionné(s). CTRL-E");
		txtResize.setLineWrap(true);
		txtResize.setEditable(false);

		JLabel lblImgDuplication = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_duplication.png")));
		panelElement.add(lblImgDuplication);

		JLabel lblDuplication = new JLabel(" Duplication   ");
		lblDuplication.setHorizontalAlignment(SwingConstants.CENTER);
		lblDuplication.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblDuplication);
		lblDuplication.setFont(font);

		JTextArea txtDuplication = new JTextArea();
		panelElement.add(txtDuplication);
		txtDuplication.setWrapStyleWord(true);
		txtDuplication.setText("Permet de faire une copie exacte d'un élément ou plusieurs élément(s) sélectionné(s). CTRL-C");
		txtDuplication.setLineWrap(true);
		txtDuplication.setEditable(false);

		JLabel lblImgZoom = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_zoom.png")));
		panelElement.add(lblImgZoom);

		JLabel lblZoom = new JLabel(" Zoom   ");
		lblZoom.setHorizontalAlignment(SwingConstants.CENTER);
		lblZoom.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblZoom);
		lblZoom.setFont(font);

		JTextArea txtZoom = new JTextArea();
		panelElement.add(txtZoom);
		txtZoom.setWrapStyleWord(true);
		txtZoom.setText("L'outil loupe permet de se rapprocher ou de s'éloigner (ALT) à l'aide d'un rectangle elastique. CTRL-Z");
		txtZoom.setLineWrap(true);
		txtZoom.setEditable(false);

		JLabel lblImgStation = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_station.png")));
		panelElement.add(lblImgStation);

		JLabel lblStation = new JLabel(" Station   ");
		lblStation.setHorizontalAlignment(SwingConstants.CENTER);
		lblStation.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblStation);
		lblStation.setFont(font);

		JTextArea txtStation = new JTextArea();
		panelElement.add(txtStation);
		txtStation.setWrapStyleWord(true);
		txtStation.setText("Permet de créer une station à l'endroit désirer. CTRL-G");
		txtStation.setLineWrap(true);
		txtStation.setEditable(false);

		JLabel lblImgBonus = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_bonus.png")));
		panelElement.add(lblImgBonus);

		JLabel lblBonus = new JLabel(" Bonus Accélérateur   ");
		lblBonus.setHorizontalAlignment(SwingConstants.CENTER);
		lblBonus.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblBonus);
		lblBonus.setFont(font);

		JTextArea txtBonus = new JTextArea();
		panelElement.add(txtBonus);
		txtBonus.setWrapStyleWord(true);
		txtBonus.setEditable(false);
		txtBonus.setLineWrap(true);
		txtBonus.setText("Permet de créer un bonus accélérateur utilisable par un vaisseau lors de l'interception. CTRL-B");

		JLabel lblImgBarriere = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_barriere.png")));
		panelElement.add(lblImgBarriere);

		JLabel lblBarriere = new JLabel(" Barrière Protectrice   ");
		lblBarriere.setHorizontalAlignment(SwingConstants.CENTER);
		lblBarriere.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblBarriere);
		lblBarriere.setFont(font);

		JTextArea txtBarriere = new JTextArea();
		panelElement.add(txtBarriere);
		txtBarriere.setText("Permet de positionner une barrière protectrice. Utilisable en deux clic distincts représentant le point initial et final de la barrière. CTRL-M");
		txtBarriere.setWrapStyleWord(true);
		txtBarriere.setLineWrap(true);
		txtBarriere.setEditable(false);

		JLabel lblImgPortails = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_portals.png")));
		panelElement.add(lblImgPortails);

		JLabel lblPortails = new JLabel(" Portails   ");
		lblPortails.setHorizontalAlignment(SwingConstants.CENTER);
		lblPortails.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblPortails);
		lblPortails.setFont(font);

		JTextArea txtPortails = new JTextArea();
		txtPortails.setText("Permet de créer une paire de portails permettant une téléportation entre deux position de la zone de jeux. CTRL-P");
		panelElement.add(txtPortails);
		txtPortails.setWrapStyleWord(true);
		txtPortails.setLineWrap(true);
		txtPortails.setEditable(false);

		JLabel lblImgTest = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_test.png")));
		panelElement.add(lblImgTest);

		JLabel lblTest = new JLabel(" Source d'électromotance   ");
		lblTest.setHorizontalAlignment(SwingConstants.CENTER);
		lblTest.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblTest);
		lblTest.setFont(font);

		JTextArea txtTest = new JTextArea();
		txtTest.setText("Permet de passer en mode test. CTRL-T");
		panelElement.add(txtTest);
		txtTest.setWrapStyleWord(true);
		txtTest.setLineWrap(true);
		txtTest.setEditable(false);

		JLabel lblImgHome = new JLabel(new ImageIcon(getClass().getResource("/Images/icon_home.png")));
		panelElement.add(lblImgHome);

		JLabel lblHome = new JLabel(" Menu Principal   ");
		lblHome.setHorizontalAlignment(SwingConstants.CENTER);
		lblHome.setVerticalAlignment(SwingConstants.CENTER);
		panelElement.add(lblHome);
		lblHome.setFont(font);

		JTextArea txtMenu = new JTextArea();
		panelElement.add(txtMenu);
		txtMenu.setText("Permet de basculer au menu principal. CTRL-Q");
		txtMenu.setWrapStyleWord(true);
		txtMenu.setLineWrap(true);
		txtMenu.setEditable(false);

		
	}

	/**
	 * Permet de modifier l'onglet de l'aide sur lequel on est
	 * @param num - int : numero de l'onglet
	 */
	public void setTab(int num){
		this.tabbedPane.setSelectedIndex(num);
	}

}