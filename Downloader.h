#pragma once

typedef std::map<int, std::vector<Order>> Type_Value;
typedef std::map<std::string, std::map<int, std::vector<Order>>>  Buy_Type_Value;

class Downloader
{
public:
	typedef std::map<std::string, std::map<int, std::vector<Order>>>  Buy_Type_Value;
	static Buy_Type_Value downloadOrderData(std::pair<int, std::string> region_id);
	static Buy_Type_Value downloadOrderData();
	static Item downloadItemData(int id);
	static System downloadSystemData(int id);
	static void getroute(Difference& inp, bool safe);
};

Buy_Type_Value Downloader::downloadOrderData(std::pair<int, std::string> region)
{
	std::vector<Order> tempV;
	Type_Value SellMap;
	Type_Value BuyMap;

	int count = 1;
	Item tempit;
	System tempsys;
	Order c;
	auto r = cpr::Get(cpr::Url{ "https://esi.evetech.net/latest/markets/10000002/orders" },
		cpr::Parameters{ {"datasource","tranquility"}, {"order_type","all"}, {"page", std::to_string(count)} });
	double server_time = 0;
	int pages = stoi(r.header["X-Pages"]);
	Json::Value json;
	Json::Reader reader;
	std::string for_url = "https://esi.evetech.net/latest/markets/";
	std::string url;
	auto systemMap = DB_Manager::getSystems();
	auto itemMap = DB_Manager::getItems();
	int type_id = 0;
	int system_id = 0;

	url = for_url + std::to_string(region.first) + "/orders";
	count = 1;
	do
	{
		r = cpr::Get(cpr::Url{ url },
			cpr::Parameters{ {"datasource","tranquility"}, {"order_type","all"}, {"page", std::to_string(count)} });
		if (r.status_code != 200)
		{
			std::cout << "Error with download" << std::endl;
			std::cout << r.text << std::endl;
			system("pause");
		}
		pages = stoi(r.header["X-Pages"]);
		server_time += r.elapsed;
		reader.parse(r.text, json);
		for (int i = 0; i < 1000; i++)
		{
			c.duration = json[i]["duration"].asInt();
			c.is_buy_order = json[i]["is_buy_order"].asString();
			c.issued = json[i]["issued"].asString();
			c.system_id = json[i]["location_id"].asInt64();
			c.min_volume = json[i]["min_volume"].asInt();
			c.order_id = json[i]["order_id"].asInt64();
			c.price = json[i]["price"].asDouble();
			c.range = json[i]["range"].asString();
			system_id = json[i]["system_id"].asInt64();
			type_id = json[i]["type_id"].asInt64();
			c.volume_remain = json[i]["volume_remain"].asInt();
			c.volume_total = json[i]["volume_total"].asInt();

			if (itemMap.contains(type_id))
			{
				tempit = itemMap.at(type_id);
				c.type_id = tempit.type_id;
				c.market_group_id = tempit.type_id;
				c.item_name = tempit.item_name;
				c.volume = tempit.volume;
				c.group_id = tempit.group_id;
			}
			else
			{
				continue;
				tempit = Downloader::downloadItemData(type_id);
				c.type_id = tempit.type_id;
				c.market_group_id = tempit.type_id;
				c.item_name = tempit.item_name;
				c.volume = tempit.volume;
				c.group_id = tempit.group_id;
				itemMap = DB_Manager::getItems();
			}

			if (systemMap.contains(system_id))
			{
				tempsys = systemMap.at(system_id);
				c.system_id = tempsys.system_id;
				c.system_name = tempsys.system_name;
				c.security_status = tempsys.security_status;
			}
			else
			{
				continue;
				tempsys = Downloader::downloadSystemData(system_id);
				c.system_id = tempsys.system_id;
				c.system_name = tempsys.system_name;
				c.security_status = tempsys.security_status;
				systemMap = DB_Manager::getSystems();
			}

			if (c.is_buy_order == "true")
			{
				if (BuyMap.contains(type_id))
				{
					BuyMap.at(type_id).push_back(c);
				}
				tempV.clear();
				tempV.push_back(c);
				BuyMap.insert(Type_Value::value_type(type_id, tempV));
			}
			else if (c.is_buy_order == "false")
			{
				if (SellMap.contains(type_id))
				{
					SellMap.at(type_id).push_back(c);
				}
				tempV.clear();
				tempV.push_back(c);
				SellMap.insert(Type_Value::value_type(type_id, tempV));
			}
		}
		count++;
	} while (count <= pages);
	std::cout << "region " << region.second << " done" << std::endl;


	Buy_Type_Value map2;
	map2.insert(Buy_Type_Value::value_type("false", SellMap));
	map2.insert(Buy_Type_Value::value_type("true", BuyMap));

	std::cout << "Server response time - " << server_time << std::endl;

	return map2;
}

