#include <iostream>
#include <algorithm>
#include <stdlib.h>
#include <string>
#include <cmath>
#include <windows.h>
#include <vector>
#include <conio.h>

using namespace std;

double mobhppercent, playerhppercent, playermppercent, playerexppercent;

int forgeadd[21]={0,1,2,3,4,5,5,5,5,5,5,7,7,7,7,7,10,15,20,25,30};
int point=1;
int where = 0;
int t=0; // 턴이 지난 횟수
int totalskill = 6;
int totalitem = 3;
int usingskill;
bool killtrigger = false;
int stage = 9;

string worldmap[10] = {
"-",
"전직소",
"무기 강화소",
"방어구 강화소",
"시작의 숲 (권장 레벨 LV1 이상)",
"케이브 동굴 (권장 레벨 LV7 이상)",
"수상한 공터 (권장 레벨 LV12 이상)",
"저주받은 땅 (권장 레벨 LV20 이상)",
"-",
"-",
};

pair<string, pair<int,int>> skills[500]; // 스킬 이름(띄어 쓰기 X), ManaCost, Learned(1 = 스킬 배움, 2 = 장착 중)
pair<string, pair<int,int>> itemlist[500]; // 아이템 이름, 구매가, 판매가

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
        int skill[6];
        pair<int,int> playeritemlist[500]; // 수량, 강화(무기가 아니라면 -1)

        void heal()
        {
            this->hp=this->maxhp;
            this->mp=this->maxmp;
            Log[t] = this->name + "(이)는 휴식을 하여 전부 회복하였다.";
            t++;
        }

        void LVUP()
        {
            this->maxhp+=(10+(level/2)-1);
            this->maxmp+=(5+(level/2)-1);
            this->damage+=(1+int(level/4));
            this->defence+=(1+int(level/4));
            this->speed+=1;
            this->hp=this->maxhp;
            this->mp=this->maxmp;


            this->exp -= this->LVUPexp;
            this->level++;
            this->LVUPexp*=1.3;
            Log[t] = "레벨이 상승 하였습니다!" + to_string(this->level-1) + "->" + to_string(this->level);
            t++;


            if(this->level==3 && skills[2].second.second==0)
            {
                Log[t] = "크로스컷을 습득 하였습니다!";
                t++;
                skills[2].second.second=1;
            }
            if(this->level==10  && skills[3].second.second==0)
            {
                Log[t] = "힐링을 습득 하였습니다!";
                t++;
                skills[3].second.second=1;
            }
            if(this->level==15  && skills[4].second.second==0)
            {
                Log[t] = "급소찌르기를 습득 하였습니다!";
                t++;
                skills[4].second.second=1;
            }

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
        int level;
        int exp;
        int gold;

        //시작의 숲
        void MiniSlime()
        {
            this->name = "(LV1) 미니 슬라임";
            this->maxhp = 50;
            this->hp = maxhp;
            this->damage = 4;
            this->defence = 3;
            this->speed = 5;
            this->level = 1;
            this->exp = 5;
            this->gold = 80;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void Snake()
        {
            this->name = "(LV2) 뱀";
            this->maxhp = 75;
            this->hp = maxhp;
            this->damage = 6;
            this->defence = 3;
            this->speed = 10;
            this->level = 2;
            this->exp = 8;
            this->gold = 130;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void Slime()
        {
            this->name = "(LV3) 슬라임";
            this->maxhp = 100;
            this->hp = maxhp;
            this->damage = 9;
            this->defence = 3;
            this->speed = 3;
            this->level = 3;
            this->exp = 15;
            this->gold = 200;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void Oak()
        {
            this->name = "[BOSS](LV15) 오크";
            this->maxhp = 10000;
            this->hp = maxhp;
            this->damage = 50;
            this->defence = 30;
            this->speed = 22;
            this->level = 15;
            this->exp = 2450;
            this->gold = 7000;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        // 케이브 케이브
        void RockSlime()
        {
            this->name = "(LV4) 돌 슬라임";
            this->maxhp = 100;
            this->hp = maxhp;
            this->damage = 15;
            this->defence = 25;
            this->speed = 1;
            this->level = 4;
            this->exp = 20;
            this->gold = 300;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void Bat()
        {
            this->name = "(LV6) 박쥐";
            this->maxhp = 120;
            this->hp = maxhp;
            this->damage = 20;
            this->defence = 5;
            this->speed = 12;
            this->level = 6;
            this->exp = 30;
            this->gold = 430;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void MiniGolem()
        {
            this->name = "(LV8) 미니 골렘";
            this->maxhp = 200;
            this->hp = maxhp;
            this->damage = 25;
            this->defence = 15;
            this->speed = 1;
            this->level = 8;
            this->exp = 45;
            this->gold = 600;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void Golem()
        {
            this->name = "(LV13) 골렘";
            this->maxhp = 500;
            this->hp = maxhp;
            this->damage = 35;
            this->defence = 25;
            this->speed = 1;
            this->level = 13;
            this->exp = 230;
            this->gold = 2000;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        // 서늘한 공터
        void killerdog()
        {
            this->name = "(LV10) 사냥개";
            this->maxhp = 200;
            this->hp = maxhp;
            this->damage = 40;
            this->defence = 10;
            this->speed = 22;
            this->level = 10;
            this->exp = 100;
            this->gold = 800;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void hunter()
        {
            this->name = "(LV10) 사냥꾼";
            this->maxhp = 300;
            this->hp = maxhp;
            this->damage = 30;
            this->defence = 15;
            this->speed = 15;
            this->level = 10;
            this->exp = 90;
            this->gold = 740;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void shadower()
        {
            this->name = "(LV11) 암살자";
            this->maxhp = 120;
            this->hp = maxhp;
            this->damage = 150;
            this->defence = 1;
            this->speed = 30;
            this->level = 11;
            this->exp = 50;
            this->gold = 1300;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void badknight()
        {
            this->name = "(LV13) 타락한 기사";
            this->maxhp = 600;
            this->hp = maxhp;
            this->damage = 50;
            this->defence = 15;
            this->speed = 20;
            this->level = 13;
            this->exp = 200;
            this->gold = 1750;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void nohead()
        {
            this->name = "[BOSS](LV22) 듀라한";
            this->maxhp = 22222;
            this->hp = maxhp;
            this->damage = 222;
            this->defence = 1;
            this->speed = 40;
            this->level = 22;
            this->exp = 7500;
            this->gold = 33000;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }

        // 저주받은 땅
        void zombie()
        {
            this->name = "(LV15) 좀비";
            this->maxhp = 1000;
            this->hp = maxhp;
            this->damage = 80;
            this->defence = 30;
            this->speed = 40;
            this->level = 15;
            this->exp = 440;
            this->gold = 2500;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void skeleton()
        {
            this->name = "(LV17) 스켈레톤";
            this->maxhp = 777;
            this->hp = maxhp;
            this->damage = 150;
            this->defence = 20;
            this->speed = 50;
            this->level = 17;
            this->exp = 380;
            this->gold = 2800;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void tankzombie()
        {
            this->name = "(LV18) 탱크 좀비";
            this->maxhp = 1000;
            this->hp = maxhp;
            this->damage = 100;
            this->defence = 200;
            this->speed = 1;
            this->level = 18;
            this->exp = 420;
            this->gold = 3000;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void darkknight()
        {
            this->name = "(LV20) 칠흑의 기사";
            this->maxhp = 1500;
            this->hp = maxhp;
            this->damage = 130;
            this->defence = 50;
            this->speed = 35;
            this->level = 20;
            this->exp = 510;
            this->gold = 3830;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?";
            t++;
        }
        void demonite()
        {
            this->name = "[BOSS](LV40) 마왕 간부 데모나이트";
            this->maxhp = 5000;
            this->hp = maxhp;
            this->damage = 500;
            this->defence = 120;
            this->speed = 20;
            this->level = 40;
            this->exp = 12000;
            this->gold = 75000;
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
            if(this->name == "[BOSS](LV15) 오크")
            {
                int getskill = rand() % 100;
                cout << getskill;
                Sleep(500);
                if(getskill < 50 && skills[5].second.second == 0)
                {
                    Log[t] = this->name + " 를 죽여 분쇄 를 습득하였습니다!";
                    t++;
                    skills[5].second.second = 1;
                }
                getskill = rand() % 100;
                if(getskill < 20 && skills[6].second.second == 0)
                {
                    Log[t] = this->name + " 를 죽여 거인의일격 을 습득하였습니다!";
                    t++;
                    skills[6].second.second = 1;
                }
            }
        }
};

void Login(Player *p); // 첫 로그인 시 실행되는 함수
void Save(Player *p); // 게임 진행 상황을 저장하는 함수
void Load(Player *p); // 이전에 진행한 게임을 불러오는 함수
void home(Player *p); // 마을
void homemenu(Player *p); // 마을 인터페이스
void homeselectmenu(Player *p); // 마을에서 선택
void movemenu(Player *p); // 이동할 곳 선택
void skillset(Player *p); // 스킬 장착 및 해제
void shop(Player *p); // 상점
void pattack(Player *p, mob *m); // Player 공격
void mattack(Player *p, mob *m); // Mob 공격
void attack(Player *p, mob *m); // 전투 진행 함수
void skillattack(Player *p, mob *m, int skillnum); // 스킬 공격(항상 선공)
void fight(Player *p); // 탐험 인터페이스
void readymenu(Player *p); // 탐험에서의 선택
void summonmob(Player *p); // 몹 소환 및 확률
void fightmenu(mob *m, Player *p, bool skillmode); // 전투 인터페이스
void fightselectmenu(mob *m, Player *p); // 전투 중 선택
void Forge(Player *p, int protect, int chance, string mode, int upmoney); // 강화가 진행되는 함수
void weaponforge(Player *p, bool visit); // 무기강화소 (확률 및 돈 조정)
void armorforge(Player *p, bool visit); // 방어구강화소 (확률 및 돈 조정)


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

        // 스킬 설정 옵션 (skill setting), name, Mana, Learned(1 = 스킬 배움, 2 = 장착 중)
        fprintf(fp, "방어 0 1\n");
        fprintf(fp, "크로스컷 30 0\n");
        fprintf(fp, "힐링 60 0\n");
        fprintf(fp, "급소찌르기 20 0\n");
        fprintf(fp, "분쇄 50 0\n");
        fprintf(fp, "거인의일격 100 0\n");
        fprintf(fp, "0, 0, 0, 0");

        fclose(fp);

        fp = fopen("itemDB.txt","w");

        fprintf(fp, "소형포션 300 200\n");
        fprintf(fp, "중형포션 1000 700\n");
        fprintf(fp, "대형포션 2000 1500\n");

        fclose(fp);

        fp = fopen("playeritem.txt","w");

        fprintf(fp, "소형포션 0 -1\n");
        fprintf(fp, "중형포션 0 -1\n");
        fprintf(fp, "대형포션 0 -1\n");

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

        p->skill[1]=1;
        p->skill[2]=0;
        p->skill[3]=0;
        p->skill[4]=0;
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
    for(int i=1; i<=totalskill; i++)
    {
        fprintf(fp,"%s %d %d\n", skills[i].first.c_str(), skills[i].second.first, skills[i].second.second);
    }
    fprintf(fp,"%d %d %d %d", p->skill[1], p->skill[2], p->skill[3] ,p->skill[4]);
    fclose(fp);

    fp = fopen("playeritem.txt","w");

    char itemnames[10001];
    for(int i=1; i<=totalitem; i++)
    {
        strcpy(itemnames, itemlist[i].first.c_str());
        fprintf(fp,"%s %d %d\n", itemnames, p->playeritemlist[i].first, p->playeritemlist[i].second);
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
    for(int i=1; i<=totalskill; i++)
    {
        char skillnames[10000];
        fscanf(fp,"%s %d %d\n", skillnames, &skills[i].second.first, &skills[i].second.second);
        skills[i].first = skillnames;
    }
    fscanf(fp,"%d %d %d %d", &p->skill[1], &p->skill[2], &p->skill[3] ,&p->skill[4]);
    fclose(fp);

    fp = fopen("itemDB.txt","r");
    for(int i=1; i<=totalitem; i++)
    {
        char itemnames[10000];
        fscanf(fp,"%s %d %d\n", itemnames, &itemlist[i].second.first, &itemlist[i].second.second);
        itemlist[i].first = itemnames;
    }
    fclose(fp);

    fp = fopen("playeritem.txt","r");
    for(int i=1; i<=totalitem; i++)
    {
        char trash[10000];
        fscanf(fp,"%s %d %d\n", trash, &p->playeritemlist[i].first, &p->playeritemlist[i].second);
    }
    fclose(fp);

    /*
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

void home(Player *p)
{
    Save(p);
    system("cls");
    homemenu(p);
    homeselectmenu(p);
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
                    if(point==3)
                    {
                        command = true;
                        point=1;
                        skillset(p);
                    }
                    if(point==4)
                    {
                        command = true;
                        point=1;
                        shop(p);
                    }
                }
            system("cls");
            homemenu(p);
            }
        }
    }
    command = false;
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
                    if(where==2)
                    {
                        weaponforge(p, false);
                        break;
                    }
                    if(where==3)
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

void skillset(Player *p)
{
    system("cls");
    bool command=false;

    for(int i=t-5; i<t; i++)
    {
        if(i==-1) cout << "#Log Start\n";
        else if(i<0) cout << '\n';
        else cout << Log[i] << '\n';
    }
    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

    for(int i=1; i<4; i++)
    {
        p->skill[i]=0;
    }
    usingskill=1;

    for(int i=1; i<=totalskill; i++)
    {
        if(i==point) cout << ">";

        if(skills[i].second.second==1)
        {
            cout << "    " << skills[i].first << "(" << skills[i].second.first << ")" << '\n';
        }
        else if(skills[i].second.second==2)
        {
            p->skill[usingskill]=i;
            usingskill++;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            cout << "   " << skills[i].first << "(" << skills[i].second.first << ")" << '\n';
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            cout << "   " << skills[i].first << "(" << skills[i].second.first << ")" << '\n';
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
    }

    Save(p);

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
                            if(point<totalskill)
                            {
                                point++;
                            }
                        }
                    }
                }
                if(key==13) // enter키
                {
                    command = true;
                    if(usingskill<=4 || skills[point].second.second==2)
                    {
                        if(skills[point].second.second==1)
                        {
                            Log[t] = skills[point].first + " 스킬을 장착하였습니다.";
                            t++;
                            skills[point].second.second=2;
                        }
                        else if(skills[point].second.second==2)
                        {
                            Log[t] = skills[point].first + " 스킬을 해제하였습니다.";
                            t++;
                            skills[point].second.second=1;
                        }
                    }
                    else if(skills[point].second.second==1)
                    {
                        Log[t] = "스킬 슬롯이 가득 찼습니다.";
                        t++;
                    }
                }
                if(key==27) //esc
                {
                    point = 1;
                    break;
                }
            }
            skillset(p);
        }
    }
    command = false;
    home(p);
}

void shop(Player *p)
{
    system("cls");
    bool command=false;

    for(int i=t-5; i<t; i++)
    {
        if(i==-1) cout << "#Log Start\n";
        else if(i<0) cout << '\n';
        else cout << Log[i] << '\n';
    }
    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

    for(int i=1; i<=totalitem; i++)
    {
        if(i==point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << itemlist[i].first << " : BUY " << itemlist[i].second.first << " / SELL " << itemlist[i].second.second << " / 보유 개수 : (" << p->playeritemlist[i].first << ")" <<'\n';
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
                            if(point>0)
                            {
                                point--;
                            }
                        }
                        if(key==80) // 아래쪽
                        {
                            if(point<totalitem)
                            {
                                point++;
                            }
                        }
                    }
                }
                if(key==66 || key==98) // B 키
                {
                    if(p->gold >= itemlist[point].second.first)
                    {
                        p->gold-=itemlist[point].second.first;
                        p->playeritemlist[point].first++;
                        Log[t] = itemlist[point].first + "를 구매하였다.";
                        t++;
                    }
                }
                if(key==27) //esc
                {
                    point = 1;
                    break;
                }
            }
            shop(p);
        }
    }
    command=false;
    home(p);
}

void pattack(Player *p, mob *m)
{
    double multiple = double((p->level - m->level)*5 + 100)/100;
    if(multiple>1.3) multiple=1.3;
    if(multiple < 0) multiple=0;
    int damage = round((rand() % p->damage + p->damage) / (1+(m->defence*0.1)) * multiple);
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
    double multiple = double((m->level - p->level)*5 + 100)/100;
    if(multiple>1.3) multiple=1.3;
    if(multiple < 0) multiple=0;
    int damage = round((rand() % m->damage + m->damage) / (1+(p->defence*0.1)) * multiple);
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
    int mphealing = min(p->maxmp, p->mp+(p->maxmp/20)) - p->mp; // mp 5% 회복
    p->mp += mphealing;
}

void skillattack(Player *p, mob *m, int skillnum)
{
    int damage;
    double multiple = double((p->level - m->level)*5 + 100)/100;
    if(multiple>1.3) multiple=1.3;

    if(skillnum == 1)
    {
        int success = rand() % 4;
        int temp = p->hp;

        if(success>0)
        {
            Log[t] = skills[skillnum].first + "를 사용하여 공격을 막아 일부를 마나로 변환합니다.";
            p->defence*=2;
            t++;
            mattack(p, m);
            p->defence/=2;

            int mphealing = (temp - p->hp) / 2; // 잃은 hp의 50%만큼 mp 회복
            p->mp = min(p->maxmp, p->mp+mphealing);

            mphealing = min(p->maxmp, p->mp+(p->maxmp/20)) - p->mp; // mp 5% 회복
            p->mp += mphealing;
        }
        else
        {
            Log[t] = skills[skillnum].first + "를 사용하였으나 막는 것을 실패하였다!";
            t++;
            p->defence/=2;
            mattack(p, m);
            p->defence*=2;
            int mphealing = min(p->maxmp, p->mp+(p->maxmp/20)) - p->mp; // mp 5% 회복
            p->mp += mphealing;
        }

    }
    if(skillnum == 2) // 크로스컷
    {
        if(skills[skillnum].second.first <= p->mp)
        {
            p->mp-=skills[skillnum].second.first;
            for(int i=0; i<2; i++)
            {
                damage = (rand() % (p->damage*2) + p->damage) / (1+(m->defence*0.1)) * multiple;
                Log[t] = m->name + "에게 " + skills[skillnum].first + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
                t++;
                m->hp-=damage;
                if(m->hp<=0)
                {
                    m->Mobdeath(p);
                    return;
                }
            }
            mattack(p, m);
        }
        else
        {
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(skills[p->skill[point]].second.first) + ")";
            t++;
        }
    }
    if(skillnum == 3) // 힐링
    {
        if(skills[skillnum].second.first <= p->mp)
        {
            p->mp-=skills[skillnum].second.first;
            int healing = min(p->maxhp, p->hp+(p->maxhp/8)) - p->hp; // hp 약 12.5% 회복
            p->hp += healing;
            Log[t] = skills[skillnum].first + "을 사용하여 " + to_string(healing) + " 체력을 회복하였습니다!";
            t++;
        }
        else
        {
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(skills[p->skill[point]].second.first) + ")";
            t++;
        }
    }
    if(skillnum == 4) // 급소찌르기
    {
        if(skills[skillnum].second.first <= p->mp)
        {
            p->mp-=skills[skillnum].second.first;
            damage = (rand() % p->damage) + p->damage * multiple;
            Log[t] = m->name + "에게 " + skills[skillnum].first + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
            t++;
            m->hp-=damage;
            if(m->hp<=0)
            {
                m->Mobdeath(p);
                return;
            }
            mattack(p, m);
        }
        else
        {
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(skills[p->skill[point]].second.first) + ")";
            t++;
        }
    }
    if(skillnum == 5) // 분쇄
    {
        if(skills[skillnum].second.first <= p->mp)
        {
            p->mp-=skills[skillnum].second.first;
            for(int i=0; i<3; i++)
            {
                damage = (rand() % (p->damage * 3)) / (1+(m->defence*0.1)) * multiple;
                Log[t] = m->name + "에게 " + skills[skillnum].first + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
                t++;
                m->hp-=damage;
                if(m->hp<=0)
                {
                    m->Mobdeath(p);
                    return;
                }
            }
            mattack(p, m);
        }
        else
        {
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(skills[p->skill[point]].second.first) + ")";
            t++;
        }
    }
    if(skillnum == 6) // 거인의일격
    {
        if(skills[skillnum].second.first <= p->mp)
        {
            p->mp-=skills[skillnum].second.first;
            damage = (rand() % (p->damage*4) + p->damage*5) / (1+(m->defence*0.1)) * (multiple*3);
            Log[t] = m->name + "에게 " + skills[skillnum].first + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
            t++;
            m->hp-=damage;
            if(m->hp<=0)
            {
                m->Mobdeath(p);
                return;
            }
            mattack(p, m);
        }
        else
        {
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(skills[p->skill[point]].second.first) + ")";
            t++;
        }
    }
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

// 몬스터 소환 확률
void summonmob(Player *p)
{
    mob m;
    if(where==4)
    {
        int n = rand()%100+1;
        if(n<=40) m.MiniSlime();
        else if(n<=70) m.Snake();
        else if(n<=98) m.Slime();
        else if(n<=100) m.Oak();
        fightmenu(&m, p, false);
        fightselectmenu(&m, p);
    }
    if(where==5)
    {
        int n = rand()%100+1;
        if(n<=40) m.RockSlime();
        else if(n<=80) m.Bat();
        else if(n<=95) m.MiniGolem();
        else if(n<=100) m.Golem();
        fightmenu(&m, p, false);
        fightselectmenu(&m, p);
    }
    if(where==6)
    {
        int n = rand()%100+1;
        if(n<=30) m.killerdog();
        else if(n<=50) m.hunter();
        else if(n<=70) m.shadower();
        else if(n<=97) m.badknight();
        else if(n<=100) m.nohead();
        fightmenu(&m, p, false);
        fightselectmenu(&m, p);
    }
    if(where==7)
    {
        int n = rand()%100+1;
        if(n<=35) m.zombie();
        else if(n<=70) m.skeleton();
        else if(n<=90) m.tankzombie();
        else if(n<=97) m.darkknight();
        else if(n<=100) m.demonite();
        fightmenu(&m, p, false);
        fightselectmenu(&m, p);
    }
}

void fightmenu(mob *m, Player *p, bool skillmode)
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

    if(skillmode==false)
    {
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
    }
    else
    {
        for(int i=1; i<=4; i++)
        {
            if(i==point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            cout << skills[p->skill[i]].first << "(" << skills[p->skill[i]].second.first << ")";
            cout << "   ";
        }
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    }
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
    bool skillmode = false;
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
                    if(skillmode)
                    {
                        skillattack(p, m, p->skill[point]);
                        if(killtrigger) point = 1;
                    }
                    else
                    {
                        if(point==1)
                        {
                            attack(p,m);
                            Save(p);
                        }
                        if(point==2)
                        {
                            skillmode = true;
                            point = 1;
                        }
                        if(point==4)
                        {
                            Log[t] = "당신은 " + m->name + "(으)로부터 도망쳤다!";
                            t++;
                            point = 1;
                            return;
                        }
                    }
                }
                if(key==27 && skillmode) //esc
                {
                    skillmode = !skillmode;
                    point = 2;
                }
            system("cls");
            fightmenu(m, p, skillmode);
            }
        }
    }
    killtrigger = false;
    fight(p);
    readymenu(p);
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
        if(p->armorlevel==20)
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

    // 100 95 90 85 80 70 70 60 60 50 50 50 40 40 40 30 30 20 10 5
    if(p->weaponlevel<=4) chance = 100 - p->weaponlevel*5;
    else if(p->weaponlevel<=6) chance = 70;
    else if(p->weaponlevel<=8) chance = 60;
    else if(p->weaponlevel<=11) chance = 50;
    else if(p->weaponlevel<=14) chance = 40;
    else if(p->weaponlevel<=16) chance = 30;
    else if(p->weaponlevel==17) chance = 20;
    else if(p->weaponlevel==18) chance = 10;
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

    // 100 95 90 85 80 70 70 60 60 50 50 50 40 40 40 30 30 20 10 5
    if(p->armorlevel<=4) chance = 100 - p->armorlevel*5;
    else if(p->armorlevel<=6) chance = 70;
    else if(p->armorlevel<=8) chance = 60;
    else if(p->armorlevel<=11) chance = 50;
    else if(p->armorlevel<=14) chance = 40;
    else if(p->armorlevel<=16) chance = 30;
    else if(p->armorlevel==17) chance = 20;
    else if(p->armorlevel==18) chance = 10;
    else chance = 5;

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
