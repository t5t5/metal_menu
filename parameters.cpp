#include "parameters.h"

static NumberParameter<int> p_language(1);
static NumberParameter<int> p_randomInt(1);
static NumberParameter<float> p_randomFloat(12.56f);
static NumberParameter<int> p_baudRate(9600);
static IpAddressParameter p_ipAddress(192, 168, 0, 254);

NumberParameter<int>* language = &p_language;
NumberParameter<int>* randomIntConst = &p_randomInt;
NumberParameter<float>* randomFloatConst = &p_randomFloat;
NumberParameter<int>* baudRate = &p_baudRate;
IpAddressParameter* ipAddress = &p_ipAddress;
