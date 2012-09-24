#include "DxLib.h"
#include "../UsePrototype.h"
#include "Battle_Player.h"

void Battle_Player_Ini( Character_t *Character ){
	// 勇者のステータスの初期化
	Character->HP=100;
	Character->MP=20;
	Character->Power=30;
	Character->Defense=30;
	Character->LEVEL=1;
	Character->Money=100;
	Character->Speed=10;
	Character->Ex=0;
	Character->MaxHP=100;
	Character->MaxMP=20;
}