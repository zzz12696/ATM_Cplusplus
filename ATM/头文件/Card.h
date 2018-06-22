#pragma once

#define ID_LENGTH 13
#define PASSWORD_LENGTH 7

typedef struct Card_ {
	char ID[ID_LENGTH];					// 卡号
	char password[PASSWORD_LENGTH];		// 密码
	bool isLocked;						// 标记卡片是否被锁
	int balance;						// 卡内余额
} Card;