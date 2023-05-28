#include "RBT_back.h"
#include <malloc.h>
#include <stdio.h>

key_t from_int(int num)
{
    key_t result;
    result.data= num;
    return result;
}
rbt *rbt_init()
{
    rbt *r = malloc(sizeof(rbt));
    if (!r)
        return NULL;
    r->root = NULL;
    return r;
}

int rbnode_clear(rbnode *node)
{
    if (!node)
        return 1;
    rbnode_clear(node->left);
    rbnode_clear(node->right);
    free(node);
    return 0;
}

int rb_free(rbt *tree)
{
    if (!tree)
        return 1;
    if  (( rbnode_clear(tree->root) ))
    {
        free(tree);
        return 0;
    }
    else
        return 1;
}

int key_bigger(key_t key1, key_t key2)
{
    return (key1.data>key2.data);
}

int key_same(key_t key1, key_t key2)
{
    return (key1.data==key2.data);
}

rbnode *rb_search(rbt *tree, key_t key)
{
    rbnode *result = tree->root;
    while (result)
    {
        if (key_bigger(result->key, key))
            result = result->left;
        else if (key_bigger(key, result->key))
            result = result->right;
        else
            return result;
    }
    return NULL;
}

rbnode *rb_min(rbt *tree)
{
    rbnode *result = tree->root;
    if (!result)
        return NULL;
    while (result->left)
        result = result->left;
    return result;
}

rbnode *rb_max(rbt *tree)
{
    rbnode *result = tree->root;
    if (!result)
        return NULL;
    while (result->left)
        result = result->left;
    return result;
}

int rb_rotate_left (rbt *t, rbnode *x)
{
    rbnode *y = x->right;         /* ������� ����� ������ ���������                         */

    x->right = y->left;            /* ����� ������� y ���������� ������ �������� x           */
    if (y->left)
        y->left->parent = x;       /* ���� ��� ���������� ����, ��������������� ��� �������� */

    if (!x->parent)                /* ���� ������� ������ �����                              */
        t->root = y;               /* ���������� ����� ������                                */
    else                           /* ���� ������� �� ������ �����                           */
    {
        if (x == x->parent->left)  /* ���� x - ����� �������                                 */
            x->parent->left = y;   /* y ���������� ����� ���������� �������� ����� ��������  */
        else                       /* ���� x - ������ �������                                */
            x->parent->right = y;  /* y ���������� ������ ���������� �������� ����� �������� */

    }
    y->parent = x->parent;         /* ��������� �������� y                                   */

    y->left = x;                   /* x ���������� ����� �������� y,                         */
    x->parent = y;                 /* � y - ��������� x                                      */
    return 0;
}



int rb_rotate_right (rbt *t, rbnode *x)
{
    rbnode *y = x->left;          /* ������� ����� ������ ���������                         */

    x->left = y->right;            /* ������ ������� y ���������� ����� �������� x           */
    if (y->right)
        y->right->parent = x;      /* ���� ��� ���������� ����, ��������������� ��� �������� */

    if (!x->parent)                /* ���� ������� ������ �����                              */
        t->root = y;               /* ���������� ����� ������                                */
    else                           /* ���� ������� �� ������ �����                           */
    {
        if (x == x->parent->left)  /* ���� x - ����� �������                                 */
            x->parent->left = y;   /* y ���������� ����� ���������� �������� ����� ��������  */
        else                       /* ���� x - ������ �������                                */
            x->parent->right = y;  /* y ���������� ������ ���������� �������� ����� �������� */

    }
    y->parent = x->parent;         /* ��������� �������� y                                   */

    y->right = x;                  /* x ���������� ������ �������� y,                        */
    x->parent = y;                 /* � y - ��������� x                                      */
    return 0;
}
//Add node without restoring RBT
rbnode *rb_bst_insert(rbt *tree, key_t key)
{
    rbnode *y = NULL, *x = tree->root,
            *z = malloc(sizeof(rbnode));
    if (!z)
        return NULL;

    z->key = key;
    z->color = RB_RED;
    z->left = z->right = NULL;

    while (x)
    {
        y = x;
        if (key_same(z->key, x->key))
        {
            free(z);
            return NULL;
        }

        if (key_bigger(x->key, z->key))
            x=x->left;
        else
            x=x->right;
    }

    z->parent = y;
    if (!y)
        tree->root = z;
    else
    {
        if (key_bigger(y->key, z->key))
            y->left = z;
        else
            y->right = z;
    }

    return z;
}

int rb_insert(rbt *tree, key_t key)
{
    rbnode *x = rb_bst_insert(tree, key);
    if (!x)
        return 1;

    while (x != tree->root && x->parent->color == RB_RED)
    {
        rbnode *y = x->parent == x->parent->parent->left ? x->parent->parent->right
                                                          : x->parent->parent->left;

        if (y && y->color == RB_RED)
        {
            x->parent->color = RB_BLACK;
            y->color = RB_BLACK;
            x->parent->parent->color = RB_RED;
            x = x->parent->parent;
        }
        else
        {
            if (x->parent == x->parent->parent->left && x == x->parent->right)
            {
                x = x->parent;
                rb_rotate_left(tree, x);
            }
            else if (x->parent == x->parent->parent->right && x == x->parent->left)
            {
                x = x->parent;
                rb_rotate_right(tree, x);
            }

            x->parent->color = RB_BLACK;
            x->parent->parent->color = RB_RED;
            x == x->parent->left ? rb_rotate_right(tree, x->parent->parent)
                                 : rb_rotate_left(tree, x->parent->parent);
        }
    }

    tree->root->color = RB_BLACK;
    return 0;
}