Buy_Type_Value Downloader::downloadOrderData()
{
	std::map<int, std::string> regions =
	{
	  {10000002,"The Forge"},
	  {10000068,"Verge Vendor"},
	  {10000042,"Metropolis"},
	  {10000030,"Heimatar"},
	  {10000065,"Kor-Azor"},
	  {10000016,"Lonetrek"},
	  {10000048,"Placid"},
	  {10000069,"Black Rise"},
	  {10000033,"The Citadel"},
	  {10000037,"Everyshore"},
	  {10000032,"Sinq Laison"},
	  {10000044,"Solitude"},
	  {10000028,"Molden Heath"},
	  {10000038,"The Bleak Lands"},
	  {10000054,"Aridia"},
	  {10000052,"Kador"},
	  {10000043,"Domain"},
	  {10000036,"Devoid"},
	  {10000049,"Khanid"},
	  {10000020,"Tash-Murkon"},
	  {10000001,"Derelik"}
	};

	std::vector<Order> tempV;
	Type_Value SellMap;
	Type_Value BuyMap;

	int count = 1;
	Item tempit;
	System tempsys;
	Order c;
	auto r = cpr::Get(cpr::Url{ "https://esi.evetech.net/latest/markets/10000002/orders" },
		cpr::Parameters{ {"datasource","tranquility"}, {"order_type","all"}, {"page", std::to_string(count)} });
	double server_time = 0;
	int pages = stoi(r.header["X-Pages"]);
	Json::Value json;
	Json::Reader reader;
	std::string for_url = "https://esi.evetech.net/latest/markets/";
	std::string url;
	systemMap systemMap = DB_Manager::getSystems();
	int system_id = 0;
	itemMap itemMap = DB_Manager::getItems();
	int type_id = 0;
	int returnsize;

	for (auto it = regions.begin(); it != regions.end(); it++)
	{
		url = for_url + std::to_string((*it).first) + "/orders";
		count = 1;
		do
		{
			r = cpr::Get(cpr::Url{ url },
				cpr::Parameters{ {"datasource","tranquility"}, {"order_type","all"}, {"page", std::to_string(count)} });
			if (r.status_code != 200)
			{
				std::cout << "Error with download" << std::endl;
				std::cout << r.text << std::endl;
				system("pause");
			}
			pages = stoi(r.header["X-Pages"]);
			server_time += r.elapsed;
			reader.parse(r.text, json);
			returnsize = json.size();
			for (int i = 0; i < returnsize; i++)
			{

				c.duration = json[i]["duration"].asInt();
				c.is_buy_order = json[i]["is_buy_order"].asString();
				c.issued = json[i]["issued"].asString();
				c.system_id = json[i]["location_id"].asInt64();
				c.min_volume = json[i]["min_volume"].asInt();
				c.order_id = json[i]["order_id"].asInt64();
				c.price = json[i]["price"].asDouble();
				c.range = json[i]["range"].asString();
				system_id = json[i]["system_id"].asInt64();
				type_id = json[i]["type_id"].asInt64();
				c.volume_remain = json[i]["volume_remain"].asInt();
				c.volume_total = json[i]["volume_total"].asInt();

				if (itemMap.contains(type_id))
				{
					tempit = itemMap.at(type_id);
					c.type_id = tempit.type_id;
					c.market_group_id = tempit.type_id;
					c.item_name = tempit.item_name;
					c.volume = tempit.volume;
					c.group_id = tempit.group_id;
				}
				else
				{
					continue;
					tempit = Downloader::downloadItemData(type_id);
					c.type_id = tempit.type_id;
					c.market_group_id = tempit.type_id;
					c.item_name = tempit.item_name;
					c.volume = tempit.volume;
					c.group_id = tempit.group_id;
					itemMap = DB_Manager::getItems();
				}

				if (systemMap.contains(system_id))
				{
					tempsys = systemMap.at(system_id);
					c.system_id = tempsys.system_id;
					c.system_name = tempsys.system_name;
					c.security_status = tempsys.security_status;
				}
				else
				{
					continue;
					tempsys = Downloader::downloadSystemData(system_id);
					c.system_id = tempsys.system_id;
					c.system_name = tempsys.system_name;
					c.security_status = tempsys.security_status;
					systemMap = DB_Manager::getSystems();
				}

				if (c.is_buy_order == "true")
				{
					if (BuyMap.contains(type_id))
					{
						BuyMap.at(type_id).push_back(c);
					}
					tempV.clear();
					tempV.push_back(c);
					BuyMap.insert(Type_Value::value_type(type_id, tempV));
				}
				else if (c.is_buy_order == "false")
				{
					if (SellMap.contains(type_id))
					{
						SellMap.at(type_id).push_back(c);
					}
					tempV.clear();
					tempV.push_back(c);
					SellMap.insert(Type_Value::value_type(type_id, tempV));
				}
			}
			count++;
		} while (count <= pages);
		std::cout << "region " << (*it).second << " done" << std::endl;
	}

	Buy_Type_Value map2;
	map2.insert(Buy_Type_Value::value_type("false", SellMap));
	map2.insert(Buy_Type_Value::value_type("true", BuyMap));

	std::cout << "Server response time - " << server_time << std::endl;

	return map2;
}

