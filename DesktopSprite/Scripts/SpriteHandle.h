#pragma once
#include "Animation.h"
#include "SpriteAction.h"
namespace Sprite {
	// ����������ֵ
	//enum SpriteMood {
	//	Nofeelings = -10,
	//	Bad = 0,
	//	Angry = 30,
	//	Normal = 50,
	//	Happy = 100,
	//	Wonderful = 150
	//};

	//// �����Ը������
	//class SpriteDisposition {

	//};
	//

	// �´����� / ������� / �ܿ����� / ������ƾ�� 
	class SpriteHandle
	{

	public:
		SpriteHandle();
		~SpriteHandle();

		// ��ʼ��
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

		// ��չ��������
		// vector<ISpriteExtension> extensions;
		// ������ֵ (����:100 < ... < һ��:50 < ... < ������:0
		float Moodvalue = 50;
	};

}
