#include "importXML.h"

using namespace System;
using namespace System::IO;
using namespace System::Xml;
//need to load project with external lib (dirent.h)
using namespace std;

void printCustomers(vector<Customer>&);

//NOTE: check if pass value is int or perfect string? 
//throw exception with filename and error

//template<class EX>
//class traced_error : virtual public std::exception, virtual public EX
//{
//public:
//	traced_error(const std::string& file, int line, const EX& ex)
//		: EX(ex),
//		line_(line),
//		file_(file)
//	{
//	}
//
//	const char* what() const
//	{
//		std::stringstream ss;
//		static std::string msg;
//		ss << "File: " << file_ << " Line: " << line_ << " Error: " << EX::what();
//		msg = ss.str().c_str();
//		return msg.c_str();
//	}
//
//	int line_;
//	std::string file_;
//};
//
//template<class EX> traced_error<EX> make_traced_error(const std::string& file, int line, const EX& ex)
//{
//	return traced_error<EX>(file, line, ex);
//}
//
//
//class my_exception : virtual public std::exception
//{
//public:
//	my_exception() {};
//
//	const char* what() const
//	{
//		return "Invalid Format (Double / Int)";
//	}
//};
//
//class my_exception1 : virtual public std::exception
//{
//public:
//	my_exception1() {};
//
//	const char* what() const
//	{
//		return "Error, field cannot be null!";
//	}
//};
//
//#define throwx(EX) (throw make_traced_error(__FILE__,__LINE__,EX))

//checking for null values
String^ isNull(String^ s)
{
	int error;
	if (String::IsNullOrEmpty(s))
		error = 1;
	if (error)
		throwx(my_exception1());
	else
		return s;
	
}

double checkForDouble(String^ s)
{
	try {
		double num = double::Parse(s);
		return num;
	}
	catch (FormatException^ ex)
	{
		throwx(my_exception());
	}
}

int checkForInt(String^ s)
{
	try {
		int num = int::Parse(s);
		return num;
	}
	catch (FormatException^ ex)
	{
		throwx(my_exception());
	}
}

