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


