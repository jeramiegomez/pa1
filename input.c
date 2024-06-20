#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 10

// Define the structure of ListNode
typedef struct ListNode {
    int value;
    struct ListNode *next; //edit
} ListNode;

// Structure to hold command and number
typedef struct {
    char *str;   // Pointer to a string for the command
    int number;  // Integer for the number
} Command;

// Function declarations
ListNode * createList(int valn);
void printList(ListNode * head);
ListNode * deleteNode(ListNode * head, int valueToDelete);
Command* create_command();
void free_command(Command *cmd);
void get_commands(Command **commands, int *command_count);
void process_commands(Command *commands, int command_count, ListNode **head);

// Function to create a linked list with values from valn-1 down to 0
ListNode * createList(int valn)
{
    ListNode * head = NULL;   // Initialize head pointer to NULL
    ListNode * temp = NULL;   // Temporary pointer to ListNode
    
    // Loop from valn - 1 down to 0
    for(int i = valn - 1; i > 0; i--)
    {
        temp = malloc(sizeof(ListNode));   // Allocate memory for a new ListNode
        
        temp->value = i;   // Set the value of the ListNode to i
        
        temp->next = head;   // Set the next pointer of temp to the current head
        
        head = temp;   // Update the head to point to temp, effectively adding temp to the start of the list
    }
    
    return head;   // Return the head pointer of the created linked list
}

// Function to print the linked list
void printList(ListNode * head)
{
    ListNode * current = head;
    while(current != NULL)
    {
        printf("%d  ", current->value);
        current = current->next;
        
    }
  //  printf("NULL\n");
  printf("\n");
}

// Function to delete a node from the linked list
ListNode * deleteNode(ListNode * head, int valueToDelete)
{
    if(head == NULL){
        return NULL;  // If the list is empty, return NULL
    }
    
    ListNode* traverse = head;  // Initialize a traversal pointer starting from the head
    
    if(traverse->value == valueToDelete){
        traverse = traverse->next;  // If the node to delete is the head node, move traverse to the next node
        free(head);  // Free the memory of the head node
        return traverse;  // Return the new head (second node after deletion)
    }
    
    while((traverse != NULL) && ((traverse->next) != NULL) && ((traverse->next->value) != valueToDelete)){
        traverse = traverse->next;  // Traverse the list until the node before the node to delete
    }
    
    if(traverse != NULL && traverse->next != NULL){
        ListNode *nodeToDelete = traverse->next;
        traverse->next = nodeToDelete->next;  // Link the previous node to the next node of the node to delete
        free(nodeToDelete);  // Free the memory of the node to delete
    }
    
    return head;  // Return the head of the updated linked list
}

// Function to allocate memory and create a Command structure
Command* create_command() {
    Command *cmd = (Command*)malloc(sizeof(Command)); // Allocate memory for Command structure
    if (cmd == NULL) { // Check if memory allocation was successful
        fprintf(stderr, "Memory allocation failed\n"); // Print error message if allocation failed
        exit(1); // Exit the program with an error code
    }

    cmd->str = (char*)malloc(MAX_COMMAND_LENGTH * sizeof(char)); // Allocate memory for the command string
    if (cmd->str == NULL) { // Check if memory allocation was successful
        fprintf(stderr, "Memory allocation failed\n"); // Print error message if allocation failed
        free(cmd); // Free the allocated memory for Command structure
        exit(1); // Exit the program with an error code
    }

    return cmd; // Return the pointer to the allocated Command structure
}

// Function to free the memory allocated for the Command structure
void free_command(Command *cmd) {
    free(cmd->str); // Free the memory allocated for the command string
    free(cmd); // Free the memory allocated for the Command structure itself
}

// Function to get user input and store commands
void get_commands(Command **commands, int *command_count) {
    int capacity = 10; // Initial capacity for the dynamic array
    *commands = (Command*)malloc(capacity * sizeof(Command)); // Allocate initial memory for the commands array
    *command_count = 0; // Initialize command count to 0

    while (1) { // Infinite loop to continuously prompt the user for input
        if (*command_count >= capacity) { // If the array is full, increase its capacity
            capacity *= 2;
            *commands = (Command*)realloc(*commands, capacity * sizeof(Command));
        }

        Command *cmd = create_command(); // Create a new command structure

        printf("Enter your command and number (open, close, switch, exit to quit): ");
        scanf("%s", cmd->str); // Read the command string from user input
        if (strcmp(cmd->str, "exit") == 0) { // Check if the command is "exit"
            free_command(cmd);
            break; // Exit the loop if the command is "exit"
        }
        scanf("%d", &(cmd->number)); // Read the number from user input

        // Store the command in the array
        (*commands)[*command_count] = *cmd;
        (*command_count)++;

        free(cmd); // Free the temporary command structure
    }
}

// Function to process commands and update the linked list
void process_commands(Command *commands, int command_count, ListNode **head) {
    for (int i = 0; i < command_count; i++) {
        if (strcmp(commands[i].str, "open") == 0) {
            // Add a node with the given number
            ListNode *newNode = (ListNode*)malloc(sizeof(ListNode));
            newNode->value = commands[i].number;
            newNode->next = *head;
            *head = newNode;
        } else if (strcmp(commands[i].str, "close") == 0) {
            // Delete a node with the given number
            *head = deleteNode(*head, commands[i].number);
        } else if (strcmp(commands[i].str, "switch") == 0) {
            // You can implement a specific action for "switch" if needed
        
            printf("Switch command received with number %d\n", commands[i].number);
        }
    }
}

int main()
{
    int valn = 1; // Example value of valn
    
    // Create a linked list with values from valn-1 down to 0
    ListNode * myList = createList(valn);
    
    // Print the created linked list
   // printf("Created linked list: ");
    //printList(myList);
    
    // Create an array to store commands
    Command *commands;
    int command_count;

    // Get command input from user
    get_commands(&commands, &command_count); // Call get_commands to continuously prompt the user for input and store commands

    // Process commands to update the linked list
    process_commands(commands, command_count, &myList);
    
    // Print the updated linked list after processing commands
    printf("Updated linked list: \n");
    printList(myList);

    // Free the allocated memory for commands
    for (int i = 0; i < command_count; i++) {
        free(commands[i].str);
    }
    free(commands);

    // Free the linked list
    while (myList != NULL) {
        ListNode *temp = myList;
        myList = myList->next;
        free(temp);
    }

    return 0;
}