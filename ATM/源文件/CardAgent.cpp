
#include <fstream>
#include <string>
#include "CardAgent.h"

using std::ifstream;			using std::ios;
using std::ofstream;

using std::string;


// �ж����п��Ƿ���ں�̨
// ����ֵ��ID �����򷵻� true ������ m_index�����򷵻� false
bool CardAgent::IDExist(const std::string ID)
{
	char tmpID[ID_LENGTH];
	int count;
	bool flag = false;

	ifstream fin(CARD_DATA_FILE, ios::binary);
	if (!fin.is_open())
	{
		// ����������ļ���ʧ�ܣ�����Ϊ��ǰ��̨û�п��õ����п�����
		// ������еĲ�ѯ�������� false ����
		return flag;
	}
	
	fin.read((char*)&count, sizeof(int));
	
	for (int i = 0; i < count; i++)
	{
		fin.read(tmpID, ID_LENGTH);
		if (!ID.compare(tmpID))  // string::compare ��׼�����ú�������ͬ�򷵻�0����ͬ����ڻ�С��0
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


// ��֤�����Ƿ���ȷ
// ����ֵ����ȷ�򷵻� true�������򷵻� false
bool CardAgent::ValidatePass(const std::string password)
{
	ifstream fin(CARD_DATA_FILE, ios::binary);

	fin.seekg(sizeof(int) + m_index * sizeof(Card) + ID_LENGTH, SEEK_SET);

	char tmpPassword[PASSWORD_LENGTH];
	fin.read(tmpPassword, PASSWORD_LENGTH);  // ��ȡ7λ�����浽 tmpPassword �У����ں�����������֤
	fin.close();

	if (!password.compare(tmpPassword))
	{
		return true;
	}

	return false;
}


// ��ȡ���������п�����Ϣ
void CardAgent::GetCard()
{
	ifstream fin(CARD_DATA_FILE, ios::binary);

	fin.seekg(sizeof(int) + m_index * sizeof(Card), SEEK_SET);

	fin.read((char*)&m_card, sizeof(Card));  //��ȡ������Ϣ�������� m_card ��
	fin.close();
}


// ɾ����ǰ�ڴ��п�����Ϣ��ģ���˿�
void CardAgent::DelCard()
{
	m_index = -1;
	memset(&m_card, 0, sizeof(Card));  // �� m_card �е�ǰλ�ú���� sizeof(Card) ���ֽ��� 0 �滻������
}


// ����
void CardAgent::LockCard()
{
	m_card.isLocked = true;
	SaveCard();
}


// ȡ����޸����
void CardAgent::ModifyBalance(int amount)
{
	m_card.balance += amount;
	SaveCard();
}


// �������п����޸�ʵʱ���浽�ļ���
void CardAgent::SaveCard()
{
	// �Զ�дģʽ�򿪣���ʱ��������ļ������ҿ��Դ�ָ��λ�ö�д
	ofstream fout(CARD_DATA_FILE, ios::binary | ios::out | ios::in);

	fout.seekp(sizeof(int) + m_index * sizeof(Card), SEEK_SET);
	fout.write((char*)&m_card, sizeof(m_card));
	fout.close();
}


// �鿴���Ƿ���
bool CardAgent::IsLocked()
{
	return m_card.isLocked;
}


// ȡ��ʱ�ж�����Ƿ��㹻
bool CardAgent::BalanceIsEnough(int amount)
{
	return m_card.balance >= amount;
}


// ��ȡ���
int CardAgent::GetBalance()
{
	return m_card.balance;
}


// ��������ʱ�ж������Ƿ���ȷ
bool CardAgent::ComparePassword(std::string pass)
{
	return pass.compare(m_card.password) == 0 ? true : false;
}


// �޸�����
void CardAgent::ChangePassword(std::string password)
{
	for (int i = 0; i < PASSWORD_LENGTH; i++)
	{
		m_card.password[i] = password[i];
	}
	SaveCard();
}
