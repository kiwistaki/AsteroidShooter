package ca.polymtl.inf2990;

import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.util.Timer;
import java.util.TimerTask;
import java.awt.BorderLayout;
import java.awt.Canvas;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Point;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentEvent;
import java.awt.event.ComponentAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseAdapter;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JOptionPane;
import javax.swing.JSeparator;
import javax.swing.JToolBar;
import javax.swing.KeyStroke;
import javax.swing.SwingUtilities;
import javax.swing.WindowConstants;

import InterfaceGraphique.InputManager;


/**
 * Cette classe crée une fenêtre Java ainsi qu'un contexte OpenGL dans lequel
 * la librairie C++ pourra dessiner.
 * 
 * Il ne s'agit que d'un exemple des différentes fonctionnalités qu'il est
 * possible d'implanter en Java, notamment la création d'une fenêtre, d'un
 * contexte OpenGL, d'une barre de menus et d'une barre d'outils, ainsi que la
 * gestionnaire de certains événements.
 * 
 * CETTE CLASSE NE CONSTITUE PAS UN EXEMPLE DE BONNE PROGRAMMATION.  Elle est
 * monolithique et vise à être séparée en plusieurs classes, éventuellement dans
 * des paquetages différents, lorsque les véritables fonctionnalités seront
 * implantées.
 *
 * @author Martin Bisson
 * @date   2007-08-15
 */
