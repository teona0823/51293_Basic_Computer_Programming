#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<mmsystem.h>
#pragma comment(lib,"winmm.lib")

#define LEFT 75 //�·� �̵�    //Ű���尪�� 
#define RIGHT 77 //��� �̵� 
#define UP 72 //ȸ�� 
#define DOWN 80 //soft drop
#define SPACE 32 //hard drop
#define p 112 //�Ͻ����� 
#define P 80 //�Ͻ�����
#define ESC 27 //�������� 
#define B 66
#define b 98

#define false 0
#define true 1

#define ACTIVE_BLOCK -2 // �����ǹ迭�� ����� ����� ���µ� 
#define CEILLING -1     // ����� �̵��� �� �ִ� ������ 0 �Ǵ� ���� ������ ǥ�� 
#define EMPTY 0         // ����� �̵��� �� ���� ������ ����� ǥ�� 
#define WALL 1
#define INACTIVE_BLOCK 2 // �̵��� �Ϸ�� ��ϰ� 

#define MAIN_X 11 //������ ����ũ�� 
#define MAIN_Y 23 //������ ����ũ�� 
#define MAIN_X_ADJ 3 //������ ��ġ���� 
#define MAIN_Y_ADJ 1 //������ ��ġ���� 

#define STATUS_X_ADJ MAIN_X_ADJ+MAIN_X+1 //��������ǥ�� ��ġ���� 

int STATUS_Y_GOAL; //GOAL ����ǥ����ġY ��ǥ ���� 
int STATUS_Y_LEVEL; //LEVEL ����ǥ����ġY ��ǥ ����
int STATUS_Y_SCORE; //SCORE ����ǥ����ġY ��ǥ ����

int blocks[8][4][4][4] = {
{{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
 {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},
{{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0}},
{{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0},
 {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}},
{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},
{{0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},{0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0}},
{{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0}, {0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0},
 {0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,0}}
};

int org_blocks[9][4][4][4] = {
{{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},
 {0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,1,1,0,0,1,1,0,0,0,0,0}},
{{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0},{0,1,0,0,0,1,0,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,1,1,0,0,0,1,1,0,0,0,0,0},{0,0,0,0,0,0,1,0,0,1,1,0,0,1,0,0}},
{{0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0},
 {0,0,0,0,0,1,1,0,1,1,0,0,0,0,0,0},{0,0,0,0,1,0,0,0,1,1,0,0,0,1,0,0}},
{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},
{{0,0,0,0,1,0,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,1,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,0,1,0},{0,0,0,0,0,1,1,0,0,1,0,0,0,1,0,0}},
{{0,0,0,0,0,1,0,0,1,1,1,0,0,0,0,0},{0,0,0,0,0,1,0,0,0,1,1,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,0,1,0,0},{0,0,0,0,0,1,0,0,1,1,0,0,0,1,0,0}},
{{0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0},{0,0,0,0,1,1,0,0,0,1,0,0,0,1,0,0},
 {0,0,0,0,0,0,0,0,1,1,1,0,1,0,0,0},{0,0,0,0,0,1,0,0,0,1,0,0,0,1,1,0}},
 {{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0},{0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0}}
};

int block_color[8] = { 14, 11, 12, 10, 6, 9, 13, 8 };

int b_type; //��� ������ ���� 
int b_rotation; //��� ȸ���� ���� 
int b_type_next; //���� ��ϰ� ���� 
int b_type_prev;

int main_org[MAIN_Y][MAIN_X]; //�������� ������ �����ϴ� �迭 ����Ϳ� ǥ���Ŀ� main_cpy�� ����� 
int main_org_color[MAIN_Y][MAIN_X];
int main_cpy[MAIN_Y][MAIN_X]; //�� maincpy�� �������� ����Ϳ� ǥ�õǱ� ���� ������ ������ ���� 
//main�� ��ü�� ��� ����Ϳ� ǥ������ �ʰ�(�̷��� �ϸ� ����Ͱ� �����Ÿ�) 
//main_cpy�� �迭�� ���ؼ� ���� �޶��� ���� ����Ϳ� ��ħ 
int bx, by; //�̵����� ����� �����ǻ��� x,y��ǥ�� ���� 

int key; //Ű����� �Է¹��� Ű���� ���� 

int speed; //��������ӵ� 
int level; //���� level 
int level_goal; //���������� �Ѿ�� ���� ��ǥ���� 
int cnt; //���� �������� ������ �� ���� ���� 
int score; //���� ���� 
int last_score = 0; //�������������� 
int score1 = 0; //�ְ�������� 
int score2 = 0;
int score3 = 0;
char name[11];
char last_name[11];
char name1[11] = { '\0' };
char name2[11] = { '\0' };
char name3[11] = { '\0' };

int coin = 0;
int old_coin = 0;
int item[3] = { 0, 0, 0 };
int old_item[3] = { 0, 0, 0 };
int item_price[3] = { 3, 5, 7 };
int item_id;

int item2_on = 0;//��ź������ ����
int item0_on = 0; // ���� �ι� on ����
int count = 0; // ���� �ι� ������ ���� ��ϸ��� ī��Ʈ..
int old_count = 0; // ���� �ι� ������ ���� ������ �����Ҷ� ī�� 
int item1_on = 0; // ��ĭ �� ������ ��뿩��    

int new_block_on = 0; //���ο� ���� �ʿ����� �˸��� flag 
int crush_on = 0; //���� �̵����� ����� �浹�������� �˷��ִ� flag 
int level_up_on = 0; //���������� ����(���� ������ǥ�� �Ϸ�Ǿ�����) �˸��� flag 
int space_key_on = 0; //hard drop�������� �˷��ִ� flag 

int is_clicked = 0;

void title(void); //���ӽ���ȭ�� 
void shop(void);
void enter_name(void);
void reset(void); //������ �ʱ�ȭ 
void reset_main(void); //���� ������(main_org[][]�� �ʱ�ȭ)
void reset_main_cpy(void); //copy ������(main_cpy[][]�� �ʱ�ȭ)
void draw_map(void); //���� ��ü �������̽��� ǥ�� 
void draw_main(void); //�������� �׸� 
void new_block(void); //���ο� ����� �ϳ� ���� 
void check_key(void); //Ű����� Ű�� �Է¹��� 
void drop_block(void); //����� �Ʒ��� ����Ʈ�� 
int check_crush(int bx, int by, int rotation); //bx, by��ġ�� rotationȸ������ ���� ��� �浹 �Ǵ� 
void move_block(int dir); //dir�������� ����� ������ 
void check_line(void); //���� ����á������ �Ǵ��ϰ� ���� 
void check_level_up(void); //������ǥ�� �޼��Ǿ������� �Ǵ��ϰ� levelup��Ŵ 
void check_game_over(void); //���ӿ������� �Ǵ��ϰ� ���ӿ����� ���� 
void item0(void);
void direct_draw(void);
void pause(void);//������ �Ͻ�������Ŵ 

void textcolor(int colornum)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colornum);
}

