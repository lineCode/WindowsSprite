#pragma once
#include "SpriteAction.h"
namespace Sprite {
	// ��չ���߽ӿڣ���չ���������̳�
	interface ISpriteExtension
	{

	};

	// �����Ը������
	class SpriteDisposition {

	};
	// ����������ֵ
	enum SpriteMood {
		Nofeelings = -10,
		Bad = 0,
		Angry = 30,
		Normal = 50,
		Happy = 100,
		Wonderful = 150
	};


	// �������/�ܿ�����/������ƾ��
	class SpriteHandle
	{
	public:
		SpriteHandle();
		~SpriteHandle();
		


		// ��ȡ��ǰִ�еĶ���
		ActionState GetCurrentAction();
		// ��ȡ��ǰ������ֵ
		float GetCurrentMoodValue();
		// ����˼��
		void Think();
		// ͣ����(���־�ֹ)
		void Stop();
		// ������
		void Live();

	private:
		// ����������
		SpriteAction action;
		// ��չ��������
		vector<ISpriteExtension> extensions;
		// ������ֵ (����:100 < ... < һ��:50 < ... < ������:0
		float Moodvalue = 50;
	};

}
