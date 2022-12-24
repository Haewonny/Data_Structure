#include <stdio.h>
#include <stdlib.h> // srand(), rand() 정의
#include <time.h>
/*
  [ 쉘 정렬 (shell sort) ]
  - 전체 리스트를 일정 간격(gap)의 부분 리스트로 나눔
  - 나뉘어진 각각의 부분 리스트를 삽입 정렬 함
 */
#define MAX_SIXE 20

// gap 만큼 떨어진 요소들을 삽입 정렬 - 정렬의 범위는 first에서 last
void inc_insertion_sort(int list[], int first, int last, int gap) {
    int i, j, key;
    for(i = first + gap; i <= last; i = i + gap) {
        key = list[i];
        for(j = i - gap; j >= first && key < list[j]; j = j - gap) {
            list[j + gap] = list[j];
        }
        list[j + gap] = key;
    }
}
// 쉘 정렬 함수
void shell_sort(int list[], int n) {
    int i, gap;
    for(gap = n / 2; gap > 0; gap = gap / 2) {
        if((gap % 2) == 0)
            gap++; // gap이 짝수이면 +1
        for(i = 0; i < gap; i++) // 부분 리스트의 개수는 gap
            inc_insertion_sort(list, i, n - 1, gap);
    }
}

// main 함수
int main(void){
    int n, list[MAX_SIXE]; // list[]는 정렬하고자 하는 배열
    n = MAX_SIXE;

    srand((unsigned) time(NULL)); // 난수 시퀀스의 첫째 숫자 결정
    for(int i = 0; i < n; i++) // 난수 생성
        list[i] = rand() % 100; // 난수의 범위 0~99

    shell_sort(list, n); // 삽입 정렬 호출

    for(int i = 0; i < n; i++) // 정렬된 배열 출력
        printf("%d ", list[i]);
    printf("\n");

    return 0;
}