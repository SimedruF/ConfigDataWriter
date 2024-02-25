#include "test.h"
#include "ConfigDataWriter.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    // Cfg data definition for testing
    ConfigData cfg_data1 = { 10, 100, 1000, 30.5, "11;2000;30000;0"};
    ConfigData cfg_data2 = { 0, 0, 0, 0.0, "1"};
    int cfg_data1_array[] = {1, 2, 3};
    int cfg_data2_array[100];
    char TableHead[] = "Time,Value";
    char TestCfgBuffer[] = "11;2000;30000;0";
    int csv_int_array[3][2] = { {1,2},{3,4},{5,6}};
    float csv_float_array[3][2] = {{1.1, 2.5}, {3.4, 4.5}, {5.6, 6.7}};
    char ConfigName[3][20] = {
        "First cfg param",
        "Second",
        "Third"};
    char Section[] = "Section1";
    char Comment[] = " Comment for Section1";
    int nb_lines=0;

    printf("\nTesting binary cfg:\n ");
    // Config Data writer binary saving test
    ConfigDataWriter config_binary("ea_test1.cfg");
    // Set cfg buffer
    config_binary.SetCfgBuffer(cfg_data1.cfgData, sizeof(cfg_data1.cfgData));
    printf("Config buffer: %s\n ", config_binary.GetCfgBuffer());
    config_binary.SaveCfgDataBinary(cfg_data1);
    config_binary.LoadCfgDataBinary(cfg_data2);
    printf("Config value1 : %d\n ", cfg_data2.blades_nb);
    printf("Config value2 : %d\n ", cfg_data2.max_rot_speed);
    printf("Config value3 : %d\n ", cfg_data2.airflow_pressure);
    printf("Config value3 : %d\n ", cfg_data2.diameter);
    printf("Config value4 : %s\n ", cfg_data2.cfgData);


    printf("\nTesting simple txt cfg:\n ");
    // Simple config file test
    ConfigDataWriter config_simple("ea_test1.txt");
    config_simple.SaveSimpleConfig(cfg_data1_array, 3);
    nb_lines = config_simple.ReadSimpleConfig(cfg_data2_array);
    for (int i = 0; i < nb_lines; ++i)
    {
        printf("%d\n ", cfg_data2_array[i]);
    }

    printf("\nTesting csv data:\n ");
    // CSV data saving test
    ConfigDataWriter config_integer_csv("integer_data.csv");
    config_integer_csv.SaveIntDataCSV(TableHead, sizeof(TableHead), &csv_int_array[0][0], 2, 3);
    ConfigDataWriter config_float_csv("float_data.csv");
    config_float_csv.SaveFloatDataCSV(TableHead, sizeof(TableHead), &csv_float_array[0][0], 2, 3);

    char TableHeadCfg[] = "blades_nb,max_rot_speed,airflow_pressure,diameter";
    char csv_array_cfg[100] = "11,1000,24,36.5";
    snprintf(csv_array_cfg, sizeof(csv_array_cfg), "%d,%d,%d,%f", cfg_data1.blades_nb, cfg_data1.max_rot_speed, cfg_data1.airflow_pressure, cfg_data1.diameter);
    ConfigDataWriter app_config_csv("app_cfg.csv");
    app_config_csv.SaveCfgDataCSV(TableHeadCfg, sizeof(TableHeadCfg), &csv_array_cfg[0], 1);
    app_config_csv.ReadCSV_File("app_cfg.csv");
    printf("Num tokens =  %d\n ", app_config_csv.GetCsvNumTokens());
    for (int i = 0; i < app_config_csv.GetCsvNumTokens();i++)
        printf(" Tokens[%d]  =  %s\n ",i, app_config_csv.GetCsvToken(i));
    cfg_data2.blades_nb = atoi(app_config_csv.GetCsvToken(0));
    cfg_data2.max_rot_speed = atoi(app_config_csv.GetCsvToken(1));
    cfg_data2.airflow_pressure = atoi(app_config_csv.GetCsvToken(2));
    cfg_data2.diameter = atof(app_config_csv.GetCsvToken(3));
    printf("Config blades_nb : %d\n ", cfg_data2.blades_nb);
    printf("Config max_rot_speed : %d\n ", cfg_data2.max_rot_speed);
    printf("Config airflow_pressure : %d\n ", cfg_data2.airflow_pressure);
    printf("Config diameter : %f\n ", cfg_data2.diameter);

    printf("\nTesting ini cfg:\n ");
    // Ini data saving test
    ConfigDataWriter config_ini("program.ini");
    config_ini.SaveIniConfig(Comment,Section, ConfigName, cfg_data1_array, 3);

    return 0;
}