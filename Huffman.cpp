#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 256

// 노드 구조체 정의
typedef struct Node {
    char character;
    int frequency;
    struct Node* left;
    struct Node* right;
    struct Node* next;
} Node;

// 우선순위 큐 노드 구조체 정의
typedef struct PriorityQueueNode {
    Node* node;
    struct PriorityQueueNode* next;
} PriorityQueueNode;

// 우선순위 큐 구조체 정의
typedef struct PriorityQueue {
    PriorityQueueNode* head;
} PriorityQueue;

// 문자 빈도수 저장 구조체
typedef struct Frequency {
    char character;
    int frequency;
} Frequency;

// Huffman 트리를 구성하는 함수
Node* buildHuffmanTree(Frequency* frequencies, int numChars);

// 우선순위 큐에 노드를 삽입하는 함수
void enqueue(PriorityQueue* queue, Node* node);

// 우선순위 큐에서 최소 빈도수를 가진 두 노드를 제거하는 함수
void dequeueMin(PriorityQueue* queue, Node** min1, Node** min2);

// Huffman 코드를 생성하는 함수
void generateHuffmanCodes(Node* root, const char* code, int depth, char** codes);

// 입력 파일을 Huffman 압축하여 결과를 출력 파일에 저장하는 함수
void compressFile(FILE* inputFile, FILE* outputFile, char** codes);

// 입력 파일을 Huffman 압축 해제하여 결과를 출력 파일에 저장하는 함수
void decompressFile(FILE* inputFile, FILE* outputFile, Node* root, int numChars);

// Huffman 코드에 할당된 메모리를 해제하는 함수
void freeHuffmanCodes(char** codes);

int main() {
    // input.txt파일을 읽기 모드로 열기
    FILE* inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("input.txt 열기 실패.\n");
        return 1;
    }

    // 문자 빈도수 저장할 배열 초기화
    Frequency frequencies[MAX_CHAR];
    for (int i = 0; i < MAX_CHAR; i++) {
        frequencies[i].character = (char)i;
        frequencies[i].frequency = 0;
    }

    // input.txt 파일로부터 문자 빈도수 계산
    int c;
    while ((c = fgetc(inputFile)) != EOF) {
        frequencies[c].frequency++;
    }

    // input.txt 파일 닫기
    fclose(inputFile);

    // stats.txt 쓰기모드로 열기
    FILE* statsFile = fopen("stats.txt", "w");
    if (statsFile == NULL) {
        printf("stats.txt 열기 실패.\n");
        return 1;
    }

    // 빈도수를 stats.txt 에 저장
    for (int i = 0; i < MAX_CHAR; i++) {
        if (frequencies[i].frequency > 0) {
            fprintf(statsFile, "%c\t%d\n", frequencies[i].character, frequencies[i].frequency);
        }
    }

    fclose(statsFile);

    // Huffman 트리 생성
    Node* root = buildHuffmanTree(frequencies, MAX_CHAR);

    // Huffman 코드 생성
    char* codes[MAX_CHAR];
    for (int i = 0; i < MAX_CHAR; i++) {
        codes[i] = NULL;
    }
    generateHuffmanCodes(root, "", 0, codes);


    // 다시 input.txt 읽기 모드로 열기
    inputFile = fopen("input.txt", "r");
    if (inputFile == NULL) {
        printf("input.txt 열기 실패.\n");
        return 1;
    }

    // output.huf 이진 쓰기 모드로 열기
    FILE* outputFile = fopen("output.huf", "wb");
    if (outputFile == NULL) {
        printf("output.huf 열기 실패.\n");
        return 1;
    }

    // input.txt 파일을 Huffman 압축하여 output.huf 파일에 저장 in output.huf file
    compressFile(inputFile, outputFile, codes);

    fclose(inputFile);
    fclose(outputFile);

    // output.txt 쓰기 모드로 열기
    FILE* outputFileTxt = fopen("output.txt", "w");
    if (outputFileTxt == NULL) {
        printf("output.txt 열기 실패.\n");
        return 1;
    }

    // 다시 output.huf 이진모드로 읽기
    outputFile = fopen("output.huf", "rb");
    if (outputFile == NULL) {
        printf("output.huf 열기 실패.\n");
        return 1;
    }

    // output.huf 파일을 Huffman 압축 해제하여 output.txt 파일에 저장
    decompressFile(outputFile, outputFileTxt, root, MAX_CHAR);

    fclose(outputFileTxt);
    fclose(outputFile);

    freeHuffmanCodes(codes);

    free(root);

    printf("압축 및 압축 해제 성공.\n");

    return 0;
}

