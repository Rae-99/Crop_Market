#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;

int valint(int minVal, int maxVal, const string& disp) {
    int value;
    while(true) {
        cout << disp;
        if(!(cin >> value) || value < minVal || value > maxVal) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Enter " << minVal << "-" << maxVal << ": ";
            continue;
        }
        cin.ignore(10000, '\n'); 
        return value;
    }
}

char valYN(const string& disp) {
    char ch;
    while (true) {
        cout << disp;
        cin >> ch;
        cin.ignore();
        ch = toupper(ch);  // normalize to uppercase
        if (ch == 'Y' || ch == 'N') {
            return ch;
        }
        cout << "Invalid input. Enter Y or N only: ";
    }
}


class login {

private:
    string encrypt(string text){               
        char key = 7;
        for (int i = 0; i < text.length(); i++){
            text[i] = text[i] ^ key;
        }
        return text;
    }

protected:
    string password;


public:
string username;
    bool run() {
        

        while (true) {
            cout << "+===========================================+\n";
            cout << "|  >>  CROP-MARKET : FARMER'S PORTAL  <<  |\n";
            cout << "+===========================================+\n";
            cout << "|                                           |\n";
            cout << "|       >>  1. Log In                       |\n";
            cout << "|       >>  2. Sign Up                      |\n";
            cout << "|       >>  0. Exit                         |\n";
            cout << "|                                           |\n";
            cout << "+-------------------------------------------+\n";
            int a = valint(0, 2, "|  Enter your choice : ");
            cout << "+-------------------------------------------+\n";


            switch (a) {
                case 1: {
                    reenter:
                    string storedname,storedpassword;
                    cout << "Enter username: ";
                    getline(cin,username);
                    cout << "Enter password: ";
                    cin >> password;
                    cin.ignore();

                    ifstream info("userinfo.txt");
                    bool isCorrect=false;
                    while(getline(info,storedname,',') && 
                          getline(info,storedpassword)){

                    if (storedname==username && encrypt(storedpassword)==password) {
                        cout << "\nHello " << username << "!! Welcome Back\n";
                        
                        isCorrect=true;
                        return true;
                        
                    } 
                }
                   if(isCorrect==false){

                    cout<<"Incorrect username or password...."<<endl;
                    cout<<"1.Retry\n0.Exit\n";
                    int b = valint(0, 1, "Enter choice : ");
                    if(b==1){
                        goto reenter;
                    }else break;
                    
                   }
                    
                
                break;
            }
                

                case 2: {
                    bool taken = false;
                    do {
                        taken = false;
                        cout << "Enter username: ";
                        getline(cin, username);

                
                        ifstream checkFile("userinfo.txt");
                        string storedname;
                        while (getline(checkFile, storedname, ',')) {
                            string dummy;
                            getline(checkFile, dummy);
                            if (storedname == username) {
                                taken = true;
                                break;
                            }
                        }
                        checkFile.close();

                        if (taken) {
                            cout << "Username already taken. Please choose a different one.\n";
                        }

                    } while (taken);

                    bool passwordsMatch = false;
                    do {
                        cout << "Enter password: ";
                        cin >> password;
                        cout << "Reenter password: ";
                        string password_re;
                        cin >> password_re;
                        cin.ignore();

                        if (password == password_re) {
                            passwordsMatch = true;
                            cout << "Your account has been created\n";
                            ofstream info("userinfo.txt", ios::app);
                            info << username << "," << encrypt(password) << endl;
                            cout << "\nHello " << username << "!! Welcome\n";
                            return true;
                        } else {
                            cout << "Passwords don't match. Try again.\n";
                        }
                    } while (!passwordsMatch);
                    break;
                }

                case 0:
                    return false;

                default:
                    cout << "Wrong input\n";
            }
        }
    }

    string getusername(){       //Getter for Username
        return username;
    }

    void setUsername(string u){
        username=u;
    }

};

