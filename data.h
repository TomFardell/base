#ifndef DATA_H
#define DATA_H

#include "memory.h"

typedef struct LinkNode {
  struct LinkNode *next;
  struct LinkNode *prev;
} LinkNode;

// Initialise a new link node given pointers to next and previous nodes
LinkNode link_node_init(LinkNode *next, LinkNode *prev);

// Get the container node for a given link node, given the link node is a specified member of a specified type
#define link_node_get_container_node(node, type_name, member_name) \
  ((type_name *)((U64)(node) - offset_of(type_name, member_name)))

// Initialise a given link node to be the head of a new linked list
void linked_list_init(LinkNode *head);

// Push a given node to the end of linked list
void linked_list_push_back(LinkNode *head, LinkNode *node);
// Push a given node to the start linked list
void linked_list_push_front(LinkNode *head, LinkNode *node);
// Get the node at a given index where negative indices index from the back of the list (-1 is last element)
LinkNode *linked_list_get_node_at_index(LinkNode *head, I64 idx);

#endif  // DATA_H

// vim: filetype=c :