// Huffman 트리를 구성하는 함수
Node* buildHuffmanTree(Frequency* frequencies, int numChars) {
    PriorityQueue queue;
    queue.head = NULL;

    // 빈도수가 0이 아닌 노드들을 우선순위 큐에 넣음
    for (int i = 0; i < numChars; i++) {
        if (frequencies[i].frequency > 0) {
            Node* newNode = (Node*)malloc(sizeof(Node));
            newNode->character = frequencies[i].character;
            newNode->frequency = frequencies[i].frequency;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->next = NULL;
            enqueue(&queue, newNode);
        }
    }

    while (queue.head != NULL && queue.head->next != NULL) {
        Node* min1;
        Node* min2;
        dequeueMin(&queue, &min1, &min2);

        Node* newNode = (Node*)malloc(sizeof(Node));
        newNode->character = '\0';
        newNode->frequency = min1->frequency + min2->frequency;
        newNode->left = min1;
        newNode->right = min2;
        newNode->next = NULL;

        enqueue(&queue, newNode);
    }

    if (queue.head != NULL) {
        return queue.head->node;
    }

    return NULL;
}
// 우선순위 큐에 노드를 삽입하는 함수
void enqueue(PriorityQueue* queue, Node* node) {
    PriorityQueueNode* newNode = (PriorityQueueNode*)malloc(sizeof(PriorityQueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if (queue->head == NULL || node->frequency < queue->head->node->frequency) {
        newNode->next = queue->head;
        queue->head = newNode;
    }
    else {
        PriorityQueueNode* current = queue->head;

        while (current->next != NULL && current->next->node->frequency <= node->frequency) {
            current = current->next;
        }

        newNode->next = current->next;
        current->next = newNode;
    }
}
// 우선순위 큐에서 최소 빈도수를 가진 두 노드를 제거하는 함수
void dequeueMin(PriorityQueue* queue, Node** min1, Node** min2) {
    if (queue->head != NULL && queue->head->next != NULL) {
        *min1 = queue->head->node;
        *min2 = queue->head->next->node;
        queue->head = queue->head->next->next;
    }
}

// Huffman 코드를 생성하는 함수
void generateHuffmanCodes(Node* root, const char* code, int depth, char** codes) {
    if (root->left == NULL && root->right == NULL) {
        codes[(int)root->character] = (char*)malloc((depth + 1) * sizeof(char));
        strcpy(codes[(int)root->character], code);
    }
    else {
        char leftCode[100] = "";
        char rightCode[100] = "";
        strcpy(leftCode, code);
        strcpy(rightCode, code);
        strcat(leftCode, "0");
        strcat(rightCode, "1");
        generateHuffmanCodes(root->left, leftCode, depth + 1, codes);
        generateHuffmanCodes(root->right, rightCode, depth + 1, codes);
    }
}

// 입력 파일을 Huffman 압축하여 결과를 출력 파일에 저장하는 함수
void compressFile(FILE* inputFile, FILE* outputFile, char** codes) {
    unsigned char currentByte = 0;
    int bitIndex = 0;
    int c;

    while ((c = fgetc(inputFile)) != EOF) {
        char* code = codes[c];

        if (code == NULL) {
            // 예외 처리: 코드가 존재하지 않는 문자일 경우 스킵
            continue;
        }

        int codeLength = strlen(code);
        for (int i = 0; i < codeLength; i++) {
            if (code[i] == '1') {
                currentByte |= (1 << bitIndex);
            }

            bitIndex++;

            if (bitIndex == 8) {
                fwrite(&currentByte, sizeof(unsigned char), 1, outputFile);
                bitIndex = 0;
                currentByte = 0;
            }
        }
    }

    if (bitIndex > 0) {
        fwrite(&currentByte, sizeof(unsigned char), 1, outputFile);
    }
}
// 입력 파일을 Huffman 압축 해제하여 결과를 출력 파일에 저장하는 함수
void decompressFile(FILE* inputFile, FILE* outputFile, Node* root, int numChars) {
    unsigned char currentByte;
    int bitIndex = 0;
    Node* currentNode = root;

    while (fread(&currentByte, sizeof(unsigned char), 1, inputFile) > 0) {
        for (int i = 0; i < 8; i++) {
            int bit = (currentByte >> i) & 1;

            if (bit == 0) {
                currentNode = currentNode->left;
            }
            else {
                currentNode = currentNode->right;
            }

            if (currentNode->left == NULL && currentNode->right == NULL) {
                fprintf(outputFile, "%c", currentNode->character);
                currentNode = root;
            }
        }
    }
}
// Huffman 코드에 할당된 메모리를 해제하는 함수
void freeHuffmanCodes(char** codes) {
    for (int i = 0; i < MAX_CHAR; i++) {
        if (codes[i] != NULL) {
            free(codes[i]);
        }
    }
}