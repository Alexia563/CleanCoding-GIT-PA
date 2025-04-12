//parcurgerge  graf cu DFS/BFS*/

#include <stdio.h>
#include <stdlib.h>

// Structura pentru nodul unei liste de adiacență
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Structura pentru graf
typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjacency_lists;
} Graph;

// Creează un nod nou
Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// Creează un graf cu un număr dat de vârfuri
Graph *create_graph(int vertices) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = vertices;
    graph->adjacency_lists = malloc(vertices * sizeof(Node *));
    graph->visited = malloc(vertices * sizeof(int));

    for (int i = 0; i < vertices; i++) {
        graph->adjacency_lists[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Adaugă o muchie între două noduri (graful este neorientat)
void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjacency_lists[src];
    graph->adjacency_lists[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjacency_lists[dest];
    graph->adjacency_lists[dest] = new_node;
}

// Introduce muchiile în graf
void insert_edges(Graph *graph, int number_of_edges) {
    int src, dest;
    printf("Adaugă %d muchii (ex: 0 1):\n", number_of_edges);
    for (int i = 0; i < number_of_edges; i++) {
        scanf("%d %d", &src, &dest);
        add_edge(graph, src, dest);
    }
}

// Verifică dacă o coadă este goală
int is_empty(Node *queue) {
    return queue == NULL;
}

// Adaugă un element în coadă
void enqueue(Node **queue, int value) {
    Node *new_node = create_node(value);

    if (is_empty(*queue)) {
        *queue = new_node;
    } else {
        Node *temp = *queue;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// Scoate un element din coadă
int dequeue(Node **queue) {
    int value = (*queue)->data;
    Node *temp = *queue;
    *queue = (*queue)->next;
    free(temp);
    return value;
}

// Resetează vectorul de vizite
void reset_visited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// Parcurgere DFS
void DFS(Graph *graph, int vertex) {
    Node *temp = graph->adjacency_lists[vertex];
    graph->visited[vertex] = 1;
    printf("%d ", vertex);

    while (temp != NULL) {
        int connected_vertex = temp->data;
        if (graph->visited[connected_vertex] == 0) {
            DFS(graph, connected_vertex);
        }
        temp = temp->next;
    }
}

// Parcurgere BFS
void BFS(Graph *graph, int start_vertex) {
    Node *queue = NULL;

    graph->visited[start_vertex] = 1;
    enqueue(&queue, start_vertex);

    while (!is_empty(queue)) {
        int current_vertex = dequeue(&queue);
        printf("%d ", current_vertex);

        Node *temp = graph->adjacency_lists[current_vertex];
        while (temp) {
            int adj_vertex = temp->data;

            if (graph->visited[adj_vertex] == 0) {
                graph->visited[adj_vertex] = 1;
                enqueue(&queue, adj_vertex);
            }
            temp = temp->next;
        }
    }
}

int main() {
    int number_of_vertices;
    int number_of_edges;
    int starting_vertex;

    printf("Câte noduri are graful? ");
    scanf("%d", &number_of_vertices);

    printf("Câte muchii are graful? ");
    scanf("%d", &number_of_edges);

    Graph *graph = create_graph(number_of_vertices);
    insert_edges(graph, number_of_edges);

    printf("De unde plecăm în DFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere DFS: ");
    DFS(graph, starting_vertex);

    reset_visited(graph);
    printf("\n");

    printf("De unde plecăm în BFS? ");
    scanf("%d", &starting_vertex);
    printf("Parcurgere BFS: ");
    BFS(graph, starting_vertex);

    printf("\n");
    return 0;
}


