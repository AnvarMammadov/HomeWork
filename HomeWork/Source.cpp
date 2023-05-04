#include<iostream>
#include<Windows.h>
#include<conio.h>
using namespace std;
//Product > name, price, discount

//	Store > Address, Product** products, count


//	Show All Products      1
//	Search Products        2
//	Add New Products       3
//	Delete products        4
//	Buy Products           5
//    Store About            6
//    Exit App               

struct Product {
	double price;
	double discount;
	char* name;
	int quantity;
};
struct Store {
	Product** products;
	char* adress;
	int count;
};
void MyCls(int time) {
	Sleep(time * 1000);
	system("cls");
}
void ShowMenu() {
	cout << "\n\t\t\t\t\t" << (char)2 << " W E l C O M E\tS T O R E " << (char)2 << endl << endl << "\n\t\t\t\t\t\tPRODUCT MENU" << endl << endl;
	cout << "\n\t\t\t1.Show All Products \t\t\t2.Search Products\n\n\t\t\t3.Add New Products\t\t\t4.Delete Products" <<
		"\n\n\t\t\t5.Buy Products\t\t\t\t6.Store About\n\n\t\t\t\t\t\t7.Exit Store" << endl << endl;
}
void ShowProduct(Product& product) {
	cout << " - - - Product Info - - - " << endl;
	cout << "Product Name     : " << product.name << endl;
	cout << "Product Price    : " << product.price << " $ " << endl;
	cout << "Product Discount : " << product.discount << " % " << endl;
	cout << "Product Quantity : " << product.quantity << endl << endl << endl;
}
void ShowAllProducts(const Store& store) {
	cout << " - - - All Products - - - " << endl;
	for (size_t i = 0; i < store.count; i++)
	{
		cout << "N0 : " << i + 1 << ": " << endl;
		ShowProduct(*store.products[i]);
	}
}
void FindProduct(Store& store, char* searchItem) {
	cout << " - - - Products - - - " << endl << endl;
	bool found = false;
	for (int i = 0; i < store.count; i++) {
		if (strstr(store.products[i]->name, searchItem) != nullptr) {
			ShowProduct(*store.products[i]);
			found = true;
		}
	}
	if (!found) {
		cout << "Product Not Find..." << endl;
	}

}
Product* GetNewProduct(const Store& store) {
	cin.ignore();
	cin.clear();

	cout << "Enter Product Name : ";
	char* name = new char[30];
	cin.getline(name, 30);

	cout << "Enter Product Price : ";
	double price = 0;
	cin >> price;

	cout << "Enter Product Discount : ";
	double discount = 0;
	cin >> discount;

	cout << "Enter Product Quantity : ";
	int quantity = 0;
	cin >> quantity;

	return new Product{ price,discount,name,quantity };
}
void AddProductToStore(Store& store, Product* newProduct) {
	if (newProduct == nullptr) { cout << "New Product Not Found..." << endl; return; }

	auto newStore = new Product * [store.count + 1] {};
	for (size_t i = 0; i < store.count; i++)
	{
		newStore[i] = store.products[i];
	}
	newStore[store.count] = newProduct;
	store.products = newStore;
	newStore = nullptr;
	store.count++;
}
void DeleteProduct(Store& store, int index) {
	auto newProducts = new Product * [store.count - 1];
	for (size_t i = 0; i < index; i++)
	{
		newProducts[i] = store.products[i];
	}
	for (size_t i = index + 1; i < store.count; i++)
	{
		newProducts[i - 1] = store.products[i];
	}
	store.products = newProducts;
	newProducts = nullptr;
	store.count--;
}
bool ReturnMenu() {
	cout << "\n\nDo you want return Product Menu ?  ==> [ Please Press any K E Y... ]" << endl;
	char key = NULL;
	key = _getch();
	if (key) return true;
	return false;
}
void IncreaseValue(Product& product, int quantity) {
	if (quantity >= product.quantity / 2) {
		product.price += product.price * 0.2;
	}
	else if (quantity < product.quantity / 2) {
		product.price += 0.1;
	}
}
void BuyProduct(Product& product, int quantity) {
	if (quantity <= product.quantity && quantity >= 1 && product.quantity >= 1) {
		product.quantity -= quantity;
		IncreaseValue(product, quantity);
		cout << "You purchase of " << quantity << " " << product.name << " has been completed successfully..." << endl;
	}
	else {
		cout << "There are currently not as many products ( " << product.name << " ) as you would like ... " << endl;
	}
}
void ShowStoreFooter(Store& store) {
	cout << "Our company was founded with a simple mission: \n\nto provide high-quality products at affordable prices to our customers.\n" <<
		"We believe that everyone deserves access to fresh, \nhealthy food, and we're committed to sourcing only the best ingredients for our products.\n" <<
		"With a team of dedicated professionals and a passion for excellence, \nwe're proud to be a trusted provider of food and household items in our community.\n" <<
		"\n\n We Store Location :  \"Baku City, Nasimi District, Imran Gasimov Street. \"" << endl;
}
void main() {
	system("color f0");


	Product* p1 = new Product{ 0.7,0,new char[20] {"Coca-Cola"},60 };
	Product* p2 = new Product{ 4.7,20,new char[20] {"Pringles"},15 };
	Product* p3 = new Product{ 2,10,new char[20] {"Lays Cheeps"},45 };

	Store* store = new Store{ new Product * [3] {p1,p2,p3},new char[60] {"Baki seheri Nesimi Rayonu.."},3 };

	enum Operations { Show = '1', Search = '2', Add = '3', Delete = '4', Buy = '5', Footer = '6' };
	while (true)
	{
		char select = NULL;
		ShowMenu();
		cin >> select;
		if (select == '7') { MyCls(0.5); cout << "Closed App" << endl; MyCls(1.5); break; }
		while (true)
		{
			MyCls(0);
			if (select == Show) {
				ShowAllProducts(*store);
				if (ReturnMenu()) { MyCls(0); break; }
			}
			else if (select == Search) {
				cout << "Search [ Enter product name ] :   ";
				char* searchItem = new char[50] {};
				cin.ignore();
				cin.clear();
				cin.getline(searchItem, 50);
				FindProduct(*store, searchItem);
				if (ReturnMenu()) { MyCls(0); break; }
			}
			else if (select == Add) {
				Product* product = GetNewProduct(*store);
				AddProductToStore(*store, product);
				cout << "\" " << product->name << " \"" << " added to store successfully... " << endl;
				if (ReturnMenu()) { MyCls(0); break; }
			}
			else if (select == Delete) {
				ShowAllProducts(*store);
				cout << "Enter Product number for delete : ";
				int no = 0;
				cin >> no;
				if (no >= 1 && no <= store->count) {
					int index = no - 1;
					cout << "\" " << store->products[index]->name << " \"" << " deleted to store successfully... " << endl;
					DeleteProduct(*store, index);
					if (ReturnMenu()) { MyCls(0); break; }
				}
				else {
					cout << "InCorrect NO..." << endl;  MyCls(1.5); break;
				}
			}
			else if (select == Buy) {
				ShowAllProducts(*store);
				cout << "Enter Product number for buy : ";
				int no = 0;
				cin >> no;
				int count = 0;
				if (no >= 1 && no <= store->count) {
					cout << "Enter quantity : ";
					int quantity = 0;
					cin >> quantity;
					int index = no - 1;
					auto product = store->products[index];
					BuyProduct(*product, quantity);
					if (ReturnMenu()) { MyCls(0); break; }
				}
				else {
					cout << "InCorrect NO..." << endl;  MyCls(1.5); break;
				}
			}
			else if (select == Footer) {
				ShowStoreFooter(*store);
				if (ReturnMenu()) { MyCls(0); break; }
			}
			else {
				cout << "InCorrect Input Operation...\nPlease Wait..." << endl; MyCls(2); break;
			}

		}
	}

	cout << endl << endl << endl; cin.get();
}