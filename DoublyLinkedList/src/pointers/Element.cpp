#include "stdafx.h"
#include "Element.hpp"

Element::Element()
{
}

Element::Element(const std::string& data)
{
	data_ = data;
}

Element::~Element()
{
}

void Element::set_next(Element* item){
	next_ = item;
}

void Element::set_prev(Element* item)
{
	prev_ = item;
}

Element* Element::get_prev()
{
	return prev_;
}


Element* Element::get_next()
{
	return next_;
}

std::string& Element::get_data()
{
	return data_;
}
