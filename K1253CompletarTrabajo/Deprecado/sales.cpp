/***************
***	INCLUDES ***
****************/

#include <iostream>
#include <array>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>

/**************
***	DEFINES ***
***************/

#define NUM_MONTHS 12
#define DATA_BIN_FILE "data.bin"

#define TABLE_COL_NAME_SIZE 25
#define TABLE_COL_MONTH_SIZE 12

/*************
***	MACROS ***
**************/

#define GetSalesCountByRegion(data, region) GetSalesCount(data, region, -1, -1)
#define GetSalesCountBySeller(data, seller) GetSalesCount(data, -1, seller, -1)
#define GetSalesCountByMonth(data, month) GetSalesCount(data, -1, -1, month)
#define GetSalesCountByRegionSeller(data, region, seller) GetSalesCount(data, region, seller, -1)
#define GetSalesCountByRegionMonth(data, region, month) GetSalesCount(data, region, -1, month)
#define GetSalesCountBySellerMonth(data, seller, month) GetSalesCount(data, -1, seller, month)

#define GetSalesSumAmountByRegion(data, region) GetSalesSumAmount(data, region, -1, -1)
#define GetSalesSumAmountBySeller(data, seller) GetSalesSumAmount(data, -1, seller, -1)
#define GetSalesSumAmountByMonth(data, month) GetSalesSumAmount(data, -1, -1, month)
#define GetSalesSumAmountByRegionSeller(data, region, seller) GetSalesSumAmount(data, region, seller, -1)
#define GetSalesSumAmountByRegionMonth(data, region, month) GetSalesSumAmount(data, region, -1, month)
#define GetSalesSumAmountBySellerMonth(data, seller, month) GetSalesSumAmount(data, -1, seller, month)

/*************
***	USINGS ***
**************/

using namespace std;

using Data =
	vector<				// Regions
		vector<			// Sellers
			array<		// Months
				vector< // Sales
					int>,
				NUM_MONTHS>>>;

/*****************
***	PROTOTYPES ***
******************/

void LoadTxtFile();
bool LoadBinData(Data &);
void SaveBinData(const Data &);
void AddSale(Data &, int, int, int, int);

string GetMonthName(int month);
string GetSellerName(int seller);

int GetSalesCount(const Data &, int = -1, int = -1, int = -1);
int GetSalesSumAmount(const Data &, int = -1, int = -1, int = -1);

vector<int> GetBestSellersByRegion(const Data &, int);
vector<int> GetBestMonthsByRegion(const Data &, int);

void PrintSellersNames(const vector<int>);
void PrintMonths(const vector<int>);
void PrintStatistics(const Data &, int = -1);
void PrintTable(const Data &, int);

/***********
***	MAIN ***
************/

int main(int argc, char **argv)
{
	for (int i{}; i < argc; i++)
		if (strcmp(argv[i], "--loadDataFile") == 0)
			LoadTxtFile();

	Data data{};

	if (!LoadBinData(data))
	{
		cout << "There was an error trying to load " << DATA_BIN_FILE << ". Please load TXT file first.\n";
		return 1;
	}

	cout << "Loaded a total of <" << GetSalesCount(data) << "> sales.\n";

	PrintStatistics(data);

	return 0;
}

/****************
***	FUNCTIONS ***
*****************/

void LoadTxtFile()
{
	cout << "Reading sales information from the input stream.\n";

	Data data;

	for (int region{}, seller{}, month{}, amount{}; cin >> region >> seller >> month >> amount;)
		AddSale(data, region, seller, month, amount);

	SaveBinData(data);
}

