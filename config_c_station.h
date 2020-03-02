

#ifndef FINALE_PROGRAMMIERAUFGABE_CONFIG_C_STATION_H
#define FINALE_PROGRAMMIERAUFGABE_CONFIG_C_STATION_H

struct c_station *search_c_station(int id);
void delete_all_c_station();
void delete_c_station();
void edit_c_station();
void save_c_config();
void import_c_config();
void output_c_station();
void append_c_station(int max_vehicles, int init_capacity, int aux_capacity, int charge_duration);
void input_c_station();

#endif //FINALE_PROGRAMMIERAUFGABE_CONFIG_C_STATION_H
