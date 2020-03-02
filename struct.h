

#ifndef FINALE_PROGRAMMIERAUFGABE_STRUCT_H
#define FINALE_PROGRAMMIERAUFGABE_STRUCT_H

#ifndef EXTERN
#define EXTERN extern
#endif


EXTERN struct vehicle_type {
    int id;
    char brand[50];
    char model[50];
    int priority;
    int charge_duration;
    struct vehicle_type *next;
};

EXTERN struct vehicle_object{
    int id;
    char brand[50];
    char model[50];
    int priority;
    int charge_duration;
    int current_charge;
    struct vehicle_object *next;
};

EXTERN struct c_station {
    int id;
    int max_vehicles;
    int init_capacity;
    int aux_capacity;
    int current_capacity;
    int current_aux_capacity;
    int charge_duration; //Dauer bis zur vollständigen Wiederaufladung der Ladestation
    struct c_station *next;
    struct vehicle_object *first;
};

EXTERN struct vehicle_type *first_vehicle_type;
EXTERN struct c_station *first_c_station;

#endif //FINALE_PROGRAMMIERAUFGABE_HEADER_H
