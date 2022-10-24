#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

int point=1;
int n=4;
int t=0; // 턴이 지난 횟수
bool killtrigger = false;

string Log[100000];

class Player
{
    public:
        string name;
        int maxhp;
        int hp;
        int damage;
        int defence;
        int speed;
        int gold;

        void profile() // 프로필 파일 만들 예정
        {
            name = "이쁜이 민우";
            maxhp = 100;
            hp = 100;
            damage = 10;
            defence = 5;
            speed = 5;
            gold = 0;
        }
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
        int gold;

        void Slime()
        {
            this->name = "슬라임";
            this->maxhp = 50;
            this->hp = maxhp;
            this->damage = 5;
            this->defence = 3;
            this->speed = 5;
            this->exp = 5;
            this->gold = 10;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }

        void Mobdeath(Player p)
        {
            killtrigger = true;
            this->hp=0;
            Log[t] = this->name + "(을)를 처치했다!";
            t++;
            Log[t] = "보상으로 " + to_string(this->gold) + "골드(을)를 획득 했다!";
            t++;
        }
};

class slime
{
    public:
        string name = "슬라임";
        int maxhp = 50;
        int damage = 5;
        int defence = 3;
        int speed = 5;
        int exp = 5;
        int level = 1;
};

void pattack(Player *p, mob *m)
{
    int damage = rand() % 3 + p->damage;
    Log[t] = to_string(damage) + " 데미지를 입혔습니다!";
    m->hp-=damage;
    t++;
    if(m->hp<=0)
    {
        m->Mobdeath(*p);
        return;
    }
}

void mattack(Player *p, mob *m)
{
    int damage = rand() % 3 + m->damage;
    Log[t] = to_string(damage) + " 데미지를 입었습니다!";
    p->hp-=damage;
    t++;
    if(p->hp<=0)
    {
        return;
    }
}

void attack(Player *p, mob *m)
{
    if(p->speed >= m->speed)
    {
        pattack(p, m);
        if(killtrigger==true) return;
        mattack(p, m);
    }
    else
    {
        mattack(p, m);
        pattack(p, m);
    }
}

void fightmenu(mob m, Player p)
{
    for(int i=t-5; i<t; i++)
    {
        if(i==-1) cout << "#Log Start\n";
        else if(i<0) cout << '\n';
        else cout << Log[i] << '\n';
    }

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

    cout << "(적)" << m.name << '\n';
    cout << "HP : " << m.hp << " / " << m.maxhp << '\n';
    cout << '\n';
    cout << p.name << '\n';
    cout << "HP : " << p.hp << " / " << p.maxhp << '\n';
    cout << '\n';
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

void selectmenu(mob m, Player p)
{
    int key;
    while(!killtrigger)
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
                    if(point==1)
                    {
                        attack(&p,&m);
                    }
                }
            system("cls");
            fightmenu(m, p);
            }
        }
    }
    killtrigger = false;
}

void fight(Player p)
{
    mob m;
    m.Slime();
    // 몬스터 소환 코드(비어있음)
    fightmenu(m, p);
    selectmenu(m, p);
}


int main()
{
    srand(GetTickCount());
    Player p;
    p.profile();
    fight(p);
}
