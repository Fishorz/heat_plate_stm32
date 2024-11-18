#include "NTCtempSensor.h"

//-40 ~ +300 ℃ /5
// in k ohm x.xxx
//1 = -40
//2 = -35
//3 = -30
//static uint32_t ntc3960_100k[] = { 3283068, 2364601, 1728310, 1279210, 957158,
//		723060, 550905, 423023, 327187, 254804, 199749, 157602, 125142, 100000,
//		80419, 65087, 53020, 43473, 35882, 296898, 24713, 20657, 17345, 14628,
//		12386, 10530, 8985, 7694, 6610, 5698, 4926, 4272, 3714, 3238, 2830,
//		2479, 2176, 1915, 1688, 1497, 1330, 1185, 1058, 947, 849, 764, 688, 621,
//		561, 509, 462, 420, 383, 349, 319, 292, 268, 246, 226, 208, 192, 178,
//		165, 153, 142, 132, 123, 114, 107 };

static uint32_t PT_1000[] = {
		 960.9,  980.4,   1000, 1019.5, 1039.0, 1058.5, //-10 - 15
		1077.9, 1097.3, 1116.7, 1136.1, 1155.4, 1174.7, //20 - 45
		1194.0, 1213.2, 1232.4, 1251.6, 1270.8, 1289.9, //50 - 75
		1309.0, 1328.0, 1347.1, 1366.1, 1385.1, 1404.0, //80 - 105
		1422.9, 1441.8, 1460.7, 1479.5, 1498.3, 1517.1, //110-135
		1535.8, 1554.6, 1573.3, 1591.9, 1610.5, 1629.1, //140 - 165
		1647.7, 1666.3, 1684.8, 1703.3, 1721.7, 1740.2, //170 - 195
		1758.6, 1776.9, 1795.3, 1813.6, 1831.9, 1850.1,//200 - 225
		1904.7, 1922.9, 1941.0, 1959.1, 1941.0, 1955.5, //230 - 255
		1977.1, 1995.1, 2013.1, 2031.1, 2049.0, 2067.0,  //260 - 285
		2084.8, 2102.7, 2120.5, //290 - 300
};

void adcSelect(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
		uint32_t channel) {
	sConfig->Channel = channel;
}

//void calTemp(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
//		NTC_TypeDef *uNTC) {
int32_t getTableNum(NTC_TypeDef *uNTC) {
	int length;
//	length = sizeof(ntc3960_100k) / sizeof(ntc3960_100k[0]);
	length = sizeof(PT_1000) / sizeof(PT_1000[0]);
	int32_t i = 0;
//	for (i = 0; i < sizeof(ntc3960_100k) - 1; i++) {
	for (i = 0; i < length; i++) {
		/* Use of > determined by inspection of data - colder temps have higher ADC value */
//		if (uNTC->resistor > ntc3960_100k[i])
		if (uNTC->resistor > PT_1000[i])
			return i;
	}
	return i;
}

float calTemp(NTC_TypeDef *uNTC, uint32_t inoputAdcValue) {
	uNTC->_NTC_adcvalue = inoputAdcValue;
//	printf("run cal temp \r\n");

//cal resistor
	uNTC->voltage = 0.0;
	// 3.3V is mcu voltage
	uNTC->voltage = (uNTC->_NTC_adcvalue / 4096.0) * 3.3;
	uNTC->voltage = uNTC->voltage + 0.05;
	uNTC->resistor = (refenceResistor * 1.0 * uNTC->voltage)
			/ (supplyVoltage * 1.0 - (uNTC->voltage));
//	uNTC->resistor = uNTC->resistor;

	uNTC->tableNum = getTableNum(uNTC);
	int32_t temp1, temp2;
	// -10 mean the firt temp in the table
	//*5 mean step of the temp in the table
	temp1 = -10 + (uNTC->tableNum * 5);
	temp2 = -10 + ((uNTC->tableNum + 1) * 5);
// for over temp
//	if (uNTC->tableNum >= sizeof(ntc3960_100k)) {
	if (uNTC->tableNum >= sizeof(PT_1000)) {
		temp2 = temp1;
	}
//	double c = (ntc3960_100k[uNTC->tableNum + 1] - uNTC->resistor)
//			/ (uNTC->resistor - ntc3960_100k[uNTC->tableNum]);
	double c = (PT_1000[uNTC->tableNum + 1] - uNTC->resistor)
			/ (uNTC->resistor - PT_1000[uNTC->tableNum]);
	uNTC->temp = (temp2 + c * temp1) / (1 + c);

//	uNTC->temp = (1.0
//			/ (c1 + c2 * uNTC->logR2
//					+ c3 * uNTC->logR2 * uNTC->logR2 * uNTC->logR2));

//	uint32_t fti; //double to int
//				logR2 = logR2 *10000;
//	fti = (uint32_t) uNTC->temp;
//				fti = (int) temp[i];
//	printf("run cal temp done!!\r\n");
	return uNTC->temp;
}
