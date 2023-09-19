#include "SceneMapEdit.h"
#include "DxLib.h"
#include <cassert>

#include "Pad.h"

//ファイルの出力に使用する
#include <iostream>
#include <fstream>
#include <string>  //文字列を扱うためのクラス
#include <cstdlib>
using namespace std;

namespace
{
	//カーソル移動リピートフレーム
	constexpr int kCursorRepeatFrame = 4;
}

SceneMapEdit::SceneMapEdit() :
	m_cursorX(5),
	m_cursorY(4),
	m_rightRipeatFrame(0),
	m_downRipeatFrame(0),
	m_upRipeatFrame(0),
	m_leftRipeatFrame(0)
{
	//グラフィックのハンドル
	m_bgHandle = LoadGraph("data/bg.png");
	assert(m_bgHandle != -1);

	//マップチップの数を数える
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_bgHandle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;

	//チップ配置情報の作成
	for (int x = 0; x < kChipNumX; x++)
	{
		for (int y = 0; y < kChipNumY; y++)
		{
			m_chipData[y][x] = 0;
		}
	}
}

SceneMapEdit::~SceneMapEdit()
{
	//グラフィックの解放
	DeleteGraph(m_bgHandle);
}

void SceneMapEdit::Init()
{
}

void SceneMapEdit::End()
{
}

void SceneMapEdit::Update()
{
	//カーソルの移動
	//パッドの十字キーを使用してカーソルを移動
	//int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//zキー
	if (Pad::isPadTrigger(PAD_INPUT_1))
	{
		//配列の範囲外アクセスを検知するためのassert
		assert(m_cursorX >= 0 && m_cursorX < kChipNumX);
		assert(m_cursorY >= 0 && m_cursorY < kChipNumY);

		//選択しているマップチップの番号を+1
		m_chipData[m_cursorY][m_cursorX]++;

		//グラフィック内に存在するマップチップの数
		int chipNum = GetGraphChipNum();

		//Chipの番号は0番からの通し番号で管理している
		//Chipが10個だと　通し番号は0～9

		if (m_chipData[m_cursorY][m_cursorX] > chipNum - 1)
		{
			m_chipData[m_cursorY][m_cursorX] = 0;
		}
	}
	//xキー
	if (Pad::isPadTrigger(PAD_INPUT_2))
	{
		//配列の範囲外アクセスを検知するためのassert
		assert(m_cursorX >= 0 && m_cursorX < kChipNumX);
		assert(m_cursorY >= 0 && m_cursorY < kChipNumY);

		//選択しているマップチップの番号を-1
		m_chipData[m_cursorY][m_cursorX]--;

		//グラフィック内に存在するマップチップの数
		int chipNum = GetGraphChipNum();

		//ループ処理
		if (m_chipData[m_cursorY][m_cursorX] < 0)
		{
			m_chipData[m_cursorY][m_cursorX] = chipNum - 1;
		}
	}

	//ファイル出力テスト      cキー
	if (Pad::isPadTrigger(PAD_INPUT_3))
	{
		OutputText();
		OutputBinary();
	}

	//ファイル読み込みテスト
	if (Pad::isPadTrigger(PAD_INPUT_4))      //Aキー
	{
		InputText();
		InputBinary();
	}
#if false
	//test
	if (false)
	{
		fstream file;
		file.open("test.txt", ios::in || ios::out);   //複数のフラグを同時に指定可能
	}
#endif




	//課題の自己流答え
	//if (CheckHitKey(KEY_INPUT_1))
	//{
		//m_chipData[m_cursorY][m_cursorX]++;
	//}
	//else if (CheckHitKey(KEY_INPUT_2))
	//{
		//m_chipData[m_cursorY][m_cursorX]--;
	//}


#if false
	if (Pad::isPadTrigger(PAD_INPUT_UP))
	{
		m_cursorY--;
		if (m_cursorY < 0)
		{
			m_cursorY = kChipNumY - 1;
		}
	}
#else
	//上方向へのカーソル移動
	if (Pad::isPadPress(PAD_INPUT_UP))
	{
		m_upRipeatFrame++;
		if ((m_upRipeatFrame >= kCursorRepeatFrame) ||
			Pad::isPadTrigger(PAD_INPUT_UP))

		{
			m_upRipeatFrame = 0;

			//カーソル移動の処理
			CursorUp(Pad::isPadTrigger(PAD_INPUT_UP));


		}


	}
#endif
#if false
	if (Pad::isPadTrigger(PAD_INPUT_DOWN))
	{
		m_cursorY++;
		if (m_cursorY > kChipNumY)
		{
			m_cursorY = 0;
		}
	}
#else
	//下方向へのカーソル移動
	if (Pad::isPadPress(PAD_INPUT_DOWN))
	{
		m_downRipeatFrame++;
		if ((m_downRipeatFrame >= kCursorRepeatFrame) ||
			Pad::isPadTrigger(PAD_INPUT_DOWN))

		{
			m_downRipeatFrame = 0;

			//カーソル移動の処理
			CursorDown(Pad::isPadTrigger(PAD_INPUT_DOWN));
		}

	}
#endif
#if false
	if (Pad::isPadTrigger(PAD_INPUT_LEFT))
	{
		m_cursorX--;
		if (m_cursorX < 0)
		{
			m_cursorX = kChipNumX - 1;
		}
	}
#else
	//左方向へのカーソル移動
	if (Pad::isPadPress(PAD_INPUT_LEFT))
	{
		m_leftRipeatFrame++;
		if ((m_leftRipeatFrame >= kCursorRepeatFrame) ||
			Pad::isPadTrigger(PAD_INPUT_LEFT))

		{
			m_leftRipeatFrame = 0;

			//カーソル移動の処理
			CursorLeft(Pad::isPadTrigger(PAD_INPUT_LEFT));
		}

	}
#endif
#if false
	if (Pad::isPadTrigger(PAD_INPUT_RIGHT))
	{
		m_cursorX++;
		if (m_cursorX > kChipNumX)
		{
			m_cursorX = 0;
		}
	}
#else
	//右方向へのカーソル移動
	if (Pad::isPadPress(PAD_INPUT_RIGHT))
	{
		m_rightRipeatFrame++;
		if ((m_rightRipeatFrame >= kCursorRepeatFrame) ||
			Pad::isPadTrigger(PAD_INPUT_RIGHT))

		{
			m_rightRipeatFrame = 0;

			//カーソル移動の処理
			CursorRight(Pad::isPadTrigger(PAD_INPUT_RIGHT));
		}

	}
#endif
}

