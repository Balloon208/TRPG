#include "Entity.h"

bool Login(Player* p); // ù �α��� �� ����Ǵ� �Լ�
void Save(Player* p); // ���� ���� ��Ȳ�� �����ϴ� �Լ�
void Load(Player* p); // ������ ������ ������ �ҷ����� �Լ�
void showlog(); // �α׸� �����ִ� �Լ�
void showplayerstatus(Player* p, string slot1, string slot2, string slot3, string slot4); // �÷��̾� �������ͽ�
void showmobstatus(mob* m);
void fulllog(int current, int finish); // Ǯ�α� �����ִ� �Լ�
void showfulllog(); // Ǯ�α� �������̽�
void home(Player* p); // ����
void homemenu(Player* p); // ���� �������̽�
void homeselectmenu(Player* p); // �������� ����
void movemenu(Player* p); // �̵��� �� ����
void skillset(Player* p); // ��ų ���� �� ����
void shop(Player* p); // ����
void pattack(Player* p, mob* m, bool skillmode); // Player ����
void mattack(Player* p, mob* m); // Mob ����
void attack(Player* p, mob* m); // ���� ���� �Լ�
void skillattack(Player* p, mob* m, int skillnum); // ��ų ����(�׻� ����)
void readymenu(Player* p); // Ž�迡���� ����
void summonmob(Player* p); // �� ��ȯ �� Ȯ��
void fightmenu(mob* m, Player* p, bool skillmode); // ���� �������̽�
void fight(Player* p); // Ž�� �������̽�
void fightselectmenu(mob* m, Player* p); // ���� �� ����
bool selectitem(Player* p); // ������ ����
void showitem(Player* p); // ������ �����ֱ�
void Forge(Player* p, int protect, int chance, string mode, int upmoney); // ��ȭ�� ����Ǵ� �Լ�
void weaponforge(Player* p, bool visit); // ���Ⱝȭ�� (Ȯ�� �� �� ����)
void armorforge(Player* p, bool visit); // ����ȭ�� (Ȯ�� �� �� ����)
void death(Player* p);

void death(Player* p) {
    p->gold = 0;
    p->heal();
    Save(p);
    system("cls");
    cout << p->name << "���� ����Ͽ� ��带 ��� �Ҿ����ϴ�." << endl;
    cout << "������ ��ȯ�Ͻðڽ��ϱ�? ( ��ȯ�Ϸ��� �����̽� �� Ű�� �������� )";
    while (1)
    {
        if (kbhit())
        {
            int key = getch();
            if (key == 32) break; //esc
        }
    }
    home(p);
}

