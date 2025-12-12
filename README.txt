#ESIEA
#ING3 TD 31
# Etudiants : El Arche Wassim & Bahanag Dimitri

Creation d'une bibliotheque en C de calcul mathematiques sous la forme de differente fonction mais en structure
BigBinary(De tres grand binaire)

#Preambule
- Implementer la structure BigBinary
- Fonction qui créée un BigBinary a partir d'une chaine de caractere
- Fonction qui initalise un BigBinary a partir d'une certaine taille mais rempli de 0
- Fonction afficher BigBinary
- Libere un Bigbinary de la memoire aloué

#PHASE 1 :
Implementation de fonction arithmetique simple en binaire:
- Addition
- Soustraction
- Egalité entre 2 binaire
- Inferieur ou egal ( si A<B renvoie 1 sinon 0)

#PHASE 2 :
Implementation de fonction arithmetique avancée:
- Multiplication Egyptienne
- Modulo
- PGCD
- Exponentiation modulaire rapide
- Fonction de suppression des zéros en tête

#PHASE BONUS :
Implementation du chiffrement RSA:
- Fonction de chiffrement RSA : C = M^e mod N
- Fonction de dechiffrement RSA : M = C^d mod N
- Validation avec des jeux de données de test

#PS :
- Gestion mémoire dynamique avec malloc/free
- Support de très grands nombres (>250 bits testés)
- Multiplication égyptienne par décalages successifs