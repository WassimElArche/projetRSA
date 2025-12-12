#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 2

typedef struct{
    int *Tdigits;
    int taille;
    int Signe;

} BigBinary;


void retirerZeroBigBinary(BigBinary *a) {
    int i = 0;
    while (i < a->taille && a->Tdigits[i] == 0) i++;
    if (i == a->taille) {
        a->taille = 1;
        a->Signe = 0;
        a->Tdigits[0] = 0;
        return;
    }
    for (int j = i; j < a->taille; j++) {
        a->Tdigits[j - i] = a->Tdigits[j];
    }
    a->taille -= i;
    a->Signe = 1;
}

BigBinary creeBigBinaryDepuisChaine(const char *chaine) {
    BigBinary nb;
    int n = strlen(chaine);
    nb.taille = 0;
    for (int i = 0; i < n; i++) {
        if (chaine[i] == '1' || chaine[i] == '0') {
            nb.taille++;
        }
    }
    nb.Tdigits = malloc(nb.taille * sizeof(int));
    nb.Signe = 1;
    int index = 0;
    int tousZero =1;
    for (int i = 0; i < nb.taille; i++) {
        if (chaine[i] == '1' || chaine[i] == '0') {
            nb.Tdigits[index] = chaine[i] - '0';
        }
        if (nb.Tdigits[index] == 1) tousZero = 0;
        index++;
    }
    if (tousZero) nb.Signe = 0;
    return nb;

}


BigBinary initBigBinary(int taille , int signe ) {
    BigBinary nb;
    nb.taille = taille;
    nb.Signe = signe;
    nb.Tdigits = malloc(nb.taille * sizeof(int));
    for (int i = 0; i < nb.taille; i++) {
        nb.Tdigits[i] = 0;
    }
    return nb;

}

void afficherBigBinary(BigBinary bigBinary) {
    if (bigBinary.Signe == -1) printf("-");
    else if (bigBinary.Signe == 0 || bigBinary.taille == 0 ) printf("0");
    else {
        for (int i = 0 ; i < bigBinary.taille ; i++) {
            printf("%d", bigBinary.Tdigits[i]);
        }
        printf("\n");
    }
}

BigBinary createBigBinary(int taille) {
    BigBinary bb;
    bb.Tdigits = malloc(taille * sizeof(int));
    bb.taille = taille;
    bb.Signe = 0;
    return bb;
}

int inferieurBigBinary(BigBinary bigBinary1, BigBinary bigBinary2){
    int i1 = 0;
    while (i1 < bigBinary1.taille && bigBinary1.Tdigits[i1] == 0) i1++;
    int taille1 = bigBinary1.taille - i1;
    int i2 = 0;
    while (i2 < bigBinary2.taille && bigBinary2.Tdigits[i2] == 0) i2++;
    int taille2 = bigBinary2.taille - i2;
    if (bigBinary1.Signe < bigBinary2.Signe) return 1;
    if (bigBinary1.Signe > bigBinary2.Signe) return 0;
    if (taille1 < taille2) return 1;
    if (taille1 > taille2) return 0;
    for (int k = 0; k < taille1; k++) {
        int bit1 = bigBinary1.Tdigits[i1 + k];
        int bit2 = bigBinary2.Tdigits[i2 + k];
        if (bit1 < bit2) return 1;
        if (bit1 > bit2) return 0;
    }

    return 0;
}




void libereBigBinary(BigBinary *bb) {
    free(bb->Tdigits);
    bb->Tdigits = NULL;
    bb->taille = 0;
    bb->Signe = 0;
}

int egaliteBigBinary(BigBinary bigBinary1 , BigBinary bigBinary2) {
    if (bigBinary1.taille != bigBinary2.taille || bigBinary1.Signe != bigBinary2.Signe) return 0;
    int valBool = 1;
    for (int i = 0; i < bigBinary1.taille; i++) {
        if (bigBinary1.Tdigits[i] != bigBinary2.Tdigits[i]) valBool =  0;
    }
    return valBool;
}

int maxTaille(int a , int b) {
    return a > b ? a : b;
}

