#pragma once
#include "SpriteAction.h"
namespace Sprite {

	class SpriteHandle
	{
	public:
		SpriteHandle();
		~SpriteHandle();

		void LoadAnmationResources();
	private:
		SpriteAction action;
	};

}
