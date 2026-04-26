#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "data.h"
#include "definitions.h"

typedef struct I32Node {
  I32 data;
  LinkNode node;
} I32Node;

#define node_init(data_name, data_value) {.data_name = data_value}

#endif  // LINKED_LIST_H

// vim: filetype=c :
