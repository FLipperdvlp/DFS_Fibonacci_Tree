#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* left;
    struct Node* right;
} Node;

Node* CreateFibTree(int n) {
    if (n <= 1) {
        Node* node = malloc(sizeof(Node));

        node->value = n;
        node->left = NULL;
        node->right = NULL;

        return node;
    }

    Node* node = malloc(sizeof(Node));

    node->value = n;
    node->left = CreateFibTree(n - 1);
    node->right = CreateFibTree(n - 2);

    return node;
}

int fiboTree(int n, int level) {
    for (int i = 0; i < level; i++) {
        printf("│  ");
    }
    printf("├─→ fibo(%d)\n", n);

    if (n <= 1) {
        for (int i = 0; i < level; i++) {
            printf("│  ");
        }
        printf("└─ ← %d\n", n);
        return n;
    }

    int left = fiboTree(n - 1, level + 1);
    int right = fiboTree(n - 2, level + 1);
    int result = left + right;

    for (int i = 0; i < level; i++) {
        printf("│  ");
    }
    printf("└─ ← %d\n", result);

    return result;
}


void DFS(Node* root, int level, int* maxValue, int* visited) {
    if (root == NULL) {
        return;
    }

    (*visited)++;

    if (root->value > *maxValue) {
        *maxValue = root->value;
    }

    for (int i = 0; i < level; i++) {
        printf("│   ");
    }

    printf("├── Odwiedzam: %d\n", root->value);

    DFS(root->left, level + 1, maxValue, visited);
    DFS(root->right, level + 1, maxValue, visited);
}



int main(void) {
    int n = 0;

    printf("Podaj n: ");
    if (scanf("%d", &n) != 1 || n < 0) {
        printf("Nieprawidlowe n.\n");
        return 1;
    }

    Node* root = CreateFibTree(n);

    printf("\nDrzewo wywolan rekurencyjnych:\n");
    int result = fiboTree(n, 0);

    int maxValue = root->value;
    int visited = 0;

    printf("\nPrzejscie DFS:\n");

    DFS(root, 0, &maxValue, &visited);

    printf("\nWyniki DFS:\n");
    printf("Maksymalna wartosc: %d\n", maxValue);
    printf("Liczba odwiedzonych wezlow: %d\n", visited);

    return 0;
}