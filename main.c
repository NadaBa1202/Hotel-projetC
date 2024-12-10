#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define MAX_LINES 24
#define MAX_TOKEN_SIZE 256
// Module de traitement des animaux
typedef struct animal {
    char type[50];
    char nom[50];
    char prop[50];
    char date_entree[50];
    char date_sortie[50];
    char resp[50];
} animal;

struct animal* creer_espace_animal(int *N, int nbmax) {
    *N = 0;  // Initialize the count of animals to 0
    struct animal* espace_animal = (struct animal*)malloc(nbmax * sizeof(struct animal));
    if (espace_animal == NULL) {  // Check if memory allocation failed
        printf("echec d'allocation !\n");
        exit(1);
    }
    return espace_animal;  // Return the pointer to the allocated space
}

void ajout_animal(animal* espace_animal, int* N, int nbmax) {
    if (*N < nbmax) {
        printf("Donner les informations liees a l'animal\n");
        printf("Type: ");
        scanf("%s", espace_animal[*N].type);
        printf("Nom: ");
        scanf("%s", espace_animal[*N].nom);
        printf("Proprietaire: ");
        scanf("%s", espace_animal[*N].prop);
        printf("Date d'entree: ");
        scanf("%s", espace_animal[*N].date_entree);
        printf("Date de sortie: ");
        scanf("%s", espace_animal[*N].date_sortie);
        printf("Responsable: ");
        scanf("%s", espace_animal[*N].resp);
        *N = *N + 1;
    } else {
        printf("L'espace est complet\n");
    }
}

void effacer_animal(animal* espace_animal, int* N) {
    char p[50];
    int a = 0; // Initialize a
    printf("Nom de proprietaire: ");
    scanf("%s", p); // No need for &

    for (int i = 0; i < *N; i++) { // Start from 0
        if (strcmp(espace_animal[i].prop, p) == 0) { // Use strcmp
            a++;
            for (int j = i; j < *N - 1; j++) {
                espace_animal[j] = espace_animal[j + 1];
            }
            (*N)--; // Decrease N
            i--; // Adjust index after removal
        }
    }
    if (a > 0) {
        printf("%d animal(s) efface(s).\n", a);
    } else {
        printf("Aucun animal trouve avec ce nom de proprietaire.\n");
    }
}

void affiche_espace(animal* espace_animal, int* N) {
    for (int i = 0; i < *N; i++) {
        printf("Animal %d: %s, %s, %s, %s to %s, Responsable: %s\n",
               i + 1, espace_animal[i].type, espace_animal[i].nom,
               espace_animal[i].prop, espace_animal[i].date_entree,
               espace_animal[i].date_sortie, espace_animal[i].resp);
    }
}

int place_disponible(int *N, int nbmax) {
    return nbmax - *N;
}

void Animaux(){
    const int nbmax = 30;
    int N;
    struct animal* espace_animal = NULL;
    espace_animal = creer_espace_animal(&N, nbmax);

    int sortir = 0;
    while (sortir == 0) {
        printf("Bienvenu dans l'espace animal\n");
        printf("Choisir le numero de la commande\n");
        printf("1. Ajouter un animal\n");
        printf("2. Afficher l'espace\n");
        printf("3. Effacer un animal\n");
        printf("4. Afficher nombre de places disponibles\n");
        printf("5. Quitter\n");
        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                ajout_animal(espace_animal, &N, nbmax);
                break;
            case 2:
                affiche_espace(espace_animal, &N);
                break;
            case 3:
                effacer_animal(espace_animal, &N);
                break;
            case 4:
                printf("Nombre de places disponibles: %d\n", place_disponible(&N, nbmax));
                break;
            case 5:
                sortir = 1;
                break;
            default:
                printf("Erreur: option invalide. Veuillez choisir une option valide.\n");
        }
    }
}
//evenements****//
// D finition de la structure Evenement
typedef struct Evenement {
    char nom_event[50];
    char type[50];
    char date_event[50];
    char theme_event[50];
    int budget;
    int max_invit;
    char lieu[50];
    struct Evenement* suiv;
} Evenement;

// D finition de la structure Organisateur
typedef struct Organisateur {
    char nom_organisateur[50];
    char tache[50];
    char nom_evenement[50];
    struct Organisateur *suiv;
} Organisateur;

