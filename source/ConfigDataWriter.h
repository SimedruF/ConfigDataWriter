#ifndef CONFIGDATAWRITER_H
#define CONFIGDATAWRITER_H
#include "ConfigDataWriterStruct.h"
#define CFG_FILE (char*)"ea_test1.cfg"
#define MAX_LINE_LENGTH 1024
#define MAX_NUM_FIELDS 100

class ConfigDataWriter
{
public:
    // ConfigDataWriter constructor
    ConfigDataWriter(const char *fileName);
    // Save binary config
    int SaveCfgDataBinary(const ConfigData &configItem);
    int SaveCfgDataBinary(const char *fileName, const ConfigData &configItem);
    // Read binary config
    int LoadCfgDataBinary(ConfigData &configItem);
    // Save an array of int values in configuration file
    int SaveSimpleConfig(int *configItems, int size);
    // Read the values from config file into an array
    int ReadSimpleConfig(int *configItems);
    // Save integer data in CSV format
    int SaveIntDataCSV(const char *TableHead, int size, int *configItems, int column, int row);
    // Save float data in CSV format
    int SaveFloatDataCSV(const char *TableHead, int size, float *configItems, int column, int row);
    // Save ini file
    int SaveIniConfig(char *Comment, char *Section, char ConfigItemName[][20], int *configItems, int size);
    /// Read ini file -> parsing the ini file to identify the sections
    /// and for each section the list of config variables -> work in progress
    int ReadIniConfig(int *configItems);
    /// @brief Read a csv file
    /// @param fileName
    /// @return Returns 0 if the operation was succesfull and -1 if the file can't be opened
    int ReadCSV_File(const char *fileName);

    int SaveCfgDataCSV(const char *TableHead, int size, const char *configItems, int lines);

    /// @brief Set cfg buffer
    /// @param cfg_buffer
    /// @param size
    void SetCfgBuffer(char *cfg_buffer, int size);

    /// Get cfg buffer 
    char *GetCfgBuffer();

    /// GetCsvNumTokens
    int GetCsvNumTokens();
    /// GetCsvToken
    char *GetCsvToken(int token_index);

private:
    char fileName[200];
    char cfgBuffer[200];
    char *csv_tokens[MAX_NUM_FIELDS];
    int csv_num_tokens;
};

#endif // CONFIGDATAWRITER_H
