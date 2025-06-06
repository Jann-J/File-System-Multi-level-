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

/*
int main(int argc, char *argv[]){
    b_plus_tree root;
    init_tree(&root);

    int choice;
    char mis[MIS_LIMIT];
    student *s;

    while (1) {
        printf("\n===== COEP Record Management System =====\n");
        printf("1. Insert a student\n");
        printf("2. Update a student\n");
        printf("3. Get list of students (by MIS/branch/year)\n");
        printf("4. Search for a student (by MIS or name)\n");
        printf("5. Delete a student\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: {
                s = (student*) malloc(sizeof(student));
                printf("Enter MIS: "); fgets(s->mis, MIS_LIMIT, stdin); s->mis[strcspn(s->mis, "\n")] = 0;
                printf("First name: "); fgets(s->first_name, NAME_LIMIT, stdin); s->first_name[strcspn(s->first_name, "\n")] = 0;
                printf("Last name: "); fgets(s->last_name, NAME_LIMIT, stdin); s->last_name[strcspn(s->last_name, "\n")] = 0;
                printf("CGPA: "); scanf("%f", &s->cgpa); getchar();
                printf("Branch: "); fgets(s->branch, NAME_LIMIT, stdin); s->branch[strcspn(s->branch, "\n")] = 0;
                printf("Batch (year): "); scanf("%d", &s->year_of_passing); getchar();

                insert_record(s, &root);
                printf("Student inserted.\n");
                break;
            }
            case 2: {
                printf("Enter MIS of student to update: ");
                fgets(mis, MIS_LIMIT, stdin); mis[strcspn(mis, "\n")] = 0;

                s = (student*) malloc(sizeof(student));
                strcpy(s->mis, mis);
                printf("Enter updated First name: "); fgets(s->first_name, NAME_LIMIT, stdin); s->first_name[strcspn(s->first_name, "\n")] = 0;
                printf("Enter updated Last name: "); fgets(s->last_name, NAME_LIMIT, stdin); s->last_name[strcspn(s->last_name, "\n")] = 0;
                printf("Enter updated CGPA: "); scanf("%f", &s->cgpa); getchar();
                printf("Enter updated Branch: "); fgets(s->branch, NAME_LIMIT, stdin); s->branch[strcspn(s->branch, "\n")] = 0;
                printf("Enter updated Batch: "); scanf("%d", &s->year_of_passing); getchar();

                if (update_record(mis, s, root)) {
                    printf("Record updated.\n");
                } else {
                    printf("Student not found.\n");
                }
                break;
            }
            case 3:
                printf("Feature under development: filtering by branch/year. Coming soon!\n");
                break;
            case 4:
                printf("Feature under development: MIS/name-based search.\n");
                break;
            case 5:
                printf("Feature under development: delete functionality.\n");
                break;
            case 0:
                printf("Exiting system. Goodbye!\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}
*/

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