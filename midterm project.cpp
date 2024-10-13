#include <iostream>
#include <string>
#include <iomanip>
#include <vector> 
#include <cctype> 
using namespace std;

class Item {
	private:
	    string id;
	    string name;
	    int quantity;
	    double price;
	    string category;
	
	public:
	    Item(string id, string name, int quantity, double price, string category) : id(id), name(name), quantity(quantity), price(price), category(category) {}
	
	    virtual void displayItem() = 0; 
	
	    void setQuantity(int q) { quantity = q; }
	    void setPrice(double p) { price = p; }
	
	    string getId() const { return id; }
	    string getName() const { return name; }
	    int getQuantity() const { return quantity; }
	    double getPrice() const { return price; }
	    string getCategory() const { return category; }
};

class DisplayInventory : public Item {	
	public:
	    DisplayInventory(string id, string name, int quantity, double price, string category) : Item(id, name, quantity, price, category) {}
	
	    void displayItem() override {
	        cout << left << setw(15) << getId() << setw(20) << getName() << setw(20)
	             << getQuantity() << setw(20) << getPrice() << setw(20) << getCategory() << endl;
	    }
};

class StoreInventory {
	private:
	    vector<Item*> items; 
	    
	    void sortItemsByPrice(bool ascending);
	    void sortItemsByQuantity(bool ascending);
	    void displaySortedItems();
	
	public:
	    vector<Item*>& getItems() {
	        return items;
	    }
		
		void itemEmpty(){
			if (items.empty()) {
	    		cout << "No items in the Inventory.\n"; 
	        	return;
	    	}
		}

		isDuplicateID(const string& id) {
		    for (const auto& item : items) {
		        if (item->getId() == id) {
		            return true; 
		        }
		    }
		    return false; 
		}

		string toLower(const string& str) {
		    string lowerStr;
		    for (char c : str) {
		        lowerStr += tolower(c); 
		    }
		    return lowerStr;
		}
		
		isDuplicateName(const string& name) {
		    for (const auto& item : items) {
		        if (item->getName() == name) {
		            return true; 
		        }
		    }
		    return false; 
		}
		
		bool isValidQuantity(const string& input) {
		    if (input.empty()) return false; 
		    for (char c : input) {
		        if (!isdigit(c)) { 
		            return false; 
		        }
		    }
		    return true; 
		}
		
		bool isValidPrice(const string& input) {
		    if (input.empty()) return false; 
		    bool decimalFound = false;
		    
		    for (char c : input) {
		        if (!isdigit(c)) {
		            if (c == '.' && !decimalFound) {
		                decimalFound = true; 
		            } 
					else {
		                return false; 
		            }
		        }
		    }
		    return true; 
		}
		
		int validateQuantity() {
		    string quantityInput;
		    int quantity;
		
		    while (true) {
		        cout << "Enter Quantity: ";
		        getline(cin,quantityInput);
		
		        if (!isValidQuantity(quantityInput) || (quantity = stoi(quantityInput)) <= 0) {
		            cout << "Invalid Quantity!\n\n";
		        } 
				else {
		            break;  
		        }
		    }
		    return quantity;
		}
		
		double validatePrice() {
		    string priceInput;
		    double price;
		
		    while (true) {
		        cout << "Enter Price: ";
		        getline(cin,priceInput);
		
		        if (!isValidPrice(priceInput) || (price = stod(priceInput)) <= 0) {
		            cout << "Invalid Price!\n\n";
		        } 
				else {
		            break;  
		        }
		    }
		    return price;
		}

	    void addItem();
	    void updateItem();
	    void removeItem(); 
	    void searchItem();
	    void sortItem();
};

void charValidation(){ 
    cin.clear();
	cin.ignore(1000, '\n');
}

class DisplayAll : public Item { 
	private:
    	StoreInventory& inventory; 

	public:
    	DisplayAll(StoreInventory& inv) : Item("", "", 0, 0.0, ""), inventory(inv) {}
	
