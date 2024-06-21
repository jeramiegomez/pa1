#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct window {
    int window_num;
    struct window *next;
} window;

window* open_windows(window **windows, int windowID) {
    window *new_window = (window*)malloc(sizeof(window));
    new_window->window_num = windowID;
    new_window->next = *windows;
    *windows = new_window;
    return new_window;
}

void switch_windows(window **windows, int windowID) {
    window *temp = *windows;
    window *prev = NULL;

    while (temp != NULL && temp->window_num != windowID) {
        prev = temp;
        temp = temp->next;
    }

    if (temp != NULL && prev != NULL) {
        prev->next = temp->next;
        temp->next = *windows;
        *windows = temp;
    }
}

void close_windows(window **windows, int windowID) {
    window *temp = *windows, *prev = NULL;

    if (temp != NULL && temp->window_num == windowID) {
        *windows = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->window_num != windowID) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

int main() {
    char operation[10];
    int windowID;
    window *windows = NULL;
    char input[20];

    while (1) {
        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }
        
        if (sscanf(input, "%s %d", operation, &windowID) != 2) {
            continue;
        }

        if (!strcmp(operation, "open")) {
            open_windows(&windows, windowID);
            printf("%d\n", windows->window_num);
        } else if (!strcmp(operation, "switch")) {
            switch_windows(&windows, windowID);
            if (windows != NULL) {
                printf("%d\n", windows->window_num);
            }
        } else if (!strcmp(operation, "close")) {
            close_windows(&windows, windowID);
            if (windows == NULL) {
                break;
            }
            if (windows != NULL) {
                printf("%d\n", windows->window_num);
            }
        }
    }
    return 0;
}