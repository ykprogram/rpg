#ifndef DEF_MAPPLAYER_H

#define DEF_MAPPLAYER_H

typedef struct{
	int x, y;//�v���C���[�̉摜��xy
	int w, h;//�v���C���[�̉����Əc��
	int Graph[ 12 ];//�摜���i�[���邽�߂̕�
	char PlayerMotion;//��{��Graph[12]�̒��ɓ����B
	char MoveControl;//���ꂪ0�Ȃ瓮���Ă��Ȃ��A1�Ȃ瓮���Ă�
}Map_Player_t;

	#ifdef MAPPLAYER_PROTOTYPE //���̉��ɂ���֐����g��������΍���#define�Ő錾����

	//�����ɂ���include�͍\���̂��g�����߂̂���
	#include "../BeforeBattle/Before_Battle.h"
	#include "../Mouse.h"
	#include "../Define.h"
	#include "Map.h"
	void Map_Player_Ini( Map_Player_t *Player );
	void PlayerUp( Map_Player_t *Player );
	void PlayerDown( Map_Player_t *Player );
	void PlayerRight( Map_Player_t *Player );
	void PlayerLeft( Map_Player_t *Player );
	void PlayerControl_Map( Map_t *Map, Map_Player_t *Player );
	void PlayerMove_Map( Mouse_t Mouse, Map_Player_t *Player );
	int Encounter( Map_Player_t Player );

	#endif		//MAPPLAYER_PROTOTYPE END

#endif//DEF_MAPPLAYER_H END