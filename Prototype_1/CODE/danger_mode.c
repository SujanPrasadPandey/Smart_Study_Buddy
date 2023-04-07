#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char command[256];
    char link[256];
    FILE *file;

    // Mute the PC
    printf("Setting the volume to 0%%...\n");
    snprintf(command, sizeof(command), "amixer -D pulse sset Master 0%%");
    system(command);

    // Open the first link from study_materials.txt
    file = fopen("study_materials.txt", "r");
    if (file == NULL) {
        printf("Error: study_materials.txt not found.\n");
        return 1;
    }

    if (fgets(link, sizeof(link), file) != NULL) {
        strtok(link, "\n");  // Remove newline character
        printf("Opening %s...\n", link);
        snprintf(command, sizeof(command), "xdg-open %s", link);
        system(command);
    } else {
        printf("Error: study_materials.txt is empty.\n");
        return 1;
    }

    fclose(file);
    return 0;
}

