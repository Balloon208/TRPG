#include "Entity.h"

#pragma region DefineFunction
bool Login(Player* p); // 첫 로그인 시 실행되는 함수
void Save(Player* p); // 게임 진행 상황을 저장하는 함수
void Load(Player* p); // 이전에 진행한 게임을 불러오는 함수
void showlog(); // 로그를 보여주는 함수
void showplayerstatus(Player* p, string slot1, string slot2, string slot3, string slot4); // 플레이어 스테이터스
void showmobstatus(mob* m);
void fulllog(int current, int finish); // 풀로그 보여주는 함수
void showfulllog(); // 풀로그 인터페이스
void home(Player* p); // 마을
void homemenu(Player* p); // 마을 인터페이스
void homeselectmenu(Player* p); // 마을에서 선택
void movemenu(Player* p); // 이동할 곳 선택
void skillset(Player* p, bool mode); // 스킬 장착 및 해제
void passiveeffect(Player* p, mob* m, bool onoff); // 패시브 효과 적용/미적용
void shop(Player* p); // 상점
void pattack(Player* p, mob* m, bool skillmode); // Player 공격
void mattack(Player* p, mob* m); // Mob 공격
void attack(Player* p, mob* m); // 전투 진행 함수
void skillattack(Player* p, mob* m, int skillnum); // 스킬 공격(항상 선공)
void readymenu(Player* p); // 탐험에서의 선택
void summonmob(Player* p); // 몹 소환 및 확률
void fightmenu(mob* m, Player* p, bool skillmode); // 전투 인터페이스
void fight(Player* p); // 탐험 인터페이스
void fightselectmenu(mob* m, Player* p); // 전투 중 선택
bool selectitem(Player* p); // 아이템 선택
void showitem(Player* p); // 아이템 보여주기
void Forge(Player* p, int protect, int chance, string mode, int upmoney); // 강화가 진행되는 함수
void weaponforge(Player* p, bool visit); // 무기강화소 (확률 및 돈 조정)
void armorforge(Player* p, bool visit); // 방어구강화소 (확률 및 돈 조정)
void death(Player* p);
#pragma endregion

