//このファイルではマウスに関係する処理をするファイルです。
#include "DxLib.h"
#include "UsePrototype.h"
#include "Mouse.h"

void Mouse_Ini( Mouse_t *Mouse ){
	Mouse->Graph = LoadGraph("RPG DATA\\sword.png");
}

void Mouse_Draw( Mouse_t *Mouse ){
	GetMousePoint(&Mouse->MouseX,&Mouse->MouseY);
	DrawGraph(Mouse->MouseX, Mouse->MouseY, Mouse->Graph, TRUE);
}