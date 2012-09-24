//このファイルは自作関数が載ってます
#include "DxLib.h"
#include "UsePrototype.h"
#include "Function.h"

static short colorR=255, colorG=0, colorB=0;

static int FontNumHandle[10];

FunctionGraph_t FunctionGraph;

//フォントを読み込む
void Function_Ini(){
	LoadDivGraph( "RPG DATA\\font.png", 10, 10, 1, 12, 16, FontNumHandle ) ;
	FunctionGraph.Graph = LoadGraph("RPG DATA\\message.png");
}

//虹色表示
DWORD GetRainbowColor(){
	if(colorR==0)if(colorG==255)colorB +=3;
	if(colorR==0)if(colorB==255)colorG -=3;
	if(colorR==255)if(colorB==0)colorG +=3;
	if(colorG==255)if(colorB==0)colorR -=3;
	if(colorG==0)if(colorB==255)colorR +=3;
	if(colorR==255)if(colorG==0)colorB -=3;
	return GetColor(colorR,colorG,colorB);
}	

//画像を虹色で描画する関数、フラグで背景を透過処理するかしないかを決められる
void RainbowDrawGraph(int x,int y, int Handle, int Flag){
	//ここから
	if(colorR==0)if(colorG==255)colorB +=3;
	if(colorR==0)if(colorB==255)colorG -=3;
	if(colorR==255)if(colorB==0)colorG +=3;
	if(colorG==255)if(colorB==0)colorR -=3;
	if(colorG==0)if(colorB==255)colorR +=3;
	if(colorR==255)if(colorG==0)colorB -=3;
	//ここまでが虹色を出すための数値の変化

	// 描画輝度を虹色にセット
	SetDrawBright( colorR, colorG, colorB ) ;
	// グラフィックの描画
	DrawGraph( x, y, Handle, Flag ) ;
	//これがないとすべての描画処理が虹色になってしまう
	SetDrawBright( 255, 255, 255 ) ;
}

// 数値をグラフィック表示する関数
void FontNumDraw( int x, int y,int FontNum )
{
	// Numが十進数で何桁になるか調べる
	char  BeamWidth= 0 ;
	for( short i = 10 ; FontNum >= i ; i *= 10 ) BeamWidth ++ ;

	// 画面左上にグラフィックで描画
	// x は数字グラフィックを描く矩形の左端の座標です
	x += BeamWidth * 12 ;	

	for( char i = 0 ; i <= BeamWidth ; i ++ )
	{
		//%は割った時のあまりだぞー
		DrawGraph( x, y, FontNumHandle[ FontNum % 10 ], TRUE ) ;
		x -= 12 ;// 描画Ｘ座標を移動
		FontNum /= 10 ;// １番下の桁が描画し終わったので一桁下げる
	}
}

//二つの画像の当たり判定を接触していれば1,していなければ0を返す
int Hantei( int x, int y, int handle, int x2, int y2, int handle2 ){
	int w, w2, h, h2;
	// それぞれの画像の横幅を調べる
	GetGraphSize( handle, &w, &h ) ;
	GetGraphSize( handle2, &w2, &h2 ) ;
	//当たり判定
	if((x < x2 + w2) && (x + w > x2) && (y < y2 + h2) && (y + h > y2))return 1;//接触している場合は１を返す
	else return 0;//接触していない場合は0を返す
}

//プレイヤーと二つ目の画像の当たり判定を接触していれば1,していなければ0を返す
int Player_Hantei( Map_Player_t Player, int x, int y, int handle ){
	int w, h;
	// それぞれの画像の横幅を調べる
	GetGraphSize( handle, &w, &h ) ;
	//当たり判定
	if((Player.x < x + w) && (Player.x + Player.w > x) && (Player.y < y + h) && (Player.y + Player.h > y))return 1;//接触している場合は１を返す
	else return 0;//接触していない場合は0を返す
}

