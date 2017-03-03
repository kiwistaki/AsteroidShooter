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
import javax.swing.JOptionPane;
import javax.swing.JRadioButtonMenuItem;
import javax.swing.KeyStroke;

public class InterfacePartieRapide extends InterfaceGenerique {

	private JMenuBar 			menuBar;
	private final ButtonGroup 	buttonGroup = new ButtonGroup();
	private FenetreCommune 		fenetre_;
	private int					lastTime = -1;
	private JRadioButtonMenuItem  btnVueOrtho;
	private JRadioButtonMenuItem  btnVueOrbite;

	public InterfacePartieRapide(FenetreCommune fenetre) {
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
		fenetre_.setTitle("Partie rapide");
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
		
			int statut = Demarrage.fctC_getStatutPartie();
			
			if (statut == 0) {				
				int scroll = envoyerInput();
				
				int key = InputManager.getInstance().getCurrentPressedKey();
				
				if(btnVueOrbite.isSelected()){
					if(scroll < 0 || key == KeyEvent.VK_EQUALS){
						Demarrage.fctC_zoomIn();
					} else if (scroll > 0 || key == KeyEvent.VK_MINUS){
						Demarrage.fctC_zoomOut();
					}
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
				
				int tempsJeu = Demarrage.fctC_getTempsPartie();
				
				// TEMP pour affichage
				if (tempsJeu != lastTime) {
					//System.out.println(tempsJeu);
					lastTime = tempsJeu;
				}
			} else if (statut == -1) {
				InputManager.getInstance().getPressedKeys().clear();
				rejouer(false);
			} else if (statut == 1) {
				InputManager.getInstance().getPressedKeys().clear();
				rejouer(true);
			}
		}else{
			fenetre_.setJMenuBar(menuBar);
		}
		
		// Permet de verifier le contenu d'affichage
		fenetre_.validate();
		Demarrage.fctC_dessinerOpenGL(canvas_, InputManager.getInstance().getModePause());
	}
	
	public void rejouer(boolean win) {
		int result;
		
		if (win) {
			result = JOptionPane.showOptionDialog(null, "Félicitations! Une fois de plus, ces satanés astéroïdes ont été" +
					" repoussés! Étant le nouveau maître de l'univers, vous avez le choix" +
					" de recommencer cette campagne éprouvante ou d'aller faire un petit" +
					" dodo bien mérité.\n\nAppuyez sur oui pour recommencer la campagne" +
					" ou sur non pour aller au menu principal.", "On a gagné! On a gagné! On a gagné!", JOptionPane.YES_NO_OPTION, JOptionPane.INFORMATION_MESSAGE, null, null, null);
		} else {
			result = JOptionPane.showOptionDialog(null, "Malheureusement, ces satanés astéroïdes n'ont pas été" +
					" repoussés! N'étant le nouveau maître de l'univers, vous avez le choix" +
					" de recommencer cette campagne éprouvante ou d'aller noyer votre" +
					" peine.\n\nAppuyez sur oui pour recommencer la campagne" +
					" ou sur non pour aller au menu principal.", "Hélas, vous avez perdu...", JOptionPane.YES_NO_OPTION, JOptionPane.INFORMATION_MESSAGE, null, null, null);
		}
		// result == 0 pour 'yes' et 1 pour 'no'
		if (result == 0) {
			//InputManager.getInstance().PartieRapide();
			Demarrage.fctC_initialiserModePartieRapide(InputManager.getInstance().coop_, InputManager.getInstance().joueur2_, InputManager.getInstance().nomFichier_);
			redimensionnerCanvas();
		} else {
			InputManager.getInstance().MenuPrincipal();
		}
	}
	
	@Override
	public void setBoutonOrtho(boolean estOrtho){
		
		btnVueOrbite.setSelected(!estOrtho);
		btnVueOrtho.setSelected(estOrtho);
	
	}
}