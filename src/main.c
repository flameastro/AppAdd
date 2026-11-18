#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (strcmp(argv[1], "help") == 0) {
        printf("list - list all available appImages to download\n");
        printf("install - install a specific appImage\n");
    }

    if (strcmp(argv[1], "list") == 0) {
        // get appImages list
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
            system("wget -q https://github.com/flameastro/appImages/raw/main/apps/Flameshot-14.0.0.x86_64.AppImage");
        } else if (strcmp(argv[2], "audacity") == 0) {
            system(
                "wget -q https://github.com/flameastro/appImages/raw/main/apps/audacity-linux-4.0.2-x86_64.AppImage");
        }
    }

    return 0;
}
