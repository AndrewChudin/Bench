#include "stdafx.h"
#include "DoublyLinkedList.hpp"

DoublyLinkedList::DoublyLinkedList()
{
}

DoublyLinkedList::~DoublyLinkedList()
{

	Element *item = begin_, *next;
	while (item != nullptr)
	{
		next = item->get_next();
		delete item;
		item = next;
	}

}

void DoublyLinkedList::add(const std::string& data)
{
	Element* new_item = new Element(data);
	if (end_ != (Element*)0)
	{
		end_->set_next(new_item);
		new_item->set_prev(end_);
		end_ = new_item;
	}
	else
	{
		begin_ = new_item;
		end_ = new_item;
	}
}

void DoublyLinkedList::remove(const size_t& number)
{
	Element* next, *prev, *item = begin_;
	for (size_t i = 0; i < number; i++)
		item = item->get_next();
	next = item->get_next();
	prev = item->get_prev();
	next->set_prev(prev);
	prev->set_next(next);
	delete item;
}

std::string & DoublyLinkedList::operator[](const size_t& number)
{
	Element* item = begin_;
	for (size_t i = 0; i < number; i++)
		item = item->get_next();
	return item->get_data();
}
