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

int forgeadd[21]={0,1,2,3,4,5,5,5,5,5,5,7,7,8,8,8,10,15,20,25,30};
int point=1;
int where = 0;
int t=0; // 턴이 지난 횟수
int totalskill = 7;
int totalitem = 4;
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

tuple<string, int,int> skills[500]; // 스킬 이름(띄어 쓰기 X), ManaCost, Learned(1 = 스킬 배움, 2 = 장착 중)
tuple<string, int, int, int> itemlist[500]; // 아이템 이름, 아이템 종류 ,구매가, 판매가

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
        pair<int,int> playeritemlist[500]; // 수량, 아이템 종류(소모품 = -1, 스킬북 = 1)

        void heal()
        {
            this->hp=this->maxhp;
            this->mp=this->maxmp;
            Log[t] = this->name + "(이)는 휴식을 하여 전부 회복하였다."; t++;
        }

        void LearnSkill(int num)
        {
            if(num==2)
            {
                Log[t] = get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
                get<2>(skills[2])=1;
            }
            if(num==3)
            {
                Log[t] = get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
                get<2>(skills[3])=1;
            }
            if(num==4)
            {
                Log[t] = get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
                get<2>(skills[4])=1;
            }
            if(num==5)
            {
                Log[t] = "[BOSS](LV15) 오크 를 죽여 " + get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
                get<2>(skills[5])=1;
            }
            if(num==6)
            {
                Log[t] = "[BOSS](LV15) 오크 를 죽여 " + get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
                get<2>(skills[6])=1;
            }
            if(num==7)
            {
                Log[t] = get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
                get<2>(skills[7])=1;
            }
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
            Log[t] = "레벨이 상승 하였습니다!" + to_string(this->level-1) + "->" + to_string(this->level); t++;

            if(this->level==3 && get<2>(skills[2])==0)
            {
                this->LearnSkill(2);
            }
            if(this->level==10  && get<2>(skills[3])==0)
            {
                this->LearnSkill(3);
            }
            if(this->level==15  && get<2>(skills[4])==0)
            {
                this->LearnSkill(4);
            }
            if(this->LVUPexp<this->exp) this->LVUP();
        }
};

