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
int t = 0; // 턴이 지난 횟수
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
"무기 강화소",
"방어구 강화소",
"시작의 숲 (권장 레벨 LV1 이상)",
"케이브 동굴 (권장 레벨 LV7 이상)",
"수상한 공터 (권장 레벨 LV12 이상)",
"저주받은 땅 (권장 레벨 LV20 이상)",
"어둠의 미로 (권장 레벨 LV25 이상)",
"-",
"-"
};

tuple<string, int, int> skills[500]; // 스킬 이름(띄어 쓰기 X), ManaCost, Learned(1 = 스킬 배움, 2 = 장착 중)
tuple<string, int> passiveskills[500]; // 스킬 이름(띄어 쓰기 X), Learned(1 = 스킬 배움, 2 = 장착 중)
tuple<string, int, int, int> itemlist[500]; // 아이템 이름, 아이템 종류 ,구매가, 판매가

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
    if (cnt <= 1) cnt=1; // DivisionByZero, 데미지의 극한값 제한을 하기 위함
    return cnt;
}

