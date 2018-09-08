#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
char CopyrightChar = '\xa9';
typedef struct
{
	char Ad[100];
	long int kod;
    long int numara;
} telephone;

int ara,ksay,durum=1,i, c;
char ara1[50];


FILE *kp;
telephone kayit;

// Islem fonskiyonlari...

void silme(void);
void duzenleme(void);

main()
{

    setlocale(LC_ALL,"turkis");

    kp = fopen("TelefonRehber.txt", "r+");

    if (kp == NULL)
        kp = fopen("TelefonRehber.txt", "w+");
    do
    {
        system("CLS"); // Ekraný temizler...

        printf("CopyRight%c 2017 by YusufDede YunusEmreAlcik FahrettinAksu \n\n",CopyrightChar);
        printf("\n\t\t TELEFON REHBERI v1.0");
        printf("\n\t\t***********************\n\n");
        printf("ISLEMLER\n\n");
        printf("1 - Kayit Ekle\n");
        printf("2 - Telefonlari Listele\n");
        printf("3 - Kaydi Duzenle\n");
        printf("4 - Numara ile Kayit bul\n");
        printf("5 - Isim ile Kayit Bul\n");
        printf("6 - Kayit Sil\n");
        printf("0 - Cikis\n");

        printf("\n\n\n Secim... ");
        scanf("%d",&c);


        if(c==1)
        {
            kayitEkle();
        }
        else if(c==2)
        {
            Listele();
        }
        else if(c==3)
        {
            duzenleme();
        }
        else if(c==4)
        {
            NumaraArama();
        }

        else if(c==5)
        {
            IsimArama();
        }

        else if(c==6)
        {
            silme();
        }
    }while(c != 0);
    fclose(kp);
}
void silme(void)
{
    int silno;
    char siltekrar,ch;

    printf("\nSilinecek Musteri Kodu : ");
    scanf("%d",&silno);

    fseek(kp, silno*sizeof(telephone), 0);
    fread(&kayit, sizeof(telephone), 1, kp);
    if(kayit.kod==silno)
    {
    printf("\nMusteri Kodu : %d",kayit.kod);
    printf("\nMusteri Adi : %s",kayit.Ad);
    printf("\nTelefon     : ");
    printf("%d",kayit.numara);
    printf("\nKAYIT SILINICEK!...<E/H>");
    ch=getch();
    }

    if (ch == 'E' || ch == 'e')
    {
        strcpy(kayit.Ad,"");
        kayit.numara=0.0;
        fseek(kp, silno*sizeof(kayit), 0);
        fwrite(&kayit, sizeof(kayit), 1, kp);
        printf("\nKAYIT BASARIYLA SILINDI\n\n");
    }
    else
    {
         if(kayit.kod != silno)
        {
            printf("KAYIT BULANAMADI!...");
        }
        printf("\n\nTekrar Arama Yapmak istermisiniz <E/H> ");
        siltekrar=getch();
        if(siltekrar == 'E' || siltekrar == 'e')
        {
            printf("\nSilinecek Musteri Kodu : ");
    scanf("%d",&silno);

    fseek(kp, silno*sizeof(telephone), 0);
    fread(&kayit, sizeof(telephone), 1, kp);
    if(kayit.kod==silno)
    {
    printf("\nMusteri Kodu : %d",kayit.kod);
    printf("\nMusteri Adi : %s",kayit.Ad);
    printf("\nTelefon     : ");
    printf("%d",kayit.numara);
    printf("\nKAYIT SILINICEK!...<E/H>");
    ch=getch();
        }
            if (ch == 'E' || ch == 'e')
            {
            strcpy(kayit.Ad,"");
            kayit.numara=0.0;
            fseek(kp, silno*sizeof(kayit), 0);
            fwrite(&kayit, sizeof(kayit), 1, kp);
            printf("\nKAYIT BASARIYLA SILINDI\n\n");
            }
            if(kayit.kod != silno)
            {
            printf("KAYIT BULANAMADI!...");
            }
        }

    }
    printf("\n\n Devam icin herhangi bir tusa basin");
    getch();
}
void kayitEkle()
{
        printf("\nMusteri Kodu :");
        scanf("%d",&kayit.kod);
        printf("Musteri Adi  :");
        scanf("%s",&kayit.Ad);
        printf("Telefon      :");
        scanf("%d",&kayit.numara);

        fseek(kp, kayit.kod*sizeof(telephone), 0); // Isaretciyi en basa cek SEEK_SET
        fwrite(&kayit, sizeof(telephone), 1, kp);
        fflush(kp);
        //fflush(FILE *) tampon bellektekiler diske yazilacaktir....
}
void Listele()
{
        system("CLS");//clrscr();

        fseek(kp, 0, 0);
        fread(&kayit, sizeof(telephone), 1, kp);
        printf("\nM.Kodu   Adi       Telefon\n==========================\n");
        while (!feof(kp))
        {
            if(strcmp(kayit.Ad,""))
            {
            printf("\n%ld \t %s \t   ", kayit.kod,kayit.Ad);
            printf("%ld",kayit.numara);
            }
            fread(&kayit, sizeof(telephone), 1, kp);
        }
        printf("\n\n Devam icin herhangi bir tusa basin");
        getch();
}
void IsimArama()
{
     printf("\nAranacak Isim : ");
        scanf("%s",&ara1);

        fseek(kp, 0, 0);
        fread(&kayit, sizeof(kayit), 1, kp);
        while (!feof(kp))
        {
            if(!strncmp(kayit.Ad,ara1,strlen(ara1)))
            {
                printf("\nMusteri Kodu : %d",kayit.kod);
                printf("\nMusteri Adi  : %s",kayit.Ad);
                printf("\nTelefon      : %d",kayit.numara);
                durum=0;
            }
            fread(&kayit, sizeof(kayit), 1, kp);
        }
        if(durum)
        {
            printf("\nKAYIT BULUNAMADI");
        }
        printf("\n\n Devam icin herhangi bir tusa basin");
        getch();
}
void NumaraArama()
{
     printf("\nAranacak Musteri Numarasi : ");
        scanf("%d",&ara);

        fseek(kp, 0, 0);
        fread(&kayit, sizeof(telephone), 1, kp);

        while (!feof(kp))
        {
            if(kayit.numara==ara)
            {
            printf("\nMusteri Kodu: %d",kayit.kod);
            printf("\nMusteri Adi : %s",kayit.Ad);
            printf("\nTelefon     : %d",kayit.numara);
            break;

            }
                fread(&kayit, sizeof(telephone), 1, kp);
            }
            if(kayit.numara != ara)
                {
                printf("\nKAYIT BULUNAMADI");
                }

            printf("\n\n Devam icin herhangi bir tusa basin");
            getch();

}
void duzenleme(void)
{
    int dno;
    char tekrar,ch;
    printf("\nDuzeltilecek Musteri Kodu : ");
    scanf("%d",&dno);
    fseek(kp, dno*sizeof(kayit), 0);
    fread(&kayit, sizeof(kayit), 1, kp);
        if(kayit.kod==dno)
        {
        printf("\nMusteri Kodu: %d",kayit.kod);
        printf("\nMusteri Adi : %s",kayit.Ad);
        printf("\nTelefon     : %d",kayit.numara);
        printf("\nDUZELTILECEK KAYIT BU MU? <E/H>");
        ch=getch();
        }

    if (ch == 'E' || ch == 'e')
    {
        printf("\nMusteri Adi: ");
        scanf("%s",kayit.Ad);
        printf("\nTelefon    : ");
        scanf("%d", &kayit.numara);
        fseek(kp, dno*sizeof(kayit), 0);
        fwrite(&kayit, sizeof(kayit), 1, kp);
        printf("\nKAYIT BASARIYLA DUZELTILDI\n\n");
    }
    else
    {
        if(kayit.kod != dno)
        {
            printf("KAYIT BULANAMADI!...");
        }
        printf("\n\nTekrar Arama Yapmak isterminiz <E/H> ");
        tekrar=getch();
        if(tekrar == 'E' || tekrar == 'e')
        {
    	printf("\nDuzeltilecek Musteri Kodu : ");
    	scanf("%d",&dno);

	    fseek(kp, dno*sizeof(kayit), 0);
	    fread(&kayit, sizeof(kayit), 1, kp);
	    if(kayit.kod==dno)
        {
        printf("\nMusteri Kodu: %d",kayit.kod);
        printf("\nMusteri Adi : %s",kayit.Ad);
        printf("\nTelefon     : %d",kayit.numara);
        printf("\nDUZELTILECEK KAYIT BU MU? <E/H>");
        ch=getch();
        }
	    if (ch == 'E' || ch == 'e')
	    	{
	        printf("\nMusteri Adi : ");
	        scanf("%s",kayit.Ad);
	        printf("\nTelefon     : ");
	        scanf("%d", &kayit.numara);
	        fseek(kp, dno*sizeof(kayit), 0);
	        fwrite(&kayit, sizeof(kayit), 1, kp);
	        printf("\nKAYIT BASARIYLA DUZELTILDI\n\n");
	    	}
	    	if(kayit.kod != dno)
            {
            printf("KAYIT BULANAMADI!...");
            }
		}
        else
        {
        	printf("KAYIT DUZELTILMEDI!... ");
		}
    }
    printf("\n\n Devam icin herhangi bir tusa basin");
    getch();
}
