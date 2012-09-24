#include "DxLib.h"
#include "../UsePrototype.h"
#include "Battle.h"


int Damage=0;
int BackGround;
MenuElement_t BattleMenu[4]={
	{30, 380, 30, 30, GetColor(255,255,255), 255, 255, 255, "��������"},
	{30, 430, 30, 30, GetColor(255,255,255), 255/2, 255/2, 255/2, "�A�C�e��"},

	{120, 380, 120, 120, GetColor(255,255,255), 255/2, 255/2, 255/2, "�ɂ���"},
	{120, 430, 120, 120, GetColor(255,255,255), 255/2, 255/2, 255/2, "��������"}
};

StringScript_t BattleMenuString[8]={
	// �o��
	{ 230,380,GetColor(255,255,255), "%s�����ꂽ!"},
	{ 230,400,GetColor(255,255,255), "�E�҂͉�������?" },

	// ������
	{ 230,380,GetColor(255,255,255), "�E�҂͓����o�����I" },

	// �U��
	{ 230,380,GetColor(255,255,255), "�E�҂̍U���I"},
	{ 230,400,GetColor(255,255,255), "%d�_���[�W�I" },

	// �G�̍U��
	{ 230,380,GetColor(255,255,255), "%s�̍U���I"},
	{ 230,400,GetColor(255,255,255), "%d�_���[�W�I" },

};

//�G�̏�����
Character_t Enemy[2]={
	// HP,  MP, Lv,  ��,  ��,  ��,  ���x,  �o��, �摜,  MHP,  MMP,               ���O,   X,   Y, �p�X
	{  10,  10,  1,  15,  10,  10,     5,    10,    0,   10,   10,           "�[���[", 280, 200, "RPG DATA\\�[���[.png" },
	{ 100, 100, 10, 150, 100, 100,    10,   100,    0,  100,  100, "�A�[�}�[�h�[���[", 280,  80, "RPG DATA\\�[���[ type2.png"  }
};

void Battle_Ini(){
	Enemy[0].Graph = LoadGraph( Enemy[0].Pass );
	Enemy[1].Graph = LoadGraph( Enemy[1].Pass );
	//BackGround= LoadGraph("RPG DATA\\BackSougen.png");
}


static int NowNumber=0;
// ��b�Ȃǂ�\������,UseBeforeZ��1�̏ꍇ
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

// �͂��߂�x,y,�Q�[�W�̃t���[���g, ���g, �F, ���ׂ̗ɒ��g�̐�������`�悷�邩���Ȃ���
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
	// ���ꂽ�Ƃ�
	if(move==0){if(DrawBattleMessage( 0, 2, BattleMenuString, 0, EnemyType, TRUE) == 1 )move=1;}


	// �I��
	if(move==1)switch( DrawMenu( 2, 2, KEY_INPUT_Z, BattleMenu) ){
	// ���x����
	case 0:backmenu=0;if( Character->Speed >= Enemy[EnemyType].Speed ){
		Damage=DamageCalc2( *Character, &Enemy[EnemyType]);move=3;
		   }else {
			   Damage=DamageCalc2( Enemy[EnemyType], Character);move=5;
		   }break;
	case 1:break;
	case 2:move=2;break;
	case 3:break;
	}

	//�����o���E�҂̏���
	if(move==2)if( DrawBattleMessage( 2, 3, BattleMenuString, 0, EnemyType,FALSE) == 1 ){move=0;Enemy[EnemyType].HP = Enemy[EnemyType].MaxHP ;return 2;}



	// �I�Ƀ_���[�W��^���鏈���@���������̒��ɂ͏��������̏���
	if(move==3)if(DamageCalc3( Character, &Enemy[EnemyType], 3, 5, 5, EnemyType, FALSE)==1){ 
			Character->Ex += Enemy[EnemyType].Ex ; 
			Enemy->HP = Enemy[EnemyType].MaxHP ; 
			move=0 ; 
			return 2 ;
		}

	// �G�̃_���[�W��^���镪��\���@���������̒��ɂ͕��������̏���
	if(move==5)if(DamageCalc3( &Enemy[EnemyType], Character, 5, 7, 3, EnemyType, TRUE)==1){
			move=0 ;
			return 0 ;
		}
	

	return 4 ;
}/*
 ( ( �U�����̃��x��*2 /5 +2) *�Z�̈З� *�U�����̔\�͒l/�h�䑤�̔\�͒l/50+2)*GetRand(85�`100)/100
 ( ( �U�����̃��x�� *2 /5 +2) *�U�����̍U���� /�h�䑤�̖h��� /50 +2 )*GetRand(85�`100)/100
 */

int DamageCalc( Character_t Attacker, Character_t Defender ){
	// �ʏ�U���̌v�Z���̓�����Ԃ�
	return ( Attacker.LEVEL *2 *Attacker.Power /Defender.Defense +2 )*( 85+ GetRand(15) )/100;
};

int DamageCalc2( Character_t Attacker, Character_t *Defender ){
	// �\�����邽�߂ɂ���������
	int Damage2= DamageCalc( Attacker, *Defender ) ;
	// �G��HP����_���[�W������
	Defender->HP -= Damage2;
	if(Defender->HP < 0 )Defender->HP=0;
	return Damage2;
}

// �U�����̃X�e�[�^�X�@�h�䑤�̃X�e�[�^�X�@���͂̎n�܂�@���͂̏I���@���ɍs��move�̐��l�@�G�̔ԍ��@�O��Z�L�[���g�����������������ۂ�
int DamageCalc3( Character_t *Attacker, Character_t *Defender, int StartLog, int EndLog, int Go, int EnemyType, int Flag){
	// �h�䑤�ɗ^����_���[�W�v�Z
	if( DrawBattleMessage( StartLog, EndLog, BattleMenuString, Damage, EnemyType, Flag ) == 1 ){
		// HP��0�ȉ��̏ꍇ�@�ˏ���
		if( Defender->HP <= 0 )return 1 ;
		// �h�䑤�̃_���[�W�v�Z
		Damage=DamageCalc2( *Defender, Attacker );
		// ���̍s����
		move=Go;
		// �������ڂ̍s���ł������ꍇ�͂����Ń��j���[�ɖ߂�
		if(backmenu==1)move=1 ;
		backmenu=1;
	}
	return 0;
}