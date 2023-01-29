#include "menumodelindex.h"

#include "menudefines.h"
#include "menumodel.h"

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

const char* MenuModelIndex::name() const
{
	return m_node
		? (language == 1) ? m_node->translate : m_node->name
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
