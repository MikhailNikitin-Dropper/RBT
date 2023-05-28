#include "RBT_visual.h"
#include "RBT_visual.h"
#include "RBT_info.h"
#include <string.h>
#include <math.h>

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
    rectangle(pos.x - 15, pos.y, pos.x + 15, pos.y + 30);
    setfillstyle(SOLID_FILL, n->color == RB_RED ? LIGHTRED : BLACK);
    fillellipse(pos.x, pos.y+15, 15, 15);
    setcolor(LIGHTGRAY);

    if (n->color == RB_NIL)
    {
        settextstyle(0, 0, 4);
        outtextxy(pos.x - 11, pos.y + 8, "NIL");
    }
    else
    {
        char key[5];
        sprintf(key, "%d", n->key.data);
        settextstyle(0, 0, 8);
        outtextxy(pos.x - 4, pos.y + 8, key);
        }
    }

    n->pos.x = pos.x;
    n->pos.y = pos.y;

    setlinestyle(SOLID_LINE, 0, NORM_WIDTH);
    setcolor(BLACK);

    if (n->left)
    {
        end = rb_height(n->left->right);

        next_pos.x = pos.x - ((pow(2, end) * 30));
        next_pos.y = pos.y + 70;

        line(pos.x, pos.y + 30, next_pos.x, next_pos.y);

        rb_paint_req(n->left, next_pos, beg - 1, end);
    }

    if (n->right)
    {
        beg = rb_height(n->right->left);

        next_pos.x = pos.x + ((pow(2, beg) * 30));
        next_pos.y = pos.y + 70;

        line(pos.x, pos.y + 30, next_pos.x, next_pos.y);

        rb_paint_req(n->right, next_pos, beg, end - 1);
    }
}