void gotoxy(int x, int y) { //gotoxy�Լ� 
    COORD pos = { 2 * x,y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE; //Ŀ������� �Լ��� ���Ǵ� ������ 
void setcursortype(CURSOR_TYPE c) { //Ŀ������� �Լ� 
    CONSOLE_CURSOR_INFO CurInfo;

    switch (c) {
    case NOCURSOR:
        CurInfo.dwSize = 1;
        CurInfo.bVisible = FALSE;
        break;
    case SOLIDCURSOR:
        CurInfo.dwSize = 100;
        CurInfo.bVisible = TRUE;
        break;
    case NORMALCURSOR:
        CurInfo.dwSize = 20;
        CurInfo.bVisible = TRUE;
        break;
    }
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

int main() {
    int i;

    system("cls");
    srand((unsigned)time(NULL)); //����ǥ���� 
    setcursortype(NOCURSOR); //Ŀ�� ���� 
    title(); //����Ÿ��Ʋ ȣ�� 
    enter_name();
    reset(); //������ ���� 

    while (1) {
        for (i = 0; i < 5; i++) { //����� ��ĭ�������µ��� 5�� Ű�Է¹��� �� ���� 
            check_key(); //Ű�Է�Ȯ�� 
            draw_main(); //ȭ���� �׸� 
            Sleep(speed); //���Ӽӵ����� 
            if (crush_on && check_crush(bx, by + 1, b_rotation) == false) Sleep(100);
            //����� �浹���ΰ�� �߰��� �̵��� ȸ���� �ð��� ���� 
            if (space_key_on == 1) { //�����̽��ٸ� �������(hard drop) �߰��� �̵��� ȸ���Ҽ� ���� break; 
                space_key_on = 0;
                break;
            }
        }
        drop_block(); // ����� ��ĭ ���� 
        check_level_up(); // �������� üũ 
        check_game_over(); //���ӿ����� üũ 
        if (new_block_on == 1) new_block(); // �� �� flag�� �ִ� ��� ���ο� �� ���� 
    }
}

void title(void) {
    int x = 5; //Ÿ��Ʋȭ���� ǥ�õǴ� x��ǥ 
    int y = 4; //Ÿ��Ʋȭ���� ǥ�õǴ� y��ǥ 
    int cnt; //Ÿ��Ʋ �������� ���� ����  

    gotoxy(x, y + 0); printf("����������������"); Sleep(100);
    gotoxy(x, y + 1); printf("�����  ����    ������"); Sleep(100);
    gotoxy(x, y + 2); printf("�����              ���  ��"); Sleep(100);
    gotoxy(x, y + 3); printf("������  ��  ��  ������"); Sleep(100);
    gotoxy(x, y + 4); printf("���  �������������"); Sleep(100);
    gotoxy(x, y + 5); printf("           BCP_11��"); Sleep(100);
    gotoxy(x + 5, y + 2); printf("T E T R I S"); Sleep(100);
    gotoxy(x, y + 7); printf("Please Enter key to Start..");
    gotoxy(x, y + 9); printf("  ��   : Shift");
    gotoxy(x, y + 10); printf("��  �� : Left / Right");
    gotoxy(x, y + 11); printf("  ��   : Soft Drop");
    gotoxy(x, y + 12); printf(" SPACE : Hard Drop");
    gotoxy(x, y + 13); printf("   P   : Pause");
    gotoxy(x, y + 14); printf("   V   : Shop");
    gotoxy(x, y + 15); printf("  ESC  : Quit");
    gotoxy(x, y + 16); printf("BONUS FOR HARD DROPS / COMBOS to COIN");

    FILE* sfile1 = fopen("score1.dat", "rt"); // score1.dat������ ����
    if (sfile1 == 0) { score1 = 0; } //������ ������ �� �ְ������� 0�� ���� 
    else {
        fscanf(sfile1, "%d", &score1); // ������ ������ �ְ������� �ҷ��� 
        fclose(sfile1); //���� ���� 
    }
    FILE* nfile1 = fopen("name1.dat", "rt");
    if (nfile1 == 0) { strcpy(name1, "USER"); }
    else
    {
        fscanf(nfile1, "%s", &name1);
        fclose(nfile1);
    }

    FILE* sfile2 = fopen("score2.dat", "rt"); // score2.dat������ ����
    if (sfile2 == 0) { score2 = 0; } //������ ������ �� 2�������� 0�� ���� 
    else {
        fscanf(sfile2, "%d", &score2); // ������ ������ �ְ������� �ҷ��� 
        fclose(sfile2); //���� ���� 
    }
    FILE* nfile2 = fopen("name2.dat", "rt");
    if (nfile2 == 0) { strcpy(name2, "USER"); }
    else
    {
        fscanf(nfile2, "%s", &name2);
        fclose(nfile2);
    }

    FILE* sfile3 = fopen("score3.dat", "rt"); // score3.dat������ ����
    if (sfile3 == 0) { score3 = 0; } //������ ������ �� 3�������� 0�� ���� 
    else {
        fscanf(sfile3, "%d", &score3); // ������ ������ �ְ������� �ҷ��� 
        fclose(sfile3); //���� ���� 
    }
    FILE* nfile3 = fopen("name3.dat", "rt");
    if (nfile3 == 0) { strcpy(name3, "USER"); }
    else
    {
        fscanf(nfile3, "%s", &name3);
        fclose(nfile3);
    }

    FILE* Fcoin = fopen("coin.dat", "rt"); // coin.dat ������ �б� ���� ����

    if (Fcoin == 0) coin = 20; // ������ ���� ��� 
    else {
        fscanf(Fcoin, "%d", &coin); // ������ ������ ������ �ҷ���
        fclose(Fcoin); // ���� �ݱ�
    }

    FILE* Fitem0 = fopen("item0.dat", "rt"); // coin.dat ������ �б� ���� ����

    if (Fitem0 == 0) item[0] = 0; // ������ ���� ��� 
    else {
        fscanf(Fitem0, "%d", &item[0]); // ������ ������ ������0�� �ҷ���
        fclose(Fitem0); // ���� �ݱ�
    }

    FILE* Fitem1 = fopen("item1.dat", "rt"); // coin.dat ������ �б� ���� ����

    if (Fitem1 == 0) item[1] = 0; // ������ ���� ��� 
    else {
        fscanf(Fitem1, "%d", &item[1]); // ������ ������ ������1�� �ҷ���
        fclose(Fitem1); // ���� �ݱ�
    }

    FILE* Fitem2 = fopen("item2.dat", "rt"); // coin.dat ������ �б� ���� ����

    if (Fitem2 == 0) item[2] = 0; // ������ ���� ��� 
    else {
        fscanf(Fitem2, "%d", &item[2]); // ������ ������ ������2�� �ҷ���
        fclose(Fitem2); // ���� �ݱ�
    }
    item2_on = 0;

    gotoxy(x + 20, y + 1); printf("+-- L E A D E R B O A R D --+");
    gotoxy(x + 20, y + 2); printf("|                           |");
    gotoxy(x + 20, y + 3); printf("| 1. %11s : %6d   |", name1, score1);
    gotoxy(x + 20, y + 4); printf("| 2. %11s : %6d   |", name2, score2);
    gotoxy(x + 20, y + 5); printf("| 3. %11s : %6d   |", name3, score3);
    gotoxy(x + 20, y + 6); printf("|                           |");
    gotoxy(x + 20, y + 7); printf("+---------------------------+");

    for (cnt = 0;; cnt++) { //cnt�� 1�� ������Ű�鼭 ��� �ݺ�    //�ϳ��� ���߿��� �� ��¦�̴� �ִϸ��̼�ȿ�� 
        //if (_kbhit()) break; //Ű�Է��� ������ ���ѷ��� ���� 
        if (_kbhit()) {
            // Ű �Է��� �ִ� ���
            char key = _getch();
            if (key == '\r') {
                // ���� Ű�� ���� ���
                break; // ���� ���� ����
            }
            else if (key == 'v' || key == 'V')
                shop();
        }

        if (cnt % 200 == 0) { gotoxy(x + 4, y + 1); printf("��"); }       //cnt�� 200���� ������ �������� ���� ǥ�� 
        if ((cnt % 200 - 100) == 0) { gotoxy(x + 4, y + 1); printf("  "); } //�� ī��Ʈ���� 100ī��Ʈ �������� ���� ���� 
        if ((cnt % 350) == 0) { gotoxy(x + 13, y + 2); printf("��"); } //������ ������ �ð����� ���� 
        if ((cnt % 350 - 100) == 0) { gotoxy(x + 13, y + 2); printf("  "); }
        Sleep(10); // 00.1�� ������  
    }

    while (_kbhit()) _getch(); //���ۿ� ��ϵ� Ű���� ���� 

}

void shop(void)
{
    int x = 5;
    int y = 4;
    system("cls");

    gotoxy(x, y + 0); printf("����������������"); Sleep(100);
    gotoxy(x, y + 1); printf("�����  ����    ������"); Sleep(100);
    gotoxy(x, y + 2); printf("�����              ���  ��"); Sleep(100);
    gotoxy(x, y + 3); printf("������  ��  ��  ������"); Sleep(100);
    gotoxy(x, y + 4); printf("���  �������������"); Sleep(100);
    gotoxy(x + 5, y + 2); printf("  S H O P  "); Sleep(100);
    gotoxy(x + 15, y + 2); printf("Current Coin : %d", coin);
    gotoxy(x, y + 10); printf("��2score(1) : %d", item[0]);
    gotoxy(x, y + 11); printf("Hammer(2) : %d", item[1]);
    gotoxy(x, y + 12); printf("Bomb(3) : %d", item[2]);
    gotoxy(x, y + 6); printf("+- 1 -+");
    gotoxy(x, y + 7); printf("|  ��  |");
    gotoxy(x, y + 8); printf("+-----+");
    gotoxy(x, y + 9); printf("  $ 3");
    gotoxy(x + 5, y + 6); printf("+- 2 -+");
    gotoxy(x + 5, y + 7); printf("|  ��  |");
    gotoxy(x + 5, y + 8); printf("+-----+");
    gotoxy(x + 5, y + 9); printf("  $ 5");
    gotoxy(x + 10, y + 6); printf("+- 3 -+");
    gotoxy(x + 10, y + 7); printf("|  ��  |");
    gotoxy(x + 10, y + 8); printf("+-----+");
    gotoxy(x + 10, y + 9); printf("  $ 7");

    gotoxy(x, y + 14); printf("0 �Է� �� ������ ���۵˴ϴ�.");
    gotoxy(x, y + 15); printf("������ �������� ���ڸ� �Է��ϼ���: ");
    scanf("%d", &item_id);

    if (item_id == 1)
    {
        if (coin < 3)
        {
            gotoxy(x, y + 16); printf("Error : Not Enough Coin");
            Sleep(3000);
            system("cls");
            shop();
        }
        else
        {
            coin = coin - 3;
            item[0]++;
            shop();
        }
    }
    else if (item_id == 2)
    {
        {
            if (coin < 5)
            {
                gotoxy(x, y + 16); printf("Error : Not Enough Coin");
                Sleep(3000);
                shop();
            }
            else
            {
                coin = coin - 5;
                item[1]++;
                shop();
            }
        }
    }
    else if (item_id == 3)
    {
        {
            if (coin < 7)
            {
                gotoxy(x, y + 16); printf("Error : Not Enough Coin");
                Sleep(3000);
                shop();
            }
            else
            {
                coin = coin - 7;
                item[2]++;
                shop();
            }
        }
    }
    else if (item_id == 0)
    {
        while (_kbhit()) _getch();
        enter_name;
    }
    else
    {
        gotoxy(x, y + 16); printf("Error : Enter a Number 0~3");
        Sleep(3000);
        shop();
    }
}

void enter_name(void)
{
    int x = 5;
    int y = 4;
    system("cls");

    gotoxy(x, y + 0); printf("����������������"); Sleep(100);
    gotoxy(x, y + 1); printf("�����  ����    ������"); Sleep(100);
    gotoxy(x, y + 2); printf("�����              ���  ��"); Sleep(100);
    gotoxy(x, y + 3); printf("������  ��  ��  ������"); Sleep(100);
    gotoxy(x, y + 4); printf("���  �������������"); Sleep(100);
    gotoxy(x + 5, y + 2); printf("L O G   I N"); Sleep(100);
    gotoxy(x, y + 6); printf("Enter Your Name: ");
    scanf("%s", name);

    if (strlen(name) > 11)
    {
        printf("\n   Error: Please Enter Your Name Within 11 Characters");
        Sleep(3000);
        enter_name();
    }
}

void direct_draw(void) {

    int i, j;

    for (i = 1; i < 3; i++) { // z, Z Ű�� ���� �� ���̷�Ʈ�� ȭ�� �籸��
        for (j = 0; j < 4; j++) {
            if (blocks[7][0][i][j] == 1) {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("��");
            }
            else {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
}

void reset(void) {

    FILE* sfile1 = fopen("score1.dat", "rt"); // score1.dat������ ����
    if (sfile1 == 0) { score1 = 0; } //������ ������ �� �ְ������� 0�� ���� 
    else {
        fscanf(sfile1, "%d", &score1); // ������ ������ �ְ������� �ҷ��� 
        fclose(sfile1); //���� ���� 
    }
    FILE* nfile1 = fopen("name1.dat", "rt");
    if (nfile1 == 0) { strcpy(name1, "USER"); }
    else
    {
        fscanf(nfile1, "%s", &name1);
        fclose(nfile1);
    }

    level = 1; //�������� �ʱ�ȭ 
    score = 0;
    level_goal = 1000;
    key = 0;
    crush_on = 0;
    cnt = 0;
    speed = 100;

    system("cls"); //ȭ������ 
    reset_main(); // main_org�� �ʱ�ȭ 
    draw_map(); // ����ȭ���� �׸�
    draw_main(); // �������� �׸� 

    b_type_next = rand() % 7; //�������� ���� ��� ������ �����ϰ� ���� 
    new_block(); //���ο� ����� �ϳ� ����  

}

void reset_main(void) { //�������� �ʱ�ȭ  
    int i, j;

    for (i = 0; i < MAIN_Y; i++) { // �������� 0���� �ʱ�ȭ  
        for (j = 0; j < MAIN_X; j++) {
            main_org[i][j] = 0;
            main_cpy[i][j] = 100;
        }
    }
    for (j = 1; j < MAIN_X; j++) { //y���� 3�� ��ġ�� õ���� ���� 
        main_org[3][j] = CEILLING;
    }
    for (i = 1; i < MAIN_Y - 1; i++) { //�¿� ���� ����  
        main_org[i][0] = WALL;
        main_org[i][MAIN_X - 1] = WALL;
    }
    for (j = 0; j < MAIN_X; j++) { //�ٴں��� ���� 
        main_org[MAIN_Y - 1][j] = WALL;
    }
}

void reset_main_cpy(void) { //main_cpy�� �ʱ�ȭ 
    int i, j;

    for (i = 0; i < MAIN_Y; i++) {         //�����ǿ� ���ӿ� ������ �ʴ� ���ڸ� ���� 
        for (j = 0; j < MAIN_X; j++) {  //�̴� main_org�� ���� ���ڰ� ���� �ϱ� ���� 
            main_cpy[i][j] = 100;
        }
    }
}

void draw_map(void) { //���� ���� ǥ�ø� ��Ÿ���� �Լ�  
    int y = 3;             // level, goal, score�� �����߿� ���� �ٲ�� �� ���� �� y���� ���� �����ص� 
    // �׷��� Ȥ�� ���� ���� ǥ�� ��ġ�� �ٲ� �� �Լ����� �ȹٲ㵵 �ǰ�.. 
    gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL = y - 1); printf(" USER : %s", name);
    gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL = y); printf(" LEVEL : %5d", level);
    gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL = y + 1); printf(" GOAL  : %5d", 10 - cnt);
    gotoxy(STATUS_X_ADJ, y + 2); printf("+-  N E X T  -+ ");
    gotoxy(STATUS_X_ADJ, y + 3); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 4); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 5); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 6); printf("|             | ");
    gotoxy(STATUS_X_ADJ, y + 7); printf("+-- -  -  - --+ ");
    gotoxy(STATUS_X_ADJ, y + 8); printf(" YOUR SCORE :");
    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE = y + 9); printf("        %6d", score);
    gotoxy(STATUS_X_ADJ, y + 10); printf(" LAST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 11); printf("        %s's %d", last_name, last_score);
    gotoxy(STATUS_X_ADJ, y + 12); printf(" BEST SCORE :");
    gotoxy(STATUS_X_ADJ, y + 13); printf("        %s's %d", name1, score1);
    gotoxy(STATUS_X_ADJ, y + 15); printf("  ��   : Shift        SPACE : Hard Drop");
    gotoxy(STATUS_X_ADJ, y + 16); printf("��  �� : Left / Right   P   : Pause");
    gotoxy(STATUS_X_ADJ, y + 17); printf("  ��   : Soft Drop     ESC  : Quit");
    gotoxy(STATUS_X_ADJ, y + 20); printf("11�� - ������ ������ �ڰ��� �ڼ���");

    gotoxy(4, y + 22); printf("item  Z: double score(5 turn) / B: hammer / C:bomb");
    gotoxy(4, y + 23); printf("inventory: ��(Z):%3d / ��(B) :%3d / ��(C):%3d", item[0], item[1], item[2]);
}

