#ifndef RB_HEADER
#define RB_HEADER

#include <stdio.h>
#include <string.h>

struct rb_tree;
struct rb_node;

typedef int (*rb_comp_t)(void * a, void * b);
typedef int (*rb_dump_t)(void * v);

typedef struct rb_tree {
    struct rb_node * root;

    rb_comp_t comp;
    rb_dump_t dump;
} rb_tree_t;

typedef struct rb_node {
    int is_black;
    struct rb_node * left, * right, * parent;
    void * value
} rb_node_t;

int rb_insert(rb_tree_t * tree, void * value);
int rb_delete(rb_tree_t * tree, rb_node_t * node);
rb_node_t * rb_find(rb_tree_t * tree, void * value);
int rb_dump(rb_tree_t * tree);
void * rb_node_value(rb_node_t * node);

#endif
