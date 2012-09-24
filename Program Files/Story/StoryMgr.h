#ifndef EDF_STORY_H

#define EDF_STORY_H

// ストーリー項目の表示に必要な構造体を用意する
typedef struct{
        int x, y;       // 座標格納用変数
        char story[128]; // 項目名格納用変数
} Story_t ;

	#ifdef STORY_PROTOTYPE

	#include "../Function.h"
	#include "../Music/Music.h"
	void TestStoryIni();
	int StoryMgr();

	#endif //STORY_PROTOTYPE END
#endif