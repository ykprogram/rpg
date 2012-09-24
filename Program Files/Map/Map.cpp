//このファイルではマップに関する関数が書いてあります
#include "DxLib.h"
#include "../UsePrototype.h"
#include "Map.h"

//ここで数値の初期化(Iniでこれを書くと行数がかさむ)
Building_t Building[1]={
	{130,130,0,0,0,0}
};

static int BackGroundGraph[3];

static char BackGround[2][WorldY][WorldX]={
	{//最初のフィールド
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	},
	{//第二のフィールド(一応これが城の中になる設定)
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	}
};



//ここで背景を追加できます
void BackGround_Ini(){
	BackGroundGraph[0] = LoadGraph("RPG DATA\\sougen1.png");// 暗いほうの草原
	BackGroundGraph[1] = LoadGraph("RPG DATA\\sougen2.png");// 明るいほうの草原

	Building[0].Graph =LoadGraph("RPG DATA\\castle.png"); // 城の読み込み
}

//FieldNumberは３つの配列の最初である
void DrawBackGround( Map_t Map, int FieldNumber ){
	//BackGroundにおいて0となっているところはGraphic[0]を背景にしろということです。
	if(BackGround[FieldNumber][Map.MapY][Map.MapX]==0)DrawGraph( 0, 0, BackGroundGraph[0], FALSE ) ;
	if(BackGround[FieldNumber][Map.MapX][Map.MapY]==1)DrawGraph( 0, 0, BackGroundGraph[1], FALSE ) ;
}
//マップに出る城やダンジョンを描画し当たり判定を設ける
void DrawBuilding(Map_Player_t Player, Map_t Map, int *FieldNumber){
	if((*FieldNumber==Building[0].MapNum)&&(Map.MapX==Building[0].MapX)&&(Map.MapY==Building[0].MapY)){
		DrawGraph(Building[0].x, Building[0].y, Building[0].Graph, TRUE);
		if(Player_Hantei( Player, Building[0].x, Building[0].y, Building[0].Graph )==1)*FieldNumber=1;
	}
}