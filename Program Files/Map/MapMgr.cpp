//���̃t�@�C���ł̓}�b�v�̖{�̂��u���Ă���܂�(������main�֐���Map()�Ə����Ɖ��̏����������Ƃ������Ƃł�)
#include "DxLib.h"
#include "../UsePrototype.h"
#include "MapMgr.h"

//����łǂ̃}�b�v��`�悷�邩��I���ł���
//MapNumber=1;�����̂悤�ɂ��ă}�b�v��؂�ւ���
int MapNumber=0;


//�Q�[���������i�ɂ����Ƃ��ɏ����v���g�^�C�v�錾
void Test(Map_t Map,  Map_Player_t Player ){
	DrawFormatString( 0, 0, GetColor(255, 255, 255), "����x���W��%d",Player.x) ;
	DrawFormatString( 0, 20, GetColor(255, 255, 255), "����y���W��%d",Player.y) ;
	DrawFormatString( 0, 40, GetColor(255, 255, 255), "����MapX��%d",Map.MapX) ;
	DrawFormatString( 0, 60, GetColor(255, 255, 255), "����MapY��%d",Map.MapY) ;
}

// �}�b�v�̎��̐錾
Map_t Map;

int MapMgr( Mouse_t Mouse,  Map_Player_t *Player, Character_t Character ){
	DrawBackGround( Map, MapNumber );								//����Ŕw�i��`�悷��B���̐��l�Ń}�b�v�\����؂�ւ���
	DrawBuilding( *Player, Map, &MapNumber);							//��⌚����`��
	if( Menu( Character, Map, &MapNumber ) == 0 )PlayerMove_Map( Mouse, Player );	//������ʂɃ��j���[���\������Ă�����v���C���[�𓮂���(�}�E�X�̏��������������Ă܂�)
	PlayerControl_Map( &Map, Player );								//����ōs���𐧌�����
	FontNumDraw( 300, 200, MapNumber );								//�}�b�v�i���o�[������t�H���g�ŕ\��
	//Test( Map, *Player );											//�Q�[�������������炱�̊֐��͏����܂�
	return Encounter( *Player );									//�G�ɏo������I����,��Main.cpp�ł�Phase��switch�Ń}�b�v��1�Ȃ̂�1����
}