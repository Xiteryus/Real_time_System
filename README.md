# Real_time_System
TP sur les système temps réel (ordonnancement en C) 

## Exercice 1 : étude de la faisabilité

Lancement de la simulation 
```
gcc Ex1.c -o Ex1
./Ex1 
```
1. Pour HFP : pas de faisabilité pour ces taches 

| Tâche | C (exec) | D (échéance) | T (période) | P (priorité) |
|-------|----------|--------------|-------------|--------------|
| **Thread 1** | 2 | 7 | 7 | 20 |
| **Thread 2** | 3 | 11 | 11 | 15 |
| **Thread 3** | 5 | 13 | 13 | 10 |

```
Simulation HPF :
t= 0 : Execution T1 (restant=1, deadline=7)
t= 1 : Execution T1 (restant=0, deadline=7)
t= 2 : T1 terminé
t= 2 : Execution T2 (restant=2, deadline=11)
t= 3 : Execution T2 (restant=1, deadline=11)
t= 4 : Execution T2 (restant=0, deadline=11)
t= 5 : T2 terminé
t= 5 : Execution T3 (restant=4, deadline=13)
t= 6 : Execution T3 (restant=3, deadline=13)
t= 7 : Execution T1 (restant=1, deadline=14)
t= 8 : Execution T1 (restant=0, deadline=14)
t= 9 : T1 terminé
t= 9 : Execution T3 (restant=2, deadline=13)
t=10 : Execution T3 (restant=1, deadline=13)
t=11 : Execution T2 (restant=2, deadline=22)
t=12 : Execution T2 (restant=1, deadline=22)
Deadline manquée : T3 à t=13 (deadline=13, restant=1)
```

2. Pour généraliser notre application, on demande à l'utilisateur le nombre de tache qu'il veut executer : 
```
Combien de tâches voulez-vous simuler ? 3

Tâche 1 :
Durée (C) : 2
Échéance (D) : 7
Période (P) : 7
Priorité : 20

Tâche 2 :
Durée (C) : 3
Échéance (D) : 11
Période (P) : 11
Priorité : 15

Tâche 3 :
Durée (C) : 5
Échéance (D) : 13
Période (P) : 13
Priorité : 10
```

3. On ajoute les ordononceurs statique RM et DM : 
```
Simulation Rate Monotonic (RM) :
t= 0 : Execution T1 (restant=1, deadline=7)
t= 1 : Execution T1 (restant=0, deadline=7)
t= 2 : T1 terminé
t= 2 : Execution T2 (restant=2, deadline=11)
t= 3 : Execution T2 (restant=1, deadline=11)
t= 4 : Execution T2 (restant=0, deadline=11)
t= 5 : T2 terminé
t= 5 : Execution T3 (restant=4, deadline=13)
t= 6 : Execution T3 (restant=3, deadline=13)
t= 7 : Execution T1 (restant=1, deadline=14)
t= 8 : Execution T1 (restant=0, deadline=14)
t= 9 : T1 terminé
t= 9 : Execution T3 (restant=2, deadline=13)
t=10 : Execution T3 (restant=1, deadline=13)
t=11 : Execution T2 (restant=2, deadline=22)
t=12 : Execution T2 (restant=1, deadline=22)
Deadline manquée : T3 à t=13 (deadline=13, restant=1)
```
```
Simulation Deadline Monotonic (DM) :
t= 0 : Execution T1 (restant=1, deadline=7)
t= 1 : Execution T1 (restant=0, deadline=7)
t= 2 : T1 terminé
t= 2 : Execution T2 (restant=2, deadline=11)
t= 3 : Execution T2 (restant=1, deadline=11)
t= 4 : Execution T2 (restant=0, deadline=11)
t= 5 : T2 terminé
t= 5 : Execution T3 (restant=4, deadline=13)
t= 6 : Execution T3 (restant=3, deadline=13)
t= 7 : Execution T1 (restant=1, deadline=14)
t= 8 : Execution T1 (restant=0, deadline=14)
t= 9 : T1 terminé
t= 9 : Execution T3 (restant=2, deadline=13)
t=10 : Execution T3 (restant=1, deadline=13)
t=11 : Execution T2 (restant=2, deadline=22)
t=12 : Execution T2 (restant=1, deadline=22)
Deadline manquée : T3 à t=13 (deadline=13, restant=1)
```

4. // 

## Exercice 2 : Ordonnanceur EDF

Lancement de la simulation 
```
gcc Ex2.c -o Ex2
./Ex2
```
Exemple pour ces tâches(pas de priorité necessaire pour EDF) : 

| Tâche | C (exec) | D (échéance) | T (période) | P (priorité) |
|-------|----------|--------------|-------------|--------------|
| **Thread 1** | 3 | 8 | 8 | / |
| **Thread 2** | 3 | 12 | 12 | / |
| **Thread 3** | 3 | 14 | 14 | / |
| **Thread 4** | 3 | 20 | 20 | / |

````
Simulation Earliest deadline first (EDF) :
t= 0 : Execution T1 (restant=2, deadline=8)
t= 1 : Execution T1 (restant=1, deadline=8)
t= 2 : Execution T1 (restant=0, deadline=8)
t= 3 : T1 terminé
t= 3 : Execution T2 (restant=2, deadline=12)
t= 4 : Execution T2 (restant=1, deadline=12)
t= 5 : Execution T2 (restant=0, deadline=12)
t= 6 : T2 terminé
t= 6 : Execution T3 (restant=2, deadline=14)
t= 7 : Execution T3 (restant=1, deadline=14)
t= 8 : Execution T3 (restant=0, deadline=14)
t= 9 : T3 terminé
t= 9 : Execution T1 (restant=2, deadline=16)
t=10 : Execution T1 (restant=1, deadline=16)
t=11 : Execution T1 (restant=0, deadline=16)
t=12 : T1 terminé
t=12 : Execution T4 (restant=2, deadline=20)
t=13 : Execution T4 (restant=1, deadline=20)
t=14 : Execution T4 (restant=0, deadline=20)
t=15 : T4 terminé
t=15 : Execution T2 (restant=2, deadline=24)
t=16 : Execution T1 (restant=2, deadline=24)
t=17 : Execution T1 (restant=1, deadline=24)
t=18 : Execution T1 (restant=0, deadline=24)
t=19 : T1 terminé
t=19 : Execution T2 (restant=1, deadline=24)
t=20 : Execution T2 (restant=0, deadline=24)
t=21 : T2 terminé
t=21 : Execution T3 (restant=2, deadline=28)
t=22 : Execution T3 (restant=1, deadline=28)
t=23 : Execution T3 (restant=0, deadline=28)
t=24 : T3 terminé
t=24 : Execution T1 (restant=2, deadline=32)
t=25 : Execution T1 (restant=1, deadline=32)
t=26 : Execution T1 (restant=0, deadline=32)
t=27 : T1 terminé
t=27 : Execution T2 (restant=2, deadline=36)
t=28 : Execution T2 (restant=1, deadline=36)
t=29 : Execution T2 (restant=0, deadline=36)
t=30 : T2 terminé

Simulation terminée sans deadline manquée (30 unités).
````

Pas d'affichage graphique

## Exercice 3 : mini projet