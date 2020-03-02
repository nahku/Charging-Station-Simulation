
#ifndef FINALE_PROGRAMMIERAUFGABE_CONFIG_VEHICLE_H
#define FINALE_PROGRAMMIERAUFGABE_CONFIG_VEHICLE_H

struct vehicle_type *search_vehicle_type(int id);
void delete_all_vehicle();
void delete_vehicle();
void edit_vehicle();
void output_vehicle();
void append_vehicle(char *brand, char *model, int priority, int charge_duration);
void input_vehicle();
void save_vehicle_config();
void import_vehicle_config();

#endif //FINALE_PROGRAMMIERAUFGABE_CONFIG_VEHICLE_H

