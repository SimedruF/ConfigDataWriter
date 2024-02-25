#include "ConfigDataWriter.h"
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



/// @brief ConfigDataWriter constructor
/// @param fileName Filename
ConfigDataWriter::ConfigDataWriter(const char *fileName)
{
    snprintf(this->fileName, 30, "%s", fileName);
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
    if(  strcmp(this->fileName,CFG_FILE) != 0)
    {
        snprintf(this->fileName, sizeof(this->fileName), "%s", CFG_FILE);
        printf("FileName :%s\n",this->fileName);
    }
    if (open_file == NULL)
    {
         printf(" SaveCfgDataBinary: Error to open the file \n");
        printf("FileName :%s\n",this->fileName);
        ret_value = -1;
    }
    fwrite_ret = fwrite(&configItem, sizeof(configItem)+1, 1, open_file);
    if (fwrite_ret != 0)
    {
        printf("SaveCfgDataBinary: Content written successfully !\n");
        ret_value = 0;
    }
    else
    {
        printf("SaveCfgDataBinary: Error writing file !\n");
        ret_value = -2;
    }

    fclose(open_file);
    return ret_value;
}
/// @brief Saving config data to a file in binary format
/// @param configItem Contain the values to be saved in the file
/// @return Error to open the file=-1, Error to write the file=-2 , OK = 0
int ConfigDataWriter::SaveCfgDataBinary(const char *fileName, const ConfigData &configItem)
{
    // FILE handle
    FILE *open_file;
    int ret_value = -1;
    size_t fwrite_ret = 0;
    snprintf(this->fileName, 30, "%s", fileName);
    open_file = fopen(this->fileName, "w");
    if(  strcmp(this->fileName,CFG_FILE) != 0)
    {
        snprintf(this->fileName, sizeof(this->fileName), "%s", CFG_FILE);
        printf("FileName :%s\n",this->fileName);
    }
    if (open_file == NULL)
    {
        fprintf(stderr, " SaveCfgDataBinary: Error to open the file \n");
        printf("FileName :%s\n",this->fileName);
        ret_value = -1;
    }
    fwrite_ret = fwrite(&configItem, sizeof(configItem)+1, 1, open_file);
    if (fwrite_ret != 0)
    {
        printf("SaveCfgDataBinary: Content written successfully !\n");
        ret_value = 0;
    }
    else
    {
        printf("SaveCfgDataBinary: Error writing file !\n");
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

    if(  strcmp(this->fileName,CFG_FILE) != 0)
    {
        snprintf(this->fileName, sizeof(this->fileName), "%s", CFG_FILE);
        printf("FileName :%s\n",this->fileName);
    }
    open_file = fopen(this->fileName, "r");
    if (open_file == NULL)
    {
        fprintf(stderr, " LoadCfgDataBinary: Error to open the file !\n");
        printf("FileName :%s\n",this->fileName);
        ret_value = -1;
    }
    /* Seek to the beginning of the file */
    fseek(open_file, 0, SEEK_SET);

    // reading to read_struct
    fread_ret = fread(&configItem, sizeof(configItem), 1, open_file);

    if (fread_ret != 0)
    {
        printf("LoadCfgDataBinary: Content read successfully !\n");
        ret_value = 0;
    }
    else
    {
        printf("LoadCfgDataBinary:Error reading file %s!\n",this->fileName);
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
    int ret_value = -1;
    FILE *configFile = fopen(this->fileName, "w");
    if (configFile != NULL)
    {
        for (int i = 0;i<size;i++)
        {
            // write the config items in file
            fprintf(configFile, "%d\n", configItems[i]);
        }
        ret_value = 0;
    }
    else
    {
        fprintf(stderr, "Error to open the file !\n");
        ret_value = - 1;
    }
    // close the file
    fclose(configFile);
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
        // close the file
        fclose(configFile);
    }
    else
    {
        fprintf(stderr, " ReadSimpleConfig: Error to open the file \n");
        printf("FileName :%s\n", this->fileName);
        // close the file
        fclose(configFile);
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
        // close the file
        fclose(configFile);
        return -1;
    }

    return 0;
}

/// @brief Save cfg data to a csv file
/// @param TableHead Head of the table
/// @param size The size of the TableHead
/// @param configItems Saved data - ConfigData
/// @param lines The number of lines in configuration
/// @return OK=0 NOK =-1
int ConfigDataWriter::SaveCfgDataCSV(const char *TableHead, int size, const char *configItems, int lines)
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
        for (int i = 0; i < lines; i++)
        {

            fprintf(configFile, "%s", configItems);
            fprintf(configFile, "\n"); // go to the next row
        }
        // close the file
        fclose(configFile);
    }
    else
    {
        fprintf(stderr, "SaveCfgDataCSV: Error to open the file!\n");
        // close the file
        fclose(configFile);
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
        // close the file
        fclose(configFile);
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
        // close the file
        fclose(configFile);
    }
    else
    {
        fprintf(stderr, " ReadIniConfig: Error to open the file \n");
        printf("FileName :%s\n", this->fileName);
        // close the file
        fclose(configFile);
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
/// @brief Read a csv file
/// @param fileName 
/// @return Returns 0 if the operation was succesfull and -1 if the file can't be opened
int ConfigDataWriter::ReadCSV_File(const char *fileName)
{
    char fileNameLocal[200];
    int num_tokens = 0;
    int num_lines = 0;
    int column = 0;
    snprintf(fileNameLocal, 30, "%s", fileName);
    FILE *file = fopen(fileNameLocal, "r");
    if (file == NULL)
    {
        fprintf(stderr, "ReadCSV_File: Error to open the file \n");
        fclose(file);
        return -1;
    }

    static char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file))
    {
        num_lines++;
        column = 0;
        num_tokens = 0;
        char *token;
        token = strtok(line, ",");
        if (token != NULL && num_tokens < MAX_NUM_FIELDS)
        {
            while (token)
            {
                printf("\nLine %d -> column %d = %s\t", num_lines, column, token);
                csv_tokens[num_tokens++] = token;
                token = strtok(NULL, ", ");
                column++;
            }
        }
    }
    csv_num_tokens = num_tokens;
    fclose(file);
    return num_tokens;
}
/// @brief 
/// @return 
int ConfigDataWriter::GetCsvNumTokens()
{
    return csv_num_tokens;
}
/// @brief 
/// @param token_index 
/// @return 
char *ConfigDataWriter::GetCsvToken(int token_index)
{
    return csv_tokens[token_index];
}