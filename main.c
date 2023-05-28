#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include "RBT_info.h"
#include "RBT_back.h"
#include "RBT_visual.h"

int main()
{
    int gd=DETECT, gm=DETECT;
    initgraph(&gd, &gm, "RBT");
    setbkcolor(WHITE);
    place pos;
    pos.x=200;
    pos.y=20;
    cleardevice();
    rbt *t = rbt_init();

    rb_print(t->root); printf("\n");
    rb_insert(t, from_int(1));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    readkey();
    cleardevice();

    rb_insert(t, from_int(3));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    readkey();
    cleardevice();

    rb_insert(t, from_int(2));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    readkey();
    cleardevice();

    rb_insert(t, from_int(1));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    rb_paint_select_insert(t->root->left);
    readkey();
    cleardevice();

    rb_insert(t, from_int(0));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    readkey();
    rb_min(t);
    readkey();
    cleardevice();

    rb_insert(t, from_int(4));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    readkey();
    cleardevice();

    rb_insert(t, from_int(5));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    readkey();
    cleardevice();

    rb_insert(t, from_int(6));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    readkey();
    rb_paint_min(t);
    readkey();
    cleardevice();

    rb_insert(t, from_int(7));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    readkey();
    cleardevice();

    rb_insert(t, from_int(8));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    readkey();
    cleardevice();

    rb_insert(t, from_int(9));
    rb_print(t->root); printf("\n");
    rb_paint(t, pos);
    readkey();

    printf("%zu", rb_red_height(t->root));
    printf("%zu", rb_black_height(t->root));
    rb_delete(t, from_int(4));
    rb_print(t->root); printf("\n");
    closegraph();

    rb_delete(t, from_int(1));
    rb_print(t->root); printf("\n");

    rb_delete(t, from_int(4));
    rb_print(t->root); printf("\n");
    rb_delete(t, from_int(8));
    rb_print(t->root); printf("\n");

    rb_free(t);

    return 0;
}
