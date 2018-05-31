#pragma once
#include "SpriteAction.h"
namespace Sprite {
	// 扩展工具接口，扩展工具类必须继承
	interface ISpriteExtension
	{

	};

	// 精灵性格控制器
	class SpriteDisposition {

	};
	// 精灵心情阈值
	enum SpriteMood {
		Nofeelings = -10,
		Bad = 0,
		Angry = 30,
		Normal = 50,
		Happy = 100,
		Wonderful = 150
	};


	// 精灵大脑/总控制器/精灵控制句柄
	class SpriteHandle
	{
	public:
		SpriteHandle();
		~SpriteHandle();
		


		// 获取当前执行的动作
		ActionState GetCurrentAction();
		// 获取当前心情数值
		float GetCurrentMoodValue();
		// 自主思烤
		void Think();
		// 停下来(保持静止)
		void Stop();
		// 动起来
		void Live();

	private:
		// 动作控制器
		SpriteAction action;
		// 扩展工具数组
		vector<ISpriteExtension> extensions;
		// 心情数值 (开心:100 < ... < 一般:50 < ... < 不开心:0
		float Moodvalue = 50;
	};

}
