#include "NTCtempSensor.h"

//-40 ~ +300 ℃ /5
// in k ohm x.xxx
//1 = -40
//2 = -35
//3 = -30
static uint32_t ntc3960_100k[] = { 3283068, 2364601, 1728310, 1279210, 957158,
		723060, 550905, 423023, 327187, 254804, 199749, 157602, 125142, 100000,
		80419, 65087, 53020, 43473, 35882, 296898, 24713, 20657, 17345, 14628,
		12386, 10530, 8985, 7694, 6610, 5698, 4926, 4272, 3714, 3238, 2830,
		2479, 2176, 1915, 1688, 1497, 1330, 1185, 1058, 947, 849, 764, 688, 621,
		561, 509, 462, 420, 383, 349, 319, 292, 268, 246, 226, 208, 192, 178,
		165, 153, 142, 132, 123, 114, 107 };

void adcSelect(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
		uint32_t channel) {
	sConfig->Channel = channel;

}

//void calTemp(ADC_HandleTypeDef *hadc, ADC_ChannelConfTypeDef *sConfig,
//		NTC_TypeDef *uNTC) {
int32_t getTableNum(NTC_TypeDef *uNTC) {
	int length;
	length = sizeof(ntc3960_100k) / sizeof(ntc3960_100k[0]);
	int32_t i = 0;
//	for (i = 0; i < sizeof(ntc3960_100k) - 1; i++) {
	for (i = 0; i < length; i++) {
		/* Use of > determined by inspection of data - colder temps have higher ADC value */
		if (uNTC->resistor > ntc3960_100k[i])
			return i;
	}
	return i;
}

float calTemp(NTC_TypeDef *uNTC, uint32_t inoputAdcValue) {
	uNTC->_NTC_adcvalue = inoputAdcValue;
//	printf("run cal temp \r\n");

//cal resistor
	float voltage = 0.0;
	// 3.3V is mcu voltage
	voltage = (uNTC->_NTC_adcvalue / 4096.0) * 3.3;
	uNTC->resistor = (refenceResistor * 1.0 * voltage)
			/ (supplyVoltage * 1.0 - (voltage));
	uNTC->resistor = uNTC->resistor;

	uNTC->tableNum = getTableNum(uNTC);
	int32_t temp1, temp2;
	temp1 = -40 + (uNTC->tableNum * 5);
	temp2 = -40 + ((uNTC->tableNum + 1) * 5);
// for over temp
	if (uNTC->tableNum >= sizeof(ntc3960_100k)) {
		temp2 = temp1;
	}
	double c = (ntc3960_100k[uNTC->tableNum + 1] - uNTC->resistor)
			/ (uNTC->resistor - ntc3960_100k[uNTC->tableNum]);
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
