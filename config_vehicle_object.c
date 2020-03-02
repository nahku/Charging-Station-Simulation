#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "menu.h"
#include "config_c_station.h"
#include "config_vehicle_object.h"


//Funktion, die die ID des Fahrzeugtyps mit bestimmter Marke und Modell zurückgibt
int search_vehicle_id(char brand[50], char model[50]){
    struct vehicle_type *current = first_vehicle_type;

    while(current != NULL){
        if(strcmp(current->brand, brand) == 0 && strcmp(current->model, model) == 0){
            return current->id; //Zurueckgeben der ID, bei der Marke und Modell uebereinstimmen
        }
        current = current->next;
    }
    return NULL; //NULL, falls kein passender Fahrzeugtyp gefunden wird
}

//Funktion zum Speichern der Zuordnung von Fahrzeugen
void save_association(){
    struct c_station *t_c_station;
    struct vehicle_type *t_vehicle_type;
    struct vehicle_object *current;

    FILE *config = fopen("a_config.csv", "w");

    if (config == NULL){
        printf("Es konnte keine Datei erstellt werden\n");
        fclose(config);
        return;
    }



    t_c_station = first_c_station;
    t_vehicle_type = first_vehicle_type;

    while ((t_c_station)  != NULL){
        current = t_c_station->first;

        while(current != NULL){ //Speichern der Ladestations-ID und der Fahzeugtyps-ID in die Konfigurationsdatei
            fprintf(config, "%d,%d\n",t_c_station->id, search_vehicle_id(current->brand, current->model)); //Suche der Fahrzeugtyps-ID durch vergleichen der Marke und des Modells des Fahrzeugsobjekts
            current = current->next;
        }

        t_c_station = t_c_station->next;
    }

    printf("\n");
    printf("Aktuelle Konfiguration wurde gespeichert\n");
    printf("\n");

    fclose(config);
}

//Funktion zum Importieren der Zuordnung von Fahrzeugen
void import_association(){
    int c_station_id, vehicle_id, counter;
    FILE *config = fopen("a_config.csv", "r");

    while((fscanf(config, "%d,%d\n", &c_station_id, &vehicle_id)) != EOF ){
        append_vehicle_object(search_c_station(c_station_id),search_vehicle_type(vehicle_id)); //Anhaengen eines Fahrzeuges an die passende Ladestation durch vergleichen der IDs
    }

    printf("Fahrzeugzuordnung wurde importiert\n");

    fclose(config);
}

//Funktion zum Speichern der Zuordnung von Fahrzeugen und der Fahrzeugtypen und Ladesaeulen
void save_config(){
    save_c_config();
    save_vehicle_config();
    save_association();
}

//Funktion zum Importieren der Zuordnung von Fahrzeugen und der Fahrzeugtypen und Ladesaeulen
void import_config(){
    import_c_config();
    import_vehicle_config();
    import_association();
}

//Funktion zum Löschen aller Fahrzeugobjekte
void delete_all_vehicle_object(){
    struct c_station *target = first_c_station;

    while(target != NULL){ //Wird zum ordnungsmaessigen beenden des Programms benoetigt
        delete_vehicle_object(target);
        target = target->next;
    }
}

//Funktion zum Löschen aller Fahrzeugobjekte einer Ladestation
void delete_vehicle_object(struct c_station *target){
    struct vehicle_object *t_vehicle_object_1, *t_vehicle_object_2;

    if(target->first != NULL) { //Wird benoetigt zur Speicherfreigabe bei Loeschen einer Ladestation
        t_vehicle_object_1 = target->first->next;
        while(t_vehicle_object_1 != NULL) {
            t_vehicle_object_2 = t_vehicle_object_1->next;
            target->first->next = t_vehicle_object_1;
            free(t_vehicle_object_1);
            t_vehicle_object_1 = t_vehicle_object_2;
        }
        free(target->first->next);
        free(target->first);
        target->first = NULL;
    }
}

//Funktion zur Prüfung, ob noch Platz für ein neues Fahrzeugobjekt in der Ladesäule ist
int check_vehicle_limit(struct c_station *target){

    int max, counter = 0;
    if(target == NULL){
        printf("Fehler: keine Ladestation zur Prüfung vorhanden\n");
        return 0;
    }

    max = target->max_vehicles;

    struct vehicle_object *current = target->first;

    while(current != NULL){ //Zaehlen der Fahrzeugobjekte
        counter++;
        current = current->next;
    }

    if(counter < max){ //1 falls genug Platz ist, sonst 0
        return 1;
    } else{
        return 0;
    }
}

//Funktion zur Ausgabe aller Fahrzeugobjekte einer Ladestation
void output_vehicle_object(struct c_station *target) {

    struct vehicle_object *current;
    current = target->first;

    printf("\n");
    printf("Ladestation %d\n", target->id);

    if(current == NULL){
        printf("Keine Autos an dieser Ladestation!\n");
    }

    while(current != NULL){ //Tabellenausgabe
        printf("||==========================================================================||\n");
        printf("|ID|          Marke          |       Modell       |Prio.|Ladedauer|Akt.Ladung|\n");
        printf("||==========================================================================||\n");
        while(current != NULL) {
            printf("|%-2d|%-25s|%-20s|%-5d|%-9d|%-10d|\n",
                   current->id,current->brand, current->model, current->priority, current->charge_duration, current->current_charge);
            printf("|----------------------------------------------------------------------------|\n");
            current = current->next;
        }
    }
}

