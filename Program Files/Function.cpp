//���̃t�@�C���͎���֐����ڂ��Ă܂�
#include "DxLib.h"
#include "UsePrototype.h"
#include "Function.h"

static short colorR=255, colorG=0, colorB=0;

static int FontNumHandle[10];

FunctionGraph_t FunctionGraph;

//�t�H���g��ǂݍ���
void Function_Ini(){
	LoadDivGraph( "RPG DATA\\font.png", 10, 10, 1, 12, 16, FontNumHandle ) ;
	FunctionGraph.Graph = LoadGraph("RPG DATA\\message.png");
}

//���F�\��
DWORD GetRainbowColor(){
	if(colorR==0)if(colorG==255)colorB +=3;
	if(colorR==0)if(colorB==255)colorG -=3;
	if(colorR==255)if(colorB==0)colorG +=3;
	if(colorG==255)if(colorB==0)colorR -=3;
	if(colorG==0)if(colorB==255)colorR +=3;
	if(colorR==255)if(colorG==0)colorB -=3;
	return GetColor(colorR,colorG,colorB);
}	

//�摜����F�ŕ`�悷��֐��A�t���O�Ŕw�i�𓧉ߏ������邩���Ȃ��������߂���
void RainbowDrawGraph(int x,int y, int Handle, int Flag){
	//��������
	if(colorR==0)if(colorG==255)colorB +=3;
	if(colorR==0)if(colorB==255)colorG -=3;
	if(colorR==255)if(colorB==0)colorG +=3;
	if(colorG==255)if(colorB==0)colorR -=3;
	if(colorG==0)if(colorB==255)colorR +=3;
	if(colorR==255)if(colorG==0)colorB -=3;
	//�����܂ł����F���o�����߂̐��l�̕ω�

	// �`��P�x����F�ɃZ�b�g
	SetDrawBright( colorR, colorG, colorB ) ;
	// �O���t�B�b�N�̕`��
	DrawGraph( x, y, Handle, Flag ) ;
	//���ꂪ�Ȃ��Ƃ��ׂĂ̕`�揈�������F�ɂȂ��Ă��܂�
	SetDrawBright( 255, 255, 255 ) ;
}

// ���l���O���t�B�b�N�\������֐�
void FontNumDraw( int x, int y,int FontNum )
{
	// Num���\�i���ŉ����ɂȂ邩���ׂ�
	char  BeamWidth= 0 ;
	for( short i = 10 ; FontNum >= i ; i *= 10 ) BeamWidth ++ ;

	// ��ʍ���ɃO���t�B�b�N�ŕ`��
	// x �͐����O���t�B�b�N��`����`�̍��[�̍��W�ł�
	x += BeamWidth * 12 ;	

	for( char i = 0 ; i <= BeamWidth ; i ++ )
	{
		//%�͊��������̂��܂肾���[
		DrawGraph( x, y, FontNumHandle[ FontNum % 10 ], TRUE ) ;
		x -= 12 ;// �`��w���W���ړ�
		FontNum /= 10 ;// �P�ԉ��̌����`�悵�I������̂ňꌅ������
	}
}

//��̉摜�̓����蔻���ڐG���Ă����1,���Ă��Ȃ����0��Ԃ�
int Hantei( int x, int y, int handle, int x2, int y2, int handle2 ){
	int w, w2, h, h2;
	// ���ꂼ��̉摜�̉����𒲂ׂ�
	GetGraphSize( handle, &w, &h ) ;
	GetGraphSize( handle2, &w2, &h2 ) ;
	//�����蔻��
	if((x < x2 + w2) && (x + w > x2) && (y < y2 + h2) && (y + h > y2))return 1;//�ڐG���Ă���ꍇ�͂P��Ԃ�
	else return 0;//�ڐG���Ă��Ȃ��ꍇ��0��Ԃ�
}

//�v���C���[�Ɠ�ڂ̉摜�̓����蔻���ڐG���Ă����1,���Ă��Ȃ����0��Ԃ�
int Player_Hantei( Map_Player_t Player, int x, int y, int handle ){
	int w, h;
	// ���ꂼ��̉摜�̉����𒲂ׂ�
	GetGraphSize( handle, &w, &h ) ;
	//�����蔻��
	if((Player.x < x + w) && (Player.x + Player.w > x) && (Player.y < y + h) && (Player.y + Player.h > y))return 1;//�ڐG���Ă���ꍇ�͂P��Ԃ�
	else return 0;//�ڐG���Ă��Ȃ��ꍇ��0��Ԃ�
}

//���ɏo�郁�b�Z�[�W�̘g��\������
void MessageFrame(){
	DrawGraph(0,480-125,FunctionGraph.Graph,TRUE);
}

// ���ꂩ��C�ɂȂ������ƍX�V���邱�ƂȂǂ����ɏ����Ă����܂�
// ���s���Ă���̏����͊e�����̊֐�����A���Ă��鐔�l�������p��������
// �Ԃ��l���X�g
// 0 3
// 1 4
// 2 5
// �c�̌�, ���̌�, ������̍\����

