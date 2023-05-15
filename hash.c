int hash_function_2(char *name) {
    int hash = 0;
    for (int i = 0; i < strlen(name); i++) {
        hash = hash * 31 + name[i];
    }
    return hash % TABLE_SIZE;
}

int hash_function_3(char *name) {
    int hash = 0;
    for (int i = 0; i < strlen(name); i++) {
        hash = hash * 17 + name[i];
    }
    return hash % TABLE_SIZE;
}

void handle_collision(int hash_value, void *data) {
    if (hash_table[hash_value] != NULL) {
        struct node *new_node = malloc(sizeof(struct node));
        new_node->data = data;
        new_node->next = hash_table[hash_value];
        hash_table[hash_value] = new_node;
    } else {
        hash_table[hash_value] = data;
    }
}
