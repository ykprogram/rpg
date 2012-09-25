//��������ǂݎn�߂܂��B
//switch�̒��ɂ���֐���mgr�̂ق��ɓ����Ă܂��B
//�K���֐����g���Ƃ���UsePrototype.h���C���N���[�h���邱�ƂɂȂ��Ă܂�
#include "DxLib.h"
#include "UsePrototype.h"
#include "Define.h"
#include "Mouse.h"
#include "Function.h"
#include "Start Menu\Start Menu.h"
#include "Map\MapMgr.h"
#include "Map\Map_Player.h"
#include "Battle Phase\Battle.h"
#include "BeforeBattle\Before_Battle.h"
#include "Story\StoryMgr.h"
#include "Music\Music.h"
#include "Map\MapMenu.h"
#include "KeyBoard.h"
#include "Battle Phase\Battle_Player.h"

static char Phase=0;//����Ń��C��switch�𐧌䂷��
static int Enemy=0;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,LPSTR lpCmdLine, int nCmdShow )
{
	Mouse_t Mouse;				// �}�E�X�̎��̐錾
	Map_Player_t Player;		// �v���C���[�̎��̐錾
	Character_t Character;		// �L�����N�^�[�̃X�e�[�^�X�̎��Ԑ錾

	SetGraphMode( ScreenWidth, ScreenHeight, 32 ) ;
	ChangeWindowMode(TRUE), DxLib_Init(), SetDrawScreen( DX_SCREEN_BACK ); // �E�B���h�E���[�h�ύX�Ə������Ɨ���ʐݒ�
	SetMouseDispFlag(TRUE) ;	// �}�E�X��\����Ԃɂ��� 
	DrawFormatString( 0, 0, GetColor(255, 255, 255), "�ǂݍ��ݒ�,Now Loading...") ;
	Before_Battle_Ini();		// �퓬�ɓ���O�̃��[�r�[�̏�����
	Function_Ini();				// Function�̏�����������(�摜)
	Mouse_Ini( &Mouse );		// �}�E�X�̏�����������(�摜)
	Menu_Ini();					// ���j���[�̏�����(�摜)
	BackGround_Ini();			// �w�i�̏�����������(�摜)
	Map_Player_Ini( &Player );	// �v���C���[�̏�����������(�摜)
	//Start_BackGraph();		// �X�^�[�g��ʂ̔w�i��`�悷��
	Battle_Ini();				// �G�̉摜�����[�h
	Battle_Player_Ini( &Character );// �\�͂̏�����
	Music_Ini();				// ���y�̏�����
	TestStoryIni();				// ���܂�������̏�����
	
	
	// while( ����ʂ�\��ʂɔ��f, ���b�Z�[�W����, ��ʃN���A, �G�X�P�[�v��������E�o, Phase��1000������ƒE�o)
	while( ScreenFlip()==0 && ProcessMessage()==0 && ClearDrawScreen()==0 && CheckHitKey( KEY_INPUT_ESCAPE )==0){
		AllKey();									// �����CheckHitKey2���g����悤�ɂȂ��	
		switch(Phase){
		case 0:Phase=StoryMgr();break;				// ���j���[�Ȃ񂾂���Phase�ɑ�����Ă�͕̂Ԃ�l
		case 1:Phase=StartMenu();break;				// �}�b�v���̈ړ������邱�ꂪ0���Ǝ~�܂��Ă��Ă���ȊO���Ɠ����Ă���
		case 2:Phase=MapMgr( Mouse, &Player, Character );Player.MoveControl=0;break;//�Ȃ����}�b�v�����Player���|�C���^�[�ɂ��Ȃ��Ɠ����Ă���Ȃ���
		case 3:Phase=BeforeBattleMgr( &Enemy );break;
		case 4:Phase=Battle( &Character, Enemy );break;
		}
		if(Phase==5)return 0;
		Mouse_Draw( &Mouse );// �����Ń}�E�X�̃|�C���^�[���擾���`�悷��
	}
	DxLib_End(); // DX���C�u�����I������				
	return 0;
} 

		
	//int Music;
	//char handle[100];if(GetDragFilePath( handle )==0)Music = LoadSoundMem( handle );
	//if(CheckHitKey(KEY_INPUT_M))PlaySoundMem( Music, DX_PLAYTYPE_BACK ) ;
	//SetDragFileValidFlag(TRUE);	// D&D���邽�߂̂���