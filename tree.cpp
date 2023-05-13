#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

// �־��� ������ ���ο� Node�� �����Ͽ� ��ȯ�ϴ� �Լ�
Node* createNode(int value) {
    Node* node = (Node*)malloc(sizeof(Node)); // Node ����ü�� ���� �޸� �Ҵ�
    node->value = value; // Node�� ���� ����
    node->left = NULL; // ���� �ڽ� Node�� �����͸� NULL�� �ʱ�ȭ
    node->right = NULL; // ������ �ڽ� Node�� �����͸� NULL�� �ʱ�ȭ
    return node; // ������ Node�� ��ȯ
}

// �׽�Ʈ�� ���� Ʈ���� �����Ͽ� ��ȯ�ϴ� �Լ�
Node* makeTree() {
    // ��� ����
    Node* root = createNode(100);
    Node* node1 = createNode(200);
    Node* node2 = createNode(300);
    Node* node3 = createNode(400);
    Node* node4 = createNode(500);

    // ��� �� ����
    root->left = node1;
    root->right = node2;
    node2->left = node3;
    node2->right = node4;

    // ������ ���� Ʈ���� ��Ʈ ��带 ��ȯ
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

// �־��� ��带 ���� ��ȸ�ϸ� ����� ���� ����ϴ� �Լ�
void preOrder(Node* root) {
    if (root == NULL) return; // ��尡 NULL�� ��� �Լ� ����
    printf("%d ", root->value); // ����� ���� ���
    preOrder(root->left); // ����� ���� �ڽ� ��带 ���� ��ȸ
    preOrder(root->right); // ����� ������ �ڽ� ��带 ���� ��ȸ

}

// �־��� ��带 ���� ��ȸ�ϸ� ����� ���� ����ϴ� �Լ�
void inOrder(Node* root) {
    if (root == NULL) return; // ��尡 NULL�� ��� �Լ� ����
    inOrder(root->left); // ����� ���� �ڽ� ��带 ���� ��ȸ
    printf("%d ", root->value); // ����� ���� ���
    inOrder(root->right); // ����� ������ �ڽ� ��带 ���� ��ȸ

}

// �־��� ��带 ���� ��ȸ�ϸ� ����� ���� ����ϴ� �Լ�
void postOrder(Node* root) {
    if (root == NULL) return; // ��尡 NULL�� ��� �Լ� ����
    postOrder(root->left); // ����� ���� �ڽ� ��带 ���� ��ȸ
    postOrder(root->right); // ����� ������ �ڽ� ��带 ���� ��ȸ
    printf("%d ", root->value);
}