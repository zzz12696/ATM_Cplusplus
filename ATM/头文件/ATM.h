#pragma once

#include "Card.h"
#include "CardAgent.h"

//����������
#define WITHDRAW 1
#define CHECK_BALANCE 2
#define CHANGE_PASSWORD 3
#define TAKE_CARD 4

#define ATM_DATA_FILE "../BkgData/ATM.dat"

#define MAX_WITHDRAW_PER_DEAL 10000		// ��󵥱�ȡ����


class ATM {
private:
	int m_balance;				// ATM ����ǰ���
	CardAgent m_cardAgent;		// ���� ATM �����п����ݴ򽻵�

	// ��¼ϵͳ�����뿨���Լ���֤����
	void Login();

	// �˿�
	void Logout();

	// �������п�
	void InsertCard();

	// �˿�
	void TakeCard();

	// չʾ���ܲ˵�
	int FuncMenu();

	// ȡ��
	void Withdraw();

	// �޸Ļ������
	void ModifyBalance(int amount);

	// ����ʱ���������������ļ���ȡģ��������
	bool CountBalance();

	// ʵʱ���� ATM ���ݵ��ļ�
	void UpdateData();

	// ��ѯ���
	void CheckBalance();

	// �޸�����
	// ����ֵ���������� -1������ʧ�ܷ��� -2���ɹ����� 1
	int ChangePassword();

public:
	// ���� ATM����ʼ����
	void run();
};