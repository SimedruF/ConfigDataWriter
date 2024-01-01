#include "ConfigDataWriter.h"
#include <stdlib.h>
#include <stdio.h>

ConfigDataWriter::ConfigDataWriter(const char *fileName)
{
    snprintf(this->fileName, sizeof(this->fileName), "%s", fileName);
}

int ConfigDataWriter::SaveCfgDataBinary(const ConfigData &configItem)
{
    // Add .ini handle for UserData type
    FILE *open_file;
    int ret_value = -1;
    size_t fwrite_ret = 0;
    open_file = fopen(this->fileName, "w");
    if (open_file == NULL)
    {
        fprintf(stderr, " Error to open the file \n");
        printf("FileName :%s\n",this->fileName);
        ret_value = -1;
    }
    fwrite_ret = fwrite(&configItem, sizeof(configItem)+1, 1, open_file);
    if (fwrite_ret != 0)
    {
        printf("Content written successfully !\n");
        ret_value = 1;
    }
    else
    {
        printf("Error writing file !\n");
        ret_value = -2;
    }

    fclose(open_file);
    return ret_value;
}
int ConfigDataWriter::LoadCfgDataBinary(ConfigData &configItem)
{
    // Add handle for ConfigData type
    FILE *open_file;
    int ret_value = -1;
    size_t fread_ret = 0;
    open_file = fopen(this->fileName, "r");
    if (open_file == NULL)
    {
        fprintf(stderr, " Error to open the file !\n");
        ret_value = -1;
    }
    /* Seek to the beginning of the file */
    fseek(open_file, 0, SEEK_SET);

    // reading to read_struct
    fread_ret = fread(&configItem, sizeof(configItem), 1, open_file);

    if (fread_ret != 0)
    {
        printf("Content read successfully !\n");
        ret_value = 1;
    }
    else
    {
        printf("Error reading file %s!\n",this->fileName);
        ret_value = -2;
    }

    fclose(open_file);
    return ret_value;
}

int ConfigDataWriter::SaveConfigIni(int *configItems, int size)
{
    FILE *configFile = fopen(this->fileName, "w");
    if (configFile != NULL)
    {
        for (int i = 0;i<size;i++)
        {
            // write the config items in file
            fprintf(configFile, "%d\n", configItems[i]);
        }
        // close the file
        fclose(configFile);
    }
    else
    {
        fprintf(stderr, "Nu am putut deschide fișierul de configurare.\n");
    }

    return 0;
}

int ConfigDataWriter::ReadConfigIni(int *configItems)
{
    int i=0;
    FILE *configFile = fopen(this->fileName, "r");
    if (configFile != NULL)
    {
        int num_of_flights;
        char buffer[255];
        /* Seek to the beginning of the file */
        fseek(configFile, 0, SEEK_SET);
        while (fgets(buffer, sizeof(buffer), configFile) != NULL)
        {
            /* Read the cfg value */
            int testvalue = atoi(buffer);
            /* Process line here. Note that fgets stores also the line terminator (CR-LF or LF). */
            configItems[i] = testvalue;
            i = i + 1;
        }
        // Alte structuri pot fi adăugate la nevoie
        fclose(configFile);
    }
    else
    {
        fprintf(stderr, " Error to open the file \n");
        printf("FileName :%s\n", this->fileName);
    }
    return i;
}