#include <stdio.h>
#include <stdlib.h>
/*
  [ 배열로 구현된 리스트 ]
  - 순차적 메모리 할당 -> 리스트의 순차적 표현 (sequential representation)
  - 특징
    1) 구현이 간단함
    2) 삽입, 삭제시에 오버헤드가 발생할 수 있음 (기존의 데이터 이동 때문)
    3) 리스트의 크기가 고정되어 있음
      -> 공간이 부족하면 더 큰 배열을 만들고, 기존 배열의 데이터를 모두 복사해야 함
 */
#define MAX_LIST_SIZE 100 // 리스트의 최대 크기
typedef int element; // 리스트 항목의 정의 (정수 타입)
typedef struct {
    element array[MAX_LIST_SIZE]; // 배열 정의
    int size; // 현재 리스트에 저장된 항목들의 개수
} ArrayListType;

// 리스트 초기화 함수
void init(ArrayListType* L) {
    L -> size = 0; // size를 0으로 초기화
}

// 오류 처리 함수
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1); // 강제종료
}

// 공백 상태 검출 함수 - 리스트가 비어 있으면 1을 반환, 그렇지 않으면 0을 반환
int is_empty(ArrayListType* L) {
    return L -> size == 0; // 비어 있으면 1(true)
}

// 포화 상태 검출 함수 - 리스트가 가득 차 있으면 1을 반환, 그렇지 않으면 0을 반환
int is_full(ArrayListType* L) {
    return L -> size == MAX_LIST_SIZE;
}

// pos 위치의 요소값 확인 함수
element get_entry(ArrayListType* L, int pos) {
    if(pos < 0 || pos >= L -> size) // 인덱스 위치 벗어나면
        error("위치 오류");
    return L -> array[pos];
}

// 리스트 출력 함수
void print_list(ArrayListType* L) {
    for(int i = 0; i < L -> size; i++)
        printf("%d -> ", L -> array[i]);
    printf("\n");
}

// 리스트의 맨 뒤에 항목 삽입하는 함수
void insert_last(ArrayListType* L, element item) {
    if(L -> size >= MAX_LIST_SIZE)
        error("리스트 오버플로우");
    L -> array[L -> size++] = item;
}

// 리스트의 pos 위치에 항목 삽입하는 함수
void insert(ArrayListType* L, int pos, element item) {
    if(!is_full(L) && (pos >= 0) && (pos <= L -> size)) { // 리스트가 가득 차 있지 않고, 인덱스가 정상 범위에 있으면
        for(int i = (L -> size - 1); i >= pos; i--)
            L -> array[i + 1] = L -> array[i]; // pos 위치에 있던 원소부터 오른쪽으로 한칸씩 이동
        L -> array[pos] = item;
        L -> size++;
    }
}

// 리스트의 pos 위치에 있는 항목 삭제하는 함수
element delete(ArrayListType* L, int pos) {
    element item;

    if(pos < 0 || pos >= L -> size)
        error("위치 오류");
    item = L -> array[pos]; // pos 위치 데이터 삭제
    for(int i = pos; i < (L -> size - 1); i++)
        L -> array[i] = L -> array[i + 1]; // pos 위치에 있던 원소부터 왼쪽으로 한칸씩 이동
    L -> size--;

    return item;
}

// main 함수
int main(void){

    // ArrayListType을 정적으로 생성하고 ArrayListType을 가리키는 포인터를 함수의 매개변수로 전달함
    ArrayListType list;

    init(&list); // 리스트 초기화

    insert(&list, 0, 10); print_list(&list); // 0번째 위치에 10 추가
    insert(&list, 0, 20); print_list(&list); // 0번째 위치에 20 추가
    insert(&list, 0, 30); print_list(&list); // 0번째 위치에 30 추가

    insert_last(&list, 40); print_list(&list); // 맨 끝에 40 추가

    delete(&list, 0); print_list(&list); // 0번째 항목 삭제

    return 0;
}