BigBinary soustractionBigBinary(BigBinary bigBinary1, BigBinary bigBinary2) {

    int taille = (bigBinary1.taille > bigBinary2.taille) ? bigBinary1.taille : bigBinary2.taille;
    int* resultat = malloc((taille + 1)*sizeof(int));

    int i = bigBinary1.taille - 1;
    int j = bigBinary2.taille - 1;
    int k = 0;
    int retenue = 0;

    while (i >= 0 || j >= 0) {
        int bitBigBinary1 = (i >= 0) ? bigBinary1.Tdigits[i] : 0;
        int bitBigBinary2 = (j >= 0) ? bigBinary2.Tdigits[j] : 0;
        int diff = bitBigBinary1 - bitBigBinary2 - retenue;

        if (diff >= 0) {
            resultat[k] = diff;
            retenue = 0;
        } else {
            resultat[k] = diff + 2;
            retenue = 1;
        }

        i--;
        j--;
        k++;
    }

    BigBinary result = createBigBinary(k);
    result.Signe = 1;

    for (int m = 0; m < k; m++) {
        result.Tdigits[m] = resultat[k - m - 1];
    }

    free(resultat);
    return result;
}



BigBinary additionBigBinary(BigBinary bigBinary1 , BigBinary bigBinary2) {
    int taille = bigBinary1.taille;
    if (bigBinary2.taille > bigBinary1.taille) {
        taille = bigBinary2.taille;
    }
    int* resultat = malloc((taille+1) * sizeof(int));
    int i = bigBinary1.taille -1;
    int j = bigBinary2.taille -1;
    int k=0;
    int retenue = 0;
    while (i>=0|| j>=0 || retenue) {
        int bitBigbinary1 = (i>=0) ? bigBinary1.Tdigits[i] : 0;
        int bitBigBinary2 = (j>=0) ? bigBinary2.Tdigits[j] : 0;
        int somme = bitBigbinary1 + bitBigBinary2 + retenue;
        switch (somme){
            case 0:
                resultat[k] = 0;
                retenue = 0;
                break;
            case 1:
                resultat[k] = 1;
                retenue = 0;
                break;
            case 2:
                resultat[k] = 0;
                retenue = 1;
                break;
            case 3:
                resultat[k] = 1;
                retenue = 1;
                break;
        }
        i--;
        j--;
        k++;
    }
    BigBinary result = createBigBinary(k);
    result.Signe = 1;
    for (int i = 0 ; i < k ; i++) {
        result.Tdigits[i] = resultat[k- i - 1];
    }
    free(resultat);
    return result;
}


BigBinary BigBinary_PGCD(BigBinary a , BigBinary b){
    BigBinary u, v;
    if (egaliteBigBinary(a , b) == 1) return a;
    if (inferieurBigBinary(a,b) == 1) {
        u = b;
        v = a;
    }
    else {
        u = a;
        v = b;
    }
    while (!egaliteBigBinary(u,v)) {
        if (inferieurBigBinary(u,v) == 0) {
            u = soustractionBigBinary(u,v);
        }
        else {
            v = soustractionBigBinary(v,u);
        }
    }
    retirerZeroBigBinary(&u);
    return u;
}



BigBinary copiesBigBinary(BigBinary bigBinary) {
    BigBinary result = createBigBinary(bigBinary.taille);
    for (int i = 0 ; i < bigBinary.taille ; i++) {
        result.Tdigits[i] = bigBinary.Tdigits[i];
    }
    result.Signe = bigBinary.Signe;
    return result;
}


BigBinary multiplicationEgyptienne(BigBinary bigBinary1, BigBinary bigBinary2) {
    BigBinary result = initBigBinary(1, 0);
    result.Tdigits[0] = 0;
    BigBinary puissance = copiesBigBinary(bigBinary1);
    for (int i = bigBinary2.taille - 1; i >= 0; i--) {
        if (bigBinary2.Tdigits[i] == 1) {
            BigBinary temp = additionBigBinary(result, puissance);
            libereBigBinary(&result);
            result = temp;
        }
        if (i > 0) {
            BigBinary temp = additionBigBinary(puissance, puissance);
            libereBigBinary(&puissance);
            puissance = temp;
        }
    }

    libereBigBinary(&puissance);
    return result;
}



