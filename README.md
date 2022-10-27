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
> ### 리스트 (list)
>   > 항목들이 차례대로 저장되어 있고, 리스트의 항목들은 순서 또는 위치를 가짐
>
```
- insert(list, pos, item) : pos 위치에 요소를 추가함 -> 아무 곳에나 데이터를 삽입할 수 있음
- insert_last(list, item) : 맨 끝에 요소를 추가함
- insert_first(list, item) : 맨 처음에 요소를 추가함
- delete(list, pos) : pos 위치의 요소를 제거함
- clear(list) : 리스트의 모든 요소를 제거함
- get_entry(list, pos) : pos 위치의 요소를 반환함
- get_length(list) : 리스트의 길이를 구함
- is_empty(list) : 리스트가 비었는지를 검사함
- is_full(list) : 리스트가 꽉 찼는지를 검사함
- print_list(list) : 리스트의 모든 요소를 표시함 
```
***
> ### 트리 (tree)
>   > 계층적 자료구조, 부모 - 자식 관계의 노드들로 이루어짐
>
```
[ 트리의 용어 ]
- 노드(node) : 트리의 구성요소
- 루트(root) : 부모가 없는 노드
- 서브 트리(subtree) : 하나의 노드와 그 노드의 자손들로 이루어진 트리
- 단말노드(terminal node) : 자식이 없는 노드
- 비단말노드(nonterminal node) : 적어도 하나의 자식을 가지는 노드
- 레벨(level) : 트리의 각층의 번호 -> 맨 위가 1
- 높이(height) : 트리의 최대 레벨
- 차수(degree) : 노드가 가지고 있는 자식 노드의 개수
```
***
> ### 우선순위 큐 (priority queue)
>   > 우선순위를 가진 항목들을 저장하는 큐, FIFO 순서가 아니라 우선순위가 높은 데이터가 먼저 나감 
>
```
- create() : 우선순위 큐를 생성
- init(q) : 우선순위 큐 q를 초기화
- is_empty(q) : 우선순위 큐 q가 비어있는가를 검사함
- is_full(q) : 우선순위 큐 q가 가득 찼는가를 검사함
- insert(q, x) : 우선순위 큐 q에 요소 x를 추가함
- delete(q) : 우선순위 큐로부터 우선순위가 가장 높은 요소를 삭제하고 이 요소를 반환함
- find(q) : 우선순위가 가장 높은 요소를 반환함
```
***