#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct FoodItem
{
    char name[100];
    float price;
    int quantity;
    struct FoodItem* next;
};

struct OrderItem
{
    char name[100];
    char customerName[100];
    float price;
    int quantity;
    struct OrderItem* next;
};

struct OrderQueueNode
{
    struct OrderItem* data;
    struct OrderQueueNode* next;
};

struct StackNode
{
    int tableNumber;
    char customerName[100];
    struct OrderItem* orderInfo;
    struct StackNode* next;
};

struct User
{
    char username[20];
    char password[20];
};

struct User admin = {"admin", "123"};
struct OrderQueueNode *front = NULL;
struct OrderQueueNode *rear= NULL;

int authenticate(struct User* currentUser)
{
    char username[20];
    char password[20];
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);
    if (strcmp(currentUser->username, username) == 0 && strcmp(currentUser->password, password) == 0)
    {
        return 1;
    }
    else
    {
        printf("Authentication failed. Invalid username or password.\n");
        return 0;
    }
}

struct FoodItem* createFoodItemNode(char name[], float price, int quantity)
{



    struct FoodItem* newItem = (struct FoodItem*)malloc(sizeof(struct FoodItem));
    if (newItem != NULL)
    {
        strcpy(newItem->name, name);
        newItem->price = price;
        newItem->quantity = quantity;
        newItem->next = NULL;
    }
    return newItem;
}

void addFoodItem(struct FoodItem** head, char name[], float price, int quantity)
{
    struct FoodItem* newItem = createFoodItemNode(name, price, quantity);
    newItem->next = *head;
    *head = newItem;
    printf("Food item added successfully!\n");
}

void editFoodItem(struct FoodItem** head, char oldName[])
{
    struct FoodItem* current = *head;
    while (current != NULL)
    {
        if (strcmp(current->name, oldName) == 0)
        {
            printf("Enter the new name for %s: ", oldName);
            scanf("%s", current->name);
            printf("Enter the new quantity for %s: ", current->name);
            scanf("%d", &current->quantity);
            printf("Food item edited successfully!\n");
            return;
        }
        current = current->next;
    }
    printf("Food item not found!\n");
}\

void deleteFoodItem(struct FoodItem** head, char name[])
{
    struct FoodItem* current = *head;
    struct FoodItem* prev = NULL;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (prev == NULL)
            {
                *head = current->next;
            }
            else
            {
                prev->next = current->next;
            }
            free(current);
            printf("Food item deleted successfully!\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Food item not found!\n");
}

void displayMenu(struct FoodItem* head)
{
    struct FoodItem* current = head;

    if (current != NULL)
    {
        printf("|--------|----------------------|------------|-----------|\n");
        printf("| %-6s | %-20s | %-10s | %-9s |\n", "No.", "Name", "Price ($)", "Quantity");
        printf("|--------|----------------------|------------|-----------|\n");
    }
    else
    {
        printf("No item available\n\n");
        return;
    }

    int itemNumber = 1;
    while (current != NULL)
    {
        printf("| %-6d | %-20s | %-10.2f | %-9d |\n", itemNumber, current->name, current->price, current->quantity);
        current = current->next;
        itemNumber++;
    }
    printf("|--------|----------------------|------------|-----------|\n");
}

struct OrderItem* createOrderItemNode(char name[], float pricePerUnit, int quantity, char customerName[])
{
    struct OrderItem* newItem = (struct OrderItem*)malloc(sizeof(struct OrderItem));
    if (newItem != NULL)
    {
        strcpy(newItem->name, name);
        strcpy(newItem->customerName, customerName);
        newItem->price = pricePerUnit * quantity;
        newItem->quantity = quantity;
        newItem->next = NULL;
    }
    return newItem;
}

int placeOrder(struct FoodItem** menu, struct OrderItem** order, const char name[], int quantity, char customerName[])
{
    struct FoodItem* current = *menu;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            if (current->quantity >= quantity)
            {
                struct OrderItem* orderItem = createOrderItemNode(name, current->price, quantity, customerName);
                orderItem->next = *order;
                *order = orderItem;

                current->quantity -= quantity;

                printf("Order placed successfully for %s!\n", customerName);
                return 1;
            }
            else
            {
                printf("Insufficient quantity in stock!\n");
                return 0;
            }
        }
        current = current->next;
    }
    printf("Food item not found!\n");
    return 0;
}

