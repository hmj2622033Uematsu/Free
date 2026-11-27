#pragma once

class TargetSystem
{
private:

	// 選択できる対象
	const char** targets;
	// 対象の数
	int targetCount;

	// 選択中の対象
	int selectTarget;

	// 前回のキー状態
	bool upKeyPrev;
	bool downKeyPrev;
	bool enterKeyPrev;
	bool escKeyPrev;

	// 決定・キャンセル状態
	bool decision;
	bool cancel;

public:
	// 
	TargetSystem();

	// コマンドに応じた対象を設定
	void SetTargets(int commandIndex);

	// 対象の更新
	void Update();

	// 対象の描画
	void Draw();

	// 決定したか確認
	bool IsDecided();

	// キャンセルしたか確認
	bool IsCanseled();

	// 選択中の対象番号を取得
	int GetSelectedTarget();

	// 選択中の対象名を取得
	const char* GetSelectedTargetName();
};