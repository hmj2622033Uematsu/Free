#include "DxLib.h"
#include "TargetSystem.h"

// 対象一覧

// 0 見る
const char* lookTargets[] =
{
	"駅のホーム",
	"周囲の雪",
	"待合室"
};

// 1 調べる
const char* searchTargets[] =
{
	"掲示板",
	"ベンチ",
	"古い時計"
};

// 2 話す
const char* talkTargets[] =
{
	"幸"
};

// 3 移動
const char* moveTargets[] =
{
	"待合室",
	"駅の外"
};

// 4 持ち物
const char* itemTargets[] =
{
	"懐中時計",
	"宛先"
};

// 5 考える
const char* thinkTargets[] =
{
	"この駅について",
	"幸について"
};


// コンストラクタ
TargetSystem::TargetSystem()
{
	targets = nullptr;

	targetCount = 0;
	selectTarget = 0;

	upKeyPrev = false;
	downKeyPrev = false;
	enterKeyPrev = false;
	escKeyPrev = false;

	decision = false;
	cancel = false;
}

// 対象を設定
void TargetSystem::SetTargets(int commandIndex)
{
	selectTarget = 0;

	switch (commandIndex)
	{
	case 0:
		targets = lookTargets;
		targetCount = 3;
		break;

	case 1:
		targets = searchTargets;
		targetCount = 3;
		break;

	case 2:
		targets = talkTargets;
		targetCount = 1;
		break;

	case 3:
		targets = moveTargets;
		targetCount = 2;
		break;

	case 4:
		targets = itemTargets;
		targetCount = 2;
		break;

	case 5:
		targets = thinkTargets;
		targetCount = 2;
		break;
		
	default:
		targets = nullptr;
		targetCount = 0;
		break;

		//画面切り替え直後の連続入力を防止
		enterKeyPrev = CheckHitKey(KEY_INPUT_RETURN);
		upKeyPrev = CheckHitKey(KEY_INPUT_UP);
		downKeyPrev = CheckHitKey(KEY_INPUT_DOWN);
	}
}

// 対象の更新
void TargetSystem::Update()
{
	decision = false;
	cancel = false;

	bool upKeyNow = CheckHitKey(KEY_INPUT_UP);
	bool downKeyNow = CheckHitKey(KEY_INPUT_DOWN);
	bool enterKeyNow = CheckHitKey(KEY_INPUT_RETURN);
	bool escKeyNow = CheckHitKey(KEY_INPUT_ESCAPE);

	// 左キー
	if (upKeyNow && !upKeyPrev) // 連続入力を防ぐ
	{
		selectTarget--;
		if (selectTarget < 0)
		{
			selectTarget = targetCount - 1;
		}
	}
	// 右キー
	if (downKeyNow && !downKeyPrev)
	{
		selectTarget++;
		if (selectTarget >= targetCount)
		{
			selectTarget = 0;
		}
	}
	// Enterキー
	if (enterKeyNow && !enterKeyPrev)
	{
		decision = true;
	}
	// ESCキー
	if (escKeyNow && !escKeyPrev)
	{
		cancel = true;
	}

	// キー状態を保存
	
	upKeyPrev = upKeyNow;
	downKeyPrev = downKeyNow;
	enterKeyPrev = enterKeyNow;
	escKeyPrev = escKeyNow;
}

// 対象の描画
void TargetSystem::Draw()
{
	// 対象選択ウィンドウ
	DrawBox(0, 400, 960, 640, GetColor(20, 30, 42), true);

	DrawString(20, 450, "TARGET", GetColor(180, 210, 230));

	// 対象一覧
	for (int i = 0; i < targetCount; i++)
	{
		int x = 30;
		int y = 520 + i * 35;

		unsigned int color;

		if (i == selectTarget)
		{
			color = GetColor(255, 230, 150);
		}
		else
		{
			color = GetColor(220, 230, 240);
		}

		DrawString(x, y, targets[i], color);

		// 操作説明
		DrawString(480, 450, "↑↓ : 選択", GetColor(180, 210, 230));
		DrawString(480, 475, "ENTER : 決定", GetColor(180, 210, 230));
		DrawString(480, 500, "ESC : 戻る", GetColor(180, 210, 230));
	}
};

// 決定確認
bool TargetSystem::IsDecided()
{
	return decision;
}
// キャンセル確認
bool TargetSystem::IsCanseled()
{
	return cancel;
}
// 選択中の対象番号
int TargetSystem::GetSelectedTarget()
{
	return selectTarget;
}

// 選択中の対象名
const char* TargetSystem::GetSelectedTargetName()
{
	if (targets == nullptr || targetCount == 0)
	{
		return "";
	}

	return targets[selectTarget];
}