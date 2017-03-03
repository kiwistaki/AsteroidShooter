//////////////////////////////////////////////////////////////////////////////
/// @file ModeTest.h
/// @author FloppyDisketeers
/// @date 2014-01-21
/// @version 1.0 
///
/// @addtogroup inf2990 INF2990
/// @{
//////////////////////////////////////////////////////////////////////////////

#ifndef __APPLICATION_MODETEST_H__
#define __APPLICATION_MODETEST_H__

#include "ModeJeu.h"

/**
 * @class ModeTest
 * @brief Cette classe implemente le mode test
 * @author FloppyDisketeers
 */
class ModeTest : public ModeJeu {
public:
	/**
	 *  Constructeur par paramètre
	 *  @param: carte
	 *  @param: vue
	 */
	ModeTest(Carte& carte, vue::Vue* vue);

	/**
	 *  Destructeur
	 */
	~ModeTest();

	/// Update recoit les informations et laisse le jeu analyser les donnees
	virtual void		update(float deltaT);
private:
};

#endif // __APPLICATION_MODETEST_H__