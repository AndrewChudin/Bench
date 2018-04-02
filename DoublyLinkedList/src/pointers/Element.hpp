#pragma once
class Element
{
public:
	Element();
	Element(const std::string& data);
	~Element();
	void set_next(Element* item);
	void set_prev(Element* item);
	Element* get_prev();
	Element* get_next();
	std::string& get_data();
private:
	std::string data_;
	Element* next_ = nullptr, *prev_ = nullptr;
};

