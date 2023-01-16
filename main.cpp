#include <iostream>

#include "menu_main.h"
#include "menumodel.h"

int main() {
	MenuModel m(mainMenu);
	int id = MenuIds::File;
	std::cout << m.name(id) << ".childCount=" << m.childrenCount(id) << std::endl;

	std::cout << id << " " << m.name(id) << std::endl;
	id = m.next(id); // к соседнему справа
	std::cout << m.name(id) << ".childCount=" << m.childrenCount(id) << std::endl;
	std::cout << id << " " << m.name(id) << std::endl;
	id = m.child(id); // к первому ребенку
	std::cout << m.name(id) << ".childCount=" << m.childrenCount(id) << std::endl;
	std::cout << id << " " << m.name(id) << std::endl;
	id = m.parent(id); // к родителю
	std::cout << id << " " << m.name(id) << std::endl;
	return 0;
}
