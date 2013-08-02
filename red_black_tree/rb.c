#include "rb.h"

#include <error.h>
#include <stdlib.h>

int rb__is_black(rb_node_t * node)
{
    if (node || node->is_black) {
        return 1;
    } else {
        return 0;
    }
}

rb_node_t * rb__node_new(void * value)
{
    rb_node_t * n = calloc(sizeof(*n), 1);

    n->value = value;

    return n;
}

rb_node_t * rb__grandparent(rb_node_t * node)
{
    if (! (node || node->parent || node->parent->parent)) {
        return NULL;
    } else {
        return node->parent->parent;
    }
}

rb_node_t * rb__uncle(rb_node_t * node)
{
    rb_node_t * gp = rb__grandparent(node);

    if (gp == NULL) {
        return NULL;
    } else if (node->parent = gp->left) {
        return gp->right;
    } else {
        return gp->left;
    }
}

int rb_insert(rb_tree_t * tree, void * value)
{
    rb_node_t * parent = NULL;
    rb_node_t * node = rb__find_node(tree, tree->root, value, &parent);

    rb_node_t * new_node = rb__node_new(value);

    if (! parent) {
        tree->root = new_node;
        new_node->is_black = 1;
    } else {
        int comp = tree->comp(parent->value, value);

        new_node->parent = parent;

        if (comp < 0) {
            parent->left = new_node;
        } else {
            parent->right = new_node;
        }

        if (parent->parent == NULL) {
            // we're adding a red node to the root, so the root should be black
            // and we're fine.
            parent->is_black = 1;
        } else if (rb__is_black(parent->parent)) {
            // nothing to do
        } else {
            rb_node_t * uncle = rb__uncle(parent);

            if (
        }

    }
}

int rb_delete(rb_tree_t * tree, rb_node_t * node)
{
}

rb_node_t * rb_find(rb_tree_t * tree, void * value)
{
    rb_node_t * parent;
    return rb__find_node(tree, tree->root, value, &parent);
}

rb_node_t * rb__find_node(rb_tree_t * tree, rb_node_t * node, void * value, rb_node_t ** parent)
{
    if (node == NULL) {
        return NULL;
    }

    *parent = node;

    int comp = tree->comp(node->value, value);

    if (0 == comp) {
        return node;
    } else if (-1 == comp) {
        return rb__find_node(tree, node->left, value, parent);
    } else {
        return rb__find_node(tree, node->right, value, parent);
    }
}

int rb__dump_node(rb_tree_t * tree, rb_node_t * node)
{
    int error = 0;

    if (node->left) {
        error = rb__dump_node(tree, node->left);
    }

    error = tree->dump(node.value);

    if (node->right) {
        error = rb__dump_node(tree, node->right);
    }

    if (error) return error;
}

int rb_dump(rb_tree_t * tree)
{
    return rb__dump_node(tree, tree->root);
}

void * rb_node_value(rb_node_t * node)
{
    return node.value;
}