// Fonction pour ajouter un nouvel  v nement
Evenement* ajouterEvenement(Evenement* tete) {
    printf("Ajouter un nouvel evenement.\n");
    Evenement* nouvel = (Evenement*)malloc(sizeof(Evenement));
    printf("Entrez le nom de l'evenement : ");
    fgets(nouvel->nom_event, sizeof(nouvel->nom_event), stdin);
    nouvel->nom_event[strcspn(nouvel->nom_event, "\n")] = 0;  // Supprimer le '\n' apr s fgets

    printf("Entrez le type de l'evenement : ");
    fgets(nouvel->type, sizeof(nouvel->type), stdin);
    nouvel->type[strcspn(nouvel->type, "\n")] = 0;

    printf("Entrez la date de l'evenement : ");
    fgets(nouvel->date_event, sizeof(nouvel->date_event), stdin);
    nouvel->date_event[strcspn(nouvel->date_event, "\n")] = 0;

    printf("Entrez le theme de l'evenement : ");
    fgets(nouvel->theme_event, sizeof(nouvel->theme_event), stdin);
    nouvel->theme_event[strcspn(nouvel->theme_event, "\n")] = 0;

    printf("Entrez le budget de l'evenement : ");
    scanf("%d", &nouvel->budget);

    printf("Entrez le nombre maximal des invites : ");
    scanf("%d", &nouvel->max_invit);
    getchar();  // Consommer le '\n' restant apr s scanf

    printf("Entrez le lieu de l'evenement : ");
    fgets(nouvel->lieu, sizeof(nouvel->lieu), stdin);
    nouvel->lieu[strcspn(nouvel->lieu, "\n")] = 0;

    nouvel->suiv = tete;
    return nouvel;
}

// Fonction pour supprimer un  v nement
void supprimerEvenement(Evenement** tete) {
    printf("Donner le nom de l'evenement annule : ");
    char nom[50];
    fgets(nom, sizeof(nom), stdin);
    nom[strcspn(nom, "\n")] = 0;

    Evenement* courant = *tete;
    Evenement* precedent = NULL;

    while (courant != NULL && strcmp(courant->nom_event, nom) != 0) {
        precedent = courant;
        courant = courant->suiv;
    }

    if (courant == NULL) {
        printf("Evenement non trouve.\n");
        return;
    }

    if (precedent == NULL) {
        *tete = courant->suiv;  // Si c'est le premier  v nement
    } else {
        precedent->suiv = courant->suiv;
    }

    free(courant);
    printf("L'evenement '%s' a ete annule.\n", nom);
}

// Fonction pour afficher les  v nements   une date sp cifique
void afficherEvenementsCourant(Evenement* tete, const char* date) {
    Evenement* courant = tete;
    while (courant != NULL) {
        if (strcmp(courant->date_event, date) == 0) {
            printf("L'evenement a cette date : %s\n", courant->nom_event);
        }
        courant = courant->suiv;
    }
}

// Fonction pour afficher toutes les informations d'un  v nement
void afficherToutesInformationsEvenement(Evenement* tete, const char* nom) {
    Evenement* courant = tete;
    while (courant != NULL) {
        if (strcmp(courant->nom_event, nom) == 0) {
            printf("Nom de l'evenement : %s\n", courant->nom_event);
            printf("Type : %s\n", courant->type);
            printf("Date : %s\n", courant->date_event);
            printf("Theme : %s\n", courant->theme_event);
            printf("Budget : %d\n", courant->budget);
            printf("Nombre maximal d'invites : %d\n", courant->max_invit);
            printf("Lieu : %s\n", courant->lieu);
            return;
        }
        courant = courant->suiv;
    }
    printf("Evenement non trouve.\n");
}

// Fonction pour lib rer la m moire allou e pour les  v nements
void libererListe(Evenement* tete) {
    Evenement* courant;
    while (tete != NULL) {
        courant = tete;
        tete = tete->suiv;
        free(courant);
    }
}

// Fonction pour importer les informations des organisateurs   partir d'un fichier
Organisateur* importerInfosOrg(Organisateur* tete, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return tete;
    }

    char ligne[256];
    while (fgets(ligne, sizeof(ligne), fichier)) {
        Organisateur* nouvel = (Organisateur*)malloc(sizeof(Organisateur));
        sscanf(ligne, "%49[^,],%49[^,],%49[^\n]",
               nouvel->nom_organisateur, nouvel->tache, nouvel->nom_evenement);
        nouvel->suiv = tete;
        tete = nouvel;
    }

    fclose(fichier);
    return tete;
}

