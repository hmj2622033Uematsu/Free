#include "DxLib.h"
#include <string>
#include "CommandSystem.h"
#include "TargetSystem.h"

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
	TargetSystem target;

	// 画面状態
	bool targetMode = false;

	// 最後に決定した対象
	const char* selectedTargetName = nullptr;

	while (1) // メインループ
	{
		//コマンド画面でESC終了
		//if (CheckHitKey(KEY_INPUT_ESCAPE) && !targetMode)
		//{
		//	break;
		//}
		
		ClearDrawScreen(); // 画面をクリアする

		if (!targetMode)
		{
			// コマンド更新
			command.Update();

			// Enterで決定
			if (command.IsDecided())
			{
				// 選択したコマンドに対応する対象を設定
				target.SetTargets(command.GetSelectCommand());

				// 対象選択画面へ切り替え
				targetMode = true;

				// 前回の結果を消す
				selectedTargetName = nullptr;
			}

			// コマンド描画
			command.Draw();

			// 前回決定した対象を表示
			if (selectedTargetName != nullptr)
			{
				DrawString(30, 410, selectedTargetName, GetColor(255, 255, 255));
			}
		}
		else
		{
			// 対象更新
			target.Update();

			// Escでコマンド画面へ戻る
			if (target.IsCanseled())
			{
				targetMode = false;
			}

			// Enterで対象設定
			if (target.IsDecided())
			{
				selectedTargetName = target.GetSelectedTargetName();
				//コマンド選択画面へ戻る
				targetMode = false;
			}
			// 対象描画
			if (targetMode)
			{
				target.Draw();
			}
		}

		ScreenFlip(); // 裏画面の内容を表画面に反映させる
		WaitTimer(16);
		if (ProcessMessage() == -1) break; // Windowsから情報を受け取りエラーが起きたら終了
		//if (CheckHitKey(KEY_INPUT_ESCAPE) == 1) break; // ESCキーが押されたら終了
	}

	DxLib_End(); // DXライブラリ使用の終了処理
	return 0; // ソフトの終了
}