class buyer : public login {
    private:
        int amount, choice, quant;

        
private:
    void restore(string prid, int quantity) {
        ifstream in("cropinfo.txt");
        ofstream out("temp.txt");
        string line;
        
        while (getline(in, line)) {
            stringstream ss(line);
            string f1, f2, f3, f4, rest;
            getline(ss, f1, ',');
            getline(ss, f2, ',');
            getline(ss, f3, ',');
            getline(ss, f4, ',');
            
            if (f1 == prid) {
                int quant_avail = stoi(f4);
                quant_avail += quantity; 
                f4 = to_string(quant_avail);
            }   
            out << f1 << "," << f2 << "," << f3 << "," << f4;
            while (getline(ss, rest, ',')) {
                out << "," << rest;
            }
            out << endl;
        }
        in.close();
        out.close();
        remove("cropinfo.txt");
        rename("temp.txt", "cropinfo.txt");
    }

    public:
        
        int temp2=3, temp1;
        vector<vector<int>> cart;  //{'prdt id or choice', 'quantity', 'amount'}

        void disp_list(){
            cout << "\n+===========================================+\n";
            cout << "|  >>  CROP-MARKET : PRODUCT CATALOGUE <<  |\n";
            cout << "+===========================================+\n";
            cout << "|                                           |\n";
            cout << "|       >>  1. Wheat                        |\n";
            cout << "|       >>  2. Jowar                        |\n";
            cout << "|       >>  3. Bajra                        |\n";
            cout << "|       >>  4. Maize                        |\n";
            cout << "|       >>  5. Barley                       |\n";
            cout << "|                                           |\n";
            cout << "|       >>  0. View Cart                    |\n";
            cout << "|       >> -1. Back to Menu                 |\n";
            cout << "|                                           |\n";
            cout << "+-------------------------------------------+\n";
            choice = valint(-1, 5, "|  Enter your choice : ");
            cout << "+-------------------------------------------+\n";

            string cropname,sellid,grade,quant_str,r50,r100,r;
            bool isAvailable=false;

            ifstream info7("cropinfo.txt");
            

            if(choice==0){
                disp_cart();
                if(!cart.empty()){
                    char a = valYN("Do you want to checkout? (Y/N): ");
                    if(a=='Y' || a=='y'){
                        payment();
                        return;
                    }
                }

                disp_list();
            }

            else if(choice==-1)
                return;
            
            else if(choice<6 && choice>0){
                while(getline(info7,sellid,',') && 
                      getline(info7,cropname,',') && 
                      getline(info7,grade,',') && 
                      getline(info7,quant_str,',') &&
                      getline(info7,r50,',') &&
                      getline(info7,r100,',') &&
                      getline(info7,r)){
                    if(cropname==to_string(choice)){        
                        isAvailable=true;
                        if(r=="0"){
                            r="-";
                        }
                        if(r100=="0"){
                            r100="-";
                        }
                        cout<<"\n"<<"Product ID : "<<sellid<<"\n"<<"Crop: "<<cropname<<"\n"<<"Grade : "<<grade<<"\n"<<
                        "Quantity available : "<<quant_str<<" kg\n"<<"Rate below 50kg : "<<r50<<"\n"<<
                        "Rate between 50-100kg : "<<r100<<"\n"<<"Rate above 100kg : "<<r<<endl;
                    }
                }
                info7.close();
                
                if(!isAvailable){
                    cout<<"Product not available!\n";
                }
            }  
        }

        int getchoice(){        //Getter for choice
            return choice;
        }

        void transaction(){
            cout << "\n+===========================================+\n";
            cout << "|  >>  CROP-MARKET : PURCHASE OPTIONS <<  |\n";
            cout << "+===========================================+\n";
            cout << "|                                           |\n";
            cout << "|       >>  1. Buy Bulk                     |\n";
            cout << "|       >>  2. Buy Sample                   |\n";
            cout << "|       >>  3. Back                         |\n";
            cout << "|                                           |\n";
            cout << "+-------------------------------------------+\n";
            temp1 = valint(1, 3, "|  Enter your choice : ");
            cout << "+-------------------------------------------+\n";
            

            switch (temp1)
            {
            case 1:
                bulk();
                break;

            case 2:
                sample();
                break;

            case 3:
                return;
            
            default:
                cout<<"Invalid choice!\n";
                break;
            }
        }    
        
