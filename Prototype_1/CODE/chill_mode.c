#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 100
#define MAX_LINKS 10

int main() {
   char command[MAX_LENGTH];
   char link[MAX_LINKS][MAX_LENGTH];
   char nickname[MAX_LINKS][MAX_LENGTH];
   int num_links = 0;
   int choice = 0;
   
   FILE *fp;
   fp = fopen("chill_mode.txt", "r");

   if(fp == NULL) {
      printf("Error: Unable to open links.txt\n");
      exit(1);
   }
   
   // Read the links and nicknames from the file
   while(fscanf(fp, "%d,%[^,],%[^\n]", &choice, link[num_links], nickname[num_links]) != EOF) {
      num_links++;
   }
   fclose(fp);
   
   // Display the menu and get the choice from the user
   printf("Choose a number:\n");
   for(int i = 0; i < num_links; i++) {
      printf("%d. %s\n", i+1, nickname[i]);
   }
   scanf("%d", &choice);

   if (choice < 1 || choice > num_links) {
      printf("Invalid choice\n");
      exit(1);
   }
   
   // Open the selected link
   snprintf(command, MAX_LENGTH, "xdg-open %s", link[choice-1]);
   system(command);
   
   // Connect to Bluetooth
    printf("Connecting to Bluetooth...\n");
    sprintf(command, "bluetoothctl connect 68:9A:87:93:8E:E4");
    system(command);

    // Set the volume to 100%
    printf("Setting the volume to 100%%...\n");
    sprintf(command, "amixer -D pulse sset Master 100%%");
    system(command);
   
   return 0;
}

