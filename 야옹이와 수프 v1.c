#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <windows.h> 

#define ROOM_WIDTH 10
#define HME_POS 1 
#define BWL_POS (ROOM_WIDTH - 2)

void print_status(int soup_count, int intimacy); // 1-2 상태 출력
void handle_interaction(int* intimacy, char* name); // 1-3 상호작용
void draw_room(int cat_pos, int prev_pos); // 1-4 방 그리기
void auto_move_cat(int intimacy, int* cat_pos, int* prev_pos, char* name); // 1-5 이동
void check_soup(int cat_pos, int* soup_count, char* name); // 1-6 행동 (수프)

int main(void) {
    // 랜덤 값 초기화 (실행할 때마다 다른 랜덤값)
    srand((unsigned int)time(NULL)); 
    int soup_count = 0;
    int intimacy = 2;
    int cat_pos = ROOM_WIDTH / 2;
    int prev_pos = cat_pos;
    int keep_going = 1; // 게임 루프 계속할지 결정하는 플래그
    char name[20];

    // 1-1 인트로&준비 (ascii art + 이름 입력)
    printf("****야옹이와 수프****\n\n");
    printf(" /\\_/\\  \n");
    printf("( o.o ) \n");
    printf(" > ^ <  \n\n");

    printf("야옹이의 이름을 지어 주세요: ");
    scanf_s("%s", name, 20);
    printf("야옹이의 이름은 %s입니다.\n", name);
    Sleep(1000);
    system("cls");

    // 게임 메인 루프 ( 1-2 ~ 1-6 )
    while (keep_going) {
        print_status(soup_count, intimacy); // 1-2 상태 출력
        Sleep(500);
        handle_interaction(&intimacy, name); // 1-3 상호작용
        Sleep(500);
        auto_move_cat(intimacy, &cat_pos, &prev_pos, name); // 1-5 이동
        Sleep(500);
        draw_room(cat_pos, prev_pos); // 1-4 방 그리기
        Sleep(500);
        check_soup(cat_pos, &soup_count, name); // 1-6 행동 (수프 확인 및 생성)
        Sleep(2500); 
        system("cls");
    }
    return 0;
}

// 1-2 상태 출력
void print_status(int soup_count, int intimacy) {
    printf("==================== 현재 상태 ===================\n");
    printf("현재까지 만든 수프: %d개\n", soup_count);
    printf("집사와의 관계(0~4): %d\n", intimacy);

    switch (intimacy) {
    case 0:
        printf("곁에 오는 것조차 싫어합니다.\n");
        break;
    case 1:
        printf("간식 자판기 취급입니다.\n");
        break;
    case 2:
        printf("그럭저럭 쓸 만한 집사입니다.\n");
        break;
    case 3:
        printf("훌륭한 집사로 인정 받고 있습니다.\n");
        break;
    case 4:
        printf("집사 껌딱지입니다.\n");
        break;
    }
    printf("==================================================\n");
}

// 1-3 상호작용
void handle_interaction(int* intimacy, char* name) {
    int input;
    int dice;

    printf("어떤 상호작용을 하시겠습니까?   0. 아무것도 하지 않음  1. 긁어 주기\n>> ");

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
        printf("아무것도 하지 않습니다.\n");
        printf("4/6의 확률로 친밀도가 떨어집니다.\n");
        printf("주사위를 굴립니다. 또르륵...\n");
        printf("%d이(가) 나왔습니다!\n", dice);

        if (dice <= 4) {
            if (*intimacy > 0) (*intimacy)--;
            printf("친밀도가 떨어집니다.\n");
            printf("현재 친밀도: %d\n", *intimacy);
        }
        else {
            printf("다행히 친밀도가 떨어지지 않았습니다.\n");
            printf("현재 친밀도: %d\n", *intimacy);
        }
    }
    else if (input == 1) {
        printf("%s의 턱을 긁어주었습니다.\n", name);
        printf("2/6의 확률로 친밀도가 높아집니다.\n");
        printf("주사위를 굴립니다. 또르륵...\n");
        printf("%d이(가) 나왔습니다!\n", dice);
        if (dice >= 5) {
            if (*intimacy < 4) (*intimacy)++;
            printf("친밀도는 높아집니다.\n");
            printf("현재 친밀도: %d\n", *intimacy);

        }
        else {
            printf("친밀도는 그대로입니다.\n");
            printf("현재 친밀도: %d\n", *intimacy);
        }
    }
}

// 1-4 방 그리기
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

// 1-5 이동
void auto_move_cat(int intimacy, int* cat_pos, int* prev_pos, char* name) {
    int dice = rand() % 6 + 1;
    int threshold = 6 - intimacy;

    printf("%s 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n", name);
    printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", threshold);
    printf("주사위를 굴립니다. 또르륵...\n");
    printf("%d이(가) 나왔습니다!\n", dice);

    *prev_pos = *cat_pos;
    if (dice >= threshold) {
        if (*cat_pos < ROOM_WIDTH - 2) {
            (*cat_pos)++;
            printf("냄비 쪽으로 한 칸 이동합니다.\n");
        }
        else {
            printf("오른쪽 벽에 막혀 이동하지 못했습니다.\n");
        }
    }
    else {
        if (*cat_pos > 1) {
            (*cat_pos)--;
            printf("집 쪽으로 한 칸 이동합니다.\n");
        }
        else {
            printf("왼쪽 벽에 막혀 이동하지 못했습니다.\n");
        }
    }

    if (*cat_pos == HME_POS) {
        printf("%s은(는) 자신의 집에서 편안함을 느낍니다.\n", name);
    }
}

// 1-6 행동 (수프 확인 및 생성)
void check_soup(int cat_pos, int* soup_count, char* name) {
    if (cat_pos == ROOM_WIDTH - 2) {
        int type = rand() % 3;
        switch (type) {
        case 0:
            printf("%s가 감자 수프를 만들었습니다!\n", name);
            break;
        case 1:
            printf("%s가 양송이 수프를 만들었습니다!\n", name);
            break;
        case 2:
            printf("%s가 브로콜리 수프를 만들었습니다!\n", name);
            break;
        }

        (*soup_count)++;
        printf("현재까지 만든 수프: %d개\n", *soup_count);
    }
}