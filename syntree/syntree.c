#include "syntree.h"


int syntreeInit(Syntree *self) {
    NodeHashTable *table = malloc(sizeof(NodeHashTable));
    nodeHashTableInit(table);
    self->table = table;

    syntreeNodeNumber(self, 0);
    self->root = nodeById(self, 0);
    return 0;
}

void syntreeReleaseNode(SyntreeNode *node) {
    if (node != NULL) {
        for (int i = 0; i < node->children->index; i++) {
            SyntreeNode *child = nodeListGet(node->children, i);
            syntreeReleaseNode(child);
        }
        free(node);
    }
}

void syntreeRelease(Syntree *self) {
    syntreeReleaseNode(self->root);
    nodeHashTableRelease(self->table);
}

SyntreeNodeID syntreeNodeNumber(Syntree *self, int number) {
    SyntreeNode *node = (SyntreeNode *) malloc(sizeof(SyntreeNode));
    syntreeNodeInit(node);
    node->value = number;
    nodeHashTableAdd(self->table, node->id, node);
    return node->id;
}

SyntreeNodeID syntreeNodeTag(Syntree *self, SyntreeNodeID id) {
    SyntreeNode *node = nodeById(self, id);
    SyntreeNodeID newId = syntreeNodeNumber(self, -82934502);
    SyntreeNode *newNode = nodeById(self, newId);

    nodeListPushBack(newNode->children, node);
    return newId;
}

SyntreeNodeID syntreeNodePair(Syntree *self, SyntreeNodeID id1, SyntreeNodeID id2) {
    SyntreeNode *node1 = nodeById(self, id1);
    SyntreeNode *node2 = nodeById(self, id2);
    SyntreeNodeID newId = syntreeNodeNumber(self, -82934502);
    SyntreeNode *newNode = nodeById(self, newId);

    nodeListPushBack(newNode->children, node1);
    nodeListPushBack(newNode->children, node2);
    return newId;
}

SyntreeNodeID syntreeNodeAppend(Syntree *self, SyntreeNodeID list, SyntreeNodeID elem) {
    SyntreeNode *listNode = nodeById(self, list);
    SyntreeNode *elemNode = nodeById(self, elem);

    nodeListPushBack(listNode->children, elemNode);
    return list;
}

SyntreeNodeID syntreeNodePrepend(Syntree *self, SyntreeNodeID list, SyntreeNodeID elem) {
    SyntreeNode *listNode = nodeById(self, list);
    SyntreeNode *elemNode = nodeById(self, elem);
    nodeListPushFront(listNode->children, elemNode);
    return list;
}

void syntreePrintNode(const SyntreeNode *node) {
    if (node != NULL) {
        if (node->value != -82934502) {
            printf("(%d)", node->value);
        }
        if (node->children->index > 0) {
            printf("{");
        }
        for (int i = 0; i < node->children->index; i++) {
            SyntreeNode *child = nodeListGet(node->children, i);
            syntreePrintNode(child);

        }
        if (node->children->index > 0) {
            printf("}");
        }
    }
}

void syntreePrint(const Syntree *self, SyntreeNodeID root) {
    SyntreeNode *rootNode = nodeById(self, root);
    syntreePrintNode(rootNode);
    printf("\n");
}


