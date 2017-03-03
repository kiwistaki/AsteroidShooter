/**
 * @file GestionnaireRessources.h
 * @author The FloppyDisketeers
 * @date 2014-02-04
 * @version 1.0
 */
#ifndef GESTIONNAIRE_ASTEROIDE_H
#define GESTIONNAIRE_ASTEROIDE_H

#include "../../../../Commun/Externe/assimp/include/assimp.hpp"
#include "../../../../Commun/Externe/assimp/include/aiVector3D.h"

#include <vector>
using namespace std;

/**
 * @class GestionnaireAsteroide
 * @brief Classe qui s'occuppe de créer les astéroïdes
 *
 * Cette classe génère différent modèles d'astéroïde, créer des call lists et
 * permet d'en prendre un au hasard lorsqu'on veut créer un NoeudAsteroide.
 *
 * Cette classe est un singleton.
 *
 * L'algorithme de génération des astéroïdes est celui du marching cube (http://en.wikipedia.org/wiki/Marching_cubes).
 * Cet algorithme utilise une fonction implicite 3D, par exemple, celle d'une sphère:
 * f(x, y, z) = x² + y² + z² - R² = 0 où R est le rayon de la sphère, pour générer
 * une surface.
 *
 * L'algorithme part d'un cube qu'il subdivise en plusieurs petits cubes. Chacun
 * des sommets de ces cubes se voient attribuer une valeur à partir de la fonction implicite.
 * On parcours ensuite chacun des cubes et on vérifie si les sommets ont une valeur négative
 * ou positive. 
 *
 * Dans le premier cas, le sommet est à l'extérieur de la surface. Dans le second cas, le
 * sommet est à l'intérieur. On prend note de tous les sommets dont la valeur est négative
 * et on créer des sommets qui définissent une surface qui exclue ces sommets négatifs.
 *
 * On répète le processus processus pour toutes les subdivisions du cube original et la
 * liste finale de sommets représente la surface implicite.
 *
 * Dans ce cas particulier, on veut des astéroïdes qui ont des formes relativement sphérique
 * et ellipsoïde. On part donc d'une sphère ou d'une forme ellipsoïde et on perturbe sa
 * surface en introduisant du bruit à l'aide d'une texture procédurale (http://en.wikipedia.org/wiki/Procedural_texture).
 * Plusieurs types de textures procédurales existent et celle utilise est de type Worley
 * (http://en.wikipedia.org/wiki/Worley_noise).
 *
 * La fonction implicite utilisé pour généré les astéroïdes est:
 * f(x, y, z) = (x² / a + y² / b + z² / c + sin(texel) * varSin + texel * varTexel) - R²
 *
 * Où a, b et c sont les rayons de l'ellipsoïde, texel est la valeur de la texture au point (x, y, z) et
 * varSin et varTexel sont des coefficients pour contrôler comment la surface sera modifié. R est le rayon
 * de la sphère initiale que l'on vient perturber.
 *
 * Il est a noter que les rayons a, b et c ne sont pas utilisés dans des divisions mais bien dans
 * des multiplications dans l'implémentation.
 *
 * Pour plus de détails sur l'implémentation  des textures Worley : http://aftbit.com/cell-noise-2/
 * Pour plus de détails sur l'implémentation de l'algorithm de Marching Cube : http://paulbourke.net/geometry/polygonise/
 */
class GestionnaireAsteroide {
	public:
		static GestionnaireAsteroide*	getInstance();

