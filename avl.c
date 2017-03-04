/*
 *      AVL tree implementation by Paul Johnson
 *	http://en.wikipedia.org/wiki/AVL_tree
 *
 *      paulie@pauliesworld.org
 *      http://www.pauliesworld.org
 *
 */

#include <stdio.h>
#include <stdlib.h>

struct avl_node {
/*
 *	Each AVL node has a depth and height variable.  Height
 *	calculates the maximum descendant length of a node's subtree.
 *	Depth calculates a node's position relative to the root of the
 *	entire AVL tree.  Depth is an expensive variable and is used 
 *	only to print out the tree conveniently.  If you use this code,
 *	I recommend commenting out any thing related to depth
 *	calculation.
 */

	int data;
	int depth;
	int height;
	struct avl_node* left;
	struct avl_node* right;
};

int
avl_tree_node_count(struct avl_node* root)
{
	if(root == NULL) {
		return 0;
	}

	return(1+avl_tree_node_count(root->left)
		+avl_tree_node_count(root->right));
}

int
height(struct avl_node* root)
{
	if(root == NULL) {
		return 0;
	} else {
		return root->height;
	}
}

int
maximum(int left, int right)
{
	return((left > right) ? left : right);
}

struct avl_node*
avl_tree_print(struct avl_node* root, int levels)
{
	int i;

	if(root != NULL) {
		avl_tree_print(root->right,levels);

		if (root->depth < levels) {
			for (i = 0; i < root->depth; i++) {
				printf("   ");
			}
		printf("%i\n",root->data);
	}

	avl_tree_print(root->left,levels);

	}
}

struct avl_node*
avl_tree_find_minimum(struct avl_node* root)
{
	if(root == NULL) {
		return NULL;
	}

	if(root->left == NULL) {
		return root;
	} else {
		return avl_tree_find_minimum(root->left);
	}
}

struct avl_node*
avl_tree_find_maximum(struct avl_node* root)
{
	if(root != NULL) {
		while(root->right != NULL) {
			root = root->right;
		}
	}

	return root;
}

struct avl_node*
avl_tree_subtract_depth(struct avl_node* root)
{
	if(root == NULL) {
		return NULL;
	}

	root->depth--;

	avl_tree_subtract_depth(root->left);
	avl_tree_subtract_depth(root->right);
}

struct avl_node*
avl_tree_add_depth(struct avl_node* root)
{
	if (root == NULL) {
		return NULL;
	}

	root->depth++;

	avl_tree_add_depth(root->left);
	avl_tree_add_depth(root->right);
}

struct avl_node*
avl_tree_rotate_left_left(struct avl_node* root)
{

/*
 *      Single Rotation (LL)
 *
 *             r              nr
 *            / \            /  \
 *           nr        ->  left  r
 *          / \            /  \ / \
 *       left
 *
 */
	struct avl_node* new_root;

	new_root = root->left;
	root->left = new_root->right;
	new_root->right = root;

	root->depth++;
	new_root->depth--;
	avl_tree_add_depth(root->right);
	avl_tree_subtract_depth(new_root->left);

	root->height = maximum(height(root->left),height(root->right))+1;
	new_root->height = maximum(height(new_root->left),root->height)+1;

	return new_root;
}

struct avl_node*
avl_tree_rotate_right_right(struct avl_node* root)
{

/*
 *      Single Rotation (RR)
 *
 *       r                   nr
 *      / \                 /  \
 *         nr       ->     r   right
 *        /  \            / \   / \
 *           right
 *
 */
	struct avl_node* new_root;

	new_root = root->right;
	root->right = new_root->left;
	new_root->left = root;

	root->depth++;
	new_root->depth--;
	avl_tree_add_depth(root->left);
	avl_tree_subtract_depth(new_root->right);

	root->height = maximum(height(root->left),height(root->right))+1;
	new_root->height = maximum(height(new_root->right),root->height)+1;

	return new_root;
}

