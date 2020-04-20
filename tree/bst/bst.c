#include <stdlib.h>
#include <math.h>

#include "bst.h"
#include "../../log.h"

#define TAG     "BST"

#define RECURSIVE   1
#define ITERATIVE   0

#define max(a, b) \
    ({ __typeof__(a) _a = (a); \
     __typeof__(b) _b = (b); \
     _a > _b ? _a : _b; })

static bstnode_t* create_bst_node (bst_t key, bstnode_t* parent, bstnode_t *left, bstnode_t *right);
static bstnode_t* insert_bst_node (bstnode_t* root, bstnode_t* node);
static bstnode_t* delete_bst_node (bstnode_t* root, bstnode_t* node);

// create a binary tree node, parent member is not necessary but convenient for node insert and delete
static bstnode_t* create_bst_node (bst_t key, bstnode_t* parent, bstnode_t *left, bstnode_t *right)
{
    bstnode_t *t = malloc(sizeof(bstnode_t));
    if (t != NULL) {
        t->key = key;
        t->left = left;
        t->right = right;
        t->parent = parent;
    }
    return t;
}

// insert a binary tree node into the tree
static bstnode_t* insert_bst_node (bstnode_t* root, bstnode_t* node)
{
    bstnode_t *pre = NULL;
    bstnode_t *cur = root;

    while (cur != NULL) {
        pre = cur;
        if (cur->key > node->key) {
            cur = cur->left;
        } else if (cur->key < node->key) {
            cur = cur->right;
        } else {
            // do nothing for the same node
            free(node), node = NULL;
            return root;
        }
    }

    node->parent = pre;
    if (pre == NULL)
        root = node;
    else if (pre->key > node->key)
        pre->left = node;
    else
        pre->right = node;

    return root;
}


// create a node with key value and insert it into the tree
bstnode_t* bst_insert (bstnode_t* root, bst_t key)
{
    bstnode_t* node = create_bst_node(key, NULL, NULL, NULL);
    if (!node)
        return root;

    return insert_bst_node(root, node);
}

// delete a node in the tree, return the root of the new tree
static bstnode_t* delete_bst_node (bstnode_t* root, bstnode_t* node)
{
    bstnode_t* rm = NULL;
    bstnode_t* next = NULL;

    if (node->left == NULL || node->right == NULL)
        rm = node; // if node is a leaf node or only has one child(l or r), rm should be node itself
    else
        rm = bst_successor(node); // if node has left and right childs, rm should be its succesor node

    // for case of node only have one child
    if (node->left != NULL)
        next = rm->left;
    else
        next = rm->right;

    if (next != NULL)
        next->parent = rm->parent; // connect the next node to the parent of node

    if (rm->parent == NULL)
        root = next; // if the node is root of tree, the new root should be succesor
    else if (rm == rm->parent->left)
        rm->parent->left = next; // if the node is a left node, connect its parent to its left child
    else
        rm->parent->right = next; // if the node is a right node, connect its parent to its right child

    // for case of node have two childs
    if (rm != node)
        node->key = rm->key; // replace key of the node with its succesor, and then remove rm mode

    if (rm != NULL)
        free(rm), rm = NULL;

    return root;
}

// delete the node with the key value
bstnode_t* bst_delete(bstnode_t* root, bst_t key)
{
    bstnode_t* node;

    if ((node = bst_search(root, key)) != NULL)
        root = delete_bst_node(root, node);

    return root;
}

// find the min node in the tree
bstnode_t* bst_min (bstnode_t* root)
{
    if (root == NULL)
        return NULL;

    bstnode_t *cur = root;
    while (cur->left != NULL)
        cur = cur->left;

    return cur;
}

// find the max node in the tree
bstnode_t* bst_max (bstnode_t* root)
{
    if (root == NULL)
        return NULL;

    bstnode_t *cur = root;
    while (cur->right != NULL)
        cur = cur->right;

    return cur;
}

