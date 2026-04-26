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

void _linked_list_init(LinkNode *head) {
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
