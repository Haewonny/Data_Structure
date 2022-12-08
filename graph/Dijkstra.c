#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
/*
  [ Dijkstra의 최단 경로 알고리즘 ]
  - 탐욕적인 방법(greedy) : 각 단계에서 최선의 답을 선택하는 과정을 반복함으로써 최종적인 해답에 도달
  - 하나의 시작 정점에서 다른 정점까지의 최단 경로 계산

  - 집합 S : 시작 정점 v로부터의 최단 경로가 이미 확정된 정점들의 집합
  - distance[] : 최단 경로가 알려진 정점들만을 이용한 다른 정점들까지의 최단 경로 길이
  - 매 단계에서 가장 distance 값이 작은 정점을 s에 추가

 */
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100
#define INF 1000000 // 무한대 (연결이 없는 경우)

typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int distance[MAX_VERTICES]; // 시작 정점으로부터의 최단경로 거리
int found[MAX_VERTICES]; // 방문한 정점 표시

int choose(int distance[], int n, int found[]) {
    int i, min, minpos;
    min = INT_MAX;
    minpos = -1;
    for(i = 0; i < n; i++) {
        if(distance[i] < min && !found[i]) { // 더 짧은 거리이고 아직 선택되지 않았다면
            min = distance[i];
            minpos = i;
        }
    }
    return minpos;
}

// 출력 함수
void print_status(GraphType* g) {
    static int step = 1;
    printf("STEP %d : ", step++);
    printf("distance : ");
    for(int i = 0; i < g -> n; i++) {
        if(distance[i] == INF)
            printf(" * ");
        else
            printf("%2d ", distance[i]);
    }
    printf("\n");
    printf(" found : ");
    for(int i = 0; i < g -> n; i++)
        printf("%2d ", found[i]);
    printf("\n\n");
}

void dijkstra_shortest_path(GraphType* g, int start) {
    int i, u, w;
    for(i = 0; i < g -> n; i++) { // 초기화
        distance[i] = g -> weight[start][i];
        found[i] = FALSE;
    }
    found[start] = TRUE; // 시작 정점 방문 표시
    distance[start] = 0;
    for(i = 0; i < g -> n - 1; i++) {
        print_status(g);
        u = choose(distance, g -> n, found); // 거리 짧은 노드 번호
        found[u] = TRUE;
        for(w = 0; w < g -> n; w++) {
            if(!found[w]){
                if(distance[u] + g -> weight[u][w] < distance[w])
                    distance[w] = distance[u] + g -> weight[u][w];
            }
        }
    }
}
// main 함수
int main() {
    GraphType g = {7,{
            {0, 7, INF, INF, 3, 10, INF },
            {7, 0, 4, 10, 2, 6, INF },
            {INF, 4, 0, 2, INF, INF, INF },
            {INF, 10, 2, 0, 11, 9, 4 },
            {3, 2, INF, 11, 0, INF, 5 },
            {10, 6, INF, 9, INF, 0, INF },
            {INF, INF, INF, 4, 5, INF, 0 }
    }};
    dijkstra_shortest_path(&g, 0);

    return 0;
}