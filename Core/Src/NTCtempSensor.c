#include "NTCtempSensor.h"
extern ADC_HandleTypeDef hadc1;

const float temperature_table = {{25, 150, 250}, {103180, 1366.2, 168.6}};