void draw_main(void) { //������ �׸��� �Լ� 
    int i, j;

    for (j = 1; j < MAIN_X - 1; j++) { //õ���� ��� ���ο���� �������� �������� ���� �׷��� 
        if (main_org[3][j] == EMPTY) main_org[3][j] = CEILLING;
    }
    for (i = 0; i < MAIN_Y; i++) {
        for (j = 0; j < MAIN_X; j++) {
            if (main_cpy[i][j] != main_org[i][j]) { //cpy�� ���ؼ� ���� �޶��� �κи� ���� �׷���.
                //�̰� ������ ��������ü�� ��� �׷��� �������� ��¦�Ÿ�
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                switch (main_org[i][j]) {
                case EMPTY: //��ĭ��� 
                    printf("  ");
                    break;
                case CEILLING: //õ���� 
                    printf(". ");
                    break;
                case WALL: //����� 
                    printf("��");
                    break;
                case INACTIVE_BLOCK: //���� �� ���  
                    textcolor(block_color[b_type_prev]);
                    printf("��");
                    textcolor(15);
                    break;
                case ACTIVE_BLOCK: //�����̰��ִ� �� ���  
                    textcolor(block_color[b_type]);
                    printf("��");
                    textcolor(15);
                    break;
                }
            }
        }
    }
    for (i = 0; i < MAIN_Y; i++) { //�������� �׸� �� main_cpy�� ����  
        for (j = 0; j < MAIN_X; j++) {
            main_cpy[i][j] = main_org[i][j];
        }
    }
}

