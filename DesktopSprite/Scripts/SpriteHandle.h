#pragma once
#include "Animation.h"
#include "SpriteAction.h"
namespace Sprite {
	// 精灵心情阈值
	//enum SpriteMood {
	//	Nofeelings = -10,
	//	Bad = 0,
	//	Angry = 30,
	//	Normal = 50,
	//	Happy = 100,
	//	Wonderful = 150
	//};

	//// 精灵性格控制器
	//class SpriteDisposition {

	//};
	//

	// 下达命令 / 精灵大脑 / 总控制器 / 精灵控制句柄 
	class SpriteHandle
	{

	public:
		SpriteHandle();
		~SpriteHandle();

		// 初始化
		void StartLive(Animation* ani);
		//
		void Update();
		void SetPlayState(PlayerResult currentstate);
	private:
		Animation* aniPlayer;
		vector<SpriteAction> actions;
		PlayerResult lastState = PlayerResult::sing;
		PlayerResult currentState = PlayerResult::sing;
		ID2D1Bitmap * currentImage;

		// 扩展工具数组
		// vector<ISpriteExtension> extensions;
		// 心情数值 (开心:100 < ... < 一般:50 < ... < 不开心:0
		float Moodvalue = 50;
	};

}
