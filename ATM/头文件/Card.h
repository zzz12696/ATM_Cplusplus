#pragma once

#define ID_LENGTH 13
#define PASSWORD_LENGTH 7

typedef struct Card_ {
	char ID[ID_LENGTH];					// ����
	char password[PASSWORD_LENGTH];		// ����
	bool isLocked;						// ��ǿ�Ƭ�Ƿ���
	int balance;						// �������
} Card;