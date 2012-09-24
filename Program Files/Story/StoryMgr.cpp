#include "DxLib.h"
#include "../UsePrototype.h"
#include "StoryMgr.h"
#include "../KeyBoard.h"
#define MAX_STORY_LOG 8

Story_t Story[MAX_STORY_LOG]={
	{ 40, 480, "あらすじは再び空欄になりました"},
	{ 40, 480*2-100, "これ以上見てても変化は特にありません"},
	{ 40, 480*3-100*2, "シナリオはよ"},
	{ 40, 480*4-100*3, "というようにここはつぶやきの場となっております"},
	{ 40, 480*5-100*4, "さけるチーズ"},
	{ 40, 480*6-100*5, "BGMやSEも欲しいね"},
	{ 40, 480*7-100*6, "エクスタシィィィィィイイイイイ！！"},
	{480, 450, "(Zでスキップする)"}
}; 
static int MovieGraphHandle ;
void TestStoryIni(){

	//MovieGraphHandle = LoadGraph( "RPG DATA\\Produced(ykprogram ver).wmv" ) ;

	//PlayMovieToGraph( MovieGraphHandle ) ;
}
//ストーリーの管理
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