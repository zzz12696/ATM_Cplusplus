#pragma once

#include <string>
#include "Card.h"

#define CARD_DATA_FILE "../BkgData/Cards.dat"


// �������̨�����ݴ򽻵���������
class CardAgent
{
private:
	Card m_card;
	int m_index;		// ��ǰ��λ�ں�̨���ļ��е��±꣬������дЧ��

public:
	bool IDExist(const std::string ID);
	bool ValidatePass(const std::string password);

	void GetCard();
	void DelCard();
	void LockCard();
	void ModifyBalance(int amount);
	bool BalanceIsEnough(int amount);
	int GetBalance();
	bool ComparePassword(std::string password);
	void ChangePassword(std::string password);
	void SaveCard();
	bool IsLocked();
};