		/**
		 * Génère un certain nombre d'astéroïdes en faisant varier les
		 * paramètres de création. Cette fonction ne fait que compiler des
		 * display list d'OpenGL et génère des sphères englobantes pour les
		 * astéroïdes
		 * @param numAsteroides Le nombre de variation d'astéroïdes à générer
		 * @param numCellX Le nombre de subdivision sur l'axe des x
		 * @param numCellY Le nombre de subdivision sur l'axe des y
		 * @param numCellZ Le nombre de subdivision sur l'axe des z
		 * @param rayonSphere Le rayon de la sphère que l'on vient perturber
		 * @param ellipseXMin La valeur minimale que peut prendre le rayon elliptique sur l'axe des x
		 * @param ellipseXMax La valeur maximale que peut prendre le rayon elliptique sur l'axe des x
		 * @param ellipseYMin La valeur minimale que peut prendre le rayon elliptique sur l'axe des y
		 * @param ellipseYMax La valeur maximale que peut prendre le rayon elliptique sur l'axe des y
		 * @param ellipseZMin La valeur minimale que peut prendre le rayon elliptique sur l'axe des z
		 * @param ellipseZMax La valeur maximale que peut prendre le rayon elliptique sur l'axe des z
		 * @param variationSinMin La valeur minimale que peut prendre la variation du sinus
		 * @param variationSinMax La valeur maximale que peut prendre la variation du sinus
		 * @param variationTexelMin La valeur minimale que peut prendre le gain du texel
		 * @param variationTexelMax La valeur maximale que peut prendre le gain du texel
		 */
		void							genererAsteroides(int numAsteroides,
														  int numCellX, int numCellY, int numCellZ,
														  float rayonSphere,
														  float ellipseXMin, float ellipseXMax,
														  float ellipseYMin, float ellipsYMax,
														  float ellipseZMin, float ellipseZMax,
														  float variationSinMin, float variationSinMax,
														  float variationTexelMin, float variationTexelMax);

		/**
		 * Détruit tous les astéroïdes
		 */
		void							detruireAsteroides();

		/**
		 * Retourne un modèle d'astéroïde pris au hasard parmis le bassin
		 * d'objets.
		 * @param liste La liste d'affichage OpenGL représentant le modèle
		 * d'astéroïde.
		 * @param rayon Le rayon de l'astéroïde
		 */
		void							getModeleAsteroide(unsigned int& liste, float& rayon) const;

	private:
		/**
		 * @struct GridCell_t
		 * Structure représentant un cube dans l'algorithme du marching cube.
		 * Contient la position de ses 8 sommets ainsi que les valeurs de la
		 * surface implicite pour chacun des sommets
		 */
		struct GridCell_t {
			/** La position des sommets */
			aiVector3D pos[8];
		
			/** La valeur de la surface implicite aux sommets du cube */
			float val[8];
		};

		/** Instance du singleton */
		static GestionnaireAsteroide	instance_;

		/** Valeur utilisé pour le hashage */
		static const unsigned int		OFFSET_BASIS = 2166136261;

		/** Valeur utilisé pour le hashage */
		static const unsigned int		FNV_PRIME = 16777619;

		/** Rayon de la sphère */
		float							rayonSphere_;

		/** Rayon en X minimale pour l'ellipsoïde */
		float							ellipseXMin_;

		/** Rayon en X maximale pour l'ellipsoïde */
		float							ellipseXMax_;

		/** Rayon en Y minimale pour l'ellipsoïde */
		float							ellipseYMin_;

		/** Rayon en Y maximale pour l'ellipsoïde */
		float							ellipseYMax_;

		/** Rayon en Z minimale pour l'ellipsoïde */
		float							ellipseZMin_;

		/** Rayon en Z maximale pour l'ellipsoïde */
		float							ellipseZMax_;

		/** Variation du sinus minimale */
		float							variationSinMin_;

		/** Variation du sinus maximale */
		float							variationSinMax_;

		/** Variation du texel minimale */
		float							variationTexelMin_;

		/** Variation du texel maximale */
		float							variationTexelMax_;

		/** Tableau qui indique, pour un sommet donné, sur quels arrêtes des
		 * sommets devront êtres générés */
		static const int				edgeTable[256];

		/** Tableau qui indique comment former les triangles dans le cube */
		static const int				triTable[256][16];

		/** Liste des display lists générés */
		vector<unsigned int>			listeAsteroides_;

		/** Liste des rayons */
		vector<float>					rayonAsteroides_;

		/**
		 * Constructeur. Génère les modèles et créer les call lists
		 */
										GestionnaireAsteroide();

		/**
		 * Destructeur.
		 */
									   ~GestionnaireAsteroide();

		/**
		 * Constructeur par copie pour le singleton
		 */
										GestionnaireAsteroide(const GestionnaireAsteroide& src);

