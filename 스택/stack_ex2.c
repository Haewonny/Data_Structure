#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
   [ 후위 표기식 계산 ]
   - 컴파일러는 프로그램의 중위 표기식을 후위 표기식으로 변환하여 사용함
     (*중위 표기식 : 사람이 사용하는 표기식, 연산자에 우선순위가 있고, 괄호를 써서 순서를 바꿀 수도 있다.)
   - 후위 표기식은 연산의 우선순위를 나타내기 위해 괄호가 필요 없음
     -> 오른쪽 괄호를 만날 때까지 기다리는 것이 아니라, 식을 읽어가며 바로 계산함
   - 수식 계산시에 연산자의 우선수위를 고려할 필요가 없음
     -> 먼저 계산해야 하는 연산자가 앞에 있음 (식 자체에 우선순위 자체가 표현되어 있음)

   **알고리즘**
   1. 수식을 왼쪽에서 오른쪽으로 스캔하면서 피연산자이면 스택에 저장함
   2. 연산자이면 필요한 수만큼의 피연산자를 스택에서 꺼내 연산을 실행함
   3. 연산의 결과를 다시 스택에 저장함
 */
// 스택 코드는 stack3.c에 있는 거 활용
// ***** 스택 코드의 시작
#define MAX_STACK_SIZE 100 // 스택의 최대 크기

typedef int element; // int 타입
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

// 후위 표기 수식 계산 함수
int eval(char exp[]){ // 문자열의 시작 주소를 받아옴
    int op1, op2, value;
    int len = strlen(exp); // 문자열의 길이
    char ch;

    StackType s;
    init_stack(&s);

    for(int i = 0; i < len; i++){ // for문 돌면서 문자열 길이만큼 토큰 읽기
        ch = exp[i];
        if(ch != '+' && ch != '-' && ch != '*' && ch != '/'){ // 입력이 피연산자이면
            value = ch - '0'; // '5' - '0' = 5
            push(&s, value);
        }
        else{ // 연산자이면 피연산자를 스택에서 제거
            op2 = pop(&s);
            op1 = pop(&s);

            switch (ch) { // 연산을 수행하고 스택에 저장
                case '+':
                    push(&s, op1 + op2);
                    break;
                case '-':
                    push(&s, op1 - op2);
                    break;
                case '*':
                    push(&s, op1 * op2);
                    break;
                case '/':
                    push(&s, op1 / op2);
                    break;
            }
        }
    }
    return pop(&s);
}

// main 함수
int main(void){
    int result;
    printf("후위 표기식 : 82/3-32*+ \n");

    result = eval("82/3-32*+");
    printf("결과값 : %d\n", result);

    return 0;
}