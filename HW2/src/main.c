#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "file.h"
#include "crypt.h"

void Help();
void Error(char);

int main(int arc, char *arv[]){
	int i;
	if(arc==1)
		Error('n');
	else if(strcmp(arv[1], "-h")==0)
		Help();
	else if(strcmp(arv[1], "-e")==0){
		if(arc<=2)
			Error('a');
		for(i=2;i<arc;i++)
			Encrypt(arv[i]);
	}
	else if(strcmp(arv[1], "-d")==0){
		if(arc<=2)
			Error('a');
		for(i=2;i<arc;i++)
			Decrypt(arv[i]);
	}
	else if(strcmp(arv[1], "-c")==0){
		if(arc!=4)
			Error('a');
		else
			Copy(arv[2], arv[3]);
	}
	else
		Error('o');
	return 0;
}

void Help(){
	puts("用法：./mycopy [選項] [檔案......]");
	puts("選項：");
	puts("  -h                       檢視此輔助說明");
	puts("  -e 檔案1 [檔案2......]   檔案加密（加密後檔案將會附加副檔名.cip）");
	puts("  -d 檔案1 [檔案2......]   檔案解密（解密後檔案將會附加副檔名.txt）");
	puts("  -c 資料夾 資料夾         複製資料夾至目的");
	puts("");
	puts("                                        made by 410121021 林育慈");
}

void Error(char type){
	if(type=='a')
		puts("輸入參數數目錯誤");
	else if(type=='n')
		puts("請輸入功能選項");
	else if(type=='o')
		puts("請輸入正確的指令");
	puts("請使用 ./mycopy -h 觀看輔助說明");

}
