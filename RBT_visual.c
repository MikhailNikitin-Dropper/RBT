#include "RBT_visual.h"
#include "RBT_back.h"
#include "RBT_info.h"
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE_X 20
#define SIZE_Y 20
#define NULL ((void *)0)
 void rb_paint(rbt *t, place tree_pos)
{
    size_t beg = 0, end = 0;

    cleardevice();

    if (t->root)
        rb_paint_req(t->root, tree_pos, beg, end);
}

void rb_paint_req(rbnode *n, place pos, size_t beg, size_t end)
{
    place next_pos;

    setcolor(LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(pos.x, pos.y, pos.x + SIZE_X*2, pos.y + SIZE_Y*2);
    setfillstyle(SOLID_FILL, n->color == RB_RED ? LIGHTRED : BLACK);
    fillellipse(pos.x+SIZE_X, pos.y+SIZE_Y, SIZE_X, SIZE_Y);
    setcolor(LIGHTGRAY);

    if (n->color == RB_NIL)
    {
        settextstyle(0, 0, SIZE_Y/2);
        outtextxy(pos.x + SIZE_X/2, pos.y + SIZE_Y/2, "NIL");
    }
    else
    {
        char key[5];
        sprintf(key, "%d", n->key.data);
        settextstyle(0, 0, SIZE_Y/2);
        outtextxy(pos.x + SIZE_X/2, pos.y + SIZE_Y/2, key);
    }

    n->pos.x = pos.x;
    n->pos.y = pos.y;

    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setcolor(BLACK);

    if (n->left)
    {
        end = rb_height(n->left->right);

        next_pos.x = pos.x - ((pow(2, end) * SIZE_X));
        next_pos.y = pos.y + SIZE_Y*6;

        line(pos.x + SIZE_X, pos.y + SIZE_Y, next_pos.x+SIZE_X, next_pos.y+SIZE_Y);

        rb_paint_req(n->left, next_pos, beg - 1, end);
    }

    if (n->right)
    {
        beg = rb_height(n->right->left);

        next_pos.x = pos.x + ((pow(2, beg) * SIZE_X*2));
        next_pos.y = pos.y + SIZE_Y*6;

        line(pos.x+SIZE_X, pos.y + SIZE_Y, next_pos.x+SIZE_X, next_pos.y+SIZE_Y);

        rb_paint_req(n->right, next_pos, beg, end - 1);
    }
}

void rb_paint_select(const rbnode *n, int color)
{
    setcolor(color);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(n->pos.x, n->pos.y, n->pos.x + SIZE_X*2, n->pos.y + SIZE_Y*2);
}

void rb_paint_select_insert(const rbnode *n)
{
    rb_paint_select(n, CYAN);
    if (n->parent)
    {
        n = (const rbnode *)(n->parent);
        rb_paint_select(n, LIGHTBLUE);
    }
}

void rb_paint_select_rotate_l(const rbnode *n)
{
    setcolor(LIGHTBLUE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    ellipse(n->pos.x+SIZE_X, n->pos.y, 0, 180, SIZE_X*2, SIZE_Y);
    line(n->pos.x - SIZE_X, n->pos.y, n->pos.x, n->pos.y - SIZE_Y*0.5);
    line(n->pos.x - SIZE_X, n->pos.y, n->pos.x - 2*SIZE_X, n->pos.y - SIZE_Y*0.5);
}

void rb_paint_select_rotate_r(const rbnode *n)
{
    setcolor(LIGHTBLUE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    ellipse(n->pos.x+SIZE_X, n->pos.y, 0, 180, SIZE_X*2, SIZE_Y);
    line(n->pos.x + 3*SIZE_X, n->pos.y, n->pos.x + 2*SIZE_X, n->pos.y - SIZE_Y*0.5);
    line(n->pos.x + 3*SIZE_X, n->pos.y, n->pos.x + 4*SIZE_X, n->pos.y - SIZE_Y*0.5);

}

void rb_paint_double_black(const rbnode *n)
{
    setcolor(WHITE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(n->pos.x , n->pos.y, n->pos.x + SIZE_X*2, n->pos.y + SIZE_Y*2);

    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    rectangle(n->pos.x -1, n->pos.y - 1, n->pos.x + 1 + 2*SIZE_X, n->pos.y + 1 + 2*SIZE_Y);
    rectangle(n->pos.x - 2, n->pos.y - 2, n->pos.x + 2 + 2*SIZE_X, n->pos.y + 2 + 2*SIZE_Y);

}



rbnode *rb_paint_min(rbt *t)
{
    rbnode *x = t->root;
    if (!x)
        return NULL;

    rb_paint_select(x, CYAN);
    while (x->left)
    {
        x = x->left;
        rb_paint_select_insert(x);
    }

    return x;
}

rbnode *rb_paint_max(rbt *t)
{
    rbnode *x = t->root;
    if (!x)
        return NULL;

    rb_paint_select(x, CYAN);
    while (x->right)
    {
        x = x->right;
        rb_paint_select_insert(x);
    }

    return x;
}

void rb_paint_select_repaint(const rbnode *n, int new_color)
{
    place pos = n->pos;
    setcolor(GREEN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(pos.x, pos.y, pos.x + SIZE_X*2, pos.y + SIZE_Y*2);
    setfillstyle(SOLID_FILL, new_color);
    fillellipse(pos.x+SIZE_X, pos.y+SIZE_Y, SIZE_X, SIZE_Y);

    setcolor(LIGHTGRAY);
    char key[5];
    sprintf(key, "%d", n->key.data);
    settextstyle(0, 0, SIZE_Y/2);
    outtextxy(pos.x + SIZE_X/2, pos.y + SIZE_Y/2, key);

}

void rb_paint_select_copy(const rbnode *n_old, const rbnode *n_new)
{
    char key_old[5], key_new[5];
    place old_pos = n_old->pos, new_pos = n_new->pos;

    sprintf(key_old, "%d", n_old->key.data);
    sprintf(key_new, "%d", n_new->key.data);

    setcolor(YELLOW);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    line(old_pos.x+SIZE_X, old_pos.y+SIZE_Y, new_pos.x+SIZE_X, new_pos.y+SIZE_Y);

    setcolor(GREEN);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(new_pos.x, new_pos.y, new_pos.x + SIZE_X*2, new_pos.y + SIZE_Y*2);
    setfillstyle(SOLID_FILL, n_old->color == RB_BLACK ? BLACK : LIGHTRED);
    fillellipse(new_pos.x+SIZE_X, new_pos.y+SIZE_Y, SIZE_X, SIZE_Y);

    setcolor(LIGHTGRAY);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(old_pos.x, old_pos.y, old_pos.x + SIZE_X*2, old_pos.y + SIZE_Y*2);
    setfillstyle(SOLID_FILL, n_new->color == RB_BLACK ? BLACK : LIGHTRED);
    fillellipse(old_pos.x+SIZE_X, old_pos.y+SIZE_Y, SIZE_X, SIZE_Y);

    setcolor(LIGHTGRAY);
    settextstyle(0, 0, SIZE_Y/2);
    outtextxy(new_pos.x + SIZE_X/2, new_pos.y + SIZE_Y/2, key_old);
    outtextxy(old_pos.x + SIZE_X/2, old_pos.y + SIZE_Y/2, key_new);

}

void rb_paint_stext_l(const rbnode *n, const char *str1, const char *str2)
{
    setcolor(BLACK);
    settextstyle(0, 0, SIZE_Y/4);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    int width1 = textwidth(str1);
    int width2 = textwidth(str2);
    if (str2)
         outtextxy(n->pos.x - width2 - 1, n->pos.y+SIZE_Y+1, str2);
    outtextxy(n->pos.x - width1 - 1, n->pos.y, str1);

}


void rb_paint_stext_r(const rbnode *n, const char *str1, const char *str2)
{
    setcolor(BLACK);
    settextstyle(0, 0, SIZE_Y/4);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    if (str2)
         outtextxy(n->pos.x + 2*SIZE_X+1, n->pos.y+SIZE_Y+1, str2);
    outtextxy(n->pos.x + 2*SIZE_X+1, n->pos.y, str1);

}

rbnode *rb_paint_bst_insert(rbt *t, key_t key)
{
    rbnode *y = NULL, *x = t->root;
    rbnode *z = malloc(sizeof(rbnode));

    if (!z)
        return NULL;

    z->key = key;
    z->color = RB_RED;
    z->left = z->right = NULL;

    while (x)
    {
        rb_paint_select_insert(x);
        y = x;
        if (z->key.data == x->key.data)
        {
            rb_paint_stext_r(x, "Element is already in tree", NULL);
            free(z);
            return NULL;
        }
        x = z->key.data < x->key.data ? x->left : x->right;
    }

    z->parent = y;

    if (!y)
        t->root = z;
    else
    {
        if (z->key.data < y->key.data)
            y->left = z;
        else
            y->right = z;
    }

    return z;
}

int rb_paint_insert(rbt *t, key_t key, place root_pos)
{
    rbnode *x = rb_paint_bst_insert(t, key);
    if (!x)
        return 1;

    rb_paint(t, root_pos);

    rb_paint_select(x, GREEN);
    if (!(x->parent))
    {
        rb_paint_stext_l(x, "Root red - change to black", " ");
        rb_paint_select_repaint(x, BLACK);
        delay(1000);
    }
    else if (x->parent->color == RB_BLACK)
        rb_paint_stext_l(x->parent, "Parent is black - all is good", " ");
    while (x != t->root && x->parent->color == RB_RED)
    {
        if (x->parent == x->parent->parent->right)
        {
            rb_paint_stext_r(x->parent, "Parent is red -> analyze uncle", " ");
            delay(1000);
        }
        else
        {
            rb_paint_stext_l(x->parent, "Parent is red -> analyze uncle", " ");
            delay(1000);
        }

        rbnode *y = x->parent == x->parent->parent->left ? x->parent->parent->right : x->parent->parent->left; //y - uncle

        if (y && y->color == RB_RED)
        {
            if (y == y->parent->right)
            {
                rb_paint_stext_r(y, "Red uncle - change parent and uncle to black",
                           "grandfather to red; grandfather is curent");
                delay(1000);
            }
            else
            {
                rb_paint_stext_l(y, "Red uncle - change parent and uncle to black",
                           "grandfather to red; grandfather is curent");
                delay(1000);
            }

            x->parent->color = RB_BLACK;

            rb_paint_select_repaint(x, BLACK);
            y->color = RB_BLACK;
            rb_paint_select_repaint(y, BLACK);
            x->parent->parent->color = RB_RED;
            rb_paint_select_repaint(x->parent->parent, LIGHTRED);

            delay(1000);

            x = x->parent->parent;

            rb_paint(t, root_pos);

            rb_paint_select(x, GREEN);

            if (!x->parent)
            {
                rb_paint_stext_l(x,
                           "Black root -> repaint to black",
                           " ");
                rb_paint_select_repaint(x, BLACK);
                delay(1000);
            }

            else if (x->parent->color == RB_BLACK)
            {
                rb_paint_stext_l(x->parent, "Black parent -> done", " ");
                delay(1000);
            }
        }

        else
        {
            if (y)
            {
                if (y == y->parent->right)
                {
                    rb_paint_stext_r(y,
                               "Black uncle -> check",
                               "way from grandfather");
                    delay(1000);
                }
                else
                    {
                        rb_paint_stext_l(y,
                               "Black uncle -> check",
                               "way from grandfather");
                        delay(1000);
                    }
            }
            else
            {
                if (x->parent == x->parent->parent->right)
                    rb_paint_stext_l(x->parent,
                               "Uncle - nil=black -> check",
                               "way from grandfather");
                else
                    rb_paint_stext_r(x->parent,
                               "Uncle - nil=black -> check",
                               "way from grandfather");
            }
            delay(1000);

            rb_paint(t, root_pos);


            rb_paint_select(x->parent->parent, GREEN);
            rb_paint_select(x->parent, GREEN);
            rb_paint_select(x, CYAN);

            if (x->parent == x->parent->parent->left && x == x->parent->right)
            {
                rb_paint_stext_l(x,
                           "x - right child, its parent - left",
                           "-> left rotation around parent of x");

                x = x->parent;


                rb_paint_select_rotate_l(x);
                rb_rotate_left(t, x);

                rb_paint(t, root_pos);

                rb_paint_select(x->parent->parent, GREEN);
                rb_paint_select(x->parent, GREEN);
                rb_paint_select(x, CYAN);
            }

            else if (x->parent == x->parent->parent->right && x == x->parent->left)
            {

                rb_paint_stext_r(x,
                           "x - left child, its parent - right",
                           "-> right rotation around parent of x");

                x = x->parent;

                rb_paint_select_rotate_r(x);
                rb_rotate_right(t, x);

                rb_paint(t, root_pos);

                rb_paint_select(x->parent->parent, GREEN);
                rb_paint_select(x->parent, GREEN);
                rb_paint_select(x, CYAN);
            }

            if (x == x->parent->right)
                rb_paint_stext_l(x,
                           "one way exists -> repaint",
                           "parent into black, grandfather into red");
            else
                rb_paint_stext_r(x,
                           "one way exists -> repaint",
                           "parent into black, grandfather into red");

            x->parent->color = RB_BLACK;

            rb_paint_select_repaint(x->parent, BLACK);
            x->parent->parent->color = RB_RED;
            rb_paint_select_repaint(x->parent->parent, LIGHTRED);

            rb_paint(t, root_pos);

            rb_paint_select(x, CYAN);

            if (x == x->parent->left)
            {
                rb_paint_select(x->parent->parent, GREEN);
                rb_paint_select(x->parent, GREEN);

                rb_paint_stext_l(x->parent,
                           "way direction - left -> right",
                           "rotation around grandfather");


                rb_paint_select_rotate_r(x->parent->parent);
                rb_rotate_right(t, x->parent->parent);
                delay(1000);
            }
            else
            {
                rb_paint_select(x->parent->parent, GREEN);
                rb_paint_select(x->parent, GREEN);

                rb_paint_stext_r(x->parent,
                           "way direction - right -> left",
                           "rotation around grandfather");
                rb_paint_select_rotate_l(x->parent->parent);
                rb_rotate_left(t, x->parent->parent);
                delay(1000);
            }
        }
    }
    t->root->color = RB_BLACK;
    rb_paint(t, root_pos);
    delay(1000);
    return 0;
}



int rb_paint_delete(rbt *t, key_t key, place root_pos)
{
    rbnode *x, *y, *z = t->root, *n = NULL;

    while (z && z->key.data != key.data)
    {
        rb_paint_select_insert(z);

        if (key.data < z->key.data)
        {
            if (!(z->left))
            {
                rb_paint_stext_l(z,"Element not found", " ");
                return -1;
            }
            z = z->left;
        }
        else
        {
            if (!(z->right))
            {
                rb_paint_stext_r(z,"Element not found", NULL);
                return -1;
            }
            z = z->right;
        }
    }

    rb_paint_select_insert(z);

    if (!z->left || !z->right)
    {

        if (z->left || z->right)
            rb_paint_stext_l(z,
                       "have only one subtree ->",
                       "this is deleted node");
        else
            rb_paint_stext_l(z,
                       "haven't got any subtree ->",
                       "this is deleted node");
        y = z;
    }
    else
    {
        rb_paint_stext_l(z,
                   "both subtree exists -> find min",
                   "element in right subtree");
        rbt r;
        r.root = z->right;

        y = rb_paint_min(&r);
        rb_paint_stext_l(y,
                   "this is deleted node ->",
                   "move data to first node");
        rb_paint_select_copy(y, z);
        z->key.data = y->key.data;
    }

    if (y == t->root)
    {
        rb_paint_stext_r(y,
                   "deleted root -> tree",
                   "is empty");
        free(y);
        t->root = NULL;
        return 0;
    }

    x = y->left ? y->left : y->right;

    if (!x)
    {
        n = malloc(sizeof(rbnode));
        n->color = RB_NIL;
        n->left = NULL;
        n->right = NULL;
        x = n;
    }

    x->parent = y->parent;

    if (!y->parent)
        t->root = x;
    else
    {

        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    if (y->color == RB_BLACK)
    {
        rb_paint_stext_r(y,
                   "«change remove node to its",
                   "child; child is current");

        if (x->color == RB_NIL)
        {
            rb_paint_stext_l(y, "child - nil", " ");
            delay(1000);
        }
        rb_paint(t, root_pos);

        while (x != t->root && x->color != RB_RED)
        {
            int l = 0;
            rbnode *w = x == x->parent->left ? x->parent->right
                                              : x->parent->left;
            if (x == x->parent->left)
                rb_paint_stext_l(x,
                           "x black -> its double black;",
                           "define its brother color");
            else
                rb_paint_stext_r(x,
                           "x black -> its double black;",
                           "define its brother color");

            rb_paint_double_black(x);
            delay(1000);

            if (w->color == RB_RED)
            {
                if (w == w->parent->left)
                    rb_paint_stext_l(w,
                               "brother red -> repaint it",
                               "to black, parent to red ");
                else
                    rb_paint_stext_r(w,
                               "brother red -> repaint it",
                               "to black, parent to red ");

                w->color = RB_BLACK;

                rb_paint_select_repaint(w, BLACK);

                x->parent->color = RB_RED;
                rb_paint_select_repaint(x->parent, LIGHTRED);

                if (x == x->parent->left)
                {
                    rb_paint_stext_l(x,
                              "x - left child -> left",
                              "rotation around parent");
                    rb_paint_select_rotate_l(x->parent);
                    rb_rotate_left(t, x->parent);
                    w = x->parent->right;
                }
                else
                {

                    rb_paint_stext_r(x,
                              "x - left child -> right",
                              "rotation around parent");
                    rb_paint_select_rotate_r(x->parent);
                    rb_rotate_right(t, x->parent);
                    w = x->parent->left;
                }

                rb_paint(t, root_pos);

                rb_paint_double_black(x);

                ++l;
            }

            if (l)
            {
                if (w == w->parent->left)
                    rb_paint_stext_l(w,
                               "now brother black ->",
                               "define nephew color ");
                else
                    rb_paint_stext_r(w,
                               "now brother black ->",
                               "define nephew color ");
            }
            else
            {
                if (w == w->parent->right)
                    rb_paint_stext_l(w,
                               "now brother black ->",
                               "define nephew color ");
                else
                    rb_paint_stext_r(w,
                               "now brother black ->",
                               "define nephew color ");
            }

            if ((!w->left || w->left->color == RB_BLACK) &&
                (!w->right || w->right->color == RB_BLACK))
            {
                if (w == w->parent->right)
                {
                    if (w->right)
                    {
                        if (w->left)
                        {
                            rb_paint_select(w->left, GREEN);
                            rb_paint_stext_r(w->right,
                                       "both nephew black ->",
                                       "repaint brother to red");
                            delay(1000);
                            rb_paint_select_repaint(w, LIGHTRED);
                            rb_paint_stext_r(w,
                                      "double black transfer to parent", " ");
                            delay(1000);
                        }
                        else
                        {
                            rb_paint_stext_r(w->right,
                                       "both nephew black -> (left",
                                       "- nil = black) ->");
                            delay(1000);
                            rb_paint_stext_r(w->right,
                                      "repaint brother to red,",
                                      "double black transfer to parent");
                            rb_paint_select_repaint(w, LIGHTRED);
                            delay(1000);
                        }
                    }
                    else
                    {
                        if (w->left)
                        {
                            rb_paint_stext_l(w->left,
                                       "both nephew black -> (right",
                                       "- nil = black) ->");
                            delay(1000);
                            rb_paint_stext_l(w->left,
                                      "repaint brother to red,",
                                      "double black transfer to parent");

                            rb_paint_select_repaint(w, LIGHTRED);
                            delay(1000);
                        }
                        else
                        {
                            rb_paint_stext_r(w,
                                      "both nephew nil = black",
                                      "-> repaint brother to red");
                            delay(1000);
                            rb_paint_select_repaint(w, LIGHTRED);
                            rb_paint_stext_r(w,
                                      "double black transfer to parent", " ");
                            delay(1000);
                        }
                    }
                }
                else
                {
                    if (w->right)
                    {
                        if (w->left)
                        {
                            rb_paint_select(w->right, GREEN);
                            rb_paint_stext_l(w->left,
                                       "both nephew black",
                                      "-> repaint brother to red");
                            delay(1000);
                            rb_paint_select_repaint(w, LIGHTRED);
                            rb_paint_stext_l(w->left,
                                      "double black transfer to parent", " ");
                            delay(1000);
                        }
                        else
                        {
                            rb_paint_stext_r(w->right,
                                       "both nephew black -> (left",
                                       "- nil = black) ->");
                            delay(1000);
                            rb_paint_stext_r(w->right,
                                      "repaint brother to red,",
                                      "double black transfer to parent");
                            rb_paint_select_repaint(w, LIGHTRED);
                            delay(1000);
                        }
                    }
                    else
                    {
                        if (w->left)
                        {
                            rb_paint_stext_l(w->left,
                                       "both nephew black -> (right",
                                       "- nil = black) ->");
                            delay(1000);
                            rb_paint_stext_l(w->left,
                                      "repaint brother to red,",
                                      "double black transfer to parent");
                            rb_paint_select_repaint(w, LIGHTRED);
                            delay(1000);
                        }
                        else
                        {
                            rb_paint_stext_l(w,
                                      "both nephew nil = black",
                                      "-> repaint brother to red");
                            delay(1000);
                            rb_paint_select_repaint(w, LIGHTRED);
                            rb_paint_stext_l(w,
                                      "double black transfer to parent", " ");
                            delay(1000);
                        }
                    }
                }

                w->color = RB_RED;
                if (x->parent->color == RB_RED)
                {
                    rb_paint(t, root_pos);
                    rb_paint_select(x, GREEN);

                    rb_paint_double_black(x->parent);

                    rb_paint_stext_r(x->parent,
                              "parent red ->",
                              "repaint to black; done");
                    x->parent->color = RB_BLACK;
                    rb_paint_select_repaint(x->parent, BLACK);
                    x = t->root;
                }
                else
                {
                    if (x->color == RB_NIL)
                    {
                        if (x == x->parent->left)
                            x->parent->left = NULL;
                        else
                            x->parent->right = NULL;
                    }

                    x = x->parent;
                    rb_paint(t, root_pos);
                    rb_paint_select(x, GREEN);
                    if (!x->parent)
                    {
                        rb_paint_double_black(x);
                        rb_paint_stext_r(x,
                                  "root double black ->",
                                  "repaint to black; done");
                    }
                }
            }


            else
            {
                int k = 0;

                if ((x == x->parent->left && (!w->right || w->right->color == RB_BLACK)) ||
                    (x == x->parent->right && (!w->left || w->left->color == RB_BLACK)))
                {
                    w->color = RB_RED;

                    if (x == x->parent->left)
                    {
                        if (w->right)
                        {
                            rb_paint_stext_r(w->right,
                                       "closest nephew red ,",
                                       "opposite - black ->");
                            delay(1000);
                            rb_paint_stext_r(w->right,
                                      "repaint brother in red,",
                                      "closest nephew to black");
                        }
                        else
                        {
                            rb_paint_stext_r(w,
                                      "closest nephew red ,",
                                      "opposite -  nil=black ->");
                            delay(1000);
                            rb_paint_stext_r(w,
                                      "repaint brother in red,",
                                      "closest nephew to black");
                        }

                        rb_paint_select_repaint(w, LIGHTRED);

                        w->left->color = RB_BLACK;

                        rb_paint_select_repaint(w->left, BLACK);

                        rb_paint_stext_l(x,
                                  "x - left child -> right",
                                  "rotation around brother");

                        rb_paint_select_rotate_r(w);
                        rb_rotate_right(t, w);

                        w = x->parent->right;
                    }

                    else
                    {
                        if (w->left)
                        {
                            rb_paint_stext_l(w->left,
                                       "closest nephew red ,",
                                       "opposite - black ->");
                            delay(1000);
                            rb_paint_stext_l(w->left,
                                      "repaint brother in red,",
                                      "closest nephew to black");
                        }
                        else
                        {
                            rb_paint_stext_l(w,
                                      "closest nephew red ,",
                                      "opposite -  nil=black ->");
                            delay(1000);
                            rb_paint_stext_l(w,
                                      "repaint brother in red,",
                                      "closest nephew to black");
                        }

                        rb_paint_select_repaint(w, LIGHTRED);
                        w->right->color = RB_BLACK;
                        rb_paint_select_repaint(w->right, BLACK);

                        rb_paint_stext_r(x,
                                  "x - right child -> left",
                                  "rotation around brother");

                        rb_paint_select_rotate_l(w);
                        rb_rotate_left(t, w);

                        w = x->parent->left;
                    }

                    rb_paint(t, root_pos);
                    rb_paint_double_black(x);
                    ++k;
                }


                if (x == x->parent->left)
                {
                    rb_paint_stext_r(w->right,
                               "opposite nephew red",
                               "don't care about clousest ->");
                    delay(1000);
                    rb_paint_stext_r(w->right,
                              "repaint brother into parent color,",
                              "parent and nephew - to black");

                    rb_paint_select_repaint(w, x->parent->color == RB_RED ? LIGHTRED : BLACK);

                    w->color = x->parent->color;
                    x->parent->color = RB_BLACK;
                    rb_paint_select_repaint(x->parent, BLACK);
                    w->right->color = RB_BLACK;
                    rb_paint_select_repaint(w->right, BLACK);

                    rb_paint_stext_l(x,
                              "x - left child -> left rotation",
                              "around parent; done");

                    rb_paint_select_rotate_l(x->parent);
                    rb_rotate_left(t, x->parent);
                }
                else
                {
                    rb_paint_stext_l(w->left,
                               "opposite nephew red",
                               "don't care about clousest ->");
                    delay(1000);
                    rb_paint_stext_l(w->left,
                              "repaint brother into parent color,",
                              "parent and nephew - to black");


                    rb_paint_select_repaint(w, x->parent->color == RB_RED ? LIGHTRED : BLACK);
                    w->color = x->parent->color;

                    x->parent->color = RB_BLACK;
                    rb_paint_select_repaint(x->parent, BLACK);

                    w->left->color = RB_BLACK;
                    rb_paint_select_repaint(w->left, BLACK);
                    rb_paint_stext_r(x,
                                  "x - right child -> left",
                                  "rotation around brother");

                    rb_paint_select_rotate_r(x->parent);
                    rb_rotate_right(t, x->parent);
                }

                x = t->root;
            }
        }


        if (x->color == RB_RED)
        {
            rb_paint(t, root_pos);
            rb_paint_select(x, GREEN);
            delay(1000);
            if (x == x->parent->left)
                rb_paint_stext_l(x,
                           "x - red -> repaint",
                           "to black; done");
            else
                rb_paint_stext_r(x,
                           "x - red -> repaint",
                           "to black; done");
            rb_paint_select_repaint(x, BLACK);
        }

        x->color = RB_BLACK;
    }
    else
    {
        rb_paint_stext_r(y,
                   "change removing node to its",
                   "child; node is red -> done");
        if (!y->left && !y->right)
        {
            rb_paint_stext_r(y, "child - nil", " ");
            delay(1000);
        }
    }

    free(y);

    if (n)
    {
        if (n == t->root)
            t->root = NULL;
        else
        {
            if (n == n->parent->left)
                n->parent->left = NULL;
            if (n == n->parent->right)
                n->parent->right = NULL;
        }
        free(n);
    }

    rb_paint(t, root_pos);
    return 0;
}
