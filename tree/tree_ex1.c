#include <stdio.h>
#include <stdlib.h>
/*
  [ 수식 트리 계산 ]
  - 후위 순회 사용
  - 서브 트리의 값을 순환 호출로 계산
  - 비단말 노드를 방문할 때는 "양쪽 서브 트리의 값"을 피연산자로 하여,
    현재 방문 중인 노드에 저장되어 있는 연산자를 이용하여 계산함
*/
typedef struct TreeNode {
    int data;
    struct TreeNode* left, *right;
} TreeNode; // 트리 노드를 정의하는 구조체

// 트리 만들기
TreeNode n1 = { 1, NULL, NULL };
TreeNode n2 = { 4, NULL, NULL };
TreeNode n3 = { '*', &n1, &n2 };
TreeNode n4 = { 16, NULL, NULL };
TreeNode n5 = { 25, NULL, NULL };
TreeNode n6 = { '+', &n4, &n5 };
TreeNode n7 = { '+', &n3, &n6 };
//      +
//     /  \
//    *    +
//   / \  / \
//  1  4 16 25

TreeNode* Exp = &n7;

// 수식 계산 함수
int evaluate(TreeNode* root) {
    if (root == NULL)
        return 0;
    if (root -> left == NULL && root -> right == NULL) // 단말노드인 경우에
        return root -> data; // data 그냥 return
    else {
        int op1 = evaluate(root -> left);
        int op2 = evaluate(root -> right);
        printf("%d %c %d을 계산합니다.\n", op1, root -> data, op2);
        switch (root -> data) {
            case '+':
                return op1 + op2;
            case '-':
                return op1 - op2;
            case '*':
                return op1 * op2;
            case '/':
                return op1 / op2;
        }
    }
    return 0;
}

int main(void){
    printf("수식의 값은 %d입니다. \n", evaluate(Exp));

    return 0;
}