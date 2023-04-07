#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void open_program(const char* program) {
    char* command = malloc(strlen(program) + 20);
    sprintf(command, "./%s", program);
    system(command);
    free(command);
}

int main() {
    srand(time(NULL)); // seed the random number generator

    int serial_fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (serial_fd < 0) {
        perror("Failed to open serial port");
        return 1;
    }

    struct termios options;
    tcgetattr(serial_fd, &options);
    cfsetispeed(&options, B9600);
    cfsetospeed(&options, B9600);
    options.c_cflag |= (CLOCAL | CREAD);
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_oflag &= ~OPOST;
    tcsetattr(serial_fd, TCSANOW, &options);

    while (1) {
        char buffer[1024];
        int len = read(serial_fd, buffer, sizeof(buffer));
        if (len > 0) {
            buffer[len] = '\0';
            printf("%s", buffer);
            fflush(stdout);

            if (strstr(buffer, "work_mode") != NULL) {
                // Open work mode program
                open_program("work_mode");
            } else if (strstr(buffer, "chill_mode") != NULL) {
                // Open chill mode program
                open_program("chill_mode");
            } else if (strstr(buffer, "DANGER") != NULL) {
                // Open danger mode program
                open_program("danger_mode");
            }
        }
    }

    close(serial_fd);
    return 0;
}

