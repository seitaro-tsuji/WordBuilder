#include "DxLib.h"
#include "allfunc.h"
#include "allvari.h"

static int m_Key[256];  // キーの入力状態格納用変数

//キーボード関連の初期化関数
void KeyInitialize() {
    PAD1 = GetJoypadInputState(DX_INPUT_PAD1);
}

// キーの入力状態更新
void Keyboard_Update() {
    PAD1 = GetJoypadInputState(DX_INPUT_PAD1);  //コントローラー
    char tmpKey[256];             // 現在のキーの入力状態を格納する
    GetHitKeyStateAll(tmpKey);  // 全てのキーの入力状態を得る
    for (int i = 0; i < 256; i++) {
        if (tmpKey[i] != 0) { // i番のキーコードに対応するキーが押されていたら
            m_Key[i]++;   // 加算
        }
        else if (i == KEY_INPUT_DOWN && (PAD1 & PAD_INPUT_DOWN)) {
            m_Key[KEY_INPUT_DOWN]++;
        }
        else if (i == KEY_INPUT_UP && (PAD1 & PAD_INPUT_UP)) {
            m_Key[KEY_INPUT_UP]++;
        }
        else if (i == KEY_INPUT_RIGHT && (PAD1 & PAD_INPUT_RIGHT)) {
            m_Key[KEY_INPUT_RIGHT]++;
        }
        else if (i == KEY_INPUT_LEFT && (PAD1 & PAD_INPUT_LEFT)) {
            m_Key[KEY_INPUT_LEFT]++;
        }
        else if (i == KEY_INPUT_Z && (PAD1 & PAD_INPUT_2)) {    //ボタン2(A)はZキーに対応
            m_Key[KEY_INPUT_Z]++;
        }
        else if (i == KEY_INPUT_X && (PAD1 & PAD_INPUT_1)) {    //ボタン1(B)はXキーに対応
            m_Key[KEY_INPUT_X]++;
        }
        else if (i == KEY_INPUT_C && (PAD1 & PAD_INPUT_3)) {    //ボタン3(Y)はCキーに対応
            m_Key[KEY_INPUT_C]++;
        }
        else if (i == KEY_INPUT_W && (PAD1 & PAD_INPUT_4)) {    //ボタン4(X)はWキーに対応
            m_Key[KEY_INPUT_W]++;
        }
        else {              // 押されていなければ
            m_Key[i] = 0; // 0にする
        }
    }
}

// KeyCodeのキーの入力状態を取得する
int Keyboard_Get(int KeyCode) {
    return m_Key[KeyCode]; // KeyCodeの入力状態を返す
}