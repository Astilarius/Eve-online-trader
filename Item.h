#pragma once

class Item
{
public:
	~Item();
	Item();
	Item(const Item& other);
	Item(Item&& other);
	Item& operator=(const Item& other);
	Item& operator=(Item&& other);
	friend std::ostream& operator<<(std::ostream& os, Item& dt);

	int type_id;
	int market_group_id;
	std::string item_name;
	double volume;
	int group_id;
};

Item::~Item()
{
	this->type_id = 0;
	this->market_group_id = 0;
	this->item_name = "";
	this->volume = 0;
	this->group_id = 0;
}

Item::Item()
{
	this->type_id = 0;
	this->market_group_id = 0;
	this->item_name = "";
	this->volume = 0;
	this->group_id = 0;
}

Item::Item(const Item& other)
{
	this->type_id = other.type_id;
	this->market_group_id = other.market_group_id;
	this->item_name = other.item_name;
	this->volume = other.volume;
	this->group_id = other.group_id;
}

Item::Item(Item&& other)
{
	this->type_id = other.type_id;
	this->market_group_id = other.market_group_id;
	this->item_name = other.item_name;
	this->volume = other.volume;
	this->group_id = other.group_id;

	other.type_id = 0;
	other.market_group_id = 0;
	other.item_name = "";
	other.volume = 0;
	other.group_id = 0;
}

Item& Item::operator=(const Item& other)
{
	this->type_id = other.type_id;
	this->market_group_id = other.market_group_id;
	this->item_name = other.item_name;
	this->volume = other.volume;
	this->group_id = other.group_id;
	return *this;
}

Item& Item::operator=(Item&& other)
{
	if (this != &other)
	{
		this->type_id = 0;
		this->market_group_id = 0;
		this->item_name = "";
		this->volume = 0;
		this->group_id = 0;

		this->type_id = other.type_id;
		this->market_group_id = other.market_group_id;
		this->item_name = other.item_name;
		this->volume = other.volume;
		this->group_id = other.group_id;

		other.type_id = 0;
		other.market_group_id = 0;
		other.item_name = "";
		other.volume = 0;
		other.group_id = 0;
	}
	return *this;
}

std::ostream& operator<<(std::ostream& os, Item& dt)
{
	os << "type_id: " << dt.type_id << '\n';
	os << "market_group_id: " << dt.market_group_id << '\n';
	os << "item_name: " << dt.item_name << '\n';
	os << "volume: " << dt.volume << '\n';
	os << "group_id: " << dt.group_id << '\n';
	return os;
}