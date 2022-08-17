#pragma once

class Difference
{
public:
	void setDiff(Order& newSell, Order& newBuy);
	void findDiff(double newtax);
	Difference(Order newSell, Order newBuy);
	friend std::ostream& operator<<(std::ostream& os, Difference& dt);
	friend bool operator<(Difference const& obj, Difference const& obj2);
	Order sell;
	Order buy;
	double tax = 0;
	double diff;
	double totaldiff;
	double totalvolume;
	int quantity;
	int jumps_amount;
	double diff_per_jump;
};

void Difference::setDiff(Order& newSell, Order& newBuy)
{
	sell = newSell;
	buy = newBuy;
	diff = buy.price * ( 1 - tax ) - sell.price;
}

void Difference::findDiff(double newtax)
{
	this->tax = newtax;
	this->diff = this->buy.price * (1 - tax) - this->sell.price;
	if (this->buy.volume_remain < this->sell.volume_remain)
	{
		quantity = this->buy.volume_remain;
	}
	else
	{
		quantity = this->sell.volume_remain;
	}
	this->totaldiff = this->diff * quantity;
	this->totalvolume = this->buy.volume * quantity;
}

Difference::Difference(Order newSell, Order newBuy)
{
	sell = newSell;
	buy = newBuy;
	diff = buy.price * (1 - tax) - sell.price;
}

std::ostream& operator<<(std::ostream& os, Difference& dt)
{
	os << "PROFIT PER JUMP = " << std::setprecision(10000000) << dt.diff_per_jump << '\n';
	os << "PROFIT = " << std::setprecision(10000000) << dt.totaldiff << '\n';
	os << "amount to buy : " << dt.quantity << std::endl;
	os << "buy order location: " << dt.buy.system_name << " sec: " << dt.buy.security_status << std::endl;
	os << "sell order location : " << dt.sell.system_name << " sec: " << dt.sell.security_status << std::endl;
	os << "sell price: " << std::setprecision(10000000) << dt.sell.price << "\nbuy price: " << std::setprecision(10000000) << dt.buy.price << '\n';
	os << "type: " << dt.sell.item_name << '\n';
	os << "total volume: " << dt.totalvolume << '\n';
	os << "sell range: " << dt.sell.range << '\n';
	return os;
}

bool operator<(Difference const& obj1, Difference const& obj2)
{
	if (obj1.diff_per_jump < obj2.diff_per_jump) return true;
	return false;
}