void new_block(void) { //���ο� ��� ����  
    int i, j;

    bx = (MAIN_X / 2) - 1; //��� ���� ��ġx��ǥ(�������� ���) 
    by = 0;  //��� ������ġ y��ǥ(���� ��) 
    b_type_prev = b_type; // ���� ������ ���� �������� �ű�
    b_type = b_type_next; //���������� ������ 
    b_type_next = rand() % 7; //���� ���� ���� 
    b_rotation = 0;  //ȸ���� 0������ ������ 

    if (is_clicked == 1) {
        b_type = 7;
        b_type_next = rand() % 7;
    }
    else {
        b_type_next = rand() % 7; //z �ȴ����� �� ���� ���� ���� 
    }

    new_block_on = 0; //new_block flag�� ��  

    for (i = 0; i < 4; i++) { //������ bx, by��ġ�� ������  
        for (j = 0; j < 4; j++) {
            if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
        }
    }
    for (i = 1; i < 3; i++) { //���ӻ���ǥ�ÿ� ������ ���ú��� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                textcolor(block_color[b_type_next]);
                printf("��");
                textcolor(15);
            }
            else {
                gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                printf("  ");
            }
        }
    }
    count++; //���� �ι� ������ ������ ���� ī��Ʈ

    if (count - old_count > 2) {
        item0_on = 0;
        gotoxy(STATUS_X_ADJ + 7, 13); printf("                                        ");
    }
}

