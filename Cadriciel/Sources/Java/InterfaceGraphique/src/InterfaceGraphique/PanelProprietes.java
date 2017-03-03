package InterfaceGraphique;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.FocusAdapter;
import java.awt.event.FocusEvent;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.util.HashMap;

import javax.swing.GroupLayout;
import javax.swing.GroupLayout.Alignment;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

/**
 * @author Sacha L-Roussel
 * 
 * Classe définissant le panneau de modification des propriétés des objets présent dans le fenetre d'édition
 */

@SuppressWarnings("serial")
public class PanelProprietes extends JPanel {
	
	
	private JLabel lblPos;
	private JLabel lblRotation;
	private JLabel lblMiseEchelle;
	
	private JTextField posX;
	private JTextField posY;
	private JButton btnPos;
	
	private JTextField rotation;
	private JButton btnRotation;
	
	private JTextField miseEchelle;
	private JButton btnMiseEchelle;
	
	private int lastPosX = Integer.MAX_VALUE;
	private int lastPosY = Integer.MAX_VALUE;
	private int lastAngle = Integer.MAX_VALUE;
	private float lastScaleX = Integer.MAX_VALUE;
	
	private HashMap<Integer, TypeElementJeu> correspondanceType;
	private TypeElementJeu typeObjetSelectionne = TypeElementJeu.AUCUN;

