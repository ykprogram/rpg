#ifndef DEF_MAP_MENU_H

#define DEF_MAP_MENU_H

//マップで出るメニューの構造体
typedef struct{
	int x,y,Graph;
	char Flag;
} MapMenu_t;

	#ifdef MAPMENU_PROTOTYPE

	#include "../Function.h"
	#include "../Battle Phase/Battle.h"
	#include "Map_Player.h"
	void Menu_Ini();
	int Menu( Character_t Character, Map_t Map, int *FieldNumber );
	void MainMenu();
	void Search();
	void Item();
	void Magic( Map_t Map,int *FieldNumber );
	void StatusMenu( Character_t Character );

	#endif //MAPMENU_PROTOTYPE

#endif //DEF_MAP_MENU_H END