bool Login(Player* p)
{
    int n;
    string name;

    FILE* fp;

    fp = fopen("./Save/playerinfom.txt", "r");
    fscanf(fp, "register:%d", &n);
    fclose(fp);

    if (n != 2)
    {
        cout << "�ű� ������ ���Ͽ� �̸��� �Է��ϼ��� : ";
        cin >> name;

        char wname[200];
        strcpy(wname, name.c_str());

        fp = fopen("./Save/playerinfom.txt", "w");
        fprintf(fp, "register:%d\n", 2);
        fprintf(fp, "%s\n", wname);
        fprintf(fp, "maxhp:%d\n", 100);
        fprintf(fp, "hp:%d\n", 100);
        fprintf(fp, "maxmp:%d\n", 50);
        fprintf(fp, "mp:%d\n", 50);
        fprintf(fp, "damage:%d\n", 10);
        fprintf(fp, "defence:%d\n", 5);
        fprintf(fp, "speed:%d\n", 5);
        fprintf(fp, "gold:%d\n", 0);
        fprintf(fp, "level:%d\n", 1);
        fprintf(fp, "exp:%d\n", 0);
        fprintf(fp, "LVUPexp:%d\n", 50);
        fprintf(fp, "weaponlevel:%d\n", 0);
        fprintf(fp, "armorlevel:%d\n", 0);
        fclose(fp);

        fp = fopen("./Save/playerskills.txt", "w");

        // ��ų ���� �ɼ� (skill setting), name, Mana, Learned(1 = ��ų ���, 2 = ���� ��)
        fprintf(fp, "��� 0 1\n");
        fprintf(fp, "ũ�ν��� 30 0\n");
        fprintf(fp, "���� 60 0\n");
        fprintf(fp, "�޼���� 20 0\n");
        fprintf(fp, "�м� 50 0\n");
        fprintf(fp, "�������ϰ� 100 0\n");
        fprintf(fp, "�۽�Ʈ���� 200 0\n");
        fprintf(fp, "0, 0, 0, 0");

        fclose(fp);

        fp = fopen("./Save/itemDB.txt", "w");

        fprintf(fp, "�������� -1 500 300\n");
        fprintf(fp, "�������� -1 2000 1500\n");
        fprintf(fp, "�������� -1 5000 3000\n");
        fprintf(fp, "[Skillbook]�۽�Ʈ���� 7 30000 0\n");

        fclose(fp);

        fp = fopen("./Save/playeritem.txt", "w");

        fprintf(fp, "�������� 0 -1\n");
        fprintf(fp, "�������� 0 -1\n");
        fprintf(fp, "�������� 0 -1\n");
        fprintf(fp, "[Skillbook]�۽�Ʈ���� 0 7\n");

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

        p->skill[1] = 1;
        p->skill[2] = 0;
        p->skill[3] = 0;
        p->skill[4] = 0;
        return false;
    }
    else
    {
        for (int i = 1; i <= 2; i++)
        {
            if (i == point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
            else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            if (i == 1) cout << "�̾��ϱ�";
            if (i == 2) cout << "�����ϱ�";
            cout << "   ";
        }
        // �ΰ� �� ��ư ���� (�̾��ϱ�) / (�����ϱ�)
        bool command = false;
        int key;
        point = 1;
        while (!command)
        {
            if (kbhit())
            {
                key = getch();
                {
                    if (key == 224) // ����Ű
                    {
                        key = getch();
                        if (key == 75 && point > 1) point--; // ����
                        if (key == 77 && point < 2) point++; // ������
                    }
                    if (key == 13) // enterŰ
                    {
                        if (point == 1)
                        {
                            command = true;
                            return false;
                        }
                        if (point == 2)
                        {
                            fp = fopen("./Save/playerinfom.txt", "w");
                            fprintf(fp, "register:%d\n", 0);
                            fclose(fp);
                            system("cls");
                            cout << "�ʱ�ȭ�� �Ϸ�Ǿ����ϴ�. �ٽ� ������ �ּ���.";
                            return true;
                        }
                    }
                    system("cls");
                }

                for (int i = 1; i <= 4; i++)
                {
                    if (i == point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                    else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    if (i == 1) cout << "�̾��ϱ�";
                    if (i == 2) cout << "�����ϱ�";
                    cout << "   ";
                }
            }
        }

    }
}

void Save(Player* p)
{
    char wname[200];
    strcpy(wname, p->name.c_str());

    FILE* fp;
    fp = fopen("./Save/playerinfom.txt", "w");
    fprintf(fp, "register:%d\n", 2);
    fprintf(fp, "%s\n", wname);
    fprintf(fp, "maxhp:%d\n", p->maxhp);
    fprintf(fp, "hp:%d\n", p->hp);
    fprintf(fp, "maxmp:%d\n", p->maxmp);
    fprintf(fp, "mp:%d\n", p->mp);
    fprintf(fp, "damage:%d\n", p->damage);
    fprintf(fp, "defence:%d\n", p->defence);
    fprintf(fp, "speed:%d\n", p->speed);
    fprintf(fp, "gold:%d\n", p->gold);
    fprintf(fp, "level:%d\n", p->level);
    fprintf(fp, "exp:%d\n", p->exp);
    fprintf(fp, "LVUPexp:%d\n", p->LVUPexp);
    fprintf(fp, "weaponlevel:%d\n", p->weaponlevel);
    fprintf(fp, "armorlevel:%d\n", p->armorlevel);
    fclose(fp);

    fp = fopen("./Save/playerskills.txt", "w");
    for (int i = 1; i <= totalskill; i++)
    {
        fprintf(fp, "%s %d %d\n", get<0>(skills[i]).c_str(), get<1>(skills[i]), get<2>(skills[i]));
    }
    fprintf(fp, "%d %d %d %d", p->skill[1], p->skill[2], p->skill[3], p->skill[4]);
    fclose(fp);

    fp = fopen("./Save/playeritem.txt", "w");

    char itemnames[10001];
    for (int i = 1; i <= totalitem + totalskillbooks; i++)
    {
        strcpy(itemnames, get<0>(itemlist[i]).c_str());
        fprintf(fp, "%s %d %d\n", itemnames, p->playeritemlist[i].first, p->playeritemlist[i].second);
    }
    fclose(fp);

    fp = fopen("./Save/itemDB.txt", "w");

    char DBitemnames[10001];
    for (int i = 1; i <= totalitem + totalskillbooks; i++)
    {
        strcpy(DBitemnames, get<0>(itemlist[i]).c_str());
        fprintf(fp, "%s %d %d %d\n", DBitemnames, get<1>(itemlist[i]), get<2>(itemlist[i]), get<3>(itemlist[i]));
    }
    fclose(fp);
}

void Load(Player* p)
{
    int trash;
    char wname[200];

    FILE* fp;
    fp = fopen("./Save/playerinfom.txt", "r");
    fscanf(fp, "register:%d\n", &trash);
    fscanf(fp, "%s\n", wname);
    p->name = wname;
    fscanf(fp, "maxhp:%d\n", &p->maxhp);
    fscanf(fp, "hp:%d\n", &p->hp);
    fscanf(fp, "maxmp:%d\n", &p->maxmp);
    fscanf(fp, "mp:%d\n", &p->mp);
    fscanf(fp, "damage:%d\n", &p->damage);
    fscanf(fp, "defence:%d\n", &p->defence);
    fscanf(fp, "speed:%d\n", &p->speed);
    fscanf(fp, "gold:%d\n", &p->gold);
    fscanf(fp, "level:%d\n", &p->level);
    fscanf(fp, "exp:%d\n", &p->exp);
    fscanf(fp, "LVUPexp:%d\n", &p->LVUPexp);
    fscanf(fp, "weaponlevel:%d\n", &p->weaponlevel);
    fscanf(fp, "armorlevel:%d\n", &p->armorlevel);
    fclose(fp);

    fp = fopen("./Save/playerskills.txt", "r");
    for (int i = 1; i <= totalskill; i++)
    {
        char skillnames[10000];
        fscanf(fp, "%s %d %d\n", skillnames, &get<1>(skills[i]), &get<2>(skills[i]));
        get<0>(skills[i]) = skillnames;
    }
    fscanf(fp, "%d %d %d %d", &p->skill[1], &p->skill[2], &p->skill[3], &p->skill[4]);
    fclose(fp);

    fp = fopen("./Save/itemDB.txt", "r");
    for (int i = 1; i <= totalitem + totalskillbooks; i++)
    {
        char itemnames[10000];
        fscanf(fp, "%s %d %d %d\n", itemnames, &get<1>(itemlist[i]), &get<2>(itemlist[i]), &get<3>(itemlist[i]));
        get<0>(itemlist[i]) = itemnames;
    }
    fclose(fp);

    fp = fopen("./Save/playeritem.txt", "r");
    for (int i = 1; i <= totalitem + totalskillbooks; i++)
    {
        char trash[10000];
        fscanf(fp, "%s %d %d\n", trash, &p->playeritemlist[i].first, &p->playeritemlist[i].second);
    }
    fclose(fp);
}

void showlog()
{
    for (int i = t - 5; i < t; i++)
    {
        if (i < 0) cout << '\n';
        else cout << Log[i] << '\n';
    }
    cout << "�ѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤѤ�\n\n";
}

void showplayerstatus(Player* p, string slot1, string slot2, string slot3, string slot4)
{
    playerhppercent = (double)p->hp / p->maxhp * 100;
    playermppercent = (double)p->mp / p->maxmp * 100;
    playerexppercent = (double)p->exp / p->LVUPexp * 100;

    // �� ���Կ� �ش��ϴ� �̸��� �־��ֽø� �˴ϴ�. ex) showplayerstatus(p, "1", "2", "3", "4");
    for (int i = 0; i < 10; i++) //playerhpbar
    {
        if (i * 10 < playerhppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "��";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << '\n';
    for (int i = 0; i < 10; i++) //playermpbar
    {
        if (i * 10 < playermppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "��";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << '\n';
    cout << p->name << '\n';
    cout << "HP : " << p->hp << " / " << p->maxhp;
    cout << "\n\n";

    for (int i = 1; i <= 4; i++)
    {
        if (i == point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        if (i == 1) cout << slot1;
        if (i == 2) cout << slot2;
        if (i == 3) cout << slot3;
        if (i == 4) cout << slot4;
        cout << "   ";
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << "\n\n";
    cout << "���� : " << p->level << " (" << p->exp << ")" << "   ";
    cout << "��� : " << p->gold << '\n';

    cout << "[";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // levelbar
    for (int i = 1; i <= 25; i++)
    {
        if (playerexppercent < i * 4)
        {
            if (playerexppercent - ((i - 1) * 4) >= 2) // 2%�� ��쿡 ���ϰ�
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

void showmobstatus(mob* m)
{
    mobhppercent = (double)m->hp / m->maxhp * 100;
    for (int i = 0; i < 10; i++) //mobhpbar
    {
        if (i * 10 < mobhppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "��";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << '\n';
    cout << "(��)" << m->name << '\n';
    cout << "HP : " << m->hp << " / " << m->maxhp << '\n';
    cout << '\n';
}

void fulllog(int current, int finish)
{
    system("cls");
    cout << "ESC �� ���� ���ư�����. (����Ű �� �Ʒ��� �̵� ����)" << "\n\n";
    for (int i = current; i <= finish; i++)
    {
        cout << "[" << i << "]" << " " << Log[i] << '\n';
    }
}

void showfulllog()
{
    int lognum = 20;
    int current = (t - lognum <= 0) ? 0 : t - lognum;
    int finish = (current <= lognum) ? t - 1 : current + lognum - 1;
    int key;

    fulllog(current, finish);
    while (1)
    {
        if (kbhit())
        {
            key = getch();
            if (key == 224) // ����Ű
            {
                key = getch();
                if (key == 72) // ����
                {
                    if (current - lognum <= 0) current = 0;
                    else current -= lognum;
                }
                if (key == 80) // �Ʒ���
                {
                    if (finish + lognum >= t - 1) current = t - lognum - 1 > 0 ? t - lognum - 1 : 0;
                    else current += lognum;
                }
            }
            if (key == 27) //esc
            {
                break;
            }
            finish = (t <= lognum) ? t - 1 : current + 20;
            fulllog(current, finish);
        }
    }
}

void home(Player* p)
{
    Save(p);
    system("cls");
    homemenu(p);
    homeselectmenu(p);
}

void homemenu(Player* p)
{
    showlog();
    showplayerstatus(p, "�̵�", "�޽�", "��ų����", "����");
}

void homeselectmenu(Player* p)
{
    bool command = false;
    int key;
    point = 1;
    while (!command)
    {
        if (kbhit())
        {
            key = getch();
            if (key == 224) // ����Ű
            {
                key = getch();
                if (key == 75 && point > 1) point--; // ����
                if (key == 77 && point < 4) point++; // ������
            }
            if (key == 13) // enterŰ
            {
                if (point == 1)
                {
                    command = true;
                    point = 3;
                    movemenu(p);
                }
                if (point == 2)
                {
                    p->heal();
                    Save(p);
                }
                if (point == 3)
                {
                    command = true;
                    point = 1;
                    skillset(p);
                }
                if (point == 4)
                {
                    command = true;
                    point = 1;
                    shop(p);
                }
            }
            if (key == 84 || key == 116) showfulllog(); // tŰ
            system("cls");
            homemenu(p);
        }
    }
    command = false;
}

void movemenu(Player* p)
{
    bool command = false;

    system("cls");
    showlog();

    cout << "�̵��� ���� ������ �ּ���.\n\n";

    for (int i = point - 1; i <= point + 1; i++)
    {
        if (i == point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        cout << worldmap[i] << '\n';
    }

    while (!command)
    {
        int key;
        if (kbhit())
        {
            key = getch();
            {
                if (key == 224) // ����Ű
                {
                    key = getch();
                    if (key == 72 && point > 1)// ����
                    {
                        point--;
                    }
                    if (key == 80 && point < stage - 1)// �Ʒ���
                    {
                        point++;
                    }
                }
                if (key == 13) // enterŰ
                {
                    command = true;
                    where = point;
                    point = 1;
                    if (where == 1)
                    {
                        weaponforge(p, false);
                        break;
                    }
                    if (where == 2)
                    {
                        armorforge(p, false);
                        break;
                    }
                    Log[t] = "����� " + worldmap[where] + "(��)�� ������ ������."; t++;
                    fight(p);
                    readymenu(p);
                }
                if (key == 27) //esc
                {
                    point = 1;
                    break;
                }
                if (key == 84 || key == 116) showfulllog(); // tŰ
            }
            movemenu(p);
        }
    }
    command = false;
    home(p);
}

void skillset(Player* p)
{
    system("cls");
    bool command = false;

    showlog();

    for (int i = 1; i <= 4; i++)
    {
        p->skill[i] = 0;
    }
    usingskill = 1;

    for (int i = 1; i <= totalskill; i++)
    {
        if (i == point) cout << ">";

        if (get<2>(skills[i]) == 1)
        {
            cout << "    " << get<0>(skills[i]) << "(" << get<1>(skills[i]) << ")" << '\n';
        }
        else if (get<2>(skills[i]) == 2)
        {
            p->skill[usingskill] = i;
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

    while (!command)
    {
        int key;
        if (kbhit())
        {
            key = getch();
            {
                if (key == 224) // ����Ű
                {
                    key = getch();
                    {
                        if (key == 72) // ����
                        {
                            if (point > 1)
                            {
                                point--;
                            }
                        }
                        if (key == 80) // �Ʒ���
                        {
                            if (point < totalskill)
                            {
                                point++;
                            }
                        }
                    }
                }
                if (key == 13) // enterŰ
                {
                    command = true;
                    if (usingskill <= 4 || get<2>(skills[point]) == 2) // ��ų �ִ밹�� ���� ��ų�, ������ �ϴ� ���.
                    {
                        if (get<2>(skills[point]) == 1) // ������ ���
                        {
                            Log[t] = get<0>(skills[point]) + " ��ų�� �����Ͽ����ϴ�."; t++;
                            get<2>(skills[point]) = 2;
                        }
                        else if (get<2>(skills[point]) == 2) // ������ ���
                        {
                            Log[t] = get<0>(skills[point]) + " ��ų�� �����Ͽ����ϴ�."; t++;
                            get<2>(skills[point]) = 1;
                        }
                    }
                    else if (get<2>(skills[point]) == 1) // �ִ밹���̸�, ������ �ϴ� ���
                    {
                        Log[t] = "��ų ������ ���� á���ϴ�."; t++;
                    }
                }
                if (key == 47 || key == 63) // / or ?
                {
                    p->skilldescription(point);
                }
                if (key == 27) //esc
                {
                    point = 1;
                    break;
                }
                if (key == 84 || key == 116) showfulllog(); // tŰ
            }
            skillset(p);
        }
    }
    command = false;
    home(p);
}

void shop(Player* p)
{
    item item;
    system("cls");
    bool command = false;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    showlog();

    cout << "�����ϱ� ���ؼ� B, �ȱ� ���ؼ� S�� �����ּ���.\n\n";
    cout << "���� ��� : " << p->gold << "\n\n";
    for (int i = 1; i <= totalitem + totalskillbooks; i++)
    {
        if (i == point)
        {
            if (get<1>(itemlist[i]) == -100) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
            else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
        }
        else
        {
            if (get<1>(itemlist[i]) == -100) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
            else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
        }

        cout << get<0>(itemlist[i]) << " : BUY " << get<2>(itemlist[i]) << " / SELL " << get<3>(itemlist[i]) << " / ���� ���� : (" << p->playeritemlist[i].first << ")" << '\n';
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    while (!command)
    {
        int key;
        if (kbhit())
        {
            key = getch();

            if (key == 224) // ����Ű
            {
                key = getch();
                if (key == 72 && point > 1) point--; // ����
                if (key == 80 && point < totalitem + totalskillbooks) point++; // �Ʒ���
            }

            if ((key == 66 || key == 98) && get<1>(itemlist[point]) != -100) // B Ű
            {
                if (p->gold >= get<2>(itemlist[point]))
                {
                    p->gold -= get<2>(itemlist[point]);
                    p->playeritemlist[point].first++;
                    Log[t] = get<0>(itemlist[point]) + "�� �����Ͽ���."; t++;

                    if (get<1>(itemlist[point]) >= 1 && get<1>(itemlist[point]) < 100) // ��ų��
                    {
                        p->LearnSkill(get<1>(itemlist[point]));
                        get<1>(itemlist[point]) = -100;
                    }
                    Save(p);
                }
                else
                {
                    Log[t] = "��尡 �����մϴ�. (" + to_string(p->gold) + "/" + to_string(get<2>(itemlist[point])) + ")"; t++;
                }
            }
            if (key == 83 || key == 115) // S Ű
            {
                if (p->playeritemlist[point].first > 0 && !(p->playeritemlist[point].second >= 1 && p->playeritemlist[point].second < 100))
                {
                    p->gold += get<3>(itemlist[point]);
                    p->playeritemlist[point].first--;
                    Log[t] = get<0>(itemlist[point]) + "�� �Ǹ��Ͽ���.";
                    t++;
                    Save(p);
                }
            }
            if (key == 47 || key == 63)
            {
                item.itemdescription(p, point);
            }
            if (key == 27) //esc
            {
                point = 1;
                break;
            }
            if (key == 84 || key == 116) showfulllog(); // tŰ
            shop(p);
        }
    }
    command = false;
    home(p);
}

void pattack(Player* p, mob* m)
{
    double multiple = double((p->level - m->level) * 5 + 100) / 100;
    if (multiple > 1.3) multiple = 1.3;
    if (multiple < 0) multiple = 0;
    int damage = round((rand() % p->damage + p->damage) / (1 + (m->defence * 0.1)) * multiple);
    Log[t] = m->name + "���� " + to_string(damage) + " �������� �������ϴ�!";
    m->hp -= damage;
    t++;
    if (m->hp <= 0)
    {
        m->Mobdeath(p);
        return;
    }
}

void mattack(Player* p, mob* m)
{
    double multiple = double((m->level - p->level) * 5 + 100) / 100;
    if (multiple > 1.3) multiple = 1.3;
    if (multiple < 0) multiple = 0;
    int damage = round((rand() % m->damage + m->damage) / (1 + (p->defence * 0.1)) * multiple);
    Log[t] = m->name + "��(��) �����Ͽ� " + to_string(damage) + " �������� �Ծ����ϴ�!";
    p->hp -= damage;
    t++;
    if (p->hp <= 0)
    {
        death(p);
    }
}

void attack(Player* p, mob* m, bool skillmode)
{
    if (p->speed >= m->speed)
    {
        pattack(p, m);
        if (killtrigger == true) return;
        fightmenu(m, p, skillmode);
        Delay(100);
        mattack(p, m);
    }
    else
    {
        mattack(p, m);
        fightmenu(m, p, skillmode);
        Delay(100);
        pattack(p, m);
    }
    int mphealing = min(p->maxmp, p->mp + (p->maxmp / 20)) - p->mp; // mp 5% ȸ��
    p->mp += mphealing;
}

void skillattack(Player* p, mob* m, int skillnum)
{
    int damage;
    double multiple = double((p->level - m->level) * 5 + 100) / 100;
    if (multiple > 1.3) multiple = 1.3;

    if (skillnum == 1) // ���
    {
        int success = rand() % 4;
        int temp = p->hp;

        if (success > 0)
        {
            Log[t] = get<0>(skills[skillnum]) + "�� ����Ͽ� ������ ���� ���ط��� �Ϻθ� ������ ��ȯ�մϴ�.";
            p->defence *= 2;
            t++;
            fightmenu(m, p, true);
            Delay(100);
            mattack(p, m);
            p->defence /= 2;

            int mphealing = (temp - p->hp) / 2; // ���� hp�� 50%��ŭ mp ȸ��
            p->mp = min(p->maxmp, p->mp + mphealing);

            mphealing = min(p->maxmp, p->mp + (p->maxmp / 20)) - p->mp; // mp 5% ȸ��
            p->mp += mphealing;
        }
        else
        {
            Log[t] = get<0>(skills[skillnum]) + "�� ����Ͽ����� ���� ���� �����Ͽ���!";
            t++;
            p->defence /= 2;
            fightmenu(m, p, true);
            Delay(100);
            mattack(p, m);
            p->defence *= 2;
            int mphealing = min(p->maxmp, p->mp + (p->maxmp / 20)) - p->mp; // mp 5% ȸ��
            p->mp += mphealing;
        }

    }
    if (skillnum == 2) // ũ�ν���
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            for (int i = 0; i < 2; i++)
            {
                damage = (rand() % (p->damage * 2) + p->damage) / (1 + (m->defence * 0.1)) * multiple;
                Log[t] = m->name + "���� " + get<0>(skills[skillnum]) + "�� ����Ͽ� " + to_string(damage) + " �������� �������ϴ�!";
                t++;
                m->hp -= damage;
                if (m->hp <= 0)
                {
                    m->Mobdeath(p);
                    return;
                }
            }
            fightmenu(m, p, true);
            Delay(100);
            mattack(p, m);
        }
        else
        {
            Log[t] = "������ �����մϴ�. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if (skillnum == 3) // ����
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            int healing = min(p->maxhp, p->hp + (p->maxhp / 8)) - p->hp; // hp �� 12.5% ȸ��
            p->hp += healing;
            Log[t] = get<0>(skills[skillnum]) + "�� ����Ͽ� " + to_string(healing) + " ü���� ȸ���Ͽ����ϴ�!";
            t++;
        }
        else
        {
            Log[t] = "������ �����մϴ�. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if (skillnum == 4) // �޼����
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            damage = (rand() % p->damage) + p->damage * multiple;
            Log[t] = m->name + "���� " + get<0>(skills[skillnum]) + "�� ����Ͽ� " + to_string(damage) + " �������� �������ϴ�!";
            t++;
            m->hp -= damage;
            if (m->hp <= 0)
            {
                m->Mobdeath(p);
                return;
            }
            fightmenu(m, p, true);
            Delay(100);
            mattack(p, m);
        }
        else
        {
            Log[t] = "������ �����մϴ�. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if (skillnum == 5) // �м�
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            for (int i = 0; i < 3; i++)
            {
                damage = (rand() % (p->damage * 5)) / (1 + (m->defence * 0.1)) * multiple;
                Log[t] = m->name + "���� " + get<0>(skills[skillnum]) + "�� ����Ͽ� " + to_string(damage) + " �������� �������ϴ�!";
                t++;
                m->hp -= damage;
                if (m->hp <= 0)
                {
                    m->Mobdeath(p);
                    return;
                }
            }
            fightmenu(m, p, true);
            Delay(100);
            mattack(p, m);
        }
        else
        {
            Log[t] = "������ �����մϴ�. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if (skillnum == 6) // �������ϰ�
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            damage = (rand() % (p->damage * 4) + p->damage * 5) / (1 + (m->defence * 0.1)) * (multiple * 3);
            Log[t] = m->name + "���� " + get<0>(skills[skillnum]) + "�� ����Ͽ� " + to_string(damage) + " �������� �������ϴ�!";
            t++;
            m->hp -= damage;
            if (m->hp <= 0)
            {
                m->Mobdeath(p);
                return;
            }
            fightmenu(m, p, true);
            Delay(100);
            mattack(p, m);
        }
        else
        {
            Log[t] = "������ �����մϴ�. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if (skillnum == 7) // �۽�Ʈ����
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            damage = m->hp / 8; // ���� ü���� 12.5%
            Log[t] = m->name + "���� " + get<0>(skills[skillnum]) + "�� ����Ͽ� " + to_string(damage) + " �������� �������ϴ�!";
            t++;
            m->hp -= damage;
            if (m->hp <= 0)
            {
                m->Mobdeath(p);
                return;
            }
            fightmenu(m, p, true);
            Delay(100);
            mattack(p, m);
        }
        else
        {
            Log[t] = "������ �����մϴ�. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
}

void fight(Player* p)
{
    Save(p);
    system("cls");
    mob m;

    showlog();
    showplayerstatus(p, "Ž���Ѵ�", "���ư���", "", "");
}

void readymenu(Player* p)
{
    bool command = false;
    int key;
    point = 1;
    while (!command)
    {
        if (kbhit())
        {
            key = getch();
            {
                if (key == 224) // ����Ű
                {
                    key = getch();
                    if (key == 75 && point > 1) point--; // ����
                    if (key == 77 && point < 2) point++; // ������
                }
                if (key == 13) // enterŰ
                {
                    if (point == 1)
                    {
                        command = true;
                        summonmob(p);
                    }
                    if (point == 2)
                    {
                        Log[t] = p->name + "(��)�� Ž���� �׸��ΰ� ���ư���."; t++;
                        command = true;
                        point = 1;
                    }
                }
                if (key == 84 || key == 116) showfulllog();
                system("cls");
                fight(p);
            }
        }
    }
    home(p);
}

// ���� ��ȯ Ȯ��
void summonmob(Player* p)
{
    mob m;
    if (where == 3)
    {
        int n = rand() % 100 + 1;
        if (n <= 40) m.MiniSlime();
        else if (n <= 70) m.Snake();
        else if (n <= 98) m.Slime();
        else if (n <= 100) m.Oak();
        fightmenu(&m, p, false);
        fightselectmenu(&m, p);
    }
    if (where == 4)
    {
        int n = rand() % 100 + 1;
        if (n <= 40) m.RockSlime();
        else if (n <= 80) m.Bat();
        else if (n <= 95) m.MiniGolem();
        else if (n <= 100) m.Golem();
        fightmenu(&m, p, false);
        fightselectmenu(&m, p);
    }
    if (where == 5)
    {
        int n = rand() % 100 + 1;
        if (n <= 30) m.killerdog();
        else if (n <= 50) m.hunter();
        else if (n <= 70) m.shadower();
        else if (n <= 97) m.badknight();
        else if (n <= 100) m.nohead();
        fightmenu(&m, p, false);
        fightselectmenu(&m, p);
    }
    if (where == 6)
    {
        int n = rand() % 100 + 1;
        if (n <= 35) m.zombie();
        else if (n <= 70) m.skeleton();
        else if (n <= 90) m.tankzombie();
        else if (n <= 97) m.darkknight();
        else if (n <= 100) m.demonite();
        fightmenu(&m, p, false);
        fightselectmenu(&m, p);
    }
}

void fightmenu(mob* m, Player* p, bool skillmode)
{
    system("cls");

    showlog();

    showmobstatus(m);

    if (skillmode == false) showplayerstatus(p, "����", "��ų", "������", "����");
    else
    {
        string skillarray[5];
        for (int i = 1; i <= 4; i++)
        {
            skillarray[i] = get<0>(skills[p->skill[i]]) + "(" + to_string(get<1>(skills[p->skill[i]])) + ")";
        }
        showplayerstatus(p, skillarray[1], skillarray[2], skillarray[3], skillarray[4]);

    }
}

void fightselectmenu(mob* m, Player* p)
{
    bool skillmode = false;
    int key;
    point = 1;
    while (!killtrigger)
    {
        if (kbhit())
        {
            key = getch();

            if (key == 224) // ����Ű
            {
                key = getch();
                if (key == 75 && point > 1) point--; // ����
                if (key == 77 && point < 4) point++; // ������
            }
            if (key == 13) // enterŰ
            {
                if (skillmode)
                {
                    skillattack(p, m, p->skill[point]);
                    if (killtrigger) point = 1;
                }
                else
                {
                    if (point == 1)
                    {
                        attack(p, m, skillmode);
                        Save(p);
                    }
                    if (point == 2)
                    {
                        skillmode = true;
                        point = 1;
                    }
                    if (point == 3)
                    {
                        bool use = selectitem(p);
                        if (use)
                        {
                            mattack(p, m);
                            int mphealing = min(p->maxmp, p->mp + (p->maxmp / 20)) - p->mp; // mp 5% ȸ��
                            p->mp += mphealing;
                        }
                    }
                    if (point == 4)
                    {
                        Log[t] = "����� " + m->name + "(��)�κ��� �����ƴ�!";
                        t++;
                        point = 1;
                        return;
                    }
                }
            }
            if (key == 47 || key == 63) // / or ?
            {
                if (skillmode)
                {
                    if (p->skill[point] != 0) p->skilldescription(p->skill[point]);
                }
                else m->mobdescription();
            }
            if (key == 27 && skillmode) //esc
            {
                skillmode = !skillmode;
                point = 2;
            }
            if (key == 84 || key == 116) showfulllog(); // tŰ
            system("cls");
            fightmenu(m, p, skillmode);
        }
    }
    killtrigger = false;
    fight(p);
    readymenu(p);
}


void showitem(Player* p, int point)
{
    for (int i = 1; i <= totalitem; i++)
    {
        if (get<1>(itemlist[i]) >= 1) continue;
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

        if (point == i) cout << "> ";
        if (p->playeritemlist[i].first == 0) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);

        cout << get<0>(itemlist[i]) << "(" << p->playeritemlist[i].first << ")\n";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

bool selectitem(Player* p)
{
    item item;
    bool selected = false;
    int key;
    point = 1;

    while (!selected)
    {
        system("cls");
        showlog();
        showitem(p, point);

        while (1)
        {
            if (kbhit())
            {
                key = getch();
                if (key == 224) // ����Ű
                {
                    key = getch();
                    if (key == 72 && point > 1) point--; // ����
                    if (key == 80 && point < totalitem) point++; // �Ʒ���
                }
                if (key == 13) // enterŰ
                {
                    bool used = item.useitem(p, point);
                    selected = true;
                    point = 3;
                    Save(p);
                    return used;
                }
                if (key == 47 || key == 63)
                {
                    item.itemdescription(p,point);
                }
                if (key == 27) //esc
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


void Forge(Player* p, int protect, int chance, string mode, int upmoney) // status ������ ����ȵ�, ���� ���������
{
    if (p->gold < upmoney)
    {
        Log[t] = "��尡 �����մϴ�. (" + to_string(p->gold) + "/" + to_string(upmoney) + ")";
        t++;
        return;
    }
    int k = rand() % 10000 + 1;
    if (mode == "weapon")
    {
        if (p->weaponlevel == 20)
        {
            Log[t] = "�ִ� ��ȭ �����Դϴ�. ��ȭ�� ����մϴ�.";
            t++;
            return;
        }
        p->gold -= upmoney;
        if (chance * 100 >= k) // ����
        {
            Log[t] = "��� ��ȭ�� ���� �Ͽ���! (" + to_string(p->weaponlevel) + " -> " + to_string(p->weaponlevel + 1) + ")";
            t++;
            p->weaponlevel++;
            p->damage += forgeadd[p->weaponlevel];
        }
        else
        {
            int down;
            if (!protect) down = rand() % (p->weaponlevel / 4 <= 0 ? 1 : p->weaponlevel / 4 + 1);
            else down = rand() % (p->weaponlevel / 6 <= 0 ? 1 : p->weaponlevel / 7 + 1);
            Log[t] = "��� ��ȭ�� �����Ͽ���... (" + to_string(p->weaponlevel) + " -> " + to_string(p->weaponlevel - down) + ")";
            t++;
            for (int i = p->weaponlevel; i > p->weaponlevel - down; i--)
            {
                p->damage -= forgeadd[i];
            }
            p->weaponlevel -= down;
        }
    }
    if (mode == "armor")
    {
        if (p->armorlevel == 20)
        {
            Log[t] = "�ִ� ��ȭ �����Դϴ�. ��ȭ�� ����մϴ�.";
            t++;
            return;
        }
        p->gold -= upmoney;
        if (chance * 100 >= k) // ����
        {
            Log[t] = "�� ��ȭ�� ���� �Ͽ���! (" + to_string(p->armorlevel) + " -> " + to_string(p->armorlevel + 1) + ")";
            t++;
            p->armorlevel++;
            p->defence += forgeadd[p->armorlevel];
            p->maxhp += forgeadd[p->armorlevel] * 10;
            p->hp += forgeadd[p->armorlevel] * 10;
        }
        else
        {
            int down;
            if (!protect) down = rand() % (p->armorlevel / 3 <= 0 ? 1 : p->armorlevel / 3 + 1);
            else down = rand() % (p->armorlevel / 6 <= 0 ? 1 : p->armorlevel / 6 + 1);
            Log[t] = "�� ��ȭ�� �����Ͽ���... (" + to_string(p->armorlevel) + " -> " + to_string(p->armorlevel - down) + ")";
            t++;
            for (int i = p->armorlevel; i > p->armorlevel - down; i--)
            {
                p->defence -= forgeadd[i];
                p->maxhp -= forgeadd[p->armorlevel] * 10;
                p->hp -= forgeadd[p->armorlevel] * 10;
            }
            p->armorlevel -= down;
        }
    }
    Save(p);
    if (mode == "weapon") weaponforge(p, true);
    if (mode == "armor") armorforge(p, true);
}

void weaponforge(Player* p, bool visit)
{
    int key;
    int chance;
    system("cls");
    if (!visit)
    {
        Log[t] = "����� ���Ⱝȭ�ҿ� �鷶��.";
        t++;
    }

    showlog();

    // 100 95 90 85 80 70 70 60 60 50 50 50 40 40 40 30 30 20 10 5
    if (p->weaponlevel <= 4) chance = 100 - p->weaponlevel * 5;
    else if (p->weaponlevel <= 6) chance = 70;
    else if (p->weaponlevel <= 8) chance = 60;
    else if (p->weaponlevel <= 11) chance = 50;
    else if (p->weaponlevel <= 14) chance = 40;
    else if (p->weaponlevel <= 16) chance = 30;
    else if (p->weaponlevel == 17) chance = 20;
    else if (p->weaponlevel == 18) chance = 10;
    else chance = 5;
    
    cout << "���� ��ȭ (���� : " << p->weaponlevel << ")" << " Ȯ�� : " << chance << "  ������:" << p->damage << "\n\n";

    cout << "��ȭ�� ���Ѵٸ� 'o' Ű�� ��������.   �ʿ� ��� : " << p->weaponlevel * 1000 << "\n\n";
    cout << "��ȣ��ȭ(+15 ����)�� ���Ѵٸ� 'p' Ű�� ��������.   �ʿ� ��� : " << p->weaponlevel * 10000 << "\n\n";
    cout << "��ȭ�� �ϰ� ���� �ʴٸ� 'Esc' Ű�� ��������.\n\n";
    cout << "���� ��� : " << p->gold << "\n\n";

    key = getch();
    if (key == 224) // ����Ű�� ���� ����
    {
        getch();
        weaponforge(p, true);
    }
    else if (key == 'o' || key == 'O')
    {
        Forge(p, 0, chance, "weapon", p->weaponlevel * 1000);
    }
    else if (key == 'p' || key == 'P')
    {
        Forge(p, 1, chance, "weapon", p->weaponlevel * 10000);
    }
    else if (key == 84 || key == 116)
    {
        showfulllog(); // tŰ
        weaponforge(p, true);
    }
    else if (key == 27) return;
    else weaponforge(p, true);

}

void armorforge(Player* p, bool visit)
{
    int key;
    int chance;
    system("cls");

    if (!visit)
    {
        Log[t] = "����� ����ȭ�ҿ� �鷶��.";
        t++;
    }

    showlog();

    // 100 95 90 85 80 70 70 60 60 50 50 50 40 40 40 30 30 20 10 5
    if (p->armorlevel <= 4) chance = 100 - p->armorlevel * 5;
    else if (p->armorlevel <= 6) chance = 70;
    else if (p->armorlevel <= 8) chance = 60;
    else if (p->armorlevel <= 11) chance = 50;
    else if (p->armorlevel <= 14) chance = 40;
    else if (p->armorlevel <= 16) chance = 30;
    else if (p->armorlevel == 17) chance = 20;
    else if (p->armorlevel == 18) chance = 10;
    else chance = 5;

    cout << "�� ��ȭ (���� : " << p->armorlevel << ")" << " Ȯ�� : " << chance << "  ����:" << p->defence << "  �ִ� ü��:" << p->maxhp << "\n\n";

    cout << "��ȭ�� ���Ѵٸ� 'o' Ű�� ��������.   �ʿ� ��� : " << p->armorlevel * 2000 << "\n\n";
    cout << "��ȣ��ȭ(+10 ����)�� ���Ѵٸ� 'p' Ű�� ��������.   �ʿ� ��� : " << p->armorlevel * 20000 << "\n\n";
    cout << "��ȭ�� �ϰ� ���� �ʴٸ� 'Esc' Ű�� ��������.\n\n";
    cout << "���� ��� : " << p->gold << "\n\n";

    key = getch();
    if (key == 224) // ����Ű�� ���� ����
    {
        getch();
        armorforge(p, true);
    }
    else if (key == 'o' || key == 'O') Forge(p, 0, chance, "armor", p->armorlevel * 2000);
    else if (key == 'p' || key == 'P') Forge(p, 1, chance, "armor", p->armorlevel * 20000);
    else if (key == 84 || key == 116)
    {
        showfulllog(); // tŰ
        armorforge(p, true);
    }
    else if (key == 27) return;
    else armorforge(p, true);
}

int main()
{
    srand(GetTickCount());
    Player p;
    int restart = Login(&p);
    if (restart) return 0;
    Load(&p);
    Log[0] = "#Log Start"; t++;
    Log[1] = "[��]T Ű�� ���� ��ü �α׸� Ȯ���� �� �ֽ��ϴ�."; t++;
    Log[2] = "[��]? Ű�� ���� ����, ������, ��ų���� ���� ������ Ȯ���� �� �ֽ��ϴ�."; t++;
    home(&p);
}