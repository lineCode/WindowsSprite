
#include "SpriteAction.h"
namespace Sprite {

	SpriteAction::SpriteAction(ID2D1Bitmap* images[], int length, float delay, bool reverse = false)
	{
		currentIndex = 0;
		// 数组长度
		this->length = length;
		this->images = new ID2D1Bitmap*[length];
		for (int i = 0; i < length; i++)
		{
			this->images[i] = images[i];
		}
		this->delayTime = delay;
		this->reverse = reverse;
		//images;
	}


	SpriteAction::~SpriteAction()
	{

	}

	float SpriteAction::GetDelay()
	{
		return this->delayTime;
	}

	void SpriteAction::ActionBefore()
	{

	}

	void SpriteAction::ActionAfter(PlayerResult result)
	{
		int nextIndex = currentIndex + turn;
		switch (result)
		{
		case sing:
			if (reverse)
			{
				if (nextIndex < 0)
					turn = 1;
				else if (nextIndex > length - 1)
					turn = -1;
			}
			currentIndex += turn;
			break;
		case delay:
			break;
		case expetion:
			break;
		default:
			break;
		}
	}

	// 执行动作-
	ID2D1Bitmap * SpriteAction::ActionIng()
	{
		ID2D1Bitmap * result = this->images[currentIndex];
		return result;
	}

}
