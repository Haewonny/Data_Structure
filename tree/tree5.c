#include <stdio.h>
/*
  [ 스레드 이진 트리 ]
  - 재귀 함수나 스택 없이 중위 순회가 가능함
  - 이진 트리의 NULL 링크를 이용하여 순환 호출 없이도 트리의 노드들을 순회함
  - NULL 링크에 중위 순회시에 후속 노드인 중위 후속자(inorder successor)를 저장시켜 놓은 트리가 스레드 이진 트리(threaded binary tree)
*/
typedef struct TreeNode {
    int data;
    struct TreeNode* left, *right;
    int is_thread; // 만약 오른쪽 링크가 스레드이면 TRUE -> 링크가 자식을 가리키는 것인지 스레드를 가리키는 것인지 구별하기 위해 필요
} TreeNode; // 트리 노드를 정의하는 구조체

// 중위 순회의 다음 노드를 알려주는 함수
TreeNode* find_successor(TreeNode* p) {
    // q는 p의 오른쪽 포인터
    TreeNode *q = p->right;

    // 경우 1) 만약 오른쪽 포인터가 NULL이거나 스레드이면 오른쪽 포인터를 반환함
    if (q == NULL || p->is_thread == 1)
        return q;

    // 경우 2) 만약 오른쪽 자식이면 다시 가장 왼쪽 노드로 이동
    while (q->left != NULL)
        q = q->left;

    return q;
}

// 스레드 중위 순회 함수
void thread_inorder(TreeNode* t) {
    TreeNode* q;
    q = t;
    while(q -> left) // 가장 왼쪽 노드로 감
        q = q -> left;
    do {
        printf("%d ", q -> data); // 데이터 출력
        q = find_successor(q); // 후속자 함수 호출 (중위 순회의 다음 노드를 알려줌)
    } while(q); // q가 NULL(false)가 아닌 동안
}

// 트리 만들기 - 마지막에 0, 1로 스레드인지 구분
TreeNode n1 = { 1, NULL, NULL, 1 };
TreeNode n4 = { 4, NULL, NULL, 1 };
TreeNode n7 = { 7, &n1, &n4, 0 };
TreeNode n16 = { 16, NULL, NULL, 1 };
TreeNode n25 = { 25, NULL, NULL, 0 };
TreeNode n8 = { 8, &n16, &n25, 0 };
TreeNode n5 = { 5, &n7, &n8, 0 };
//      5
//     /  \
//    7     8
//   / \    / \
//  1/ 4/  16/ 25
TreeNode* root = &n5;

int main(void){
    // 스레드 설정
    n1.right = &n7;
    n4.right = &n5;
    n16.right = &n8;

    // 중위 순회
    printf("중위 순회 = ");
    thread_inorder(root);
    printf("\n");

    return 0;
}