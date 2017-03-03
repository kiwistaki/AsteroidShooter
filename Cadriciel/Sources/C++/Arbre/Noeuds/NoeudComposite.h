///////////////////////////////////////////////////////////////////////////////
/// @file NoeudComposite.h
/// @author DGI-INF2990
/// @date 2007-01-25
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_NOEUDS_NOEUDCOMPOSITE_H__
#define __ARBRE_NOEUDS_NOEUDCOMPOSITE_H__


#include "NoeudAbstrait.h"

#include <vector>


///////////////////////////////////////////////////////////////////////////
/// @class NoeudComposite
/// @brief Implantation d'un noeud du patron composite qui peut posseder
///        des enfants.
///
///        Cette classe implante les differentes fonctions relatives aux
///        enfants, comme l'ajout, le retrait, la recherche, etc.
///
/// @author DGI-2990
/// @date 2007-01-24
///////////////////////////////////////////////////////////////////////////
class NoeudComposite : public NoeudAbstrait
{
public:
   /// Constructeur.
								NoeudComposite(
									const std::string& type = std::string( "" )
									);

   /// Destructeur.
   virtual					   ~NoeudComposite();

   /// Le choix du conteneur pour les enfants.
   typedef std::vector<NoeudAbstrait*>	conteneur_enfants;

   /// getter
   /// @return Le conteneur d'enfants
   inline const conteneur_enfants& getEnfants() const { return enfants_; }
   inline conteneur_enfants& getEnfants() { return enfants_; }

   // Interface d'un noeud

   /// Calcule la profondeur de l'arbre sous le noeud courant.
   /// @return La profondeur de l'arbre
   virtual unsigned int			calculerProfondeur() const;

   /// Vide le noeud de ses enfants.
   virtual void					vider();
   /// Efface le noeud passe en parametre.
   virtual void					effacer( const NoeudAbstrait* noeud );

   /// Cherche un noeud par le type (sur un noeud constant).
   /// @return Le Noeud recherche
   virtual const NoeudAbstrait*	chercher( const std::string& typeNoeud ) const;
   /// Cherche un noeud par le type.
   /// @return Le Noeud recherche
   virtual NoeudAbstrait*		chercher( const std::string& typeNoeud );
   /// Cherche un noeud enfant selon l'indice (sur un noeud constant).
   /// @return Le Noeud recherche
   virtual const NoeudAbstrait*	chercher( unsigned int indice ) const;
   /// Cherche un noeud enfant selon l'indice.
   /// @return Le Noeud recherche
   virtual NoeudAbstrait*		chercher( unsigned int indice );

   /// Ajoute un noeud enfant.
   /// @return Vrai si l'objet a ete ajoute
   virtual bool					ajouter( NoeudAbstrait* enfant );
   /// Obtient le nombre d'enfants du noeud.
   /// @return Le nombre d'enfants
   virtual unsigned int			obtenirNombreEnfants() const;

   // Changer la selection du noeud: on prend la version de la classe de
   // base.
   // virtual void inverserSelection();
   /// Efface les enfants selectionnes.
   virtual void					effacerSelection();
   /// Selectionne tous les enfants de meme que le noeud.
   virtual void					selectionnerTout();
   /// Deselectionne tous les enfants de meme que le noeud.
   virtual void					deselectionnerTout();
   /// Verifier si le noeud ou un de ses enfants est selectionne.
   /// @return Vrai si un des enfants est selectionne
   virtual bool					selectionExiste() const;

   /// Change le mode d'affichage des polygones.
   virtual void					changerModePolygones( bool estForce );
   /// Assigne le mode d'affichage des polygones.
   virtual void					assignerModePolygones( GLenum modePolygones );
   // Affiche le noeud: on prend la version de la classe de base.
   // virtual void afficher() const;
   /// Affiche le noeud de maniere concrete.
   virtual void					afficherConcret() const;
   /// Anime le noeud.
   virtual void					animer( float dt );
  

protected:
  
   /// La liste des enfants.
   conteneur_enfants					enfants_;


private:
   /// Constructeur copie declare prive mais non defini pour eviter le
   /// constructeur copie genere par le compilateur.
   NoeudComposite(const NoeudComposite&);

};


#endif // __ARBRE_NOEUDS_NOEUDCOMPOSITE_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
