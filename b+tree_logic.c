#include"header.h"

void init_tree(b_plus_tree* btree){
    *btree = NULL;
    return;
}

node* create_node(int is_leaf) {
    node* new_node = (node*)malloc(sizeof(node));
    new_node->is_leaf = is_leaf;
    new_node->num_keys = 0;
    new_node->next = NULL;

    for (int i = 0; i <= MAX_KEYS; i++) {
        new_node->student[i] = NULL;
        new_node->children[i] = NULL;
    }

    for (int i = 0; i < MAX_KEYS; i++) {
        new_node->keys[i][0] = '\0';
    }

    return new_node;
}


void insert_record(student* s, b_plus_tree *btree){
    char upKey[MIS_LIMIT];
    node* newChild = NULL;

    // tree is empty, create the first node
    if(*btree == NULL){
        node* root = create_node(1);
        strcpy(root->keys[0], s->mis);
        root->num_keys = 1;
        root->student[0] = s;

        
        *btree = root;
        return;
    }

    node* newRoot = insert_internal(*btree, s, s->mis, upKey, &newChild);

    if (newRoot != NULL) {
        node* root = create_node(0);
        strcpy(root->keys[0], upKey);
        root->children[0] = *btree;
        root->children[1] = newChild;
        root->num_keys = 1;
        *btree = root;
    }
}

node* insert_internal(node* root, student* s, char* key, char* upKey, node** newChild) {
    int i;

    if (root->is_leaf) {
        // Leaf insert
        if (root->num_keys < MAX_KEYS) {
            i = root->num_keys - 1;
            while (i >= 0 && strcmp(key, root->keys[i]) < 0) {
                strcpy(root->keys[i + 1], root->keys[i]);
                root->student[i + 1] = root->student[i];
                i--;
            }
            strcpy(root->keys[i + 1], key);
            root->student[i + 1] = s;
            root->num_keys++;
            return NULL;
        } else {
            // Split leaf node
            node* newLeaf = create_node(1);
            char tempKeys[MAX_KEYS + 1][MIS_LIMIT];
            student* tempstudent[MAX_KEYS + 1];

            for (i = 0; i < MAX_KEYS; i++) {
                strcpy(tempKeys[i], root->keys[i]);
                tempstudent[i] = root->student[i];
            }

            // Insert new key in sorted order
            int pos = 0;
            while (pos < MAX_KEYS && strcmp(key, tempKeys[pos]) > 0) pos++;

            for (i = MAX_KEYS; i > pos; i--) {
                strcpy(tempKeys[i], tempKeys[i - 1]);
                tempstudent[i] = tempstudent[i - 1];
            }

            strcpy(tempKeys[pos], key);
            tempstudent[pos] = s;

            root->num_keys = (MAX_KEYS + 1) / 2;
            newLeaf->num_keys = (MAX_KEYS + 1) - root->num_keys;

            for (i = 0; i < root->num_keys; i++) {
                strcpy(root->keys[i], tempKeys[i]);
                root->student[i] = tempstudent[i];
            }

            for (i = root->num_keys; i < MAX_KEYS; i++) {
                root->keys[i][0] = '\0';
                root->student[i] = NULL;
            }

            for (i = 0; i < newLeaf->num_keys; i++) {
                strcpy(newLeaf->keys[i], tempKeys[i + root->num_keys]);
                newLeaf->student[i] = tempstudent[i + root->num_keys];
            }

            newLeaf->next = root->next;
            root->next = newLeaf;

            strcpy(upKey, newLeaf->keys[0]);
            *newChild = newLeaf;

            return root;
        }
    } else {
        // Internal node
        for (i = 0; i < root->num_keys && strcmp(key, root->keys[i]) >= 0; i++);

        node* newChildLocal = insert_internal(root->children[i], s, key, upKey, newChild);

        if (newChildLocal == NULL && *newChild == NULL)
            return NULL;

        if (root->num_keys < MAX_KEYS) {
            for (int j = root->num_keys; j > i; j--) {
                strcpy(root->keys[j], root->keys[j - 1]);
                root->children[j + 1] = root->children[j];
            }

            strcpy(root->keys[i], upKey);
            root->children[i + 1] = *newChild;
            root->num_keys++;

            return NULL;
        } else {
            // Split internal
            node* newInternal = create_node(0);
            char tempKeys[MAX_KEYS + 1][MIS_LIMIT];
            node* tempChildren[MAX_KEYS + 2];

            for (int j = 0; j < MAX_KEYS; j++) {
                strcpy(tempKeys[j], root->keys[j]);
                tempChildren[j] = root->children[j];
            }
            tempChildren[MAX_KEYS] = root->children[MAX_KEYS];

            for (int j = MAX_KEYS; j > i; j--) {
                strcpy(tempKeys[j], tempKeys[j - 1]);
                tempChildren[j + 1] = tempChildren[j];
            }

            strcpy(tempKeys[i], upKey);
            tempChildren[i + 1] = *newChild;

            int mid = (MAX_KEYS + 1) / 2;
            root->num_keys = mid;

            for (int j = 0; j < mid; j++) {
                strcpy(root->keys[j], tempKeys[j]);
                root->children[j] = tempChildren[j];
            }
            root->children[mid] = tempChildren[mid];

            newInternal->num_keys = MAX_KEYS - mid;
            for (int j = 0; j < newInternal->num_keys; j++) {
                strcpy(newInternal->keys[j], tempKeys[mid + 1 + j]);
                newInternal->children[j] = tempChildren[mid + 1 + j];
            }
            newInternal->children[newInternal->num_keys] = tempChildren[MAX_KEYS + 1];

            strcpy(upKey, tempKeys[mid]);
            *newChild = newInternal;

            return newInternal;
        }
    }
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

// int delete_record(char *mis){
    // find the record(different function for this maybe?? so we can reuse for update function as well), if found delete it return  1
    // else return 0

    //scenerios
    // last key in leaf -> direct delete
    // not last -> sort the leaf as well
    // the only one in leaf -> delete the whole leaf
    // if it is key in internal nodes then...well a lot to do
// }

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

int update_record(char *mis, student *updated, b_plus_tree btree){
    if(btree == NULL) return 0;

    node *leaf = find_leaf(btree, mis); //write this later

    if(!leaf) return 0;

    for(int i = 0; i < leaf->num_keys; i++){
        if(strcmp(mis, leaf->student[i]->mis) == 0){
            strcpy(leaf->student[i]->first_name, updated->first_name);
            strcpy(leaf->student[i]->last_name, updated->last_name);
            leaf->student[i]->cgpa = updated->cgpa;
            strcpy(leaf->student[i]->branch, updated->branch);
            leaf->student[i]->year_of_passing = updated->year_of_passing;

            return 1;
        }
    }
    return 0;
}