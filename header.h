#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define NUM_OF_SEM 8
#define NAME_LIMIT 50
#define MIS_LIMIT 11
#define MAX_KEYS 3

typedef struct Student {
    char mis[MIS_LIMIT];
    char first_name[NAME_LIMIT];
    char last_name[NAME_LIMIT];
    float cgpa;
    int sgpa[NUM_OF_SEM];
    char branch[NAME_LIMIT];
    int year_of_passing;
    int admission_through;         // 0 -> mht-cet 1-> jee_mains
    int division;
} student;

typedef struct node {
    char keys[MAX_KEYS][MIS_LIMIT];
    student *student[MAX_KEYS + 1];
    struct node *children[MAX_KEYS + 1];
    int num_keys;
    int is_leaf;
    struct node *next;
} node;

typedef node *b_plus_tree;

// Helper functions
void init_tree(b_plus_tree* btree);
node* create_node(int is_leaf);
node* find_leaf(node* root, char* mis);
void print_student(student* s);
student* create_student(char* mis, char* first_name, char* last_name, float cgpa, char* branch, int yop);

// Insert Record
void insert_record(student* s, b_plus_tree *btree);
node* insert_internal(node* root, student* s, char* key, char* upKey, node** newChild);

// Update record
int update_record(char *mis, student *updated, b_plus_tree btree);

// Delete Record
int delete_record(char *mis);

// Range query based on mis
void print_range_mis(node *root, char *start_mis, char *end_mis);

// Search by mis
student* search_by_mis(node* root, char* mis);
// Print all records
void print_leaf_mis(b_plus_tree root);
