package InterfaceGraphique;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.DecimalFormat;

import javax.swing.BoxLayout;
import javax.swing.JButton;
import javax.swing.JComboBox;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JSlider;
import javax.swing.JTextField;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;

@SuppressWarnings("serial")
public class FenetreConfigurationZoneJeu extends JFrame {
	private final String[]				COTES_DIFFICULTE = { "", "Facile", "Normal", "Difficile", "IMPROSSIBRUUU" };
	
	// Valeurs par défaut
	private final int					FREQUENCE_ASTEROIDE_DEFAUT = 500; // En millisecondes
	private final int					NOMBRE_STATIONS_DEFAUT = 1;
	private final String				BONUS_ACCELERATION_DEFAUT = "10";
	
	// Valeurs extrêmes
	// Il faut ajouter 500 millisecondes pour avoir les vrais min et max
	private final int					FREQUENCE_ASTEROIDE_MIN = 0;	// En millisecondes
	private final int					FREQUENCE_ASTEROIDE_MAX = 2500;	// En millisecondes
	private final int					NOMBRE_STATIONS_MIN = 1;
	private final int					NOMBRE_STATIONS_MAX = 10;
	private final int					BONUS_ACCELERATION_MIN = 10;
	private final int					BONUS_ACCELERATION_MAX = 100;
	
	// Texte
	private JLabel 						texteFrequenceAsteroide_;
	private JLabel						frequenceAsteroide_;
	
	private JLabel 						texteNombreStations_;
	private JLabel						nombreStations_;
	
	private JLabel 						texteBonusAcceleration_;
	private JLabel						texteCoteDifficulte_;
	
	// Fields
	private JSlider						sliderFrequenceAsteroide_;	// Il faut ajouter 500 millisecondes pour avoir la vraie valeur
	private JSlider						sliderNombreStations_;
	private JTextField					fieldBonusAcceleration_;
	private JComboBox<String>			comboCoteDifficulte_;
	
	// Boutons
	private JButton						btnSauvegarder_;
	private JButton						btnDefaut_;
	private JButton 					btnAnnuler_;
	
	// Composantes graphique
	private JPanel 						contentPanel_;
	
	public FenetreConfigurationZoneJeu() {
		texteFrequenceAsteroide_ = new JLabel("Fr\u00E9quence de passage des ast\u00E9ro\u00EFde");
		frequenceAsteroide_ = new JLabel("1 astéroïde / seconde");
		
		texteNombreStations_ = new JLabel("Nombre de stations minimales à sauver");
		nombreStations_ = new JLabel("1 station");
		
		texteBonusAcceleration_ = new JLabel("Bonus de vitesse des acc\u00E9l\u00E9rateurs");
		texteCoteDifficulte_ = new JLabel("Cote de difficult\u00E9 de la carte");
		
		sliderFrequenceAsteroide_ = new JSlider();
		sliderFrequenceAsteroide_.setPaintTicks(true);
		sliderFrequenceAsteroide_.setMajorTickSpacing(100);
		sliderFrequenceAsteroide_.setMinimum(FREQUENCE_ASTEROIDE_MIN);
		sliderFrequenceAsteroide_.setMaximum(FREQUENCE_ASTEROIDE_MAX);
		sliderFrequenceAsteroide_.setValue(FREQUENCE_ASTEROIDE_DEFAUT);
		sliderFrequenceAsteroide_.addChangeListener(new FrequenceAsteroideListener());
		
		sliderNombreStations_ = new JSlider();
		sliderNombreStations_.setPaintTicks(true);
		sliderNombreStations_.setMajorTickSpacing(1);
		sliderNombreStations_.setMinimum(NOMBRE_STATIONS_MIN);
		sliderNombreStations_.setMaximum(NOMBRE_STATIONS_MAX);
		sliderNombreStations_.setValue(NOMBRE_STATIONS_DEFAUT);
		sliderNombreStations_.addChangeListener(new NombreStationsListener());
		
		fieldBonusAcceleration_ = new JTextField(3);
		fieldBonusAcceleration_.setText(BONUS_ACCELERATION_DEFAUT);
		
		comboCoteDifficulte_ = new JComboBox<String>(COTES_DIFFICULTE);
		
		btnSauvegarder_ = new JButton("Sauvegarder");
		btnSauvegarder_.addActionListener(new BoutonSauvegarderListener());
		btnDefaut_ = new JButton("Valeurs par défaut");
		btnDefaut_.addActionListener(new BoutonDefautListener());
		btnAnnuler_ = new JButton("Annuler");
		btnAnnuler_.addActionListener(new BoutonAnnulerListener());
		
		// Attributs de fenêtre
		setSize(400, 250);
		setResizable(false);
		setTitle("Configuration de la zone de jeu");
		
		contentPanel_ = new JPanel();
		setLayout(new BoxLayout(contentPanel_, BoxLayout.Y_AXIS));
		contentPanel_.add(texteFrequenceAsteroide_);
		contentPanel_.add(sliderFrequenceAsteroide_);
		contentPanel_.add(frequenceAsteroide_);
		contentPanel_.add(texteNombreStations_);
		contentPanel_.add(sliderNombreStations_);
		contentPanel_.add(nombreStations_);
		contentPanel_.add(texteBonusAcceleration_);
		contentPanel_.add(fieldBonusAcceleration_);
		contentPanel_.add(texteCoteDifficulte_);
		contentPanel_.add(comboCoteDifficulte_);
		contentPanel_.add(btnSauvegarder_);
		contentPanel_.add(btnDefaut_);
		contentPanel_.add(btnAnnuler_);
		
		setContentPane(contentPanel_);
	}
	
