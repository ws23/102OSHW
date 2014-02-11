#include "crypt.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void copyFile(char *src, char *dest){
	FILE *fin,*fout;
	char ch;
	fin = fopen(src, "rb");
	fout = fopen(dest, "wb");
	while(fread(&ch, sizeof(char), 1, fin) != 0)
		fwrite(&ch, sizeof(char), 1, fout);
	fclose(fin);
	fclose(fout);
}

void createDir(char *path){
	mkdir(path, 0764);	
}

void findDir(char *src, char *dest){
	DIR *dir, *dir2;
	struct dirent *ptr, *ptr2;
	char srcPathName[256], destPathName[256], *tmp, oridestPathName[256];
	dir = opendir(src);
	while((ptr = readdir(dir))!=NULL){
		if(strcmp(ptr->d_name, ".")==0 || strcmp(ptr->d_name, "..")==0)
			continue;
		sprintf(srcPathName, "%s/%s", src, ptr->d_name);
		sprintf(destPathName, "%s/%s", dest, ptr->d_name);
		dir2 = opendir(srcPathName);
		if(dir2==NULL){ // file
			copyFile(srcPathName, destPathName);
			tmp = strstr(destPathName, ".txt\0");
			if(tmp!=NULL){	
				strcpy(oridestPathName, destPathName);
				Encrypt(destPathName);
				remove(oridestPathName);
			}
				printf("createFile %s\n", destPathName);
		}
		else{ // dir
			createDir(destPathName);
			printf("createDir %s\n", destPathName);
			findDir(srcPathName, destPathName);
		}
	}
	closedir(dir);
}

void removeDir(char *path){
	DIR *dir, *dir2;
	struct dirent *ptr, *ptr2;
	char pathName[256];
	dir = opendir(path);
	while((ptr = readdir(dir))!=NULL){
		if(strcmp(ptr->d_name, ".")==0 || strcmp(ptr->d_name, "..")==0)
			continue;
		sprintf(pathName, "%s/%s", path, ptr->d_name);
		dir2 = opendir(pathName);
		if(dir2==NULL){ // FILE
			remove(pathName);
			printf("removeFile %s\n", pathName);
		}
		else{ // dir
			removeDir(pathName);
			remove(pathName);
			printf("removeDir %s\n", pathName);
		}
		closedir(dir2);
	}
	closedir(dir);
}

void Copy(char *src, char *dest){
	DIR *dir;
	struct dirent *ptr;
	char cmd = 0;
	dir = opendir(dest);
	if(dir==NULL)
		createDir(dest);
	else{
		while(1){
			printf("%s is exist, do you want to continue?\n[Y]/N >", dest);
			cmd = getchar();
			if(cmd=='Y' || cmd=='y' || cmd=='N' || cmd=='n')
				break;
		}
		if(cmd!='N' && cmd!='n')
			removeDir(dest);
	}
	if(cmd!='N' && cmd!='n'){
		findDir(src, dest);
		closedir(dir);
	}
}

