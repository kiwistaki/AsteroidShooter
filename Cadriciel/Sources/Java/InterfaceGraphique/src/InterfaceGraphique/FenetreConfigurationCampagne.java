package InterfaceGraphique;

import java.io.*;
import java.util.ArrayList;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.Toolkit;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;

import javax.swing.BorderFactory;
import javax.swing.Box;
import javax.swing.BoxLayout;
import javax.swing.ButtonGroup;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JList;
import javax.swing.JPanel;
import javax.swing.JRadioButton;
import javax.swing.JScrollPane;
import javax.swing.ListSelectionModel;
import javax.swing.WindowConstants;
import javax.swing.event.ListSelectionEvent;
import javax.swing.event.ListSelectionListener;

public class FenetreConfigurationCampagne extends JFrame {

	private static final long serialVersionUID = 1L;
	
	private final int 			LARGEUR_FENETRE = 500;
	private final int 			HAUTEUR_FENETRE = 500;
	private final String		REPERTOIRE_CARTES = System.getProperty("user.dir") + "\\zones\\"; // Path du repertoire utilisateur
	
	private GestionnaireBoutons gestionnaire_;
	
	private JLabel				lblCartes_;
	private JList<String>		listeCartes_;
	private JScrollPane			panneauCartes_;
	private JScrollPane			panneauCartesSelectionnes_;
	private JButton				btnAjouterCartes_;
	
	private JButton				btnOk_;
	private JButton				btnSupprimer_;
	
	private JRadioButton		radioSolo_;
	private JRadioButton		radioCoop_;
	private JRadioButton		radioVirtuel_;
	private JRadioButton		radioHumain_;
	private ButtonGroup			groupBouton_;
	private ButtonGroup			groupButton2_;
	
	private JLabel 				lblCoop_;
	private JLabel 				lblSecondJoueur_;
	
