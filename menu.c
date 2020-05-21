#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h> 

void Menu();
void BlogYaz();
void BlogGoster();
void BlogIncele(int);
void BlogDuzenleGoster();
void BlogDuzenle(int);
int isnull(char*);
void BloglariYukle();

struct blogstruct {
	char baslik[32];
	char mesaj[2048];
} blog[20];

void BloglariYukle() {
	DIR *d;
	struct dirent *dir;
	char string[32];
	d = opendir("yazilar");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			FILE *fp;
			sprintf(string,"yazilar/%s",dir->d_name);
			if(strlen(dir->d_name) > 3) {
 				if((fp = fopen(string,"r")) == NULL) {
					printf("Can not open \"%s\"",string);
					exit(1);
				}
				sprintf(string,"%s",dir->d_name);
				string[strlen(string)-4] = '\0';
				BilgiOku(fp,"baslik:",&blog[atoi(string)].baslik,0);
				BilgiOku(fp,"mesaj:",&blog[atoi(string)].mesaj,1);
				fclose(fp);
	    	}
		}
	    closedir(d);
	}
}

void Menu() {
	system("cls");
	printf("\t\tMy Blogger\n\n");
	printf("\t1-Blog Yaz\t2-Blog Duzenle\t\t99-Geri\n");
	int secim;
	scanf("%d",&secim);
	fflush (stdin);
	if(secim == 1) BlogYaz();
	else if(secim == 2) BlogDuzenleGoster();
	else main();
}

void BlogYaz() {
	system("cls");
	printf("\t\tMy Blogger\n\n");
	int id,i;
	for(i=0;i<20;i++) {
		if(isnull(blog[i].baslik))
		{
			id = i;
			break;
		}
	}
	printf("Basligi girin: ");
	gets(blog[id].baslik);
	printf("Blog icerigini girin: ");
	gets(blog[id].mesaj);
	FILE *fp;
	char dosyayolu[32];
	sprintf(dosyayolu,"yazilar/%d.txt",id);
	if((fp = fopen(dosyayolu,"w")) == NULL) {
		printf("Can not open \"%s\"",dosyayolu);
	}
	fprintf(fp,"baslik: %s\nmesaj: %s",blog[id].baslik,blog[id].mesaj);
	fclose(fp);
	printf("Blog yayinlandi!");
	setTimeout(2500);
	Menu();
}

void BlogGoster() {
	system("cls");
	printf("\t\tMy Blogger\n\n");
	int i;
	for(i=0;i<20;i++) {
		if(!isnull(blog[i].baslik))
		{
			printf("\t%d) %s",i+1,blog[i].baslik);
		}
	}
	printf("\n\n\t99) Geri\n");
	int secim;
	scanf("%d",&secim);
	fflush (stdin);
	if(secim == 99) {
		main();
		return;
	}
	BlogIncele(secim-1);
}

void BlogIncele(int id) {
	system("cls");
	printf("\t\tMy Blogger\n\n");
	printf("\tBaslik: %s\n\tMesaj: %s",blog[id].baslik,blog[id].mesaj);
	printf("\n\n\t99) Geri\n");
	int secim;
	scanf("%d",&secim);
	BlogGoster();
}

void BlogDuzenleGoster() {
	system("cls");
	printf("\t\tMy Blogger\n\n");
	int i;
	for(i=0;i<20;i++) {
		if(!isnull(blog[i].baslik))
		{
			printf("\t%d) %s",i+1,blog[i].baslik);
		}
	}
	printf("\n\t99) Geri\n");
	int secim;
	scanf("%d",&secim);
	fflush (stdin);
	if(secim == 99) {
		Menu();
		return;
	}
	BlogDuzenle(secim-1);
}

void BlogDuzenle(int id) {
	system("cls");
	printf("\t\tMy Blogger\n\n");
	printf("\tid: %d\n\tBaslik: %s\n\tMesaj: %s",id+1,blog[id].baslik,blog[id].mesaj);
	printf("\n\n\t1) Basligi duzenle\n\t2) Mesaji duzenle\n\t3) Sil\n\t99)Geri\n");
	int secim;
	scanf("%d",&secim);
	fflush (stdin);
	if(secim == 1) {
		system("cls");
		printf("\t\tMy Blogger\n\n");
		printf("\tBasligi girin: ");
		char baslik[32];
		gets(baslik);
		FILE *fp;
		char dosyayolu[16];
		sprintf(dosyayolu,"yazilar/%d.txt",id);
		if((fp = fopen(dosyayolu,"w")) == NULL) {
			printf("Can not open \"%s\"",dosyayolu);
		}
		sprintf(blog[id].baslik,"%s",baslik);
		fprintf(fp,"baslik: %s\nmesaj: %s",blog[id].baslik,blog[id].mesaj);
		fclose(fp);
		printf("Baslik duzenlendi!");
		setTimeout(2500);
	   	BlogDuzenleGoster();
	}
	else if(secim == 2) {
		system("cls");
		printf("\t\tMy Blogger\n\n");
		printf("\tMesaji girin: ");
		char mesaj[2048];
		gets(mesaj);
		FILE *fp;
		char dosyayolu[16];
		sprintf(dosyayolu,"yazilar/%d.txt",id);
		if((fp = fopen(dosyayolu,"w")) == NULL) {
			printf("Can not open \"%s\"",dosyayolu);
		}
		sprintf(blog[id].mesaj,"%s",mesaj);
		fprintf(fp,"baslik: %s\nmesaj: %s",blog[id].baslik,blog[id].mesaj);
		fclose(fp);
		printf("Mesaj duzenlendi!");
		setTimeout(2500);
	   	BlogDuzenleGoster();
	}
	else if(secim == 3) {
		char filename[16];
		sprintf(filename,"yazilar/%d.txt",id);
		sprintf(blog[id].baslik,"");
		sprintf(blog[id].mesaj,"");
		int ret = remove(filename);
	   	if(ret == 0) {
	      	printf("Blog basariyla silindi.");
	   	} else {
	      	printf("Hata! Blog silinemedi.");
	   	}
	   	setTimeout(2500);
	   	BlogDuzenleGoster();
	}
	else if(secim == 99) {
		BlogDuzenleGoster();
	}
}

int isnull(char *str) {
	if (str[0] == '\0')
	{
		return 1;
	}
	return 0;
}
