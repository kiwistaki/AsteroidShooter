///////////////////////////////////////////////////////////////////////////////
/// @file NoeudAbstrait.h
/// @author DGI-INF2990
/// @date 2007-01-24
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDABSTRAIT_H__
#define __ARBRE_NOEUDS_NOEUDABSTRAIT_H__


#include <windows.h>
#include "../../../../Commun/Externe/GLEW/include/GL/glew.h"
#include <GL/gl.h>
#include <string>

#include "Modele3D.h"
#include "Vecteur.h"

#include "../../../../Commun/Utilitaire/BoiteEnglobanteOrientee.h"

///////////////////////////////////////////////////////////////////////////
/// @class NoeudAbstrait
/// @brief Classe de base du patron composite utilisee pour creer l'arbre
///        de rendu.
///
///        Cette classe abstraite comprend l'interface de base que doivent
///        implanter tous les noeuds pouvant etre present dans l'arbre de
///        rendu.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudAbstrait
{
public:
   /**
    * Constructeur par parametres
	* @param type Le nom du noeud
	*/
   NoeudAbstrait(const std::string& type=std::string(""));

   /**
    * Constructeur par copie
	* @param src L'objet que l'on veut copier
	*/
								NoeudAbstrait(const NoeudAbstrait& src);

   /**
    * Destructeur
	*/
   virtual					   ~NoeudAbstrait();

   /**
    * Obtient le parent de ce noeud
	* @return Le noeud parent
	*/
   NoeudAbstrait*		obtenirParent();

   /**
    * Obtient le parent de ce noeud (version constante)
	* @return Le noeud parent
	*/
   const NoeudAbstrait*	obtenirParent() const;

   /**
    * Assigne le parent de ce noeud
    * @param Le noeud parent
    */
   void					assignerParent( NoeudAbstrait* parent );

   /**
    * Obtient la position relative du noeud
	* @return La position relative
	*/
   const Vecteur3&		obtenirPositionRelative() const;

   /// Assigne la position relative du noeud.
   /// @param positionRelative La position relative du Noeud
   void					assignerPositionRelative( const Vecteur3& positionRelative);

   /// Obtient le type du noeud.
   /// @return Le type 
   const std::string&	obtenirType() const;

   /// ecrit l'etat de l'affichage du du noeud.
   /// @param affiche L'etat d'affichage du noeud
   void					assignerAffiche( bool affiche );

   /// Verifie si le noeud se fait afficher.
   /// @return Un booleen indiquant si le noeud est affiche.
   bool					estAffiche() const;

   /// ecrit l'etat de la selection du noeud.
   /// @param selectionner L'etat de selection
   void					assignerSelection( bool selectionne );

   /// Verifie si le noeud est selectionne.
   /// @return Un booleen indiquant si le noeud est selectionne.
   bool					estSelectionne() const;

   /// ecrit si le noeud peut etre selectionne ou non.
   /// @param selectionnable Si l'objet est selectionnable ou non
   void					assignerEstSelectionnable( bool selectionnable );

   /// Verifie si le noeud est selectionnable.
   /// @return Un booleen indiquant si le noeud est selectionnable.
   bool					estSelectionnable() const;

   /// ecrit si le noeud peut etre enregistre ou non.
   /// @param enregistrable Si le noeud est enregistrable ou non
   void					assignerEstEnregistrable( bool enregistrable );

   /// Verifie si le noeud est enregistrable.
   /// @return Un booleen indiquant si le noeud est enregistrable.
   bool					estEnregistrable() const;

   /// Definit une transformation
   /// @param translation	Le vecteur de translation
   /// @param angleRotation L'angle de rotation
   /// @param axeRotation	L'axe de rotation
   /// @param taille		La taille du noeud
   void					setTransformation(const aiVector3D& translation,
													 float angleRotation,
													 const aiVector3D& axeRotation,
													 const aiVector3D& taille);

   /// Calcule la profondeur de l'arbre sous le noeud courant.
   /// @return La profondeur de l'arbre.
   virtual unsigned int			calculerProfondeur() const;

   /// Vide le noeud de ses enfants.
   virtual void					vider();

   /// Efface le noeud passe en parametre.
   /// @param noeud Le noeud a effacer
   virtual void					effacer( const NoeudAbstrait* noeud );

   /// Cherche un noeud par le type (sur un noeud constant).
   /// @param Le type de noeud a rechercher
   /// @return Le noeud recherche
   virtual const NoeudAbstrait*	chercher( const std::string& typeNoeud ) const;

   /// Cherche un noeud par le type.
   /// @param Le type de noeud a rechercher
   /// @return Le noeud recherche
   virtual NoeudAbstrait*		chercher( const std::string& typeNoeud );

   /// Cherche un noeud enfant selon l'indice (sur un noeud constant).
   /// @param indice L'indice du noeud a rechercher
   /// @return Le noeud recherche
   virtual const NoeudAbstrait* chercher( unsigned int indice ) const;

   /// Cherche un noeud enfant selon l'indice.
   /// @param indice L'indice du noeud a rechercher
   /// @return Le noeud recherche
   virtual NoeudAbstrait*		chercher( unsigned int indice );

   /// Ajoute un noeud enfant.
   /// @param enfant Le noeud enfant a ajouter
   /// @return Un booleen si le noeud est ajoute
   virtual bool					ajouter( NoeudAbstrait* enfant );

   /// Obtient le nombre d'enfants du noeud.
   /// @return Le nombre d'enfants
   virtual unsigned int			obtenirNombreEnfants() const;

   /// Changer la selection du noeud.
   virtual void					inverserSelection();

   /// Efface les enfants selectionnes.
   virtual void					effacerSelection();

   /// Selectionne tous les enfants de meme que le noeud.
   virtual void					selectionnerTout();

   /// Deselectionne tous les enfants de meme que le noeud.
   virtual void					deselectionnerTout();

   /// Verifier si le noeud ou un de ses enfants est selectionne.
   /// @return un booleen si un des noeuds est selectionne
   virtual bool					selectionExiste() const;

   /// Change le mode d'affichage des polygones.
   /// @param estForce Etat du mode d'affichage des polygones
   virtual void					changerModePolygones( bool estForce );

   /// Assigne le mode d'affichage des polygones.
   /// @param modePolygones Le mode d'affichage des polygones
   virtual void					assignerModePolygones( GLenum modePolygones );

   /// Affiche le noeud.
   virtual void					afficher(bool selection3D=false) const;

   /// Affiche le noeud de maniere concrete.
   virtual void					afficherConcret() const;

   /// Anime le noeud.
   /// @param dt Le delta du temps depuis la derniere frame affichee
   virtual void					animer( float dt );

   /// Dessin temporaire pour les objets en mettant des couleurs differents
   /// @param longueur	La longueur de l'objet temporaire
   /// @param r			La valeur de rouge
   /// @param g			La valeur de vert
   /// @param b			La valeur de bleu
   virtual void					objetTemporaire( float longueur, float r, float g, float b ) const;

   /**
    * Retourne le modele 3D
	* @return Le modele 3D
	*/
   inline Modele3D*				getModele3D() { return &modele_; }

   // Permet d'obtenir la position du noeud
   // @return La position du noeud
   inline aiVector3D			getPosition() const { return position_; }
	
   /**
   * @description Methode qui permet de definir si l'element doit etre transparent
   * @author Vincent Longpre
   */
	void						toggleTransparent();

	/**
	 * Getter pour la boîte englobante
	 * @return La boîte englobante
	 */
	inline math::BoiteEnglobanteOrientee&	getBoiteEnglobanteOrientee() { return boiteEnglobanteOrientee_; }

	// Permet d'obtenir la boite englobante orientee avec une methode constante
	// @return La boite englobante
	inline const math::BoiteEnglobanteOrientee& getBoiteEnglobanteOrientee() const { return boiteEnglobanteOrientee_; }

protected:
   /// Type du noeud.
   std::string      type_;

   /// Mode d'affichage des polygones.
   GLenum           modePolygones_;

   /// Position relative du noeud.
   Vecteur3         positionRelative_;

   /// Vrai si on doit afficher le noeud.
   bool             affiche_;

   /// Selection du noeud.
   bool             selectionne_;

   /// Vrai si le noeud est selectionnable.
   bool             selectionnable_;

   /// Determine si l'objet peut etre sauvegarde en XML.
   bool             enregistrable_;

   /// Pointeur vers le parent.
   NoeudAbstrait*   parent_;

   /// Modele 3D correspondant a ce noeud.
   Modele3D			modele_;
	
   /// Liste d'affichage pour l'affichage de ce noeud.
   GLuint			liste_;

   /// Position du noeud
   aiVector3D		position_;

   /// Angle de rotation
   float			angleRotation_;

   /// Axe de rotation du noeud
   aiVector3D		axeRotation_;

   /// Taille du noeud
   aiVector3D		taille_;

	/**
	 * La boite englobante orientee de l'objet
	 */
	math::BoiteEnglobanteOrientee	boiteEnglobanteOrientee_;

	/**
	 * Variable statique utilisée pour attribuer des noms pour la sélection 3D aux objets
	 */
	static unsigned int nomSelection_;
};

#endif // __ARBRE_NOEUDS_NOEUDABSTRAIT_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
