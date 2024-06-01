#include <stdio.h>
#include <stdlib.h>

// Struktur node AVL Tree
struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
};
typedef struct Node Node;

// Fungsi untuk membuat node baru dalam AVL Tree
Node *createNode(int data) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}
// Fungsi untuk mendapatkan tinggi dari sebuah node
int getHeight(Node *node) {
    if (node == NULL)
        return 0;
    return node->height;
}
// Fungsi untuk menghitung faktor keseimbangan sebuah node
int getBalanceFactor(Node *node) {
    if (node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}
// Fungsi untuk melakukan rotasi ke kanan
Node *rightRotate(Node *node) {
    Node *newRoot = node->left;
    Node *temp = newRoot->right;

    newRoot->right = node;
    node->left = temp;

    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
    newRoot->height = 1 + (getHeight(newRoot->left) > getHeight(newRoot->right) ? getHeight(newRoot->left) : getHeight(newRoot->right));

    return newRoot;
}
// Fungsi untuk melakukan rotasi ke kiri
Node *leftRotate(Node *node) {
    Node *newRoot = node->right;
    Node *temp = newRoot->left;
    newRoot->left = node;
    node->right = temp;
    node->height = 1 + (getHeight(node->left) > getHeight(node->right) ? getHeight(node->left) : getHeight(node->right));
    newRoot->height = 1 + (getHeight(newRoot->left) > getHeight(newRoot->right) ? getHeight(newRoot->left) : getHeight(newRoot->right));
    return newRoot;
}

// Fungsi untuk menyisipkan nilai ke dalam AVL Tree
Node *insert(Node *root, int data) {
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    else
        return root; // Nilai duplikat tidak diperbolehkan dalam AVL Tree

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));

    int balanceFactor = getBalanceFactor(root);
    // Kasus Left Left
    if (balanceFactor > 1 && data < root->left->data)
        return rightRotate(root);
    // Kasus Right Right
    if (balanceFactor < -1 && data > root->right->data)
        return leftRotate(root);
    // Kasus Left Right
    if (balanceFactor > 1 && data > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // Kasus Right Left
    if (balanceFactor < -1 && data < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Fungsi untuk mendapatkan node dengan nilai terkecil dalam AVL Tree
Node *getMinValueNode(Node *node) {
    Node *current = node;

    while (current->left != NULL)
        current = current->left;

    return current;
}

// Fungsi untuk menghapus sebuah nilai dari AVL Tree
Node *deleteNode(Node *root, int data) {
    if (root == NULL)
        return root;

    if (data < root->data)
        root->left = deleteNode(root->left, data);
    else if (data > root->data)
        root->right = deleteNode(root->right, data);
    else {
        if (root->left == NULL || root->right == NULL) {
            Node *temp = root->left ? root->left : root->right;

            if (temp == NULL) {
                temp = root;
                root = NULL;
            } else
                *root = *temp;

            free(temp);
        } else {
            Node *temp = getMinValueNode(root->right);
            root->data = temp->data;
            root->right = deleteNode(root->right, temp->data);
        }
    }

    if (root == NULL)
        return root;

    root->height = 1 + (getHeight(root->left) > getHeight(root->right) ? getHeight(root->left) : getHeight(root->right));
    int balanceFactor = getBalanceFactor(root);
    // Kasus Left Left
    if (balanceFactor > 1 && getBalanceFactor(root->left) >= 0)
        return rightRotate(root);

    // Kasus Right Right
    if (balanceFactor < -1 && getBalanceFactor(root->right) <= 0)
        return leftRotate(root);

    // Kasus Left Right
    if (balanceFactor > 1 && getBalanceFactor(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Kasus Right Left
    if (balanceFactor < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// Fungsi untuk mencetak AVL Tree secara PreOrder traversal
void printPreOrder(Node *root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

// Fungsi untuk mencetak AVL Tree secara InOrder traversal
void printInOrder(Node *root) {
    if (root == NULL)
        return;

    printInOrder(root->left);
    printf("%d ", root->data);
    printInOrder(root->right);
}

// Fungsi untuk mencetak PostOrder 
void printPostOrder(Node *root) {
    if (root == NULL)
        return;
    printPostOrder(root->left);
    printPostOrder(root->right);
    printf("%d ", root->data);
}

int main() {
    Node *root = NULL;
    int choice, value;
    do {
        printf("\n--- Menu AVL Tree ---\n");
        printf("1. Insertion\n");
        printf("2. Deletion\n");
        printf("3. Traversal\n");
        printf("4. Exit\n");
        printf("Choose: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Insert: ");
                scanf("%d", &value);
                root = insert(root, value);
                break;
            case 2:
                printf("Delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                break;
            case 3:
                printf("PreOrder: ");
                printPreOrder(root);
                printf("\n");
                printf("InOrder: ");
                printInOrder(root);
                printf("\n");
                printf("PostOrder: ");
                printPostOrder(root);
                printf("\n");
                break;
            case 4:
                printf("Thank You\n");
                break;
        }
    } while (choice != 4);
    return 0;
}
