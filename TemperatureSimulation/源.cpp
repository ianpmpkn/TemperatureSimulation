#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <fstream> 
#include <string>
#include <time.h>
#include <algorithm>
#include <iostream>
#include <stdlib.h>

using namespace std;

const int EACHDAY = 96;
const int REVERSE = 1;
const int FORWARD = 2;
const int STANBY = 3;

int getRandom(int left, int right) {
	return rand() % (right - left + 1) + left;
}

bool getDice(int p) {
	if (getRandom(0, 100) <= p) {
		return true;
	}
	else
		return false;
}

int getTriDice(int p1, int p2) {
	//p1<p2
	int rd = getRandom(0, 100);
	if (rd <= p1) {
		return REVERSE;
	}
	else if (rd >= p1 && rd <= (p1 + p2)) {
		return FORWARD;
	}
	else
		return STANBY;
}

//��Χ��0��1�ĸ�����
float getRandomFloat() {
	return (rand() / double(RAND_MAX));
}

//��Χ��0.9��1.1���¶ȱ仯����
float getRandomA() {
	float rd = getRandom(9,11);
	return rd / 10;
}

////��Χ��-0.1��0.1��֮����¶ȱ仯
//float getRandomTempChange() {
//	float rd = 0;
//	for (int i = 0; i < 10; i++) {
//		rd += (getRandomFloat() / 100);
//	}
//	if (getDice(50))
//		return rd;
//	else
//		return -rd;
//}

class SingleDay {
public:
	SingleDay(int ThisYear, int ThisMonth, int ThisDay, float LastTemp);

	int Year;
	int Month;
	int Day;

	//ȡ��ʱ��
	string Time[EACHDAY];
	//ȡ���¶�
	float Temp[EACHDAY];
	float HighTemp;
	float LowTemp;
	/*float AvgTemp;*/

protected:
	//�������¸���
	int DForwardP;
	//���콵�¸���
	int DReverseP;
	//ҹ���¸���
	int NForwardP;
	//ҹ�����¸���
	int NReverseP;

	//�¶ȸı�ϵ��
	float RiseA;
	float FallA;
	float FallAL;

	//��ƽ���������
	float AvgTopTemp;
	//��ƽ���������
	float AvgBottomTemp;

	//����������£���ֹͻ��
	float FirstTemp;

	//�ճ�
	int Sunrise;
	//����
	int Highnoon;
	//����
	int Sunset;

private:
	string TimeEXP(int rd);
	bool isExist(int* p,int num, int val);
};

//ʱ��ת����
string SingleDay::TimeEXP(int rd) {
	int hour = rd / 60;
	int minute = rd % 60;
	string left;
	string right;

	if (hour < 10) 
		left = "0" + to_string(hour);
	else
		left = to_string(hour);

	if (minute < 10)
		right = "0" + to_string(minute);
	else
		right = to_string(minute);

	return to_string(Year) + "/" + to_string(Month) + "/" + to_string(Day) + " " + left + ":" + right;
}

bool  SingleDay::isExist(int* p, int num, int val) {
	for (int i = 0; i < num; i++) {
		if (p[i] == val) {
			return true;
		}
	}
	return false;
}