// Fonction pour afficher les informations des organisateurs
void afficherOrganisateurs(Organisateur* tete) {
    Organisateur* courant = tete;
    while (courant != NULL) {
        printf("Nom: %s, Tache: %s, Evenement: %s\n",
               courant->nom_organisateur, courant->tache, courant->nom_evenement);
        courant = courant->suiv;
    }
}

// Fonction pour lib rer la m moire allou e pour les organisateurs
void libererListeOrganisateurs(Organisateur* tete) {
    Organisateur* courant = tete;
    while (courant != NULL) {
        Organisateur* suivant = courant->suiv;
        free(courant);
        courant = suivant;
    }
}

// Fonction pour enregistrer les  v nements dans un fichier
void enregistrerEvenements(Evenement* tete, const char* nomFichier) {
    FILE* fichier = fopen(nomFichier, "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier pour l'ecriture.\n");
        return;
    }

    Evenement* courant = tete;
    while (courant != NULL) {
        fprintf(fichier, "%s,%s,%s,%s,%d,%d,%s\n",
                courant->nom_event, courant->type, courant->date_event, courant->theme_event,
                courant->budget, courant->max_invit, courant->lieu);
        courant = courant->suiv;
    }

    fclose(fichier);
    printf("Les evenements ont ete enregistres dans le fichier.\n");
}

// Fonction principale pour g rer les  v nements
void Evenements() {
    Evenement* teteEvenement = NULL;
    Organisateur* teteOrganisateur = NULL;
    printf("Bienvenu a Evenements!\n");
    printf("1. Ajouter un evenement\n");
    printf("2. Afficher toutes les informations d'un evenement\n");
    printf("3. Supprimer un evenement\n");
    printf("4. Afficher les taches des organisateurs\n");
    printf("5. Quitter\n");
    int option;
    int sortir = 0;
    while (sortir == 0) {
        printf("Choisir une option : ");
        scanf("%d", &option);
        getchar();  // Consommer le '\n' restant apr s scanf

        switch (option) {
            case 1:
                teteEvenement = ajouterEvenement(teteEvenement);
                enregistrerEvenements(teteEvenement, "evenements.txt");
                break;
            case 2: {
                printf("Donner le nom de l'evenement : ");
                char E[50];
                fgets(E, sizeof(E), stdin);
                E[strcspn(E, "\n")] = 0;  // Remove the newline character
                afficherToutesInformationsEvenement(teteEvenement, E);
                break;
            }
            case 3:
                supprimerEvenement(&teteEvenement);
                break;
            case 4:
                teteOrganisateur = importerInfosOrg(teteOrganisateur, "organisateurs.txt");
                afficherOrganisateurs(teteOrganisateur);
                libererListeOrganisateurs(teteOrganisateur);
                break;
            case 5:
                sortir = 1;
                break;
            default:
                printf("Erreur : option invalide. Veuillez choisir une option valide.\n");
        }
    }

    libererListe(teteEvenement);
}

// ***********************************************************RESERVATION*********************************************************************************

// Structure pour le Client
typedef struct Client {
    int id;
    char nom_prenom[50];
} Cl;

// Structure pour les Chambres
typedef struct Chambre {
    int num;
    int etage;
    char t_lit[20];
    char dispo;      // Disponibilit  ('D' ou 'R')
} Ch;

// Structure pour une R servation
typedef struct Reservation {
    int id_reserv;
    char nom_client[50];
    char prenom_client[50];
    int id_chambre;
    char date_check_in[50];
    char date_check_out[50];
    int nb_accompagnants;
    int nb_chambres;
} Rsv;

typedef struct Activite {
    char jour[20];
    char heure[6];
    int duree;
    char nom_A[50];
} A;

typedef struct Noeud {
    char participant[50];
    char event[50];
    struct Noeud* suiv;
} Noeud;

Noeud* tete = NULL;
Noeud* queue = NULL;

// Fonction pour afficher les chambres disponibles
void dispo_chambre(const char *Chambres) {
    FILE *C;
    Ch chambres[MAX_LINES];
    char line[256];
    int i = 0;

    if ((C = fopen(Chambres, "r")) == NULL) {
        printf("\nImpossible d'ouvrir le fichier des chambres en lecture.\n");
        return;
    }
    // Lire les chambres depuis le fichier
    while (fgets(line, sizeof(line), C) && i < MAX_LINES) {
        sscanf(line, "%d %d %s %c", &chambres[i].num, &chambres[i].etage, chambres[i].t_lit, &chambres[i].dispo);
        i++;
    }
    fclose(C);
    // Afficher les chambres disponibles
    printf("\nChambres disponibles :\n");
    printf("Numero  | Et. | Type    | Disponibilite\n");
    printf("----------------------------------------\n");
    for (int j = 0; j < i; j++) {
        printf("%-8d| %-3d | %-8s| %c\n", chambres[j].num, chambres[j].etage, chambres[j].t_lit, chambres[j].dispo);
    }
}

