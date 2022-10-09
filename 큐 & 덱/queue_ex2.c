#include <stdio.h>
#include <stdlib.h>
#include <time.h> // random number 사용
/*
  [ 은행 업무 시뮬레이션 ]
  - 큐잉 모델(queueing model) : 고객에 대한 서비스를 수행하는 서버와 서비스를 받는 고객들로 이루어짐
  - 고객들이 기다리는 평균 시간을 계산해 보려고 함
 */
// 원형큐 코드는 queue2.c에 있는 거 활용
// ***** 원형큐 코드의 시작
#define MAX_QUEUE_SIZE 5 // 큐의 최대 크기
typedef struct {
    int id;
    int arrival_time;
    int service_time;
} element; // 큐의 요소 타입 (구조체)

typedef struct { // 큐 타입
    int front;
    int rear;
    element data[MAX_QUEUE_SIZE]; // 데이터 배열
} QueueType;

// 오류 함수 -> 오류 메시지 출력
void error(char* message) {
    fprintf(stderr, "%s\n", message);
    exit(1); // 종료
}

// 큐 초기화 - 초기 상태는 front, rear 값이 0
void init_queue(QueueType* q) {
    q -> front = 0;
    q-> rear = 0;
}

// 포화 상태 검출 함수 - 큐에 빈 공간이 없나?
// **표현 방법 알아두기 => 인덱스 맞추려고
int is_full(QueueType* q) {
    return ((q -> rear + 1) % MAX_QUEUE_SIZE == q -> front);
}

// 공백 상태 검출 함수 - 큐가 비었는가?
int is_empty(QueueType* q) {
    return (q -> front == q -> rear); // front == rear 이면 true(1)
}

// 삽입 함수
void enqueue(QueueType* q, element item) {
    if(is_full(q)) // 큐가 포화 상태이면
        error("큐가 포화상태입니다.");

    // **삽입 전에 rear = 7이었다면 rear = (7+1)%8 = 0이 됨!
    q -> rear = (q -> rear + 1) % MAX_QUEUE_SIZE; // rear가 가리키는 곳 이동
    q -> data[q -> rear] = item; // 값 대입
}

// 삭제 함수
element dequeue(QueueType* q) {
    if(is_empty(q)) // 큐가 공백 상태이면
        error("큐가 공백상태입니다.");

    q -> front = (q -> front + 1) % MAX_QUEUE_SIZE;
    return q -> data[q -> front];
}
// ***** 원형큐 코드의 끝

// main 함수
int main(void){
    int minutes = 60; // 총 영업 시간
    int total_wait = 0; // 전체 고객의 대기시간 합계
    int total_customers = 0; // 서비스한 고객의 수
    int service_time = 0; // 고객 한 명 서비스 시간 (1분 - 3분)
    int service_customer; // 현재 처리 중인 고객의 번호
    element customer; // 큐의 요소 타입 - id, arrival_time, service_time 가짐

    QueueType queue; // 큐 생성
    init_queue(&queue); // 큐 초기화

    srand(time(NULL)); // 난수 시퀀스 초기화

    for(int clock = 0; clock < minutes; clock++) { // 1분 단위로 한 시간동안 수행
        /*
          고객이 도착했는지 확인한다.
            도착했다면 고객 번호 지정, 서비스 시간(1-3분 랜덤)을 세팅하여 큐에 삽입한다.
          현재 서비스 중인 고객이 있다면 1분간 서비스를 한다.
            없다면 큐에서 고객 한 명을 꺼내어 대기 시간을 출력하고, 전체 대기시간에 더한다.
            서비스 시간을 세팅해 놓는다.
         */
        printf("현재시각 = %d\n", clock);
        if((rand() % 10) < 3) { // 고객 도착 상황 (0 - 9의 숫자로 변환)
            // customer 구조체 변수
            customer.id = total_customers++;
            customer.arrival_time = clock; // 대기 시간을 체크하기 위해서 도착 시간 저장
            customer.service_time = rand() % 3 + 1; // 서비스는 1-3분 사이로 지정

            enqueue(&queue, customer); // 큐에 고객 삽입
            printf("고객 %d이 %d분에 들어옵니다. 업무 처리 시간 = %d\n", customer.id, customer.arrival_time, customer.service_time);
        }
        if(service_time > 0) { // 현재 처리 중인 고객이 있다면 1분간 처리
            printf("고객 %d 업무 처리 중입니다.\n", service_customer);
            service_time--;
        }
        else {
            if(!is_empty(&queue)) { // 대기 중인 고객이 있다면
                customer = dequeue(&queue); // 고객 서비스 시간
                service_customer = customer.id;
                service_time = customer.service_time; // 고객의 서비스 시간 세팅

                printf("고객 %d이 %d분에 업무를 시작합니다. 대기 시간은 %d분이었습니다.\n", customer.id, clock, clock - customer.arrival_time); // 대기 시간은 '현재 시간 - 도착 시간'
                total_wait += (clock - customer.arrival_time); // 전체 대기 시간 업데이트
            }
        }
    }
    printf("전체 대기 시간 = %d분 \n", total_wait);
    return 0;
}