SingleDay::SingleDay(int ThisYear, int ThisMonth, int ThisDay, float LastTemp) {

	Year = ThisYear;
	Month = ThisMonth;
	Day = ThisDay;
	FirstTemp = LastTemp;

	 switch (Month)
	 {
	 case 1:DForwardP = 91; DReverseP = 3; NForwardP = 75; NReverseP = 1;  AvgTopTemp = 2; AvgBottomTemp = -9; Sunrise = 455; Highnoon = 737; Sunset = 1020; break;
	 case 2:DForwardP = 91; DReverseP = 3; NForwardP = 74; NReverseP = 1;  AvgTopTemp = 5; AvgBottomTemp = -6; Sunrise = 443; Highnoon = 747; Sunset = 1052; break;
	 case 3:DForwardP = 92; DReverseP = 4; NForwardP = 73; NReverseP = 2;  AvgTopTemp = 12; AvgBottomTemp = 0; Sunrise = 406; Highnoon = 746; Sunset = 1086; break;
	 case 4:DForwardP = 92; DReverseP = 4; NForwardP = 72; NReverseP = 2;  AvgTopTemp = 20; AvgBottomTemp = 8; Sunrise = 357; Highnoon = 738; Sunset = 1118; break;
	 case 5:DForwardP = 93; DReverseP = 5; NForwardP = 72; NReverseP = 3;  AvgTopTemp = 26; AvgBottomTemp = 14; Sunrise = 313; Highnoon = 731; Sunset = 1148; break;
	 case 6:DForwardP = 94; DReverseP = 5; NForwardP = 71; NReverseP = 4;  AvgTopTemp = 30; AvgBottomTemp = 19; Sunrise = 287; Highnoon = 732; Sunset = 1176; break;
	 case 7:DForwardP = 95; DReverseP = 5; NForwardP = 71; NReverseP = 5;  AvgTopTemp = 31; AvgBottomTemp = 22; Sunrise = 289; Highnoon = 738; Sunset = 1186; break;
	 case 8:DForwardP = 95; DReverseP = 5; NForwardP = 70; NReverseP = 5;  AvgTopTemp = 30; AvgBottomTemp = 21; Sunrise = 313; Highnoon = 740; Sunset = 1168; break;
	 case 9:DForwardP = 94; DReverseP = 5; NForwardP = 71; NReverseP = 4;  AvgTopTemp = 26; AvgBottomTemp = 15; Sunrise = 342; Highnoon = 734; Sunset = 1125; break;
	 case 10:DForwardP = 93; DReverseP = 5; NForwardP = 72; NReverseP = 3;  AvgTopTemp = 19; AvgBottomTemp = 8; Sunrise = 370; Highnoon = 723; Sunset = 1076; break;
	 case 11:DForwardP = 92; DReverseP = 5; NForwardP = 73; NReverseP = 2;  AvgTopTemp = 10; AvgBottomTemp = 0; Sunrise = 403; Highnoon = 717; Sunset = 1032; break;
	 case 12:DForwardP = 91; DReverseP = 5; NForwardP = 74; NReverseP = 1;  AvgTopTemp = 3; AvgBottomTemp = -6; Sunrise = 436; Highnoon = 723; Sunset = 1010; break;

	 default:
		 break;
	 }

	auto RD = new int[EACHDAY];

	//�ؼ�ʱ��
	int MyBottomTime = Sunrise;
	int MyTopTime = (Highnoon + Sunset) / 2;

	//�ؼ��¶�
	auto MyTopTemp = AvgTopTemp;
	auto MyBottomTemp = AvgBottomTemp;
	auto MyFirstTemp = FirstTemp;

	//�ҵ��ؼ�ʱ�������
	int BottomIndex = 0;
	int TopIndex = 0;

	//������
	int tridice;

	//���ÿ�չؼ��¶�
	if (getDice(50))
		MyTopTemp += getRandomFloat() * 2;
	else
		MyTopTemp -= getRandomFloat() * 2;

	if (getDice(50))
		MyBottomTemp += getRandomFloat() * 2;
	else
		MyBottomTemp -= getRandomFloat() * 2;

	//���ÿ�չؼ�ʱ��
	MyBottomTime -= getRandom(0, 30);
	MyTopTime += getRandom(-10, 10);

	RD[0] = MyBottomTime;
	RD[1] = MyTopTime;

	//�������ϵ��
	RiseA = (MyTopTemp - MyBottomTemp) / (MyTopTime - MyBottomTime);
	FallA = (MyTopTemp - MyBottomTemp) / (1440 - (MyTopTime - MyBottomTime));
	FallAL = (MyFirstTemp - MyBottomTemp) / MyBottomTime;

	//��òɼ�ʱ����Ϣ
	for (int i = 2; i < EACHDAY; i++) {
		int rd = getRandom(0, 1440);
		if (!isExist(RD, 2 + i, rd)) {
			RD[i] = rd;
		}
		else {
			i = i - 1;
		}
	} 

	cout << "MyTopTime:" << TimeEXP(MyTopTime) << endl;
	cout << "MyBottomTime:" << TimeEXP(MyBottomTime) << endl;
	cout << "MyTopTemp:" << MyTopTemp << endl;
	cout << "MyBottomTemp:" << MyBottomTemp << endl;
	cout << "RiseA:" << RiseA << endl;
	cout << "FallA:" << FallA << endl;
	cout << endl;


	//RD�ǵ�������
	sort(RD, RD + EACHDAY);

	//ָ���ؼ����¶�
	for (int i = 0; i < EACHDAY; i++) {
		//cout << RD[i] << endl;

		//��дʱ������
		Time[i] = TimeEXP(RD[i]);

		if (RD[i] == MyBottomTime){
			Temp[i] = MyBottomTemp ;
			BottomIndex = i;
		}
		else if (RD[i] == MyTopTime) {
			//Temp[i] = MyTopTemp ;
			TopIndex = i;
		}

		//cout << Time[i] << endl;
	}

	//����ҹʱ���

	if (BottomIndex != 0) {
		for (int i = BottomIndex; i > 0; i--) {
			tridice = getTriDice(NReverseP, NForwardP);
			if (tridice == REVERSE) {
				Temp[i - 1] = Temp[i] - (RD[i] - RD[i - 1]) * RiseA * getRandomA();
				//cout << Time[i - 1] << "," << Temp[i - 1] << endl;
			}
			else if (tridice == FORWARD)
			{
				Temp[i - 1] = Temp[i] + (RD[i] - RD[i - 1]) * FallAL * getRandomA();
				//cout << Time[i - 1] << "," << Temp[i - 1] << endl;
			}
			else if (tridice == STANBY)
			{
				Temp[i - 1] = Temp[i] ;
				//cout << Time[i - 1] << "," << Temp[i - 1] << endl;
			}
		}
	}	

	//cout << Time[BottomIndex] << "," << Temp[BottomIndex] << endl;

	for (int i = BottomIndex + 1; i < EACHDAY; i++) {
		//�ռ�ʱ���
		if (RD[i] >= MyBottomTime && RD[i] <= MyTopTime) {
			tridice = getTriDice(DReverseP, DForwardP);
			if (tridice == REVERSE) {
				Temp[i] = Temp[i - 1] - (RD[i] - RD[i - 1]) * FallA * getRandomA();
				//cout << Time[i] << "," << Temp[i] << endl;
			}
			else if (tridice == FORWARD)
			{
				Temp[i] = Temp[i - 1] + (RD[i] - RD[i - 1]) * RiseA * getRandomA();
				//cout << Time[i] << "," << Temp[i - 1] << endl;
			}
			else if (tridice == STANBY)
			{
				Temp[i] = Temp[i - 1];
				//cout << Time[i] << "," << Temp[i] << endl;
			}
		}
		else if (RD[i] == MyTopTime);
		//����ҹʱ���
		else {
			tridice = getTriDice(NReverseP, NForwardP);
			if (tridice == REVERSE) {
				Temp[i] = Temp[i - 1] + (RD[i] - RD[i - 1]) * RiseA * getRandomA();
				//cout << Time[i] << "," << Temp[i] << endl;
			}
			else if (tridice == FORWARD)
			{
				Temp[i] = Temp[i - 1] - (RD[i] - RD[i - 1]) * FallA * getRandomA();
				//cout << Time[i] << "," << Temp[i] << endl;
			}
			else if (tridice == STANBY)
			{
				Temp[i] = Temp[i - 1] ;
				//cout << Time[i] << "," << Temp[i] << endl;
			}
		}
	}
	//��ֹͻ��
	Temp[BottomIndex - 1] = (Temp[BottomIndex - 2]  + Temp[BottomIndex]) / 2;
	Temp[BottomIndex + 1] = (Temp[BottomIndex + 2]  + Temp[BottomIndex]) / 2;
	
	//�н�ǰ�գ���ֹͻ��
	Temp[0] = (LastTemp + Temp[2]) / 2;
	Temp[1] = (Temp[0] + Temp[2]) / 2;

	//���ɱ��չؼ�����
	HighTemp = Temp[TopIndex];
	LowTemp = Temp[BottomIndex];
	
	/*for (int i = 0; i < EACHDAY; i++) {
		AvgTemp += Temp[i];
	}
	AvgTemp = AvgTemp / EACHDAY;*/
}



