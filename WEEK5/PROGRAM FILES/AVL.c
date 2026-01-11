#include <stdio.h>
#include <stdlib.h>

/* AVL Tree Node Structure */
struct Node {
    int data;
    struct Node *left, *right;
    int height;
};

/* Utility function to find maximum */
int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

/* Get height of node */
int nodeHeight(struct Node *nodePtr) {
    if (nodePtr == NULL)
        return 0;
    return nodePtr->height;
}

/* Create a new node */
struct Node* createNewNode(int item) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = item;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

/* Right Rotation */
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = maxValue(nodeHeight(y->left), nodeHeight(y->right)) + 1;
    x->height = maxValue(nodeHeight(x->left), nodeHeight(x->right)) + 1;

    return x;
}

/* Left Rotation */
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = maxValue(nodeHeight(x->left), nodeHeight(x->right)) + 1;
    y->height = maxValue(nodeHeight(y->left), nodeHeight(y->right)) + 1;

    return y;
}

/* Get balance factor */
int getBalance(struct Node* nodePtr) {
    if (nodePtr == NULL)
        return 0;
    return nodeHeight(nodePtr->left) - nodeHeight(nodePtr->right);
}

/* Insert into AVL Tree */
struct Node* insertNode(struct Node* root, int value) {
    if (root == NULL)
        return createNewNode(value);

    if (value < root->data)
        root->left = insertNode(root->left, value);
    else if (value > root->data)
        root->right = insertNode(root->right, value);
    else
        return root;

    root->height = 1 + maxValue(nodeHeight(root->left), nodeHeight(root->right));

    int balance = getBalance(root);

    // LL Case
    if (balance > 1 && value < root->left->data)
        return rightRotate(root);

    // RR Case
    if (balance < -1 && value > root->right->data)
        return leftRotate(root);

    // LR Case
    if (balance > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RL Case
    if (balance < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

/* Level Order Traversal */
void levelOrder(struct Node* root) {
    if (root == NULL) {
        printf("Tree is empty\n");
        return;
    }

    struct Node* queue[100];
    int front = 0, rear = 0, level = 0;

    queue[rear++] = root;

    printf("\nLevel Order Traversal:\n");

    while (front < rear) {
        int count = rear - front;
        printf("Level %d: ", level++);

        for (int i = 0; i < count; i++) {
            struct Node* curr = queue[front++];
            printf("%d ", curr->data);

            if (curr->left != NULL)
                queue[rear++] = curr->left;
            if (curr->right != NULL)
                queue[rear++] = curr->right;
        }
        printf("\n");
    }
}

/* Main Function */
int main() {
    struct Node* root = NULL;
    int n, value;

    printf("Enter number of nodes: ");
    scanf("%d", &n);

    printf("Enter %d values:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insertNode(root, value);
    }

    levelOrder(root);

    if (getBalance(root) >= -1 && getBalance(root) <= 1)
        printf("\nTree is AVL Balanced\n");
    else
        printf("\nTree is NOT Balanced\n");

    return 0;
}
