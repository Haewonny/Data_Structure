#include <stdio.h>
#include <stdlib.h>
/*
   [ 다항식의 덧셈 ]
   - 다항식을 컴퓨터로 처리하기 위한 자료구조
   - 하나의 다항식을 하나의 연결리스트로 표현 -> 항 하나를 하나의 노드에 저
   - 헤더 노드(header node)
      : 리스트의 앞과 뒤를 가리키는 포인터를 가지고 있어서, 리스트의 마지막에 노드를 삽입하기 수월함

   **알고리즘**
   1. p와 q가 가리키는 항들의 지수(expon)가 같으면 계수를 더한다
   2. q가 가리키는 항의 지수가 높으면 그대로 C로 옮긴다 - p는 이동하지 않고, q만 이동
   3. p가 가리키는 항의 지수가 높으면 그대로 C로 옮긴다 - q는 이동하지 않고, p만 이동

 */
typedef struct ListNode { // 노드 타입을 구조체로 정의함
    int coef;
    int expon;
    struct ListNode* link; // 자기 참조 구조체 - ListNode 타입의 노드를 가리키는 포인터
} ListNode;

// 연결 리스트 헤더
typedef struct ListType { // 리스트 헤더 타입
    int size; // 리스트의 사이즈
    ListNode* head; // 리스트의 맨 앞을 가리키는 포인터
    ListNode* tail; // 리스트의 맨 뒤를 가리키는 포인터
} ListType;

// 오류 처리 함수
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1);
}

// 리스트 헤더 생성 함수
ListType* create() {
    ListType* plist = (ListType*) malloc(sizeof (ListType));
    plist -> size = 0; // 공백 리스트
    plist -> head = plist -> tail = NULL;

    return plist;
}


// 리스트의 끝에 노드를 삽입하는 함수
// plist는 연결 리스트의 헤더를 가리키는 포인터, coef는 계수, expon는 지수
void insert_last(ListType* plist, int coef, int expon) {
    ListNode* temp = (ListNode*) malloc(sizeof (ListNode));
    if(temp == NULL)
        error("메모리 할당 에러");
    temp -> coef = coef; // 새로운 노드에 계수 대입
    temp -> expon = expon; // 새로운 노드에 지수 대입
    temp -> link = NULL; // 새로운 노드는 마지막 노드
    if(plist -> tail == NULL) { // 리스트가 공백 상태일 때
        plist -> head = plist -> tail = temp;
    }
    else {
        plist -> tail -> link = temp;
        plist -> tail = temp;
    }
    plist -> size++;
}

// 덧셈 함수 plist3 = plist1 + plist2
void poly_add(ListType* plist1, ListType* plist2, ListType* plist3) {
    ListNode* a = plist1 -> head;
    ListNode* b = plist2 -> head;
    int sum;

    while(a && b) {
        if(a -> expon == b -> expon) { // a의 차수 == b의 차수
            sum = a -> coef + b -> coef;
            if(sum != 0)
                insert_last(plist3, sum, a -> expon);
            a = a -> link;
            b = b -> link;
        }
        else if(a -> expon > b -> expon) { // a의 차수 > b의 차수
            insert_last(plist3, a -> coef, a -> expon);
            a = a -> link;
        }
        else { // a의 차수 < b의 차수
            insert_last(plist3, b -> coef, b -> expon);
            b = b -> link;
        }
    }

    // a나 b 중의 하나가 먼저 끝나게 되면 남아있는 항들은 모두 결과 다항식으로 복사
    for(; a != NULL; a = a -> link)
        insert_last(plist3, a -> coef, a -> expon);
    for(; b != NULL; b = b -> link)
        insert_last(plist3, b -> coef, b -> expon);
}

// 다항식 출력 함수
void poly_print(ListType* plist) {
    ListNode* p = plist -> head;

    printf("polynomial = ");
    for(; p; p = p -> link) {
        printf("%d^%d + ", p -> coef, p -> expon);
    }
    printf("\n");
}

// main 함수
int main(void){
    ListType* list1, * list2, * list3; // 각 다항식 리스트의 헤더를 가리키는 포인터

    // 연결 리스트 헤더 생성
    list1 = create();
    list2 = create();
    list3 = create();

    // 다항식 1을 생성
    insert_last(list1, 3, 12);
    insert_last(list1, 2, 8);
    insert_last(list1, 1, 0);

    // 다항식 2을 생성
    insert_last(list2, 8, 12);
    insert_last(list2, -3, 10);
    insert_last(list2, 10, 6);

    poly_print(list1);
    poly_print(list2);

    // 다항식 3 = 다항식 1 + 다항식 2
    poly_add(list1, list2, list3);
    poly_print(list3);

    free(list1);
    free(list2);
    free(list3);

    return 0;
}