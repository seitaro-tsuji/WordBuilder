#pragma once
#ifndef ALLFUNC_H
#define ALLFUNC_H

#include "allvari.h"

//キーボード関連の初期化関数
void KeyInitialize();

// キーの入力状態を更新するKeyboard.cpp
void Keyboard_Update();

// 引数のキーコードのキーの入力状態を返すKeyboard.cpp
int Keyboard_Get(int KeyCode);

//ゲーム全体の初期化をする関数title.cpp
void Game_Initialize(int* gamestep);

//タイトル画面での処理をする関数title.cpp
void TitleUpdate(player_t* player, int* gamestep, int mapdata[480 / masusize][640 / masusize]);

//タイトル画面の描画をする関数title.cpp
void TitleDraw();

//タイトル画面で呼び出す関数title.cpp
void Title(player_t* player, int* gamestep, int mapdata[480 / masusize][640 / masusize]);

//文字の形を数値データで得る関数litter.cpp
void Getlitterdata(char str[3], int litddata[littersize][littersize]);

//マップの初期化関数map.cpp
void mapInitialize(player_t* player, int mapdata[480 / masusize][640 / masusize], int n);

//マップとプレイヤーの表示をする関数map.cpp
void Drawmap(player_t player, int mapdata[480 / masusize][640 / masusize]);

//与えられた座標のmapdata上の数値を返す関数map.cpp
int GetNumbermapdata(int x, int y, int mapdata[480 / masusize][640 / masusize]);

//進むことができるかの判定をする関数map.cpp
int MoveAbleToGo(player_t player, int mapdata[480 / masusize][640 / masusize], int dire);

//マップ上でプレイヤーを動かす関数map.cpp
void MovePlayer(player_t* player, int mapdata[480 / masusize][640 / masusize], int* gamestep);

//初級ステージの計算処理、描画処理を行う関数map.cpp
void StageEasy(player_t* player, int mapdata[480 / masusize][640 / masusize], int *gamestep);

#endif