void no_allow_item() {
    gotoxy(STATUS_X_ADJ, 19);  printf("!  You can't use this.  ! ");
}

void check_key(void) {
    key = 0; //Ű�� �ʱ�ȭ  

    if (_kbhit()) { //Ű�Է��� �ִ� ���  
        key = _getch(); //Ű���� ����
        if (key == 224) { //����Ű�ΰ�� 
            do { key = _getch(); } while (key == 224);//����Ű���ð��� ���� 
            switch (key) {
            case LEFT: //����Ű ��������  
                if (check_crush(bx - 1, by, b_rotation) == true) move_block(LEFT);
                break;                            //�������� �� �� �ִ��� üũ �� �����ϸ� �̵�
            case RIGHT: //������ ����Ű ��������- ���� �����ϰ� ó���� 
                if (check_crush(bx + 1, by, b_rotation) == true) move_block(RIGHT);
                break;
            case DOWN: //�Ʒ��� ����Ű ��������-���� �����ϰ� ó���� 
                if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN);
                break;
            case UP: //���� ����Ű �������� 
                if (check_crush(bx, by, (b_rotation + 1) % 4) == true) move_block(UP);
                //ȸ���� �� �ִ��� üũ �� �����ϸ� ȸ��
                else if (crush_on == 1 && check_crush(bx, by - 1, (b_rotation + 1) % 4) == true) move_block(100);
            }                    //�ٴڿ� ���� ��� �������� ��ĭ����� ȸ���� �����ϸ� �׷��� ��(Ư������)
        }
        else if (key == 122 || key == 90) { //ZŰ ���� ���
            if (item[0] > 0) {//item0 ���� �Լ� �ִ� scope
                item[0]--;
                item0();
            }
            else {
                no_allow_item();
            }
        }



        else if (key == 99 || key == 67) {
            if (item[2] > 0) {
                item2_on = 1;
                item[2]--;

                for (int i = 0; i < MAIN_Y; i++) {
                    for (int j = 0; j < MAIN_Y; j++) {
                        if (main_org[j][i] <= ACTIVE_BLOCK) {
                            main_org[j][i] = EMPTY;
                        }
                        if (main_cpy[j][i] <= ACTIVE_BLOCK) {
                            main_cpy[j][i] = EMPTY;
                        }
                    }
                }

                draw_main();

                cnt = 0;

                for (int i = 0; i < 4; i++) {
                    gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + 6);
                    printf("��ź!");
                    Sleep(200);
                }
                reset_main_cpy();

                for (int i = MAIN_Y - 2; i > MAIN_Y - 4; i--) {
                    for (int j = 1; j < MAIN_X - 1; j++) {
                        main_org[i][j] = INACTIVE_BLOCK * (b_type + 1);
                        gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i);
                        printf("��");
                        Sleep(0);
                    }
                }
                Sleep(20);
                check_line();
                /////////////////
                int i, j;
                bx = (MAIN_X / 2) - 1; //��� ���� ��ġx��ǥ(�������� ���) 
                by = 0;  //��� ������ġ y��ǥ(���� ��) 
                b_rotation = 0;  //ȸ���� 0������ ������ 

                new_block_on = 0; //new_block flag�� ��  

                for (i = 0; i < 4; i++) { //������ bx, by��ġ�� ������  
                    for (j = 0; j < 4; j++) {
                        if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK * (b_type + 1);
                    }
                }
                //system("cls"); //ȭ�� ����� ���� �׸� 
                reset_main_cpy();
                draw_main();
                draw_map();
                for (i = 0; i < 4; i++) { //���ӻ���ǥ�ÿ� ������ ���ú��� �׸� 
                    for (j = 0; j < 4; j++) {
                        if (org_blocks[b_type_next][0][i][j] == 1) {
                            gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                            printf("��");
                        }
                        else {
                            gotoxy(STATUS_X_ADJ + 2 + j, i + 6);
                            printf("  ");
                        }
                    }
                }
                item2_on = 0;
            }
            else {
                no_allow_item();
                item2_on = 0;
            }

        }

        else { //����Ű�� �ƴѰ�� 
            switch (key) {

            case SPACE: //�����̽�Ű �������� 
                space_key_on = 1; //�����̽�Ű flag�� ��� 
                while (crush_on == 0) { //�ٴڿ� ���������� �̵���Ŵ 
                    drop_block();
                    score += level; // hard drop ���ʽ�
                    gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score); //���� ǥ��  
                }
                break;
            case P: //P(�빮��) �������� 
            case p: //p(�ҹ���) �������� 
                pause(); //�Ͻ����� 
                break;
            case B:
            case b:
                if (item[1] > 0) {
                    item[1] -= 1;
                    is_clicked = 1;
                    direct_draw();
                }

                else {
                    no_allow_item();
                }
                break;
            case ESC: //ESC�������� 
                system("cls"); //ȭ���� ����� 
                exit(0); //�������� 
            }
        }
    }
    while (_kbhit()) _getch(); //Ű���۸� ��� 
}

