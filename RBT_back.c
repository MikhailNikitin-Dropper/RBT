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
    rbnode *y = x->right;         /* находим новый корень поддерева                         */

    x->right = y->left;            /* левый потомок y становится правым потомком x           */
    if (y->left)
        y->left->parent = x;       /* если это внутренний узел, устанавливается его родитель */

    if (!x->parent)                /* если поворот вокруг корня                              */
        t->root = y;               /* установили новый корень                                */
    else                           /* если поворот не вокруг корня                           */
    {
        if (x == x->parent->left)  /* если x - левый ребенок                                 */
            x->parent->left = y;   /* y становится левым поддеревом родителя точки вращения  */
        else                       /* если x - правый ребенок                                */
            x->parent->right = y;  /* y становится правым поддеревом родителя точки вращения */

    }
    y->parent = x->parent;         /* установка родителя y                                   */

    y->left = x;                   /* x становится левым потомком y,                         */
    x->parent = y;                 /* а y - родителем x                                      */
    return 0;
}



int rb_rotate_right (rbt *t, rbnode *x)
{
    rbnode *y = x->left;          /* находим новый корень поддерева                         */

    x->left = y->right;            /* правый потомок y становится левым потомком x           */
    if (y->right)
        y->right->parent = x;      /* если это внутренний узел, устанавливается его родитель */

    if (!x->parent)                /* если поворот вокруг корня                              */
        t->root = y;               /* установили новый корень                                */
    else                           /* если поворот не вокруг корня                           */
    {
        if (x == x->parent->left)  /* если x - левый ребенок                                 */
            x->parent->left = y;   /* y становится левым поддеревом родителя точки вращения  */
        else                       /* если x - правый ребенок                                */
            x->parent->right = y;  /* y становится правым поддеревом родителя точки вращения */

    }
    y->parent = x->parent;         /* установка родителя y                                   */

    y->right = x;                  /* x становится правым потомком y,                        */
    x->parent = y;                 /* а y - родителем x                                      */
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

    /* Шаг 1 - удаление элемента из дерева поиска */

    while (z && !(key_same(z->key, key)))
        z = key_bigger(z->key, key) ? z->left      /* Спускаемся до листа влево или вправо  */
                         : z->right;    /* в зависимости от ключа                */

    if (!z) return -1;                  /* элемент не найден                     */

    /* находим узел y, который будет фактически удален из дерева */
    if (!z->left || !z->right)
        y = z;
    else
    {
        rbt r;
        r.root = z->right;
        y = rb_min (&r);

        z->key  = y->key;                /* копируем ключ                        */
    }

    /* находим единственного потомка фактически удаляемого узла */

    x = y->left ? y->left : y->right;

    if (!x) /* если x - NIL-узел, актуализируем его */
    {
        n         = malloc(sizeof(rbnode));
        n->color  = RB_BLACK;
        x         = n;
    }

    x->parent = y->parent;               /* x будет новым ребенком родителя y   */

    if (!y->parent)                      /* если удаляется корень               */
        t->root = x;                     /* устанавливаем корень                */
    else                                 /* иначе удаляется новый ребенок       */
    {                                    /* родителя удаленного узла            */
        if (y == y->parent->left)
            y->parent->left = x;
        else
            y->parent->right = x;
    }

    if (y->color == RB_BLACK)               /* Если удален черный элемент,         */
    {                                    /* надо восстановить RB-свойства       */
        /* x объявляется "дважды черной вершиной", без отражения в памяти
         * x всегда будет указывать на дважды черную вершину, поднимаясь вверх до корня
         *   или пока не окажется красной вершиной
         */
        while (x != t->root && x->color == RB_BLACK)
        {
            rbnode *w = x == x->parent->left ? x->parent->right /* w - брат    */
                                              : x->parent->left; /* вершины x   */

            if (w->color == RB_RED)                   /* случай "брат - красный"   */
            {
                w->color         = RB_BLACK;          /* перекраска                */
                x->parent->color = RB_RED;

                if (x == x->parent->left)          /* нужный поворот и новый w  */
                {                                  /* в зависимости от того,    */
                    rb_rotate_left(t, x->parent);  /* левым или правым ребенком */
                    w = x->parent->right;          /* является x                */
                }
                else
                {
                    rb_rotate_right(t, x->parent);
                    w = x->parent->left;
                }
            }
            if ((!w->left  || w->left->color  == RB_BLACK) &&
                (!w->right || w->right->color == RB_BLACK)
                    )                                   /* случай "оба племянники --- черные"     */
            {                                      /* в т.ч. NIL-узел считается черным       */
                w->color = RB_RED;                    /* перекраска и смена x                   */
                x = x->parent;                     /* добавляем черноту родителю x           */
                if (x->color == RB_RED)               /* если он был красный - завершение цикла */
                {
                    x->color = RB_BLACK;
                    x = t->root;
                }
            }
            else
            {
                if ((x == x->parent->left  && (!w->right || w->right->color == RB_BLACK)) ||
                    (x == x->parent->right && (!w->left  || w->left->color  == RB_BLACK))
                        ) /* случай "противоположный племянник черный" */
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
                /* случай "ближний племянник черный" */
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

                x = t->root;   /* выход из цикла */
            }
        }

        x->color = RB_BLACK;
    }

    free (y);  /* удаляем элемент из памяти */
    if (n)     /* исключаем и удаляем       */
    {
        if (n == t->root)                  /* если удалялся последний элемент */
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
