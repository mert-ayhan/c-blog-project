#include <stdio.h>

void BilgiOku(FILE *fp,char str[],char *_str) {
	char s[32];
	while(!feof(fp)) {
		fscanf(fp,"%s",s);
		if(strcmp(s,str)) {
			fscanf(fp,"%s",s);
			sprintf(_str,"%s",s);
		}
	}
}

void SifreKontrol(char kadi[],char ksifre[]) {
	if(!strcmp(kadi,"admin") && !strcmp(ksifre,sifre)) {
		printf("\nBasariyla giris yaptiniz!");
		return;
	}
	printf("Hatali kullanici adi veya sifre girdiniz!");
	exit(1);
}
