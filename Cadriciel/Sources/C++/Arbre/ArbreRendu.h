///////////////////////////////////////////////////////////////////////////////
/// @file ArbreRendu.h
/// @author Martin Bisson
/// @date 2007-01-28
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __ARBRE_ARBRERENDU_H__
#define __ARBRE_ARBRERENDU_H__


#include "NoeudComposite.h"

#include <string>
#include <map>


class NoeudAbstrait;
class UsineNoeud;


///////////////////////////////////////////////////////////////////////////
/// @class ArbreRendu
/// @brief Classe d'arbre de rendu qui contient la racine de l'arbre de
///        rendu avec les usines qui permettent d'ajouter des noeuds a
///        cet arbre.
///
///        La profondeur de cet arbre est limitee par la taille de la pile
///        des matrices et la taille de la pile des noms pour la selection
///        OpenGL, etant donne que chaque niveau de l'arbre effectue un
///        "push" sur chacune de ces piles lors du rendu.  L'arbre ne
///        verifie pas que la profondeur reste sous la limite, mais il
///        offre des fonctions permettant de le verifier aisement.
///
/// @author Martin Bisson
/// @date 2007-01-28
///////////////////////////////////////////////////////////////////////////
class ArbreRendu : public NoeudComposite
{
public:
	/// Constructeur par defaut.
						ArbreRendu();
	/// Destructeur.
	virtual			   ~ArbreRendu();

	/// Ajoute une usine associee a un type de noeud.
	/// @param type	Le type du noeud
	/// @param usine L'usine du noeud a associer
	inline void			ajouterUsine(const std::string& type, const UsineNoeud* usine);

	/// Cree un nouveau noeud.
	/// @param typeNouveauNoeud Le type du noeud a creer
	NoeudAbstrait*		creerNoeud(const std::string& typeNouveauNoeud) const;

	/// Cree et ajoute un nouveau noeud a l'arbre.
	/// @param nomParent Le nom du parent du noeud
	/// @param typeNouveauNoeud Le type du nouveau noeud a ajouter
	NoeudAbstrait*		ajouterNouveauNoeud(const std::string& nomParent,
												const std::string& typeNouveauNoeud);

	/// Calcule la profondeur maximale possible pour l'arbre de rendu.
	static unsigned int	calculerProfondeurMaximale();

	virtual void		afficher(bool selection3D=false) const;

private:
	/// Definition du type pour l'association du nom d'un type vers l'usine
	/// correspondante.
	typedef std::map< std::string, const UsineNoeud* > RegistreUsines;
	/// Association du nom d'un type vers l'usine correspondante.
	RegistreUsines usines_;
};


////////////////////////////////////////////////////////////////////////
///
/// @fn inline void ArbreRendu::ajouterUsine(const std::string& type, const UsineNoeud* usine)
///
/// Cette fonction permet d'ajouter une usine qui sera ensuite utilisee
/// pour creer de nouveaux noeuds.
///
/// @param[in] type  : La cha�ne qui identifie le type de noeuds a creer
///                    avec cette usine.
/// @param[in] usine : L'usine ajoutee.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
inline void ArbreRendu::ajouterUsine(
   const std::string& type, const UsineNoeud* usine
   )
{
   usines_[type] = usine;
}


#endif // __ARBRE_ARBRERENDU_H__


///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
