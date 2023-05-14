#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 1000
#define TABLE_SIZE 100

typedef struct {
    char name[20];
    int quantity;
    float price;
} Item;

typedef struct {
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
    int num_items;
    printf("How many items do you want to add? ");
    scanf("%d", &num_items);

    fflush(stdin);

    for (int i = 0; i < num_items; i++) {
        // Check if the item name is already in the inventory
        char item_name[20];
        printf("Enter item name: ");
        scanf("%s", item_name);

        int key = hash_function(item_name);

        if (table[key].key != 0) {
            printf("Item name already exists in the inventory.\n");
            continue;
        }

        // Add the item to the inventory
        Item item;
        printf("Enter item quantity: ");
        scanf("%d", &item.quantity);
        printf("Enter item price: ");
        scanf("%f", &item.price);

        HashItem hash_item;
        hash_item.key = key;
        hash_item.value = item;

        table[key] = hash_item;
        num_items++;
    }
}


void display_inventory() {
    printf("Inventory:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].key != 0) {
            printf("%s\t%d\t$%.2f\n", table[i].value.name, table[i].value.quantity, table[i].value.price);
        }
    }
}

void save_inventory(char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    fprintf(file, "Inventory:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (table[i].key != 0) {
            fprintf(file, "%s\t%d\t$%.2f\n", table[i].value.name, table[i].value.quantity, table[i].value.price);
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
    while (fgets(line, 100, file)) {
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



int main() {
    printf("Welcome to the inventory management system!\n");

    int choice;
    do {
        printf("What would you like to do?\n");
        printf("1. Add an item\n");
        printf("2. Display the inventory\n");
        printf("3. Remove an item\n");
        printf("4. Display items to be ordered\n");
        printf("5. Clear inventory\n");
        printf("6. Quit\n");

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_item();
                break;
            case 2:
                display_inventory_from_file();
                break;
            case 3:
                remove_item();
                break;
            case 4:
                display_low_quantity_items();
                break;
            case 5:
                clear_inventory_file();
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 6);

    return 0;
    add_item(); 
    add_item(); 
    display_inventory(); 
    save_inventory("inventory.txt"); 
    return 0;
}
