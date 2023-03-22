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
    pair<int, int> playeritemlist[500]; // ����, ������ ����(�Ҹ�ǰ = -1, ��ų�� = 1)

    void heal()
    {
        this->hp = this->maxhp;
        this->mp = this->maxmp;
        Log[t] = this->name + "(��)�� �޽��� �Ͽ� ���� ȸ���Ͽ���."; t++;
    }

    void LearnSkill(int num)
    {
        if (num == 2)
        {
            Log[t] = get<0>(skills[num]) + "��(��) �����Ͽ����ϴ�!"; t++;
            get<2>(skills[2]) = 1;
        }
        if (num == 3)
        {
            Log[t] = get<0>(skills[num]) + "��(��) �����Ͽ����ϴ�!"; t++;
            get<2>(skills[3]) = 1;
        }
        if (num == 4)
        {
            Log[t] = get<0>(skills[num]) + "��(��) �����Ͽ����ϴ�!"; t++;
            get<2>(skills[4]) = 1;
        }
        if (num == 5)
        {
            Log[t] = "[BOSS](LV15) ��ũ �� �׿� " + get<0>(skills[num]) + "��(��) �����Ͽ����ϴ�!"; t++;
            get<2>(skills[5]) = 1;
        }
        if (num == 6)
        {
            Log[t] = "[BOSS](LV15) ��ũ �� �׿� " + get<0>(skills[num]) + "��(��) �����Ͽ����ϴ�!"; t++;
            get<2>(skills[6]) = 1;
        }
        if (num == 7)
        {
            Log[t] = get<0>(skills[num]) + "��(��) �����Ͽ����ϴ�!"; t++;
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
        Log[t] = "������ ��� �Ͽ����ϴ�!" + to_string(this->level - 1) + "->" + to_string(this->level); t++;

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
        cout << "��ų ����\n\n";
        cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n\n";

        cout << "��ų �̸� : " << get<0>(skills[skillnum]) << "(" << get<1>(skills[skillnum]) << ")\n\n";

        if (skillnum == 1)
        {
            cout << "�� ��ų�� ����ϸ� ���Ϳ��� �޴� �������� �����ϰ�,\n�޴� ������ ��ŭ ������ �߰��� ȸ���մϴ�.";
        }
        if (skillnum == 2)
        {
            cout << "���� ������ �ι� �����ϴ�. �ʽ��ڰ� ���� ���� ���� ��ų �� �ϳ��Դϴ�.\n\nȹ��ó : ���� 3 �޼�";
        }
        if (skillnum == 3)
        {
            cout << "�÷��̾� hp�� 12.5%�� ��� ȸ���մϴ�.\n������ ���ٸ� �ش� ��ų�� ����ϴ� �͵� �����ϴ�.\n\nȹ��ó : ���� 10 �޼�";
        }
        if (skillnum == 4)
        {
            cout << "������ ������ �����ϴ� ������ �մϴ�.\n������ ���� ������ �ſ� ȿ�����Դϴ�.\n\nȹ��ó : ���� 15 �޼�";
        }
        if (skillnum == 5)
        {
            cout << "���� ������ �������� ������ �� ����ϴ� ��ų�Դϴ�.\n�������� ������ �ſ� �������Դϴ�.\n\n";
            cout << "ȹ��ó : [BOSS](LV15) ��ũ óġ�� ���� Ȯ���� ȹ��";
        }
        if (skillnum == 6)
        {
            cout << "�ű��� ��ũ�� ���� ������ �����Ͽ�\n������ �ſ� ������ �������� �����ϴ�.\n";
            cout << "���κ��� ���� ����ü���� ū �������� �Դϴ�.\n\nȹ��ó : [BOSS](LV15) ��ũ óġ�� ���� Ȯ���� ȹ��";
        }
        if (skillnum == 7)
        {
            cout << "������ �̿��Ͽ� ������ ü�� ��� �������� �ݴϴ�.\n";
            cout << "������ ���������� �ش� ��ų�� ���µ� �����մϴ�.\n\nȹ��ó : �������� ����";
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

    //������ ��
    void MiniSlime()
    {
        this->name = "(LV1) �̴� ������";
        this->mobcode = "F1";
        this->maxhp = 50;
        this->hp = maxhp;
        this->damage = 4;
        this->defence = 3;
        this->speed = 5;
        this->level = 1;
        this->exp = 5;
        this->gold = 80;
        this->desc = "���� �������Դϴ�. ���� �꼺�� ���ϰ� ������ �����ؾ� �մϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void Snake()
    {
        this->name = "(LV2) ��";
        this->mobcode = "F2";
        this->maxhp = 75;
        this->hp = maxhp;
        this->damage = 6;
        this->defence = 3;
        this->speed = 10;
        this->level = 2;
        this->exp = 8;
        this->gold = 130;
        this->desc = "���� ���Դϴ�. �ʺ��ڵ��� ���� ���� �����մϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void Slime()
    {
        this->name = "(LV3) ������";
        this->mobcode = "F3";
        this->maxhp = 100;
        this->hp = maxhp;
        this->damage = 9;
        this->defence = 3;
        this->speed = 3;
        this->level = 3;
        this->exp = 15;
        this->gold = 200;
        this->desc = "����� �������Դϴ�. �꼺�� ���ϰ� ������ �����ؾ��մϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void Oak()
    {
        this->name = "[BOSS](LV15) ��ũ";
        this->mobcode = "FB";
        this->maxhp = 10000;
        this->hp = maxhp;
        this->damage = 50;
        this->defence = 30;
        this->speed = 22;
        this->level = 15;
        this->exp = 2450;
        this->gold = 7000;
        this->desc = "���� ������ ����ϴ� ��ũ�Դϴ�.\n���� �뷱���� ���� �������ͽ��� ���ϰ� �ֽ��ϴ�.";
        this->desc += "\n���� ���ʹ� ����� ���ϹǷ� �����ؾ��մϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    // ���̺� ���̺�
    void RockSlime()
    {
        this->name = "(LV4) �� ������";
        this->mobcode = "C1";
        this->maxhp = 100;
        this->hp = maxhp;
        this->damage = 15;
        this->defence = 25;
        this->speed = 1;
        this->level = 4;
        this->exp = 20;
        this->gold = 300;
        this->desc = "���� �̷���� �������Դϴ�. ���� '��ü'�� ������ �Դϴ�!";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void Bat()
    {
        this->name = "(LV6) ����";
        this->mobcode = "C2";
        this->maxhp = 120;
        this->hp = maxhp;
        this->damage = 25;
        this->defence = 5;
        this->speed = 12;
        this->level = 6;
        this->exp = 30;
        this->gold = 430;
        this->desc = "������ ������ ���Ͽ� ���ݼ��� ��� �� �����Դϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void MiniGolem()
    {
        this->name = "(LV8) �̴� ��";
        this->mobcode = "C3";
        this->maxhp = 200;
        this->hp = maxhp;
        this->damage = 30;
        this->defence = 15;
        this->speed = 1;
        this->level = 8;
        this->exp = 45;
        this->gold = 600;
        this->desc = "�ܴ��� ���� ���� �ı����� ���� ���� ���Դϴ�.\n���� �п��Ͽ� ����� �� �� �����ϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void Golem()
    {
        this->name = "(LV13) ��";

        this->maxhp = 700;
        this->mobcode = "C4";
        this->hp = maxhp;
        this->damage = 45;
        this->defence = 25;
        this->speed = 1;
        this->level = 13;
        this->exp = 230;
        this->gold = 2000;
        this->desc = "�ܴ��� ���� ���� �ı����� ���� ���Դϴ�.\n����� �����ϰ� ����� �����ϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    // ������ ����
    void killerdog()
    {
        this->name = "(LV10) ��ɰ�";
        this->mobcode = "S1";
        this->maxhp = 200;
        this->hp = maxhp;
        this->damage = 45;
        this->defence = 10;
        this->speed = 22;
        this->level = 10;
        this->exp = 130;
        this->gold = 800;
        this->desc = "������ ����� ���Ͽ� ��鿩�� ���Դϴ�.\n��ɲ��� �ֿ��ϴ� �������� �ϳ��Դϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void hunter()
    {
        this->name = "(LV10) ��ɲ�";
        this->mobcode = "S2";
        this->maxhp = 300;
        this->hp = maxhp;
        this->damage = 40;
        this->defence = 15;
        this->speed = 15;
        this->level = 10;
        this->exp = 150;
        this->gold = 740;
        this->desc = "�ΰ� ����� �ַ� �ϴ� ��ɲ��Դϴ�.\n���������� ������ ���ϰ� �ִ� �� �մϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void shadower()
    {
        this->name = "(LV11) �ϻ���";
        this->mobcode = "S3";
        this->maxhp = 120;
        this->hp = maxhp;
        this->damage = 500;
        this->defence = 1;
        this->speed = 30;
        this->level = 11;
        this->exp = 50;
        this->gold = 1300;
        this->desc = "�ſ� ���� �ӵ��� ���� ���Դϴ�. �������� �ſ� ���մϴ�.\n�ָӴϿ� ���� ���� ���� �� �����ϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void badknight()
    {
        this->name = "(LV13) Ÿ���� ���";
        this->mobcode = "S4";
        this->maxhp = 600;
        this->hp = maxhp;
        this->damage = 50;
        this->defence = 15;
        this->speed = 20;
        this->level = 13;
        this->exp = 340;
        this->gold = 1750;
        this->desc = "�� ������ �������� �� �� ���� ���� ���� �ֺ��� ���ε��ϴ�.\n";
        this->desc += "�� ���� �޾������� �ұ��ϰ�, Ÿ��ȭ�� �Ͽ��� �� �ɷ�ġ�� �״���ΰ� �����ϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void nohead()
    {
        this->name = "[BOSS](LV22) �����";
        this->mobcode = "SB";
        this->maxhp = 22222;
        this->hp = maxhp;
        this->damage = 222;
        this->defence = 1;
        this->speed = 40;
        this->level = 22;
        this->exp = 7500;
        this->gold = 33000;
        this->desc = "����� ��ȥ�� �� ������� �״� �� ������ �����ڷ�, ������ �������� ���ϰ� �ֽ��ϴ�.\n";
        this->desc += "�Ӹ��� �������� �ʾ� �޼Ҹ� �븮�� �ſ� ���� ������ �ſ� ���� ���Դϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }

    // ���ֹ��� ��
    void zombie()
    {
        this->name = "(LV17) ����";
        this->mobcode = "G1";
        this->maxhp = 1000;
        this->hp = maxhp;
        this->damage = 80;
        this->defence = 30;
        this->speed = 40;
        this->level = 17;
        this->exp = 680;
        this->gold = 2500;
        this->desc = "�Ϲ����� �����Դϴ�. ��������, ������ ������ ���� �ʽ��ϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void skeleton()
    {
        this->name = "(LV18) ���̷���";
        this->mobcode = "G2";
        this->maxhp = 777;
        this->hp = maxhp;
        this->damage = 150;
        this->defence = 20;
        this->speed = 50;
        this->level = 18;
        this->exp = 980;
        this->gold = 2800;
        this->desc = "���� �̷���� ���̷��� �Դϴ�.\n�� ���Ӱ��� �ٸ��� �������� �����մϴ�.\n";
        this->desc += "��ɰ��� �� ���͸� �����ϴ� �� �����ϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void tankzombie()
    {
        this->name = "(LV18) ��ũ ����";
        this->mobcode = "G3";
        this->maxhp = 1000;
        this->hp = maxhp;
        this->damage = 100;
        this->defence = 200;
        this->speed = 1;
        this->level = 18;
        this->exp = 1100;
        this->gold = 2500;
        this->desc = "�ܴ��� ������ ���� ������ ��ȭ���Դϴ�. ������ �ſ� �����ϴ�";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void darkknight()
    {
        this->name = "(LV20) ĥ���� ���";
        this->mobcode = "G4";
        this->maxhp = 1500;
        this->hp = maxhp;
        this->damage = 130;
        this->defence = 50;
        this->speed = 35;
        this->level = 20;
        this->exp = 1250;
        this->gold = 3830;
        this->desc = "���ǿ� ������ ����� �׿��Լ� �������ϴ�.\n���� ��Ÿ��� ���̷��� ������ ���Դϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }
    void demonite()
    {
        this->name = "[BOSS](LV35) ���� ���� ������Ʈ";
        this->mobcode = "GB";
        this->maxhp = 5000;
        this->hp = maxhp;
        this->damage = 800;
        this->defence = 999999;
        this->speed = 20;
        this->level = 35;
        this->exp = 25000;
        this->gold = 75000;
        this->desc = "���� ���α��� �Ǹ��� '������Ʈ' �Դϴ�.\n";
        this->desc += "�Ϲ����� ������δ� ������ ������ �ʾ� Ư���� ������� óġ�ؾ� �� �� �����ϴ�.";
        Log[t] = this->name + "(��)�� ������. ������ �ұ�?"; t++;
    }

    void Mobdeath(Player* p)
    {
        killtrigger = true;
        this->hp = 0;
        bool penaltyflag = false;

        Log[t] = this->name + "(��)�� óġ�ߴ�!"; t++;

        // ���� ���̰� ���ϰ� ���� ���, ���� ���̿� ���� �г�Ƽ�� �ΰ��Ѵ�.
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
        // ���� ã�� ���ؼ� 'mobcode = {Codename}' ���� ã������.

        int getnum = rand() % 1000;
        int amount;

        if (mobcode == "F3" && !penaltyflag)
        {
            if (getnum < 100)
            {
                amount = rand() % 2 + 1;
                Log[t] = this->name + " �� �׿� " + get<0>(itemlist[1]) + "x" + to_string(amount) + " �� ȹ���Ͽ����ϴ�!"; t++;
                p->playeritemlist[1].first += amount;
            }
        }
        if (mobcode == "C2" && !penaltyflag)
        {
            if (getnum < 200)
            {
                amount = rand() % 3 + 1;
                Log[t] = this->name + " �� �׿� " + get<0>(itemlist[1]) + "x" + to_string(amount) + " �� ȹ���Ͽ����ϴ�!"; t++;
                p->playeritemlist[1].first += amount;
            }
        }
        if (mobcode == "C3" && !penaltyflag)
        {
            if (getnum < 100)
            {
                amount = 1;
                Log[t] = this->name + " �� �׿� " + get<0>(itemlist[2]) + "x" + to_string(amount) + " �� ȹ���Ͽ����ϴ�!"; t++;
                p->playeritemlist[2].first += amount;
            }
            else if (getnum < 300)
            {
                amount = rand() % 2 + 1;
                Log[t] = this->name + " �� �׿� " + get<0>(itemlist[1]) + "x" + to_string(amount) + " �� ȹ���Ͽ����ϴ�!"; t++;
                p->playeritemlist[1].first += amount;
            }
        }
        if (mobcode == "S2" && !penaltyflag)
        {
            if (getnum < 150)
            {
                amount = rand() % 2 + 1;
                Log[t] = this->name + " �� �׿� " + get<0>(itemlist[2]) + "x" + to_string(amount) + " �� ȹ���Ͽ����ϴ�!"; t++;
                p->playeritemlist[2].first += amount;
            }
        }
        if (mobcode == "G2" || mobcode == "G3" || mobcode == "G4") return;
        if (mobcode == "G1" && !penaltyflag)
        {
            if (getnum < 5000)
            {
                amount = 1;
                Log[t] = this->name + " �� �׿�" + get<0>(itemlist[3]) + "x" + to_string(amount) + " �� ȹ���Ͽ����ϴ�!"; t++;
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
                Log[t] = this->name + " �� �׿� " + get<0>(itemlist[1]) + "x" + to_string(amount) + " �� �����Ͽ����ϴ�!"; t++;
                p->playeritemlist[1].first += amount;

                amount = rand() % 3 + 1;
                Log[t] = this->name + " �� �׿� " + get<0>(itemlist[2]) + "x" + to_string(amount) + " �� ȹ���Ͽ����ϴ�!"; t++;
                p->playeritemlist[2].first += amount;
            }
        }
    }

    void mobdescription(bool showstatus = false)
    {
        system("cls");
        cout << "���� ����\n\n";
        cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n\n";

        cout << "���� �̸� : " << this->name << "\n\n";

        cout << this->desc << "\n\n";

        if (showstatus == false) cout << "�� ���� ����(SŰ ������)\n\n";
        else cout << "�� ���� �׸� ����(SŰ ������)\n\n";

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
                if (key == 83 || key == 115) showstatus = !showstatus; // sŰ

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
            Log[t] = get<0>(itemlist[num]) + "(��)�� �����ϴ�."; t++;
            return false;
        }
        else
        {
            if (num == 1)
            {
                int healing = 50;
                int trueheal = min(p->maxhp, p->hp + healing) - p->hp;
                Log[t] = get<0>(itemlist[1]) + "�� ����Ͽ� ü���� " + to_string(trueheal) + "ȸ���߽��ϴ�."; t++;

                p->hp += trueheal;
                p->playeritemlist[1].first--;
            }
            if (num == 2)
            {
                int healing = 300;
                int trueheal = min(p->maxhp, p->hp + healing) - p->hp;
                Log[t] = get<0>(itemlist[2]) + "�� ����Ͽ� ü���� " + to_string(trueheal) + "ȸ���߽��ϴ�."; t++;

                p->hp += trueheal;
                p->playeritemlist[2].first--;
            }
            if (num == 3)
            {
                int healing = 1000;
                int trueheal = min(p->maxhp, p->hp + healing) - p->hp;
                Log[t] = get<0>(itemlist[3]) + "�� ����Ͽ� ü���� " + to_string(trueheal) + "ȸ���߽��ϴ�."; t++;

                p->hp += trueheal;
                p->playeritemlist[3].first--;
            }

            return true;
        }
    }
    void itemdescription(Player* p, int num)
    {
        system("cls");
        cout << "������ ����\n\n";
        cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n\n";

        cout << "������ �̸� : " << get<0>(itemlist[num]) << " ���� ���� : " << get<0>(p->playeritemlist[num]) << "\n\n";
        if (num == 1)
        {
            cout << "���� �����Դϴ�. ���� ü���� 50 ȸ���մϴ�.";
        }
        if (num == 2)
        {
            cout << "�Ϲ� ũ���� �����Դϴ�. ���� ü���� 300 ȸ���մϴ�.";
        }
        if (num == 3)
        {
            cout << "ū ũ���� �����Դϴ�. ���� ü���� 1000 ȸ���մϴ�.";
        }
        if (num == 4)
        {
            cout << "�۽�Ʈ���带 ���� �ִ� ��ų���Դϴ�. ���� ��� �۽�Ʈ���带 �����մϴ�.\n";
            cout << "(�Ǹ� �Ұ�, �ִ� ���� ����: 1��)";
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