bool LoadBinData(Data &data)
{
	unsigned total{};

	ifstream file;
	try
	{
		file.open(DATA_BIN_FILE, ios::in | ios::binary);

		unsigned regions_size{};
		file.read(reinterpret_cast<char *>(&regions_size), sizeof(unsigned));

		data.resize(regions_size);
		for (unsigned region_ix{}; region_ix < regions_size; region_ix++)
		{
			unsigned sellers_size{};
			file.read(reinterpret_cast<char *>(&sellers_size), sizeof(unsigned));
			data.at(region_ix).resize(sellers_size);

			for (unsigned seller_ix{}; seller_ix < sellers_size; seller_ix++)
			{
				unsigned months_size{};
				file.read(reinterpret_cast<char *>(&months_size), sizeof(unsigned));

				for (unsigned month_ix{}; month_ix < months_size; month_ix++)
				{
					unsigned amounts_size{};
					file.read(reinterpret_cast<char *>(&amounts_size), sizeof(unsigned));

					for (unsigned amount_ix{}; amount_ix < amounts_size; amount_ix++)
					{
						int amount{};
						file.read(reinterpret_cast<char *>(&amount), sizeof(int));
						data.at(region_ix).at(seller_ix).at(month_ix).push_back(amount);
						total++;
					}
				}
			}
		}
		file.close();
	}
	catch (int error)
	{
		if (file.is_open())
			file.close();
		return false;
	}

	return total > 0;
}

void SaveBinData(const Data &data)
{
	ofstream file;
	file.open(DATA_BIN_FILE, ios::out | ios::binary);

	unsigned size{}, total{};

	unsigned regions_size = data.size();
	file.write(reinterpret_cast<char *>(&regions_size), sizeof(unsigned));

	size += sizeof(unsigned);

	for (auto region : data)
	{
		size += sizeof(unsigned);
		unsigned sellers_size = region.size();
		file.write(reinterpret_cast<char *>(&sellers_size), sizeof(unsigned));

		for (auto seller : region)
		{
			size += sizeof(unsigned);
			unsigned months_size = seller.size();
			file.write(reinterpret_cast<char *>(&months_size), sizeof(unsigned));

			for (auto month : seller)
			{
				size += sizeof(unsigned);
				unsigned amounts_size = month.size();
				file.write(reinterpret_cast<char *>(&amounts_size), sizeof(unsigned));

				for (auto amount : month)
				{
					size += sizeof(int);
					total++;
					file.write(reinterpret_cast<char *>(&amount), sizeof(int));
				}
			}
		}
	}

	file.close();

	cout << "A total of <" << total << "> sales were added to " << DATA_BIN_FILE << " file using <" << size << "> bytes.\n";
}

void AddSale(Data &data, int region, int seller, int month, int amount)
{
	while ((int)data.size() < region)
		data.push_back({});

	while ((int)data.at(region - 1).size() < seller)
		data.at(region - 1).push_back({});

	data.at(region - 1).at(seller - 1).at(month - 1).push_back(amount);
}

string GetRegionName(int region)
{
	switch (region)
	{
	case 1:
		return "North";
	case 2:
		return "West";
	case 3:
		return "South";
	case 4:
		return "East";
	default:
		return "Not defined";
	}
}

string GetMonthName(int month)
{
	switch (month)
	{
	case 1:
		return "January";
	case 2:
		return "February";
	case 3:
		return "March";
	case 4:
		return "April";
	case 5:
		return "May";
	case 6:
		return "June";
	case 7:
		return "July";
	case 8:
		return "August";
	case 9:
		return "September";
	case 10:
		return "October";
	case 11:
		return "November";
	case 12:
		return "December";
	default:
		return "Not defined";
	}
}

string GetSellerName(int seller)
{
	switch (seller)
	{
	case 1:
		return "Roger Caceres";
	case 2:
		return "German Ceballos";
	case 3:
		return "Jeronimo Fermepin Galdo";
	case 4:
		return "Pilar Fernandez";
	case 5:
		return "Nicolas Filippi Farmar";
	case 6:
		return "Enrique Marques";
	case 7:
		return "Tobias Sailler Quintana";
	case 8:
		return "Curt Venator Rauch";
	default:
		return "Not defined";
	}
}

