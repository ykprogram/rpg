#include "DxLib.h"
#include "KeyBoard.h"

static short m_Key[256];  // キーの入力状態格納用変数

// キーの入力状態更新(ぶっちゃけこれを使うのはmain関数内だけでおk)
void AllKey(){
	char tmpKey[256];             // 現在のキーの入力状態を格納する
	GetHitKeyStateAll( tmpKey );  // 全てのキーの入力状態を得る
	// i番のキーコードに対応するキーが押されていたら加算押されていなければ 0にする
	for( int i=0; i<256; i++ )( tmpKey[i] != 0 ) ? m_Key[i]++ : m_Key[i] = 0;
}

// CheckHitKeyの押しっぱなしが出来ない関数,KeyCodeのキーの入力状態を取得する
int CheckHitKey2( int KeyCode ){
	return m_Key[ KeyCode ]; // KeyCodeの入力状態を返す
} 