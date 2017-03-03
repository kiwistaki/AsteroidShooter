#include "GestionnaireRessources.h"

#include "Utilitaire.h"
#include "AideGL.h"

GestionnaireRessources GestionnaireRessources::instance_;

GestionnaireRessources::GestionnaireRessources() {
	postProcessSteps_ = aiProcess_GenNormals | aiProcess_JoinIdenticalVertices |
						aiProcess_Triangulate | aiProcess_GenUVCoords |
						aiProcess_SortByPType;
}

GestionnaireRessources::~GestionnaireRessources() {
	for (size_t i = 0; i < importer_.size(); i++) {
		importer_[i]->FreeScene();
		delete importer_[i];
	}
}

GestionnaireRessources* GestionnaireRessources::getInstance() {
	return &instance_;
}

const aiScene* GestionnaireRessources::chargerModele3D(const string& nomFichier,
													   map<string, GLuint >& textures)
{
	const aiScene* scene;
	// On charge le modele si on ne l'a pas deja charge
	map<string, const aiScene*>::iterator it = modelesCharges_.find(nomFichier);
	if (it == modelesCharges_.end()) {
		Assimp::Importer* importer = new Assimp::Importer();
		scene = importer->ReadFile(nomFichier, postProcessSteps_);
		importer_.push_back(importer);

		if (scene == NULL) {
			utilitaire::afficherErreur("Impossible de charger l'objet 3d!");
			return NULL;
		}

		modelesCharges_[nomFichier] = scene;
	}
	// Sinon on utilise la version cached
	else {
		scene = modelesCharges_[nomFichier];
	}

	// Chargement des textures
	/*if (scene->HasTextures()) {
		utilitaire::afficherErreur("Les textures integrees ne sont pas prises en charge pour le moment.");
		return false;
	}*/

	for (size_t i = 0; i < scene->mNumMaterials; i++) {
		aiMaterial* material = scene->mMaterials[i];

		int id = 0;
		aiString textureName = "";
		while (true) {
			aiReturn retour = material->GetTexture(aiTextureType_DIFFUSE, id, &textureName);

			if (retour != AI_SUCCESS) {
				break;
			}

			GLuint textureId = 0;
			if (!chargerTexture(textureName.data, textureId)) {
				textures.clear();
				return scene;
			}

			textures[textureName.data] = textureId;

			id += 1;
		}
	}

	return scene;
}

GLuint GestionnaireRessources::creerCallList(const aiScene* scene) {
	map<const aiScene*, GLuint>::iterator it = callListCrees_.find(scene);
	GLuint liste;
	if (it == callListCrees_.end()) {
		liste = glGenLists(1);

		glNewList(liste, GL_COMPILE);
			dessinerModele(scene, scene->mRootNode);
		glEndList();

		callListCrees_[scene] = liste;
	} else {
		liste = it->second;
	}

	return liste;
}

bool GestionnaireRessources::chargerTexture(const string& nomFichier,
											GLuint& texture)
{
	// On charge la texture si on ne l'a pas deja charge
	map<string, GLuint>::iterator it = texturesCharges_.find(nomFichier);
	if (it == texturesCharges_.end()) {
		glGenTextures(1, &texture);
		if (aidegl::glLoadTexture(string("media/") + nomFichier, texture, false)) {
			texturesCharges_[nomFichier] = texture;
			return true;
		}

		return false;
	}

	texture = it->second;
	return true;
}

