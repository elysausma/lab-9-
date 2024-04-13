//Elysa Usma COP 3502C
// LAB #9 

#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 10

// RecordType
struct RecordType
{
    int     id;
    char    name;
    int     order; 
};

// Node for linked list
struct Node
{
    struct RecordType data;
    struct Node* next;
};

// HashType structure containing array of linked lists
struct HashType
{
    struct Node* array[HASH_SIZE];
};

// Compute the hash function
int hash(int x)
{
    return x % HASH_SIZE;
}

// Parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
        // Implement parse data block
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

// Display records in the hash structure
void displayRecordsInHash(struct HashType *pHashArray)
{
    int i;
    for (i = 0; i < HASH_SIZE; ++i)
    {
        printf("Index %d -> ", i);
        struct Node* current = pHashArray->array[i];
        while (current != NULL)
        {
            printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
            current = current->next;
        }
        printf("NULL\n");
    }
}

// insert into hash table
void insertRecord(struct HashType* hashTable, struct RecordType record)
{
    int index = hash(record.id);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        exit(-1);
    }
    newNode->data = record;
    newNode->next = hashTable->array[index];
    hashTable->array[index] = newNode;
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;
    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    struct HashType hashTable;
    for (int i = 0; i < HASH_SIZE; ++i)
        hashTable.array[i] = NULL;
  
    for (int i = 0; i < recordSz; ++i)
        insertRecord(&hashTable, pRecords[i]);

    displayRecordsInHash(&hashTable);

    for (int i = 0; i < recordSz; ++i)
      free(&pRecords[i]);
    free(pRecords);

    return 0;
}
