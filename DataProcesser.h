#pragma once

typedef std::map<std::string, std::map<int, std::vector<Order>>>  Buy_Type_Value;
class DataProcesser
{
public:
	DataProcesser(int newsystem_id, int newbudget, int newvolume, double newtax, bool highsec_only);
	typedef std::map<std::string, std::map<int, std::vector<Order>>>  Buy_Type_Value;
	std::vector<Difference> process(Buy_Type_Value input);
	int system_id;
	int budget;
	int volume;
	double tax;
	bool highsec_only;
	std::vector<Difference> result;
};

DataProcesser::DataProcesser(int newsystem_id, int newbudget, int newvolume, double newtax, bool new_highsec_only)
{
	this->system_id = newsystem_id;
	this->budget = newbudget;
	this->volume = newvolume;
	this->tax = newtax;
	this->highsec_only = new_highsec_only;
}

std::vector<Difference> DataProcesser::process(Buy_Type_Value input)
{
	std::map<int, Difference> diffM;

	Order biggest;
	Order lowest;
	Difference diff(lowest, biggest);
	//input.at("true").at();
	for (auto it = input.at("true").begin(); it != input.at("true").end(); it++)
	{
		biggest = Order::findMaxBuy( (*it).second );
		diff.buy = biggest;
		diffM.insert(std::map<int, Difference>::value_type(biggest.type_id, diff));
		//diffV.push_back(diff);
	}
	for (auto it = diffM.begin(); it != diffM.end(); it++)
	{
		if (input.at("false").contains((*it).second.buy.type_id))
		{
			lowest = Order::findMinSell(input.at("false").at((*it).second.buy.type_id));
			diffM.at((*it).second.buy.type_id).sell = lowest;
			//diffV.at((*it).buy.type_id).sell = lowest;
		}
	}
	auto tempIt = diffM.begin();
	for (auto it = diffM.begin(); it != diffM.end(); )
	{
		(*it).second.findDiff(this->tax);
		if ((*it).second.sell.type_id == 0)
		{
			tempIt = it;
			it++;
			diffM.erase(tempIt);
			continue;
		}
		//*
		if (this->system_id != 0)
		{
			if (((*it).second.sell.system_id != this->system_id) | ((*it).second.buy.system_id != this->system_id))
			{
				tempIt = it;
				it++;
				diffM.erase(tempIt);
				continue;
			}
		}
		//*/
		if ((*it).second.sell.price > this->budget)
		{
			tempIt = it;
			it++;
			diffM.erase(tempIt);
			continue;
		}
		if ((*it).second.diff <= 0)
		{
			tempIt = it;
			it++;
			diffM.erase(tempIt);
			continue;
		}
		if (((*it).second.buy.security_status < 0.5) && (this->highsec_only == true))
		{
			tempIt = it;
			it++;
			diffM.erase(tempIt);
			continue;
		}
		if ( ((*it).second.sell.security_status < 0.5) && (this->highsec_only == true) )
		{
			tempIt = it;
			it++;
			diffM.erase(tempIt);
			continue;
		}
		if ( (*it).second.buy.volume > this->volume )
		{
			tempIt = it;
			it++;
			diffM.erase(tempIt);
			continue;
		}
		if ( (*it).second.totalvolume > this->volume )
		{
			(*it).second.quantity = floor(this->volume / (*it).second.buy.volume);
			(*it).second.totaldiff = (*it).second.diff * (*it).second.quantity;
			(*it).second.totalvolume = (*it).second.buy.volume * (*it).second.quantity;
		}
		it++;
	}

	std::vector<Difference> out;
	for (auto it = diffM.begin(); it != diffM.end(); it++)
	{
		out.push_back((*it).second);
	}
	for (auto it = out.begin(); it != out.end(); it++)
	{
		Downloader::getroute( (*it) );
	}
	return out;
}