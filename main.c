#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BASE 2

typedef struct{
    int *Tdigits;
    int taille;
    int Signe;

} BigBinary;


// PHASE 1

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
    //vrai taille psq si taille dif et les premier bit sont 0 alors inutile
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


//PHASE 2
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


BigBinary multiplicationEgyptienne(BigBinary bigBinary1 , BigBinary bigBinary2) {
    int nb = bigBinary2.taille;
    BigBinary result = bigBinary1;
    for (int i = 1 ; i < nb ;i++) {
        bigBinary1 = additionBigBinary(bigBinary1,bigBinary1);
        if (bigBinary2.taille != 1) bigBinary2.taille = bigBinary2.taille-1;
        if (bigBinary2.Tdigits[bigBinary2.taille-1] == 1) {
            result = additionBigBinary(result,bigBinary1);
        }
    }
    return result;
}

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

BigBinary BigBinary_mod(BigBinary a , BigBinary b) {
    BigBinary nombreDeb = copiesBigBinary(b);
    int i = 1;
    BigBinary doubleDeb = additionBigBinary(nombreDeb, nombreDeb);
    while (inferieurBigBinary(doubleDeb, a) == 1) {
        libereBigBinary(&nombreDeb);
        nombreDeb = doubleDeb;
        doubleDeb = additionBigBinary(nombreDeb, nombreDeb);
        i = 2;
    }
    libereBigBinary(&doubleDeb);
    if (i > 1) {
        BigBinary temp = soustractionBigBinary(a, nombreDeb);
        a = temp;
    }
    libereBigBinary(&nombreDeb);
    while (inferieurBigBinary(b, a) == 1 || egaliteBigBinary(b, a) == 1) {
        nombreDeb = copiesBigBinary(b);
        doubleDeb = additionBigBinary(nombreDeb, nombreDeb);

        while (inferieurBigBinary(doubleDeb, a) == 1 || egaliteBigBinary(doubleDeb, a) == 1) {
            libereBigBinary(&nombreDeb);
            nombreDeb = doubleDeb;
            doubleDeb = additionBigBinary(nombreDeb, nombreDeb);
        }
        libereBigBinary(&doubleDeb);
        BigBinary temp = soustractionBigBinary(a, nombreDeb);
        a = temp;
        libereBigBinary(&nombreDeb);
        retirerZeroBigBinary(&a);
    }

    return a;
}

BigBinary BigBinary_expo(BigBinary a , BigBinary n , unsigned int e) {
    BigBinary result = initBigBinary(1,1);
    result.Tdigits[0] = 1;
    unsigned int bits[32];
    for (int i = 0 ; i < 32 ; i++) {
        bits[31-i] = (e>>i) & 1;
    }
    int IndicePremierBit = -1;
    for (int i = 0;i<31 ; i++) {
        if (bits[i] == 1) {
            IndicePremierBit = i;
        }
    }
    if (IndicePremierBit == -1) return BigBinary_mod(a,n);
    for (int i = IndicePremierBit ; i <= 31 ; i++) {
        result = BigBinary_mod(multiplicationEgyptienne(result,result),n);
        if (bits[i] == 1) {
            result = BigBinary_mod(multiplicationEgyptienne(result, a),n);
        }
    }
    return result;
    //10000000000000000000000000000000000000000001111111010110100101011011011001011001010111010
    //10100011000010111111011001110010101101100100111110001101000001001111000000110000111010111
}


BigBinary chiffrement_RSA(BigBinary a , BigBinary n , unsigned int e) {
    return BigBinary_expo(a,n,e);
}

BigBinary dechiffrement_RSA(BigBinary a , BigBinary n , unsigned int e) {
    return initBigBinary(1,1);
}





int main() {

    printf("Test 6: 15 * 8 (1111 * 1000)\n");
    BigBinary m11 = creeBigBinaryDepuisChaine("11000011010011111");  // 15
    BigBinary m12 = creeBigBinaryDepuisChaine("1001001110101111100001");  // 8
    BigBinary resM6 = chiffrement_RSA(m11 ,m12 , 101 );
    printf("Resultat: ");
    afficherBigBinary(resM6);
    libereBigBinary(&m11);
    libereBigBinary(&m12);
    libereBigBinary(&resM6);


    /*
    // Test 6: Grand nombre
    printf("Test 6: 15 * 8 (1111 * 1000)\n");
    BigBinary m11 = creeBigBinaryDepuisChaine("1111");  // 15
    BigBinary m12 = creeBigBinaryDepuisChaine("1000");  // 8
    BigBinary resM6 = multiplicationEgyptienne(m11, m12);
    printf("Resultat: ");
    afficherBigBinary(resM6);
    printf("Attendu:  1111000 (120 en decimal)\n");
    printf("Verification: 15 * 8 = 120 ✓\n\n");
    libereBigBinary(&m11);
    libereBigBinary(&m12);
    libereBigBinary(&resM6);*/

    return 0;
}