#include"header.h"

student* create_student(char* mis, char* first_name, char* last_name, float cgpa, char* branch, int yop) {
    student* s = (student*)malloc(sizeof(student));
    strcpy(s->mis, mis);
    strcpy(s->first_name, first_name);
    strcpy(s->last_name, last_name);
    s->cgpa = cgpa;
    strcpy(s->branch, branch);
    s->year_of_passing = yop;
    return s;
}

void print_leaf_mis(b_plus_tree root) {
    while (!root->is_leaf) {
        root = root->children[0];
    }

    printf("\nLeaf Nodes (MIS order):\n");
    while (root != NULL) {
        for (int i = 0; i < root->num_keys; i++) {
            printf("%s ", root->keys[i]);

        }
        root = root->next;
    }
    printf("\n");
}

void print_student(student* s) {
    if (!s) return;
    printf("MIS: %s\n", s->mis);
    printf("Name: %s %s\n", s->first_name, s->last_name);
    printf("Branch: %s\n", s->branch);
    printf("CGPA: %.2f\n", s->cgpa);
    printf("Year of Passing: %d\n", s->year_of_passing);
    printf("Division: %d\n", s->division);
    printf("------\n");
}

node* find_leaf(node* root, char* mis) {
    if (!root) return NULL;

    node* curr = root;
    while (!curr->is_leaf) {
        int i = 0;
        while (i < curr->num_keys && strcmp(mis, curr->keys[i]) >= 0)
            i++;
        curr = curr->children[i];
    }
    return curr;
}
