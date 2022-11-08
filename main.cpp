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
"무기 강화소",
"방어구 강화소",
"시작의 숲 (권장 레벨 LV1 이상)",
"케이브 동굴 (권장 레벨 LV5 이상)",
"수상한 공터 (권장 레벨 LV12 이상)",
"저주받은 땅 (권장 레벨 LV20 이상)",
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
            this->gold = 80;
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
            this->gold = 130;
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
            this->gold = 200;
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
            this->speed = 22;
            this->exp = 2650;
            this->gold = 45000;
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
            this->gold = 300;
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
            this->exp = 35;
            this->gold = 430;
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
            this->exp = 60;
            this->gold = 700;
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
            this->exp = 450;
            this->gold = 4320;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        // 서늘한 공터
        void killerdog()
        {
            this->name = "사냥개";
            this->maxhp = 200;
            this->hp = maxhp;
            this->damage = 30;
            this->defence = 3;
            this->speed = 22;
            this->exp = 150;
            this->gold = 1080;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void hunter()
        {
            this->name = "사냥꾼";
            this->maxhp = 300;
            this->hp = maxhp;
            this->damage = 20;
            this->defence = 5;
            this->speed = 15;
            this->exp = 190;
            this->gold = 1450;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void shadower()
        {
            this->name = "암살자";
            this->maxhp = 120;
            this->hp = maxhp;
            this->damage = 60;
            this->defence = 1;
            this->speed = 30;
            this->exp = 80;
            this->gold = 2700;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void badknight()
        {
            this->name = "타락한 기사";
            this->maxhp = 600;
            this->hp = maxhp;
            this->damage = 30;
            this->defence = 5;
            this->speed = 20;
            this->exp = 380;
            this->gold = 3750;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void nohead()
        {
            this->name = "(BOSS)듀라한";
            this->maxhp = 5000;
            this->hp = maxhp;
            this->damage = 100;
            this->defence = 1;
            this->speed = 40;
            this->exp = 12000;
            this->gold = 110000;
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

void fight(Player *p);
void fightmenu(mob *m, Player *p);
void fightselectmenu(mob *m, Player *p);
void home(Player *p);
void readymenu(Player *p);
void weaponforge(Player *p, bool visit);
void armorforge(Player *p, bool visit);
void Save(Player *p);

int totalskill = 5;
int skills[5]; // 1 = 스킬 배움, 2 = 장착 중

void Login(Player *p)
{
    int n;
    string name;

    FILE* fp = fopen("playerinfom.txt","r");
    fscanf(fp,"register:%d", &n);
    fclose(fp);

    if(n!=2)
    {
        cout << "신규 가입을 위하여 이름을 입력하세요 : ";
        cin >> name;

        char wname[200];
        strcpy(wname, name.c_str());
        /*
        fout <<
        "register:" << 2 << '\n' <<
        "name:" << name << '\n' <<
        "maxhp:" << 100 << '\n' <<
        "hp" << 100 << '\n' <<
        "maxmp:" << 50 << '\n' <<
        "mp:" << 50 << '\n' <<
        "damage:" << 10 << '\n' <<
        "defence:" << 5 << '\n' <<
        "speed:" << 5 << '\n' <<
        "gold:" << 0 << '\n' <<
        "level:" << 1 << '\n' <<
        "exp:" << 0 << '\n' <<
        "LVUPexp:" << 50 << '\n' <<
        "weaponlevel:" << 0 << '\n' <<
        "armorlevel:" << 0 << '\n';
        */

        FILE* fp;
        fp = fopen("playerinfom.txt","w");
        fprintf(fp,"register:%d\n", 2);
        fprintf(fp,"%s\n", wname);
        fprintf(fp,"maxhp:%d\n", 100);
        fprintf(fp,"hp:%d\n", 100);
        fprintf(fp,"maxmp:%d\n", 50);
        fprintf(fp,"mp:%d\n", 50);
        fprintf(fp,"damage:%d\n", 10);
        fprintf(fp,"defence:%d\n", 5);
        fprintf(fp,"speed:%d\n", 5);
        fprintf(fp,"gold:%d\n", 0);
        fprintf(fp,"level:%d\n", 1);
        fprintf(fp,"exp:%d\n", 0);
        fprintf(fp,"LVUPexp:%d\n", 50);
        fprintf(fp,"weaponlevel:%d\n", 0);
        fprintf(fp,"armorlevel:%d\n", 0);
        fclose(fp);

        fp = fopen("playerskills.txt","w");
        for(int i=0; i<totalskill; i++)
        {
            fprintf(fp,"%d ", 0);
        }
        fclose(fp);

        p->name = name;
        p->maxhp = 100;
        p->hp = 100;
        p->maxmp = 50;
        p->mp = 50;
        p->damage = 10;
        p->defence = 5;
        p->speed = 5;
        p->gold = 0;
        p->level = 1;
        p->exp = 0;
        p->LVUPexp = 50;

        p->weaponlevel = 0;
        p->armorlevel = 0;
    }
}

void Save(Player *p)
{
    /*
    ofstream fout;
    fout.open("playerinfom.txt");

    fout <<
    2 << '\n' <<
    p->name << '\n' <<
    p->maxhp << '\n' <<
    p->hp << '\n' <<
    p->maxmp << '\n' <<
    p->mp << '\n' <<
    p->damage << '\n' <<
    p->defence << '\n' <<
    p->speed << '\n' <<
    p->gold << '\n' <<
    p->level << '\n' <<
    p->exp << '\n' <<
    p->LVUPexp << '\n' <<
    p->weaponlevel << '\n' <<
    p->armorlevel << '\n';

    */

    char wname[200];
    strcpy(wname, p->name.c_str());

    FILE* fp;
    fp = fopen("playerinfom.txt","w");
    fprintf(fp,"register:%d\n", 2);
    fprintf(fp,"%s\n", wname);
    fprintf(fp,"maxhp:%d\n", p->maxhp);
    fprintf(fp,"hp:%d\n", p->hp);
    fprintf(fp,"maxmp:%d\n", p->maxmp);
    fprintf(fp,"mp:%d\n", p->mp);
    fprintf(fp,"damage:%d\n", p->damage);
    fprintf(fp,"defence:%d\n", p->defence);
    fprintf(fp,"speed:%d\n", p->speed);
    fprintf(fp,"gold:%d\n", p->gold);
    fprintf(fp,"level:%d\n", p->level);
    fprintf(fp,"exp:%d\n", p->exp);
    fprintf(fp,"LVUPexp:%d\n", p->LVUPexp);
    fprintf(fp,"weaponlevel:%d\n", p->weaponlevel);
    fprintf(fp,"armorlevel:%d\n", p->armorlevel);
    fclose(fp);

    fp = fopen("playerskills.txt","w");
    for(int i=0; i<totalskill; i++)
    {
        fprintf(fp,"%d ", skills[i]);
    }
    fclose(fp);
}

void Load(Player *p)
{
    /*
    ifstream fin;
    fin.open("playerinfom.txt");

    string name;
    int trash, maxhp, hp, maxmp, mp, damage, defence, speed, gold, level, exp, LVUPexp, weaponlevel, armorlevel;

    char buffer[50];

    for(int i=0; i<15; i++)
    {
        fin >> buffer;
        fin.getline(buffer, 50);
        if(i==0)trash = stoi(buffer);
        if(i==1)name = buffer;
        if(i==2)maxhp = stoi(buffer);
        if(i==3)hp = stoi(buffer);
        if(i==4)maxmp = stoi(buffer);
        if(i==5)mp = stoi(buffer);
        if(i==6)damage = stoi(buffer);
        if(i==7)defence = stoi(buffer);
        if(i==8)speed = stoi(buffer);
        if(i==9)gold = stoi(buffer);
        if(i==10)level = stoi(buffer);
        if(i==11)exp = stoi(buffer);
        if(i==12)LVUPexp = stoi(buffer);
        if(i==13)weaponlevel = stoi(buffer);
        if(i==14)armorlevel = stoi(buffer);
    }
    */

    /*
    fin >>
    trash >>
    name >>
    maxhp >>
    hp >>
    maxmp >>
    mp >>
    damage >>
    defence >>
    speed >>
    gold >>
    level >>
    exp >>
    LVUPexp >>
    weaponlevel >>
    armorlevel;


    p->name = name;
    p->maxhp = maxhp;
    p->hp = hp;
    p->maxmp = maxmp;
    p->mp = mp;
    p->damage = damage;
    p->defence = defence;
    p->speed = speed;
    p->gold = gold;
    p->level = level;
    p->exp = exp;
    p->LVUPexp = LVUPexp;
    p->weaponlevel = weaponlevel;
    p->armorlevel = armorlevel;

    fin.close();
    */

    int trash;
    char wname[200];

    FILE* fp;
    fp = fopen("playerinfom.txt","r");
    fscanf(fp,"register:%d\n", &trash);
    fscanf(fp,"%s\n", wname);
    p->name = wname;
    fscanf(fp,"maxhp:%d\n", &p->maxhp);
    fscanf(fp,"hp:%d\n", &p->hp);
    fscanf(fp,"maxmp:%d\n", &p->maxmp);
    fscanf(fp,"mp:%d\n", &p->mp);
    fscanf(fp,"damage:%d\n", &p->damage);
    fscanf(fp,"defence:%d\n", &p->defence);
    fscanf(fp,"speed:%d\n", &p->speed);
    fscanf(fp,"gold:%d\n", &p->gold);
    fscanf(fp,"level:%d\n", &p->level);
    fscanf(fp,"exp:%d\n", &p->exp);
    fscanf(fp,"LVUPexp:%d\n", &p->LVUPexp);
    fscanf(fp,"weaponlevel:%d\n", &p->weaponlevel);
    fscanf(fp,"armorlevel:%d\n", &p->armorlevel);
    fclose(fp);

    fp = fopen("playerskills.txt","r");
    for(int i=0; i<totalskill; i++)
    {
        fscanf(fp,"%d ", &skills[i]);
    }
    fclose(fp);

    /*
    cout <<
    trash << '\n' <<
    p->name << '\n' <<
    p->maxhp << '\n' <<
    p->hp << '\n' <<
    p->maxmp << '\n' <<
    p->mp << '\n' <<
    p->damage << '\n' <<
    p->defence << '\n' <<
    p->speed << '\n' <<
    p->gold << '\n' <<
    p->level << '\n' <<
    p->exp << '\n' <<
    p->LVUPexp << '\n' <<
    p->weaponlevel << '\n' <<
    p->armorlevel << '\n';
    Sleep(1000);
    */
}

void summonmob(Player *p)
{
    mob m;
    if(where==3)
    {
        int n = rand()%100+1;
        if(n<=40) m.MiniSlime();
        else if(n<=70) m.Snake();
        else if(n<=98) m.Slime();
        else if(n<=100) m.Oak();
        fightmenu(&m, p);
        fightselectmenu(&m, p);
    }
    if(where==4)
    {
        int n = rand()%100+1;
        if(n<=40) m.RockSlime();
        else if(n<=80) m.Bat();
        else if(n<=95) m.MiniGolem();
        else if(n<=100) m.Golem();
        fightmenu(&m, p);
        fightselectmenu(&m, p);
    }
    if(where==5)
    {
        int n = rand()%100+1;
        if(n<=30) m.killerdog();
        else if(n<=50) m.hunter();
        else if(n<=70) m.shadower();
        else if(n<=97) m.badknight();
        else if(n<=100) m.nohead();
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
                    point = 1;
                    if(where==1)
                    {
                        weaponforge(p, false);
                        break;
                    }
                    if(where==2)
                    {
                        armorforge(p, false);
                        break;
                    }
                    Log[t] = "당신은 " + worldmap[where] + "(으)로 여정을 떠났다.";
                    t++;
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
        if(i==3) cout << "스킬설정";
        if(i==4) cout << "상점";
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
                        point = 3;
                        movemenu(p);
                    }
                    if(point==2)
                    {
                        p->heal();
                        Save(p);
                    }
                    /*if(point==3)
                    {
                        p->skillset();
                    }*/
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
    Save(p);
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
                        Save(p);
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
    Save(p);
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
    if(p->gold < upmoney)
    {
        Log[t] = "골드가 부족합니다. (" + to_string(p->gold) + "/" + to_string(upmoney) + ")";
        t++;
        return;
    }
    int k = rand()%10000 + 1;
    if(mode=="weapon")
    {
        if(p->weaponlevel==20)
        {
            Log[t] = "최대 강화 상태입니다. 강화를 취소합니다.";
            t++;
            return;
        }
        p->gold-=upmoney;
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
        if(p->armorlevel==15)
        {
            Log[t] = "최대 강화 상태입니다. 강화를 취소합니다.";
            t++;
            return;
        }
        p->gold-=upmoney;
        if(chance*100 >= k) // 성공
        {
            Log[t] = "방어구 강화에 성공 하였다! (" + to_string(p->armorlevel) + " -> " + to_string(p->armorlevel+1) + ")";
            t++;
            p->armorlevel++;
            p->defence+=forgeadd[p->armorlevel];
            p->maxhp+=forgeadd[p->armorlevel]*10;
            p->hp+=forgeadd[p->armorlevel]*10;
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
                p->maxhp-=forgeadd[p->armorlevel]*10;
                p->hp-=forgeadd[p->armorlevel]*10;
            }
            p->armorlevel-=down;
        }
    }
    Save(p);
    if(mode=="weapon") weaponforge(p, true);
    if(mode=="armor") armorforge(p, true);
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
    cout << "보유 골드 : " << p->gold << "\n\n";

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

    // 80 70 60 50 30 30 20 20 15 15 15 10 10 5 0
    if(p->armorlevel<=4) chance = 80 - p->armorlevel*10;
    else if(p->armorlevel<=6) chance = 30;
    else if(p->armorlevel<=8) chance = 20;
    else if(p->armorlevel<=11) chance = 15;
    else if(p->armorlevel<=13) chance = 10;
    else chance = 100;

    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

    cout << "방어구 강화 (현재 : " << p->armorlevel << ")" << " 확률 : " << chance << "  방어력:" << p->defence << "  최대 체력:" << p->maxhp << "\n\n";

    cout << "강화를 원한다면 'o' 키를 누르세요.   필요 골드 : " << p->armorlevel*2000 << "\n\n";
    cout << "보호강화(+10 이하)를 원한다면 'p' 키를 누르세요.   필요 골드 : " << p->armorlevel*20000 << "\n\n";
    cout << "강화를 하고 싶지 않다면 'Esc' 키를 누르세요.\n\n";
    cout << "보유 골드 : " << p->gold << "\n\n";

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
    Login(&p);
    Load(&p);
    home(&p);
}

/*

아이디어 노트

-------------------------스킬에 관하여-----------------------

방안은 총 2가지이다

1. 선택형 스킬
player에 bool skill[n] = true / false (playerinfom.txt에 기록되어야함. 획득 경로는 상점..? / 특수 조건..? / 레벨)


2. 성장형 스킬

1의 장점 : 재밌어지고 다양한 경우의 수(공략법) 존재
1의 단점 : 매우 구현이 힘들어지고, 밸런스를 맞추기 힘들다.
2의 장점 : 구현이 적당한 난이도, 밸런스 맞추기 매우 쉽다.
2의 단점 : 스킬의 흥미도가 과연 있을까...
*/
