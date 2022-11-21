#include <stdio.h>
#include <stdlib.h>
/*
  [ 인접 리스트 ]
  - 그래프를 표현하는 방법 중 하나
  - 각 정점에 인접한 정점들을 연결리스트로 표현
 */
#define MAX_VERTICES 50 // 최대 노드 50개

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

// 인접 리스트 출력 함수
void print_adj_mat(GraphType* g) {
    for(int i = 0; i < g -> n; i++) {
        GraphNode* p = g -> adj_list[i];
        printf("정점 %d의 인접 리스트 ", i);
        while (p != NULL) {
            printf("-> %d ", p -> vertex);
            p = p -> link;
        }
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
    insert_edge(g, 0, 1); insert_edge(g, 1, 0);
    insert_edge(g, 0, 2); insert_edge(g, 2, 0);
    insert_edge(g, 0, 3); insert_edge(g, 3, 0);
    insert_edge(g, 1, 2); insert_edge(g, 2, 1);
    insert_edge(g, 2, 3); insert_edge(g, 3, 2);

    print_adj_mat(g);
    free(g);

    return 0;
}