int getxmlShipdata(std::string shipFile, vector<Ship>& shipFiles )
{
	XmlTextReader^ reader = nullptr;
	String^ filename = gcnew String(shipFile.c_str());   //Convert from standard string to System String
	String^ shipName = "<null>";
	String^ shipOwner;
	String^ shipValue = "0.0";
	String^ shipCompany = """";
	String^ maxLoad = "0";
	String^ basicLoad = "0";
	String^ basicPrice = "0.0";
	String^ heavyLoad = "0";
	String^ heavyPrice = "0.0";
	String^ refrigeratedLoad = "0";
	String^ refrigeratedPrice = "0.0";
	String^ liquidLoad = "0";
	String^ liquidPrice = "0.0";
	String^ specialLoad = "0";
	String^ specialPrice = "0.0";
	String^ country = """";
	String^ portName = """";
	String^ date = "0";
	String^ month = "0";
	String^ year = "0";

	try
	{       
		double standardShipValue = 0.0;
		double standardShipBasicPrice = 0.0;
		double standardShipHeavyPrice = 0.0;
		double standardShipRefrigeratedPrice = 0.0;
		double standardShipSpecialPrice = 0.0;
		double standardShipLiquidPrice = 0.0;

		int standardShipAllMaxLoad = 0;
		int standardShipBasicLoad = 0;
		int standardShipHeavyLoad = 0;
		int standardShipRefrigeratedLoad = 0;
		int standardShipSpecialLoad = 0;
		int standardShipLiquidLoad = 0;
		int standardShipDate = 0;
		int standardShipMonth = 0;
		int standardShipYear = 0;

		reader = gcnew XmlTextReader(filename);
		reader->WhitespaceHandling = WhitespaceHandling::None;

		while (reader->Read())
		{
			switch (reader->NodeType)
			{
			case XmlNodeType::Element:
				
				if (reader->Name == "ship") {
					shipName = isNull(reader->GetAttribute("name"));
					//Console::Write("Ship Name: " + shipName);
				}

				if (reader->Name == "owner") {
					reader->Read();
					shipOwner = isNull(reader->Value);
					//Console::Write("\nOwner: " + shipOwner);
				}
				if (reader->Name == "value_in_billion") {
					reader->Read();
					shipValue = reader->Value;
					//Console::Write("\nShip Value: " + shipValue);
				}
				standardShipValue = checkForDouble(isNull(shipValue));
				if (reader->Name == "company") {
					reader->Read();
					shipCompany = isNull(reader->Value);
					//Console::Write("\nCompany: " + shipCompany);
				}

				if (reader->Name == "container" && reader->GetAttribute("type") == "all") {
					reader->Read();
					if (reader->Name == "max_load") {
						reader->Read();
						maxLoad = reader->Value;
						//Console::Write("\nMax Load: " + maxLoad);
					}
				}
				standardShipAllMaxLoad = checkForInt(isNull(maxLoad));
				if (reader->Name == "container") {
					if (reader->GetAttribute("type") == "basic" || reader->GetAttribute("type_ID") == "basic") {
						reader->Read();
						if (reader->Name == "max_load") {
							reader->Read();
							basicLoad = reader->Value;
							//Console::Write("\nBasic Load: " + basicLoad); 
							reader->Read();
							reader->Read();
							//Console::Write(reader->Name);
							if (reader->Name  == ("price_per_container")){
								//reader->ReadToNextSibling("price_per_container");
								reader->Read();
								basicPrice = reader->Value;
								//Console::Write("\nBasic Price: " + basicPrice);
							}
						}
						if (reader->Name == "price_per_container") {
							reader->Read();
							basicLoad = reader->Value;
							//Console::Write("\nBasic Price: " + basicPrice);
							reader->Read();
							reader->Read();
							if (reader->Name == ("max_load")) {
								//reader->ReadToNextSibling("price_per_container");
								reader->Read();
								basicPrice = reader->Value;
								//Console::Write("\nBasic Load: " + basicLoad);
							}
						}

					}
					standardShipBasicLoad = checkForInt(isNull(basicLoad));
					standardShipBasicPrice = checkForDouble(isNull(basicPrice));
					//-----------------End of Basic----------------------------------------------------------

					if (reader->GetAttribute("type") == "heavy" || reader->GetAttribute("type_ID") == "heavy") {
						reader->Read();
						if (reader->Name == "max_load") {
							reader->Read();
							heavyLoad = reader->Value;
							//Console::Write("\nHeavy Load: " + heavyLoad);
							reader->Read();
							reader->Read();
							if (reader->Name == ("price_per_container")) {
								//reader->ReadToNextSibling("price_per_container");
								reader->Read();
								heavyPrice = reader->Value;
								//Console::Write("\nHeavy Price: " + heavyPrice);
							}
						}
						if (reader->Name == "price_per_container") {
							reader->Read();
							heavyLoad = reader->Value;
							//Console::Write("\nHeavy Price: " + heavyPrice);
							reader->Read();
							reader->Read();
							if (reader->Name == ("max_load")) {
								//reader->ReadToNextSibling("price_per_container");
								reader->Read();
								heavyPrice = reader->Value;
								//Console::Write("\nHeavy Load: " + heavyLoad);
							}
						}

					}
					standardShipHeavyLoad = checkForInt(isNull(heavyLoad));
					standardShipHeavyPrice = checkForDouble(isNull(heavyPrice));
					//-----------------End of Heavy----------------------------------------------------------
					if (reader->GetAttribute("type") == "special" || reader->GetAttribute("type_ID") == "special") {
						reader->Read();
						if (reader->Name == "max_load") {
							reader->Read();
							specialLoad = reader->Value;
							//Console::Write("\nSpecial Load: " + specialLoad);
							reader->Read();
							reader->Read();
							if (reader->Name == ("price_per_container")) {
								//reader->ReadToNextSibling("price_per_container");
								reader->Read();
								specialPrice = reader->Value;
								//Console::Write("\nSpecial Price: " + specialPrice);
							}
						}
						if (reader->Name == "price_per_container") {
							reader->Read();
							specialLoad = reader->Value;
							//Console::Write("\nSpecial Price: " + specialPrice);
							reader->Read();
							reader->Read();
							if (reader->Name == ("max_load")) {
								//reader->ReadToNextSibling("price_per_container");
								reader->Read();
								specialPrice = reader->Value;
								//Console::Write("\nSpecial Load: " + specialLoad);
							}
						}
					}
					standardShipSpecialLoad = checkForInt(isNull(specialLoad));
					standardShipSpecialPrice = checkForDouble(isNull(specialPrice));
					//-----------------End of Special----------------------------------------------------------

					if (reader->GetAttribute("type") == "refrigerated" || reader->GetAttribute("type_ID") == "refrigerated") {
						reader->Read();
						if (reader->Name == "max_load") {
							reader->Read();
							refrigeratedLoad = reader->Value;
							//Console::Write("\nRefrigerated Load: " + refrigeratedLoad);
							reader->Read();
							reader->Read();
							if (reader->Name == ("price_per_container")) {
								//reader->ReadToNextSibling("price_per_container");
								reader->Read();
								refrigeratedPrice = reader->Value;
								//Console::Write("\nRefrigerated Price: " + refrigeratedPrice);
							}
						}
						if (reader->Name == "price_per_container") {
							reader->Read();
							refrigeratedLoad = reader->Value;
							//Console::Write("\nRefrigerated Price: " + refrigeratedPrice);
							reader->Read();
							reader->Read();
							if (reader->Name == ("max_load")) {
								//reader->ReadToNextSibling("price_per_container");
								reader->Read();
								refrigeratedPrice = reader->Value;
								//Console::Write("\nRefrigerated Load: " + refrigeratedLoad);
							}
						}
					}
					standardShipRefrigeratedLoad = checkForInt(isNull(refrigeratedLoad));
					standardShipRefrigeratedPrice = checkForDouble(isNull(refrigeratedPrice));
					//-----------------End of Refrigerated----------------------------------------------------------

					if (reader->GetAttribute("type") == "liquid" || reader->GetAttribute("type_ID") == "liquid") {
						reader->Read();
						if (reader->Name == "max_load") {
							reader->Read();
							liquidLoad = reader->Value;
							//Console::Write("\nLiquid Load: " + liquidLoad);
							reader->Read();
							reader->Read();
							if (reader->Name == ("price_per_container")) {
								//reader->ReadToNextSibling("price_per_container");
								reader->Read();
								liquidPrice = reader->Value;
								//Console::Write("\nLiquid Price: " + liquidPrice);
							}
						}
						if (reader->Name == "price_per_container") {
							reader->Read();
							liquidLoad = reader->Value;
							//Console::Write("\nLiquid Price: " + liquidPrice);
							reader->Read();
							reader->Read();
							if (reader->Name == ("max_load")) {
								//reader->ReadToNextSibling("price_per_container");
								reader->Read();
								liquidPrice = reader->Value;
								//Console::Write("\nLiquid Load: " + liquidLoad);
							}
						}

					}
					standardShipLiquidLoad = checkForInt(isNull(liquidLoad));
					standardShipLiquidPrice = checkForDouble(isNull(liquidPrice));
					//-----------------End of Liquid----------------------------------------------------------
				}
				//--------------------------End of Container---------------------------------------------

				if (reader->Name == "destination") {
					//Console::Write(reader->Name);
					reader->Read();
					if (reader->Name == "country") {
						reader->Read();
						country = isNull(reader->Value);
						//Console::Write("\nCountry: " + country);
						reader->ReadToNextSibling("port_name");
						reader->Read();
						reader->Read();
						portName = isNull(reader->Value);
						//Console::Write("\nPort Name: " + portName);
					}
				}

				if (reader->Name == "deadline") {
					//Console::Write(reader->Name);
					reader->Read();
					if (reader->Name == "date") {
						reader->Read();
						date = reader->Value;
						//Console::Write("\nDate: " + date);
						reader->ReadToNextSibling("month");
						reader->Read();
						reader->Read();
						month = reader->Value;
						//Console::Write("\nMonth: " + month);
						reader->ReadToNextSibling("year");
						reader->Read();
						reader->Read();
						year = reader->Value;
						//Console::Write("\nYear: " + year);
					}
				}
				standardShipDate = checkForInt(isNull(date));
				standardShipMonth = checkForInt(isNull(month));
				standardShipYear = checkForInt(isNull(year));

			}
		}
		string standardShipName = msclr::interop::marshal_as<string>(shipName);
		string standardShipOwner = msclr::interop::marshal_as<string>(shipOwner);

		string standardShipCompany = msclr::interop::marshal_as<string>(shipCompany);

		string standardDestinationCountry = msclr::interop::marshal_as<string>(country);
		string standardDestinationPort = msclr::interop::marshal_as<string>(portName);


		Ship ships(standardShipName, standardShipOwner, standardShipValue, standardShipCompany, standardShipAllMaxLoad, standardShipBasicLoad,
			standardShipBasicPrice, standardShipHeavyLoad, standardShipHeavyPrice, standardShipLiquidLoad, standardShipLiquidPrice, standardShipRefrigeratedLoad, standardShipRefrigeratedPrice,
			standardShipSpecialLoad, standardShipSpecialPrice, standardDestinationCountry, standardDestinationPort,
			standardShipDate, standardShipMonth, standardShipYear);

		shipFiles.push_back(ships);
	}
	finally
	{
		if (reader != nullptr)
			reader->Close();
	}


	return 1;
}

int getxmlContainerdata(std::string containerFile, vector<Customer>& customerFiles, vector<Container *> containerFiles)
{


	XmlTextReader^ reader = nullptr;
	String^ filename = gcnew String(containerFile.c_str());   //Convert from standard string to System String
	String^ custID = """";
	String^ name = """";
	String^ age = "0";
	String^ company = """";
	String^ basicLoad = "0";
	String^ basicSpecial = "0";
	String^ heavyLoad = "0";
	String^ heavySpecial = "0";
	String^ refrigeratedLoad = "0";
	String^ refrigeratedSpecial = "0";
	String^ liquidLoad = "0";
	String^ liquidSpecial = "0";
	String^ specialProperty = "<null>";
	String^ country = """";
	String^ portName = """";
	String^ date = "0";
	String^ month = "0";
	String^ year = "0";

	int standardBasicLoad = 0;
	int standardBasicSpecial = 0;
	int standardHeavyLoad = 0;
	int standardHeavySpecial = 0;
	int standardRefrigeratedLoad = 0;
	int standardRefrigeratedSpecial = 0;
	int standardLiquidLoad = 0;
	int standardLiquidSpecial = 0;

	int standardAge = 0;
	int standardShipDate = 0;
	int standardShipMonth = 0;
	int standardShipYear = 0;

	bool standardIsSpecial = false;
	string standardSpecialProperty ="<null>";
	string standardBasic = "Basic";
	string standardHeavy = "Heavy";
	string standardLiquid = "Liquid";
	string standardRefrigerator = "Refrigerated";

	try
	{
		reader = gcnew XmlTextReader(filename);
		reader->WhitespaceHandling = WhitespaceHandling::None;
		while (reader->Read())
		{
			switch (reader->NodeType)
			{
			case XmlNodeType::Element:
				if (reader->Name == "customer") {
					custID = isNull(reader->GetAttribute("ID"));
					//Console::Write("Customer ID: " + custID);
				}
				if (reader->Name == "name") {
					reader->Read();
					name = isNull(reader->Value);
					//Console::Write("\nName: " + name);
				}
				if (reader->Name == "age") {
					reader->Read();
					age = reader->Value;
					//Console::Write("\nAge: " + age);
				}
				standardAge = checkForInt(isNull(age));
				if (reader->Name == "company") {
					reader->Read();
					company = isNull(reader->Value);
					//Console::Write("\nCompany: " + company);
				}

				if (reader->Name == "container") {
					if (reader->GetAttribute("type") == "basic" || reader->GetAttribute("type_ID") == "basic") {
						reader->Read();
						if (reader->Name == "number") {
							reader->Read();
							basicLoad = reader->Value;
							standardIsSpecial = false;
							standardSpecialProperty = "<null>";
							//Console::Write("\nBasic Load: " + basicLoad);
						}
						int standardBasicLoad = checkForInt(isNull(basicLoad));
						//string standardSpecialProperty = msclr::interop::marshal_as<string>(specialProperty);
						containerFiles.push_back(new Basic (standardBasic, standardBasicLoad, standardIsSpecial, standardSpecialProperty));
					}
					if (reader->GetAttribute("type") == "basic_special" || reader->GetAttribute("type_ID") == "basic_special") {
						reader->Read();
						if (reader->Name == "special_property") {
							reader->Read();
							specialProperty = reader->Value;
							//Console::Write("\nSpecial Property: " + specialProperty);
							standardIsSpecial = true;
							reader->Read();
							reader->Read();
							if (reader->Name == "number") {
								//reader->ReadToNextSibling("number");
								reader->Read();
								basicSpecial = reader->Value;
								//Console::Write("\nBasic Special Load: " + basicSpecial);
							}
						}
						if (reader->Name == "number") {
							reader->Read();
							basicSpecial = reader->Value;
							standardIsSpecial = true;
							//Console::Write("\nBasic Special Load: " + basicSpecial);
							reader->Read();
							reader->Read();
							if (reader->Name == "special_property") {
								//reader->ReadToNextSibling("number");
								reader->Read();
								specialProperty = reader->Value;
								//Console::Write("\nSpecial Property: " + specialProperty);
							}
						}
						int standardBasicSpecial = checkForInt(isNull(basicSpecial));
						string standardSpecialProperty = msclr::interop::marshal_as<string>(specialProperty);
						containerFiles.push_back(new Basic(standardBasic, standardBasicSpecial, standardIsSpecial, standardSpecialProperty));
					}
					//-----------------End of Basic----------------------------------------------------------
					if (reader->GetAttribute("type") == "heavy" || reader->GetAttribute("type_ID") == "heavy") {
						reader->Read();
						if (reader->Name == "number") {
							reader->Read();
							heavyLoad = reader->Value;
							standardIsSpecial = false;
							standardSpecialProperty = "<null>";
							//Console::Write("\nHeavy Load: " + heavyLoad);
						}
						int standardHeavyLoad = checkForInt(isNull(heavyLoad));
						//string standardSpecialProperty = msclr::interop::marshal_as<string>(specialProperty);
						containerFiles.push_back(new Heavy(standardHeavy, standardHeavyLoad, standardIsSpecial, standardSpecialProperty));
					}
					if (reader->GetAttribute("type") == "heavy_special" || reader->GetAttribute("type_ID") == "heavy_special") {
						reader->Read();
						if (reader->Name == "special_property") {
							reader->Read();
							specialProperty = reader->Value;
							//Console::Write("\nSpecial Property: " + specialProperty);
							reader->Read();
							reader->Read();
							standardIsSpecial = true;
							if (reader->Name == "number") {
								//reader->ReadToNextSibling("number");
								reader->Read();
								heavySpecial = reader->Value;
								//Console::Write("\nHeavy Special Load: " + heavySpecial);
							}
						}
						if (reader->Name == "number") {
							reader->Read();
							heavySpecial = reader->Value;
							//Console::Write("\nHeavy Special Load: " + heavySpecial);
							reader->Read();
							reader->Read();
							standardIsSpecial = true;
							if (reader->Name == "special_property") {
								//reader->ReadToNextSibling("number");
								reader->Read();
								specialProperty = reader->Value;
								//Console::Write("\nSpecial Property: " + specialProperty);
							}
						}
						int standardHeavySpecial = checkForInt(isNull(heavySpecial));
						string standardSpecialProperty = msclr::interop::marshal_as<string>(specialProperty);
						containerFiles.push_back(new Heavy(standardHeavy, standardHeavySpecial, standardIsSpecial, standardSpecialProperty));

					}
					
					//-----------------End of Heavy----------------------------------------------------------
					if (reader->GetAttribute("type") == "refrigerated" || reader->GetAttribute("type_ID") == "refrigerated") {
						reader->Read();
						if (reader->Name == "number") {
							reader->Read();
							refrigeratedLoad = reader->Value;
							standardIsSpecial = false;
							standardSpecialProperty = "<null>";
							//Console::Write("\nRefrigerated Load: " + refrigeratedLoad);
						}
						int standardRefrigeratedLoad = checkForInt(isNull(refrigeratedLoad));
						//string standardSpecialProperty = msclr::interop::marshal_as<string>(specialProperty);
						containerFiles.push_back(new Refrigerated(standardRefrigerator, standardRefrigeratedLoad, standardIsSpecial, standardSpecialProperty));

					}
					if (reader->GetAttribute("type") == "refrigerated_special" || reader->GetAttribute("type_ID") == "refrigerated_special") {
						reader->Read();
						if (reader->Name == "special_property") {
							reader->Read();
							specialProperty = reader->Value;
							//Console::Write("\nSpecial Property: " + specialProperty);
							standardIsSpecial = true;
							reader->Read();
							reader->Read();
							if (reader->Name == "number") {
								//reader->ReadToNextSibling("number");
								reader->Read();
								refrigeratedSpecial = reader->Value;
								//Console::Write("\nRefrigerated Special Load: " + refrigeratedSpecial);
							}
						}
						if (reader->Name == "number") {
							reader->Read();
							refrigeratedSpecial = reader->Value;
							//Console::Write("\nRefrigerated Special Load: " + refrigeratedSpecial);
							standardIsSpecial = true;
							reader->Read();
							reader->Read();
							if (reader->Name == "special_property") {
								//reader->ReadToNextSibling("number");
								reader->Read();
								specialProperty = reader->Value;
								//Console::Write("\nSpecial Property: " + specialProperty);
							}
						}
						int standardRefrigeratedSpecial = checkForInt(isNull(refrigeratedSpecial));
						string standardSpecialProperty = msclr::interop::marshal_as<string>(specialProperty);
						containerFiles.push_back(new Refrigerated(standardRefrigerator, standardRefrigeratedSpecial, standardIsSpecial, standardSpecialProperty));

					}
					
					//-----------------End of Refrigerated----------------------------------------------------------
					if (reader->GetAttribute("type") == "liquid" || reader->GetAttribute("type_ID") == "liquid") {
						reader->Read();
						if (reader->Name == "number") {
							reader->Read();
							liquidLoad = reader->Value;
							standardIsSpecial = false;
							standardSpecialProperty = "<null>";
							//Console::Write("\nLiquid Load: " + liquidLoad);
						}
						int standardLiquidLoad = checkForInt(isNull(liquidLoad));
						//string standardSpecialProperty = msclr::interop::marshal_as<string>(specialProperty);
						containerFiles.push_back(new Liquid(standardLiquid, standardLiquidLoad, standardIsSpecial, standardSpecialProperty));


					}
					if (reader->GetAttribute("type") == "liquid_special" || reader->GetAttribute("type_ID") == "liquid_special") {
						reader->Read();
						if (reader->Name == "special_property") {
							reader->Read();
							specialProperty = reader->Value;
							//Console::Write("\nSpecial Property: " + specialProperty);
							standardIsSpecial = true;
							reader->Read();
							reader->Read();
							if (reader->Name == "number") {
								//reader->ReadToNextSibling("number");
								reader->Read();
								liquidSpecial = reader->Value;
								//Console::Write("\nLiquid Special Load: " + liquidSpecial);
							}
						}
						if (reader->Name == "number") {
							reader->Read();
							liquidSpecial = reader->Value;
							//Console::Write("\nLiquid Special Load: " + liquidSpecial);
							standardIsSpecial = true;
							reader->Read();
							reader->Read();
							if (reader->Name == "special_property") {
								//reader->ReadToNextSibling("number");
								reader->Read();
								specialProperty = reader->Value;
								//Console::Write("\nSpecial Property: " + specialProperty);
							}
						}
						int standardLiquidSpecial = checkForInt(isNull(liquidSpecial));
						string standardSpecialProperty = msclr::interop::marshal_as<string>(specialProperty);
						containerFiles.push_back(new Liquid(standardLiquid, standardLiquidSpecial, standardIsSpecial, standardSpecialProperty));

					}
					//---------------------------------------End of Liquid--------------------------------------

					
				}
				//--------------------------End of Container---------------------------------------------

				if (reader->Name == "destination") {
					//Console::Write(reader->Name);
					reader->Read();
					if (reader->Name == "country") {
						reader->Read();
						country = isNull(reader->Value);
						//Console::Write("\nCountry: " + country);
						reader->ReadToNextSibling("port_name");
						reader->Read();
						reader->Read();
						portName = isNull(reader->Value);
						//Console::Write("\nPort Name: " + portName);
					}
				}

				if (reader->Name == "deadline") {
					//Console::Write(reader->Name);
					reader->Read();
					if (reader->Name == "date") {
						reader->Read();
						date = reader->Value;
						//Console::Write("\nDate: " + date);
						reader->ReadToNextSibling("month");
						reader->Read();
						reader->Read();
						month = reader->Value;
						//Console::Write("\nMonth: " + month);
						reader->ReadToNextSibling("year");
						reader->Read();
						reader->Read();
						year = reader->Value;
						//Console::Write("\nYear: " + year);
					}
				}
				standardShipDate = checkForInt(isNull(date));
				standardShipMonth = checkForInt(isNull(month));
				standardShipYear = checkForInt(isNull(year));

			}
		}
		string standardCustID = msclr::interop::marshal_as<string>(custID);
		string standardName = msclr::interop::marshal_as<string>(name);

		string standardCompany = msclr::interop::marshal_as<string>(company);

		string standardDestinationCountry = msclr::interop::marshal_as<string>(country);
		string standardDestinationPort = msclr::interop::marshal_as<string>(portName);


		//Insert customer
		Customer customers(standardCustID, standardName, standardAge, standardCompany, standardDestinationCountry, standardDestinationPort,
			standardShipDate, standardShipMonth, standardShipYear, containerFiles);

		customerFiles.push_back(customers);

	}
	finally
	{
		if (reader != nullptr)
			reader->Close();
	}

	return 1;
}


