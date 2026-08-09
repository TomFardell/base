/*------*/
/* Data */
/*---------------------------------------------------------------------------------------------------------------*/
// This module contains logic for linked lists.
//
// These linked lists are implemented similarly to in the Linux kernel. Rather than link nodes themselves
// containing data, we use define_node to define node structs that hold both data and a link node. We can then use
// the link_node_get_container_node and link_node_get_data macros to retrieve the node struct and the data held in
// the node struct respectively. Link nodes are doubly linked to two other link nodes, meaning linked lists are all
// doubly linked lists.
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
//
// Some methods allow for indexing of elements of a linked list. These can take a negative index, which will index
// from the back of the list, i.e. an index of -1 corresponds to the last element.
//
// Iterating over linked lists can be done using the foreach macro(s). This expands to a for loop that iterates
// over all data-containing link nodes in the list.
/*---------------------------------------------------------------------------------------------------------------*/
#ifndef DATA_H
#define DATA_H

#include "definitions.h"

typedef struct LinkNode {
  struct LinkNode *next;
  struct LinkNode *prev;
} LinkNode;

// These member names will be used within other macros, so makes sense to define all these node types using this
#define define_node(type)     \
  typedef struct type##Node { \
    type data;                \
    LinkNode node;            \
  } type##Node

// Initialise a new link node given pointers to next and previous nodes
LinkNode link_node_init(LinkNode *next, LinkNode *prev);

// Get the container node for a given link node, assuming the link node is contained within a node struct defined
// using the define_node macro
#define link_node_get_container_node(node_address, container_type) \
  ((container_type *)((U64)(node_address) - offset_of(container_type, node)))
// Get the data associated wiht a given link node, assuming the link node is contained within a node struct defined
// using the define_node macro
#define link_node_get_data(node_address, data_type) \
  (link_node_get_container_node(node_address, data_type##Node)->data)

// Insert a link node after a given node
void link_node_insert_after(LinkNode *after, LinkNode *node);
// Insert a link node before a given node
void link_node_insert_before(LinkNode *before, LinkNode *node);
// Remove a given node from its linked list
void link_node_remove_from_linked_list(LinkNode *node);

// Initialise a given link node to be the head of a new linked list
void linked_list_init(LinkNode *head);

// Push a given node to the end of linked list
void linked_list_push_back(LinkNode *head, LinkNode *node);
// Push a given node to the start linked list
void linked_list_push_front(LinkNode *head, LinkNode *node);
// Insert a node into a linked list so that that node's index becomes the index passed
void linked_list_insert_at_index(LinkNode *head, I64 idx, LinkNode *node);

// Get the link node node at a given index in a linked list
LinkNode *linked_list_get_node_at_index(const LinkNode *head, I64 idx);
// Get the container node at a given index in a linked list, assuming the link nodes of the linked list are
// contained within node structs defined using the define_node macro
#define linked_list_get_container_node_at_index(head_address, idx, container_type) \
  link_node_get_container_node(linked_list_get_node_at_index(head_address, idx), container_type)
// Get the data at a given index in a linked list, assuming the link nodes of the linked list are contained within
// node structs defined using the define_node macro
#define linked_list_get_data_at_index(head_address, idx, data_type) \
  linked_list_get_container_node_at_index(head_address, idx, data_type##Node)->data
// Get the number of elements in a linked list
U64 linked_list_get_length(const LinkNode *head);

// Macro to iterate over a linked list. This only gets the link nodes, so the first line of the body should
// probably call link_node_get_container_node or link_node_get_data
#define foreach(node_name, head_address) \
  for (LinkNode *node_name = (head_address)->next; node_name != (head_address); node_name = node_name->next)
// Macro to iterate over a linked list in the reverse direction
#define foreach_reverse(node_name, head_address) \
  for (LinkNode *node_name = (head_address)->prev; node_name != (head_address); node_name = node_name->prev)

// Remove the node at a given index from a linked list
void linked_list_remove_at_index(LinkNode *head, I64 idx);

#endif  // DATA_H

// vim: filetype=c :
