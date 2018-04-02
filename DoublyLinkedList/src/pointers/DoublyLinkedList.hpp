#pragma once
#include "Element.hpp"

class DoublyLinkedList
{
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	void add(const std::string& new_item);
	void remove(const size_t& number);
	std::string& operator[](const size_t& number);
private:
	Element* begin_, *end_;
};

