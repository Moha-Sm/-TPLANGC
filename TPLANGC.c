{
    "version": "2.0.0",
    "tasks": [
      {
        "label": "build C",
        "type": "shell",
        "command": "gcc",
        "args": [
          "-g",
          "${file}",
          "-o",
          "${fileDirname}/${fileBasenameNoExtension}.exe"
        ],
        "group": "build",
        "problemMatcher": [],
        "detail": "Compiler un programme C"
      }
    ]
  }

  {
    "version": "0.2.0",
    "configurations": [
      {
        "name": "Déboguer C",
        "type": "cppdbg",
        "request": "launch",
        "program": "${fileDirname}/${fileBasenameNoExtension}.exe",
        "args": [],
        "stopAtEntry": false,
        "cwd": "${fileDirname}",
        "environment": [],
        "externalConsole": true,
        "MIMode": "gdb",
        "miDebuggerPath": "C:/chemin/vers/gdb.exe",  // à adapter
        "setupCommands": [
          {
            "description": "Activer la coloration GDB",
            "text": "-enable-pretty-printing",
            "ignoreFailures": true
          }
        ]
      }
    ]
  }


#include <stdio.h>
#include <stdlib.h> // Pour l'utilisation de rand() et srand() 
#include <time.h>   // Pour utiliser les fonctionnalités du temps (date et heure)
#include <string.h> // Pour utiliser strcmp

float addition() {
    int a = rand() % 101;
    int b = rand() % 101;
    int reponse;
    float pts = 0;

    printf("%d + %d = ?\n", a, b);

    for (int essaie = 1; essaie <= 3; essaie++) {
        printf("Essai %d: ", essaie);
        scanf("%d", &reponse);

        if (reponse == a + b) {
            if (essaie == 1) pts = 10;
            else if (essaie == 2) pts = 5;
            else pts = 1;

            printf("Bravo ! Vous avez gagné %.1f point(s)\n", pts);
            return pts;
        }
    }

    printf("Désolé, la bonne réponse était %d\n", a + b);
    return pts;
}

float soustraction() {
    int a = rand() % 101;
    int b = rand() % 101;
    if (a < b) { int temp = a; a = b; b = temp; }
    int reponse;
    float pts = 0;

    printf("%d - %d = ?\n", a, b);

    for (int essaie = 1; essaie <= 3; essaie++) {
        printf("Essai %d: ", essaie);
        scanf("%d", &reponse);

        if (reponse == a - b) {
            if (essaie == 1) pts = 10;
            else if (essaie == 2) pts = 5;
            else pts = 1;

            printf("Bravo ! Vous avez gagné %.1f point(s)\n", pts);
            return pts;
        }
    }

    printf("Désolé, la bonne réponse était %d\n", a - b);
    return pts;
}

float multiplication() {
    int a = rand() % 10 + 1;
    int b = rand() % 10 + 1;
    int reponse;
    float pts = 0;

    printf("%d * %d = ?\n", a, b);

    for (int essaie = 1; essaie <= 3; essaie++) {
        printf("Essai %d: ", essaie);
        scanf("%d", &reponse);

        if (reponse == a * b) {
            if (essaie == 1) pts = 10;
            else if (essaie == 2) pts = 5;
            else pts = 1;

            printf("Bravo ! Vous avez gagné %.1f point(s)\n", pts);
            return pts;
        }
    }

    printf("Désolé, la bonne réponse était %d\n", a * b);
    return pts;
}

float tables_multiplications() {
    float pts = 0;
    int t;

    printf("Choisissez une table de multiplication entre 1 et 10 : ");
    scanf("%d", &t);

    if (t < 1 || t > 10) {
        printf("Choix invalide. Veuillez entrer un nombre entre 1 et 10.\n");
        return 0;
    }

    for (int i = 1; i <= 10; i++) {
        int reponse;
        int bonne_reponse = t * i;
        int trouve = 0;

        for (int essaie = 1; essaie <= 3; essaie++) {
            printf("%d * %d = ? (Essai %d): ", t, i, essaie);
            scanf("%d", &reponse);

            if (reponse == bonne_reponse) {
                if (essaie == 1) pts += 10;
                else if (essaie == 2) pts += 5;
                else pts += 1;

                printf("Correct !\n");
                trouve = 1;
                break;
            }
        }

        if (!trouve) {
            printf("PERDU ! La bonne réponse était %d\n", bonne_reponse);
        }
    }

    printf("Total des points obtenus pour la table : %.1f\n", pts);
    return pts;
}

