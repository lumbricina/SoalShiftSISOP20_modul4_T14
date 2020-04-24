#define FUSE_USE_VERSION 28
#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <errno.h>
#include <sys/time.h>

//nomer 1
static  const  char *dirpath = "/mnt/d";
char key[100] = "9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";

// Enkripsi . . . sepertinya
void enkripsi (char str[1000]) {
	int x, y;

	for (x = 0; x < strlen(str) && str[x] != '\0'; x++) {
		for (y = 0; y < strlen(key) && str[y] != '\0'; y++) {
			if(str[x] == key[y]) { str[x] = key[(y+10)%strlen(key)];
				break;
 			}
		}
	}
	printf("hasil enkrip : %s\n", str);

}

//enkripsi nama filenya . . . sepertinya
static int enfile (const char *path, void *buf, fuse_fill_dir_t filler,off_t offset, struct fuse_file_info *fi) {
    int path[1000];

    DIR *dp;
    struct dirent *de;

    (void) offset;
    (void) fi;

    dp = opendir(path);
    if (dp == NULL) 
    return -errno;

    while ((de = readdir(dp)) != NULL) {
        struct stat st;
        memset(&st, 0, sizeof(st));

        char namafile[1000];
        strcpy(namafile, de->d_name);

        if (strcmp(".", de->d_name) != 0 && strcmp("..", de->d_name) != 0 && de->d_type == 4){
            char folder[101]; //entah mengapa kalau 100 errornya nambah
            sprintf(folder, "%s/%s", path, namafile);
            enfile(folder);
            enkripsi(namafile); //enkripsi nama filenya
            printf("folder : %s\n", namafile);
        }
        
        if (de->d_type == 8) {
		
            enkripsi(namafile);
            printf("file : %s\n", namafile);
        }
            

    }

    closedir(dp);
    return 0;

}

//ga tau dah mas, ga kuat
//susah amat
