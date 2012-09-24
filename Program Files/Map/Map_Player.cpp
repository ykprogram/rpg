//���̃t�@�C���ł̓}�b�v�ɂ���v���C���[�̎�ȏ������s���t�@�C���ł��B
#include "DxLib.h"
#include "../UsePrototype.h"
#include "Map_Player.h"

static int a=0;		//�����グ�Ă�Ƃ��Ȃǂ̃��[�V������\���̂Ɏg��

void Map_Player_Ini( Map_Player_t *Player ){
	Player->x=ScreenWidth/2;   
	Player->y=ScreenHeight/2;
	Player->PlayerMotion=0;
	Player->MoveControl=0;
	LoadDivGraph( "RPG DATA\\RPG�R�m2.png", 12, 4, 3, 45, 45, Player->Graph ) ;
	GetGraphSize( Player->Graph[ Player->PlayerMotion ], &Player->w, &Player->h ) ;
}

//�ȉ��l�̓v���C���[�̓����B�����グ��Ƃ������삪�Ȃ��E�E�E�B
void PlayerUp( Map_Player_t *Player ){
	a++;
	Player->y-=4;
	Player->PlayerMotion=1;
	Player->MoveControl=1;
}
void PlayerDown( Map_Player_t *Player ){
	a++;
	Player->y+=4;
	Player->PlayerMotion=0;
	Player->MoveControl=1;
}
void PlayerRight( Map_Player_t *Player ){
	a++;
	Player->x+=4;
	Player->PlayerMotion=8+(a/8%4);
	Player->MoveControl=1;
}
void PlayerLeft( Map_Player_t *Player ){
	a++;
	Player->x-=4;
	Player->PlayerMotion=4+(a/8%4);
	Player->MoveControl=1;
}

//�v���C���[���}�b�v�ŉ�ʒ[�ɗ������̏��� �����@����E��
void PlayerControl_Map( Map_t *Map, Map_Player_t *Player ){
	if(Player->x<=0){
		if(Map->MapX != 0){
			Player->x=ScreenWidth-46;
			Map->MapX--;
			a=0;
		}else Player->x=0;
	}
	if(Player->y<=0){
		if(Map->MapY != 0){
			Player->y=ScreenHeight-46;
			Map->MapY--;
			a=0;
		}else Player->y=0;
	}
	if(Player->x>=ScreenWidth-45){
		if( Map->MapX != 9 ){
			Player->x=1;
			Map->MapX++;
			a=0;
		}else Player->x=ScreenWidth-45;
	}
	if(Player->y>=ScreenHeight-45){
		if( Map->MapY != 9 ){
			Player->y=1;
			Map->MapY++;
			a=0;
		}else Player->y=ScreenHeight-45;
	}
}

//�}�b�v�ł̃v���C���[�̃��[�V�����ƕ`��(�}�E�X�ł�������)
void PlayerMove_Map( Mouse_t Mouse,  Map_Player_t *Player  ){
	DrawGraph( Player->x, Player->y, Player->Graph[ Player->PlayerMotion ], TRUE ) ;

	if( CheckHitKey( KEY_INPUT_UP )==1   && Player->MoveControl==0 )PlayerUp( Player );
	if( CheckHitKey( KEY_INPUT_DOWN )==1 && Player->MoveControl==0 )PlayerDown( Player );
	if( CheckHitKey( KEY_INPUT_RIGHT )==1&& Player->MoveControl==0 )PlayerRight( Player );
	if( CheckHitKey( KEY_INPUT_LEFT )==1 && Player->MoveControl==0 )PlayerLeft( Player );

	//�}�E�X�̍��{�^����������Ă�����(�}�E�X�̏������g���Ă�̂�Main�֐�����Mouse_t�̎��̂������Ă���)
	if( GetMouseInput() & MOUSE_INPUT_LEFT ){
		if( (Player->y - Mouse.MouseY > 5) && (Player->y > Mouse.MouseY) &&  Player->MoveControl==0 )PlayerUp( Player );
		if( (Mouse.MouseY - Player->y > 5) && (Player->y < Mouse.MouseY) &&  Player->MoveControl==0 )PlayerDown( Player );
		if( (Mouse.MouseX - Player->x > 5) && (Player->x < Mouse.MouseX) &&  Player->MoveControl==0 )PlayerRight( Player );
		if( (Player->x - Mouse.MouseX > 5) && (Player->x > Mouse.MouseX) &&  Player->MoveControl==0 )PlayerLeft( Player );
	}
}

//�G���o������m�����ǂ����i�G���J�E���g�j
int Encounter( Map_Player_t Player ){
	//�����Ă��鎞�ɂ����G�̃G���J�E���g���s�� �m��200
	if( Player.MoveControl!=0 && GetRand(200)==0 ){
		Set_Before_BattleMovie();
		return 3;
	}
	if(CheckHitKey2(KEY_INPUT_E)==1){Set_Before_BattleMovie();return 3;}
	return 2;
}