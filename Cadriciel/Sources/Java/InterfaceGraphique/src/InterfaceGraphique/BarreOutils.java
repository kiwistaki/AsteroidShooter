package InterfaceGraphique;

import javax.imageio.ImageIO;
import javax.swing.ButtonGroup;
import javax.swing.ImageIcon;
import javax.swing.JPanel;
import javax.swing.JToggleButton;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.FlowLayout;
import java.awt.Image;
import java.io.IOException;


/**
 * @author Sacha L-Roussel
 * 
 * Classe d�finissant la barre d'outils latt�rale de la fen�tre d'�dition.
 * Elle contient un certain nombre de boutons permettant d'acc�der � des fonctions autrement dans la barre de menu
 * de la classe InterfaceEdition.
 *
 */
@SuppressWarnings("serial")
public class BarreOutils extends JPanel {
	
	private JToggleButton[] listeBoutons;
	private int largeurBoutons = 40;
	private int hauteurBoutons = 40;
	private int nbBoutons = 12;
	

	private final ButtonGroup buttonGroup = new ButtonGroup();

	
	/**
	 * Constructeur par d�faut de la barre d'outils.
	 * @param Aucuns param�tres
	 * @return Rien
	 */
	public BarreOutils() {
		
		//Gestionnaire d'action qui fait le traitement afin d'appeler la bonne m�thode parmis celles dans la classe d�marrage.
		GestionnaireBoutons gestionnaire = new GestionnaireBoutons(InputManager.getInstance());
		
		FlowLayout layout = new FlowLayout(FlowLayout.CENTER, 0, 1);
		setLayout(layout);
		
		listeBoutons = new JToggleButton[nbBoutons];
		
		for(int i=0; i<nbBoutons; i++){
			listeBoutons[i] = new JToggleButton();
			listeBoutons[i].setPreferredSize(new Dimension(largeurBoutons, hauteurBoutons));
			listeBoutons[i].addActionListener(gestionnaire);
			listeBoutons[i].setBorder(null);
			listeBoutons[i].setFocusable(false); // Permet d'�viter que le canvas perde le focus qui lui permet de r�ponse aux raccourcis clavier.
			buttonGroup.add(listeBoutons[i]);
			add(listeBoutons[i]);
		}
		
		setActionListeners();
		
		setBackground(new Color(50,50,50));
	
	}
	
	/**
	 * M�thode permettant d'acc�der au bouton en une position connue (� partir de 0)
	 * @param int position	Position connue du bouton (En ordre d'apparition)
	 * @return JToggleButton 	Retourne l'objet repr�sentt� par le bouton.
	 */
	public JToggleButton getButton(int position){
		return listeBoutons[position];
	}
	
	
	/**
	 * Permet de sp�cifier la taille qu'occuperont les boutons dans la barre d'outils
	 * @param larg	Largeur des boutons
	 * @param haut Hauteur des boutons
	 * @return void
	 */
	public void setBoutonsSize(int larg, int haut){
		for(int i = 0; i < nbBoutons; i++){
			listeBoutons[i].setSize(larg, haut);
			listeBoutons[i].setPreferredSize(new Dimension(larg, haut));
		}
	}

	
	/**
	 * Retourne la largeur des boutons
	 * @param Aucun
	 * @return int	Valeur enti�re repr�sentant la largeur du bouton.
	 */
	public int getLargeurBoutons(){
		return largeurBoutons;
	}
	
	/**
	 * Retourne la heuteur des boutons
	 * @param Aucuns param�tres
	 * @return int	Valeur entir�re repr�sentant la hauteur d'un bouton
	 */
	public int getHauteurBoutons(){
		return this.hauteurBoutons;
	}
	
	/**
	 * Retourne le nombre de boutons pr�sent dans la barre d'outils.
	 * @param Aucuns param�tres
	 * @return int	Entier qui repr�sente le nombre de boutons pr�sents
	 */
	public int getNbBoutons(){
		return nbBoutons;
	}
	
