#include "RBT_info.h"

size_t rb_count(rbnode *root) {
    if (!root) return 0;

    return rb_count(root->left) + rb_count(root->right) + 1;
}

size_t rb_height(rbnode *root) {
    if (!root) return 0;

    size_t l_height = rb_height(root->left),
        r_height = rb_height(root->right);

    return l_height > r_height ? (l_height + 1) : (r_height + 1);
}

size_t rb_black_height(rbnode *root) {
    if (!root) return 0;

    size_t l_black_height = rb_black_height(root->left),
        r_black_height = rb_black_height(root->right),
        is_black = root->color == RB_BLACK ? 1 : 0;

    return l_black_height > r_black_height ? (l_black_height + is_black) : (r_black_height + is_black);
}

size_t rb_red_height(rbnode *root) {
    if (!root) return 0;

    size_t l_red_height = rb_red_height(root->left),
           r_red_height = rb_red_height(root->right),
           is_red = root->color == RB_RED ? 1 : 0;

    return l_red_height > r_red_height ? (l_red_height + is_red) : (r_red_height + is_red);
}

size_t rb_inner_count(rbnode *root) {
    if (!root) return 0;

    int is_leaf = !(root->left) && !(root->right);

    return rb_inner_count(root->left) + rb_inner_count(root->right) + !is_leaf;
}
