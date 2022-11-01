#include <stdio.h>
#include <stdlib.h>
/*
  [ 이진 탐색 트리 ]
  - 탐색 작업을 효율적으로 하기 위한 자료구조
  - KEY(왼쪽 서브트리) <= KEY(루트 노드) <= KEY(오른쪽 서브트리)
  - 이진 탐색 트리를 중위 순회하면 오름차순으로 정렬된 값을 얻을 수 있음
  - 이진 탐색 트리의 연산
    1) 탐색 연산 : 탐색하고자 하는 숫자(key)와 노드의 숫자(KEY)를 비교한 결과가 같으면 탐색이 성공적으로 끝남
    2) 삽입 연산 : 이진 탐색 트리에 원소를 삽입하기 위해서는 먼저 탐색을 수행하는 것이 필요 -> 탐색에 실패한 위치가 바로 새로운 노드를 삽입하는 위치
    3) 삭제 연산 : 3가지 경우가 있음
                1. 삭제하려는 노드가 단말 노드인 경우
                  ==> 단말노드의 부모 노드를 찾아서 연결을 끊기
                2. 삭제하려는 노드가 왼쪽이나 오른쪽 서브 트리 중 하나만 가지고 있는 경우
                  ==> 삭제되는 노드가 왼쪽이나 오른쪽 서브 트리 중 하나만 가지고 있을 때, 그 노드는 삭제하고 서브 트리는 부모 노드에 붙여줌
                3. 삭제하려는 노드가 서브 트리 2개 모두 가지고 있는 경우
                  ==> 삭제 노드와 가장 비슷한 값을 가진 노드를 삭제 노드 위치로 가져옴
*/
typedef struct TreeNode {
    int key;
    struct TreeNode* left, *right;
} TreeNode; // 트리 노드를 정의하는 구조체

// 노드 생성 함수
TreeNode* new_node(int item) { // 노드 생성, 데이터를 담고 포인터를 반환
    TreeNode* temp = (TreeNode*) malloc(sizeof (TreeNode)); // 노드 생성

    temp -> key = item;
    temp -> left = temp -> right = NULL; // 왼쪽, 오른쪽 자식이 없다고 표시

    return temp; // 생성한 노드의 포인터 반환
}

// 노드 삽입 함수
TreeNode* insert_node(TreeNode* node, int key) {
    // 트리가 공백이면 새로운 노드를 반환함
    if(node == NULL)
        return new_node(key);

    // 그렇지 않으면 순환적으로 트리를 내려감 **재귀적**
    if(key < node -> key)
        node -> left = insert_node(node -> left, key); // 왼쪽 서브 트리에 삽입
    else if(key > node -> key)
        node -> right = insert_node(node -> right, key); // 오른쪽 서브 트리에 삽압

    // 변경된 root 포인터를 반환함
    return node;
}

// 트리 중위 순회 함수
void inorder(TreeNode* root) {
    if(root) { // root != NULL : 포인터가 NULL이면 값이 0(false)
        inorder(root -> left); // 왼쪽 서브트리 순회
        printf("[%d] ", root -> key); // 노드 방문
        inorder(root -> right); // 오른쪽 서브트리 순회
    }
}

// 트리 탐색 함수
TreeNode* search(TreeNode* node, int key) {
    if(node == NULL)
        return NULL; //  찾고자하는 값이 없음
    if(key == node -> key)
        return node; // (1) 성공
    else if(key < node -> key)
        return search(node -> left, key); // (2) 왼쪽 서브 트리 탐색
    else
        return search(node -> right, key); // (3) 오른쪽 서브 트리 탐색
}

// 삭제할 때 대체할 가장 비슷한 값을 가진 노드를 찾는 함수
TreeNode* min_value_node(TreeNode* node) {
    TreeNode* current = node;

    // 맨 왼쪽 자손 노드를 찾으러 내려감
    while(current -> left != NULL) // 왼쪽에 노드가 있으면
        current = current -> left; // 한 칸 내려감

    return current;
}

// 삭제 함수 - 이진 탐색 트리의 키가 주어지면 키가 저장된 노드를 삭제하고 새로운 루트 노드를 반환함
TreeNode* delete_node(TreeNode* root, int key) {
    if(root == NULL) // 트리가 비었으면
        return root;

    // 만약 키가 루트보다 작으면 왼쪽 서브 트리에 있는 것임
    if(key < root -> key)
        root -> left = delete_node(root -> left, key);
    // 만약 키가 루트보다 크면 오른쪽 서브 트리에 있는 것임
    else if(key > root -> key)
        root -> right = delete_node(root -> right, key);
    else {
        // 첫 번째(삭제하려는 노드가 단말 노드)나 두 번째(삭제하려는 노드가 서브 트리 1개만 가지고 있음) 경우
        if(root -> left == NULL) {
            TreeNode* temp = root -> right;
            free(root);

            return temp;
        }
        else if(root -> right == NULL) {
            TreeNode* temp = root -> left;
            free(root);

            return temp;
        }
        // 세 번째 경우 (삭제하려는 노드가 서브 트리 2개를 모두 가지고 있는 경우)
        TreeNode* temp = min_value_node(root -> right);

        // 중위 순회시 후계 노드를 복사함
        root -> key = temp -> key; // 값 옮기기

        // 중위 순회시 후계 노드를 삭제함
        root -> right = delete_node(root -> right, temp -> key);
    }
    return root;
}

// main 함수
int main(void){
    TreeNode* root = NULL; // 빈 트리
    TreeNode* tmp = NULL;

    root = insert_node(root, 35);
    root = insert_node(root, 22);
    root = insert_node(root, 68);
    root = insert_node(root, 7);
    root = insert_node(root, 26);
    root = insert_node(root, 99);

    inorder(root); printf("\n"); // 중위 순회 + 출력
    root = delete_node(root, 26);
    inorder(root); printf("\n");
    root = delete_node(root, 35);
    inorder(root); printf("\n");
    root = delete_node(root, 22);
    inorder(root); printf("\n");
    root = delete_node(root, 7);
    inorder(root); printf("\n");
    root = delete_node(root, 68);
    inorder(root); printf("\n");
    root = delete_node(root, 99);

    printf("\n\n");

    return 0;
}