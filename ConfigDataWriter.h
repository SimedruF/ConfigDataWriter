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
    ConfigDataWriter(const char *fileName);

    // Save binary config
    int SaveCfgDataBinary(const ConfigData &configItem);
    // Read binary config
    int LoadCfgDataBinary(ConfigData &configItem);
    // Save an array of int values in configuration file
    int SaveConfigIni(int *configItems, int size);
    // Read the values from config file into an array
    int ReadConfigIni(int *configItems);

private:
    char fileName[100];
};

#endif // CONFIGDATAWRITER_H