void drop_block(void) {
    int i, j;

    int sum = 2;

    if (crush_on && check_crush(bx, by + 1, b_rotation) == true) crush_on = 0; //���� ��������� crush flag �� 
    if (crush_on && check_crush(bx, by + 1, b_rotation) == false) { //���� ��������ʰ� crush flag�� ���������� 
        for (i = 0; i < MAIN_Y; i++) { //���� �������� ���� ���� 
            for (j = 0; j < MAIN_X; j++) {
                if (main_org[i][j] == ACTIVE_BLOCK) main_org[i][j] = INACTIVE_BLOCK;
            }
        }
        crush_on = 0; //flag�� �� 
        check_line(); //����üũ�� �� 
        new_block_on = 1; //���ο� ������ flag�� ��    
        return; //�Լ� ���� 
    }
    if (check_crush(bx, by + 1, b_rotation) == true) move_block(DOWN); //���� ��������� ������ ��ĭ �̵� 
    if (check_crush(bx, by + 1, b_rotation) == false) {
        crush_on++;
        if (b_type == 7) {
            is_clicked = 0;

            for (i = 3; i < MAIN_Y - 1; i++) {
                if (main_org[i][bx + 1] == INACTIVE_BLOCK) {
                    sum += 1;
                }
            }

            for (i = MAIN_Y - sum - 2; i > 3; i--) {
                main_org[i][bx + 1] = 0;
            }

            for (i = MAIN_Y - 2; i > MAIN_Y - sum - 2; i--) {
                main_org[i][bx + 1] = 2;
            }

            draw_main();
            new_block_on = 1;
            return;
        }
    }//������ �̵��� �ȵǸ�  crush flag�� ��
}

int check_crush(int bx, int by, int b_rotation) { //������ ��ǥ�� ȸ�������� �浹�� �ִ��� �˻� 
    int i, j;

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) { //������ ��ġ�� �����ǰ� ������� ���ؼ� ��ġ�� false�� ���� 
            if (blocks[b_type][b_rotation][i][j] == 1 && main_org[by + i][bx + j] > 0) return false;
        }
    }
    return true; //�ϳ��� �Ȱ�ġ�� true���� 
};

void move_block(int dir) { //����� �̵���Ŵ 
    int i, j;

    switch (dir) {
    case LEFT: //���ʹ��� 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) { //�������� ��ĭ���� active block�� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j - 1] = ACTIVE_BLOCK;
            }
        }
        bx--; //��ǥ�� �̵� 
        break;

    case RIGHT:    //������ ����. ���ʹ����̶� ���� ������ ���� 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j + 1] = ACTIVE_BLOCK;
            }
        }
        bx++;
        break;

    case DOWN:    //�Ʒ��� ����. ���ʹ����̶� ���� ������ ����
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i + 1][bx + j] = ACTIVE_BLOCK;
            }
        }
        by++;
        break;

    case UP: //Ű���� ���� �������� ȸ����Ŵ. 
        for (i = 0; i < 4; i++) { //������ǥ�� ���� ����  
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4; //ȸ������ 1������Ŵ(3���� 4�� �Ǵ� ���� 0���� �ǵ���) 
        for (i = 0; i < 4; i++) { //ȸ���� ����� ���� 
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = ACTIVE_BLOCK;
            }
        }
        break;

    case 100: //����� �ٴ�, Ȥ�� �ٸ� ��ϰ� ���� ���¿��� ��ĭ���� �÷� ȸ���� ������ ��� 
        //�̸� ���۽�Ű�� Ư������ 
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i][bx + j] = EMPTY;
            }
        }
        b_rotation = (b_rotation + 1) % 4;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < 4; j++) {
                if (blocks[b_type][b_rotation][i][j] == 1) main_org[by + i - 1][bx + j] = ACTIVE_BLOCK;
            }
        }
        by--;
        break;
    }
}

void check_line(void) {
    int i, j, k, l;

    int    block_amount; //������ ��ϰ����� �����ϴ� ���� 
    int combo = 0; //�޺����� �����ϴ� ���� ������ �ʱ�ȭ 

    for (i = MAIN_Y - 2; i > 3;) { //i=MAIN_Y-2 : ���ʺ��� ��ĭ����,  i>3 : õ��(3)�Ʒ����� �˻� 
        block_amount = 0; //��ϰ��� ���� ���� �ʱ�ȭ 
        for (j = 1; j < MAIN_X - 1; j++) { //���� �������� ��ϰ��縦 �� 
            if (main_org[i][j] > 0) block_amount++;
        }
        if (block_amount == MAIN_X - 2) { //����� ���� �� ��� 
            if (level_up_on == 0) { //���������°� �ƴ� ��쿡(�������� �Ǹ� �ڵ� �ٻ����� ����) 
                score += 100 * level; //�����߰� 
                cnt++; //���� �� ���� ī��Ʈ ���� 
                combo++; //�޺��� ����  
            }
            for (k = i; k > 1; k--) { //������ ��ĭ�� ��� ����(������ õ���� �ƴ� ��쿡��) 
                for (l = 1; l < MAIN_X - 1; l++) {
                    if (main_org[k - 1][l] != CEILLING) main_org[k][l] = main_org[k - 1][l];
                    if (main_org[k - 1][l] == CEILLING) main_org[k][l] = EMPTY;
                    //������ õ���� ��쿡�� õ���� ��ĭ ������ �ȵǴϱ� ��ĭ�� ���� 
                }
            }
        }
        else i--;
    }
    if (combo) { //�� ������ �ִ� ��� ������ ���� ��ǥ�� ���� ǥ����  
        if (combo > 1) { //2�޺��̻��� ��� ��� ���ʽ��� �޼����� �����ǿ� ����ٰ� ���� 
            //gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 1, MAIN_Y_ADJ + by - 2); printf("%d COMBO!", combo);
            //Sleep(500);
            if (item0_on == 1) // ���� �ι� ������ on �϶� combo ���� �ι�
            {
                score += (combo * level * 200);
            }
            else
            {
                score += (combo * level * 100);// ���� (����) combo ����+..
            }
            coin += combo;//�޺� �� ���� ����
            gotoxy(STATUS_X_ADJ, 3 + 14); printf(" YOUR COIN :");
            gotoxy(STATUS_X_ADJ, 3 + 15); printf("        %6d", coin);
            //reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
            //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 
        }
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", (cnt <= 10) ? 10 - cnt : 0);
        gotoxy(STATUS_X_ADJ, STATUS_Y_SCORE); printf("        %6d", score);
    }
}