#pragma region Login/Save/Load

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
        cout << "신규 가입을 위하여 이름을 입력하세요 : ";
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

        fp = fopen("./Save/playerpassiveskills.txt", "w");

        // 스킬 설정 옵션 (skill setting), name, Mana, Learned(1 = 스킬 배움, 2 = 장착 중)
        fprintf(fp, "[Passive]강인한힘 0\n");
        fprintf(fp, "[Passive]광인화 0\n");
        fprintf(fp, "[Passive]철갑화 0\n");
        fclose(fp);

        fp = fopen("./Save/itemDB.txt", "w");

        fprintf(fp, "소형포션 -1 500 300\n");
        fprintf(fp, "중형포션 -1 2000 1500\n");
        fprintf(fp, "대형포션 -1 5000 3000\n");
        fprintf(fp, "[Skillbook]퍼스트블러드 7 30000 0\n");

        fclose(fp);

        fp = fopen("./Save/playeritem.txt", "w");

        fprintf(fp, "소형포션 0 -1\n");
        fprintf(fp, "중형포션 0 -1\n");
        fprintf(fp, "대형포션 0 -1\n");
        fprintf(fp, "[Skillbook]퍼스트블러드 0 7\n");

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
            if (i == 1) cout << "이어하기";
            if (i == 2) cout << "새로하기";
            cout << "   ";
        }
        // 로고 및 버튼 선택 (이어하기) / (새로하기)
        bool command = false;
        int key;
        point = 1;
        while (!command)
        {
            if (kbhit())
            {
                key = getch();
                {
                    if (key == 224) // 방향키
                    {
                        key = getch();
                        if (key == 75 && point > 1) point--; // 왼쪽
                        if (key == 77 && point < 2) point++; // 오른쪽
                    }
                    if (key == 13) // enter키
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
                            cout << "초기화가 완료되었습니다. 다시 실행해 주세요.";
                            return true;
                        }
                    }
                    system("cls");
                }

                for (int i = 1; i <= 4; i++)
                {
                    if (i == point) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
                    else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
                    if (i == 1) cout << "이어하기";
                    if (i == 2) cout << "새로하기";
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

    fp = fopen("./Save/playerpassiveskills.txt", "w");
    for (int i = 1; i <= totalpassive; i++)
    {
        fprintf(fp, "%s %d\n", get<0>(passiveskills[i]).c_str(), get<1>(passiveskills[i]));
    }
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

    fp = fopen("./Save/playerpassiveskills.txt", "r");
    for (int i = 1; i <= totalpassive; i++)
    {
        char skillnames[10000];
        fscanf(fp, "%s %d\n", skillnames, &get<1>(passiveskills[i]));
        get<0>(passiveskills[i]) = skillnames;
    }
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
#pragma endregion

#pragma region Utility

void death(Player* p) {
    p->gold = 0;
    p->heal();
    Save(p);
    system("cls");
    cout << p->name << "님이 사망하여 골드를 모두 잃었습니다." << endl;
    cout << "집으로 귀환하시겠습니까? ( 귀환하려면 스페이스 바 키를 누르세요 )";
    while (1)
    {
        if (kbhit())
        {
            int key = getch();
            if (key == 32) break; //esc
        }
    }
    point = 1;
    home(p);
}

void showlog()
{
    for (int i = t - 5; i < t; i++)
    {
        if (i < 0) cout << '\n';
        else cout << Log[i] << '\n';
    }
    cout << "ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ\n\n";
}

void showplayerstatus(Player* p, string slot1, string slot2, string slot3, string slot4)
{
    playerhppercent = (double)p->hp / p->maxhp * 100;
    playermppercent = (double)p->mp / p->maxmp * 100;
    playerexppercent = (double)p->exp / p->LVUPexp * 100;

    // 각 슬롯에 해당하는 이름만 넣어주시면 됩니다. ex) showplayerstatus(p, "1", "2", "3", "4");
    for (int i = 0; i < 16; i++) //playerhpbar
    {
        if (i * 6.25 < playerhppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "■";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
    cout << '\n';
    for (int i = 0; i < 16; i++) //playermpbar
    {
        if (i * 6.25 < playermppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "■";
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
    cout << "레벨 : " << p->level << " (" << p->exp << ")" << "   ";
    cout << "골드 : " << p->gold << '\n';

    cout << "[";
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // levelbar
    for (int i = 1; i <= 25; i++)
    {
        if (playerexppercent < i * 4)
        {
            if (playerexppercent - ((i - 1) * 4) >= 2) // 2%의 경우에 연하게
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
    for (int i = 0; i < 16; i++) //mobhpbar
    {
        if (i * 6.25 < mobhppercent) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
        else SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
        cout << "■";
    }
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    cout << '\n';
    cout << "(적)" << m->name << '\n';
    cout << "HP : " << m->hp << " / " << m->maxhp << '\n';
    cout << '\n';
}

void fulllog(int current, int finish)
{
    system("cls");
    cout << "ESC 를 눌러 돌아가세요. (방향키 위 아래로 이동 가능)" << "\n\n";
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
            if (key == 224) // 방향키
            {
                key = getch();
                if (key == 72) // 위쪽
                {
                    if (current - lognum <= 0) current = 0;
                    else current -= lognum;
                }
                if (key == 80) // 아래쪽
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
#pragma endregion

#pragma region Home

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
    showplayerstatus(p, "이동", "휴식", "스킬설정", "상점");
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
            if (key == 224) // 방향키
            {
                key = getch();
                if (key == 75 && point > 1) point--; // 왼쪽
                if (key == 77 && point < 4) point++; // 오른쪽
            }
            if (key == 13) // enter키
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
                    skillset(p, false);
                }
                if (point == 4)
                {
                    command = true;
                    point = 1;
                    shop(p);
                }
            }
            if (key == 84 || key == 116) showfulllog(); // t키
            if (key == 73 || key == 105) p->playerdescription(); // i키
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

    cout << "이동할 곳을 선택해 주세요.\n\n";

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
                if (key == 224) // 방향키
                {
                    key = getch();
                    if (key == 72 && point > 1)// 위쪽
                    {
                        point--;
                    }
                    if (key == 80 && point < stage - 1)// 아래쪽
                    {
                        point++;
                    }
                }
                if (key == 13) // enter키
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
                    Log[t] = "당신은 " + worldmap[where] + "(으)로 여정을 떠났다."; t++;
                    fight(p);
                    readymenu(p);
                }
                if (key == 27) //esc
                {
                    point = 1;
                    break;
                }
                if (key == 84 || key == 116) showfulllog(); // t키
                if (key == 73 || key == 105) p->playerdescription(); // i키
            }
            movemenu(p);
        }
    }
    command = false;
    home(p);
}
#pragma endregion

#pragma region Shop

void shop(Player* p)
{
    item item;
    system("cls");
    bool command = false;

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    showlog();

    cout << "구매하기 위해선 B, 팔기 위해선 S를 눌러주세요.\n\n";
    cout << "현재 골드 : " << p->gold << "\n\n";
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

        cout << get<0>(itemlist[i]) << " : BUY " << get<2>(itemlist[i]) << " / SELL " << get<3>(itemlist[i]) << " / 보유 개수 : (" << p->playeritemlist[i].first << ")" << '\n';
    }

    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);

    while (!command)
    {
        int key;
        if (kbhit())
        {
            key = getch();

            if (key == 224) // 방향키
            {
                key = getch();
                if (key == 72 && point > 1) point--; // 위쪽
                if (key == 80 && point < totalitem + totalskillbooks) point++; // 아래쪽
            }

            if ((key == 66 || key == 98) && get<1>(itemlist[point]) != -100) // B 키
            {
                if (p->gold >= get<2>(itemlist[point]))
                {
                    p->gold -= get<2>(itemlist[point]);
                    p->playeritemlist[point].first++;
                    Log[t] = get<0>(itemlist[point]) + "를 구매하였다."; t++;

                    if (get<1>(itemlist[point]) >= 1 && get<1>(itemlist[point]) < 100) // 스킬북
                    {
                        p->LearnSkill("A", get<1>(itemlist[point]));
                        get<1>(itemlist[point]) = -100;
                    }
                    Save(p);
                }
                else
                {
                    Log[t] = "골드가 부족합니다. (" + to_string(p->gold) + "/" + to_string(get<2>(itemlist[point])) + ")"; t++;
                }
            }
            if (key == 83 || key == 115) // S 키
            {
                if (p->playeritemlist[point].first > 0 && !(p->playeritemlist[point].second >= 1 && p->playeritemlist[point].second < 100))
                {
                    p->gold += get<3>(itemlist[point]);
                    p->playeritemlist[point].first--;
                    Log[t] = get<0>(itemlist[point]) + "를 판매하였다.";
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
            if (key == 84 || key == 116) showfulllog(); // t키
            if (key == 73 || key == 105) p->playerdescription(); // i키
            shop(p);
        }
    }
    command = false;
    home(p);
}
#pragma endregion

#pragma region AttackLogic

void pattack(Player* p, mob* m)
{
    double multiple = double((p->level - m->level) * 5 + 100) / 100;
    if (multiple > 1.3) multiple = 1.3;
    if (multiple < 0.5) multiple = 0.5;

    int damage = round((rand() % p->damage + p->damage) / log3(m->defence) * multiple);
    Log[t] = m->name + "에게 " + to_string(damage) + " 데미지를 입혔습니다!";
    m->hp -= damage;
    t++;
    if (m->hp <= 0)
    {
        passiveeffect(p, m, false);
        m->Mobdeath(p);
        return;
    }
}

void mattack(Player* p, mob* m)
{
    double multiple = double((m->level - p->level) * 5 + 100) / 100;
    if (multiple > 1.3) multiple = 1.3;
    if (multiple < 0.5) multiple = 0.5;
    int damage = round((rand() % m->damage + m->damage) / log3(p->defence) * multiple);
    Log[t] = m->name + "이(가) 공격하여 " + to_string(damage) + " 데미지를 입었습니다!";
    p->hp -= damage;
    t++;
    if (p->hp <= 0)
    {
        passiveeffect(p, m, false);
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
    int mphealing = min(p->maxmp, p->mp + (p->maxmp / 20)) - p->mp; // mp 5% 회복
    p->mp += mphealing;
}

#pragma endregion

#pragma region Skills

void skillattack(Player* p, mob* m, int skillnum)
{
    int damage;
    double multiple = double((p->level - m->level) * 5 + 100) / 100;
    if (multiple > 1.3) multiple = 1.3;

    if (skillnum == 1) // 방어
    {
        int success = rand() % 4;
        int temp = p->hp;

        if (success > 0)
        {
            Log[t] = get<0>(skills[skillnum]) + "를 사용하여 공격을 막아 피해량의 일부를 마나로 변환합니다.";
            p->defence *= 2;
            t++;
            fightmenu(m, p, true);
            Delay(100);
            mattack(p, m);
            p->defence /= 2;

            int mphealing = (temp - p->hp) / 2; // 잃은 hp의 50%만큼 mp 회복
            p->mp = min(p->maxmp, p->mp + mphealing);

            mphealing = min(p->maxmp, p->mp + (p->maxmp / 20)) - p->mp; // mp 5% 회복
            p->mp += mphealing;
        }
        else
        {
            Log[t] = get<0>(skills[skillnum]) + "를 사용하였으나 막는 것을 실패하였다!";
            t++;
            p->defence /= 2;
            fightmenu(m, p, true);
            Delay(100);
            mattack(p, m);
            p->defence *= 2;
            int mphealing = min(p->maxmp, p->mp + (p->maxmp / 20)) - p->mp; // mp 5% 회복
            p->mp += mphealing;
        }

    }
    if (skillnum == 2) // 크로스컷
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            for (int i = 0; i < 2; i++)
            {
                damage = (rand() % (p->damage * 2) + p->damage) / log3(m->defence) * multiple;
                Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
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
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if (skillnum == 3) // 힐링
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            int healing = min(p->maxhp, p->hp + (p->maxhp / 8)) - p->hp; // hp 약 12.5% 회복
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
    if (skillnum == 4) // 급소찌르기
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            damage = (rand() % p->damage) + p->damage * multiple;
            Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
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
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if (skillnum == 5) // 분쇄
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            for (int i = 0; i < 3; i++)
            {
                damage = (rand() % (p->damage * 5)) / log3(m->defence) * multiple;
                Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
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
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if (skillnum == 6) // 거인의일격
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            if (multiple < 1) multiple = 1;
            p->mp -= get<1>(skills[skillnum]);
            damage = (rand() % (p->damage * 5) + p->damage * 10) / log3(m->defence) * pow(multiple,2);
            Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
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
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
    if (skillnum == 7) // 퍼스트블러드
    {
        if (get<1>(skills[skillnum]) <= p->mp)
        {
            p->mp -= get<1>(skills[skillnum]);
            damage = m->hp / 5 + m->maxhp / 20; // (남은 체력의 20% + 최대 체력의 5%)
            Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
            t++;

            m->hp -= damage;
            damage = round(double((rand() % (p->damage * 5) + p->damage * 3) * m->hp / m->maxhp)); // 데미지 3배~8배 (방어 관통)) * 남은 체력% /100
            if (damage < 0) damage = 0;
            Log[t] = m->name + "에게 " + get<0>(skills[skillnum]) + "를 사용하여 " + to_string(damage) + " 데미지를 입혔습니다!";
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
            Log[t] = "마나가 부족합니다. (" + to_string(p->mp) + "/" + to_string(get<1>(skills[skillnum])) + ")";
            t++;
        }
    }
}

void skillset(Player* p, bool mode = false)
{
    system("cls");
    bool command = false;

    showlog();

    if (mode == false) cout << "C 키를 눌러 스킬 선택 모드를 변경하세요. (현재 : Active skill)\n\n";
    else cout << "C 키를 눌러 스킬 선택 모드를 변경하세요. (현재 : Passive skill)\n\n";

    if (mode == false)
    {
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
                cout << "   " << get<0>(skills[i]) << "(" << get<1>(skills[i]) << ")" << '\n';
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
    }
    else
    {
        for (int i = 1; i <= totalpassive; i++)
        {
            if (i == point) cout << ">";

            if (get<1>(passiveskills[i]) == 1)
            {
                cout << "   " << get<0>(passiveskills[i]) << '\n';
            }
            else if (get<1>(passiveskills[i]) == 2)
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2);
                cout << "   " << get<0>(passiveskills[i]) << '\n';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
            else
            {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
                cout << "   " << get<0>(passiveskills[i]) << '\n';
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
            }
        }
    }

    Save(p);

    while (!command)
    {
        int key;
        if (kbhit())
        {
            key = getch();
            if (key == 224) // 방향키
            {
                key = getch();
                if (key == 72) // 위쪽
                {
                    if (point > 1)
                    {
                        point--;
                    }
                }
                if (key == 80) // 아래쪽
                {
                    if (mode == false)
                    {
                        if (point < totalskill)
                        {
                            point++;
                        }
                    }
                    else
                    {
                        if (point < totalpassive)
                        {
                            point++;
                        }
                    }
                }
            }
            if (key == 13) // enter키
            {
                command = true;

                if (mode == false)
                {
                    if (usingskill <= 4 || get<2>(skills[point]) == 2) // 스킬 최대갯수 내에 들거나, 해제를 하는 경우.
                    {
                        if (get<2>(skills[point]) == 1) // 장착의 경우
                        {
                            Log[t] = get<0>(skills[point]) + " 스킬을 장착하였습니다."; t++;
                            get<2>(skills[point]) = 2;
                        }
                        else if (get<2>(skills[point]) == 2) // 해제의 경우
                        {
                            Log[t] = get<0>(skills[point]) + " 스킬을 해제하였습니다."; t++;
                            get<2>(skills[point]) = 1;
                        }
                    }
                    else if (get<2>(skills[point]) == 1) // 최대갯수이며, 장착을 하는 경우
                    {
                        Log[t] = "스킬 슬롯이 가득 찼습니다."; t++;
                    }
                }
                else
                {
                    if (get<1>(passiveskills[point]) == 1)
                    {
                        Log[t] = get<0>(passiveskills[point]) + " 을 활성화하였습니다."; t++;
                        get<1>(passiveskills[point]) = 2;
                    }
                    else if (get<1>(passiveskills[point]) == 2)
                    {
                        Log[t] = get<0>(passiveskills[point]) + " 을 비활성화하였습니다."; t++;
                        get<1>(passiveskills[point]) = 1;
                    }
                }
            }
            if (key == 47 || key == 63) // / or ?
            {
                p->skilldescription(point, mode);
            }
            if (key == 67 || key == 99) // c키
            {
                mode = !mode;
                point = 1;
            }
            if (key == 27) //esc
            {
                point = 1;
                break;
            }
            if (key == 84 || key == 116) showfulllog(); // t키
            if (key == 73 || key == 105) p->playerdescription(); // i키
            skillset(p, mode);
        }
    }
    command = false;
    home(p);
}
#pragma endregion

#pragma region Passives

void passiveeffect(Player* p, mob* m, bool onoff)
{
    if (onoff == true)
    {
        memory[0][0] = p->damage;
        memory[0][1] = p->defence;
        memory[0][2] = p->speed;
    }
    else
    {
        p->damage = memory[0][0];
        p->defence = memory[0][1];
        p->speed = memory[0][2];
    }

    if (get<1>(passiveskills[1]) == 2) // 강인한힘
    {
        int amount = 5;

        if (onoff == true)
        {
            Log[t] = "전투에 돌입하여 " + get<0>(passiveskills[1]) + " 효과가 적용됩니다."; t++;
            p->damage += amount;
        }
    }
    if (get<1>(passiveskills[2]) == 2) // 광인화
    {
        if (onoff == true)
        {
            Log[t] = "전투에 돌입하여 " + get<0>(passiveskills[2]) + " 효과가 적용됩니다."; t++;
            p->damage *= 1.5;
            p->defence /= 2;
        }
    }
    if (get<1>(passiveskills[3]) == 2) // 철갑화
    {
        if (onoff == true)
        {
            Log[t] = "전투에 돌입하여 " + get<0>(passiveskills[3]) + " 효과가 적용됩니다."; t++;
            p->defence *= 1.1;
            p->speed = 1;
        }
    }
}
#pragma endregion

#pragma region SummonMob
// 몬스터 소환 확률
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
    }
    if (where == 4)
    {
        int n = rand() % 100 + 1;
        if (n <= 40) m.RockSlime();
        else if (n <= 80) m.Bat();
        else if (n <= 95) m.MiniGolem();
        else if (n <= 100) m.Golem();
    }
    if (where == 5)
    {
        int n = rand() % 100 + 1;
        if (n <= 30) m.killerdog();
        else if (n <= 50) m.hunter();
        else if (n <= 70) m.shadower();
        else if (n <= 97) m.badknight();
        else if (n <= 100) m.nohead();
    }
    if (where == 6)
    {
        int n = rand() % 100 + 1;
        if (n <= 35) m.zombie();
        else if (n <= 70) m.skeleton();
        else if (n <= 90) m.tankzombie();
        else if (n <= 97) m.blackknight();
        else if (n <= 100) m.demonite();
    }
    if (where == 7)
    {
        int n = rand() % 100 + 1;
        if (n <= 5) m.devilwall();
        else if (n <= 30) m.imp1();
        else if (n <= 55) m.darkknight();
        else if (n <= 70) m.darkshadower();
        else if (n <= 90) m.devilslime();
        else if (n <= 100) m.imp2();
    }
    passiveeffect(p, &m, true);
    fightmenu(&m, p, false);
    fightselectmenu(&m, p);
}
#pragma endregion

#pragma region Fight

#pragma region Logic
void fight(Player* p)
{
    Save(p);
    system("cls");
    mob m;

    showlog();
    showplayerstatus(p, "탐험한다", "돌아간다", "", "");
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
                if (key == 224) // 방향키
                {
                    key = getch();
                    if (key == 75 && point > 1) point--; // 왼쪽
                    if (key == 77 && point < 2) point++; // 오른쪽
                }
                if (key == 13) // enter키
                {
                    if (point == 1)
                    {
                        command = true;
                        summonmob(p);
                    }
                    if (point == 2)
                    {
                        Log[t] = p->name + "(이)는 탐험을 그만두고 돌아갔다."; t++;
                        command = true;
                        point = 1;
                    }
                }
                if (key == 84 || key == 116) showfulllog();
                if (key == 73 || key == 105) p->playerdescription(); // i키
                system("cls");
                fight(p);
            }
        }
    }
    home(p);
}

