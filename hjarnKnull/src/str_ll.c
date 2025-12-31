#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str_ll.h"

#include "bf.h"
#include "simpleStack.h"

static void free_range(Node *start, Node *end_exclusive) {
	while (start && start != end_exclusive) {
		Node *tmp = start;
		start = start->next;
		free(tmp);
	}
}

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

struct comp{int count; Node *end;} compress(Node *curr, const char negative, const char positive) {
	Node *runner = curr;
	Node *block_end = curr;
	int count = 0;
	while (runner && (runner->data == negative || runner->data == positive)) {
		count += runner->data == positive ? 1 : -1;
		block_end = runner;
		runner = runner->next;
	}
	const struct comp comp_result = {
		.count = count,
		.end = block_end
	};
	return comp_result;
}

Node *compress_consecutive(Node *head) {
	if (!head) return NULL;

	Node *prev = NULL;
	Node *curr = head;

	while (curr) {
		if (curr->data == BF_INCREASE || curr->data == BF_DECREASE || curr->data == BF_LEFT || curr->data == BF_RIGHT) {
			Node *block_start = curr;
			Node *block_end = NULL;
			Node *runner = curr;

			const char positive = curr->data == BF_INCREASE ? BF_INCREASE : BF_RIGHT;
			const char negative = curr->data == BF_DECREASE ? BF_DECREASE : BF_LEFT;
			const struct comp comp_result = compress(runner, negative, positive);
			block_end = comp_result.end;

			if (comp_result.count == 0) {
				Node *after = runner;

				if (prev) {
					prev->next = after;
					free_range(block_start, after);
					curr = after;
				} else {
					if (!after) {
						free_range(block_start, NULL);
						return NULL;
					}
					free_range(block_start->next, after);
					block_start->data = after->data;
					block_start->next = after->next;
					free(after);
					curr = block_start;
				}
				continue;
			}

			prev = block_end;
			curr = runner;
			continue;
		}

		prev = curr;
		curr = curr->next;
	}
	return head;
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

char *SLL_to_string(Node *head) {
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
