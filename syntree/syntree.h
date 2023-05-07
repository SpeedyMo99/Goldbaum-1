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
