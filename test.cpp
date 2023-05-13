#include <stdio.h>
#include "tree.h"


int test() {
    Node* root = makeTree();

    printf("Pre-order: ");
    preOrder(root);
    printf("\n");

    printf("In-order: ");
    inOrder(root);
    printf("\n");

    printf("Post-order: ");
    postOrder(root);
    printf("\n");

    return 0;
}