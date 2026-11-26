#include <DxLib.h>
#include <string>
#include "CommandSystem.h"

const int WIDTH = 960, HEIGHT = 640; // ウィンドウの幅と高さのピクセル数


int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	SetWindowText("PANDORA"); // ウィンドウタイトル
	SetGraphMode(WIDTH, HEIGHT, 32); // ウィンドウの大きさとカラービット数の設定
	ChangeWindowMode(true); // ウィンドウモードで起動
	if (DxLib_Init() == -1) return -1; // ライブラリの初期化 エラーが起きたら終了
	SetBackgroundColor(0, 0, 0); // 背景色の指定
	SetDrawScreen(DX_SCREEN_BACK); // 描画面を裏画面にする

	// 
	CommandSystem command;

	while (1) // メインループ
	{
		
		ClearDrawScreen(); // 画面をクリアする

		// コマンド更新
		command.Update();

		// コマンド描画
		command.Draw();


		ScreenFlip(); // 裏画面の内容を表画面に反映させる
		WaitTimer(16);
		if (ProcessMessage() == -1) break; // Windowsから情報を受け取りエラーが起きたら終了
		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; // ESCキーが押されたら終了
	}

	DxLib_End(); // DXライブラリ使用の終了処理
	return 0; // ソフトの終了
}