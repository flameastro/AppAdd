#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUANTITY 16

int length = 0;

void get_app_images(char app_images[QUANTITY][64]) {
    system("wget -q -nd https://github.com/flameastro/appImages/raw/main/apps/files.txt");
    FILE *file = fopen("files.txt", "r");

    int i = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // remove \n
        strcpy(app_images[i], buffer);
        i++;
        length++;
    }

    system("rm files.txt");
}

int main(int argc, char *argv[]) {
    char appimages[QUANTITY][64];

    if ((argc == 1) || (strcmp(argv[1], "help") == 0)) {
        printf("help - get all the available commands\n");
        printf("list - list all available appImages to download\n");
        printf("install - install a specific appImage\n");
        printf("uninstall - uninstall a specific appImage\n");
        exit(0);
    }

    if (strcmp(argv[1], "list") == 0) {
        get_app_images(appimages);

        for (int i = 0; i < length; i++) {
            printf("%s\n", appimages[i]);
        }

        exit(0);
    }

    if (strcmp(argv[1], "install") == 0) {
        if (argc == 2) {
            printf("Cant install any appImage.\n");
            exit(1);
        }

        get_app_images(appimages); // update appimages variable

        int index = 0;
        int found = 0;
        for (int i = 0; i < length; i++) {
            if (strcmp(argv[2], appimages[i]) == 0) {
                found = 1;
                index = i;
                break;
            }
        }

        if (found == 1) { // 1 = true
            char command[256];
            snprintf(command, sizeof(command),
                     "wget -q -O %s.AppImage https://github.com/flameastro/appImages/raw/main/apps/%s.AppImage",
                     appimages[index], appimages[index]);
            system(command);

            system("mv *.AppImage ~/Downloads\n");
            printf("Located at ~/Downloads/%s.AppImage\n", appimages[index]);
            exit(0); // success
        }

        printf("Cant find any appImage.\n");
        exit(1);
    }

    if (strcmp(argv[1], "uninstall") == 0) {
        if (argc == 2) {
            printf("Cant uninstall any appImage.\n");
            exit(1);
        }

        get_app_images(appimages); // update appimages

        char appimage[64];
        strcpy(appimage, argv[2]);

        int found = 0;
        for (int i = 0; i < length; i++) {
            if (strcmp(appimage, appimages[i]) == 0) {
                found = 1;
                break;
            }
        }

        if (found == 1) {
            char command[128];

            snprintf(command, sizeof(command), "rm ~/Downloads/%s*", appimage);
            printf("%d", system(command));
            exit(0);
        }

        printf("AppImage file not found\n");
        exit(1);
    }

    return 0;
}
