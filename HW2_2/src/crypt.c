#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* encrypt(char* str){
	char *s = str;
	while(*s){
		(*s) += 3;
		s++;
	}
	return str;
}

char* decrypt(char* str){
	char *s = str;
	while(*s){
		(*s) -= 3;
		s++;
	}
	return str;
}

void Encrypt(char* file){
	int i,len,size;
	char *content, c, *tmp;
	FILE *fin, *fout;
	fin = fopen(file, "r");
	if(!fin)
		printf("%s 不存在，請確認需要進行加密的檔案位置。\n", file);
	else{
		fseek (fin, 0, SEEK_END);
		size = ftell (fin);
		fclose(fin);
		fin = fopen(file, "r");
		content = (char*)malloc(sizeof(char)*size);
		i = 0;
		while(c = fgetc(fin)){
			if(c == EOF)
				break;
			content[i++] = c;
		}
		fclose(fin);

		len = strlen(file);
		tmp = strstr(file, ".txt\0");
		if(tmp!=NULL)
			strncpy(tmp, ".cip\0", 5);
		else
			strcat(file, ".cip");
		fout = fopen(file, "w");
		encrypt(content);
		for(i=0;i<size;i++)
			fputc(content[i], fout);
		fclose(fout);
	}
}

void Decrypt(char* file){
	int i,len,size;
	char *content, c, *tmp;
	FILE *fin, *fout;
	fin = fopen(file, "r");
	if(!fin)
		printf("%s 不存在，請確認需要進行解密的檔案位置。\n", file);
	else{
		fseek (fin, 0, SEEK_END);
		size = ftell (fin);
		fclose(fin);
		fin = fopen(file, "r");
		content = (char*)malloc(sizeof(char)*size);
		i = 0;
		while(c = fgetc(fin)){
			if(c == EOF)
				break;
			content[i++] = c;
		}
		fclose(fin);

		len = strlen(file);
		tmp = strstr(file, ".cip\0");
		if(tmp!=NULL)
			strncpy(tmp, ".txt\0", 5);
		else
			strcat(file, ".txt");
		fout = fopen(file, "w");
		decrypt(content);
		for(i=0;i<size;i++)
			fputc(content[i], fout);
		fclose(fout);
	}
}

