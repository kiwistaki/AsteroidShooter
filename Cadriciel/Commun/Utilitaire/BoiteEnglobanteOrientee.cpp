#include "BoiteEnglobanteOrientee.h"

#include "../Externe/assimp/include/aiMatrix4x4.h"
#include "Utilitaire.h"
#include "AideCollision.h"

#include <windows.h>
#include <GL/gl.h>

namespace math {

BoiteEnglobanteOrientee::BoiteEnglobanteOrientee() : right_(1.0f, 0.0f, 0.0f), up_(0.0f, 1.0f, 0.0f) {
	moitieLongueurTransforme_ = moitieLongueur_ = 0.75f;
	moitieHauteurTransforme_ = moitieHauteur_ = 0.75f;
	rightTransforme_ = right_;
	upTransforme_ = up_;
}

BoiteEnglobanteOrientee::BoiteEnglobanteOrientee(const Vecteur3f& coinMin,
												 const Vecteur3f& coinMax) : right_(1.0f, 0.0f, 0.0f), up_(0.0f, 1.0f, 0.0f)
{
	moitieLongueur_ = (coinMax[0] - coinMin[0]) / 2.0f;
	moitieHauteur_	= (coinMax[1] - coinMin[1]) / 2.0f;

	centre_.x = coinMin[0] + moitieLongueur_;
	centre_.y = coinMin[1] + moitieHauteur_;

	moitieLongueurTransforme_ = moitieLongueur_;
	moitieHauteurTransforme_ = moitieHauteur_;
	centreTransforme_ = centre_;
	rightTransforme_ = right_;
	upTransforme_ = up_;
}

bool BoiteEnglobanteOrientee::calculerCollision(const BoiteEnglobanteOrientee& obb) const {
	// Algorithme tire de http://www.jkh.me/files/tutorials/Separating%20Axis%20Theorem%20for%20Oriented%20Bounding%20Boxes.pdf
	// Belles explications
	aiVector3D T = obb.centreTransforme_ - centreTransforme_;

	float firstAxis = abs(T * rightTransforme_);
	float firstSeparatingAxis = moitieLongueurTransforme_ + abs((obb.moitieLongueurTransforme_ * obb.rightTransforme_) * rightTransforme_) +
								abs((obb.moitieHauteurTransforme_ * obb.upTransforme_) * rightTransforme_);

	if (firstAxis > firstSeparatingAxis) {
		return false;
	}

	float secondAxis = abs(T * upTransforme_);
	float secondSeparatingAxis = moitieHauteurTransforme_ + abs((obb.moitieLongueurTransforme_ * obb.rightTransforme_) * upTransforme_) +
								 abs((obb.moitieHauteurTransforme_ * obb.upTransforme_) * upTransforme_);

	if (secondAxis > secondSeparatingAxis) {
		return false;
	}

	float thirdAxis = abs(T * obb.rightTransforme_);
	float thirdSeparatingAxis = abs((moitieLongueurTransforme_ * rightTransforme_) * obb.rightTransforme_) +
								abs((moitieHauteurTransforme_ * upTransforme_) * obb.rightTransforme_) + obb.moitieLongueurTransforme_;

	if (thirdAxis > thirdSeparatingAxis) {
		return false;
	}

	float fourthAxis = abs(T * obb.upTransforme_);
	float fourthSeparatingAxis = abs((moitieLongueurTransforme_ * rightTransforme_) * obb.upTransforme_) +
								 abs((moitieHauteurTransforme_ * upTransforme_) * obb.upTransforme_) + obb.moitieHauteurTransforme_;

	if (fourthAxis > fourthSeparatingAxis) {
		return false;
	}

	// Il n'y a aucun axe qui separe les deux rectangles
	return true;
}

void BoiteEnglobanteOrientee::update(const aiVector3D& position, float angle, const aiVector3D& taille) {
	aiMatrix4x4 translation, rotation, scale, transformation;
	aiMatrix4x4::Translation(position, translation);
	aiMatrix4x4::RotationZ((float)utilitaire::DEG_TO_RAD(angle), rotation);
	aiMatrix4x4::Scaling(taille, scale);

	transformation = translation * rotation * scale;

	rightTransforme_ = rotation * right_;
	upTransforme_ = rotation * up_;

	rightTransforme_.Normalize();
	upTransforme_.Normalize();

	moitieLongueurTransforme_ = moitieLongueur_ * taille.x;
	moitieHauteurTransforme_ = moitieHauteur_ * taille.y;

	centreTransforme_ = transformation * centre_ ;
}

void BoiteEnglobanteOrientee::afficher() const {
	aiVector3D axeX = rightTransforme_ * moitieLongueurTransforme_;
	aiVector3D axeY = upTransforme_ * moitieHauteurTransforme_;
	aiVector3D coin1 = centreTransforme_ - axeX - axeY;
	aiVector3D coin2 = centreTransforme_ - axeX + axeY;
	aiVector3D coin3 = centreTransforme_ + axeX + axeY;
	aiVector3D coin4 = centreTransforme_ + axeX - axeY;

	glBegin(GL_LINE_LOOP);
		glVertex2f(coin1.x, coin1.y);
		glVertex2f(coin2.x, coin2.y);
		glVertex2f(coin3.x, coin3.y);
		glVertex2f(coin4.x, coin4.y);
	glEnd();
}

const vector<Vecteur3f> BoiteEnglobanteOrientee::getCoins() const {
	vector<Vecteur3f> coins;
	aiVector3D rightScale = rightTransforme_ * moitieLongueurTransforme_;
	aiVector3D upScale = upTransforme_ * moitieHauteurTransforme_;

	aiVector3D coin1 = centreTransforme_ - rightScale - upScale;
	aiVector3D coin2 = centreTransforme_ - rightScale + upScale;
	aiVector3D coin3 = centreTransforme_ + rightScale + upScale;
	aiVector3D coin4 = centreTransforme_ + rightScale - upScale;

	coins.push_back(Vecteur3f(coin1.x, coin1.y, coin1.z));
	coins.push_back(Vecteur3f(coin2.x, coin2.y, coin2.z));
	coins.push_back(Vecteur3f(coin3.x, coin3.y, coin3.z));
	coins.push_back(Vecteur3f(coin4.x, coin4.y, coin4.z));

	return coins;
}

const vector<Droite3D> BoiteEnglobanteOrientee::getDroites() const {
	vector<Droite3D> droites;
	const vector<Vecteur3f> coins = getCoins();
	Vecteur3 basGauche(coins[0][0], coins[0][1], coins[0][2]);
	Vecteur3 hautGauche(coins[1][0], coins[1][1], coins[1][2]);
	Vecteur3 hautDroit(coins[2][0], coins[2][1], coins[2][2]);
	Vecteur3 basDroit(coins[3][0], coins[3][1], coins[3][2]);

	droites.push_back(Droite3D(basGauche, basDroit));
	droites.push_back(Droite3D(basGauche, hautGauche));
	droites.push_back(Droite3D(hautGauche, hautDroit));
	droites.push_back(Droite3D(hautDroit, basDroit));

	return droites;
}

void BoiteEnglobanteOrientee::getBoiteEnglobanteNonOrientee(Vecteur2f& coinHautGauche,
															Vecteur2f& coinBasDroite) const
{
	coinHautGauche[0] = centreTransforme_.x - moitieLongueurTransforme_;
	coinHautGauche[1] = centreTransforme_.y + moitieLongueurTransforme_;

	coinBasDroite[0] = centreTransforme_.x + moitieLongueurTransforme_;
	coinBasDroite[1] = centreTransforme_.y - moitieLongueurTransforme_;
}

}