#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

int point=1;
int n=4;
int t=0; // 턴이 지난 횟수

string Log[100000];

class Player
{
    private:
        int maxhp = 100;
        int hp = 100;
        int damage = 10;
        int defence = 5;
        int speed = 5;
};

class mob
{
    public:
        string name;
        int maxhp;
        int hp;
        int damage;
        int defence;
        int speed;
        int exp;

        int Slime()
        {
            this->name = "슬라임";
            this->maxhp = 50;
            this->hp = maxhp;
            this->damage = 5;
            this->defence = 3;
            this->speed = 5;
            this->exp = 5;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
};

void attack()
{
    Player P;
    int damage = rand() % 3 + 9;
    Log[t] = to_string(damage) + " 데미지를 입혔습니다!";

    t++;
}

void fightmenu()
{
    for(int i=t-5; i<t; i++) // 로그가 5번 미만일 경우에는 0~t, 5번 이상이면 t-5~t
    {
        if(i==-1) cout << "#Log Start\n";
        else if(i<0) cout << '\n';
        else cout << Log[i] << '\n';
    }

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";
    cout << "몬스터를 만났다. 무엇을 할까?\n\n";
    for(int i=1; i<=n; i++)
    {
        if(i==point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        if(i==1) cout << "공격";
        if(i==2) cout << "스킬";
        if(i==3) cout << "아이템";
        if(i==4) cout << "도망";
        cout << "   ";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void selectmenu()
{
    int key;
    while(1)
    {
        if(kbhit())
        {
            key=getch();
            {
                if(key==224) // 방향키
                {
                    key=getch();
                    {
                        if(key==75) // 왼쪽
                        {
                            if(point>1)
                            {
                                point--;
                            }
                        }
                        if(key==77) // 오른쪽
                        {
                            if(point<n)
                            {
                                point++;
                            }
                        }
                    }
                }
                if(key==13) // enter키
                {
                    if(point==1) attack();
                }
            }
            system("cls");
            fightmenu();
        }
    }
}

void fight()
{
    mob m;
    m.Slime();
    // 몬스터 소환 코드(비어있음)
    fightmenu();
    selectmenu();
}


int main()
{
    srand(GetTickCount());
    fight();
}