    	void displayItem() override {
    		inventory.itemEmpty();
    		
    		if (!inventory.getItems().empty()) {
    			cout << "\n---------------------------------------------" <<endl;
		    	cout << "I T E M S - I N - T H E - I N V E N T O R Y" <<endl;
		    	cout << "---------------------------------------------" <<endl;
    			cout << endl << "---------------------------------------------------------------------------------------" <<endl;
	        	cout << left << setw(15) << "ID" << setw(20) << "Name" << setw(20) << "Quantity"
	        	     << setw(20) << "Price" << setw(20) << "Category" << endl;
	        	cout << "---------------------------------------------------------------------------------------" <<endl;     
	
		        vector<Item*>& items = inventory.getItems(); 
		
		        for (Item* item : items) {
		            item->displayItem(); 
		        }
		        cout << "---------------------------------------------------------------------------------------" <<endl;
	    	}
    	}
};

void StoreInventory :: addItem() { 
    string id, name, category;
	int quantity, choice;
    double price;
    char ans;

    do{
    	do{
    		cout << "\n--------------------------------" <<endl;
		    cout << "A D D I T E M" <<endl;
		    cout << "--------------------------------" <<endl;
    		cout << "--------------------------------" <<endl;
			cout << "Category:" << endl;
			cout << "--------------------------------" <<endl;
	    	cout << "1 - Clothing" << endl;
	    	cout << "2 - Electronics" << endl;
	    	cout << "3 - Entertainment" << endl;
	    	cout << "--------------------------------" <<endl;
	    	cout << "Enter Category: ";
	    	cin >> choice;
	    	cout << "--------------------------------" <<endl;
			charValidation();
	    	
	    	switch (choice) {
	    	    case 1: category = "Clothing"; break;
	    	    case 2: category = "Electronics"; break;
	    	    case 3: category = "Entertainment"; break;
	    		default:
	    	        cout << "Invalid Category!\n";
	    	}
    	} while(choice != 1 && choice != 2 && choice != 3);
    		
		do {
            cout << "Enter Item ID: ";
	    	getline(cin, id);
            
            if (isDuplicateID(id)) {
                cout << "ID already exists! Please enter another ID.\n" <<endl;
            }
            
        } while (isDuplicateID(id));

		do {
            cout << "Enter Item Name: ";
	    	getline(cin, name);
            
            if (isDuplicateName(name)) {
			    cout << "\nItem found!" << endl;
			
			    for (Item* item : items) {
			        if (item->getName() == name) {
			            cout << "ID: " << item->getId() << endl;
			            break;  
			        }
			    }
			    
			    cout << "This item already exists! Please enter another item.\n" <<endl;
			}
	    } while (isDuplicateName(name));
		    
	
		quantity = validateQuantity();
	    price = validatePrice();

    	items.push_back(new DisplayInventory(id, name, quantity, price, category));
    	cout << "\nItem added successfully!\n";
		
		do {
            cout << "\nDo you want to add another item? (Y/N): ";
            cin >> ans;
            if (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
                cout << "Invalid Answer!\n";
            }
        } while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
		
		if (ans == 'N' || ans == 'n') {
			system("cls");
    		return; 
        }
        
    } while (ans == 'Y' || ans == 'y');
}

