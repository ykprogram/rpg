//���̃t�@�C���ł́A�퓬�ɓ���O���[�r�[�I�Ȃ��̂����邽�߂̃t�@�C���ł��B
#include "DxLib.h"
#include "../UsePrototype.h"
#include "Before_Battle.h"

static char timer=0;//���b�Ԑ퓬�O�̃��[�r�[���Đ����邩
static int Rand=0;
static int Graphx[16],Graphy[16],copy[16];

//��ʂ��R�s�[���邽�߂ɕ`�挳�ɂȂ���̂����
void Before_Battle_Ini(){
	for(char i=0;i<4;i++)for(char j=0;j<4;j++)copy[i*4+j] = MakeGraph( ScreenWidth/4, ScreenHeight/4 ) ;//16�摜�i�[�f�[�^�����B
}

//�퓬�ɓ���O�ɉ�ʂ��R�s�[
void Set_Before_BattleMovie(){
	for(char i=0;i<4;i++)for(char j=0;j<4;j++){
		GetDrawScreenGraph( (640/4)*j, (480/4)*i, (640/4)*(j+1), (480/4)*(i+1), copy[i*4+j] ) ;
		Graphx[i*4+j]=640/4*j;//�`�悷��e�����W
		Graphy[i*4+j]=480/4*i;//�`�悷��e�����W
	}
	//���̎��_�łǂ̉��o�����邩���߂�
	Rand=GetRand(1);
}
// EnemyType�͏o������G��I�Ԃ��߂̂���
int BeforeBattleMgr(int *EnemyType){
	PlayBGM(battle);
	switch(Rand){
	case 0:BeforeBattleMovie();break;
	case 1:BeforeBattleMovie1();break;
	}
	timer++;
	//�����ŏ����������ł��B
	if(timer==125){
		timer=0;
		*EnemyType=GetRand(1);//�����œG�𒊑I����
		return 4;
	}
	return 3;
}

//�^�񒆂���̊O��
void BeforeBattleMovie(){
	//����
	Graphx[0]+=12;
	Graphy[0]+=9;
	Graphx[1]+=4;
	Graphy[1]+=9;
	Graphx[4]+=12;
	Graphy[4]+=4;
	Graphx[5]+=4;
	Graphy[5]+=3;
	//�E��
	Graphx[2]-=4;
	Graphy[2]+=9;
	Graphx[3]-=12;
	Graphy[3]+=9;
	Graphx[6]-=4;
	Graphy[6]+=3;
	Graphx[7]-=12;
	Graphy[7]+=4;
	//����
	Graphx[8]+=12;
	Graphy[8]-=4;
	Graphx[9]+=4;
	Graphy[9]-=3;
	Graphx[12]+=12;
	Graphy[12]-=9;
	Graphx[13]+=4;
	Graphy[13]-=9;
	//�E��
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
	//���S�܂ł̒���20
}

//���񂾂񏬂���������
void BeforeBattleMovie1(){
	for(int i=0;i<16;i++)DrawExtendGraph( Graphx[i]+0.64*timer, Graphy[i]+0.48*timer, Graphx[i]+160-timer*0.64, Graphy[i]+120-timer*0.48, copy[i], TRUE ) ;
}