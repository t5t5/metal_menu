#include "menumodel.h"

MenuModel::MenuModel(const MenuNode* n)
	: node(n)
{
}

MenuModelIndex MenuModel::index(
		int line, const MenuModelIndex& parent /* = MenuModelIndex() */) const
{
	int parentItemId = (parent.isValid())
		? parent.m_node->id
		: RootMenuId;

	const MenuNode* n = node;
	int i = -1;
	while (n->id != NoMenuId) {
		if (n->parentId == parentItemId) {
			++i;
			if (i == line) { return MenuModelIndex(this, n, i); }
		}
		++n;
	}
	return MenuModelIndex();
}

bool MenuModel::hasChildren(const MenuModelIndex& parent) const
{
	int parentItemId = (parent.isValid())
		? parent.m_node->id
		: RootMenuId;

	const MenuNode* n = node;
	while (n->id != NoMenuId) {
		if (n->parentId == parentItemId) { return true; }
		++n;
	}
	return false;
}

int MenuModel::lineCount(const MenuModelIndex& parent /* = MenuModelIndex() */) const
{
	int parentItemId = (parent.isValid())
		? parent.m_node->id
		: RootMenuId;

	const MenuNode* n = node;
	int count = 0;
	while (n->id != NoMenuId) {
		if (n->parentId == parentItemId) { ++count; }
		++n;
	}
	return count;
}

MenuModelIndex MenuModel::parent(const MenuModelIndex& index) const
{
	if (!index.isValid()) { return MenuModelIndex(); }

	int parentMenuId = index.m_node->parentId;
	if (parentMenuId == RootMenuId) { return MenuModelIndex(); }

	const MenuNode* n = node;
	while (n->id != NoMenuId) {
		if (n->id == parentMenuId) {
			const MenuNode* nn = node;
			int i = -1;
			while (nn->id != NoMenuId) {
				if (nn->parentId == n->parentId) {
					++i;
					if (n == nn) {
						return MenuModelIndex(this, n, i);
					}
				}
				++nn;
			}
		}
		++n;
	}
	return MenuModelIndex();
}

const char* MenuModel::name(const MenuModelIndex& index) const
{
	return index.name();
}

AbstractMenuValue* MenuModel::value(const MenuModelIndex& index) const
{
	return index.value();
}

AbstractMenuAction* MenuModel::action(const MenuModelIndex& index) const
{
	return index.action();
}
