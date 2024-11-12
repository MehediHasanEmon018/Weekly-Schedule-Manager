

#include <stdio.h>
#include <string.h>

#define MAX_DAYS 7
#define MAX_SUBJECTS 10
#define MAX_NAME_LENGTH 50
#define MAX_TIME_LENGTH 10

char subjects[MAX_DAYS * MAX_SUBJECTS][MAX_NAME_LENGTH];  // Array to store subject names
char times[MAX_DAYS * MAX_SUBJECTS][MAX_TIME_LENGTH];     // Array to store subject times
int subject_count[MAX_DAYS] = {0};                        // Array to keep track of number of subjects per day

// Function to get the index in the array based on day and slot
int get_index(int day, int slot) {
    return (day - 1) * MAX_SUBJECTS + slot;
}

// Add a subject to a specific day
void add_subject(int day) {
    int day_index = day - 1;
    if (subject_count[day_index] >= MAX_SUBJECTS) {
        printf("Cannot add more subjects; the day is full!\n");
        return;
    }

    int index = get_index(day, subject_count[day_index]);
    printf("Enter subject name (no spaces): ");
    scanf("%s", subjects[index]); // Store subject name in subjects array

    printf("Enter time (e.g., 10:30AM): ");
    scanf("%s", times[index]); // Store time in times array

    subject_count[day_index]++;
    printf("Subject added successfully!\n");
}

// Display the schedule for a specific day
void display_day_schedule(int day) {
    int day_index = day - 1;
    if (subject_count[day_index] == 0) {
        printf("  No subjects scheduled for this day.\n");
        return;
    }

    printf("\n========= Day %d Schedule =========\n", day);
    for (int i = 0; i < subject_count[day_index]; i++) {
        int index = get_index(day, i);
        printf("Subject %d: %-15s | Time: %s\n", i + 1, subjects[index], times[index]);
    }
    printf("===================================\n");
}

// Display the weekly schedule
void display_weekly_schedule() {
    for (int i = 0; i < MAX_DAYS; i++) {
        display_day_schedule(i + 1);
    }
}

// Edit an existing subject
void edit_subject(int day) {
    int day_index = day - 1;
    int subject_num;

    display_day_schedule(day);
    if (subject_count[day_index] == 0) return;

    printf("Enter the subject number to edit: ");
    scanf("%d", &subject_num);

    if (subject_num < 1 || subject_num > subject_count[day_index]) {
        printf("Invalid subject number!\n");
        return;
    }

    int index = get_index(day, subject_num - 1);

    printf("Enter new subject name (no spaces): ");
    scanf("%s", subjects[index]); // Update subject name in subjects array

    printf("Enter new time: ");
    scanf("%s", times[index]); // Update time in times array

    printf("Subject updated successfully!\n");
}

// Delete a subject from a specific day
void delete_subject(int day) {
    int day_index = day - 1;
    int subject_num;

    display_day_schedule(day);
    if (subject_count[day_index] == 0) return;

    printf("Enter the subject number to delete: ");
    scanf("%d", &subject_num);

    if (subject_num < 1 || subject_num > subject_count[day_index]) {
        printf("Invalid subject number!\n");
        return;
    }

    int index = get_index(day, subject_num - 1);

    // Shift remaining subjects up to "delete" the chosen one
    for (int i = index; i < get_index(day, subject_count[day_index] - 1); i++) {
        strcpy(subjects[i], subjects[i + 1]);
        strcpy(times[i], times[i + 1]);
    }

    subject_count[day_index]--;
    printf("Subject deleted successfully!\n");
}

// Display the menu options
void display_menu() {
    printf("\n===================================\n");
    printf("       WEEKLY SCHEDULE MANAGER\n");
    printf("===================================\n");
    printf("1 - Add Subject to Day\n");
    printf("2 - Edit Subject\n");
    printf("3 - Delete Subject\n");
    printf("4 - Display Entire Weekly Schedule\n");
    printf("5 - Display Specific Day's Schedule\n");
    printf("6 - Exit\n");
    printf("===================================\n");
    printf("Enter your choice (1-6): ");
}

int main() {
    int choice, day;

    while (1) {
        display_menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the day number (1-7): ");
                scanf("%d", &day);
                if (day < 1 || day > 7) {
                    printf("Invalid day number!\n");
                } else {
                    add_subject(day);
                }
                break;
            case 2:
                printf("Enter the day number (1-7): ");
                scanf("%d", &day);
                if (day >= 1 && day <= 7) {
                    edit_subject(day);
                } else {
                    printf("Invalid day number!\n");
                }
                break;
            case 3:
                printf("Enter the day number (1-7): ");
                scanf("%d", &day);
                if (day >= 1 && day <= 7) {
                    delete_subject(day);
                } else {
                    printf("Invalid day number!\n");
                }
                break;
            case 4:
                display_weekly_schedule();
                break;
            case 5:
                printf("Enter the day number (1-7): ");
                scanf("%d", &day);
                if (day >= 1 && day <= 7) {
                    display_day_schedule(day);
                } else {
                    printf("Invalid day number!\n");
                }
                break;
            case 6:
                printf("Exiting... Have a great day!\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    }
}
