#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE_NUM 1000

/**
 * 图中边的结构体定义
 *
 * @author jianzhang.zj
 */
typedef struct arc_type
{
    int node_id;                // 节点编号
    int arc_value;              // 边上权值
    struct arc_type *next_arc;  // 下一条边地址
} arc_type;

/**
 * 图的结构体定义
 *
 * @author jianzhang.zj
 */
typedef struct graph_type
{
    arc_type **head;            // 图中每个点第一条边地址
    int node_num;               // 图中顶点数量
    int arc_num;                // 图中边的数量
} graph_type;

/**
 * 向图中添加一条边，边的方向为 u ---> v，权值为 value
 *
 * @param graph 图的地址
 * @param u     前驱节点
 * @param v     后继节点
 * @param value 边上权值
 * @author jianzhang.zj
 */
void add_arc(graph_type *graph, int u, int v, int value)
{
    arc_type *arc = (arc_type *) malloc(sizeof (arc_type));
    arc->node_id = v;
    arc->arc_value = value;
    arc->next_arc = graph->head[u];
    graph->head[u] = arc;
}

/**
 * 新建一个图，图中节点数量为 node_num，边的数量为 arc_num
 *
 * @param node_num 图中节点的数量
 * @param arc_num  图中边的数量
 * @return 图的地址
 * @author jianzhang.zj
 */
graph_type *get_graph(int node_num, int arc_num)
{
    // 1. 申请一段内存空间用来保存图
    graph_type *graph = (graph_type *) malloc(sizeof (graph_type));
    // 2. 根据图中节点的数量，申请一段内存空间用以保存指向每个节点第一条边的指针
    graph->head = (arc_type **) malloc((sizeof (arc_type *)) * node_num);
    int i;
    for (i = 0; i < node_num; i ++)
    {
        graph->head[i] = NULL;
    }
    // 3. 设置图的节点数量和边数量
    graph->node_num = node_num;
    graph->arc_num = arc_num;

    return graph;
}

/**
 * 读入并初始化一个图
 *
 * @return 图的地址
 * @author jianzhang.zj
 */
graph_type *read_graph()
{
    int node_num, arc_num;

    printf("请输入图中节点的数量：\n");
    scanf("%d", &node_num);

    printf("请输入图中边的数量：\n");
    scanf("%d", &arc_num);

    graph_type *graph = get_graph(node_num, arc_num);

    printf("请输入图中所有的边：\n");
    int i, u, v, value;
    for (i = 0; i < arc_num; i ++)
    {
        scanf("%d%d%d", &u, &v, &value);
        add_arc(graph, u, v, value);
        add_arc(graph, v, u, value);    // 仅仅是无向图的时候需要添加反向边
    }

    return graph;
}

/**
 * 打印一个图
 *
 * @param graph 图的地址
 * @author jianzhang.zj
 */
void print_graph(graph_type *graph)
{
    int i;
    for (i = 0; i < graph->node_num; i ++)
    {
        int u = i;
        arc_type *arc = graph->head[u];
        for (; arc != NULL; arc = arc->next_arc)
        {
            int v = arc->node_id;
            int value = arc->arc_value;
            printf("%d ---> %d : %d\n", u, v, value);
        }
    }
}

int main()
{
    graph_type *graph = read_graph();
    print_graph(graph);
    return 0;
}