void StoreInventory :: updateItem() { 
    string id, choice;
    char ans;
	
	do{
		itemEmpty();
		bool itemFound = false; 

		if (!getItems().empty()) {
			do{
				cout << "--------------------------------" <<endl;
		    	cout << "U P D A T E I T E M" <<endl;
		    	cout << "--------------------------------" <<endl;
		    	
				DisplayAll all(*this); 
	            all.displayItem(); 
	
				cout << "\n--------------------------------" <<endl;
		    	cout << "Enter Item ID to update: ";
		    	getline(cin, id);
		    	cout << "--------------------------------" <<endl;
			
				for (Item* item : items) {
				    if (toLower(item->getId()) == toLower(id)) {
				        cout << "\nItem found!" << endl;
				        itemFound = true;
				
				        int choice;
				        do {
				        	cout << "--------------------------------" <<endl;
				            cout << "Update:" << endl;
				            cout << "1 - Quantity" << endl;
				            cout << "2 - Price" << endl;
				            cout << "--------------------------------" <<endl;
				            cout << "Enter Update Choice: ";
				            cin >> choice;
				            cout << "--------------------------------" <<endl;
				            charValidation(); 
				
				            int currentQuantity = item->getQuantity();
							double currentPrice = item->getPrice();
	
							int newQuantity;
							double newPrice;
				
				            if (choice == 1) {
				            	newQuantity = validateQuantity();
				                if (newQuantity == currentQuantity) {
							        cout << "No need for update! The quantity you entered is just the same as current quantity." << endl;
							    } 
								else {
							        item->setQuantity(newQuantity);  
							        cout << "Quantity of Item " << item->getName() << " is updated from " << currentQuantity << " to " << newQuantity << endl;
							    }
				            } 
				            
							else if (choice == 2) {
				                newPrice = validatePrice();
								if (newPrice == currentPrice) {
							        cout << "No need for update! The price you entered is just the same as current price." << endl;
							    }  
							    else{
									item->setPrice(newPrice);  
				                	cout << "Price of Item " <<item->getName() << " is updated from " <<currentPrice  << " to " <<newPrice <<endl;;
								}
				            } 
				            
							else {
				                cout << "Invalid Update Choice!\n";
				            }
				            
				        } while (choice != 1 && choice != 2); 
				        break;
				    }
				}
				
				if (!itemFound) { 
	            	cout << "Item not found.\n";
	            	do {
			            cout << "\nDo you still want to update an item? (Y/N): ";
			            cin >> ans;
			            if (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
			                cout << "Invalid Answer!\n";
			            }
		        	} while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
					
					if (ans == 'N' || ans == 'n') {
						system("cls");
			    		return; 
			        }
			        cin.ignore();
	        	}
	    	} while(!itemFound);
	    	
	    	do {
	            cout << "\nDo you want to update another item? (Y/N): ";
	            cin >> ans;
	            if (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
	                cout << "Invalid Answer!\n";
	            }
        	} while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
			
			if (ans == 'N' || ans == 'n') {
				system("cls");
	    		return; 
	        }
	        
	        cin.ignore();
		}
	} while (ans == 'Y' || ans == 'y');
}

void StoreInventory :: removeItem(){ 
    string id;
    char ans, choice;
    
    do {
        itemEmpty();

        if (!getItems().empty()) {
        	cout << "\n--------------------------------" <<endl;
		    cout << "R E M O V E I T E M" <<endl;
			cout << "--------------------------------" <<endl;
			
            DisplayAll all(*this); 
            all.displayItem(); 
        
            bool itemFound = false; 
            
            do {
                cout << "--------------------------------" <<endl;
                cout << "Enter Item ID to remove: ";
	    		getline(cin, id);
                cout << "--------------------------------" <<endl;

                for (auto it = items.begin(); it != items.end(); ++it) {
				    if (toLower((*it)->getId()) == toLower(id)) {
				        string itemName = (*it)->getName(); 
				
				        delete *it; 
				        items.erase(it); 
				
				        cout << "Item " << itemName << " has been removed.\n"; 
				        itemFound = true; 
				        break; 
				    }
				}

                if (!itemFound) {
                    cout << "Item not found!\n";
                    do{
	                    cout << "\nDo you still want to remove an item? (Y/N): ";
				        cin >> choice;
				        if (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n') {
				           cout << "Invalid Answer!\n";
				        }
			        } while (choice != 'Y' && choice != 'y' && choice != 'N' && choice != 'n');
			        	
			        if (choice == 'N' || choice == 'n') {
			        	system("cls");
				    	return; 
				    }
					cin.ignore();
		        }
            } while (!itemFound); 
            
            if (getItems().empty()) {
                cout << "No more items in the inventory.\n";
                return; 
                
            }

            do {
	            cout << "\nDo you want to remove another item? (Y/N): ";
	            cin >> ans;
	            if (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
	                cout << "Invalid Answer!\n";
	            }
        	} while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
        	
        	if (ans == 'N' || ans == 'n') {
        		system("cls");
	    		return; 
	        }
	        
	        cin.ignore();
        } 
        
		else {
            return; 
        }
        
    } while (ans == 'Y' || ans == 'y'); 
}

