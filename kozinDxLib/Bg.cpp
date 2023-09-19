#include "Bg.h"
#include "Dxlib.h"
#include "Game.h"

// ファイルの出力に使用する
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

namespace
{
	//マップチップの情報
	constexpr int kChipWidth = 32;
	constexpr int kChipHeight = 32;

	//チップを置く数   縦１５個　横２０個
	constexpr int kChipNumX = Game::kScreenWidth / kChipWidth;
	constexpr int kChipNumY = Game::kScreenHeight / kChipHeight;

	//マップチップの配置情報
	constexpr int kChipData[kChipNumY][kChipNumX] =
	{
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,3,0,0,0,4,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,6,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,20,21,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,36,37,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	};
}

Bg::Bg() :
	m_handle(-1),
	m_graphChipNumX(0),
	m_graphChipNumY(0)
{
	//マップチップ配置データの初期化
	for (int x = 0; x < kChipNumX; x++)
	{
		for (int y = 0; y < kChipNumY; y++)
		{
			m_chipData[y][x] = kChipData[y][x];
		}
	}
}

Bg::~Bg()
{
}

void Bg::Init()
{
	//マップチップの数を数える
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_handle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;

	//デバッグ表示
	//printfDx("ChipNumX:%d\n", m_graphChipNumX);
	//printfDx("ChipNumY:%d\n", m_graphChipNumY);

	//マップチップ配置データの読み込み
	fstream file;
	//バイナリモードで開く
	file.open("map/map.bin", ios::in | ios::binary);
	//ファイルを開くのに失敗した場合の処理
	if (!file.is_open())
	{
		//ファイルを開くのに失敗した場合の処理
		printfDx("ファイルを開くのに失敗しました\n");
	}
	else
	{
		//ファイルのオープンに成功した
		//ファイルの中身をメモリ上にコピーする
		file.read(reinterpret_cast<char*> (&(m_chipData[0][0])), sizeof(int) * kChipNumX * kChipNumY);
		file.close();
	}
}

void Bg::Update()
{
}

void Bg::Draw()
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
				srcX, srcY, kChipWidth, kChipHeight, m_handle, true);

		}

	}



}
