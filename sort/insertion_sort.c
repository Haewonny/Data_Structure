#include <stdio.h>
#include <stdlib.h> // srand(), rand() 정의
#include <time.h>
/*
  [ 삽입 정렬 (insertion sort) ]
  - 정렬되어 있는 부분에 새로운 레코드를 올바른 위치에 삽입하는 과정 반복
 */
#define MAX_SIXE 20

// 삽입 정렬 함수
void insertion_sort(int list[], int n) {
    int i, j, key;
    for(i = 1; i < n; i++) {
        key = list[i]; // i번째 숫자를 삽입하려고 함
        for(j = i - 1; j >= 0 && list[j] > key; j--)
            list[j + 1] = list[j]; // 레코드의 오른쪽 이동
        list[j + 1] = key;
    }
}

// main 함수
int main(void){
    int n, list[MAX_SIXE]; // list[]는 정렬하고자 하는 배열
    n = MAX_SIXE;

    srand((unsigned) time(NULL)); // 난수 시퀀스의 첫째 숫자 결정
    for(int i = 0; i < n; i++) // 난수 생성
        list[i] = rand() % 100; // 난수의 범위 0~99

    insertion_sort(list, n); // 삽입 정렬 호출

    for(int i = 0; i < n; i++) // 정렬된 배열 출력
        printf("%d ", list[i]);
    printf("\n");

    return 0;
}