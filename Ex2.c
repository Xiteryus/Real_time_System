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

//ordononceur 

// EDF : priorité dynamique 
int ordo_EDF(Task *tasks, int nb_tasks) {
    int best = -1;
    for (int i = 0; i < nb_tasks; i++) {
        if (tasks[i].rem > 0) {
            if (best == -1 || tasks[i].deadline < tasks[best].deadline) {
                best = i;
            }
        }
    }
    return best;
}


// SIMULATION

void simulate(Task *tasks, int nb_tasks, int (*scheduler)(Task*, int), const char *name) {
    printf("\nSimulation %s :\n", name);

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

        // 3) Ordonnanceur
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


int main(void) {
    int nb_tasks;
    int ordo;
    printf("Combien de tâches voulez-vous simuler ? ");
    scanf("%d", &nb_tasks);

    Task *tasks = malloc(nb_tasks * sizeof(Task));
    if (!tasks) {
        perror("Erreur malloc");
        return 1;
    }

    // Lecture des tâches
    for (int i = 0; i < nb_tasks; i++) {
        tasks[i].id = i + 1;
        printf("\nTâche %d :\n", tasks[i].id);
        printf("Durée (C) : "); scanf("%d", &tasks[i].duree);
        printf("Échéance (D) : "); scanf("%d", &tasks[i].echeance);
        printf("Période (P) : "); scanf("%d", &tasks[i].periode);
        printf("Priorité : (pas utile pour EDF)"); scanf("%d", &tasks[i].priorite);
    }

    // Lancer plusieurs simulations avec les mêmes tâches
    simulate(tasks,nb_tasks,ordo_EDF,"Earliest deadline first (EDF)");
    

    free(tasks);
    return 0;
}
