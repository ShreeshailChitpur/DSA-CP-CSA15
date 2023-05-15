#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <unistd.h>

#define MAX_ITEMS 1000
#define TABLE_SIZE 100

typedef struct
{
    char name[20];
    int quantity;
    float price;
} Item;

typedef struct
{
    char name1[20];
    int key;
    Item value;
} HashItem;

int num_items = 0;
HashItem table[TABLE_SIZE];

// Hash function: mod [h(k) = mod m]
int hash_function(char *name)
{
    int hash = 0;
    for (int i = 0; i < strlen(name); i++)
    {
        hash = hash + name[i];
    }
    return hash % TABLE_SIZE;
}

/*
Other hash functions options:
|| MULTIPLICATIVE HASH FUNCTION: ||
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

|| SECOND HASH FUNCTION FOR COLLISION HANDLING: ||
Uses chaining:
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
*/

// Function to clear the inventory
void clear_inventory_file()
{
    FILE *file = fopen("inventory.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    ftruncate(fileno(file), 0);
    printf("\tCleared inventory!\n");
    fclose(file);
}

// Function to add new item to the inventory
void add_item()
{

    char item_name[20];
    printf("Enter item name: ");
    scanf("%s", item_name);

    int key = hash_function(item_name);

    if (table[key].key != 0)
    {
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

// Function to display items added in the inventory
void display_inventory()
{
    printf("Inventory list:\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i].key != 0)
        {
            printf("%s\t%d\t\t$%.2f\n", table[i].name1, table[i].value.quantity, table[i].value.price);
        }
    }
}

// Function to add items to inventory.txt file
void save_inventory(char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    fprintf(file, "\t Inventory\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (table[i].key != 0)
        {
            fprintf(file, "%s\t%d\t%f\n", table[i].name1, table[i].value.quantity, table[i].value.price);
        }
    }

    fclose(file);
    printf("Inventory saved to file '%s'\n", filename);
}

// Function to display items from iventory.txt file
void display_inventory_from_file()
{
    printf("Item\tQuantity\tPrice\n");
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    char line[100];
    int firstLine = 1;
    while (fgets(line, 100, file))
    {
        if (firstLine)
        {
            firstLine = 0; // Set the flag to false for subsequent lines
            continue;      // Skip the first line
        }
        Item item;
        sscanf(line, "%s %d %f", item.name, &item.quantity, &item.price);
        printf("%s\t%d\t$%.2f\n", item.name, item.quantity, item.price);
    }

    fclose(file);
}

// Function to remove item from inventory
void remove_item()
{
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    char item_name[20];
    printf("Enter the name of the item to remove: ");
    scanf("%s", item_name);

    char line[100];

    // Skip the first line of the file.
    fgets(line, 100, file);

    int found = 0;
    do
    {
        while (fgets(line, 100, file))
        {
            Item item;
            sscanf(line, "%s %d %f", item.name, &item.quantity, &item.price);
            if (strcmp(item.name, item_name) == 0)
            {
                printf("%s removed from inventory\n", item_name);
                found = 1;

                // Remove the item from the inventory table
                int key = hash_function(item_name);
                table[key].key = 0;
                table[key].name1[0] = '\0';
                table[key].value.quantity = 0;
                table[key].value.price = 0;

                break;
            }
        }
    } while (!feof(file) && !found);

    fclose(file);

    if (!found)
    {
        printf("%s not found in inventory\n", item_name);
    }
}

// Function to display items that need to be restocked
// If quantity < 30 --> Need to be ordered
void display_low_quantity_items()
{
    FILE *file = fopen("inventory.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file\n");
        return;
    }

    char line[100];
    while (fgets(line, 100, file))
    {
        Item item;
        sscanf(line, "%s %d %f", item.name, &item.quantity, &item.price);
        if (item.quantity < 30)
        {
            printf("\tList of items to be stocked: \n");
            printf("Item name: %s\tQuantity: %d\tPrice: $%f\n", item.name, item.quantity, item.price);
        }
    }

    fclose(file);
}

void login()
{

    int a = 0, i = 0;
    char uname[10], c = ' ';
    char pword[10], code[10];
    char user[10] = "user";
    char pass[10] = "pass";
    do
    {

        printf("\n  ========================  LOGIN   ========================  ");
        printf(" \n                        USERNAME:-");
        scanf("%s", &uname);
        printf(" \n                        PASSWORD:-");
        while (i < 10)
        {
            pword[i] = getch();
            c = pword[i];
            if (c == 13)
                break;
            else
                printf("*");
            i++;
        }
        pword[i] = '\0';
        // char code=pword;
        i = 0;
        // scanf("%s",&pword);
        if (strcmp(uname, "user") == 0 && strcmp(pword, "pass") == 0)
        {
            printf("  \n\n\n       WELCOME TO PRODUCT MANAGEMENT SYSTEM !!!! LOGIN IS SUCCESSFUL");
            printf("\n\n\n\t\t\t\tPress any key to continue...");
            getch(); // holds the screen
            break;
        }
        else
        {
            printf("\n        SORRY !!!!  LOGIN IS UNSUCESSFUL");
            a++;

            getch(); // holds the screen
        }
    } while (a <= 2);
    if (a > 2)
    {
        printf("\nSorry you have entered the wrong username and password for four times!!!");

        getch();
    }
    system("cls");
}

// Driver function
int main()
{
    printf("                                                                                                         \n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t==================================\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t|\t     WELCOME TO \t |\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t|  INVENTORY MANAGEMENT SYSTEM \t |\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t|\t\tUSING HASHING \t |\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t==================================\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
    printf("---------------------------------------------------------------------------------------------------------------\n");
    // printf("hello world\n");
    // clear_inventory_file();
    // add_item();
    // add_item();
    // display_inventory();
    // save_inventory("inventory.txt");
    // display_inventory_from_file();
    // display_low_quantity_items();
    printf("\n");

    login();

    int choice;
    do
    {
        printf("\n\tWhat would you like to do?\n");
        printf("1. Add an item\n");
        printf("2. Display the inventory\n");
        printf("3. Remove an item\n");
        printf("4. Display items to be ordered\n");
        printf("5. Clear inventory\n");
        printf("6. Save inventory\n");
        printf("7. Quit\n");

        scanf("%d", &choice);

        switch (choice)
        {
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
            save_inventory("inventory.txt");
            break;
        case 7:
            printf("\n\tThank you for using inventory management system!\n");
            break;
        default:
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 7);
    return 0;
}