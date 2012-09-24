#include "DxLib.h"
#include "../UsePrototype.h"
#include "MapMenu.h"
#include "../KeyBoard.h"

//つまり表示させられるメニューの個数は2個ということ。
//注意,画面に画像を表示させるつもりがなくてもこの関数を使うこと
MapMenu_t MapMenu[5]={
	{  0, 0, 0, 0  },		// 4つの選択画面の画像

	{  0, 0,  0, 0 },		// 調べるコマンド
	{ 20, 20, 0, 0 },		// アイテムコマンド
	{  0, 0,  0, 0 },		// 呪文コマンド
	{ 20, 20, 0, 0 }		// ステータス表示画面
};

// メニュー項目要素を4つ作るメニューに表示させる文字
MenuElement_t MenuElement2[4]={
	{36, 30, 36, 36, GetColor(255,255,255), 255, 255, 255, "調べる"},
	{36, 80, 36, 36, GetColor(255,255,255), 255/2, 255/2, 255/2, "アイテム"},
	{36, 130, 36, 36, GetColor(255,255,255), 255/2, 255/2, 255/2, "呪文"},
	{36, 180, 36, 36, GetColor(255,255,255), 255/2, 255/2, 255/2, "強さ"}
};

StringScript_t MenuString[3]={
	{20,480-125+20,GetColor(255,0,255),"勇者はあたりを調べた"},
	{20,480-125+20+20,GetColor(255,0,255),"が特に変わったところはないようだ"},
	{20,480-125+20+20+20,GetRainbowColor(),"表示出力中"}
};

//マップのメニューをロードする
void Menu_Ini(){
	MapMenu[0].Graph = LoadGraph("RPG DATA\\menu.png");
	MapMenu[4].Graph = LoadGraph("RPG DATA\\menu2.png");
}

// マップでのメニューを担当する(ここの返り値が0ならメニューが表示されていない1なら表示されている。)
// ここを最初に読み込むMainMenu()が先じゃないぞ
int Menu( Character_t Character, Map_t Map, int *FieldNumber ){

	if( CheckHitKey2( KEY_INPUT_C )== 1)if(MapMenu[0].Flag==0)MapMenu[0].Flag=1;

	if( MapMenu[0].Flag==1 )MainMenu();					// メニューが開いた時の処理,ここで選択
	if( MapMenu[1].Flag==1 )Search();					// 調べるの動作
	if( MapMenu[2].Flag==1 )Item();						// アイテムの動作
	if( MapMenu[3].Flag==1 )Magic( Map, FieldNumber);	// 呪文の動作
	if( MapMenu[4].Flag==1 )StatusMenu( Character );	// ステータス画面の描画

	//削除の処理はここ
	if( CheckHitKey2( KEY_INPUT_X )== 1 && MapMenu[1].Flag!=1 )for( int i=0;i<5;i++)MapMenu[i].Flag=0;

	//メニューが表示されているときは勇者を動かさないということ
	//なぜMapMenu[0]だけかというとこれがトップ画面なのでずっと出っ放し。
	//必ずメニューを描画しているときはこのフラグは１
	if(MapMenu[0].Flag==1)return 1;

	return 0;

}


//メニュー画面を表示
void MainMenu(){
	//４つの項目をどれも開いていなかったら
	if(MapMenu[1].Flag != 1 && MapMenu[2].Flag != 1 && MapMenu[3].Flag != 1 && MapMenu[4].Flag != 1){
		// メニュー項目を描画
		DrawGraph( MapMenu[0].x, MapMenu[0].y, MapMenu[0].Graph, TRUE );
		MapMenu[ DrawMenu( 4, 1, KEY_INPUT_Z, MenuElement2 ) + 1 ].Flag=1;
	}
}




//調べるコマンド
void Search(){
	MessageFrame();
	//もし文字がすべて表示し終えたら戻る
	if( DrawMessageString( 0, 3, MenuString, 0, FALSE ) == 1 )MapMenu[1].Flag=0;
}

//アイテムコマンド
void Item(){
	DrawGraph( MapMenu[2].x, MapMenu[2].y, MapMenu[0].Graph, TRUE);
	DrawFormatString(20+15,20+20,GetColor(255,255,255),"持っていません");
}

// 呪文コマンド
void Magic( Map_t Map ,int *FieldNumber){
	DrawFormatString(0,0,GetRainbowColor(),"城");
	if(CheckHitKey2(KEY_INPUT_Z)==1)*FieldNumber=0;
}

//ステータスを表示（強さコマンド）
void StatusMenu( Character_t Character ){
	DrawGraph(MapMenu[4].x,MapMenu[4].y,MapMenu[4].Graph,TRUE);
	FontNumDraw(120,38,Character.LEVEL);
	FontNumDraw(120,69,Character.HP);
	FontNumDraw(120,99,Character.MP);
	FontNumDraw(120,129,Character.Power);
	FontNumDraw(120,162,Character.Defense);
	FontNumDraw(120,195,Character.Money);
}