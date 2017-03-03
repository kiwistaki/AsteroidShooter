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
 * Cette classe cr�e une fen�tre Java ainsi qu'un contexte OpenGL dans lequel
 * la librairie C++ pourra dessiner.
 * 
 * Il ne s'agit que d'un exemple des diff�rentes fonctionnalit�s qu'il est
 * possible d'implanter en Java, notamment la cr�ation d'une fen�tre, d'un
 * contexte OpenGL, d'une barre de menus et d'une barre d'outils, ainsi que la
 * gestionnaire de certains �v�nements.
 * 
 * CETTE CLASSE NE CONSTITUE PAS UN EXEMPLE DE BONNE PROGRAMMATION.  Elle est
 * monolithique et vise � �tre s�par�e en plusieurs classes, �ventuellement dans
 * des paquetages diff�rents, lorsque les v�ritables fonctionnalit�s seront
 * implant�es.
 *
 * @author Martin Bisson
 * @date   2007-08-15
 */
public class Exemple implements Runnable {
   
   
   /**
    * Fonction principale de l'application qui constitue en fait son point
    * d'entr�e.  Elle v�rifie en premier si l'usager souhaite ex�cuter les
    * test unitaires (si l'argument est testsC++). Dans l'affirmative, elle
    * invoque l'appel des tests unitaires C++ via JNI et retourne le code
    * d'erreur renvoy�. Sinon, la fonction d'entr�e proc�de au traitement
    * par d�faut : elle se contente de cr�er un objet <code>Exemple</code>
    * et de l'invoquer dans le thread AWT.
    *
    * @param   args   Les param�tres pass�es � l'application par la ligne de
    *                 commande. Si le premier argument (args[0]) contient la
    *                 cha�ne "testsC++", les tests unitaires C++ sont invoqu�s
    *                 et l'application quitte (retourne) imm�diatement.
    */
   public static void main(String args[]) {
      
	  // V�rifier si nous ex�cuterons les tests unitaires... 
	  if (args.length >= 1 && args[0].equals("testsC++")) {
		  // Ex�cution des tests C++
		  int resultat = fctC_executerTests();
		  System.exit(resultat);
	  }
	  // Pas d'ex�cution des tests unitaires, cr��ons la fen�tre et affichons-l�
	  else {
	      // Cr�ation de l'unique instance du contr�leur
	      final Exemple instance = new Exemple();
	      
	      // Cr�ation et affichage de la fen�tre principale
	      EventQueue.invokeLater(instance);
	  }
      
   }
   
   
   /**
    * Fonction qui cr�e l'interface graphique et le pr�pare � recevoir des
    * �v�nements.  Cette fonction est appel�e par le thread AWT afin que les
    * appels au GUI soit tous faits dans le m�me thread.
    */
   public void run() {
 
      // Construction de la fen�tre.
      construireFenetre();
      // Construction des menus.
      construireMenus();
      // Construction de la barre d'outils.
      construireBarreOutils();
      // Ajout des gestionnaires d'�v�nements
      ajouterGestionnaires();
      // Affichage de la fen�tre.
      fenetre_.setVisible(true);
      
      // Activation de la minuterie appel�e plusieurs fois par seconde pour
      // r�afficher la fen�tre.
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
    * Fonction qui initialise un contexte OpenGL dans la fen�tre identifi�e par
    * le canvas AWT pass� en param�tre.  Cette fonction doit �tre la premi�re �
    * �tre appel�e, car la cr�ation de l'objet du mod�le C++ s'attend � avoir un
    * contexte OpenGL valide.
    *
    * @param   canvas   Le canvas dans lequel cr�er le contexte OpenGL.
    */
   public static native void fctC_initialiserOpenGL( Canvas canvas );
   
   /**
    * Fonction qui lib�re le contexte OpenGL dans la fen�tre identifi�e par le
    * canvas AWT pass� en param�tre.  Cette fonction doit �tre la derni�re �
    * �tre appel�e, car elle lib�re �galement l'objet du mod�le C++.
    *
    * @param   canvas   Le canvas dans lequel cr�er le contexte OpenGL.
    */
   public static native void fctC_libererOpenGL( Canvas canvas );
   
   /**
    * Fonction qui affiche la sc�ne dans la fen�tre identifi�e par le canvas AWT
    * pass� en param�tre.
    *
    * @param   canvas   Le canvas dans lequel cr�er le contexte OpenGL.
    */
   public static native void fctC_dessinerOpenGL( Canvas canvas );
   
   /**
    * Fonction qui doit �tre appel�e lorsque la fen�tre est redimensionn�e afin
    * d'ajuster les param�tres de la machine � �tats d'OpenGL pour correspondre
    * aux nouvelles dimensions de la fen�tre.
    *
    * @param   largeur   La nouvelle largeur de la fen�tre.
    * @param   hauteur   La nouvelle hauteur de la fen�tre.
    */
   public static native void fctC_redimensionnerFenetre(
         int largeur, int hauteur
         );
   
   /**
    * Fonction qui anime le jeu d'un certain intervalle de temps.
    * 
    * Elle vise � �tre appel�e de nombreuses fois par seconde.  Elle effectue
    * les diff�rents calculs de physique et effectue un affichage.
    *
    * @param   temps   L'intervalle de temps � utiliser pour les diff�rents
    *                  calculs.  On vise � faire correspondre cet invervalle de
    *                  temps au temps entre deux appels � la fonction.
    */
   public static native void fctC_animer(float temps);

   /**
    * Fonction qui applique un zoom avant sur le pr�sent volume de vision.
    */
   public static native void fctC_zoomIn();
   
   /**
    * Fonction qui applique un zoom arri�re sur le pr�sent volume de vision.
    */
   public static native void fctC_zoomOut();
   
   /**
    * Fonction qui retourne le nombre moyen d'affichage par secondes.
    */
   public static native int obtenirAffichagesParSeconde();
   
   /**
    * Fonction qui ex�cute les jeux de tests unitaires C++.
    */
   public static native int fctC_executerTests();
   
   /**
    * Fonction qui envoie l'input du code Java vers le C++
    * @param x Position en x de la souris
    * @param y Position en y de la souris
    * @param bouton Le bouton sur lequel on a appuy� sur la souris
    * @param touche La touche sur laquel on a appuy� sur le clavier
    */
   public static native void fctC_envoyerInput(int x, int y, int bouton, int touche);
   
   /////////////////////////////////////////
   //                                     //
   //  FONCTIONS DE GESTION D'�V�NEMENTS  //
   //                                     //
   /////////////////////////////////////////
   

   /**
    * Fonction appel�e lorsque l'�l�ment Nouveau du menu est actionn�.
    */
   public void Nouveau() {
      signaler("L'�l�ment Nouveau a �t� activ�.");
   }
   /**
    * Fonction appel�e lorsque l'�l�ment Quitter du menu est actionn�.
    */
   public void Quitter() {
      signaler("L'�l�ment Quitter a �t� activ�.");
   }
   /**
    * Fonction appel�e lorsque le bouton Aide de la barre d'outils est actionn�.
    */
   public void Aide() {
      signaler("L'�l�ment Aide a �t� activ�.");
   }
   /**
    * Fonction appel�e lorsque le bouton Texte de la barre d'outils est
    * actionn�.
    */
   public void Texte() {
      signaler("L'�l�ment Texte a �t� activ�.");
   }
   
   /**
    * Fonction appel�e lorsque la touche "a" est appuy�e.
    */
   public void appuyer_a() {
      signaler("La touche \"a\" a �t� appuy�e.");
   }
   
   /**
    * Fonction appel�e lorsque la touche "f" est appuy�e.  Elle affiche le
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
    * r�pondre aux actions lanc�es par certains �l�ments d'interface comme les
    * menus et les boutons.  Elle utilise la r�flexion Java pour trouver la
    * bonne fonction � appeler pour r�pondre � l'�v�nement.
    *
    * Elle ne constitue pas une excellente solution � la gestion des �v�nements,
    * mais vise plut�t � donner un exemple des possibilit�s de la r�flexion Java
    * pour r�soudre ce genre de probl�mes.
    */
   private class GestionnaireAction implements ActionListener {
      
      /**
       * Constructeur qui ne fait qu'assigner le gestionnaire des actions re�ues
       * par cet �couteur.
       *
       * @param   gestionnaire   Le gestionnaire des actions re�ues par cet
       *                         �couteur.
       */
      public GestionnaireAction(Object gestionnaire) {
         gestionnaire_ = gestionnaire;
      }
      
      /**
       * Implantation de l'interface <code>ActionListener</code> qui g�re les
       * actions provenant de certains �v�nements d'interface.
       *
       * @param   evenement   L'�v�nement correspondant � l'action.
       */
      public void actionPerformed(ActionEvent evenement) {
         
         String nom = evenement.getActionCommand();
         
         // On obtient la m�thode par r�flexion Java.
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
    * Cette classe implante l'interface <code>KeyListener</code> pour r�pondre
    * aux �v�nements du clavier.  Elle utilise la r�flexion Java pour trouver la
    * bonne fonction � appeler pour r�pondre � l'�v�nement.
    *
    * Elle ne constitue pas une excellente solution � la gestion des �v�nements,
    * mais vise plut�t � donner un exemple des possibilit�s de la r�flexion Java
    * pour r�soudre ce genre de probl�mes.
    */
   private class GestionnaireClavier extends KeyAdapter {
      
      /**
       * Constructeur qui ne fait qu'assigner le gestionnaire des actions re�ues
       * par cet �couteur.
       *
       * @param   gestionnaire   Le gestionnaire des actions re�ues par cet
       *                         �couteur.
       */
      public GestionnaireClavier(Object gestionnaire) {
         gestionnaire_ = gestionnaire;
      }
      
      /**
       * Implantation de l'interface <code>KeyListener</code> qui g�re les
       * �v�nements de tapage d'une touche.
       *
       * @param   evenement   L'�v�nement correspondant � l'action.
       */
      public void keyTyped(KeyEvent evenement) {
         
         String nom = "appuyer_" + evenement.getKeyChar();
         
         // On obtient la m�thode par r�flexion Java.
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
    * Cette fonction construit la fen�tre Java.
    */
   private void construireFenetre() {
      
      // Construction de la fen�tre.
      fenetre_ = new JFrame();
      fenetre_.setTitle("INF2990");
      fenetre_.getContentPane().setLayout(new BorderLayout());
      
      // Canvas AWT qui contiendra le contexte OpenGL.
      canvas_ = new Canvas();
      fenetre_.add(canvas_, BorderLayout.CENTER);
      
      fenetre_.setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);
      
      canvas_.setBackground(Color.MAGENTA);
      canvas_.setPreferredSize(new Dimension(500,500));
      
      // Cette commande doit �tre faite avant de cr�er le contexte OpenGL afin
      // de s'assurer que le canvas a v�ritablement �t� cr��.
      fenetre_.pack();
      
      fctC_initialiserOpenGL(canvas_);
      
      canvas_.requestFocus();
      
   }
   
   /**
    * Cette fonction construit la barre de menus.
    */
   private void construireMenus() {
      
      // Cr�ation de la barre de menus.
      JMenuBar barre = new JMenuBar();

      JMenu menuFichier = new JMenu("Fichier");
      // On s'assure que les menus appara�tront par-dessus l'OpenGL
      menuFichier.getPopupMenu().setLightWeightPopupEnabled(false);
      // On assigne un mn�monique.
      menuFichier.setMnemonic('F');
      
      // Gestionnaire des menus.
      GestionnaireAction gestionnaire = new GestionnaireAction(this);
      
      // Cr�ation des �l�ments du menu.
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
    * Cette fonction ajoute des gestionnaires d'�v�nements pour la souris et
    * le clavier.
    */
   private void ajouterGestionnaires() {
      
      // Ajout d'un gestionnaire d'�v�nements de souris.
      canvas_.addMouseListener(new MouseAdapter() {
         public void mousePressed(MouseEvent evenement) {
            System.out.println(
                  "La souris a �t� appuy�e � la position (" +
                  evenement.getX() + " , " + evenement.getY() + ")"
                  );
         }
      });
      
      // Ajout d'un gestionnaire d'�v�nements de clavier.
      canvas_.addKeyListener(new GestionnaireClavier(this));
      
      // Ajout d'un gestionnaire pour la redimension.
      canvas_.addComponentListener(new ComponentAdapter() {
         public void componentResized(ComponentEvent evenement) {
            fctC_redimensionnerFenetre(canvas_.getWidth(), canvas_.getHeight());
         }
      });
      
   }
   
   
   /**
    * Cette fonction active la minuterie qui appelle p�riodiquement une fonction
    * afin de rafra�chir constamment la fen�tre.
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
    * dans une fen�tre de dialogue puis termine l'application.
    *
    * @param  message   Le message d'erreur � afficher.
    */
   private void signalerErreurFatale(String message) {
      
      signalerErreur(message);
      System.exit(-1);
      
   }
   
   
   /**
    * Fonction qui signale une erreur.  Elle affiche le message d'erreur dans
    * une fen�tre de dialogue.
    *
    * @param   message   Le message d'erreur � afficher.
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
    * fen�tre de dialogue.
    *
    * @param   message   Le message � afficher.
    */
   private void signaler(String message) {

      JOptionPane.showMessageDialog(
            null,
            message,
            "Message",
            JOptionPane.INFORMATION_MESSAGE
            );
      
   }
   
   
   // Le temps souhait� entre 2 affichages, en millisecondes.
   static private final int TEMPS_INTER_AFFICHAGE = 20;
   
   // La fen�tre principale du programme.
   private JFrame fenetre_;
   // Le Canvas AWT qui contiendra le contexte OpenGL.
   private Canvas canvas_;
   
   
}
