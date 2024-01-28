#include "ConfigDataWriter.h"
#include <stdlib.h>
#include <stdio.h>
/// @brief ConfigDataWriter constructor
/// @param fileName Filename
ConfigDataWriter::ConfigDataWriter(const char *fileName)
{
    snprintf(this->fileName, sizeof(this->fileName), "%s", fileName);
}
/// @brief Saving config data to a file in binary format
/// @param configItem Contain the values to be saved in the file
/// @return Error to open the file=-1, Error to write the file=-2 , OK = 0
int ConfigDataWriter::SaveCfgDataBinary(const ConfigData &configItem)
{
    // FILE handle
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
        ret_value = 0;
    }
    else
    {
        printf("Error writing file !\n");
        ret_value = -2;
    }

    fclose(open_file);
    return ret_value;
}
/// @brief Loading config data from file, in binary format
/// @param configItem Contain the values saved in the file
/// @return Error to open the file =-1, Error to read the file , OK = 0
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
        ret_value = 0;
    }
    else
    {
        printf("Error reading file %s!\n",this->fileName);
        ret_value = -2;
    }

    fclose(open_file);
    return ret_value;
}
/// @brief Saving integer data to a file
/// @param configItems The values to be saved in the file
/// @return NOK =-1 , OK = 0
int ConfigDataWriter::SaveSimpleConfig(int *configItems, int size)
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
        fprintf(stderr, "Error to open the file !\n");
        return -1;
    }

    return 0;
}
/// @brief Reading integer data from a file
/// @param configItems Contain the values found in the file
/// @return NOK =-1 , OK= Number of values found in the file
int ConfigDataWriter::ReadSimpleConfig(int *configItems)
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
        return -1;
    }
    return i;
}
/// @brief Save integer data to a csv file
/// @param TableHead Head of the table
/// @param size The size of the TableHead
/// @param configItems Saved data - integer
/// @param column The number of columns
/// @param row The number of rows
/// @return OK=0 NOK =-1
int ConfigDataWriter::SaveIntDataCSV(const char *TableHead, int size, int *configItems, int column, int row)
{
    FILE *configFile = fopen(this->fileName, "w");
    char TableHeadArr[255];
    snprintf(TableHeadArr, size, "%s", TableHead);

    if (configFile != NULL)
    {
        for (int ix = 0; ix < size; ix++)
        {
            // write the config items in file
            fprintf(configFile, "%c", TableHeadArr[ix]);
        }
        fprintf(configFile, "\n"); // go to the next row
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                fprintf(configFile, "%d", *((configItems + i * column) + j));

                // Add comma between elements, except the last element 
                if (j < column - 1)
                {
                    fprintf(configFile, ",");
                }
            }
            fprintf(configFile, "\n"); // go to the next row
        }
        // close the file
        fclose(configFile);
    }
    else
    {
        fprintf(stderr, "Error to open the file!\n");
        return -1;
    }

    return 0;
}
/// @brief Save float data to a csv file
/// @param TableHead Head of the table
/// @param size The size of the TableHead
/// @param configItems Saved data - float
/// @param column The number of columns
/// @param row The number of rows
/// @return OK=0 NOK =-1
int ConfigDataWriter::SaveFloatDataCSV(const char *TableHead, int size, float *configItems, int column, int row)
{
    FILE *configFile = fopen(this->fileName, "w");
    char TableHeadArr[255];
    snprintf(TableHeadArr, size, "%s", TableHead);

    if (configFile != NULL)
    {
        for (int ix = 0; ix < size; ix++)
        {
            // write the config items in file
            fprintf(configFile, "%c", TableHeadArr[ix]);
        }
        fprintf(configFile, "\n"); // go to the next row
        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                fprintf(configFile, "%f", *((configItems + i * column) + j));

                // Add comma between elements, except the last element
                if (j < column - 1)
                {
                    fprintf(configFile, ",");
                }
            }
            fprintf(configFile, "\n"); // go to the next row
        }
        // close the file
        fclose(configFile);
    }
    else
    {
        fprintf(stderr, "Error to open the file!\n");
        return -1;
    }

    return 0;
}

/// @brief Save ini file 
/// @param Comment The comment befor each section
/// @param Section The section name
/// @param ConfigItemName Config item name
/// @param configItems Config item value
/// @param size The number of items 
/// @return OK=0 NOK =-1
int ConfigDataWriter::SaveIniConfig(char*Comment, char *Section, char ConfigItemName[][20], int *configItems, int size)
{
    FILE *configFile = fopen(this->fileName, "w");
    if (configFile != NULL)
    {
        fprintf(configFile, ";%s\n", Comment);
        fprintf(configFile, "[%s]\n", Section);

        for (int i = 0; i < size; i++)
        {
            // Write the config items in file
            fprintf(configFile, "%s = %d\n", ConfigItemName[i], configItems[i]);
        }
        // close the file
        fclose(configFile);
    }
    else
    {
        fprintf(stderr, "Error to open the file!\n");
        return -1;
    }

    return 0;
}
/// @brief Read ini file -> parsing the ini file to identify the sections
/// and for each section the list of config variables -> work in progress
/// @param configItems Config item value
/// @return OK=0 NOK =-1
int ConfigDataWriter::ReadIniConfig(int *configItems)
{
    int i = 0;
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
        return -1;
    }
    return i;
}
/// @brief Set cfg buffer
/// @param cfg_buffer
/// @param size
void ConfigDataWriter::SetCfgBuffer(char *cfg_buffer, int size)
{
    snprintf(this->cfgBuffer, size, "%s", cfg_buffer);
}

/// @brief Get cfg buffer
/// @return cfgBuffer
char* ConfigDataWriter::GetCfgBuffer()
{
    return this->cfgBuffer;
}