		/**
		 * Opérateur d'affection pour le singleton
		 */
		GestionnaireAsteroide&			operator=(const GestionnaireAsteroide& src);

		/**
		 * Utilisé pour la génération de textures Worley. Utilise une distribution
		 * Poisson, pour connaître la probabilité du nombre de points dans un
		 * carré.
		 * @param value Une valeur générée aléatoirement par un générateur linéaire.
		 * @return Le nombre de points se trouvant dans le carré courant.
		 */
		unsigned int					poissonLookUp(unsigned int value) const;

		/**
		 * Utilisé pour la génération de textures Worley. Doonne un nombre
		 * pseudo aléatoire à l'aide d'un générateur linéaire (http://en.wikipedia.org/wiki/Linear_congruential_generator)
		 * @param lastValue La dernière valeur retournée par ce générateur
		 * @return Une valeur pseudo aléatoire
		 */
		unsigned int					lcgRandom(unsigned int lastValue) const;

		/**
		 * Utilisé pour la génération de textures Worley. Utilisé pour avoir un
		 * nombre toujours reproduisable afin de l'utilisé comme seed pour le
		 * générateur lcg. On utilise le FNV hashing algorithm (http://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function)
		 * @param i La position en x du cube pour la génération de texture Worley
		 * @param j La position en y du cube pour la génération de texture Worley
		 * @param k La position en z du cube pour la génération de texture Worley
		 * @return Une valeur qui sera toujours la même pour ces 3 valeurs
		 */
		unsigned int					hashValues(unsigned int i, unsigned int j, unsigned int k) const;

		/**
		 * Utiliser insertion sort pour insérer une valeur dans un tableau afin de toujours avoir le maximum
		 * en première position.
		 * @param distArray Le tableau dans lequel on veut ajouter la valeur
		 * @param value La valeur à ajouter
		 */
		void							insererTableauDistances(vector<float>& distArray, float value) const;

		/**
		 * Génère la couleur pour un point de la texture worley
		 * @param input La position du cube pour lequel on veut évaluer la texture Worley
		 * @param seed La veleur du seed pour cette texture
		 * @param distArray Un vector de float contenant les distances relatives des points
		 * dans la texture Worley
		 * @return La couleur de ce point
		 */
		float							genererCouleurWorley(const aiVector3D& input, int seed,
															 vector<float>& distArray) const;

		/**
		 * Génère une texture 3D de type Worley Noise (un tableau de texture 2D)
		 * @param width La longueur de la texture
		 * @param height La hauteur de la texture
		 * @param depth La profondeur de la texture
		 * @return Un vecteur de vecteurs de vecteurs de floats représentant la
		 * texture 3D
		 */
		vector<vector<vector<float> > >	textureWorleyNoise3D(int width, int height, int depth) const;

		/**
		 * Génère les triangles pour le cube courant
		 * @param cell Le cube courant
		 * @param vertices Une référence vers une liste de sommets. Cette liste
		 * contiendra les sommets générés pour ce cube.
		 */
		void							polygonise(const GridCell_t& cell,
												   vector<aiVector3D>& vertices) const;

		/**
		 * Génère un sommet par interpolation linéaire pour une arrête
		 * @param p1 Le premier point de l'arrête
		 * @param p2 Le second point de l'arrête
		 * @param v1 La valeur du premier point
		 * @param v2 La valeur du second point
		 * @return Le sommet interpolé
		 */
		aiVector3D						sommetInterpoler(const aiVector3D& p1, const aiVector3D& p2,
														 float v1, float v2) const;

		/**
		 * Fonction de densité pour la surface implicite
		 * @param point Le point pour lequel la fonction est évaluée
		 * @param texel Le texel a utiliser dans la fonction de densité
		 * @return La valeur de la fonction au point évalué
		 */
		float							fonctionDensite(const aiVector3D& point, float texel) const;

		/**
		 * Retourne un nombre aléatoire entre deux extrêmes
		 * @param min La valeur minimale du nombre
		 * @param max La valeur maximale du nombre
		 * @return Le nomobre aléatoire dans [min, max]
		 */
		float							aleatoireDansInterval(float min, float max) const;
};

#endif