        void bulk(){
            string prid;
            string id,grad,quant_str,r50,r100,r,cropname;
            
            // Ask user for Product ID
            cout<<"Enter the Product ID which you wish to buy : ";
            cin>>prid;
            
            // Verify and get product details
            ifstream info9("cropinfo.txt");
            bool found = false;
            while(getline(info9,id,',') && 
                  getline(info9,cropname,',') && 
                  getline(info9,grad,',') && 
                  getline(info9,quant_str,',') &&
                  getline(info9,r50,',') &&
                  getline(info9,r100,',') &&
                  getline(info9,r)){
                if(prid==id){
                    found = true;
                    cout<<"\nProduct Found!\n";
                    cout<<"Crop: "<<cropname<<"\n";
                    cout<<"Grade: "<<grad<<"\n";
                    cout<<"Quantity available: "<<quant_str<<" kg\n";
                    cout<<"Rate below 50kg: ₹"<<r50<<"\n";
                    cout<<"Rate between 50-100kg: ₹"<<r100<<"\n";
                    cout<<"Rate above 100kg: ₹"<<r<<"\n\n";
                    
                    quant = valint(1, 10000, "How much do you wish to buy? : ");
                    
                    int quantity = quant;
                    int num1=stoi(r50);
                    int num2=stoi(r100);
                    int num3=stoi(r);
                    
                    if(quantity>stoi(quant_str)){
                        cout<<"Insufficient stock! Only "<<quant_str<<" kg available.\n";
                        info9.close();
                        return;
                    }
                    
                    if(quantity>100){
                        amount=num3*quantity;   
                    }
                    else if(quantity>50){
                        amount=num2*quantity;    
                    }
                    else{
                        amount=num1*quantity;    
                    }
                    info9.close();
                    cout<<"Total amount = ₹"<<amount<<endl;
                    
                    cout<<"\n1. Add to cart and buy more \n2. Checkout \n3. Discard this item \n";
                    temp2 = valint(1, 3, "Enter your choice: ");
                    
                    if(temp2==1){
                        cart.push_back({stoi(prid), quantity, amount});
                        ofstream info13("history.txt",ios::app);
                        info13<<"Buy"<<","<<username<<","<<cropname<<","<<quantity<< "," << amount<<"\n";
                        info13.close();
                        
                        // Update inventory
                        ifstream in("cropinfo.txt");
                        ofstream out("temp.txt");
                        string line;
                        while (getline(in, line)) {
                            stringstream ss(line);
                            string f1, f2, f3, f4, rest;
                            getline(ss, f1, ',');
                            getline(ss, f2, ',');
                            getline(ss, f3, ',');
                            getline(ss, f4, ',');
                            
                            if (f1 == prid) {
                                int quant_avail = stoi(f4);
                                if (quant_avail - quantity == 0) {
                                    f2 = "0";
                                } 
                                else {
                                    quant_avail -= quantity;
                                    f4 = to_string(quant_avail);
                                }
                            }   
                            out << f1 << "," << f2 << "," << f3 << "," << f4;
                            while (getline(ss, rest, ',')) {
                                out << "," << rest;
                            }
                            out << endl;
                        }
                        in.close();
                        out.close();
                        remove("cropinfo.txt");
                        rename("temp.txt", "cropinfo.txt");
                        
                        
                        cout<<"Item added to cart!\n";
                        return;
                    }
                    else if(temp2==2){
                        cart.push_back({stoi(prid), quantity, amount});
                        ofstream info13("history.txt",ios::app);
                        info13<<"Buy"<<","<<username<<","<<cropname<<","<<quantity<< "," << amount<<"\n";
                        info13.close();
                        
                        // Update inventory
                        ifstream in("cropinfo.txt");
                        ofstream out("temp.txt");
                        string line;
                        while (getline(in, line)) {
                            stringstream ss(line);
                            string f1, f2, f3, f4, rest;
                            getline(ss, f1, ',');
                            getline(ss, f2, ',');
                            getline(ss, f3, ',');
                            getline(ss, f4, ',');
                            
                            if (f1 == prid) {
                                int quant_avail = stoi(f4);
                                if (quant_avail - quantity == 0) {
                                    f2 = "0";
                                } 
                                else {
                                    quant_avail -= quantity;
                                    f4 = to_string(quant_avail);
                                }
                            }   
                            out << f1 << "," << f2 << "," << f3 << "," << f4;
                            while (getline(ss, rest, ',')) {
                                out << "," << rest;
                            }
                            out << endl;
                        }
                        in.close();
                        out.close();
                        remove("cropinfo.txt");
                        rename("temp.txt", "cropinfo.txt");
                    }
                    else if(temp2==3){
                        restore(prid, quantity);  
                        cout << "Item discarded. Inventory restored.\n";
                        return;
                    }
                }
            }
        
        info9.close();
            
        if(!found){
            cout<<"Invalid Product ID! Please try again.\n";
        }
    }