public class Exemple implements Runnable {
   
   
   /**
    * Fonction principale de l'application qui constitue en fait son point
    * d'entrée.  Elle vérifie en premier si l'usager souhaite exécuter les
    * test unitaires (si l'argument est testsC++). Dans l'affirmative, elle
    * invoque l'appel des tests unitaires C++ via JNI et retourne le code
    * d'erreur renvoyé. Sinon, la fonction d'entrée procède au traitement
    * par défaut : elle se contente de créer un objet <code>Exemple</code>
    * et de l'invoquer dans le thread AWT.
    *
    * @param   args   Les paramètres passées à l'application par la ligne de
    *                 commande. Si le premier argument (args[0]) contient la
    *                 chaîne "testsC++", les tests unitaires C++ sont invoqués
    *                 et l'application quitte (retourne) immédiatement.
    */
   public static void main(String args[]) {
      
	  // Vérifier si nous exécuterons les tests unitaires... 
	  if (args.length >= 1 && args[0].equals("testsC++")) {
		  // Exécution des tests C++
		  int resultat = fctC_executerTests();
		  System.exit(resultat);
	  }
	  // Pas d'exécution des tests unitaires, crééons la fenêtre et affichons-là
	  else {
	      // Création de l'unique instance du contrôleur
	      final Exemple instance = new Exemple();
	      
	      // Création et affichage de la fenêtre principale
	      EventQueue.invokeLater(instance);
	  }
      
   }
   
   
   /**
    * Fonction qui crée l'interface graphique et le prépare à recevoir des
    * événements.  Cette fonction est appelée par le thread AWT afin que les
    * appels au GUI soit tous faits dans le même thread.
    */
   public void run() {
 
      // Construction de la fenêtre.
      construireFenetre();
      // Construction des menus.
      construireMenus();
      // Construction de la barre d'outils.
      construireBarreOutils();
      // Ajout des gestionnaires d'événements
      ajouterGestionnaires();
      // Affichage de la fenêtre.
      fenetre_.setVisible(true);
      
      // Activation de la minuterie appelée plusieurs fois par seconde pour
      // réafficher la fenêtre.
      activerMinuterie();
      
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
    * Fonction qui initialise un contexte OpenGL dans la fenêtre identifiée par
    * le canvas AWT passé en paramètre.  Cette fonction doit être la première à
    * être appelée, car la création de l'objet du modèle C++ s'attend à avoir un
    * contexte OpenGL valide.
    *
    * @param   canvas   Le canvas dans lequel créer le contexte OpenGL.
    */
   public static native void fctC_initialiserOpenGL( Canvas canvas );
   
   /**
    * Fonction qui libère le contexte OpenGL dans la fenêtre identifiée par le
    * canvas AWT passé en paramètre.  Cette fonction doit être la dernière à
    * être appelée, car elle libère également l'objet du modèle C++.
    *
    * @param   canvas   Le canvas dans lequel créer le contexte OpenGL.
    */
   public static native void fctC_libererOpenGL( Canvas canvas );
   
   /**
    * Fonction qui affiche la scène dans la fenêtre identifiée par le canvas AWT
    * passé en paramètre.
    *
    * @param   canvas   Le canvas dans lequel créer le contexte OpenGL.
    */
   public static native void fctC_dessinerOpenGL( Canvas canvas );
   
   /**
    * Fonction qui doit être appelée lorsque la fenêtre est redimensionnée afin
    * d'ajuster les paramètres de la machine à états d'OpenGL pour correspondre
    * aux nouvelles dimensions de la fenêtre.
    *
    * @param   largeur   La nouvelle largeur de la fenêtre.
    * @param   hauteur   La nouvelle hauteur de la fenêtre.
    */
   public static native void fctC_redimensionnerFenetre(
         int largeur, int hauteur
         );
   
   /**
    * Fonction qui anime le jeu d'un certain intervalle de temps.
    * 
    * Elle vise à être appelée de nombreuses fois par seconde.  Elle effectue
    * les différents calculs de physique et effectue un affichage.
    *
    * @param   temps   L'intervalle de temps à utiliser pour les différents
    *                  calculs.  On vise à faire correspondre cet invervalle de
    *                  temps au temps entre deux appels à la fonction.
    */
   public static native void fctC_animer(float temps);

   /**
    * Fonction qui applique un zoom avant sur le présent volume de vision.
    */
   public static native void fctC_zoomIn();
   
   /**
    * Fonction qui applique un zoom arrière sur le présent volume de vision.
    */
   public static native void fctC_zoomOut();
   
   /**
    * Fonction qui retourne le nombre moyen d'affichage par secondes.
    */
   public static native int obtenirAffichagesParSeconde();
   
   /**
    * Fonction qui exécute les jeux de tests unitaires C++.
    */
   public static native int fctC_executerTests();
   
   /**
    * Fonction qui envoie l'input du code Java vers le C++
    * @param x Position en x de la souris
    * @param y Position en y de la souris
    * @param bouton Le bouton sur lequel on a appuyé sur la souris
    * @param touche La touche sur laquel on a appuyé sur le clavier
    */
   public static native void fctC_envoyerInput(int x, int y, int bouton, int touche);
   
   /////////////////////////////////////////
   //                                     //
   //  FONCTIONS DE GESTION D'ÉVÉNEMENTS  //
   //                                     //
   /////////////////////////////////////////
   

   /**
    * Fonction appelée lorsque l'élément Nouveau du menu est actionné.
    */
   public void Nouveau() {
      signaler("L'élément Nouveau a été activé.");
   }
   /**
    * Fonction appelée lorsque l'élément Quitter du menu est actionné.
    */
   public void Quitter() {
      signaler("L'élément Quitter a été activé.");
   }
   /**
    * Fonction appelée lorsque le bouton Aide de la barre d'outils est actionné.
    */
   public void Aide() {
      signaler("L'élément Aide a été activé.");
   }
   /**
    * Fonction appelée lorsque le bouton Texte de la barre d'outils est
    * actionné.
    */
   public void Texte() {
      signaler("L'élément Texte a été activé.");
   }
   
   /**
    * Fonction appelée lorsque la touche "a" est appuyée.
    */
   public void appuyer_a() {
      signaler("La touche \"a\" a été appuyée.");
   }
   
   /**
    * Fonction appelée lorsque la touche "f" est appuyée.  Elle affiche le
    * nombre d'affichages par seconde.
    */
   public void appuyer_f() {
      System.out.println(
            "Le nombre d'affichages par seconde est: " +
            obtenirAffichagesParSeconde()
            );
   }
   
   
   
   
   /**
    * Cette classe implante l'interface <code>ActionListener</code> pour
    * répondre aux actions lancées par certains éléments d'interface comme les
    * menus et les boutons.  Elle utilise la réflexion Java pour trouver la
    * bonne fonction à appeler pour répondre à l'événement.
    *
    * Elle ne constitue pas une excellente solution à la gestion des événements,
    * mais vise plutôt à donner un exemple des possibilités de la réflexion Java
    * pour résoudre ce genre de problèmes.
    */
   private class GestionnaireAction implements ActionListener {
      
      /**
       * Constructeur qui ne fait qu'assigner le gestionnaire des actions reçues
       * par cet écouteur.
       *
       * @param   gestionnaire   Le gestionnaire des actions reçues par cet
       *                         écouteur.
       */
      public GestionnaireAction(Object gestionnaire) {
         gestionnaire_ = gestionnaire;
      }
      
      /**
       * Implantation de l'interface <code>ActionListener</code> qui gère les
       * actions provenant de certains événements d'interface.
       *
       * @param   evenement   L'événement correspondant à l'action.
       */
      public void actionPerformed(ActionEvent evenement) {
         
         String nom = evenement.getActionCommand();
         
         // On obtient la méthode par réflexion Java.
         try {
            @SuppressWarnings("rawtypes")
			Class[] typeParametres = {};
            Object[] parametres = {};
            
            Method methode = gestionnaire_.getClass().getMethod(
                  nom, typeParametres
                  );
            methode.invoke(gestionnaire_, parametres);
         }
         catch (NoSuchMethodException ex) {
            // ...
         }
         catch (IllegalAccessException ex) {
            // ...
         }
         catch (InvocationTargetException ex) {
            // ...
         }
         catch (SecurityException ex) {
            // ...
         }
         
      }

      // L'objet responsable de la gestion des actions.
      private Object gestionnaire_;
      
   }
   
   
   /**
    * Cette classe implante l'interface <code>KeyListener</code> pour répondre
    * aux événements du clavier.  Elle utilise la réflexion Java pour trouver la
    * bonne fonction à appeler pour répondre à l'événement.
    *
    * Elle ne constitue pas une excellente solution à la gestion des événements,
    * mais vise plutôt à donner un exemple des possibilités de la réflexion Java
    * pour résoudre ce genre de problèmes.
    */
   private class GestionnaireClavier extends KeyAdapter {
      
      /**
       * Constructeur qui ne fait qu'assigner le gestionnaire des actions reçues
       * par cet écouteur.
       *
       * @param   gestionnaire   Le gestionnaire des actions reçues par cet
       *                         écouteur.
       */
      public GestionnaireClavier(Object gestionnaire) {
         gestionnaire_ = gestionnaire;
      }
      
      /**
       * Implantation de l'interface <code>KeyListener</code> qui gère les
       * événements de tapage d'une touche.
       *
       * @param   evenement   L'événement correspondant à l'action.
       */
      public void keyTyped(KeyEvent evenement) {
         
         String nom = "appuyer_" + evenement.getKeyChar();
         
         // On obtient la méthode par réflexion Java.
         try {
            @SuppressWarnings("rawtypes")
			Class[] typeParametres = {};
            Object[] parametres = {};
            
            Method methode = gestionnaire_.getClass().getMethod(
                  nom, typeParametres
                  );
            methode.invoke(gestionnaire_, parametres);
         }
         catch (NoSuchMethodException ex) {
            // ...
         }
         catch (IllegalAccessException ex) {
            // ...
         }
         catch (InvocationTargetException ex) {
            // ...
         }
         catch (SecurityException ex) {
            // ...
         }
         
      }

      // L'objet responsable de la gestion des actions.
      private Object gestionnaire_;
      
   }
   
   
   
   
   /**
    * Cette fonction construit la fenêtre Java.
    */
   private void construireFenetre() {
      
      // Construction de la fenêtre.
      fenetre_ = new JFrame();
      fenetre_.setTitle("INF2990");
      fenetre_.getContentPane().setLayout(new BorderLayout());
      
      // Canvas AWT qui contiendra le contexte OpenGL.
      canvas_ = new Canvas();
      fenetre_.add(canvas_, BorderLayout.CENTER);
      
      fenetre_.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
      
      canvas_.setBackground(Color.MAGENTA);
      canvas_.setPreferredSize(new Dimension(500,500));
      
      // Cette commande doit être faite avant de créer le contexte OpenGL afin
      // de s'assurer que le canvas a véritablement été créé.
      fenetre_.pack();
      
      fctC_initialiserOpenGL(canvas_);
      
      canvas_.requestFocus();
      
   }
   
   /**
    * Cette fonction construit la barre de menus.
    */
   private void construireMenus() {
      
      // Création de la barre de menus.
      JMenuBar barre = new JMenuBar();

      JMenu menuFichier = new JMenu("Fichier");
      // On s'assure que les menus apparaîtront par-dessus l'OpenGL
      menuFichier.getPopupMenu().setLightWeightPopupEnabled(false);
      // On assigne un mnémonique.
      menuFichier.setMnemonic('F');
      
      // Gestionnaire des menus.
      GestionnaireAction gestionnaire = new GestionnaireAction(this);
      
      // Création des éléments du menu.
      JMenuItem elementNouveau = new JMenuItem("Nouveau");
      elementNouveau.setMnemonic('N');
      elementNouveau.setIcon(new ImageIcon(
            getClass().getResource("/ca/polymtl/inf2990/icones/nouveau.png")
            ));
      elementNouveau.setAccelerator(KeyStroke.getKeyStroke("ctrl N"));
      elementNouveau.setActionCommand("Nouveau");
      elementNouveau.addActionListener(gestionnaire);

      JMenuItem elementQuitter = new JMenuItem("Quitter");
      elementQuitter.setMnemonic('Q');
      elementQuitter.setAccelerator(KeyStroke.getKeyStroke("ctrl Q"));
      elementQuitter.setActionCommand("Quitter");
      elementQuitter.addActionListener(gestionnaire);

      // Ajout dans la barre
      menuFichier.add(elementNouveau);
      menuFichier.add(new JSeparator());
      menuFichier.add(elementQuitter);
      barre.add(menuFichier);
      
      fenetre_.setJMenuBar(barre);
   }
   
   /**
    * Cette fonction construit la barre d'outils.
    */
   private void construireBarreOutils() {
      
      JToolBar barre = new JToolBar();

      // Gestionnaire des boutons.
      GestionnaireAction gestionnaire = new GestionnaireAction(this);

      JButton boutonAide = new JButton();
      boutonAide.setIcon(new ImageIcon(
            getClass().getResource("/ca/polymtl/inf2990/icones/aide32x32.png")
            ));
      boutonAide.setActionCommand("Aide");
      boutonAide.addActionListener(gestionnaire);

      JButton boutonTexte = new JButton();
      boutonTexte.setText("Texte");
      boutonTexte.setActionCommand("Texte");
      boutonTexte.addActionListener(gestionnaire);

      // Ajout dans la barre
      barre.add(boutonAide);
      //barre.add(new JSeparator());
      barre.add(boutonTexte);
      
      fenetre_.add(barre, BorderLayout.NORTH);
   }
   
   /**
    * Cette fonction ajoute des gestionnaires d'événements pour la souris et
    * le clavier.
    */
   private void ajouterGestionnaires() {
      
      // Ajout d'un gestionnaire d'événements de souris.
      canvas_.addMouseListener(new MouseAdapter() {
         public void mousePressed(MouseEvent evenement) {
            System.out.println(
                  "La souris a été appuyée à la position (" +
                  evenement.getX() + " , " + evenement.getY() + ")"
                  );
         }
      });
      
      // Ajout d'un gestionnaire d'événements de clavier.
      canvas_.addKeyListener(new GestionnaireClavier(this));
      
      // Ajout d'un gestionnaire pour la redimension.
      canvas_.addComponentListener(new ComponentAdapter() {
         public void componentResized(ComponentEvent evenement) {
            fctC_redimensionnerFenetre(canvas_.getWidth(), canvas_.getHeight());
         }
      });
      
   }
   
   
   /**
    * Cette fonction active la minuterie qui appelle périodiquement une fonction
    * afin de rafraîchir constamment la fenêtre.
    */
   private void activerMinuterie() {
      
      Timer minuterie = new Timer();
      minuterie.scheduleAtFixedRate(new TimerTask() {
         public void run() {
            try {
               SwingUtilities.invokeAndWait(new Runnable() {
                  public void run() {
                     float temps = TEMPS_INTER_AFFICHAGE / 1000.0f;
                     // TEST
                     // On passe l'input par JNI jusqu'au C++
                     Point mousePosition = InputManager.getInstance().getMousePosition();
                     int boutton = InputManager.getInstance().getCurrentPressedButton();
                     int touche = InputManager.getInstance().getCurrentPressedKey();
                     fctC_envoyerInput(mousePosition.x, mousePosition.y, boutton, touche);
                     
                     fctC_animer(temps);
                     fctC_dessinerOpenGL(canvas_);
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
   
   
   
   /**
    * Fonction qui signale une erreur fatale.  Elle affiche le message d'erreur
    * dans une fenêtre de dialogue puis termine l'application.
    *
    * @param  message   Le message d'erreur à afficher.
    */
   private void signalerErreurFatale(String message) {
      
      signalerErreur(message);
      System.exit(-1);
      
   }
   
   
   /**
    * Fonction qui signale une erreur.  Elle affiche le message d'erreur dans
    * une fenêtre de dialogue.
    *
    * @param   message   Le message d'erreur à afficher.
    */
   private void signalerErreur(String message) {

      JOptionPane.showMessageDialog(
            null,
            message,
            "Erreur",
            JOptionPane.ERROR_MESSAGE
            );
      
   }
   
   
   /**
    * Fonction qui signale un message.  Elle affiche le message dans une
    * fenêtre de dialogue.
    *
    * @param   message   Le message à afficher.
    */
   private void signaler(String message) {

      JOptionPane.showMessageDialog(
            null,
            message,
            "Message",
            JOptionPane.INFORMATION_MESSAGE
            );
      
   }
   
   
   // Le temps souhaité entre 2 affichages, en millisecondes.
   static private final int TEMPS_INTER_AFFICHAGE = 20;
   
   // La fenêtre principale du programme.
   private JFrame fenetre_;
   // Le Canvas AWT qui contiendra le contexte OpenGL.
   private Canvas canvas_;
   
   
}
