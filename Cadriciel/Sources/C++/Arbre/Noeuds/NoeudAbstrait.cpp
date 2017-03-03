////////////////////////////////////////////////
/// @file   NoeudAbstrait.cpp
/// @author DGI-2990
/// @date   2007-01-24
///
/// @addtogroup inf2990 INF2990
/// @{
////////////////////////////////////////////////

#include "NoeudAbstrait.h"
#include "Utilitaire.h"

unsigned int NoeudAbstrait::nomSelection_ = 1;

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::NoeudAbstrait(const std::string& type)
///
/// Ne fait qu'initialiser les variables membres de la classe.
///
/// @param[in] type               : Le type du noeud.
///
/// @return Aucune (constructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::NoeudAbstrait(
   const std::string& type //= std::string( "" )
   ) :
   type_(type) ,
   modePolygones_(GL_FILL) ,
   positionRelative_(0) ,
   affiche_(true) ,
   selectionne_(false) ,
   selectionnable_(true) ,
   enregistrable_(true) ,
   parent_(0),
   angleRotation_(0.0f),
   taille_(1.0f)
{
}

NoeudAbstrait::NoeudAbstrait(const NoeudAbstrait& src) :
		type_(src.type_),
		modePolygones_(src.modePolygones_),
		positionRelative_(src.positionRelative_),
		affiche_(src.affiche_),
		selectionne_(false),
		selectionnable_(src.selectionnable_),
		enregistrable_(src.enregistrable_),
		parent_(src.parent_),
		angleRotation_(src.angleRotation_),
		axeRotation_(src.axeRotation_),
		taille_(src.taille_),
		boiteEnglobanteOrientee_(src.boiteEnglobanteOrientee_)
{
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait::~NoeudAbstrait()
///
/// Destructeur vide declare virtuel pour les classes derivees.  La
/// liberation des afficheurs n'est pas la responsabilite de cette
/// classe.
///
/// @return Aucune (destructeur).
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait::~NoeudAbstrait()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::calculerProfondeur() const
///
/// Cette fonction calcule la profondeur de l'arbre incluant le noeud
/// courant ainsi que tous ses enfants.
///
/// Cette fonction retourne toujours 1 pour un noeud sans enfant.
///
/// @return La profondeur de l'arbre sous ce noeud, donc toujours 1.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::calculerProfondeur() const
{
   return 1;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::vider()
///
/// Cette fonction vide le noeud de tous ses enfants.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par defaut de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::vider()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
///
/// Cette fonction efface le noeud s'il fait partie des enfants de
/// ce noeud.
///
/// Cette fonction ne fait rien pour un noeud sans enfant, elle ne fait
/// donc rien dans cette implantation par defaut de la classe de base.
///
/// @param[in] noeud : Le noeud a effacer.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacer( const NoeudAbstrait* noeud )
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
///
/// Cette fonction cherche un noeud d'un type donne parmi le noeud
/// lui-meme et ses enfants.
///
/// Elle retourne donc le noeud lui-meme si son type est celui passe en
/// parametre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud a trouver.
///
/// @return Le pointeur vers le noeud s'il est trouve.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud ) const
{
   if (typeNoeud == type_)
      return this;
   else
      return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
///
/// Cette fonction cherche un noeud d'un type donne parmi le noeud
/// lui-meme et ses enfants.
///
/// Elle retourne donc le noeud lui-meme si son type est celui passe en
/// parametre, ou 0 sinon.
///
/// @param[in] typeNoeud : Le type du noeud a trouver.
///
/// @return Le pointeur vers le noeud s'il est trouve.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher( const std::string& typeNoeud )
{
   if (typeNoeud == type_)
      return this;
   else
      return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
///
/// Cette fonction cherche le i-eme enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derniere ne possede pas d'enfant.
///
/// @param[in] indice : L'indice du noeud a trouver.
///
/// @return Le pointeur vers le noeud s'il est trouve.
///
////////////////////////////////////////////////////////////////////////
const NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice ) const
{
   return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
///
/// Cette fonction cherche le i-eme enfant d'un noeud.
///
/// Elle retourne toujours 0 pour la classe de base, car cette
/// derniere ne possede pas d'enfant.
///
/// @param[in] indice : L'indice du noeud a trouver.
///
/// @return Le pointeur vers le noeud s'il est trouve.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::chercher( unsigned int indice )
{
   return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
///
/// Cette fonction ajoute un enfant a ce noeud.
///
/// Elle retourne toujours faux et ne fait rien, car ce type de noeud
/// abstrait ne peut pas avoir d'enfant.
///
/// @param[in] enfant: Le noeud a ajouter.
///
/// @return Vrai si l'ajout a bien ete effectue, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::ajouter(NoeudAbstrait* enfant)
{
   return false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn unsigned int NoeudAbstrait::obtenirNombreEnfants() const
///
/// Cette fonction retourne le nombre d'enfants de ce noeud.
///
/// Elle retourne toujours 0, car ce type de noeud abstrait ne peut pas
/// avoir d'enfant.
///
/// @return Vrai si l'ajout a bien ete effectue, faux autrement.
///
////////////////////////////////////////////////////////////////////////
unsigned int NoeudAbstrait::obtenirNombreEnfants() const
{
   return 0;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::inverserSelection()
///
/// Cette fonction inverse l'etat de selection de ce noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::inverserSelection()
{
   selectionne_ = !selectionne_;
   modele_.setSelectionne(selectionne_);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::effacerSelection()
///
/// Cette fonction efface les noeuds qui sont selectionnes parmi les
/// enfants de ce noeud.
///
/// Elle ne fait rien, car ce type de noeud abstrait ne peut pas avoir
/// d'enfant.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::effacerSelection()
{
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::selectionnerTout()
///
/// Cette fonction selectionne le noeud et ses enfants.
///
/// Elle ne fait que selectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::selectionnerTout()
{
   assignerSelection(true);
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::deselectionnerTout()
///
/// Cette fonction deselectionne le noeud et ses enfants.
///
/// Elle ne fait que deselectionner le noeud pour cette classe, car ce
/// type de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::deselectionnerTout()
{
   selectionne_ = false;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::selectionExiste() const
///
/// Cette fonction verifie si le noeud ou un de ses enfants est
/// selectionne.
///
/// Elle ne fait que regarder si le noeud est selectionne, car ce type
/// de noeud abstrait ne peut pas avoir d'enfants.
///
/// @return Vrai s'il existe un noeud selectionne, faux autrement.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::selectionExiste() const
{
   return selectionne_;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::changerModePolygones( bool estForce )
///
/// Cette fonction change le mode de rendu des polygones du noeud s'il
/// est selectionne ou si on le force.
///
/// @param[in] estForce: Vrai si on veut changer le mode meme si le
///                      noeud n'est pas selectionne.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::changerModePolygones( bool estForce )
{
   if ( ( estForce ) || ( estSelectionne() ) ) {
      if ( modePolygones_ == GL_FILL )
         modePolygones_ =  GL_LINE;
      else if ( modePolygones_ == GL_LINE )
         modePolygones_ = GL_POINT;
      else
         modePolygones_ = GL_FILL;
   }
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
///
/// Cette fonction assigne le mode de rendu des polygones du noeud.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerModePolygones( GLenum modePolygones )
{
   // Le mode par defaut si on passe une mauvaise valeur est GL_FILL
   if ( (modePolygones != GL_FILL) &&
        (modePolygones != GL_LINE) &&
        (modePolygones != GL_POINT) ) {
      modePolygones = GL_FILL;
   }

   modePolygones_ = modePolygones;
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficher() const
///
/// Cette fonction affiche le noeud comme tel.
///
/// Elle consiste en une template method (dans le sens du patron de
/// conception, et non les template C++) qui effectue ce qui est
/// generalement a faire pour l'affichage, c'est-a-dire:
/// - Mise en pile de la matrice de transformation
/// - Translation du noeud pour qu'il soit a sa position relative
/// - Utilisation du mode d'affichage des polygones
/// - ...
/// - Restauration de l'etat.
///
/// L'affichage comme tel est confie a la fonction afficherConcret(),
/// appelee par la fonction afficher().
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficher(bool selection3D) const
{
	if (affiche_) {
		glPushMatrix();
		glPushAttrib(GL_CURRENT_BIT | GL_POLYGON_BIT);

		// La translation de la position relative
		glTranslated(
			positionRelative_[0], positionRelative_[1], positionRelative_[2]
		);
      
		// Assignation du mode d'affichage des polygones
		glPolygonMode( GL_FRONT_AND_BACK, modePolygones_ );
      
		if (selection3D) {
			// Petit hack pour pouvoir accéder au noeud directement dès qu'on le trouve
			glLoadName((unsigned int)this);
			//glLoadName(nomSelection_);
			nomSelection_ += 1;
		}

		// Affichage concret
		afficherConcret();
      
		// Restauration
		glPopAttrib();
		glPopMatrix();
	}
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::afficherConcret() const
///
/// Cette fonction effectue le veritable rendu de l'objet.  Elle est
/// appelee par la template method (dans le sens du patron de conception,
/// et non des template C++) afficher() de la classe de base.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::afficherConcret() const
{
	glPushMatrix();
		if (selectionne_) {		
			// On desactive les textures pour changer la couleur
			glDisable(GL_TEXTURE_2D);

			// XOR avec la couleur en dessous (pour que l'on voit toujours le rectangle)
			glLogicOp(GL_XOR);
			glEnable(GL_COLOR_LOGIC_OP);

			glColor3f(1.0f, 1.0f, 1.0f);
			boiteEnglobanteOrientee_.afficher();

			glDisable(GL_COLOR_LOGIC_OP);

			glEnable(GL_TEXTURE_2D); // Reactivation des textures

			glColor4f(0.0f, 0.85f, 0.0f, 0.5f);
		}

		/// Transformation par rapport a l'objet lui-meme
		glTranslatef(position_.x, position_.y, position_.z);
		glRotatef(angleRotation_, axeRotation_.x, axeRotation_.y, axeRotation_.z);
		glScalef(taille_.x, taille_.y, taille_.z);

		modele_.dessiner();
	glPopMatrix();
}


////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::animer( float dt )
///
/// Cette fonction effectue l'animation du noeud pour un certain
/// intervalle de temps.
///
/// Elle ne fait rien pour cette classe et vise a etre surcharger par
/// les classes derivees.
///
/// @param[in] dt : Intervalle de temps sur lequel faire l'animation.
///
/// @return Aucune.
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::animer( float dt )
{
	boiteEnglobanteOrientee_.update(position_, angleRotation_, taille_);
}

////////////////////////////////////////////////
/// @fn void NoeudAbstrait::objetTemporaire( float r, float g, float b )
///
///		Cette fonction affichage les objets temporaires pour les noeuds.
///
///		Elle n'a pas besoin d'etre reimplementee.
///
/// @param[in] rayon :	rayon du cercle
///			   r :		float de la couleur rouge
///			   g :		float de la couleur verte
///			   b :		float de la couleur bleue
///
/// @return Aucune.
////////////////////////////////////////////////
void NoeudAbstrait::objetTemporaire( float longueur, float r, float g, float b ) const
{
	// CODE OPENGL POUR FAIRE LES FORMES TEMPORAIRE
	// affiche un cube de longueur en parametre
	glColor3f(  r,  g,  b );

	// FRONT
  glBegin(GL_POLYGON);
  glVertex3f(  longueur, -longueur, -longueur ); 
  glVertex3f(  longueur,  longueur, -longueur ); 
  glVertex3f( -longueur,  longueur, -longueur ); 
  glVertex3f( -longueur, -longueur, -longueur ); 
  glEnd();
 
  // BACK
  glBegin(GL_POLYGON);
  glVertex3f(  longueur, -longueur, longueur );
  glVertex3f(  longueur,  longueur, longueur );
  glVertex3f( -longueur,  longueur, longueur );
  glVertex3f( -longueur, -longueur, longueur );
  glEnd();
 
  // RIGHT
  glBegin(GL_POLYGON);
  glVertex3f( longueur, -longueur, -longueur );
  glVertex3f( longueur,  longueur, -longueur );
  glVertex3f( longueur,  longueur,  longueur );
  glVertex3f( longueur, -longueur,  longueur );
  glEnd();
 
  // LEFT
  glBegin(GL_POLYGON);
  glVertex3f( -longueur, -longueur,  longueur );
  glVertex3f( -longueur,  longueur,  longueur );
  glVertex3f( -longueur,  longueur, -longueur );
  glVertex3f( -longueur, -longueur, -longueur );
  glEnd();
 
  // TOP
  glBegin(GL_POLYGON);
  glVertex3f(  longueur,  longueur,  longueur );
  glVertex3f(  longueur,  longueur, -longueur );
  glVertex3f( -longueur,  longueur, -longueur );
  glVertex3f( -longueur,  longueur,  longueur );
  glEnd();
 
  // BOTTOM
  glBegin(GL_POLYGON);
  glColor3f(   1.0,  0.0,  0.0 );
  glVertex3f(  longueur, -longueur, -longueur );
  glVertex3f(  longueur, -longueur,  longueur );
  glVertex3f( -longueur, -longueur,  longueur );
  glVertex3f( -longueur, -longueur, -longueur );
  glEnd();
	
}

////////////////////////////////////////////////////////////////////////
///
/// @fn NoeudAbstrait* NoeudAbstrait::obtenirParent()
///
/// Cette fonction retourne le pointeur vers le parent de ce noeud.
///
/// @return Le pointeur vers le parent.
///
////////////////////////////////////////////////////////////////////////
NoeudAbstrait* NoeudAbstrait::obtenirParent()
{
   return parent_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
///
/// Cette fonction retourne le pointeur constant vers le parent de ce noeud.
///
/// @return Le pointeur constant vers le parent.
///
////////////////////////////////////////////////////////////////////////
inline const NoeudAbstrait* NoeudAbstrait::obtenirParent() const
{
   return parent_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerParent( NoeudAbstrait* parent )
///
/// Cette fonction assigne le parent du noeud afin qu'il soit possible
/// de remonter dans l'arbre.
///
/// @param[in] parent : Le parent du noeud.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerParent(
   NoeudAbstrait* parent
   )
{
   parent_       = parent;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const Vecteur3& NoeudAbstrait::obtenirPositionRelative() const
///
/// Cette fonction retourne la position relative du noeud par rapport
/// a son parent.
///
/// @return La position relative.
///
////////////////////////////////////////////////////////////////////////
const Vecteur3& NoeudAbstrait::obtenirPositionRelative() const
{
   return positionRelative_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerPositionRelative( const Vecteur3& positionRelative )
///
/// Cette fonction permet d'assigner la position relative du noeud par
/// rapport a son parent.
///
/// @param positionRelative : La position relative.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerPositionRelative(
   const Vecteur3& positionRelative
   )
{
   positionRelative_ = positionRelative;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn const std::string& NoeudAbstrait::obtenirType() const
///
/// Cette fonction retourne une chaîne representante le type du noeud.
///
/// @return Le type du noeud.
///
////////////////////////////////////////////////////////////////////////
const std::string& NoeudAbstrait::obtenirType() const
{
   return type_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerAffiche( bool affiche )
///
/// Cette fonction permet d'assigner si le noeud se fait afficher ou
/// non lorsque l'arbre de rendu se fait afficher.  Elle permet donc
/// de temporairement suspendre ou activer l'affichage d'un noeud.
///
/// @param affiche : L'etat affiche ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerAffiche( bool affiche )
{
   affiche_ = affiche;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::estAffiche() const
///
/// Cette fonction retourne l'etat que le noeud se fait afficher ou non.
///
/// @return L'etat affiche ou non.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::estAffiche() const
{
   return affiche_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerSelection( bool selectionne )
///
/// Cette fonction permet d'assigner l'etat d'etre selectionne ou non du noeud.
///
/// @param selectionne : L'etat selectionne ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerSelection( bool selectionne )
{
   // Un objet non selectionnable n'est jamais selectionne.
   selectionne_ = (selectionne && selectionnable_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::estSelectionne() const
///
/// Cette fonction retourne l'etat d'etre selectionne ou non du noeud.
///
/// @return L'etat selectionne ou non.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::estSelectionne() const
{
   // Un objet non selectionnable n'est jamais selectionne.
   return (selectionne_ && selectionnable_);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
///
/// Cette fonction permet d'assigner l'etat d'etre selectionnable ou non du noeud.
///
/// @param selectionnable : L'etat selectionnable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerEstSelectionnable( bool selectionnable )
{
   selectionnable_ = selectionnable;
   selectionne_    = selectionne_ && selectionnable_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::estSelectionnable() const
///
/// Cette fonction retourne l'etat d'etre selectionnable ou non du noeud.
///
/// @return L'etat selectionnable ou non.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::estSelectionnable() const
{
   return selectionnable_;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
///
/// Cette fonction permet d'assigner l'etat d'etre entregistrable ou non du noeud.
///
/// @param enregistrable : L'etat enregistrable ou non.
///
/// @return Aucune
///
////////////////////////////////////////////////////////////////////////
void NoeudAbstrait::assignerEstEnregistrable( bool enregistrable )
{
   enregistrable_ = enregistrable;
}

////////////////////////////////////////////////////////////////////////
///
/// @fn bool NoeudAbstrait::estEnregistrable() const
///
/// Cette fonction retourne l'etat d'etre enregistrable en XML ou non du
/// noeud.
///
/// @return L'etat enregistrable ou non.
///
////////////////////////////////////////////////////////////////////////
bool NoeudAbstrait::estEnregistrable() const
{
   return enregistrable_;
}

void NoeudAbstrait::setTransformation(const aiVector3D& translation,
											 float angleRotation,
											 const aiVector3D& axeRotation,
											 const aiVector3D& taille)
{
	position_ = translation;
	angleRotation_ = angleRotation;
	axeRotation_ = axeRotation;
	taille_ = taille;
}

////////////////////////////////////////////////
/// @}
////////////////////////////////////////////////