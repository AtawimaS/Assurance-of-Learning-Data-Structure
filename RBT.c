#include <stdio.h>
#include <stdlib.h>

// Struktur node Red Black Tree
struct Node {
    int data;
    struct Node *parent;
    struct Node *left;
    struct Node *right;
    int color; // 0 untuk hitam, 1 untuk merah
};

typedef struct Node Node;

Node* createNode(int data) { // Fungsi untuk membuat node baru pada Red Black Tree
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->color = 1; // Awalnya warna diatur menjadi merah
    newNode->left = newNode->right = newNode->parent = NULL;
    return newNode;
}

void leftRotate(Node** root, Node* node) { // Fungsi untuk melakukan rotasi ke kiri
    Node* rightChild = node->right;
    node->right = rightChild->left;

    if (node->right != NULL)
        node->right->parent = node;

    rightChild->parent = node->parent;

    if (node->parent == NULL)
        *root = rightChild;
    else if (node == node->parent->left)
        node->parent->left = rightChild;
    else
        node->parent->right = rightChild;

    rightChild->left = node;
    node->parent = rightChild;
}

void rightRotate(Node** root, Node* node) { // Fungsi untuk melakukan rotasi ke kanan
    Node* leftChild = node->left;
    node->left = leftChild->right;
    if (node->left != NULL)
        node->left->parent = node;

    leftChild->parent = node->parent;

    if (node->parent == NULL)
        *root = leftChild;
    else if (node == node->parent->left) node->parent->left = leftChild;
    else node->parent->right = leftChild;
    leftChild->right = node;
    node->parent = leftChild;
}

void insertFixup(Node** root, Node* newNode) { // Fungsi untuk memperbaiki Red Black Tree setelah insert
    Node* parent = NULL;
    Node* grandparent = NULL;

    while (newNode != *root && newNode->color == 1 && newNode->parent->color == 1) {
        parent = newNode->parent;
        grandparent = newNode->parent->parent;

        // Kasus 1: Orang tua berada di sebelah kiri kakek
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;

            // Kasus 1a: Jika paman berwarna merah
            if (uncle != NULL && uncle->color == 1) {
                grandparent->color = 1;
                parent->color = 0;
                uncle->color = 0;
                newNode = grandparent;
            } else {
                // Kasus 1b: Jika paman berwarna hitam dan node baru berada di sebelah kanan
                if (newNode == parent->right) {
                    leftRotate(root, parent); // Melakukan rotasi ke kiri
                    newNode = parent;
                    parent = newNode->parent;
                }

                // Kasus 1c: Jika paman berwarna hitam dan node baru berada di sebelah kiri
                rightRotate(root, grandparent);
                int tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                newNode = parent;
            }
        } else { // Kasus 2: Orang tua berada di sebelah kanan kakek
            Node* uncle = grandparent->left;

            // Kasus 2a: Jika paman berwarna merah
            if (uncle != NULL && uncle->color == 1) {
                grandparent->color = 1;
                parent->color = 0;
                uncle->color = 0;
                newNode = grandparent;
            } else {
                // Kasus 2b: Jika paman berwarna hitam dan node baru berada di sebelah kiri
                if (newNode == parent->left) {
                    rightRotate(root, parent); // Melakukan rotasi ke kanan
                    newNode = parent;
                    parent = newNode->parent;
                }

                // Kasus 2c: Jika paman berwarna hitam dan node baru berada di sebelah kanan
                leftRotate(root, grandparent);
                int tempColor = parent->color;
                parent->color = grandparent->color;
                grandparent->color = tempColor;
                newNode = parent;
            }
        }
    }

    (*root)->color = 0; // Akar selalu berwarna hitam
}

void insert(Node** root, int data) { // Fungsi untuk melakukan insert pada Red Black Tree
    Node* newNode = createNode(data);
    // Melakukan penambahan seperti pada BST biasa
    Node* parent = NULL;
    Node* current = *root;

    while (current != NULL) {
        parent = current;
        if (newNode->data < current->data)
            current = current->left;
        else
            current = current->right;
    }
    newNode->parent = parent;
    if (parent == NULL)
        *root = newNode;
    else if (newNode->data < parent->data)
        parent->left = newNode;
    else
        parent->right = newNode;
    insertFixup(root, newNode); // Memperbaiki tree agar tidak ada kesalahan
}
void print(Node* root) { // Fungsi untuk menampilkan hasil dari RBT
    if (root == NULL)
        return;

    print(root->left);
    printf("%d ", root->data);
    print(root->right);
}

int main() {
    Node* root = NULL;
    int sequence[] = {41, 22, 5, 51, 48, 29, 18, 21, 45, 3};
    int length = sizeof(sequence) / sizeof(sequence[0]);
    for (int i = 0; i < length; i++) {
        insert(&root, sequence[i]);
    }
    printf("Inorder Traversal of Created Tree\n");
    print(root);
    printf("\n");
    system("pause");
    return 0;
}
