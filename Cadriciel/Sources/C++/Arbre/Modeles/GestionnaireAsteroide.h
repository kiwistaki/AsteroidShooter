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
 * @brief Classe qui s'occuppe de cr�er les ast�ro�des
 *
 * Cette classe g�n�re diff�rent mod�les d'ast�ro�de, cr�er des call lists et
 * permet d'en prendre un au hasard lorsqu'on veut cr�er un NoeudAsteroide.
 *
 * Cette classe est un singleton.
 *
 * L'algorithme de g�n�ration des ast�ro�des est celui du marching cube (http://en.wikipedia.org/wiki/Marching_cubes).
 * Cet algorithme utilise une fonction implicite 3D, par exemple, celle d'une sph�re:
 * f(x, y, z) = x� + y� + z� - R� = 0 o� R est le rayon de la sph�re, pour g�n�rer
 * une surface.
 *
 * L'algorithme part d'un cube qu'il subdivise en plusieurs petits cubes. Chacun
 * des sommets de ces cubes se voient attribuer une valeur � partir de la fonction implicite.
 * On parcours ensuite chacun des cubes et on v�rifie si les sommets ont une valeur n�gative
 * ou positive. 
 *
 * Dans le premier cas, le sommet est � l'ext�rieur de la surface. Dans le second cas, le
 * sommet est � l'int�rieur. On prend note de tous les sommets dont la valeur est n�gative
 * et on cr�er des sommets qui d�finissent une surface qui exclue ces sommets n�gatifs.
 *
 * On r�p�te le processus processus pour toutes les subdivisions du cube original et la
 * liste finale de sommets repr�sente la surface implicite.
 *
 * Dans ce cas particulier, on veut des ast�ro�des qui ont des formes relativement sph�rique
 * et ellipso�de. On part donc d'une sph�re ou d'une forme ellipso�de et on perturbe sa
 * surface en introduisant du bruit � l'aide d'une texture proc�durale (http://en.wikipedia.org/wiki/Procedural_texture).
 * Plusieurs types de textures proc�durales existent et celle utilise est de type Worley
 * (http://en.wikipedia.org/wiki/Worley_noise).
 *
 * La fonction implicite utilis� pour g�n�r� les ast�ro�des est:
 * f(x, y, z) = (x� / a + y� / b + z� / c + sin(texel) * varSin + texel * varTexel) - R�
 *
 * O� a, b et c sont les rayons de l'ellipso�de, texel est la valeur de la texture au point (x, y, z) et
 * varSin et varTexel sont des coefficients pour contr�ler comment la surface sera modifi�. R est le rayon
 * de la sph�re initiale que l'on vient perturber.
 *
 * Il est a noter que les rayons a, b et c ne sont pas utilis�s dans des divisions mais bien dans
 * des multiplications dans l'impl�mentation.
 *
 * Pour plus de d�tails sur l'impl�mentation  des textures Worley : http://aftbit.com/cell-noise-2/
 * Pour plus de d�tails sur l'impl�mentation de l'algorithm de Marching Cube : http://paulbourke.net/geometry/polygonise/
 */
class GestionnaireAsteroide {
	public:
		static GestionnaireAsteroide*	getInstance();

		/**
		 * G�n�re un certain nombre d'ast�ro�des en faisant varier les
		 * param�tres de cr�ation. Cette fonction ne fait que compiler des
		 * display list d'OpenGL et g�n�re des sph�res englobantes pour les
		 * ast�ro�des
		 * @param numAsteroides Le nombre de variation d'ast�ro�des � g�n�rer
		 * @param numCellX Le nombre de subdivision sur l'axe des x
		 * @param numCellY Le nombre de subdivision sur l'axe des y
		 * @param numCellZ Le nombre de subdivision sur l'axe des z
		 * @param rayonSphere Le rayon de la sph�re que l'on vient perturber
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
		 * D�truit tous les ast�ro�des
		 */
		void							detruireAsteroides();

		/**
		 * Retourne un mod�le d'ast�ro�de pris au hasard parmis le bassin
		 * d'objets.
		 * @param liste La liste d'affichage OpenGL repr�sentant le mod�le
		 * d'ast�ro�de.
		 * @param rayon Le rayon de l'ast�ro�de
		 */
		void							getModeleAsteroide(unsigned int& liste, float& rayon) const;

	private:
		/**
		 * @struct GridCell_t
		 * Structure repr�sentant un cube dans l'algorithme du marching cube.
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

		/** Valeur utilis� pour le hashage */
		static const unsigned int		OFFSET_BASIS = 2166136261;

		/** Valeur utilis� pour le hashage */
		static const unsigned int		FNV_PRIME = 16777619;

		/** Rayon de la sph�re */
		float							rayonSphere_;

		/** Rayon en X minimale pour l'ellipso�de */
		float							ellipseXMin_;

		/** Rayon en X maximale pour l'ellipso�de */
		float							ellipseXMax_;

		/** Rayon en Y minimale pour l'ellipso�de */
		float							ellipseYMin_;

		/** Rayon en Y maximale pour l'ellipso�de */
		float							ellipseYMax_;

		/** Rayon en Z minimale pour l'ellipso�de */
		float							ellipseZMin_;

		/** Rayon en Z maximale pour l'ellipso�de */
		float							ellipseZMax_;

		/** Variation du sinus minimale */
		float							variationSinMin_;

		/** Variation du sinus maximale */
		float							variationSinMax_;

		/** Variation du texel minimale */
		float							variationTexelMin_;

		/** Variation du texel maximale */
		float							variationTexelMax_;

		/** Tableau qui indique, pour un sommet donn�, sur quels arr�tes des
		 * sommets devront �tres g�n�r�s */
		static const int				edgeTable[256];

		/** Tableau qui indique comment former les triangles dans le cube */
		static const int				triTable[256][16];

		/** Liste des display lists g�n�r�s */
		vector<unsigned int>			listeAsteroides_;

		/** Liste des rayons */
		vector<float>					rayonAsteroides_;

		/**
		 * Constructeur. G�n�re les mod�les et cr�er les call lists
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
		 * Op�rateur d'affection pour le singleton
		 */
		GestionnaireAsteroide&			operator=(const GestionnaireAsteroide& src);

		/**
		 * Utilis� pour la g�n�ration de textures Worley. Utilise une distribution
		 * Poisson, pour conna�tre la probabilit� du nombre de points dans un
		 * carr�.
		 * @param value Une valeur g�n�r�e al�atoirement par un g�n�rateur lin�aire.
		 * @return Le nombre de points se trouvant dans le carr� courant.
		 */
		unsigned int					poissonLookUp(unsigned int value) const;

		/**
		 * Utilis� pour la g�n�ration de textures Worley. Doonne un nombre
		 * pseudo al�atoire � l'aide d'un g�n�rateur lin�aire (http://en.wikipedia.org/wiki/Linear_congruential_generator)
		 * @param lastValue La derni�re valeur retourn�e par ce g�n�rateur
		 * @return Une valeur pseudo al�atoire
		 */
		unsigned int					lcgRandom(unsigned int lastValue) const;

		/**
		 * Utilis� pour la g�n�ration de textures Worley. Utilis� pour avoir un
		 * nombre toujours reproduisable afin de l'utilis� comme seed pour le
		 * g�n�rateur lcg. On utilise le FNV hashing algorithm (http://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function)
		 * @param i La position en x du cube pour la g�n�ration de texture Worley
		 * @param j La position en y du cube pour la g�n�ration de texture Worley
		 * @param k La position en z du cube pour la g�n�ration de texture Worley
		 * @return Une valeur qui sera toujours la m�me pour ces 3 valeurs
		 */
		unsigned int					hashValues(unsigned int i, unsigned int j, unsigned int k) const;

		/**
		 * Utiliser insertion sort pour ins�rer une valeur dans un tableau afin de toujours avoir le maximum
		 * en premi�re position.
		 * @param distArray Le tableau dans lequel on veut ajouter la valeur
		 * @param value La valeur � ajouter
		 */
		void							insererTableauDistances(vector<float>& distArray, float value) const;

		/**
		 * G�n�re la couleur pour un point de la texture worley
		 * @param input La position du cube pour lequel on veut �valuer la texture Worley
		 * @param seed La veleur du seed pour cette texture
		 * @param distArray Un vector de float contenant les distances relatives des points
		 * dans la texture Worley
		 * @return La couleur de ce point
		 */
		float							genererCouleurWorley(const aiVector3D& input, int seed,
															 vector<float>& distArray) const;

		/**
		 * G�n�re une texture 3D de type Worley Noise (un tableau de texture 2D)
		 * @param width La longueur de la texture
		 * @param height La hauteur de la texture
		 * @param depth La profondeur de la texture
		 * @return Un vecteur de vecteurs de vecteurs de floats repr�sentant la
		 * texture 3D
		 */
		vector<vector<vector<float> > >	textureWorleyNoise3D(int width, int height, int depth) const;

		/**
		 * G�n�re les triangles pour le cube courant
		 * @param cell Le cube courant
		 * @param vertices Une r�f�rence vers une liste de sommets. Cette liste
		 * contiendra les sommets g�n�r�s pour ce cube.
		 */
		void							polygonise(const GridCell_t& cell,
												   vector<aiVector3D>& vertices) const;

		/**
		 * G�n�re un sommet par interpolation lin�aire pour une arr�te
		 * @param p1 Le premier point de l'arr�te
		 * @param p2 Le second point de l'arr�te
		 * @param v1 La valeur du premier point
		 * @param v2 La valeur du second point
		 * @return Le sommet interpol�
		 */
		aiVector3D						sommetInterpoler(const aiVector3D& p1, const aiVector3D& p2,
														 float v1, float v2) const;

		/**
		 * Fonction de densit� pour la surface implicite
		 * @param point Le point pour lequel la fonction est �valu�e
		 * @param texel Le texel a utiliser dans la fonction de densit�
		 * @return La valeur de la fonction au point �valu�
		 */
		float							fonctionDensite(const aiVector3D& point, float texel) const;

		/**
		 * Retourne un nombre al�atoire entre deux extr�mes
		 * @param min La valeur minimale du nombre
		 * @param max La valeur maximale du nombre
		 * @return Le nomobre al�atoire dans [min, max]
		 */
		float							aleatoireDansInterval(float min, float max) const;
};

#endif