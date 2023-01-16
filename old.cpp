// from godbolt
#include <iostream>

using MenuId = char;

enum MenuIds
{
    File = 0,
    Edit = 1,
    View = 2,
    Save = 3,
    Open = 4,
    Exit = 5,
    Undo = 6,
    Redo = 7,
    View1 = 8,
    View2 = 9,
};

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

struct MenuNode
{
    MenuId id;
    MenuId parentId;
    MenuId leftId;
    MenuId rightId;
    MenuId childId;
    const char* name;
    void (*selectFunction)();
    void (*enterFunction)();
};

void selectHello()
{
    std::cout << "selectHello" << std::endl;
}

void enterHello()
{
    std::cout << "enterHello" << std::endl;
}

const MenuNode menu1[] = {
//       id | parentId | leftId | rightId | childId |  name  |  selectFunc  |   enterFunc   |
    {  File,        -1,      -1,     Edit,     Save, itemFile,  selectHello,    enterHello },
    {  Edit,        -1,    File,     View,     Undo, itemEdit,  nullptr,    nullptr },
    {  View,        -1,    View,       -1,    View1, itemView,  nullptr,    nullptr },
    {  Save,      File,      -1,     Open,       -1, itemSave,  nullptr,    nullptr },
    {  Open,      File,    Save,       -1,       -1, itemOpen,  nullptr,    nullptr },
    {  Exit,      File,    Open,       -1,       -1, itemExit,  nullptr,    nullptr },
    {  Undo,      Edit,      -1,     Redo,       -1, itemUndo,  nullptr,    nullptr },
    {  Redo,      Edit,    Undo,       -1,       -1, itemRedo,  nullptr,    nullptr },
    { View1,      View,      -1,    View2,       -1, itemView1, nullptr,    nullptr },
    { View2,      View,   View1,       -1,       -1, itemView2, nullptr,    nullptr },
    {    -1,        -1,      -1,       -1,       -1, nullptr,   nullptr,    nullptr },
};

class MenuModel
{
public:
    MenuModel(const MenuNode* n);

    bool hasNext(int itemId) const;
    bool hasPrevious(int itemId) const;
    bool hasParent(int itemId) const;
    bool hasChild(int itemId) const;

    int id(int itemId) const;
    int next(int itemId) const;
    int previous(int itemId) const;
    int parent(int itemId) const;
    int child(int itemId) const;
    const char* name(int itemId) const;
private:
    const MenuNode* node;
};

MenuModel::MenuModel(const MenuNode* n) : node(n) { }

bool MenuModel::hasNext(int itemId) const
{
    const MenuNode* n = node + itemId;
    return n->rightId != -1;
}

bool MenuModel::hasPrevious(int itemId) const
{
    const MenuNode* n = node + itemId;
    return n->leftId != -1;
}

bool MenuModel::hasParent(int itemId) const
{
    const MenuNode* n = node + itemId;
    return n->parentId != -1;
}

bool MenuModel::hasChild(int itemId) const
{
    const MenuNode* n = node + itemId;
    return n->childId != -1;
}

int MenuModel::id(int itemId) const
{
    const MenuNode* n = node + itemId;
    return n->id;
}

int MenuModel::next(int itemId) const
{
    const MenuNode* n = node + itemId;
    return (n->rightId != -1) ? n->rightId : -1;
}

int MenuModel::previous(int itemId) const
{
    const MenuNode* n = node + itemId;
    return (n->leftId != -1) ? n->leftId : -1;
}

int MenuModel::parent(int itemId) const
{
    const MenuNode* n = node + itemId;
    return (n->parentId != -1) ? n->parentId : -1;
}

int MenuModel::child(int itemId) const
{
    const MenuNode* n = node + itemId;
    n->enterFunction();
    return (n->childId != -1) ? n->childId : -1;
}

const char* MenuModel::name(int itemId) const
{
    const MenuNode* n = node + itemId;
    return (n->id != -1) ? n->name : nullptr;
}


int main()
{
    MenuModel m(menu1);
    int id = MenuIds::File;
    std::cout << id << " " << m.name(id) << std::endl;
    id = m.next(id); // к соседнему справа
    std::cout << id << " " << m.name(id) << std::endl;
    id = m.child(id); // к первому ребенку
    std::cout << id << " " << m.name(id) << std::endl;
    id = m.parent(id); // к родителю
    std::cout << id << " " << m.name(id) << std::endl;
    return 0;
}