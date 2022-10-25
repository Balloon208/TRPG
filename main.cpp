#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

double mobhppercent, playerhppercent, playermppercent;
int point=1;
int t=0; // 턴이 지난 횟수
bool killtrigger = false;
bool command = false;

string Log[100000];

class Player
{
    public:
        string name;
        int maxhp;
        int hp;
        int maxmp;
        int mp;
        int damage;
        int defence;
        int speed;
        int gold;
        int level;
        int exp;

        void profile() // 프로필 파일 만들 예정
        {
            this->name = "넴넴";
            this->maxhp = 100;
            this->hp = 100;
            this->maxmp = 50;
            this->mp = 50;
            this->damage = 10;
            this->defence = 5;
            this->speed = 5;
            this->gold = 0;
            this->level = 1;
            this->exp = 0;
        }

        void heal()
        {
            this->hp=this->maxhp;
            this->mp=this->maxmp;
            Log[t] = this->name + "(이)는 휴식을 하여 전부 회복하였다.";
            t++;
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
        void Snake()
        {
            this->name = "뱀";
            this->maxhp = 75;
            this->hp = maxhp;
            this->damage = 8;
            this->defence = 3;
            this->speed = 10;
            this->exp = 8;
            this->gold = 15;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }

        void Mobdeath(Player *p)
        {
            killtrigger = true;
            this->hp=0;
            Log[t] = this->name + "(을)를 처치했다!";
            t++;
            Log[t] = "보상으로 " + to_string(this->gold) + "골드(을)를 획득 했다!";
            p->gold+=this->gold;
            t++;
            Log[t] = "+" + to_string(this->exp) + "EXP";
            p->exp+=this->exp;
            t++;
        }
};

/* 추후 클래스 공부를 더 한 이후에 이용할 예정
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
*/

void fight(Player *p);

void movemenu(Player *p)
{
    fight(p);
}

void homemenu(Player *p)
{
    playerhppercent = (double)p->hp/p->maxhp * 100;
    playermppercent = (double)p->mp/p->maxmp * 100;

    for(int i=t-5; i<t; i++)
    {
        if(i==-1) cout << "#Log Start\n";
        else if(i<0) cout << '\n';
        else cout << Log[i] << '\n';
    }

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";
    for(int i=0; i<10; i++) //playerhpbar
    {
        if(i*10<playerhppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "■";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << '\n';
    for(int i=0; i<10; i++) //playermpbar
    {
        if(i*10<playermppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "■";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << '\n';
    cout << p->name << '\n';
    cout << "HP : " << p->hp << " / " << p->maxhp << '\n';
    cout << '\n';

    for(int i=1; i<=4; i++)
    {
        if(i==point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        if(i==1) cout << "이동";
        if(i==2) cout << "휴식";
        if(i==3) cout << "-";
        if(i==4) cout << "-";
        cout << "   ";
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "\n\n";
    cout << "레벨 : " << p->level << " (" << p->exp << ")" << "   ";
    cout << "골드 : " << p->gold;
}

void homeselectmenu(Player *p)
{
    int key;
    point = 1;
    while(!command)
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
                            if(point<4)
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
                        command = true;
                        movemenu(p);
                    }
                    if(point==2)
                    {
                        p->heal();
                    }
                }
            system("cls");
            homemenu(p);
            }
        }
    }
    command = false;
}

void home(Player *p)
{
    system("cls");
    homemenu(p);
    homeselectmenu(p);
}

void pattack(Player *p, mob *m)
{
    int damage = rand() % 3 + p->damage;
    Log[t] = m->name + "에게 " + to_string(damage) + " 데미지를 입혔습니다!";
    m->hp-=damage;
    t++;
    if(m->hp<=0)
    {
        m->Mobdeath(p);
        return;
    }
}

void mattack(Player *p, mob *m)
{
    int damage = rand() % 3 + m->damage;
    Log[t] = m->name + "이 공격하여 " + to_string(damage) + " 데미지를 입었습니다!";
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

void fightmenu(mob *m, Player *p)
{
    mobhppercent = (double)m->hp/m->maxhp * 100;
    playerhppercent = (double)p->hp/p->maxhp * 100;
    playermppercent = (double)p->mp/p->maxmp * 100;

    for(int i=t-5; i<t; i++)
    {
        if(i==-1) cout << "#Log Start\n";
        else if(i<0) cout << '\n';
        else cout << Log[i] << '\n';
    }

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

    for(int i=0; i<10; i++) //mobhpbar
    {
        if(i*10<mobhppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "■";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << '\n';
    cout << "(적)" << m->name << '\n';
    cout << "HP : " << m->hp << " / " << m->maxhp << '\n';
    cout << '\n';

    for(int i=0; i<10; i++) //playerhpbar
    {
        if(i*10<playerhppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "■";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << '\n';
    for(int i=0; i<10; i++) //playermpbar
    {
        if(i*10<playermppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "■";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << '\n';
    cout << p->name << '\n';
    cout << "HP : " << p->hp << " / " << p->maxhp << '\n';
    cout << '\n';
    for(int i=1; i<=4; i++)
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
    cout << "\n\n";
    cout << "레벨 : " << p->level << " (" << p->exp << ")" << "   ";
    cout << "골드 : " << p->gold;
}

void fightselectmenu(mob *m, Player *p)
{
    int key;
    point = 1;
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
                            if(point<4)
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
                        attack(p,m);
                    }
                }
            system("cls");
            fightmenu(m, p);
            }
        }
    }
    killtrigger = false;
}

void fight(Player *p)
{
    system("cls");
    mob m;
    m.Slime();
    // 몬스터 소환 코드(비어있음)
    fightmenu(&m, p);
    fightselectmenu(&m, p);
    system("cls");
    m.Snake();
    // 몬스터 소환 코드(비어있음)
    fightmenu(&m, p);
    fightselectmenu(&m, p);
    home(p);
}

int main()
{
    srand(GetTickCount());
    Player p;
    p.profile();
    home(&p);
}
