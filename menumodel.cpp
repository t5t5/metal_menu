#include "menumodel.h"

const MenuNode* findMenuNode(const MenuNode* n, int itemId)
{
	while (n->id != NoMenuId) {
		if (n->id == itemId) { return n; }
		++n;
	}
	return nullptr;
}

// ------------------------------------------------------------------------

MenuModel::MenuModel(const MenuNode* n)
	: node(n)
{
}

bool MenuModel::hasNext(int itemId) const
{
	auto n = findMenuNode(node, itemId);
	if (n == nullptr) { return false; }
	auto nn = n + 1;
	return ((nn->id != NoMenuId) && (nn->parentId == n->parentId));
}

bool MenuModel::hasPrevious(int itemId) const
{
	auto n = findMenuNode(node, itemId);
	if ((n == nullptr) || (n == node)) { return false; }
	auto pn = n - 1;
	return pn->parentId == n->parentId;
}

bool MenuModel::hasParent(int itemId) const
{
	auto n = findMenuNode(node, itemId);
	if (n == nullptr) { return false; }
	return n->parentId != RootMenuId;
}

bool MenuModel::hasChild(int itemId) const
{
	return childrenCount(itemId) > 0;
}

int MenuModel::childrenCount(int itemId) const
{
	const MenuNode* n = node;
	int count = 0;
	while (n->id != NoMenuId) {
		if (n->parentId == itemId) { ++count; }
		++n;
	}
	return count;
}

int MenuModel::id(int itemId) const
{
	auto n = findMenuNode(node, itemId);
	return (n == nullptr) ? NoMenuId : n->id;
}

int MenuModel::next(int itemId) const
{
	auto n = findMenuNode(node, itemId);
	if (n == nullptr) { return NoMenuId; }
	auto nn = n + 1;
	return ((nn->id != NoMenuId) && (nn->parentId == n->parentId))
		? nn->id
		: NoMenuId;
}

int MenuModel::previous(int itemId) const
{
	auto n = findMenuNode(node, itemId);
	if ((n == nullptr) || (n == node)) { return NoMenuId; }
	auto pn = n - 1;
	return (pn->parentId == n->parentId) ? pn->id : NoMenuId;
}

int MenuModel::parent(int itemId) const
{
	auto n = findMenuNode(node, itemId);
	if (n == nullptr) { return NoMenuId; }
	return n->parentId;
}

int MenuModel::child(int parentItemId, int index /* = 0 */) const
{
	const MenuNode* n = node;
	int i = -1;
	while (n->id != NoMenuId) {
		if (n->parentId == parentItemId) {
			++i;
			if (i == index) { return n->id; }
		}
		++n;
	}
	return NoMenuId;
}

const char* MenuModel::name(int itemId) const
{
	if (itemId == RootMenuId) { return nullptr; }
	auto n = findMenuNode(node, itemId);
	return (n == nullptr)
		? nullptr
		: (language == 1) ? n->translate : n->name;
}

AbstractMenuValue* MenuModel::value(int itemId) const
{
	auto n = findMenuNode(node, itemId);
	return (n == nullptr) ? nullptr : n->value;
}

AbstractMenuAction* MenuModel::action(int itemId) const
{
	auto n = findMenuNode(node, itemId);
	return (n == nullptr) ? nullptr : n->action;
}