//Funktion zur Ausgabe aller Fahrzeugobjekte zugehörig zu den Ladestationen
void output_all_vehicle_object() {

    struct c_station *current = first_c_station;

    if(current == NULL){
        printf("\n");
        printf("Es sind noch keine Ladestationen vorhanden\n");
        printf("\n");
    }

    while(current != NULL) { //Aufeinanderfolgende Ausgabe der Fahrzeuge der jeweiligen Ladestation
        output_vehicle_object(current);
        current = current->next;
    }
}

//Funktion zur Auswahl der Ladestation zum Hinzufügen eines Fahrzeugs
struct c_station *choose_c_station(){

    int id;
    struct c_station *current = first_c_station;

    if(current == NULL){
        printf("Es gibt noch keine Ladestationen.\n");
        return NULL;
    }

    printf("Alle Ladestationen:\n");    //Anzeigen aller Ladestationen zur Auswahl
    output_c_station(first_c_station,first_vehicle_type);
    printf("\n");

    printf("Zu welcher Station moechten Sie ein Fahrzeug hinzufuegen (bitte geben Sie die passende ID ein)?\n");
    scanf("%d", &id);

    while(current != NULL) {
        if (current->id != id) {
            current = current->next;
        } else {
            break; //Abbruch, falls passende Ladestation gefunden wurde
        }
    }

    if(current == NULL){
        printf("Es konnte keine passende Ladestation gefunden werden.\n");
        return NULL;
    }
    else{
        return current;
    }
}

//Funktion zur Auswahl der Ladestation zum Hinzufügen eines Fahrzeugs
struct vehicle_type *choose_vehicle_type(){

    int id = 0;

    struct vehicle_type *current = first_vehicle_type;

    if(current == NULL){
        printf("Es gibt noch keine Fahrzeugtypen.\n");
        return NULL;
    }

    printf("Alle Fahrzeugtypen:\n"); //Ausgabe aller Fahrzeugtypen zur Auswahl
    output_vehicle();
    printf("\n");

    printf("Von welchem Fahrzeugtyp wollen Sie ein Objekt erstellen (bitte geben Sie die passende ID ein)?\n");
    scanf("%d",&id);

    while(current != NULL) {
        if (current->id == id) {
            break;
        } else {
            current = current->next;
        }
    }

    if(current == NULL){
        printf("Es konnte kein passender Fahrzeugtyp gefunden werden.\n");
        return NULL;
    }
    else{
        return current;
    }

}

//Hänge neues ausgewähltes Fahrzeug an ausgewählte Ladestation
void append_vehicle_object(struct c_station *target, struct vehicle_type *temp){

    int counter = 0;

    if((target != NULL) && (temp != NULL)){
    if(!check_vehicle_limit(target)){ //Pruefen, ob noch Platz für das Fahrzeug an der Ladestation ist
        printf("Es gibt keinen freien Platz fuer dieses Fahrzeug\n");
        return;
    }

    struct vehicle_object *current = target->first;

    if(current == NULL){ //Falls noch keine Fahrzeuge an der Ladesauele sind

        if((current = malloc(sizeof(struct vehicle_object))) == NULL) {
            printf("Fehler: Es konnte kein Speicherplatz allokiert werden\n");
            return;
        }

        current->id = counter;
        strcpy(current->brand, temp->brand);
        strcpy(current->model, temp->model);
        current->priority = temp->priority;
        current->charge_duration = temp->charge_duration;
        current->current_charge = 0;
        current->next = NULL;
        target->first = current;
    }
    else{ //Falls schon ein Fahrzeug vorhanden ist
        while(current->next != NULL){
            current = current->next;
            counter++;
        }

        if((current->next = malloc(sizeof(struct vehicle_type))) == NULL) {
            printf("Fehler: Es konnte kein Speicherplatz allokiert werden\n");
            return;
        }
        counter++;
        current = current->next;
        current->id = counter;
        strcpy(current->brand, temp->brand);
        strcpy(current->model, temp->model);
        current->priority = temp->priority;
        current->charge_duration = temp->charge_duration;
        current->current_charge = 0;
        current->next = NULL;
    }
        output_vehicle_object(target); //Ausgabe, wenn das Hinzufügen erfolgreich war
    }
    else{
        printf("Es konnte kein Fahrzeug angehaengt werden.\n");
    }
}

//Funktion gibt Anzahl an Fahrzeugen an einer Ladestation zurück
int count_vehicle_objects(struct c_station *target){

    int counter = 0;

    if(target == NULL){
        printf("Fehler: keine Ladestation zur Pruefung vorhanden\n");
        return NULL;
    }

    struct vehicle_object *current = target->first;

    while(current != NULL){ //Zaehlen der Fahrzeuge an einer Ladestation
        counter++;
        current = current->next;
    }
    return counter;
}

//Funktion gibt Anzahl an Fahrzeugen hoher Priorität (1) an einer Ladestation zurück
int count_prio_vehicle_objects(struct c_station *target){
    int counter = 0;

    if(target == NULL){
        printf("Fehler: keine Ladestation zur Pruefung vorhanden\n");
        return 0;
    }

    struct vehicle_object *current = target->first;

    while(current != NULL){
        if(current->priority == 1){ //Zaehlen nur der Fahrzeuge, die eine hohe Prioritaet haben
            counter++;
        }
        current = current->next;
    }
    return counter;
}
