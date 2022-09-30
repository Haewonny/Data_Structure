# Data_Structure
[22-2] 자료구조 정리
***
> ### 스택 (stack)
>   > 쌓아놓은 더미, LIFO(가장 최근에 들어온 데이터가 가장 먼저 나감)
> 
```
- create(max_size) : 최대 크기가 max_size인 공백스택을 생성
- push() : 스택에 주어진 데이터를 추가
- pop() : 스택에서 데이터를 삭제와 동시에 반환
- is_empty() : 스택이 공백상태인지 검사
- is_full() : 스택이 포화상태인지 검사
- peek() : 요소를 스택에서 삭제하지 않고 보기(read)만 하는 연산
```
***
> ### 큐 (queue)
>   > 먼저 들어온 데이터가 먼저 나가는 자료구조, FIFO
>
```
- create(max_size) : 최대 크기가 max_size인 공백큐 생성
- init() : 큐를 초기화
- is_empty() : 큐가 공백상태인지 검사
- is_full() : 큐가 포화상태인지 검사
- enqueue() : 큐의 끝에 요소 추가
- dequeue() : 큐의 맨 앞에 있는 요소를 삭제와 동시에 반환
- peek() : 큐의 맨 앞에 있는 요소를 삭제하지 않고 보기(read)만 하는 연산
```
***
> ### 덱 (deque)
>   > double-ended queue, 큐의 front와 rear에서 모두 삽입과 삭제가 가능한 큐
>
```
- create(max_size) : 최대 크기가 max_size인 공백덱 생성
- init() : 덱을 초기화
- is_empty() : 덱이 공백상태인지 검사
- is_full() : 덱이 포화상태인지 검사
- add_front() : 덱의 앞에 요소 추가
- add_rear() : 덱의 끝에 요소 추가
- delete_front() : 덱의 앞에 있는 요소를 삭제와 동시에 반환
- delete_rear() : 덱의 뒤에 있는 요소를 삭제와 동시에 반환
- get_front() : 덱의 앞에 있는 요소를 삭제하지 않고 보기(read)만 하는 연산
- get_rear() : 덱의 뒤에 있는 요소를 삭제하지 않고 보기(read)만 하는 연산
```
***