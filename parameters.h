#ifndef PARAMETERS_H
#define PARAMETERS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "parameter_number.h"
#include "parameter_ipaddress.h"

extern NumberParameter<int>* language;
extern NumberParameter<int>* randomIntConst;
extern NumberParameter<float>* randomFloatConst;
extern NumberParameter<int>* baudRate;
extern IpAddressParameter* ipAddress;

#endif // PARAMETERS_H
