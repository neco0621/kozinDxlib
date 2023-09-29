#pragma once

//パッドの状態を取得する
namespace Pad
{
	//パッドの更新処理　1フレームに1回行う
	void Update();

	//押されているかを取得
	bool isPadPress(int key);
	//押された瞬間を取得
	bool isPadTrigger(int key);
	//離した瞬間を取得
	bool isPadRelase(int key);
}