// Fonction pour r server une chambre
void reserver(const char *Reservations, const char *Chambres) {
    FILE *R, *C;
    Ch chambres[MAX_LINES];
    int nb_chambres_disponibles = 0;
    int id_chambre, id_client, nb_accompagnants;
    char nom_client[50], prenom_client[50], date_check_in[50], date_check_out[50];
    char line[256];
    bool chambre_trouvee = false;

    // Charger les chambres
    if ((C = fopen(Chambres, "r")) == NULL) {
        printf("\nErreur : Impossible d'ouvrir le fichier '%s' en lecture.\n", Chambres);
        return;
    }

    while (fgets(line, sizeof(line), C)) {
        if (nb_chambres_disponibles >= MAX_LINES) {
            printf("\nErreur : Nombre maximal de chambres depasse (%d).\n", MAX_LINES);
            fclose(C);
            return;
        }
        sscanf(line, "%d %d %s %c",
               &chambres[nb_chambres_disponibles].num,
               &chambres[nb_chambres_disponibles].etage,
               chambres[nb_chambres_disponibles].t_lit,
               &chambres[nb_chambres_disponibles].dispo);
        nb_chambres_disponibles++;
    }
    fclose(C);

    // Collecter les informations du client
    printf("\nEntrez votre nom : ");
    scanf("%s", nom_client);
    printf("Entrez votre prenom : ");
    scanf("%s", prenom_client);
    printf("Entrez le nombre d'accompagnants : ");
    if (scanf("%d", &nb_accompagnants) != 1 || nb_accompagnants < 0) {
        printf("\nErreur : Nombre d'accompagnants invalide.\n");
        return;
    }
    printf("Entrez le numero de la chambre a reserver : ");
    if (scanf("%d", &id_chambre) != 1) {
        printf("\nErreur : Numero de chambre invalide.\n");
        return;
    }
    printf("Entrez la date du check-in (--/--/----) : ");
    scanf("%s", date_check_in);
    printf("Entrez la date du checkout (--/--/----) : ");
    scanf("%s", date_check_out);

    // V rifier et mettre   jour la disponibilit  de la chambre
    for (int i = 0; i < nb_chambres_disponibles; i++) {
        if (chambres[i].num == id_chambre) {
            if (chambres[i].dispo == 'D') {
                chambres[i].dispo = 'R'; // R server la chambre
                chambre_trouvee = true;
                printf("Chambre %d reservee avec succes !\n", id_chambre);
                break;
            } else {
                printf("La chambre %d est deja reservee !\n", id_chambre);
                return;
            }
        }
    }

    if (!chambre_trouvee) {
        printf("Chambre %d non trouvee !\n", id_chambre);
        return;
    }

    // Sauvegarder les chambres mises   jour
    if ((C = fopen(Chambres, "w")) == NULL) {
        printf("\nErreur : Impossible d'ouvrir le fichier '%s' en ecriture.\n", Chambres);
        return;
    }

    for (int i = 0; i < nb_chambres_disponibles; i++) {
        fprintf(C, "%d %d %s %c\n", chambres[i].num, chambres[i].etage,
                chambres[i].t_lit, chambres[i].dispo);
    }
    fclose(C);

    // Enregistrer la r servation
    if ((R = fopen(Reservations, "a")) == NULL) {
        printf("\nErreur : Impossible d'ouvrir le fichier '%s' en ecriture.\n", Reservations);
        return;
    }

    fprintf(R, "Client nom: %s, prenom: %s, Chambre: %d, Accompagnants: %d, Check-in: %s, Check-out: %s\n",
            nom_client, prenom_client, id_chambre, nb_accompagnants, date_check_in, date_check_out);

    fclose(R);
    printf("Reservation enregistree avec succes.\n");
}

