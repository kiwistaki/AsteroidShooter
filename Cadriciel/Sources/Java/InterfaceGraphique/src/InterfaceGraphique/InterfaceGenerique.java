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
	 * Cette m�thode doit �tre surcharg�e par les classes enfants et servira
	 * de boucle principale.
	 * @param temps Le temps depuis la derni�re frame
	 */
	public abstract void run(float temps);
	
	/**
	 * M�thode qui permet d'envoyer les inputs de clavier et souris � la librairie C++ via le lien JNI
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
