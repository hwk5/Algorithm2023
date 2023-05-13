#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

int main() {
    printf("make tree\n");

    Node* root = makeTree();
    printNode(root);

    return 0;
}