int main()
{
	//while (1) {
	//	int a, b;
	//	cin >> a >> b;
	//	cout << (a * 60 + b)<<endl;
	//}
	srand(time(NULL));

	ofstream ofile1;
	ofstream ofile2;

	//ofile1.open("front_end_result.csv", ios::out | ios::trunc);//�ж�.csv�ļ��Ƿ���ڣ�������������ÿ�ζ���ɾ��֮ǰ�ļ����������ɣ����ɸ�д
	//ofile1.open("front_end_result.csv", ios::out | ios::app);//���������������ļ�ĩβ���ɸ�д
	ofile1.open("front_end_result.csv", ios::out | ios::trunc);
	ofile2.open("predict_result.csv", ios::out | ios::trunc);

	ofile1 << "Time,Temperature" << endl;
	ofile2 << "Year,Month,Day,HighTemp,LowTemp" << endl;

	float LastTemp = -5.71;
	for (int y = 2021; y <= 2023; y++) {
		
		for (int m = 1; m <= 12; m++) {

			int has = 0;

			switch (m)
			{
			case 1: has = 31; break;
			case 2: has = 28; break;
			case 3: has = 31; break;
			case 4: has = 30; break;
			case 5: has = 31; break;
			case 6: has = 30; break;
			case 7: has = 31; break;
			case 8: has = 31; break;
			case 9: has = 30; break;
			case 10: has = 31; break;
			case 11: has = 30; break;
			case 12: has = 31; break;

			default:
				break;
			}
			
			for (int d = 1; d <= has; d++)
			{
				SingleDay NewDay(y, m, d, LastTemp);
				LastTemp = NewDay.Temp[EACHDAY - 1];

				ofile2 << NewDay.Year << "," << NewDay.Month << "," << NewDay.Day << "," << NewDay.HighTemp << "," << NewDay.LowTemp ;
				ofile2 << "\n";

				for (int t = 0; t < EACHDAY; t++) {

					ofile1 << NewDay.Time[t] << "," << NewDay.Temp[t];
					ofile1 << "\n";

					cout << NewDay.Time[t] << "," << NewDay.Temp[t] << endl;
				}

			}
		}
	}
	
	ofile1.close();
	ofile2.close();

	return 0;
}