void SceneMapEdit::Draw()
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			//この番号のチップで敷き詰める
			int chipNo = m_chipData[y][x];



			//マップチップのグラフィック切り出し座標
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			//DrawGraph(0, 0, m_handle, true);

			DrawRectGraph(x * kChipWidth, y * kChipHeight,
				srcX, srcY, kChipWidth, kChipHeight, m_bgHandle, true);

		}

	}

	//グリッドの表示

	//縦線
	for (int x = 0; x < kChipNumX; x++)
	{
		DrawLine(x * kChipWidth, 0, x * kChipWidth, Game::kScreenHeight, GetColor(255, 255, 255));
	}
	//横線
	for (int y = 0; y < kChipNumY; y++)
	{
		DrawLine(0, y * kChipHeight, Game::kScreenWidth, y * kChipHeight, GetColor(255, 255, 255));
	}

	//現在選択しているチップにカーソルを表示
	int cursorPosX = m_cursorX * kChipWidth;
	int cursorPosY = m_cursorY * kChipHeight;
	DrawBox(cursorPosX, cursorPosY, cursorPosX + kChipWidth,
		cursorPosY + kChipHeight, GetColor(255, 255, 0), false);
	//一回り小さい四角を描画して線の太い四角にする
	DrawBox(cursorPosX + 1, cursorPosY + 1, cursorPosX + kChipWidth - 1,
		cursorPosY + kChipHeight - 1, GetColor(255, 255, 0), false);

}

void SceneMapEdit::CursorUp(bool isLoop)
{
	m_cursorY--;
	if (m_cursorY < 0)
	{
		if (isLoop)
		{
			m_cursorY = kChipNumY - 1;
		}
		else
		{
			m_cursorY = 0;
		}
	}
}

