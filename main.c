#include"header.h"


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

                // MIS
                printf("Enter MIS: ");
                fgets(s->mis, MIS_LIMIT, stdin);
                s->mis[strcspn(s->mis, "\n")] = 0;

                // First Name
                printf("First name: ");
                fgets(s->first_name, NAME_LIMIT, stdin);
                s->first_name[strcspn(s->first_name, "\n")] = 0;

                // Last Name
                printf("Last name: ");
                fgets(s->last_name, NAME_LIMIT, stdin);
                s->last_name[strcspn(s->last_name, "\n")] = 0;

                // SGPA (8 semesters)
                printf("Enter SGPA for 8 semesters (space separated, -1 if not available yet):\n");
                for (int i = 0; i < NUM_OF_SEM; i++) {
                    scanf("%f", &s->sgpa[i]);
                }
                getchar(); // clear newline

                // calculate cgpa
                s->cgpa = calculate_cgpa(s->sgpa);

                // Branch
                printf("Branch: ");
                fgets(s->branch, NAME_LIMIT, stdin);
                s->branch[strcspn(s->branch, "\n")] = 0;

                // Year of Passing
                printf("Year of passing: ");
                scanf("%d", &s->year_of_passing); getchar();

                // Admission Mode
                printf("Admission Through (0 - MHT-CET, 1 - JEE Mains): ");
                scanf("%d", &s->admission_through); getchar();

                // Division
                printf("Division (enter -1 if not allotted): ");
                scanf("%d", &s->division); getchar();

                insert_record(s, &root);
                printf("Student inserted.\n");
                break;

            }
            case 2: {
                printf("Enter MIS of student to update: ");
                fgets(mis, MIS_LIMIT, stdin); 
                mis[strcspn(mis, "\n")] = 0;

                student* existing = search_by_mis(root, mis);

                if (!existing) {
                    printf("Student with MIS %s not found.\n", mis);
                    break;
                }

                // Show current info
                printf("Current student details:\n");
                print_student(existing);

                // Update only specific fields
                printf("Enter updated First name (or press enter to keep '%s'): ", existing->first_name);
                char temp[NAME_LIMIT];
                fgets(temp, NAME_LIMIT, stdin);
                if (temp[0] != '\n') {
                    temp[strcspn(temp, "\n")] = 0;
                    strcpy(existing->first_name, temp);
                }

                printf("Enter updated Last name (or press enter to keep '%s'): ", existing->last_name);
                fgets(temp, NAME_LIMIT, stdin);
                if (temp[0] != '\n') {
                    temp[strcspn(temp, "\n")] = 0;
                    strcpy(existing->last_name, temp);
                }

                printf("Enter updated Branch (or press enter to keep '%s'): ", existing->branch);
                fgets(temp, NAME_LIMIT, stdin);
                if (temp[0] != '\n') {
                    temp[strcspn(temp, "\n")] = 0;
                    strcpy(existing->branch, temp);
                }

                printf("Enter updated Batch (or -1 to keep %d): ", existing->year_of_passing);
                int batch;
                if (scanf("%d", &batch) == 1 && batch != -1) {
                    existing->year_of_passing = batch;
                }
                getchar(); // flush newline

                printf("Record updated successfully.\n");
                break;
            }
            case 3:
                printf("Feature under development: filtering by branch/year or both. Coming soon!\n");
                break;
            case 4:
                printf("Enter MIS to search: ");
                fgets(mis, MIS_LIMIT, stdin); 
                mis[strcspn(mis, "\n")] = 0;

                // Search for student
                student* existing = search_by_mis(root, mis);

                if (!existing) {
                    printf("Student with MIS %s not found.\n", mis);
                }
                print_student(existing);
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


/*
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

    print_range_mis(root, "1234567890", "3456767890");
    return 0;
}
    */