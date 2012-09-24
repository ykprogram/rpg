#ifndef DEF_BATTLE_H  //二重include防止

#define DEF_BATTLE_H

typedef struct {
	int HP;			// 体力
	int MP;			// ﾏｼﾞｯｸﾎﾟｲﾝﾄ
	int LEVEL;		// レベル
	int Power;		// 攻撃力
	int Defense;	// 防御力
	int Money;		// 所持金
	int Speed;		// 速度
	int Ex;			// 経験値
	int Graph;		// 画像
	int MaxHP;		// 最大体力
	int MaxMP;		// 最大ﾏｼﾞｯｸﾎﾟｲﾝﾄ
	char Name[30];	// 敵の名前
	//ここからは画像関係
	int X;		// x座標
	int Y;		// y座標
	char Pass[50];	// 画像のあるとこまでのパス
}Character_t;

	#ifdef BATTLE_PROTOTYPE

	#include "../Define.h"
	#include "../Function.h"
	void Battle_Ini();
	int Battle( Character_t *Character, int EnemyType );
	int DamageCalc( Character_t Attacker, Character_t Defender );
	int	DamageCalc2( Character_t Attacker, Character_t *Defender );
	int DamageCalc3( Character_t *Character, Character_t *Defender, int StartLog, int EndLog, int Go, int EnemyType, int Flag);

	#endif //BATTLE_PROTOTYPE END

#endif