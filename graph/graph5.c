#include <stdio.h>
#include <stdlib.h>
/*
  [ BFS (너비 우선 탐색) - 인접 행렬 이용 ]
  - 시작 정점으로부터 가까운 정점들을 먼저 방문하고, 멀리 떨어져 있는 정점들은 나중에 방문하는 탐색 방법
  - 큐를 사용하여 구현됨
 */
#define MAX_VERTICES 50 // 최대 노드 50개
#define MAX_QUEUE_SIZE 5 // 큐의 최대 크기

// ***** 큐 코드 시작
typedef int element; // 큐의 요소 타입 (정수)
typedef struct { // 큐 타입
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE]; // 데이터 배열
} QueueType;

// 에러 함수 -> 오류 메시지 출력
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1); // 종료
}

// 큐 초기화 - 초기 상태는 front, rear 값이 -1
void init_queue(QueueType* q) {
    q -> front = -1;
    q-> rear = -1;
}

// 포화 상태 검출 함수
int is_full(QueueType* q) {
    if(q -> rear == MAX_QUEUE_SIZE - 1) // rear가 가리키는 곳이 배열의 마지막 원소임
        return 1;
    else
        return 0;
}

// 공백 상태 검출 함수
int is_empty(QueueType* q) {
    if(q -> front == q -> rear)
        return 1;
    else
        return 0;
}

// 삽입 함수
void enqueue(QueueType* q, int item) {
    if(is_full(q)){ // 큐가 포화 상태이면
        error("큐가 포화상태입니다.");
        return; // void라서
    }
    q -> data[++(q -> rear)] = item; // rear가 가리키는 곳을 오른쪽으로 한 칸 옮기고 item 값 대입
}

// 삭제 함수
int dequeue(QueueType* q) {
    if(is_empty(q)){ // 큐가 공백 상태이면
        error("큐가 공백상태입니다.");
        return -1;
    }
    int item = q -> data[++(q -> front)]; // front는 빠져나간 곳(빈 곳)을 가리키게 됨
    return item;
}
// ***** 큐 코드 끝

// ***** 그래프 코드 시작
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
// ***** 그래프 코드 끝

int visited[MAX_VERTICES]; // 노드 방문 표시

// 인접 행렬로 표현된 그래프에 대한 BFS
void bfs_mat(GraphType* g, int v) {
    int w;
    QueueType q; // 큐 생성
    init_queue(&q); // 큐 초기화

    visited[v] = 1; // 정점 v 방문 표시
    printf("%d 방문 -> ", v); // 방문하면 출력
    enqueue(&q, v); // 시작 정점을 큐에 저장

    while(!is_empty(&q)) { // 큐가 비어있지 않다면
        v = dequeue(&q); // 큐에 정점 추출
        for(w = 0; w < g -> n; w++) { // 인접 정점 탐색
            if(g -> adj_mat[v][w] && !visited[w]) { // ** v와 연결이 안 되어있고, 방문을 안 했다면
                visited[w] = 1; // 방문 표시
                printf("%d 방문 -> ", w);
                enqueue(&q, w); // 방문한 정점을 큐에 저장
            }
        }
    }
}

// main 함수
int main(void){
    GraphType* g = (GraphType*) malloc(sizeof(GraphType)); // 그래프 생성
    init(g); // 그래프 초기화

    // 노드 삽입
    for(int i = 0; i < 6; i++)
        insert_vertex(g, i);

    // 간선 삽입
    insert_edge(g, 0, 2);
    insert_edge(g, 2, 1);
    insert_edge(g, 2, 3);
    insert_edge(g, 0, 4);
    insert_edge(g, 4, 5);
    insert_edge(g, 1, 5);

    printf("[ 너비 우선 탐색 ]\n");
    bfs_mat(g, 0); // 0번 노드부터 방문
    printf("\n");

    free(g);

    return 0;
}