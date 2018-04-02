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

void Element::set_next(const std::shared_ptr<Element>& item){
	next_ = item;
}

void Element::set_prev(const std::shared_ptr<Element>& item)
{
	prev_ = item;
}

std::shared_ptr<Element>& Element::get_prev()
{
	return prev_;
}


std::shared_ptr<Element>& Element::get_next()
{
	return next_;
}

std::string& Element::get_data()
{
	return data_;
}
