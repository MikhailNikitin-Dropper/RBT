#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <malloc.h>
#include "RBT_info.h"
#include "RBT_back.h"
#include "RBT_visual.h"

int main()
{
    int gd=DETECT, gm=DETECT;
    initgraph(&gd, &gm, "RBT");
    setbkcolor(WHITE);
    place *pos = malloc(sizeof(place));
    pos->x=200;
    pos->y=20;
    cleardevice();
    rbt *t = rbt_init();
    rb_paint_insert(t, from_int(1), *pos);
    rb_paint_insert(t, from_int(2), *pos);
    rb_paint_insert(t, from_int(3), *pos);
    /*rb_print(t->root); printf("\n");
    rb_insert(t, from_int(1));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);
    rb_paint_stext_l(t->root, "Smth", "And another");
    cleardevice();

    rb_insert(t, from_int(3));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);
    rb_paint_select_copy(t->root, t->root->right);
    cleardevice();

    rb_insert(t, from_int(2));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);
    cleardevice();

    rb_insert(t, from_int(1));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);
    rb_paint_select_insert(t->root->left);
    cleardevice();

    rb_insert(t, from_int(0));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);
    rb_min(t);
    cleardevice();

    rb_insert(t, from_int(4));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);
    cleardevice();

    rb_insert(t, from_int(5));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);
    cleardevice();

    rb_insert(t, from_int(6));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);
    rb_paint_min(t);
    cleardevice();

    rb_insert(t, from_int(7));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);
    cleardevice();

    rb_insert(t, from_int(8));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);
    cleardevice();

    rb_insert(t, from_int(9));
    rb_print(t->root); printf("\n");
    rb_paint(t, *pos);


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

    rb_free(t);*/

    return 0;
}
