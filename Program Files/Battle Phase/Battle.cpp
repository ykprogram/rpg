#include "DxLib.h"
#include "../UsePrototype.h"
#include "Battle.h"


int Damage=0;
int BackGround;
MenuElement_t BattleMenu[4]={
	{30, 380, 30, 30, GetColor(255,255,255), 255, 255, 255, "たたかう"},
	{30, 430, 30, 30, GetColor(255,255,255), 255/2, 255/2, 255/2, "アイテム"},

	{120, 380, 120, 120, GetColor(255,255,255), 255/2, 255/2, 255/2, "にげる"},
	{120, 430, 120, 120, GetColor(255,255,255), 255/2, 255/2, 255/2, "さくせん"}
};

StringScript_t BattleMenuString[8]={
	// 出現
	{ 230,380,GetColor(255,255,255), "%sが現れた!"},
	{ 230,400,GetColor(255,255,255), "勇者は何をする?" },

	// 逃げる
	{ 230,380,GetColor(255,255,255), "勇者は逃げ出した！" },

	// 攻撃
	{ 230,380,GetColor(255,255,255), "勇者の攻撃！"},
	{ 230,400,GetColor(255,255,255), "%dダメージ！" },

	// 敵の攻撃
	{ 230,380,GetColor(255,255,255), "%sの攻撃！"},
	{ 230,400,GetColor(255,255,255), "%dダメージ！" },

};

//敵の初期化
Character_t Enemy[2]={
	// HP,  MP, Lv,  力,  守,  金,  速度,  経験, 画像,  MHP,  MMP,               名前,   X,   Y, パス
	{  10,  10,  1,  15,  10,  10,     5,    10,    0,   10,   10,           "ゼリー", 280, 200, "RPG DATA\\ゼリー.png" },
	{ 100, 100, 10, 150, 100, 100,    10,   100,    0,  100,  100, "アーマードゼリー", 280,  80, "RPG DATA\\ゼリー type2.png"  }
};

void Battle_Ini(){
	Enemy[0].Graph = LoadGraph( Enemy[0].Pass );
	Enemy[1].Graph = LoadGraph( Enemy[1].Pass );
	//BackGround= LoadGraph("RPG DATA\\BackSougen.png");
}


static int NowNumber=0;
// 会話などを表示する,UseBeforeZが1の場合
static int DrawBattleMessage(int Start, int End, StringScript_t MenuString[], int Damage, int EnemyName, int UseBeforeZ){
	if(End<NowNumber+Start+UseBeforeZ){ NowNumber=0;return 1; }
	for( int i=Start; i<(NowNumber+Start+UseBeforeZ); i++){
		if( i==5 || i==0)DrawFormatString(MenuString[i].x,MenuString[i].y,MenuString[i].color,MenuString[i].hyoji,Enemy[EnemyName].Name);
		else DrawFormatString(MenuString[i].x,MenuString[i].y,MenuString[i].color,MenuString[i].hyoji,Damage);
		DrawFormatString(0,200+(i*20),GetRainbowColor(),"%d",i);
	}
	DrawFormatString(40,200,GetRainbowColor(),"%d",NowNumber);
	if(CheckHitKey2(KEY_INPUT_Z)==1)NowNumber++;
	return 0;
}

// はじめのx,y,ゲージのフレーム枠, 中身, 色, その隣に中身の数字をを描画するかしないか
void DrawGauge(int x, int y, int GaugeFrame, int GaugeIn, int ColorFrame, int ColorIn, int Flag){
	DrawBox( x, y, x+GaugeFrame, y+15, ColorFrame, FALSE );
	DrawBox( x+1, y+1, x+1+GaugeIn-2, y-1+15,ColorIn, TRUE );
	if(Flag==TRUE)FontNumDraw( 15+GaugeFrame, y, GaugeIn );
}

