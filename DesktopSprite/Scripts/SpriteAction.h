#pragma once
#include "Animation.h"


namespace Sprite {
	enum Actions {
		test,
		stdy,
		walk,
		run,
		jump,
		craw,
	};
	// 控制精灵的动作逻辑，不负责绘制动画
	class SpriteAction
	{

	public:
		SpriteAction(ID2D1Bitmap *images[], int length, float delay, bool reverse);
		~SpriteAction();
		float GetDelay();
		// 动作前的准备
		void ActionBefore();
		// 执行动作
		ID2D1Bitmap * ActionIng();
		/*
		 *	动作执行完毕。
		 *  params:
		 *		result=动作执行结果,标识flag.
		 */
		void ActionAfter(PlayerResult result);

	private:
		bool reverse = false;
		int turn = 1;
		int length;
		// 记录播放的位图标
		int currentIndex;
		// 切换帧延迟时间
		float delayTime;
		// 动画位图指针数组
		ID2D1Bitmap ** images;

	};
}