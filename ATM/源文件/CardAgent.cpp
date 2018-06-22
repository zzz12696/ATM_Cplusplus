
#include <fstream>
#include <string>
#include "CardAgent.h"

using std::ifstream;			using std::ios;
using std::ofstream;

using std::string;


// 判断银行卡是否存在后台
// 返回值：ID 存在则返回 true 并设置 m_index，否则返回 false
bool CardAgent::IDExist(const std::string ID)
{
	char tmpID[ID_LENGTH];
	int count;
	bool flag = false;

	ifstream fin(CARD_DATA_FILE, ios::binary);
	if (!fin.is_open())
	{
		// 如果卡数据文件打开失败，则认为当前后台没有可用的银行卡数据
		// 因此所有的查询都将返回 false 即可
		return flag;
	}
	
	fin.read((char*)&count, sizeof(int));
	
	for (int i = 0; i < count; i++)
	{
		fin.read(tmpID, ID_LENGTH);
		if (!ID.compare(tmpID))  // string::compare 标准库内置函数，相同则返回0，不同则大于或小于0
		{
			flag = true;
			m_index = i;
			break;
		}

		fin.seekg(sizeof(Card) - ID_LENGTH, SEEK_CUR);
	}

	fin.close();
	return flag;
}


// 验证密码是否正确
// 返回值：正确则返回 true，错误则返回 false
bool CardAgent::ValidatePass(const std::string password)
{
	ifstream fin(CARD_DATA_FILE, ios::binary);

	fin.seekg(sizeof(int) + m_index * sizeof(Card) + ID_LENGTH, SEEK_SET);

	char tmpPassword[PASSWORD_LENGTH];
	fin.read(tmpPassword, PASSWORD_LENGTH);  // 读取7位，保存到 tmpPassword 中，用于后续的密码验证
	fin.close();

	if (!password.compare(tmpPassword))
	{
		return true;
	}

	return false;
}


// 获取操作的银行卡的信息
void CardAgent::GetCard()
{
	ifstream fin(CARD_DATA_FILE, ios::binary);

	fin.seekg(sizeof(int) + m_index * sizeof(Card), SEEK_SET);

	fin.read((char*)&m_card, sizeof(Card));  //获取卡的信息，保存在 m_card 中
	fin.close();
}


// 删除当前内存中卡的信息，模拟退卡
void CardAgent::DelCard()
{
	m_index = -1;
	memset(&m_card, 0, sizeof(Card));  // 将 m_card 中当前位置后面的 sizeof(Card) 个字节用 0 替换并返回
}


// 锁卡
void CardAgent::LockCard()
{
	m_card.isLocked = true;
	SaveCard();
}


// 取款后修改余额
void CardAgent::ModifyBalance(int amount)
{
	m_card.balance += amount;
	SaveCard();
}


// 将对银行卡的修改实时保存到文件中
void CardAgent::SaveCard()
{
	// 以读写模式打开，打开时不会清空文件内容且可以从指定位置读写
	ofstream fout(CARD_DATA_FILE, ios::binary | ios::out | ios::in);

	fout.seekp(sizeof(int) + m_index * sizeof(Card), SEEK_SET);
	fout.write((char*)&m_card, sizeof(m_card));
	fout.close();
}


// 查看卡是否被锁
bool CardAgent::IsLocked()
{
	return m_card.isLocked;
}


// 取款时判断余额是否足够
bool CardAgent::BalanceIsEnough(int amount)
{
	return m_card.balance >= amount;
}


// 获取余额
int CardAgent::GetBalance()
{
	return m_card.balance;
}


// 输入密码时判断密码是否正确
bool CardAgent::ComparePassword(std::string pass)
{
	return pass.compare(m_card.password) == 0 ? true : false;
}


// 修改密码
void CardAgent::ChangePassword(std::string password)
{
	for (int i = 0; i < PASSWORD_LENGTH; i++)
	{
		m_card.password[i] = password[i];
	}
	SaveCard();
}
