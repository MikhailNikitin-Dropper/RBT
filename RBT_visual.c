#include "RBT_visual.h"
#include "RBT_back.h"
#include "RBT_info.h"
#include <string.h>
#include <math.h>
#define SIZE_X 20
#define SIZE_Y 20

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

void rb_paint_rotate_l(rbnode *n)
{
    setcolor(LIGHTBLUE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    ellipse(n->pos.x+SIZE_X, n->pos.y, 0, 180, SIZE_X*2, SIZE_Y);
    line(n->pos.x - SIZE_X, n->pos.y, n->pos.x, n->pos.y - SIZE_Y*0.5);
    line(n->pos.x - SIZE_X, n->pos.y, n->pos.x - 2*SIZE_X, n->pos.y - SIZE_Y*0.5);
}

void rb_paint_rotate_r(rbnode *n)
{
    setcolor(LIGHTBLUE);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    ellipse(n->pos.x+SIZE_X, n->pos.y, 0, 180, SIZE_X*2, SIZE_Y);
    line(n->pos.x + 3*SIZE_X, n->pos.y, n->pos.x + 2*SIZE_X, n->pos.y - SIZE_Y*0.5);
    line(n->pos.x + 3*SIZE_X, n->pos.y, n->pos.x + 4*SIZE_X, n->pos.y - SIZE_Y*0.5);
}

void rb_select_double_black(rbnode *n)
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

void rb_paint_stext_l(const rbnode *n, const char *str)
{
    setcolor(BLACK);
    settextstyle(0, 0, SIZE_Y/3);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    int width = textwidth(str);
    outtextxy(n->pos.x - width - 1, n->pos.y, str);
}


void rb_paint_stext_r(const rbnode *n, const char *str)
{
    setcolor(BLACK);
    settextstyle(0, 0, SIZE_Y/3);
    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    int width = textwidth(str);
    outtextxy(n->pos.x + 2*SIZE_X+1, n->pos.y, str);
}

