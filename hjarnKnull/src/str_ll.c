#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str_ll.h"

#include "simpleStack.h"

// inspiration from https://www.geeksforgeeks.org/dsa/convert-a-string-to-a-singly-linked-list/

// helper: compute length of SLL
size_t sll_length(Node *head) {
	size_t len = 0;
	for (Node *p = head; p; p = p->next) ++len;
	return len;
}

// helper: free SLL nodes
void free_sll(Node *head) {
	while (head) {
		Node *tmp = head;
		head = head->next;
		free(tmp);
	}
}

Node* add(const char data) {
	Node *n = malloc(sizeof(Node));
	if (n == NULL) {
		OOM;
	}
	n->data = data;
	n->next = NULL;
	return n;
}

Node* string_to_SLL(const char *text) {
	if (!text || !*text) return NULL;

	Node *head = add(text[0]);
	Node *curr = head;
	for (size_t i = 1; text[i] != '\0'; ++i) {
		curr->next = add(text[i]);
		curr = curr->next;
	}
	return head;
}

char *SSL_to_string(Node *head) {
	if (!head) return NULL;

	const size_t len = sll_length(head) + 1; // + 1 for NUL

	char *str = malloc(sizeof(char) * len);
	if (str == NULL) {
		OOM;
	}

	const Node *curr = head;
	int nth_char = 0;
	while (curr != NULL) {
		str[nth_char++] = curr->data;
		curr = curr->next;
	}
	str[nth_char] = '\0';

	// don't forget to free() !
	return str;
}

void print_list(const Node *head) {
	const Node *curr = head;
	while (curr) {
		printf("%c", curr->data);
		if (curr->next) printf(" -> ");
		curr = curr->next;
	}
	printf("\n");
}

void free_list(Node *head) {
	while (head) {
		Node *next = head->next;
		free(head);
		head = next;
	}
}