bool GestionnaireRessources::calculerPointsExtremes(const string& nomFichier,
													Vecteur3f& xMin,
													Vecteur3f& yMin,
													Vecteur3f& zMin,
													Vecteur3f& xMax,
													Vecteur3f& yMax,
													Vecteur3f& zMax)
{
	map<string, const aiScene*>::iterator it = modelesCharges_.find(nomFichier);
	if (it == modelesCharges_.end()) {
		return false;
	}

	const aiScene* scene = it->second;

	map<string, Vecteur3f>::iterator p_it = pointsExtremesMinX_.find(nomFichier);
	if (p_it == pointsExtremesMinX_.end()) {
		calculerPointsExtremes(scene, scene->mRootNode, xMin, yMin, zMin, xMax,
							   yMax, zMax);

		pointsExtremesMinX_[nomFichier] = xMin;
		pointsExtremesMaxX_[nomFichier] = xMax;
		pointsExtremesMinY_[nomFichier] = yMin;
		pointsExtremesMaxY_[nomFichier] = yMax;
		pointsExtremesMinZ_[nomFichier] = zMin;
		pointsExtremesMaxZ_[nomFichier] = zMax;
	} else {
		xMin = pointsExtremesMinX_[nomFichier];
		xMax = pointsExtremesMaxX_[nomFichier];
		yMin = pointsExtremesMinY_[nomFichier];
		yMax = pointsExtremesMaxY_[nomFichier];
		zMin = pointsExtremesMinZ_[nomFichier];
		zMax = pointsExtremesMaxZ_[nomFichier];
	}

	return true;
}

float GestionnaireRessources::calculerRayonSphereEnglobante(const string& nomFichier) {
	map<string, const aiScene*>::iterator it = modelesCharges_.find(nomFichier);
	if (it == modelesCharges_.end()) {
		return false;
	}

	float rayon = 0.0f;

	map<string, float>::iterator r_it = rayonsSpheresEnglobantes_.find(nomFichier);
	if (r_it == rayonsSpheresEnglobantes_.end()) {
		map<string, Vecteur3f>::iterator p_it = pointsExtremesMinX_.find(nomFichier);
		if (p_it == pointsExtremesMinX_.end()) {
			return false;
		}

		// Le rayon de la sphere englobante est le point le plus eloigne parmi les 6 points extremes possibles...
		double max = 0;
		double norme = 0;
		norme = pointsExtremesMinX_[nomFichier].norme2(); if (norme > max) max = norme;
		norme = pointsExtremesMinY_[nomFichier].norme2(); if (norme > max) max = norme;
		norme = pointsExtremesMinZ_[nomFichier].norme2(); if (norme > max) max = norme;

		norme = pointsExtremesMaxX_[nomFichier].norme2(); if (norme > max) max = norme;
		norme = pointsExtremesMaxY_[nomFichier].norme2(); if (norme > max) max = norme;
		norme = pointsExtremesMaxZ_[nomFichier].norme2(); if (norme > max) max = norme;

		rayonsSpheresEnglobantes_[nomFichier] = rayon = (float)sqrt(max);
	} else {
		rayon = r_it->second;
	}

	return rayon;
}

void GestionnaireRessources::calculerPointsExtremes(const aiScene* scene,
													const aiNode* noeud,
													Vecteur3f& xMin,
													Vecteur3f& yMin,
													Vecteur3f& zMin,
													Vecteur3f& xMax,
													Vecteur3f& yMax,
													Vecteur3f& zMax) const
{
	// Pour chacun des 'meshes'...
	for (unsigned int i=0; i<noeud->mNumMeshes; i++) {
		const aiMesh* mesh = scene->mMeshes[noeud->mMeshes[i]];

		// Pour chaque face...
		for (unsigned int j=0; j<mesh->mNumFaces; j++) {
			const aiFace* face = &mesh->mFaces[j];

			// Pour chaque vertex...
			for (unsigned int k=0; k<face->mNumIndices; k++) {
				int indexVertex = face->mIndices[k];	// get group index for current index

				// On verifie les coordonnees...
				float x=mesh->mVertices[indexVertex].x;
				float y=mesh->mVertices[indexVertex].y;
				float z=mesh->mVertices[indexVertex].z;

				if (x<xMin[0]) { xMin[0]=x; xMin[1]=y; xMin[2]=z; } else if (x>xMax[0]) { xMax[0]=x; xMax[1]=y; xMax[2]=z; }
				if (y<yMin[1]) { yMin[0]=x; yMin[1]=y; yMin[2]=z; } else if (y>yMax[1]) { yMax[0]=x; yMax[1]=y; yMax[2]=z; }
				if (z<zMin[2]) { zMin[0]=x; zMin[1]=y; zMin[2]=z; } else if (z>zMax[2]) { zMax[0]=x; zMax[1]=y; zMax[2]=z; }
			}
		}
	}

	// Calcul recursif des points extremes
	for (unsigned int i=0; i<noeud->mNumChildren; i++) {
		calculerPointsExtremes(scene, noeud->mChildren[i], xMin, yMin, zMin,
							   xMax, yMax, zMax);
	}
}

