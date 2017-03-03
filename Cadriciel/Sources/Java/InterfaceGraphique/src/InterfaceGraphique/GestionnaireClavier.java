package InterfaceGraphique;

import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

/**
 *Classe permettant de gérer les actions du clavier (par réflexion) permettant ainsi de délocaliser
 *les méthodes appelées, et de les mettre dans la classe InputManager. Aussi, de cette manière, on
 *a besoin que d'un seul KeyEvent qui gère tous les évènements du clavier
 */
public class GestionnaireClavier extends KeyAdapter {


	// L'objet responsable de la gestion des actions.
	private Object gestionnaire_;

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
	 * Implantation de l'interface KeyListener qui gère les
	 * événements d'une touche enfoncée.
	 *
	 * @param   evenement   L'événement correspondant à l'action.
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
		
		// On obtient la méthode par réflexion Java.
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
	 * Méthode appelée lorsqu'une touche de clavier est relaché
	 * @param evenement	Evenement lié a l'action du relachement de clic
	 * @return void
	 */
	public void keyReleased(KeyEvent evenement){
		InputManager.getInstance().keyReleased(evenement); 
		
	}
}


