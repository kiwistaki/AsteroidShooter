///////////////////////////////////////////////////////////////////
/// @file Vaisseau.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0
///
/// @addgroup INF2990-04
/// @{
///////////////////////////////////////////////////////////////////
#ifndef VAISSEAU_H_
#define VAISSEAU_H_

#include "ElementJeuAbstrait.h"
#include "NoeudVaisseau.h"
#include "Asteroide.h"

// Forward class declaration
class ArbreRenduINF2990;

/** @class Vaisseau
 *  @brief La classe Vaisseau permet la creation d'un objet Vaisseau
 *
 *	Cette classe contiendra un noeud de type NoeudVaisseau qui gerera
 *  la texture et la modelisation de l'objet Vaisseau.
 */
class Vaisseau: public ElementJeuAbstrait
{
public:
	/// Constructeur
	/// @param joueur1 Si cette valeur a est true, alors c'est le joueur 1, false sinon
					Vaisseau(bool joueur1);

	/// Constructeur par parametres
	/// @param positionDepart La position de depart
	/// @param taille La taille de l'element
	/// @param directionVitesse La vitesse de l'element
	/// @param poids Le poids de l'element
	/// @param joueur1 Si cette valeur a est true, alors c'est le joueur 1, false sinon
					Vaisseau( Vecteur3f positionDepart,
							 Vecteur3f taille, Vecteur3f directionVitesse, float poids,
							 bool joueur1);
					Vaisseau(const Vaisseau& vaisseau);

	/// Destructeur
	virtual		   ~Vaisseau();

	/// Permet d'obtenir le type de l'element
	virtual Type	getType() = 0;

	/// Mise a jour
	virtual void	update(float deltaT);

	//Action à effectuer lorsqu'un vaisseau (Joueur ou AI) entre en collision avec une borne de la zone de jeu.
	void			collisionZoneJeu(char axe);

	/// Methode qui permet de creer des projectiles
	void			attaquer(aiVector3D direction, aiVector3D position, float deltaT);

	/// Methode pour setter la frequence de tir d'un vaisseau
	void			setTempsPourUnTir(float freq);

	/// Permet de cloner l'element
	virtual			ElementJeuAbstrait* clone() const = 0;

	/// Permet au vaisseau de ce deplacer
	void			seDeplacer(float deltaT);
	
	/**
	 * Décélère jusqu'à avoir une vitesse de 0
	 */
	void			decelerer(float deltaT);

	/// Permet au vaisseau deffectuer une rotation
	void			virage(float deltaT, int sens);
	void			virage(float deltaT, int sens, float vitesseRotation);

	/// Permet au vaisseau deffectuer sa manoeuvre
	void			manoeuvre();
	void			manoeuvre(float angle);

	/// Permet au vaisseau virtuel d'éviter de tirer sur le joueur1
	bool			intersectionTirVaisseau(aiVector3D posJoueurVirtuel ,aiVector3D trajectoireTir);

	/// Permet de verifier la collision entre les types d'objets concernés et de les traiter
	virtual bool	checkCollision(ElementJeuAbstrait* element);
	virtual bool	checkCollision(Accelerateur* accelerateur);
	virtual bool	checkCollision(Asteroide* asteroide);
	virtual bool	checkCollision(Barriere* barriere);
	virtual bool	checkCollision(Portail* portail);	
	virtual bool	checkCollision(Projectile* projectile);	
	virtual bool	checkCollision(Station* station);
	virtual bool	checkCollision(Vaisseau* vaisseau);
	virtual void	traiterCollision(ElementJeuAbstrait* element);
	virtual	void	traiterCollision(Accelerateur* accelerateur);
	virtual	void	traiterCollision(Asteroide* asteroide);
	virtual	void	traiterCollision(Barriere* barriere);
	virtual	void	traiterCollision(Portail* portail);
	virtual void	traiterCollision(Projectile* projectile);
	virtual void	traiterCollision(Station* station);
	virtual void	traiterCollision(Vaisseau* vaisseau);

	inline bool		canBeAttracted(){return canBeAttracted_;}
	void			setCanBeAttracted(bool canBeAttracted);

	aiVector3D		getVitesse(){ return vitesse_;};
	void			setVitesse(aiVector3D v){ vitesse_ = v;}

	static const float VITESSE_MAX;
	static const float TEMPS_ENTRE_CHAQUE_TIR;
	static const float	VITESSE_ROTATION;

	inline bool			isControlable(){return isControlable_; };
	void				setControlable(bool isControlable);

	void				setTempsAvantControlable(double t){ tempsAvantControlable_=t; }
	
	void				setAccelerationPortail(aiVector3D accelerationPortail);

	void				setTempsAcceleration(double t){ tempsAccelerationExtra_ = t;}
	double				getTempsAcceleration(){ return tempsAccelerationExtra_;}

	void				setEstAccelere(bool b){ estAccelere_ = b;}
	bool				getEstAccelere(){ return estAccelere_;}

	void				setFacteurAcceleration(int facteurA) {facteurAcceleration_ = facteurA; }
	int					getFacteurAcceleration(){ return facteurAcceleration_; }

	bool				isBlocked(){ return isBlocked_;}
	void				setBlocked(bool b){ isBlocked_ = b;}

	virtual Asteroide*	getAstCible() {return NULL;}
	virtual	void		setAstCibleNull() {;}

protected:
	NoeudVaisseau*		noeud_;
	double				tempsAccelerationExtra_;	// Temps restant pour l'acceleration
	aiVector3D			direction_;					// Direction courante de l'accélération
	aiVector3D			vitesse_;					// Direction courante du vaisseau peu importe son orientation
	bool				isControlable_;				// Quand le vaisseau devient incontrolable.

private:
	float				tempsPourUnTir_;			// Temps restant avant le prochain tir

	bool				canBeAttracted_;			// Si l'objet peut etre encore attire par le portail.

	double				largeurCarte_;				// Pour le joueur virtuel

	double				tempsAvantControlable_;		// temps restant avant que le vaisseau soit controlable en ms.

	aiVector3D			accelerationPortail_;		// acceleration du portail

	bool				estAccelere_;

	int					facteurAcceleration_;

	bool				isBlocked_;
};

#endif
///////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////