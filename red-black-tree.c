#include <stdio.h>
#include <stdlib.h>

#define RED 1
#define BLACK 0

typedef struct node_type {
    int val;                        // 节点的关键字
    int color;                      // 节点的颜色
    struct node_type *fa;           // 节点的父亲
    struct node_type *left_son;     // 节点的左儿子
    struct node_type *right_son;    // 节点的右儿子
} node_type;

typedef struct tree_type {
    int size;              // 红黑树的大小
    node_type *root;       // 红黑树的根
    node_type *NIL;        // 红黑树的 NIL 节点
} tree_type;

// 声明一个红黑树的全局变量
tree_type *tree;

/**
 * 添加一个红黑树中的节点
 * @param int val               节点的关键字
 * @param int color             节点的颜色
 * @param node_type *fa         节点的父亲指针
 * @param node_type *left_son   节点的左儿子指针
 * @param node_type *right_son  节点的右儿子指针
 * @return node_type *          指向节点的指针
 */
node_type *add_node(int val, int color, node_type *fa, node_type *left_son, node_type *right_son) {
    node_type *u = (node_type *)malloc(sizeof(node_type));
    u->val = val;
    u->color = color;
    u->fa = fa;
    u->left_son = left_son;
    u->right_son = right_son;
}

/**
 * 对红黑树进行初始化
 */
void tree_init() {
    tree = (tree_type *)malloc(sizeof(tree_type));
    tree->size = 0;
    tree->root = NULL;
    tree->NIL = add_node(-1, BLACK, NULL, NULL, NULL);
}

/**
 * 更加直观的一种打印树的方式
 * @param node_type *u      当前节点的指针
 */
void tree_print(node_type *u) {
    if (u == NULL || u == tree->NIL) {
        return;
    }
    printf("%4d\ncolor : %6s      left_son : %4d      right_son : %4d\n\n", u->val, (u->color == BLACK ? "BLACK" : "RED"), u->left_son->val, u->right_son->val);
    if (u != tree->NIL) {
        tree_print(u->left_son);
        tree_print(u->right_son);
    }
}

/**
 * 打印树的关键信息
 * @param node_type *u      当前节点的指针
 */
void tree_print_back_up(node_type *u) {
    if (u == NULL) {
        return;
    }
    if (u == tree->NIL) {
        printf("addr : %10p\n", u);
        printf("NIL\n");
        printf("val : %4d, color : %6s, father is %10p, left_son : %10p, right_son : %10p\n", u->val, (u->color == BLACK ? "BLACK" : "RED"), u->fa, u->left_son, u->right_son);
        printf("\n");
        return;
    }
    printf("addr : %10p\n", u);
    printf("val : %4d, color : %6s, father is %10p, left_son : %10p, right_son : %10p\n", u->val, (u->color == BLACK ? "BLACK" : "RED"), u->fa, u->left_son, u->right_son);
    printf("\n");
    tree_print(u->left_son);
    tree_print(u->right_son);
}

/**
 * 对节点 u 进行左旋
 * @param node_type *u      当前节点的指针
 */
void left_rotate(node_type *u) {
    node_type *fa = u->fa;
    node_type *right_son = u->right_son;
    node_type *right_left_son = right_son->left_son;

    u->right_son = right_left_son;
    right_left_son->fa = u;

    right_son->left_son = u;
    u->fa = right_son;

    if (fa->left_son == u) {
        fa->left_son = right_son;
    } else if (fa->right_son == u) {
        fa->right_son = right_son;
    } else {
        printf("there is something wrong in left_rotate\n");
        exit(EXIT_FAILURE);
    }
    right_son->fa = fa;
    if (right_son->fa == tree->NIL) {
        tree->root = right_son;
    }
}

/**
 * 对节点 u 进行右旋
 * @param node_type *u      当前节点的指针
 */
void right_rotate(node_type *u) {
    node_type *fa = u->fa;
    node_type *left_son = u->left_son;
    node_type *left_right_son = left_son->right_son;

    u->left_son = left_right_son;
    left_right_son->fa = u;

    left_son->right_son = u;
    u->fa = left_son;

    if (fa->left_son == u) {
        fa->left_son = left_son;
    } else if (fa->right_son == u) {
        fa->right_son = left_son;
    } else {
        printf("there is something wrong in right_rotate\n");
        exit(EXIT_FAILURE);
    }
    left_son->fa = fa;
    if (left_son->fa == tree->NIL) {
        tree->root = left_son;
    }
}

/**
 * 插入节点之后的修复函数
 * @param node_type *u      当前待调整的节点指针
 */
