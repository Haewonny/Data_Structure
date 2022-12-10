#include <stdio.h>
#include <stdlib.h>
/*
  [ 위상 정렬 (topological sort) ]
  - 방향 그래프에서 간선 <u, v>가 있다면 정점 u는 정점 v를 선행한다고 함
  - 방향 그래프 정점들의 선행 순서를 위배하지 않으면서 모든 정점들을 나열함


  ** 알고리즘 **
  1. 모든 정점이 선행 정점을 가지면 사이클이 존재하므로 위상 정렬 불가
  2. 선행 정점을 가지지 않는 정점 v 선택
  3. v를 출력
  4. v와 v에서 나온 모든 간선들을 그래프에서 삭제
 */
#define MAX_VERTICES 50

typedef struct GraphNode {
    int vertex;
    struct GraphNode* link;
} GraphNode; // 그래프 노드 타입

typedef struct GraphType {
    int n; // 정점의 개수
    GraphNode* adj_list[MAX_VERTICES]; // 노드를 가리키는 포인터
} GraphType;

// 그래프 초기화
void graph_init(GraphType* g) {
    g -> n = 0; // 정점이 없음
    for(int v = 0; v < MAX_VERTICES; v++)
        g -> adj_list[v] = NULL;
}

// 정점 삽입 연산
void insert_vertex(GraphType* g, int v) {
    if(((g -> n) + 1) > MAX_VERTICES) {
        fprintf(stderr, "그래프 : 정점의 개수 초과");
        return;
    }
    g -> n++;
}

// 간선 삽입 연산
void insert_edge(GraphType* g, int u, int v) {
    GraphNode* node;
    if(u >= g -> n || v >= g -> n) {
        fprintf(stderr, "그래프 : 정점 번호 오류");
        return;
    }
    node = (GraphNode*) malloc(sizeof (GraphNode));
    node -> vertex = v;
    node -> link = g -> adj_list[u];
    g -> adj_list[u] = node;
}

// ***** 스택 코드 시작
#define MAX_STACK_SIZE 100 // 스택의 최대 크기

typedef int element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType; // 스택 구조체

// 스택 초기화 함수
void init_stack(StackType* s){ // 포인터를 받아옴
    s -> top = -1; // top에는 아무것도 없는 상태
}

// 공백 상태 검출 함수
int is_empty(StackType* s){
    return (s -> top == -1); // top이 -1이면 공백인 상태(true == 1)
}

// 포화 상태 검출 함수
int is_full(StackType* s){
    return (s -> top == (MAX_STACK_SIZE - 1)); // top이 MAX_STACK_SIZE - 1이면 포화 상태(true == 1)
}

// 삽입 함수
void push(StackType* s, element item){
    if(is_full(s)){ // 스택이 포화 상태이면
        fprintf(stderr, "스택 포화 에러\n");
        return;
    }
    else
        s -> data[++(s -> top)] = item; // 스택 top 인덱스 하나 증가
}

// 삭제 함수
element pop(StackType* s){ // 반환값이 스택 요소(구조체)
    if(is_empty(s)){ // 스택이 공백 상태이면
        fprintf(stderr, "스택 공백 에러\n");
        exit(1);
    }
    else
        return s -> data[(s -> top)--];
}
// ***** 스택 코드 끝

// 위상 정렬 함수
int topo_sort(GraphType* g) {
    int i;
    StackType s; // 스택 생성
    GraphNode* node;

    // 모든 정점의 진입 차수를 계산함
    int* in_degree = (int*) malloc(g -> n * sizeof (int));
    for(i = 0; i < g -> n; i++) {
        in_degree[i] = 0; // 초기화
    }

    for(i = 0; i < g -> n; i++) {
        GraphNode* node = g -> adj_list[i]; // 정점 i에서 나오는 간선들
        while(node != NULL) {
            in_degree[node -> vertex]++;
            node = node -> link;
        }
    }

    // 진입 차수가 0인 정점을 스택에 삽입
    init_stack(&s); // 스택 초기화
    for(i = 0; i < g -> n; i++) {
        if(in_degree[i] == 0)
            push(&s, i);
    }

    // 위상 순서를 생성
    while(!is_empty(&s)) {
        int w;
        w = pop(&s); // 스택에서 하나 뺌

        printf("정점 %d -> ", w); // 정점 출력
        node = g -> adj_list[w]; // 각 정점의 진입 차수를 변경함
        while(node != NULL) {
            int u = node -> vertex;
            in_degree[u]--; // 진입 차수를 감소
            if(in_degree[u] == 0)
                push(&s, u);
            node = node -> link; // 다음 정점
        }
    }

    free(in_degree);
    printf("\n");

    return (i == g -> n); // 반환값이 1이면 성공, 0이면 실패
}

// main 함수
int main() {
    GraphType g; // 그래프 생성
    graph_init(&g); // 그래프 초기화

    insert_vertex(&g, 0); insert_vertex(&g, 1);
    insert_vertex(&g, 2); insert_vertex(&g, 3);
    insert_vertex(&g, 4); insert_vertex(&g, 5);

    // 정점 0의 인접 리스트 생성
    insert_edge(&g, 0, 2); insert_edge(&g, 0, 3);
    // 정점 1의 인접 리스트 생성
    insert_edge(&g, 1, 3); insert_edge(&g, 1, 4);
    // 정점 2의 인접 리스트 생성
    insert_edge(&g, 2, 3); insert_edge(&g, 2, 5);
    // 정점 3의 인접 리스트 생성
    insert_edge(&g, 3, 5);
    // 정점 4의 인접 리스트 생성
    insert_edge(&g, 4, 5);

    topo_sort(&g);

    return 0;
}