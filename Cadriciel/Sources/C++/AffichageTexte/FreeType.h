//////////////////////////////////////////////////////////////////////////////
/// @file FreeType.h
/// @author FloppyDisketeers
/// @date 2014-04-1
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __AFFICHAGETEXTE_FREETYPE_H__
#define __AFFICHAGETEXTE_FREETYPE_H__

#include <string>

#include "../../../Commun/Externe/FreeType/include/ft2build.h"
#include <ft2build.h>
#include FT_FREETYPE_H

#include "../../../Commun/Externe/GLEW/include/GL/glew.h"
#include <GL/GL.h>
#include <GL/glu.h>

// Source aide: http://nehe.gamedev.net/tutorial/freetype_fonts_in_opengl/24001/

using namespace std;

/// Classe utilisant la librairie FreeType en initialisant les donnees desirees
class FreeType
{
public:
					FreeType();
					FreeType(const string& pathTrueTypeFont);
				   ~FreeType();

	void			initLibrary();
	void			initTexture();
	void			cleanTexture();
	void			loadFontFace(const string& pathTrueTypeFont);
	void			creerDisplayList();
	void			setResolution(float width, float height);
	inline FT_Face&	getFace(){return face_;}
	void			setPixelSize(int pixelSize);
	void			printTextAtPosition(string text, int penX, int penY);

private:
	void			appliquerBitmapTexture(FT_Bitmap* bitmap, FT_Int x, FT_Int y);

	FT_Library		library_;	/* handle to library     */
	FT_Face			face_;		/* handle to face object */

	/* informations utiles pour setter certains parametres */
	int				pixelSize_;
	float			screenResWidth_;
	float			screenResHeight_;

	GLuint			textName_;	// GLuint pour binder la texture et l'utiliser.

	GLuint*			textures_;	// Holds The Texture Id's (text_base)
    GLuint			list_base_;	// Holds The First Display List Id
};

#endif // __AFFICHAGETEXTE_FREETYPE_H__