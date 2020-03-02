
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "simulation.h"
#include "menu.h"
#include "config_vehicle_object.h"
#include "config_c_station.h"

//Funktion gibt zur ID passenden Ladesaeulenzeiger zurueck
struct c_station *search_c_station(int id){
    struct c_station *current = first_c_station;
    while(current != NULL){
        if(current->id == id){
            return current; //Wenn die ID gleich ist, gib den Zeiger auf diese Ladesaeule zurueck
        }
        current = current->next;
    }
    return NULL;
}

//Funktion zum Löschen aller Ladesäulen
void delete_all_c_station(){
    struct c_station *t_c_station_1, *t_c_station_2;
    if(first_c_station != NULL){
        t_c_station_1 = first_c_station->next;
        while(t_c_station_1!= NULL) {
            t_c_station_2 = t_c_station_1->next;
            first_c_station->next = t_c_station_1;
            free(t_c_station_1);
            t_c_station_1 = t_c_station_2;
        }
        free(first_c_station->next);
        free(first_c_station);
        first_c_station = NULL;
    }
}

//Funktion zum Löschen einer bestimmten Ladestation
void delete_c_station(){
    int id = 0, i = 0;

    struct c_station *t_c_station_1, *t_c_station_2;

    if(first_c_station == NULL){
        printf("Es gibt noch keine Ladestationen\n");
        return;
    }

    printf("Ladestationen:\n");
    output_c_station();
    printf("\n");

    printf("Welche Ladestation wollen Sie loeschen (bitte geben Sie die ID ein)?\n");
    scanf("%d", &id);

    if(first_c_station != NULL) {
        if(first_c_station->id == id) { //Loeschen, falls ID uebereinstimmt
            t_c_station_1 = first_c_station->next;
            delete_vehicle_object(first_c_station); //Löschen der zur Ladestation gehörenden Fahrzeuge
            free(first_c_station);
            first_c_station = t_c_station_1;
            i = 1;
        }
        else {
            t_c_station_1 = first_c_station;
            while(t_c_station_1->next != NULL) {
                t_c_station_2 = t_c_station_1->next;
                if(t_c_station_2->id == id) { //Loeschen, falls ID uebereinstimmt
                    t_c_station_1->next = t_c_station_2->next;
                    delete_vehicle_object(t_c_station_2); //Löschen der zur Ladestation gehörenden Fahrzeuge
                    free(t_c_station_2);
                    i = 1;
                    break;
                    }
                    t_c_station_1 = t_c_station_2;
                }
            }
        }
        if(i == 1){
            printf("\n");
            printf("Die Ladestation mit der ID %d wurde erfolgreich geloescht\n", id);
            printf("\n");
        }
        else{
            printf("\n");
            printf("Es gibt keine Ladestation mit der passenden ID (%d)\n", id);
            printf("\n");
        }
    }

