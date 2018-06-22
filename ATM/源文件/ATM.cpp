#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

#include "ATM.h"

using std::cout;
using std::endl;
using std::getline;
using std::cin;
using std::ofstream;
using std::ios;
using std::ifstream;

using std::string;


// ��ȡһ���������ò��� aInt ����
// ���������Դ��� 8 λ
// ����ֵ����ȷ�򷵻� true�������򷵻� flase
bool InputInt(int &aInt)
{
	string str;

	getline(cin, str);

	if (str.length() > 1 && str[0] == '0' || str.length() > 8)
	{
		return false;
	}

	for (unsigned int i = 0; i < str.length(); ++i)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}

	aInt = atoi(str.c_str());  // �� str ����ַ���ת������ֵ����ֵ�� aInt
	return true;
}


// ���� ATM
void ATM::run()
{
	// ����ʱ�������������
	CountBalance();

	while (1)
	{
		// ģ��忨��¼���̣���¼�ɹ��Ż᷵��
		InsertCard();

		int choice;
		bool exitSys = false;
		while (1)
		{
			choice = FuncMenu();

			switch (choice)
			{
			case WITHDRAW:
				Withdraw();
				break;
			case CHECK_BALANCE:
				CheckBalance();
				break;
			case CHANGE_PASSWORD:
				if (ChangePassword() == -1) exitSys = true;	// ����
				break;
			case TAKE_CARD:
				exitSys = true;
				break;
			default:
				break;
			}  // switch

			if (exitSys)
			{
				TakeCard();
				break;
			}
		} // while
	} // while
}


// ��¼���棬���в忨��������֤����
void ATM::Login()
{
	string inputID;
	string inputPass;

	while (1)
	{
		// ��֤�����Ƿ����
		cout << "*************��ӭʹ�ñ�ϵͳ**************" << endl;
		cout << "*  ���뿨�ţ� ";
		getline(cin, inputID);

		if (inputID.length() != 12)
		{
			cout << "*  �����п������ڣ�����������" << endl;
			continue;  // �ص� login ҳ��
		}
	
		bool IDIsExist = m_cardAgent.IDExist(inputID);
		if (!IDIsExist)  //TODO:������֧
		{
			cout << "*  �����п������ڣ�����������" << endl;
			continue;  // �ص� login ҳ��
		}
		else
		{
			m_cardAgent.GetCard();
			if (m_cardAgent.IsLocked())
			{
				cout << "*  �����п��Ѿ���������ǰ����̨�˹�������" << endl;
				cout << endl;
				TakeCard();
				continue;  // �ص� login ҳ��
			}
			else
			{
				// �����ڣ�û�б��������ž���֤�����Ƿ���ȷ����֤��������Ϊ 3 ��
				int i = 0;
				while (i < 3)
				{
					i++;
					cout << "*  �������룺 ";
					getline(cin, inputPass);  // �� getline �������뵽 inputPass �ַ���

					if (m_cardAgent.ValidatePass(inputPass))
					{
						// ������ȷ��ֱ�ӷ���
						return;
					}
					else
					{
						// ������󣬼���������ʾ��ͬ��ʾ
						if (i == 3)
						{
							// ���������������ﵽ 3 �Σ�����
							cout << "*  �����������ﵽ 3 �Σ���������" << endl;
							m_cardAgent.LockCard();
							TakeCard();
						}
						else
						{
							cout << "*  ����������������룡ʣ��" << 3 - i << "�λ���" << endl;
						}
					}
				}
			}
		}
	} // while
}


// �˳����޲�����ֻ��Ϊ�˸������ ATM �Ĺ�������
void ATM::Logout()
{
}


// ģ��忨��ʵ�ʼ������¼����
void ATM::InsertCard()
{
	Login();
}


// ģ���˿���ʵ�ʼ�ɾ����ǰ����������Ϣ
void ATM::TakeCard()
{
	m_cardAgent.DelCard();
	Logout();
}


// չʾ�˵�
// ����ֵ��ѡ��Ĳ˵���
int ATM::FuncMenu()
{
	cout << endl;
	cout << "*  1��ȡ��" << endl;
	cout << "*  2����ѯ���" << endl;
	cout << "*  3���޸�����" << endl;
	cout << "*  4���˳�ϵͳ" << endl << endl;

	int choice;
	while (1)
	{
		cout << "*  ���ѡ�� ";
		if (!InputInt(choice))
		{
			cout << "*  ������������������" << endl;
			continue;
		}

		if (choice >=1 && choice <= 4)
		{
			return choice;
		}
		cout << "*  ������������������" << endl;
	}
}


