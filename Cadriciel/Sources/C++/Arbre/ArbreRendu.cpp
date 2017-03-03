////////////////////////////////////////////////
/// @file   ArbreRendu.cpp
/// @author Martin Bisson
/// @date   2007-01-28
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "ArbreRendu.h"
#include "UsineNoeud.h"
#include "NoeudAbstrait.h"

#include <GL/glu.h>

////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRendu::ArbreRendu()
///
/// Ne fait qu'assigner que ce noeud n'est pas selectionnable.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRendu::ArbreRendu()
   : NoeudComposite("racine")
{
   // On ne veut pas que ce noeud soit selectionnable.
   assignerEstSelectionnable(false);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn ArbreRendu::~ArbreRendu()
///
/// Detruit les usines des noeuds de l'arbre.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
ArbreRendu::~ArbreRendu()
{
	for (RegistreUsines::iterator it = usines_.begin(); it != usines_.end(); ++it) {
		delete it->second;
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* ArbreRendu::creerNoeud(const std::string& typeNouveauNoeud) const
///
/// Cette fonction permet de creer un nouveau noeud, sans l'ajouter
/// directement a l'arbre de rendu.
///
/// @param[in] typeNouveauNoeud : Le type du nouveau noeud.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* ArbreRendu::creerNoeud(const std::string& typeNouveauNoeud) const
{
   if (usines_.find(typeNouveauNoeud) == usines_.end()) {
      // Incapable de trouver l'usine
      return 0;
   }

   // Pour une raison que je ne comprends pas, la ligne suivante ne
   // compile pas:
   //
   // const UsineNoeud* usine = usines_[typeNouveauNoeud];
   //
   // On utilisera donc:
   const UsineNoeud* usine = (*(usines_.find(typeNouveauNoeud))).second;

   return usine->creerNoeud();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* ArbreRendu::ajouterNouveauNoeud(const std::string& typeParent, const std::string& typeNouveauNoeud)
///
/// Cette fonction permet d'ajouter un nouveau noeud dans l'arbre de
/// rendu.
///
/// @param[in] typeParent       : Le type du parent du nouveau noeud.
/// @param[in] typeNouveauNoeud : Le type du nouveau noeud.
///
/// @return Le noeud nouvellement cree.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* ArbreRendu::ajouterNouveauNoeud(
   const std::string& typeParent,
   const std::string& typeNouveauNoeud
   )
{
   NoeudAbstrait* parent = chercher(typeParent);
   if (parent == 0) {
      // Incapable de trouver le parent
      return 0;
   }

   NoeudAbstrait* nouveauNoeud = creerNoeud(typeNouveauNoeud);
   if (nouveauNoeud)
      parent->ajouter(nouveauNoeud);

   return nouveauNoeud;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int ArbreRendu::calculerProfondeurMaximale()
///
/// Cette fonction retourne la profondeur maximale possible de l'arbre.
/// Comme lors du rendu, on effectue un glPushMatrix() pour sauvegarder
/// les transformations, ainsi qu'un glPushName() pour ajouter un nom
/// sur la pile des noms pour la selection, la profondeur maximale de
/// l'arbre est limitee par la taille de la pile des matrices ainsi que
/// par celle de la pile des noms pour la selection.
///
/// Cette fonction verifie donc ces deux valeurs et retourne la plus
/// petite, c'est-a-dire celle qui limite la profondeur de l'arbre.
///
/// @return La profondeur maximale possible de l'arbre de rendu.
///
////////////////////////////////////////////////////////////////////////
unsigned int ArbreRendu::calculerProfondeurMaximale()
{
   GLint profondeurPileMatrice, profondeurPileNoms;

   glGetIntegerv(GL_MAX_MODELVIEW_STACK_DEPTH , &profondeurPileMatrice);
   glGetIntegerv(GL_MAX_NAME_STACK_DEPTH      , &profondeurPileNoms);

   return (profondeurPileMatrice < profondeurPileNoms) ?
      profondeurPileMatrice : profondeurPileNoms;
}

void ArbreRendu::afficher(bool selection3D) const {
	if (selection3D) {
		glInitNames();
		glPushName(0);
		nomSelection_ = 1;
	}

    for (conteneur_enfants::const_iterator it = enfants_.begin();
         it != enfants_.end();
         ++it) {
        (*it)->afficher(selection3D);
    }

	if (selection3D) {
		glPopName();
	}
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////
