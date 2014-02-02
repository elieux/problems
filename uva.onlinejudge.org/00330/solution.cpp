#include <iostream>
#include <iomanip>
#include <algorithm>
#include <map>

typedef unsigned int uint;

struct Item {
	double cost;
	double price;
	uint quantity;
	
	double value() const {
		return quantity * cost;
	}
};

typedef std::map<std::string, Item> Inventory;

int main() {
	Inventory inventory;
	double profit = 0.0;
	
	std::string
		action_end   ("*"),
		action_report("report"),
		action_delete("delete"),
		action_new   ("new"),
		action_buy   ("buy"),
		action_sell  ("sell");
	
	while (true)
	{
		std::string action;
		std::cin >> action;
		if (action == action_end)
			break;
		
		if (action == action_report)
		{
			std::cout << "                  INVENTORY REPORT"                          << std::endl;
			std::cout << "Item Name     Buy At      Sell At      On Hand        Value" << std::endl;
			std::cout << "---------     ------      -------      -------        -----" << std::endl;
			
			double total = 0.0;
			for (Inventory::iterator it = inventory.begin(); it != inventory.end(); it++)
			{
				const std::string& item_name = (*it).first;
				const Item& item = (*it).second;
				total += item.value();
				
				std::cout << std::left  << std::setw(10)                                       << item_name;
				std::cout << std::right << std::setw(10) << std::setprecision(2) << std::fixed << item.cost;
				std::cout << std::right << std::setw(13) << std::setprecision(2) << std::fixed << item.price;
				std::cout << std::right << std::setw(13)                                       << item.quantity;
				std::cout << std::right << std::setw(13) << std::setprecision(2) << std::fixed << item.value();
				std::cout << std::endl;
			}
			
			std::cout << "------------------------"                                                                                << std::endl;
			std::cout << "Total value of inventory" << std::right << std::setw(35) << std::setprecision(2) << std::fixed << total  << std::endl;
			std::cout << "Profit since last report" << std::right << std::setw(35) << std::setprecision(2) << std::fixed << profit << std::endl;
			
			std::cout << std::endl;
			profit = 0.0;
			continue;
		}
		
		std::string item_name;
		std::cin >> item_name;
		
		if (action == action_new)
		{
			Item item = Item();
			std::cin >> item.cost >> item.price;
			inventory[item_name] = item;
			continue;
		}
		
		Item& item = inventory[item_name];
		
		if (action == action_delete)
		{
			profit -= item.value();
			inventory.erase(inventory.find(item_name));
			continue;
		}
		
		uint quantity;
		std::cin >> quantity;
		
		if (action == action_buy)
		{
			item.quantity += quantity;
		}
		else if (action == action_sell)
		{
			profit += quantity * (item.price - item.cost);
			item.quantity -= quantity;
		}
	}
	
	return 0;
}
