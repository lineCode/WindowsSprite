#pragma once
#include "Animation.h"
namespace Sprite {
	enum ActionState {
		stay, walk, craw, push, drop
	};

	class SpriteAction
	{
	public:
		SpriteAction();
		~SpriteAction();

	private:
		// ������
		D2DWindow::Animation player;
		// ����λͼ����
		vector<ID2D1Bitmap> images;

	};

	SpriteAction::SpriteAction()
	{
	}

	SpriteAction::~SpriteAction()
	{
	}
}