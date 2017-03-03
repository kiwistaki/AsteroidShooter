package InterfaceGraphique;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 *Classe permettant de g�rer les actions du clavier (par r�flexion) permettant ainsi de d�localiser
 *les m�thodes appel�es, et de les mettre dans la classe InputManager. Aussi, de cette mani�re, on
 *a besoin que d'un seul KeyEvent qui g�re tous les �v�nements du clavier
 */
public class GestionnaireClavier extends KeyAdapter {


	// L'objet responsable de la gestion des actions.
	private Object gestionnaire_;

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
	 * Implantation de l'interface KeyListener qui g�re les
	 * �v�nements d'une touche enfonc�e.
	 *
	 * @param   evenement   L'�v�nement correspondant � l'action.
	 */
	public void keyPressed(KeyEvent evenement){
		String nom;
		
		InputManager.getInstance().keyPressed(evenement);
		
		if (evenement.getKeyChar() == KeyEvent.VK_ESCAPE ) {
			nom = "appuyer_ESC";
		} else if (evenement.getKeyChar() == KeyEvent.VK_BACK_SPACE) {
			nom = "appuyer_backspace";
		} else {
			nom = "appuyer_" + evenement.getKeyChar();
		}
		
		// On obtient la m�thode par r�flexion Java.
		try {
			@SuppressWarnings("rawtypes")
			Class[] typeParametres = {};
			Object[] parametres = {};

			Method methode = gestionnaire_.getClass().getMethod(nom, typeParametres);
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
	
	/**
	 * M�thode appel�e lorsqu'une touche de clavier est relach�
	 * @param evenement	Evenement li� a l'action du relachement de clic
	 * @return void
	 */
	public void keyReleased(KeyEvent evenement){
		InputManager.getInstance().keyReleased(evenement); 
		
	}
}


