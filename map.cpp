#include "DxLib.h"
#include "allfunc.h"
#include "allvari.h"

//ウィンドウを表示する関数(ウィンドウ内部は背景の画像を少し薄くする)
void DrawWindow_M(int x1, int y1, int x2, int y2, int frame_flag = 1) {
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 200);
	DrawModiGraph(x1, y1, x2, y1, x2, y2, x1, y2, black_image, TRUE);      //後でこの画像の透過度を変化させることでウィンドウ内部の描写を薄くする
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (frame_flag == 1)
		DrawBox(x1, y1, x2, y2, GetColor(255, 255, 255), FALSE);
}

//マップの初期化や移動をする関数
void mapInitialize(player_t* player, int mapdata[480 / masusize][640 / masusize], int n) {
	player->m = n;		//マップナンバーをnにする
	if (n == 1) {
		//プレイヤーの初期座標を9,44にする
		player->x = 9 * masusize;
		player->y = 1 * masusize;
		check_num = 0;
		player->jamp_phase = 3;
		player->life_flag = 0;
		start = 110;
		goal_high = 0;
		goal_low = 110;		//ゴールの足場のy座標の20上がいい

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == 13 && j < 12)	//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == 13 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}
	if (n == 2) {
		//プレイヤーの初期座標を9,44にする
		player->x = 9 * masusize;
		player->y = 1 * masusize;
		player->jamp_phase = 3;
		start = 110;
		goal_high = 0;
		goal_low = 110;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(即死ブロック)
				else if (i == 13 && j < 12)	//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == 13 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (j == 31)
					mapdata[i][j] = 1;
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}
	if (n == 3) {
		player->x = 0;
		player->y = 0;
	}

	//6~　中級ステージ
	if (n == 6) {
		//プレイヤーの初期座標を9,44にする
		player->x = 9 * masusize;
		player->y = 1 * masusize;
		check_num = 0;
		player->jamp_phase = 3;
		player->life_flag = 1;
		player->life = 3;
		player->wp = 3;
		fall_y = 0;
		start = 110;
		goal_high = 0;
		goal_low = 110;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (j == 31 && i < 24)
					mapdata[i][j] = 4;			//4壊せないブロック
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}
	if (n == 7) {
		//start,goal
		start = 80;
		goal_high =320;
		goal_low = 400;
		//プレイヤーの初期座標
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += 1;
		player->wp = 3;
		

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)							//ここまでテンプレ
				else if (i == 19 && j < 32)
					mapdata[i][j] = 2;
				else if (i == 19)
					mapdata[i][j] = 1;
				else if (i == 30 && j < 32)
					mapdata[i][j] = 1;
				else if (i == 30)
					mapdata[i][j] = 2;
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}
	/*if (n == 8) {
		//start,goal
		start = 430;
		goal_high = 0;
		goal_low = 110;
		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += 1;
		player->wp = 3;


		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)							//ここまでテンプレ
				else if (i == goal_low / masusize + 2 && j >= 40)
					mapdata[i][j] = 1;
				else if (i == goal_low / masusize + 3 && j >= 40 && j <= 51)
					mapdata[i][j] = 2;
				else if (i == goal_low / masusize - 2 && j >= 41 && j <= 51)
					mapdata[i][j] = 2;
				else if (41 <= j && j <= 51 && i <= goal_low / masusize - 2)
					mapdata[i][j] = 4;
				else if (28 <= i && i <= 30 && 23<= j && j <= 27)
					mapdata[i][j] = 4;
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}*/
	if (n == 8) {
		//プレイヤーの初期座標を9,44にする
		player->x = 9 * masusize;
		player->y = 10 * masusize;
		player->jamp_phase = 3;
		player->life += 1;
		player->wp = 3;
		start = 220;
		goal_high = 0;
		goal_low = 220;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 13)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 48)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (12 < j && j < 49 && i != 23 && i != 22 && i != 21)
					mapdata[i][j] = 4;			//壊せないブロック
				else if (12 < j && j < 49)
					mapdata[i][j] = 1;			//1(ブロック)
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}
	if (n == 9) {
		player->x = 0;
		player->y = 0;
		player->life_flag = 0;
	}

	//11~上級ステージ
	if (n == 11) {
		//start,goal,check
		start = 240;
		goal_high = 0;
		goal_low = 240;
		check_num = 1;
		wp_max = 5;
		ex_flag = 0;
		fall_y = 0;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life = 3;
		player->life_flag = 1;
		fall_y = 0;
		player->check = 0;
		player->wp = wp_max;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでテンプレ
				else if (i == 6 && j == 32)
					mapdata[i][j] = 5;			//5(check)
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}
	if (n == 12) {
		//start,goal,check
		start = 120;
		goal_high = 0;
		goal_low = 120;
		check_num = 1;
		wp_max = 5;
		fall_y = 0;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += player->wp/2;
		player->life_flag = 1;
		player->check = 0;
		player->wp = wp_max;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでテンプレ
				else if (i == 32 && 30 <= j && j <= 34)
					mapdata[i][j] = 1;
				else if (i == 28 && 30 <= j && j <= 34)
					mapdata[i][j] = 4;
				else if (j == 30 && 29 <= i && i <= 31)
					mapdata[i][j] = 1;
				else if (j == 34 && 29 <= i && i <= 31)
					mapdata[i][j] = 1;
				else if (i == 30 && j == 32)
					mapdata[i][j] = 5;
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}
	if (n == 13) {
		//start,goal,check
		start = 120;
		goal_high = 0;
		goal_low = 360;
		check_num = 2;
		wp_max = 6;
		fall_y = 0;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += player->wp/2;
		player->life_flag = 1;
		player->check = 0;
		player->wp = wp_max;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでテンプレ
				else if (j == 20 && i < 25)
					mapdata[i][j] = 4;
				else if (j == 35 && i > 15)
					mapdata[i][j] = 4;
				else if ((i == 22 && j == 24) || (i == 22 && j == 31))
					mapdata[i][j] = 5;
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}
	if (n == 14) {
		//start,goal,check
		start = 220;
		goal_high = 0;
		goal_low = 220;
		check_num = 2;
		wp_max = 8;
		fall_y = 0;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += player->wp/2;
		player->life_flag = 1;
		player->check = 0;
		player->wp = wp_max;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでテンプレ
				else if (12 < j && j < 49 && i != 23 && i != 22 && i != 21)
					mapdata[i][j] = 4;			//壊せないブロック
				else if (12 < j && j < 49)
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == 24)
					mapdata[i][j] = 1;
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間
				if (j == 24 && 24 <= i && i <= 28)
					mapdata[i][j] = 1;
				if (j == 36 && 16 <= i && i <= 20)
					mapdata[i][j] = 1;
				if ((i == 29 && j == 24) || (i == 15 && j == 36))
					mapdata[i][j] = 5;
			}
		}
	}
	if (n == 15) {
		//start,goal,check
		start = 120;
		goal_high = 0;
		goal_low = 120;
		check_num = 3;
		wp_max = 5;
		fall_y = 0;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += player->wp/2;
		player->life_flag = 1;
		player->check = 0;
		player->wp = wp_max;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでテンプレ
				else if (i == 14 && j != 30 && j != 31 && j != 32 && j != 33)
					mapdata[i][j] = 4;
				else if (31 <= j && j <= 32 && i > 25)
					mapdata[i][j] = 2;
				else if (i == 27 && j < 20)
					mapdata[i][j] = 4;
				else if (i == 27 && j > 43)
					mapdata[i][j] = 4;
				else if ((i == 22 && j == 2) || (i == 22 && j == 61) || (i==28&&j==17))
					mapdata[i][j] = 5;
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間
			}
		}
	}
	if (n == 16) {
		//start,goal,check
		start = 400;
		goal_high = 0;
		goal_low = 120;
		check_num = 5;
		wp_max = 6;
		fall_y = 0;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += player->wp/2;
		player->life_flag = 1;
		player->check = 0;
		player->wp = wp_max;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでテンプレ
				else if ((j == 22 || j == 23 || j == 33 || j == 34 || j == 44 || j == 45) && i > 30)
					mapdata[i][j] = 2;
				else if ((i == 38 && j == 17) || (i == 38 && j == 28) || (i == 38 && j == 39) || (i == 38 && j == 50) || (i == 6 && j == 12))
					mapdata[i][j] = 5;
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間
			}
		}
	}
	if (n == 17) {
		player->x = 0;
		player->y = 0;
		player->life_flag = 0;
	}
	//~18はEXTRA
	if (n == 18) {
		//start,goal
		start = 430;
		goal_high = 0;
		goal_low = 110;
		check_num = 1;
		wp_max = 4;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 60;
		player->jamp_phase = 3;
		player->life = 3;
		player->life_flag = 1;
		player->check = 0;
		player->wp = wp_max;
		fall_y = 0;


		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)							//ここまでテンプレ
				else if (i == goal_low / masusize + 2 && j >= 40)
					mapdata[i][j] = 1;
				else if (i == goal_low / masusize + 3 && j >= 40 && j <= 51)
					mapdata[i][j] = 2;
				else if (i == goal_low / masusize - 2 && j >= 41 && j <= 51)
					mapdata[i][j] = 2;
				else if (51 <= j && j <= 51 && i <= goal_low / masusize - 2)
					mapdata[i][j] = 4;
				else if (28 <= i && i <= 30 && 23 <= j && j <= 27)
					mapdata[i][j] = 4;
				else if (i == 27 && j == 25)
					mapdata[i][j] = 5;
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}
	if (n == 19) {
		//start,goal,check
		start = 220;
		goal_high = 340;
		goal_low = 440;
		check_num = 2;
		wp_max = 8;
		fall_y = 0;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += player->wp/2;
		player->life_flag = 1;
		player->check = 0;
		player->wp = wp_max;
		fall_y = 0;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでテンプレ
				else if (i == goal_low / masusize + 1 && j ==63)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでテンプレ
				else if (i == 25 && j <= 31)
					mapdata[i][j] = 2;
				else if (i == 25)
					mapdata[i][j] = 1;
				else if (i == 33 && j <= 31)
					mapdata[i][j] = 1;
				else if (i == 33)
					mapdata[i][j] = 2;
				else if (i == 15 && j <= 31)
					mapdata[i][j] = 1;
				else if (i == 15)
					mapdata[i][j] = 2;
				else if (i == 7 &&1 <= j && j <= 31)
					mapdata[i][j] = 2;
				else if (i == 7)
					mapdata[i][j] = 1;
				else if ((i == 5 && j == 60) || (i == 31 && j == 5))
					mapdata[i][j] = 5;
				else
					mapdata[i][j] = 0;			//その他のマスは何もない空間			
			}
		}
	}
	if (n == 20) {
		//start,goal,check
		start = 220;
		goal_high = 0;
		goal_low = 220;
		check_num = 2;
		wp_max = 12;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += player->wp/2;
		player->life_flag = 1;
		player->check = 0;
		player->wp = wp_max;
		fall_y = 0;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				mapdata[i][j] = 0;			//一旦全部0にする
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでテンプレ
				if (12 < j && j < 50 && i != 23 && i != 22 && i != 21)
					mapdata[i][j] = 4;			//壊せないブロック
				else if (12 < j && j < 50)
					mapdata[i][j] = 1;			//1(ブロック)
				if (25 <= j && j <= 30 && 8 <= i && i <= 40)
					mapdata[i][j] = 1;
				if (8 <= i && i <= 12 && 31 <= j && j <= 36)
					mapdata[i][j] = 0;
				if (36 <= i && i <= 40 && 31 <= j && j <= 36)
					mapdata[i][j] = 0;
				if ((i == 10 && j == 34) || (i == 38 && j == 34))
					mapdata[i][j] = 5;
				if (i == 24 && mapdata[i][j] == 0)
					mapdata[i][j] = 1;
			}
		}
	}
	if (n == 21) {
		//start,goal,check
		start = 80;
		goal_high = 0;
		goal_low = 80;
		check_num = 4;
		wp_max = 12;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += player->wp/2;
		player->life_flag = 1;
		player->check = 0;
		player->wp = wp_max;
		fall_y = 0;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				mapdata[i][j] = 0;			//一旦全部0にする
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでは変更なし
				else if (i == 10 && (j < 21 || 42 < j))
					mapdata[i][j] = 4;
				if (i == 20 && j < 16)
					mapdata[i][j] = 4;
				if (i == 30 && j < 11)
					mapdata[i][j] = 4;
				if (i == 20 && j > 47)
					mapdata[i][j] = 4;
				if (i == 30 && j > 52)
					mapdata[i][j] = 4;
				if ((i == 17 || i == 27) && (j == 3 || j == 60))
					mapdata[i][j] = 5;
				if ((j == 31 || j == 32) && i > 20)
					mapdata[i][j] = 2;
			}
		}
	}
	if (n == 22) {
		//start,goal,check
		start = 80;
		goal_high = 0;
		goal_low = 80;
		check_num = 6;
		wp_max = 14;

		//プレイヤーの初期座標(基本変更しない部分)
		player->x = 9 * masusize;
		player->y = start - 30;
		player->jamp_phase = 3;
		player->life += player->wp/2;
		player->life_flag = 1;
		player->check = 0;
		player->wp = wp_max;
		fall_y = 0;

		//全てのマスに対して
		for (i = 0; i < 480 / masusize; i++) {
			for (j = 0; j < 640 / masusize; j++) {
				mapdata[i][j] = 0;			//一旦全部0にする
				if (i == 480 / masusize - 1) 	//最下段は
					mapdata[i][j] = 2;			//2(奈落)
				else if (i == start / masusize + 2 && j < 12)		//スタート地点
					mapdata[i][j] = 1;			//1(ブロック)
				else if (i == goal_low / masusize + 2 && j > 52)		//ゴール地点
					mapdata[i][j] = 1;			//1(ブロック)				//ここまでは変更なし
				if (j == 31)
					mapdata[i][j] = 2;
				if (i == 11 || i == 23 || i == 35)
					mapdata[i][j] = 2;
				if (j == 31 && 16 <= i && i <= 21)
					mapdata[i][j] = 1;
				if (i == 11 && ((25 <= j && j <= 30) || (34 <= j && j <= 40)))
					mapdata[i][j] = 1;
				if (i == 23 && ((13 <= j && j <= 17) || (42 <= j && j <= 48)))
					mapdata[i][j] = 1;
				if (i == 35 && ((23 <= j && j <= 26) || (33 <= j && j <= 38)))
					mapdata[i][j] = 1;
				if ((i == 22 || i == 34 || i == 46) && (j <= 10 || 53 <= j))
					mapdata[i][j] = 4;
				if ((i == 19 || i == 31 || i == 43) && (j == 3 || j == 60))
					mapdata[i][j] = 5;
			}
		}
	}
	if (n == 23) {
		player->x = 0;
		player->y = 0;
		player->life_flag = 0;
	}


	chara_image[0] = LoadGraph("画像/棒人間＿静止.png");
	chara_image[1] = LoadGraph("画像/棒人間＿右移動.png");
	chara_image[2] = LoadGraph("画像/棒人間＿左移動.png");
	chara_image[3] = LoadGraph("画像/棒人間＿ジャンプ.png");
	black_image = LoadGraph("画像/真っ黒画面.png");
	font_clear = CreateFontToHandle("メイリオ", 45, 4, DX_FONTTYPE_ANTIALIASING_EDGE);	//フォントの作成
	heart = LoadGraph("画像/ハート.png");
	heart5 = LoadGraph("画像/ハート5.png");
	font_small = CreateFontToHandle("メイリオ", 8, 1, DX_FONTTYPE_ANTIALIASING_EDGE);
	clear_massage = LoadGraph("画像/クリア文字.png");
}

