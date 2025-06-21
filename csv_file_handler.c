#include"header.h"

void load_csv_records(const char* filename, b_plus_tree *tree) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Failed to open CSV file: %s\n", filename);
        return;
    }

    char line[1024];
    fgets(line, sizeof(line), file); // skip header

    while (fgets(line, sizeof(line), file)) {
        student* s = (student*) malloc(sizeof(student));
        char sgpa_raw[200];

        // Tokenize fields using comma
        char* token = strtok(line, ",");
        if (!token) continue;
        strcpy(s->mis, token);

        token = strtok(NULL, ",");
        strcpy(s->first_name, token);

        token = strtok(NULL, ",");
        strcpy(s->last_name, token);

        token = strtok(NULL, ",");
        s->cgpa = atof(token);

        token = strtok(NULL, ",");
        strcpy(sgpa_raw, token);

        // Parse SGPA values
        char* sgpa_token = strtok(sgpa_raw, " ");
        for (int i = 0; i < NUM_OF_SEM && sgpa_token != NULL; i++) {
            s->sgpa[i] = atof(sgpa_token);
            sgpa_token = strtok(NULL, " ");
        }

        token = strtok(NULL, ",");
        strcpy(s->branch, token);

        token = strtok(NULL, ",");
        s->year_of_passing = atoi(token);

        token = strtok(NULL, ",");
        s->admission_through = atoi(token);

        token = strtok(NULL, ",");
        s->division = atoi(token);

        insert_record(s, tree);
    }

    fclose(file);
    printf("CSV data loaded successfully.\n");
}
