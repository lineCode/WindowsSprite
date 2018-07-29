#include "SpriteHandle.h"
using namespace Sprite;

SpriteHandle::SpriteHandle()
{
}

SpriteHandle::~SpriteHandle()
{

}


void SpriteHandle::StartLive(Animation* ani)
{
	this->aniPlayer = ani;

	/*ID2D1Bitmap* test_imgs;
	test_imgs = ani->CreateBitmapFromFile(TEXT("Content/Images/back1.png"));*/
	ID2D1Bitmap* sing_imgs[4];
	sing_imgs[0] = ani->CreateBitmapFromFile(TEXT("Content/Images/sing1.png"));
	sing_imgs[1] = ani->CreateBitmapFromFile(TEXT("Content/Images/sing2.png"));
	sing_imgs[2] = ani->CreateBitmapFromFile(TEXT("Content/Images/sing3.png"));
	sing_imgs[3] = ani->CreateBitmapFromFile(TEXT("Content/Images/sing4.png"));
	SpriteAction sing(sing_imgs, 4, 300, true);
	this->actions.push_back(sing);


	ID2D1Bitmap* darg_imgs[6];
	darg_imgs[0] = ani->CreateBitmapFromFile(TEXT("Content/Images/drag1.png"));
	darg_imgs[1] = ani->CreateBitmapFromFile(TEXT("Content/Images/drag2.png"));
	darg_imgs[2] = ani->CreateBitmapFromFile(TEXT("Content/Images/drag3.png"));
	darg_imgs[3] = ani->CreateBitmapFromFile(TEXT("Content/Images/drag4.png"));
	darg_imgs[3] = ani->CreateBitmapFromFile(TEXT("Content/Images/drag5.png"));
	darg_imgs[3] = ani->CreateBitmapFromFile(TEXT("Content/Images/drag6.png"));
	SpriteAction drag(darg_imgs, 6, 250, true);
	this->actions.push_back(drag);
}

void Sprite::SpriteHandle::Update()
{
	currentImage = actions[currentState].ActionIng();
	aniPlayer->Play(currentImage, actions[currentState].GetDelay());
	actions[0].ActionAfter(currentState);
	lastState = currentState;
}

void Sprite::SpriteHandle::SetPlayState(PlayerResult state)
{
	this->lastState = this->currentState;
	this->currentState = state;
}