/*
 *	Doubly linked list implementation by Paul Johnson
 *
 *	paulie@pauliesworld.org
 *	http://www.pauliesworld.org
 *
 */

#include <stdio.h>
#include <stdlib.h>

struct dl_list_node {
	int data;
	struct dl_list_node* previous;
	struct dl_list_node* next;
};

int
dl_list_node_count(struct dl_list_node* node)
{
	int node_count=0;

	if(node == NULL) {
		return 0;
	}

	while(node != NULL) {
		node_count++;
		node = node->next;
	}

	return(node_count);
}

struct dl_list_node*
dl_list_reverse(struct dl_list_node* node)
{
	while(node->previous != NULL) {
		node = node->previous;
	}

	return node;
}

struct dl_list_node*
dl_list_print(struct dl_list_node* node)
{
	printf("Previous\tCurrent\t\tNext\n");
	while(node != NULL) {

		if(node->previous == NULL) {
			printf("NULL\t\t");
		} else {
			printf("addr(%i)\t\t",node->previous->data);
		}

		printf("%i\t\t",node->data);

		if(node->next == NULL) {
			printf("NULL\t\n");
		} else {
			printf("addr(%i)\t\n",node->next->data);
		}

		node = node->next;
	}
}

struct dl_list_node*
dl_list_init()
{
	struct dl_list_node* head;
	head = (struct dl_list_node*)malloc(sizeof(struct dl_list_node));

	head->data = NULL;
	head->next = NULL;
	head->previous = NULL;

	return head;
}

struct dl_list_node*
dl_list_search(struct dl_list_node* node, int data)
{
	while(node != NULL) {
		if(node->data == data) {
			return node;
		}
		node = node->next;
	}

	return NULL;
}

struct dl_list_node*
dl_list_insert(struct dl_list_node* node, int data)
{
	struct dl_list_node* new_node;

	new_node = (struct dl_list_node*)malloc(sizeof(struct dl_list_node));

	if(new_node == NULL) {
		printf("No memory.");
		exit(1);
	} else {
		new_node ->data = data;
		new_node->next = NULL;
		new_node->previous = node;
		node->next = new_node;
		node = new_node;
	}
	return node;
}

struct dl_list_node*
dl_list_delete(struct dl_list_node* node, int data)
{
	node = dl_list_search(node,data);

	if (node != NULL) {
		if(node->next == NULL && node->previous == NULL) {
		} else if(node->next == NULL) {
			node->previous->next = NULL;
		} else if(node->previous == NULL) {
			node->next->previous = NULL;
		} else {
			node->previous->next = node->next;
			node->next->previous = node->previous;
		}

		free(node);
	}
}

int
main(int argc, char** argv)
{
	int i;
	struct dl_list_node* node = NULL;

	node = dl_list_init();

	for(i = 1; i < 10; i++) {
		node = dl_list_insert(node,i);
	}

	node = dl_list_reverse(node);

	printf("Doubly linked list created:\n");
	printf("Node count:\t%i\n",dl_list_node_count(node));
	printf("--------------------------------------\n");
	dl_list_print(node);
	sleep(2);
	printf("--------------------------------------\n");
	printf("Deleting the value 5\n");
	printf("--------------------------------------\n");
	dl_list_delete(node,5);
	sleep(2);
	dl_list_print(node);

}
