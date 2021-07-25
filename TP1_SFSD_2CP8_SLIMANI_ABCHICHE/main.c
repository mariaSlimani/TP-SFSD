#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

// procedure de codage
void codage (FILE* toCrypt, FILE* result, unsigned char key [])
{
    int j=0;
    unsigned char c,k;
    k= fgetc(toCrypt);
    while (!feof(toCrypt))
    {
        // chaque caractere reçoit sans inverse, on ajoute la cle, et on fait le modulo
        c= (~k) + key[j] -127 +32;
        fprintf(result,"%c", c);
        j++;
        //on parcours la cle, quand on arrive a la fin du mot on retour au debut
        if (key [j] == '\0')
        {
            j=0;
        }
        //on ecrit le caracter sur le fichier resultat
        k= fgetc(toCrypt);
    }

}

// procedure de decodage
void decodage (FILE* todeCrypt, FILE* result, unsigned char key [])
{
    int j=0;
    unsigned char c,k;
    k= fgetc(todeCrypt);
    while (!feof(todeCrypt))
    {
        // on diminut la cle et on fait le modulo, et on fait l'inverse
        c= ~(k -32 +127 -key[j]) ;
        fprintf(result,"%c", c);
        j++;
        if (key [j] == '\0')
        {
            j=0;
        }
        //on ecrit le caracter sur le fichier resultat
        k= fgetc(todeCrypt);
    }

}



int main()
{
    char nomf1[30], nomf2[30];
    char mot [30];
    int choice, error;
    int stop=0;
    FILE *f, *g;
    do{
    // setting the window into a fixed size
    system("mode con cols=130 lines=40");
    error=1;
    while (error==1)
    {
        set_screen(0);
        gotoxy(10,10);
        printf("Choose what to do next! ");
        gotoxy(15,11);
        printf("1- Crypt a file! ");
        gotoxy(15,12);
        printf("2- Decrypt a file! ");
        gotoxy(15,13);
        printf("3- Exit! \n");
        scanf("%d", &choice);
        if ((choice != 1) && (choice != 2)&& (choice !=3))
            {
                error=1;
                printf("Input a valid value");
            }
        else
            {
                error=0;
            }
    }
    if (choice==1)
        {
            //cryptage
            do
                {
                set_screen(0);
                gotoxy(5,12);
                printf("Input the name of the file to crypt : ");
                scanf("%s",nomf1);
                f=fopen(nomf1,"r");

                if (f==NULL)
                    {
                        printf("cannot open file 1\n");
                        Sleep(300);
                        error =1;
                    }
                else
                    {
                        error=0;
                    }
        }while (error ==1);

        do
            {
                gotoxy(5,13);
                printf("Input the name of the result file : ");
                scanf("%s",nomf2);
                g=fopen(nomf2,"w");
                if (g==NULL)
                    {
                        printf("cannot open file 2\n");
                        Sleep(300);
                        error=1;
                        set_screen(0);
                    }
                else
                    {
                        error=0;
                    }
            }while (error==1);

        printf("Input the key : ");
        scanf("%s",mot);

        codage(f,g,mot);
        fclose(f);
        fclose(g);
    }
    else if (choice ==2)
    {
        //decryptage
        do{
                set_screen(0);
                gotoxy(5,12);
                printf("Input the name of the file to decrypt : ");
                scanf("%s",nomf1);
                f=fopen(nomf1,"r");

                if (f==NULL)
                    {
                        printf("cannot open file 1\n");
                        error =1;
                    }
                else
                    {
                        error=0;
                    }
        }while (error ==1);

        do{
            gotoxy(5,13);
            printf("Input the name of the result file : ");
            scanf("%s",nomf2);
            g=fopen(nomf2,"w");
            if (g==NULL)
                {
                    printf("cannot open file 2\n");
                    error=1;
                    set_screen(0);
                }
            else
                {
                    error=0;
                }
        }while (error==1);
        printf("Input the key : ");
        scanf("%s",mot);

        decodage(f,g,mot);
        fclose(f);
        fclose(g);
    }
    else
    {
        stop =1;
    }
    }while (stop !=1);
}

//Procedures d'affichage

