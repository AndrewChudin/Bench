#pragma once
class Element
{
public:
	Element();
	Element(const std::string& data);
	~Element();
	void set_next(const std::shared_ptr<Element>& item);
	void set_prev(const std::shared_ptr<Element>& item);
	std::shared_ptr<Element>& get_prev();
	std::shared_ptr<Element>& get_next();
	std::string& get_data();
private:
	std::string data_;
	std::shared_ptr<Element> next_ = nullptr, prev_ = nullptr;
};

