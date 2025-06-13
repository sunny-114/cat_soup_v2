#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
#include <windows.h> 

#define ROOM_WIDTH 14
#define HME_POS 1 
#define BWL_POS (ROOM_WIDTH - 2)

int soup_count = 0;
int intimacy = 2;
int cat_pos = ROOM_WIDTH / 2;
int prev_pos = ROOM_WIDTH / 2;
int CP = 0;
int mood = 3;
int resting_home = 0;
int has_scratcher = 0;
int has_cattower = 0;
int has_mouse_toy = 0;
int has_laser_pointer = 0;
int SCR_POS = -1;
int CAT_POS = -1;
int turn_count = 0;

void print_status(void); 
void feeling_bad(void);
void mood_move(void); 
void check_behavior(void); 
void draw_room(void); 
void handle_interaction(void); 
void product_CP(void); 
void shop_buy (void); 
void surprise_quest(void); 

// 메인루프 & 인트로로
int main(void) {
    srand((unsigned int)time(NULL)); 
    int keep_going = 1; 

    printf("****야옹이와 수프****\n\n");
    printf(" /\\_/\\  \n");
    printf("( o.o ) \n");
    printf(" > ^ <  \n\n");
    printf("쫀떡이가 식빵을 굽고 있습니다.");
    Sleep(1000);
    system("cls");

    while (keep_going) {
        turn_count++;

        print_status(); // 상태 출력
        Sleep(500);
        feeling_bad(); // 기분 나빠짐
        Sleep(500);
        mood_move(); // 이동
        Sleep(500); 
        check_behavior(); // 행동
        Sleep(500);
        draw_room(); // 방 그리기
        Sleep(500);
        handle_interaction(); // 상호작용 & 결과
        Sleep(500);
        product_CP(); // CP 생산
        Sleep(500);
        shop_buy(); // 상점 구매
        Sleep(500);

        if (turn_count == 3) {
            surprise_quest(); // 돌발 퀘스트
        }
        Sleep(2500); 
        system("cls");
    }
    return 0;
}

// 상태 출력
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

// 기분 나빠짐
void feeling_bad(void) {
    int dice = rand() % 6 + 1; 
    int threshold = 6 - intimacy;

    printf("아무 이유 없이 기분이 나빠집니다. 고양이니까?\n");
    printf("6-%d: 주사위 눈이 %d이하이면 그냥 기분이 나빠집니다.\n", intimacy, threshold);
    printf("주사위를 굴립니다. 또르르...\n");
    printf("%d이(가) 나왔습니다.\n", dice);

    if (dice <= threshold && mood > 0) {
        printf("쫀떡이의 기분이 나빠집니다: %d -> %d\n", mood, mood - 1);
        mood--;
    } else {
        printf("쫀떡이의 기분은 그대로입니다: %d\n", mood);
    }
}

// 이동
void mood_move(void) {
    prev_pos = cat_pos;
    
    switch (mood) {
    case 0:
        printf("기분이 매우 나쁜 쫀떡이는 집으로 향합니다.\n");
        if (cat_pos > HME_POS) cat_pos--;
        else if (cat_pos < HME_POS) cat_pos++;
        break;
    case 1:
        if (!has_scratcher && !has_cattower) {
            printf("놀 거리가 없어서 기분이 매우 나빠집니다.\n");
            if (mood > 0) mood--;
            break;
        }
        
        int dist_scratcher = has_scratcher ? abs(cat_pos - SCR_POS) : 999;
        int dist_cattower = has_cattower ? abs(cat_pos - CAT_POS) : 999;

        if (dist_scratcher <= dist_cattower) {
            printf("쫀떡이는 심심해서 스크래처 쪽으로 이동합니다.\n");
            if (cat_pos > SCR_POS) cat_pos--;
            else if (cat_pos < SCR_POS) cat_pos++;
        } else {
            printf("쫀떡이는 심심해서 캣타워 쪽으로 이동합니다.\n");
            if (cat_pos > CAT_POS) cat_pos--;
            else if (cat_pos < CAT_POS) cat_pos++;
        }
        break;
    case 2:
        printf("쫀떡이는 기분좋게 식빵을 굽고 있습니다.\n");
        break;
    case 3:
        printf("쫀떡이는 골골송을 부르며 수프를 만들러 갑니다.\n");
        if (cat_pos > BWL_POS) cat_pos--;
        else if (cat_pos < BWL_POS) cat_pos++;
        break;
    }

    if (cat_pos != HME_POS && prev_pos == HME_POS) {
        resting_home = 0;
    }
    if (cat_pos == HME_POS && prev_pos != HME_POS) {
        resting_home = 1;
    }
}

