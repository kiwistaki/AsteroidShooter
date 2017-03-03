///////////////////////////////////////////////////////////////////////////
/// @file ElementJeuAbstrait.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0
///
/// @addtogroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////////////

#ifndef ElementJeuAbstrait_H_
#define ElementJeuAbstrait_H_

#include <iostream>

#include "assimp.hpp"
#include "aiMatrix4x4.h"
#include "aiVector3D.h"
#include "../../../Commun/Utilitaire/Vecteur.h"
#include "../../../Commun/Utilitaire/BoiteEnglobanteOrientee.h"
#include "../../../Commun/Utilitaire/AideCollision.h"

using namespace std;
using namespace math;

enum Type {ACCELERATEUR = 0, ASTEROIDE, BARRIERE, PORTAIL, PROJECTILE, STATION, VAISSEAU, POSITIONDEPART, VAISSEAUVIRTUEL};

// Forward class declaration
class NoeudAbstrait;
class Accelerateur;
class Asteroide;
class Barriere;
class Portail;
class PositionDepart;
class Projectile;
class Station;
class Vaisseau;

/** @class ElementJeuAbstrait
*	@brief Cette classe abstraite servira de modele pour les objets du jeu
 *	
 *	Elle va utilise les noeuds de memes types pour l'affichage des objets, tout en fournissant
 *	les elements principaux des objets du jeu.
 */
class ElementJeuAbstrait
{
public:
	/// Constructeur
	ElementJeuAbstrait();

								/// Constructeur par copie
								ElementJeuAbstrait(const ElementJeuAbstrait& element);

								/// Destructeur
								virtual					   ~ElementJeuAbstrait();

	/// Visiteur
	//virtual void				acceptVisitor(Visitor& visitor) = 0;

	/// Permet d'obtenir la position de depart de l'element
	/// @return La position de depart de l'element
	inline aiVector3D			getPositionDepart(){return positionDepart_;}

	/// Permet de definir la position de depart de l'element
	/// @param positionDepart La position de depart de l'element
	void						setPositionDepart(Vecteur3f positionDepart);

	/// Permet de definir la position de depart de l'element
	/// @param positionDepart La position de depart de l'element
	void						setPositionDepart(aiVector3D positionDepart);

	/// Permet d'obtenir la position actuelle de l'element
	/// @return La position de l'element dans le jeu
	inline aiVector3D			getPositionActuelle(){return positionActuelle_;}

	/// Permet de definir la position actuelle de l'element
	/// @param positionActuelle La position actuelle de l'element
	void						setPositionActuelle(Vecteur3f positionActuelle);

	/// Permet d'obtenir la position precedente de l'element
	/// @return La position de l'element dans le jeu
	inline aiVector3D			getPositionPrecedente(){return positionPrecedente_;}

	//Permet de spécifier la position précédente de l'élément. 
	void						setPositionPrecedente(aiVector3D positionPrecedente){ positionPrecedente_ = positionPrecedente;}

	/// Permet de definir la position actuelle de l'element
	/// @param positionActuelle La position actuelle de l'element
	void						setPositionActuelle(aiVector3D positionActuelle);

	/// Permet d'obtenir la direction de la vitesse de l'element
	/// @return La direction de la vitesse de l'element
	inline aiVector3D			getDirectionVitesse(){return directionVitesse_;}

	/// Permet de definir la direction de la vitesse de l'element
	/// @param vitesse La nouvelle direction de vitesse de l'element
	void						setDirectionVitesse(Vecteur3f directionVitesse);

	/// Permet de definir la direction de la vitesse de l'element
	/// @param vitesse La nouvelle direction de vitesse de l'element
	void						setDirectionVitesse(aiVector3D directionVitesse);

	/// Permet d'obtenir le module de la vitesse de l'element
	/// @return La direction de la vitesse de l'element
	inline float				getModuleVitesse(){return moduleVitesse_;}

	/// Permet d'obtenir le module de la vitesse de l'element
	/// @return La direction de la vitesse de l'element
	void						setModuleVitesse(float moduleVitesse);

	/// Permet d'obtenir l'acceleration de l'element
	/// @return L'acceleration de l'element
	inline aiVector3D			getAcceleration(){return acceleration_;}

	/// Permet de definir l'acceleration de l'element
	/// @param acceleration La nouvelle acceleration de l'element
	void						setAcceleration(aiVector3D acceleration);

	/// Permet d'obtenir l'axe de l'element
	/// @return L'axe de l'element
	inline aiVector3D			getAxe(){return axe_;}

	/// Permet de definir l'axe de l'element
	/// @param axe Le nouvel axe de l'element
	void						setAxe(Vecteur3f axe);

	/// Permet d'obtenir la taille
	/// @return La taille
	inline aiVector3D			getTaille(){return taille_;}

	/// Permet de definir la taille
	/// @param taille La nouvelle taille
	void						setTaille(Vecteur3f taille);

	/// Permet de definir la taille
	/// @param taille La nouvelle taille
	void						setTaille(aiVector3D taille);

	/// Permet d'obtenir le poids
	/// @return Le poids de l'element
	inline float				getPoids(){return poids_;}

	/// Permet de definir le poids
	/// @param poids Le nouveau poids
	void						setPoids(float poids);

	/// Permet d'obtenir l'angle
	/// @return L'angle de l'element sur son axe
	inline float				getAngle(){return angle_;}

	/// Permet de definir l'angle
	/// @param angle Le nouvel angle
	void						setAngle(float angle);

	/// Permet d'obtenir l'id
	/// @return L'id de l'element
	inline unsigned int			getId(){return id_;}

