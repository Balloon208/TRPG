#include "GameSetting.h"

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
    pair<int, int> playeritemlist[500]; // 수량, 아이템 종류(소모품 = -1, 스킬북 = 1)

    void heal()
    {
        this->hp = this->maxhp;
        this->mp = this->maxmp;
        Log[t] = this->name + "(이)는 휴식을 하여 전부 회복하였다."; t++;
    }

    void LearnSkill(int num)
    {
        if (num == 2)
        {
            Log[t] = get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
            get<2>(skills[2]) = 1;
        }
        if (num == 3)
        {
            Log[t] = get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
            get<2>(skills[3]) = 1;
        }
        if (num == 4)
        {
            Log[t] = get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
            get<2>(skills[4]) = 1;
        }
        if (num == 5)
        {
            Log[t] = "[BOSS](LV15) 오크 를 죽여 " + get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
            get<2>(skills[5]) = 1;
        }
        if (num == 6)
        {
            Log[t] = "[BOSS](LV15) 오크 를 죽여 " + get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
            get<2>(skills[6]) = 1;
        }
        if (num == 7)
        {
            Log[t] = get<0>(skills[num]) + "을(를) 습득하였습니다!"; t++;
            get<2>(skills[7]) = 1;
        }
    }

    void LVUP()
    {
        this->maxhp += (10 + (level / 2) - 1);
        this->maxmp += (5 + (level / 2) - 1);
        this->damage += (1 + int(level / 4));
        this->defence += (1 + int(level / 4));
        this->speed += 1;
        this->hp = this->maxhp;
        this->mp = this->maxmp;

        this->exp -= this->LVUPexp;
        this->level++;
        this->LVUPexp *= 1.3;
        Log[t] = "레벨이 상승 하였습니다!" + to_string(this->level - 1) + "->" + to_string(this->level); t++;

        if (this->level == 3 && get<2>(skills[2]) == 0)
        {
            this->LearnSkill(2);
        }
        if (this->level == 10 && get<2>(skills[3]) == 0)
        {
            this->LearnSkill(3);
        }
        if (this->level == 15 && get<2>(skills[4]) == 0)
        {
            this->LearnSkill(4);
        }
        if (this->LVUPexp < this->exp) this->LVUP();
    }

    void skilldescription(int skillnum)
    {
        system("cls");
        cout << "스킬 설명\n\n";
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

        cout << "스킬 이름 : " << get<0>(skills[skillnum]) << "(" << get<1>(skills[skillnum]) << ")\n\n";

        if (skillnum == 1)
        {
            cout << "이 스킬을 사용하면 몬스터에게 받는 데미지가 감소하고,\n받는 데미지 만큼 마나를 추가로 회복합니다.";
        }
        if (skillnum == 2)
        {
            cout << "강한 공격을 두번 날립니다. 초심자가 가장 먼저 배우는 스킬 중 하나입니다.\n\n획득처 : 레벨 3 달성";
        }
        if (skillnum == 3)
        {
            cout << "플레이어 hp의 12.5%를 즉시 회복합니다.\n포션이 없다면 해당 스킬을 사용하는 것도 좋습니다.\n\n획득처 : 레벨 10 달성";
        }
        if (skillnum == 4)
        {
            cout << "상대방의 방어력을 무시하는 공격을 합니다.\n방어력이 높은 적에게 매우 효과적입니다.\n\n획득처 : 레벨 15 달성";
        }
        if (skillnum == 5)
        {
            cout << "숲의 대장이 나무들을 정리할 때 사용하는 스킬입니다.\n데미지의 편차가 매우 심한편입니다.\n\n";
            cout << "획득처 : [BOSS](LV15) 오크 처치시 일정 확률로 획득";
        }
        if (skillnum == 6)
        {
            cout << "거구의 오크의 힘을 마나로 구현하여\n적에게 매우 강력한 데미지를 입힙니다.\n";
            cout << "본인보다 약한 생명체에게 큰 데미지를 입니다.\n\n획득처 : [BOSS](LV15) 오크 처치시 일정 확률로 획득";
        }
        if (skillnum == 7)
        {
            cout << "마력을 이용하여 적에게 체력 비례 데미지를 줍니다.\n";
            cout << "상대방이 약해질수록 해당 스킬의 위력도 감소합니다.\n\n획득처 : 상점에서 구매";
        }
        while (1)
        {
            if (kbhit())
            {
                int key = getch();
                if (key == 27) break;//esc
            }
        }
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
    string desc;

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
        this->desc = "작은 슬라임입니다. 약한 산성을 지니고 있으니 조심해야 합니다.";
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
        this->desc = "흔한 뱀입니다. 초보자들을 무는 것을 좋아합니다.";
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
        this->desc = "평범한 슬라임입니다. 산성을 지니고 있으니 조심해야합니다.";
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
        this->desc = "숲의 대장을 담당하는 오크입니다.\n골고루 밸런스가 잡힌 스테이터스를 지니고 있습니다.";
        this->desc += "\n보스 몬스터는 상당히 강하므로 조심해야합니다.";
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
        this->desc = "돌로 이루어진 슬라임입니다. 무려 '고체'의 슬라임 입니다!";
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
        this->desc = "미지의 실험을 통하여 공격성을 띄게 된 박쥐입니다.";
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
        this->desc = "단단한 몸과 높은 파괴력을 지닌 작은 골렘입니다.\n골렘이 분열하여 만들어 진 것 같습니다.";
        Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
    }
    void Golem()
    {
        this->name = "(LV13) 골렘";

        this->maxhp = 700;
        this->mobcode = "C4";
        this->hp = maxhp;
        this->damage = 45;
        this->defence = 25;
        this->speed = 1;
        this->level = 13;
        this->exp = 230;
        this->gold = 2000;
        this->desc = "단단한 몸과 높은 파괴력을 지닌 골렘입니다.\n상당히 정교하게 만들어 졌습니다.";
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
        this->exp = 130;
        this->gold = 800;
        this->desc = "오로지 사냥을 위하여 길들여진 개입니다.\n사냥꾼이 애용하는 강아지중 하나입니다.";
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
        this->exp = 150;
        this->gold = 740;
        this->desc = "인간 사냥을 주로 하는 사냥꾼입니다.\n누군가에게 조종을 당하고 있는 듯 합니다.";
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
        this->desc = "매우 빠른 속도를 가진 몹입니다. 데미지가 매우 강합니다.\n주머니에 돈이 많이 들은 것 같습니다.";
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
        this->exp = 340;
        this->gold = 1750;
        this->desc = "이 구역의 지배자의 알 수 없는 힘이 그의 주변에 감싸돕니다.\n";
        this->desc += "그 힘을 받았음에도 불구하고, 타락화만 하였을 뿐 능력치는 그대로인거 같습니다.";
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
        this->desc = "사념의 영혼이 모여 만들어진 그는 이 구역의 지배자로, 강력한 데미지를 지니고 있습니다.\n";
        this->desc += "머리가 존재하지 않아 급소를 노리기 매우 쉬워 방어력은 매우 낮아 보입니다.";
        Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
    }

    // 저주받은 땅
    void zombie()
    {
        this->name = "(LV17) 좀비";
        this->mobcode = "G1";
        this->maxhp = 1000;
        this->hp = maxhp;
        this->damage = 80;
        this->defence = 30;
        this->speed = 40;
        this->level = 17;
        this->exp = 680;
        this->gold = 2500;
        this->desc = "일반적인 좀비입니다. 다행히도, 물려도 감염은 되지 않습니다.";
        Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
    }
    void skeleton()
    {
        this->name = "(LV18) 스켈레톤";
        this->mobcode = "G2";
        this->maxhp = 777;
        this->hp = maxhp;
        this->damage = 150;
        this->defence = 20;
        this->speed = 50;
        this->level = 18;
        this->exp = 980;
        this->gold = 2800;
        this->desc = "뼈로 이루어진 스켈레톤 입니다.\n모 게임과는 다르게 근접으로 공격합니다.\n";
        this->desc += "사냥개가 이 몬스터를 좋아하는 거 같습니다.";
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
        this->exp = 1100;
        this->gold = 2500;
        this->desc = "단단한 근육을 가진 좀비의 진화종입니다. 방어력이 매우 높습니다";
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
        this->exp = 1250;
        this->gold = 3830;
        this->desc = "악의에 가득찬 기운이 그에게서 느껴집니다.\n오직 당신만을 죽이려는 눈빛을 보입니다.";
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
        this->desc = "마왕 간부급의 악마인 '데모나이트' 입니다.\n";
        this->desc += "일반적인 방법으로는 공격이 통하지 않아 특별한 방법으로 처치해야 할 것 같습니다.";
        Log[t] = this->name + "(을)를 만났다. 무엇을 할까?"; t++;
    }

    void Mobdeath(Player* p)
    {
        killtrigger = true;
        this->hp = 0;
        bool penaltyflag = false;

        Log[t] = this->name + "(을)를 처치했다!"; t++;

        // 레벨 차이가 심하게 나는 경우, 레벨 차이에 따라 패널티를 부과한다.
        if (p->level - this->level >= 5)
        {
            double penalty = (p->level - this->level) * 2 / 5;
            this->gold /= penalty;
            this->exp /= penalty;

            penaltyflag = true;
        }

        Log[t] = "+" + to_string(this->gold) + "G" + "   " + "+" + to_string(this->exp) + "EXP"; t++;
        p->gold += this->gold;
        p->exp += this->exp;
        if (p->LVUPexp <= p->exp) p->LVUP();

        // dropitem
        this->dropitem(p, this->mobcode, penaltyflag);

    }

    void dropitem(Player* p, string mobcode, bool penaltyflag)
    {
        // 몹을 찾기 위해선 'mobcode = {Codename}' 으로 찾으세요.

        int getnum = rand() % 1000;
        int amount;

        if (mobcode == "F3" && !penaltyflag)
        {
            if (getnum < 100)
            {
                amount = rand() % 2 + 1;
                Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[1]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                p->playeritemlist[1].first += amount;
            }
        }
        if (mobcode == "C2" && !penaltyflag)
        {
            if (getnum < 200)
            {
                amount = rand() % 3 + 1;
                Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[1]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                p->playeritemlist[1].first += amount;
            }
        }
        if (mobcode == "C3" && !penaltyflag)
        {
            if (getnum < 100)
            {
                amount = 1;
                Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[2]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                p->playeritemlist[2].first += amount;
            }
            else if (getnum < 300)
            {
                amount = rand() % 2 + 1;
                Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[1]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                p->playeritemlist[1].first += amount;
            }
        }
        if (mobcode == "S2" && !penaltyflag)
        {
            if (getnum < 150)
            {
                amount = rand() % 2 + 1;
                Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[2]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                p->playeritemlist[2].first += amount;
            }
        }
        if (mobcode == "G2" || mobcode == "G3" || mobcode == "G4") return;
        if (mobcode == "G1" && !penaltyflag)
        {
            if (getnum < 5000)
            {
                amount = 1;
                Log[t] = this->name + " 를 죽여" + get<0>(itemlist[3]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                p->playeritemlist[3].first += amount;
            }
        }

        if (mobcode == "FB")
        {
            if (getnum < 500 && get<2>(skills[5]) == 0)
            {
                p->LearnSkill(5);
            }
            getnum = rand() % 1000;
            if (getnum < 200 && get<2>(skills[6]) == 0)
            {
                p->LearnSkill(6);
            }
            if (!penaltyflag)
            {
                amount = rand() % 5 + 1;
                Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[1]) + "x" + to_string(amount) + " 를 힉득하였습니다!"; t++;
                p->playeritemlist[1].first += amount;

                amount = rand() % 3 + 1;
                Log[t] = this->name + " 를 죽여 " + get<0>(itemlist[2]) + "x" + to_string(amount) + " 를 획득하였습니다!"; t++;
                p->playeritemlist[2].first += amount;
            }
        }
    }

    void mobdescription(bool showstatus = false)
    {
        system("cls");
        cout << "몬스터 설명\n\n";
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

        cout << "몬스터 이름 : " << this->name << "\n\n";

        cout << this->desc << "\n\n";

        if (showstatus == false) cout << "상세 정보 보기(S키 누르기)\n\n";
        else cout << "상세 정보 그만 보기(S키 누르기)\n\n";

        if (showstatus)
        {
            cout << "HP : " << this->hp << " / " << this->maxhp << '\n';
            cout << "Damage : " << this->damage << '\n';
            cout << "Defence : " << this->defence << '\n';
            cout << "Speed : " << this->speed << '\n';
            cout << "Dropexp : " << this->exp << '\n';
            cout << "Dropgold : " << this->gold << '\n';
        }
        while (1)
        {
            if (kbhit())
            {
                int key = getch();
                if (key == 27) break;//esc
                if (key == 83 || key == 115) showstatus = !showstatus; // s키

                this->mobdescription(showstatus);
                break;
            }
        }
    }
};

