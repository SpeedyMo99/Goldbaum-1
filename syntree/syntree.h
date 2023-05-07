#ifndef SYNTREE_H
#define SYNTREE_H

#include <stdio.h>
#include <stdlib.h>



typedef int SyntreeNodeID;

struct NodeList;

struct SyntreeNode {
    SyntreeNodeID id;
    int value;
    struct NodeList *children;
};
typedef struct SyntreeNode SyntreeNode;

struct NodeList {
    struct SyntreeNode **arr;
    int size;
    int index;
};
typedef struct NodeList NodeList;

typedef struct {
    int size;
    int count;
    struct SyntreeNode **arr;
} NodeHashTable;

typedef struct {
    struct SyntreeNode *root;
    struct NodeHashTable *table;
} Syntree;


void nodeListInit(NodeList *list) {
    list->size = 2;
    list->arr = (SyntreeNode**) calloc(list->size, sizeof(SyntreeNode*));
    list->index = 0;
}

SyntreeNode *nodeListGet(NodeList *list, int index) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "%d is out of bounds!\n", index);
        exit(-1);
    }
    return list->arr[index];
}

void nodeListSet(NodeList *list, int index, SyntreeNode *node) {
    if (index < 0 || index >= list->size) {
        fprintf(stderr, "%d is out of bounds!\n", index);
        exit(-1);
    }
    list->arr[index] = node;
}

void nodeListEnlarge(NodeList *list) {
    int newSize = list->size*2;
    SyntreeNode **newArr = (SyntreeNode**) calloc(newSize, sizeof(SyntreeNode*));

    for (int i = 0; i < list->size; i++) {
        newArr[i] = list->arr[i];
    }
    free(list->arr);
    list->arr = newArr;
    list->size = newSize;
}

void nodeListPushBack(NodeList *list, SyntreeNode *node) {
    if (list->index >= list->size) {
        nodeListEnlarge(list);
    }
    nodeListSet(list, list->index, node);
    list->index++;
}

void nodeListPushFront(NodeList *list, SyntreeNode *node) {
    if (list -> index >= list->size) {
        nodeListEnlarge(list);
    }
    for (int i = list->index; i > 0; i--) {
        list->arr[i] = list->arr[i-1];
    }
    list->arr[0] = node;
    list->index++;
}

#define primeCount 5
int primes[primeCount] = { 31, 127, 8191, 131071, 524287 };

int hash(SyntreeNodeID key, int size) {
    return key % size;
}

void nodeHashTableInit(NodeHashTable *table) {
    table->size = primes[0];
    table->count = 0;
    table->arr = (SyntreeNode**) calloc(table->size, sizeof(SyntreeNode*));
}

void nodeHashTableRelease(NodeHashTable *table) {
    free(table->arr);
}

void nodeHashTableEnlarge(NodeHashTable *table) {
    int newPrime = -1;
    for (int i = 0; i < primeCount; i++) {
        if (primes[i] > table->size) {
            newPrime = primes[i];
            break;
        }
    }
    if (newPrime == -1) {
        fprintf(stderr, "Hashtable got way to large!\n");
        exit(-1);
    }
    SyntreeNode **newArr = (SyntreeNode**) calloc(newPrime, sizeof(SyntreeNode*));

    for (int i = 0; i < table->size; i++) {
        SyntreeNode *node = table->arr[i];
        if (node != NULL) {
            int newHash = hash(node->id, newPrime);
            while (newArr[newHash % newPrime] != NULL) {
                newHash++;
            }
            newArr[newHash % newPrime] = node;
        }
    }
    free(table->arr);
    table->arr = newArr;
    table->size = newPrime;
}

void nodeHashTableAdd(NodeHashTable *table, SyntreeNodeID key, SyntreeNode *value) {
    if (((float) table->count / table->size) > 0.5) {
        nodeHashTableEnlarge(table);
    }
    int hashVal = hash(key, table->size);
    while (table->arr[hashVal % table->size] != NULL) {
        hashVal++; // Lineares Sondieren
    }
    table->arr[hashVal % table->size] = value;
    table->count++;
}

SyntreeNode *nodeHashTableGet(NodeHashTable *table, SyntreeNodeID key) {
    int hashVal = hash(key, table->size);
    // assert table->arr(hash) != NULL
    while (((table->arr)[hashVal % table->size])->id != key) {
        hashVal++;
    }
    return table->arr[hashVal % table->size];
}

int nextNodeId() {
    static int last = 0;
    return last++;
}

void syntreeNodeInit(SyntreeNode *node) {
    node->id = nextNodeId();
    node->value = 0;

    NodeList *list = (NodeList*) malloc(sizeof(NodeList));
    nodeListInit(list);
    node->children = list;
}

SyntreeNode *nodeById(Syntree *syntree, SyntreeNodeID id) {
    return nodeHashTableGet(syntree->table, id);
}

extern int
syntreeInit(Syntree *self);

extern void
syntreeRelease(Syntree *self);

extern SyntreeNodeID
syntreeNodeNumber(Syntree *self, int number);

extern SyntreeNodeID
syntreeNodeTag(Syntree *self, SyntreeNodeID id);

extern SyntreeNodeID
syntreeNodePair(Syntree *self, SyntreeNodeID id1, SyntreeNodeID id2);

extern SyntreeNodeID
syntreeNodeAppend(Syntree *self, SyntreeNodeID list, SyntreeNodeID elem);

extern SyntreeNodeID
syntreeNodePrepend(Syntree *self, SyntreeNodeID elem, SyntreeNodeID list);

extern void
syntreePrint(const Syntree *self, SyntreeNodeID root);



#endif