void displayOrderSummary(struct OrderItem* order)
{
    printf("======================================================================================\n");
    printf("|                      O r d e r   S u m m a r y                     |\n");
    printf("======================================================================================\n");

    if (order == NULL)
    {
        printf("|                      No Order items found!                        |\n");
    }
    else
    {
        printf("| %-23s | %-32s | %-10s | %-8s |\n", "Customer Name", "Item Name", "Price ($)", "Quantity");
        printf("------------------------------------------------------------------------------------\n");

        struct OrderItem* current = order;
        while (current != NULL)
        {
            printf("| %-23s | %-32s | $%-9.2f | %-8d |\n", current->customerName, current->name, current->price, current->quantity);
            current = current->next;
        }
    }

    printf("======================================================================================\n");

}


void showtotal(struct OrderItem* order)
{
    printf("Total Sale: ");
    struct OrderItem* current = order;
    double total = 0;
    while (current != NULL)
    {
        total += current->price;
        current = current->next;
    }

    printf("$%.2f\n", total);
}

float getPriceByName(struct FoodItem* menu,char name[])
{
    struct FoodItem* current = menu;
    while (current != NULL)
    {
        if (strcmp(current->name, name) == 0)
        {
            return current->price;
        }
        current = current->next;
    }
    return 0.0;
    
struct FoodItem* loadMenuFromFile()
{
    struct FoodItem* head = NULL;
    FILE* file = fopen("menu.txt", "r");
    if (file != NULL)
    {
        char name[50];
        float price;
        int quantity;
        char customerName[100];
        while (fscanf(file, "%s %f %d\n", name, &price, &quantity) == 3)
        {
            struct FoodItem* newItem = createFoodItemNode(name, price, quantity);
            if (newItem != NULL)
            {
                newItem->next = head;
                head = newItem;
            }
        }
        fclose(file);

    }
    else
    {
        printf("Menu file not found. Starting with an empty menu.\n");
    }
    return head;
}
    
void saveMenuToFile(struct FoodItem* head)
{
    FILE* file = fopen("menu.txt", "w");
    if (file != NULL)
    {
        struct FoodItem* current = head;
        while (current != NULL)
        {
            fprintf(file, "%s %.2f %d\n", current->name, current->price, current->quantity);
            current = current->next;
        }
        fclose(file);

    }
    else
    {
        printf("Error: Unable to save menu items.\n");
    }
}

void deleteItemFromFile(const char* itemName)
{
    FILE* file = fopen("menu.txt", "r");
    if (file == NULL)
    {
        printf("Menu file not found.\n");
        return;
    }

    FILE* tempFile = fopen("temp_menu.txt", "w");
    if (tempFile == NULL)
    {
        printf("Error: Unable to create temporary file.\n");
        fclose(file);
        return;
    }

    char name[50];
    float price;
    int quantity;
    int itemFound = 0;

    while (fscanf(file, "%s %f %d\n", name, &price, &quantity) == 3)
    {
        if (strcmp(name, itemName) == 0)
        {
            itemFound = 1;
            continue; 
        }
        fprintf(tempFile, "%s %.2f %d\n", name, price, quantity);
    }

    fclose(file);
    fclose(tempFile);

    remove("menu.txt");
    rename("temp_menu.txt", "menu.txt");

    if (itemFound)
    {
        printf("Item \"%s\" deleted from the menu.\n", itemName);
    }
    else
    {
        printf("Item \"%s\" not found in the menu.\n", itemName);
    }
}

struct StackNode* createStackNode(char customerName[],struct OrderItem* orderInfo)
{
    int tableNumber =  rand() % 10 + 1;

    struct StackNode* newNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (newNode != NULL)
    {
        newNode->tableNumber = tableNumber;
        strcpy(newNode->customerName, customerName);
        newNode->orderInfo = orderInfo;
        newNode->next = NULL;
    }
    return newNode;
}

void push(struct StackNode **top,char customerName[], struct OrderItem* orderInfo)
{
    struct StackNode* newNode = createStackNode(customerName, orderInfo);
    if (newNode != NULL)
    {
        newNode->next = *top;
        *top = newNode;
    }

}

struct StackNode* pop(struct StackNode **top)
{
    if (*top == NULL)
    {
        printf("Stack is empty.\n");
        return NULL;
    }

    struct StackNode* temp = *top;
    *top = (*top)->next;
    free(temp);

    return temp;
}
void displaystack(struct StackNode* top)
{
    if(top != NULL)
    {
        printf("\n=================================================\n");
        printf("| %-15s | %-15s |\n", "Table Number", "Customer Name\n");
        printf("==================================================\n");

        while (top != NULL)
        {
            printf("| %-15d | %-15s |\n", top->tableNumber, top->customerName);
            top = top->next;
        }

        printf("==================================================\n");
    }
    else
    {
        printf("=================================================\n");
        printf("                        No Data In stack           \n");
        printf("=================================================\n");
    }
}

void clearStack(struct StackNode **top)
{
    while (*top != NULL)
    {
        struct StackNode *temp = *top;
        *top = (*top)->next;
        free(temp);
    }

    printf("Stack cleared successfully.\n");
}

struct OrderQueueNode* createOrderQueueNode(struct FoodItem* data)
{
    struct OrderQueueNode* newNode = (struct OrderQueueNode*)malloc(sizeof(struct OrderQueueNode));
    if (newNode != NULL)
    {
        newNode->data = data;
        newNode->next = NULL;
    }
    return newNode;
}

int isOrderQueueEmpty(struct OrderQueue* orderQueue)
{
    return front == NULL;
}

void enqueueOrder(struct OrderQueueNode** front, struct OrderQueueNode** rear, struct OrderItem* data)
{
    struct OrderQueueNode* newNode = createOrderQueueNode(data);
    if (newNode != NULL)
    {
        if (*front == NULL)
        {
            *front = *rear = newNode;
        }
        else
        {
            (*rear)->next = newNode;
            *rear = newNode;
        }
    }
}

struct OrderQueueNode* dequeueOrder(struct OrderQueueNode** front)
{
    if (*front == NULL)
    {
        printf("Order Queue is empty.\n");
        return NULL;
    }

    struct OrderQueueNode* temp = *front;
    *front = (*front)->next;

    printf("\n=============================================================\n");
    printf("Processing order: %s - Quantity: %d - Customer: %s\n", temp->data->name, temp->data->quantity, temp->data->customerName);
    fflush(stdout); 

    for (int i = 0; i < 25; ++i)
    {
        printf(".");
        fflush(stdout);
        usleep(50000);
    }

    printf("\n");

    printf("Order processed: %s - Quantity: %d - Customer: %s\n", temp->data->name, temp->data->quantity, temp->data->customerName);

    free(temp->data);
    free(temp);

    return temp;
}

void displayOrderQueue(struct OrderQueueNode** front)
{
    if (*front != NULL)
    {
        printf("=========================================================================================================\n");
        printf("| %-5s | %-20s | %-30s | %-10s | %-20s |\n", "S.No.", "Customer Name", "Item Name", "Quantity", "Price");
        printf("=========================================================================================================\n");

        struct OrderQueueNode* current = *front;
        int serialNumber = 1;
        while (current != NULL)
        {
            printf("| %-5d | %-20s | %-30s | %-10d | $%-20.2f |\n", serialNumber, current->data->customerName, current->data->name, current->data->quantity, current->data->price);
            current = current->next;
            serialNumber++;
        }

        printf("=========================================================================================================\n");
    }
    else
    {
        printf("=========================================================================================================\n");
        printf(" No Order queue\n");
        printf("=========================================================================================================\n");
    }
}

void freeMenuAndOrder(struct FoodItem* menu, struct OrderItem* order)
{
    while (menu != NULL)
    {
        struct FoodItem* tempMenu = menu;
        menu = menu->next;
        free(tempMenu);
    }

    while (order != NULL)
    {
        struct OrderItem* tempOrder = order;
        order = order->next;
        free(tempOrder);
    }
}

int main()
{
    struct FoodItem* menu = NULL;
    struct OrderItem* order = NULL;
    struct OrderQueueNode* orderQueue = NULL;
    struct StackNode* top = NULL;

a:
    menu = loadMenuFromFile();
    printf("Welcome to Cafeteria Management System\n");
    int choice;
    char itemName[50];
    float itemPrice;
    int itemQuantity;
    char customerName[100];
    char editItemName[50];
    int isAuthenticated = 0;

    do
    {
        printf("\n1. Display Menu\n");
        printf("2. Place Order\n");
        printf("3. Display Order Queue\n");
        printf("4. Admin Login\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayMenu(menu);
            break;
        case 2:
            printf("Enter your name: ");
            scanf("%s", customerName);
            printf("Enter item name to order: ");
            scanf("%s", itemName);
            printf("Enter quantity to order: ");
            scanf("%d", &itemQuantity);
            if(placeOrder(&menu, &order, itemName, itemQuantity, customerName) == 1)
            {
                itemPrice = getPriceByName(menu, itemName);

                struct FoodItem* orderedItem = createFoodItemNode(itemName, itemPrice, itemQuantity);
                enqueueOrder(&front, &rear, createOrderItemNode(itemName, itemPrice, itemQuantity, customerName));
                push(&top,customerName,createOrderItemNode(itemName, itemPrice, itemQuantity, customerName));

            }

            break;
        case 3:
            displayOrderQueue(&front);
            break;
        case 4:
            isAuthenticated = authenticate(&admin);
            break;
        case 5:
            goto b;
            break;
        default:
            printf("Invalid choice.\n");

        }

        if (isAuthenticated)


        {
            do
            {
                printf("\nCafeteria Management System\n");
                printf("Enter your choice: \n");
                printf("1. Add Food Item\n");
                printf("2. Edit Food Item\n");
                printf("3. Delete Food Item\n");
                printf("4. Place Order\n");
                printf("5. Display Menu\n");
                printf("6. Display Order Summary\n");
                printf("7. Display stack\n");
                printf("8. Display Order queue\n");
                printf("9. Process one Order \n");
                printf("10. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch (choice)
                {
                case 1:
                    printf("Enter item name: ");
                    scanf("%s", itemName);
                    printf("Enter item price: ");
                    scanf("%f", &itemPrice);
                    printf("Enter item quantity: ");
                    scanf("%d", &itemQuantity);
                    addFoodItem(&menu, itemName, itemPrice, itemQuantity);
                    break;
                case 2:
                    printf("Enter the name of the item to edit: ");
                    scanf("%s", editItemName);
                    editFoodItem(&menu, editItemName);
                    break;
                case 3:
                    printf("Enter item name to delete: ");
                    scanf("%s", itemName);
                    deleteItemFromFile(itemName);
                    deleteFoodItem(&menu, itemName);
                    break;
                case 4:
                    printf("Enter customer's name: ");
                    scanf("%s", customerName);
                    printf("Enter item name to order: ");
                    scanf("%s", itemName);
                    printf("Enter quantity to order: ");
                    scanf("%d", &itemQuantity);
                    if(placeOrder(&menu, &order, itemName, itemQuantity, customerName) == 1)
                    {
                        itemPrice = getPriceByName(menu, itemName);

                        struct FoodItem* orderedItem = createFoodItemNode(itemName, itemPrice, itemQuantity);
                        enqueueOrder(&front, &rear, createOrderItemNode(itemName, itemPrice, itemQuantity, customerName));
                        push(&top,customerName,createOrderItemNode(itemName, itemPrice, itemQuantity, customerName));

                    }

                    break;
                case 5:
                    displayMenu(menu);
                    break;
                case 6:
                    displayOrderSummary(order);
                    showtotal(order);
                    break;

                case 7:
                    displaystack(top);
                    break;
                case 8:
                    displayOrderQueue(&front);
                    break;
                case 9:
                    if (!isOrderQueueEmpty(&front))
                    {
                        dequeueOrder(&front);

                    }
                    else
                    {
                        printf("Order Queue is empty. No orders to process.\n");
                    }
                    break;
                case 10:
                    saveMenuToFile(menu);
                    goto a;
                    break;



                default:
                    printf("Invalid choice! Please enter a valid option.\n");
                }
            }
            while (choice != 11);
        }
    }
    while (choice != 5);
b:
    freeMenuAndOrder(menu, order);
    menu = NULL;
    order = NULL;

    while (front != NULL)
    {
        struct OrderQueueNode* temp = front;
        front = (front)->next;
        free(temp->data);
        free(temp);
    }

    while (top != NULL)
    {
        struct StackNode* temp = top;
        top = top->next;
        free(temp->orderInfo);
        free(temp);
    }

    printf("\nThank you for using Cafeteria Management System!\n");
    return 0;
}