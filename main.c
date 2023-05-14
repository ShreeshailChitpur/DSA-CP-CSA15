#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 1000

typedef struct {
    char name[20];
    int quantity;
    float price;
} Item;

// Structure to store the
// user details (Signup details)
struct details {
	char uname[100];
	int age;
	char password[100];
	char email[100];
	char mobile[10];
};

struct details s[100];

int flag = 1, i, j = 0, count = 0, caps = 0;
int small = 0, special = 0, numbers = 0;
int success = 0, x, choice;
char temp_name[100], temp_password1[100];
char temp_password2[100], temp_email[100];
char temp_mobile[100];
int temp_age, total = 0, food_choice, n;
int num_items = 0;
Item items[MAX_ITEMS];

void add_item() {
    if (num_items >= MAX_ITEMS) {
        printf("Inventory is full\n");
        return;
    }

    Item item;
    printf("Enter item name: ");
    scanf("%s", item.name);
    printf("Enter item quantity: ");
    scanf("%d", &item.quantity);
    printf("Enter item price: ");
    scanf("%f", &item.price);

    items[num_items] = item;
    num_items++;
}

void display_inventory() {
    printf("Inventory:\n");
    for (int i = 0; i < num_items; i++) {
        printf("%s\t%d\t$%.2f\n", items[i].name, items[i].quantity, items[i].price);
    }
}

// Function to create a new
// user for the Food ordering
// system
void signup()
{
	printf("\n\n*****Welcome to signup page****\n");
	printf("\tEnter Your name: ");
	scanf("%s", temp_name);

	printf("\tEnter Your Age: ");
	scanf("%d", &temp_age);

	printf("\tEnter Your Email: ");
	scanf("%s", temp_email);

	printf("\tEnter Password: ");
	scanf("%s", temp_password1);

	printf("\tConfirm Password:");
	scanf("%s", temp_password2);

	printf("\nEnter Your Mobile Number: ");
	scanf("%s", temp_mobile);

	// Function Call to validate
	// the user creation
	x = validate();
	if (x == 1){
		account_check();
		login();
	}
}

// Function to validate the user
// for signup process
int validate()
{
	// Validate the name
	for (i = 0; temp_name[i] != '\0'; i++) {
		if (!((temp_name[i] >= 'a' && temp_name[i] <= 'z')
			|| (temp_name[i] >= 'A'
				&& temp_name[i] <= 'Z'))) {
			printf("\nPlease Enter the valid Name\n");
			flag = 0;
			break;
		}
	}
	if (flag == 1) {
		count = 0;

		// Validate the Email ID
		for (i = 0;temp_email[i] != '\0'; i++) {
			if (temp_email[i] == '@'|| temp_email[i] == '.')
				count++;
		}
		if (count >= 2&& strlen(temp_email) >= 5) {
			// Validating the Password and
			// Check whether it matches
			// with Conform Password
			if (!strcmp(temp_password1,
						temp_password2)) {
				if (strlen(temp_password1) >= 8
					&& strlen(temp_password1) <= 12) {
					caps = 0;
					small = 0;
					numbers = 0;
					special = 0;
					for (i = 0; temp_password1[i] != '\0';
						i++) {
						if (temp_password1[i] >= 'A'
							&& temp_password1[i] <= 'Z')
							caps++;
						else if (temp_password1[i] >= 'a'
								&& temp_password1[i]
										<= 'z')
							small++;
						else if (temp_password1[i] >= '0'
								&& temp_password1[i]
										<= '9')
							numbers++;
						else if (temp_password1[i] == '@'
								|| temp_password1[i] == '&'
								|| temp_password1[i] == '#'
								|| temp_password1[i]
										== '*')
							special++;
					}
					if (caps >= 1 && small >= 1
						&& numbers >= 1 && special >= 1) {
						// Validating the Input age
						if (temp_age != 0 && temp_age > 0) {
							// Validating the Input mobile
							// number
							if (strlen(temp_mobile) == 10) {
								for (i = 0; i < 10; i++) {
									if (temp_mobile[i]
											>= '0'
										&& temp_mobile[i]
											<= '9') {
										success = 1;
									}
									else {
										printf("\n\nPlease Enter Valid mobile Number\n\n");
										return 0;
										break;
									}
								}

								// Success is assigned with
								// value 1, Once every
								// inputs are correct.
								if (success == 1)
									return 1;
							}
							else {
								printf("\n\nPlease Enter the 10 digit mobile number\n");
								return 0;
							}
						}
						else {
							printf("\n\nPlease Enter the valid age\n\n");
							return 0;
						}
					}
					else {
						printf("\n\nPlease Enter the");
						printf("strong password, Your ");
						printf("password must contain ");
						printf("atleast one uppercase, ");
						printf("Lowercase, Number and ");
						printf("special character\n\n");
						return 0;
					}
				}
				else {
					printf("\nYour Password is very short\nLength must between 8 to 12\n\n");
					return 0;
				}
			}
			else {
				printf("\nPassword Mismatch\n\n");
				return 0;
			}
		}
		else {
			printf("\nPlease Enter Valid E-Mail\n\n");

			return 0;
		}
	}
}

