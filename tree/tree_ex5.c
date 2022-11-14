#include <stdio.h>
/*
  [ 이진 트리 연산 - 단말 노드 개수 세기 ]
  - 왼쪽 단말 노드 수 + 오른쪽 단말 노드 수
*/
typedef struct TreeNode {
    int data;
    struct TreeNode* left, *right;
} TreeNode; // 트리 노드를 정의하는 구조체

// 단말 노드 개수 세는 함수
int get_leaf_count(TreeNode* node) {
    int cnt = 0;
    if(node != NULL) {
        if(node -> left == NULL && node -> right == NULL)
            return 1;
        else
            cnt = get_leaf_count(node -> left) + get_leaf_count(node -> right);
    }
    return cnt;
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
    printf("단말 노드의 개수는 = %d", get_leaf_count(root));

    return 0;
}