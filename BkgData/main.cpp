#include <iostream>
#include <fstream>
#include "Card.h"

#define CARD_DATA_FILE "Cards.dat"
#define ATM_DATA_FILE "ATM.dat"

using std::ofstream;		
using std::ios;
using std::cerr;  //��׼���������
using std::endl;
using std::ifstream;

int main()
{
	Card cards[5] = {
		"621226200205", "555919", false, 36000	,
		"621226200201", "892007", false, 5200	,
		"621226200202", "345998", false, 8000	,
		"621226200203", "788123", false, 20000	,
		"621226200204", "090837", false, 1605
	};

	ofstream fCards(CARD_DATA_FILE, ios::binary);

	if (!fCards.is_open())
	{
		cerr << "�� " << CARD_DATA_FILE << " �ļ�ʧ��" << endl;
		exit(1);
	}
	
	//�����ļ��ĸ�ʽ����ʼ���ĸ��ֽ��ǿ�������������͸��Ŷ����ſ�
	int count = 5;
	fCards.write((char*)&count, sizeof(int));

	for (int i = 0; i < 5; i++)
	{
		fCards.write((char*)&cards[i], sizeof(Card));
	}
	
	fCards.close();

	/***************************************************/

	ofstream fATM(ATM_DATA_FILE, ios::binary);

	if (!fATM.is_open())
	{
		cerr << "�� " << ATM_DATA_FILE << " �ļ�ʧ��" << endl;
		exit(1);
	}

	int ATMBalance = 20000;
	fATM.write((char*)&ATMBalance, sizeof(ATMBalance));
	fATM.close();

	return 0;
}