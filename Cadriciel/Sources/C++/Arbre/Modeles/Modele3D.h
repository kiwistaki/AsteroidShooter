///////////////////////////////////////////////////////////////////////////////
/// @file Modele3D.h
/// @author Julien Gascon-Samson
/// @date 2011-05-19
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
///////////////////////////////////////////////////////////////////////////////
#ifndef __MODELE3D_H__
#define __MODELE3D_H__

#include "assimp.hpp"      // Interface d'importation "assimp" C++
#include "aiScene.h"       // Structure de donnees de sortie "assimp"
#include "aiPostProcess.h" // Drapaux de post-traitement "assimp"

#include <windows.h>
#include <GL\gl.h>

#include <string>
#include <map>

#include "Vecteur.h"

using namespace std;

///////////////////////////////////////////////////////////////////////////
/// @class Modele3D
/// @brief Classe qui encapsule un modele 3d de la librairie 'assimp'.
///        Cette classe permet de charger un modele 3d d'un fichier
///        exporte par un outil (en utilisant ladite librairie) et de
///        l'afficher.
///
/// @author Julien Gascon-Samson
/// @date 2011-07-21
///////////////////////////////////////////////////////////////////////////
class Modele3D
{
public:
	/// Creation du modele 3d
	Modele3D();

	/// Destruction du modele 3d
	~Modele3D();

	/**
	 * Attribuer au modèle son display liste (utilisé principalement pour les
	 * objets de type NoeudAsteroide)
	 * @param liste La display liste à utiliser
	 */
	void setDisplayList(GLuint list);

	/// Charger le modele 3d a partir d'un fichier
	void charger(const string& nomFichier);

	/// Effectuer le rendu
	void dessiner() const;

    /// Calcule la sphere englobante
    double calculerSphereEnglobante() const;

    /// Calcule le cylindre englobant
	/// @param rayon Le rayon
	/// @param bas Le bas
	/// @param haut Le haut
    void calculerCylindreEnglobant(double& rayon, double& bas, double& haut) const;

    /// Calcule le rayon du cylindre englobant
	/// @param coinMin Le coin minimum
	/// @param coinMax Le coin maximum
    void calculerBoiteEnglobante(Vecteur3& coinMin, Vecteur3& coinMax) const;

	/// Assigner le facteur d'agrandissement
	/// @param facteurAgrandissement Le facteur d'agrandissement du modele
	inline void assignerFacteurAgrandissement(float facteurAgrandissement);

	/// Obtenir le facteur d'agrandissement
	inline const float obtenirFacteurAgrandissement();

	/// Permet de definir si un modele est selectionne ou non
	/// @param selectionne L'etat de selection
	inline void setSelectionne(bool selectionne) { selectionne_ = selectionne; }

	inline float getRayonSphereEnglobante() const { return rayonSphereEnglobante_; }

private:

	/// Nom associe au modele
	string					nomModele_;

	/** Identifiant de la liste d'affichage */
	GLuint					liste_;

	/// Objet scene assimp representant le modele charge
	const aiScene*			scene_;
	
	/// Map des textures, pour associer chaque nom de texture a un identificateur GLuint
	map<string, GLuint>		mapTextures_;

	/// Facteur d'agrandissement de l'objet
	float					facteurAgrandissement_;

	/** Le modele est-il selectionne? */
	bool					selectionne_;

	/** Points extremes minimaux en X. On les sauvegarde au debut pour ne pas a avoir a les
	 * calculer tout le temps
	 */
	Vecteur3f				pointsExtremesMinX_;

	/** Points extremes minimaux en Y. On les sauvegarde au debut pour ne pas a avoir a les
	 * calculer tout le temps
	 */
	Vecteur3f				pointsExtremesMinY_;

	/** Points extremes minimaux en Z. On les sauvegarde au debut pour ne pas a avoir a les
	 * calculer tout le temps
	 */
	Vecteur3f				pointsExtremesMinZ_;

	/** Points extremes maximaux en X. On les sauvegarde au debut pour ne pas a avoir a les
	 * calculer tout le temps
	 */
	Vecteur3f				pointsExtremesMaxX_;

	/** Points extremes maximaux en Y. On les sauvegarde au debut pour ne pas a avoir a les
	 * calculer tout le temps
	 */
	Vecteur3f				pointsExtremesMaxY_;

	/** Points extremes maximaux en Z. On les sauvegarde au debut pour ne pas a avoir a les
	 * calculer tout le temps
	 */
	Vecteur3f				pointsExtremesMaxZ_;

	/** Rayon de la sphère englobante pour ne pas avoir à la calculer à chaque fois */
	float					rayonSphereEnglobante_;
};

////////////////////////////////////////////////////////////////////////
///
/// @fn void Modele3D::assignerFacteurAgrandissement( 
///                    float facteurAgrandissement )
///
/// Cette fonction permet d'assigner un facteur de zoom qui peut etre
/// utilise pour grossir ou reduir l'objet. Notez que vous n'etes pas
/// obliges de recourir a cette fonction, vous pouvez aussi bien
/// manipuler les matrices OpenGL avant d'appeler la fonction de rendu.
///
/// @param[in] facteurAgrandissement : facteur d'agrandissement.
///            Un facteur de 1 correspond a la taille originale.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Modele3D::assignerFacteurAgrandissement(float facteurAgrandissement)
{
	facteurAgrandissement_ = facteurAgrandissement;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Modele3D::obtenirFacteurAgrandissement()
///
/// Cette fonction retourne le facteur d'agrandissement actuel de
/// l'objet, qui sera applique au rendu.
///
/// @return Le facteur d'agrandissement. Un facteur de 1 correspond a
///         la taille originale.
///
////////////////////////////////////////////////////////////////////////
const float Modele3D::obtenirFacteurAgrandissement()
{
	return facteurAgrandissement_;
}

#endif // __MODELE3D_H__

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
