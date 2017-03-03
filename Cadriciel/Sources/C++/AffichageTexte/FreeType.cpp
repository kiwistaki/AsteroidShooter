//////////////////////////////////////////////////////////////////////////////
/// @file FreeType.cpp
/// @author FloppyDisketeers
/// @date 2014-04-1
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "FreeType.h"

/// Pour creer un objet FreeType, il faut toujours initialiser la librairie (fait dans le constructeur)
/// Creer la face de l'objet en loadant le .ttf (methode loadFontFace)
/// Setter la grosseur du caractere (setPixelSize)

////////////////////////////////////////////////////////////////////////
///
/// @fn FreeType::FreeType()
///
/// Constructeur par defaut
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
FreeType::FreeType()
{
	initLibrary();
}

////////////////////////////////////////////////////////////////////////
///
/// @fn FreeType::~FreeType();
///
/// Destructeur par defaut
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
FreeType::~FreeType()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FreeType::initLibrary()
///
/// Initialize la librairie
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FreeType::initLibrary()
{
	int error = FT_Init_FreeType( &library_ );
	
	if ( error ) 
	{ 
		cerr << "There is an error initializing the FreeType library" << endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FreeType::initTexture()
///
/// Initialize les textures
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FreeType::initTexture()
{
	glEnable(GL_BLEND);
	glDisable(GL_DEPTH_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &textName_);
	glBindTexture(GL_TEXTURE_2D, textName_);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FreeType::cleanTexture()
///
/// Reset les parametres pour les textures
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FreeType::cleanTexture()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FreeType::creerDisplayList()
///
/// Creer un display list des lettres
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FreeType::creerDisplayList()
{

}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FreeType::loadFontFace(const string& pathTrueTypeFont)
///
/// Charge le fichier .ttf pour que les caracteres puissent etre utilises
///
/// @param[in] pathTrueTypeFont	: chemin vers le fichier .ttf
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FreeType::loadFontFace(const string& pathTrueTypeFont)
{
	int error = FT_New_Face( library_, pathTrueTypeFont.c_str(), 0, &face_ );
	
	if ( error == FT_Err_Unknown_File_Format )
	{
		cerr << "The font file could be opened and read, but it appears that its font format is unsupported." << endl;
	}
	else if ( error )
	{
		cerr << "Another error code means that the font file could not be opened or read, or simply that it is broken." << endl;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FreeType::setResolution(float width, float height)
///
/// Set la resolution de l'ecran
///
/// @param[in] width	: Largeur de l'ecran
/// @param[in] height	: Hauteur de l'ecran
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FreeType::setResolution(float width, float height)
{
	screenResWidth_	 = width;
	screenResHeight_ = height; 
}
	
////////////////////////////////////////////////////////////////////////
///
/// @fn void FreeType::setCharSize(int charSize)
///
/// Met la grosseur des caracteres
///
/// @param[in] charSize	: taille des caracteres
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FreeType::setPixelSize(int pixelSize)
{
	int error = FT_Set_Pixel_Sizes(
				face_,			/* handle to face object */
				0,				/* pixel_width           */
				pixelSize );	/* pixel_height          */
	// 0 at pixel_width means same as pixel_height
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FreeType::printTextAtPosition(string text, int penX, int penY)
///
/// Imprime un texte a partir d'une position donnee
///
/// @param[in] text	: le texte a ecrire
/// @param[in] penX	: position de depart en X
/// @param[in] penY	: position de depart en y
/// @param[in] sx	: scaling factor en X
/// @param[in] sy	: scaling factor en y
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FreeType::printTextAtPosition(string text, int penX, int penY)
{
	FT_GlyphSlot  slot = face_->glyph;  /* a small shortcut */
	FT_UInt       glyph_index;
	int error; 

	for ( int i = 0; i < text.size(); i++ )
	{
		/* load glyph image into the slot (erase previous one) */
		error = FT_Load_Char( face_, text[i], FT_LOAD_RENDER );
		if ( error )
			continue;  /* ignore errors */

		/* now, draw to our target surface */
		appliquerBitmapTexture( &slot->bitmap,
								penX + slot->bitmap_left,
								penY - slot->bitmap_top );

		/* increment pen position */
		penX += slot->advance.x >> 6;
	}
}

////////////////////////////////////////////////////////////////////////
///
/// @fn void FreeType::appliquerBitmapTexture()
///
/// Creer un quad pour appliquer le bitmap sur l'objet OpenGL
///
/// @param[in] bitmap	: l'image a mapper
/// @param[in] x		: position de depart en X pour dessiner le coin gauche superieur  
/// @param[in] y		: position de depart en y pour dessiner le coin gauche superieur
///
/// @return Aucun.
///
////////////////////////////////////////////////////////////////////////
void FreeType::appliquerBitmapTexture(FT_Bitmap* bitmap, FT_Int x, FT_Int y)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);

	FreeType::initTexture();

	glTexImage2D(
      GL_TEXTURE_2D,
      0,
      GL_ALPHA,
      bitmap->width,
      bitmap->rows,
      0,
      GL_ALPHA,
      GL_UNSIGNED_BYTE,
      bitmap->buffer
    );

    float w = bitmap->width;
    float h = bitmap->rows ;
	
	glColor4f(1.0, 1.0, 0.0, 1.0);

	glBegin(GL_QUADS);
	// Coord texture Coord. géométrie
	glTexCoord2f( 0.0, 0.0 ); glVertex3f( x  , y+h,   0);
	glTexCoord2f( 0.0, 1.0 ); glVertex3f( x  , y, 0);
	glTexCoord2f( 1.0, 1.0 ); glVertex3f( x+w, y, 0); 
	glTexCoord2f( 1.0, 0.0 ); glVertex3f( x+w, y+h,   0); 
	glEnd();

	glPopAttrib();
}
