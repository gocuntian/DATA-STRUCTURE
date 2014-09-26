#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct node_type {
    int value;
    struct node_type *next;
    struct node_type *prev;
} node_type;

typedef struct list_type {
    node_type *head;
    node_type *tail;
    int node_counter;
} list_type;

node_type *get_new_node(int value) {
    node_type *new_node = (node_type *) malloc(sizeof(node_type));
    new_node->value = value;
    new_node->next = NULL;
    new_node->prev = NULL;
    return new_node;
}

list_type *get_new_list() {
    list_type *new_list = (list_type *) malloc(sizeof(list_type));
    new_list->head = NULL;
    new_list->tail = NULL;
    new_list->node_counter = 0;
    return new_list;
}

void insert_node(list_type *list, int value) {
    node_type *curr_node = NULL;
    for (curr_node = list->head; curr_node != NULL && curr_node->next != NULL; curr_node = curr_node->next) {
        ;
    }
    node_type *new_node = get_new_node(value);

    if (curr_node == NULL) {
        // 这种情况的出现当且仅当插入前链表为空
        list->head = new_node;
    } else {
        curr_node->next = new_node;
        new_node->prev = curr_node;
    }

    list->tail = new_node;

    list->node_counter ++;
}

node_type *get_node(list_type *list, int value) {
    node_type *curr_node = list->head;
    for (; curr_node != NULL && curr_node->value != value; curr_node = curr_node->next);
    return curr_node;
}

void delete_node(list_type *list, int value) {
    node_type *curr_node = get_node(list, value);
    if (curr_node == NULL) {
        return;
    }
    if (curr_node->prev != NULL) {
        curr_node->prev->next = curr_node->next;
    }
    if (curr_node->next != NULL) {
        curr_node->next->prev = curr_node->prev;
    }
    if (curr_node == list->head) {
        list->head = curr_node->next;
    }
    if (curr_node == list->tail) {
        list->tail = curr_node->prev;
    }
    free(curr_node);
    list->node_counter --;
}

/**
 * 交换两个节点，最少需要引入两个额外的节点指针变量，需要改变 8 个指针
 * @param node1 待交换的节点
 * @param node2 待交换的节点
 * @author jianzhang.zj
 */
void exchange_node(node_type *node1, node_type *node2) {
    if (node1 == node2) {
        // 情形 1
        return;
    } else if (node2->next == node1) {
        // 情形 2.1
        return exchange_node(node2, node1);
    } else if (node1->next == node2) {
        // 情形 2.2
        if (node1->prev != NULL) {
            node1->prev->next = node2;
        }
        if (node2->next != NULL) {
            node2->next->prev = node1;
        }
        node1->next = node2->next;
        node2->prev = node1->prev;
        node1->prev = node2;
        node2->next = node1;
        return;
    }

    // 情形 3
    if (node1->prev != NULL) {
        node1->prev->next = node2;
    }
    if (node1->next != NULL) {
        node1->next->prev = node2;
    }
    if (node2->prev != NULL) {
        node2->prev->next = node1;
    }
    if (node2->next != NULL) {
        node2->next->prev = node1;
    }

    node_type *temp1 = node1->next;
    node_type *temp2 = node1->prev;

    node1->next = node2->next;
    node1->prev = node2->prev;

    node2->next = temp1;
    node2->prev = temp2;
}

void exchange_value(list_type *list, int value1, int value2) {
    node_type *node1 = get_node(list, value1);
    node_type *node2 = get_node(list, value2);

    if (node1 == NULL || node2 == NULL) {
        if (node1 == NULL) {
            printf("\"%d\" is not in the list.\n", value1);
        }
        if (node2 == NULL) {
            printf("\"%d\" is not in the list.\n", value2);
        }
        return;
    }
    exchange_node(node1, node2);

    node_type *head = list->head;
    node_type *tail = list->tail;

    if (node1 == head) {
        list->head = node2;
    } else if (node1 == tail) {
        list->tail = node2;
    }

    if (node2 == head) {
        list->head = node1;
    } else if (node2 == tail) {
        list->tail = node1;
    }
}

void print_list(list_type *list) {
    node_type *curr_node = NULL;
    for (curr_node = list->head; curr_node != NULL; curr_node = curr_node->next) {
        printf("%-4d", curr_node->value);
    }
    printf("\n%d node(s) printed !\n\n", list->node_counter);
}

int main() {
    list_type *list = get_new_list();
    for (; 1; ) {
        int cmd, value, temp;
        scanf("%d", &cmd);
        if (cmd == -1) {
            scanf("%d", &value);
            delete_node(list, value);
        } else if (cmd == 1) {
            scanf("%d", &value);
            insert_node(list, value);
        } else if (cmd == 0) {
            scanf("%d%d", &value, &temp);
            exchange_value(list, value, temp);
        } else {
            printf("enter \"-1\" for delete and \"1\" to insert node.\n");
            printf("enter \"0\" to exchange the two values you enter next time.\n");
        }
        print_list(list);
    }
    return 0;
}
