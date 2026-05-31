#include "DxLib.h"
#include "allfunc.h"
#include "allvari.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(FALSE),
    DxLib_Init(), SetDrawScreen(DX_SCREEN_BACK);

    //ゲームの初期化
    Game_Initialize(&game_step);

    //キーボード関連の初期化
    KeyInitialize();

    //以下の処理を毎フレーム行う
    while (ScreenFlip() == 0 && ProcessMessage() == 0 && ClearDrawScreen() == 0 && CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
        Keyboard_Update();      //キーボードの更新

        if (game_step == 0)
            Title(&player ,&game_step, mapdata);    //タイトル画面の計算、描画処理
        if (game_step == 1)
            StageEasy(&player, mapdata, &game_step);    //初級ステージの計算、描画処理        
    }

    DxLib_End();
    return 0;
}

int main() {
    return WinMain(GetModuleHandle(NULL), NULL, GetCommandLineA(), SW_SHOWNORMAL);
}