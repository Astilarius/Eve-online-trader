#pragma once

class Interface
{
public:
	static void menu();
};

void Interface::menu()
{
	std::cout << "Greetings, trader!" << std::endl;
	int budget;
	std::cout << "What is your budget?" << std::endl;
	std::cin >> budget;
	int volume;
	std::cout << "What volume can you carry?" << std::endl;
	std::cin >> volume;
	double tax;
	std::cout << "What is your sales tax? (in percents)" << std::endl;
	std::cin >> tax;
	bool safe;
	std::cout << "Do you only want to trade in highsec?" << std::endl;
	std::cin >> safe;
	tax /= 100;
	char choice;
	char choice2;
	int system = 0;
	Buy_Type_Value myMap;
	Timer timer;
	/*
	do
	{
		std::cout << "Do you wish to scan specific system or all empire regions? input:" << std::endl;
		std::cout << "input 1, to choose specific system" << std::endl;
		std::cout << "input 2, to choose all regions" << std::endl;
		std::cin >> choice;
		std::system("cls");
		switch (choice)
		{
		case '1':
		{
			do
			{
				std::cout << "Choose system:" << std::endl;
				std::cout << "input 1, to choose Jita" << std::endl;
				std::cin >> choice2;
				switch (choice2)
				{
				case '1':
				{
					std::cout << "downloading The Forge data" << std::endl;
					system = 30000142;
					timer.addCurrentTime();
					myMap = Downloader::downloadOrderData({ 10000002,"The Forge" });
					break;
				}
				default: {std::cout << "Incorrect input" << std::endl; }
				}
			} while (choice2 != '1');
			break;
		}
		case '2':
		{
			std::cout << "downloading data" << std::endl;
			timer.addCurrentTime();
	        myMap = Downloader::downloadOrderData();
			break;
		}
		default:
		{
			std::cout << "Incorrect input" << std::endl;
		}
		}
	} while ( (choice != '1') & (choice != '2') );
	//*/
	std::system("cls");
	timer.addCurrentTime();
	myMap = Downloader::downloadOrderData();

	std::system("cls");
	timer.addCurrentTime();
	std::cout << "Downloading from server time - " << timer.lastTwoTimes() << std::endl;
	std::cout << "Downloading from server complete" << std::endl;

	DataProcesser dp(system, budget, volume, tax, safe);
	auto outp = dp.process(myMap);
	timer.addCurrentTime();
	std::cout << "Finding profit complete" << std::endl;
	std::cout << std::endl << "Finding profit time - " << timer.lastTwoTimes() << std::endl;

	std::sort(outp.begin(), outp.end());
	std::reverse(outp.begin(), outp.end());

	timer.addCurrentTime();
	std::cout << "Sorting profit complete" << std::endl;
	std::cout << std::endl << "Sorting profit time - " << timer.lastTwoTimes() << std::endl;
	std::cout << std::endl << "Total time - " << timer.fullTime() << std::endl;

	std::cout << "Amount of deals: " << outp.size() << std::endl << std::endl;

	std::cout << "budget: " << budget << std::endl;
	std::cout << "max volume: " << volume << std::endl;
	std::cout << "highsec only: " << safe << std::endl << std::endl;

	for (auto it = outp.begin(); it != outp.end(); it++)
	{
		std::cout << (*it) << std::endl;
		std::system("pause");
	}
	std::system("pause");
}