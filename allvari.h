#pragma once
#ifndef ALLVARI_H
#define ALLVARI_H

#define littersize	40		//ピクセル単位で文字のサイズ(デフォルトなら17がベスト)
#define masusize	10		//1マスの一辺のピクセル数
#define Title_num	3		//タイトル画面での選択肢数
#define EasyClear	3		//初級クリアの処理をするエリアナンバー
#define NormalClear	9		//中級クリアの処理をするエリアナンバー
#define HardClear	17		//上級クリアの処理をするエリアナンバー
#define EXTRAClear	23		//EXTRAクリアの処理をするエリアナンバー

//構造体player_t
typedef struct {
	int x;			//x座標
	int y;			//y座標
	int m;			//マップナンバー
	int life_flag;	//1ならライフが適用されるフラグ(中級以上で1)
	int y_past;		//1フレーム前のy座標(原因不明のバグが起こるのでその対策)
	int jamp;		//ジャンプ状態を表す変数
	int jamp_phase;	//ジャンプフェーズ
	int image;		//画像
	int action;		//行動
	int life;		//ライフ
	int wp;			//wordpoint 文字を入力できる残り回数
	int check;		//回収したチェックポイントの数
	int extra_flag;	//EXTRA開放フラグ　上級クリアで1になる
}player_t;

static int i, j, k;	//ループ文用
static int r, g, b, a;	//画素取得用
static int white = GetColor(255, 255, 255);	//白色のデータ
static int black = GetColor(0, 0, 0);		//黒色のデータ
static int red = GetColor(255, 0, 0);		//赤色のデータ
static int yellow = GetColor(255, 255, 0);	//黄色のデータ
static int blue = GetColor(0, 0, 255);		//青色のデータ
static int l_blue = GetColor(24, 235, 249);	//水色のデータ
static int gray = GetColor(128, 128, 128);	//灰色のデータ
static int green = GetColor(0, 255, 0);		//緑色のデータ
static int l_green = GetColor(0, 180, 0);	//薄緑のデータ
static int green2 = GetColor(42, 211, 56);	//明緑のデータ
static int pink = GetColor(255, 128, 128);	//桃色のデータ
static int litinputhandle;
static char inputlitter[30];	//入力された文字データ(これの後ろ2枠をlitterにする)
static char litter[3];	//文字のデータ(全角1文字分)
static int litterdata[littersize][littersize];	//文字のデータ(0と1で表現)
static int litterdatahandle;				//文字データのハンドルloadsoftimage用
static int fonthandle;
static player_t player;		//プレイヤーに関する変数の構造体
static int x, y;
static int start;		//スタート地点のy座標
static int goal_high;	//ゴールできるy座標(上)
static int goal_low;		//ゴールできるy座標(下)
static int check_num;	//チェックポイントの総数
static int wp_max;		//WPの最大値
static char GameTitle[128];		//ゲームのタイトル
static int title_cursor;	//タイトル画面で使うカーソル
static int title_pal;
static int start_step;		//タイトル→ゲームスタートの時の暗転用
static int extra_flag;		//EXTRAフラグ(上級クリアで1になる)
static int map_cursor;		//マップ画面で使うカーソル
static int game_step;		//ゲームのステップ(0:タイトル画面　1:初級ステージ)
static int font_title1;		//タイトル画面のタイトル表示用のフォント
static int font_title2;		//タイトル画面のステージ表示用のフォント
static int font_small;		//小さいフォント
static int font_clear;		//クリア画面のフォント
static int life_re;			//Cキー押した時用、残りライフを記録する
static int wp_re;			//Cキー押した時用、残りWPを記録する
static int ex_flag;		//説明の表示フラグ
static int erea_flag;	//エリア移動フラグ
static int ec_step;		//エリアチェンジのステップ
static int death_flag;	//死亡したときに1にするフラグ
static int return_flag;	//タイトルに戻るフラグ
static int massage_flag;//メッセージを表示するフラグ
static char m_str[1280];	//メッセージ
static int mapdata[480 / masusize][640 / masusize];		//マップのデータ(数値)
static int cnt;		//1フレームで1増えるcount
static int chara_image[4];	//キャラクターの画像セット
static int black_image;		//真っ黒な画面の画像
static int heart;			//ハートの画像
static int heart5;			//ハート5の画像
static int clear_massage;	//クリアメッセージのハンドル
static int pal;				//暗転時のαブレンドのパラメータ
static int next_map;		//エリア移動先のマップナンバー
static int fall_y;			//落下したy座標
static int image;
static int PAD1;
#endif