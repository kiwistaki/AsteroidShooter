package InterfaceGraphique;

import java.awt.Canvas;
import java.awt.Point;

import javax.swing.JLayeredPane;

public abstract class InterfaceGenerique {

	protected JLayeredPane contentPane_;
	protected Canvas canvas_;
	
	protected final double aspectRatio_ = (1.78); // 16:9
	
	static protected final int TEMPS_INTER_AFFICHAGE = 20;
	
	/**
	 * Cette méthode doit être surchargée par les classes enfants et servira
	 * de boucle principale.
	 * @param temps Le temps depuis la dernière frame
	 */
	public abstract void run(float temps);
	
	/**
	 * Méthode qui permet d'envoyer les inputs de clavier et souris à la librairie C++ via le lien JNI
	 * @param Aucun
	 * @return La valeur du scroll
	 */
	protected int envoyerInput() {
		// On passe l'input par JNI jusqu'au C++
		Point mousePosition = InputManager.getInstance().getMousePosition();
		int boutton = InputManager.getInstance().getCurrentPressedButton();
		int touche = InputManager.getInstance().getCurrentPressedKey();
		int scroll = InputManager.getInstance().getCurrentScrolledMouseWheel();
		
		Demarrage.fctC_envoyerInput(mousePosition.x, mousePosition.y, boutton, touche, scroll);
		
		return scroll;
	}
	
	public void setBoutonOrtho(boolean estOrtho){
		
	}
	
	public void resetButtons(){
		
	}

}