class DisplayByCategory : public Item { 
	private:
    	StoreInventory& inventory; 

	public:
    	DisplayByCategory(StoreInventory& inv) : Item("", "", 0, 0.0, ""), inventory(inv) {}

    	void displayItem() override {
        	string choice, selectedCategory;
        	char ans;
        	
        	do{
	        	inventory.itemEmpty();
	        	
	        	if (!inventory.getItems().empty()) {
		        	do{
		        		cout << "\n--------------------------------------------------" <<endl;
		    			cout << "D I S P L A Y - I T E M S - B Y - C A T E G O R Y" <<endl;
		    			cout << "--------------------------------------------------" <<endl;
		        		cout << "--------------------------------" <<endl;
						cout << "Select Category:" <<endl;
						cout << "--------------------------------" <<endl;
						cout << "1 - Clothing" <<endl;
						cout << "2 - Electronics" <<endl;
						cout << "3 - Entertainment" <<endl; 
						cout << "--------------------------------" <<endl;
						cout << "Enter Category: ";
			        	cin >> choice;
			        	cout << "--------------------------------" <<endl;
			        	charValidation();
			
						if (isdigit(choice[0]) && choice.length() == 1) {
						    int catChoice = stoi(choice);
						    switch (catChoice) {
						        case 1:
						            selectedCategory = "Clothing";
						            break;
						        case 2:
						            selectedCategory = "Electronics";
						            break;
						        case 3:
						            selectedCategory = "Entertainment";
						            break;
						        default:
						            cout << "Invalid Category!\n";
						            cout << "Category " <<choice << " does not exist!" <<endl;
						            break;
						    }
						} 
						
						else {
	                        if (inventory.toLower(choice) == "clothing") {
	                            selectedCategory = "Clothing";
	                        } 
							else if (inventory.toLower(choice) == "electronics") {
	                            selectedCategory = "Electronics";
	                        } 
							else if (inventory.toLower(choice) == "entertainment") {
	                            selectedCategory = "Entertainment";
	                        } 
							else {
	                            cout << "Invalid Category!\n";
	                            cout << "Category " <<choice << " does not exist!" <<endl;
	                            continue; 
	                        }
	                    }
					} while (selectedCategory.empty());

		        	bool found = false;	 
		
		        	vector<Item*>& items = inventory.getItems(); 
	
	                for (Item* item : items) {
	                    if (inventory.toLower(item->getCategory()) == inventory.toLower(selectedCategory)) {
	                        found = true; 
	                        break; 
	                    }
	                }
	
			        if (found) {
			            cout << endl << "Category: " << selectedCategory << endl;
			            cout << "------------------------------------------------------------------------" << endl;
			            cout << left << setw(15) << "ID" << setw(20) << "Name" << setw(20) << "Quantity"
			                 << setw(20) << "Price" << endl;
			            cout << "------------------------------------------------------------------------" << endl;
			            
			            for (Item* item : items) {
	                        if (inventory.toLower(item->getCategory()) == inventory.toLower(selectedCategory)) {
	                            cout << left << setw(15) << item->getId() << setw(20) << item->getName()
	                                 << setw(20) << item->getQuantity() << setw(20) << item->getPrice() << endl;
	                        }
			            }
			        } 
					
					else {
			            cout << "No items found in the category: " << selectedCategory << endl;
			        }
			        
			        do {
			            cout << "\nDo you want to display another category? (Y/N): ";
			            cin >> ans;
			            if (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
			                cout << "Invalid Answer!\n";
			            }
		        	} while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
					
					if (ans == 'N' || ans == 'n') {
						system("cls");
			    		return; 
			        }
			        
			        cin.ignore();
				}
			} while(ans == 'Y' || ans == 'y');
        }
};

