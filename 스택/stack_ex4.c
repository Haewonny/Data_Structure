#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
   [ 미로 탐색 ]
   - 체계적인 방법이 필요
   - 현재의 위치에서 가능한 방향을 스택에 저장해 놓았다가 막다른 길을 만나면 스택에서 다음 탐색 위치를 꺼냄
 */
// 스택 코드는 stack3.c에 있는 거 활용
// ***** 스택 코드의 시작
#define MAX_STACK_SIZE 100 // 스택의 최대 크기
#define MAZE_SIZE 6 // 6 x 6 미로

typedef struct {
    short r; // 행
    short c; // 열
} element;

typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType; // 스택 구조체

// 스택 초기화 함수
void init_stack(StackType* s){ // 포인터를 받아옴
    s -> top = -1; // top에는 아무것도 없는 상태
    // ** 포인터 -> 멤버
}

// 공백 상태 검출 함수
int is_empty(StackType* s){
    return (s -> top == -1); // top이 -1이면 공백인 상태(true == 1)
}

// 포화 상태 검출 함수
int is_full(StackType* s){
    return (s -> top == (MAX_STACK_SIZE - 1)); // top이 MAX_STACK_SIZE - 1이면 포화 상태(true == 1)
}

// 삽입 함수
void push(StackType* s, element item){
    if(is_full(s)){ // 스택이 포화 상태이면
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else
        s -> data[++(s -> top)] = item; // 스택 top 인덱스 하나 증가
}

// 삭제 함수
element pop(StackType* s){ // 반환값이 스택 요소(구조체)
    if(is_empty(s)){ // 스택이 공백 상태이면
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s -> data[(s -> top)--];
}

// peek 함수
element peek(StackType* s){
    if(is_empty(s)){ // 스택이 공백 상태이면
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s -> data[(s -> top)]; // top 위치 변화 없음
}
// ***** 스택 코드의 끝

element here = {1, 0}, entry = {1, 0};

char maze[MAZE_SIZE][MAZE_SIZE] = { // 전역 배열
        {'1', '1', '1', '1', '1', '1' },
        {'e', '0', '1', '0', '0', '1' }, // e는 입구, 현재위치
        {'1', '0', '0', '0', '1', '1' },
        {'1', '0', '1', '0', '1', '1' },
        {'1', '0', '1', '0', '0', 'x' },
        {'1', '1', '1', '1', '1', '1' },

};

// 위치를 스택에 삽입
void push_loc(StackType* s, int r, int c){
    if(r < 0 || c < 0)
        return;
    if(maze[r][c] != '1' && maze[r][c] != '.'){
        element tmp;
        tmp.r = r;
        tmp.c = c;
        push(s, tmp);
    }
}

// 미로를 화면에 출력
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE]){
    printf("\n");
    for(int r = 0; r < MAZE_SIZE; r++){
        for(int c = 0; c < MAZE_SIZE; c++){
            printf("%c", maze[r][c]);
        }
        printf("\n");
    }
}

// main 함수
int main(void){
    int r, c;
    StackType s;

    init_stack(&s);
    here = entry;
    while(maze[here.r][here.c] != 'x'){ // here이 출구가 아니라면
        r = here.r;
        c = here.c;

        maze[r][c] = '.';
        maze_print(maze);

        // 상하좌우 호출
        push_loc(&s, r - 1, c);
        push_loc(&s, r + 1, c);
        push_loc(&s, r, c - 1);
        push_loc(&s, r, c + 1);

        if(is_empty(&s)){
            printf("실패\n");
            return 1;
        }
        else
            here = pop(&s);
    }
    printf("성공\n");

    return 0;
}