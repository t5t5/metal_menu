#include "menu_main.h"

const char* itemApplication = "Application";
const char* itemParameters  = "Parameters";
const char* itemLanguages   = "Languages";
const char* itemExit        = "Exit";
const char* itemParam1      = "Parameter1";
const char* itemParam2      = "Parameter2";
const char* itemParam3      = "Parameter3";
const char* itemResetParam3 = "Reset Parameter3";
const char* itemRusLang     = "Russin";
const char* itemEngLang     = "English";

const char* itemTrApplication = "Приложение";
const char* itemTrParameters  = "Параметры";
const char* itemTrLanguages   = "Языки";
const char* itemTrExit        = "Выход";
const char* itemTrParam1      = "Parameter1";
const char* itemTrParam2      = "Parameter2";
const char* itemTrParam3      = "Parameter3";
const char* itemTrResetParam3 = "Сброс Parameter3";
const char* itemTrRusLang     = "Русский";
const char* itemTrEngLang     = "Английский";

static int param3 = 100;

int language = 0;

static NumberMenuValue<int> param3value(&param3);
static SetValueMenuAction<int> param3reset(&param3, 100);

static SetValueMenuAction<int> setEnglish(&language, 0);
static SetValueMenuAction<int> setRussian(&language, 1);

const MenuNode menu1[] = {
//             id  |   parentId |           name |        translate |        value |      action
	{ Application,   RootMenuId, itemApplication, itemTrApplication,       nullptr,      nullptr, },
	{  Parameters,   RootMenuId,  itemParameters,  itemTrParameters,       nullptr,      nullptr, },
	{   Languages,   RootMenuId,   itemLanguages,   itemTrLanguages,       nullptr,      nullptr, },
	{        Exit,  Application,        itemExit,        itemTrExit,       nullptr,      nullptr, },
	{      Param1,   Parameters,      itemParam1,      itemTrParam1,       nullptr,      nullptr, },
	{      Param2,   Parameters,      itemParam2,      itemTrParam2,       nullptr,      nullptr, },
	{      Param3,   Parameters,      itemParam3,      itemTrParam3,  &param3value,      nullptr, },
	{ ResetParam3,   Parameters, itemResetParam3, itemTrResetParam3,       nullptr, &param3reset, },
	{     EngLang,    Languages,     itemEngLang,     itemTrEngLang,       nullptr,  &setEnglish, },
	{     RusLang,    Languages,     itemRusLang,     itemTrRusLang,       nullptr,  &setRussian, },
	{    NoMenuId,     NoMenuId,         nullptr,           nullptr,       nullptr,      nullptr, },
};

const MenuNode* mainMenu = menu1;

// ------------------------------------------------------------------------
