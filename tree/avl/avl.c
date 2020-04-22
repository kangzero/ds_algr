#include <stdlib.h>
#include <stdio.h>

#include "avl.h"
#include "../../log.h"

#define TAG     "AVL"
//#define ITERATIVE
#define RECURSIVE

/*
 * AVL Tree: Height-balanced tree invented by Adelson-Velsky and Evgendis Landis
 *
 * Spec: a self-balancing Binary Search Tree where the difference between heights of
 * left and right subtrees can NOT be more than one for all nodes.
 *
 * Reason: Most of the BST operations take O(H) time where h is the height of the BST.
 * The cost of these operations may become O(N) for a skewed Binary tree. If we make
 * sure that the height of the tree remains O(logN) after every insertion and deletion,
 * then we can guarantee an upper bound of O(logN) for all these operations. The height
 * of an AVL tree is always O(logN) where n is the number of nodes in the tree.
 */

#define HEIGHT(p)   (((p) == NULL) ? 0 : (((avlnode*)(p))->height))

#define MAX(a, b)   \
    ({__typeof__(a) _a = (a); \
      __typeof__(b) _b = b; \
      _a > _b ? _a : _b;})

static avlnode* ll_rotation (avlnode* node);
static avlnode* rr_rotation (avlnode* node);
static avlnode* lr_rotation (avlnode* node);
static avlnode* rl_rotation (avlnode* node);
static avlnode* create_avl_node (avl_t key, avlnode* left, avlnode* right);
static avlnode* delete_node (avlnode *root, avlnode *node);

// the height of the tree is the node's max level
// 1. an empty bst's height is 0
// 2. the root height is 1, root's child is 2, and so on...
uint32_t avl_height (avlnode* node)
{
    return HEIGHT(node);
}

// preoder traverse the avl tree
void preorder_avltree (avlnode* root)
{
    if (root != NULL) {
        Log.i(TAG, "%d", root->key);
        preorder_avltree(root->left);
        preorder_avltree(root->right);
    }
}


// inorder traverse the avl tree
void inorder_avltree (avlnode* root)
{
    if (root != NULL) {
        inorder_avltree(root->left);
        Log.i(TAG, "%d", root->key);
        inorder_avltree(root->right);
    }
}

// postorder traverse the avl tree
void postorder_avltree (avlnode* root)
{
    if (root != NULL) {
        postorder_avltree(root->left);
        postorder_avltree(root->right);
        Log.i(TAG, "%d", root->key);
    }
}

// search the key node in the avl tree
avlnode* avl_search (avlnode *root, avl_t key)
{
#ifdef RECURSIVE
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        return avl_search(root->left, key);
    else
        return avl_search(root->right, key);
#elif ITERATIVE
    avlnode *cur = root;

    while (cur != NULL && cur->key != key) {
        if (key < cur->key)
            cur = cur->left;
        else
            cur = cur->right;
    }

    return cur;
#endif
}

// the min node in the tree
avlnode* avl_min (avlnode *root)
{
    if (root == NULL)
        return NULL;

    while (root->left != NULL)
        root = root->left;
    return root;
}

// the max node in the tree
avlnode* avl_max (avlnode *root)
{
    if (root == NULL)
        return NULL;

    while (root->right != NULL)
        root = root->right;
    return root;
}

// left left rotation: the node is the min imbalance tree, return the root after rotation
static avlnode* ll_rotation (avlnode* node)
{
    avlnode *p = node->left;
    node->left = p->right;
    p->right = node;

    node->height = MAX(HEIGHT(node->left), HEIGHT(node->right)) + 1;
    p->height = MAX(HEIGHT(p->left), node->height) + 1;

    return p;
}

// right right rotation
static avlnode* rr_rotation (avlnode* node)
{
    avlnode *p = node->right;
    node->right = p->left;
    p->left = node;

    node->height = MAX(HEIGHT(node->left), HEIGHT(node->right)) + 1;
    p->height = MAX(node->height, HEIGHT(p->right)) + 1;

    return p;
}

// left right rotation
static avlnode* lr_rotation (avlnode* node)
{
    node->left = rr_rotation(node->left);
    return ll_rotation(node);
}

// right left rotation
static avlnode* rl_rotation (avlnode* node)
{
    node->right = ll_rotation(node->right);
    return rr_rotation(node);
}

// create an avl tree node
static avlnode* create_avl_node (avl_t key, avlnode* left, avlnode* right)
{
    avlnode *t =  (avlnode*)malloc(sizeof(avlnode));
    if (t == NULL) {
        Log.w(TAG, "%s failed", __func__);
        return NULL;
    }

    t->key = key;
    t->left = left;
    t->right = right;
    t->height = 0;

    return t;
}

// insert a node into the avl tree
avlnode* avl_insert (avlnode *root, avl_t key)
{
    if (root == NULL) { // insert an node into an empty avl tree
        root = create_avl_node(key, NULL, NULL);
        if (root == NULL) {
            Log.w(TAG, "%s: create node fail", __func__);
            return NULL;
        }
    } else if (key < root->key) { // insert the node into left subtree
        root->left = avl_insert(root->left, key);
        // if AVL lost balance after insertion in left subtree, ll or lr rotate
        if (HEIGHT(root->left) - HEIGHT(root->right) > 1) {
            if (key < root->left->key)
                root = ll_rotation(root);
            else
                root = lr_rotation(root);
        }
    } else if (key > root->key) { // insert the node into right subtree
        root->right = avl_insert(root->right, key);
        // if AVL lost balance after insertion in right subtree, rr or rl rotate
        if (HEIGHT(root->right) - HEIGHT(root->left) > 1) {
            if (key > root->right->key)
                root = rr_rotation(root);
            else
                root = rl_rotation(root);
        }
    } else if (key == root->key) { // do nothing for the same node
        Log.w(TAG, "%s: can't insert a same node", __func__);
    }

    root->height = MAX(HEIGHT(root->left), HEIGHT(root->right)) + 1;

    return root;
}

