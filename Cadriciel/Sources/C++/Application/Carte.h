//////////////////////////////////////////////////////////////////////////////
/// @file Carte.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////
#ifndef __APPLICATION_CARTE_H__
#define __APPLICATION_CARTE_H__

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include "../ElementObjet/Asteroide.h"
#include "../ElementObjet/Vaisseau.h"
#include "../ElementObjet/ElementJeuAbstrait.h"
#include "../ElementObjet/PositionDepart.h"
#include "GestionnaireCollision.h"
#include "tinyxml.h"
#include "../../../../Commun/Utilitaire/Vue/Vue.h"
#include "../../../../Commun/Utilitaire/AideGL.h"
#include "../../../../Commun/Utilitaire/LignePointillee.h"

#define RATIO (16.0f/9.0f)

/// Enum du mode du joueur2
enum ModeJoueur { REEL, VIRTUEL };

using namespace std;

// Forward class declaration
class ArbreRenduINF2990;

///////////////////////////////////////////////////////////////////////////
/// @class Carte
/// @brief Classe qui permet l'ajout et la supression d'élements sur la carte (zone de jeu)  
///        
///
/// @author FloppyDisketeers
/// @date 2014-01-21
///////////////////////////////////////////////////////////////////////////
class Carte
{
public:
	/**
	* Constructeur
	*/
									Carte(string nom, ArbreRenduINF2990* arbreRendu);

	/**
	* Constructeur par copie
	* @param carte La duquel copier les membres
	*/
									Carte(Carte &carte);
		 
	/**
	* Destructeur
	*/
									~Carte();

	/// Methode qui permet d'effacer un element
	/// @param element L'element a supprimer
	void							effacerElement(ElementJeuAbstrait* element);

	/// Methode qui permet d'effacer des éléments d'un certain type
	/// @param int Le type d'élément a supprimer
	void							effacerElementsType(int type);

	/// Methode qui modifie la visibilite des elements d'un certain type
	/// @param type Le type de l'element dont changer la visibilite
	/// @param visible La visibilite de l'objet
	void							changerVisibilitePositionDepart(bool visible);

	/// Methode qui ajoute un objet deja cree a la liste des objets
	/// @param element L'element a ajouter
	void							ajouterElement(ElementJeuAbstrait* element);

	/// Methode qui permet d'ajouter un element avec un noeud XML
	/// @param element L'element a creer via XML
	void							creerElementParXML(TiXmlElement& element);

	/// Methode qui permet d'ajouter une barrière
	/// @param position1 La position du premier bout de la barriere
	/// @param position2 La position du deuxieme bout de la barriere
	void							creerBarriere(Vecteur3 position1, Vecteur3 position2);
	
	/// Methode qui permet d'ajouter un asteroide
	Asteroide*						creerAsteroide();

	/// Methode qui permet d'ajouter un projectile
	void							ajouterProjectile(Projectile* proj);

	/// Met à jour les éléments de jeu
	void							update(float deltaT);

	/// Dessine le cadre de la zone de jeu
	void							dessinerCadreZoneDeJeu();

	/// Dessine le cadre de la zone de depart
	void							dessinerCadreDepart();

	/// Methode qui retourne le nombre de stations spatiales de la carte
	unsigned int					getNbStationSpatial();

	/// Permet d'obtenir le nombre minimal de station a sauver de la destruction des astéroides
	unsigned int					getNbMinStationASauver() const;

	/// Permet de definir le nombre minimal de station a sauver de la destruction des astéroides
	/// @param nbStation Le nombre minimal de station a sauver de la destruction des astéroides
	void							setNbMinStationASauver(unsigned int nbStation);

	/// Permet d'obtenir la frequence d'apparition des astéroides 
	float							getFrequenceAsteroides() const;

	/// Permet de definir la frequence d'apparition des astéroides
	/// @param frequence La frequence d'apparition des astéroides 
	void							setFrequenceAsteroides(float frequence);

	/// Permet d'obtenir l'acceleration fournie par les bonus accelerateurs
	unsigned int					getAccelerationBonus() const;

