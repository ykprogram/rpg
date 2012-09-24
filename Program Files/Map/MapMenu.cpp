#include "DxLib.h"
#include "../UsePrototype.h"
#include "MapMenu.h"
#include "../KeyBoard.h"

//�܂�\���������郁�j���[�̌���2�Ƃ������ƁB
//����,��ʂɉ摜��\����������肪�Ȃ��Ă����̊֐����g������
MapMenu_t MapMenu[5]={
	{  0, 0, 0, 0  },		// 4�̑I����ʂ̉摜

	{  0, 0,  0, 0 },		// ���ׂ�R�}���h
	{ 20, 20, 0, 0 },		// �A�C�e���R�}���h
	{  0, 0,  0, 0 },		// �����R�}���h
	{ 20, 20, 0, 0 }		// �X�e�[�^�X�\�����
};

// ���j���[���ڗv�f��4��郁�j���[�ɕ\�������镶��
MenuElement_t MenuElement2[4]={
	{36, 30, 36, 36, GetColor(255,255,255), 255, 255, 255, "���ׂ�"},
	{36, 80, 36, 36, GetColor(255,255,255), 255/2, 255/2, 255/2, "�A�C�e��"},
	{36, 130, 36, 36, GetColor(255,255,255), 255/2, 255/2, 255/2, "����"},
	{36, 180, 36, 36, GetColor(255,255,255), 255/2, 255/2, 255/2, "����"}
};

StringScript_t MenuString[3]={
	{20,480-125+20,GetColor(255,0,255),"�E�҂͂�����𒲂ׂ�"},
	{20,480-125+20+20,GetColor(255,0,255),"�����ɕς�����Ƃ���͂Ȃ��悤��"},
	{20,480-125+20+20+20,GetRainbowColor(),"�\���o�͒�"}
};

//�}�b�v�̃��j���[�����[�h����
void Menu_Ini(){
	MapMenu[0].Graph = LoadGraph("RPG DATA\\menu.png");
	MapMenu[4].Graph = LoadGraph("RPG DATA\\menu2.png");
}

// �}�b�v�ł̃��j���[��S������(�����̕Ԃ�l��0�Ȃ烁�j���[���\������Ă��Ȃ�1�Ȃ�\������Ă���B)
// �������ŏ��ɓǂݍ���MainMenu()���悶��Ȃ���
int Menu( Character_t Character, Map_t Map, int *FieldNumber ){

	if( CheckHitKey2( KEY_INPUT_C )== 1)if(MapMenu[0].Flag==0)MapMenu[0].Flag=1;

	if( MapMenu[0].Flag==1 )MainMenu();					// ���j���[���J�������̏���,�����őI��
	if( MapMenu[1].Flag==1 )Search();					// ���ׂ�̓���
	if( MapMenu[2].Flag==1 )Item();						// �A�C�e���̓���
	if( MapMenu[3].Flag==1 )Magic( Map, FieldNumber);	// �����̓���
	if( MapMenu[4].Flag==1 )StatusMenu( Character );	// �X�e�[�^�X��ʂ̕`��

	//�폜�̏����͂���
	if( CheckHitKey2( KEY_INPUT_X )== 1 && MapMenu[1].Flag!=1 )for( int i=0;i<5;i++)MapMenu[i].Flag=0;

	//���j���[���\������Ă���Ƃ��͗E�҂𓮂����Ȃ��Ƃ�������
	//�Ȃ�MapMenu[0]�������Ƃ����Ƃ��ꂪ�g�b�v��ʂȂ̂ł����Əo�������B
	//�K�����j���[��`�悵�Ă���Ƃ��͂��̃t���O�͂P
	if(MapMenu[0].Flag==1)return 1;

	return 0;

}


//���j���[��ʂ�\��
void MainMenu(){
	//�S�̍��ڂ��ǂ���J���Ă��Ȃ�������
	if(MapMenu[1].Flag != 1 && MapMenu[2].Flag != 1 && MapMenu[3].Flag != 1 && MapMenu[4].Flag != 1){
		// ���j���[���ڂ�`��
		DrawGraph( MapMenu[0].x, MapMenu[0].y, MapMenu[0].Graph, TRUE );
		MapMenu[ DrawMenu( 4, 1, KEY_INPUT_Z, MenuElement2 ) + 1 ].Flag=1;
	}
}




//���ׂ�R�}���h
void Search(){
	MessageFrame();
	//�������������ׂĕ\�����I������߂�
	if( DrawMessageString( 0, 3, MenuString, 0, FALSE ) == 1 )MapMenu[1].Flag=0;
}

//�A�C�e���R�}���h
void Item(){
	DrawGraph( MapMenu[2].x, MapMenu[2].y, MapMenu[0].Graph, TRUE);
	DrawFormatString(20+15,20+20,GetColor(255,255,255),"�����Ă��܂���");
}

// �����R�}���h
void Magic( Map_t Map ,int *FieldNumber){
	DrawFormatString(0,0,GetRainbowColor(),"��");
	if(CheckHitKey2(KEY_INPUT_Z)==1)*FieldNumber=0;
}

//�X�e�[�^�X��\���i�����R�}���h�j
void StatusMenu( Character_t Character ){
	DrawGraph(MapMenu[4].x,MapMenu[4].y,MapMenu[4].Graph,TRUE);
	FontNumDraw(120,38,Character.LEVEL);
	FontNumDraw(120,69,Character.HP);
	FontNumDraw(120,99,Character.MP);
	FontNumDraw(120,129,Character.Power);
	FontNumDraw(120,162,Character.Defense);
	FontNumDraw(120,195,Character.Money);
}