#include <stdio.h>
/*
  [ 이진 트리 연산 - 노드 개수 세기 ]
  - 이진 트리 안의 노드의 개수를 계산
  - 각각의 서브 트리에 대하여 순환 호출한 다음, 반환되는 값에 1을 더하여 반환
*/
typedef struct TreeNode {
    int data;
    struct TreeNode* left, *right;
} TreeNode; // 트리 노드를 정의하는 구조체

// 노드 개수 세는 함수
int get_node_count(TreeNode* node) {
    int cnt = 0;
    if(node != NULL)
        cnt = 1 + get_node_count(node -> left) + get_node_count(node -> right);
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
    printf("노드의 개수는 = %d", get_node_count(root));

    return 0;
}