static short SelectNum = 0, SelectNum2 = 0; // ���݂̑I��ԍ�( ߁��)��ʔ���ɁRɁRɁR� �_ / �_/ �_
static int Ini_end=0;
int DrawMenu(int ElementMaxY, int ElementMaxX, int KeyCode, MenuElement_t Menu[]){
	// �v�Z�t�F�[�Y 

	// ��,��,�E�L�[�������ꂽ�u�Ԃ�������
	if( CheckHitKey2( KEY_INPUT_DOWN )  == 1 ){PlaySE(select2);SelectNum = ( SelectNum + 1 ) % ElementMaxY;}				// ���݂̑I�����ڂ�����ɂ��炷(���[�v����)
	if( CheckHitKey2( KEY_INPUT_UP ) == 1 ){PlaySE(select2);SelectNum = ( SelectNum + ElementMaxY - 1 ) % ElementMaxY;}	// ���݂̑I�����ڂ����ɂ��炷(�t���[�v����)
	if( CheckHitKey2( KEY_INPUT_RIGHT ) == 1 ){PlaySE(select2);SelectNum2 = (SelectNum2 + 1)% ElementMaxX ;}				// ���݂̑I�����ڂ���E�ɂ��炷(���[�v����)
	if( CheckHitKey2( KEY_INPUT_LEFT ) == 1 ){PlaySE(select2);SelectNum2 = (SelectNum2 + ElementMaxX - 1)%ElementMaxX;}	// ���݂̑I�����ڂ�����ɂ��炷(�t���[�v����)

	if( CheckHitKey2( KEY_INPUT_DOWN ) == 1 || CheckHitKey2( KEY_INPUT_UP ) == 1 || CheckHitKey2( KEY_INPUT_RIGHT ) == 1|| CheckHitKey2( KEY_INPUT_LEFT )==1 ){ // �㉺���E�L�[�������ꂽ�u��
		for(int i=0; i<ElementMaxY; i++ ){              // ���j���[���ڐ��ł���5���[�v����
			for(int j=0; j<ElementMaxX; j++ ){
				if( i == SelectNum && j == SelectNum2){
					Menu[i+(j*ElementMaxY)].x = Menu[i+(j*ElementMaxY)].ax ;	// ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�,���W���ɂ���
					Menu[i+(j*ElementMaxY)].BrightR = 255 ;
					Menu[i+(j*ElementMaxY)].BrightG = 255 ;
					Menu[i+(j*ElementMaxY)].BrightB = 255 ;
				}else {
					Menu[i+(j*ElementMaxY)].x = Menu[i+(j*ElementMaxY)].bx;		// ���������Ă���̂��A�I��ԍ��ȊO�Ȃ�,���W��100�ɂ���
					Menu[i+(j*ElementMaxY)].BrightR = 255/2 ;
					Menu[i+(j*ElementMaxY)].BrightG = 255/2 ;
					Menu[i+(j*ElementMaxY)].BrightB = 255/2 ;
				} 
			}
		}
	}

	// �`��t�F�[�Y

	for( int i=0; i<ElementMaxY*ElementMaxX; i++ ){ // ���j���[���ڂ������`��
		SetDrawBright(Menu[i].BrightR,Menu[i].BrightG,Menu[i].BrightB);
		DrawFormatString( Menu[i].x, Menu[i].y, Menu[i].color, Menu[i].name );
		SetDrawBright(255,255,255);
	}
	DrawFormatString( 0, 0, GetColor(255,255,255), "%d", SelectNum );
	DrawFormatString( 0, 20, GetColor(255,255,255), "%d", SelectNum2 );

	if(CheckHitKey2(KeyCode)==1){
		Ini_end = SelectNum2 * ElementMaxY + SelectNum;
		Menu[SelectNum+(SelectNum2*ElementMaxY)].x = Menu[SelectNum+(SelectNum2*ElementMaxY)].bx;
		Menu[SelectNum+(SelectNum2*ElementMaxY)].BrightR = 255/2 ;
		Menu[SelectNum+(SelectNum2*ElementMaxY)].BrightG = 255/2 ;
		Menu[SelectNum+(SelectNum2*ElementMaxY)].BrightB = 255/2 ;
		Menu[0].x = Menu[0].ax ;	// ���������Ă���̂��A�I��ԍ��Ɠ����v�f�Ȃ�,���W���ɂ���
		Menu[0].BrightR = 255 ;
		Menu[0].BrightG = 255 ;
		Menu[0].BrightB = 255 ;
		SelectNum2=0, SelectNum=0;
		return Ini_end;
	}
	return 1000;
}

static char NowNumber=0;
// ��b�Ȃǂ�\������,UseBeforeZ��1�̏ꍇ
int DrawMessageString(int Start, int End, StringScript_t MenuString[], int num, int UseBeforeZ){
	if(End<NowNumber+Start+UseBeforeZ){ NowNumber=0;return 1; }
	for( int i=Start; i<(NowNumber+Start+UseBeforeZ); i++){
		DrawFormatString(MenuString[i].x,MenuString[i].y,MenuString[i].color,MenuString[i].hyoji,num);
		DrawFormatString(0,200+(i*20),GetRainbowColor(),"%d",i);
	}
	DrawFormatString(40,200,GetRainbowColor(),"%d",NowNumber);
	if(CheckHitKey2(KEY_INPUT_Z)==1)NowNumber++;
	return 0;
}