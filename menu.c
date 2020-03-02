
#include <stdio.h>
#include <stdlib.h>
#include "struct.h"
#include "menu.h"
#include "config_c_station.h"
#include "config_vehicle.h"
#include "config_vehicle_object.h"
#include "simulation.h"

//Funktion zum Beenden und Freigeben des Speicherplatzes
void close(){
    delete_all_vehicle_object(); //Freigeben des gesamten reservierten Speichers zum ordnungsgemaessen Beenden
    delete_all_c_station();
    delete_all_vehicle();
    exit(0); //Programmende ohne Fehler
}

//Hauptmenue
void menu(){
    int input = 0;
    do{ //Endlosschleife
        printf("\n");
        printf("Willkommen im Hauptmenue:\n");
        printf("Sie koennen waehlen:\n");
        printf("Konfiguration der Infrastruktur..............1\n");
        printf("Fahrzeugzuordnung ...........................2\n");
        printf("Simulationsmenue.............................3\n");
        printf("\n");
        printf("Beenden des Programms :(.....................0\n");
        printf("Bitte geben Sie die gewuenschte Zahl ein:\n");
    do{
        scanf("%d", &input);
        if(input<0||input>3){
            printf("Falsche Eingabe, bitte waehlen Sie erneut:\n");
        }
    } while(input<0||input>3); //Begrenzung der Eingabe auf erlaubte Zustaende

    switch (input){
        case 0: close();
            break;
        case 1: config_menu();
            break;
        case 2: create_menu();
            break;
        case 3: sim_menu();
            break;
    }}while(1);
}

//Menü zum Hinzufügen von Fahrzeugobjekten und speichern/importieren der gesamten Konfiguration
void create_menu(){
    int input = 0;
    do{
        printf("\n");
        printf("Willkommen im Menue zur Erzeugung von Objekten:\n");
        printf("Sie koennen waehlen:\n");
        printf("\n");
        printf("Hinzufuegen eines Autos zu einer Ladestation.......1\n");
        printf("Anzeigen aller hinzugefuegten Autos................2\n");
        printf("Gesamtkonfiguration speichern......................3\n");
        printf("Gesamtkonfiguration importieren....................4\n");
        printf("\n");
        printf("Zurueck zum Hauptmenue.............................0\n");

    do{
        scanf("%d", &input);
        if(input<0||input>4){
            printf("Falsche Eingabe, bitte waehlen Sie erneut:\n");
        }
    } while(input<0||input>4);

    switch (input){
        case 0: return;
            break;
        case 1: append_vehicle_object(choose_c_station(), choose_vehicle_type()); //Anhaengen des vom Nutzer ausgewaehlten Fahrzeugs an die ausgewaehlte Ladesauele
            break;
        case 2: output_all_vehicle_object();
            break;
        case 3: save_config();
            break;
        case 4: import_config();
            break;
    }}while(1);
}

//Menü zur Konfiguration, bzw. Erstellung von Ladesäulen und Fahrzeugprototypen
void config_menu(){
    int input = 0;
    do{
        printf("\n");
        printf("Willkommen im Konfigurationsmenue\n");
        printf("Sie koennen waehlen:\n");
        printf("\n");
        printf("Ladestation erstellen............................1\n");
        printf("Ladestationen anzeigen...........................2\n");
        printf("Ladestationen aendern............................3\n");
        printf("Ladestationen loeschen...........................4\n");
        printf("Ladestationskonfiguration speichern..............5\n");
        printf("Ladestationskonfiguration importieren............6\n");
        printf("\n");
        printf("Elektrofahrzeugtyp erstellen.....................7\n");
        printf("Elektrofahrzeugtyp anzeigen......................8\n");
        printf("Elektrofahrzeugtyp aendern.......................9\n");
        printf("Elektrofahrzeugtyp loeschen.....................10\n");
        printf("Elektrofahrzeugtypen speichern..................11\n");
        printf("Elektrofahrzeugtypen importieren................12\n");
        printf("\n");
        printf("(mit Fahrzeuguordnung zu den Ladestationen)\n");
        printf("Gesamtkonfiguration speichern...................13\n");
        printf("Gesamtkonfiguration importieren.................14\n");
        printf("\n");
        printf("Zurueck zum Hauptmenue............................0\n");

    do{
        scanf("%d", &input);
        if(input<0||input>14){
            printf("Falsche Eingabe, bitte waehlen Sie erneut:\n");
        }
    } while(input<0||input>14);

    switch (input){
        case 0: return;
            break;
        case 1: input_c_station();
                printf("Ladestationen:\n");
                output_c_station();
            break;
        case 2: printf("Ladestationen:\n");
                output_c_station();
            break;
        case 3: edit_c_station();
            break;
        case 4: delete_c_station();
            break;
        case 5: save_c_config();
            break;
        case 6: import_c_config();
            break;
        case 7: input_vehicle();
                printf("Fahrzeugtypen:\n");
                output_vehicle();
            break;
        case 8: printf("Fahrzeugtypen:\n");
                output_vehicle();
            break;
        case 9: edit_vehicle();
            break;
        case 10: delete_vehicle();
            break;
        case 11: save_vehicle_config();
            break;
        case 12: import_vehicle_config();
            break;
        case 13: save_config();
            break;
        case 14: import_config();
            break;
    }}while(1);
}

//Menü zum Ablauf der Simulation
void sim_menu(){
    int input = 0;
    do{
        printf("\n");
        printf("Willkommen im Menue der Simulation:\n");
        printf("Sie koennen waehlen:\n");
        printf("Simulation starten.................................1\n");
        printf("Simulation mit variablen Zeitschritten starten.....2\n");
        printf("Zeit vergehen lassen, ohne dass etwas passiert.....3\n");
        printf("\n");
        printf("Zurueck zum Hauptmenue.............................0\n");

    do{
        scanf("%d", &input);
        if(input<0||input>3){
            printf("Falsche Eingabe, bitte waehlen Sie erneut:\n");
        }
    } while(input<0||input>3);

    switch (input){
        case 0: return;
            break;
        case 1: simulate();
            break;
        case 2: simulate_steps();
            break;
        case 3: jump_time();
            break;
    }}while(1);
}
