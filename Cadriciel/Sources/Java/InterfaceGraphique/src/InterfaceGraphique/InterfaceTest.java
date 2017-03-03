package InterfaceGraphique;

import java.awt.Color;
import java.awt.Toolkit;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import java.awt.event.KeyEvent;
import java.util.HashSet;

import javax.swing.ButtonGroup;
import javax.swing.JLayeredPane;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.KeyStroke;

public class InterfaceTest extends InterfaceGenerique {

	private JMenuBar menuBar;
	private final ButtonGroup buttonGroup = new ButtonGroup();
	private FenetreCommune fenetre_;
	
	private JRadioButtonMenuItem  btnVueOrtho;
	private JRadioButtonMenuItem  btnVueOrbite;

	public InterfaceTest(FenetreCommune fenetre) {
		fenetre_ = fenetre;
		fenetre_.reinitialiserFenetre();
		
		//Gestionnaire d'action qui fait le traitement afin d'appeler la bonne méthode parmis celles dans la classe démarrage.
		GestionnaireBoutons gestionnaire = new GestionnaireBoutons(InputManager.getInstance());
		
		contentPane_ = (JLayeredPane)fenetre.getContentPane();
		canvas_ = fenetre.getCanvas();
		
		//Menu Supérieur
		menuBar = new JMenuBar();
		fenetre_.setJMenuBar(menuBar);
		
		//Fichier
		JMenu menuFichier = new JMenu("Fichier");
		menuBar.add(menuFichier);
		
		JMenuItem btnMenuPrinc = new JMenuItem("Menu principal");
		btnMenuPrinc.setAccelerator(KeyStroke.getKeyStroke('Q', Toolkit.getDefaultToolkit().getMenuShortcutKeyMask()));
		btnMenuPrinc.addActionListener(gestionnaire);
		btnMenuPrinc.setActionCommand("MenuPrincipal");
		menuFichier.add(btnMenuPrinc);
		
		JMenuItem btnMenuEdition = new JMenuItem("Fenêtre d'édition");
		btnMenuEdition.addActionListener(gestionnaire);
		btnMenuEdition.setActionCommand("FenetreEdition");
		menuFichier.add(btnMenuEdition);
		
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
		
		fenetre_.addComponentListener(new ComponentAdapter() {
			@Override
			public void componentResized(ComponentEvent arg0) {
				redimensionnerCanvas();
			}
		});

		definirCanvas();
		fenetre_.setTitle("Test");
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
		newCanvasWidth = contentPane_.getWidth() - 10;
		newCanvasHeight = (int) (newCanvasWidth/aspectRatio_);

		//On vérifie si l'état courant fait en sorte de faire dépasser le canvas de la fenetre, si oui on modifie le
		//changement afin de calculer le ration d'aspect selon la hauteur de la fenêtre.
		if (newCanvasHeight + 10 > contentPane_.getHeight()) {
			newCanvasHeight = contentPane_.getHeight() - 10;
			newCanvasWidth = (int) (newCanvasHeight*aspectRatio_);
		}

		canvas_.setSize(newCanvasWidth, newCanvasHeight);
		canvas_.setLocation(contentPane_.getWidth()/2 - canvas_.getWidth()/2, contentPane_.getHeight()/2 - canvas_.getHeight()/2);

		Demarrage.fctC_redimensionnerFenetre(newCanvasWidth, newCanvasHeight);
	}
	
	/**
	 * Méthode qui définit l'état de base du canvas de dessin
	 * @param Aucun
	 * @return void
	 */
	protected void definirCanvas() {
		canvas_.setSize(contentPane_.getWidth() - 20, (int) ( (contentPane_.getWidth())/aspectRatio_) );
		canvas_.setLocation(contentPane_.getWidth()/2 - canvas_.getWidth()/2, contentPane_.getHeight()/2 - canvas_.getHeight()/2);
		canvas_.setBackground(new Color(200, 20, 200));
		canvas_.setIgnoreRepaint(true); // Permet d'éviter le flickering // voir aussi la méthode dans configuration() de la classe démarrage
	}
	
	public void run(float temps) {
		if(!InputManager.getInstance().getModePause()){
			int scroll = envoyerInput();
			
			int key = InputManager.getInstance().getCurrentPressedKey();
			
			if(scroll < 0 || key == KeyEvent.VK_EQUALS){
				Demarrage.fctC_zoomIn();
			} else if (scroll > 0 || key == KeyEvent.VK_MINUS){
				Demarrage.fctC_zoomOut();
			}
			
			HashSet<Integer> ensembleTouches = InputManager.getInstance().getPressedKeys();
			int[] touches = new int[ensembleTouches.size()];
			int idx = 0;
			for (int touche : ensembleTouches) {
				touches[idx] = touche;
				idx += 1;
			}
			
			Demarrage.fctC_multipleInputVaisseau(touches, touches.length);
			
			Demarrage.fctC_animer(temps);
			fenetre_.setJMenuBar(null);
		}else{
			fenetre_.setJMenuBar(menuBar);
		}
		
		// Permet de verifier le contenu d'affichage
		fenetre_.validate();
		Demarrage.fctC_dessinerOpenGL(canvas_, InputManager.getInstance().getModePause());
	}

	@Override
	public void setBoutonOrtho(boolean estOrtho){
		
		if(estOrtho){
			btnVueOrbite.setSelected(false);
			btnVueOrtho.setSelected(true);
		}else{
			btnVueOrbite.setSelected(true);
			btnVueOrtho.setSelected(false);
		}
	}

}