class item
{
public:
    bool useitem(Player* p, int num)
    {
        if (p->playeritemlist[num].first == 0)
        {
            Log[t] = get<0>(itemlist[num]) + "(이)가 없습니다."; t++;
            return false;
        }
        else
        {
            if (num == 1)
            {
                int healing = 50;
                int trueheal = min(p->maxhp, p->hp + healing) - p->hp;
                Log[t] = get<0>(itemlist[1]) + "을 사용하여 체력을 " + to_string(trueheal) + "회복했습니다."; t++;

                p->hp += trueheal;
                p->playeritemlist[1].first--;
            }
            if (num == 2)
            {
                int healing = 300;
                int trueheal = min(p->maxhp, p->hp + healing) - p->hp;
                Log[t] = get<0>(itemlist[2]) + "을 사용하여 체력을 " + to_string(trueheal) + "회복했습니다."; t++;

                p->hp += trueheal;
                p->playeritemlist[2].first--;
            }
            if (num == 3)
            {
                int healing = 1000;
                int trueheal = min(p->maxhp, p->hp + healing) - p->hp;
                Log[t] = get<0>(itemlist[3]) + "을 사용하여 체력을 " + to_string(trueheal) + "회복했습니다."; t++;

                p->hp += trueheal;
                p->playeritemlist[3].first--;
            }

            return true;
        }
    }
    void itemdescription(Player* p, int num)
    {
        system("cls");
        cout << "아이템 설명\n\n";
        cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";

        cout << "아이템 이름 : " << get<0>(itemlist[num]) << " 보유 개수 : " << get<0>(p->playeritemlist[num]) << "\n\n";
        if (num == 1)
        {
            cout << "작은 포션입니다. 사용시 체력을 50 회복합니다.";
        }
        if (num == 2)
        {
            cout << "일반 크기의 포션입니다. 사용시 체력을 300 회복합니다.";
        }
        if (num == 3)
        {
            cout << "큰 크기의 포션입니다. 사용시 체력을 1000 회복합니다.";
        }
        if (num == 4)
        {
            cout << "퍼스트블러드를 배울수 있는 스킬북입니다. 구매 즉시 퍼스트블러드를 습득합니다.\n";
            cout << "(판매 불가, 최대 보유 수량: 1개)";
        }
        while (1)
        {
            if (kbhit())
            {
                int key = getch();
                if (key == 27) break;//esc
            }
        }
    }
};