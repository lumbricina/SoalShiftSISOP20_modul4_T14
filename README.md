# SoalShiftSISOP20_modul4_T14

## T14
* Fancista Syarif Hidayatullah 05311840000027
* Agnes Lesmono 05311840000044


```
static  const  char *dirpath = "/mnt/d/sisop/modul 4";
char kalimat[100] = "9(ku@AW1[Lmvgax6q`5Y2Ry?+sF!^HKQiBXCUSe&0M.b%rI'7d)o4~VfZ*{#:}ETt$3J-zpc]lnh8,GwP_ND|jO";
```
kalimat yang digunakan untuk melakukan enkripsi

```
void enkripsi (char* str) {
	int x, y;
    if(!strcmp(str,".") && !strcmp(str,".."))
    return;
    
	for (x = 0; x < strlen(str); x++) {
		for (y = 0; y < strlen(kalimat); y++) {
			if(str[x] == kalimat[y]) { 
                str[x] = kalimat[(y+10)%strlen(kalimat)];
				break;
 			}
		}
	}
	printf("hasil enkrip : %s\n", str);

}
```
Pada enkripsi, setiap huruf yang digunakan akan bergeser 10 dari huruf tersebut ada di ```kalimat```. Kemudian hasil enkripsi akan di cetak. :+1:

```
void dekripsi(char* strd) {
    int x, y;
    if(!strcmp(strd,".") && !strcmp(strd,".."))
    return;

    for (x = 0; x < strlen(strd); x++){
        for (y = 0; y < strlen(kalimat); y++){
            if(strd[x] == kalimat[y]){
                strd[x] = kalimat[(y+(strlen(kalimat)-10))%strlen(kalimat)];
                break;
            
            }
        }
    }
    printf("hasil dekrip : %s\n", strd);
}
```
Pada dekripsi menggunakan cara yang sama dengan enkripsi namun kebalikannya.

```
static int xmp_getattr(const char *path, struct stat *stbuf) {
    char fpath[1000];
    char nama[1000];
    int res;

    sprintf(nama,"%s",path);
	enkripsi(nama);

	sprintf(fpath, "%s%s",dirpath,nama);
	printf("getattr custom %s\n", fpath);
	
    if (strstr(fpath, enkripsi1)){
	char yangbaru[1000];
	int len = strlen(fpath);
	strcpy(yangbaru, fpath);
	yangbaru[len - 4] = '\0';
        res = lstat(fpath, stbuf);
	}
    if (res != 0){
		return -ENOENT;
	}
	return 0;

}
```
Digunakan untuk mendapatkan nama file terenkripsi

```
static int xmp_readdir(const char *path, void *buf, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fi) {

    DIR *dp;
	struct dirent *de;

	(void) offset;
	(void) fi;

	char fpath[1000];
	char nama[1000];

	if (strcmp(path, "/") == 0) {
		sprintf(fpath, "%s", dirpath);
	} else {
		sprintf(nama,"%s",path);
		enkripsi(nama);
		sprintf(fpath, "%s%s",dirpath,nama);
	}
	dp = opendir(fpath);

	if (dp == NULL)
		return -errno;

	while ((de = readdir(dp)) != NULL) {
		struct stat st;
		memset(&st, 0, sizeof(st));
		st.st_ino = de->d_ino;
		st.st_mode = de->d_type << 12;
		if (filler(buf, de->d_name, &st, 0)) break;
	}
	closedir(dp);
	return 0;
}
```
Untuk membaca direktori dan mendapatkan nama direktori serta nama file

```
static int xmp_mkdir(const char *path, mode_t mode)
{
	int res;
	char fpath[1000];
	char nama[1000];
	
    sprintf(nama,"%s",path);
	enkripsi(nama);
	sprintf(fpath, "%s%s",dirpath,nama);
	printf("mkdir %s\n", fpath);
	
    res = mkdir(fpath, mode);

	if (res == -1)
		return -errno;

	return 0;
}
```
Untuk membuat direktori

