#ifndef EDF_STORY_H

#define EDF_STORY_H

// �X�g�[���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
typedef struct{
        int x, y;       // ���W�i�[�p�ϐ�
        char story[128]; // ���ږ��i�[�p�ϐ�
} Story_t ;

	#ifdef STORY_PROTOTYPE

	#include "../Function.h"
	#include "../Music/Music.h"
	void TestStoryIni();
	int StoryMgr();

	#endif //STORY_PROTOTYPE END
#endif