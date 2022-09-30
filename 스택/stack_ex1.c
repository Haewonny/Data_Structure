#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
   [ 괄호 검사 ]
   - 조건 1) 왼쪽 괄호의 개수와 오른쪽 괄호의 개수가 같아야 한다.
   - 조건 2) 같은 괄호에서 왼쪽 괄호는 오른쪽 괄호보다 먼저 나와야 한다.
   - 조건 3) 괄호 사이에는 포함 관계만 존재한다.

   **알고리즘**
   1. 문자열에 있는 괄호를 차례로 조사하면서 왼쪽 괄호를 만나면 그 괄호를 스택에 삽입하고, 오른쪽 괄호를 만나면 스택 top에 있는 왼쪽 괄호를 삭제한 후,
      그 괄호가 (방금 읽은) 오른쪽 괄호와 짝이 맞는지 검사한다.
   2. 이때, 스택이 비어 있으면 조건 1 또는 조건 2를 위배하게 되고, 괄호의 짝이 맞지 않으면 조건 3에 위배된다.
   3. 마지막 괄호까지 조사한 후에도 스택에 괄호가 남아 있으면 조건 1에 위배되므로 0(거짓)을 반환하고,
      그렇지 않으면 1(참)을 반환한다.
 */
// 스택 코드는 stack3.c에 있는 거 활용
// ***** 스택 코드의 시작
#define MAX_STACK_SIZE 100 // 스택의 최대 크기

typedef char element; // char 타입
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

    /*
      [ top이 가리키는 곳에 대입하고 싶은 경우 ]
       s -> data [s -> top]
       ---------  --------
          배열        위치
    */
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

// 괄호 검사 함수
int check_matching(const char* in){ // 함수는 배열 원본에서 작업하기 때문에 const 키워드 사용
    StackType s;
    char ch, open_ch;
    int n = strlen(in); // n은 문자열의 길이
    init_stack(&s); // 스택 초기화

    for(int i = 0; i < n; i++){ // 문자열의 길이를 알기 때문에 for문 사용
        ch = in[i]; // ch는 다음 문자
        switch(ch){
        case '(': case '[': case '{':{
            push(&s, ch);
            break;
        }
        case ')': case ']': case '}':{
            if(is_empty(&s)) // 스택에 남아있으면
                return 0; // 오류
            else{
                open_ch = pop(&s);
                if((open_ch == '(' && ch != ')') ||
                   (open_ch == '[' && ch != ']') ||
                   (open_ch == '{' && ch != '}')){
                    return 0;
                }
                break;
            }
        }
        }
    }
    if(!is_empty(&s)) // 스택에 남아있으면
        return 0; // 오류

    return 1;
}

// main 함수
int main(void){
    char* p = "{A[(i+1)]=0;}"; // 샘플 데이터
    if(check_matching(p) == 1)
        printf("%s 괄호 검사 성공\n", p);
    else
        printf("%s 괄호 검사 실패\n", p);
    return 0;
}