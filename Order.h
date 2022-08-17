#pragma once

class Order : public Item, public System
{
public:
	Order();
	Order(const Order& other);
	Order(Order&& other);
	void clear();
	friend std::ostream& operator<<(std::ostream& os, Order& dt);
	friend bool operator<(Order const& obj, Order const& obj2);
	Order& operator=(const Order& other);
	Order& operator=(Order&& other);
	static Order findMaxBuy(std::vector<Order> v);
	static Order findMinSell(std::vector<Order> v);
	//bool writeInSQLite(sqlite3* db);
	int duration;
	std::string is_buy_order;
	std::string issued;
	int min_volume;
	int order_id;
	double price;
	std::string range;
	int volume_remain;
	int volume_total;
};

Order::Order() : Item(), System()
{
	duration = NULL;
	is_buy_order = "";
	issued = "";
	min_volume = NULL;
	order_id = NULL;
	price = NULL;
	range = "";
	volume_remain = NULL;
	volume_total = NULL;
}

Order::Order(const Order& other) : Item(other), System(other)
{
	duration = other.duration;
	is_buy_order = other.is_buy_order;
	issued = other.issued;
	min_volume = other.min_volume;
	order_id = other.order_id;
	price = other.price;
	range = other.range;
	volume_remain = other.volume_remain;
	volume_total = other.volume_total;
}

Order::Order(Order&& other) : Item(other), System(other)
{
	duration = other.duration;
	is_buy_order = other.is_buy_order;
	issued = other.issued;
	min_volume = other.min_volume;
	order_id = other.order_id;
	price = other.price;
	range = other.range;
	volume_remain = other.volume_remain;
	volume_total = other.volume_total;

	other.duration = 0;
	other.is_buy_order = "";
	other.issued = "";
	other.min_volume = 0;
	other.order_id = 0;
	other.price = 0;
	other.range = "";
	other.volume_remain = 0;
	other.volume_total = 0;
}

void Order::clear()
{
	this->duration = 0;
	this->issued = "";
	this->is_buy_order = "";
	this->min_volume = 0;
	this->order_id = 0;
	this->price = 0;
	this->range = "";
	this->volume_remain = 0;
	this->volume_total = 0;
}

Order Order::findMaxBuy(std::vector<Order> v)
{
	Order biggest = v.front();
	for (auto it = v.begin(); it != v.end(); it++)
	{
		if ((*it).is_buy_order == "true")
		{
			biggest = *it;
			break;
		}
	}
	for (auto it = v.begin(); it != v.end(); it++)
	{
		if ( ( (*it).price > biggest.price ) & ( (*it).is_buy_order == "true" ) )
		{
			biggest = *it;
		}
	}
	return biggest;
}

Order Order::findMinSell(std::vector<Order> v)
{
	Order lowest = v.front();
	for (auto it = v.begin(); it != v.end(); it++)
	{
		if ((*it).is_buy_order == "false")
		{
			lowest = *it;
			break;
		}
	}
	for (auto it = v.begin(); it != v.end(); it++)
	{
		if ( ( (*it).price < lowest.price ) & ( (*it).is_buy_order == "false" ) )
		{
			lowest = *it;
		}
	}
	return lowest;
}

std::ostream& operator<<(std::ostream& os, Order& dt)
{
	os << "duration: " << dt.duration << '\n';
	os << "is_buy_order: " << dt.is_buy_order << '\n';
	os << "issued: " << dt.issued << '\n';
	os << "location_id: " << dt.system_id << '\n';
	os << "min_volume: " << dt.min_volume << '\n';
	os << "order_id: " << dt.order_id << '\n';
	os << "price: " << std::setprecision(1000000) << dt.price << '\n';
	os << "range: " << dt.range << '\n';
	os << "volume_remain: " << dt.volume_remain << '\n';
	os << "volume_total: " << dt.volume_total << '\n';
	return os;
}

bool operator<(Order const& obj, Order const& obj2)
{
	if (obj.price < obj2.price) return true;
	return false;
}

Order& Order::operator=(const Order& obj)
{
	this->duration = obj.duration;
	this->issued = obj.issued;
	this->is_buy_order = obj.is_buy_order;
	this->min_volume = obj.min_volume;
	this->order_id = obj.order_id;
	this->price = obj.price;
	this->range = obj.range;
	this->volume_remain = obj.volume_remain;
	this->volume_total = obj.volume_total;
	this->type_id = obj.type_id;
	this->market_group_id = obj.market_group_id;
	this->item_name = obj.item_name;
	this->volume = obj.volume;
	this->group_id = obj.group_id;
	this->system_id = obj.system_id;
	this->system_name = obj.system_name;
	this->security_status = obj.security_status;
	return *this;
}

Order& Order::operator=(Order&& obj)
{
	if (this != &obj)
	{
		this->duration = 0;
		this->issued = "";
		this->is_buy_order = "";
		this->min_volume = 0;
		this->order_id = 0;
		this->price = 0;
		this->range = "";
		this->volume_remain = 0;
		this->volume_total = 0;
		this->type_id = 0;
		this->market_group_id = 0;
		this->item_name = "";
		this->volume = 0;
		this->group_id = 0;
		this->system_id = 0;
		this->system_name = "";
		this->security_status = 0;

		this->duration = obj.duration;
		this->issued = obj.issued;
		this->is_buy_order = obj.is_buy_order;
		this->min_volume = obj.min_volume;
		this->order_id = obj.order_id;
		this->price = obj.price;
		this->range = obj.range;
		this->volume_remain = obj.volume_remain;
		this->volume_total = obj.volume_total;
		this->type_id = obj.type_id;
		this->market_group_id = obj.market_group_id;
		this->item_name = obj.item_name;
		this->volume = obj.volume;
		this->group_id = obj.group_id;
		this->system_id = obj.system_id;
		this->system_name = obj.system_name;
		this->security_status = obj.security_status;

		obj.duration = 0;
		obj.issued = "";
		obj.is_buy_order = "";
		obj.min_volume = 0;
		obj.order_id = 0;
		obj.price = 0;
		obj.range = "";
		obj.volume_remain = 0;
		obj.volume_total = 0;
		obj.type_id = 0;
		obj.market_group_id = 0;
		obj.item_name = "";
		obj.volume = 0;
		obj.group_id = 0;
		obj.system_id = 0;
		obj.system_name = "";
		obj.security_status = 0;
	}
	return *this;
}