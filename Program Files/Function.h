//����֐����g���Ƃ��͂��̃t�@�C�����C���N���[�h����΂悢
//���ꂼ��̊֐��̓�����Function.cpp���Q�l

#ifndef EDF_FUNCTION_H

#define EDF_FUNCTION_H

//function�Ŏg���摜�̃f�[�^
typedef struct{
	int x,y,Graph;
}FunctionGraph_t;

//���j���[�����\��
typedef struct{
	int x,y,color;		// x, y, �F�i�[
	char hyoji[100];	// �����i�[�ϐ� 
}StringScript_t;

// ���j���[���ڂ̕\���ɕK�v�ȍ\���̂�p�ӂ���
typedef struct{
	int x, y;					// ���W�i�[�ϐ�
	int bx,ax;					// �ړ���,�O���W
	int color;					// �F�i�[�ϐ�
	int BrightR,BrightG,BrightB;// ���x�i�[�ϐ�
	char name[128];				// ���ږ��i�[�ϐ�
} MenuElement_t ;


	#ifdef FUNCTION_PROTOTYPE

	#include "Map\Map.h"
	#include "Map\Map_Player.h"
	#include "Map\MapMenu.h"
	#include "Mouse.h"
	#include "Music\Music.h"
	#include "KeyBoard.h"
	#include "Battle Phase\Battle.h"
	void Function_Ini();
	unsigned long GetRainbowColor() ;
	void RainbowDrawGraph(int x,int y,int Handle, int Flag);
	void FontNumDraw( int x, int y, int FontNum );
	int Hantei( int x, int y, int handle, int x2, int y2, int handle2 );
	int Player_Hantei( Map_Player_t Player, int x, int y, int handle );
	void MessageFrame();
	int DrawMenu(int ElementMaxY, int ElementMaxX,  int KeyCode, MenuElement_t Menu[]);
	int DrawMessageString(int Start, int End, StringScript_t MenuString[], int num ,int UseBeforeZ);

	#endif //FUNCTION_PROTOTYPE END

#endif