//Funktion zur Bearbeitung einer bestimmten Ladestation
void edit_c_station(){

    int id = 0, input, t_max_vehicles, t_init_capacity, t_aux_capacity, t_charge_duration;

    struct c_station *current = first_c_station;

    if(current == NULL){
        printf("Es gibt noch keine Ladestationen.\n");
        return;

    }

    printf("Ladestationen:\n");
    output_c_station();
    printf("\n");

    printf("Welche Ladestation wollen Sie bearbeiten (bitte geben Sie die ID ein)?\n");
    scanf("%d", &id);

    while(current != NULL) { //Schleife zum Finden des zur ID passenden Ladestationszeigers
        if (current->id == id) {
            break;
        } else {
            current = current->next;
        }
    }

     if(current == NULL){
        printf("\n");
        printf("Es gibt keine Ladestation mit der passenden ID (%d)\n", id);
        return;
    }
    else{
        printf("\n");
        printf("Welches Attribut moechten Sie bearbeiten? \n");
        printf("1. Maximale Anzahl an Fahrzeugen, 2. Initiale Kapazitaet\n");
        printf("3. Reservekapazitaet, 4. Wiederaufladedauer\n");
        printf("Bitte geben sie die gewuenschte Zahl ein:\n");

        do{
            scanf("%d", &input);
            if(input<1||input>4){
                printf("Falsche Eingabe, bitte waehlen Sie erneut:\n");
            }
        } while(input<1||input>4);

        printf("Eingabe der Aenderung: \n");

        switch (input){ //Aenderung des gewuenschten Parameters
            case 1:
                printf("Bitte geben Sie die neue maximale Anzahl an Fahrzeugen an:\n");
                scanf("%d", &t_max_vehicles);
                current->max_vehicles = t_max_vehicles;
                break;
            case 2:
                printf("Bitte geben Sie die neue initiale Kapazitaet der Ladesaeule an: \n");
                scanf("%d", &t_init_capacity);
                current->init_capacity = t_init_capacity;
                current->current_capacity = t_init_capacity;
                break;
            case 3:
                printf("Bitte geben Sie die neue Reservekapazitaet an: \n");
                scanf("%d", &t_aux_capacity);
                current->aux_capacity = t_aux_capacity;
                current->current_aux_capacity = t_aux_capacity;
                break;
            case 4:
                printf("Bitte geben Sie die neue Wiederaufladedauer der Ladesaeule an: \n");
                scanf("%d", &t_charge_duration);
                current->charge_duration = t_charge_duration;
                break;
        }
        printf("Die Aenderung wurde erfolgreich durchgefuehrt:\n");
        output_c_station();
    }
}

//Funktion zur manuellen Eingabe der Ladestationen
void input_c_station() {
    int t_max_vehicles, t_init_capacity, t_aux_capacity, t_charge_duration;
    printf("Eingabe der Ladestationsprototypen: \n");

    printf("Bitte geben Sie die maximale Anzahl an Fahrzeugen an, die die Ladesaeule gleichzeitig befahren koennen:\n");
    scanf("%d", &t_max_vehicles);

    printf("Bitte geben Sie die initiale Kapazitaet der Ladesaeule an: \n");
    scanf("%d", &t_init_capacity);

    printf("Bitte geben Sie die Reservekapazitaet an: \n");
    scanf("%d", &t_aux_capacity);

    printf("Bitte geben Sie die Wiederaufladedauer der Ladesaeule an: \n");
    scanf("%d", &t_charge_duration);

    append_c_station(t_max_vehicles, t_init_capacity, t_aux_capacity, t_charge_duration); //Haenge diese Ladestation an die Ladestationsliste an
}

//Funktion zur Ausgabe aller Ladestationen mit den zugehörigen Parametern
void output_c_station() {

    //Tabellenausgabe
    struct c_station *current = first_c_station;
    printf("||===============================================================================||\n");
    printf("| ID|Max.Anz.Fahrzeuge|Init.Kap.|Res.Kap.|Wiederaufladedauer|Akt.Kap.|Akt.Res.Kap.|\n");
    printf("||===============================================================================||\n");

    if(current == NULL){
        printf("| Es sind keine Ladestationen vorhanden                                           |\n");
        printf("|---------------------------------------------------------------------------------|\n");
    }

    while(current != NULL) { //Schleife zur Ausgabe der Attribute aller Ladestationen
        printf("| %-2d|%-17d| %-8d|%-8d|%-18d|%-8d|%-12d|\n",
               current->id,current->max_vehicles, current->init_capacity, current->aux_capacity, current->charge_duration, current->current_capacity, current->current_aux_capacity);
        printf("|---------------------------------------------------------------------------------|\n");
        current = current->next;
    }
}

