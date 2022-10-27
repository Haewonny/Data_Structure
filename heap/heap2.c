#include <stdio.h>
#include <stdlib.h>
/*
  [ 힙 정렬 ]
  - 정렬할 n개의 요소들을 최대 힙에 삽입
  - 요소를 한 번에 하나씩 힙에서 삭제하여 저장 -> 내림차순 정렬
  - 최소 힙을 사용하면 오름차순 정렬이 됨
  - 힙 정렬이 유용한 경우는 전체 자료를 정렬하는 것이 아니라 가장 큰 값 몇 개만 필요한 경우
 */
#define MAX_ELEMENT 200 // 힙의 최대 크기
#define SIZE 8
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

// 힙 정렬 함수
void heap_sort(element a[], int n) {
    int i;
    HeapType* h;

    h = create(); // 힙 생성
    init(h); // 힙 초기화
    for(i = 0; i < n; i++) {
        insert_max_heap(h, a[i]); // 힙에 n번 삽입
    }
    // 최대 힙 사용 -> 오름차순 정렬을 위해 삭제되는 요소들을 배열의 뒤에서부터 앞쪽으로 채워 나감
    for(i = (n - 1); i >= 0; i--) {
        a[i] = delete_max_heap(h); // 힙에서 n번 삭제
    }

    free(h);
}

// main 함수
int main(void){
    element list[SIZE] = { 23, 56, 11, 9, 56, 99, 27, 34 };

    heap_sort(list, SIZE);
    for(int i = 0; i < SIZE; i++) {
        printf("%d ", list[i].key);
    }
    printf("\n");

    return 0;
}