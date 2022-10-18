#include <stdio.h>
#include <stdlib.h>
/*
  [ 포인터를 이용한 이진 트리의 표현 = 링크 표현법 ]
  - 포인터를 이용하여 부모 노드가 자식 노드를 가리키게 하는 방법
  - node에는 자식 노드를 가리키는 노드만 있음
 */
typedef struct TreeNode {
    int data;
    struct TreeNode* left, *right;
} TreeNode; // 트리 노드를 정의하는 구조체
//      n1
//     /  \
//    n2  n3

int main(void){
    TreeNode* n1, * n2, * n3;

    // 노드 3개 생성
    n1 = (TreeNode*)malloc(sizeof (TreeNode));
    n2 = (TreeNode*)malloc(sizeof (TreeNode));
    n3 = (TreeNode*)malloc(sizeof (TreeNode));

    // 첫 번째 노드를 설정
    n1 -> data = 10;
    n1 -> left = n2;
    n1 -> right = n3;

    // 두 번째 노드를 설정
    n2 -> data = 20;
    n2 -> left = NULL; // 비어있음 (자식 X)
    n2 -> right = NULL;

    // 세 번째 노드를 설정
    n3 -> data = 30;
    n3 -> left = NULL;
    n3 -> right = NULL;

    printf("%d\n", n1 -> data);
    printf("%d\n", n1 -> left -> data);
    printf("%d\n", n1 -> right -> data);

    free(n1); free(n2); free(n3);

    return 0;
}