int move=0;
int backmenu=0;
int Battle( Character_t *Character, int EnemyType){	
	DrawGraph(0,0,BackGround,TRUE);
	MessageFrame();
	DrawFormatString( 60, 140, GetColor(255, 255, 255), " LV:%d ",Character->LEVEL) ;

	DrawGauge( 15, 16, Character->MaxHP, Character->HP, GetColor( 0, 255, 0 ), GetColor(0, 255/2, 0),TRUE);
	DrawGauge( 15, 31, Character->MaxMP, Character->MP, GetColor( 255, 255, 0 ),GetColor( 255/2, 255/2, 0 ),TRUE );

	DrawGraph(Enemy[EnemyType].X, Enemy[EnemyType].Y, Enemy[EnemyType].Graph, TRUE);
	// 現れたとこ
	if(move==0){if(DrawBattleMessage( 0, 2, BattleMenuString, 0, EnemyType, TRUE) == 1 )move=1;}


	// 選択
	if(move==1)switch( DrawMenu( 2, 2, KEY_INPUT_Z, BattleMenu) ){
	// 速度判定
	case 0:backmenu=0;if( Character->Speed >= Enemy[EnemyType].Speed ){
		Damage=DamageCalc2( *Character, &Enemy[EnemyType]);move=3;
		   }else {
			   Damage=DamageCalc2( Enemy[EnemyType], Character);move=5;
		   }break;
	case 1:break;
	case 2:move=2;break;
	case 3:break;
	}

	//逃げ出す勇者の処理
	if(move==2)if( DrawBattleMessage( 2, 3, BattleMenuString, 0, EnemyType,FALSE) == 1 ){move=0;Enemy[EnemyType].HP = Enemy[EnemyType].MaxHP ;return 2;}



	// 的にダメージを与える処理　中かっこの中には勝った時の処理
	if(move==3)if(DamageCalc3( Character, &Enemy[EnemyType], 3, 5, 5, EnemyType, FALSE)==1){ 
			Character->Ex += Enemy[EnemyType].Ex ; 
			Enemy->HP = Enemy[EnemyType].MaxHP ; 
			move=0 ; 
			return 2 ;
		}

	// 敵のダメージを与える分を表示　中かっこの中には負けた時の処理
	if(move==5)if(DamageCalc3( &Enemy[EnemyType], Character, 5, 7, 3, EnemyType, TRUE)==1){
			move=0 ;
			return 0 ;
		}
	

	return 4 ;
}/*
 ( ( 攻撃側のレベル*2 /5 +2) *技の威力 *攻撃側の能力値/防御側の能力値/50+2)*GetRand(85～100)/100
 ( ( 攻撃側のレベル *2 /5 +2) *攻撃側の攻撃力 /防御側の防御力 /50 +2 )*GetRand(85～100)/100
 */

int DamageCalc( Character_t Attacker, Character_t Defender ){
	// 通常攻撃の計算式の答えを返す
	return ( Attacker.LEVEL *2 *Attacker.Power /Defender.Defense +2 )*( 85+ GetRand(15) )/100;
};

int DamageCalc2( Character_t Attacker, Character_t *Defender ){
	// 表示するためにいったん代入
	int Damage2= DamageCalc( Attacker, *Defender ) ;
	// 敵のHPからダメージを引く
	Defender->HP -= Damage2;
	if(Defender->HP < 0 )Defender->HP=0;
	return Damage2;
}

// 攻撃側のステータス　防御側のステータス　文章の始まり　文章の終わり　次に行くmoveの数値　敵の番号　前にZキーを使う処理があったか否か
int DamageCalc3( Character_t *Attacker, Character_t *Defender, int StartLog, int EndLog, int Go, int EnemyType, int Flag){
	// 防御側に与えるダメージ計算
	if( DrawBattleMessage( StartLog, EndLog, BattleMenuString, Damage, EnemyType, Flag ) == 1 ){
		// HPが0以下の場合　ﾀﾋ処理
		if( Defender->HP <= 0 )return 1 ;
		// 防御側のダメージ計算
		Damage=DamageCalc2( *Defender, Attacker );
		// 次の行動へ
		move=Go;
		// もし二回目の行動であった場合はここでメニューに戻る
		if(backmenu==1)move=1 ;
		backmenu=1;
	}
	return 0;
}