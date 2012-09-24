#ifndef DEF_BATTLE_H  //��dinclude�h�~

#define DEF_BATTLE_H

typedef struct {
	int HP;			// �̗�
	int MP;			// ϼޯ��߲��
	int LEVEL;		// ���x��
	int Power;		// �U����
	int Defense;	// �h���
	int Money;		// ������
	int Speed;		// ���x
	int Ex;			// �o���l
	int Graph;		// �摜
	int MaxHP;		// �ő�̗�
	int MaxMP;		// �ő�ϼޯ��߲��
	char Name[30];	// �G�̖��O
	//��������͉摜�֌W
	int X;		// x���W
	int Y;		// y���W
	char Pass[50];	// �摜�̂���Ƃ��܂ł̃p�X
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