        void sample(){
            string prid;
            string id,grad,quant_str,r50,r100,r,cropname;
            
            cout<<"Enter the Product ID for sample purchase : ";
            cin>>prid;
            
            ifstream info8("cropinfo.txt");
            bool found = false;
            while(getline(info8,id,',') && 
                  getline(info8,cropname,',') && 
                  getline(info8,grad,',') && 
                  getline(info8,quant_str,',') &&
                  getline(info8,r50,',') &&
                  getline(info8,r100,',') &&
                  getline(info8,r)){
                if(prid==id){
                    found = true;
                    int num3 = stoi(r50);
                    amount = num3 * 10;                 // 10kg sample
                    
                    cout<<"\nProduct Found!\n";
                    cout<<"Crop: "<<cropname<<"\n";
                    cout<<"Grade: "<<grad<<"\n";
                    cout<<"Sample amount is 10kg\n";
                    cout<<"Total amount = ₹"<<amount<<endl;
                    
                    if(10 > stoi(quant_str)){
                        cout<<"Insufficient stock for sample! Only "<<quant_str<<" kg available.\n";
                        info8.close();
                        return;
                    }
                    info8.close(); 
                    cout<<"\n1. Checkout     2. Discard this item \n";
                    cout<<"Enter your choice: ";
                    cin>>temp2;
                    
                    if(temp2==1){
                        ifstream in("cropinfo.txt");
                        ofstream out("temp.txt");
                        string line;
                        while (getline(in, line)) {
                            stringstream ss(line);
                            string f1, f2, f3, f4, rest;
                            getline(ss, f1, ',');
                            getline(ss, f2, ',');
                            getline(ss, f3, ',');
                            getline(ss, f4, ',');
                            
                            if (f1 == prid) {
                                int quant_avail = stoi(f4);
                                if (quant_avail - 10 == 0) {
                                    f2 = "0";
                                } 
                                else {
                                    quant_avail -= 10;
                                    f4 = to_string(quant_avail);
                                }
                            }   
                            out << f1 << "," << f2 << "," << f3 << "," << f4;
                            while (getline(ss, rest, ',')) {
                                out << "," << rest;
                            }
                            out << endl;
                        }
                        in.close();
                        out.close();
                        remove("cropinfo.txt");
                        rename("temp.txt", "cropinfo.txt");
                        ofstream info13("history.txt",ios::app);
                        info13<<"Buy"<<","<<username<<","<<cropname<<","<<10<< "," << amount<<"\n";
                        info13.close();
                        
                        payment(prid);
                    }
                    else if(temp2==2){
                        return;
                    }
                    break;
                }
            }
            info8.close();
            
            if(!found){
                cout<<"Invalid Product ID! Please try again.\n";
            }
        }

        
                //called for sample
        void payment(string prid){
            cout << "\n+===========================================+\n";
            cout << "|  >>  CROP-MARKET : SAMPLE ORDER     <<  |\n";
            cout << "+===========================================+\n";
            cout << "|                                           |\n";
            cout << "|   Product ID     Quantity      Amount     |\n";
            cout << "+-------------------------------------------+\n";
            cout << "|      " << prid << "           10kg          Rs." << amount << "     |\n";
            cout << "|                                           |\n";
            cout << "+-------------------------------------------+\n";
            char conf = valYN("|  Confirm Payment? (Y/N) : ");
            cout << "+-------------------------------------------+\n";

            switch(conf){
                case 'Y': {
                    cout << "|\n|  >> Enter Delivery Address : ";
                    string address;
                    getline(cin, address);
                    cout << "+-------------------------------------------+\n";
                    
                    // Save order with address
                    ofstream orders("orders.txt", ios::app);
                    orders << username << "," << prid << "," 
                        << 10 << "," << amount << "," 
                        << address << endl;
                    orders.close();
                    
                    cout << "|\n|   >> Payment Successful!\n";
                    cout << "|   >> Order placed at: " << address << "\n|\n";
                    cout << "+-------------------------------------------+\n";
                    break;
                }
                case 'N':
                    return;
                default:
                    cout << "|\n|   >> Invalid input, retry\n|\n";
                    cout << "+-------------------------------------------+\n";
                    payment(prid);  
            }
        }
        

