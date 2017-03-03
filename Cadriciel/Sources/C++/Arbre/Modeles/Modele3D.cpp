////////////////////////////////////////////////////////////////////////////////////
/// @file Modele3D.cpp
/// @author Julien Gascon-Samson
/// @date 2011-07-21
/// @version 1.0
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////////////////////////////////////////

/*
	Mention : certaines portions du code source servant d'implementation a cette classe sont inspirees
	de l'exemple SimpleTexturedOpenGL fourni avec le cadriciel de developpement de la librairie AssImp.
	(Licence Apache/BSD)
*/

#include "Modele3D.h"
#include "Utilitaire.h"
#include "AideGL.h"
#include "GestionnaireRessources.h"

////////////////////////////////////////////////////////////////////////
///
/// @fn Modele3D::Modele3D()
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
Modele3D::Modele3D():
	facteurAgrandissement_(1.0),
	selectionne_(false)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn Modele3D::~Modele3D()
///
/// Destructeur qui desalloue les ressources allouees par 'assimp' ainsi
/// que les textures OpenGL.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
Modele3D::~Modele3D()
{
}

void Modele3D::setDisplayList(GLuint liste) {
	liste_ = liste;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Modele3D::charger( const string& nomModele, const string& nomFichier )
///
/// Cette fonction charge un modele 3D a partir d'un fichier supporte
/// par la librairie 'assimp'. Les textures OpenGL afferentes sont
/// egalement chargees.
///
/// @param[in] nomFichier : nom du fichier modele (normalement .mtl)
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Modele3D::charger(const string& nomFichier)
{
	scene_ = GestionnaireRessources::getInstance()->chargerModele3D(nomFichier, mapTextures_);

	liste_ = GestionnaireRessources::getInstance()->creerCallList(scene_);

	GestionnaireRessources::getInstance()->calculerPointsExtremes(nomFichier, pointsExtremesMinX_,
																  pointsExtremesMinY_, pointsExtremesMinZ_,
																  pointsExtremesMaxX_, pointsExtremesMaxY_,
																  pointsExtremesMaxZ_);

	rayonSphereEnglobante_ = GestionnaireRessources::getInstance()->calculerRayonSphereEnglobante(nomFichier);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void Modele3D::dessiner()
///
/// Cette fonction effectue le rendu recursif OpenGL du modele 'assimp'
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void Modele3D::dessiner() const
{
	glCallList(liste_);
}

double Modele3D::calculerSphereEnglobante() const
{
	// Le rayon de la sphere englobante est le point le plus eloigne parmi les 6 points extremes possibles...
	double max = 0;
	double norme = 0;
	norme = pointsExtremesMinX_.norme2(); if (norme > max) max = norme;
	norme = pointsExtremesMinY_.norme2(); if (norme > max) max = norme;
	norme = pointsExtremesMinZ_.norme2(); if (norme > max) max = norme;

	norme = pointsExtremesMaxX_.norme2(); if (norme > max) max = norme;
	norme = pointsExtremesMaxY_.norme2(); if (norme > max) max = norme;
	norme = pointsExtremesMaxZ_.norme2(); if (norme > max) max = norme;

	return sqrt(max);
}

void Modele3D::calculerCylindreEnglobant(double& rayon, double& bas, double& haut) const
{
	// Obtenir le point extreme le plus eloigne parmi les axes xy. L'axe z servira
	// a etablir le bas et le haut du cylindre.

	double max = 0;
	double norme = 0;
	norme = pointsExtremesMinX_[0] * pointsExtremesMinX_[0] + pointsExtremesMinX_[1] * pointsExtremesMinX_[1]; if (norme>max) max=norme;
	norme = pointsExtremesMinY_[0] * pointsExtremesMinY_[0] + pointsExtremesMinY_[1] * pointsExtremesMinY_[1]; if (norme>max) max=norme;
	norme = pointsExtremesMinZ_[0] * pointsExtremesMinZ_[0] + pointsExtremesMinZ_[1] * pointsExtremesMinZ_[1]; if (norme>max) max=norme;

	norme = pointsExtremesMaxX_[0] * pointsExtremesMaxX_[0] + pointsExtremesMaxX_[1] * pointsExtremesMaxX_[1]; if (norme>max) max=norme;
	norme = pointsExtremesMaxY_[0] * pointsExtremesMaxY_[0] + pointsExtremesMaxY_[1] * pointsExtremesMaxY_[1]; if (norme>max) max=norme;
	norme = pointsExtremesMaxZ_[0] * pointsExtremesMaxZ_[0] + pointsExtremesMaxZ_[1] * pointsExtremesMaxZ_[1]; if (norme>max) max=norme;

	// Nous avons trouve le rayon...
	rayon = sqrt(max);

	// Le bas et le dessus sont les extremums en z.
	bas = 999999; haut = 0;
	if (pointsExtremesMinX_[2] < bas) bas = pointsExtremesMinX_[2]; if (pointsExtremesMinX_[2] > haut) haut = pointsExtremesMinX_[2];
	if (pointsExtremesMinY_[2] < bas) bas = pointsExtremesMinY_[2]; if (pointsExtremesMinY_[2] > haut) haut = pointsExtremesMinY_[2];
	if (pointsExtremesMinZ_[2] < bas) bas = pointsExtremesMinZ_[2]; if (pointsExtremesMinZ_[2] > haut) haut = pointsExtremesMinZ_[2];

	if (pointsExtremesMaxX_[2] < bas) bas = pointsExtremesMaxX_[2]; if (pointsExtremesMaxX_[2] > haut) haut = pointsExtremesMaxX_[2];
	if (pointsExtremesMaxY_[2] < bas) bas = pointsExtremesMaxY_[2]; if (pointsExtremesMaxY_[2] > haut) haut = pointsExtremesMaxY_[2];
	if (pointsExtremesMaxZ_[2] < bas) bas = pointsExtremesMaxZ_[2]; if (pointsExtremesMaxZ_[2] > haut) haut = pointsExtremesMaxZ_[2];
}

void Modele3D::calculerBoiteEnglobante(Vecteur3& coinMin, Vecteur3& coinMax) const
{
	// Le coin min est simplement les coordonnees minimales et le coin max est
	// simplement les coordonnees maximales.
	coinMin[0] = pointsExtremesMinX_[0];
	coinMin[1] = pointsExtremesMinY_[1];
	coinMin[2] = pointsExtremesMinZ_[2];

	coinMax[0] = pointsExtremesMaxX_[0];
	coinMax[1] = pointsExtremesMaxY_[1];
	coinMax[2] = pointsExtremesMaxZ_[2];
}

///////////////////////////////////////////////////////////////////////////////
/// @}
///////////////////////////////////////////////////////////////////////////////