/*
 * Here is an example for better understanding succesor and predecessor node:
 *                  6
 *                /   \
 *               1     7
 *                \     \
 *                 5     9
 *                /     /  \
 *               3     8    10
 *              / \
 *             2   4
 *
 * succesor node:
 * 1. if the node has a right child, its successor node is its min node in its child tree
 *    node 7's successor is 8
 * 2. if the node does NOT has a right child
 *    a.if the node is a left child, its succesor is its parent node
 *      node 2's succesor is 3
 *    b. the node is a right child, then search the node p from its parent node to root, p is a left child
 *      node 5's succesor is 6
 *
 * predecessor node:
 * 1. if the node has a left child, its predecessor node is its max node in its child tree
 *    node 6's predecessor is 5
 * 2. if the node does NOT has a left child
 *    a. if the node is a right child, its predecessor is its parent node
 *      node 4's predecessor is 3
 *    b. if the node is a left child, then searcch the node p from its parent node to root, p is a right child
 *      node 2's predecessor is 1
 */

/*
 *  The code under test could eaisly search from the node to the root since we have parent node in the node struct.
 *  However, tf we don't have parent node member in the tree node struct, saying only left and right node members.
 *  Then we have search the tree from root to the node to find the succesor or predecessor node.
 *
 *  succesor and predecessor search function for the node w/o parent meber is shown as below: [To Be Verified]
 */
#define NO_PARENT_MEMBER

#ifdef NO_PARENT_MEMBER
typedef struct treeNode {
    int val;
    struct treeNode *left;
    struct treeNode *right;
} TreeNode;

static TreeNode* get_right_node(TreeNode* root)
{
    if (root == NULL) return NULL;

    while (root->right != NULL)
        root = root->right;

    return root;
}

static TreeNode* get_parent_node(TreeNode* root, int key, TreeNode** parent, TreeNode** firstParent)
{
    while (root) {
        if (root->val = key)
            return root;

        *parent = root;
        if (root->val > key) {
            root = root->left;
        } else {
            *firstParent = root; // right node exists
            root = root->right;
        }
    }

    return NULL;
}

static TreeNode* get_predecessor(TreeNode* root, int key)
{
    if (root) {
        TreeNode *parent, *firstParent;
        TreeNode *node = get_parent_node(root, key, &parent, &firstParent);
        if (node == NULL) return node;

        if (node->left)
            return get_right_node(node->right);
        if (parent == NULL || (parent && firstParent == NULL))
            return NULL;
        if (node == parent->right)
            return parent;
        else
            return firstParent;
    }

    return root;
}

static TreeNode* get_left_node(TreeNode* root)
{
    if (root == NULL) return NULL;

    while (root != NULL)
        root = root->left;

    return root;
}

static TreeNode* get_node(TreeNode* root, int key, TreeNode** parent, TreeNode** firstParent)
{
    while (root) {
        if (root->val == key)
            return root;

        *parent = root;
        if (root->val < key) {
            root = root->right;
        } else {
            *firstParent = root; // left node exists
            root = root->left;
        }
    }
    return NULL;
}

static TreeNode* get_predecessor_node(TreeNode* root, int key)
{
    if (root) {
        TreeNode *parent, *firstParent;
        TreeNode *node = get_node(root, key, &parent, &firstParent);
        if (node == NULL) return NULL;

        if (node->right)
            return get_right_node(node->right);
        if (parent == NULL || (parent && firstParent == NULL)) return NULL;
        if (node == parent->left)
            return parent;
        else
            return firstParent;
    }
    return root;
}
#endif

// find node's succesor: the min node in the tree with a key larger than the input node
bstnode_t* bst_successor (bstnode_t* node)
{
    // node has right child
    if (node->right != NULL)
        return bst_min(node->right);

    // if the node does not have right child, 2 cases:
    // 1. node is a left child, then its successor is its parent node
    // 2. node is a right child, then its succesor is its lowest parent node who has left child
    bstnode_t *p = node->parent;
    while (p != NULL && node == p->right) {
        node = p;
        p = p->parent;
    }

    return p;
}

// find node's predecessor: the max node in the tree with a key smaller than the input node
bstnode_t* bst_predecessor (bstnode_t* node)
{
    // node has left child
    if (node->left)
        return bst_max(node->left);

    // if the node does not have left child
    // 1. node is a right child, then its predecessor is its parent node
    // 2. node is a left child, then its predecessor is its lowest parent node who has right node
    bstnode_t* p = node->parent;
    while (p != NULL && node == p->left) {
        node = p;
        p = node->parent;
    }
    return p;
}