BigBinary BigBinary_mod(BigBinary a , BigBinary b) {
    BigBinary resultat = copiesBigBinary(a);
    BigBinary nombreDeb = copiesBigBinary(b);
    int i = 1;
    BigBinary doubleDeb = additionBigBinary(nombreDeb, nombreDeb);
    while (inferieurBigBinary(doubleDeb, resultat) == 1) {
        libereBigBinary(&nombreDeb);
        nombreDeb = doubleDeb;
        doubleDeb = additionBigBinary(nombreDeb, nombreDeb);
        i = 2;
    }
    libereBigBinary(&doubleDeb);
    if (i > 1) {
        BigBinary temp = soustractionBigBinary(resultat, nombreDeb);
        libereBigBinary(&resultat);
        resultat = temp;
    }
    libereBigBinary(&nombreDeb);
    while (inferieurBigBinary(b, resultat) == 1 || egaliteBigBinary(b, resultat) == 1) {
        nombreDeb = copiesBigBinary(b);
        doubleDeb = additionBigBinary(nombreDeb, nombreDeb);

        while (inferieurBigBinary(doubleDeb, resultat) == 1 || egaliteBigBinary(doubleDeb, resultat) == 1) {
            libereBigBinary(&nombreDeb);
            nombreDeb = doubleDeb;
            doubleDeb = additionBigBinary(nombreDeb, nombreDeb);
        }
        libereBigBinary(&doubleDeb);
        BigBinary temp = soustractionBigBinary(resultat, nombreDeb);
        libereBigBinary(&resultat);
        resultat = temp;
        libereBigBinary(&nombreDeb);
        retirerZeroBigBinary(&resultat);
    }

    return resultat;
}

BigBinary BigBinary_expo(BigBinary a, BigBinary n, unsigned int e) {
    BigBinary resultat = initBigBinary(1, 1);
    resultat.Tdigits[0] = 1;
    BigBinary base = BigBinary_mod(a,n);
    while (e>0) {
        if (e%2 == 1) {
            BigBinary temp = multiplicationEgyptienne(resultat, base);
            libereBigBinary(&resultat);
            resultat = BigBinary_mod(temp, n);
            libereBigBinary(&temp);
        }
        BigBinary temp2 = multiplicationEgyptienne(base, base);
        libereBigBinary(&base);
        base = BigBinary_mod(temp2, n);
        libereBigBinary(&temp2);
        e = e/2;
    }

    return resultat;

}


BigBinary chiffrement_RSA(BigBinary message , BigBinary clepublicN , unsigned int clepublicE) {
    return BigBinary_expo(message,clepublicN,clepublicE);
}

BigBinary dechiffrement_RSA(BigBinary messageChiffre , BigBinary clepublicN , unsigned int clepriveE){
    return BigBinary_expo(messageChiffre,clepublicN,clepriveE);
}




int main() {
    BigBinary a = creeBigBinaryDepuisChaine("11010101100101");
    BigBinary b = creeBigBinaryDepuisChaine("1010111");

    printf("test egalite\n");
    printf(egaliteBigBinary(a, b) ? "egal\n" : "pas egal\n");

    printf("\ntest inferieur\n");
    printf(inferieurBigBinary(a, b) ? "a plus petit\n" : "a plus grand\n");

    printf("\ntest addition\n");
    BigBinary add = additionBigBinary(a, b);
    afficherBigBinary(add);

    printf("\ntest soustraction\n");
    BigBinary sub;
    if (inferieurBigBinary(a, b))
        sub = soustractionBigBinary(b, a);
    else
        sub = soustractionBigBinary(a, b);
    afficherBigBinary(sub);

    printf("\ntest multiplication\n");
    BigBinary mul = multiplicationEgyptienne(a, b);
    afficherBigBinary(mul);

    printf("\ntest pgcd\n");
    BigBinary g = BigBinary_PGCD(a, b);
    afficherBigBinary(g);

    printf("\ntest modulo\n");
    BigBinary mod = BigBinary_mod(a, b);
    afficherBigBinary(mod);

    printf("\ntest exposition modulaire\n");
    BigBinary expmod = BigBinary_expo(a, b, 13);
    afficherBigBinary(expmod);

    libereBigBinary(&a);
    libereBigBinary(&b);

    BigBinary aa = creeBigBinaryDepuisChaine("11000011010011111");
    BigBinary nn = creeBigBinaryDepuisChaine("100100111110110100001");

    printf("\ntest chiffrement\n");
    BigBinary ch = chiffrement_RSA(aa, nn, 101);
    afficherBigBinary(ch);

    printf("\ntest dechiffrement\n");
    BigBinary de = dechiffrement_RSA(ch, nn, 251501);
    afficherBigBinary(de);

    libereBigBinary(&a);
    libereBigBinary(&b);
    libereBigBinary(&add);
    libereBigBinary(&sub);
    libereBigBinary(&mul);
    libereBigBinary(&g);
    libereBigBinary(&mod);
    libereBigBinary(&expmod);
    libereBigBinary(&ch);
    libereBigBinary(&de);

    return 0;
}
