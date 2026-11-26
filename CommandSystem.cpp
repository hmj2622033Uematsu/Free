#include "DxLib.h"
#include "CommandSystem.h"

void CommandSystem::Update()
{

	// 上キー
	bool leftKeyNow = CheckHitKey(KEY_INPUT_LEFT);

	if (leftKeyNow && !leftKeyPrev)
	{
		selectCommand--;
		if (selectCommand < 0)
		{
			selectCommand = CommandCount - 1;
		}
	}
	// 下キー
	bool rightKeyNow = CheckHitKey(KEY_INPUT_RIGHT);
	if (rightKeyNow && !rightKeyPrev)
	{
		selectCommand++;
		if (selectCommand >= CommandCount)
		{
			selectCommand = 0;
		}
	}

	// キー状態を保存
	leftKeyPrev = leftKeyNow;
	rightKeyPrev = rightKeyNow;
}

void CommandSystem::Draw()
{
	// コマンド表示エリア
	DrawBox(0, 400, 960, 640, GetColor(20, 30, 42), true);

	// コマンドタイトル
	DrawString(20, 450, "COMMAND", GetColor(180, 210, 230));

	// コマンドを描画
	for (int i = 0; i < CommandCount; i++)
	{
		//３列２行
		int x = 30 + (i % 3) * 200;
		int y = 500 + (i / 3) * 45;

		//選択中の色
		unsigned int color;


		if (i == selectCommand)
		{
			color = GetColor(0, 128, 0);
		}
		else
		{
			color = GetColor(220, 230, 240);
		}

		// コマンド文字
		DrawString(x, y, commands[i], color);
	}
	// 操作説明
	DrawString(480, 450, "←→ : 選択", GetColor(180, 210, 230));
}

// 選択中のコマンドを取得
int CommandSystem::GetSelectCommand()
{
	return selectCommand;
}