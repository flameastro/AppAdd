#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUANTITY 16

#define BOLD "\x1b[1m"
#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define PURPLE "\x1b[34m"
#define RESET "\x1b[0m"

int length = 0;

void get_app_images(char app_images[QUANTITY][64]) {
    system("wget -q -nd https://github.com/flameastro/appImages/raw/main/files.txt");
    FILE *file = fopen("files.txt", "r");

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // remove \n
        strcpy(app_images[length], buffer);
        length++;
    }

    fclose(file);

    system("rm files.txt");
}

int main(int argc, char *argv[]) {
    char appimages[QUANTITY][64];

    if ((argc == 1) || (strcmp(argv[1], "help") == 0)) {
        printf(GREEN "help - get all the available commands" RESET "\n");
        printf(GREEN "list - list all available appImages to download" RESET "\n");
        printf(GREEN "install - install a specific appImage" RESET "\n");
        printf(GREEN "uninstall - uninstall a specific appImage" RESET "\n");
        exit(0);
    }

    if (strcmp(argv[1], "list") == 0) {
        printf(GREEN "Listing all the available App Image files..." RESET "\n");
        get_app_images(appimages);

        for (int i = 0; i < length; i++) {
            printf(BOLD PURPLE "%s" RESET "\n", appimages[i]);
        }

        exit(0);
    }

    if (strcmp(argv[1], "install") == 0) {
        if (argc == 2) {
            printf(RED "Cant install any appImage." RESET "\n");
            exit(1);
        }

        get_app_images(appimages); // update appimages variable

        for (int i = 2; i < argc; i++) {
            char appimage[64] = "";
            strcpy(appimage, argv[i]);

            int found = 0;
            for (int j = 0; j < length; j++) {
                if (strcmp(appimage, appimages[j]) == 0) {
                    found = 1;
                    break;
                }
            }

            if (found == 1) {
                char command[256] = "";
                snprintf(command, sizeof(command),
                         "wget -q -O %s.AppImage https://github.com/flameastro/appImages/raw/main/apps/%s.AppImage",
                         appimage, appimage);

                char path[128];
                snprintf(path, sizeof(path), "[ -f '%s/Downloads/%s.AppImage' ]", getenv("HOME"), appimage);

                int exists = system(path);
                if (exists == 0) {
                    printf(RED "The %s.AppImage file already exists in " PURPLE "Downloads" RED " folder" RESET "\n",
                           appimage);
                } else {
                    printf(GREEN "Downloading it..." RESET "\n");

                    system(command);
                    snprintf(command, sizeof(command), "mv %s.AppImage ~/Downloads\n", appimage);
                    system(command);

                    printf(GREEN "Located at " BOLD "~/Downloads/%s.AppImage" RESET "\n", appimage);
                }

            } else {
                printf(RED "Cant find any appImage." RESET "\n");
            }
        }

        exit(0);
    }

    if (strcmp(argv[1], "uninstall") == 0) {
        if (argc == 2) {
            printf(RED "Cant uninstall any appImage." RESET "\n");
            exit(1);
        }

        get_app_images(appimages);

        for (int i = 2; i < argc; i++) {
            char appimage[64] = "";
            strcpy(appimage, argv[i]);

            int found = 0;
            for (int j = 0; j < length; j++) {
                if (strcmp(appimage, appimages[j]) == 0) {
                    found = 1;
                    break;
                }
            }

            if (found == 1) {
                char command[128] = "";

                snprintf(command, sizeof(command), "rm ~/Downloads/%s.AppImage 2>/dev/null", appimage);
                int res = system(command);

                if (res == 0) {
                    printf(GREEN "AppImage was uninstalled successfully!" RESET "\n");
                } else {
                    printf(RED "File does not exists" RESET "\n");
                }
            } else {
                printf(RED "AppImage file not found" RESET "\n");
            }
        }

        exit(0);
    }

    printf(RED "Command not found. Try again." RESET "\n");
    exit(1);

    return 0;
}
