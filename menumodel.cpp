#include "menumodel.h"

MenuModel::MenuModel(const MenuNode* n)
	: node(n)
{
}

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

int MenuModel::childrenCount(int itemId) const
{
	const MenuNode* n = node + itemId;
	if (n->childId == -1) { return 0; }
	int count = 1;
	while (n->rightId != -1) {
		++count;
		n = node + int(n->rightId);
	}
	return count;
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
	return (n->childId != -1) ? n->childId : -1;
}

const char* MenuModel::name(int itemId) const
{
	const MenuNode* n = node + itemId;
	return (n->id != -1) ? n->name : nullptr;
}