	/// Permet de definir l'id
	/// @param id Le nouvel id
	void						setId(unsigned int id);

	/// Permet d'obtenir le type de l'element
	/// @return Le type de l'element
	virtual Type				getType() = 0;

	/// Mise a jour
	virtual void				update(float deltaT) = 0;

	/// Permet de deplacer un element
	/// @param deplacement Le vecteur de deplacement
	void						deplacer(Vecteur3f deplacement);

	/// Permet de deplacer un element
	/// @param deplacement Le vecteur de deplacement
	void						deplacerAiVector(aiVector3D deplacement);

	/// Permet de pivoter l'element
	/// @param axe		L'axe de rotation
	/// @param angle	L'angle de rotation
	void						pivoter(Vecteur3f axe, float angle);

	/// Permet de pivoter l'element
	/// @param axe		L'axe de rotation
	/// @param angle	L'angle de rotation
	void						pivoterAiVector(aiVector3D axe, float angle);

	/// Permet de redimensionner l'element
	/// @param redimensionnement Le vecteur de redimensionnement
	void						redimensionner(Vecteur3f redimensionnement);

	/// Permet de definir si l'element est selectionne
	/// @param selection Si l'objet est selectionne
	void						setSelectionne(bool selection);

	/// Permet d'obtenir si un element est selectionne
	/// @return Si l'element est selectionne
	bool						getSelectionne() const;

	/**
	* Inverse la selection de l'objet
	 */
	void						inverserSelection();

	/**
	* Calcule la sphere englobante du modele 3d
	 * @return le rayon de la sphere
	 */
	double						calculerSphereEnglobante() const;

	/**
	* Calcule le cylindre englobant du modele 3d
	 * @param rayon Le rayon du cylindre
	 * @param bas	Le plus bas point du cylindre
	 * @param haut	Le plus haut point du cylindre
	 */
	void						calculerCylindreEnglobant(double& rayon, double& bas, double& haut) const;

	/**
	* Calcule la boite englobante du modele 3d
	 * @param coinMin Le coin minimum de la boite
	 * @param coinMax Le coin maximum de la boite
	 */
	void						calculerBoiteEnglobante(Vecteur3& coinMin, Vecteur3& coinMax) const;

	/**
	* Methode qui permet de cloner l'objet
	* @return un pointeur vers la copie de l'objet
	*/
	virtual	ElementJeuAbstrait*	clone() const = 0;
		 
	/**
	 * Retourne la boite orientee qui englobe le noeud qui represente cet
	 * element de jeu.
	 */
	BoiteEnglobanteOrientee&	getBoiteEnglobanteOrientee();

	// Methode utile dans le gestionnaire de collision qui servira à "dispatché" vers la méthode appropriée"
	virtual bool				checkCollision(ElementJeuAbstrait* elementJeu) = 0;
	/// Methode pour verifier si une collision existe
	virtual bool				checkCollision(Accelerateur* accelerateur) = 0;
	virtual bool				checkCollision(Asteroide* asteroide) = 0;
	virtual bool				checkCollision(Barriere* barriere) = 0;
	virtual bool				checkCollision(Portail* portail) = 0;
	virtual bool				checkCollision(Projectile* projectile) = 0;
	virtual bool				checkCollision(Station* station) = 0;
	virtual bool				checkCollision(Vaisseau* vaisseau) = 0;

	// Methode utile dans le gestionnaire de collision qui servira à "dispatché" vers la méthode appropriée"
	virtual void				traiterCollision(ElementJeuAbstrait* elementAbstrait) = 0;
	/// Methode pour traiter la collision si elle a lui avec les differents elements
	virtual void				traiterCollision(Accelerateur* accelerateur) = 0;
	virtual void				traiterCollision(Asteroide* asteroide) = 0;
	virtual void				traiterCollision(Barriere* barriere) = 0;
	virtual void				traiterCollision(Portail* portail) = 0;
	virtual void				traiterCollision(Projectile* projectile) = 0;
	virtual void				traiterCollision(Station* station) = 0;
	virtual void				traiterCollision(Vaisseau* vaisseau) = 0;

	/// Affiche les textes superposes
   virtual void					afficherTexte();

	virtual float				getRayon();
	/// Methode qui permet au joueur virtuel d'éviter les obstacles
	virtual bool				checkCollisionJoueurVirtuel(Vaisseau* joueurVirtuel) { return false; }
	void						setForcePortail(float forcePortail);	
	inline Portail*				getPreviousPortail(){return previousPortail_;}
	void						setPreviousPortail(Portail* previousPortail_);

	virtual inline int			getPointDeVie(){return 1;}

	inline const NoeudAbstrait* getNoeudAbstrait() const { return noeudAbstrait_; }

protected:
	aiVector3D					positionDepart_;
	aiVector3D					positionPrecedente_;
	aiVector3D					positionActuelle_;
	aiVector3D					directionVitesse_;	// Vecteur normalisé
	aiVector3D					acceleration_;
	aiVector3D					axe_;
	aiVector3D					taille_;
	float						moduleVitesse_;
	float						angle_;
	float						poids_;
	unsigned int				id_;
	NoeudAbstrait*				noeudAbstrait_;
	float						forcePortail_;		// Force attraction cause par le portail, sert de booleen aussi (0 == pas de force de portail)
	Portail*					previousPortail_;	// REference vers le portail qui vient de transporter l'objet... 
													// Utile pour verifier la distance qu'il doit depasser avant de redevenir attirable
	static unsigned long		numero_;

};

#endif
//////////////////////////////////////////////////////////////////////////
///@}
//////////////////////////////////////////////////////////////////////////