#pragma once

typedef struct Node {
	char data;
	struct Node *next;
} Node;

Node* add(const char data);
Node* string_to_SLL(const char *text);
char *SSL_to_string(Node *head);
void print_list(const Node *head);
void free_list(Node *head);
size_t sll_length(Node *head);
void free_sll(Node *head);
void compress_consecutive(Node *head);