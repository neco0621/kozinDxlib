#pragma once

//�p�b�h�̏�Ԃ��擾����
namespace Pad
{
	//�p�b�h�̍X�V�����@1�t���[����1��s��
	void Update();

	//������Ă��邩���擾
	bool isPadPress(int key);
	//�����ꂽ�u�Ԃ��擾
	bool isPadTrigger(int key);
	//�������u�Ԃ��擾
	bool isPadRelase(int key);
}

