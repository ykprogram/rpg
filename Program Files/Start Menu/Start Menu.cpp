#include "DxLib.h"
#include "../UsePrototype.h"
#include "Start Menu.h"
#include "../KeyBoard.h"

// ���j���[���ڗv�f��5���
MenuElement_t MenuElement[5]={
	// �^�O�̒��g�̏��ԂŊi�[�����Bx��80���Ay��100���Aname��"�Q�[���X�^�[�g"������
	{  80, 100, 100, 80, GetColor(255,255,255), 255, 255, 255,"�Q�[���X�^�[�g" }, 
	{ 100, 150, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"���܂�" },
	{ 100, 200, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"�w���v" },
	{ 100, 250, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"�R���t�B�O" },
	{ 100, 300, 100, 80, GetColor(255,255,255), 255/2, 255/2, 255/2,"�Q�[���I��" },
};

//int MenuBackGround;
void Start_BackGraph(){
	//���j���[��ʂ̉摜�����[�h
	//MenuBackGround= LoadGraph("RPG DATA\\google.png");
}

int StartMenu(){
	for(int i=0;i<5; i++)DrawBox( MenuElement[i].x, MenuElement[i].y, MenuElement[i].x+18, MenuElement[i].y+18, GetColor( 255, 0, 0 ), FALSE) ;
	//DrawGraph(240,40,MenuBackGround,TRUE);
	DrawFormatString( 320, 240, GetColor( 255, 255, 255 ), "ver3.00");
	switch( DrawMenu( 5, 1, KEY_INPUT_Z, MenuElement ) ){
	case 0:return 2;	// �Q�[���X�^�[�g
	case 4:return 1000; // �Q�[���I��
	}
	return 1;

}