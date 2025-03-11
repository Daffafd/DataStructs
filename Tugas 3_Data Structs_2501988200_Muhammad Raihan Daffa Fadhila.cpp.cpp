#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define TABLE_SIZE 10

struct node {
    char data[100];
    struct node* next;
} *hashTable[26], * curr;

int hashFuction(char data[]) {
    int hashKey = -1;
    char firstChar;
    firstChar = data[0];
    hashKey = tolower(firstChar) - 97;
    return hashKey;
}

int divHash(int key) {
    return key % TABLE_SIZE;
}

int foldingHash(int key) {
    int part1 = key / 1000;
    int part2 = key % 1000;
    return (part1 + part2) % TABLE_SIZE;
}

int midSquare(int key) {
    int square = key * key;
    return (square / 100) % 100;  // Ambil dua digit tengah
}

int digitExtraction(int key) {
    return key % TABLE_SIZE;
}

int rotation(int key) {
    return (key >> 3) ^ key;
}

void viewHashTable() {
    for (int i = 0; i < 26; i++) {
        if (hashTable[i] != NULL) {
            printf("Index [%d]:\n", i);
            curr = hashTable[i];
            while (curr != NULL) {
                printf("%s ", curr->data);
                curr = curr->next;
            }
            printf("\n");
        }
    }
}

void pushBack(int hashKey, char data[]) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if (hashTable[hashKey] == NULL) {
        hashTable[hashKey] = newNode;
    }
    else {
        curr = hashTable[hashKey];
        while (curr->next != NULL)
            curr = curr->next;
        curr->next = newNode;
    }
}

int main() {
    int choice, hashMethod;
    char data[100];

    printf("Choose a Hash Function:\n");
    printf("1. Hash Function (First Character)\n");
    printf("2. Division Method\n");
    printf("3. Folding Method\n");
    printf("4. Mid-Square Method\n");
    printf("5. Digit Extraction Method\n");
    printf("6. Rotation Method\n");
    scanf("%d", &hashMethod);

    do {
        printf("Input Data: ");
        scanf("%s", data);
        getchar();

        if (strcmpi(data, "exit") == 0) break;

        switch (hashMethod) {
        case 1:
            pushBack(hashFuction(data), data);
            break;
        case 2:
            pushBack(divHash(atoi(data)), data);
            break;
        case 3:
            pushBack(foldingHash(atoi(data)), data);
            break;
        case 4:
            pushBack(midSquare(atoi(data)), data);
            break;
        case 5:
            pushBack(digitExtraction(atoi(data)), data);
            break;
        case 6:
            pushBack(rotation(atoi(data)), data);
            break;
        default:
            printf("Invalid choice\n");
        }
    } while (1);

    viewHashTable();
    getchar();

    return 0;
}
