#include "SceneMapEdit.h"
#include "DxLib.h"
#include <cassert>

#include "Game.h"
#include "Pad.h"

//�t�@�C���̏o�͂Ɏg�p����
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;

//�t�@�C���̓ǂݍ��݂Ɏg�p����
#include<string>

namespace
{
	//�J�[�\���ړ����s�[�g�t���[��
	constexpr int kCursorRepeatFrame = 6;

	// �`�b�v�f�[�^�ύX�̃��s�[�g�t���[��
	constexpr int kChipRepeatFrame = 8;
}

SceneMapEdit::SceneMapEdit() :
	m_cursorX(0),
	m_cursorY(0),
	m_upRepeatFrame(0),
	m_downRepeatFrame(0),
	m_leftRepeatFrame(0),
	m_rightRepeatFrame(0),
	m_upChipRepeatFrame(0),
	m_downChipRepeatFrame(0)
{
	//�O���t�B�b�N�̃��[�h
	m_bgHandle = LoadGraph("data/bg.png");
	assert(m_bgHandle != -1);

	//�}�b�v�`�b�v�̐��𐔂���
	int graphWidth = 0;
	int graphHeight = 0;
	GetGraphSize(m_bgHandle, &graphWidth, &graphHeight);

	m_graphChipNumX = graphWidth / kChipWidth;
	m_graphChipNumY = graphHeight / kChipHeight;

	//�`�b�v�z�u���̐���
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
	//�O���t�B�b�N�̉��
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
	// �ړ�����
	if (Pad::IsRepeat(PAD_INPUT_UP, m_upRepeatFrame, kCursorRepeatFrame))
	{
		CursorUp(Pad::IsTrigger(PAD_INPUT_UP));
	}
	if (Pad::IsRepeat(PAD_INPUT_DOWN, m_downRepeatFrame, kCursorRepeatFrame))
	{
		CursorDown(Pad::IsTrigger(PAD_INPUT_DOWN));
	}
	if (Pad::IsRepeat(PAD_INPUT_LEFT, m_leftRepeatFrame, kCursorRepeatFrame))
	{
		CursorLeft(Pad::IsTrigger(PAD_INPUT_LEFT));
	}
	if (Pad::IsRepeat(PAD_INPUT_RIGHT, m_rightRepeatFrame, kCursorRepeatFrame))
	{
		CursorRight(Pad::IsTrigger(PAD_INPUT_RIGHT));
	}

	//A�{�^��
	if (Pad::IsTrigger(PAD_INPUT_1))
	{
		assert(m_cursorX >= 0 && m_cursorX < kChipNumX);

		//�I�����Ă���}�b�v�`�b�v�̔ԍ���+1
		m_chipData[m_cursorY][m_cursorX]++;

		//�O���t�B�b�N���ɑ��݂���}�b�v�`�b�v�̐�
		int chipNum = GetGraphChipNum();

		//���[�v����
		if (m_chipData[m_cursorY][m_cursorX] > chipNum - 1)
		{
			m_chipData[m_cursorY][m_cursorX] = 0;
		}
	}

	//B�{�^��
	if (Pad::IsTrigger(PAD_INPUT_2))
	{
		assert(m_cursorY >= 0 && m_cursorY < kChipNumY);

		//�I�����Ă���}�b�v�`�b�v�̔ԍ���-1
		m_chipData[m_cursorY][m_cursorX]--;

		//�O���t�B�b�N���ɑ��݂���}�b�v�`�b�v�̐�
		int chipNum = GetGraphChipNum();

		//���[�v����
		if (m_chipData[m_cursorY][m_cursorX] < 0)
		{
			m_chipData[m_cursorY][m_cursorX] = chipNum - 1;
		}
	}

	//�t�@�C���o��
	//X�{�^��
	if (Pad::IsTrigger(PAD_INPUT_3))
	{
		OutputBinary();
	}

	//�t�@�C���ǂݍ���
	//Y�{�^��
	if (Pad::IsTrigger(PAD_INPUT_4))
	{
		InputBinary();
	}
#if false
	if (false)
	{
		std::fstream file;
		file.open("test.txt", std::ios::in | std::ios::out);	// �����̃t���O�𓯎��Ɏw��\
	}
#endif
}

void SceneMapEdit::Draw() const
{
	for (int y = 0; y < kChipNumY; y++)
	{
		for (int x = 0; x < kChipNumX; x++)
		{
			// �}�b�v��񂩂�u���`�b�v������Ă���
			int chipNo = m_chipData[y][x];

			//�}�b�v�`�b�v�̃O���t�B�b�N�؂�o�����W
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			DrawRectGraph(kChipWidth * x, kChipHeight * y,
				srcX, srcY, kChipWidth, kChipHeight, m_bgHandle, true);
		}
	}

	//�O���b�h�̕\��
	//�c��
	for (int x = 0; x < kChipNumX; x++)
	{
		DrawLine(kChipWidth * x, 0, kChipWidth * x, Game::kScreenHeight, 0x0000ff);
	}
	//����
	for (int y = 0; y < kChipNumY; y++)
	{
		DrawLine(0, kChipHeight * y, Game::kScreenWidth, kChipHeight * y, 0x0000ff);
	}


	//���ݑI�����Ă���`�b�v�ɃJ�[�\���\��
	int cursorPosX = m_cursorX * kChipWidth;
	int cursorPosY = m_cursorY * kChipHeight;

	//				������W�@�@�@�@�@�@�@�@�@�@�@�@�@�@�E�����W
	DrawBox(cursorPosX, cursorPosY, cursorPosX + kChipWidth, cursorPosY + kChipHeight,
		0x0000ff, false);

	//���菬�����l�p�̕`�悵�Đ��̑����l�p�ɂ���
	DrawBox(cursorPosX + 1, cursorPosY + 1, cursorPosX + kChipWidth - 1, cursorPosY + kChipHeight - 1,
		0x0000ff, false);
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
			// �g���K�[�̎��̓J�[�\�������[�v����
			m_cursorX = 0;
		}
		else
		{
			// ���s�[�g�����̎��͈�x�~�߂�
			m_cursorX = kChipNumX - 1;
		}
	}
}
void SceneMapEdit::ChipUp(bool isLoop)
{
	assert(0 <= m_cursorX && m_cursorX < kChipNumX);
	assert(0 <= m_cursorY && m_cursorY < kChipNumY);

	// �I�����Ă���}�b�v�`�b�v�̔ԍ���+1
	m_chipData[m_cursorY][m_cursorX]++;

	if (GetGraphChipNum() - 1 < m_chipData[m_cursorY][m_cursorX])
	{
		if (isLoop)	m_chipData[m_cursorY][m_cursorX] = 0;
		else		m_chipData[m_cursorY][m_cursorX] = GetGraphChipNum() - 1;
	}
}



