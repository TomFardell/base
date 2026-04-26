#ifndef DATA_H
#define DATA_H

#include "memory.h"

typedef struct LinkNode {
  struct LinkNode *next;
  struct LinkNode *prev;
} LinkNode;

// Initialise a new link node given pointers to next and previous nodes
LinkNode link_node_init(LinkNode *next, LinkNode *prev);

// Get the data associated with a given link node given that the link node is a member of a specified type
#define link_node_get_data(node, type_name, member_name) \
  ((type_name *)((U64)(node) - offset_of(type_name, member_name)))

// Initialise a linked list with a given identifier name for the head
#define linked_list_init(name) \
  LinkNode name;               \
  _linked_list_init(&name)
// Initialise a given link node to be the head of a new linked list
void _linked_list_init(LinkNode *head);

// Push a given node to the end of linked list
void linked_list_push_back(LinkNode *head, LinkNode *node);
// Push a given node to the start linked list
void linked_list_push_front(LinkNode *head, LinkNode *node);

#endif  // DATA_H

// vim: filetype=c :