	private ArrayList<String>	listeCartesChoisies_;
	private JList<String>		listeCartesTemp_;
	
	
	/**
	 * Constructeur
	 */
	public FenetreConfigurationCampagne() {
		super();
		
		setDefaultCloseOperation(WindowConstants.HIDE_ON_CLOSE); // Cacher la fenetre en appuyant sur le X
		setResizable(false); // Empecher le redimensionnement de la fenetre
		setTitle("Configuration de la campagne"); // Titre de la fenetre
		
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize(); // Obtenir les dimensions de l'ecran
		setBounds((screenSize.width - LARGEUR_FENETRE) / 2,
				  (screenSize.height - HAUTEUR_FENETRE) / 2,
				   LARGEUR_FENETRE, HAUTEUR_FENETRE); // Definir les dimensions de la fenetre
		
		// Pour revenir au menu principal
		addWindowListener(new java.awt.event.WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				InputManager.getInstance().MenuPrincipal();
			}
		});
				
		listeCartesChoisies_ = new ArrayList<String>();
		gestionnaire_ = new GestionnaireBoutons(InputManager.getInstance());
			
		constructionFenetre();
	}
	
	/**
	 * Méthode qui popule la liste des cartes disponibles
	 */
	public void constructionFenetre() {		
		
			JPanel buttonPane = new JPanel();
			JPanel listPane = new JPanel();
			JPanel radioButtonsPane = new JPanel();
					
			File repertoireCartes = new File(REPERTOIRE_CARTES); // Path du repertoire de cartes
			File[] cartes = repertoireCartes.listFiles(); // Lister les fichiers dans le repertoire
			String[] strCartes = new String[cartes.length-1]; // Tableau de noms des fichiers
			
			// Lister le nom des fichiers
			int idx = 0;
			for (int i = 0; i < cartes.length; i++) {
				//On ignore la carte par défaut
				if(!cartes[i].getName().equals("carteDefaut.xml")){	
					strCartes[idx] = cartes[i].getName();
					idx += 1;
				}
				
			}
			
			// Label pour la liste de cartes
			lblCartes_ = new JLabel("Sélectionner les cartes à utiliser pour la campagne.");
			lblCartes_.setSize(lblCartes_.getPreferredSize());
			lblCartes_.setAlignmentX(Box.LEFT_ALIGNMENT);
			
			// Listes de cartes
			listeCartes_ = new JList<String>(strCartes);
			listeCartes_.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
			listeCartes_.setLayoutOrientation(JList.HORIZONTAL_WRAP);
			

			listeCartesTemp_ = new JList<String>();
			listeCartesTemp_.setSelectionMode(ListSelectionModel.MULTIPLE_INTERVAL_SELECTION);
			
			
			//	Deux action listener qui permettent de déselectionner les cartes surlignées dans l'autre liste lors d'un clic dans une des liste.
			listeCartes_.addListSelectionListener(new ListSelectionListener() {
		        public void valueChanged(ListSelectionEvent listSelectionEvent) {
		        	listeCartesTemp_.clearSelection();
		        }
		      });		
			listeCartesTemp_.addListSelectionListener(new ListSelectionListener() {
		        public void valueChanged(ListSelectionEvent listSelectionEvent) {
		        	listeCartes_.clearSelection();
		        }
		      });
			
			
			// Panneaux de cartes et de cartes sélectionnés
			panneauCartes_ = new JScrollPane(listeCartes_);
			panneauCartes_.setAlignmentX(Box.LEFT_ALIGNMENT);
			
			panneauCartesSelectionnes_ = new JScrollPane(listeCartesTemp_);
			panneauCartesSelectionnes_.setAlignmentX(Box.LEFT_ALIGNMENT);
			
			
			// Boutons
			btnAjouterCartes_ = new JButton("Ajouter les cartes à la campagne");
			btnAjouterCartes_.setAlignmentX(Box.LEFT_ALIGNMENT);
			
			btnAjouterCartes_.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					if (listeCartes_.getSelectedIndices().length > 0) { // S'il y a au moins 1 element selectionne
						
						ArrayList<String> temp = (ArrayList<String>) listeCartes_.getSelectedValuesList();
						
						for (int i = 0; i < listeCartes_.getSelectedIndices().length; i++) {
							listeCartesChoisies_.add(REPERTOIRE_CARTES + temp.get(i));
							
						}
						
						String[] str = new String[listeCartesChoisies_.size()];
						str = listeCartesChoisies_.toArray(str);
						
						for(int i = 0; i < str.length; ++i){
							str[i] = str[i].substring(REPERTOIRE_CARTES.length());
						}
						
						listeCartesTemp_.setListData(str);
												
						listeCartes_.clearSelection();
						
						if(listeCartesChoisies_.size() >= 2){
							btnOk_.setEnabled(true);
						}
						
						btnSupprimer_.setEnabled(true);
					}
				}
			});
			
			
			btnOk_ = new JButton("Démarrer");
			btnOk_.setEnabled(false);
			btnOk_.setAlignmentX(Box.LEFT_ALIGNMENT);
			btnOk_.addActionListener(gestionnaire_);
			btnOk_.setActionCommand("ConfigurationCampagne");
			
			btnSupprimer_ = new JButton("Supprimer");
			btnSupprimer_.setAlignmentX(Box.LEFT_ALIGNMENT);
			btnSupprimer_.setEnabled(false);
			btnSupprimer_.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					
					if(listeCartesTemp_.getSelectedIndices().length > 0){
						
						ArrayList<String> selected = (ArrayList<String>) listeCartesTemp_.getSelectedValuesList();
								
						for(int i=0; i<selected.size(); i++){
							for(int j=0; j< listeCartesChoisies_.size(); j++){
								if(selected.get(i).equals((listeCartesChoisies_.get(j)).substring(REPERTOIRE_CARTES.length())) ){
									listeCartesChoisies_.remove(j);
								}
							}
						}
												
						String[] str = new String[listeCartesChoisies_.size()];
						str = listeCartesChoisies_.toArray(str);
						
						for(int i = 0; i < str.length; ++i){
							str[i] = str[i].substring(REPERTOIRE_CARTES.length());
						}
						
						listeCartesTemp_.setListData(str);											
					}
					
					
					if(listeCartesChoisies_.size() < 2){
						btnOk_.setEnabled(false);
						if(listeCartesChoisies_.size()==0){
							btnSupprimer_.setEnabled(false);
						}
					}
					
					
					listeCartesTemp_.clearSelection();
				}
			});

						
			//	Boutons Radio
			groupBouton_ = new ButtonGroup();
			groupButton2_ = new ButtonGroup();
			
			radioSolo_ = new JRadioButton("Partie Solo");
			radioSolo_.setOpaque(false);
			radioSolo_.setSelected(true);
			groupBouton_.add(radioSolo_);
			radioSolo_.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					if(radioSolo_.isSelected()){
						radioHumain_.setEnabled(false);
						radioVirtuel_.setEnabled(false);
						lblSecondJoueur_.setEnabled(false);
						groupButton2_.clearSelection();

						radioVirtuel_.setSelected(true);
					}
				}
			});
			
			radioCoop_ = new JRadioButton("Partie Coopération");
			radioCoop_.setOpaque(false);
			groupBouton_.add(radioCoop_);
			radioCoop_.addActionListener(new ActionListener() {
				@Override
				public void actionPerformed(ActionEvent e) {
					if(radioCoop_.isSelected()){
						radioHumain_.setEnabled(true);
						radioVirtuel_.setEnabled(true);
						lblSecondJoueur_.setEnabled(true);
					}
				}
			});
			
			radioVirtuel_ = new JRadioButton("Partenaire Virtuel");
			radioVirtuel_.setOpaque(false);
			groupButton2_.add(radioVirtuel_);
			radioVirtuel_.setSelected(true);
			radioVirtuel_.setEnabled(false);
			
			radioHumain_ = new JRadioButton("Partenaire Humain");
			radioHumain_.setOpaque(false);
			groupButton2_.add(radioHumain_);
			radioHumain_.setEnabled(false);
			

			lblCoop_ = new JLabel("Voulez-vous jouer en équipe :");
			lblSecondJoueur_ = new JLabel("Choisissez votre compagnon :");
			lblSecondJoueur_.setEnabled(false);
			
			//	Ajout de radio buttons
			radioButtonsPane.setLayout(new GridLayout(3, 2));
			radioButtonsPane.setBorder(BorderFactory.createEmptyBorder(10,10,0,10));
			radioButtonsPane.add(lblCoop_);
			radioButtonsPane.add(lblSecondJoueur_);
			radioButtonsPane.add(radioSolo_);
			radioButtonsPane.add(radioVirtuel_);
			radioButtonsPane.add(radioCoop_);
			radioButtonsPane.add(radioHumain_);			
			
			//	Ajout des composante dans les panels
			listPane.setLayout(new BoxLayout(listPane, BoxLayout.Y_AXIS));
	        listPane.setBorder(BorderFactory.createEmptyBorder(10,10,0,10));
			listPane.add(lblCartes_);
			listPane.add(Box.createVerticalStrut(10));
			listPane.add(panneauCartes_);
			listPane.add(Box.createVerticalStrut(5));
			listPane.add(panneauCartesSelectionnes_);
			
			
			buttonPane.setLayout(new BoxLayout(buttonPane, BoxLayout.LINE_AXIS));
	        buttonPane.add(Box.createHorizontalStrut(10));
			buttonPane.add(btnAjouterCartes_);
	        buttonPane.add(Box.createHorizontalStrut(5));
			buttonPane.add(btnSupprimer_);
	        buttonPane.add(Box.createHorizontalGlue());
	        buttonPane.add(Box.createHorizontalGlue());
	        buttonPane.add(Box.createHorizontalGlue());
	        buttonPane.add(Box.createHorizontalGlue());
			buttonPane.add(btnOk_);
	        buttonPane.add(Box.createVerticalStrut(60));
			
	        
			// Ajout des panels au contentPane
	        Container contentPane = getContentPane();
	        contentPane.add(radioButtonsPane, BorderLayout.BEFORE_FIRST_LINE);
	        contentPane.add(listPane, BorderLayout.CENTER);
	        contentPane.add(buttonPane, BorderLayout.PAGE_END);
	        
	        radioButtonsPane.setBackground(new Color(200, 210, 220));
	        listPane.setBackground(new Color(200, 210, 220));
	        buttonPane.setBackground(new Color(200, 210, 220));
	        
	}
	
	
	/**
	 * Méthode qui retourne la liste des noms des cartes choisies pour la campagne
	 * @return La liste des cartes choisies
	 */
	public Object[] getListeCartesChoisies() {
		return listeCartesChoisies_.toArray();
	}
	
	public int getModeCoop() {
		
		if(radioCoop_.isSelected()){
			return 1;
		}else{
			return 0;
		}
	}
	
	public int getJoueur2Virtuel() {

		if(radioVirtuel_.isSelected()){
			return 1;
		}else{
			return 0;
		}
		
	}
	
	public void setModeCoop(int modeCoop) {
		
		if(modeCoop == 1){
			radioCoop_.setSelected(true);
			radioSolo_.setSelected(false);
			
			radioHumain_.setEnabled(true);
			radioVirtuel_.setEnabled(true);
			lblSecondJoueur_.setEnabled(true);
		}else{
			radioCoop_.setSelected(false);
			radioSolo_.setSelected(true);
			
			radioHumain_.setEnabled(false);
			radioVirtuel_.setSelected(true);
			radioVirtuel_.setEnabled(false);
			lblSecondJoueur_.setEnabled(false);
		}

	}
	
	public void setJoueur2Virtuel(int joueurVirtuel) {

		if(getModeCoop() == 1){
			if(joueurVirtuel == 1){
				radioCoop_.setSelected(true);
				
				radioHumain_.setEnabled(true);
				radioVirtuel_.setEnabled(true);
				
				radioVirtuel_.setSelected(true);
				radioHumain_.setSelected(false);
			}else{
				radioCoop_.setSelected(true);
				
				radioHumain_.setEnabled(true);
				radioVirtuel_.setEnabled(true);
				
				radioVirtuel_.setSelected(false);
				radioHumain_.setSelected(true);
			}
		}else{
			
			radioCoop_.setSelected(false);
			
			radioHumain_.setEnabled(false);
			radioVirtuel_.setEnabled(false);
			
			radioVirtuel_.setSelected(false);
			radioHumain_.setSelected(false);
			lblSecondJoueur_.setEnabled(false);
	
		}
		
	}
	
	public void setCartesCampagne(String[] cartes){
		
		
		String[] str = cartes;
		
		for(int i = 0; i < str.length; ++i){
			str[i] = str[i].substring(REPERTOIRE_CARTES.length());
		}
		
		listeCartesTemp_.setListData(str);
								
		listeCartes_.clearSelection();
		
		if(listeCartesChoisies_.size() >= 2){
			btnOk_.setEnabled(true);
		}
		
		btnSupprimer_.setEnabled(true);
		
	
	}
	
	
}