//checking if the file is an xml
bool checkIfXML(const std::string& s) {
	if (s.size() < 4)
		return true;
	if (s.compare(s.size() - 4, 4, ".xml") == 0)
		return true;
}

//using a recursive method to get the all the files in seperate directories
int getdir(string dir, vector<string> &files)
{
	DIR *dp;
	struct dirent *dirp;

	if ((dp = opendir(dir.c_str())) == NULL) {
		/*cout << "Error(" << errno << ") opening " << dir << endl;
		cout << "Enter Folder Path Again "<< endl;*/
		return errno;
	}

	while ((dirp = readdir(dp)) != NULL) {
		string name(dirp->d_name);
		if (name != "." && name != "..") {
			string test = dir + "/" + name;
			if (checkIfXML(test) == true) {
				files.push_back(test);
			}
			if (dirp->d_type == DT_DIR) {
				getdir(test, files);

			}
		}
	}
	closedir(dp);

}


//check if container file is correct
int checkContainerFile(std::string containerFile) {
	XmlTextReader^ reader = nullptr;
	String^ filename = gcnew String(containerFile.c_str());   //Convert from standard string to System String

	try
	{
		reader = gcnew XmlTextReader(filename);
		reader->WhitespaceHandling = WhitespaceHandling::None;
		while (reader->Read())
		{
			switch (reader->NodeType)
			{
			case XmlNodeType::Element:
				//Console::Write(reader->Name);
				if (reader->Name == "containerRequirement" || reader->Name == "containerrequirement" || reader->Name == "ContainerRequirement") {
					//Console::Write("Entered");
					return 1;
				}
			}
		}
	}
	finally
	{
		if (reader != nullptr)
			reader->Close();
	}



}

