//���̃t�@�C���ł̓}�b�v�Ɋւ���֐��������Ă���܂�
#include "DxLib.h"
#include "../UsePrototype.h"
#include "Map.h"

//�����Ő��l�̏�����(Ini�ł���������ƍs����������)
Building_t Building[1]={
	{130,130,0,0,0,0}
};

static int BackGroundGraph[3];

static char BackGround[2][WorldY][WorldX]={
	{//�ŏ��̃t�B�[���h
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }
	},
	{//���̃t�B�[���h(�ꉞ���ꂪ��̒��ɂȂ�ݒ�)
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
	}
};



//�����Ŕw�i��ǉ��ł��܂�
void BackGround_Ini(){
	BackGroundGraph[0] = LoadGraph("RPG DATA\\sougen1.png");// �Â��ق��̑���
	BackGroundGraph[1] = LoadGraph("RPG DATA\\sougen2.png");// ���邢�ق��̑���

	Building[0].Graph =LoadGraph("RPG DATA\\castle.png"); // ��̓ǂݍ���
}

//FieldNumber�͂R�̔z��̍ŏ��ł���
void DrawBackGround( Map_t Map, int FieldNumber ){
	//BackGround�ɂ�����0�ƂȂ��Ă���Ƃ����Graphic[0]��w�i�ɂ���Ƃ������Ƃł��B
	if(BackGround[FieldNumber][Map.MapY][Map.MapX]==0)DrawGraph( 0, 0, BackGroundGraph[0], FALSE ) ;
	if(BackGround[FieldNumber][Map.MapX][Map.MapY]==1)DrawGraph( 0, 0, BackGroundGraph[1], FALSE ) ;
}
//�}�b�v�ɏo����_���W������`�悵�����蔻���݂���
void DrawBuilding(Map_Player_t Player, Map_t Map, int *FieldNumber){
	if((*FieldNumber==Building[0].MapNum)&&(Map.MapX==Building[0].MapX)&&(Map.MapY==Building[0].MapY)){
		DrawGraph(Building[0].x, Building[0].y, Building[0].Graph, TRUE);
		if(Player_Hantei( Player, Building[0].x, Building[0].y, Building[0].Graph )==1)*FieldNumber=1;
	}
}