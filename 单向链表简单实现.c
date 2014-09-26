#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node_type {
    int value;
    struct node_type *next;
} node_type;

typedef struct list_type {
    node_type *head;
    int node_counter;
} list_type;

/**
 * 添加一个新节点
 * @param value 新节点存储的数据
 * @return 该节点的指针
 */
node_type *get_new_node(int value) {
    node_type *new_node = (node_type *) malloc(sizeof(node_type));
    new_node->value = value;
    new_node->next = NULL;
    return new_node;
}

/**
 * 添加一个新的链表
 * @return 该链表的指针
 */
list_type *get_new_list() {
    list_type *new_list = (list_type *) malloc(sizeof(list_type));
    new_list->head = NULL;
    new_list->node_counter = 0;
    return new_list;
}

void insert_node(list_type *list, int value) {
    node_type *curr_node = NULL;
    for (curr_node = list->head; curr_node != NULL && curr_node->next != NULL; curr_node = curr_node->next) {
        ;
    }
    list->node_counter ++;
    node_type *new_node = get_new_node(value);
    if (curr_node == NULL) {
        list->head = new_node;
    } else {
        curr_node->next = new_node;
    }
}

void delete_node(list_type *list, int value) {
    node_type *curr_node = NULL, *prev_node = NULL;
    for (curr_node = list->head; curr_node != NULL && curr_node->value != value; curr_node = curr_node->next) {
        prev_node = curr_node;
    }

    // 这种情况出现，要么是链表为空，要么是链表中没有值为 value 的节点
    if (curr_node == NULL) {
        return;
    }
    list->node_counter --;
    if (prev_node == NULL) {
        list->head = curr_node->next;
    } else {
        prev_node->next = curr_node->next;
        free(curr_node);
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
        int cmd, value;
        scanf("%d", &cmd);
        if (cmd == -1) {
            scanf("%d", &value);
            delete_node(list, value);
        } else if (cmd == 1) {
            scanf("%d", &value);
            insert_node(list, value);
        } else {
            printf("please enter \"-1\" for delete and \"1\" to insert node int the list.\n");
        }
        print_list(list);
    }
    return 0;
}