// ȡ��
void ATM::Withdraw()
{
	int amount;

	cout << "*  ������ȡ��� ";

	if (!InputInt(amount))
	{
		// ֻ��һ�ζ�ȡ���Ļ��ᣬ��������򷵻ز˵�
		cout << "*  ������������������" << endl;
		return;
	}
	
	if (!m_cardAgent.BalanceIsEnough(amount))
	{
		cout << "*  �������㣡ȡ��ʧ��" << endl;
		return;
	}

	if (amount > MAX_WITHDRAW_PER_DEAL)
	{
		cout << "*  ȡ���������ȡ�������ޣ�ȡ��ʧ��" << endl;
		return;
	}

	if (amount > m_balance)
	{
		cout << "*  �Բ��𣬵�ǰ ATM ���㣬ȡ��ʧ��" << endl;
		return;
	}

	m_cardAgent.ModifyBalance(-1 * amount);  // �޸��˻����
	ModifyBalance(-1 * amount);  // �޸�ATM���

	cout << "*  ȡ��ɹ���" << endl;
}


// ʵʱ���»������
void ATM::ModifyBalance(int amount)
{
	m_balance += amount;
	UpdateData();
}


// ����ʱ���������
bool ATM::CountBalance()
{

	ifstream fin(ATM_DATA_FILE);

	if (fin.is_open())
	{
		fin.read((char*)&m_balance, sizeof(int));
		fin.close();
		return true;
	}
	else {
		// �������ļ���ʧ�ܣ�����Ϊ��ǰ�������Ϊ 0
		cout << "*  ��ǰ ATM ���Ϊ 0������ϵ��ع�����Ա���д���" << endl;
		m_balance = 0;
		return false;
	}
}


// ���� ATM ���ݵ��ļ���
void ATM::UpdateData()
{
	// �Զ�дģʽ�򿪣���ʱ��������ļ������ҿ��Դ�ָ��λ�ö�д
	ofstream fout(ATM_DATA_FILE, ios::binary | ios::out | ios::in);

	fout.write((char*)&m_balance, sizeof(m_balance));
	fout.close();
}


// ��ѯ�˻����
void ATM::CheckBalance()
{
	cout << "*  �������Ϊ�� " << m_cardAgent.GetBalance() << " Ԫ" << endl;
}


/*
* ���ܣ��޸����п�����
* ע�⣺�޸����п�����ͬ���������뵱ǰ������֤��������֤����ͬ����������������
*/
int ATM::ChangePassword()
{
	string currentPassword;
	cout << "*  �����뵱ǰ���룺 ";
	getline(cin, currentPassword);

	int i;
	for (i = 1; i < 3; i++)
	{
		if (!m_cardAgent.ComparePassword(currentPassword))
		{
			cout << "*  ���������뵱ǰ���룺 ";
			getline(cin, currentPassword);
			continue;
		}
		break;
	}

	if (i >= 3)
	{
		// ��֤��ǰ�����������ﵽ 3 �Σ�����
		m_cardAgent.LockCard();
		cout << "*  ��������ﵽ 3 �Σ�����" << endl;
		return -1;
	}
	else {
		// ������ȷ
		string newPassword;
		cout << "*  �����������룺 ";
		getline(cin, newPassword);

		bool flag = false;
		if (newPassword.length() == (PASSWORD_LENGTH - 1))
		{
			for (int i = 0; i < (PASSWORD_LENGTH - 1); i++)
			{
				if (!isdigit(newPassword[i]))
				{
					cout << "*  �����ʽ����" << endl;
					return -2;
				}
			}

			string secondPass;
			cout << "*  ���ٴ����������룺 ";
			getline(cin, secondPass);
			if (secondPass.compare(newPassword))
			{
				cout << "*  ����ȷ�ϴ���" << endl;
				return -2;
			}
			else {
				// �޸�����
				m_cardAgent.ChangePassword(newPassword);
				cout << "*  �޸�����ɹ�" << endl;
				return 1;
			}
		}
		else {
			cout << "*  �����ʽ����" << endl;
			return -2;
		} // if (newPassword.length() == 6)

	} // if (i >= 3)
}