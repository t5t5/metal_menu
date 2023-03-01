#include "menumodelindex.h"

#include "menudefines.h"
#include "menumodel.h"
#include "parameters.h"

MenuModelIndex::MenuModelIndex(const MenuModel* model, MenuNode* node, int line)
	: m_model(model)
	, m_node(node)
	, m_line(line)
{
}

MenuModelIndex::MenuModelIndex()
	: m_model(nullptr)
	, m_node(nullptr)
	, m_line(0)
{
}

bool MenuModelIndex::isValid() const
{
	return m_model;
}

const MenuModel* MenuModelIndex::model() const
{
	return m_model;
}

MenuModelIndex MenuModelIndex::parent() const
{
	return m_model
		? m_model->parent(*this)
		: MenuModelIndex();
}

int MenuModelIndex::line() const
{
	return m_line;
}

Menu::ItemFlags MenuModelIndex::flags() const
{
	Menu::ItemFlags flags = Menu::NoItemFlag;
	if (m_node) {
		flags = m_node->flags;
		if (!flags.test(Menu::ItemValueReadOnly)) {
			AbstractMenuValue* v = m_node->value;
			if (!v || (v && v->isReadOnly())) {
				flags |= Menu::ItemValueReadOnly;
			}
		}
	}
	return flags;
}

const char* MenuModelIndex::name() const
{
	return m_node
		? (language->value() == 1) ? m_node->translate : m_node->name
		: nullptr;
}

AbstractMenuValue* MenuModelIndex::value() const
{
	return m_node ? m_node->value : nullptr;
}

AbstractMenuAction* MenuModelIndex::action() const
{
	return m_node ? m_node->action : nullptr;
}

void MenuModelIndex::setValue(AbstractMenuValue* value) const
{
	if (!m_node) { return; }
	m_node->value = value;
}

void MenuModelIndex::setAction(AbstractMenuAction* action) const
{
	if (!m_node) { return; }
	m_node->action = action;
}

bool MenuModelIndex::operator==(const MenuModelIndex& other) const
{
	return m_node == other.m_node;
}

bool MenuModelIndex::operator!=(const MenuModelIndex& other) const
{
	return m_node != other.m_node;
}
