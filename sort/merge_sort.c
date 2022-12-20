#include <stdio.h>
/*
  [ 합병 정렬 (merge sort) ]
  - 입력 배열을 두 개의 균등한 크기로 분할하고, 분할된 부분 배열들을 각각 따로 정렬
  - 정렬된 두 개의 부분 배열을 합병(merge)하여 전체 리스트를 정렬함
  - 분할 정복
   1) 분할(divide) : 부분 배열의 크기가 충분히 작아질 때까지 이 작업을 반복
   2) 정복(conquer) : 정렬된 두 개의 부분 배열을 합병을 통해 하나의 정렬된 큰 배열로 통합
 */
#define MAX_SIXE 100

int sorted[MAX_SIXE]; // 원래 배열과 크기가 같은 추가 공간이 필요함

// 합병 함수
void merge(int list[], int left, int mid, int right) {
    int i, j, k, l;
    i = left; j = mid + 1; // 배열에서 맨 앞 따라감
    k = left; // sorted 배열의 맨 앞

    // 분할 정렬된 list의 합병
    while(i <= mid && j <= right) { // 두 리스트에 원소가 하나라도 남아 있으면
        if(list[i] <= list[j])
            sorted[k++] = list[i++];
        else
            sorted[k++] = list[j++];
    }

    // 남아 있는 레코드의 일괄 복사
    if(i > mid) {
        for(l = j; l <= right; l++)
            sorted[k++] = list[l];
    }
    else {
        for(l = i; l <= mid; l++)
            sorted[k++] = list[l];
    }

    // 배열 sorted[]의 리스트를 배열 list[]로 복사
    for(l = left; l <= right; l++)
        list[l] = sorted[l];
}

// 합병 정렬 함수
void merge_sort(int list[], int left, int right) {
    int mid;
    if(left < right) {
        mid = (left + right) / 2; // 리스트의 균등 분할
        merge_sort(list, left, mid); // 부분 리스트 정렬
        merge_sort(list, mid + 1, right); // 부분 리스트 정렬
        merge(list, left, mid, right); // 합병
    }
}

// 출력 함수
void print(int list[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d ", list[i]);
}

// main 함수
int main(void){
    int n = 8;
    int list[] = { 27, 10, 12, 20, 25, 13, 15, 22 }; // 정렬할 리스트 생성

    merge_sort(list, 0, n - 1);
    print(list, n);

    return 0;
}