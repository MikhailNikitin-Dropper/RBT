#ifndef RBT_BACK_H_INCLUDED
#define RBT_BACK_H_INCLUDED
typedef struct place
{
    int x, y;
} place;

// Node color
typedef enum
{
    RB_RED,
    RB_BLACK,
    RB_NIL
} rb_color;

// Key type
typedef struct key_t
{
    int data;
} key_t;

// Node of tree
typedef struct rbnode
{
    key_t key;
    rb_color color;
    struct rbnode *left, *right, *parent;
    place pos;
} rbnode;

// Tree
typedef struct rbt
{
    rbnode *root; // NULL для пустого дерева из одного nil-узла
} rbt;
//Transform int into data;
key_t from_int(int num);

// Tree construct
rbt *rbt_init();

// Tree destruct
int rb_free(rbt *tree);

// Search key in tree
rbnode *rb_search(rbt *tree, key_t key);

// Search min key
rbnode *rb_min(rbt *tree);

// Search max
rbnode *rb_max(rbt *tree);

// Left rotate around node
int rb_rotate_left(rbt *tree, rbnode *x);

// Right rotate around node
int rb_rotate_right(rbt *tree, rbnode *x);

// Insert element in tree
int rb_insert(rbt *tree, key_t key);

// Delete element from tree
int rb_delete(rbt *t, key_t key);

//Output tree
int rb_print(const rbnode *root);

#endif // RBT_BACK_H_INCLUDED
