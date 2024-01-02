#include "test.h"
#include "ConfigDataWriter.h"
#include <stdio.h>

int main()
{
    // Cfg data definition for testing
    ConfigData cfg_data1 = {10,100,1000};
    ConfigData cfg_data2 = {0, 0, 0};
    int cfg_data1_array[] = {1, 2, 3};
    int cfg_data2_array[100];
    char TableHead[] = "Time,Value";
    int csv_int_array[3][2] = { {1,2},{3,4},{5,6}};
    float csv_float_array[3][2] = {{1.1, 2.5}, {3.4, 4.5}, {5.6, 6.7}};
    char ConfigName[3][20] = {
        "First cfg param",
        "Second",
        "Third"};
    char Section[] = "Section1";
    char Comment[] = " Comment for Section1";
    int nb_lines=0;
    // Config Data writer binary saving test
    ConfigDataWriter config("ea_test1.cfg");

    config.SaveCfgDataBinary(cfg_data1);
    config.LoadCfgDataBinary(cfg_data2);

    // Simple config file test
    ConfigDataWriter config_simple("ea_test1.txt");
    config_simple.SaveSimpleConfig(cfg_data1_array, 3);
    nb_lines = config_simple.ReadSimpleConfig(cfg_data2_array);
    for (int i = 0; i < nb_lines; ++i)
    {
        printf("%d\n ", cfg_data2_array[i]);
    }

    // CSV data saving test
    ConfigDataWriter config_integer_csv("integer_data.csv");
    config_integer_csv.SaveIntDataCSV(TableHead, sizeof(TableHead), &csv_int_array[0][0], 2, 3);
    ConfigDataWriter config_float_csv("float_data.csv");
    config_float_csv.SaveFloatDataCSV(TableHead, sizeof(TableHead), &csv_float_array[0][0], 2, 3);

    // Ini data saving test
    ConfigDataWriter config_ini("program.ini");
    config_ini.SaveIniConfig(Comment,Section, ConfigName, cfg_data1_array, 3);

    return 0;
}