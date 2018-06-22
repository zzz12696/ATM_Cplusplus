#pragma once

#include <string>
#include "Card.h"

#define CARD_DATA_FILE "../BkgData/Cards.dat"


// 用于与后台卡数据打交道的数据类
class CardAgent
{
private:
	Card m_card;
	int m_index;		// 当前卡位于后台卡文件中的下标，提升读写效率

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