void fightmenu(mob* m, Player* p, bool skillmode)
{
    system("cls");

    showlog();

    showmobstatus(m);

    if (skillmode == false) showplayerstatus(p, "공격", "스킬", "아이템", "도망");
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

            if (key == 224) // 방향키
            {
                key = getch();
                if (key == 75 && point > 1) point--; // 왼쪽
                if (key == 77 && point < 4) point++; // 오른쪽
            }
            if (key == 13) // enter키
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
                            int mphealing = min(p->maxmp, p->mp + (p->maxmp / 20)) - p->mp; // mp 5% 회복
                            p->mp += mphealing;
                        }
                    }
                    if (point == 4)
                    {
                        Log[t] = "당신은 " + m->name + "(으)로부터 도망쳤다!";
                        t++;
                        point = 1;
                        passiveeffect(p, m, false);
                        return;
                    }
                }
            }
            if (key == 47 || key == 63) // / or ?
            {
                if (skillmode)
                {
                    if (p->skill[point] != 0) p->skilldescription(p->skill[point], false);
                }
                else m->mobdescription();
            }
            if (key == 27 && skillmode) //esc
            {
                skillmode = !skillmode;
                point = 2;
            }
            if (key == 84 || key == 116) showfulllog(); // t키
            if (key == 73 || key == 105) p->playerdescription(); // i키
            system("cls");
            fightmenu(m, p, skillmode);
        }
    }
    killtrigger = false;
    fight(p);
    readymenu(p);
}

