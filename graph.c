#include <stdio.h>
#include <stdlib.h>

#define MAX_NODE_NUM 1000

/**
 * ͼ�бߵĽṹ�嶨��
 *
 * @author jianzhang.zj
 */
typedef struct arc_type
{
    int node_id;                // �ڵ���
    int arc_value;              // ����Ȩֵ
    struct arc_type *next_arc;  // ��һ���ߵ�ַ
} arc_type;

/**
 * ͼ�Ľṹ�嶨��
 *
 * @author jianzhang.zj
 */
typedef struct graph_type
{
    arc_type **head;            // ͼ��ÿ�����һ���ߵ�ַ
    int node_num;               // ͼ�ж�������
    int arc_num;                // ͼ�бߵ�����
} graph_type;

/**
 * ��ͼ�����һ���ߣ��ߵķ���Ϊ u ---> v��ȨֵΪ value
 *
 * @param graph ͼ�ĵ�ַ
 * @param u     ǰ���ڵ�
 * @param v     ��̽ڵ�
 * @param value ����Ȩֵ
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
 * �½�һ��ͼ��ͼ�нڵ�����Ϊ node_num���ߵ�����Ϊ arc_num
 *
 * @param node_num ͼ�нڵ������
 * @param arc_num  ͼ�бߵ�����
 * @return ͼ�ĵ�ַ
 * @author jianzhang.zj
 */
graph_type *get_graph(int node_num, int arc_num)
{
    // 1. ����һ���ڴ�ռ���������ͼ
    graph_type *graph = (graph_type *) malloc(sizeof (graph_type));
    // 2. ����ͼ�нڵ������������һ���ڴ�ռ����Ա���ָ��ÿ���ڵ��һ���ߵ�ָ��
    graph->head = (arc_type **) malloc((sizeof (arc_type *)) * node_num);
    int i;
    for (i = 0; i < node_num; i ++)
    {
        graph->head[i] = NULL;
    }
    // 3. ����ͼ�Ľڵ������ͱ�����
    graph->node_num = node_num;
    graph->arc_num = arc_num;

    return graph;
}

/**
 * ���벢��ʼ��һ��ͼ
 *
 * @return ͼ�ĵ�ַ
 * @author jianzhang.zj
 */
graph_type *read_graph()
{
    int node_num, arc_num;

    printf("������ͼ�нڵ��������\n");
    scanf("%d", &node_num);

    printf("������ͼ�бߵ�������\n");
    scanf("%d", &arc_num);

    graph_type *graph = get_graph(node_num, arc_num);

    printf("������ͼ�����еıߣ�\n");
    int i, u, v, value;
    for (i = 0; i < arc_num; i ++)
    {
        scanf("%d%d%d", &u, &v, &value);
        add_arc(graph, u, v, value);
        add_arc(graph, v, u, value);    // ����������ͼ��ʱ����Ҫ��ӷ����
    }

    return graph;
}

/**
 * ��ӡһ��ͼ
 *
 * @param graph ͼ�ĵ�ַ
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