//Funktion zum Anhängen neuer Ladestationen an die bestehende Liste
void append_c_station(int max_vehicles, int init_capacity, int aux_capacity, int charge_duration){
    struct c_station *t_c_station;
    int counter = 0; //Zaehlervariable zur korrekten Festlegung der ID der neuen Ladestation

    if(first_c_station == NULL) {
        if((first_c_station = malloc(sizeof(struct c_station))) == NULL) {
            printf("Fehler: Es konnte kein Speicherplatz allokiert werden\n");
            return;
        }
        //Zuordnung der Werte fuer das erste Listenelement
        first_c_station->id = counter;
        first_c_station->max_vehicles = max_vehicles;
        first_c_station->init_capacity = init_capacity;
        first_c_station->aux_capacity = aux_capacity;
        first_c_station->current_capacity = init_capacity;
        first_c_station->current_aux_capacity = aux_capacity;
        first_c_station->charge_duration = charge_duration;
        first_c_station->next = NULL;
        first_c_station->first = NULL;
    }
    else {

        t_c_station = first_c_station;
        //Gehe zum letzten Element
        while(t_c_station->next != NULL){
            t_c_station = t_c_station->next;
            counter++;
        }

        if((t_c_station->next = malloc(sizeof(struct c_station))) == NULL) {
            printf("Fehler: Es konnte kein Speicheplatz allokiert werden\n");
            return;
        }

        counter++;

        t_c_station = t_c_station->next;
        //Zuordnen der uebergebenen Werte, falls Element nicht das erste Element ist
        t_c_station->id = counter;
        t_c_station->max_vehicles = max_vehicles;
        t_c_station->init_capacity = init_capacity;
        t_c_station->aux_capacity = aux_capacity;
        t_c_station->current_capacity = init_capacity;
        t_c_station->current_aux_capacity = aux_capacity;
        t_c_station->charge_duration = charge_duration;
        t_c_station->next = NULL;
        t_c_station->first = NULL;
    }
}

//Funktion zum Speichern der Ladestationskonfiguration
void save_c_config(){
    FILE *config = fopen("c_config.csv", "w");
    struct c_station *t_c_station;

    if (config == NULL){
        printf("Es konnte keine Datei erstellt werden\n");
        fclose(config); //Ordnungsgemaesses schließen des Filestreams
        return;
    }

    if(first_c_station == NULL){
        printf("Es sind keine Ladestationsprototypen vorhanden\n");
        fclose(config); //Ordnungsgemaesses schließen des Filestreams
        return;
    }

    t_c_station = first_c_station;

    while ((t_c_station)  != NULL){ //Schreiben der Ladestationskonfiguration in eine Datei
        fprintf(config, "%d,%d,%d,%d,%d;\n", t_c_station->id, t_c_station->max_vehicles, t_c_station->init_capacity,
                t_c_station->aux_capacity, t_c_station->charge_duration);
        t_c_station = t_c_station->next;
    }

    printf("\n");
    printf("Aktuelle Ladestationskonfiguration wurde gespeichert\n");
    printf("\n");

    fclose(config);
}

//Funktion zum Importieren der Ladestationen aus der Konfigurationsdatei
void import_c_config(){
    FILE *config = fopen("c_config.csv", "r");
    int t_id, t_max_vehicles, t_init_capacity, t_aux_capacity, t_charge_duration;

    if (config == NULL){
        printf("Es konnte keine Datei geöffnet werden\n");
        fclose(config);
        return;
    }


    while((fscanf(config,"%d,%d,%d,%d,%d;\n", &t_id, &t_max_vehicles, &t_init_capacity, &t_aux_capacity, &t_charge_duration)) != EOF){ //Lesen aus der formatierten gespeicherten Konfigurationsdatei
        append_c_station(t_max_vehicles, t_init_capacity, t_aux_capacity, t_charge_duration); //Anhaengen der eingelesenen Werte
    }

    printf("\n");
    printf("Gespeicherte Ladestationskonfiguration wurde geladen\n");
    printf("\n");


    fclose(config);
}
