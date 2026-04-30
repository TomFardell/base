/*------*/
/* Data */
/*---------------------------------------------------------------------------------------------------------------*/
// This module contains logic for linked lists.
//
// These linked lists are implemented similarly to in the Linux kernel. Rather than link nodes themselves
// containing data, link nodes can be inserted into any struct at any position. The linked list logic applies only
// to the link nodes, so these methods work for any struct containing a link node (or even mmultiple). Link nodes
// are doubly linked to two other link nodes, meaning linked lists are all doubly linked lists.
//
// Linked lists work as follows:
// - Linked lists have a head node that should not have data attached. An empty linked list is just a head node
//   whose next and prev are itself
// - Other link nodes can be added into the list
// - The list can be iterated by starting from head->next and going though each link node's ->next until the head
//   node is reached again
//
// Please consult this excellent diagram (only the next pointers are displayed in the interest of clarity). This
// displays a 2-element linked list holding the values 10 and 20.
//
//         +-----------------------------------------------------------------------+
//         |                                                                       |
//         |                +--------------------+       +--------------------+    |
//         |                | I32Node node1      |       | I32Node node2      |    |
//         |                +--------------------+       +--------------------+    |
//         V                | I32 data = 10      |       | I32 data = 20      |    |
// +----------------+       | +----------------+ |       | +----------------+ |    |
// | LinkNode head  |       | | LinkNode node  | |       | | LinkNode node  | |    |
// +----------------+       | +----------------+ |       | +----------------+ |    |
// | LinkNode *next---------->| LinkNode *next------------>| LinkNode *next--------+
// | LinkNode *prev |       | | LinkNode *prev | |       | | LinkNode *prev | |
// +----------------+       | +----------------+ |       | +----------------+ |
//                          +--------------------+       +--------------------+
//
// In particular, the head does not contain any data.
/*---------------------------------------------------------------------------------------------------------------*/
#ifndef DATA_H
#define DATA_H

#include "definitions.h"
#include "memory.h"

typedef struct LinkNode {
  struct LinkNode *next;
  struct LinkNode *prev;
} LinkNode;

// Initialise a new link node given pointers to next and previous nodes
LinkNode link_node_init(LinkNode *next, LinkNode *prev);

// Get the container node for a given link node, given the link node is a specified member of a specified type
#define link_node_get_container_node(node_address, container_type_name, container_link_node_member_name) \
  ((container_type_name *)((U64)(node_address) - offset_of(container_type_name, container_link_node_member_name)))

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
#define linked_list_get_container_node_at_index(head_address, idx, container_type_name,               \
                                                container_link_node_member_name)                      \
  link_node_get_container_node(linked_list_get_node_at_index(head_address, idx), container_type_name, \
                               container_link_node_member_name)
// Get the number of elements in a linked list
U64 linked_list_get_length(LinkNode *head);

// Remove the node at a given index from a linked list
void linked_list_remove_at_index(LinkNode *head, I64 idx);

#endif  // DATA_H

// vim: filetype=c :
