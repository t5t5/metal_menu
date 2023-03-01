#include "menu_main.h"

#include "parameters.h"


#include "menuaction_setvalue_number.h"
#include "menuvalue_enum.h"
#include "menuvalue_enumkey.h"
#include "menuvalue_ip.h"
#include "menuvalue_ip2.h"
#include "menuvalue_floatconst.h"
#include "menuvalue_number.h"
#include "menuvalue_textconst.h"

// ------------------------------------------------------------------------
// languages
static EnumKeyMenuValue<int>::Item LanguagesTextValues[] =
{
	{ 0,  "English", "Анг." },
	{ 1,  "Russian", "Рус." },
};
static EnumKeyMenuValue<int> languageEnumKeyValueItem(language, LanguagesTextValues);

static SetValueNumberMenuAction<int> setEnglishAction(language, 0);
static SetValueNumberMenuAction<int> setRussianAction(language, 1);

// ------------------------------------------------------------------------
// main screen changable read only parameters
static NumberMenuValue<int> randomIntValueItem(randomIntConst);
static ConstFloatMenuValue randomFloatValueItem(randomFloatConst);

// ------------------------------------------------------------------------
// number baud rate read only parameter
static NumberMenuValue<int> baudRateIntValueItem(baudRate);

// number enum baud rate parameters
static int BaudRateIntValues[] = { 9600, 57600, 115200, };
static EnumMenuValue<int> baudRateEnumValueItem(baudRate, BaudRateIntValues);

// number enum with text baud rate parameters
static EnumKeyMenuValue<int>::Item BaudRateTextValues[] = {
	{ 9600,   "Slow",   "Медл."},
	{ 57600,  "Normal", "Норм."},
	{ 115200, "Fast",   "Быст."},
};
static EnumKeyMenuValue<int> baudRateEnumKeyValueItem(baudRate, BaudRateTextValues);

// ------------------------------------------------------------------------
// read only text values
static ConstTextMenuValue versionValueItem("0.99a");

// ------------------------------------------------------------------------
// ip addresses editors
static IpMenuValue ip1ValueItem(ipAddress);
static Ip2MenuValue ip2ValueItem(ipAddress);

// ------------------------------------------------------------------------
// main menu struct
MenuNode menu1[] = {
//             id |   parentId  |                  flags |           name |         translate |                    value |            action
	{  Application,   RootMenuId,        Menu::NoItemFlag,   "Application",       "Приложение",                   nullptr,            nullptr, },
	{      Message,  Application,        Menu::NoItemFlag,       "Message",        "Сообщение",                   nullptr,            nullptr, },
	{      Version,  Application,        Menu::NoItemFlag,       "Version",           "Версия",         &versionValueItem,            nullptr, },
	{         Exit,  Application,        Menu::NoItemFlag,          "Exit",            "Выход",                   nullptr,            nullptr, },
	{    RandomInt,   RootMenuId, Menu::ItemValueReadOnly,    "Random Int",  "Случайное целое",       &randomIntValueItem,            nullptr, },
	{  RandomFloat,   RootMenuId, Menu::ItemValueReadOnly,  "Random Float",  "Случайное плав.",     &randomFloatValueItem,            nullptr, },
	{   Parameters,   RootMenuId,        Menu::NoItemFlag,     "Paramters",        "Параметры",                   nullptr,            nullptr, },
	{      Network,   RootMenuId,        Menu::NoItemFlag,       "Network",             "Сеть",                   nullptr,            nullptr, },
	{    Languages,   Parameters,        Menu::NoItemFlag,     "Languages",            "Языки",                   nullptr,            nullptr, },
	{      EngLang,    Languages,        Menu::NoItemFlag,       "English",       "Английский",                   nullptr,  &setEnglishAction, },
	{      RusLang,    Languages,        Menu::NoItemFlag,       "Russian",          "Русский",                   nullptr,  &setRussianAction, },
	{   RusEngLang,    Languages,        Menu::NoItemFlag,      "Language",             "Язык", &languageEnumKeyValueItem,            nullptr, },
	{  BaudRateInt,   Parameters, Menu::ItemValueReadOnly,   "BaudRateInt",     "Скорость-Int",     &baudRateIntValueItem,            nullptr, },
	{ BaudRateEnum,   Parameters,        Menu::NoItemFlag,  "BaudRateEnum",    "Скорость-Enum",    &baudRateEnumValueItem,            nullptr, },
	{ BaudRateText,   Parameters,        Menu::NoItemFlag,  "BaudRateText",    "Скорость-Text", &baudRateEnumKeyValueItem,            nullptr, },
	{      ParamIP,      Network,  Menu::ItemValueComplex,   "IP address 1",      "IP адрес 1",             &ip1ValueItem,            nullptr, },
	{     ParamIP2,      Network,  Menu::ItemValueComplex,   "IP address 2",      "IP адрес 2",             &ip2ValueItem,            nullptr, },
	{     NoMenuId,     NoMenuId,        Menu::NoItemFlag,         nullptr,            nullptr,                   nullptr,            nullptr, },
};

MenuNode* mainMenu = menu1;

// ------------------------------------------------------------------------
