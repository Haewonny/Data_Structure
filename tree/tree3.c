#include <stdio.h>
#include <stdlib.h>
/*
  [ 반복적인 순회 - 중위 순회 ]
  - 중위 순회 (inorder traversal) : LVR, 왼쪽 자손 - 루트 - 오른쪽 자손 순으로 방문
  - **중요**
    while(1) {
        1. 현재의 root를 시작으로 해서, (for문) 왼쪽 방향으로 child, grand child, great-grand child, ... 등을
           계속 따라 내려가면서 그들을 모두 stack에 넣음
        2. NULL node를 만나면 스택에서 노드 1개를 꺼내어 방문을 함 (스택에 노드가 없으면 루프를 나옴)
        3. 방문한 노드의 오른쪽 child를 root로 만들어 놓음
    }
*/
#define SIZE 100

typedef struct TreeNode {
    int data;
    struct TreeNode* left, *right;
} TreeNode; // 트리 노드를 정의하는 구조체

int top = -1;
TreeNode* stack[SIZE]; // 포인터 배열

// 스택 push, pop 구현
void push(TreeNode* p) {
    if(top < SIZE - 1) // 다 안 찼으면
        stack[++top] = p;
}

TreeNode* pop() {
    TreeNode* p = NULL; // 초기화 (스택 안에 아무것도 없을 때)
    if(top >= 0) // 스택에 뭐가 있으면
        p = stack[top--];
    return p; // pop한 거 반환
}

// 반복적인 중위 순회
void inorder_iter(TreeNode* root) {
    // 무한 루프
    while(1) {
        // 1. 왼쪽 방향으로 따라 내려가면서 모두 스택에 삽입
        for(; root; root = root -> left) // root != NULL인 동안 반복
            push(root);

        // 2. NULL 노드를 만나면(root == NULL) 스택에서 노드 한 개 꺼내서 방문
        root = pop();
        if(!root) // 스택에 노드가 없으면(root == NULL)
            break; // 루프를 나옴
        printf("[%d] ", root -> data); // 방문 -> data 출력

        // 3. 방문한 노드의 오른쪽 child를 root로 만들어 놓음
        root = root -> right;
    }
}

// 트리 만들기
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };
//      15
//     /  \
//    4   20
//    /   / \
//   1   16  25
TreeNode* root = &n6;

int main(void){
    printf("반복적인 중위 순회 = ");
    inorder_iter(root);
    printf("\n");

    return 0;
}