        void payment(){
            if(cart.empty()){
                cout << "\n+-------------------------------------------+\n";
                cout << "|  >> Cart is empty! Nothing to checkout.  |\n";
                cout << "+-------------------------------------------+\n";
                return;
            }
            disp_cart();

            cout << "+-------------------------------------------+\n";
            char conf = valYN("|  Confirm Payment? (Y/N) : ");
            cout << "+-------------------------------------------+\n";

            switch(conf){
                case 'Y': {
                    cout << "|\n|  >> Enter Delivery Address : ";
                    string address;
                    getline(cin, address);
                    cout << "+-------------------------------------------+\n";
                    
                    ofstream orders("orders.txt", ios::app);
                    for(const auto& item : cart) {
                        orders << username << "," << item[0] << "," 
                            << item[1] << "," << item[2] << "," 
                            << address << endl;
                    }
                    orders.close();
                    
                    cout << "|\n|   >> Payment Successful!\n";
                    cout << "|   >> Order placed at: " << address << "\n|\n";
                    cout << "+-------------------------------------------+\n";
                    cart.clear();
                    break;
                }
                case 'N':
                    return;
                default:
                    cout << "|\n|   >> Invalid input, retry\n|\n";
                    cout << "+-------------------------------------------+\n";
                    payment(); 
            }
        }

        void disp_cart(){
            int total = 0;
            cout << "\n\n+===========================================+\n";
            cout << "|  >>  CROP-MARKET : YOUR CART        <<  |\n";
            cout << "+===========================================+\n";
            cout << "|                                           |\n";

            if(cart.size() == 0){
                cout << "|        ** Your Cart is Empty **          |\n";
                cout << "|                                           |\n";
                cout << "+-------------------------------------------+\n";
            }
            else{
                cout << "|   #   Product ID   Quantity   Amount      |\n";
                cout << "+-------------------------------------------+\n";
                for(int i = 0; i < cart.size(); i++){
                    cout << "|   " << (i+1) << ".     "
                        << cart[i][0] << "          "
                        << cart[i][1] << "kg       "
                        << "Rs." << cart[i][2] << "\n";
                    total += cart[i][2];
                }
                cout << "|                                           |\n";
                cout << "+-------------------------------------------+\n";
                cout << "|  >>  Total Amount : Rs." << total << "\n";
                cout << "+-------------------------------------------+\n";
            }
        }
};


class sell : public login {
private:
    int p, quantity, r50 = 0, r100 = 0, r = 0,sellid=1000;
    char grade;
    string line;

    void viewOrderDetails() {
        string buyer_name, product_id, quantity, amount, address;
        int order_num = 1;

        cout << "\n+===========================================+\n";
        cout << "|  >>  ORDER DETAILS WITH ADDRESS    <<  |\n";
        cout << "+===========================================+\n";
        cout << "|                                           |\n";

        ifstream orders_file("orders.txt");
        while(getline(orders_file, buyer_name, ',') &&
              getline(orders_file, product_id, ',') &&
              getline(orders_file, quantity, ',') &&
              getline(orders_file, amount, ',') &&
              getline(orders_file, address)){
            
            cout << "|  Order #" << order_num << ":\n";
            cout << "|    Buyer: " << buyer_name << "\n";
            cout << "|    Product ID: " << product_id << "\n";
            cout << "|    Quantity: " << quantity << " kg\n";
            cout << "|    Amount: Rs." << amount << "\n";
            cout << "|    Delivery Address: " << address << "\n";
            cout << "|                                           |\n";
            order_num++;
        }
        orders_file.close();
        cout << "+-------------------------------------------+\n";
    }


public:

