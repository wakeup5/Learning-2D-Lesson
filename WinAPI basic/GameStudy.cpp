#include "stdafx.h"
#include "GameStudy.h"

//�ʱ�ȭ
HRESULT GameStudy::initialize(void)
{
	GameNode::initialize();	

	return S_OK;
}

//����
void GameStudy::release(void)
{
	GameNode::release();
}

//ȭ�鰻��
void GameStudy::update(void)
{
	GameNode::update();
 
}

//ȭ�����
void GameStudy::render(HDC hdc)
{
  
}





//����

//���̽� ��Ű
//���� ������
//�и� ���� ������
//���� ���� ħ�� ����

//���� 2
//�����̴� ������ ����. ũ�Ⱑ �� �ٸ� �����ص��� 10��
//���������� ���� �ִ� ����
//ó�� ���� �������� ���� �ڿ� ���� ������ �������.
//���� �ε����� �ݻ��
//�밡���� �����ϰ� �ִ�.
//�˿�Ű�� ������ ���� ���� ����.
