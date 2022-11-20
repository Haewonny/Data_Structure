#include <stdio.h>
#include <stdlib.h>
/*
  [ DFS (깊이 우선 탐색) - 인접 행렬 이용 ]
  - 한 방향으로 갈 수 있을 때까지 가다가 더 이상 갈 수 없게 되면 가장 가까운 갈림길로 돌아와서 이 곳으로부터 다른 방향으로 다시 탐색 진행
  - 되돌아가기 위해서는 스택이 필요함
 */
#define MAX_VERTICES 50 // 최대 노드 50개
#define TRUE 1
#define FALSE 0

typedef struct GraphType{
    int n; // 정점의 개수 (실제 그래프의 정점)
    int adj_mat[MAX_VERTICES][MAX_VERTICES];
} GraphType;

// 그래프 초기화 함수
void init(GraphType* g) {
    int r, c;
    g -> n = 0; // 노드가 0개
    for(r = 0; r < MAX_VERTICES; r++)
        for(c = 0; c < MAX_VERTICES; c++)
            g -> adj_mat[r][c] = 0; // 간선이 없으므로 행렬에 다 0을 채움
}

// 정점 삽입 함수
void insert_vertex(GraphType* g, int v) {
    if(((g -> n) + 1 ) > MAX_VERTICES) { // 정점 하나를 추가한 것 > MAX_VERTICES
        fprintf(stderr, "그래프 : 정점의 개수 초과");
        return;
    }
    g -> n++;
}

// 간선 삽입 함수
void insert_edge(GraphType* g, int start, int end) {
    if(start >= g -> n || end >= g -> n) {
        fprintf(stderr, "그래프 : 정점 번호 오류");
        return;
    }
    g -> adj_mat[start][end] = 1;
    g -> adj_mat[end][start] = 1;
}

int visited[MAX_VERTICES]; // 노드 방문 표시

// 인접 행렬로 표현된 그래프에 대한 DFS
void dfs_mat(GraphType* g, int v) {
    visited[v] = TRUE; // 정점 v의 방문 표시
    printf("정점 %d -> ", v); // 방문한 정점 출력
    for(int w = 0; w < g -> n; w++) // 인접한 정점 탐색 -> 같은 행
        if(g -> adj_mat[v][w] && !visited[w])
            dfs_mat(g, w); // 인접한 정점인 w에서 DFS 새로 시작
}

// main 함수
int main(void){
    GraphType* g = (GraphType*)malloc(sizeof (GraphType)); // 그래프 생성
    init(g); // 그래프 초기화

    for(int i = 0; i < 4; i++) // 노드 삽입
        insert_vertex(g, i);

    // 간선 삽입
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    printf("[ 깊이 우선 탐색 ]\n");
    dfs_mat(g, 0); // root 0부터 시작하여 탐색
    printf("\n");

    free(g);

    return 0;
}