void check_level_up(void) {
    int i, j;

    if (cnt >= 10) { //�������� 10�پ� ���־���. 10���̻� ���� ��� 
        draw_main();
        level_up_on = 1; //������ flag�� ��� 
        level += 1; //������ 1 �ø� 
        cnt = 0; //���� �ټ� �ʱ�ȭ   

        for (i = 0; i < 4; i++) {
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("             ");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("             ");
            Sleep(200);

            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 3, MAIN_Y_ADJ + 4);
            printf("��LEVEL UP!��");
            gotoxy(MAIN_X_ADJ + (MAIN_X / 2) - 2, MAIN_Y_ADJ + 6);
            printf("��SPEED UP!��");
            Sleep(200);
        }
        reset_main_cpy(); //�ؽ�Ʈ�� ����� ���� main_cpy�� �ʱ�ȭ.
        //(main_cpy�� main_org�� ���� �ٸ��Ƿ� ������ draw()ȣ��� ������ ��ü�� ���� �׸��� ��) 

        for (i = MAIN_Y - 2; i > MAIN_Y - 2 - (level - 1); i--) { //�������������� �� ����-1�� ����ŭ �Ʒ��� ���� ������ 
            for (j = 1; j < MAIN_X - 1; j++) {
                main_org[i][j] = INACTIVE_BLOCK; // ���� ������� ��� ä��� 
                gotoxy(MAIN_X_ADJ + j, MAIN_Y_ADJ + i); // ���� �����.. �̻����̰� 
                printf("��");
                Sleep(20);
            }
        }
        Sleep(100); //�������� �����ֱ� ���� delay 
        check_line(); //������� ��� ä��� �����
        //.check_line()�Լ� ���ο��� level up flag�� �����ִ� ��� ������ ����.         
        switch (level) { //�������� �ӵ��� ��������. 
        case 2:
            speed = 50;
            break;
        case 3:
            speed = 25;
            break;
        case 4:
            speed = 10;
            break;
        case 5:
            speed = 5;
            break;
        case 6:
            speed = 4;
            break;
        case 7:
            speed = 3;
            break;
        case 8:
            speed = 2;
            break;
        case 9:
            speed = 1;
            break;
        case 10:
            speed = 0;
            break;
        }
        level_up_on = 0; //������ flag����

        gotoxy(STATUS_X_ADJ, STATUS_Y_LEVEL); printf(" LEVEL : %5d", level); //����ǥ�� 
        gotoxy(STATUS_X_ADJ, STATUS_Y_GOAL); printf(" GOAL  : %5d", 10 - cnt); // ������ǥ ǥ�� 

    }
}

