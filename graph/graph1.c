#include <stdio.h>
#include <stdlib.h>
/*
  [ 인접 행렬 ]
  - 그래프를 표현하는 방법 중 하나
  - 간선 (i, j)가 그래프에 존재하면, M[i][j] = 1,
                  존재하지 않으면, M[i][j] = 0
 */
#define MAX_VERTICES 50 // 최대 노드 50개

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

// 인접 행렬 출력 함수
void print_adj_mat(GraphType* g) {
    for(int i = 0; i < g -> n; i++) {
        for(int j = 0; j < g -> n; j++)
            printf("%2d ", g -> adj_mat[i][j]);
        printf("\n");
    }
}

// main 함수
int main(void){
    GraphType* g = (GraphType*)malloc(sizeof(GraphType)); // 그래프 생성
    init(g); // 그래프 초기화

    // 정점 삽입
    for(int i = 0; i < 4; i++)
        insert_vertex(g, i);

    // 간선 삽입
    insert_edge(g, 0, 1);
    insert_edge(g, 0, 2);
    insert_edge(g, 0, 3);
    insert_edge(g, 1, 2);
    insert_edge(g, 2, 3);

    print_adj_mat(g);
    free(g);

    return 0;
}