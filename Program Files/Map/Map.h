#ifndef DEF_MAP_H

#define DEF_MAP_H 

#define WorldX 10
#define WorldY 10
//�}�b�v�̍\����
typedef struct{
	int MapX,MapY;
}Map_t;

typedef struct{
	int x,y,Graph;	// ���W�Ɖ摜���i�[����
	int MapX,MapY,MapNum;	// �}�b�v�̍��W���i�[����ϐ�
}Building_t;

	#ifdef MAP_PROTOTYPE //���̉��ɂ���֐����g��������΍���#define�Ő錾����

	#include "../Function.h"
	#include "Map_Player.h"
	void BackGround_Ini();
	void DrawBackGround( Map_t Map, int FieldNumber );
	void DrawBuilding(Map_Player_t Player, Map_t Map,int *FieldNumber);

	#endif //MAP_PROTOTYPE END

#endif //EDF_MAP_H END