// TBD: need to update height after delete node
static avlnode* delete_node (avlnode *root, avlnode *node)
{
    // if avl is an empty tree or node is NULL, do nothing
    if (root == NULL || node == NULL)
        return root;

    if (node->key < root->key) { // node is in left subtree
        root->left = delete_node(root->left, node);
        if (HEIGHT(root->right) - HEIGHT(root->left) == 2) {
            avlnode *r = root->right;
            if (HEIGHT(r->left) > HEIGHT(r->right))
                root = rl_rotation(root);
            else
                root = rr_rotation(root);
        }
    } else if (node->key > root->key) { // node is in right subtree
        root->right = delete_node(root->right, node);
        if (HEIGHT(root->left) - HEIGHT(root->right) == 2) {
            avlnode *l = root->left;
            if (HEIGHT(l->right) > HEIGHT(l->left))
                root = lr_rotation(root);
            else
                root = ll_rotation(root);
        }
    } else { // root is the node
        if (root->left && root->right) {// root has left and right subtree
            if (HEIGHT(root->left) > HEIGHT(root->right)) {
                // if left subtree is higher than right subtree:
                // 1. search the max node in left subtree
                // 2. switch the key between max node and root node
                // 3. delete the max node
                avlnode *max = avl_max(root->left);
                root->key = max->key;
                root->left = delete_node(root->left, max);
            } else {
                // if left subtree is not higher than right subtree:
                // 1. search the min node in the right subtree
                // 2. siwth the key between min and root
                // 3. delte the min node
                avlnode *min = avl_min(root->right);
                root->key = min->key;
                root->right = delete_node(root->right, min);
            }
        } else {
            avlnode *tmp = root;
            root = root->left ? root->left : root->right;
            free(tmp), tmp = NULL;
        }
    }

    return root;
}

// delete a node
avlnode* avl_delete (avlnode *root, avl_t key)
{
    avlnode *n = NULL;

    if ((n = avl_search(root, key)) != NULL)
        root = delete_node(root, n);

    return root;
}

// destroy the avl tree
void avl_destroy (avlnode *root)
{
    if (root == NULL) return;

    if (root->left != NULL)
        avl_destroy(root->left);
    if (root->right != NULL)
        avl_destroy(root->right);

    free(root), root = NULL;
}

// print the avl tree
void print_avl (avlnode *root, avl_t key, int dir)
{
    if (root != NULL) {
        if (dir == 0)
            Log.i(TAG, "%d is root", root->key);
        else
            Log.i(TAG, "%d is %d's %s child", root->key, key, dir == 1 ? "right": "left");

        print_avl(root->left, root->key, -1);
        print_avl(root->right, root->key, 1);
    }
}

#ifdef _MODULAR_TEST
int main(int argc, char* argv)
{
    logger_init();
    avl_test();
    return 1;
}
#endif

static avl_t arr[]= {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9};
#define TBL_SIZE(a) ( (sizeof(a)) / (sizeof(a[0])) )

int avl_test(void)
{
    Log.i(TAG, "==== %s start ====\n", __func__);

    int len = TBL_SIZE(arr);
    Log.i(TAG, "len = %d", len);
    avlnode *root = NULL;
    Log.i(TAG, "Added nodes into the tree:");
    for (int i = 0; i < len; i++) {
        //Log.i(TAG, "%d", arr[i]);
        root = avl_insert(root, arr[i]);
        Log.i(TAG, "insert node %d", arr[i]);
        print_avl(root, root->key, 0);
        Log.i(TAG, "height is: %d", avl_height(root));
    }

    Log.i(TAG, "Preorder traverse the avl tree:");
    preorder_avltree(root);
    Log.i(TAG, "Inorder traverse the avl tree:");
    inorder_avltree(root);
    Log.i(TAG, "Postorder traverse the avl tree:");
    postorder_avltree(root);

    Log.i(TAG, "height is: %d", avl_height(root));
    Log.i(TAG, "min is: %d", avl_min(root)->key);
    Log.i(TAG, "max is: %d", avl_max(root)->key);
    Log.i(TAG, "the avl tree is:");
    print_avl(root, root->key, 0);

    Log.i(TAG, "delete the node(left subtree is higher than right subtree): %d", 13 /*root->key*/);
    root = avl_delete(root, 13/*root->key*/);

    Log.i(TAG, "height is: %d", avl_height(root));
    Log.i(TAG, "Inorder traverse the tree:");
    inorder_avltree(root);
    Log.i(TAG, "the avl tree is:");
    print_avl(root, root->key, 0);

    Log.i(TAG, "delete the node(left subtree is NOT higher than right subtree): %d", 9 /*root->key*/);
    root = avl_delete(root, 9/*root->key*/);

    Log.i(TAG, "height is: %d", avl_height(root));
    Log.i(TAG, "Inorder traverse the tree:");
    inorder_avltree(root);
    Log.i(TAG, "the avl tree is:");
    print_avl(root, root->key, 0);

    Log.i(TAG, "delete the root node: %d", root->key);
    root = avl_delete(root, root->key);

    Log.i(TAG, "height is: %d", avl_height(root));
    Log.i(TAG, "Inorder traverse the tree:");
    inorder_avltree(root);
    Log.i(TAG, "the avl tree is:");
    print_avl(root, root->key, 0);

    avl_destroy(root);
    Log.i(TAG, "==== %s end ====\n", __func__);

    return 1;
}
