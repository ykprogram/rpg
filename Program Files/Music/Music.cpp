#include "DxLib.h"
#include "../UsePrototype.h"
#include "Music.h"

Music_t Music[AllBGM];
SE_t SE[AllSE];

void Music_Ini(){
	Music[opening].Music = LoadSoundMem( "RPG DATA\\opening.ogg" );
	Music[battle].Music = LoadSoundMem( "RPG DATA\\sentoukyoku.ogg");

	SE[select].SE = LoadSoundMem("RPG DATA\\select.wav");
	SE[select2].SE = LoadSoundMem("RPG DATA\\select3.wav");
}

//���y�𗬂��Ȃ��Ă����̊֐���ǂݍ��ݐ���
void PlayBGM( int Number ){
	//��������񂾂��ǂݍ���(�Ȃ��w�肳�ꂽnumber�̉��y���Ȃ���΂��̏����͑O�̉��y�����ꑱ����)
	if(CheckSoundMem(Music[Number].Music)==0){
		for(int i=0; i<AllBGM; i++ )StopSoundMem( Music[i].Music ) ;
		PlaySoundMem( Music[Number].Music, DX_PLAYTYPE_LOOP ) ;
	}
}

//���ʉ��e�X�g�i�K
void PlaySE( int Number ){
	PlaySoundMem( SE[Number].SE, DX_PLAYTYPE_BACK) ;
}