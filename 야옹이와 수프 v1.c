#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <windows.h> 

#define ROOM_WIDTH 10
#define HME_POS 1 
#define BWL_POS (ROOM_WIDTH - 2)

void print_status(int soup_count, int intimacy); // 1-2 ���� ���
void handle_interaction(int* intimacy, char* name); // 1-3 ��ȣ�ۿ�
void draw_room(int cat_pos, int prev_pos); // 1-4 �� �׸���
void auto_move_cat(int intimacy, int* cat_pos, int* prev_pos, char* name); // 1-5 �̵�
void check_soup(int cat_pos, int* soup_count, char* name); // 1-6 �ൿ (����)

int main(void) {
    // ���� �� �ʱ�ȭ (������ ������ �ٸ� ������)
    srand((unsigned int)time(NULL)); 
    int soup_count = 0;
    int intimacy = 2;
    int cat_pos = ROOM_WIDTH / 2;
    int prev_pos = cat_pos;
    int keep_going = 1; // ���� ���� ������� �����ϴ� �÷���
    char name[20];

    // 1-1 ��Ʈ��&�غ� (ascii art + �̸� �Է�)
    printf("****�߿��̿� ����****\n\n");
    printf(" /\\_/\\  \n");
    printf("( o.o ) \n");
    printf(" > ^ <  \n\n");

    printf("�߿����� �̸��� ���� �ּ���: ");
    scanf_s("%s", name, 20);
    printf("�߿����� �̸��� %s�Դϴ�.\n", name);
    Sleep(1000);
    system("cls");

    // ���� ���� ���� ( 1-2 ~ 1-6 )
    while (keep_going) {
        print_status(soup_count, intimacy); // 1-2 ���� ���
        Sleep(500);
        handle_interaction(&intimacy, name); // 1-3 ��ȣ�ۿ�
        Sleep(500);
        auto_move_cat(intimacy, &cat_pos, &prev_pos, name); // 1-5 �̵�
        Sleep(500);
        draw_room(cat_pos, prev_pos); // 1-4 �� �׸���
        Sleep(500);
        check_soup(cat_pos, &soup_count, name); // 1-6 �ൿ (���� Ȯ�� �� ����)
        Sleep(2500); 
        system("cls");
    }
    return 0;
}

// 1-2 ���� ���
void print_status(int soup_count, int intimacy) {
    printf("==================== ���� ���� ===================\n");
    printf("������� ���� ����: %d��\n", soup_count);
    printf("������� ����(0~4): %d\n", intimacy);

    switch (intimacy) {
    case 0:
        printf("�翡 ���� ������ �Ⱦ��մϴ�.\n");
        break;
    case 1:
        printf("���� ���Ǳ� ����Դϴ�.\n");
        break;
    case 2:
        printf("�׷����� �� ���� �����Դϴ�.\n");
        break;
    case 3:
        printf("�Ǹ��� ����� ���� �ް� �ֽ��ϴ�.\n");
        break;
    case 4:
        printf("���� �������Դϴ�.\n");
        break;
    }
    printf("==================================================\n");
}

// 1-3 ��ȣ�ۿ�
void handle_interaction(int* intimacy, char* name) {
    int input;
    int dice;

    printf("� ��ȣ�ۿ��� �Ͻðڽ��ϱ�?   0. �ƹ��͵� ���� ����  1. �ܾ� �ֱ�\n>> ");

    while (1) {
        if (scanf_s("%d", &input) != 1) {
            printf(">> ");

            while (getchar() != '\n'); 
            Sleep(500);
            continue;
        }

        if (input == 0 || input == 1)
            break; 
        printf(">> ");
        Sleep(500);
    }

    dice = rand() % 6 + 1;

    if (input == 0) {
        printf("�ƹ��͵� ���� �ʽ��ϴ�.\n");
        printf("4/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
        printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
        printf("%d��(��) ���Խ��ϴ�!\n", dice);

        if (dice <= 4) {
            if (*intimacy > 0) (*intimacy)--;
            printf("ģ�е��� �������ϴ�.\n");
            printf("���� ģ�е�: %d\n", *intimacy);
        }
        else {
            printf("������ ģ�е��� �������� �ʾҽ��ϴ�.\n");
            printf("���� ģ�е�: %d\n", *intimacy);
        }
    }
    else if (input == 1) {
        printf("%s�� ���� �ܾ��־����ϴ�.\n", name);
        printf("2/6�� Ȯ���� ģ�е��� �������ϴ�.\n");
        printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
        printf("%d��(��) ���Խ��ϴ�!\n", dice);
        if (dice >= 5) {
            if (*intimacy < 4) (*intimacy)++;
            printf("ģ�е��� �������ϴ�.\n");
            printf("���� ģ�е�: %d\n", *intimacy);

        }
        else {
            printf("ģ�е��� �״���Դϴ�.\n");
            printf("���� ģ�е�: %d\n", *intimacy);
        }
    }
}

// 1-4 �� �׸���
void draw_room(int cat_pos, int prev_pos) {
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n#");

    for (int i = 1; i < ROOM_WIDTH - 1; i++) {
        if (i == HME_POS) printf("H");
        else if (i == BWL_POS) printf("B");
        else printf(" ");
    }

    printf("#\n#");

    for (int i = 1; i < ROOM_WIDTH - 1; i++) {
        if (i == cat_pos) {
            printf("C");
        }
        else if (i == prev_pos && prev_pos != cat_pos) {
            printf(".");
        }
        else {
            printf(" ");
        }
    }

    printf("#\n");
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");
    printf("\n");
}

// 1-5 �̵�
void auto_move_cat(int intimacy, int* cat_pos, int* prev_pos, char* name) {
    int dice = rand() % 6 + 1;
    int threshold = 6 - intimacy;

    printf("%s �̵�: ����� ģ���Ҽ��� ���� ������ �� Ȯ���� �������ϴ�.\n", name);
    printf("�ֻ��� ���� %d �̻��̸� ���� ������ �̵��մϴ�.\n", threshold);
    printf("�ֻ����� �����ϴ�. �Ǹ���...\n");
    printf("%d��(��) ���Խ��ϴ�!\n", dice);

    *prev_pos = *cat_pos;
    if (dice >= threshold) {
        if (*cat_pos < ROOM_WIDTH - 2) {
            (*cat_pos)++;
            printf("���� ������ �� ĭ �̵��մϴ�.\n");
        }
        else {
            printf("������ ���� ���� �̵����� ���߽��ϴ�.\n");
        }
    }
    else {
        if (*cat_pos > 1) {
            (*cat_pos)--;
            printf("�� ������ �� ĭ �̵��մϴ�.\n");
        }
        else {
            printf("���� ���� ���� �̵����� ���߽��ϴ�.\n");
        }
    }

    if (*cat_pos == HME_POS) {
        printf("%s��(��) �ڽ��� ������ ������� �����ϴ�.\n", name);
    }
}

// 1-6 �ൿ (���� Ȯ�� �� ����)
void check_soup(int cat_pos, int* soup_count, char* name) {
    if (cat_pos == ROOM_WIDTH - 2) {
        int type = rand() % 3;
        switch (type) {
        case 0:
            printf("%s�� ���� ������ ��������ϴ�!\n", name);
            break;
        case 1:
            printf("%s�� ����� ������ ��������ϴ�!\n", name);
            break;
        case 2:
            printf("%s�� ����ݸ� ������ ��������ϴ�!\n", name);
            break;
        }

        (*soup_count)++;
        printf("������� ���� ����: %d��\n", *soup_count);
    }
}