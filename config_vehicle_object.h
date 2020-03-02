
#ifndef FINALE_PROGRAMMIERAUFGABE_CONFIG_VEHICLE_OBJECT_H
#define FINALE_PROGRAMMIERAUFGABE_CONFIG_VEHICLE_OBJECT_H
int search_vehicle_id(char brand[50], char model[50]);
void save_association();
void import_association();
void save_config();
void import_config();
void delete_all_vehicle_object();
void delete_vehicle_object(struct c_station *target);
int check_vehicle_limit(struct c_station *target);
void output_vehicle_object(struct c_station *target);
void output_all_vehicle_object();
struct c_station *choose_c_station();
struct vehicle_type *choose_vehicle_type();
void append_vehicle_object(struct c_station *target, struct vehicle_type *temp);
int count_vehicle_objects(struct c_station *target);
int count_prio_vehicle_objects(struct c_station *target);
#endif //FINALE_PROGRAMMIERAUFGABE_CONFIG_VEHICLE_OBJECT_H