int GetSalesCount(const Data &data, int region, int seller, int month)
{
	int count{};
	for (int ix_region{region != -1 ? region : 0}; ix_region < ((region != -1) ? region + 1 : (int)data.size()); ix_region++)
		for (int ix_seller{seller != -1 ? seller : 0}; ix_seller < ((seller != -1) ? seller + 1 : (int)data.at(ix_region).size()); ix_seller++)
			for (int ix_month{month != -1 ? month : 0}; ix_month < ((month != -1) ? month + 1 : (int)data.at(ix_region).at(ix_seller).size()); ix_month++)
				count += data.at(ix_region).at(ix_seller).at(ix_month).size();
	return count;
}

int GetSalesSumAmount(const Data &data, int region, int seller, int month)
{
	int sum{};
	for (int ix_region{region != -1 ? region : 0}; ix_region < ((region != -1) ? region + 1 : (int)data.size()); ix_region++)
		for (int ix_seller{seller != -1 ? seller : 0}; ix_seller < ((seller != -1) ? seller + 1 : (int)data.at(ix_region).size()); ix_seller++)
			for (int ix_month{month != -1 ? month : 0}; ix_month < ((month != -1) ? month + 1 : (int)data.at(ix_region).at(ix_seller).size()); ix_month++)
			{
				for (auto amount : data.at(ix_region).at(ix_seller).at(ix_month))
					sum += amount;
			}
	return sum;
}

int GetSalesMaxAmount(const Data &data, int region, int seller, int month)
{
	int max{};
	for (int ix_region{region != -1 ? region : 0}; ix_region < ((region != -1) ? region + 1 : (int)data.size()); ix_region++)
		for (int ix_seller{seller != -1 ? seller : 0}; ix_seller < ((seller != -1) ? seller + 1 : (int)data.at(ix_region).size()); ix_seller++)
			for (int ix_month{month != -1 ? month : 0}; ix_month < ((month != -1) ? month + 1 : (int)data.at(ix_region).at(ix_seller).size()); ix_month++)
				for (auto amount : data.at(ix_region).at(ix_seller).at(ix_month))
					if (amount > max)
						max = amount;
	return max;
}

vector<int> GetBestSellersByRegion(const Data &data, int region)
{
	int maxAmount{};
	vector<int> vec{};

	for (int ix_seller{}; ix_seller < data.at(region).size(); ix_seller++)
	{
		int max = GetSalesSumAmountByRegionSeller(data, region, ix_seller);
		if (max > maxAmount)
		{
			maxAmount = max;
			vec.clear();
		}
		if (max >= maxAmount)
			vec.push_back(ix_seller);
	}

	return vec;
}

vector<int> GetBestMonthsByRegion(const Data &data, int region)
{
	array<int, NUM_MONTHS> maxAmount{};
	vector<int> vec{};

	for (int ix_seller{}; ix_seller < data.at(region).size(); ix_seller++)
		for (int ix_month{}; ix_month < data.at(region).at(ix_seller).size(); ix_month++)
			maxAmount[ix_month] += GetSalesSumAmount(data, region, ix_seller, ix_month);

	int max{};
	for (int ix_month{}; ix_month < NUM_MONTHS; ix_month++)
	{
		if (maxAmount.at(ix_month) > max)
		{
			max = maxAmount.at(ix_month);
			vec.clear();
		}
		if (maxAmount.at(ix_month) >= max)
			vec.push_back(ix_month);
	}

	return vec;
}

void PrintSellersNames(const vector<int> vec)
{
	cout << "[";
	for (int ix{}; ix < vec.size(); ix++)
	{
		cout << (ix > 0 ? ", " : "") << GetSellerName(vec.at(ix) + 1);
	}
	cout << "]";
}

