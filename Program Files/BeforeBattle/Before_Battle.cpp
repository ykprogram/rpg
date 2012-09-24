//このファイルでは、戦闘に入る前ムービー的なものをするためのファイルです。
#include "DxLib.h"
#include "../UsePrototype.h"
#include "Before_Battle.h"

static char timer=0;//何秒間戦闘前のムービーを再生するか
static int Rand=0;
static int Graphx[16],Graphy[16],copy[16];

//画面をコピーするために描画元になるものを作る
void Before_Battle_Ini(){
	for(char i=0;i<4;i++)for(char j=0;j<4;j++)copy[i*4+j] = MakeGraph( ScreenWidth/4, ScreenHeight/4 ) ;//16個画像格納データを作る。
}

//戦闘に入る前に画面をコピー
void Set_Before_BattleMovie(){
	for(char i=0;i<4;i++)for(char j=0;j<4;j++){
		GetDrawScreenGraph( (640/4)*j, (480/4)*i, (640/4)*(j+1), (480/4)*(i+1), copy[i*4+j] ) ;
		Graphx[i*4+j]=640/4*j;//描画する各ｘ座標
		Graphy[i*4+j]=480/4*i;//描画する各ｙ座標
	}
	//この時点でどの演出をするか決める
	Rand=GetRand(1);
}
// EnemyTypeは出現する敵を選ぶためのもの
int BeforeBattleMgr(int *EnemyType){
	PlayBGM(battle);
	switch(Rand){
	case 0:BeforeBattleMovie();break;
	case 1:BeforeBattleMovie1();break;
	}
	timer++;
	//ここで初期化するんです。
	if(timer==125){
		timer=0;
		*EnemyType=GetRand(1);//ここで敵を抽選する
		return 4;
	}
	return 3;
}

//真ん中からの外へ
void BeforeBattleMovie(){
	//左上
	Graphx[0]+=12;
	Graphy[0]+=9;
	Graphx[1]+=4;
	Graphy[1]+=9;
	Graphx[4]+=12;
	Graphy[4]+=4;
	Graphx[5]+=4;
	Graphy[5]+=3;
	//右上
	Graphx[2]-=4;
	Graphy[2]+=9;
	Graphx[3]-=12;
	Graphy[3]+=9;
	Graphx[6]-=4;
	Graphy[6]+=3;
	Graphx[7]-=12;
	Graphy[7]+=4;
	//左下
	Graphx[8]+=12;
	Graphy[8]-=4;
	Graphx[9]+=4;
	Graphy[9]-=3;
	Graphx[12]+=12;
	Graphy[12]-=9;
	Graphx[13]+=4;
	Graphy[13]-=9;
	//右下
	Graphx[10]-=4;
	Graphy[10]-=3;
	Graphx[11]-=12;
	Graphy[11]-=4;
	Graphx[14]-=4;
	Graphy[14]-=9;
	Graphx[15]-=12;
	Graphy[15]-=9;
	for(char i=0;i<16;i++)DrawGraph( Graphx[i], Graphy[i], copy[i], FALSE ) ;
	// 0  1  2  3
	// 4  5  6  7
	// 8  9 10 11
	//12 13 14 15
	//中心までの長さ20
}

//だんだん小さく中央に
void BeforeBattleMovie1(){
	for(int i=0;i<16;i++)DrawExtendGraph( Graphx[i]+0.64*timer, Graphy[i]+0.48*timer, Graphx[i]+160-timer*0.64, Graphy[i]+120-timer*0.48, copy[i], TRUE ) ;
}