#include "header.h"
// range queries
// find start root
// then query in linear fashion
// till end_mis > curr_mis
void print_range_mis(node *root, char *start_mis, char *end_mis){
    if (!root) return;
    if(strcmp(end_mis, start_mis) < 0)
        return;

    node *leaf = find_leaf(root, start_mis);
    while (leaf != NULL) {
        for (int i = 0; i < leaf->num_keys; i++) {
            // within the range
            if (strcmp(leaf->keys[i], start_mis) >= 0 && strcmp(leaf->keys[i], end_mis) <= 0) {
                print_student(leaf->student[i]);
            }
            // If we’ve passed the end_mis
            if (strcmp(leaf->keys[i], end_mis) > 0) return;
        }
        leaf = leaf->next;
    }
}


// branchwise
// year-wise


// search based on
// name -> information with all the student with name (optional)
student* search_by_mis(node* root, char* mis) {
    node* leaf = find_leaf(root, mis);
    if (!leaf) return NULL;

    for (int i = 0; i < leaf->num_keys; i++) {
        if (strcmp(leaf->keys[i], mis) == 0)
            return leaf->student[i];
    }

    return NULL;
}