	/**
	 * Constructeur par défaut du panneau de configuration
	 * @param InterfaceEdition	instance du conteneur parent
	 * @return Aucun
	 */
	public PanelProprietes() {
		correspondanceType = new HashMap<Integer, TypeElementJeu>();
		correspondanceType.put(0, TypeElementJeu.ACCELERATEUR);
		correspondanceType.put(1, TypeElementJeu.ASTEROIDE);
		correspondanceType.put(2, TypeElementJeu.BARRIERE);
		correspondanceType.put(3, TypeElementJeu.PORTAIL);
		correspondanceType.put(4, TypeElementJeu.PROJECTILE);
		correspondanceType.put(5, TypeElementJeu.STATION);
		correspondanceType.put(6, TypeElementJeu.VAISSEAU);
		correspondanceType.put(7, TypeElementJeu.POSITIONDEPART);
		
		//Label
		lblPos = new JLabel("Position");
		lblRotation = new JLabel("Rotation °");
		lblMiseEchelle = new JLabel("Mise à échelle %");

		lblRotation.setToolTipText("Double-Clic : Reset");
		lblRotation.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
            	if(e.getClickCount()==2){
				 	rotation.setText("0");
				 	applyParameters();
            	}
            }
        });
		
		lblMiseEchelle.setToolTipText("Double-Clic : Reset");
		lblMiseEchelle.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
            	if(e.getClickCount()==2){
				 	miseEchelle.setText("1.0");
				 	applyParameters();
            	}
            }
        });
		
		//Composantes d'entrée
		posX = new JTextField("0");
		posX.setHorizontalAlignment(JTextField.CENTER);
		posY = new JTextField("0");
		posY.setHorizontalAlignment(JTextField.CENTER);
		
		posY.addKeyListener(new KeyAdapter(){
			@Override
			public void	keyPressed(KeyEvent evenement){
				if(evenement.getKeyCode() == KeyEvent.VK_ENTER){
					btnPos.doClick();
				}
			}
		});
		
		posY.addFocusListener( new FocusAdapter() {
			 public void focusGained(FocusEvent e) {
				 	((JTextField) e.getComponent()).setSelectionStart(0);
			    }
		});
		
		posY.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
				 	((JTextField) e.getComponent()).setSelectionStart(0);
            }
        });
			   
		
		posX.addKeyListener(new KeyAdapter(){
			@Override
			public void	keyPressed(KeyEvent evenement){
				if(evenement.getKeyCode() == KeyEvent.VK_ENTER){
					btnPos.doClick();
				}
			}
		});
		
		posX.addFocusListener( new FocusAdapter() {
			 public void focusGained(FocusEvent e) {
				 	((JTextField) e.getComponent()).setSelectionStart(0);
			    }
		});
		
		posX.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
				 	((JTextField) e.getComponent()).setSelectionStart(0);
            }
        });
		
		
		btnPos = new JButton("OK");
		btnPos.setHorizontalAlignment(JTextField.CENTER);		
		btnPos.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent arg0) {
				applyParameters();
			}
		});	
		
		rotation = new JTextField("0");
		rotation.setHorizontalAlignment(JTextField.CENTER);
		
		rotation.addKeyListener(new KeyAdapter(){
			@Override
			public void	keyPressed(KeyEvent evenement){
				if(evenement.getKeyCode() == KeyEvent.VK_ENTER){
					btnRotation.doClick();
				}
			}
		});
		
		rotation.addFocusListener( new FocusAdapter() {
			 public void focusGained(FocusEvent e) {
				 	((JTextField) e.getComponent()).setSelectionStart(0);
			    }
		});
		
		rotation.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
				 	((JTextField) e.getComponent()).setSelectionStart(0);
            }
        });
		
		btnRotation = new JButton("OK");
		btnRotation.setHorizontalAlignment(JTextField.CENTER);
		btnRotation.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent arg0) {
				applyParameters();
			}
		});
		
		miseEchelle = new JTextField("0");
		miseEchelle.setHorizontalAlignment(JTextField.CENTER);
		
		miseEchelle.addKeyListener(new KeyAdapter(){
			@Override
			public void	keyPressed(KeyEvent evenement){
				if(evenement.getKeyCode() == KeyEvent.VK_ENTER){
					btnMiseEchelle.doClick();
				}
			}
		});
		
		miseEchelle.addFocusListener( new FocusAdapter() {
			 public void focusGained(FocusEvent e) {
				 	((JTextField) e.getComponent()).setSelectionStart(0);
			    }
		});
		
		miseEchelle.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseClicked(MouseEvent e) {
				 	((JTextField) e.getComponent()).setSelectionStart(0);
            }
        });
		
		btnMiseEchelle = new JButton("OK");
		btnMiseEchelle.setHorizontalAlignment(JTextField.CENTER);
		btnMiseEchelle.addActionListener(new ActionListener(){
			@Override
			public void actionPerformed(ActionEvent arg0) {
				applyParameters();
			}
		});
		
		//Layout
		GroupLayout layout = new GroupLayout(this);
		setLayout(layout);
		layout.setAutoCreateGaps(true);
		layout.setAutoCreateContainerGaps(true);

		GroupLayout.SequentialGroup hGroup = layout.createSequentialGroup();

			hGroup.addGroup(layout.createParallelGroup().
					addComponent(lblPos, Alignment.CENTER)
						.addGroup(layout.createSequentialGroup()
								.addComponent(posX)
								.addComponent(posY))
					.addComponent(btnPos, Alignment.CENTER));
			hGroup.addGroup(layout.createParallelGroup()
					.addComponent(lblRotation, Alignment.CENTER)
					.addComponent(rotation)
					.addComponent(btnRotation, Alignment.CENTER)				
					);
			hGroup.addGroup(layout.createParallelGroup()
					.addComponent(lblMiseEchelle, Alignment.CENTER)
					.addComponent(miseEchelle)
					.addComponent(btnMiseEchelle, Alignment.CENTER)
					);
			layout.setHorizontalGroup(hGroup);

			
		GroupLayout.SequentialGroup vGroup = layout.createSequentialGroup();

			vGroup.addGroup(layout.createParallelGroup(Alignment.BASELINE)
					.addComponent(lblPos)
					.addComponent(lblRotation)
					.addComponent(lblMiseEchelle));
			vGroup.addGroup(layout.createParallelGroup(Alignment.BASELINE)
					.addGroup(layout.createParallelGroup(Alignment.LEADING)
							.addComponent(posX)
							.addComponent(posY))
					.addComponent(rotation)
					.addComponent(miseEchelle));
			vGroup.addGroup(layout.createParallelGroup(Alignment.CENTER)
					.addComponent(btnPos)
					.addComponent(btnRotation)
					.addComponent(btnMiseEchelle));
			layout.setVerticalGroup(vGroup);

	}
	
	/**
	 * Permet d'activer ou de désactiver les composantes du panel
	 * On l'utilise lorsqu'un seul objet est sélectionné et dans les aures cas (Aucun ou plusieurs éléments sélectionnés)
	 * @param boolean b		paramètre qui définit l'état d'activation des composantes du panel
	 * @return void
	 */
	public void setEnabled(boolean b){
		super.setEnabled(b);
		
		lblMiseEchelle.setEnabled(b);
		lblPos.setEnabled(b);
		lblRotation.setEnabled(b);
		
		btnPos.setEnabled(b);
		
		posX.setEnabled(b);
		posY.setEnabled(b);
		rotation.setEnabled(b);
		miseEchelle.setEnabled(b);
	}
	
	/**
	 * Permet de remettre les paramètres à leur valeur de départ
	 * @param aucun	
	 * @return void
	 */
	public void resetValue(){
		posX.setText("0");
		posY.setText("0");
		rotation.setText("0");
		miseEchelle.setText("1");
	}
	
	/**
	 * Permet de fixer la valeur du slider à une valeur propre
	 * @param int value		valeur souhaitée du slider
	 * @return void
	 */
	public void setRotation(int value){
		rotation.setText((new Integer(value)).toString());
	}
	
	/**
	 * Retourne la valeur courante du slider
	 * @param Aucun
	 * @return int		Valeur courant du slider
	 */
	public int getRotationValue(){
		return Integer.parseInt(rotation.getText());
	}
	
	/**
	 * Permet de fixer la valeur du slider à une valeur propre
	 * @param int value		valeur souhaitée du slider
	 * @return void
	 */
	public void setMiseEchelle(float value){
		miseEchelle.setText((new Float(value)).toString());
	}
	
	/**
	 * Retourne la valeur courante du slider
	 * @param Aucun
	 * @return int		Valeur courant du slider
	 */
	public float getMiseEchelleValue(){
		return Float.parseFloat(miseEchelle.getText());
	}
	
	/**
	 * Permet de fixer les coordonnées affichées dans les boites de saisie de text des coordonnées de l'objet
	 * @param int x, y		Coordonnées souhaitées
	 * @return void		
	 */
	public void setPosition(int x, int y){
		
		posX.setText(x+"");
		posY.setText(y+"");
	}
	
	/**
	 * Permet de fixer la coordonées en X de l'objet
	 * @param int x		Coordonnée en X
	 * @return void		
	 */
	public void setPositionX(int x){
		posX.setText(x+"");
	}
	
	/**
	 * Permet de fixer la coordonées en Y de l'objet
	 * @param int y		Coordonnée en Y
	 * @return void		
	 */
	public void setPositionY(int y){
		posY.setText(y+"");
	}
	
	/**
	 * Retourne la position en X afficher dans le panel
	 * @param aucun
	 * @return int		Coordonnée X		
	 */
	public int getPosX(){
		int posXTemp;
        try{
            posXTemp=Integer.parseInt(this.posX.getText());
            return posXTemp;
       }catch (NumberFormatException e){
           System.out.println("Erreur : Coordonnées en X de type incorrect");
           return Integer.MIN_VALUE;
       }
	}
	
	/**
	 * Retourne la position en Y afficher dans le panel
	 * @param aucun
	 * @return int		Coordonnée Y		
	 */
	public int getPosY(){
		int posYTemp;
        try{
        	posYTemp=Integer.parseInt(this.posY.getText());
            return posYTemp;
       }catch (NumberFormatException e){
           System.out.println("Erreur : Coordonnées en Y de type incorrect");
           return Integer.MIN_VALUE;
       }
	}
	
	public void applyParameters(){
		int positionX = getPosX();
		int positionY = getPosY();
		 
		if(positionX != Integer.MIN_VALUE && positionY != Integer.MIN_VALUE){
			float miseEchelle = getMiseEchelleValue();
			Demarrage.fctC_setPositionAngleScale(positionX, positionY, 0,
												(float)getRotationValue(),
												miseEchelle,
												((typeObjetSelectionne == TypeElementJeu.BARRIERE) ? 1.0f : miseEchelle),
												((typeObjetSelectionne == TypeElementJeu.BARRIERE) ? 1.0f : miseEchelle));
		}else{
			 JOptionPane.showMessageDialog(null, "Coordonnées de type incorrect.", "Erreur", JOptionPane.ERROR_MESSAGE);
		}
	}
	
	/**
	 * Permet de mettre à jour les paramètres de l'objet à partir des
	 * informations venant de la DLL. On met à jour ces valeurs seulement
	 * si elles diffèrent des dernières qu'on a eu de la DLL.
	 */
	public void updateParameters() {
		float[] tabTemp = Demarrage.fctC_getPositionAngleScaleType();
		int posX = (int) tabTemp[0];
		int posY = (int) tabTemp[1];
		
		int angle = (int) tabTemp[3];
		float miseEchelleX = tabTemp[4];
		
		setTypeObjetSelectionne(correspondanceType.get((int)tabTemp[7]));
		
		
		if (posX != lastPosX) {
			setPosition(posX, lastPosY);
			lastPosX = posX;
		}
		
		if (posY != lastPosY) {
			setPosition(lastPosX, posY);
			lastPosY = posY;
		}
		
		if (angle != lastAngle) {
			setRotation(angle);
			lastAngle = angle;
		}
		
		if (miseEchelleX != lastScaleX) {
			lastScaleX = miseEchelleX;
			setMiseEchelle(lastScaleX);
		}
	}

	public TypeElementJeu getTypeObjetSelectionne() {
		return typeObjetSelectionne;
	}

	public void setTypeObjetSelectionne(TypeElementJeu typeObjetSelectionne) {
		this.typeObjetSelectionne = typeObjetSelectionne;
	}
}
