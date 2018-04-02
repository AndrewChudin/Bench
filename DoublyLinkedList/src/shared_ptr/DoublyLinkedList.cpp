#include "stdafx.h"
#include "DoublyLinkedList.hpp"

DoublyLinkedList::DoublyLinkedList()
{
}

DoublyLinkedList::~DoublyLinkedList()
{
}

void DoublyLinkedList::add(const std::string& data)
{
	std::shared_ptr<Element> new_item(new Element(data));
	if (end_)
	{
		end_.get()->set_next(new_item);
		new_item.get()->set_prev(end_);
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
	std::shared_ptr<Element> next, prev, item = begin_;
	for (size_t i = 0; i < number; i++)
		item = item.get()->get_next();
	next = item.get()->get_next();
	prev = item.get()->get_prev();
	next.get()->set_prev(prev);
	prev.get()->set_next(next);
}

std::string & DoublyLinkedList::operator[](const size_t& number)
{
	std::shared_ptr<Element> item = begin_;
	for (size_t i = 0; i < number; i++)
		item = item.get()->get_next();
	return item.get()->get_data();
}
