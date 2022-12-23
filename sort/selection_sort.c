#include <stdio.h>
#include <stdlib.h> // srand(), rand() 정의
#include <time.h>
/*
  [ 선택 정렬 (selection sort) ]
  - 정렬된 왼쪽 리스트와 정렬되지 않은 오른쪽 리스트를 가정
  - 초기에는 왼쪽 리스트는 비어 있고, 정렬할 숫자들은 모두 오른쪽 리스트에 존재
  - 제자리 정렬 가능
 */
#define MAX_SIXE 20

// 선택 정렬 함수
void selection_sort(int list[], int n) {
    int least, temp;
    for(int i = 0; i < n - 1; i++) {
        least = i; // 현재 최소값
        for(int j = i + 1; j < n; j++) // 최솟값의 위치 찾기
            if(list[j] < list[least])
                least = j;

        // list[i]와 list[least] 교환
        temp = list[i];
        list[i] = list[least];
        list[least] = temp;
    }
}

// main 함수
int main(void){
    int n, list[MAX_SIXE]; // list[]는 정렬하고자 하는 배열
    n = MAX_SIXE;

    srand((unsigned) time(NULL)); // 난수 시퀀스의 첫째 숫자 결정
    for(int i = 0; i < n; i++) // 난수 생성
        list[i] = rand() % 100; // 난수의 범위 0~99

    selection_sort(list, n); // 선택 정렬 호출

    for(int i = 0; i < n; i++) // 정렬된 배열 출력
        printf("%d ", list[i]);
    printf("\n");

    return 0;
}