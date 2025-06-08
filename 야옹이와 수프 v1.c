#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <windows.h> 

#define ROOM_WIDTH 10
#define HME_POS 1 
#define BWL_POS (ROOM_WIDTH - 2)

int soup_count = 0;
int intimacy = 2;
int cat_pos = ROOM_WIDTH / 2;
int prev_pos = ROOM_WIDTH / 2;
int CP = 0;
int mood = 3;

void print_status(void); // 1-2 상태 출력
void handle_interaction(void); // 1-3 상호작용
void draw_room(void); // 1-4 방 그리기
void auto_move_cat(void); // 1-5 이동
void check_soup(void); // 1-6 행동 (수프)

int main(void) {
    // 랜덤 값 초기화 (실행할 때마다 다른 랜덤값)
    srand((unsigned int)time(NULL)); 
    int keep_going = 1; // 게임 루프 계속할지 결정하는 플래그

    // 1-1 인트로&준비 (ascii art + 이름 입력)
    printf("****야옹이와 수프****\n\n");
    printf(" /\\_/\\  \n");
    printf("( o.o ) \n");
    printf(" > ^ <  \n\n");

    printf("쫀떡이가 식빵을 굽고 있습니다.");
    Sleep(1000);
    system("cls");

    // 게임 메인 루프 ( 1-2 ~ 1-6 )
    while (keep_going) {
        print_status(); // 1-2 상태 출력
        Sleep(500);
        handle_interaction(); // 1-3 상호작용
        Sleep(500);
        auto_move_cat(); // 1-5 이동
        Sleep(500);
        draw_room(); // 1-4 방 그리기
        Sleep(500);
        check_soup(); // 1-6 행동 (수프 확인 및 생성)
        Sleep(2500); 
        system("cls");
    }
    return 0;
}

// 1-2 상태 출력
void print_status(void) {
    printf("==================== 현재 상태 ===================\n");
    printf("현재까지 만든 수프: %d개\n", soup_count);
    printf("CP: %d포인트\n", CP);
    printf("쫀떡이 기분(0~3): %d\n", mood);

    switch (mood) {
    case 0:
        printf("기분이 매우 나쁩니다.\n");
        break;
    case 1:
        printf("심심해합니다.\n");
        break;
    case 2:
        printf("식빵을 굽습니다.\n");
        break;
    case 3:
        printf("골골송을 부릅니다.\n");
        break;
    }

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
void handle_interaction(void) {
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
            if (intimacy > 0) intimacy--;
            printf("친밀도가 떨어집니다.\n");
            printf("현재 친밀도: %d\n", intimacy);
        }
        else {
            printf("다행히 친밀도가 떨어지지 않았습니다.\n");
            printf("현재 친밀도: %d\n", intimacy);
        }
    }
    else if (input == 1) {
        printf("쫀떡이의 턱을 긁어주었습니다.\n");
        printf("2/6의 확률로 친밀도가 높아집니다.\n");
        printf("주사위를 굴립니다. 또르륵...\n");
        printf("%d이(가) 나왔습니다!\n", dice);
        if (dice >= 5) {
            if (intimacy < 4) intimacy++;
            printf("친밀도는 높아집니다.\n");
            printf("현재 친밀도: %d\n", intimacy);

        }
        else {
            printf("친밀도는 그대로입니다.\n");
            printf("현재 친밀도: %d\n", intimacy);
        }
    }
}

// 1-4 방 그리기
void draw_room(void) {
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
void auto_move_cat(void) {
    int dice = rand() % 6 + 1;
    int threshold = 6 - intimacy;

    printf("쫀떡 이동: 집사와 친밀할수록 냄비 쪽으로 갈 확률이 높아집니다.\n");
    printf("주사위 눈이 %d 이상이면 냄비 쪽으로 이동합니다.\n", threshold);
    printf("주사위를 굴립니다. 또르륵...\n");
    printf("%d이(가) 나왔습니다!\n", dice);

    prev_pos = cat_pos;
    if (dice >= threshold) {
        if (cat_pos < ROOM_WIDTH - 2) {
            cat_pos++;
            printf("냄비 쪽으로 한 칸 이동합니다.\n");
        }
        else {
            printf("오른쪽 벽에 막혀 이동하지 못했습니다.\n");
        }
    }
    else {
        if (cat_pos > 1) {
            cat_pos--;
            printf("집 쪽으로 한 칸 이동합니다.\n");
        }
        else {
            printf("왼쪽 벽에 막혀 이동하지 못했습니다.\n");
        }
    }

    if (cat_pos == HME_POS) {
        printf("쫀떡이는 자신의 집에서 편안함을 느낍니다.\n");
    }
}

// 1-6 행동 (수프 확인 및 생성)
void check_soup(void) {
    if (cat_pos == ROOM_WIDTH - 2) {
        int type = rand() % 3;
        switch (type) {
        case 0:
            printf("쫀떡이가 감자 수프를 만들었습니다!\n");
            break;
        case 1:
            printf("쫀떡이가 양송이 수프를 만들었습니다!\n");
            break;
        case 2:
            printf("쫀떡이가 브로콜리 수프를 만들었습니다!\n");
            break;
        }

        soup_count++;
        printf("현재까지 만든 수프: %d개\n", soup_count);
    }
}