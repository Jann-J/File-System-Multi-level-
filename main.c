#include"header.h"

student* create_student(char* mis, char* fname, char* lname, float cgpa, char* branch, int yop) {
    student* s = (student*)malloc(sizeof(student));
    strcpy(s->mis, mis);
    strcpy(s->first_name, fname);
    strcpy(s->last_name, lname);
    s->cgpa = cgpa;
    strcpy(s->branch, branch);
    s->year_of_passing = yop;
    return s;
}

int main(int argc, char *argv[]){
    b_plus_tree root;
    init_tree(&root);

    student* s6 = create_student("6789067890", "Frank", "Wilson", 8.0, "IT", 2024);
    student* s1 = create_student("1234567890", "Alice", "Smith", 9.1, "CSE", 2025);
    student* s2 = create_student("2345667890", "Bob", "Jones", 8.5, "IT", 2025);
    student* s5 = create_student("5678956789", "Eva", "Martin", 9.5, "CSE", 2023);
    student* s4 = create_student("4567867890", "David", "Clark", 7.8, "ENTC", 2026);
    student* s3 = create_student("3456767890", "Charlie", "Brown", 9.0, "CSE", 2024);

    insert_record(s1, &root);
    insert_record(s2, &root);
    insert_record(s3, &root);
    insert_record(s4, &root);
    insert_record(s5, &root);
    insert_record(s6, &root);

    print_leaf_mis(root);

    student* updated = create_student("1234567890", "Alice", "Smith", 9.7, "CSE", 2025);
    int result = update_record(updated->mis, updated, root);
    if (result) {
        printf("Update successful.\n");
    } else {
        printf("MIS not found in tree.\n");
    }

    print_leaf_mis(root);
    return 0;
}