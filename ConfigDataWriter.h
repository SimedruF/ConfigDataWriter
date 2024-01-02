#ifndef CONFIGDATAWRITER_H
#define CONFIGDATAWRITER_H
/* Cfg structure*/
struct ConfigData
{
    int blades_nb;
    int max_rot_speed;
    int airflow_pressure;
};
class ConfigDataWriter
{
public:
    // ConfigDataWriter constructor
    ConfigDataWriter(const char *fileName);
    // Save binary config
    int SaveCfgDataBinary(const ConfigData &configItem);
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

private:
    char fileName[100];
};

#endif // CONFIGDATAWRITER_H
