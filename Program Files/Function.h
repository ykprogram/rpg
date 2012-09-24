//自作関数を使うときはこのファイルをインクルードすればよい
//それぞれの関数の働きはFunction.cppを参考

#ifndef EDF_FUNCTION_H

#define EDF_FUNCTION_H

//functionで使う画像のデータ
typedef struct{
	int x,y,Graph;
}FunctionGraph_t;

//メニュー文字表示
typedef struct{
	int x,y,color;		// x, y, 色格納
	char hyoji[100];	// 文字格納変数 
}StringScript_t;

// メニュー項目の表示に必要な構造体を用意する
typedef struct{
	int x, y;					// 座標格納変数
	int bx,ax;					// 移動後,前座標
	int color;					// 色格納変数
	int BrightR,BrightG,BrightB;// 光度格納変数
	char name[128];				// 項目名格納変数
} MenuElement_t ;


	#ifdef FUNCTION_PROTOTYPE

	#include "Map\Map.h"
	#include "Map\Map_Player.h"
	#include "Map\MapMenu.h"
	#include "Mouse.h"
	#include "Music\Music.h"
	#include "KeyBoard.h"
	#include "Battle Phase\Battle.h"
	void Function_Ini();
	unsigned long GetRainbowColor() ;
	void RainbowDrawGraph(int x,int y,int Handle, int Flag);
	void FontNumDraw( int x, int y, int FontNum );
	int Hantei( int x, int y, int handle, int x2, int y2, int handle2 );
	int Player_Hantei( Map_Player_t Player, int x, int y, int handle );
	void MessageFrame();
	int DrawMenu(int ElementMaxY, int ElementMaxX,  int KeyCode, MenuElement_t Menu[]);
	int DrawMessageString(int Start, int End, StringScript_t MenuString[], int num ,int UseBeforeZ);

	#endif //FUNCTION_PROTOTYPE END

#endif