    void vieworders() {
        string buyer_name, product_id, quantity, amount, address;
        bool found = false;
        int i = 1;

        cout << "\n+===========================================+\n";
        cout << "|  >>  CROP-MARKET : INCOMING ORDERS  <<  |\n";
        cout << "+===========================================+\n";
        cout << "|                                           |\n";
        cout << "|   #   Buyer Name    Product ID   Qty  Amount   |\n";
        cout << "+-------------------------------------------+\n";

        ifstream orders_file("orders.txt");
        while(getline(orders_file, buyer_name, ',') &&
              getline(orders_file, product_id, ',') &&
              getline(orders_file, quantity, ',') &&
              getline(orders_file, amount, ',') &&
              getline(orders_file, address)){
            
            found = true;
            cout << "|   " << i << ".  " << buyer_name << "        " 
                 << product_id << "       " << quantity 
                 << "kg    Rs." << amount << "\n";
            i++;
        }
        orders_file.close();

        if(!found){
        cout << "|     ** No orders yet **                   |\n";
        cout << "|                                           |\n";
        cout << "+-------------------------------------------+\n";
        return;  
    }
        cout << "|                                           |\n";
        cout << "+-------------------------------------------+\n";
        
        if(found){
            char choice = valYN("|  View detailed order? (Y/N) : ");
            cout << "+-------------------------------------------+\n";
            
            if(choice == 'Y' || choice == 'y'){
                viewOrderDetails();
            }
        }
    }

    void product_info() {

        string id = "999";
        string line;

        ifstream info10("cropinfo.txt");
        while (getline(info10, line)) {
            if (!line.empty()) {
                size_t pos = line.find(',');
                if (pos != string::npos)
                    id = line.substr(0, pos);
            }
        }
        info10.close();

        int newId = stoi(id) + 1;
        id = to_string(newId);

        cout << "\n+===========================================+\n";
        cout << "|  >>  CROP-MARKET : ADD PRODUCT      <<  |\n";
        cout << "+===========================================+\n";
        cout << "|                                           |\n";
        cout << "|   >>  1. Wheat                            |\n";
        cout << "|   >>  2. Jowar                            |\n";
        cout << "|   >>  3. Bajra                            |\n";
        cout << "|   >>  4. Maize                            |\n";
        cout << "|   >>  5. Barley                           |\n";
        cout << "|                                           |\n";
        cout << "+-------------------------------------------+\n";
        cout << "|  Enter product number : ";
        p = valint(1, 5, "|  Enter product number : ");
        cout << "+-------------------------------------------+\n";

        do {
            cout << "|  Enter grade (A = High, B = Average,      |\n";
            cout << "|               C = Low)       : ";
            cin >> grade;
            cin.ignore();
            grade = toupper(grade);  // accept lowercase also
            if (grade != 'A' && grade != 'B' && grade != 'C') {
                cout << "|  Invalid grade! Enter A, B or C only.    |\n";
            }
        } while (grade != 'A' && grade != 'B' && grade != 'C');

        cout << "+-------------------------------------------+\n";
        quantity = valint(1, 100000, "|  Enter quantity (kg)          : ");
        cout << "+-------------------------------------------+\n";
        r50 = valint(0, 100000, "|  Enter price up to 50kg  (Rs.): ");
        if(quantity > 50){
            cout << "+-------------------------------------------+\n";
            r100 = valint(0, 100000, "|  Enter price 50-100kg    (Rs.): ");
        } else r100 = 0;

        if(quantity > 100){
            cout << "+-------------------------------------------+\n";
            r = valint(0, 100000, "|  Enter price above 100kg (Rs.): ");
        } else r = 0;

        cout << "+-------------------------------------------+\n";

        ofstream cinfo("cropinfo.txt", ios::app);
        cinfo << id << ","
            << p << ","
            << grade << ","
            << quantity << ","
            << r50 << ","
            << r100 << ","
            << r << endl;
        cinfo.close();

        ofstream info15("history.txt",ios::app);
        string cropname;
        if(p==1) cropname="Wheat";
        if(p==2) cropname="Jowar";
        if(p==3) cropname="Bajra";
        if(p==4) cropname="Maize";
        if(p==5) cropname="Barley";

        info15<<"Sell"<<","<<username<<","<<cropname<<","<<quantity<< "," << " - "<<"\n";
        info15.close();

        cout << "|                                           |\n";
        cout << "|  >>  Product added! ID : " << id << "             |\n";
        cout << "|                                           |\n";
        cout << "+-------------------------------------------+\n";
    }

};

class Crop {
private:
    string name, soil, water, temperature, season;

public:
    Crop(string n, string s, string w, string t, string se)            //Constructor
        : name(n), soil(s), water(w), temperature(t), season(se) {}

