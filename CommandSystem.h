#pragma once

class CommandSystem
{
private:
	// コマンドの数
	static const int CommandCount = 6;

	// コマンド
	const char* commands[CommandCount] =
	{
		"見る",
		"調べる",
		"話す",
		"移動",
		"持ち物",
		"考える"
	};

	//選択中のコマンド
	int selectCommand = 0;

	// 前回のキー状態
	bool leftKeyPrev = false;
	bool rightKeyPrev = false;
	bool enterKeyPrev = false;
	// 決定状態
	bool decision = false;

public:
	// コマンドの更新
	void Update();

	// コマンドの描画
	void Draw();

	// キー状態のリセット
	void ResetKeyState();

	// 選択中の番号を取得
	int GetSelectCommand();

	// コマンド決定の確認
	bool IsDecided();
}
;