#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "menu.h"
#include "config_c_station.h"
#include "config_vehicle.h"
#include "config_vehicle_object.h"
#include "simulation.h"

int time = 0;

//Management des Entladens der Ladestation
void update_c_station_capacity(){
    struct c_station *current = first_c_station;

    while(current != NULL) { //Anpassen aller Ladestationskapazitaeten pro Stunde
        int vehicle_count = count_vehicle_objects(current); //Berechnung der neuen Kapazitaet aus aktueller Kapazitaet minus Anzahl der Fahrzeuge, da Fahrzeuge eine Ladestunde pro Stunde aufladen
        int update_capacity = (current->current_capacity - vehicle_count);

        if (update_capacity < 0) {
            current->current_capacity = update_capacity;
            update_c_station_aux_capacity(current); //Falls nicht genuegend regulaere Kapazitaet vorhanden, Aktualisierung der Reservekapazitaet
        }
        else{
            current->current_capacity = update_capacity;
        }
        current = current->next;
    }
}

//Management des Entladens der Reservekapazität
void update_c_station_aux_capacity(struct c_station *target){

        int prio_vehicle_count = count_prio_vehicle_objects(target); //Falls regulaere Kapaziaet nicht ausreicht, Berechnung der neuen Reservekapazitaet
        int update_aux_capacity = (target->current_aux_capacity - prio_vehicle_count);

        target->current_aux_capacity = update_aux_capacity;
}

//Management des Wiederaufladens der Ladestationen
void recharge_c_station_capacity(){
    struct c_station *current = first_c_station;

    while(current != NULL) {
        if((time % current->charge_duration) == 0){ //Falls der aktuelle Zeitfortschritt der einzlnen Ladesaeulen zum Ladezyklus passt, wird die Haupt- und Reservekapazitaet aufgeladen
            current->current_capacity = current->init_capacity;
            current->current_aux_capacity = current->aux_capacity;
        }
        current = current->next;
    }
}

//Funktion zum Löschen der Fahrzeugobjekte, wird benötigt bei vollem Aufladen
void delete_specific_vehicle_object(struct c_station *target, int id){
    struct vehicle_object *t_vehicle_object_1, *t_vehicle_object_2;
    //Bei voller Kapazitaet der Fahrzeuge sollen diese von der Ladesaeule entfernt werden
    if(target->first != NULL){ //Das richtige Element zum Loeschen wird ueber die ID ausewaehlt
        if(target->first->id == id){
            t_vehicle_object_1 = target->first->next;
            free(target->first);
            target->first = t_vehicle_object_1;
        }
        else{
            t_vehicle_object_1 = target->first;
            while(t_vehicle_object_1->next != NULL){
                t_vehicle_object_2 = t_vehicle_object_1->next;
                if(t_vehicle_object_2->id == id){
                    t_vehicle_object_1->next = t_vehicle_object_2->next;
                    free(t_vehicle_object_2);
                    break;
                }
                t_vehicle_object_1 = t_vehicle_object_2;
            }
        }
    }
}

//Management des Aufladens der Fahrzeugobjekte und deren Entfernung
void sim_vehicle_object(){
    struct c_station *current = first_c_station;

    while(current != NULL) {

        struct vehicle_object *obj = current->first;
        if(current->current_capacity >= 0) { //Falls genug Kapazitaet vorhanden ist (diese wurde zuvor upgedatet), laden die Fahrzeuge
            while(obj != NULL) {             //Genug Kapazitaet fuer diesen Zeitschritt kennzeichnet sich dadurch, dass current_capacity der Ladestation >= 0 ist
                obj->current_charge = obj->current_charge + 1;
                if (obj->current_charge == obj->charge_duration) {
                    //printf("Ladestation %d: Fahrzeug %d voll aufgeladen und faehrt weg\n", current->id, obj->id);
                    delete_specific_vehicle_object(current, obj->id); //Falls das Fahrzeug voll ist, wird es entfernt
                }
                obj = obj->next;
            }
        }
        else{
            //Falls nicht genug Kapaziaet vorhanden ist, werden, falls genug Reservekapaziaet vorhanden ist, nur die Fahrzeuge mit der Prioritaet 1 geladen
            if(current->current_aux_capacity >= 0){
                while(obj != NULL){

                    if(obj->priority == 1){ //Pruefung ob das Fahrzeug Anspruch auf die Reservekapazitaet hat
                        obj->current_charge = obj->current_charge + 1;
                        if(obj->current_charge == obj->charge_duration){
                            //printf("Ladestation %d: Fahrzeug %d voll aufgeladen durch Resevekapazitaet und faehrt weg\n", current->id, obj->id);
                            delete_specific_vehicle_object(current, obj->id); //Falls das Fahrzeug voll ist, wird es entfernt
                        }
                    }
                    obj = obj->next;
                }
            }
        }
    current = current->next;
    }
}

