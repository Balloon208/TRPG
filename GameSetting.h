#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <windows.h>
#include <vector>
#include <conio.h>
#include <tuple>

using namespace std;

double mobhppercent, playerhppercent, playermppercent, playerexppercent;

int weaponforgeadd[21] = { 0,2,4,7,10,15,20,25,30,35,40,100,100,100,100,100,150,150,200,200,300 };
int armorforgeadd[21] = { 0,2,3,3,5,5,7,7,8,8,10,20,20,30,30,30,50,50,50,80,100};
int point = 1;
int where = 0;
int t = 0; // ���� ���� Ƚ��
int totalskill = 7;
int totalpassive = 3;
int totalitem = 3;
int totalskillbooks = 1;
int usingskill;
bool killtrigger = false;
int stage = 9;
int memory[10][10];

string worldmap[10] = {
"-",
"���� ��ȭ��",
"�� ��ȭ��",
"������ �� (���� ���� LV1 �̻�)",
"���̺� ���� (���� ���� LV7 �̻�)",
"������ ���� (���� ���� LV12 �̻�)",
"���ֹ��� �� (���� ���� LV20 �̻�)",
"����� �̷� (���� ���� LV25 �̻�)",
"-",
"-"
};

tuple<string, int, int> skills[500]; // ��ų �̸�(��� ���� X), ManaCost, Learned(1 = ��ų ���, 2 = ���� ��)
tuple<string, int> passiveskills[500]; // ��ų �̸�(��� ���� X), Learned(1 = ��ų ���, 2 = ���� ��)
tuple<string, int, int, int> itemlist[500]; // ������ �̸�, ������ ���� ,���Ű�, �ǸŰ�

string Log[100000];

void Delay(int num)
{
    Sleep(num);
    if (kbhit())
    {
        while (kbhit()) getch();
    }
}

float log3(int num)
{
    float cnt = 0;
    while (num / 3 != 0)
    {
        num /= 3;
        cnt++;
    }
    cnt += num / 3;
    if (cnt <= 1) cnt=1; // DivisionByZero, �������� ���Ѱ� ������ �ϱ� ����
    return cnt;
}