void StoreInventory :: searchItem() { 
	char ans;
	
	do{
		itemEmpty();
		
		if (!getItems().empty()) {
	    	cout << "--------------------------------" <<endl;
			cout << "Enter the Item ID to search: ";
		    string searchId;
	    	getline(cin, searchId);
		    cout << "--------------------------------" <<endl;
		
		    bool found = false;
		    
		    for (const auto& item : items) { 
		        if (toLower(item->getId()) == toLower(searchId)) {
		            cout << "Item found:\n";
		            cout << endl << "---------------------------------------------------------------------------------------" <<endl;
				    cout << left << setw(15) << "ID" << setw(20) << "Name" 
				         << setw(20) << "Quantity" << setw(20) << "Price" 
				         << setw(20) << "Category" << endl;
				    cout << "---------------------------------------------------------------------------------------" <<endl;  
		            cout << left << setw(15) << item->getId() << setw(20) << item->getName() 
		                 << setw(20) << item->getQuantity() << setw(20) << item->getPrice() 
		                 << setw(20) << item->getCategory() << endl;
		            cout << "---------------------------------------------------------------------------------------" <<endl;       
		            found = true;
		            break;
		        }
		    }
		
		    if (!found) {
		        cout << "Item not found.\n";
			}    
			
			do{
	            cout << "\nDo you want to search another item? (Y/N): ";
	            cin >> ans;
	            if (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n') {
	                cout << "Invalid Answer!\n";
	            }
        	} while (ans != 'Y' && ans != 'y' && ans != 'N' && ans != 'n');
			
			if (ans == 'N' || ans == 'n') {
				system("cls");
	    		return; 
	        }
	        
	        cin.ignore();
		}
	} while(ans == 'Y' || ans == 'y');
}

void StoreInventory::sortItemsByPrice(bool ascending) {
    for (size_t i = 0; i < items.size() - 1; i++) {
        for (size_t j = 0; j < items.size() - 1 - i; j++) {
            if ((ascending && items[j]->getPrice() > items[j + 1]->getPrice()) ||
                (!ascending && items[j]->getPrice() < items[j + 1]->getPrice())) {
                swap(items[j], items[j + 1]);
            }
        }
    }
    displaySortedItems();
}
void StoreInventory::sortItemsByQuantity(bool ascending) {
    for (size_t i = 0; i < items.size() - 1; i++) {
        for (size_t j = 0; j < items.size() - 1 - i; j++) {
            if ((ascending && items[j]->getQuantity() > items[j + 1]->getQuantity()) ||
                (!ascending && items[j]->getQuantity() < items[j + 1]->getQuantity())) {
                swap(items[j], items[j + 1]);
            }
        }
    }
    displaySortedItems();
}
void StoreInventory::displaySortedItems() { 
	cout << endl << "---------------------------------------------------------------------------------------" <<endl;
    cout << left << setw(15) << "ID" << setw(20) << "Name" 
         << setw(20) << "Quantity" << setw(20) << "Price" 
         << setw(20) << "Category" << endl;
    cout << "---------------------------------------------------------------------------------------" <<endl;     

    for (const auto& item : items) {
        cout << left << setw(15) << item->getId() << setw(20) << item->getName() 
             << setw(20) << item->getQuantity() << setw(20) << item->getPrice() 
             << setw(20) << item->getCategory() << endl;     
    }
    cout << "---------------------------------------------------------------------------------------" <<endl;
}
void StoreInventory::sortItem() { 
    int sortChoice, orderChoice;
    bool ascending;
	
	itemEmpty();

	if (!getItems().empty()) {
		
		if(getItems().size() == 1){
			cout << "There is only one item in the Inventory. No need for sorting" <<endl;
			return;
		}
		
	    do{
	    	cout << "--------------------------------" <<endl;
			cout << "Select sorting method:" <<endl;
		    cout << "1 - Sort by Price" <<endl;
		    cout << "2 - Sort by Quantity" <<endl;
		    cout << "--------------------------------" <<endl;
		    cout << "Enter Sorting Method Choice: ";
		    cin >> sortChoice;
		    cout << "--------------------------------" <<endl;
		    charValidation();
		    if (sortChoice != 1 && sortChoice != 2){
		    	cout << "Invalid Sorting Method Choice!" <<endl;
			}
		} while(sortChoice != 1 && sortChoice != 2);
	
		do{
			cout << "--------------------------------" <<endl;
		    cout << "Select sorting order:\n";
		    cout << "1 - Ascending\n";
		    cout << "2 - Descending\n";
		    cout << "--------------------------------" <<endl;
		    cout << "Enter Sorting Order: ";
		    cin >> orderChoice;
		    cout << "--------------------------------" <<endl;
		    charValidation();
		    ascending = (orderChoice == 1);
		    if (orderChoice != 1 && orderChoice != 2){
		    	cout << "Invalid Sorting Method Choice!" <<endl;
			}
	    } while(orderChoice != 1 && orderChoice != 2);
	
	    switch (sortChoice) {
	        case 1:
	            sortItemsByPrice(ascending);
	            break;
	        case 2:
	            sortItemsByQuantity(ascending);
	            break;
	        default:
	            cout << "Invalid Sorting Option!\n";
	    }
	}
}

