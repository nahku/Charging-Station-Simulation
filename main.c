#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"
#include "menu.h"
#include "config_vehicle_object.h"
#include "config_c_station.h"

//Globale Variablen zur Listenverwaltung der Ladestationen und Fahrzeugtypen
struct vehicle_type *first_vehicle_type = NULL;
struct c_station *first_c_station = NULL;

int main() {
    menu(); //Aufrufen des Hauptmenues
    return 0;
}
