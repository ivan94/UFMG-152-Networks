#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(int argc, char const *argv[]) {
    if(argc != 4){
        printf("Usage: %s <folder> <number_of_files> <max_filename_size>\n", argv[0]);
    }

    srand(time(NULL));

    int n = atoi(argv[2]);
    int maxsize = atoi(argv[3]);

    char filename[maxsize+1];
    for(; n>0; n--){
        int namesize = maxsize, i;
        for(i = 0; i<namesize; i++){
            filename[i] = (rand()%26)+'a';
        }
        filename[i] = '\0';

        printf("%d\n", namesize);

        char fullfilename[maxsize+100];
        strcpy(fullfilename, argv[1]);
        strcat(fullfilename, filename);

        FILE* f = fopen(fullfilename, "w");
        // fprintf(f, "a\n");
        fclose(f);
        // printf("%s\n", fullfilename);
    }

    return 0;
}