// 행동
void check_behavior(void) {

    if (cat_pos == HME_POS) {
        if (resting_home == 1) {
            if (prev_pos != HME_POS) {
                printf("쫀떡이는 집에서 쉬려고 합니다.\n");
                resting_home = 2;
            } else if (resting_home == 2) { 
                if (mood < 3) {
                    int prev_mood = mood;
                    mood++;
                    printf("쫀떡이는 집에서 쉽니다.\n");
                    printf("한턴을 쉬어서 기분이 좋아집니다: %d -> %d\n", prev_mood, mood);
                }
            }
        }
    }

    else if (has_scratcher && cat_pos == SCR_POS) {
        printf("쫀떡이는 스크래처를 긁고 놀았습니다.\n");
        if (mood < 3) {
            int prev_mood = mood;
            mood++;
            printf("기분이 조금 좋아졌습니다: %d->%d\n", prev_mood, mood);
        }
    }

    else if (has_cattower && cat_pos == CAT_POS) {
        printf("쫀떡이는 캣타워를 뛰어다닙니다.\n");
        if (mood < 3) {
            int prev_mood = mood;
            mood += 2;
            if (mood > 3) mood = 3;
            printf("기분이 제법 좋아졌습니다: %d->%d\n", prev_mood, mood);
        }
    }

    else if (cat_pos == BWL_POS) {
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

// 방 그리기
void draw_room(void) {
    for (int i = 0; i < ROOM_WIDTH; i++) printf("#");

        printf("\n#");

    for (int i = 1; i < ROOM_WIDTH - 1; i++) {
        if (i == HME_POS) printf("H");
        else if (i == BWL_POS) printf("B");
        else if (i == SCR_POS && has_scratcher) printf("S"); 
        else if (i == CAT_POS && has_cattower) printf("T"); 
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

// 상호작용 & 결과
void handle_interaction(void) {
    int input;
    int dice;
    int option_count = 1; 

    printf("어떤 상호작용을 하시겠습니까?\n");
    printf("  0. 아무것도 하지 않음\n");
    printf("  1. 긁어주기\n");

    if (has_mouse_toy && has_laser_pointer) {
        printf("  2. 장난감 쥐로 놀아주기\n");
        printf("  3. 레이저 포인터로 놀아주기\n");
        option_count = 3;
    } else if (has_mouse_toy) {
        printf("  2. 장난감 쥐로 놀아주기\n");
        option_count = 2;
    } else if (has_laser_pointer) {
        printf("  2. 레이저 포인터로 놀아주기\n");
        option_count = 2;
    }

    while (1) {
        printf(">> ");
        if (scanf_s("%d", &input) != 1) {
            while (getchar() != '\n');
            continue;
        }
        if (input >= 0 && input <= option_count) break;
    }

    dice = rand() % 6 + 1;
    printf("주사위를 굴립니다. 또르륵... %d이(가) 나왔습니다!\n", dice);

    int prev_mood = mood;
    int prev_intimacy = intimacy;

    if (input == 0) { 
        if (mood > 0) mood--;
        printf("쫀떡이의 기분이 나빠졌습니다: %d -> %d\n", prev_mood, mood);

        if (dice <= 5 && intimacy > 0) {
            intimacy--;
            printf("집사와의 관계가 나빠집니다.\n");
        }
    }
    else if (input == 1) { 
        printf("쫀떡이의 기분은 그대로입니다: %d\n", mood);

        if (dice >= 5 && intimacy < 4) {
            intimacy++;
        }
    }
    else if (input == 2) {
        if (has_mouse_toy && has_laser_pointer) {
            printf("장난감 쥐로 쫀떡이와 놀아줬습니다.\n");
            mood++;
            if (mood > 3) mood = 3;
            if (mood < 0) mood = 0;
            printf("쫀떡이의 기분이 조금 좋아졌습니다: %d -> %d\n", prev_mood, mood);

            if (dice >= 4 && intimacy < 4) {
                intimacy++;
            }
        }
        else if (has_mouse_toy) {
            printf("장난감 쥐로 쫀떡이와 놀아줬습니다.\n");
            mood++;
            if (mood > 3) mood = 3;
            if (mood < 0) mood = 0;
            printf("쫀떡이의 기분이 조금 좋아졌습니다: %d -> %d\n", prev_mood, mood);

            if (dice >= 4 && intimacy < 4) {
                intimacy++;
            }
        }
        else if (has_laser_pointer) {
            printf("레이저 포인터로 쫀떡이와 신나게 놀아줬습니다.\n");
            mood += 2;
            if (mood > 3) mood = 3;
            if (mood < 0) mood = 0;
            printf("쫀떡이의 기분이 꽤 좋아졌습니다: %d -> %d\n", prev_mood, mood);

            if (dice >= 2 && intimacy < 4) {
                intimacy++;
            }
        }
    }
    else if (input == 3) { 
        printf("레이저 포인터로 쫀떡이와 신나게 놀아줬습니다.\n");
        mood += 2;
        if (mood > 3) mood = 3;
        if (mood < 0) mood = 0;
        printf("쫀떡이의 기분이 꽤 좋아졌습니다: %d -> %d\n", prev_mood, mood);

        if (dice >= 2 && intimacy < 4) {
            intimacy++;
        }
    }
}

// CP 생산
void product_CP(void) {
    int get_CP = (mood - 1 >= 0 ? mood -1 : 0) + intimacy;

    CP += get_CP;

    printf("쫀떡의 기분(0~3): %d\n", mood);
    printf("집사와의 친밀도(0~4): %d\n", intimacy);
    printf("쫀떡의 기분과 친밀도에 따라서 CP가 %d 포인트 생산되었습니다.\n", get_CP);
    printf("보유 CP: %d 포인트\n", CP);
     
}

// 상점 구매
void shop_buy(void) {
    int choice;

    while (1) {
        printf("상점에서 물건을 살 수 있습니다.\n");
        printf("어떤 물건을 구매할까요?\n");
        printf("0. 아무 것도 사지 않는다.\n");
        printf("1. 장난감 쥐: 1 CP %s\n", has_mouse_toy ? "(품절)" : "");
        printf("2. 레이저 포인터: 2 CP %s\n", has_laser_pointer ? "(품절)" : "");
        printf("3. 스크래처: 4 CP %s\n", has_scratcher ? "(품절)" : "");
        printf("4. 캣 타워: 6 CP %s\n", has_cattower ? "(품절)" : "");
        printf(">> ");
        scanf_s("%d", &choice);

        if (choice < 0 || choice > 4) {
            continue;
        }

        if (choice == 0) {
            return;
        }

        switch (choice) {
            case 1:
                if (has_mouse_toy) {
                    printf("장난감 쥐를 이미 구매했습니다.\n");
                } else if (CP < 1) {
                    printf("CP가 부족합니다.\n");
                } else {
                    CP -= 1;
                    has_mouse_toy = 1;
                    printf("장난감 쥐를 구매했습니다. 보유 CP: %d 포인트\n", CP);
                }
                return;
            
            case 2:
                if (has_laser_pointer) {
                    printf("레이저 포인터를 이미 구매했습니다.\n");
                } else if (CP <2) {
                    printf("CP가 부족합니다.\n");
                } else {
                CP -= 2;
                has_laser_pointer = 1;
                printf("레이저 포인터를 구매했습니다. 보유 CP: %d 포인트\n", CP);
                }
                return;

            case 3:
                if (has_scratcher) {
                    printf("스크래처를 이미 구매했습니다.\n");
                } else if (CP <4) {
                    printf("CP가 부족합니다.\n");
                } else {
                CP -= 4;
                has_scratcher = 1;
                printf("스크래처를 구매했습니다. 보유 CP: %d 포인트\n", CP);

                    do {
                        SCR_POS = rand() % ROOM_WIDTH;
                    } while (SCR_POS == HME_POS || SCR_POS == BWL_POS || SCR_POS == CAT_POS);
                }
                return;

            case 4:
                if (has_cattower){
                    printf("캣 타워를 이미 구매했습니다.\n");
                } else if (CP < 6) {
                    printf("CP가 부족합니다.\n");
                } else {
                CP -= 6;
                has_cattower = 1;
                printf("캣 타워를 구매했습니다. 보유 CP: %d 포인트\n", CP);

                    do {
                        CAT_POS = rand() % ROOM_WIDTH;
                    } while (CAT_POS == HME_POS || CAT_POS == BWL_POS || CAT_POS == SCR_POS);
                }
                return;
        }

    } 
}

// 돌발 퀘스트
void surprise_quest(void) {
    int target = rand() % 6 + 1;
    int roll, count = 0;

    printf("돌발퀘스트 발생! %d가 나올 때까지 주사위를 굴리세요.\n", target);
    printf("엔터 키를 누르면 주사위를 굴립니다.\n");

    do {
        printf(">> ");
        (void)getchar();  

        roll = rand() % 6 + 1;
        count++;
        printf("굴린 결과: %d\n", roll);

    } while (roll != target);

    printf("%d번 만에 %d가 나왔습니다! 돌발퀘스트 완료!\n", count, target);
}
