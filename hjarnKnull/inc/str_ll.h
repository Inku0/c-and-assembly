#pragma once

typedef struct Node {
	char data;
	struct Node *next;
} Node;

// add a character to the linked list
Node* add(const char data);

// convert a string to a linked list of characters
Node* string_to_SLL(const char *text);

// convert a link list (from its head) to a string pointer
char *SLL_to_string(Node *head);

// (debugging) print every element in linked list
void print_list(const Node *head);

// calculate the length of the provided linked list
size_t sll_length(Node *head);

// free memory allocated for linked list
void free_sll(Node *head);

// optimize the string linked list by combining optimizable instructions.
// +++. becomes +.
Node* compress_consecutive(Node *head);