    string getName() const {                                           //Getters
        return name; 
    }
    string getSoil() const { 
        return soil; 
    }
    string getWater() const { 
        return water; 
    }
    string getTemperature() const {
        return temperature; 
    }
    string getSeason() const { 
        return season; 
    }
};

class help {
protected:
    string soil, water, temp, season;
    vector<Crop> crops; 
    
public:

    help(string s, string w, string t, string se) 
        : soil(s), water(w), temp(t), season(se) {
    
        crops.push_back(Crop("Rice",      "h", "h", "h", "m"));
        crops.push_back(Crop("Wheat",     "h", "m", "m", "w"));
        crops.push_back(Crop("Maize",     "m", "m", "m", "s"));
        crops.push_back(Crop("Millets",   "l", "l", "h", "s"));
        crops.push_back(Crop("Sugarcane", "h", "h", "h", "m"));
    }

    virtual void display() = 0;
};

class rec : public help {
private:

    int calculatescore(const Crop& c, const string& soil, const string& water,
                   const string& temp, const string& season) {
        int score = 0;

        if (c.getSoil() == soil)   
            score += 3;
        if (c.getWater() == water)  
            score += 2;
        if (c.getTemperature() == temp) 
            score += 2;
        if (c.getSeason() == season) 
            score += 3;

        return score;
    }

    
public:

    rec(string s, string w, string t, string se) 
        : help (s, w, t, se) {}
    
    void display() override {
        cout << "\n+===========================================+\n";
        cout << "|  >>  RECOMMENDED CROPS              <<  |\n";
        cout << "+===========================================+\n";
        cout << "|                                           |\n";
        
        bool found = false;
        for (const Crop& c : crops) {
            int score = calculatescore(c, soil, water, temp, season);
            if (score >= 6) {
                found = true;
                cout << "|   >>  " << c.getName()
                     << "  (Score : " << score << "/10)\n";
                cout << "|                                           |\n";
            }
        }
        
        if (!found) {
            cout << "|   >>  No strong matches found.            |\n";
            cout << "|        Try adjusting your inputs.         |\n";
            cout << "|                                           |\n";
        }
    }

};