void SceneMapEdit::ChipDown(bool isLoop)
{
	assert(0 <= m_cursorX && m_cursorX < kChipNumX);
	assert(0 <= m_cursorY && m_cursorY < kChipNumY);

	// �I�����Ă���}�b�v�`�b�v�̔ԍ���-1
	m_chipData[m_cursorY][m_cursorX]--;

	if (m_chipData[m_cursorY][m_cursorX] < 0)
	{
		if (isLoop)	m_chipData[m_cursorY][m_cursorX] = GetGraphChipNum() - 1;
		else		m_chipData[m_cursorY][m_cursorX] = 0;
	}
}

int SceneMapEdit::GetGraphChipNum()
{
	return m_graphChipNumX * m_graphChipNumY;;
}

void SceneMapEdit::OutputText()
{
	std::fstream file;

	file.open("test.txt", std::ios::out);	// �t�@�C�����J�� �o�͂������̂�std::ios::out
	// �t�@�C���̓��e���������ꍇ��std::ios::in�ŊJ��

// �t�@�C�����J���̂Ɏ��s�����ꍇ�̏���
	if (!file.is_open())
	{
		// �t�@�C�����J�v��Ɏ��s�����ꍇ�̏���
		// ���ȏ��͊J���Ȃ������炻�̎��_�Ńv���O�����I��
		// return EXIT_FAILURE;

		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");
	}
	else
	{
#if false
		// �t�@�C�����J�����ꍇ�̏���
		file << "�t�@�C���ɏ������񂶂Ⴆ�B" << std::endl;	// open�����t�@�C���ɏ�������

		// ���l�̏������݃e�X�g
		int num = 256;
		file << num << std::endl;
#endif
		// �쐬�����}�b�v�̃f�[�^���e�L�X�g�ŏo�͂���
		for (int y = 0; y < kChipNumY; y++)
		{
			file << "{" << std::flush;
			for (int x = 0; x < kChipNumX; x++)
			{
				// �Ō�̂�","�͏o�͂��Ȃ�
				if (x == kChipNumX - 1) file << m_chipData[y][x] << std::flush;
				else					file << m_chipData[y][x] << "," << std::flush;
			}
			file << "}," << std::endl;
		}

		file.close();

		printfDx("�t�@�C���ɏ������݂��s���܂���\n");
	}
}



void SceneMapEdit::InputText()
{
	std::fstream file;

	file.open("test.txt", std::ios::in);	// �ǂݍ��ނƂ���std::ios::in�ŊJ��

	// �t�@�C�����J���̂Ɏ��s�����ꍇ�̏���
	if (!file.is_open())
	{
		// �t�@�C�����J�v��Ɏ��s�����ꍇ�̏���
		// ���ȏ��͊J���Ȃ������炻�̎��_�Ńv���O�����I��
		// return EXIT_FAILURE;

		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");
	}
	else
	{
		// �t�@�C���̃I�[�v���ɐ��������̂œǂݍ��݂��s��
		std::string str;	// ������char�̔z��������Ă���(�悤�Ȃ���)
		std::getline(file, str);

		file.close();

		printfDx(str.c_str());
	}
}

void SceneMapEdit::OutputBinary()
{
	std::fstream file;

	// �o�C�i�����[�h�ŊJ��
	// �g���q�͂Ȃ�ł��悢�@�o�C�i���f�[�^��\��bin, �f�[�^��\��dat�������W���[
	file.open("data/map/map.bin", std::ios::out | std::ios::binary);

	if (!file.is_open())
	{
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");
	}
	else
	{
		// �}�b�v�`�b�v�̔z�u�f�[�^���o�C�i���ŏo��

		// fstream��write�֐����g�p���ďo�͂���
		// ��������̂ǂ��ɒu���Ă��邩(�A�h���X)��
		// �������牽�o�C�g�o�͂��邩�A���w�肷��
		file.write((const char*)&m_chipData, sizeof(m_chipData));

		file.close();

		printfDx("�o�C�i���f�[�^�Ƃ��ă}�b�v�f�[�^���o�͂��܂���\n");
	}
}


void SceneMapEdit::InputBinary()
{
	std::fstream file;

	// �o�C�i�����[�h�ŊJ��
	file.open("data/map/map.bin", std::ios::in | std::ios::binary);

	if (!file.is_open())
	{
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");
	}
	else
	{
		// �ǂݍ��񂾃o�C�i���̓��e����������̃}�b�v�`�b�v���ɏ㏑������
		file.read((char*)&m_chipData, sizeof(m_chipData));

		file.close();

		printfDx("�o�C�i���f�[�^�Ƃ��ă}�b�v�f�[�^����͂��܂���\n");
	}
}