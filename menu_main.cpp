#include "menu_main.h"

#include "menuvalue_enum.h"
#include "menuvalue_enumkey.h"
#include "menuvalue_ip.h"
#include "menuvalue_ip2.h"
#include "menuvalue_number.h"
#include "menuvalue_text.h"

const char* itemApplication = "Application";
const char* itemParameters  = "Parameters";
const char* itemLanguages   = "Languages";
const char* itemMessage     = "Message";
const char* itemVersion     = "Version";
const char* itemExit        = "Exit";
const char* itemParam1      = "Parameter1";
const char* itemBaudRate1   = "BaudRateInt";
const char* itemBaudRate2   = "BaudRateEnum";
const char* itemBaudRate3   = "BaudRateText";
const char* itemParam3      = "Parameter3";
const char* itemParamIP     = "IP";
const char* itemParamIP2    = "IP2";
const char* itemResetParam3 = "Reset Parameter3";
const char* itemRusLang     = "Russin";
const char* itemEngLang     = "English";

const char* itemTrApplication = "Приложение";
const char* itemTrParameters  = "Параметры";
const char* itemTrLanguages   = "Языки";
const char* itemTrMessage     = "Сообщение";
const char* itemTrVersion     = "Версия";
const char* itemTrExit        = "Выход";
const char* itemTrParam1      = "Parameter1";
const char* itemTrBaudRate1   = "Скорость-Int";
const char* itemTrBaudRate2   = "Скорость-Enum";
const char* itemTrBaudRate3   = "Скорость-Text";
const char* itemTrParam3      = "Parameter3";
const char* itemTrParamIP     = "IP";
const char* itemTrParamIP2    = "IP2";
const char* itemTrResetParam3 = "Сброс Parameter3";
const char* itemTrRusLang     = "Русский";
const char* itemTrEngLang     = "Английский";

enum BaudRate
{
	Rate9600 = 9600,
	Rate57600 = 57600,
	Rate115200 = 115200,
};

static int baudRateInt = 9600;
static BaudRate baudRateEnum = Rate9600;
static int param3 = 100;

int language = 0;

static int BaudRateIntValues[] = { 9600, 57600, 115200, };
static EnumMenuValue<int> baudRateValueInt(&baudRateInt, BaudRateIntValues);

static BaudRate BaudRateEnumValues[] = { Rate9600, Rate57600, Rate115200, };
static EnumMenuValue<BaudRate> baudRateValueEnum(&baudRateEnum, BaudRateEnumValues);

static EnumKeyMenuValue<int>::Item BaudRateTextValues[] = {
	{ 9600,   "Slow",   "Медл."},
	{ 57600,  "Normal", "Норм."},
	{ 115200, "Fast",   "Быст."},
};
static EnumKeyMenuValue<int> baudRateValueText(&baudRateInt, BaudRateTextValues);

static NumberMenuValue<int> param3value(&param3);
static SetValueMenuAction<int> param3reset(&param3, 100);

static SetValueMenuAction<int> setEnglish(&language, 0);
static SetValueMenuAction<int> setRussian(&language, 1);

static const char version[] = "0.99a";

static TextMenuValue versionValue(version);

static unsigned char ip[4] = { 192, 168, 1, 254 };
static IpMenuValue paramIpValue(ip);

static unsigned char ip2[4] = { 192, 168, 1, 254 };
static Ip2MenuValue paramIp2Value(ip2);

MenuNode menu1[] = {
//             id |   parentId  |                 flags |           name |        translate |             value |      action
	{  Application,   RootMenuId,       Menu::NoItemFlag, itemApplication, itemTrApplication,            nullptr,      nullptr, },
	{   Parameters,   RootMenuId,       Menu::NoItemFlag,  itemParameters,  itemTrParameters,            nullptr,      nullptr, },
	{    Languages,   RootMenuId,       Menu::NoItemFlag,   itemLanguages,   itemTrLanguages,            nullptr,      nullptr, },
	{      Message,  Application,       Menu::NoItemFlag,     itemMessage,     itemTrMessage,            nullptr,      nullptr, },
	{      Version,  Application,       Menu::NoItemFlag,     itemVersion,     itemTrVersion,      &versionValue,      nullptr, },
	{         Exit,  Application,       Menu::NoItemFlag,        itemExit,        itemTrExit,            nullptr,      nullptr, },
	{      ParamIP,   Parameters, Menu::ItemValueComplex,     itemParamIP,     itemTrParamIP,      &paramIpValue,      nullptr, },
	{     ParamIP2,   Parameters, Menu::ItemValueComplex,    itemParamIP2,    itemTrParamIP2,     &paramIp2Value,      nullptr, },
	{       Param1,   Parameters,       Menu::NoItemFlag,      itemParam1,      itemTrParam1,            nullptr,      nullptr, },
	{  BaudRateInt,   Parameters,       Menu::NoItemFlag,   itemBaudRate1,   itemTrBaudRate1,  &baudRateValueInt,      nullptr, },
	{ BaudRateText,   Parameters,       Menu::NoItemFlag,   itemBaudRate3,   itemTrBaudRate3, &baudRateValueText,      nullptr, },
	{ BaudRateEnum,   Parameters,       Menu::NoItemFlag,   itemBaudRate2,   itemTrBaudRate2, &baudRateValueEnum,      nullptr, },
	{       Param3,   Parameters, Menu::ItemValueComplex,      itemParam3,      itemTrParam3,       &param3value,      nullptr, },
	{  ResetParam3,   Parameters,       Menu::NoItemFlag, itemResetParam3, itemTrResetParam3,            nullptr, &param3reset, },
	{      EngLang,    Languages,       Menu::NoItemFlag,     itemEngLang,     itemTrEngLang,            nullptr,  &setEnglish, },
	{      RusLang,    Languages,       Menu::NoItemFlag,     itemRusLang,     itemTrRusLang,            nullptr,  &setRussian, },
	{     NoMenuId,     NoMenuId,       Menu::NoItemFlag,         nullptr,           nullptr,            nullptr,      nullptr, },
};

MenuNode* mainMenu = menu1;

// ------------------------------------------------------------------------
