#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
   [ 중위 표기식 -> 후위 표기식 ]
   - 중위 표기식과 후위 표기식의 공통점 : 피연산자의 순서가 동일함
   - 연산자들의 순서만 다름(우선 순위 순서) -> 연산자만 스택에 저장했다가 출력하면 됨
    ex) 2+3*4 => 234*+

   **알고리즘**
   1. 피연산자는 그대로 출력함
   2. 연산자(op1)를 만났을 때, 스택이 비어 있다면 넣음
                          스택 top의 우선순위가 높거나 같은 연산자(op2)가 들어 있다면 이들을 모두 출력한 후에, op1을 스택에 넣음
   3. 왼쪽 괄호를 만나면 스택에 삽입함
     -> 왼쪽 괄호는 우선순위가 가장 낮은 연산자로 취급 (오른쪽 괄호 만날 때까지 출력하지 않음)
        오른쪽 괄호를 만나면 왼쪽 괄호가 삭제될 때까지 그 괄호 위의 모든 연산자들을 출력함
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

// 연산자의 우선순위를 반환하는 함수
int prec(char op){
    switch (op) {
        case '(': case ')': 
            return 0; // 우선순위가 가장 낮음
        case '+': case '-':
            return 1; 
        case '*': case '/':
            return 2;    
    }
    return -1;
}

// 중위 표기 수식을 후위 표기 수식으로 변환하는 함수
void infix_to_postfix(char exp[]){
    int i = 0;
    char ch, top_op;
    int len = strlen(exp); // 문자열의 길이
    
    StackType s;
    init_stack(&s); // 스택 초기화
    
    for(i = 0; i < len; i++){
        ch = exp[i];
        switch (ch) {
            case '+': case '-': case '*': case '/': // 연산자
                // 스택에 있는 연산자의 우선순위가 더 크거나 같으면 출력
                while(!is_empty(&s) && (prec(ch) <= prec(peek(&s))))
                    printf("%c", pop(&s));
                push(&s, ch);
                break;
            case '(': // 왼쪽 괄호
                push(&s, ch);
                break;
            case ')': // 오른쪽 괄호
                top_op = pop(&s);
                while(top_op != '('){ // 왼쪽 괄호를 만날 때까지 출력
                    printf("%c", top_op);
                    top_op = pop(&s);
                }
                break;
            default: // 피연산자
                printf("%c", ch);
                break;
        }
    }
    // 스택에 저장된 연산자들 출력
    while(!is_empty(&s))
        printf("%c", pop(&s));
}
// main 함수
int main(void){
    char* s = "(2+3)*4+9";

    printf("중위 표기 수식 : %s \n", s);

    printf("후위 표기 수식 : ");
    infix_to_postfix(s); // 중위 표기 수식을 후위 표기 수식으로 변환
    printf("\n");

    return 0;
}