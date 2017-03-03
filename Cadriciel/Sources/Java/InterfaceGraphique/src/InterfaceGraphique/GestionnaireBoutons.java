package InterfaceGraphique;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

import javax.swing.JToggleButton;

/**
 *Classe permettant de gérer les actions des boutons (par réflexion) permettant ainsi de délocaliser
 *les méthodes appelées, et de les mettre dans la classe InputManager. Aussi, de cette manière, on
 *a besoin que d'un seul ActionPerformed qui gère tous les évènements lié aux boutons
 */
public class GestionnaireBoutons implements ActionListener {
    
    // L'objet responsable de la gestion des actions.
    private Object gestionnaire_;
    
    private JToggleButton bouton;
    
	/**
	 * Bouton présentement sélectionné pour pouvoir le déselectionné si on
	 * appuie sur un autre bouton.
	 */
	private JToggleButton boutonSelectionne_ = null;
	
    /**
     * Constructeur qui ne fait qu'assigner le gestionnaire des actions reçues
     * par cet écouteur.
     *
     * @param   gestionnaire   Le gestionnaire des actions reçues par cet
     *                         écouteur.
     */
    public GestionnaireBoutons (Object gestionnaire) {
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
	
	    		// MEGA HACK permet de ne pas aller dans la fonction avec la réflection
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


