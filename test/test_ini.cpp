#include "test.h"
#include "../source/ConfigDataWriter.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    int cfg_data_array[3] = {1, 2, 3};
    char ConfigName[3][20] = {
        "First cfg param",
        "Second",
        "Third"};
    char Section[] = "Section1";
    char Comment[] = " Comment for Section1";

    printf("\nTesting INI config file creation:\n");
    ConfigDataWriter config_ini("../test/data/program.ini");
    config_ini.SaveIniConfig(Comment, Section, ConfigName, cfg_data_array, 3);

    printf("INI file '../test/data/program.ini' created and saved.\n");

    int read_array[3] = {0};
    int num_read = config_ini.ReadIniConfig(read_array);
    printf("Read %d values from INI file:\n", num_read);
    for (int i = 0; i < num_read; ++i)
    {
        printf("Value[%d] = %d\n", i, read_array[i]);
    }

    return 0;
}
