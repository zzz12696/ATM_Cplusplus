#pragma once

#include "Card.h"
#include "CardAgent.h"

//定义操作序号
#define WITHDRAW 1
#define CHECK_BALANCE 2
#define CHANGE_PASSWORD 3
#define TAKE_CARD 4

#define ATM_DATA_FILE "../BkgData/ATM.dat"

#define MAX_WITHDRAW_PER_DEAL 10000		// 最大单笔取款金额


class ATM {
private:
	int m_balance;				// ATM 机当前余额
	CardAgent m_cardAgent;		// 代理 ATM 与银行卡数据打交道

	// 登录系统，输入卡号以及验证密码
	void Login();

	// 退卡
	void Logout();

	// 插入银行卡
	void InsertCard();

	// 退卡
	void TakeCard();

	// 展示功能菜单
	int FuncMenu();

	// 取款
	void Withdraw();

	// 修改机内余额
	void ModifyBalance(int amount);

	// 启动时首先清点机内余额，用文件读取模拟清点过程
	bool CountBalance();

	// 实时更新 ATM 数据到文件
	void UpdateData();

	// 查询余额
	void CheckBalance();

	// 修改密码
	// 返回值：锁卡返回 -1，更改失败返回 -2，成功返回 1
	int ChangePassword();

public:
	// 启动 ATM，开始工作
	void run();
};