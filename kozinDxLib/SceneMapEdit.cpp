#include "SceneMapEdit.h"
#include "DxLib.h"
#include <cassert>

#include "Pad.h"

//�t�@�C���̏o�͂Ɏg�p����
#include <iostream>
#include <fstream>
#include <string>  //��������������߂̃N���X
#include <cstdlib>
using namespace std;

namespace
{
	//�J�[�\���ړ����s�[�g�t���[��
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
	//�O���t�B�b�N�̃n���h��
	m_bgHandle = LoadGraph("data/bg.png");
	assert(m_bgHandle != -1);

	//�}�b�v�`�b�v�̐��𐔂���
	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_bgHandle, &graphW, &graphH);

	m_graphChipNumX = graphW / kChipWidth;
	m_graphChipNumY = graphH / kChipHeight;

	//�`�b�v�z�u���̍쐬
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
	//�J�[�\���̈ړ�
	//�p�b�h�̏\���L�[���g�p���ăJ�[�\�����ړ�
	//int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//z�L�[
	if (Pad::isPadTrigger(PAD_INPUT_1))
	{
		//�z��͈̔͊O�A�N�Z�X�����m���邽�߂�assert
		assert(m_cursorX >= 0 && m_cursorX < kChipNumX);
		assert(m_cursorY >= 0 && m_cursorY < kChipNumY);

		//�I�����Ă���}�b�v�`�b�v�̔ԍ���+1
		m_chipData[m_cursorY][m_cursorX]++;

		//�O���t�B�b�N���ɑ��݂���}�b�v�`�b�v�̐�
		int chipNum = GetGraphChipNum();

		//Chip�̔ԍ���0�Ԃ���̒ʂ��ԍ��ŊǗ����Ă���
		//Chip��10���Ɓ@�ʂ��ԍ���0�`9

		if (m_chipData[m_cursorY][m_cursorX] > chipNum - 1)
		{
			m_chipData[m_cursorY][m_cursorX] = 0;
		}
	}
	//x�L�[
	if (Pad::isPadTrigger(PAD_INPUT_2))
	{
		//�z��͈̔͊O�A�N�Z�X�����m���邽�߂�assert
		assert(m_cursorX >= 0 && m_cursorX < kChipNumX);
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

	//�t�@�C���o�̓e�X�g      c�L�[
	if (Pad::isPadTrigger(PAD_INPUT_3))
	{
		OutputText();
		OutputBinary();
	}

	//�t�@�C���ǂݍ��݃e�X�g
	if (Pad::isPadTrigger(PAD_INPUT_4))      //A�L�[
	{
		InputText();
		InputBinary();
	}
#if false
	//test
	if (false)
	{
		fstream file;
		file.open("test.txt", ios::in || ios::out);   //�����̃t���O�𓯎��Ɏw��\
	}
#endif




	//�ۑ�̎��ȗ�����
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
	//������ւ̃J�[�\���ړ�
	if (Pad::isPadPress(PAD_INPUT_UP))
	{
		m_upRipeatFrame++;
		if ((m_upRipeatFrame >= kCursorRepeatFrame) ||
			Pad::isPadTrigger(PAD_INPUT_UP))

		{
			m_upRipeatFrame = 0;

			//�J�[�\���ړ��̏���
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
	//�������ւ̃J�[�\���ړ�
	if (Pad::isPadPress(PAD_INPUT_DOWN))
	{
		m_downRipeatFrame++;
		if ((m_downRipeatFrame >= kCursorRepeatFrame) ||
			Pad::isPadTrigger(PAD_INPUT_DOWN))

		{
			m_downRipeatFrame = 0;

			//�J�[�\���ړ��̏���
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
	//�������ւ̃J�[�\���ړ�
	if (Pad::isPadPress(PAD_INPUT_LEFT))
	{
		m_leftRipeatFrame++;
		if ((m_leftRipeatFrame >= kCursorRepeatFrame) ||
			Pad::isPadTrigger(PAD_INPUT_LEFT))

		{
			m_leftRipeatFrame = 0;

			//�J�[�\���ړ��̏���
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
	//�E�����ւ̃J�[�\���ړ�
	if (Pad::isPadPress(PAD_INPUT_RIGHT))
	{
		m_rightRipeatFrame++;
		if ((m_rightRipeatFrame >= kCursorRepeatFrame) ||
			Pad::isPadTrigger(PAD_INPUT_RIGHT))

		{
			m_rightRipeatFrame = 0;

			//�J�[�\���ړ��̏���
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
			//���̔ԍ��̃`�b�v�ŕ~���l�߂�
			int chipNo = m_chipData[y][x];



			//�}�b�v�`�b�v�̃O���t�B�b�N�؂�o�����W
			int srcX = kChipWidth * (chipNo % m_graphChipNumX);
			int srcY = kChipHeight * (chipNo / m_graphChipNumX);

			//DrawGraph(0, 0, m_handle, true);

			DrawRectGraph(x * kChipWidth, y * kChipHeight,
				srcX, srcY, kChipWidth, kChipHeight, m_bgHandle, true);

		}

	}

	//�O���b�h�̕\��

	//�c��
	for (int x = 0; x < kChipNumX; x++)
	{
		DrawLine(x * kChipWidth, 0, x * kChipWidth, Game::kScreenHeight, GetColor(255, 255, 255));
	}
	//����
	for (int y = 0; y < kChipNumY; y++)
	{
		DrawLine(0, y * kChipHeight, Game::kScreenWidth, y * kChipHeight, GetColor(255, 255, 255));
	}

	//���ݑI�����Ă���`�b�v�ɃJ�[�\����\��
	int cursorPosX = m_cursorX * kChipWidth;
	int cursorPosY = m_cursorY * kChipHeight;
	DrawBox(cursorPosX, cursorPosY, cursorPosX + kChipWidth,
		cursorPosY + kChipHeight, GetColor(255, 255, 0), false);
	//���菬�����l�p��`�悵�Đ��̑����l�p�ɂ���
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
	file.open("test.txt", ios::out);     //�t�@�C�����J���@�@�@�o�͂������̂�ios::out

	if (!file.is_open())
	{
		//return EXIT_FAILURE;   //���ȏ��͊J���Ȃ������炻�̎��_�Ńv���O�����I��
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");
	}
	else
	{
		//�t�@�C�����J�����ꍇ�̏���
		//file << "�t�@�C���ɏ������񂶂Ⴆ�B" << endl;   //open�����t�@�C���ɏ�������

		//���l�̏������݃e�X�g
		//int num = 100;
		//file << num << endl;

		//�쐬�����}�b�v�̃f�[�^���e�L�X�g�ŏo�͂���
		for (int y = 0; y < kChipNumY; y++)
		{
			file << "{";
			for (int x = 0; x < kChipNumX; x++)
			{
				if (x == kChipNumX - 1)    //�Ō�̂�","�͏o�͂��Ȃ�
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


		printfDx("�t�@�C���ɏ������݂��s���܂���\n");
	}
}

void SceneMapEdit::InputText()
{
	fstream file;
	file.open("test.txt", ios::in);  //�ǂݍ��ގ���ios::in�ŊJ��
	//�t�@�C�����J���̂Ɏ��s�����ꍇ
	if (!file.is_open())
	{
		//return EXIT_FAILURE;   //���ȏ��͊J���Ȃ������炻�̎��_�Ńv���O�����I��
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");
	}
	else
	{
		//�t�@�C���̃I�[�v���ɐ��������̂œǂݍ��݂��s��
		string str;
		getline(file, str);
		file.close();

		printfDx(str.c_str());
	}
}

void SceneMapEdit::OutputBinary()
{
	fstream file;
	file.open("map.bin", ios::out | ios::binary);     //�g���q�͂Ȃ�ł��悢�@�o�C�i���f�[�^��\��bin,�f�[�^��\��dat�������W���[

	//�t�@�C�����J���̂Ɏ��s�����ꍇ�̏���
	if (!file.is_open())
	{
		//�t�@�C�����J���Ȃ������ꍇ�̏���
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");
	}
	else
	{
		//�t�@�C���I�[�v���ɐ�������
		//�}�b�v�`�b�v�̔z�u�f�[�^���o�C�i���ŏo��

		//fstream��write�֐����g�p���ďo�͂���
		//��������̂ǂ��ɒu����Ă��邩�i�A�h���X�j��
		//�������牽�o�C�g�o�͂��邩�A���w�肷��
		file.write((const char*)&(m_chipData[0][0]), sizeof(int) * kChipNumX * kChipNumY);
		file.close();

		printfDx("�o�C�i���f�[�^�Ƃ��ă}�b�v�f�[�^���o�͂��܂���\n");
	}
}

void SceneMapEdit::InputBinary()
{
	fstream file;
	//�o�C�i�����[�h�ŊJ��
	file.open("map.bin", ios::in | ios::binary);

	//�t�@�C�����J���̂Ɏ��s�����ꍇ�̏���
	if (!file.is_open())
	{
		//�t�@�C�����J���Ȃ������ꍇ�̏���
		//return EXIT_FAILURE; //���ȏ��͊J���Ȃ������炻�̎��_�Ńv���O�����I��
		printfDx("�t�@�C�����J���̂Ɏ��s���܂���\n");
	}
	else
	{
		//�t�@�C���I�[�v���ɐ�������
		//�ǂݍ��񂾃o�C�i���̓��e����������̃}�b�v�`�b�v���ɏ㏑������
		file.read((char*)&(m_chipData[0][0]), sizeof(int) * kChipNumX * kChipNumY);
		file.close();

		printfDx("�o�C�i���f�[�^��ǂݍ���Ń}�b�v�f�[�^�ɂ��܂���\n");
	}
}
