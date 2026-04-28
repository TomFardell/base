#include "data.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

// Takes same args as printf
#define data_abort(...) statement(_data_abort(__FILE__, __LINE__, __func__, __VA_ARGS__))

static void _data_abort(const char *file, int line, const char *func, ...) {
  va_list args;
  va_start(args, func);

  const char *message = va_arg(args, const char *);

  fprintf(stderr, "\n");
  fprintf(stderr, "> ---| Data error |---\n");
  fprintf(stderr, "> Error in %s->%s (line %d)\n", file, func, line);
  fprintf(stderr, "> ");
  vfprintf(stderr, message, args);
  fprintf(stderr, "\n");
  fprintf(stderr, "Terminating program\n");

  va_end(args);

  exit(EXIT_FAILURE);
}

LinkNode link_node_init(LinkNode *next, LinkNode *prev) {
  return (LinkNode){next, prev};
}

void link_node_remove_from_linked_list(LinkNode *node) {
  (node->next)->prev = node->prev;
  (node->prev)->next = node->next;

  // Poison this node's next and prev
  node->next = NULL;
  node->prev = NULL;
}

void linked_list_init(LinkNode *head) {
  *head = link_node_init(head, head);
}

void linked_list_push_back(LinkNode *head, LinkNode *node) {
  node->next = head;
  node->prev = head->prev;

  head->prev->next = node;
  head->prev = node;
}

void linked_list_push_front(LinkNode *head, LinkNode *node) {
  node->next = head->next;
  node->prev = head;

  head->next->prev = node;
  head->next = node;
}

LinkNode *linked_list_get_node_at_index(LinkNode *head, I64 idx) {
  if (0 <= idx) {
    I64 count = 0;
    for (LinkNode *curr = head->next; curr != head; curr = curr->next) {
      if (count == idx) {
        return curr;
      }

      ++count;
    }

    data_abort("Index %" I64f " out of range for linked list with %" I64f " elements", idx, count);
  } else {
    I64 count = 0;
    for (LinkNode *curr = head->prev; curr != head; curr = curr->prev) {
      --count;

      if (count == idx) {
        return curr;
      }
    }

    data_abort("Index %" I64f " out of range for linked list with %" I64f " elements", idx, -count);
  }

  // Only here to suppress compiler warning. One of the two aborts will be hit first, so this is never reached
  return NULL;
}

U64 linked_list_get_length(LinkNode *head) {
  U64 count = 0;

  for (LinkNode *curr = head->next; curr != head; curr = curr->next) {
    ++count;
  }

  return count;
}

void linked_list_remove_at_index(LinkNode *head, I64 idx) {
  LinkNode *node = linked_list_get_node_at_index(head, idx);

  link_node_remove_from_linked_list(node);
}
