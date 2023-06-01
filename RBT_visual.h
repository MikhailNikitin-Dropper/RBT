#ifndef RBT_VISUAL_H_INCLUDED
#define RBT_VISUAL_H_INCLUDED
#include <graphics.h>
#include "RBT_back.h"
#include <stdio.h>
//Just tree drawing
void rb_paint(rbt *t, place tree_pos);
//Recursive painting tree and add cords to each node
void rb_paint_req(rbnode *n, place pos, size_t beg, size_t end);
//Select node
void rb_paint_select(const rbnode *n, int color);
//Select node an its parent
void rb_paint_select_insert(const rbnode *n);
//Arrow to the left
void rb_paint_select_rotate_l(const rbnode *n);
//Arrow to the right
void rb_paint_select_rotate_r(const rbnode *n);
//Double black
void rb_paint_double_black(const rbnode *n);
//Highlight path to min
rbnode *rb_paint_min(rbt *t);
//Highlight path to max
rbnode *rb_paint_max(rbt *t);
//Change node color on paint and select it
void rb_paint_select_repaint(const rbnode *n, int new_color);
//Copy key from one node to another on paint and draw arrow from old to new, highlight new node
void rb_paint_select_copy(const rbnode *n_old, const rbnode *n_new);
//Print text left to node
void rb_paint_stext_l(const rbnode *n, const char *str1, const char *str2);
//Print text right to node
void rb_paint_stext_r(const rbnode *n, const char *str, const char *str2);

//Really used functions (finally!)
//Draw and add new node to RBT without fix
rbnode *rb_paint_bst_insert(rbt *t, key_t key);
//Draw and add new node to RBT correctly
int rb_paint_insert(rbt *t, key_t key, place root_pos);
//Delete node by key
/*int rb_paint_delete(rbt *t, key_t key, place root_pos);*/
#endif // RBT_VISUAL_H_INCLUDED
