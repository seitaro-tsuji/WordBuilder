#include "DxLib.h"
#include "allfunc.h"
#include "allvari.h"

//ゲーム全体の初期化をする関数
void Game_Initialize(int *gamestep) {
	*gamestep = 0;
	extra_flag = 0;
	font_title1 = CreateFontToHandle("メイリオ", 70, 9, DX_FONTTYPE_ANTIALIASING_EDGE);	//フォントの作成
	font_title2 = CreateFontToHandle("メイリオ", 30, 4, DX_FONTTYPE_ANTIALIASING_EDGE);	//フォントの作成

	image = LoadGraph("画像/棒人間＿静止.png");		//別のファイルでloadgraphしても反映されない?
	black_image = LoadGraph("画像/真っ黒画面.png");
	PAD1 = GetJoypadInputState(DX_INPUT_PAD1);
}

//ウィンドウを表示する関数(ウィンドウ内部は背景の画像を少し薄くする)
void DrawWindow_T(int x1, int y1, int x2, int y2, int frame_flag = 1) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawModiGraph(x1, y1, x2, y1, x2, y2, x1, y2, black_image, TRUE);      //後でこの画像の透過度を変化させることでウィンドウ内部の描写を薄くする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (frame_flag == 1)
		DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), FALSE);
}

//タイトル画面での処理をする関数
void TitleUpdate(player_t* player, int *gamestep, int mapdata[480/masusize][640/masusize]) {
	cnt++;
	extra_flag = player->extra_flag;
	if (ex_flag == 0) {
		if (Keyboard_Get(KEY_INPUT_DOWN) == 1) {	//下キー
			title_cursor = (title_cursor + 1) % (Title_num + extra_flag);
		}
		if (Keyboard_Get(KEY_INPUT_UP) == 1) {		//上キー
			title_cursor = (title_cursor + Title_num + extra_flag - 1) % (Title_num + extra_flag);
		}

		if (Keyboard_Get(KEY_INPUT_Z) == 1 && cnt >= 2) {		//Zキー
			ex_flag = 1;
			cnt = 0;
		}
		//デバック用
		/*if (Keyboard_Get(KEY_INPUT_D) == 1 && cnt >= 2) {		//Dキー
			*gamestep = 1;	//stepを1にする
			player->life = 3;
			player->life_flag = 1;
			mapInitialize(player, mapdata, 17);    //プレイヤーとマップの初期化をする(デバック用)
		}*/
	}
	if (ex_flag == 1) {
		if (Keyboard_Get(KEY_INPUT_Z) == 1 && cnt >= 2) {	//Z
			start_step = 1;		//スタートステップを1にする
			title_pal = 0;		//暗転パラメータは0
		}
		if (Keyboard_Get(KEY_INPUT_X) == 1 && cnt >= 2) {	//X
			ex_flag = 0;
			cnt = 0;
		}
	}
	if (start_step == 1) {
		pal += 8;
		if (pal >= 255) {
			start_step = 2;	//palが255になったら(完全に暗転したら)step2にする
			pal = 0;		//palは0にする
		}
	}
	if (start_step == 2) {	//step2ならゲームスタート
		if (title_cursor == 0) {
			*gamestep = 1;	//stepを1にする
			mapInitialize(player, mapdata, 1);    //プレイヤーとマップの初期化をする
		}
		if (title_cursor == 1) {
			*gamestep = 1;	//stepを1にする
			mapInitialize(player, mapdata, 6);    //プレイヤーとマップの初期化をする
		}
		if (title_cursor == 2) {
			*gamestep = 1;	//stepを1にする
			mapInitialize(player, mapdata, 11);    //プレイヤーとマップの初期化をする
		}
		if (title_cursor == 3) {
			*gamestep = 1;	//stepを1にする
			mapInitialize(player, mapdata, 18);    //プレイヤーとマップの初期化をする
		}
		start_step = 0;	//stepは0に戻す
		ex_flag = 0;	//説明表示フラグも0にする
	}
}

//タイトル画面の描画をする関数
void TitleDraw() {
	DrawStringToHandle(80, 50, "ワードビルダー", l_blue, font_title1);		//タイトルの表示をする

	DrawStringToHandle(400, 200, "初級ステージ", white, font_title2);		//初級ステージ
	DrawStringToHandle(400, 270, "中級ステージ", l_green, font_title2);		//中級ステージ
	DrawStringToHandle(400, 340, "上級ステージ", red, font_title2);		//上級ステージ
	DrawString(370, 206 + title_cursor * 70, "→", white);	//カーソルの表示

	DrawFormatString(20, 400, yellow, "Esc\nZキー\n");
	DrawFormatString(90, 400, yellow, ": ゲーム終了\n: 決定\n");

	DrawGraph(100, 36, image, TRUE);

	//ex_flagが1の時はゲームの説明を表示
	if (ex_flag == 1) {
		DrawWindow_T(80, 60, 560, 420);
		DrawString(300, 380, "Zキー : ゲームスタート\nXキー : 説明画面を閉じる", white);

		if (title_cursor == 0) {
			DrawString(200, 70, "------初級ステージ------", pink);
			DrawString(90, 70, "\n\nゲームが始まったらXキーを押して\n文字を入力しましょう\n\n入力した文字の形になるようにブロックが\nステージに現れます\n\n"
				"入力できるのは漢字を含む全角文字1文字分です\n\n\n白色のブロックは文字入力による水色のブロックを\n重ねると消すことができます", white);
		}
		if (title_cursor == 1) {
			DrawString(200, 70, "------中級ステージ------", pink);
			DrawString(90, 70, "\n\n中級以降のステージではライフが存在します\n\n赤色のブロックに触れた時や高い位置から落下した\n"
				"時にライフが減ってしまいます\n※高所から赤色のブロックに落下すると2ライフ減ります\n\nゴールするとライフが1回復(上限無し)して次のマップに\n進めますが、ライフが0になるとゲームオーバーになります\n\n"
				"また、中級以降には文字入力で水色のブロックを重ねても\n破壊できないピンク色のブロックが登場します", white);
		}
		if (title_cursor == 2) {
			DrawString(200, 70, "------上級ステージ------", pink);
			DrawString(90, 70, "\n\n上級ステージではチェックポイントが存在します\n\n\'C\'のマークが入ったブロックをすべて回収してからでないと\n"
				"GOAL地点から次のマップには進めません\n\nさらに、上級ステージではWP(ワードパワー)が存在します"
				"\n\n文字入力を行う度に減っていき、WPが0の時に入力を行うと\nライフが1減少します\n\nマップ移動時に残っているWPの半分だけライフが回復し、\nWPは全回復します", white);
		}
	}

	//スタートステップ1の時は暗転をする
	if (start_step == 1) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);		//αブレンド
		DrawGraph(0, 0, black_image, TRUE);			//暗転
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//元のブレンドモードに戻す
	}
}

//タイトル画面で呼び出す関数
void Title(player_t* player, int *gamestep, int mapdata[480 / masusize][640 / masusize]) {
	//計算処理
	TitleUpdate(player ,gamestep, mapdata);

	//描画処理
	TitleDraw();
}