// preorder traverse the tree
void preorder_traversal_bst (bstnode_t *root)
{
#if RECURSIVE
    if (root != NULL) {
        Log.i(TAG, "%d", root->key);
        preorder_traversal_bst(root->left);
        preorder_traversal_bst(root->right);
    }
#elif ITERATIVE

#endif
}

// inorder traverse the tree
void inorder_traversal_bst (bstnode_t *root)
{
#if RECURSIVE
    if (root != NULL) {
        inorder_traversal_bst(root->left);
        Log.i(TAG, "%d", root->key);
        inorder_traversal_bst(root->right);
    }
#elif ITERATIVE

#endif
}

// postorder traverse the tree
void postorder_traversal_bst (bstnode_t *root)
{
#if RECURSIVE
    if (root != NULL) {
        postorder_traversal_bst(root->left);
        postorder_traversal_bst(root->right);
        Log.i(TAG, "%d", root->key);
    }
#elif ITERATIVE

#endif
}

// search a node in the tree
bstnode_t* bst_search (bstnode_t *root, bst_t key)
{
#if RECURSIVE
    if (root == NULL || root->key == key)
        return root;

    if (key < root->key)
        bst_search(root->left, key);
    else
        bst_search(root->right, key);
#elif ITERATIVE
    bstnode_t *ret = root;
    while (ret != NULL && ret->key != key) {
        if (key < ret->key)
            ret = ret->left;
        else
            ret = ret->right;
    }
    return ret;
#endif
}

// get the max depth of the tree
uint32_t bst_max_depth (bstnode_t* root)
{
#if RECURSIVE
    if (root == NULL) return 0;

    return max(1 + bst_max_depth(root->left), 1 + bst_max_depth(root->right));
#elif ITERATIVE
    // TBD - by queue
#endif
}

// destroy the tree
void bst_destroy(bstnode_t *root)
{
    if (root == NULL)
        return;

    if (root->left != NULL)
        bst_destroy(root->left);
    if (root->right != NULL)
        bst_destroy(root->right);

    free(root), root = NULL;
}

// print the tree
void print_bst (bstnode_t* root, bst_t key, char dir)
{
    if (root != NULL) {
        if (dir == 0)
            Log.i(TAG, "%2d is root", root->key);
        else
            Log.i(TAG, "%2d is %2d's %6s child", root->key, key, dir == 1 ? "right": "left");

        print_bst(root->left, root->key, -1);
        print_bst(root->right, root->key, 1);
    }
}

#ifdef _MODULAR_TEST
int main(int argc, char* argv)
{
    logger_init();
    bst_test();
    return 1;
}
#endif

static int arr1[] = {1, 5, 4, 3, 2, 6};
static int arr2[] = {6, 1, 7, 5, 9, 3, 8, 10, 2, 4};

#define TREE_SIZE(a)    ((sizeof(a)) / sizeof(a[0]))

int bst_test(void)
{
    int i, len;
    bstnode_t *root = NULL;

    Log.i(TAG, "==== %s start ====\n", __func__);

    Log.i(TAG, "Added node into the tree:");
    len = TREE_SIZE(arr1);
    for (int i = 0; i < len; i++) {
        Log.i(TAG, "%d", arr1[i]);
        root = bst_insert(root, arr1[i]);
    }

    Log.i(TAG, "Preorder traversal:");
    preorder_traversal_bst(root);

    Log.i(TAG, "Inorder traversal:");
    inorder_traversal_bst(root);

    Log.i(TAG, "Postorder traversal:");
    postorder_traversal_bst(root);

    Log.i(TAG, "The min value is:");
    Log.i(TAG, "%d", bst_min(root)->key);

    Log.i(TAG, "The max value is:");
    Log.i(TAG, "%d", bst_max(root)->key);

    Log.i(TAG, "The max depth of the tree is:");
    Log.i(TAG, "%lu", bst_max_depth(root));

    Log.i(TAG, "Print the tree:");
    print_bst(root, root->key, 0);

    Log.i(TAG, "Delete node %d:", arr1[3]);
    root = bst_delete(root, arr1[3]);
    inorder_traversal_bst(root);

    Log.i(TAG, "Delete root node %d:", arr1[0]);
    root = bst_delete(root, arr1[0]);
    inorder_traversal_bst(root);

    bst_destroy(root);

    Log.i(TAG, "==== %s end ====\n", __func__);
    return 1;
}