//check if ship file is correct
int checkShipFile(std::string shipFile) {
	XmlTextReader^ reader = nullptr;
	String^ filename = gcnew String(shipFile.c_str());   //Convert from standard string to System String

	try
	{
		reader = gcnew XmlTextReader(filename);
		reader->WhitespaceHandling = WhitespaceHandling::None;
		while (reader->Read())
		{
			switch (reader->NodeType)
			{
			case XmlNodeType::Element:
				//Console::Write(reader->Name);
				if (reader->Name == "shipInformation" || reader->Name == "shipinformation" || reader->Name == "ShipInformation") {
					//Console::Write("Entered");
					return 1;
				}
			}
		}
	}
	finally
	{
		if (reader != nullptr)
			reader->Close();
	}



}

void printShips(vector<Ship>& shipFiles) {
	//after storing it in the class

	for (std::vector<Ship>::iterator it = shipFiles.begin(); it != shipFiles.end(); ++it) {
		cout << "\n==============START SHIP===============" << endl;
		cout << "Ship Name: " << it->getShipName() <<endl;
		cout << "Ship Owner: " << it->getOwner() << endl;
		cout << "Value In Billions: " << it->getShipValue() << endl;
		cout << "Ship Company: " << it->getCompany() << endl;

		cout << "\nMax Load: " << it->getMaxLoad() << endl;
		cout << "Basic Load: " << it->getBasicLoad() << endl;
		cout << "Basic Price: " << it->getBasicPrice() << endl;
		cout << "Heavy Load: " << it->getHeavyLoad() << endl;
		cout << "Heavy Price: " << it->getHeavyPrice() << endl;
		cout << "Special Load: " << it->getSpecialLoad() << endl;
		cout << "Special Price: " << it->getSpecialPrice() << endl;
		cout << "Refrigerated Load: " << it->getRefrigeratedLoad() << endl;
		cout << "Refrigerated Price: " << it->getRefrigeratedPrice() << endl;
		cout << "Liquid Load: " << it->getLiquidLoad() << endl;
		cout << "Liquid Price: " << it->getLiquidPrice() << endl;

		cout << "\nDestination Country: " << it->getCountry() << endl;
		cout << "Destination Port: " << it->getPort() << endl;
		cout << "Deadline: " << it->getDate() << endl;
		cout << "\n==============END SHIP===============" << endl;

	}



}


