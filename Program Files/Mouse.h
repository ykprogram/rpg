#ifndef EDF_MOUSE_H

#define EDF_MOUSE_H

typedef struct{
	int MouseX, MouseY;			//À•WŠi”[
	int Graph;					//‰æ‘œŠi”[
}Mouse_t;

	#ifdef MOUSE_PROTOTYPE

	void Mouse_Ini( Mouse_t *Mouse );
	void Mouse_Draw( Mouse_t *Mouse );

	#endif //MOUSE_PROTOTYPE

#endif