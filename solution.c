#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



typedef struct Node {
    int num_children;
    struct Node** children;
    void (*func)(pid_t, pid_t);
} Node;


Node* create_node(void (*func)(pid_t, pid_t), int num_children) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->num_children = num_children;
    node->children = (Node**)malloc(sizeof(Node*) * num_children);
    node->func = func;
    return node;
}

void execute_tree(Node* root, pid_t parent_pid) {
    pid_t pid = getpid();
    if (root->func != NULL) {
        root->func(pid, parent_pid);
    }

    for (int i = 0; i < root->num_children; i++) {
        pid_t child_pid = fork();

        if (child_pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        } else if (child_pid == 0) {
            execute_tree(root->children[i], pid);
            exit(EXIT_SUCCESS);
        } else {
            wait(NULL);
        }
    }
}


// ejemplo de uso

/*
        A
       / \
      B   C
         / \
        D   E
 */


void example_func(pid_t my_pid, pid_t parent_pid) {
    printf("My PID: %d, Parent PID: %d\n", my_pid, parent_pid);
}


int main() {
    Node* A = create_node(example_func, 2);
    Node* B = create_node(example_func, 0);
    Node* C = create_node(example_func, 2);
    Node* D = create_node(example_func, 0);
    Node* E = create_node(example_func, 0);

    A->children[0] = B;
    A->children[1] = C;

    C->children[0] = D;
    C->children[1] = E;

    execute_tree(A, getppid());

    return 0;
}

