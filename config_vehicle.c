
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "menu.h"
#include "config_vehicle.h"
#include "config_vehicle_object.h"

//Funktion gibt zur ID passenden Fahrzeugtyp zurück
struct vehicle_type *search_vehicle_type(int id){
    struct vehicle_type *current = first_vehicle_type;
    while(current != NULL){
        if(current->id == id){
            return current; //Gib Fahrzeug mit passender ID zurück
        }
        current = current->next;
    }
    return NULL; //NULL wird zurückgegeben, falls kein passendes Element gefunden wird
}

//Funktion zum Löschen aller Fahrzeuge
void delete_all_vehicle(){ //Erforderlich fuer das Freigeben des Speichers bei schließen des Programms
    struct vehicle_type *t_vehicle_1, *t_vehicle_2;
    if(first_vehicle_type != NULL){
        t_vehicle_1 = first_vehicle_type->next;
        while(t_vehicle_1!= NULL) {
            t_vehicle_2 = t_vehicle_1->next;
            first_vehicle_type->next = t_vehicle_1;
            free(t_vehicle_1);
            t_vehicle_1 = t_vehicle_2;
        }
        free(first_vehicle_type->next);
        free(first_vehicle_type);
        first_vehicle_type = NULL;
    }
}

//Funktion zum Löschen eines bestimmten Fahrzeugprototyps
void delete_vehicle(){
    int id = 0, i = 0;

    struct vehicle_type *t_vehicle_type_1, *t_vehicle_type_2;

    if(first_vehicle_type == NULL){
        printf("Es gibt noch keine Fahrzeugtypen\n");
        return;
    }

    printf("Fahrzeugtypen:\n");
    output_vehicle();

    printf("\n");
    printf("Welches Fahrzeug wollen Sie loeschen (bitte geben Sie die ID ein)?\n");
    scanf("%d", &id);

    if(first_vehicle_type != NULL){
        if(first_vehicle_type->id == id){   //Falls erstes Fahrzeug die passende ID hat, wird der Speicherplatz freigegeben und der Anfangszeiger zeigt auf das 2. Element
            t_vehicle_type_1 = first_vehicle_type->next;
            free(first_vehicle_type);
            first_vehicle_type = t_vehicle_type_1;
            i = 1;
        }
        else{
            t_vehicle_type_1 = first_vehicle_type;
            while(t_vehicle_type_1->next != NULL){
                t_vehicle_type_2 = t_vehicle_type_1->next;
                if(t_vehicle_type_2->id == id){ //Speicherplatz wird freigegeben und die Zeiger werden angepasst
                    t_vehicle_type_1->next = t_vehicle_type_2->next;
                    free(t_vehicle_type_2);
                    i = 1; //Indikator, ob Fahrzeug erfolgreich geloescht wurde
                    break;
                }
                t_vehicle_type_1 = t_vehicle_type_2;
            }
        }
    }
    //Rueckmeldung fuer den Benutzer
    if(i == 1){
            printf("\n");
            printf("Das Fahrzeug mit der ID %d wurde erfolgreich geloescht\n" ,id);
            printf("\n");
        }
        else{
            printf("\n");
            printf("Es gibt kein Fahrzeug mit der passenden ID (%d)\n", id);
            printf("\n");
        }
}

//Funktion zum Bearbeiten eines bestimmten Fahrzeugprototyps
void edit_vehicle(){
    int id = 0, input = 0, t_priority, t_charge_duration;
    char t_brand[50], t_model[50];

    struct vehicle_type *current = first_vehicle_type;

    if(current == NULL){
        printf("Es gibt noch keine Fahrzeugtypen.\n");
        return;
    }

    printf("Fahrzeugtypen:\n");
    output_vehicle();

    printf("\n");
    printf("Welches Fahrzeug wollen Sie bearbeiten (bitte geben Sie die ID ein)?\n");
    scanf("%d", &id);

    while(current != NULL) { //Durchlaufe Schleife bis Fahrzeug gefunden wurde, oder Zeiger auf Nullpointer
        if (current->id == id) {
            break;
        } else {
            current = current->next;
        }
    }

    if(current == NULL){
            printf("\n");
            printf("Es gibt kein Fahrzeug mit der passenden ID (%d)\n", id);
        return;
    }

    else{
        printf("\n");
        printf("Welches Attribut moechten Sie bearbeiten? \n");
        printf("1. Fahrzeugmarke, 2. Fahrzeugmodell, 3. Prioritaet, 4. Ladedauer\n");
        printf("Bitte geben sie die gewuenschte Zahl ein:\n");

        do{
        scanf("%d", &input);
        if(input<1||input>4){
            printf("Falsche Eingabe, bitte waehlen Sie erneut:\n");
        }
        } while(input<1||input>4);

        printf("Eingabe der Aenderung: \n");

        switch (input){ //Anpassen des gewuenschten Attributs
            case 1:
                printf("Bitte geben Sie die neue Fahrzeugmarke ein: \n");
                scanf("%s", t_brand);
                strcpy(current->brand, t_brand);
                break;
            case 2:
                printf("Bitte geben Sie das neue Fahrzeugmodell ein: \n");
                scanf("%s", t_model);
                strcpy(current->model, t_model);
                break;
            case 3:
                printf("Bitte geben Sie die neue Prioritaet des Fahrzeugtyps ein: \n");
                scanf("%i", &t_priority);
                current->priority = t_priority;
                break;
            case 4:
                printf("Bitte geben Sie die neue Ladedauer des Fahrzeugtyps ein: \n");
                scanf("%i", &t_charge_duration);
                current->charge_duration = t_charge_duration;
                break;
        }

        printf("\n");
        printf("Die Aenderung wurde erfolgreich durchgefuehrt:\n");
        output_vehicle();
    }
}

