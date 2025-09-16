#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define MAX_TIME 30   // durée de la simulation en secondes

typedef struct {
    int id, duree, echeance, periode, priorite;
    int rem;
    int deadline;
    int next_release;
} Task;

// ------------------------- ORDONNANCEURS -------------------------

// HPF : priorité fixe donnée par l’utilisateur
int scheduler_HPF(Task *tasks, int nb_tasks) {
    int best = -1;
    for (int i = 0; i < nb_tasks; i++) {
        if (tasks[i].rem > 0) {
            if (best == -1 || tasks[i].priorite > tasks[best].priorite)
                best = i;
        }
    }
    return best;
}

// RM : plus la periode est petit -> plus prioritaire
int scheduler_RM(Task *tasks, int nb_tasks) {
    int best = -1;
    for (int i = 0; i < nb_tasks; i++) {
        if (tasks[i].rem > 0) {
            if (best == -1 || tasks[i].periode < tasks[best].periode)
                best = i;
        }
    }
    return best;
}

// DM : plus la deadline est petit -> plus prioritaire
int scheduler_DM(Task *tasks, int nb_tasks) {
    int best = -1;
    for (int i = 0; i < nb_tasks; i++) {
        if (tasks[i].rem > 0) {
            if (best == -1 || tasks[i].echeance < tasks[best].echeance)
                best = i;
        }
    }
    return best;
}

// SIMULATION

void simulate(Task *tasks, int nb_tasks, int (*scheduler)(Task*, int), const char *name) {
    printf("\n=== Simulation %s ===\n", name);

    // Initialisation
    for (int i = 0; i < nb_tasks; i++) {
        tasks[i].rem = 0;
        tasks[i].deadline = 0;
        tasks[i].next_release = 0;
    }

    // 
    for (int t = 0; t < MAX_TIME; t++) {
        // 1) test deadlines
        for (int i = 0; i < nb_tasks; i++) {
            if (tasks[i].rem > 0 && t >= tasks[i].deadline) {
                printf("Deadline manquée : T%d à t=%d (deadline=%d, restant=%d)\n",
                       tasks[i].id, t, tasks[i].deadline, tasks[i].rem);
                return;
            }
        }

        // 2) 
        for (int i = 0; i < nb_tasks; i++) {
            if (t == tasks[i].next_release) {
                tasks[i].rem = tasks[i].duree;
                tasks[i].deadline = t + tasks[i].echeance;
                tasks[i].next_release += tasks[i].periode;

            }
        }

        // 3) Choisir tâche avec ordonnanceur
        int best = scheduler(tasks, nb_tasks);

        // 4) Exécution
        if (best == -1) {
            printf("t=%2d : Idle\n", t);
        } else {
            tasks[best].rem--;
            printf("t=%2d : Execution T%d (restant=%d, deadline=%d)\n",
                   t, tasks[best].id, tasks[best].rem, tasks[best].deadline);
            if (tasks[best].rem == 0)
                printf("t=%2d : T%d terminé\n", t+1, tasks[best].id);
        }

        sleep(1);
    }

    printf("\nSimulation terminée sans deadline manquée (%d unités).\n", MAX_TIME);
}

// ------------------------- MAIN -------------------------

int main(void) {
    int nb_tasks;
    int ordo;
    printf("Combien de tâches voulez-vous simuler ? ");
    scanf("%d", &nb_tasks);

    // Allocation dynamique
    Task *tasks = malloc(nb_tasks * sizeof(Task));
    if (!tasks) {
        perror("Erreur malloc");
        return 1;
    }

    // Lecture des tâches
    for (int i = 0; i < nb_tasks; i++) {
        tasks[i].id = i + 1;
        printf("\n--- Tâche %d ---\n", tasks[i].id);
        printf("Durée (C) : "); scanf("%d", &tasks[i].duree);
        printf("Échéance (D) : "); scanf("%d", &tasks[i].echeance);
        printf("Période (P) : "); scanf("%d", &tasks[i].periode);
        printf("Priorité : "); scanf("%d", &tasks[i].priorite);
    }

    // Lancer plusieurs simulations avec les mêmes tâches
    printf("Quels ordononeur voulez-vous choisir ? (0 - HPF; 1 - RM; 2 - DM)");
    scanf("%d", &ordo);
    if(ordo == 0)
        simulate(tasks, nb_tasks, scheduler_HPF, "HPF");
    else{ if(ordo==1)simulate(tasks, nb_tasks, scheduler_RM,  "Rate Monotonic (RM)");
    else {if(ordo==2)simulate(tasks, nb_tasks, scheduler_DM,  "Deadline Monotonic (DM)");}} 
    

    free(tasks);
    return 0;
}
