#include <stdio.h>
#include <math.h>
/*
  [ 이진 트리 연산 - 높이 계산]
  - 서브 트리에 대하여 순환 호출하고 서브 트리의 반환 값 중에서 최대값을 구하여 반환
*/
typedef struct TreeNode {
    int data;
    struct TreeNode* left, *right;
} TreeNode; // 트리 노드를 정의하는 구조체

// 높이 계산하는 함수
int get_height(TreeNode* node) {
    int height = 0;
    if(node != NULL)
        height = 1 + fmax(get_height(node -> left), get_height(node -> right)); // 최대값 + 1 -> 트리의 높이
    return height;
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
    printf("트리의 높이는 = %d", get_height(root));

    return 0;
}