//マップとプレイヤーの表示をする関数
void Drawmap(player_t player, int mapdata[480 / masusize][640 / masusize]) {
	//全てのマスに対して
	for (i = 0; i < 480 / masusize; i++) {
		for (j = 0; j < 640 / masusize; j++) {
			if (mapdata[i][j] == 0)
				DrawBox(j * masusize, i * masusize, (j + 1) * masusize, (i + 1) * masusize, black, TRUE);	//黒色のブロック
			else if (mapdata[i][j] == 1)
				DrawBox(j * masusize, i * masusize, (j + 1) * masusize, (i + 1) * masusize, white, TRUE);	//白色のブロック
			else if (mapdata[i][j] == 2)
				DrawBox(j * masusize, i * masusize, (j + 1) * masusize, (i + 1) * masusize, red, TRUE);		//赤色のブロック
			else if (mapdata[i][j] == 3)
				DrawBox(j * masusize, i * masusize, (j + 1) * masusize, (i + 1) * masusize, l_blue, TRUE);	//水色のブロック
			else if (mapdata[i][j] == 4)
				DrawBox(j * masusize, i * masusize, (j + 1) * masusize, (i + 1) * masusize, pink, TRUE);	//桃色のブロック
			else if (mapdata[i][j] == 5) {
				DrawBox(j * masusize, i * masusize, (j + 1) * masusize, (i + 1) * masusize, white, FALSE);	//ブロック
				DrawStringToHandle(j * masusize+1, i * masusize+1, "C", white, font_small);						//"C"
			}
		}
	}

	//プレイヤーの表示chara_image[player.action]
	DrawGraph(player.x, player.y, chara_image[player.action], TRUE);

	//説明の表示
	if (ex_flag == 0) {
		DrawFormatString(0, 0, white, "Q:操作説明表示");
	}
	if (ex_flag == 1) {
		DrawFormatString(0, 0, yellow, "Q:操作説明(PAD)\n→,←:左右移動\nX    :文字の打ち込み\n");
		DrawFormatString(200, 0, yellow,"Z/A:ジャンプ\nC  :ステージの初期化\nW  :タイトルに戻る");
	}
	if (ex_flag == 2) {
		DrawFormatString(0, 0, yellow, "Qキー:操作説明非表示\n→,←:左右移動\nB    :文字の打ち込み\n");
		DrawFormatString(200, 0, yellow, "A  :ジャンプ\nY  :ステージの初期化\nX  :タイトルに戻る");
	}
	if (1 <= player.m && player.m <= 3)
		DrawFormatString(400, 0, yellow, "初級ステージ %d / 2", player.m);
	if (6 <= player.m && player.m <= 9)
		DrawFormatString(400, 0, yellow, "中級ステージ %d / 3", player.m - 5);
	if (11 <= player.m && player.m <= 16)
		DrawFormatString(400, 0, yellow, "上級ステージ %d / 6", player.m - 10);
	if (18 <= player.m)
		DrawFormatString(400, 0, blue, "EXTRA %d / 5", player.m - 17);
	if (player.life_flag) {	//ライフフラグが1ならライフアイコンの表示
		for (i = 0; i < player.life/5; i++) {
			DrawGraph(420 + i * 32, 20, heart5, TRUE);
		}
		for (j = 0; j < player.life % 5; j++) {
			DrawGraph(420 + i * 32 + j * 25, 25, heart, TRUE);
		}
	}

	//上級ステージでは回収したチェックポイントの数,WPの表示
	if (player.m >= 11 && !ex_flag) {
		DrawFormatString(200, 00, white, "check:  /%d", check_num);		//回収済みチェックポイントの数
		if (player.check < check_num)
			DrawFormatString(200, 00, white, "       %d", player.check);		//回収済みチェックポイントの数
		else
			DrawFormatString(200, 00, green2, "       %d", player.check);		//回収済みチェックポイントの数
		
		DrawFormatString(200, 20, white, "WP:   /%d", wp_max);		//WP表示
		if(player.wp)
			DrawFormatString(200, 20, white, "    %2d", player.wp);		//残っていたら城で表示
		else
			DrawFormatString(200, 20, red, "    %2d", player.wp);		//0なら赤で表示
	}

	DrawString(10, start - 45, "S T A R T", white);
	DrawString(540, goal_low - 45, "G O A L →", white);

	if (return_flag == 1) {
		DrawWindow_M(160, 120, 480, 360);		//ウィンドウの表示
		DrawFormatString(170, 130, white, "タイトルに戻りますか?\n");
		DrawFormatString(230, 170, white, "はい　　　　　いいえ");
		DrawFormatString(210 + map_cursor * 100, 170, yellow, "→");
	}

	if (erea_flag == 1) {
		if (ec_step == 1) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);		//αブレンド
			DrawGraph(0, 0, black_image, TRUE);			//暗転
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//元のブレンドモードに戻す
		}
		if (ec_step == 2) {
			DrawGraph(0, 0, black_image, TRUE);			//暗転
		}
		if (ec_step == 3) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, pal);		//αブレンド
			DrawGraph(0, 0, black_image, TRUE); ;//暗転
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);	//元のブレンドモードに戻す
		}
	}

	if (massage_flag) {
		DrawWindow_M(40, 380, 600, 470);
		DrawFormatString(45, 390, white, m_str);
	}

	//playerのマップが4の時はクリア画面を表示
	if (player.m == EasyClear) {
		DrawGraph(0, 0, black_image, TRUE);
		DrawStringToHandle(120, 50, "Congratulations!!\n", l_blue, font_clear);
		DrawFormatString(250, 120, white, "初級ステージクリア");
		DrawFormatString(200, 140, white, "プレイしてくれてありがとう!!");
		DrawFormatString(230, 220, white, "Zキー : タイトルに戻る");
	}
	//playerのマップが10の時はクリア画面を表示
	if (player.m == NormalClear) {
		DrawGraph(0, 0, black_image, TRUE);
		DrawStringToHandle(120, 50, "Congratulations!!\n", l_blue, font_clear);
		DrawFormatString(250, 120, white, "中級ステージクリア");
		DrawFormatString(200, 140, white, "プレイしてくれてありがとう!!");
		DrawFormatString(230, 220, white, "Zキー : タイトルに戻る");
	}
	//playerのマップが17の時はクリア画面を表示
	if (player.m == HardClear) {
		DrawGraph(0, 0, black_image, TRUE);
		//120,50
		DrawGraph(120, 50, clear_massage, TRUE);
		DrawFormatString(250, 120, white, "上級ステージクリア");
		DrawFormatString(200, 140, white, "プレイしてくれてありがとう!!");
		DrawFormatString(150, 220, white, "タイトル画面に何か異変が起こったようだ...!");
		DrawFormatString(230, 240, white, "Zキー : タイトルに戻る");
	}
	//playerのマップが23の時はクリア画面を表示
	if (player.m == EXTRAClear) {
		DrawGraph(0, 0, black_image, TRUE);
		//120,50
		DrawGraph(120, 50, clear_massage, TRUE);
		DrawFormatString(245, 120, white, "EXTRAステージクリア");
		DrawFormatString(245, 150, white, "   完全クリア!!!");
		DrawFormatString(170, 220, white, "最後までプレイしてくれてありがとう!!");
		DrawFormatString(230, 240, white, "Zキー : タイトルに戻る");
	}

	//playerのマップが5の時はゲームオーバー画面を表示
	if (player.m == 5) {
		DrawWindow_M(0, 0, 640, 480, 0);
		DrawString(120, 50, "残りライフが0になってしまった...\n", red);
		DrawFormatString(230, 220, white, "Zキー : タイトルに戻る");

		if (death_flag == 1) {
			DrawString(120, 80, "[死因] : 高所からの落下", red);
		}
		if (death_flag == 2) {
			DrawString(120, 80, "[死因] : 赤ブロックと接触", red);
		}
		if (death_flag == 3) {
			DrawString(120, 80, "[死因] : 文字の書きすぎ", red);
		}
	}
	//↓はデバック用
	//DrawFormatString(360, 0, white, "erea_flag = %d\nec_step = %d\npal = %d", erea_flag, ec_step, pal);
}

