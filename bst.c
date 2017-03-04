/*
 *	Binary search tree implementation by Paul Johnson
 *
 *	paulie@pauliesworld.org
 *	http://www.pauliesworld.org
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct bst_node {
	int data;
	int depth;
	struct bst_node* left;
	struct bst_node* right;
};

int
maximum(int left, int right)
{
	return((left > right) ? left : right);
}


struct bst_node*
bst_tree_find_minimum(struct bst_node* root)
{
	if(root == NULL) {
		return NULL;
	}

	if(root->left == NULL) {
		return root;
	} else {
		return bst_tree_find_minimum(root->left);
	}
}

struct bst_node*
bst_tree_reset_depth(struct bst_node* root)
{
	if(root == NULL) {
		return NULL;
	}

	root->depth--;

	bst_tree_reset_depth(root->left);
	bst_tree_reset_depth(root->right);
}

int
bst_tree_node_count(struct bst_node* root)
{
	if(root == NULL) {
		return 0;
	}

	return(1+bst_tree_node_count(root->left)
		+bst_tree_node_count(root->right));
}

int
bst_tree_height(struct bst_node* root, int height)
{
	int left, right;

	if(root == NULL) {
		return 0;
	}

	left = bst_tree_height(root->left,height);
	right = bst_tree_height(root->right,height);
	height = maximum(left,right);

	if(root->depth > height) {
		return root->depth;
	} else {
		return height;
	}
}

struct bst_node*
bst_tree_print(struct bst_node* root, int levels)
{
	int i;

	if(root != NULL) {
		bst_tree_print(root->right,levels);

		if(root->depth <= levels) {
			for(i = 0; i < root->depth; i++) {
				printf("   ");
			}

			printf("%i\n",root->data);
		}
		bst_tree_print(root->left,levels);
	}
}

struct bst_node*
bst_tree_search(struct bst_node* root, int data)
{
	if(root == NULL) {
		return NULL;
	}

	if(data < root->data) {
		return bst_tree_search(root->left,data);
	} else if(data > root->data) {
		return bst_tree_search(root->right,data);
	} else {
		return root;
	}
}

struct bst_node*
bst_tree_insert(struct bst_node* root, int data, int depth)
{
	if(root == NULL) {
		root = (struct bst_node*)malloc(sizeof(struct bst_node));

		if(root == NULL) {
			printf("No memory.");
			exit(1);
                } else {
			root->data = data;
			root->depth = depth;
			root->left = NULL;
			root->right = NULL;
		}
	} else {
		if(data < root->data) {
			root->left = bst_tree_insert(root->left,data,depth+1);
	 	} else if(data > root->data) {
			root->right = bst_tree_insert(root->right,data,depth+1);
		}
	}

	return root;
}

struct bst_node*
bst_tree_delete(struct bst_node* root, int data)
{
	struct bst_node* tmp_root;

	if(root == NULL) {
                return root;
	}

	if(data < root->data) {
		root->left = bst_tree_delete(root->left,data);
	} else if(data > root->data) {
		root->right = bst_tree_delete(root->right,data);
	} else if(root->left && root->right) {
       		tmp_root = bst_tree_find_minimum(root->right);
		root->data = tmp_root->data;
		root->right = bst_tree_delete(root->right,root->data);
	} else {
		tmp_root = root;
		if(root->left == NULL) {
			root = root->right;
		} else if(root->right == NULL) {
			root = root->left;
		}
		bst_tree_reset_depth(root);
		free(tmp_root);
	}
	return root;
}

int
main(int argc, char** argv)
{
	int i;
	struct bst_node* root = NULL;

	for(i = 0; i < 1000000; i++) {
		root = bst_tree_insert(root,rand()%1000000,0);
	}

	printf("Binary tree created:\n");
	printf("Node count:\t%i\n",bst_tree_node_count(root));
	printf("Tree height:\t%i\n",bst_tree_height(root,0));
	printf("-----------------------------\n");
	bst_tree_print(root,3);
	printf("-----------------------------\n");
	sleep(2);
	printf("Deleting the root node, %i\n",root->data);
	printf("-----------------------------\n");
	sleep(2);
	bst_tree_delete(root,root->data);
	bst_tree_print(root,3);
}
