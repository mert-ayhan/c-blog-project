#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char sifre[32];

void BilgiOku(FILE *,char [],char *,int);
void SifreKontrol(char [],char []);
void AdminGirisi();

void setTimeout(int milliseconds)
{
    if (milliseconds <= 0) {
        fprintf(stderr, "Count milliseconds for timeout is less or equal to 0\n");
        return;
    }
    int milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    int end = milliseconds_since + milliseconds;
    do {
        milliseconds_since = clock() * 1000 / CLOCKS_PER_SEC;
    } while (milliseconds_since <= end);
}

int main() {
	system("cls");
	printf("\t\tPrograma hosgeldiniz..\n\n");
	int secim;
	printf("\t1) Blog'a Giris");
	printf("\t\t2) Admin Girisi\t\t99) Cikis\n");
	scanf("%d",&secim);
	switch(secim) {
		case 1: {
			BlogGoster();
			break;
		}
		case 2: {
			AdminGirisi();
			break;
		}
		case 99: {
			printf("Programdan cikis yapiliyor..");
			exit(1);
			break;
		}
		default: {
			printf("Hatali secim yaptiniz, programdan cikis yapiliyor..");
			exit(1);
			break;
		}
	}
	return 0;
}

void AdminGirisi() {
	system("cls");
	FILE *fp;
	if((fp = fopen("bilgiler.txt","r")) == NULL) {
		printf("Can not open \"bilgiler.txt\"");
		exit(1);
	}
	BilgiOku(fp,"sifre:",&sifre,0);
	fclose(fp);
	printf("\t\tPrograma hosgeldiniz..\n\n");
	char kadi[32], ksifre[32];
	printf("\tKullanici adinizi girin: ");
	scanf("%s",&kadi);
	printf("\tKullanici sifrenizi girin: ");
	scanf("%s",&ksifre);
	SifreKontrol(kadi,ksifre);
}

void BilgiOku(FILE *fp,char str[],char *_str,int tip) {
	char s[2048],_s[32];
	sprintf(_s,"%s",str);
	fseek( fp, strlen(_s)+1, SEEK_SET );
	if(tip == 0) {
		fgets(s,2048,fp);
		sprintf(_str,"%s",s);
	}
	else if(tip == 1) {
		while(!feof(fp)) {
			fscanf(fp,"%s",s);
			if(!strcmp(s,str)) {
				fgets(s,2048,fp);
				sprintf(_str,"%s",s);
			}
		}
	}
}

void SifreKontrol(char kadi[],char ksifre[]) {
	if(!strcmp(kadi,"admin") && !strcmp(ksifre,sifre)) {
		printf("Basariyla giris yaptiniz!");
		setTimeout(2500);
		BloglariYukle();
		Menu();
	}
	else {
		printf("Hatali kullanici adi veya sifre girdiniz!");
		exit(1);
	}
}
