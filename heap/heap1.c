#include <stdio.h>
#include <stdlib.h>
/*
  [ 힙 구현 ]
  - 힙 : 노드의 키들이 key(부모 노드) >= key(자식 노드)를 만족하는 완전 이진 트리
  - 힙의 종류
    1) 최대 힙 (max heap) : 부모 노드의 키값이 자식 노드의 키값보다 크거나 같은 완전 이진 트리
    2) 최소 힙 (min heap) : 부모 노드의 키값이 자식 노드의 키값보다 작거나 같은 완전 이진 트리
  - 배열을 이용하여 힙을 구현할 수 있음
   -> 완전 이진 트리이므로 각 노드의 번호를 붙이고, 이 번호를 배열의 인덱스라고 생각하기
 */
#define MAX_ELEMENT 200 // 힙의 최대 크기
typedef struct {
    int key;
} element; // 힙에 저장되는 것은 정수

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size; // 현재 힙에 저장되어 있는 데이터의 개수 저장
} HeapType;

// 힙 생성 함수
HeapType* create() {
    return (HeapType*) malloc(sizeof (HeapType));
}

// 힙 초기화 함수
void init(HeapType* h) {
    h -> heap_size = 0; // 힙에 아무것도 없는 상태
}

// 삽입 함수 - 현재 요소의 개수가 heap_size인 힙 h에 item을 삽입함
void insert_max_heap(HeapType* h, element item) {
    int i;
    i = ++(h -> heap_size); // 일단 인덱스 위치를 확인, 삽입은 밑에서!

    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while((i != 1) && (item.key > h -> heap[i / 2].key)) { // root가 아님 && 넣을 값 > 부모 노드의 값
        h -> heap[i] = h -> heap[i / 2]; // 자식 노드와 부모 노드 교환
        i /= 2; // 인덱스 한 칸 올라감
    }
    h -> heap[i] = item; // 새로운 노드를 삽입
}

// 삭제 함수
element delete_max_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h -> heap[1]; // 제거할 root
    temp = h -> heap[(h -> heap_size)--]; // 마지막 노드에 있는 원소

    parent = 1;
    child = 2; // 왼쪽 child

    while(child <= h -> heap_size) { // child 인덱스가 heap_size를 넘어갈 수는 없음
        // 현재 노드의 자식노드 중 더 작은 자식 노드를 찾음
        if((child < h -> heap_size) && (h -> heap[child].key) < h -> heap[child + 1].key) // 형제가 있음 && 왼쪽 자식 값 < 오른쪽 자식 값
            child++;
        if(temp.key >= h -> heap[child].key) // 마지막 노드에 있던 값 >= 자식 노드의 값
            break; // 루프를 벗어난 후, 이 child의 부모 자리에 노드 삽입
        // 한 단계 아래로 이동
        h -> heap[parent] = h -> heap[child];
        parent = child; // 한 층 내려감
        child *= 2; // 왼쪽 자식 노드
    }
    h -> heap[parent] = temp; // 힙 성질을 만족하는 위치에 삽입

    return item;
}

// main 함수
int main(void){
    element e1 = { 10 }, e2 = { 5 }, e3 = { 30 }, e4 = { 25 };
    element e5, e6, e7, e8;
    HeapType* heap;

    heap = create(); // 힙 생성
    init(heap); // 힙 초기화

    // 삽입
    insert_max_heap(heap, e1);
    insert_max_heap(heap, e2);
    insert_max_heap(heap, e3);
    insert_max_heap(heap, e4);

    // 삭제
    e5 = delete_max_heap(heap);
    printf("< %d > ", e5.key);
    e6 = delete_max_heap(heap);
    printf("< %d > ", e6.key);
    e7 = delete_max_heap(heap);
    printf("< %d > ", e7.key);
    e8 = delete_max_heap(heap);
    printf("< %d > ", e8.key);

    free(heap);

    return 0;
}