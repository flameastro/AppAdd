#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int verify_argc(int argc, int min, int max) {
    if ((argc < min) || (argc > max)) {
        return 1;
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (verify_argc(argc, 2, 3) == 1) {
        printf("Too much or too low arguments\n");
        exit(1);
    }

    if (strcmp(argv[1], "help") == 0) {
        printf("list - list all available appImages to download\n");
        printf("install - install a specific appImage\n");
        printf("uninstall - uninstall a specific appImage\n");
    }

    if (strcmp(argv[1], "list") == 0) {
        system("wget -q -nd https://github.com/flameastro/appImages/raw/main/apps/files.txt");
        FILE *file = fopen("files.txt", "r");

        char buffer[256];
        while (fgets(buffer, sizeof(buffer), file) != NULL) {
            printf("%s", buffer);
        }

        system("rm files.txt");
    }

    if (strcmp(argv[1], "install") == 0) {
        if (strcmp(argv[2], "flameshot") == 0) {
            system("wget -q https://github.com/flameastro/appImages/raw/main/apps/flameshot.AppImage");
            goto mv;
        } else if (strcmp(argv[2], "audacity") == 0) {
            system("wget -q https://github.com/flameastro/appImages/raw/main/apps/audacity.AppImage");
            goto mv;
        } else {
            printf("Cant find any appImage.\n");
            exit(1);
        }

    mv:
        system("mv *.AppImage ~/Downloads");
    }

    if (strcmp(argv[1], "uninstall") == 0) {
        char command[256];

        snprintf(command, sizeof(command), "rm ~/Downloads/%s*", argv[2]);
        system(command);
    }

    return 0;
}
