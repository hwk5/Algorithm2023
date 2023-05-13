#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// 주어진 값으로 새로운 Node를 생성하여 반환하는 함수
Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node)); // Node 구조체를 동적 메모리 할당
    node->value = value; // Node의 값을 설정
    node->left = NULL; // 왼쪽 자식 Node의 포인터를 NULL로 초기화
    node->right = NULL; // 오른쪽 자식 Node의 포인터를 NULL로 초기화
    return node; // 생성한 Node를 반환
}

// 테스트용 이진 트리를 생성하여 반환하는 함수
Node* makeTree() {
    // 노드 생성
    Node* root = createNode(100);
    Node* node1 = createNode(200);
    Node* node2 = createNode(300);
    Node* node3 = createNode(400);
    Node* node4 = createNode(500);

    // 노드 간 연결
    root->left = node1;
    root->right = node2;
    node2->left = node3;
    node2->right = node4;

    // 생성한 이진 트리의 루트 노드를 반환
    return root;
}

void printNode(Node* root) {
    printf("Pre-order: ");
    preOrder(root);
    printf("\n");

    printf("In-order: ");
    inOrder(root);
    printf("\n");

    printf("Post-order: ");
    postOrder(root);
    printf("\n");
}

// 주어진 노드를 전위 순회하며 노드의 값을 출력하는 함수
void preOrder(Node* root) {
    if (root == NULL) return; // 노드가 NULL인 경우 함수 종료
    printf("%d ", root->value); // 노드의 값을 출력
    preOrder(root->left); // 노드의 왼쪽 자식 노드를 전위 순회
    preOrder(root->right); // 노드의 오른쪽 자식 노드를 전위 순회

}

// 주어진 노드를 중위 순회하며 노드의 값을 출력하는 함수
void inOrder(Node* root) {
    if (root == NULL) return; // 노드가 NULL인 경우 함수 종료
    inOrder(root->left); // 노드의 왼쪽 자식 노드를 중위 순회
    printf("%d ", root->value); // 노드의 값을 출력
    inOrder(root->right); // 노드의 오른쪽 자식 노드를 중위 순회

}

// 주어진 노드를 후위 순회하며 노드의 값을 출력하는 함수
void postOrder(Node* root) {
    if (root == NULL) return; // 노드가 NULL인 경우 함수 종료
    postOrder(root->left); // 노드의 왼쪽 자식 노드를 후위 순회
    postOrder(root->right); // 노드의 오른쪽 자식 노드를 후위 순회
    printf("%d ", root->value);
}