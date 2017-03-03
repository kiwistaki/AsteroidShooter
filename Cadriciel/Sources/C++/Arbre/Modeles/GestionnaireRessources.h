/**
 * @file GestionnaireRessources.h
 * @author The FloppyDisketeers
 * @date 2014-02-04
 * @version 1.0
 *
 * @addtogroup inf2990 INF2990
 * @{
 */
#ifndef GESTIONNAIRE_RESSOURCES_H
#define GESTIONNAIRE_RESSOURCES_H

#include <windows.h>
#include <GL\gl.h>

#include <map>
#include <string>
#include <vector>
using namespace std;

#include "assimp.hpp"      // Interface d'importation "assimp" C++
#include "aiScene.h"       // Structure de donnees de sortie "assimp"
#include "aiPostProcess.h" // Drapaux de post-traitement "assimp"

#include "../../../Commun/Utilitaire/Vecteur.h"

/**
 * @class GestionnaireRessources
 * @brief Cette class est un singleton. Elle permet de centraliser le chargement des
 * ressources et permet de re-utiliser ce qui a deja ete charge, comme les
 * modeles 3D ou les textures
 */
class GestionnaireRessources {
	public:
		/**
		 * Retourne l'instance du singleton.
		 */
		static GestionnaireRessources*	getInstance();

		/**
		 * Destructeur. Libere toutes les ressources.
		 */
									   ~GestionnaireRessources();

		/**
		 * Charge un modele 3D
		 * @param nomFichier	Le nom du fichier du modele a charger
		 * @param textures		Une map de textures pour l'objet. La cle est le nom de la texture et la valeur est l'identifiant de la texture
		 * @return				La scene assimp representant l'objet si l'objet a ete bien charge. NULL sinon
		 */
		const aiScene*					chargerModele3D(const string& nomFichier,
														map<string, GLuint>& textures);

		/**
		 * Creer une liste d'affichage pour un modele specifie
		 * @param scene Une scene Assimp permettant d'acceder aux donnees du modele pour l'afficher.
		 * @return L'identifiant de la liste d'affichage creee ou GL_INVALID_VALUE
		 */
		GLuint							creerCallList(const aiScene* scene);

		/**
		 * Charge une texture
		 * @param nomFichier	Le nom du fichier de la texture a charger
		 * @param texture		L'identificateur de la texture
		 * @return				True si la texture a ete charge correctement, false sinon
		 */
		bool							chargerTexture(const string& nomFichier,
													   GLuint& texture);

		/**
		 * Calcule les points extremes d'un modele deja charge. S'il n'est pas
		 * deja charge, alors la fonction ne calculera rien.
		 * @param nomFichier Le nom du modele pour lequel on veut calculer les
		 * points extremes.
		 * @param xMin Points extremes minimaux en x
		 * @param yMin Points extremes minimaux en y
		 * @param zMin Points extremes minimaux en z
		 * @param xMax Points extremes maximaux en x
		 * @param yMax Points extremes maximaux en y
		 * @param zMax Points extremes maximaux en z
		 * @return true si le modele est deja charge, false sinon.
		 */
		bool							calculerPointsExtremes(const string& nomFichier,
																Vecteur3f& xMin,
																Vecteur3f& yMin,
																Vecteur3f& zMin,
																Vecteur3f& xMax,
																Vecteur3f& yMax,
																Vecteur3f& zMax);

		/**
		 * Calcule le rayon de la sphère englobante
		 * @param nomFichier Le nom du fichier du modèle pour lequel on veut
		 * calculer le rayon de la sphère englobante
		 * @return Le rayon de la sphère englobante
		 */
		float							calculerRayonSphereEnglobante(const string& nomFichier);

	private:
		/** L'instance du singleton */
		static GestionnaireRessources	instance_;

		/** Liste d'Importeur assimp */
		vector<Assimp::Importer*>		importer_;

		/** Flags pour le post processing lorsqu'on charge un modele */
		unsigned int					postProcessSteps_;

		/** Map des modeles charges */
		map<string, const aiScene*>		modelesCharges_;

		/** Map des call lists crees */
		map<const aiScene*, GLuint>		callListCrees_;

		/** Map des textures charges */
		map<string, GLuint>				texturesCharges_;

		/** Points extremes minimaux en x */
		map<string, Vecteur3f>			pointsExtremesMinX_;

		/** Points extremes minimaux en y */
		map<string, Vecteur3f>			pointsExtremesMinY_;

		/** Points extremes minimaux en z */
		map<string, Vecteur3f>			pointsExtremesMinZ_;

		/** Points extremes maximaux en x */
		map<string, Vecteur3f>			pointsExtremesMaxX_;

		/** Points extremes maximaux en y */
		map<string, Vecteur3f>			pointsExtremesMaxY_;

		/** Points extremes maximaux en z */
		map<string, Vecteur3f>			pointsExtremesMaxZ_;

		/** Rayon des sphères englobantes des modèles */
		map<string, float>				rayonsSpheresEnglobantes_;

		/**
		 * Constructeur
		 */
										GestionnaireRessources();

		/**
		 * Constructeur par copie
		 */
										GestionnaireRessources(const GestionnaireRessources& src);

		/**
		 * Operateur d'assignation
		 */
										GestionnaireRessources& operator= (const GestionnaireRessources& rhs);

		/**
		 * Calcul les points extremes d'un noeud d'une scene
		 * @param scene La scene representant le modele
		 * @param noeud Le noeud du mesh pour lequel on veut calculer les
		 * points extremes
		 * @param xMin Points extremes minimaux en x
		 * @param yMin Points extremes minimaux en y
		 * @param zMin Points extremes minimaux en z
		 * @param xMax Points extremes maximaux en x
		 * @param yMax Points extremes maximaux en y
		 * @param zMax Points extremes maximaux en z
		 */
		void							calculerPointsExtremes(const aiScene* scene,
															   const aiNode* noeud,
															   Vecteur3f& xMin,
															   Vecteur3f& yMin,
															   Vecteur3f& zMin,
															   Vecteur3f& xMax,
															   Vecteur3f& yMax,
															   Vecteur3f& zMax) const;

		/**
		 * Dessine un modele charge par Assimp. Utilise pour creer les listes
		 * d'affichage
		 * @param scene La scene Assimp a dessiner
		 * @param noeud Le noeud Assimp a dessiner
		 */
		void							dessinerModele(const aiScene* scene, const aiNode* noeud) const;

		/**
		 * Applique un materiau sur l'objet. Utilise pour creer les listes
		 * d'affichage
		 * @param materiau Le materiau a appliquer
		 */
		void							appliquerMateriau(const aiMaterial* materiau) const;
};

#endif

/**
 * @}
 */