	/// Permet de definir l'acceleration fournie par les bonus accelerateurs
	/// @param acceleration L'acceleration fournie par les bonus accelerateurs
	void							setAccelerationBonus(unsigned int acceleration);

	/// Permet d'obtenir la difficulte du jeu
	int								getDifficulte() const;

	/// Permet de definir la difficulte du jeu
	/// @param difficulte Le niveau de difficulte du jeu
	void							setDifficulte(int difficulte);

	/// Permet d'obtenir le nom de la carte
	string							getNom() const;

	/// Permet de definir le nom de la carte
	/// @param nouveauNom Le nouveau nom de la carte
	void							setNom(const string nouveauNom);

	/// Permet d'obtenir la cloture en X de la zone de jeu
	Vecteur2f						getZoneJeuX() const;

	/// Permet d'obtenir la cloture en Y de la zone de jeu
	Vecteur2f						getZoneJeuY() const;

	/// Permet de definir la largeur de la zone de jeu
	/// @param largeurZone La nouvelle largeur de la zone de jeu
	void							setZoneJeu(const float largeurZone); 

	/// Permet d'obtenir le cadre de depart en X
	Vecteur2f						getCadreDepartX() const;

	/// // Permet d'obtenir le cadre de depart en Y
	Vecteur2f						getCadreDepartY() const;

	/// Methode qui retourne le conteneur d'elementJeu
	vector<ElementJeuAbstrait*>&	getVecteurElement();

	/// Methode qui retourne le conteneur d'asteroides
	vector<Asteroide*>&				getVecteurAsteroide();

	/// Methode qui retourne le conteneur de projectile
	vector<Projectile*>&			getVecteurProjectile();

	/// Methode qui verifie s'il est correct de sauvegarder la carte
	bool							sauvegardeOk() const;

	/// Methode qui retourne la largeur de la zone de jeu
	float							getLargeur() const;

	/// Methode qui permet de set le joueur 2 a joueur reel ou joueur virtuel
	void							setJoueur1(ModeJoueur mode);

	/// Methode qui permet de set le joueur 2 a joueur reel ou joueur virtuel
	void							setJoueur2(ModeJoueur mode);

	/// Methode qui permet de recuperer le joueur 1
	Vaisseau*						getJoueur1();

	/// Methode qui permet de recuperer le joueur 2
	Vaisseau*						getJoueur2();

	/// Opérateur d'assignement
	/// @param carte La carte a assigner
	Carte&							operator=(Carte& carte);

	// Permet d'obtenir les coins de la zone de passage
	// @return Les 2 coins de la zone de passage
	Vecteur4f						getCoinsZonePassage() const;

	// Permet d'obtenir la largeur de la zone de passage
	// @return la largeur
	float							getLargeurZonePassage() const;

	// Permet d'obtenir les coins de la zone de passage
	// @return Les 2 coins de la zone de passage
	Vecteur4f						getCoinsCadreDepart() const;
	/// Methode qui retourne la position depart du joueurX
	aiVector3D						getPosDepartJoueur(int joueur) const;

	///	Methode qui determine si on est en mode coop ou non				
	inline void						setModeCoop(bool modeCoop) { modeCoop_ = modeCoop; }
	inline bool						getModeCoop() const { return modeCoop_; }

	/// Methode qui determine si le joueur 2 est virtuel ou non
	inline void						setJoueur2Virtuelp(bool joueurVirtuel) { joueurVirtuel_ = joueurVirtuel; }
	inline bool						getJoueur2Virtuel() const { return joueurVirtuel_; }


	/// Methode qui remplace les positions de depart par des vaisseaux
	void							echangerPositionDepartPourVaisseau();

	/// Methode qui remplace les vaisseaux par des positions de depart
	void							echangerVaisseauPourPositionDepart();

	/// Methode qui cree les joueurs et definit si le 2e joueur est virtuel ou non
	/// @param modeCoop Si le jeu est en mode solo ou cooperatif
	/// @param joueur2Virtuel Si le deuxieme joueur est reel (humain) ou virtuel (AI)
	void							definirModeJoueurs(bool modeCoop, bool joueur2Virtuel);