int rb_delete (rbt *t, key_t key)
{
    rbnode *x, *y, *z = t->root, *n = NULL;

    /* ��� 1 - �������� �������� �� ������ ������ */

    while (z && !(key_same(z->key, key)))
        z = key_bigger(z->key, key) ? z->left      /* ���������� �� ����� ����� ��� ������  */
                         : z->right;    /* � ����������� �� �����                */

    if (!z) return -1;                  /* ������� �� ������                     */

    /* ������� ���� y, ������� ����� ���������� ������ �� ������ */
    if (!z->left || !z->right)
        y = z;
    else
    {
        rbt r;
        r.root = z->right;
        y = rb_min (&r);

        z->key  = y->key;                /* �������� ����                        */
    }

    /* ������� ������������� ������� ���������� ���������� ���� */

    x = y->left ? y->left : y->right;

    if (!x) /* ���� x - NIL-����, ������������� ��� */
    {
        n         = malloc(sizeof(rbnode));
        n->color  = RB_BLACK;
        x         = n;
    }

    x->parent = y->parent;               /* x ����� ����� �������� �������� y   */

    if (!y->parent)                      /* ���� ��������� ������               */
        t->root = x;                     /* ������������� ������                */
    else                                 /* ����� ��������� ����� �������       */
    {                                    /* �������� ���������� ����            */
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    if (y->color == RB_BLACK)               /* ���� ������ ������ �������,         */
    {                                    /* ���� ������������ RB-��������       */
        /* x ����������� "������ ������ ��������", ��� ��������� � ������
         * x ������ ����� ��������� �� ������ ������ �������, ���������� ����� �� �����
         *   ��� ���� �� �������� ������� ��������
         */
        while (x != t->root && x->color == RB_BLACK)
        {
            rbnode *w = x == x->parent->left ? x->parent->right /* w - ����    */
                                              : x->parent->left; /* ������� x   */

            if (w->color == RB_RED)                   /* ������ "���� - �������"   */
            {
                w->color         = RB_BLACK;          /* ����������                */
                x->parent->color = RB_RED;

                if (x == x->parent->left)          /* ������ ������� � ����� w  */
                {                                  /* � ����������� �� ����,    */
                    rb_rotate_left(t, x->parent);  /* ����� ��� ������ �������� */
                    w = x->parent->right;          /* �������� x                */
                }
                else
                {
                    rb_rotate_right(t, x->parent);
                    w = x->parent->left;
                }
            }
            if ((!w->left  || w->left->color  == RB_BLACK) &&
                (!w->right || w->right->color == RB_BLACK)
                    )                                   /* ������ "��� ���������� --- ������"     */
            {                                      /* � �.�. NIL-���� ��������� ������       */
                w->color = RB_RED;                    /* ���������� � ����� x                   */
                x = x->parent;                     /* ��������� ������� �������� x           */
                if (x->color == RB_RED)               /* ���� �� ��� ������� - ���������� ����� */
                {
                    x->color = RB_BLACK;
                    x = t->root;
                }
            }
            else
            {
                if ((x == x->parent->left  && (!w->right || w->right->color == RB_BLACK)) ||
                    (x == x->parent->right && (!w->left  || w->left->color  == RB_BLACK))
                        ) /* ������ "��������������� ��������� ������" */
                {
                    w->color = RB_RED;
                    if (x == x->parent->left)
                    {
                        w->left->color = RB_BLACK;
                        rb_rotate_right(t, w);
                        w = x->parent->right;
                    }
                    else
                    {
                        w->right->color = RB_BLACK;
                        rb_rotate_left(t, w);
                        w = x->parent->left;
                    }
                }
                /* ������ "������� ��������� ������" */
                w->color         = x->parent->color;
                x->parent->color = RB_BLACK;

                if (x == x->parent->left)
                {
                    w->right->color = RB_BLACK;
                    rb_rotate_left(t, x->parent);
                }
                else
                {
                    w->left->color = RB_BLACK;
                    rb_rotate_right(t, x->parent);
                }

                x = t->root;   /* ����� �� ����� */
            }
        }

        x->color = RB_BLACK;
    }

    free (y);  /* ������� ������� �� ������ */
    if (n)     /* ��������� � �������       */
    {
        if (n == t->root)                  /* ���� �������� ��������� ������� */
            t->root = NULL;
        else
        {
            if (n == n->parent->left)
                n->parent->left  = NULL;
            else
                n->parent->right = NULL;
        }
        free (n);
    }
    return 0;

}

int rb_print(const rbnode *root)
{
    if (root)
    {
        rb_print(root->left);

        printf("%i - %s", root->key.data, root->color == RB_RED ? "RED" : "BLACK");
        if (root->parent)
            printf(", parent = %i", root->parent->key.data);
        else
            printf(", root");
        if (root->left)
            printf(", left = %i", root->left->key.data);
        if (root->right)
            printf(", right = %i", root->right->key.data);
        printf("\n");

        rb_print(root->right);
    }
    return 0;
}
