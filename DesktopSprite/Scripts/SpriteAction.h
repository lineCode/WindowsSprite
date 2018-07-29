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
	// ���ƾ���Ķ����߼�����������ƶ���
	class SpriteAction
	{

	public:
		SpriteAction(ID2D1Bitmap *images[], int length, float delay, bool reverse);
		~SpriteAction();
		float GetDelay();
		// ����ǰ��׼��
		void ActionBefore();
		// ִ�ж���
		ID2D1Bitmap * ActionIng();
		/*
		 *	����ִ����ϡ�
		 *  params:
		 *		result=����ִ�н��,��ʶflag.
		 */
		void ActionAfter(PlayerResult result);

	private:
		bool reverse = false;
		int turn = 1;
		int length;
		// ��¼���ŵ�λͼ��
		int currentIndex;
		// �л�֡�ӳ�ʱ��
		float delayTime;
		// ����λͼָ������
		ID2D1Bitmap ** images;

	};
}