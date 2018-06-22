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


// 读取一个整数，用参数 aInt 接收
// 整数不可以大于 8 位
// 返回值：正确则返回 true，错误则返回 flase
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

	aInt = atoi(str.c_str());  // 把 str 这个字符串转换成数值并赋值给 aInt
	return true;
}


// 启动 ATM
void ATM::run()
{
	// 启动时首先清点机内余额
	CountBalance();

	while (1)
	{
		// 模拟插卡登录过程，登录成功才会返回
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
				if (ChangePassword() == -1) exitSys = true;	// 锁卡
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


// 登录界面，进行插卡和密码验证操作
void ATM::Login()
{
	string inputID;
	string inputPass;

	while (1)
	{
		// 验证卡号是否存在
		cout << "*************欢迎使用本系统**************" << endl;
		cout << "*  输入卡号： ";
		getline(cin, inputID);

		if (inputID.length() != 12)
		{
			cout << "*  该银行卡不存在，请重新输入" << endl;
			continue;  // 回到 login 页面
		}
	
		bool IDIsExist = m_cardAgent.IDExist(inputID);
		if (!IDIsExist)  //TODO:锁卡分支
		{
			cout << "*  该银行卡不存在，请重新输入" << endl;
			continue;  // 回到 login 页面
		}
		else
		{
			m_cardAgent.GetCard();
			if (m_cardAgent.IsLocked())
			{
				cout << "*  该银行卡已经被锁，请前往柜台人工解锁！" << endl;
				cout << endl;
				TakeCard();
				continue;  // 回到 login 页面
			}
			else
			{
				// 卡存在，没有被锁，接着就验证密码是否正确，验证次数限制为 3 次
				int i = 0;
				while (i < 3)
				{
					i++;
					cout << "*  输入密码： ";
					getline(cin, inputPass);  // 用 getline 返回输入到 inputPass 字符串

					if (m_cardAgent.ValidatePass(inputPass))
					{
						// 密码正确，直接返回
						return;
					}
					else
					{
						// 密码错误，检测次数，显示不同提示
						if (i == 3)
						{
							// 输入密码错误次数达到 3 次，锁卡
							cout << "*  输入密码错误达到 3 次，已锁卡！" << endl;
							m_cardAgent.LockCard();
							TakeCard();
						}
						else
						{
							cout << "*  密码错误，请重新输入！剩余" << 3 - i << "次机会" << endl;
						}
					}
				}
			}
		}
	} // while
}


// 退出，无操作，只是为了更好理解 ATM 的工作流程
void ATM::Logout()
{
}


// 模拟插卡，实质即进入登录界面
void ATM::InsertCard()
{
	Login();
}


// 模拟退卡，实质即删除当前操作卡的信息
void ATM::TakeCard()
{
	m_cardAgent.DelCard();
	Logout();
}


// 展示菜单
// 返回值：选择的菜单项
int ATM::FuncMenu()
{
	cout << endl;
	cout << "*  1、取款" << endl;
	cout << "*  2、查询余额" << endl;
	cout << "*  3、修改密码" << endl;
	cout << "*  4、退出系统" << endl << endl;

	int choice;
	while (1)
	{
		cout << "*  你的选择： ";
		if (!InputInt(choice))
		{
			cout << "*  输入有误，请重新输入" << endl;
			continue;
		}

		if (choice >=1 && choice <= 4)
		{
			return choice;
		}
		cout << "*  输入有误，请重新输入" << endl;
	}
}


// 取款
void ATM::Withdraw()
{
	int amount;

	cout << "*  请输入取款金额： ";

	if (!InputInt(amount))
	{
		// 只有一次读取金额的机会，输入错误则返回菜单
		cout << "*  输入有误，请输入数字" << endl;
		return;
	}
	
	if (!m_cardAgent.BalanceIsEnough(amount))
	{
		cout << "*  卡内余额不足！取款失败" << endl;
		return;
	}

	if (amount > MAX_WITHDRAW_PER_DEAL)
	{
		cout << "*  取款金额超过单笔取款金额上限，取款失败" << endl;
		return;
	}

	if (amount > m_balance)
	{
		cout << "*  对不起，当前 ATM 余额不足，取款失败" << endl;
		return;
	}

	m_cardAgent.ModifyBalance(-1 * amount);  // 修改账户余额
	ModifyBalance(-1 * amount);  // 修改ATM余额

	cout << "*  取款成功！" << endl;
}


// 实时更新机内余额
void ATM::ModifyBalance(int amount)
{
	m_balance += amount;
	UpdateData();
}


// 启动时清点机内余额
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
		// 若数据文件打开失败，则认为当前机内余额为 0
		cout << "*  当前 ATM 余额为 0，请联系相关工作人员进行处理" << endl;
		m_balance = 0;
		return false;
	}
}


// 更新 ATM 数据到文件中
void ATM::UpdateData()
{
	// 以读写模式打开，打开时不会清空文件内容且可以从指定位置读写
	ofstream fout(ATM_DATA_FILE, ios::binary | ios::out | ios::in);

	fout.write((char*)&m_balance, sizeof(m_balance));
	fout.close();
}


// 查询账户余额
void ATM::CheckBalance()
{
	cout << "*  卡内余额为： " << m_cardAgent.GetBalance() << " 元" << endl;
}


/*
* 功能：修改银行卡密码
* 注意：修改银行卡密码同样进行输入当前密码验证，三次验证错误同样会引发锁卡操作
*/
int ATM::ChangePassword()
{
	string currentPassword;
	cout << "*  请输入当前密码： ";
	getline(cin, currentPassword);

	int i;
	for (i = 1; i < 3; i++)
	{
		if (!m_cardAgent.ComparePassword(currentPassword))
		{
			cout << "*  错误！请输入当前密码： ";
			getline(cin, currentPassword);
			continue;
		}
		break;
	}

	if (i >= 3)
	{
		// 验证当前密码错误次数达到 3 次，锁卡
		m_cardAgent.LockCard();
		cout << "*  错误次数达到 3 次，锁卡" << endl;
		return -1;
	}
	else {
		// 密码正确
		string newPassword;
		cout << "*  请输入新密码： ";
		getline(cin, newPassword);

		bool flag = false;
		if (newPassword.length() == (PASSWORD_LENGTH - 1))
		{
			for (int i = 0; i < (PASSWORD_LENGTH - 1); i++)
			{
				if (!isdigit(newPassword[i]))
				{
					cout << "*  密码格式错误！" << endl;
					return -2;
				}
			}

			string secondPass;
			cout << "*  请再次输入新密码： ";
			getline(cin, secondPass);
			if (secondPass.compare(newPassword))
			{
				cout << "*  密码确认错误！" << endl;
				return -2;
			}
			else {
				// 修改密码
				m_cardAgent.ChangePassword(newPassword);
				cout << "*  修改密码成功" << endl;
				return 1;
			}
		}
		else {
			cout << "*  密码格式错误！" << endl;
			return -2;
		} // if (newPassword.length() == 6)

	} // if (i >= 3)
}