// Function to check if the account
// already exists or not
void account_check()
{
	for (i = 0; i < 100; i++) {
		// Check whether the email
		// and password are already
		// matched with existed account
		if (!(strcmp(temp_email, s[i].email)
			&& strcmp(temp_password1,
						s[i].password))) {
			printf("\n\nAccount Already Existed. Please Login !!\n\n");
			main();
			break;
		}
	}
	// if account does not already
	// existed, it creates a new
	// one with new inputs
	if (i == 100) {
		strcpy(s[j].uname, temp_name);
		s[j].age = temp_age;
		strcpy(s[j].password, temp_password1);
		strcpy(s[j].email, temp_email);
		strcpy(s[j].mobile, temp_mobile);
		j++;
		printf("\n\n\nAccount Successfully Created!!\n\n");
	}
}

// Function to Login the users
void login()
{
	printf("\n\n*****Welcome to Login page *******\n\n");
	int search = 0;

	printf("\tEnter Your Email: ");
	scanf("%s", temp_email);
	printf("\tEnter Your Password: ");
	scanf("%s", temp_password1);
	for (i = 0; i < 100; i++) {
		// Check whether the input
		// email is already existed or not
		if (!strcmp(s[i].email, temp_email)) {
			// Check whether the password
			// is matched with the email or not
			if (!strcmp(s[i].password, temp_password1)) {
				printf("\n\nWelcome %s, ", s[i].uname);
				printf("Your are successfully ");
				printf("logged in\n\n ");
				printf("We Provide two ways of search\n ");
				printf("1)Add item\n 2)Display inventory \n3)Exit\n\n");
				printf("Please Enter your choice:");
				scanf("%d", & search);
				
				switch (search) {

                case 1:
                    add_item();
                break;
                case 2:
                    display_inventory();
                    break;
				case 3: {
					// exit(1);
					main();
					return;
				}
				default: {
					printf("Please Enter the valid choice\n\n ");
					break;
				}
				}
				break;
			}
			else {
				printf("\n\nInvalid Password! ");
				printf("Please Enter the correct password\n\n");
				main();
				break;
			}
		}
		else {
			printf("\n\nAccount doesn't exist,Please signup!!\n\n ");
			main();
			break;
		}
	}
}


int main() {
    int choice = 0;

    while (choice != 3) {
        printf("1. Sign In\n");
        printf("2. Admin login\n");
        printf("3. Login\n");
        printf("4. Quit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                signup();
                break;
            case 2:
                //adminLogin();
                break;
            case 3:
                login();
                break;
            case 4:
                printf("Goodbye!\n");
                exit(0);
                break;
            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
