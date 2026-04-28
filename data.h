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

// Remove a given node from its linked list
void link_node_remove_from_linked_list(LinkNode *node);

// Initialise a given link node to be the head of a new linked list
void linked_list_init(LinkNode *head);

// Push a given node to the end of linked list
void linked_list_push_back(LinkNode *head, LinkNode *node);
// Push a given node to the start linked list
void linked_list_push_front(LinkNode *head, LinkNode *node);

// NOTE: For methods that take an index, can pass a negative index to start indexing from the back of the list. For
// example, the last element would have index -1

// Get the node at a given index
LinkNode *linked_list_get_node_at_index(LinkNode *head, I64 idx);
// Get the container node at a given index in a linked list
#define link_node_get_container_node_at_index(head, idx, type_name, member_name) \
  link_node_get_container_node(linked_list_get_node_at_index(head, idx), type_name, member_name)

// Remove the node at a given index from a linked list
void linked_list_remove_at_index(LinkNode *head, I64 idx);

#endif  // DATA_H

// vim: filetype=c :
