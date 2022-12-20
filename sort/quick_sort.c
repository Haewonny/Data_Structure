#include <stdio.h>
#include <stdlib.h>
#include <time.h>
/*
  [ 퀵 정렬 (quick sort) ]
  - 평균적으로 가장 빠른 정렬 방법
  - 분할 정복 기법 사용
  - 리스트를 2개의 부분 리스트로 비균등 분할하고, 각각의 부분 리스트를 다시 퀵 정렬함(재귀 호출)
*/
#define MAX_SIXE 10
#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t)) // 매크로 함수

// 분할 함수
int partition(int list[], int left, int right) {
    int pivot, temp;
    int low, high; // 내부 작업용

    low = left; high = right + 1; pivot = list[left];
    do {
        do {
            low++;
        } while(low <= right && list[low] < pivot); // row 이동
        do {
            high--;
        } while(high >= left && list[high] > pivot); // high 이동

        if(low < high)
            SWAP(list[low], list[high], temp);
    } while(low < high); // low와 high가 교차하기 전까지

    SWAP(list[left], list[high], temp); // 피벗과 high 교체

    return high;
}

// 퀵 정렬 함수
void quick_sort(int list[], int left, int right) {
    if(left < right) {
        int q = partition(list, left, right);
        quick_sort(list, left, q - 1);
        quick_sort(list, q + 1, right);
    }
}

// main 함수
int main(void){
    int list[MAX_SIXE];
    int i, n;
    n = MAX_SIXE;

    srand((unsigned) time(NULL));
    for(i = 0; i < n; i++) // 난수 생성
        list[i] = rand() % 100;

    quick_sort(list, 0, n - 1); // 퀵 정렬 호출

    for(i = 0; i < n; i++) // 출력
        printf("%d ", list[i]);
    printf("\n");

    return 0;
}