int main() {
    string username;

    loginpage:              //LOGIN
    login l1;
    if(!l1.run())
        return 0;       

    username=l1.getusername();      

    frontpage:
    int k;
    cout << "\n+===========================================+\n";
    cout << "|  >>  CROP-MARKET : MAIN MENU        <<  |\n";
    cout << "+===========================================+\n";
    cout << "|                                           |\n";
    cout << "|       >>  1. Buy                          |\n";
    cout << "|       >>  2. Sell                         |\n";
    cout << "|       >>  3. HelpDesk                     |\n";
    cout << "|       >>  4. History                      |\n";
    cout << "|       >>  0. Log Out                      |\n";
    cout << "|                                           |\n";
    cout << "+-------------------------------------------+\n";
    k = valint(0, 4, "|  Enter your choice : ");
    cout << "+-------------------------------------------+\n";

    if(k==0)
        goto loginpage;

    else if(k==1){              //BUY
        buyer b1;
        b1.setUsername(username);
        restartb:
        b1.disp_list();
        
        if(b1.getchoice()==-1){
            goto frontpage;
        }
        else if(b1.getchoice()==0){
            goto restartb;
        }
        else {
            b1.transaction();

            if(b1.temp1==3)
                goto restartb;
            
            if(b1.temp2 == 1){
                goto restartb;  
            }
            else if(b1.temp2 == 2){
                b1.payment();   
                goto frontpage; 
            }
            else if(b1.temp2 == 3){
                goto restartb;
            }
            else{
                cout<<"Invalid input\n";
                goto restartb;
            }
        }
    }

    else if(k==2){              //SELL
    sell s1;
    s1.setUsername(username);
    
    sell_menu:
    cout << "\n+===========================================+\n";
    cout << "|  >>  CROP-MARKET : SELLER MENU      <<  |\n";
    cout << "+===========================================+\n";
    cout << "|                                           |\n";
    cout << "|       >>  1. Add Product                  |\n";
    cout << "|       >>  2. View Orders                  |\n";
    cout << "|       >>  0. Back                         |\n";
    cout << "|                                           |\n";
    cout << "+-------------------------------------------+\n";
    int sell_choice = valint(0, 2, "|  Enter your choice : ");
    cout << "+-------------------------------------------+\n";

    if(sell_choice == 1){
        restarts:
        s1.product_info();
        
        cout << "1. Confirm\n2. Add more products\n0. Exit\n";
        int ch = valint(0, 2, "Enter choice: ");

        if (ch == 0) {
            cout << "Your changes will not be saved.\n";
            goto sell_menu;
        }
        else if (ch == 1) {
            cout << "Your changes are saved.\n";
            goto sell_menu;
        }
        else if(ch == 2){
            goto restarts;
        }
    }
    else if(sell_choice == 2){
        s1.vieworders();
        goto sell_menu;
    }
    else if(sell_choice == 0){
        goto frontpage;
    }
}

    else if(k==3){
        string soil, water, temp, season;
        
        bool val = false;
        while(!val){
            cout << "\n+===========================================+\n";
            cout << "|  >>  CROP-MARKET : HELPDESK         <<  |\n";
            cout << "+===========================================+\n";
            cout << "|                                           |\n";
            cout << "|   Share your farm details and we'll       |\n";
            cout << "|   help you get MAXIMUM YIELD!!            |\n";
            cout << "|                                           |\n";
            cout << "+-------------------------------------------+\n";
            cout << "| Soil Fertility (h=High  m=Moderate  l=Low) : ";
            cin.ignore();  
            cin >> soil;
            cout << "+-------------------------------------------+\n";
            cout << "| Water Supply   (h=High  m=Moderate  l=Low) : ";
            cin >> water;
            cout << "+-------------------------------------------+\n";
            cout << "| Temperature    (h=High  m=Moderate  l=Low) : ";
            cin >> temp;
            cout << "+-------------------------------------------+\n";
            cout << "| Season     (m=Monsoon  w=Winter  s=Summer) : ";
            cin >> season;
            cout << "+-------------------------------------------+\n";

            soil[0] = tolower(soil[0]);
            water[0] = tolower(water[0]);
            temp[0] = tolower(temp[0]);
            season[0] = tolower(season[0]);

            if ((soil == "h" || soil == "m" || soil == "l") &&
            (water == "h" || water == "m" || water == "l") &&
            (temp == "h" || temp == "m" || temp == "l") &&
            (season == "m" || season == "w" || season == "s")) {
                val = true;
            } 
            else {
            cout << "| Invalid input(s)! Please enter all values again.\n";
            cout << "+-------------------------------------------+\n";
            }
        }

        rec h1(soil, water, temp, season);
        h1.display();
        
        cout << "+-------------------------------------------+\n";
        cout << "|  Press Enter to continue...               |\n";
        cout << "+-------------------------------------------+\n";
        cin.ignore();
        cin.get();
        
        goto frontpage;
    }

    else if(k==4){
        string un, crname, qn, amt,type;
        bool hisav = false;
        int i = 1;

        cout << "\n+===========================================+\n";
        cout << "|  >>  CROP-MARKET : PURCHASE HISTORY <<  |\n";
        cout << "+===========================================+\n";
        cout << "|                                           |\n";
        cout << "|   User : " << username << "\n";
        cout << "|                                           |\n";
        cout << "|   #       Type        Crop        Quantity    Amount    |\n";
        cout << "+-------------------------------------------+\n";

        ifstream info14("history.txt");
        while(getline(info14, type, ',') &&
            getline(info14, un, ',') &&
            getline(info14, crname, ',') &&
            getline(info14, qn, ',') &&
            getline(info14, amt)){
            if(un == username){
                hisav = true;
                if(crname=="1") crname="Wheat";
                if(crname=="2") crname="Jowar";
                if(crname=="3") crname="Bajra";
                if(crname=="4") crname="Maize";
                if(crname=="5") crname="Barley";

                cout << "|   " << i << ".   "
                    <<type<<"         "<< crname << "        "
                    << qn << "kg        "
                    << "Rs." << amt << "\n";
                i++;
            }
        }
        info14.close();

        if(hisav == false){
            cout << "|                                           |\n";
            cout << "|     ** No Purchases Yet **                |\n";
        }

        cout << "|                                           |\n";
        cout << "+-------------------------------------------+\n";
        cout << "|  Press Enter to continue...               |\n";
        cout << "+-------------------------------------------+\n";
        cin.ignore();
        cin.get();
        goto frontpage;
    }

    return 0;
}