void check_game_over(void) {
    int i;

    int x = 5;
    int y = 5;

    for (i = 1; i < MAIN_X - 2; i++) {
        if (main_org[3][i] > 0) { //õ��(������ ����° ��)�� inactive�� �����Ǹ� ���� ���� 
            gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�"); //���ӿ��� �޼��� 
            gotoxy(x, y + 1); printf("��                              ��");
            gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 3); printf("��  |  G A M E  O V E R..   |   ��");
            gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
            gotoxy(x, y + 5); printf("��   YOUR SCORE: %6d         ��", score);
            gotoxy(x, y + 6); printf("��                              ��");
            gotoxy(x, y + 7); printf("��  Press any key to restart..  ��");
            gotoxy(x, y + 8); printf("��                              ��");
            gotoxy(x, y + 9); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
            last_score = score; //���������� �ű� 
            strcpy(last_name, name);

            if (score > score1) //1�� ���Ž� 
            {
                FILE* sfile3 = fopen("score3.dat", "wt"); //score3.dat�� ���� ����                

                if (sfile3 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"score3.dat\"");
                }
                else {
                    fprintf(sfile3, "%d", score2);
                    fclose(sfile3);
                }

                FILE* nfile3 = fopen("name3.dat", "wt");

                gotoxy(x, y + 6); printf("��   �ڡڡ� 3RD SCORE! �ڡڡ�   ��  ");
                gotoxy(x, y + 7); printf("��  %11s's %d          ��  ", name, score);

                if (nfile3 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST NAME ON \"name3.dat\"");
                }
                else {
                    fprintf(nfile3, "%s", name2);
                    fclose(nfile3);
                }

                FILE* sfile2 = fopen("score2.dat", "wt"); //score2.dat�� ���� ����                
                if (sfile2 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"score2.dat\"");
                }
                else {
                    fprintf(sfile2, "%d", score1);
                    fclose(sfile2);
                }

                FILE* nfile2 = fopen("name2.dat", "wt");
                if (nfile2 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST NAME ON \"name2.dat\"");
                }
                else {
                    fprintf(nfile2, "%s", name1);
                    fclose(nfile2);
                }

                FILE* sfile1 = fopen("score1.dat", "wt"); //score1.dat�� ���� ����                
                if (sfile1 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"score1.dat\"");
                }
                else {
                    fprintf(sfile1, "%d", score);
                    fclose(sfile1);
                }

                FILE* nfile1 = fopen("name1.dat", "wt");
                gotoxy(x, y + 6); printf("��  �ڡڡ� BEST SCORE! �ڡڡ�   ��  ");
                gotoxy(x, y + 7); printf("��  %11s's %d          ��  ", name, score);

                if (nfile1 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST NAME ON \"name1.dat\"");
                }
                else {
                    fprintf(nfile1, "%s", name);
                    fclose(nfile1);
                }
            }
            else if (score > score2 && score < score1) //2�� ���Ž�
            {
                FILE* sfile3 = fopen("score3.dat", "wt"); //score3.dat�� ���� ����                
                if (sfile3 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"score3.dat\"");
                }
                else {
                    fprintf(sfile3, "%d", score2);
                    fclose(sfile3);
                }

                FILE* nfile3 = fopen("name3.dat", "wt");
                if (nfile3 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST NAME ON \"name3.dat\"");
                }
                else {
                    fprintf(nfile3, "%s", name2);
                    fclose(nfile3);
                }

                FILE* sfile2 = fopen("score2.dat", "wt"); //score2.dat�� ���� ����                
                if (sfile2 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"score2.dat\"");
                }
                else {
                    fprintf(sfile2, "%d", score);
                    fclose(sfile2);
                }

                FILE* nfile2 = fopen("name2.dat", "wt");
                gotoxy(x, y + 6); printf("��   �ڡڡ� 2ND SCORE! �ڡڡ�   ��  ");
                gotoxy(x, y + 7); printf("��  %11s's %d          ��  ", name, score);

                if (nfile2 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST NAME ON \"name2.dat\"");
                }
                else {
                    fprintf(nfile2, "%s", name);
                    fclose(nfile2);
                }
            }
            else if (score > score3 && score < score2) //3�� ���Ž�
            {
                FILE* sfile3 = fopen("score3.dat", "wt"); //score3.dat�� ���� ����                

                if (sfile3 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"score3.dat\"");
                }
                else {
                    fprintf(sfile3, "%d", score);
                    fclose(sfile3);
                }

                FILE* nfile3 = fopen("name3.dat", "wt");

                gotoxy(x, y + 6); printf("��   �ڡڡ� 3RD SCORE! �ڡڡ�   ��  ");
                gotoxy(x, y + 7); printf("��  %11s's %d          ��  ", name, score);

                if (nfile3 == 0) { //���� �����޼���  
                    gotoxy(0, 0);
                    printf("FILE ERROR: SYSTEM CANNOT WRITE BEST NAME ON \"name3.dat\"");
                }
                else {
                    fprintf(nfile3, "%s", name);
                    fclose(nfile3);
                }
            }

            FILE* Rcoin = fopen("coin.dat", "rt"); // coin.dat������ ����
            if (Rcoin == 0) { old_coin += coin; }
            else {
                fscanf(Rcoin, "%d", &old_coin); // ������ ������ ������ �ҷ��� 
                fclose(Rcoin); //���� ���� 
            }
            FILE* Wcoin = fopen("coin.dat", "wt"); //coin.dat�� ���� ����                

            if (Wcoin == 0) { //���� �����޼���  
                gotoxy(0, 0);
                printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"coin.dat\"");
            }
            else {
                fprintf(Wcoin, "%d", old_coin + coin);
                fclose(Wcoin);
            }

            FILE* Ritem0 = fopen("item0.dat", "rt"); // item0.dat������ ����
            if (Ritem0 == 0) { old_item[0] += item[0]; }
            else {
                fscanf(Ritem0, "%d", &old_item[0]); // ������ ������ ������0�� �ҷ��� 
                fclose(Ritem0); //���� ���� 
            }
            FILE* Witem0 = fopen("item0.dat", "wt"); //item0.dat�� ���� ����                

            if (Witem0 == 0) { //���� �����޼���  
                gotoxy(0, 0);
                printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"item0.dat\"");
            }
            else {
                fprintf(Witem0, "%d", old_item[0] + item[0]);
                fclose(Witem0);
            }

            FILE* Ritem1 = fopen("item1.dat", "rt"); // item1.dat������ ����
            if (Ritem1 == 0) { old_item[1] += item[1]; }
            else {
                fscanf(Ritem1, "%d", &old_item[1]); // ������ ������ ������1�� �ҷ��� 
                fclose(Ritem1); //���� ���� 
            }
            FILE* Witem1 = fopen("item1.dat", "wt"); //item1.dat�� ���� ����                

            if (Witem1 == 0) { //���� �����޼���  
                gotoxy(0, 0);
                printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"item1.dat\"");
            }
            else {
                fprintf(Witem1, "%d", old_item[1] + item[1]);
                fclose(Witem1);
            }

            FILE* Ritem2 = fopen("item2.dat", "rt"); // item2.dat������ ����
            if (Ritem2 == 0) { old_item[2] += item[2]; }
            else {
                fscanf(Ritem2, "%d", &old_item[2]); // ������ ������ ������2�� �ҷ��� 
                fclose(Ritem2); //���� ���� 
            }
            FILE* Witem2 = fopen("item2.dat", "wt"); //item2.dat�� ���� ����                

            if (Witem2 == 0) { //���� �����޼���  
                gotoxy(0, 0);
                printf("FILE ERROR: SYSTEM CANNOT WRITE BEST SCORE ON \"item2.dat\"");
            }
            else {
                fprintf(Witem2, "%d", old_item[2] + item[2]);
                fclose(Witem2);
            }

            Sleep(1000);
            while (_kbhit()) _getch();
            key = _getch();
            main();
        }
    }
}

void item0() //���� �ι� ������
{
    item0_on = 1;
    old_count = count;
    gotoxy(STATUS_X_ADJ + 7, 13); printf(" !!double score item in use!!");
}

void pause(void) { //���� �Ͻ����� �Լ� 
    int i, j;

    int x = 5;
    int y = 5;

    for (i = 1; i < MAIN_X - 2; i++) { //���� �Ͻ����� �޼��� 
        gotoxy(x, y + 0); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
        gotoxy(x, y + 1); printf("��                              ��");
        gotoxy(x, y + 2); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 3); printf("��  |       P A U S E       |   ��");
        gotoxy(x, y + 4); printf("��  +-----------------------+   ��");
        gotoxy(x, y + 5); printf("��  Press any key to resume..   ��");
        gotoxy(x, y + 6); printf("��                              ��");
        gotoxy(x, y + 7); printf("�ǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢǢ�");
    }
    _getch(); //Ű�Է½ñ��� ��� 

    system("cls"); //ȭ�� ����� ���� �׸� 
    reset_main_cpy();
    draw_main();
    draw_map();

    for (i = 1; i < 3; i++) { // ������� �׸� 
        for (j = 0; j < 4; j++) {
            if (blocks[b_type_next][0][i][j] == 1) {
                gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
                textcolor(block_color[b_type_next]);
                printf("��");
                textcolor(15);
            }
            else {
                gotoxy(MAIN_X + MAIN_X_ADJ + 3 + j, i + 6);
                printf("  ");
            }
        }
    }
} //��! 