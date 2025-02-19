#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "quiz_data.txt"

struct Player {
    char name[50];
    int age;
};

void savePlayerData(struct Player player) {
    FILE *file = fopen(FILENAME, "a");
    
    fprintf(file, "Name : %s\nAge  : %d\n", player.name, player.age);
    fclose(file);
}

void readPlayerData() {
    FILE *file = fopen(FILENAME, "r");

    char line[100];
    printf("\nPlayer Data \n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void deletePlayerData() {
    if (remove(FILENAME)) {
        printf("All player data deleted successfully.\n");
    } else {
        printf("Error deleting player data\n");
    }
}

void deleteSpecificPlayer() {
    char nameDelete[50];
    printf("Enter the name of the player to delete: ");
    getchar();
    fgets(nameDelete, sizeof(nameDelete), stdin);
    nameDelete[strcspn(nameDelete, "\n")] = '\0';

    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, nameDelete) != NULL) { 
            found = 1;
            fgets(line, sizeof(line), file);
        } else {
            fputs(line, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("Player '%s' deleted successfully.\n", nameDelete);
    } else {
        printf("Player '%s' not found!\n", nameDelete);
    }
}

void updatePlayerData() {
    char nameToUpdate[50];
    printf("Enter the name of the player to update: ");
    getchar();

    fgets(nameToUpdate, sizeof(nameToUpdate), stdin);
    nameToUpdate[strcspn(nameToUpdate, "\n")] = '\0';

    FILE *file = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), file)) { 
        if (strstr(line, nameToUpdate) != NULL) {
            found = 1;
            printf("Enter new name: ");
            char newName[50];
            fgets(newName, sizeof(newName), stdin);
            newName[strcspn(newName, "\n")] = '\0';

            printf("Enter new age: ");
            int newAge;
            scanf("%d", &newAge);
            getchar();

            fprintf(temp, "Name : %s\nAge  : %d\n", newName, newAge);
            fgets(line, sizeof(line), file);
        } else {
            fputs(line, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found) {
        printf("Player '%s' updated successfully.\n", nameToUpdate);
    } else {
        printf("Player '%s' not found!\n", nameToUpdate);
    }
}

void questions(char *question, char *optionA, char *optionB, char *optionC, char *optionD, char correctAnswer) {
    char answer;
    printf("\n%s\n", question);
    printf("A. %s\nB. %s\nC. %s\nD. %s\n", optionA, optionB, optionC, optionD);
    printf("Enter your answer (A/B/C/D): ");
    scanf(" %c", &answer);
    
    if (answer == correctAnswer || answer == correctAnswer + 32) {
        printf("Correct!\n");
    } else {
        printf("Wrong! The correct answer was %c.\n", correctAnswer);
    }
}

void startQuiz(struct Player player) {
    printf("\nWelcome to the Quiz Game, %s!\n", player.name);
    questions("What is the capital of France?", "Berlin", "Madrid", "Paris", "Rome", 'C');
    questions("Which programming language is used for system programming?", "Python", "C", "Java", "Ruby", 'B');
    questions("What is 5 + 3?", "6", "7", "8", "9", 'C');
    questions("Who wrote 'Hamlet'?", "Shakespeare", "Hemingway", "Tolkien", "Austen", 'A');
    printf("\nQuiz Completed!\n");
}

void addNewPlayer() {
    struct Player player;

    printf("\nEnter your name: ");
    fgets(player.name, sizeof(player.name), stdin);

    player.name[strcspn(player.name, "\n")] = '\0';

    printf("Enter your age: ");
    scanf("%d", &player.age);
    getchar();

    savePlayerData(player);

    printf("New player data saved successfully.\n");
    startQuiz(player);
}

int main() {
    struct Player player;

    printf("Enter your name: ");
    fgets(player.name, sizeof(player.name), stdin);

    player.name[strcspn(player.name, "\n")] = '\0';

    printf("Enter your age: ");
    scanf("%d", &player.age);
    getchar();

    savePlayerData(player);
    startQuiz(player);

    int choice;

    while (1) {
        printf("\n1. View Player Data\n 2. Add New Player\n 3. Delete All Player Data\n 4. Delete Specific Player\n 5. Update Player Data\n 6. Exit\n Choose: ");
        scanf("%d", &choice);
        getchar();
        switch (choice) {
            case 1: 
            readPlayerData(); 
            break;
            
            case 2: 
            addNewPlayer(); 
            break;
            
            case 3: 
            deletePlayerData(); 
            break;

            case 4: 
            deleteSpecificPlayer(); 
            break;

            case 5: 
            updatePlayerData(); 
            break;

            case 6: 
            return 0;

            default: 
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}