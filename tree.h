#pragma once

// 노드 타입 선언
typedef struct Node {
    int value;          // 정수값
    struct Node* left;  // 왼쪽 노드 포인터
    struct Node* right; // 오른쪽 노드 포인터
} Node;

Node* makeTree();
Node* createNode(int value);
void printNode(Node* root);
void preOrder(Node* root);
void inOrder(Node* root);
void postOrder(Node* root);