void SceneMapEdit::CursorDown(bool isLoop)
{
	m_cursorY++;
	if (m_cursorY > kChipNumY - 1)
	{
		if (isLoop)
		{
			m_cursorY = 0;
		}
		else
		{
			m_cursorY = kChipNumY - 1;
		}
	}
}

void SceneMapEdit::CursorLeft(bool isLoop)
{
	m_cursorX--;
	if (m_cursorX < 0)
	{
		if (isLoop)
		{
			m_cursorX = kChipNumX - 1;
		}
		else
		{
			m_cursorX = 0;
		}
	}
}

void SceneMapEdit::CursorRight(bool isLoop)
{
	m_cursorX++;
	if (m_cursorX > kChipNumX - 1)
	{
		if (isLoop)
		{
			m_cursorX = 0;
		}
		else
		{
			m_cursorX = kChipNumX - 1;
		}
	}
}

int SceneMapEdit::GetGraphChipNum()
{
	return m_graphChipNumX * m_graphChipNumY;
}

void SceneMapEdit::OutputText()
{
	fstream file;
	file.open("test.txt", ios::out);     //ファイルを開く　　　出力したいのでios::out

	if (!file.is_open())
	{
		//return EXIT_FAILURE;   //教科書は開けなかったらその時点でプログラム終了
		printfDx("ファイルを開くのに失敗しました\n");
	}
	else
	{
		//ファイルが開けた場合の処理
		//file << "ファイルに書き込んじゃえ。" << endl;   //openしたファイルに書き込み

		//数値の書き込みテスト
		//int num = 100;
		//file << num << endl;

		//作成したマップのデータをテキストで出力する
		for (int y = 0; y < kChipNumY; y++)
		{
			file << "{";
			for (int x = 0; x < kChipNumX; x++)
			{
				if (x == kChipNumX - 1)    //最後のみ","は出力しない
				{
					file << m_chipData[y][x];
				}
				else
				{
					file << m_chipData[y][x] << ",";
				}

			}
			file << "}" << endl;
		}



		file.close();


		printfDx("ファイルに書き込みを行いました\n");
	}
}

void SceneMapEdit::InputText()
{
	fstream file;
	file.open("test.txt", ios::in);  //読み込む時はios::inで開く
	//ファイルを開くのに失敗した場合
	if (!file.is_open())
	{
		//return EXIT_FAILURE;   //教科書は開けなかったらその時点でプログラム終了
		printfDx("ファイルを開くのに失敗しました\n");
	}
	else
	{
		//ファイルのオープンに成功したので読み込みを行う
		string str;
		getline(file, str);
		file.close();

		printfDx(str.c_str());
	}
}

void SceneMapEdit::OutputBinary()
{
	fstream file;
	file.open("map.bin", ios::out | ios::binary);     //拡張子はなんでもよい　バイナリデータを表すbin,データを表すdat等がメジャー

	//ファイルを開くのに失敗した場合の処理
	if (!file.is_open())
	{
		//ファイルが開かなかった場合の処理
		printfDx("ファイルを開くのに失敗しました\n");
	}
	else
	{
		//ファイルオープンに成功した
		//マップチップの配置データをバイナリで出力

		//fstreamのwrite関数を使用して出力する
		//メモリ上のどこに置かれているか（アドレス）と
		//そこから何バイト出力するか、を指定する
		file.write((const char*)&(m_chipData[0][0]), sizeof(int) * kChipNumX * kChipNumY);
		file.close();

		printfDx("バイナリデータとしてマップデータを出力しました\n");
	}
}

void SceneMapEdit::InputBinary()
{
	fstream file;
	//バイナリモードで開く
	file.open("map.bin", ios::in | ios::binary);

	//ファイルを開くのに失敗した場合の処理
	if (!file.is_open())
	{
		//ファイルが開けなかった場合の処理
		//return EXIT_FAILURE; //教科書は開けなかったらその時点でプログラム終了
		printfDx("ファイルを開くのに失敗しました\n");
	}
	else
	{
		//ファイルオープンに成功した
		//読み込んだバイナリの内容をメモリ上のマップチップ情報に上書きする
		file.read((char*)&(m_chipData[0][0]), sizeof(int) * kChipNumX * kChipNumY);
		file.close();

		printfDx("バイナリデータを読み込んでマップデータにしました\n");
	}
}
