#include "menu_main.h"

#include <iostream>

const char* itemFile = "File";
const char* itemEdit = "Edit";
const char* itemView = "View";
const char* itemSave = "Save";
const char* itemOpen = "Open";
const char* itemExit = "Exit";
const char* itemUndo = "Undo";
const char* itemRedo = "Redo";
const char* itemView1 = "View1";
const char* itemView2 = "View2";

const MenuNode menu1[] = {
//       id | parentId | leftId | rightId | childId |  name  |  selectFunc  |   enterFunc   |
	{  File,        -1,      -1,     Edit,     Save, itemFile,  },
	{  Edit,        -1,    File,     View,     Undo, itemEdit,  },
	{  View,        -1,    View,       -1,    View1, itemView,  },
	{  Save,      File,      -1,     Open,       -1, itemSave,  },
	{  Open,      File,    Save,       -1,       -1, itemOpen,  },
	{  Exit,      File,    Open,       -1,       -1, itemExit,  },
	{  Undo,      Edit,      -1,     Redo,       -1, itemUndo,  },
	{  Redo,      Edit,    Undo,       -1,       -1, itemRedo,  },
	{ View1,      View,      -1,    View2,       -1, itemView1, },
	{ View2,      View,   View1,       -1,       -1, itemView2, },
	{    -1,        -1,      -1,       -1,       -1, nullptr,   },
};

const MenuNode* mainMenu = menu1;

// ------------------------------------------------------------------------

const MenuHandlerItem menuh1[] = {
//       id | function
	{  Edit,  [] (int i) { std::cout << "Edit selected" << std::endl; } },
	{    -1,  nullptr },
};
