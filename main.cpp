#include <iostream>
#include <stdlib.h>
#include <string>
#include <windows.h>
#include <vector>
#include <conio.h>

using namespace std;

double mobhppercent, playerhppercent, playermppercent, playerexppercent;

int forgeadd[21]={0,1,1,2,3,4,6,9,13,19,28,41,60,88,129,189,277,416,605,882,1298};
int point=1;
int where = 0;
int t=0; // 턴이 지난 횟수
bool killtrigger = false;
int stage = 9;
string worldmap[10] = {
"-",
"시작의 숲 (권장 레벨 LV1 이상)",
"케이브 동굴 (권장 레벨 LV5 이상)",
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
        int weaponlevel;
        int armorlevel;

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

            this->weaponlevel = 0;
            this->armorlevel = 0;
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
            this->LVUPexp*=1.3;
            Log[t] = "레벨이 상승 하였습니다!" + to_string(this->level-1) + "->" + to_string(this->level);
            t++;

            this->maxhp+=10;
            this->maxmp+=5;
            this->damage+=1;
            this->defence+=1;
            this->speed+=1;

            if(this->LVUPexp<this->exp) this->LVUP();
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

        //시작의 숲
        void MiniSlime()
        {
            this->name = "미니 슬라임";
            this->maxhp = 50;
            this->hp = maxhp;
            this->damage = 4;
            this->defence = 3;
            this->speed = 5;
            this->exp = 5;
            this->gold = 30;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void Snake()
        {
            this->name = "뱀";
            this->maxhp = 75;
            this->hp = maxhp;
            this->damage = 6;
            this->defence = 3;
            this->speed = 10;
            this->exp = 8;
            this->gold = 50;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void Slime()
        {
            this->name = "슬라임";
            this->maxhp = 100;
            this->hp = maxhp;
            this->damage = 9;
            this->defence = 3;
            this->speed = 3;
            this->exp = 15;
            this->gold = 120;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void Oak()
        {
            this->name = "(BOSS)오크";
            this->maxhp = 1500;
            this->hp = maxhp;
            this->damage = 50;
            this->defence = 20;
            this->speed = 5;
            this->exp = 1500;
            this->gold = 3500;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        // 케이브 케이브
        void RockSlime()
        {
            this->name = "돌 슬라임";
            this->maxhp = 100;
            this->hp = maxhp;
            this->damage = 5;
            this->defence = 20;
            this->speed = 1;
            this->exp = 25;
            this->gold = 150;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void Bat()
        {
            this->name = "박쥐";
            this->maxhp = 120;
            this->hp = maxhp;
            this->damage = 15;
            this->defence = 3;
            this->speed = 12;
            this->exp = 30;
            this->gold = 220;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void MiniGolem()
        {
            this->name = "미니 골렘";
            this->maxhp = 200;
            this->hp = maxhp;
            this->damage = 10;
            this->defence = 10;
            this->speed = 1;
            this->exp = 70;
            this->gold = 350;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void Golem()
        {
            this->name = "골렘";
            this->maxhp = 500;
            this->hp = maxhp;
            this->damage = 25;
            this->defence = 15;
            this->speed = 1;
            this->exp = 300;
            this->gold = 850;
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
            if(p->LVUPexp<=p->exp) p->LVUP();
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
void weaponforge(Player *p, bool visit);
void armorforge(Player *p, bool visit);

void summonmob(Player *p)
{
    mob m;
    if(where==1)
    {
        int n = rand()%100+1;
        if(n<=40) m.MiniSlime();
        else if(n<=70) m.Snake();
        else if(n<=98) m.Slime();
        else if(n<=100) m.Oak();
        fightmenu(&m, p);
        fightselectmenu(&m, p);
    }
    if(where==2)
    {
        int n = rand()%100+1;
        if(n<=40) m.RockSlime();
        else if(n<=80) m.Bat();
        else if(n<=95) m.MiniGolem();
        else if(n<=100) m.Golem();
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
                    command = true;
                    where = point;
                    Log[t] = "당신은 " + worldmap[point] + "(으)로 여정을 떠났다.";
                    t++;
                    point = 1;
                    fight(p);
                    readymenu(p);
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
        if(i==3) cout << "무기강화";
        if(i==4) cout << "방어구강화";
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
                    if(point==3)
                    {
                        weaponforge(p, false);
                    }
                    if(point==4)
                    {
                        armorforge(p, false);
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
    int damage = rand() % 3 + p->damage / (1+(m->defence*0.1));
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
    int damage = rand() % 3 + m->damage / (1+(p->defence*0.1));;
    Log[t] = m->name + "이(가) 공격하여 " + to_string(damage) + " 데미지를 입었습니다!";
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
                    if(point==4)
                    {
                        Log[t] = "당신은 " + m->name + "(으)로부터 도망쳤다!";
                        t++;
                        point = 1;
                        return;
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

void Forge(Player *p, int protect, int chance, string mode, int upmoney) // status 증가는 적용안됨, 가끔 강제종료됨
{
    if(p->level==20)
    {
        Log[t] = "최대 강화 상태입니다. 강화를 취소합니다.";
        t++;
        return;
    }

    if(p->gold < upmoney)
    {
        Log[t] = "골드가 부족합니다. (" + to_string(p->gold) + "/" + to_string(upmoney) + ")";
        t++;
        return;
    }
    p->gold-=upmoney;
    int k = rand()%10000 + 1;
    if(mode=="weapon")
    {
        if(chance*100 >= k) // 성공
        {
            Log[t] = "장비 강화에 성공 하였다! (" + to_string(p->weaponlevel) + " -> " + to_string(p->weaponlevel+1) + ")";
            t++;
            p->weaponlevel++;
            p->damage+=forgeadd[p->weaponlevel];
        }
        else
        {
            int down;
            if(!protect) down = rand()%(p->weaponlevel/4<=0?1:p->weaponlevel/4 + 1);
            else down = rand()%(p->weaponlevel/6<=0?1:p->weaponlevel/7 + 1);
            Log[t] = "장비 강화에 실패하였다... (" + to_string(p->weaponlevel) + " -> " + to_string(p->weaponlevel-down) + ")";
            t++;
            for(int i=p->weaponlevel; i>p->weaponlevel-down; i--)
            {
                p->damage-=forgeadd[i];
            }
            p->weaponlevel-=down;
        }
    }
    if(mode=="armor")
    {
        if(chance*100 >= k) // 성공
        {
            Log[t] = "방어구 강화에 성공 하였다! (" + to_string(p->armorlevel) + " -> " + to_string(p->armorlevel+1) + ")";
            t++;
            p->armorlevel++;
            p->defence+=forgeadd[p->armorlevel];
        }
        else
        {
            int down;
            if(!protect) down = rand()%(p->armorlevel/3<=0?1:p->armorlevel/3 + 1);
            else down = rand()%(p->armorlevel/6<=0?1:p->armorlevel/6 + 1);
            Log[t] = "방어구 강화에 실패하였다... (" + to_string(p->armorlevel) + " -> " + to_string(p->armorlevel-down) + ")";
            t++;
            for(int i=p->armorlevel; i>p->armorlevel-down; i--)
            {
                p->defence-=forgeadd[i];
            }
            p->armorlevel-=down;
        }
    }
}

void weaponforge(Player *p, bool visit)
{
    int key;
    int chance;
    system("cls");
    if(!visit)
    {
        Log[t] = "당신은 무기강화소에 들렀다.";
        t++;
    }

    for(int i=t-5; i<t; i++)
    {
        if(i==-1) cout << "#Log Start\n";
        else if(i<0) cout << '\n';
        else cout << Log[i] << '\n';
    }

    // 90 80 70 60 50 45 40 35 30 25 20 20 20 20 20 10 10 10 10 5
    if(p->weaponlevel<=5) chance = 100 - p->weaponlevel*10;
    else if(p->weaponlevel<=10) chance = 50 - ((p->weaponlevel-5)*5);
    else if(p->weaponlevel<=15) chance = 20;
    else if(p->weaponlevel<=19) chance = 10;
    else chance = 5;

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

    cout << "무기 강화 (현재 : " << p->weaponlevel << ")" << " 확률 : " << chance << "  데미지:" << p->damage <<"\n\n";

    cout << "강화를 원한다면 'o' 키를 누르세요.   필요 골드 : " << p->weaponlevel*1000 << "\n\n";
    cout << "보호강화(+15 이하)를 원한다면 'p' 키를 누르세요.   필요 골드 : " << p->weaponlevel*10000 << "\n\n";
    cout << "강화를 하고 싶지 않다면 'Esc' 키를 누르세요.\n\n";

    key=getch();
    if(key==224) // 방향키로 종료 방지
    {
        getch();
        weaponforge(p, true);
    }
    else if(key=='o' || key=='O') Forge(p, 0, chance, "weapon", p->weaponlevel*1000);
    else if(key=='p' || key=='P') Forge(p, 1, chance, "weapon", p->weaponlevel*10000);
    else if(key==27) return;
    else weaponforge(p, true);

}

void armorforge(Player *p, bool visit)
{
    int key;
    int chance;
    system("cls");

    if(!visit)
    {
        Log[t] = "당신은 방어구강화소에 들렀다.";
        t++;
    }

    for(int i=t-5; i<t; i++)
    {
        if(i==-1) cout << "#Log Start\n";
        else if(i<0) cout << '\n';
        else cout << Log[i] << '\n';
    }

    // 80 60 40 20 20 20 15 15 15 10 10 10 10 5 5
    if(p->armorlevel<=3) chance = 100 - p->armorlevel*20;
    else if(p->armorlevel<=6) chance = 20;
    else if(p->armorlevel<=9) chance = 15;
    else if(p->armorlevel<=13) chance = 10;
    else if(p->armorlevel<=15) chance = 5;
    else chance = 5;

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

    cout << "방어구 강화 (현재 : " << p->armorlevel << ")" << " 확률 : " << chance << "  방어력:" << p->defence <<"\n\n";

    cout << "강화를 원한다면 'o' 키를 누르세요.   필요 골드 : " << p->armorlevel*2000 << "\n\n";
    cout << "보호강화(+10 이하)를 원한다면 'p' 키를 누르세요.   필요 골드 : " << p->armorlevel*20000 << "\n\n";
    cout << "강화를 하고 싶지 않다면 'Esc' 키를 누르세요.\n\n";

    key=getch();
    if(key==224) // 방향키로 종료 방지
    {
        getch();
        armorforge(p, true);
    }
    else if(key=='o' || key=='O') Forge(p, 0, chance, "armor", p->armorlevel*2000);
    else if(key=='p' || key=='P') Forge(p, 1, chance, "armor", p->armorlevel*20000);
    else if(key==27) return;
    else armorforge(p, true);

}

int main()
{
    srand(GetTickCount());
    Player p;
    p.profile();
    home(&p);
}