void GestionnaireRessources::dessinerModele(const aiScene* scene, const aiNode* noeud) const {
	for (unsigned int i=0; i<noeud->mNumMeshes; i++) {
		const aiMesh* mesh = scene->mMeshes[noeud->mMeshes[i]];

		// Appliquer le materiau pour le mesh courant
		appliquerMateriau(scene->mMaterials[mesh->mMaterialIndex]);

		// Effectuer le rendu de chaque face
		for (unsigned int j=0; j<mesh->mNumFaces; j++) {
			const aiFace* face = &mesh->mFaces[j];

			// Effectuer le rendu de la face. Vu qu'on a utilise Triangulate
			// dans le chargement du modele, on n'a qu'a utiliser GL_TRIANGLES
			glBegin(GL_TRIANGLES);

			for (unsigned int k=0; k<face->mNumIndices; k++) {
				int indexVertex = face->mIndices[k];	// get group index for current index
				
				// Normales pour applications des textures
				if(mesh->mNormals != NULL)
				{
					if(mesh->HasTextureCoords(0))
					{
						glTexCoord2f(mesh->mTextureCoords[0][indexVertex].x, 1 - mesh->mTextureCoords[0][indexVertex].y);
					}
				}

				glNormal3fv(&mesh->mNormals[indexVertex].x);
				glVertex3fv(&mesh->mVertices[indexVertex].x);
			}

			glEnd();
		}

		glMatrixMode(GL_TEXTURE);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}

	// Rendu recursif des enfants
	for (unsigned int i=0; i<noeud->mNumChildren; i++) {
		dessinerModele(scene, noeud->mChildren[i]);
	}
}

void GestionnaireRessources::appliquerMateriau(const aiMaterial* materiau) const {
	// Obtenir la texture du materiau
	int indexTexture = 0;
	aiString nomFichier = "";
	
	glMatrixMode(GL_TEXTURE);
	glPushMatrix();

	if (materiau->GetTexture(aiTextureType_DIFFUSE, indexTexture, &nomFichier) == AI_SUCCESS) {
		// Activer le texturage OpenGL et lier la texture appropriee
		glEnable ( GL_TEXTURE_2D);
		GLuint idTexture = texturesCharges_.find(nomFichier.data)->second;
		glScalef(1.0,-1.0,1.0);
		glBindTexture(GL_TEXTURE_2D, idTexture);
	}
	else {
		// Desactiver le texturage OpenGL puisque cet objet n'a aucune texture
		glDisable ( GL_TEXTURE_2D);
	}

	glMatrixMode(GL_MODELVIEW);

	// Autres parametres a appliquer... (couleurs)
	float c[4];
	GLenum fill_mode;
	//int ret1, ret2;
	struct aiColor4D diffuse;
	struct aiColor4D specular;
	struct aiColor4D ambient;
	struct aiColor4D emission;
	//float shininess, strength;
	int two_sided;
	int wireframe;
	unsigned int max;	// change pour: unsigned

	c[0] = 0.8f;
	c[1] = 0.8f;
	c[2] = 0.8f;
	c[3] = 1.0f;
	
	max = 1;
	if(AI_SUCCESS == aiGetMaterialIntegerArray(materiau, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
		fill_mode = wireframe ? GL_LINE : GL_FILL;
	else
		fill_mode = GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, fill_mode);

	max = 1;
	if((AI_SUCCESS == aiGetMaterialIntegerArray(materiau, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
		glEnable(GL_CULL_FACE);
	else
		glDisable(GL_CULL_FACE);
}