#include <stdio.h>
#include <stdlib.h>
/*
  [ Floyd의 최단 경로 알고리즘 ]
  - 동적 계획법 : 같은 문제를 계속 반복하는 것이 아니라 문제를 점점 키워나감
  - 모든 정점에서 다른 모든 정점까지의 최단 경로를 계산

  ** 알고리즘 **
  1. 그래프의 가중치 행렬로 배열 A를 초기화 함
  2. 정점 0을 거쳐서 가는 경로와 비교하여 최단 경로를 수정함
  3. 정점 1을 거쳐서 가는 경로와 비교하여 최단 경로를 수정함
  (... 반복 ...)
 */
#define MAX_VERTICES 100  // 최대 노드 개수
#define INF 1000000 // 무한대 (연결이 없는 경우)

typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int A[MAX_VERTICES][MAX_VERTICES]; // 계속 덮어쓸 배열

void printA(GraphType* g) { // 배열 A의 출력
    int i, j;
    printf("====================\n");
    for(i = 0; i < g -> n; i++) {
        for(j = 0; j < g -> n; j++) {
            if(A[i][j] == INF)
                printf("  *");
            else
                printf("%3d", A[i][j]);
        }
        printf("\n");
    }
    printf("====================\n");
}

void floyd(GraphType* g) {
    int i, j, k;
    for(i = 0; i < g -> n; i++) { // 배열 A의 초기화
        for(j = 0; j < g -> n; j++) {
            A[i][j] = g -> weight[i][j];
        }
    }
    printA(g);

    for(k = 0; k < g -> n; k++) {
        for(i = 0; i < g -> n; i++) {
            for(j = 0; j < g -> n; j++) {
                if (A[i][j] + A[k][j] < A[i][j])
                    A[i][j] = A[i][k] + A[k][j];
            }
        }
        printA(g);
    }
}

// main 함수
int main() {
    GraphType g = {7, {
            {0, 7, INF, INF, 3, 10, INF },
            {7, 0, 4, 10, 2, 6, INF },
            {INF, 4, 0, 2, INF, INF, INF },
            {INF, 10, 2, 0, 11, 9, 4 },
            {3, 2, INF, 11, 0, INF, 5 },
            {10, 6, INF, 9, INF, 0, INF },
            {INF, INF, INF, 4, 5, INF, 0 }
    }};

    floyd(&g);

    return 0;
}