#pragma endregion

#pragma region ItemSelect

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
                if (key == 224) // 방향키
                {
                    key = getch();
                    if (key == 72 && point > 1) point--; // 위쪽
                    if (key == 80 && point < totalitem) point++; // 아래쪽
                }
                if (key == 13) // enter키
                {
                    bool used = item.useitem(p, point);
                    selected = true;
                    point = 3;
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
#pragma endregion

#pragma endregion

#pragma region Forge

void Forge(Player* p, int protect, int chance, string mode, int upmoney) // status 증가는 적용안됨, 가끔 강제종료됨
{
    if (p->gold < upmoney)
    {
        Log[t] = "골드가 부족합니다. (" + to_string(p->gold) + "/" + to_string(upmoney) + ")";
        t++;
        return;
    }
    int k = rand() % 10000 + 1;
    if (mode == "weapon")
    {
        if (p->weaponlevel == 20)
        {
            Log[t] = "최대 강화 상태입니다. 강화를 취소합니다.";
            t++;
            return;
        }
        p->gold -= upmoney;
        if (chance * 100 >= k) // 성공
        {
            Log[t] = "장비 강화에 성공 하였다! (" + to_string(p->weaponlevel) + " -> " + to_string(p->weaponlevel + 1) + ")";
            t++;
            p->weaponlevel++;
            p->damage += weaponforgeadd[p->weaponlevel];
        }
        else
        {
            int down;
            if (!protect) down = rand() % (p->weaponlevel / 5 <= 0 ? 1 : p->weaponlevel / 5 + 1);
            else down = 0;

            if (p->weaponlevel >= 5 && p->weaponlevel < 10 && p->weaponlevel - down < 5) down = p->weaponlevel - 5;
            else if (p->weaponlevel >= 10 && p->weaponlevel < 15 && p->weaponlevel - down < 10) down = p->weaponlevel - 10;
            else if (p->weaponlevel >= 15 && p->weaponlevel < 20 && p->weaponlevel - down < 15) down = p->weaponlevel - 15;
            Log[t] = "장비 강화에 실패하였다... (" + to_string(p->weaponlevel) + " -> " + to_string(p->weaponlevel - down) + ")";
            t++;
            for (int i = p->weaponlevel; i > p->weaponlevel - down; i--)
            {
                p->damage -= weaponforgeadd[i];
            }
            p->weaponlevel -= down;
        }
    }
    if (mode == "armor")
    {
        if (p->armorlevel == 20)
        {
            Log[t] = "최대 강화 상태입니다. 강화를 취소합니다.";
            t++;
            return;
        }
        p->gold -= upmoney;
        if (chance * 100 >= k) // 성공
        {
            Log[t] = "방어구 강화에 성공 하였다! (" + to_string(p->armorlevel) + " -> " + to_string(p->armorlevel + 1) + ")";
            t++;
            p->armorlevel++;
            p->defence += armorforgeadd[p->armorlevel];
            p->maxhp += armorforgeadd[p->armorlevel] * 10;
            p->hp += armorforgeadd[p->armorlevel] * 10;
        }
        else
        {
            int down;
            if (!protect) down = rand() % (p->armorlevel / 5 <= 0 ? 1 : p->armorlevel / 5 + 1);
            else down = 0;

            if (p->armorlevel >= 5 && p->armorlevel < 10 && p->armorlevel - down < 5) down = p->armorlevel - 5;
            else if (p->armorlevel >= 10 && p->armorlevel < 15 && p->armorlevel - down < 10) down = p->armorlevel - 10;
            else if (p->armorlevel >= 15 && p->armorlevel < 20 && p->armorlevel - down < 15) down = p->armorlevel - 15;

            Log[t] = "방어구 강화에 실패하였다... (" + to_string(p->armorlevel) + " -> " + to_string(p->armorlevel - down) + ")";
            t++;
            for (int i = p->armorlevel; i > p->armorlevel - down; i--)
            {
                p->defence -= armorforgeadd[i];
                p->maxhp -= armorforgeadd[p->armorlevel] * 10;
                p->hp -= armorforgeadd[p->armorlevel] * 10;
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
        Log[t] = "당신은 무기강화소에 들렀다.";
        t++;
    }

    showlog();

    // 100 95 90 85 80 70 70 70 60 60 50 50 40 40 40 30 30 20 20 10
    if (p->weaponlevel < 5) chance = 100 - p->weaponlevel * 5;
    else if (p->weaponlevel < 8) chance = 70;
    else if (p->weaponlevel < 10) chance = 60;
    else if (p->weaponlevel < 12) chance = 50;
    else if (p->weaponlevel < 15) chance = 40;
    else if (p->weaponlevel < 17) chance = 30;
    else if (p->weaponlevel < 19) chance = 20;
    else chance = 10;
    
    int needgold=0;
    if (p->weaponlevel < 5) needgold = p->weaponlevel * 1000;
    else if (p->weaponlevel < 10) needgold = p->weaponlevel * 2000;
    else if (p->weaponlevel < 15) needgold = p->weaponlevel * 10000;
    else if (p->weaponlevel < 18) needgold = p->weaponlevel * 20000;
    else if (p->weaponlevel < 20) needgold = p->weaponlevel * 100000;
    cout << "무기 강화 (현재 : " << p->weaponlevel << ")" << " 확률 : " << chance << "  데미지:" << p->damage << "\n\n";

    cout << "강화를 원한다면 'o' 키를 누르세요.   필요 골드 : " << needgold << "\n\n";
    cout << "보호강화(+15 이하)를 원한다면 'p' 키를 누르세요.   필요 골드 : " << needgold * 5 << "\n\n";
    cout << "강화를 하고 싶지 않다면 'Esc' 키를 누르세요.\n\n";
    cout << "보유 골드 : " << p->gold << "\n\n";

    key = getch();
    if (key == 224) // 방향키로 종료 방지
    {
        getch();
        weaponforge(p, true);
    }
    else if (key == 'o' || key == 'O')
    {
        Forge(p, 0, chance, "weapon", needgold);
    }
    else if (key == 'p' || key == 'P')
    {
        Forge(p, 1, chance, "weapon", needgold * 5);
    }
    else if (key == 84 || key == 116)
    {
        showfulllog(); // t키
        weaponforge(p, true);
    }
    else if (key == 73 || key == 105)
    {
        p->playerdescription(); // i키
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
        Log[t] = "당신은 방어구강화소에 들렀다.";
        t++;
    }

    showlog();

    // 100 95 90 85 80 70 70 70 60 60 50 50 40 40 40 30 30 20 20 10
    if (p->armorlevel < 5) chance = 100 - p->armorlevel * 5;
    else if (p->armorlevel < 8) chance = 70;
    else if (p->armorlevel < 10) chance = 60;
    else if (p->armorlevel < 12) chance = 50;
    else if (p->armorlevel < 15) chance = 40;
    else if (p->armorlevel < 17) chance = 30;
    else if (p->armorlevel < 19) chance = 20;
    else chance = 10;

    int needgold=0;
    if (p->armorlevel < 5) needgold = p->armorlevel * 1500;
    else if (p->armorlevel < 10) needgold =  p->armorlevel * 3000;
    else if (p->armorlevel < 15) needgold = p->armorlevel * 15000;
    else if (p->armorlevel < 18) needgold = p->armorlevel * 30000;
    else if (p->armorlevel < 20) needgold = p->armorlevel * 150000;

    cout << "방어구 강화 (현재 : " << p->armorlevel << ")" << " 확률 : " << chance << "  방어력:" << p->defence << "  최대 체력:" << p->maxhp << "\n\n";

    cout << "강화를 원한다면 'o' 키를 누르세요.   필요 골드 : " << needgold << "\n\n";
    cout << "보호강화(+10 이하)를 원한다면 'p' 키를 누르세요.   필요 골드 : " << needgold * 5 << "\n\n";
    cout << "강화를 하고 싶지 않다면 'Esc' 키를 누르세요.\n\n";
    cout << "보유 골드 : " << p->gold << "\n\n";

    key = getch();
    if (key == 224) // 방향키로 종료 방지
    {
        getch();
        armorforge(p, true);
    }
    else if (key == 'o' || key == 'O') Forge(p, 0, chance, "armor", needgold);
    else if (key == 'p' || key == 'P') Forge(p, 1, chance, "armor", needgold * 5);
    else if (key == 84 || key == 116)
    {
        showfulllog(); // t키
        armorforge(p, true);
    }
    else if (key == 73 || key == 105)
    {
        p->playerdescription(); // i키
        armorforge(p, true);
    }
    else if (key == 27) return;
    else armorforge(p, true);
}
#pragma endregion

#pragma region main
int main()
{
    srand(GetTickCount());
    Player p;
    int restart = Login(&p);
    if (restart) return 0;
    Load(&p);
    Log[0] = "#Log Start"; t++;
    Log[1] = "[팁]T 키를 눌러 전체 로그를 확인할 수 있습니다."; t++;
    Log[2] = "[팁]? 키를 눌러 몬스터, 아이템, 스킬들의 세부 정보를 확인할 수 있습니다."; t++;
    Log[3] = "[팁]I 키를 눌러 본인의 스테이터스를 확인할 수 있습니다."; t++;
    home(&p);
}
#pragma endregion