struct avl_node*
avl_tree_rotate_left_right(struct avl_node* root)
{
/*
 *	Double Rotation (LR)
 *
 *	   r             r              nr
 *	  / \           / \            /  \
 *	 A             nr             A    r
 *	/ \      ->   / \      ->    / \  / \
 *	  nr         A
 *	 /  \       / \
 *
 */
	root->left = avl_tree_rotate_right_right(root->left);
	root = avl_tree_rotate_left_left(root);
	return(root);
}

struct avl_node*
avl_tree_rotate_right_left(struct avl_node* root)
{

/*
 *      Double Rotation (RL)
 *
 *       r            r                 nr
 *      / \          / \               /  \
 *         A            nr            r    A 
 *        / \   ->     /  \    ->    / \  / \
 *       nr                A
 *      /  \              / \
 *
 */
	root->right = avl_tree_rotate_left_left(root->right);
	root = avl_tree_rotate_right_right(root);
	return(root);
}


struct avl_node*
avl_tree_insert(struct avl_node* root, int data, int depth)
{
	if(root == NULL) {
		root = (struct avl_node*)malloc(sizeof(struct avl_node));

		if(root == NULL) {
			printf("Out of memory");
			exit(0);
		} else {
			root->data = data;
			root->depth = depth;
			root->height = 0;
			root->left = NULL;
			root->right = NULL;
		}
	} else if(data < root->data) {
		root->left = avl_tree_insert(root->left,data,depth+1);

		if(height(root->left)-height(root->right) > 1) {
			if(data < root->left->data) {
                        	root = avl_tree_rotate_left_left(root);
			} else {
				root = avl_tree_rotate_left_right(root);
			}
		}
	} else if(data > root->data) {
		root->right = avl_tree_insert(root->right,data,depth+1);

		if(height(root->right)-height(root->left) > 1) {
			if(data > root->right->data) {
				root = avl_tree_rotate_right_right(root);
			} else {
				root = avl_tree_rotate_right_left(root);
			}
		}
	}

	root->height = maximum(height(root->left),height(root->right))+1;
	return(root);
}

struct avl_node*
avl_tree_delete(struct avl_node* root,int data)
{
	struct avl_node* new_root;

	if (root == NULL) {
		return NULL;
	}

	if(root->data > data) {
		root->left = avl_tree_delete(root->left,data);

		if(height(root->right)-height(root->left) > 1) {
			if(data < root->right->data) {
				root = avl_tree_rotate_right_right(root);
			} else {
				root = avl_tree_rotate_right_left(root);
			}
		}
	} else if(root->data < data) {
		root->right = avl_tree_delete(root->right,data);
		
		if(height(root->left)-height(root->right) > 1) {
			if(data > root->left->data) {
				root = avl_tree_rotate_left_left(root);
			} else {
				root = avl_tree_rotate_left_right(root);
			}
		}
	} else if(root->data == data) {
		new_root = root;

		if(new_root->right == NULL) {
			root = new_root->left;
			free(new_root);
		} else if(new_root->left == NULL) {
			root = new_root->right;
			free(new_root);
		} else {
			new_root = avl_tree_find_minimum(new_root->right);
			root->data = new_root->data;
			root = new_root->right;
			free(new_root);
		}
	}

	if (root != NULL) {
        	root->height =maximum(height(root->left),height(root->right))+1;
	}

        return(root);
}

int
main(int argc, char** argv) {
	int i;
	struct avl_node* root = NULL;

	for(i = 0; i < 1000000; i++) {
		root = avl_tree_insert(root,rand()%1000000,0);
	}
	printf("AVL tree created:\n");
	printf("Node count:\t%i\n",avl_tree_node_count(root));
	printf("Tree height:\t%i\n",root->height);
	printf("-----------------------------\n");
	avl_tree_print(root,4);
	printf("-----------------------------\n");
	sleep(2);
	printf("Deleting the root node, %i\n",root->data);
	printf("-----------------------------\n");
	sleep(2);
	avl_tree_delete(root,root->data);
	avl_tree_print(root,4);
}