	/**
	 * Fonction qui permet de setter les propriétés de la carte
	 * @param frequenceAsteroide La fréquence d'apparition des astéroïdes, en
	 * millisecondes.
	 * @param nombreStations Le nombre de stations minimum à sauver pour gagner.
	 * @param bonusAcceleration Le bonus de vitesse que donne le bonus
	 * d'accélération
	 * @param coteDifficulte La cote de difficulte de la carte, 1 étant le plus
	 * facile et 4 le plus difficile.
	 */
	public void setProprietes(int frequenceAsteroide, int nombreStations, int bonusAcceleration, int coteDifficulte) {
		sliderFrequenceAsteroide_.setValue(frequenceAsteroide);
		sliderNombreStations_.setValue(nombreStations);
		fieldBonusAcceleration_.setText((new Integer(bonusAcceleration)).toString());
		comboCoteDifficulte_.setSelectedIndex(coteDifficulte);
	}
	
	///////////////////////////////////////////////////////////////////////////
	// ACTION LISTENERS
	///////////////////////////////////////////////////////////////////////////
	private class FrequenceAsteroideListener implements ChangeListener {

		@Override
		public void stateChanged(ChangeEvent e) {
			int frequenceAsteroide = ((JSlider)e.getSource()).getValue();
			
			// On le convertie pour avoir le minimum et maximum
			frequenceAsteroide += 500;
			
			DecimalFormat numberFormat = new DecimalFormat("#.000");
			Double freq = frequenceAsteroide / 1000.0;

			String texteAsteroide = "";
			if (freq < 1.0) {
				Double offset = 1.0 + (1.0 - freq) * 2.0;
				texteAsteroide = numberFormat.format(offset) + " astéroides";
			} else {
				texteAsteroide = "1 astéroïde";
			}
			
			String texteSeconde = "seconde";
			if (freq > 1.0) {
				texteSeconde = numberFormat.format(freq) + " secondes";
			}
			
			frequenceAsteroide_.setText(texteAsteroide + " / " + texteSeconde);
		}
		
	}
	
	private class NombreStationsListener implements ChangeListener {

		@Override
		public void stateChanged(ChangeEvent e) {
			int nombreStations = ((JSlider)e.getSource()).getValue();
			nombreStations_.setText(nombreStations + " station" + ((nombreStations > 1) ? "s" : ""));
		}
	}
	
	private class BoutonSauvegarderListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			int bonusAcceleration = 0;
			try {
				bonusAcceleration = Integer.parseInt((String)fieldBonusAcceleration_.getText());
			} catch (NumberFormatException exc) {
				JOptionPane.showMessageDialog(contentPanel_, "Mauvaise données entrées pour le bonus d'accélération!",
											  "Erreur", JOptionPane.ERROR_MESSAGE);
				return;
			}
			
			String coteDifficulte = (String)comboCoteDifficulte_.getSelectedItem();
			
			// Il faut effectuer la validation des données avant de sauvegarder le tout
			if (bonusAcceleration < BONUS_ACCELERATION_MIN) {
				JOptionPane.showMessageDialog(contentPanel_, "Le bonus d'accélération ne peut pas être en dessous de " + BONUS_ACCELERATION_MIN + "!",
											  "Erreur", JOptionPane.ERROR_MESSAGE);
				return;
			}
			
			if (bonusAcceleration > BONUS_ACCELERATION_MAX) {
				JOptionPane.showMessageDialog(contentPanel_, "Le bonus d'accélération ne peut pas être au dessus de " + BONUS_ACCELERATION_MAX + "!",
											  "Erreur", JOptionPane.ERROR_MESSAGE);
				return;
			}
			
			if (coteDifficulte == "") {
				JOptionPane.showMessageDialog(contentPanel_, "Il faut spécifier une cote de difficulté!",
											  "Erreur", JOptionPane.ERROR_MESSAGE);
				return;
			}
			
			// On le convertie pour avoir le minimum et maximum
			int frequenceAsteroide = sliderFrequenceAsteroide_.getValue() + 500;
			int nombreStations = sliderNombreStations_.getValue();
			
			Demarrage.fctC_setProprietesZoneJeu(frequenceAsteroide, nombreStations, bonusAcceleration, comboCoteDifficulte_.getSelectedIndex());
			
			InputManager.getInstance().fermerConfigurationZoneJeu();
		}
	}
	
	private class BoutonDefautListener implements ActionListener {
		@Override
		public void actionPerformed(ActionEvent e) {
			sliderFrequenceAsteroide_.setValue(FREQUENCE_ASTEROIDE_DEFAUT);
			sliderNombreStations_.setValue(NOMBRE_STATIONS_DEFAUT);
			fieldBonusAcceleration_.setText(BONUS_ACCELERATION_DEFAUT);
			comboCoteDifficulte_.setSelectedIndex(0);
		}
	}
	
	private class BoutonAnnulerListener implements ActionListener {

		@Override
		public void actionPerformed(ActionEvent e) {
			InputManager.getInstance().fermerConfigurationZoneJeu();
		}
		
	}
}