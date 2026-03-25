#include <stdio.h>
#include <string.h>

#define MAX_ITEMS 100

struct Item {
    int id;
    char name[50];
    int quantity;
    float price;
};

struct Item inventory[MAX_ITEMS];
int itemCount = 0;

static void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

static void readLine(char *buffer, size_t size) {
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
        buffer[len - 1] = '\0';
}

// Function to add item
void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("Inventory full!\n");
        return;
    }

    int id, quantity;
    float price;
    char name[50];
    int idExists = 0;

    printf("Enter item ID: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid input for ID.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id) {
            idExists = 1;
            break;
        }
    }

    if (idExists) {
        printf("Item ID already exists!\n");
        return;
    }

    printf("Enter item name: ");
    readLine(name, sizeof(name));
    if (name[0] == '\0') {
        printf("Name cannot be empty.\n");
        return;
    }

    printf("Enter quantity: ");
    if (scanf("%d", &quantity) != 1) {
        printf("Invalid input for quantity.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    if (quantity < 0) {
        printf("Quantity cannot be negative.\n");
        return;
    }

    printf("Enter price: ");
    if (scanf("%f", &price) != 1) {
        printf("Invalid input for price.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    if (price < 0) {
        printf("Price cannot be negative.\n");
        return;
    }

    inventory[itemCount].id = id;
    strcpy(inventory[itemCount].name, name);
    inventory[itemCount].quantity = quantity;
    inventory[itemCount].price = price;
    itemCount++;

    printf("Item added successfully!\n");
}

void displayItems() {
    if (itemCount == 0) {
        printf("No items in inventory.\n");
        return;
    }

    printf("\nID\tName\t\tQuantity\tPrice\n");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < itemCount; i++) {
        printf("%d\t%-15s\t%d\t\t%.2f\n",
               inventory[i].id,
               inventory[i].name,
               inventory[i].quantity,
               inventory[i].price);
    }
}

int findItemIndexByID(int id) {
    for (int i = 0; i < itemCount; i++) {
        if (inventory[i].id == id)
            return i;
    }
    return -1;
}

void searchItem() {
    int id;
    printf("Enter item ID to search: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid id.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int idx = findItemIndexByID(id);
    if (idx == -1) {
        printf("Item not found.\n");
        return;
    }

    printf("\nItem Found:\n");
    printf("ID: %d\n", inventory[idx].id);
    printf("Name: %s\n", inventory[idx].name);
    printf("Quantity: %d\n", inventory[idx].quantity);
    printf("Price: %.2f\n", inventory[idx].price);
}

void updateItem() {
    int id;
    printf("Enter item ID to update: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid id.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int idx = findItemIndexByID(id);
    if (idx == -1) {
        printf("Item not found.\n");
        return;
    }

    int newQty;
    float newPrice;
    printf("Enter new quantity: ");
    if (scanf("%d", &newQty) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    if (newQty < 0) {
        printf("Quantity cannot be negative.\n");
        return;
    }

    printf("Enter new price: ");
    if (scanf("%f", &newPrice) != 1) {
        printf("Invalid input.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();
    if (newPrice < 0) {
        printf("Price cannot be negative.\n");
        return;
    }

    inventory[idx].quantity = newQty;
    inventory[idx].price = newPrice;
    printf("Item updated successfully.\n");
}

void deleteItem() {
    int id;
    printf("Enter item ID to delete: ");
    if (scanf("%d", &id) != 1) {
        printf("Invalid id.\n");
        clearInputBuffer();
        return;
    }
    clearInputBuffer();

    int idx = findItemIndexByID(id);
    if (idx == -1) {
        printf("Item not found.\n");
        return;
    }

    for (int i = idx; i < itemCount - 1; i++) {
        inventory[i] = inventory[i + 1];
    }
    itemCount--;
    printf("Item deleted successfully.\n");
}

int main() {
    int choice;
    do {
        printf("\n===== Inventory Management System =====\n");
        printf("1. Add Item\n");
        printf("2. Display Items\n");
        printf("3. Search Item\n");
        printf("4. Update Item\n");
        printf("5. Delete Item\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("Invalid choice!\n");
            clearInputBuffer();
            choice = 0;
            continue;
        }
        clearInputBuffer();

        switch (choice) {
            case 1: addItem(); break;
            case 2: displayItems(); break;
            case 3: searchItem(); break;
            case 4: updateItem(); break;
            case 5: deleteItem(); break;
            case 6: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n"); break;
        }
    } while (choice != 6);
    return 0;
}