

#ifndef FINALE_PROGRAMMIERAUFGABE_SIMULATION_H
#define FINALE_PROGRAMMIERAUFGABE_SIMULATION_H


void update_c_station_capacity();
void update_c_station_aux_capacity(struct c_station *target);
void sim_vehicle_object();
void delete_specific_vehicle_object(struct c_station *target, int id);
void jump_time();
void output_sim();
void simulate_steps();
void simulate();

#endif //FINALE_PROGRAMMIERAUFGABE_SIMULATION_H
