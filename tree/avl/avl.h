#ifndef _AVL_H_
#define _AVL_H_

#include <stdint.h>

typedef int avl_t;

typedef struct avlnode_t {
    avl_t key;
    uint32_t height;
    struct avlnode_t *left;
    struct avlnode_t *right;
} avlnode;

uint32_t avl_height (avlnode* node);
void preorder_avltree (avlnode* root);
void inorder_avltree (avlnode* root);
void postorder_avltree (avlnode* root);
avlnode* avl_search (avlnode *root, avl_t key);
avlnode* avl_min (avlnode *root);
avlnode* avl_max (avlnode *root);
avlnode* avl_insert (avlnode *root, avl_t key);
avlnode* avl_delete (avlnode *root, avl_t key);
void avl_destroy (avlnode *root);
void print_avl (avlnode *root, avl_t key, int dir);
int avl_test(void);

#endif