	/**
	 * M�thode priv�e permettant de s�parer la t�ches d'assignation des �couteurs
	 * d'�v�nements du reste de la classe BarreOutils.
	 * @param Aucuns param�tres
	 * @return Void
	 */
	private void setActionListeners(){
		Image img;
		Image imgTemp;
		
		
		listeBoutons[0].setActionCommand("Selection");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_select.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[0].setIcon(new ImageIcon(imgTemp));
			listeBoutons[0].setToolTipText("S�lection");
		} catch (IOException ex) {}
		
		
		listeBoutons[1].setActionCommand("Deplacement");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_move.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[1].setIcon(new ImageIcon(imgTemp));
			listeBoutons[1].setToolTipText("D�placement");
		} catch (IOException ex) {}
		
		
		listeBoutons[2].setActionCommand("Rotation");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_rotate.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[2].setIcon(new ImageIcon(imgTemp));
			listeBoutons[2].setToolTipText("Rotation");
		} catch (IOException ex) {}
		
		
		listeBoutons[3].setActionCommand("MiseAEchelle");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_resize.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[3].setIcon(new ImageIcon(imgTemp));
			listeBoutons[3].setToolTipText("Mise � �chelle");
		} catch (IOException ex) {}
		
		
		listeBoutons[4].setActionCommand("Duplication");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_duplication.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[4].setIcon(new ImageIcon(imgTemp));
			listeBoutons[4].setToolTipText("Duplication");
		} catch (IOException ex) {}
		
		
		listeBoutons[5].setActionCommand("Zoom");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_zoom.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[5].setIcon(new ImageIcon(imgTemp));
			listeBoutons[5].setToolTipText("Zoom");
		} catch (IOException ex) {}
		
		
		listeBoutons[6].setActionCommand("CreationStation");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_station.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[6].setIcon(new ImageIcon(imgTemp));
			listeBoutons[6].setToolTipText("Cr�er Station");
		} catch (IOException ex) {}
		
		
		listeBoutons[7].setActionCommand("CreationBonus");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_bonus.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[7].setIcon(new ImageIcon(imgTemp));
			listeBoutons[7].setToolTipText("Cr�er Bonus");
		} catch (IOException ex) {}
		
		
		listeBoutons[8].setActionCommand("CreationBarriere");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_barriere.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[8].setIcon(new ImageIcon(imgTemp));
			listeBoutons[8].setToolTipText("Cr�er Barri�re");
		} catch (IOException ex) {}
		
		
		listeBoutons[9].setActionCommand("CreationPortails");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_portals.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[9].setIcon(new ImageIcon(imgTemp));
			listeBoutons[9].setToolTipText("Cr�er Portails");
		} catch (IOException ex) {}
		
				
		listeBoutons[10].setActionCommand("ModeTest");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_test.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[10].setIcon(new ImageIcon(imgTemp));
			listeBoutons[10].setToolTipText("Passer en Mode Test");
		} catch (IOException ex) {}
		
		listeBoutons[11].setActionCommand("MenuPrincipal");
		try {
			img = ImageIO.read(getClass().getResource("/Images/icon_home.png"));
			imgTemp = img.getScaledInstance( (int) (largeurBoutons/1.25), (int) (hauteurBoutons/1.25), Image.SCALE_SMOOTH);
			listeBoutons[11].setIcon(new ImageIcon(imgTemp));
			listeBoutons[11].setToolTipText("Revenir au Menu Principal");
		} catch (IOException ex) {}
		
	}
	
	public void resetButtons(){
		
		for(int i=0; i<nbBoutons; i++){
			JToggleButton btnTemp = listeBoutons[i];
			if(btnTemp.isSelected()){
				btnTemp.setSelected(false);
				btnTemp.setBorder(null);
			}
			
		}
	}
	
	public ButtonGroup getButtonGroup(){
		return buttonGroup;
	}
}