//下に出るメッセージの枠を表示する
void MessageFrame(){
	DrawGraph(0,480-125,FunctionGraph.Graph,TRUE);
}

// これから気になったこと更新することなどここに書いていきます
// 実行してからの処理は各自この関数から帰ってくる数値をご利用ください
// 返す値リスト
// 0 3
// 1 4
// 2 5
// 縦の個数, 横の個数, 文字列の構造体

static short SelectNum = 0, SelectNum2 = 0; // 現在の選択番号( ﾟ∀ﾟ)ｱﾊﾊ八八ﾉヽﾉヽﾉヽﾉ ＼ / ＼/ ＼
static int Ini_end=0;
int DrawMenu(int ElementMaxY, int ElementMaxX, int KeyCode, MenuElement_t Menu[]){
	// 計算フェーズ 

	// 下,上,右キーが押された瞬間だけ処理
	if( CheckHitKey2( KEY_INPUT_DOWN )  == 1 ){PlaySE(select2);SelectNum = ( SelectNum + 1 ) % ElementMaxY;}				// 現在の選択項目を一つ下にずらす(ループする)
	if( CheckHitKey2( KEY_INPUT_UP ) == 1 ){PlaySE(select2);SelectNum = ( SelectNum + ElementMaxY - 1 ) % ElementMaxY;}	// 現在の選択項目を一つ上にずらす(逆ループする)
	if( CheckHitKey2( KEY_INPUT_RIGHT ) == 1 ){PlaySE(select2);SelectNum2 = (SelectNum2 + 1)% ElementMaxX ;}				// 現在の選択項目を一つ右にずらす(ループする)
	if( CheckHitKey2( KEY_INPUT_LEFT ) == 1 ){PlaySE(select2);SelectNum2 = (SelectNum2 + ElementMaxX - 1)%ElementMaxX;}	// 現在の選択項目を一つ左にずらす(逆ループする)

	if( CheckHitKey2( KEY_INPUT_DOWN ) == 1 || CheckHitKey2( KEY_INPUT_UP ) == 1 || CheckHitKey2( KEY_INPUT_RIGHT ) == 1|| CheckHitKey2( KEY_INPUT_LEFT )==1 ){ // 上下左右キーが押された瞬間
		for(int i=0; i<ElementMaxY; i++ ){              // メニュー項目数である5個ループ処理
			for(int j=0; j<ElementMaxX; j++ ){
				if( i == SelectNum && j == SelectNum2){
					Menu[i+(j*ElementMaxY)].x = Menu[i+(j*ElementMaxY)].ax ;	// 今処理しているのが、選択番号と同じ要素なら,座標をにする
					Menu[i+(j*ElementMaxY)].BrightR = 255 ;
					Menu[i+(j*ElementMaxY)].BrightG = 255 ;
					Menu[i+(j*ElementMaxY)].BrightB = 255 ;
				}else {
					Menu[i+(j*ElementMaxY)].x = Menu[i+(j*ElementMaxY)].bx;		// 今処理しているのが、選択番号以外なら,座標を100にする
					Menu[i+(j*ElementMaxY)].BrightR = 255/2 ;
					Menu[i+(j*ElementMaxY)].BrightG = 255/2 ;
					Menu[i+(j*ElementMaxY)].BrightB = 255/2 ;
				} 
			}
		}
	}

	// 描画フェーズ

	for( int i=0; i<ElementMaxY*ElementMaxX; i++ ){ // メニュー項目を個数分描画
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
		Menu[0].x = Menu[0].ax ;	// 今処理しているのが、選択番号と同じ要素なら,座標をにする
		Menu[0].BrightR = 255 ;
		Menu[0].BrightG = 255 ;
		Menu[0].BrightB = 255 ;
		SelectNum2=0, SelectNum=0;
		return Ini_end;
	}
	return 1000;
}

static char NowNumber=0;
// 会話などを表示する,UseBeforeZが1の場合
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