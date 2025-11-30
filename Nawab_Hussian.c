#include <stdio.h>
#include <string.h>

struct Donor {
    int id;
    char name[50];
    char bloodGroup[5];
    int age;
};

void addDonor(struct Donor donors[], int *count) {
    printf("\nEnter Donor ID: ");
    scanf("%d", &donors[*count].id);

    printf("Enter Donor Name: ");
    scanf("%s", donors[*count].name);

    printf("Enter Blood Group: ");
    scanf("%s", donors[*count].bloodGroup);

    printf("Enter Age: ");
    scanf("%d", &donors[*count].age);

    (*count)++;
    printf("\nDonor added successfully!\n");
}

void searchByBloodGroup(struct Donor donors[], int count) {
    char bg[5];
    int found = 0;

    printf("\nEnter Blood Group to search: ");
    scanf("%s", bg);

    printf("\nDonors with blood group %s:\n", bg);

    for (int i = 0; i < count; i++) {
        if (strcmp(donors[i].bloodGroup, bg) == 0) {
            printf("ID: %d | Name: %s | Age: %d\n",
                   donors[i].id, donors[i].name, donors[i].age);
            found = 1;
        }
    }

    if (!found) {
        printf("No donor found with this blood group.\n");
    }
}

void displayDonors(struct Donor donors[], int count) {
    printf("\n--- All Donor Records ---\n");

    if (count == 0) {
        printf("No records available.\n");
        return;
    }

    for (int i = 0; i < count; i++) {
        printf("ID: %d | Name: %s | Blood Group: %s | Age: %d\n",
               donors[i].id, donors[i].name, donors[i].bloodGroup, donors[i].age);
    }
}

void deleteDonor(struct Donor donors[], int *count) {
    int id, found = 0;
    printf("\nEnter ID to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < *count; i++) {
        if (donors[i].id == id) {
            found = 1;
            for (int j = i; j < *count - 1; j++) {
                donors[j] = donors[j + 1];
            }
            (*count)--;
            printf("Record deleted successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("No record found with this ID.\n");
    }
}

int main() {
    struct Donor donors[100];
    int count = 0;
    int choice;

    while (1) {
        printf("\n===== Blood Group Management System =====\n");
        printf("1. Add Donor\n");
        printf("2. Search Donor by Blood Group\n");
        printf("3. Display All Donors\n");
        printf("4. Delete Donor by ID\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addDonor(donors, &count);
            break;
        case 2:
            searchByBloodGroup(donors, count);
            break;
        case 3:
            displayDonors(donors, count);
            break;
        case 4:
            deleteDonor(donors, &count);
            break;
        case 5:
            printf("Exiting...");
            return 0;
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
}