//Funktion zum Erhöhen der Zeit, ohne ins Geschehen einzugreifen
void jump_time(){
    int t;
    printf("Um wie viele Stunden wollen Sie die Zeit erhoehen, ohne dass in das Ladegeschehen eingewirkt wird?\n");
    scanf("%d", &t);
    time = time + t;
    printf("\n");
    printf("Es sind %d Stunden vergangen, ohne dass etwas veraendert wurde\n",time);
}

//Ausgabe der Veränderung beim Simulationsschritt
void output_sim(){
    int temp1, temp2;
    printf("\n");
    printf("Es sind %d Stunden vergangen\n", time);
    printf("\n");

    //Ausgabe des Zustands der Ladestationen
    struct c_station *current = first_c_station;
    printf("Zustand der Ladestationen:\n");
    printf("\n");
    printf("||==================================================================================================||\n");
    printf("| ID |Max.Anz.Fahrzeuge|Init.Kap.|Res.Kap.|Wiederaufladedauer|Akt.Kap.|Akt.Res.Kap.|Akt.Anzahl.Fahrz.|\n");
    printf("||==================================================================================================||\n");
    if(current == NULL){
        printf("| Keine Ladestationen vorhanden                                                                      |\n");
        printf("|----------------------------------------------------------------------------------------------------|\n");
    }
    while(current != NULL) {
        temp1 = current->current_capacity;
        temp2 = current->current_aux_capacity;

        //Es ist moeglich, dass Kapazitaet negativ wird, aufgrund des Berechnungsalgorithmus, da jedoch die Fahrzeuge auch dann nicht Laden ist dies für die Funktion nicht relevant
        //Um dem Nutzer ein besseres Erlebnis zu gewaehrleisten wird daher die Kapaziatet, falls sie negativ ist, als 0 angezeigt (entladen)

        if(temp1<0){
            temp1 = 0;
        }

        if(temp2<0){
            temp2 = 0;
        }

        printf("| Ladestation %d:                                                                                     |\n", current->id);
        printf("| %-3d|%-17d| %-9d|%-8d|%-18d|%-8d|%-12d|%-16d|\n",
               current->id,current->max_vehicles, current->init_capacity, current->aux_capacity, current->charge_duration, temp1, temp2, count_vehicle_objects(current));
        printf("|----------------------------------------------------------------------------------------------------|\n");
        current = current->next;
    }
    printf("Zustand der Fahrzeuge:\n");
    output_all_vehicle_object(); //Ausgabe des Zustands der Fahrzeuge
}

//Starte Simulation mit variablen Zeitschritten
void simulate_steps(){
    int i = 0, z, y;
    printf("Bitte geben Sie ein, wie viele Stunden Sie auf einmal ablaufen lassen wollen\n");
    printf("Zum Beenden geben Sie 0 ein\n");
    scanf("%d", &z);
    do{
        for(i = 0; i < z; i++){ //For-Schleife fuehrt die Simulationsschritte in der vom Nutzer gewuenschten Haeufigkeit aus
            time++;

            update_c_station_capacity();
            sim_vehicle_object();
            recharge_c_station_capacity();
        }
        output_sim(); //Nach den multiplen Schritten wird der Zustand der Fahrzeuge und Ladestationen ausgegeben
        scanf("%d",&y);
    }while(y != 0);
}

//Starte Simulation mit Zeitschritten von einer Stunde
void simulate(){
    int i = 1;
    printf("Geben Sie eine Zahl zwischen 1 und 100 ein, um einen Zeitschritt ablaufen zu lassen\n");
    printf("Zum Beenden geben Sie 0 ein\n");

    output_sim();

    while(i != 0){
        do{
        scanf("%d", &i);
        }while(i < 0 || i>100);

        time++;
        update_c_station_capacity();
        sim_vehicle_object(); //Fahrzeuge werden aktualisiert, die nachdem Ladestationskapazitaet aktualisiert wurde, damit die Pruefung funktioniert, ob genuegend Kapazitaet fuer diesen Zeitschritt vorhanden ist
        output_sim(); //Nachdem die Simulation der Fahrzeuge und Ladestationen stattgefunden hat, wird der aktuelle Zustand ausgegeben
        recharge_c_station_capacity(); //Ggf. wird die Ladestation nach dem definierten Zeitschritt wieder aufgeladen, d.h. die neue Kapazitaet steht erst fuer den naechsten Zeitschritt zur Verfuegung

    }
}
