#ifndef DEF_MAP_H

#define DEF_MAP_H 

#define WorldX 10
#define WorldY 10
//マップの構造体
typedef struct{
	int MapX,MapY;
}Map_t;

typedef struct{
	int x,y,Graph;	// 座標と画像を格納する
	int MapX,MapY,MapNum;	// マップの座標を格納する変数
}Building_t;

	#ifdef MAP_PROTOTYPE //この下にある関数を使いたければ左を#defineで宣言しろ

	#include "../Function.h"
	#include "Map_Player.h"
	void BackGround_Ini();
	void DrawBackGround( Map_t Map, int FieldNumber );
	void DrawBuilding(Map_Player_t Player, Map_t Map,int *FieldNumber);

	#endif //MAP_PROTOTYPE END

#endif //EDF_MAP_H END