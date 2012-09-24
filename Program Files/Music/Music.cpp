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

//音楽を流さなくてもこの関数を読み込み推奨
void PlayBGM( int Number ){
	//処理を一回だけ読み込む(なお指定されたnumberの音楽がなければこの処理は前の音楽が流れ続ける)
	if(CheckSoundMem(Music[Number].Music)==0){
		for(int i=0; i<AllBGM; i++ )StopSoundMem( Music[i].Music ) ;
		PlaySoundMem( Music[Number].Music, DX_PLAYTYPE_LOOP ) ;
	}
}

//効果音テスト段階
void PlaySE( int Number ){
	PlaySoundMem( SE[Number].SE, DX_PLAYTYPE_BACK) ;
}