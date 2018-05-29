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
		// 播放器
		D2DWindow::Animation player;
		// 动画位图数组
		vector<ID2D1Bitmap> images;

	};

	SpriteAction::SpriteAction()
	{
	}

	SpriteAction::~SpriteAction()
	{
	}
}