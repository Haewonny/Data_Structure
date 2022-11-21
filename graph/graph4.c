#include <stdio.h>
#include <stdlib.h>
/*
  [ DFS (깊이 우선 탐색) - 인접 리스트 이용 ]
  - 한 방향으로 갈 수 있을 때까지 가다가 더 이상 갈 수 없게 되면 가장 가까운 갈림길로 돌아와서 이 곳으로부터 다른 방향으로 다시 탐색 진행
  - 되돌아가기 위해서는 스택이 필요함
 */
#define MAX_VERTICES 50 // 최대 노드 50개
#define TRUE 1
#define FALSE 0

typedef struct GraphNode{
    int vertex;
    struct GraphNode* link;
} GraphNode;

typedef struct GraphType{
    int n; // 정점의 개수 (실제 그래프의 정점)
    GraphNode* adj_list[MAX_VERTICES];
} GraphType;

// 그래프 초기화 함수
void init(GraphType* g) {
    int v;
    g -> n = 0;
    for(v = 0; v < MAX_VERTICES; v++)
        g -> adj_list[v] = NULL;
}

// 정점 삽입 함수
void insert_vertex(GraphType* g, int v) {
    if(((g -> n) + 1 ) > MAX_VERTICES) { // 정점 하나를 추가한 것 > MAX_VERTICES
        fprintf(stderr, "그래프 : 정점의 개수 초과");
        return;
    }
    g -> n++;
}

// 간선 삽입 함수 - v를 u의 인접 리스트에 삽입함
void insert_edge(GraphType* g, int u, int v) {
    if(u >= g -> n || v >= g -> n) {
        fprintf(stderr, "그래프 : 정점 번호 오류");
        return;
    }
    GraphNode* node = (GraphNode*)malloc(sizeof (GraphNode));

    node -> vertex = v;
    node -> link = g -> adj_list[u];
    g -> adj_list[u] = node;
}

int visited[MAX_VERTICES]; // 노드 방문 표시

// 인접 리스트로 표현된 그래프에 대한 DFS
void dfs_list(GraphType* g, int v) {
    GraphNode* w;
    visited[v] = TRUE; // 정점 v의 방문 표시
    printf("정점 %d -> ", v); // 방문한 정점 출력
    for(w = g -> adj_list[v]; w != NULL; w = w -> link) // 인접한 정점 탐색
        if(!visited[w -> vertex])
            dfs_list(g, w -> vertex); // 인접한 정점인 w에서 DFS 새로 시작
}

// main 함수
int main(void){
    GraphType* g = (GraphType*)malloc(sizeof (GraphType)); // 그래프 생성
    init(g); // 그래프 초기화

    for(int i = 0; i < 4; i++) // 노드 삽입
        insert_vertex(g, i);

    // 간선 삽입
    insert_edge(g, 0, 1); insert_edge(g, 1, 0);
    insert_edge(g, 0, 2); insert_edge(g, 2, 0);
    insert_edge(g, 0, 3); insert_edge(g, 3, 0);
    insert_edge(g, 1, 2); insert_edge(g, 2, 1);
    insert_edge(g, 2, 3); insert_edge(g, 3, 2);

    printf("[ 깊이 우선 탐색 ]\n");
    dfs_list(g, 0); // root 0부터 시작하여 탐색
    printf("\n");

    free(g);

    return 0;
}