void PrintMonths(const vector<int> vec)
{
	cout << "[";
	for (int ix{}; ix < vec.size(); ix++)
	{
		cout << (ix > 0 ? ", " : "") << GetMonthName(vec.at(ix) + 1);
	}
	cout << "]";
}

void PrintStatistics(const Data &data, int region)
{
	for (int ix_region{region != -1 ? region : 0}; ix_region < ((region != -1) ? region + 1 : (int)data.size()); ix_region++)
	{
		cout << "Statistics for Region <" << GetRegionName(ix_region + 1) << ">:\n";
		cout << "\tMax amount of the year: $" << GetSalesSumAmountByRegion(data, ix_region) << "\n";
		cout << "\tBest seller/s of the year: ";
		PrintSellersNames(GetBestSellersByRegion(data, ix_region));
		cout << "\n";
		cout << "\tBest months/s of the year: ";
		PrintMonths(GetBestMonthsByRegion(data, ix_region));
		cout << "\n";
		cout << "\n";
		PrintTable(data, ix_region);
	}
}

string FixedLengthString(string txt, unsigned length)
{
	string ret{};
	for (unsigned i{}; i < length; i++)
		ret += txt.length() > i ? txt[i] : ' ';
	return ret;
}

void PrintTable(const Data &data, int ix_region)
{
	// Print headers
	cout << "\t" << FixedLengthString("Seller", TABLE_COL_NAME_SIZE);
	for (int i{}; i < NUM_MONTHS; i++)
		cout << " | " << FixedLengthString(GetMonthName(i + 1), TABLE_COL_MONTH_SIZE);

	cout << " | " << FixedLengthString("Total", TABLE_COL_MONTH_SIZE) << "\n\t";

	// Print div line
	for (int i{}; i < (TABLE_COL_NAME_SIZE + 13 * (TABLE_COL_MONTH_SIZE + 3)); i++)
		cout << "-";
	cout << "\n";

	// Print amounts by seller
	for (int ix_seller{}; ix_seller < data.at(ix_region).size(); ix_seller++)
	{
		cout << "\t" << FixedLengthString(GetSellerName(ix_seller + 1), TABLE_COL_NAME_SIZE);
		for (int ix_month{}; ix_month < data.at(ix_region).at(ix_seller).size(); ix_month++)
		{
			cout << " | $" << FixedLengthString(to_string(GetSalesSumAmount(data, ix_region, ix_seller, ix_month)) + " [" + to_string(GetSalesCount(data, ix_region, ix_seller, ix_month)) + "]", (TABLE_COL_MONTH_SIZE - 1));
		}
		cout << " | $" << FixedLengthString(to_string(GetSalesSumAmountByRegionSeller(data, ix_region, ix_seller)) + " [" + to_string(GetSalesCountByRegionSeller(data, ix_region, ix_seller)) + "]", (TABLE_COL_MONTH_SIZE - 1)) << "\n";
	}

	// Print div line
	cout << "\t";
	for (int i{}; i < (TABLE_COL_NAME_SIZE + 13 * (TABLE_COL_MONTH_SIZE + 3)); i++)
		cout << "-";
	cout << "\n";

	// Print Total amounts
	cout << "\t" << FixedLengthString("Total", TABLE_COL_NAME_SIZE);
	for (int ix_month{}; ix_month < NUM_MONTHS; ix_month++)
	{
		cout << " | $" << FixedLengthString(to_string(GetSalesSumAmountByRegionMonth(data, ix_region, ix_month)) + " [" + to_string(GetSalesCountByRegionMonth(data, ix_region, ix_month)) + "]", (TABLE_COL_MONTH_SIZE - 1));
	}
	cout << " | $" << FixedLengthString(to_string(GetSalesSumAmountByRegion(data, ix_region)) + " [" + to_string(GetSalesCountByRegion(data, ix_region)) + "]", (TABLE_COL_MONTH_SIZE - 1)) << "\n";

	cout << "\n";
}
