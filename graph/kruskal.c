#include <stdio.h>
#include <stdlib.h>
/*
  [ Kruskal의 MST 알고리즘 ]
  - 탐욕적인 방법(greedy) : 각 단계에서 최선의 답을 선택하는 과정을 반복함으로써 최종적인 해답에 도달
  - Kruskal MST 알고리즘은 탐욕적인 방법이 항상 최적의 답을 줌

  ** 알고리즘 **
  1. 그래프의 에지들을 (비용의) 오름차순으로 정렬함
  2. 에지들을 순서대로 검사해 가면서, MST에 하나씩 삽입함
  3. 에지를 MST에 포함시키려고 할 때, 사이클이 생기지 않으면 포함시킴
                              사이클이 생기면 포함시키지 않음
    => 사이클이 생기는지는 union-find 알고리즘을 통해서 알 수 있음!
  4. 총 n-1개의 에지가 포함되면 MST가 완성된 것
 */

#define MAX_VERTICES 100 // 프로그램에서 다루는 그래프의 최대 크기

struct Edge { // 간선을 나타내는 구조체
    int start, end; // 간선의 양끝 노드
    int weight; // 가중치
};

typedef struct GraphType { // 그래프
    int n; // 간선의 개수
    struct Edge edges[MAX_VERTICES * MAX_VERTICES];
} GraphType;

// 그래프 초기화 - 간선이 하나도 없는 상태로 만들기
void graph_init(GraphType* g) {
    g -> n = 0;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int start, int end, int w) {
    g -> edges[g -> n].start = start;
    g -> edges[g -> n].end = end;
    g -> edges[g -> n].weight = w;
    g -> n++;
}

int parent[MAX_VERTICES]; // 트리를 저장하는 부모 노드

// parent 배열 초기화
void set_init(int n) { // n : 그래프에 속해 있는 노드의 개수
    for(int i = 0; i < n; i++)
        parent[i] = -1; // 각 원소를 -1로 초기화
}

// Find : c가 속하는 집합을 반환함 (루트를 찾아줌)
int set_find(int c) {
    if(parent[c] == -1)
        return c; // c가 루트임
    while(parent[c] != -1)
        c = parent[c];
    return c;
}

// UNION : 두 개의 원소가 속한 집합을 합침
void set_union(int a, int b) {
    int root1 = set_find(a); // 노드 a의 루트를 찾음
    int root2 = set_find(b); // 노드 b의 루트를 찾음
    if(root1 != root2) // 루트가 같지 않으면
        parent[root1] = root2; // 트리를 합침
}

// qsort()에서 사용되는 compare 함수
// 간선 a의 가중치가 크면 양수, 작으면 음수, 같으면 0 반환
int compare(const void* a, const void* b) {
    struct Edge* x = (struct Edge*) a;
    struct Edge* y = (struct Edge*) b;
    return (x -> weight - y -> weight);
}

// Kruskal의 최소 비용 신장 트리 함수
void kruskal(GraphType* g) {
    int edge_accepted = 0; // 현재까지 선택된 간선의 수
    int uset, vset;
    struct Edge e;

    set_init(g -> n);
    qsort(g -> edges, g -> n, sizeof (struct Edge), compare); // 간선을 오름차순으로 퀵정렬

    printf("Kruskal의 MST 알고리즘 \n");
    int i = 0;
    while(edge_accepted < (g -> n - 1)) { // 간선의 수 < (n - 1)
        e = g -> edges[i];
        uset = set_find(e.start); // 정점 u의 집합 번호
        vset = set_find(e.end); // 정점 v의 집합 번호

        if(uset != vset) { // 서로 속한 집합이 다르면
            printf("간선 (%d, %d) %d 선택\n", e.start, e.end, e.weight);
            edge_accepted++; // 간선 하나 증가
            set_union(uset, vset); // 두 개의 집합을 합침
        }
        i++;
    }
}

// main 함수
int main(void){
    GraphType* g = (GraphType*) malloc(sizeof (GraphType)); // 그래프 생성
    graph_init(g); // 그래프 초기화

    insert_edge(g, 0, 1, 29);
    insert_edge(g, 1, 2, 16);
    insert_edge(g, 2, 3, 12);
    insert_edge(g, 3, 4, 22);
    insert_edge(g, 4, 5, 27);
    insert_edge(g, 5, 0, 10);
    insert_edge(g, 6, 1, 15);
    insert_edge(g, 6, 3, 18);
    insert_edge(g, 6, 4, 25);

    kruskal(g);
    free(g);

    return 0;
}