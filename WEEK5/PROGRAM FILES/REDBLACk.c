#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

struct RBNode {
    int value;
    int shade;
    struct RBNode *lchild, *rchild, *parent;
};

struct RBNode *treeRoot = NULL;

/* Create node */
struct RBNode* createRBNode(int val) {
    struct RBNode* temp = (struct RBNode*)malloc(sizeof(struct RBNode));
    temp->value = val;
    temp->shade = RED;
    temp->lchild = temp->rchild = temp->parent = NULL;
    return temp;
}

/* Left rotate */
void rotateLeftRB(struct RBNode *curr) {
    struct RBNode *child = curr->rchild;
    curr->rchild = child->lchild;

    if (child->lchild != NULL)
        child->lchild->parent = curr;

    child->parent = curr->parent;

    if (curr->parent == NULL)
        treeRoot = child;
    else if (curr == curr->parent->lchild)
        curr->parent->lchild = child;
    else
        curr->parent->rchild = child;

    child->lchild = curr;
    curr->parent = child;
}

/* Right rotate */
void rotateRightRB(struct RBNode *curr) {
    struct RBNode *child = curr->lchild;
    curr->lchild = child->rchild;

    if (child->rchild != NULL)
        child->rchild->parent = curr;

    child->parent = curr->parent;

    if (curr->parent == NULL)
        treeRoot = child;
    else if (curr == curr->parent->lchild)
        curr->parent->lchild = child;
    else
        curr->parent->rchild = child;

    child->rchild = curr;
    curr->parent = child;
}

/* Fix violations */
void fixRBInsert(struct RBNode *node) {
    while (node != treeRoot && node->parent->shade == RED) {

        if (node->parent == node->parent->parent->lchild) {
            struct RBNode *uncle = node->parent->parent->rchild;

            if (uncle != NULL && uncle->shade == RED) {
                node->parent->shade = BLACK;
                uncle->shade = BLACK;
                node->parent->parent->shade = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->rchild) {
                    node = node->parent;
                    rotateLeftRB(node);
                }
                node->parent->shade = BLACK;
                node->parent->parent->shade = RED;
                rotateRightRB(node->parent->parent);
            }
        } else {
            struct RBNode *uncle = node->parent->parent->lchild;

            if (uncle != NULL && uncle->shade == RED) {
                node->parent->shade = BLACK;
                uncle->shade = BLACK;
                node->parent->parent->shade = RED;
                node = node->parent->parent;
            } else {
                if (node == node->parent->lchild) {
                    node = node->parent;
                    rotateRightRB(node);
                }
                node->parent->shade = BLACK;
                node->parent->parent->shade = RED;
                rotateLeftRB(node->parent->parent);
            }
        }
    }
    treeRoot->shade = BLACK;
}

/* Insert */
void insertRB(int val) {
    struct RBNode *newNode = createRBNode(val);
    struct RBNode *parentPtr = NULL;
    struct RBNode *trav = treeRoot;

    while (trav != NULL) {
        parentPtr = trav;
        if (val < trav->value)
            trav = trav->lchild;
        else
            trav = trav->rchild;
    }

    newNode->parent = parentPtr;

    if (parentPtr == NULL)
        treeRoot = newNode;
    else if (val < parentPtr->value)
        parentPtr->lchild = newNode;
    else
        parentPtr->rchild = newNode;

    fixRBInsert(newNode);
}

/* Inorder traversal */
void inorderRB(struct RBNode *node) {
    if (node != NULL) {
        inorderRB(node->lchild);
        printf("%d(%s) ", node->value,
               node->shade == RED ? "R" : "B");
        inorderRB(node->rchild);
    }
}

/* Tree structure printing */
void printRBTree(struct RBNode* root, int space) {
    if (root == NULL)
        return;

    space += 10;

    printRBTree(root->rchild, space);

    printf("\n");
    for (int i = 10; i < space; i++)
        printf(" ");

    printf("%d(%s)", root->value,
           root->shade == RED ? "R" : "B");

    printRBTree(root->lchild, space);
}

int main() {
    int n, val;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter %d values:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &val);
        insertRB(val);
    }

    printf("\nInorder Traversal:\n");
    inorderRB(treeRoot);

    printf("\n\nTree Structure:\n");
    printRBTree(treeRoot, 0);

    return 0;
}
