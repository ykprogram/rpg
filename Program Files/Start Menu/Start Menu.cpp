#include "DxLib.h"
#include "../UsePrototype.h"
#include "Start Menu.h"
#include "../KeyBoard.h"

// メニュー項目要素を5つ作る
MenuElement_t MenuElement[5]={
	// タグの中身の順番で格納される。xに80が、yに100が、nameに"ゲームスタート"が入る
	{  80, 100, 100, 80, GetColor(255,255,255), 255, 255, 255,"ゲームスタート" }, 
	{ 100, 150, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"おまけ" },
	{ 100, 200, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"ヘルプ" },
	{ 100, 250, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"コンフィグ" },
	{ 100, 300, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"ゲーム終了" },
};

//int MenuBackGround;
void Start_BackGraph(){
	//メニュー画面の画像をロード
	//MenuBackGround= LoadGraph("RPG DATA\\google.png");
}

int StartMenu(){
	for(int i=0;i<5; i++)DrawBox( MenuElement[i].x, MenuElement[i].y, MenuElement[i].x+18, MenuElement[i].y+18, GetColor( 255, 0, 0 ), FALSE) ;
	//DrawGraph(240,40,MenuBackGround,TRUE);
	DrawFormatString( 320, 240, GetColor( 255, 255, 255 ), "ver3.00");
	switch( DrawMenu( 5, 1, KEY_INPUT_Z, MenuElement ) ){
	case 0:return 2;	// ゲームスタート
	case 4:return 1000; // ゲーム終了
	}
	return 1;

}