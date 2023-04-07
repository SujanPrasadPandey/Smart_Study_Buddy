#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_LENGTH 100

char *get_random_line(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char *result = NULL;
    int count = 0;

    while (fgets(line, sizeof(line), file) != NULL) {
        if (rand() % ++count == 0) {
            // Choose the current line with probability 1/count
            free(result);
            result = malloc(strlen(line) + 1);
            strcpy(result, line);
        }
    }

    fclose(file);

    return result;
}

void open_url(char *url) {
    char command[1024];
    sprintf(command, "xdg-open %s", url);
    system(command);
}

int main() {
       char command[MAX_LENGTH];
       // Connect to Bluetooth
    printf("Connecting to Bluetooth...\n");
    sprintf(command, "bluetoothctl connect 68:9A:87:93:8E:E4");
    system(command);

    // Set the volume to 100%
    printf("Setting the volume to 100%%...\n");
    sprintf(command, "amixer -D pulse sset Master 100%%");
    system(command);
    
    // Seed the random number generator with the current time
    srand(time(NULL));

    // Open a random study music link
    char *music_link = get_random_line("study_music.txt");
    printf("Opening study music: %s", music_link);
    open_url(music_link);
    free(music_link);

    // Open the pomodoro timer website
    printf("Opening pomodoro timer website: https://pomodor.app/timer\n");
    open_url("https://pomodor.app/timer");

    // Open the first study material link
    FILE *material_file = fopen("study_materials.txt", "r");
    if (material_file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", "../txtFiles/study_materials.txt");
        exit(1);
    }

    char material_link[MAX_LINE_LENGTH];
    if (fgets(material_link, sizeof(material_link), material_file) == NULL) {
        fprintf(stderr, "Error: study materials file is empty.\n");
        exit(1);
    }

    fclose(material_file);

    printf("Opening study material: %s", material_link);
    open_url(material_link);

    return 0;
}