void printCustomers(vector<Customer>& customerFiles) {
	//after storing it in the class
	for (std::vector<Customer>::iterator it = customerFiles.begin(); it != customerFiles.end(); ++it) {
		cout << "\n==============START CUSTOMER===============" << endl;
		cout << "Customer ID: " << it->getID() << endl;
		cout << "Name: " << it->getName() << endl;
		cout << "Age: " << it->getAge() << endl;
		cout << "Company: " << it->getCompany() << endl;

		vector<Container *>tempcontainerFiles =  it->getContainerArray();

		vector<Container *>::iterator iter;
		for (iter = tempcontainerFiles.begin(); iter != tempcontainerFiles.end(); iter++) {
			cout << "\nType: " <<(*iter)->getType() << endl;
			cout << "Amount: " << (*iter)->getAmount() << endl;
			cout << "Is Special: " << (*iter)->getIsSpecial() << endl;
			cout << "Special Properties: " << (*iter)->getSpecialProperties() << endl;
		}

		cout << "\nDestination Country: " << it->getCountry() << endl;
		cout << "Destination Port: " << it->getPortName() << endl;
		cout << "Deadline: " << it->getDate() << endl;
		cout << "\n==============END CUSTOMER===============" << endl;

	}

}
int importXML(string folderPath)
{
	string dir;
	vector<string> files;
	vector<Ship> shipFiles;
	vector<Customer> customerFiles;
	vector<Container *> containerFiles;

	int count = 0;
	
	//if folder path does not exist....
	/*while (getdir(dir, files) == errno) {
		count += 1;
		cout << "Enter Folder Path: " << endl;
		if (count > 1) {
			cout << "No Such Directory!" << endl;
		}
		cin >> dir;
	}*/
	
	
	//(getdir("//mac/home/desktop/example", files));
	(getdir(folderPath, files));
	for (unsigned int i = 0; i < files.size(); i++) {
		if (checkShipFile(files[i]) == true) {
			try {
				getxmlShipdata(files[i], shipFiles);
			}
			catch (const std::exception& ex)
			{
				cout << files[i]<< endl;
				cout << ex.what();
			}

		}
		if (checkContainerFile(files[i]) == true) {
			try {
				getxmlContainerdata(files[i], customerFiles, containerFiles);
			}
			catch (const std::exception& ex)
			{
				cout << files[i] << endl;
				cout << ex.what();
			}
			

		}

	}

	printShips(shipFiles);
	printCustomers(customerFiles);

	system("pause");
	return 0;

}