void date_daujourdhui (int *year, int *month, int *day, char *wday[20]) //pour recuperer la date de la journee X
{
    time_t result = time(NULL);
    struct tm date;
    date = *localtime(&result);
    *year = 1900 + (date.tm_year); //l'annee
    *month= (date.tm_mon) +1; //le mois
    *day= (date.tm_mday); //le jour
    int weekd;
    weekd=date.tm_wday;
    switch(weekd)
    {
        case 0:
            strcpy(wday,"Dimanche");
            break;
        case 1:
            strcpy(wday,"Lundi");
            break;
         case 2:
            strcpy(wday,"Mardi");
            break;
        case 3:
            strcpy(wday,"Mercredi");
            break;
        case 4:
            strcpy(wday,"Jeudi");
            break;
        case 5:
            strcpy(wday,"Vendredi");
            break;
        case 6:
            strcpy(wday,"Samedi");
            break;

    }

}
void gotoxy(int x, int y)
{
    //positionne le curseur sur un point (x,y)
  COORD coord;
  coord.X = x;
  coord.Y = y;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void ligneV (int coord_x, int coord_y, int max_y) //affiche une ligne verticale selon les coordonnes
{
    for ( int k=coord_y; k<max_y;k++ )
{
    gotoxy(coord_x,k);
     printf("%c", 186); Sleep(20);
 }
}
/////////////////////////////////////////
void ligneH (int coord_x, int coord_y,int max_x,int timer)//affiche une ligne horizontal selon les coordonnes
{
 for ( int j=coord_x; j<max_x;j++ )
{
    gotoxy(j,coord_y);
    printf("%c", 205);
    Sleep(timer);
}
}
void SetColorAndBackground(int ForgC, int BackC)
{
    //change la couleur de la for/back ground
     WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);;
     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
     return;
}
void set_screen(int background)
{

        system("cls");
    //logo ESI
int w,c;
if (background==15){w=1;}
else {w=15;}
if ((background==1)||(background==15)) {c=0;}
else {c=3;}
int i=99;int y =30;
gotoxy(0,50);
SetColorAndBackground(w,background);
ligneH(0,35,100,0);
gotoxy(20,36);
int year,month,day;
char wday[20];
date_daujourdhui (&year, &month, &day, wday);
printf("~~Le %s %d/%d/%d ~~", wday, day,month,year);
gotoxy(20,37);
printf("Slimani Wassila && Abchiche Sarah");

gotoxy(i,y);
SetColorAndBackground(w,background);printf("   ('-.     .-')    ");y++;gotoxy(i,y);
printf(" _(  OO)   ( OO ).            ");y++;gotoxy(i,y);
printf("(");SetColorAndBackground(c,background);printf(",------. ");SetColorAndBackground(w,background);printf("(_)");SetColorAndBackground(c,background);printf("---");SetColorAndBackground(w,background);printf("\\_)   ");
SetColorAndBackground(c,background);printf(",-");SetColorAndBackground(w,background);printf(".-')  ");y++;gotoxy(i,y);
SetColorAndBackground(c,background);printf(" |  .---' /    _ |    |  |");SetColorAndBackground(w,background);printf("OO) ");y++;gotoxy(i,y);
SetColorAndBackground(c,background);printf(" |  |     \\  :`");SetColorAndBackground(w,background);printf(" `.    ");
SetColorAndBackground(c,background);printf("|  |");SetColorAndBackground(w,background);printf("  \\ ");y++;gotoxy(i,y);
printf("(");SetColorAndBackground(c,background);printf("|  '--.   '..`''.");SetColorAndBackground(w,background);
printf(")   ");SetColorAndBackground(c,background);printf("|  |");SetColorAndBackground(w,background);printf("(_/ ");y++;gotoxy(i,y);
SetColorAndBackground(c,background);printf(" |  .--'  .-._)   \\  ");SetColorAndBackground(w,background);printf(",");
SetColorAndBackground(c,background);printf("|  |");SetColorAndBackground(w,background);printf("_.' ");y++;gotoxy(i,y);
SetColorAndBackground(c,background);printf(" |  `---. \\       / ");SetColorAndBackground(w,background);printf("(_");
SetColorAndBackground(c,background);printf("|  |    ");y++;gotoxy(i,y);
printf(" `------'  `-----'    `--'    ");y++;

gotoxy(1,1);

}

