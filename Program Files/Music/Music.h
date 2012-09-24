#ifndef EDF_MUSIC_H

#define EDF_MUSIC_H

#define opening 0
#define battle  1
#define AllBGM  2

#define select	0
#define select2	1
#define AllSE 2

typedef struct{
	int Music;
}Music_t;

typedef struct{
	int SE;
}SE_t;

	#ifdef MUSIC_PROTOTYPE

	void Music_Ini();
	void PlayBGM( int Number );
	void PlaySE( int Number );

	#endif //MUSIC_PROTOTYPE END

#endif