	/// Methode qui detruit tous les asteroides generes
	void							detruireAsteroides();

	/// Methode qui detruit tous les projectiles
	void							detruireProjectiles();

	/**
	 * Détruit les objets à détruire après le update courant
	 */
	void							detruireObjets();
		 
	/**
	 * Associe les frères de chaque portail. Cette fonction est appellée
	 * lorsque l'on charge une carte à partir d'un fichier XML
	 */
	void							associerFreresPortails();

	unsigned int					getNombreStations() const { return nombreStations_; }

	void							detruireQuadTree();

	bool							joueurIsProcheCadre();

private:
	// Setter le taille du cadre de depart
	void							setCadreDepart(const float& largeurZone, const float& hauteurZone); 

	// Setter le taille du zone de passage
	void							setZonePassage(const float& largeurZone, const float& hauteurZone); 
	
	/// Attribut du nom de la carte 
	string							nom_;

	// Proprietes de la zone de jeu - En fenêtre virtuelle
	float						xMinZoneJeu_;
	float						xMaxZoneJeu_;
	float						yMinZoneJeu_;
	float						yMaxZoneJeu_;
	
	// Proprietes du cadre de depart. Bien faire la distinction en cadre de depart et cadre de jeu
	// (largeurCadre = 1.3*largeurZoneJeu_)  (hauteurCadre = hauteurZoneJeu_ + 0.3*largeurZoneJeu_)
	float						xMinCadreDepart_;
	float						xMaxCadreDepart_;
	float						yMinCadreDepart_;
	float						yMaxCadreDepart_;

	// Proprietes de la zone de passage.
	// (largeurZonePassage = hauteurZoneJeu-0.3*largeurZoneJeu)  (hauteurZonePassage = 0.7*largeurZoneJeu_)
	float						xMinZonePassage_;
	float						xMaxZonePassage_;
	float						yMinZonePassage_;
	float						yMaxZonePassage_;

	/// Attribut du nombre minimal de station a sauver de la destruction des astéroides
	unsigned int				nbMinDeStationASauver_;

	/// Attribut de la frequence d'apparition des astéroides
	float						frequenceAsteroides_;
	
	/// Attribut pour le nombre d'asteroide crees jusqu'a present
	const int					nbMaxAsteroides_;

	/// Attribut de l'acceleration fournie par les bonus accelerateurs
	unsigned int				accelerationBonus_;

	/// Attribut du niveau de difficulté
	int							difficulte_;

	/// Conteneur des éléments de la carte
	vector<ElementJeuAbstrait*> conteneurElementsJeu_;

	/// Conteneur des asteroides
	vector<Asteroide*>			conteneurAsteroide_;

	/// Conteneur des projectile
	vector<Projectile*>			conteneurProjectile_;

	/** Vecteur contenant les indices d'éléments à détruire */
	set<int, greater<int>>		elementsADetruire_;

	/** Vecteur contenant les indices d'astéroïdes à détruire */
	set<int, greater<int>>		asteroidesADetruire_;

	/// Pointeur vers le premier Vaisseau
	Vaisseau*					joueur1_;

	/// Pointeur vers le deuxieme Vaisseau (peut être l'AI)
	Vaisseau*					joueur2_;

	/** Arbre de rendu pour ajouter les noeuds lors de la création */
	ArbreRenduINF2990*			arbreRendu_;

	/// Le temps pour calculer la frequence
	float						tempsCourant_;

	/// Gestionnaire de collision
	GestionnaireCollision		gestionnaireCollision_;

	/// determine s'il y a 2 joueur ou 1
	bool						modeCoop_;

	/// determine si le deuxieme joueur est virtuel ou humain
	bool						joueurVirtuel_;

	/**
	 * Nombre de stations courantes
     */
	int							nombreStations_;
};
#endif // __APPLICATION_CARTE_H__
 
///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////