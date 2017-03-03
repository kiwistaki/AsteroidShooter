package InterfaceGraphique;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import javax.swing.JToggleButton;

/**
 *Classe permettant de g�rer les actions des boutons (par r�flexion) permettant ainsi de d�localiser
 *les m�thodes appel�es, et de les mettre dans la classe InputManager. Aussi, de cette mani�re, on
 *a besoin que d'un seul ActionPerformed qui g�re tous les �v�nements li� aux boutons
 */
public class GestionnaireBoutons implements ActionListener {
    
    // L'objet responsable de la gestion des actions.
    private Object gestionnaire_;
    
    private JToggleButton bouton;
    
	/**
	 * Bouton pr�sentement s�lectionn� pour pouvoir le d�selectionn� si on
	 * appuie sur un autre bouton.
	 */
	private JToggleButton boutonSelectionne_ = null;
	
    /**
     * Constructeur qui ne fait qu'assigner le gestionnaire des actions re�ues
     * par cet �couteur.
     *
     * @param   gestionnaire   Le gestionnaire des actions re�ues par cet
     *                         �couteur.
     */
    public GestionnaireBoutons (Object gestionnaire) {
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
       
	    try{
	    	 bouton =  (JToggleButton) evenement.getSource();
	    }catch(Exception e){
	    	
	    }
	    
	    if(bouton != null){


    		
	    	if(bouton == boutonSelectionne_){
	
	    		InputManager.getInstance().resetButtons();
	    		
	    		bouton.setBorder(null);
	    		boutonSelectionne_ = null;
	    		Demarrage.fctC_annulerCommande();
	
	    		// MEGA HACK permet de ne pas aller dans la fonction avec la r�flection
	    		nom = "derp derp";
	    		
	    		return;
	    		
	    	}


    		boutonSelectionne_ = bouton;
	    	

	    }

       
       try {
          @SuppressWarnings("rawtypes")
          Class[] typeParametres = {};
          Object[] parametres = {};
          
          Method methode = gestionnaire_.getClass().getMethod(nom, typeParametres);
          methode.invoke(gestionnaire_, parametres);
       }
       catch (NoSuchMethodException ex) {
          
       }
       catch (IllegalAccessException ex) {
          
       }
       catch (InvocationTargetException ex) {
          
       }
       catch (SecurityException ex) {
          
       }
       
    }    
 }


