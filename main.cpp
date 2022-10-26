#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <conio.h>

using namespace std;

double mobhppercent, playerhppercent, playermppercent, playerexppercent;
int point=1;
int where = 0;
int t=0; // 턴이 지난 횟수
bool killtrigger = false;
int stage = 9;
string worldmap[10] = {
"-",
"시작의 숲 (권장 레벨 LV1 이상)",
"케이브 동굴 (권장 레벨 LV3 이상)",
"수상한 공터 (권장 레벨 LV10 이상)",
"저주받은 땅 (권장 레벨 LV15 이상)",
"-",
"-",
"-",
"-",
"-",
};

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
        int LVUPexp;

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
            this->LVUPexp = 50;
        }

        void heal()
        {
            this->hp=this->maxhp;
            this->mp=this->maxmp;
            Log[t] = this->name + "(이)는 휴식을 하여 전부 회복하였다.";
            t++;
        }

        void LVUP()
        {
            this->exp -= this->LVUPexp;
            this->level++;
            this->LVUPexp*=1.1;
            Log[t] = "레벨이 상승 하였습니다!" + to_string(this->level-1) + "->" + to_string(this->level);
            t++;

            this->maxhp+=10;
            this->maxmp+=5;
            this->damage+=1;
            this->speed+=1;
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
            Log[t] = "+" + to_string(this->gold) + "G" + "   " + "+" + to_string(this->exp) + "EXP";
            p->gold+=this->gold;
            p->exp+=this->exp;
            t++;

            if(p->LVUPexp<p->exp) p->LVUP();
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
void fightmenu(mob *m, Player *p);
void fightselectmenu(mob *m, Player *p);
void home(Player *p);
void readymenu(Player *p);

void summonmob(Player *p)
{
    mob m;
    if(where==1)
    {
        int n = rand()%2+1;
        if(n==1) m.Slime();
        if(n==2) m.Snake();
        fightmenu(&m, p);
        fightselectmenu(&m, p);
    }
}

void movemenu(Player *p)
{
    bool command = false;

    system("cls");
    for(int i=t-5; i<t; i++)
    {
        if(i==-1) cout << "#Log Start\n";
        else if(i<0) cout << '\n';
        else cout << Log[i] << '\n';
    }

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

    cout << "이동할 곳을 선택해 주세요.\n\n";

    for(int i=point-1; i<=point+1; i++)
    {
        if(i==point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << worldmap[i] << '\n';
    }

    while(!command)
    {
        int key;
        if(kbhit())
        {
            key=getch();
            {
                if(key==224) // 방향키
                {
                    key=getch();
                    {
                        if(key==72) // 위쪽
                        {
                            if(point>1)
                            {
                                point--;
                            }
                        }
                        if(key==80) // 아래쪽
                        {
                            if(point<stage-1)
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
                        where = point;
                        Log[t] = "당신은 " + worldmap[point] + "(으)로 여정을 떠났다.";
                        t++;
                        point = 1;
                        fight(p);
                        readymenu(p);
                    }
                }
                if(key==27) //esc
                {
                    point = 1;
                    break;
                }
            }
            movemenu(p);
        }
    }
    command=false;
    home(p);
}

void homemenu(Player *p)
{
    playerhppercent = (double)p->hp/p->maxhp * 100;
    playermppercent = (double)p->mp/p->maxmp * 100;
    playerexppercent = (double)p->exp/p->LVUPexp * 100;

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
    cout << "골드 : " << p->gold << '\n';

    cout << "[";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // levelbar
    for(int i=1; i<=25; i++)
    {
        if(playerexppercent<i*4)
        {
            if(playerexppercent-((i-1)*4)>=2) // 2%의 경우에 연하게
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                cout << "#";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            }
            else cout << " ";
        }
        else cout << "#";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "]";
}

void homeselectmenu(Player *p)
{
    bool command = false;
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
                        point = 1;
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
    system("cls");
    mobhppercent = (double)m->hp/m->maxhp * 100;
    playerhppercent = (double)p->hp/p->maxhp * 100;
    playermppercent = (double)p->mp/p->maxmp * 100;
    playerexppercent = (double)p->exp/p->LVUPexp * 100;

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
    cout << "골드 : " << p->gold << '\n';

    cout << "[";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // levelbar
    for(int i=1; i<=25; i++)
    {
        if(playerexppercent<i*4)
        {
            if(playerexppercent-((i-1)*4)>=2) // 2%의 경우에 연하게
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                cout << "#";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            }
            else cout << " ";
        }
        else cout << "#";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "]";
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
    fight(p);
    readymenu(p);
}

void fight(Player *p)
{
    system("cls");
    mob m;

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
        if(i==1) cout << "탐험한다";
        if(i==2) cout << "돌아간다";
        if(i==3) cout << "-";
        if(i==4) cout << "-";
        cout << "   ";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "\n\n";
    cout << "레벨 : " << p->level << " (" << p->exp << ")" << "   ";
    cout << "골드 : " << p->gold << '\n';

    cout << "[";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // levelbar
    for(int i=1; i<=25; i++)
    {
        if(playerexppercent<i*4)
        {
            if(playerexppercent-((i-1)*4)>=2) // 2%의 경우에 진하게
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                cout << "#";
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
            }
            else cout << " ";
        }
        else cout << "#";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "]";
}

void readymenu(Player *p)
{
    bool command = false;
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
                        summonmob(p);
                    }
                    if(point==2)
                    {
                        Log[t] = p->name + "(이)는 탐험을 그만두고 돌아갔다.";
                        t++;
                        command = true;
                        point = 1;
                    }
                }
                system("cls");
                fight(p);
            }
        }
    }
    home(p);
}

int main()
{
    srand(GetTickCount());
    Player p;
    p.profile();
    home(&p);
}