//Funktion zur manuellen Eingabe eines Fahrzeugprototyps
void input_vehicle() {
    char t_brand[50];
    char t_model[50];
    int t_priority, t_charge_duration;

    printf("Eingabe der Fahrzeugprototypen: \n");

    printf("Bitte geben Sie die Fahrzeugmarke ein: \n");
    scanf("%s", t_brand);
    printf("Bitte geben Sie das Fahrzeugmodell ein: \n");
    scanf("%s", t_model);
    printf("Bitte geben Sie die Prioritaet des Fahrzeugtyps ein,\n");
    printf("Prioritaet 1 ermoeglicht Laden durch Reservekapaziaet:\n");
    scanf("%i", &t_priority);
    printf("Bitte geben Sie die Ladedauer des Fahrzeugtyps ein: \n");
    scanf("%i", &t_charge_duration);

    append_vehicle(t_brand, t_model, t_priority, t_charge_duration);
}

//Funktion zur Ausgabe aller Fahrzeugprototypen
void output_vehicle() {
    struct vehicle_type *current = first_vehicle_type;
    printf("||=============================================================||\n");
    printf("| ID |      Name      |     Modell     | Prioritaet | Ladedauer |\n");
    printf("||=============================================================||\n");

    if(current == NULL){
        printf("| Es sind keine Fahrzeugtypen vorhanden                         |\n");
        printf("|---------------------------------------------------------------|\n");
    }

    while(current != NULL) {
        printf("| %-3d| %-15s| %-15s| %-11d| %-10d|\n",
               current->id,current->brand, current->model, current->priority, current->charge_duration);
        printf("|---------------------------------------------------------------|\n");
        current = current->next;
    }
}

//Funktion zum Anhängen eines Fahrzeugprototyps an die bestehende Liste
void append_vehicle(char *brand, char *model, int priority, int charge_duration){
    struct vehicle_type *vehicle;
    int counter = 0; //Analog zur append_c_station-Funktion

    if(first_vehicle_type == NULL) {
        if((first_vehicle_type = malloc(sizeof(struct vehicle_type))) == NULL) {

            printf("Fehler: Es konnte kein Speicherplatz allokiert werden\n");
            return;
        }

        first_vehicle_type->id = counter;
        strcpy(first_vehicle_type->brand, brand);
        strcpy(first_vehicle_type->model, model);
        first_vehicle_type->priority = priority;
        first_vehicle_type->charge_duration = charge_duration;
        first_vehicle_type->next = NULL;

    }
    else {

        vehicle = first_vehicle_type;

        while(vehicle->next != NULL){
            vehicle = vehicle->next;
            counter++;
        }

        if((vehicle->next = malloc(sizeof(struct vehicle_type))) == NULL) {
            printf("Fehler: Es konnte kein Speicherplatz allokiert werden\n");
            return;
        }

        counter++;
        vehicle = vehicle->next;
        vehicle->id = counter;
        strcpy(vehicle->brand, brand);
        strcpy(vehicle->model, model);
        vehicle->priority = priority;
        vehicle->charge_duration = charge_duration;
        vehicle->next = NULL;
    }
}

//Funktion zum Speichern aller Fahrzeugprototypen in die zugehörige Konfigurationsdatei
void save_vehicle_config(){
    FILE *config = fopen("vehicle_config.csv", "w");
    struct vehicle_type *t_vehicle;

    if (config == NULL){
        printf("Es konnte keine Datei erstellt werden\n");
        fclose(config); //Ordnungsgemaesses schließen des Filestreams
        return;
    }

    if(first_vehicle_type == NULL){
        printf("Es sind keine Fahrzeugprototypen vorhanden\n");
        fclose(config);
        return;
    }

    t_vehicle = first_vehicle_type;

    while ((t_vehicle)  != NULL){ //Schreibe alle Fahrzeugdaten in die Konfigurationsdatei
        fprintf(config, "%d,\"%s\",\"%s\",%d,%d\n", t_vehicle->id, t_vehicle->brand, t_vehicle->model,
                t_vehicle->priority, t_vehicle->charge_duration);
        t_vehicle = t_vehicle->next;
    }

    printf("\n");
    printf("Aktuelle Fahrzeugtypenkonfiguration wurde gespeichert\n");
    printf("\n");

    fclose(config);
}

//Funktion zum Importieren aus der Konfigurationsdatei für Fahrzeugprototypen
void import_vehicle_config(){
    FILE *config = fopen("vehicle_config.csv", "r");
    char t_brand[50];
    char t_model[50];
    char stop;
    int t_id, t_priority, t_charge_duration;

    if (config == NULL){
        printf("Es konnte keine Datei geöffnet werden\n");
        fclose(config);
        return;
    }
    //Lesen aus der gespeicherten Konfigurationsdatei
    while((fscanf(config, "%d, \"%[^'\"]%c, \"%[^'\"]%c, %d, %d\n", &t_id, t_brand, &stop, t_model, &stop, &t_priority, &t_charge_duration)) != EOF ){
        append_vehicle(t_brand, t_model, t_priority,t_charge_duration);
    }

    printf("Gespeicherte Fahrzeugtypenkonfiguration wurde geladen\n");
    printf("\n");

    fclose(config);
}
