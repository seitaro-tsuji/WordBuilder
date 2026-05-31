#include "DxLib.h"
#include "allfunc.h"
#include "allvari.h"

//文字の形を数値データで得る関数
void Getlitterdata(char str[3], int litdata[littersize][littersize]) {
	SetDrawScreen(DX_SCREEN_FRONT);	//描画先を表画面にする

	fonthandle = CreateFontToHandle("メイリオ", littersize, 3, DX_FONTTYPE_NORMAL);     //フォントハンドルを作成
	DrawStringToHandle(0, 0, str, white, fonthandle);	//strを画面に出力する

	SaveDrawScreenToBMP(0, 0, littersize, littersize, "画像/文字.bmp");    //文字strを画像データに出力
	litterdatahandle = LoadSoftImage("画像/文字.bmp");	//文字.bmpを読み込む
	DrawBox(0, 0, 32, 32, black, TRUE);		//文字を見えなくしておく

	SetDrawScreen(DX_SCREEN_BACK);	//描画先を裏画面に戻す

	for (i = 0; i < littersize; i++) {
		for (j = 0; j < littersize; j++) {
			GetPixelSoftImage(litterdatahandle, j, i, &r, &g, &b, &a);	//ピクセルごとに画素の取得
			if (r)
				litdata[i][j] = 3;		//画素(r要素)が0でないなら3を格納
			else
				litdata[i][j] = 0;		//画素が0なら0を格納
		}
	}
	DeleteSoftImage(litterdatahandle);
}