#ifndef DEF_MAPPLAYER_H

#define DEF_MAPPLAYER_H

typedef struct{
	int x, y;//プレイヤーの画像のxy
	int w, h;//プレイヤーの横幅と縦幅
	int Graph[ 12 ];//画像を格納するための物
	char PlayerMotion;//基本はGraph[12]の中に入れる。
	char MoveControl;//これが0なら動いていない、1なら動いてる
}Map_Player_t;

	#ifdef MAPPLAYER_PROTOTYPE //この下にある関数を使いたければ左を#defineで宣言しろ

	//ここにあるincludeは構造体を使うためのもの
	#include "../BeforeBattle/Before_Battle.h"
	#include "../Mouse.h"
	#include "../Define.h"
	#include "Map.h"
	void Map_Player_Ini( Map_Player_t *Player );
	void PlayerUp( Map_Player_t *Player );
	void PlayerDown( Map_Player_t *Player );
	void PlayerRight( Map_Player_t *Player );
	void PlayerLeft( Map_Player_t *Player );
	void PlayerControl_Map( Map_t *Map, Map_Player_t *Player );
	void PlayerMove_Map( Mouse_t Mouse, Map_Player_t *Player );
	int Encounter( Map_Player_t Player );

	#endif		//MAPPLAYER_PROTOTYPE END

#endif//DEF_MAPPLAYER_H END