#include <iostream>
#include <string>
#include "sqlite3.h"
#include <nlohmann/json.hpp>
#include <json/json.h>
#include <json/value.h>
#include <cpr/cpr.h>
#include "System.h"
#include "Item.h"
#include "Order.h"
#include "Difference.h"
#include "Funcs.h"
#include "Data.h"
#include "DB_Manager.h"
#include "Downloader.h"
#include "Timer.h"
#include "DataProcesser.h"
#include "Interface.h"

int main() {
	Interface::menu();
	return 0;
}