//与えられた座標のmapdata上の数値を返す関数
int GetNumbermapdata(int x, int y, int mapdata[480 / masusize][640 / masusize]) {
	return mapdata[y / masusize][x / masusize];
}


//進むことができるかの判定をする関数(可能なら1を返す)
int MoveAbleToGo(player_t player, int mapdata[480 / masusize][640 / masusize], int dire) {
	x = player.x;
	y = player.y;	//見やすくするためにx,yとしておく

	if (dire == 0) {	//direが0、右向きの時は
		if (x + 10 >= 639 && goal_high <= y && y <= goal_low && player.check >= check_num)	//ゴールの範囲内なら右から画面外に行ける
			return 1;
		else if (x + 10 >= 639)		//上の範囲以外なら画面外には行けない
			return 0;
		else if (GetNumbermapdata(x + 10, y, mapdata) == 0 && GetNumbermapdata(x + 10, y + 10, mapdata) == 0 && GetNumbermapdata(x + 10, y + 19, mapdata) == 0)//上の条件を満たさないなら画面はしではない
			return 1;
		else
			return 0;
	}
	if (dire == 1) {	//direが1、左向きの時は
		if (x - 1 < 0)	//画面の端っこの時は0を返す
			return 0;
		else if (GetNumbermapdata(x - 1, y, mapdata) == 0 && GetNumbermapdata(x - 1, y + 10, mapdata) == 0 && GetNumbermapdata(x - 1, y + 19, mapdata) == 0)
			return 1;
		else
			return 0;
	}
	if (dire == 2) {	//direが2、下向きの時は
		if (GetNumbermapdata(x, y + 20, mapdata) == 0 && GetNumbermapdata(x + 9, y + 20, mapdata) == 0)
			return 1;
		else
			return 0;
	}
	if (dire == 3) {	//direが3、上向きの時は
		if (GetNumbermapdata(x, y - 1, mapdata) == 0 && GetNumbermapdata(x + 9, y - 1, mapdata) == 0 && y - 1 > 0)
			return 1;
		else
			return 0;
	}
}