void Chambres_Reservations() {
    const char *Chambres = "./Chambres.txt";
    const char *Reservations = "./Reservations.txt";
    printf("Bienvenu a l'espace reservation\n");
    printf("1. Afficher les chambres disponibles\n");
    printf("2. Reserver une chambre\n");
    printf("3. Quitter\n");
    int option;
    int sortir = 0;
    while (sortir == 0) {
        printf("Choisir une option : ");
        scanf("%d", &option);
        switch (option) {
            case 1:
                dispo_chambre(Chambres);
                break;
            case 2:
                reserver(Reservations, Chambres);
                break;
            case 3:
                printf("Merci et a bientot !\n");
                sortir = 1;
                break;
            default:
                printf("Erreur : choisir une option valide\n");
        }
    }
}
//****************************************************************Activit s**********************************************************************************

// Convert a string to lowercase
void to_lowercase(char *dest, const char *src) {
    while (*src) {
        *dest = tolower((unsigned char)*src);
        dest++;
        src++;
    }
    *dest = '\0';
}

void afficher_itineraires(const char *participant, const char *jour) {
    // Tableau des activit s
    A activites[10] = {
        {"lundi", "08:00", 30, "Yoga"},
        {"lundi", "09:00", 60, "Excursion"},
        {"lundi", "11:00", 45, "Monuments"},
        {"mardi", "10:00", 90, "Visite de galerie"},
        {"mardi", "14:00", 120, "Visite des monuments"},
        {"mercredi", "08:30", 60, "Visite des monuments"},
        {"mercredi", "10:00", 45, "Visite de galerie"},
        {"jeudi", "09:00", 60, "Tour de la ville"},
        {"vendredi", "08:00", 120, "Yoga"},
        {"samedi", "10:00", 90, "Excursion"},
    };

    // Ouvrir le fichier en mode ajout
    FILE *It = fopen("It.txt", "a");
    if (It == NULL) {
        perror("Erreur lors de l'ouverture du fichier It.txt");
        return;
    }

    char jour_lower[20];
    char activite_jour_lower[20];

    // Convertir le jour en minuscules
    to_lowercase(jour_lower, jour);

    printf("Itineraires pour le jour : %s\n", jour);
    printf("----------------------------------------\n");
    printf("| Heure  | Dur e (min) | Activite       |\n");
    printf("----------------------------------------\n");

    int trouve = 0; // Flag pour v rifier si des itin raires sont trouv s
    for (int i = 0; i < 10; i++) {
        to_lowercase(activite_jour_lower, activites[i].jour);
        if (strcmp(activite_jour_lower, jour_lower) == 0) {
            printf("| %-6s | %-11d | %-15s |\n",
                   activites[i].heure,
                   activites[i].duree,
                   activites[i].nom_A);

            //  crire les informations dans le fichier
            fprintf(It, "Participant: %s, Jour: %s, Heure: %s, Duree: %d, Activite: %s\n",
                    participant, activites[i].jour, activites[i].heure, activites[i].duree, activites[i].nom_A);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucun itineraire trouve pour ce jour.\n");
    } else {
        printf("\nLes itineraires ont ete enregistres dans le fichier It.txt.\n");
    }

    printf("----------------------------------------\n");

    // Fermer le fichier
    fclose(It);
}

void club_de_lecture(const char* participant, const char* event) {
    // Allocation m moire pour le nouveau n ud
    Noeud* nouveau = (Noeud*)malloc(sizeof(Noeud));
    if (nouveau == NULL) {
        printf("Erreur d'allocation memoire.\n");
        return;
    }

    // Initialisation des champs du n ud
    strcpy(nouveau->participant, participant);
    strcpy(nouveau->event, event);
    nouveau->suiv = NULL;

    // Ajouter le n ud   la file
    if (tete == NULL && queue == NULL) {
        // Cas o  la file est vide
        tete = queue = nouveau;
    } else {
        // Cas o  la file n'est pas vide
        queue->suiv = nouveau;
        queue = nouveau;
    }

    // Enregistrer les informations dans le fichier
    FILE* fichier = fopen("lecture.txt", "a");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        return;
    }
    fprintf(fichier, "Participant: %s, Evenement: %s\n", participant, event);
    fclose(fichier);

    printf("Participant '%s' inscrit pour l'evenement '%s'.\n", participant, event);
}

