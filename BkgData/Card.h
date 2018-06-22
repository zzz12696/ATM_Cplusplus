#pragma once

typedef struct Card_ {
	char ID[13];			// ���� 13
	char password[7];		// ���� 7
	bool isLocked;			// ��ǿ�Ƭ�Ƿ��� 1
	int balance;			// ������� 4  ��25
} Card;


/*Cards.dat ʮ�������ļ�����
����������4λ��		05 00 00 00

����һ�ſ���
����	��13λ��		36 32 31 32 32 36 32 30 30 32 30 35 00
����	��7λ��		35 35 35 39 31 39 00
isLocked��1λ��	00 cc cc cc 
balance��4λ��	a0 8c 00 00 

���ڶ��ſ���
����	��13λ��		36 32 31 32 32 36 32 30 30 32 30 31 00
����	��7λ��		38 39 32 30 30 37 00
isLocked��1λ��	00 cc cc cc
balance��4λ��	50 14 00 00

�������ſ���
����	��13λ��		36 32 31 32 32 36 32 30 30 32 30 32 00
����	��7λ��		33 34 35 39 39 38 00
isLocked��1λ��	00 cc cc cc
balance��4λ��	40 1f 00 00

�������ſ���
����	��13λ��		36 32 31 32 32 36 32 30 30 32 30 33 00
����	��7λ��		37 38 38 31 32 33 00
isLocked��1λ��	00 cc cc cc
balance��4λ��	20 4e 00 00 

�������ſ���
����	��13λ��		36 32 31 32 32 36 32 30 30 32 30 34 00
����	��7λ��		30 39 30 38 33 37 00
isLocked��1λ��	00 cc cc cc
balance��4λ��	45 06 00 00
*/

/*ATM.dat ʮ�������ļ�����
balance��4λ��	20 4e 00 00
*/