//死亡するマスに触れたら1を返す関数
int DieorAlive(player_t player, int mapdata[480 / masusize][640 / masusize]) {
	x = player.x;
	y = player.y;	//見やすく
	if (GetNumbermapdata(x, y - 1, mapdata) == 2 || GetNumbermapdata(x + 9, y - 1, mapdata) == 2 || GetNumbermapdata(x + 10, y, mapdata) == 2 ||
		GetNumbermapdata(x + 10, y + 9, mapdata) == 2 || GetNumbermapdata(x + 10, y + 19, mapdata) == 2 || GetNumbermapdata(x + 9, y + 20, mapdata) == 2 ||
		GetNumbermapdata(x, y + 20, mapdata) == 2 || GetNumbermapdata(x - 1, y + 19, mapdata) == 2 ||
		GetNumbermapdata(x - 1, y + 9, mapdata) == 2 || GetNumbermapdata(x - 1, y, mapdata) == 2)
		return 1;
	else
		return 0;
}

//nの番号のブロックに触れたら1を返す関数
int TouchNumberblock(player_t player, int mapdata[480 / masusize][640 / masusize], int n) {
	x = player.x;
	y = player.y;	//見やすく
	if (GetNumbermapdata(x, y - 1, mapdata) == n || GetNumbermapdata(x + 9, y - 1, mapdata) == n || GetNumbermapdata(x + 10, y, mapdata) == n ||
		GetNumbermapdata(x + 10, y + 9, mapdata) == n || GetNumbermapdata(x + 10, y + 19, mapdata) == n || GetNumbermapdata(x + 9, y + 20, mapdata) == n ||
		GetNumbermapdata(x, y + 20, mapdata) == n || GetNumbermapdata(x - 1, y + 19, mapdata) == n ||
		GetNumbermapdata(x - 1, y + 9, mapdata) == n || GetNumbermapdata(x - 1, y, mapdata) == n)
		return 1;
	else
		return 0;
}