Item Downloader::downloadItemData(int id)
{
	std::string url = "https://esi.evetech.net/latest/universe/types/" + std::to_string(id) + "/";
	auto r = cpr::Get(cpr::Url{url },
		cpr::Parameters{ {"datasource","tranquility"}, {"language","en"} });
	Json::Value json;
	Json::Reader reader;

	if (r.status_code != 200)
	{
		std::cout << "Error with download" << std::endl;
		std::cout << r.text << std::endl;
		system("pause");
	}

	reader.parse(r.text, json);

	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	std::string sql = "INSERT OR IGNORE INTO ITEMS VALUES (" +
		std::to_string(json["type_id"].asInt64()) + ", " +
		std::to_string(json["market_group_id"].asInt64()) + ", " +
		"'" + json["name"].asString() + "'" + ", " +
		std::to_string(json["packaged_volume"].asFloat()) + ", " +
		std::to_string(json["group_id"].asInt64()) + ")";

	rc = sqlite3_open("database.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}

	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);

	Item res;
	res.type_id = json["type_id"].asInt64();
	res.market_group_id = json["market_group_id"].asInt64();
	res.item_name = json["name"].asString();
	res.volume = json["volume"].asFloat();
	res.group_id = json["group_id"].asInt64();
	return res;
}

System Downloader::downloadSystemData(int id)
{
	std::string url = "https://esi.evetech.net/latest/universe/systems/" + std::to_string(id) + "/";
	auto r = cpr::Get(cpr::Url{ url },
		cpr::Parameters{ {"datasource","tranquility"}, {"language","en"} });
	Json::Value json;
	Json::Reader reader;

	if (r.status_code != 200)
	{
		std::cout << "Error with download" << std::endl;
		std::cout << r.text << std::endl;
		system("pause");
	}

	reader.parse(r.text, json);

	sqlite3* db;
	char* zErrMsg = 0;
	int rc;
	std::string sql = "INSERT OR IGNORE INTO SYSTEMS VALUES (" +
		std::to_string(json["system_id"].asInt64()) + ", " +
		"'" + json["name"].asString() + "'" + ", " +
		std::to_string(json["security_status"].asFloat()) + ")";

	rc = sqlite3_open("database.db", &db);

	if (rc) {
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	}

	rc = sqlite3_exec(db, sql.c_str(), NULL, 0, &zErrMsg);

	if (rc != SQLITE_OK) {
		fprintf(stderr, "SQL error: %s\n", zErrMsg);
		sqlite3_free(zErrMsg);
	}

	sqlite3_close(db);

	System res;
	res.system_id = json["system_id"].asInt64();
	res.system_name = json["name"].asString();
	res.security_status = json["security_status"].asFloat();
	return res;
}

void Downloader::getroute(Difference& inp, bool safe)
{
	std::string flag;
	if (safe) flag = "secure";
	else flag = "shortest";
	std::string url = "https://esi.evetech.net/latest/route/" + std::to_string(inp.sell.system_id) + "/" + std::to_string(inp.buy.system_id) + "/";
	auto r = cpr::Get(cpr::Url{ url },
		cpr::Parameters{ {"datasource","tranquility"}, {"flag", flag}});
	Json::Value json;
	Json::Reader reader;

	if (r.status_code != 200)
	{
		std::cout << "Error with download" << std::endl;
		std::cout << r.text << std::endl;
		system("pause");
	}

	reader.parse(r.text, json);

	inp.jumps_amount = json.size();
	inp.diff_per_jump = inp.totaldiff / inp.jumps_amount;
}