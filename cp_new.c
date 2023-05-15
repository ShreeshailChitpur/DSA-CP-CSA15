#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ITEMS 1000
#define TABLE_SIZE 100

typedef struct {
    char name[20];
    int quantity;
    float price;
} Item;

typedef struct {
    char name1[20];
    int key;
    Item value;
} HashItem;

int num_items = 0;
HashItem table[TABLE_SIZE];

int hash_function(char *name) {
    int hash = 0;
    for (int i = 0; i < strlen(name); i++) {
        hash = hash + name[i];
    }
    return hash % TABLE_SIZE;
}
void clear_inventory_file() {
  FILE *file = fopen("inventory.txt", "w");
  if (file == NULL) {
    printf("Error opening file\n");
    return;
  }

  ftruncate(fileno(file), 0);
  printf("Cleared inventory!\n");
  fclose(file);
}
void add_item() {
    
        char item_name[20];
        printf("Enter item name: ");
        scanf("%s", item_name);

        int key = hash_function(item_name);

        if (table[key].key != 0) {
            printf("Item name already exists in the inventory.\n");
        }

        // Add the item to the inventory
        Item item;
        strcpy(item.name, item_name);
        printf("Enter item quantity: ");
        scanf("%d", &item.quantity);
        printf("Enter item price: ");
        scanf("%f", &item.price);

        HashItem hash_item;
        hash_item.key = key;
        strcpy(hash_item.name1, item.name);
        hash_item.value = item;

        table[key] = hash_item;
        num_items++;
}
void display_inventory() {
    printf("Inventory:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].key != 0) {
            printf("%s\t%d\t$%.2f\n", table[i].name1, table[i].value.quantity, table[i].value.price);
        }
    }
}
//Delete from here
void save_inventory(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(file, "Inventory:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].key != 0) {
            fprintf(file, "%s\t%d\t%f\n", table[i].name1, table[i].value.quantity, table[i].value.price);
        }
    }

    fclose(file);
    printf("Inventory saved to file '%s'\n", filename);
}
void display_inventory_from_file() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char line[100];
    int firstLine = 1;
    while (fgets(line, 100, file)) {
         if (firstLine) {
            firstLine = 0; // Set the flag to false for subsequent lines
            continue; // Skip the first line
        }
        Item item;
        sscanf(line, "%s %d %f", item.name, &item.quantity, &item.price);
        printf("%s\t%d\t$%.2f\n", item.name, item.quantity, item.price);
    }

    fclose(file);
}
void remove_item() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char item_name[20];
    printf("Enter the name of the item to remove: ");
    scanf("%s", item_name);

    char line[100];
    int found = 0;
    do {
        while (fgets(line, 100, file)) {
            Item item;
            sscanf(line, "%s %d %f", item.name, &item.quantity, &item.price);
            if (strcmp(item_name, item.name) == 0) {
                // Found the item to remove
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Item not found.\n");
            break;
        }

        // Remove the item from the file
        fseek(file, -strlen(line), SEEK_CUR);
        fprintf(file, "\n");

        printf("Item removed successfully.\n");

        // Check if the user wants to remove another item
        char answer[2];
        printf("Do you want to remove another item? (Y/N) ");
        scanf("%s", answer);

        if (strcmp(answer, "Y") == 0) {
            found = 0;
        } else {
            break;
        }
    } while (found);

    fclose(file);
}
void display_low_quantity_items() {
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    char line[100];
    while (fgets(line, 100, file)) {
        Item item;
        sscanf(line, "%s %d %f", item.name, &item.quantity, &item.price);
        if (item.quantity < 30) {
            printf("Item name: %s\nQuantity: %d\nPrice: %f\n", item.name, item.quantity, item.price);
        }
    }

    fclose(file);
}
int main(){
    printf("hello world\n");
    clear_inventory_file();
    add_item();
    add_item();
    display_inventory();
    save_inventory("inventory.txt");
    display_inventory_from_file();
    display_low_quantity_items();
    return 0;
}