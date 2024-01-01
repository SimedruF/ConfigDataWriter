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
    int nb_lines=0;
    // Config Data writer  
    ConfigDataWriter config("ea_test1.cfg");

    config.SaveCfgDataBinary(cfg_data1);
    config.LoadCfgDataBinary(cfg_data2);

    ConfigDataWriter config_ini("ea_test1.ini");
    config_ini.SaveConfigIni(cfg_data1_array,3);
    nb_lines = config_ini.ReadConfigIni(cfg_data2_array);
    for (int i = 0; i < nb_lines; ++i)
    {
        printf("%d\n ", cfg_data2_array[i]);
    }
    return 0;
}