//死亡したときの処理をする関数(nは死因　1:落下　2:赤色)
void Mapdeath(player_t *player, int n, int *gamestep) {
	player->life -= 1;		//ライフ-1
	
	if (player->life > 0) {	//ライフが残っていれば
		//スタート地点に戻る
		player->x = 6 * masusize;
		player->y = start - 30;

		massage_flag = 150;
		if (n == 1)
			sprintf_s(m_str, "死んでしまった...(死因 : 落下死)");
		if (n == 2)
			sprintf_s(m_str, "死んでしまった...(死因 : 赤ブロックに触れた)");

		death_flag = 0;	//フラグを戻す
	}
	else {	//残っていなければ
		player->m = 5;	//タイトルに戻る
	}
}

//マップ上でプレイヤーを動かす関数
void MovePlayer(player_t* player, int mapdata[480 / masusize][640 / masusize], int* gamestep) {
	player->action = 0;	//静止状態
	//エリア移動フラグ、リターンフラグ、死亡フラグが立っていない時
	if (erea_flag == 0 && return_flag == 0 && death_flag == 0) {
		if (player->x >= 640 && player->y >= goal_low-20) {		//画面の右からフレームアウトしたら(goalしたら)
			erea_flag = 1;
			ec_step = 1;
			pal = 0;
		}
		if (Keyboard_Get(KEY_INPUT_X) == 1) {//Xキーが入力されたら
			//最初にmapdataを元に戻す
			for (i = 0; i < littersize; i++) {
				for (j = 0; j < littersize; j++) {
					if (mapdata[i + 6][j + 12] == 3)
						mapdata[i + 6][j + 12] = 0;
				}
			}
			DrawString(180, 0, "文字を1つだけ入力してください。", l_blue);
			KeyInputString(200, 20, 10, inputlitter, FALSE);
			Getlitterdata(inputlitter, litterdata);	//文字のデータを取り込む
			for (i = 0; i < littersize; i++) {
				for (j = 0; j < littersize; j++) {
					if (litterdata[i][j] == 3 && mapdata[i + 6][j + 12] != 4 && mapdata[i + 6][j + 12] != 2 && mapdata[i + 6][j + 12] != 5)
						mapdata[i + 6][j + 12] = litterdata[i][j];	//文字のデータをマップのデータに埋め込む
				}
			}
			//上級ステージでは代償の処理をする
			if (player->m >= 11 && !player->wp) {	//上級ステージでwp0の時
				if (player->life >= 2) {	//ライフ2以上の時
					player->life -= 1;				//ライフ-1
					massage_flag = 150;
					sprintf_s(m_str, "WP不足によりライフを1失った...");
				}
				else {
					death_flag = 3;
					Mapdeath(player, 3, gamestep);
				}
			}
			if (player->m >= 11 && player->wp) {	//上級ステージでwpが残っている場合
				player->wp -= 1;				//WP-1
			}

			//プレイヤーの初期座標を9,39にする
			/*player->x = 9 * masusize;
			player->y = 1 * masusize;
			player->jamp = 0;
			player->jamp_phase = 0;*/
		}
		if (Keyboard_Get(KEY_INPUT_Q) == 1) {//Qキー
			ex_flag = (ex_flag + 1) % 3;
		}
		if (Keyboard_Get(KEY_INPUT_C) == 1) {//Cキー
			life_re = player->life;	//残りライフの保存
			wp_re = player->wp;		//残りWPの保存
			mapInitialize(player, mapdata, player->m);	//マップ初期化
			player->life = life_re;	//ライフを元通りにする
			//player->wp = wp_re;		//WPは回復させてもいいかも
		}

		if (Keyboard_Get(KEY_INPUT_W) == 1 && player->jamp_phase == 0) {//地上でW
			return_flag = 1;
			map_cursor = 1;
		}

		if (Keyboard_Get(KEY_INPUT_RIGHT)) {//右が押されているとき
			player->action = 1;	//右移動状態
			if (MoveAbleToGo(*player, mapdata, 0))		//進めると判定されたら
				player->x += 1;			//右に移動
		}
		if (Keyboard_Get(KEY_INPUT_LEFT)) {//左が押されているとき
			player->action = 2;	//左移動状態
			if (MoveAbleToGo(*player, mapdata, 1))		//進めると判定されたら
				player->x -= 1;
		}

		//ジャンプに関する処理
		if (player->jamp_phase == 0) {	//フェーズ0、上昇も落下もしていない時
			if (Keyboard_Get(KEY_INPUT_Z) == 1 || Keyboard_Get(KEY_INPUT_A) == 1) {	//Z,Aキーが押されると
				player->jamp = 30;	//jampを30にする
				player->jamp_phase = 1;	//フェーズ1に移行
				cnt = 0;	//cntは0
			}
			else if (MoveAbleToGo(*player, mapdata, 2) == 1) {	//下が床でなくなったら
				player->jamp_phase = 3;		//降下フェーズに移行
			}
		}
		if (player->jamp_phase == 1) {	//フェーズ1、上昇中かつZキーを押している間
			cnt++;
			player->action = 3;	//ジャンプ状態
			player->jamp = 30;	//jampは30に維持する
			if ((Keyboard_Get(KEY_INPUT_Z) == 0 && Keyboard_Get(KEY_INPUT_A) == 0) || cnt >= 25) {	//Z,Aキーが離されたら、あるいは25フレーム経過したら
				player->jamp_phase = 2;	//フェーズ2に移行
				cnt = 0;
			}
		}
		if (player->jamp_phase == 2) {	//フェーズ2、上昇中でZキーを離した後
			player->action = 3;	//ジャンプ状態
			player->jamp -= 2;
			if (player->jamp == 0) {		//jampが0になったら
				player->jamp_phase = 3;		//フェーズ3に移行
				fall_y = 0;				//fall_yを0にする
			}
		}
		if (player->jamp_phase == 3) {	//フェーズ3、下降中の時
			player->action = 3;	//ジャンプ状態
			player->y_past = player->y;		//変更前のy座標を記録する
			if (player->jamp) {//jampの数値が残っていたら
				player->jamp_phase = 2;	//phase2に戻る
			}
			if (MoveAbleToGo(*player, mapdata, 2) == 1) {	//下に何もなければ
				player->y += 2;		//2下降する
				fall_y += 2;		//落下距離を2増やす
			}
			else {
				player->jamp_phase = 0;	//フェーズ0に戻る
				if (fall_y > 200 && player->life_flag == 1)
					death_flag = 1;		//150以上落下すると死亡
				fall_y = 0;		//落下距離を0に戻す
			}
		}

		if (player->jamp > 0) {	//jampが1以上の時
			if (MoveAbleToGo(*player, mapdata, 3) == 1) {	//上に進めるなら
				player->y_past = player->y;		//変更前のy座標を記録する
				player->y -= 2;		//2上昇
			}
			else {	//上に進めないなら
				player->jamp = 0;	//jampを0にする
				player->jamp_phase = 3;
			}
		}
		if (player->jamp_phase && player->jamp >= 0 && player->y == player->y_past) {	//全処理が終了した後でjampphase3,jamp>0,y座標が変化していない時
			player->y += 2;
			player->jamp_phase = 0;
		}
	}

	if (TouchNumberblock(*player, mapdata, 5)) {	//チェックポイントに触れたら
		player->check += 1;
		for (i = 0; i < 4; i++) {
			for (j = 0; j < 3; j++) {
				if (mapdata[player->y / masusize - 1 + i][player->x / masusize - 1 + j] == 5)
					mapdata[player->y / masusize - 1 + i][player->x / masusize - 1 + j] = 0;			//周囲の5番マスを0番に変える
			}
		}
	}

	if (DieorAlive(*player, mapdata) == 1 && death_flag == 0 && player->life_flag) {	//赤マスに触れたら
		death_flag = 2;		//死亡フラグを2にする
	}

	if (return_flag == 1) {
		if (Keyboard_Get(KEY_INPUT_RIGHT) == 1 || Keyboard_Get(KEY_INPUT_LEFT) == 1) {
			map_cursor = (map_cursor + 1) % 2;		//左右入力でカーソル移動
		}
		if ((Keyboard_Get(KEY_INPUT_Z) == 1 && map_cursor == 1) || Keyboard_Get(KEY_INPUT_X) == 1) {
			map_cursor = 1;		//カーソルを戻して
			return_flag = 0;	//フラグも下げる
		}
		if (Keyboard_Get(KEY_INPUT_Z) == 1 && map_cursor == 0) {
			map_cursor = 1;		//カーソル戻す
			return_flag = 0;	//フラグ下げる
			*gamestep = 0;		//タイトルに戻す
		}
	}

	if (erea_flag == 1) {//エリア移動フラグが1のとき
		if (ec_step == 1) {
			pal = pal + 8;	//毎フレーム+8
			if (pal >= 255)
				ec_step = 2;	//palが255を超えたらstep2に移行
		}
		if (ec_step == 2) {
			/*次のマップに移行する*/

			mapInitialize(player, mapdata, player->m + 1);
			ec_step = 3;	//ステップ3に移行
		}
		if (ec_step == 3) {
			pal -= 8;	//毎フレーム-8
			if (pal <= 0) {
				erea_flag = 0;
				ec_step = 0;
			}
		}
	}

	if (death_flag) {
		/*死亡したときの処理をする関数を入れる*/
		Mapdeath(player, death_flag, gamestep);
	}

	if (massage_flag) {
		massage_flag -= 1;
	}

	if (player->m == EasyClear || player->m == NormalClear || player->m == HardClear || player->m == EXTRAClear) {	//マップ3,9,17,23のときクリア画面
		if (Keyboard_Get(KEY_INPUT_Z) == 1) {	//Z
			*gamestep = 0;
			cnt = 0;
			
		}
		if (player->m == HardClear)
			player->extra_flag = 1;		//EXTRAステージの開放
	}
	if (player->m == 5) {
		if (Keyboard_Get(KEY_INPUT_Z) == 1) {
			death_flag = 0;
			*gamestep = 0;
			cnt = 0;
		}
	}
}

//初級ステージの計算処理、描画処理を行う関数
void StageEasy(player_t *player, int mapdata[480/masusize][640/masusize], int *gamestep) {
	//計算処理フェーズ
	MovePlayer(player, mapdata, gamestep);

	//描画フェーズ
	Drawmap(*player, mapdata);
}