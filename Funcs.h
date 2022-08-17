#pragma once

bool sqlExecute(sqlite3* db, const char* query)
{
	char* err;
	int rc = sqlite3_exec(db, query, NULL, NULL, &err);
	if (rc != SQLITE_OK)
	{
		std::cout << "error: " << err;
		return false;
	}
	return true;
}

void fromLineToComm(std::string input)
{
	int count = 0;
	std::string str = "";
	std::vector<std::string> q;
	int size = input.size();
	for (int j = 2; count < 4; j++)
	{
		if (!(input[j - 2] == 39 && input[j - 1] == '=')) continue;
		while (input[j] != ',' || input[j] != '}')
		{
			str = str + input[j];
		}
		break;
	}
	std::cout << str << std::endl;
}

std::vector<Difference> convertToVect(std::map<int, Difference>& in)
{
	std::vector<Difference> out;
	for (auto it = in.begin(); it != in.end(); it++)
	{
		out.push_back( (*it).second );
	}
	return out;
}