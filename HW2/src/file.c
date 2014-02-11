#include "crypt.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void processNewLine(char *str){
	char *sub;
	sub = strstr(str, "\n");
	if(sub!=NULL)
		*sub = 0;
	sub = strstr(str, "\r");
	if(sub!=NULL)
		*sub = 0;
}

void Find(char *dest){
	FILE *fin;
	char f[1000], tmp[1000], *sub, encrypt[2000], cmd[100];
	// ls ./src -R > list.tmp
	strcpy(cmd, "ls ");
	strcat(cmd, dest); 
	strcat(cmd, " -R > list.tmp");
	system(cmd);

	fin = fopen("list.tmp", "r");
	while(fgets(tmp, 999, fin)!=NULL){
		processNewLine(tmp);
		sub = strstr(tmp, dest);
		if(sub!=NULL){
			strcpy(f, tmp);
			sub = strstr(f, ":");
			*sub = '/';
			*(sub+1) = 0;
		}
		else{
			sub = strstr(tmp, ".txt");
			if(sub!=NULL){
				strcpy(encrypt, f);
				strcat(encrypt, tmp);
				Encrypt(encrypt);

				// rm xxx/xx/x/xxx.txt
				strcpy(cmd, "rm ");
				strcat(cmd, f);
				strcat(cmd, tmp);
				system(cmd);
			}
		}
	}
	system("rm list.tmp");
}

void Copy(char* src, char* dest){
	char cmd[100];

	//check Exist
	strcpy(cmd, "rm -rf ");
	strcat(cmd, dest);
	system(cmd);


	//copy
	strcpy(cmd, "cp -rf ");
	strcat(cmd, src);
	strcat(cmd, " ");
	strcat(cmd, dest);
	system(cmd);

	Find(dest);

}

