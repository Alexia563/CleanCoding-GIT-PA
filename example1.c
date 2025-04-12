// Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf

#include <stdio.h>
#include <stdlib.h>

// Structura nodului pentru lista de adiacență
typedef struct Node {
    int data;
    struct Node *next;
} Node;

// Structura grafului
typedef struct Graph {
    int vertices;
    int *visited;
    Node **adjList;
} Graph;

// Structura stivei
typedef struct Stack {
    int top;
    int capacity;
    int *array;
} Stack;

// Creează un nod nou
Node *create_node(int value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

// Adaugă o muchie (bidirecțională) între două noduri
void add_edge(Graph *graph, int src, int dest) {
    Node *new_node = create_node(dest);
    new_node->next = graph->adjList[src];
    graph->adjList[src] = new_node;

    new_node = create_node(src);
    new_node->next = graph->adjList[dest];
    graph->adjList[dest] = new_node;
}

// Creează un graf cu v noduri
Graph *create_graph(int v) {
    Graph *graph = malloc(sizeof(Graph));
    graph->vertices = v;
    graph->adjList = malloc(v * sizeof(Node *));
    graph->visited = malloc(v * sizeof(int));

    for (int i = 0; i < v; i++) {
        graph->adjList[i] = NULL;
        graph->visited[i] = 0;
    }

    return graph;
}

// Creează o stivă
Stack *create_stack(int capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = malloc(capacity * sizeof(int));
    return stack;
}

// Adaugă un element în stivă
void push(Stack *stack, int value) {
    if (stack->top < stack->capacity - 1) {
        stack->array[++stack->top] = value;
    }
}

// Parcurgere DFS a grafului
void DFS(Graph *graph, Stack *stack, int node_index) {
    Node *current = graph->adjList[node_index];
    graph->visited[node_index] = 1;
    push(stack, node_index);

    while (current != NULL) {
        int connected_node = current->data;
        if (graph->visited[connected_node] == 0) {
            DFS(graph, stack, connected_node);
        }
        current = current->next;
    }
}

// Introduce muchiile în graf
void insert_edges(Graph *graph, int number_of_edges) {
    int src, dest;
    printf("Adauga %d muchii (nodurile sunt indexate de la 0):\n", number_of_edges);
    for (int i = 0; i < number_of_edges; i++) {
        scanf("%d %d", &src, &dest);
        if (src >= 0 && src < graph->vertices && dest >= 0 && dest < graph->vertices) {
            add_edge(graph, src, dest);
        } else {
            printf("Muchie invalida: %d - %d\n", src, dest);
            i--; // repetam pasul
        }
    }
}

// Resetează vectorul de vizite
void reset_visited(Graph *graph) {
    for (int i = 0; i < graph->vertices; i++) {
        graph->visited[i] = 0;
    }
}

// Determină dacă există drum între două noduri
int has_path(Graph *graph, int src, int dest) {
    Stack *temp_stack = create_stack(graph->vertices);
    DFS(graph, temp_stack, src);

    int found = 0;
    for (int i = 0; i <= temp_stack->top; i++) {
        if (temp_stack->array[i] == dest) {
            found = 1;
            break;
        }
    }

    free(temp_stack->array);
    free(temp_stack);
    reset_visited(graph);

    return found;
}

int main() {
    int number_of_vertices;
    int number_of_edges;

    printf("Cate noduri are graful? ");
    scanf("%d", &number_of_vertices);

    printf("Cate muchii are graful? ");
    scanf("%d", &number_of_edges);

    Graph *graph = create_graph(number_of_vertices);

    insert_edges(graph, number_of_edges);

    int restaurant_1, restaurant_2;
    printf("Verificam daca exista drum intre doua restaurante.\n");
    printf("Introdu indicele primului restaurant: ");
    scanf("%d", &restaurant_1);
    printf("Introdu indicele celui de-al doilea restaurant: ");
    scanf("%d", &restaurant_2);

    if (restaurant_1 >= 0 && restaurant_1 < number_of_vertices &&
        restaurant_2 >= 0 && restaurant_2 < number_of_vertices) {

        if (has_path(graph, restaurant_1, restaurant_2)) {
            printf("Exista drum intre restaurantele %d si %d.\n", restaurant_1, restaurant_2);
        } else {
            printf("NU exista drum intre restaurantele %d si %d.\n", restaurant_1, restaurant_2);
        }
    } else {
        printf("Restaurantele introduse sunt invalide.\n");
    }

    return 0;
}
