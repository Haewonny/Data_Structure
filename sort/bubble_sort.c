#include <stdio.h>
#include <stdlib.h> // srand(), rand() 정의
#include <time.h>
/*
  [ 버블 정렬 (bubble sort) ]
  - 인접한 2개의 레코드를 비교하여 순서대로 되어 있지 않으면 서로 교환
 */
#define MAX_SIXE 20
#define SWAP(x, y, t) ( (t) = (x), (x) = (y), (y) = (t)) // 매크로 함수

// 버블 정렬 함수
void bubble_sort(int list[], int n) {
    int i, j, temp;
    for(i = n - 1; i > 0; i--) {
        for(j = 0; j < i; j++) { // 앞뒤의 레코드를 비교한 후 교체
            if(list[j] > list[j + 1])
                SWAP(list[j], list[j + 1], temp);;
        }
    }
}

// main 함수
int main(void){
    int n, list[MAX_SIXE]; // list[]는 정렬하고자 하는 배열
    n = MAX_SIXE;

    srand((unsigned) time(NULL)); // 난수 시퀀스의 첫째 숫자 결정
    for(int i = 0; i < n; i++) // 난수 생성
        list[i] = rand() % 100; // 난수의 범위 0~99

    bubble_sort(list, n); // 삽입 정렬 호출

    for(int i = 0; i < n; i++) // 정렬된 배열 출력
        printf("%d ", list[i]);
    printf("\n");

    return 0;
}