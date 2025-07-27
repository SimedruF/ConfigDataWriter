#ifndef ConfigData
/* Cfg structure*/
struct ConfigData
{
    int blades_nb;
    int max_rot_speed;
    int airflow_pressure;
    float diameter;
    char cfgData[200];
};
#endif