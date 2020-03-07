#pragma once

#include <vector>
class ContactList
{
	friend class ContactListener;
public:
	static void AddToList(unsigned int entity);
	static void RemoveFromList(unsigned int entity);
private:
	static std::vector<unsigned int> list;
};


inline std::vector<unsigned int> ContactList::list = {};

inline void ContactList::AddToList(unsigned int entity)
{
	list.push_back(entity);
}

inline void ContactList::RemoveFromList(unsigned int entity)
{
	for (int x(0); x < list.size(); x++) {
		if (list[x] == entity) {
			list.erase(list.begin() + x, list.begin() + x + 1);
			break;
		}
	}
}