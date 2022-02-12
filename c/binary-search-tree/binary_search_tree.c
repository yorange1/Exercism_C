#include "binary_search_tree.h"

#include <assert.h>
#include <stdlib.h>

static node_t *create_node(int data)
{
    node_t *node = (node_t *)calloc(1, sizeof(node_t));
    assert(node != NULL);

    node->data = data;

    return node;
}

static void add_node(node_t *root, int data)
{
    node_t **node = data <= root->data ? &root->left : &root->right;

    if (NULL == *node)
    {
        *node = create_node(data);
    }
    else
    {
        add_node(*node, data);
    }
}

static size_t count_node(node_t *tree)
{
    assert(tree != NULL);

    size_t count = 1;

    if (NULL == tree->left && NULL == tree->right)
    {
        return count;
    }

    if (tree->left != NULL)
    {
        count += count_node(tree->left);
    }

    if (tree->right != NULL)
    {
        count += count_node(tree->right);
    }

    return count;
}

node_t *build_tree(int *tree_data, size_t tree_data_len)
{
    assert(tree_data != NULL && tree_data_len > 0);

    node_t *root = create_node(tree_data[0]);

    for (size_t i = 1; i < tree_data_len; i++)
    {
        add_node(root, tree_data[i]);
    }

    return root;
}

void free_tree(node_t *tree)
{
    assert(NULL != tree);

    if (tree->left != NULL)
    {
        free_tree(tree->left);
    }

    if (tree->right != NULL)
    {
        free_tree(tree->right);
    }

    free(tree);
}

static void ldr_traver(node_t *tree, int *sorted_data, size_t *index)
{
    if (tree->left != NULL)
    {
        ldr_traver(tree->left, sorted_data, index);
    }

    sorted_data[(*index)++] = tree->data;

    if (tree->right != NULL)
    {
        ldr_traver(tree->right, sorted_data, index);
    }
}

int *sorted_data(node_t *tree)
{
    size_t node_num = count_node(tree);

    int *data = (int *)calloc(1, node_num * sizeof(int));
    assert(data != NULL);

    size_t index = 0;
    ldr_traver(tree, data, &index);

    return data;
}