void tree_insert_fix_up(node_type *u) {
    node_type *fa = u->fa;
    for (; fa->color == RED; ) {
        node_type *gf = fa->fa;
        if (fa == gf->left_son) {
            node_type *un = gf->right_son;
            if (un->color == RED) {
                fa->color = BLACK;
                un->color = BLACK;
                gf->color = RED;
                u = gf;
                fa = u->fa;
            } else if (un->color == BLACK) {
                if (fa->right_son == u) {
                    u = fa;
                    left_rotate(u);
                    fa = u->fa;
                    gf = fa->fa;
                }
                fa->color = BLACK;
                gf->color = RED;
                right_rotate(gf);
            } else {
                printf("there is something wrong in tree_insert_fix_up\n");
                exit(EXIT_FAILURE);
            }
        } else if (fa == gf->right_son) {
            node_type *un = gf->left_son;
            if (un->color == RED) {
                fa->color = BLACK;
                un->color = BLACK;
                gf->color = RED;
                u = gf;
                fa = u->fa;
            } else if (un->color == BLACK) {
                if (fa->left_son == u) {
                    u = fa;
                    right_rotate(u);
                    fa = u->fa;
                    gf = fa->fa;
                }
                fa->color = BLACK;
                gf->color = RED;
                left_rotate(gf);
            } else {
                printf("there is something wrong in tree_insert_fix_up\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    tree->root->color = BLACK;
}

/**
 * 红黑树的插入函数
 * @param node_type *new_node       待插入的节点
 */
void tree_insert(node_type *new_node) {
    node_type *u = tree->root, *fa = NULL;
    if (u == NULL) {
        u = new_node;
        u->color = BLACK;
        tree->root = u;
        tree->NIL->left_son = tree->root;
        tree->NIL->right_son = tree->NIL;
        tree->size ++;
        return;
    }
    for (; u != tree->NIL; ) {
        fa = u;
        if (new_node->val > u->val) {
            u = u->right_son;
        } else if (new_node->val < u->val) {
            u = u->left_son;
        } else {
            printf("there are more than one node whose value is %d\n", u->val);
            exit(EXIT_FAILURE);
        }
    }
    new_node->fa = fa;
    if (fa->val > new_node->val) {
        fa->left_son = new_node;
    } else if (fa->val < new_node->val) {
        fa->right_son = new_node;
    } else {
        printf("something wrong in insert\n");
        exit(EXIT_FAILURE);
    }
    tree_insert_fix_up(new_node);
    tree->size ++;
}

/**
 * 寻找指定节点的后继
 * @param node_type *u      节点指针
 * @return node_type *      节点的后继节点指针
 */
node_type *tree_next(node_type *u) {
    if (u->right_son != tree->NIL) {
        u = u->right_son;
        for (; u->left_son != tree->NIL; u = u->left_son);
        return u;
    } else if (u->right_son == tree->NIL) {
        node_type *fa = u->fa;
        for (; fa != tree->NIL && u == fa->right_son; ) {
            u = fa;
            fa = u->fa;
        }
        return fa;
    } else {
        printf("there is something wrong in tree_next()\n");
        exit(EXIT_FAILURE);
    }
}

/**
 * 红黑树删除节点之后的调整函数
 * @param node_type *u      待调整的节点指针
 */
void tree_delete_fix_up(node_type *u) {
    if (u == NULL) {
        return;
    }
    node_type *fa = u->fa;
    node_type *br = NULL;
    for (; tree->root != u && u->color == BLACK; ) {
        if (u == fa->left_son) {
            br = fa->right_son;
            if (br->color == RED) {
                br->color = BLACK;
                fa->color = RED;
                left_rotate(fa);
                br = fa->right_son;
            }
            if (br->left_son->color == BLACK && br->right_son->color == BLACK) {
                br->color = RED;
                u = fa;
                fa = u->fa;
            } else {
                if (br->right_son->color == BLACK) {
                    br->left_son->color = BLACK;
                    br->color = RED;
                    right_rotate(br);
                    br = fa->right_son;
                }
                br->color = fa->color;
                fa->color = BLACK;
                br->right_son->color = BLACK;
                left_rotate(fa);
                u = tree->root;
            }
        } else if (u == fa->right_son) {
            br = fa->left_son;
            if (br->color == RED) {
                br->color = BLACK;
                fa->color = RED;
                right_rotate(fa);
                br = fa->left_son;
            }
            if (br->left_son->color == BLACK && br->right_son->color == BLACK) {
                br->color = RED;
                u = fa;
                fa = u->fa;
            } else {
                if (br->left_son->color == BLACK) {
                    br->right_son->color = BLACK;
                    br->color = RED;
                    left_rotate(br);
                    br = fa->left_son;
                }
                br->color = fa->color;
                fa->color = BLACK;
                br->left_son->color = BLACK;
                right_rotate(fa);
                u = tree->root;
            }
        } else {
            printf("there is something wrong in tree_insert_fix_up()\n");
            exit(EXIT_FAILURE);
        }
    }
    u->color = BLACK;
}

/**
 * 删除红黑树中指定的节点
 * @param node_type *u          待删除节点的指针
 */
void tree_delete(node_type *u) {
    if (u == NULL) {
        return;
    }
    node_type *fa = u->fa, *replace = NULL;
    if (u->right_son == tree->NIL && u->left_son == tree->NIL) {
        tree->NIL->fa = fa;
        if (fa->left_son == u) {
            fa->left_son = tree->NIL;
        } else if (fa->right_son == u) {
            fa->right_son = tree->NIL;
        } else {
            printf("there something wrong in tree_delete()\n");
            exit(EXIT_FAILURE);
        }
        tree->size --;
        if (tree->size == 0) {
            tree->root = NULL;
        }
        if (tree->size > 0 && u->color == BLACK) {
            tree_delete_fix_up(tree->NIL);
        }
        free(u);
    } else if (u->left_son == tree->NIL) {
        u->right_son->fa = fa;
        if (fa->left_son == u) {
            fa->left_son = u->right_son;
        } else if (fa->right_son == u) {
            fa->right_son = u->right_son;
        } else {
            printf("there is something wrong in tree_delete()\n");
            exit(EXIT_FAILURE);
        }
        tree->size --;
        if (tree->size > 0 && fa == tree->NIL) {
            tree->root = u->right_son;
        } else if (tree->size == 0) {
            tree->root = NULL;
        }
        if (tree->size > 0 && u->color == BLACK) {
            tree_delete_fix_up(u->right_son);
        }
        free(u);
    } else if (u->right_son == tree->NIL) {
        u->left_son->fa = fa;
        if (fa->left_son == u) {
            fa->left_son = u->left_son;
        } else if (fa->right_son == u) {
            fa->right_son = u->left_son;
        } else {
            printf("there is something wrong in tree_delete()\n");
            exit(EXIT_FAILURE);
        }
        tree->size --;
        if (tree->size > 0 && fa == tree->NIL) {
            tree->root = u->left_son;
        } else if (tree->size == 0) {
            tree->root = NULL;
        }
        if (tree->size > 0 && u->color == BLACK) {
            tree_delete_fix_up(u->left_son);
        }
        free(u);
    } else {
        node_type *next = tree_next(u);
        u->val = next->val;
        tree_delete(next);
    }
}

/**
 * 在红黑树中查找关键字
 * @param int val           待查找的关键字的值
 * @return node_type *      如果查找到，返回该节点指针，否则返回 NULL
 */
node_type *tree_find(int val) {
    node_type *u = tree->root;
    if (tree->size <= 0) {
        printf("there is no node whose value is %d\n", val);
        return NULL;
    }
    for (; u != tree->NIL; ) {
        if (u->val == val) {
            return u;
        } else if (u->val > val) {
            u = u->left_son;
        } else if (u->val < val) {
            u = u->right_son;
        }
    }
    printf("there is no node whose value is %d\n", val);
    return NULL;
}

/**
 * 对代码进行手工模拟，主要验证插入和删除函数的正确性
 *
 * input :
 * 第一行一个整数，表示操作的数量 n
 * 接下来 n 行，每行要么是 "+ a" 要么是 "- a"，其中，+ 表示插入，- 表示删除
 *
 * sample input :
 * 4
 * + 2
 * + 5
 * + 1
 * - 2
 */
void test() {
    tree_init();
    int tot, i, a;
    char cmd[20];
    scanf("%d", &tot);
    for (i = 0; i < tot; i ++) {
        scanf("%s%d", cmd, &a);
        if (cmd[0] == '+') {
            node_type *u = add_node(a, RED, tree->NIL, tree->NIL, tree->NIL);
            tree_insert(u);
            printf("after the insert, red black tree has the following shape:\n");
            printf("totally %d node(s)\n", tree->size);
            tree_print(tree->root);
        } else {
            node_type *u = tree_find(a);
            if (u != NULL) {
                tree_delete(u);
            }
            printf("after the delete, red black tree has the following shape:\n");
            printf("totally %d node(s)\n", tree->size);
            tree_print(tree->root);
        }
    }
}

int main(int argc, const char *argv[])
{
    test();
    return 0;
}