class mob
{
    public:
        string name;
        string mobcode;
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
            this->mobcode = "F1";
            this->maxhp = 50;
            this->hp = maxhp;
            this->damage = 4;
            this->defence = 3;
            this->speed = 5;
            this->level = 1;
            this->exp = 5;
            this->gold = 80;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void Snake()
        {
            this->name = "(LV2) 뱀";
            this->mobcode = "F2";
            this->maxhp = 75;
            this->hp = maxhp;
            this->damage = 6;
            this->defence = 3;
            this->speed = 10;
            this->level = 2;
            this->exp = 8;
            this->gold = 130;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void Slime()
        {
            this->name = "(LV3) 슬라임";
            this->mobcode = "F3";
            this->maxhp = 100;
            this->hp = maxhp;
            this->damage = 9;
            this->defence = 3;
            this->speed = 3;
            this->level = 3;
            this->exp = 15;
            this->gold = 200;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void Oak()
        {
            this->name = "[BOSS](LV15) 오크";
            this->mobcode = "FB";
            this->maxhp = 10000;
            this->hp = maxhp;
            this->damage = 50;
            this->defence = 30;
            this->speed = 22;
            this->level = 15;
            this->exp = 2450;
            this->gold = 7000;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        // 케이브 케이브
        void RockSlime()
        {
            this->name = "(LV4) 돌 슬라임";
            this->mobcode = "C1";
            this->maxhp = 100;
            this->hp = maxhp;
            this->damage = 15;
            this->defence = 25;
            this->speed = 1;
            this->level = 4;
            this->exp = 20;
            this->gold = 300;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void Bat()
        {
            this->name = "(LV6) 박쥐";
            this->mobcode = "C2";
            this->maxhp = 120;
            this->hp = maxhp;
            this->damage = 25;
            this->defence = 5;
            this->speed = 12;
            this->level = 6;
            this->exp = 30;
            this->gold = 430;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void MiniGolem()
        {
            this->name = "(LV8) 미니 골렘";
            this->mobcode = "C3";
            this->maxhp = 200;
            this->hp = maxhp;
            this->damage = 30;
            this->defence = 15;
            this->speed = 1;
            this->level = 8;
            this->exp = 45;
            this->gold = 600;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void Golem()
        {
            this->name = "(LV13) 골렘";

            this->maxhp = 500;
            this->mobcode = "C4";
            this->hp = maxhp;
            this->damage = 45;
            this->defence = 25;
            this->speed = 1;
            this->level = 13;
            this->exp = 230;
            this->gold = 2000;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        // 서늘한 공터
        void killerdog()
        {
            this->name = "(LV10) 사냥개";
            this->mobcode = "S1";
            this->maxhp = 200;
            this->hp = maxhp;
            this->damage = 45;
            this->defence = 10;
            this->speed = 22;
            this->level = 10;
            this->exp = 100;
            this->gold = 800;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void hunter()
        {
            this->name = "(LV10) 사냥꾼";
            this->mobcode = "S2";
            this->maxhp = 300;
            this->hp = maxhp;
            this->damage = 40;
            this->defence = 15;
            this->speed = 15;
            this->level = 10;
            this->exp = 90;
            this->gold = 740;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void shadower()
        {
            this->name = "(LV11) 암살자";
            this->mobcode = "S3";
            this->maxhp = 120;
            this->hp = maxhp;
            this->damage = 500;
            this->defence = 1;
            this->speed = 30;
            this->level = 11;
            this->exp = 50;
            this->gold = 1300;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void badknight()
        {
            this->name = "(LV13) 타락한 기사";
            this->mobcode = "S4";
            this->maxhp = 600;
            this->hp = maxhp;
            this->damage = 50;
            this->defence = 15;
            this->speed = 20;
            this->level = 13;
            this->exp = 200;
            this->gold = 1750;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void nohead()
        {
            this->name = "[BOSS](LV22) 듀라한";
            this->mobcode = "SB";
            this->maxhp = 22222;
            this->hp = maxhp;
            this->damage = 222;
            this->defence = 1;
            this->speed = 40;
            this->level = 22;
            this->exp = 7500;
            this->gold = 33000;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }

        // 저주받은 땅
        void zombie()
        {
            this->name = "(LV15) 좀비";
            this->mobcode = "G1";
            this->maxhp = 1000;
            this->hp = maxhp;
            this->damage = 80;
            this->defence = 30;
            this->speed = 40;
            this->level = 15;
            this->exp = 440;
            this->gold = 2500;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void skeleton()
        {
            this->name = "(LV17) 스켈레톤";
            this->mobcode = "G2";
            this->maxhp = 777;
            this->hp = maxhp;
            this->damage = 150;
            this->defence = 20;
            this->speed = 50;
            this->level = 17;
            this->exp = 520;
            this->gold = 2800;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void tankzombie()
        {
            this->name = "(LV18) 탱크 좀비";
            this->mobcode = "G3";
            this->maxhp = 1000;
            this->hp = maxhp;
            this->damage = 100;
            this->defence = 200;
            this->speed = 1;
            this->level = 18;
            this->exp = 700;
            this->gold = 2500;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void darkknight()
        {
            this->name = "(LV20) 칠흑의 기사";
            this->mobcode = "G4";
            this->maxhp = 1500;
            this->hp = maxhp;
            this->damage = 130;
            this->defence = 50;
            this->speed = 35;
            this->level = 20;
            this->exp = 1030;
            this->gold = 3830;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }
        void demonite()
        {
            this->name = "[BOSS](LV35) 마왕 간부 데모나이트";
            this->mobcode = "GB";
            this->maxhp = 5000;
            this->hp = maxhp;
            this->damage = 800;
            this->defence = 999999;
            this->speed = 20;
            this->level = 35;
            this->exp = 25000;
            this->gold = 75000;
            Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
        }

        void Mobdeath(Player *p)
        {
            killtrigger = true;
            this->hp=0;
            bool penaltyflag = false;

            Log[t] = this->name + "(을)를 처치했다!"; t++;

            // 레벨 차이가 심하게 나는 경우, 레벨 차이에 따라 패널티를 부과한다.
            if(p->level-this->level>=5)
            {
                double penalty = (p->level-this->level)*2 / 5;
                this->gold/=penalty;
                this->exp/=penalty;

                penaltyflag = true;
            }

            Log[t] = "+" + to_string(this->gold) + "G" + "   " + "+" + to_string(this->exp) + "EXP"; t++;
            p->gold+=this->gold;
            p->exp+=this->exp;
            if(p->LVUPexp<=p->exp) p->LVUP();

            // dropitem
            this->dropitem(p, this->mobcode, penaltyflag);

        }

        void dropitem(Player *p, string mobcode, bool penaltyflag)
        {
            // 몹을 찾기 위해선 'mobcode = {Codename}' 으로 찾으세요.

            int getnum = rand() % 1000;
            int amount;

            if(mobcode == "F3" && !penaltyflag)
            {
                if(getnum < 100)
                {
                    amount = rand() % 2 + 1;
                    Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[1]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                    p->playeritemlist[1].first+=amount;
                }
            }
            if(mobcode == "C2" && !penaltyflag)
            {
                if(getnum < 200)
                {
                    amount = rand() % 3 + 1;
                    Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[1]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                    p->playeritemlist[1].first+=amount;
                }
            }
            if(mobcode == "C3" && !penaltyflag)
            {
                if(getnum < 100)
                {
                    amount = 1;
                    Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[2]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                    p->playeritemlist[2].first+=amount;
                }
                else if(getnum < 300)
                {
                    amount = rand() % 2 + 1;
                    Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[1]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                    p->playeritemlist[1].first+=amount;
                }
            }
            if(mobcode == "S2" && !penaltyflag)
            {
                if(getnum < 150)
                {
                    amount = rand() % 2 + 1;
                    Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[2]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                    p->playeritemlist[2].first+=amount;
                }
            }
            if(mobcode == "G2" || mobcode == "G3" || mobcode == "G4") return;
            if(mobcode == "G1" && !penaltyflag)
            {
                if(getnum < 5000)
                {
                    amount = 1;
                    Log[t] = this->name + " 를 죽여" + get<0>(itemlist[3]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                    p->playeritemlist[3].first+=amount;
                }
            }

            if(mobcode == "FB")
            {
                if(getnum < 500 && get<2>(skills[5]) == 0)
                {
                    p->LearnSkill(5);
                }
                getnum = rand() % 1000;
                if(getnum < 200 && get<2>(skills[6]) == 0)
                {
                    p->LearnSkill(6);
                }
                if(!penaltyflag)
                {
                    amount = rand() % 5 + 1;
                    Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[1]) + "x" + to_string(amount) + " 를 힉득하였습니다!"; t++;
                    p->playeritemlist[1].first+=amount;

                    amount = rand() % 3 + 1;
                    Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[2]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                    p->playeritemlist[2].first+=amount;
                }
            }
        }
};

class item
{
    public:
        bool useitem(Player *p, int num)
        {
            if(p->playeritemlist[num].first==0)
            {
                Log[t] = get<0>(itemlist[num]) + "(이)가 없습니다."; t++;
                return false;
            }
            else
            {
                if(num==1)
                {
                    int healing = 50;
                    int trueheal = min(p->maxhp, p->hp + healing) - p->hp;
                    Log[t] = get<0>(itemlist[1]) + "을 사용하여 체력을 " + to_string(trueheal) + "회복했습니다."; t++;

                    p->hp+=trueheal;
                    p->playeritemlist[1].first--;
                }
                if(num==2)
                {
                    int healing = 300;
                    int trueheal = min(p->maxhp, p->hp + healing) - p->hp;
                    Log[t] = get<0>(itemlist[2]) + "을 사용하여 체력을 " + to_string(trueheal) + "회복했습니다."; t++;

                    p->hp+=trueheal;
                    p->playeritemlist[2].first--;
                }
                if(num==3)
                {
                    int healing = 1000;
                    int trueheal = min(p->maxhp, p->hp + healing) - p->hp;
                    Log[t] = get<0>(itemlist[3]) + "을 사용하여 체력을 " + to_string(trueheal) + "회복했습니다."; t++;

                    p->hp+=trueheal;
                    p->playeritemlist[3].first--;
                }

                return true;
            }
        }
};

void Login(Player *p); // 첫 로그인 시 실행되는 함수
void Save(Player *p); // 게임 진행 상황을 저장하는 함수
void Load(Player *p); // 이전에 진행한 게임을 불러오는 함수
void showlog(); // 로그를 보여주는 함수
void showplayerstatus(Player *p, string slot1, string slot2, string slot3, string slot4); // 플레이어 스테이터스
void fulllog(int current, int finish); // 풀로그 보여주는 함수
void showfulllog(); // 풀로그 인터페이스
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
bool selectitem(Player *p); // 아이템 선택
void showitem(Player *p); // 아이템 보여주기
void Forge(Player *p, int protect, int chance, string mode, int upmoney); // 강화가 진행되는 함수
void weaponforge(Player *p, bool visit); // 무기강화소 (확률 및 돈 조정)
void armorforge(Player *p, bool visit); // 방어구강화소 (확률 및 돈 조정)


void Login(Player *p)
{
    int n;
    string name;

    FILE* fp;

    fp = fopen("./Save/playerinfom.txt","r");
    fscanf(fp,"register:%d", &n);
    fclose(fp);

    if(n!=2)
    {
        cout << "신규 가입을 위하여 이름을 입력하세요 : ";
        cin >> name;

        char wname[200];
        strcpy(wname, name.c_str());

        fp = fopen("./Save/playerinfom.txt","w");
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

        fp = fopen("./Save/playerskills.txt","w");

        // 스킬 설정 옵션 (skill setting), name, Mana, Learned(1 = 스킬 배움, 2 = 장착 중)
        fprintf(fp, "방어 0 1\n");
        fprintf(fp, "크로스컷 30 0\n");
        fprintf(fp, "힐링 60 0\n");
        fprintf(fp, "급소찌르기 20 0\n");
        fprintf(fp, "분쇄 50 0\n");
        fprintf(fp, "거인의일격 100 0\n");
        fprintf(fp, "퍼스트블러드 200 0\n");
        fprintf(fp, "0, 0, 0, 0");

        fclose(fp);

        fp = fopen("./Save/itemDB.txt","w");

        fprintf(fp, "소형포션 -1 500 300\n");
        fprintf(fp, "중형포션 -1 2000 1500\n");
        fprintf(fp, "대형포션 -1 5000 3000\n");
        fprintf(fp, "[Skillbook]퍼스트블러드 7 30000 0\n");

        fclose(fp);

        fp = fopen("./Save/playeritem.txt","w");

        fprintf(fp, "소형포션 0 -1\n");
        fprintf(fp, "중형포션 0 -1\n");
        fprintf(fp, "대형포션 0 -1\n");
        fprintf(fp, "대형포션 0 1\n");

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
    char wname[200];
    strcpy(wname, p->name.c_str());

    FILE* fp;
    fp = fopen("./Save/playerinfom.txt","w");
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

    fp = fopen("./Save/playerskills.txt","w");
    for(int i=1; i<=totalskill; i++)
    {
        fprintf(fp,"%s %d %d\n", get<0>(skills[i]).c_str(), get<1>(skills[i]), get<2>(skills[i]));
    }
    fprintf(fp,"%d %d %d %d", p->skill[1], p->skill[2], p->skill[3] ,p->skill[4]);
    fclose(fp);

    fp = fopen("./Save/playeritem.txt","w");

    char itemnames[10001];
    for(int i=1; i<=totalitem; i++)
    {
        strcpy(itemnames, get<0>(itemlist[i]).c_str());
        fprintf(fp,"%s %d %d\n", itemnames, p->playeritemlist[i].first, p->playeritemlist[i].second);
    }
    fclose(fp);

    fp = fopen("./Save/itemDB.txt","w");

    char DBitemnames[10001];
    for(int i=1; i<=totalitem; i++)
    {
        strcpy(DBitemnames, get<0>(itemlist[i]).c_str());
        fprintf(fp,"%s %d %d %d\n", DBitemnames, get<1>(itemlist[i]), get<2>(itemlist[i]), get<3>(itemlist[i]));
    }
    fclose(fp);
}

void Load(Player *p)
{
    int trash;
    char wname[200];

    FILE* fp;
    fp = fopen("./Save/playerinfom.txt","r");
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

    fp = fopen("./Save/playerskills.txt","r");
    for(int i=1; i<=totalskill; i++)
    {
        char skillnames[10000];
        fscanf(fp,"%s %d %d\n", skillnames, &get<1>(skills[i]), &get<2>(skills[i]));
        get<0>(skills[i]) = skillnames;
    }
    fscanf(fp,"%d %d %d %d", &p->skill[1], &p->skill[2], &p->skill[3] ,&p->skill[4]);
    fclose(fp);

    fp = fopen("./Save/itemDB.txt","r");
    for(int i=1; i<=totalitem; i++)
    {
        char itemnames[10000];
        fscanf(fp,"%s %d %d %d\n", itemnames, &get<1>(itemlist[i]), &get<2>(itemlist[i]), &get<3>(itemlist[i]));
        get<0>(itemlist[i]) = itemnames;
    }
    fclose(fp);

    fp = fopen("./Save/playeritem.txt","r");
    for(int i=1; i<=totalitem; i++)
    {
        char trash[10000];
        fscanf(fp,"%s %d %d\n", trash, &p->playeritemlist[i].first, &p->playeritemlist[i].second);
    }
    fclose(fp);
}

void showlog()
{
    for(int i=t-5; i<t; i++)
    {
        if(i<0) cout << '\n';
        else cout << Log[i] << '\n';
    }
    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";
}

void showplayerstatus(Player *p, string slot1, string slot2, string slot3, string slot4)
{
    playerhppercent = (double)p->hp/p->maxhp * 100;
    playermppercent = (double)p->mp/p->maxmp * 100;
    playerexppercent = (double)p->exp/p->LVUPexp * 100;

    // 각 슬롯에 해당하는 이름만 넣어주시면 됩니다. ex) showplayerstatus(p, "1", "2", "3", "4");
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
    cout << "HP : " << p->hp << " / " << p->maxhp;
    cout << "\n\n";

    for(int i=1; i<=4; i++)
    {
        if(i==point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        if(i==1) cout << slot1;
        if(i==2) cout << slot2;
        if(i==3) cout << slot3;
        if(i==4) cout << slot4;
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

void fulllog(int current, int finish)
{
    system("cls");
    for(int i=current; i<=finish; i++)
    {
        cout << "[" << i << "]" << " " << Log[i] << '\n';
    }
}

void showfulllog()
{
    int lognum=20;
    int current = (t-lognum<=0) ? 0 : t-lognum;
    int finish = (current<=lognum) ? t-1 : current+lognum-1;
    int key;

    fulllog(current, finish);
    while(1)
    {
        if(kbhit())
        {
            key=getch();
            if(key==224) // 방향키
            {
                key=getch();
                if(key==72) // 위쪽
                {
                    if(current-lognum<=0) current=0;
                    else current-=lognum;
                }
                if(key==80) // 아래쪽
                {
                    if(finish+lognum>=t-1) current=t-lognum-1 > 0 ? t-lognum-1 : 0;
                    else current+=lognum;
                }
            }
            if(key==27) //esc
            {
                break;
            }
            finish = (t<=lognum) ? t-1 : current+20;
            fulllog(current, finish);
        }
    }
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
    showlog();
    showplayerstatus(p, "이동", "휴식", "스킬설정", "상점");
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
            if(key==224) // 방향키
            {
                key=getch();
                if(key==75 && point>1) point--; // 왼쪽
                if(key==77 && point<4) point++; // 오른쪽
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
            if(key==84 || key==116) showfulllog(); // k
            system("cls");
            homemenu(p);
        }
    }
    command = false;
}

void movemenu(Player *p)
{
    bool command = false;

    system("cls");

    showlog();

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
                    if(key==72 && point>1) point--; // 위쪽
                    if(key==80 && point<stage-1) point++; // 아래쪽
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
                    Log[t] = "당신은 " + worldmap[where] + "(으)로 여정을 떠났다."; t++;
                    fight(p);
                    readymenu(p);
                }
                if(key==27) //esc
                {
                    point = 1;
                    break;
                }
                if(key==84 || key==116) showfulllog(); // k
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

    showlog();

    for(int i=1; i<=4; i++)
    {
        p->skill[i]=0;
    }
    usingskill=1;

    for(int i=1; i<=totalskill; i++)
    {
        if(i==point) cout << ">";

        if(get<2>(skills[i])==1)
        {
            cout << "    " << get<0>(skills[i]) << "(" << get<1>(skills[i]) << ")" << '\n';
        }
        else if(get<2>(skills[i])==2)
        {
            p->skill[usingskill]=i;
            usingskill++;
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
            cout << "   " << get<0>(skills[i]) << "(" << get<1>(skills[i]) << ")" << '\n';
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }
        else
        {
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            cout << "   " << get<0>(skills[i]) << "(" << get<1>(skills[i]) << ")" << '\n';
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
                    if(usingskill<=4 || get<2>(skills[point])==2) // 스킬 최대갯수 내에 들거나, 해제를 하는 경우.
                    {
                        if(get<2>(skills[point])==1) // 장착의 경우
                        {
                            Log[t] = get<0>(skills[point]) + " 스킬을 장착하였습니다."; t++;
                            get<2>(skills[point])=2;
                        }
                        else if(get<2>(skills[point])==2) // 해제의 경우
                        {
                            Log[t] = get<0>(skills[point]) + " 스킬을 해제하였습니다."; t++;
                            get<2>(skills[point])=1;
                        }
                    }
                    else if(get<2>(skills[point])==1) // 최대갯수이며, 장착을 하는 경우
                    {
                        Log[t] = "스킬 슬롯이 가득 찼습니다."; t++;
                    }
                }
                if(key==27) //esc
                {
                    point = 1;
                    break;
                }
                if(key==84 || key==116) showfulllog(); // k
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

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    showlog();

    cout << "구매하기 위해선 B, 팔기 위해선 S를 눌러주세요.\n\n";
    cout << "현재 골드 : " << p->gold << "\n\n";
    for(int i=1; i<=totalitem; i++)
    {
        if(i==point)
        {
            if(get<1>(itemlist[i])==-100) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        }
        else
        {
            if(get<1>(itemlist[i])==-100) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }

        cout << get<0>(itemlist[i]) << " : BUY " << get<2>(itemlist[i]) << " / SELL " << get<3>(itemlist[i]) << " / 보유 개수 : (" << p->playeritemlist[i].first << ")" <<'\n';
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    while(!command)
    {
        int key;
        if(kbhit())
        {
            key=getch();

            if(key==224) // 방향키
            {
                key=getch();
                if(key==72 && point>1) point--; // 위쪽
                if(key==80 && point<totalitem) point++; // 아래쪽
            }

            if(key==66 || key==98 && get<1>(itemlist[point])!=-100) // B 키
            {
                if(p->gold >= get<2>(itemlist[point]))
                {
                    p->gold-=get<2>(itemlist[point]);
                    p->playeritemlist[point].first++;
                    Log[t] = get<0>(itemlist[point]) + "를 구매하였다."; t++;

                    if(get<1>(itemlist[point])>=1 && get<1>(itemlist[point])<100) // 스킬북
                    {
                        p->LearnSkill(get<1>(itemlist[point]));
                        get<1>(itemlist[point])=-100;
                    }
                    Save(p);
                }
                else
                {
                    Log[t] = "골드가 부족합니다. (" + to_string(p->gold) + "/" + to_string(get<2>(itemlist[point])) + ")"; t++;
                }
            }
            if(key==83 || key==115) // S 키
            {
                if(p->playeritemlist[point].first > 0 && !(p->playeritemlist[point].second>=1 && p->playeritemlist[point].second<100))
                {
                    p->gold+=get<3>(itemlist[point]);
                    p->playeritemlist[point].first--;
                    Log[t] = get<0>(itemlist[point]) + "를 판매하였다.";
                    t++;
                    Save(p);
                }
            }
            if(key==27) //esc
            {
                point = 1;
                break;
            }
            if(key==84 || key==116) showfulllog(); // k
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
            Log[t] = get<0>(skills[skillnum]) + "를 사용하여 공격을 막아 피해량의 일부를 마나로 변환합니다.";
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
            Log[t] = get<0>(skills[skillnum]) + "를 사용하였으나 막는 것을 실패하였다!";
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
        if(get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp-=get<1>(skills[skillnum]);
            for(int i=0; i<2; i++)
            {
                damage = (rand() % (p->damage*2) + p->damage) / (1+(m->defence*0.1)) * multiple;
                Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
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
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if(skillnum == 3) // 힐링
    {
        if(get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp-=get<1>(skills[skillnum]);
            int healing = min(p->maxhp, p->hp+(p->maxhp/8)) - p->hp; // hp 약 12.5% 회복
            p->hp += healing;
            Log[t] = get<0>(skills[skillnum]) + "을 사용하여 " + to_string(healing) + " 체력을 회복하였습니다!";
            t++;
        }
        else
        {
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if(skillnum == 4) // 급소찌르기
    {
        if(get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp-=get<1>(skills[skillnum]);
            damage = (rand() % p->damage) + p->damage * multiple;
            Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
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
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if(skillnum == 5) // 분쇄
    {
        if(get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp-=get<1>(skills[skillnum]);
            for(int i=0; i<3; i++)
            {
                damage = (rand() % (p->damage * 4)) / (1+(m->defence*0.1)) * multiple;
                Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
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
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if(skillnum == 6) // 거인의일격
    {
        if(get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp-=get<1>(skills[skillnum]);
            damage = (rand() % (p->damage*4) + p->damage*5) / (1+(m->defence*0.1)) * (multiple*3);
            Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
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
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if(skillnum == 7) // 퍼스트블러드
    {
        if(get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp-=get<1>(skills[skillnum]);
            damage = m->hp / 10;
            Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
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
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
}

void fight(Player *p)
{
    Save(p);
    system("cls");
    mob m;

    showlog();
    showplayerstatus(p, "탐험한다", "돌아간다", "-", "-");
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
                    if(key==75 && point>1) point--; // 왼쪽
                    if(key==77 && point<4) point++; // 오른쪽
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
                        Log[t] = p->name + "(이)는 탐험을 그만두고 돌아갔다.";t++;
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

    showlog();

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

    if(skillmode==false) showplayerstatus(p, "공격", "스킬", "아이템", "도망");
    else
    {
        string skillarray[5];
        for(int i=1; i<=4; i++)
        {
            skillarray[i] = get<0>(skills[p->skill[i]]) + "(" + to_string(get<1>(skills[p->skill[i]])) + ")";
        }
        showplayerstatus(p, skillarray[1], skillarray[2], skillarray[3], skillarray[4]);

    }
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

            if(key==224) // 방향키
            {
                key=getch();
                if(key==75 && point>1) point--; // 왼쪽
                if(key==77 && point<4) point++; // 오른쪽
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
                    if(point==3)
                    {
                        bool use = selectitem(p);
                        if(use)
                        {
                            mattack(p,m);
                            int mphealing = min(p->maxmp, p->mp+(p->maxmp/20)) - p->mp; // mp 5% 회복
                            p->mp += mphealing;
                        }
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
            if(key==84 || key==116) showfulllog(); //k
            system("cls");
            fightmenu(m, p, skillmode);
        }
    }
    killtrigger = false;
    fight(p);
    readymenu(p);
}


void showitem(Player *p, int point)
{
    for(int i=1; i<=totalitem; i++)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        if(point==i) cout << "> ";
        if(p->playeritemlist[i].first==0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

        cout << get<0>(itemlist[i]) << "(" << p->playeritemlist[i].first << ")\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

bool selectitem(Player *p)
{
    item item;
    bool selected = false;
    int key;
    point = 1;

    while(!selected)
    {
        system("cls");
        showlog();
        showitem(p, point);

        while(1)
        {
            if(kbhit())
            {
                key = getch();
                if(key==224) // 방향키
                {
                    key=getch();
                    if(key==72 && point>1) point--; // 위쪽
                    if(key==80 && point<totalitem) point++; // 아래쪽

                }
                if(key==13) // enter키
                {
                    bool used = item.useitem(p, point);
                    selected = true;
                    point = 3;
                    Save(p);
                    return used;
                }
                if(key==27) //esc
                {
                    point = 3;
                    selected = true;
                    return false;
                }
                break;
            }
        }
    }
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

    showlog();

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
    else if(key==84 || key==116) showfulllog(); // k
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

    showlog();

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
    else if(key==84 || key==116) showfulllog(); // k
    else if(key==27) return;
    else armorforge(p, true);
}

int main()
{
    srand(GetTickCount());
    Player p;
    Login(&p);
    Load(&p);
    Log[0]="#Log Start"; t++;
    home(&p);
}
