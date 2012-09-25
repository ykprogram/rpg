//ここから読み始めます。
//switchの中にある関数はmgrのほうに入ってます。
//必ず関数を使うときはUsePrototype.hをインクルードすることになってます
#include "DxLib.h"
#include "UsePrototype.h"
#include "Define.h"
#include "Mouse.h"
#include "Function.h"
#include "Start Menu\Start Menu.h"
#include "Map\MapMgr.h"
#include "Map\Map_Player.h"
#include "Battle Phase\Battle.h"
#include "BeforeBattle\Before_Battle.h"
#include "Story\StoryMgr.h"
#include "Music\Music.h"
#include "Map\MapMenu.h"
#include "KeyBoard.h"
#include "Battle Phase\Battle_Player.h"

static char Phase=0;//これでメインswitchを制御する
static int Enemy=0;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{
	Mouse_t Mouse;				// マウスの実体宣言
	Map_Player_t Player;		// プレイヤーの実体宣言
	Character_t Character;		// キャラクターのステータスの実態宣言

	SetGraphMode( ScreenWidth, ScreenHeight, 32 ) ;
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); // ウィンドウモード変更と初期化と裏画面設定
	SetMouseDispFlag(TRUE) ;	// マウスを表示状態にする 
	DrawFormatString( 0, 0, GetColor(255, 255, 255), "読み込み中,Now Loading...") ;
	Before_Battle_Ini();		// 戦闘に入る前のムービーの初期化
	Function_Ini();				// Functionの初期化をする(画像)
	Mouse_Ini( &Mouse );		// マウスの初期化をする(画像)
	Menu_Ini();					// メニューの初期化(画像)
	BackGround_Ini();			// 背景の初期化をする(画像)
	Map_Player_Ini( &Player );	// プレイヤーの初期化をする(画像)
	//Start_BackGraph();		// スタート画面の背景を描画する
	Battle_Ini();				// 敵の画像をロード
	Battle_Player_Ini( &Character );// 能力の初期化
	Music_Ini();				// 音楽の初期化
	TestStoryIni();				// いまだけ動画の初期化
	
	
	// while( 裏画面を表画面に反映, メッセージ処理, 画面クリア, エスケープ押したら脱出, Phaseに1000が入ると脱出)
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && CheckHitKey( KEY_INPUT_ESCAPE )==0){
		AllKey();									// これでCheckHitKey2が使えるようになるよ	
		switch(Phase){
		case 0:Phase=StoryMgr();break;				// メニューなんだけどPhaseに代入してるのは返り値
		case 1:Phase=StartMenu();break;				// マップ内の移動をするこれが0だと止まっていてそれ以外だと動いている
		case 2:Phase=MapMgr( Mouse, &Player, Character );Player.MoveControl=0;break;//なぜかマップさんはPlayerをポインターにしないと動いてくれないｗ
		case 3:Phase=BeforeBattleMgr( &Enemy );break;
		case 4:Phase=Battle( &Character, Enemy );break;
		}
		if(Phase==5)return 0;
		Mouse_Draw( &Mouse );// ここでマウスのポインターを取得し描画する
	}
	DxLib_End(); // DXライブラリ終了処理				
	return 0;
} 

		
	//int Music;
	//char handle[100];if(GetDragFilePath( handle )==0)Music = LoadSoundMem( handle );
	//if(CheckHitKey(KEY_INPUT_M))PlaySoundMem( Music, DX_PLAYTYPE_BACK ) ;
	//SetDragFileValidFlag(TRUE);	// D&Dするためのもの