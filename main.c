//
//  main.c
//  lampotila
//
//  Created by Sami Sipilä on 9/30/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "stdlib.h"
#include "stdio.h"
#define leveys  100
#define korkeus 100
#define vasen_lampo 1000
#define oikea_lampo 1000
#define ala_lampo 1000
#define yla_lampo 0
#define TYYPPI double
#define TYYPPI_LYHENNE "%-5f,"

int aseta_reunat(TYYPPI *kohde);
int aseta_piste(TYYPPI *kohde, int x, int y, TYYPPI arvo);
TYYPPI lue(TYYPPI *kohde, int x, int y);
int tulosta_taulukko(TYYPPI *kohde);
int iteroi(TYYPPI *vanha, TYYPPI *uusi);
int vaihda(TYYPPI **uusi, TYYPPI **vanha);
int vertaa(TYYPPI *taulu1, TYYPPI *taulu2);
TYYPPI keskiarvo(TYYPPI *taulu);

#include <stdio.h>

int main (int argc, const char * argv[])
{
    
    TYYPPI *nykyinen = malloc(sizeof(TYYPPI)*(leveys+2)*(korkeus+2));
    TYYPPI *uusi = malloc(sizeof(TYYPPI)*(leveys+2)*(korkeus+2));
    aseta_reunat(uusi);
    aseta_reunat(nykyinen);
    int i=0;
   do{
        iteroi(nykyinen, uusi);
        vaihda(&nykyinen, &uusi);
        i++;
   }while(!(vertaa(nykyinen, uusi)));
    tulosta_taulukko(uusi);
    printf("\n %d \n", i);
    printf("keskiarvo: %f", keskiarvo(uusi));
    free(uusi);
    free(nykyinen);
    return 0;
}


int aseta_reunat(TYYPPI *kohde){
    for(int x=0;x<leveys+2;x++){
        aseta_piste(kohde, x, 0, yla_lampo);
        aseta_piste(kohde, x, korkeus+1, ala_lampo);
        }
    for(int y=0;y<korkeus+2;y++){
        aseta_piste(kohde, 0, y, vasen_lampo);
        aseta_piste(kohde, leveys+1, y, oikea_lampo);
    }
    
    return 1;
}

int aseta_piste(TYYPPI *kohde, int x, int y, TYYPPI arvo){
    kohde += ((y*(leveys+2))+x);
    *kohde = arvo;
    return 1;
}

TYYPPI lue(TYYPPI *kohde, int x, int y){
    kohde += ((y*(leveys+2))+x);
    return *kohde;
}

int tulosta_taulukko(TYYPPI *kohde){
         for(int y=0;y<korkeus+2;y++){
             for(int x=0;x<leveys+2;x++){
                 printf(TYYPPI_LYHENNE, lue(kohde, x, y));
        }
             printf("\n");
    }
    return 1;
}

int iteroi(TYYPPI *vanha, TYYPPI *uusi){
    TYYPPI arvo = 0;
    for(int y=0;y<korkeus;y++){
        for(int x=0;x<leveys;x++){
            arvo = (lue(vanha, x, y)+lue(vanha, x+2, y)+lue(vanha, x, y+2)+lue(vanha, x+2, y+2))/4;
            aseta_piste(uusi, x+1, y+1, arvo);
        }
    }
    
    return 1;
}

int vaihda(TYYPPI **uusi, TYYPPI **vanha){
    TYYPPI *temp = *vanha;
    *vanha = *uusi;
    *uusi = temp;
    return 1;
}

int vertaa(TYYPPI *taulu1, TYYPPI *taulu2){
    for(int y=0;y<korkeus;y++){
        for(int x=0;x<leveys;x++){
            if(!(lue(taulu1, x+1, y+1) == lue(taulu2, x+1, y+1))){
                return 0;}
                 }
            }
                 
    return 1;
            
    
}

TYYPPI keskiarvo(TYYPPI *taulu){
    unsigned long summa = 0;
    for(int y=0;y<korkeus;y++){
        for(int x=0;x<leveys;x++){
            summa += lue(taulu, x+1, y+1);
        }
    }
    return summa/(leveys*korkeus);
}

