#ifndef RBT_INFO_H_INCLUDED
#define RBT_INFO_H_INCLUDED
#include <stdio.h>
#include "RBT_back.h"

// Count amount of elements
size_t rb_count(rbnode *root);

//  Height of tree
size_t rb_height(rbnode *root);

// Black height of tree
size_t rb_black_height(rbnode *root);

// Red height of tree
size_t rb_red_height(rbnode *root);

// Count inner nodes of tree
size_t rb_inner_count(rbnode *root);

#endif // RBT_INFO_H_INCLUDED
