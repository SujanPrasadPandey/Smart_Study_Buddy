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

char *get_first_line(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(1);
    }

    char line[MAX_LINE_LENGTH];
    char *result = NULL;

    if (fgets(line, sizeof(line), file) != NULL) {
        result = malloc(strlen(line) + 1);
        strcpy(result, line);
    }

    fclose(file);

    return result;
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

    // Open the first link from pomodoro.txt
    char *pomodoro_link = get_first_line("pomodoro.txt");
    if (pomodoro_link == NULL) {
        fprintf(stderr, "Error: pomodoro.txt file is empty.\n");
        exit(1);
    }
    printf("Opening pomodoro timer website: %s", pomodoro_link);
    open_url(pomodoro_link);
    free(pomodoro_link);

    // Open the first study material link
    char *material_link = get_first_line("study_materials.txt");
    if (material_link == NULL) {
        fprintf(stderr, "Error: study materials file is empty.\n");
        exit(1);
    }
    printf("Opening study material: %s", material_link);
    open_url(material_link);
    free(material_link);

    return 0;
}

