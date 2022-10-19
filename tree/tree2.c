#include <stdio.h>
#include <stdlib.h>
/*
  [ 이진 트리의 순회 ]
  - 순회(traversal) : 트리의 노드들을 체계적으로 방문하는 것
  - 3가지 기본적인 순회 방법 => **루트 방문이 언제인지?**
    ( V : 루트 / L : 왼쪽 서브 트리 / R : 오른쪽 서브 트리 )
    1) 전위 순회 (preorder traversal)
       : VLR, 자손 노드보다 루트 노드를 먼저 방문
         (ex) 구조회된 문서 출력
    2) 중위 순회 (inorder traversal)
       : LVR, 왼쪽 자손 - 루트 - 오른쪽 자손 순으로 방문
         (ex) 수식 트리
    3) 후위 순회 (postorder traversal)
       : LRV, 루트 노드보다 자손을 먼저 방문
         (ex) 디렉토리 용량 계산
*/
typedef struct TreeNode {
    int data;
    struct TreeNode* left, *right;
} TreeNode; // 트리 노드를 정의하는 구조체

//      15
//     /  \
//    4   20
//    /   / \
//   1   16  25

// 전역 변수로 노드 생성 - 동적 메모리 할당 안 하면 순서가 중요함!
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, &n1, NULL };
TreeNode n3 = { 16, NULL, NULL };
TreeNode n4 = { 25, NULL, NULL };
TreeNode n5 = { 20, &n3, &n4 };
TreeNode n6 = { 15, &n2, &n5 };

TreeNode* root = &n6;
// **중요**
// printf()의 위치 + return 지점은 root == NULL

// 중위 순회
void inorder(TreeNode* root) {
    if(root) { // root != NULL : 포인터가 NULL이면 값이 0(false)
        inorder(root -> left); // 왼쪽 서브트리 순회
        printf("%d ", root -> data); // 노드 방문
        inorder(root -> right); // 오른쪽 서브트리 순회
    }
}

// 전위 순회
void preorder(TreeNode* root) {
    if(root) {
        printf("%d ", root -> data); // 노드 방문
        preorder(root -> left); // 왼쪽 서브트리 순회
        preorder(root -> right); // 오른쪽 서브트리 순회
    }
}

// 후위 순회
void postorder(TreeNode* root) {
    if(root) {
        postorder(root -> left); // 왼쪽 서브트리 순회
        postorder(root -> right); // 오른쪽 서브트리 순회
        printf("%d ", root -> data); // 노드 방문
    }
}

int main(void){
    printf("중위 순회 = ");
    inorder(root);
    printf("\n");

    printf("전위 순회 = ");
    preorder(root);
    printf("\n");

    printf("후위 순회 = ");
    postorder(root);
    printf("\n");

    return 0;
}