#include <stdio.h>
#include <stdlib.h>
/*
  [ Prim의 MST 알고리즘 ]
  - 탐욕적인 방법(greedy) : 각 단계에서 최선의 답을 선택하는 과정을 반복함으로써 최종적인 해답에 도달

  ** 알고리즘 **
  1. 시작 정점에서부터 출발하여 신장 트리를 단계적으로 키워 나감
  2. 신장 트리를 만들어 가는 과정에서 선택되는 간선들은 하나의 트리에 속함
  3. 신장 트리 집합에 인접한 정점 중에서 최저 간선으로 연결된 정점을 선택하여 신장 트리 집합에 추가함
 */
#define TRUE 1
#define FALSE 0
#define MAX_VERTICES 100  // 신장트리의 정점 개수
#define INF 1000 // 경로가 없는 것을 표현하기 위해서

typedef struct GraphType {
    int n; // 정점의 개수
    int weight[MAX_VERTICES][MAX_VERTICES];
} GraphType;

int selected[MAX_VERTICES]; // 선택된 노드
int distance[MAX_VERTICES]; // 최소의 거리 정보만을 담는 배열

// 최소 distance[v]값을 갖는 정점을 반환
int get_min_vertex(int n) {
    int v, i;
    for(i = 0; i < n; i++) {
        if(!selected[i]) { // 선택 안 된 것들 중에서 첫번째
            v = i;
            break;
        }
    }
    for(i = 0; i < n; i++) {
        if(!selected[i] && (distance[i] < distance[v])) // 선택이 안 되어 있고, 거리가 더 작으면
            v = i;
    }
    return v; // 간선의 길이가 작은 노드 반환
}

// prim의 최소 비용 신장 트리 함수
void prim(GraphType* g, int s) {
    int i, u, v;
    for(u = 0; u < g -> n; u++)
        distance[u] = INF;

    distance[s] = 0;

    for(i = 0; i < g -> n; i++) {
        u = get_min_vertex(g -> n); // 누가 제일 값이 작은지

        selected[u] = TRUE;
        if(distance[u] == INF)
            return; // 연결하지 않음
        printf("정점 %d 추가\n", u);
        for(v = 0; v < g -> n; v++)
            if(g -> weight[u][v] != INF)
                if(!selected[v] && g -> weight[u][v] < distance[v])
                    distance[v] = g -> weight[u][v]; // 거리 업데이트
    }
}

// main 함수
int main() {
    GraphType g = { 6,
                    { {0,20,24,INF,25,INF},
                      {20,0,INF,7,12,5},
                      {24,INF,0,12,30,INF},
                      {INF,7,22,0,15,10},
                      {25,12,22,15,0,INF},
                      {INF,5,INF,10,INF,0}}

    };
    prim(&g, 0);

    return 0;
}