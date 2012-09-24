#include "DxLib.h"
#include "../UsePrototype.h"
#include "StoryMgr.h"
#include "../KeyBoard.h"
#define MAX_STORY_LOG 8

Story_t Story[MAX_STORY_LOG]={
	{ 40, 480, "���炷���͍Ăы󗓂ɂȂ�܂���"},
	{ 40, 480*2-100, "����ȏ㌩�ĂĂ��ω��͓��ɂ���܂���"},
	{ 40, 480*3-100*2, "�V�i���I�͂�"},
	{ 40, 480*4-100*3, "�Ƃ����悤�ɂ����͂Ԃ₫�̏�ƂȂ��Ă���܂�"},
	{ 40, 480*5-100*4, "������`�[�Y"},
	{ 40, 480*6-100*5, "BGM��SE���~������"},
	{ 40, 480*7-100*6, "�G�N�X�^�V�B�B�B�B�B�C�C�C�C�C�I�I"},
	{480, 450, "(Z�ŃX�L�b�v����)"}
}; 
static int MovieGraphHandle ;
void TestStoryIni(){

	//MovieGraphHandle = LoadGraph( "RPG DATA\\Produced(ykprogram ver).wmv" ) ;

	//PlayMovieToGraph( MovieGraphHandle ) ;
}
//�X�g�[���[�̊Ǘ�
int StoryMgr(){
	DrawGraph( 0, 0, MovieGraphHandle, TRUE ) ;
	PlayBGM(opening);
	for(int i=0; i<MAX_STORY_LOG-1 ;i++){
		Story[i].y-=1;
		DrawFormatString( Story[i].x, Story[i].y, GetColor(255,255,255), Story[i].story );
	}
	DrawFormatString( Story[MAX_STORY_LOG-1].x, Story[MAX_STORY_LOG-1].y, GetColor(255,255,255), Story[MAX_STORY_LOG-1].story );
	if( Story[MAX_STORY_LOG-2].y<-60 || CheckHitKey2(KEY_INPUT_Z) )return 1;
	return 0;
}