int main() {
    int i = 0;
    int choix;
    time_t maintenant;
    struct tm *infotemps;
    float pts_total = 0;
    char nom[100];

    srand(time(NULL)); // Initialisation du générateur de nombres aléatoires ici

    printf("Entrez votre nom : ");
    scanf("%99s", nom); // Sécuriser la lecture du nom

    printf("+------------------------------+\n");
    printf("|1: Addition                   |\n");
    printf("|2: Soustraction               |\n");
    printf("|3: Multiplication             |\n");
    printf("|4: Tables de multiplication   |\n");
    printf("|5: Divisions                  |\n");
    printf("|0: Sortir du jeu              |\n");
    printf("+------------------------------+\n");

    // Pour avoir les données du fichier de sauvegarde des points
    FILE *fichier_scores = fopen("scores.txt", "r");

    if (fichier_scores == NULL) {
        printf("SALUT %s 😎 !! Vous êtes la bienvenue 🙃\n", nom);
    } else {
        char ligne[240];
        int trouve = 0;
        while (fgets(ligne, sizeof(ligne), fichier_scores)) {
            char fnom[100];
            char date[100];
            float pts;
            if (sscanf(ligne, "%s | %[^|] | %f points", fnom, date, &pts) == 3) {
                if (strcmp(fnom, nom) == 0) {
                    printf("Le dernier score enregistré pour %s est : %.1f points (%s)\n", fnom, pts, date);
                    trouve = 1;
                }
            }
        }
        if (!trouve) {
            printf("SALUT %s !! Vous êtes la bienvenue :-)\n", nom);
        }
        fclose(fichier_scores);
    }

    do {
        printf("Quel est votre choix ?\n");
        scanf("%d", &choix);
        float totalpoints = 0; // Réinitialisation des points à chaque itération
        switch (choix) {
            case 1:
                totalpoints = addition();
                break;
            case 2:
                totalpoints = soustraction();
                break;
            case 3:
                totalpoints = multiplication();
                break;
            case 4:
                totalpoints = tables_multiplications();
                break;
            case 5:
                printf("Vous avez choisi Divisions\n");
                break;
            case 0:
                printf("Vous avez choisi de sortir\n");
                break;
        }
        pts_total = pts_total + totalpoints; // Décompte des points
    } while (choix != 0);

    // Récupération de la date et de l’heure
    time(&maintenant);
    infotemps = localtime(&maintenant);
    char dateHeure[100];
    strftime(dateHeure, sizeof(dateHeure), "%d/%m/%y %H:%M:%S", infotemps);

    // Écriture dans le fichier
    FILE *fichier_score = fopen("scores.txt", "a"); // "a" pour ajouter à la fin
    if (fichier_score != NULL) {
        fprintf(fichier_score, "%s | %s | %.1f points\n", nom, dateHeure, pts_total);
        fclose(fichier_score);
        printf("Score enregistré dans 'scores.txt'\n");
    } else {
        printf("Erreur lors de l'ouverture du fichier pour enregistrer le score.\n");
    }

    if (choix == 1) {
        int R, P;
        int m;
        R = rand() % 101;
        P = rand() % 100 + 1;
        printf("%d + %d = ?\n", R, P);
        printf("Entrez le résultat\n");
        scanf("%d", &m);
        if (m == P + R) {
            printf("BRAVO\n");
        } else {
            printf("Perdu\n");
        }
    }

    if (choix == 0) {
        printf("Merci de votre visite\n");
    }

    return 0;
}