class LowStockItem : public Item { 
	private:
	    StoreInventory& inventory;  
	
	public:
	    LowStockItem(StoreInventory& inv) : Item("", "", 0, 0.0, ""), inventory(inv) {} 
	
	    void displayItem() override {
	    	
	    	inventory.itemEmpty();
	    	
	    	int lowStockCount = 0;
	    	
	    	for (Item* item : inventory.getItems()) {
		    	if (item->getQuantity() <= 5) {
		            lowStockCount++;
		        }
		    }
		    
		    if (lowStockCount == 0) {
		        cout << "No items with quantity of 5 and below." << endl;
		        return;  
		    }
	    	
	        if (!inventory.getItems().empty()) {
	        	cout << "--------------------------------" <<endl;
	            cout << "L O W - S T O C K - I T E M S" <<endl;
	            cout << "--------------------------------" <<endl;
	            cout <<endl << "---------------------------------------------------------------------------------------" <<endl;
	            cout << left << setw(15) << "ID" << setw(20) << "Name" 
	                 << setw(20) << "Quantity" << setw(20) << "Price" 
	                 << setw(20) << "Category" << endl;
	            cout << "---------------------------------------------------------------------------------------" <<endl;     
	
	            for (Item* item : inventory.getItems()) {
	                if (item->getQuantity() <= 5) {
	                    cout << left << setw(15) << item->getId() << setw(20) << item->getName() 
	                         << setw(20) << item->getQuantity() << setw(20) << item->getPrice() 
	                         << setw(20) << item->getCategory() << endl;    
	                }
	            }
	            cout << "---------------------------------------------------------------------------------------" <<endl; 
	        }
	    }
};

int main() {
    StoreInventory inv; 
    DisplayByCategory cat(inv);
    DisplayAll all(inv);
    LowStockItem low(inv); 
    
    int choice;

    do {
    	cout << "--------------------------------" <<endl;
    	cout << "myShop Inventory" <<endl;
    	cout << "--------------------------------" <<endl;
        cout << "1 - Add Item" <<endl;
		cout << "2 - Update Item" <<endl;
		cout << "3 - Remove Item" <<endl;
		cout << "4 - Display Items by Category" <<endl;
		cout << "5 - Display All Items" <<endl;
		cout << "6 - Search Item" <<endl;
		cout << "7 - Sort Items" <<endl;
		cout << "8 - Display Low Stock Items" <<endl;
		cout << "9 - Exit" <<endl;
		cout << "--------------------------------" <<endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "--------------------------------" <<endl;
        charValidation();
        system("cls");

        switch (choice) {
            case 1:
                inv.addItem();
                break;
            case 2:
                inv.updateItem();
                break;
            case 3:
                inv.removeItem();
                break;
            case 4: 
                cat.displayItem(); 
                break;
            case 5:
                all.displayItem();
                break;
            case 6:
                inv.searchItem(); 
                break;
            case 7: { 
            	inv.sortItem();
                break;
            }
            case 8:
                low.displayItem();
                break;
            case 9:
                break;
            default:
                cout << "Invalid Choice!\n";
                break;
        }
    } while (choice != 9);

    return 0;
}