void activites_sportives(const char *participant, const char *jour) {
    // Tableau des activit s
    A activites[10] = {
        {"Lundi", "08:00", 30, "Yoga"},
        {"Mardi", "10:00", 90, "Cours de natation"},
        {"Mardi", "14:00", 90, "Cours de natation"},
        {"Mercredi", "08:30", 60, "Yoga"},
        {"Mercredi", "10:00", 45, "Tennis"},
        {"Jeudi", "09:00", 60, "Paddel"},
        {"Vendredi", "08:00", 90, "Equitation"},
        {"Samedi", "10:00", 90, "Equitation"},
    };

    // Ouvrir le fichier en mode ajout
    FILE *AC = fopen("AC.txt", "a");
    if (AC == NULL) {
        perror("Erreur lors de l'ouverture du fichier AC.txt");
        return;
    }

    printf("Activites pour le jour : %s\n", jour);
    printf("----------------------------------------\n");
    printf("| Heure  | Duree (min) | Activit        |\n");
    printf("----------------------------------------\n");

    int trouve = 0; // Flag pour v rifier si des activit s sont trouv es
    for (int i = 0; i < 8; i++) {
        if (strcmp(activites[i].jour, jour) == 0) {
            printf("| %-6s | %-11d | %-15s |\n",
                   activites[i].heure,
                   activites[i].duree,
                   activites[i].nom_A);

            //  crire les informations dans le fichier
            fprintf(AC, "Participant: %s, Jour: %s, Heure: %s, Dur e: %d, Activite: %s\n",
                    participant, jour, activites[i].heure, activites[i].duree, activites[i].nom_A);
            trouve = 1;
        }
    }

    if (!trouve) {
        printf("Aucune activite trouvee pour ce jour.\n");
    } else {
        printf("\nLes informations ont ete enregistrees\n");
    }

    printf("----------------------------------------\n");

    // Fermer le fichier
    fclose(AC);
}

void Actvites_Offres() {
    int sortir = 0;
    while (sortir == 0) {
        printf("Voici les Activites qu'on offre:\n");
        printf("1. Itineraires\n");
        printf("2. Club de lecture\n");
        printf("3. Activites Sportives\n");
        printf("4. Quitter\n");
        printf("*** Choisir une option ***\n");
        int option;
        scanf("%d", &option);
        getchar();  // Consommer le '\n' restant apr s scanf

        switch (option) {
            case 1: {
                char jour[10], participant[50];
                printf("Participant: ");
                fgets(participant, sizeof(participant), stdin);
                participant[strcspn(participant, "\n")] = 0;  // Remove the newline character
                printf("Jour: ");
                fgets(jour, sizeof(jour), stdin);
                jour[strcspn(jour, "\n")] = 0;  // Remove the newline character
                afficher_itineraires(participant, jour);
                break;
            }
            case 2: {
                char jour[10], participant[50];
                printf("Jour: ");
                fgets(jour, sizeof(jour), stdin);
                jour[strcspn(jour, "\n")] = 0;  // Remove the newline character
                printf("Nom de participant: ");
                fgets(participant, sizeof(participant), stdin);
                participant[strcspn(participant, "\n")] = 0;  // Remove the newline character
                club_de_lecture(participant, jour);
                break;
            }
            case 3: {
                char participant[50], jour[50];
                printf("Entrez votre nom et prenom : ");
                fgets(participant, sizeof(participant), stdin);
                participant[strcspn(participant, "\n")] = 0;  // Remove the newline character
                printf("Entrez le jour pour afficher les activites sportives : ");
                fgets(jour, sizeof(jour), stdin);
                jour[strcspn(jour, "\n")] = 0;  // Remove the newline character
                activites_sportives(participant, jour);
                break;
            }
            case 4: {
                sortir = 1;
                break;
            }
            default:
                printf("Erreur : choisir une option valide\n");
        }
    }
}
//***********************************************************main_programme*************************************************************
    int main() {
        printf("Bienvenu! Comment peut-on vous aider?\n");
        int sortir = 0;  // Initialize the variable to control the loop
        while (sortir == 0) {
            printf("1. Chambres et Reservation\n");
            printf("2. Evenements\n");
            printf("3. Activites et Offres\n");
            printf("4. Animaux domestiques\n");
            printf("5. Quitter\n");
            printf("*** Choisir une option ***\n");
            int option;
            scanf("%d", &option);  // Read the user's choice
            switch (option)
            {
                case 1:
                    Chambres_Reservations();break;
                case 2:
                    Evenements();break;
                case 3:
                    Actvites_Offres();break;
                case 4:
                    Animaux();break;
                case 5:
                    printf("Merci pour votre visite. Au revoir!\n");
                    sortir = 1;
                default:
                    printf("Choix invalide");
            }
            }



        return 0;
}
