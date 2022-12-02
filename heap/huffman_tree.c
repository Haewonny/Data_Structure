#include <stdio.h>
#include <stdlib.h>
/*
  [ 허프만 코드 (Huffman codes) ]
  - 이진 트리는 각 글자의 빈도가 알려져 있는 텍스트의 내용을 압축하는 데 사용될 수 있음
    -> 이런 종류의 이진 트리를 '허프만 코딩 트리'라고 부름
  - 허프만 코드 생성 절차
    단계 1) 빈도수의 오름차순으로 글자들을 나열한다. 글자 1개로 구성된 이진 트리 n개를 생성한다.
           각 노드의 값은 해당 글자의 빈도수이다.
    단계 2) 트리들 중에서 루트의 값이 가장 작은 트리 2개를 찾아내어 합친다.
           즉, 루트 노드 1개를 추가하고, 찾아낸 두 트리가 왼쪽, 오른쪽 서브 트리가 되도록 한다.
           새로운 루트의 값은 각 자식 노드의 값의 합이 된다.
    단계 3) 루트의 값을 기준으로, 다시 트리들을 오름차순으로 나열한다.
    단계 4) 트리들이 모두 뭉쳐져서 1개가 될 때까지 단계 2와 단계 3을 반복한다.
    단계 5) 최종 생성된 트리에서, 왼쪽 간선은 비트 1을 나타내고, 오른쪽 간선은 비트 0을 나타낸다.
           각 글자에 대한 허프만 코드는 루트 노드에서 해당 단말 노드까지의 경로에 있는 간선의 레벨 값을 읽으면 된다.
 */
#define MAX_ELEMENT 200 // 힙의 최대 크기

typedef struct TreeNode {
    int weight;
    char ch;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct {
    TreeNode* ptree;
    char ch; // 문자
    int key; // 빈도수
} element;

typedef struct {
    element heap[MAX_ELEMENT];
    int heap_size; // 현재 힙에 저장되어 있는 데이터의 개수 저장
} HeapType;

// 힙 생성 함수
HeapType* create() {
    return (HeapType*) malloc(sizeof (HeapType)); // 포인터 반환
}

// 힙 초기화 함수
void init(HeapType* h) {
    h -> heap_size = 0; // 힙에 아무것도 없는 상태
}

// 삽입 함수 - 현재 요소의 개수가 heap_size인 힙 h에 item을 삽입함 ** min heap **
void insert_min_heap(HeapType* h, element item) {
    int i;
    i = ++(h -> heap_size); // 일단 인덱스 위치를 확인, 삽입은 밑에서!

    // 트리를 거슬러 올라가면서 부모 노드와 비교하는 과정
    while((i != 1) && (item.key < h -> heap[i / 2].key)) { // root가 아님 && 넣을 값 < 부모 노드의 값
        h -> heap[i] = h -> heap[i / 2]; // 자식 노드와 부모 노드 교환
        i /= 2; // 인덱스 한 칸 올라감
    }
    h -> heap[i] = item; // 새로운 노드를 삽입
}

// 삭제 함수
element delete_min_heap(HeapType* h) {
    int parent, child;
    element item, temp;

    item = h -> heap[1]; // 제거할 root
    temp = h -> heap[(h -> heap_size)--]; // 마지막 노드에 있는 원소

    parent = 1;
    child = 2; // 왼쪽 child

    while(child <= h -> heap_size) { // child 인덱스가 heap_size를 넘어갈 수는 없음
        // 현재 노드의 자식노드 중 더 작은 자식 노드를 찾음
        if((child < h -> heap_size) && (h -> heap[child].key) > h -> heap[child + 1].key) // 형제가 있음 && 왼쪽 자식 값 > 오른쪽 자식 값
            child++;
        if(temp.key < h -> heap[child].key) // 마지막 노드에 있던 값 < 자식 노드의 값
            break; // 루프를 벗어난 후, 이 child의 부모 자리에 노드 삽입
        // 한 단계 아래로 이동
        h -> heap[parent] = h -> heap[child];
        parent = child; // 한 층 내려감
        child *= 2; // 왼쪽 자식 노드
    }
    h -> heap[parent] = temp; // 힙 성질을 만족하는 위치에 삽입

    return item;
}

// ** 이진 트리 생성 함수
TreeNode* make_tree(TreeNode* left, TreeNode* right) {
    TreeNode* node = (TreeNode*) malloc(sizeof (TreeNode));
    node -> left = left;
    node -> right = right;

    return node;
}

// ** 이진 트리 제거 함수
void destory_tree(TreeNode* root) {
    if(root == NULL)
        return;
    destory_tree(root -> left);
    destory_tree(root -> right);
    free(root);
}

// 단말 노드 검사 함수 - ∵ 단말 노드에서 코드를 출력하니까
int is_leaf(TreeNode* root) {
    return !(root -> left) && !(root -> right);
}

// 배열 출력 함수
void print_array(int codes[], int n) {
    for(int i = 0; i < n; i++)
        printf("%d", codes[i]);
    printf("\n");
}

// 코드 출력 함수
void print_codes(TreeNode* root, int codes[], int top) {
    // 1을 저장하고 순환호출 함
    if(root -> left) {
        codes[top] = 1;
        print_codes(root -> left, codes, top + 1);
    }

    // 0을 저장하고 순환호출 함
    if(root -> right) {
        codes[top] = 0;
        print_codes(root -> right, codes, top + 1);
    }

    // 단말노드이면 코드를 출력함
    if(is_leaf(root)) {
        printf("%c : ", root -> ch);
        print_array(codes, top);
    }
}

// ** 허프만 코드 생성 함수
void huffman_tree(int freq[], char ch_list[], int n) {
    int i;
    TreeNode* node, * x;
    HeapType* heap;
    element e, e1, e2; // 힙에 들어가는 element
    int codes[100];
    int top = 0;

    heap = create(); // 힙 생성
    init(heap); // 힙 초기화

    for(i = 0; i < n; i++) { // 모든 글자를 heap에 삽입
        node = make_tree(NULL, NULL);
        e.ch = node -> ch = ch_list[i]; // 노드 내용 채우기 - 문자
        e.key = node -> weight = freq[i]; // 노드 내용 채우기 - 빈도수
        e.ptree = node;

        insert_min_heap(heap, e);
    }

    for(i = 1; i < n; i++) {
        // 최소값을 가지는 두 개의 노드를 삭제
        e1 = delete_min_heap(heap);
        e2 = delete_min_heap(heap);

        // 두 개의 노드를 합침
        x = make_tree(e1.ptree, e2.ptree);
        e.key = x -> weight = e1.key + e2.key;
        e.ptree = x;
        printf("%d + %d -> %d \n", e1.key, e2.key, e.key);

        insert_min_heap(heap, e);
    }

    e = delete_min_heap(heap); // 최종 트리 - e가 가리키는 트리
    print_codes(e.ptree, codes, top);
    destory_tree(e.ptree);
    free(heap);
}

// main 함수
int main(void){
    char ch_list[] = { 's', 'i', 'n', 't', 'e' };
    int freq[] = { 4, 6, 8, 12, 15 };

    huffman_tree(freq, ch_list, 5);
    
    return 0;
}