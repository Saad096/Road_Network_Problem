#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_NODES 100

typedef struct Node {
    int id;
    int weight;
    struct Node* next;
} Node;

typedef struct Graph {
    int numNodes;
    Node* adjacencyList[MAX_NODES];
} Graph;

Node* createNode(int id, int weight) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->id = id;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numNodes) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = numNodes;
    for (int i = 0; i < numNodes; ++i)
        graph->adjacencyList[i] = NULL;
    return graph;
}

void addEdge(Graph* graph, int src, int dest, int weight) {
    Node* newNode = createNode(dest, weight);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;
}

void dijkstra(Graph* graph, int source, int destination) {
    int numNodes = graph->numNodes;
    int* distances = (int*)malloc(numNodes * sizeof(int));
    int* previous = (int*)malloc(numNodes * sizeof(int));
    bool* visited = (bool*)malloc(numNodes * sizeof(bool));

    for (int i = 0; i < numNodes; ++i) {
        distances[i] = INT_MAX;
        previous[i] = -1;
        visited[i] = false;
    }

    distances[source] = 0;

    for (int count = 0; count < numNodes - 1; ++count) {
        int minDistance = INT_MAX;
        int minIndex = -1;

        for (int v = 0; v < numNodes; ++v) {
            if (!visited[v] && distances[v] <= minDistance) {
                minDistance = distances[v];
                minIndex = v;
            }
        }

        visited[minIndex] = true;

        Node* currentNode = graph->adjacencyList[minIndex];
        while (currentNode != NULL) {
            int neighbor = currentNode->id;
            int weight = currentNode->weight;

            int distanceThroughMinIndex = distances[minIndex] + weight;
            if (distanceThroughMinIndex < distances[neighbor]) {
                distances[neighbor] = distanceThroughMinIndex;
                previous[neighbor] = minIndex;
            }

            currentNode = currentNode->next;
        }
    }

    if (distances[destination] == INT_MAX) {
        printf("No path from source to destination.\n");
    } else {
        printf("Shortest path from source to destination: ");
        int currentNode = destination;
        while (currentNode != -1) {
            printf("%d ", currentNode);
            currentNode = previous[currentNode];
        }
        printf("\n");

        printf("Shortest distance from source to destination: %d\n", distances[destination]);
    }

    free(distances);
    free(previous);
    free(visited);
}

int main() {
    int numNodes = 25;
    Graph* graph = createGraph(numNodes);

    // Add edges to the graph with heuristic values
    addEdge(graph, 0, 1, 5);
    addEdge(graph, 0, 2, 5);
    addEdge(graph, 1, 3, 5);
    addEdge(graph, 2, 1, 5);
    addEdge(graph, 2, 4, 5);
    addEdge(graph, 3, 4, 2);
    addEdge(graph, 3, 5, 1);
    addEdge(graph, 4, 6, 5);
    addEdge(graph, 4, 7, 2);
    addEdge(graph, 5, 8, 3);
    addEdge(graph, 6, 9, 2);
    addEdge(graph, 6, 10, 4);
    addEdge(graph, 7, 10, 1);
    addEdge(graph, 7, 11, 6);
    addEdge(graph, 8, 11, 2);
    addEdge(graph, 9, 12, 3);
    addEdge(graph, 9, 13, 2);
    addEdge(graph, 10, 13, 1);
    addEdge(graph, 11, 14, 4);
    addEdge(graph, 11, 15, 3);
    addEdge(graph, 12, 16, 2);
    addEdge(graph, 12, 17, 3);
    addEdge(graph, 13, 17, 5);
    addEdge(graph, 14, 18, 2);
    addEdge(graph, 15, 18, 4);
    addEdge(graph, 16, 19, 1);
    addEdge(graph, 17, 19, 3);
    addEdge(graph, 18, 20, 2);
    addEdge(graph, 18, 21, 1);
    addEdge(graph, 19, 22, 5);
    addEdge(graph, 19, 23, 2);
    addEdge(graph, 20, 23, 3);
    addEdge(graph, 21, 24, 2);
    addEdge(graph, 22, 24, 1);


    int source = 0;
    int destination = 24;    
    dijkstra(graph, 0, 24);
    return 0;
}
// #include <stdio.h>
// int main(void)
// {
//     printf("Hello world!\n");
//     return 0;
// }