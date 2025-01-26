#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONTACTS 100

// Structure to represent a contact
struct Contact {
    char name[50];
    char phone[15];
    char email[50];
    char socialMedia[50];
    char homeAddress[100];
    char workAddress[100];
    char companyName[50];
};

// Structure to represent a stack for managing contact nodes
struct Stack {
    struct Contact *data[MAX_CONTACTS];
    int top;
};

// Function prototypes
struct Contact *createContact();
void push(struct Stack *stack, struct Contact *contact);
struct Contact *pop(struct Stack *stack);
void addContact(struct Stack *stack);
void displayContacts(struct Stack *stack);
void updateContact(struct Stack *stack);
void searchContacts(struct Stack *stack);
void deleteContact(struct Stack *stack);
void deleteField(struct Stack *stack);
void updateField(struct Contact *contact);

int main() {
    struct Stack contactStack;
    contactStack.top = -1;

    int choice;

    do {
        // Display menu
        printf("\nAddress Book Menu:\n");
        printf("1. Add Contact\n");
        printf("2. Display Contacts\n");
        printf("3. Update Contact\n");
        printf("4. Search Contacts\n");
        printf("5. Delete Contact\n");
        printf("6. Delete Field\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact(&contactStack);
                break;
            case 2:
                displayContacts(&contactStack);
                break;
            case 3:
                updateContact(&contactStack);
                break;
            case 4:
                searchContacts(&contactStack);
                break;
            case 5:
                deleteContact(&contactStack);
                break;
            case 6:
                deleteField(&contactStack);
                break;
            case 7:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    // Free allocated memory by popping all elements from the stack
    while (contactStack.top != -1) {
        struct Contact *contact = pop(&contactStack);
        free(contact);
    }

    return 0;
}

struct Contact *createContact() {
    struct Contact *newContact = (struct Contact *)malloc(sizeof(struct Contact));
    if (!newContact) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    return newContact;
}

void push(struct Stack *stack, struct Contact *contact) {
    if (stack->top == MAX_CONTACTS - 1) {
        printf("Stack overflow.\n");
        exit(EXIT_FAILURE);
    }

    stack->data[++stack->top] = contact;
}

struct Contact *pop(struct Stack *stack) {
    if (stack->top == -1) {
        printf("Stack underflow.\n");
        exit(EXIT_FAILURE);
    }

    return stack->data[stack->top--];
}

void addContact(struct Stack *stack) {
    struct Contact *newContact = createContact();

    printf("Enter name: ");
    scanf(" %[^\n]", newContact->name);  // Note the space before %[^\n]
    printf("Enter phone number: ");
    scanf(" %[^\n]", newContact->phone);
    printf("Enter email: ");
    scanf(" %[^\n]", newContact->email);
    printf("Enter social media handles: ");
    scanf(" %[^\n]", newContact->socialMedia);
    printf("Enter home address: ");
    scanf(" %[^\n]", newContact->homeAddress);
    printf("Enter work address: ");
    scanf(" %[^\n]", newContact->workAddress);
    printf("Enter company name: ");
    scanf(" %[^\n]", newContact->companyName);

    push(stack, newContact);

    printf("Contact added successfully!\n");
}
void displayContacts(struct Stack *stack) {
    if (stack->top != -1) {
        printf("\nList of Contacts:\n");
        for (int i = stack->top; i >= 0; i--) {
            struct Contact *contact = stack->data[i];
            printf("Name: %s\n", contact->name);
            printf("Phone: %s\n", contact->phone);
            printf("Email: %s\n", contact->email);
            printf("Social Media: %s\n", contact->socialMedia);
            printf("Home Address: %s\n", contact->homeAddress);
            printf("Work Address: %s\n", contact->workAddress);
            printf("Company Name: %s\n", contact->companyName);
            printf("--------------------\n");
        }
    } else {
        printf("No contacts to display.\n");
    }
}

void updateContact(struct Stack *stack) {
    if (stack->top != -1) {
        char searchName[50];
        printf("Enter the name to update: ");
        scanf("%s", searchName);

        int found = 0;
        for (int i = stack->top; i >= 0; i--) {
            struct Contact *contact = stack->data[i];
            if (strcmp(contact->name, searchName) == 0) {
                updateField(contact);
                printf("Contact updated successfully!\n");
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Contact not found.\n");
        }
    } else {
        printf("No contacts to update.\n");
    }
}

void searchContacts(struct Stack *stack) {
    if (stack->top != -1) {
        char searchName[50];
        printf("Enter the name to search: ");
        scanf("%s", searchName);

        int found = 0;
        for (int i = stack->top; i >= 0; i--) {
            struct Contact *contact = stack->data[i];
            if (strcmp(contact->name, searchName) == 0) {
                printf("Contact found:\n");
                printf("Name: %s\n", contact->name);
                printf("Phone: %s\n", contact->phone);
                printf("Email: %s\n", contact->email);
                printf("Social Media: %s\n", contact->socialMedia);
                printf("Home Address: %s\n", contact->homeAddress);
                printf("Work Address: %s\n", contact->workAddress);
                printf("Company Name: %s\n", contact->companyName);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Contact not found.\n");
        }
    } else {
        printf("No contacts to search.\n");
    }
}

void deleteContact(struct Stack *stack) {
    if (stack->top != -1) {
        char searchName[50];
        printf("Enter the name to delete: ");
        scanf("%s", searchName);

        int found = 0;
        for (int i = stack->top; i >= 0; i--) {
            struct Contact *contact = stack->data[i];
            if (strcmp(contact->name, searchName) == 0) {
                free(pop(stack));
                printf("Contact deleted successfully!\n");
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Contact not found.\n");
        }
    } else {
        printf("No contacts to delete.\n");
    }
}

void deleteField(struct Stack *stack) {
    if (stack->top != -1) {
        char searchName[50];
        printf("Enter the name to delete field from: ");
        scanf("%s", searchName);

        int found = 0;
        for (int i = stack->top; i >= 0; i--) {
            struct Contact *contact = stack->data[i];
            if (strcmp(contact->name, searchName) == 0) {
                int deleteChoice;
                printf("Select deletion option:\n");
                printf("1. Delete entire contact\n");
                printf("2. Delete specific field\n");
                printf("Enter your choice: ");
                scanf("%d", &deleteChoice);

                switch (deleteChoice) {
                    case 1:
                        free(pop(stack));
                        printf("Contact deleted successfully!\n");
                        break;
                    case 2:
                        updateField(contact);  // Setting the field to an empty string effectively deletes it
                        printf("Field deleted successfully!\n");
                        break;
                    default:
                        printf("Invalid choice. No deletion performed.\n");
                        break;
                }

                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Contact not found.\n");
        }
    } else {
        printf("No contacts to delete field from.\n");
    }
}

void updateField(struct Contact *contact) {
    int fieldChoice;

    printf("Select field to update:\n");
    printf("1. Phone\n");
    printf("2. Email\n");
    printf("3. Social Media\n");
    printf("4. Home Address\n");
    printf("5. Work Address\n");
    printf("6. Company Name\n");
    printf("Enter your choice: ");
    scanf("%d", &fieldChoice);

    switch (fieldChoice) {
        case 1:
            printf("Enter new phone number: ");
            scanf("%s", contact->phone);
            break;
        case 2:
            printf("Enter new email: ");
            scanf("%s", contact->email);
            break;
        case 3:
            printf("Enter new social media handles: ");
            scanf("%s", contact->socialMedia);
            break;
        case 4:
            printf("Enter new home address: ");
            scanf("%s", contact->homeAddress);
            break;
        case 5:
            printf("Enter new work address: ");
            scanf("%s", contact->workAddress);
            break;
        case 6:
            printf("Enter new company name: ");
            scanf("%s", contact->companyName);
            break;
        default:
            printf("Invalid choice. No field updated.\n");
            return;  // Exit the function if the choice is invalid
    }

    printf("Field updated successfully!\n");
}