#ifndef _BST_H_
#define _BST_H_

#include <stdint.h>

typedef int bst_t;

typedef struct bstnode_t {
    bst_t key;
    struct bstnode_t *left;
    struct bstnode_t *right;
    struct bstnode_t *parent;
} bstnode_t;

void preorder_traversal_bst (bstnode_t *root);
void inorder_traversal_bst(bstnode_t *root);
void postorder_traversal_bst(bstnode_t *root);
bstnode_t* bst_insert (bstnode_t* root, bst_t key);
bstnode_t* bst_delete(bstnode_t* root, bst_t key);
bstnode_t* bst_min (bstnode_t* root);
bstnode_t* bst_max (bstnode_t* root);
bstnode_t* bst_successor (bstnode_t* node);
bstnode_t* bst_predecessor (bstnode_t* node);
bstnode_t* bst_search (bstnode_t *root, bst_t key);
uint32_t bst_max_depth (bstnode_t* root);
void bst_destroy(bstnode_t *root);
void print_bst(bstnode_t* root, bst_t key, char dir);

int bst_test(void);

#endif
