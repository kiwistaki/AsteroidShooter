package InterfaceGraphique;

import java.awt.Canvas;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Toolkit;
import java.awt.event.WindowEvent;
import javax.swing.JFrame;
import javax.swing.JLayeredPane;
import javax.swing.WindowConstants;

public class FenetreCommune extends JFrame {
	private static final long serialVersionUID = 1L;
	
	private Dimension screenSize_;
	private int largeurEcran_;
	private int hauteurEcran_;
	private int largeurFenetre_;
	private int hauteurFenetre_;
	
	protected JLayeredPane contentPane_;
	protected Canvas canvas_;

	/**
	 * Constructeur par d�faut. On initialise le ContentPanel et le Canvas de
	 * la fen�tre
	 */
	public FenetreCommune() {
		super();

		definirDimensionsFenetre();
		definirContentPane();

		setDefaultCloseOperation(WindowConstants.HIDE_ON_CLOSE);
		
		// Ce qui est important c'est qu'on enl�ve JAMAIS le canvas du content
		// panel, �a fuck le contexte OpenGL.
		canvas_ = new Canvas();
		canvas_.setSize(getSize());
		contentPane_.add(canvas_);
		
		
		// Pour revenir au menu principal
		addWindowListener(new java.awt.event.WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				InputManager.getInstance().MenuPrincipal();
			}
		});
	}
	
	/**
	 * M�thode a appeller au d�but de la construction des diff�rentes fen�tres
	 * pour r�-initialiser le contenu de la fen�tre
	 */
	public void reinitialiserFenetre() {
		// Dat hack. On enl�ve tous les �l�ments sauf le canvas (premi�re position)
		// et on set la barre de menu � null
		for (int i = contentPane_.getComponents().length - 1; i >= 0; i--) {
			if (contentPane_.getComponents()[i].getClass() != canvas_.getClass()) {
				contentPane_.remove(i);
			}
		}
		
		this.setJMenuBar(null);
	}
	
	/**
	 * Permet de repositionner la fen�tre a son emplacement original avant de l'afficher ou de la r�afficher.  
	 * @param Aucun param�tres
	 * @return void
	 */
	public void resetPosition(){
		setBounds(largeurEcran_/2 - largeurFenetre_/2, hauteurEcran_/2 - hauteurFenetre_/2, largeurFenetre_, hauteurFenetre_);
	}

	/**
	 * Retourne le canvas contenu au centre de la fenetre d'edition
	 * @param Aucun param�tres
	 * @return Le canvas sur lequel le jeu est dessin� 
	 */
	public Canvas getCanvas() {
		return canvas_;
	}
	
	/**
	 * M�thode qui calcule les dimensions de l'ecran de l'appareil
	 * @param Aucun
	 * @return void
	 */
	private void definirDimensionsEcran() {
		//On va chercher la taille de l'ecran afin de d�terminer la taille et la position optimale de notre fenetre, peu importe l'ecran
		screenSize_ = Toolkit.getDefaultToolkit().getScreenSize();
		largeurEcran_ = (int) screenSize_.getWidth();
		hauteurEcran_ = (int) screenSize_.getHeight();
		
		Demarrage.fctC_setCanvasSizeMax(largeurEcran_, hauteurEcran_);
	}
	
	/**
	 * M�thode qui calcule la taille optimale de la fen�tre de jeu selon les dimensions de l'�cran de l'appareil
	 */
	private void definirDimensionsFenetre() {
		definirDimensionsEcran();
		
		largeurFenetre_ = (int) (largeurEcran_ / 2);
		hauteurFenetre_ = (int) (hauteurEcran_ / 1.5);
	}
	
	/**
	 * M�thode qui d�finit l'�tat de d�part du panel qui contient tous les �l�ments de l'interface
	 * @param Aucun
	 * @return void
	 */
	private void definirContentPane() {
		contentPane_ = new JLayeredPane() {			
			private static final long serialVersionUID = 1L;

			public void paintComponent(Graphics g) {
				super.paintComponent(g);
				Graphics2D g2d = (Graphics2D) g;
				Image img = Toolkit.getDefaultToolkit().getImage(MenuPrincipal.class.getResource("/Images/background2.jpg"));
				g2d.drawImage(img, 0, 0,this); 
			}
		};

		setContentPane(contentPane_);
		contentPane_.setLayout(null);
	}
	
}
