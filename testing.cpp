#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace std;


class login {
protected:
    unordered_map<string, string> users;
    string password;


public:
string username;
    bool run() {
        

        while (true) {
            cout << "WELCOME\n1. Log in\n2. Sign up\n0. Exit\n";
            cout << "Choose option: ";
            int a, b;
            cin >> a;

            switch (a) {
                case 1: {
                    reenter:
                    string storedname,storedpassword;
                    cout << "Enter username: ";
                    cin.ignore();
                    getline(cin,username);
                    cout << "Enter password: ";
                    cin >> password;

                    ifstream info("userinfo.txt");
                    bool isCorrect=false;
                    while(getline(info,storedname,',') && 
                          getline(info,storedpassword)){

                    if (storedname==username && storedpassword==password) {
                        cout << "Hello " << username << "!! Welcome Back\n";
                        
                        isCorrect=true;
                        return true;
                        
                    } 
                }
                   if(isCorrect==false){
                    int b;

                    cout<<"Incorrect username or password...."<<endl;
                    cout<<"1.Retry\n0.Exit\n";
                    cout<<"Enter choice : ";
                    cin>>b;
                    if(b==1){
                        goto reenter;
                    }else break;
                    
                   }
                    
                
                break;
            }
                

                case 2: {
                    cout << "Enter username: ";
                    cin.ignore();
                    getline(cin,username);

                    bool passwordsMatch = false;
                    do {
                        cout << "Enter password: ";
                        cin >> password;
                        cout << "Reenter password: ";
                        string password_re;
                        cin >> password_re;

                        if (password == password_re) {
                            passwordsMatch = true;
                            users[username] = password;
                            cout << "Your account has been created\n";
                            ofstream info("userinfo.txt",ios::app);
                            info<<username<<","<<password<<endl;

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

    public:
        
        int temp2=3, temp1;
        vector<vector<int>> cart;  //{'prdt id or choice', 'quantity', 'amount'}

        void disp_list(){
            cout<<"Select the desired product :\n1.Wheat\n2.Jowar\n3.Bajra\n4.Maize\n5.Barley\n( -1. EXIT     0. Visit Cart )\n";
            cout<<"Enter your choice : ";
            cin>>choice;

            string cropname,sellid,grade,quant_str,r50,r100,r;
            bool isAvailable=false;

            ifstream info7("cropinfo.txt");
            

            if(choice==0){
                disp_cart();
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
                
                if(isAvailable){
                    transaction();
                }
                else{
                    cout<<"Product not available!\n";
                }
            }  
        }

        int getchoice(){        //Getter for choice
            return choice;
        }

        void transaction(){
            cout<<"\nSelect what you want to do?\n(1. Buy Bulk 2. Buy Sample 3. Back) : ";
            cin>>temp1;
            

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
                    
                    cout<<"How much do you wish to buy? : ";
                    cin>>quant;
                    
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
                    
                    cout<<"Total amount = ₹"<<amount<<endl;
                    
                    cout<<"\n1. Add to cart and buy more \n2. Checkout \n3. Discard this item \n";
                    cout<<"Enter your choice: ";
                    cin>>temp2;
                    
                    if(temp2==1){
                        cart.push_back({stoi(prid), quantity, amount});
                        ofstream info13("history.txt",ios::app);
                        info13<<username<<","<<prid<<","<<quantity<< "," << amount<<"\n";
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
                        info13<<username<<","<<prid<<","<<quantity<< "," << amount<<"\n";
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
                        
                        payment(prid, cart);
                    }
                    else if(temp2==3){
                        return;
                    }
                    break;
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
            
            // Ask user for Product ID
            cout<<"Enter the Product ID for sample purchase : ";
            cin>>prid;
            
            // Verify and get product details
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
                    int num3 = stoi(r);
                    amount = num3 * 10;  // 10kg sample
                    
                    cout<<"\nProduct Found!\n";
                    cout<<"Crop: "<<cropname<<"\n";
                    cout<<"Grade: "<<grad<<"\n";
                    cout<<"Sample amount is 10kg\n";
                    cout<<"Total amount = ₹"<<amount<<endl;
                    
                    // Check if enough stock for sample
                    if(10 > stoi(quant_str)){
                        cout<<"Insufficient stock for sample! Only "<<quant_str<<" kg available.\n";
                        info8.close();
                        return;
                    }
                    
                    cout<<"\n1. Checkout     2. Discard this item \n";
                    cout<<"Enter your choice: ";
                    cin>>temp2;
                    
                    if(temp2==1){
                        // Update inventory for sample purchase
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
                        
                        // Save to history
                        ofstream info13("history.txt",ios::app);
                        info13<<username<<","<<prid<<","<<10<< "," << amount<<"\n";
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

        void payment(string prid, vector<vector<int>> cart){
            disp_cart();

            char conf;
            confirmation_b:
            cout<<"Confirm Payment? (Y/N) : " ;
            cin>>conf;
            
            switch (conf) {
                case 'Y':
                case 'y':
                    cout<<"Payment Successful!\n\n";
                    cart.clear();
                    break;
                case 'N':
                case 'n':
                    return;
                default:
                    cout<<"Invalid input, retry\n";
                    goto confirmation_b;
            }   
        }

        void payment(string prid){
            cout<<"\n         -Sample amount is 10kg- \n";
            cout<<"     Product ID      Quantity        Amount\n";
            cout<<"        "<<prid<<"         10kg(default)     ₹ "<<amount<<"\n";

            char conf;
            confirmation_s:
            cout<<"Confirm Payment? (Y/N) : " ;
            cin>>conf;
            
            switch (conf) {
                case 'Y':
                case 'y':
                    cout<<"Payment Successful!\n\n";
                    break;
                case 'N':
                case 'n':
                    return;
                default:
                    cout<<"Invalid input, retry\n";
                    goto confirmation_s;
            }   
        }
        
        // Checkout method for cart
        void payment(){
            if(cart.empty()){
                cout<<"Cart is empty! Nothing to checkout.\n";
                return;
            }
            disp_cart();
            
            char conf;
            confirmation_c:
            cout<<"Confirm Payment? (Y/N) : " ;
            cin>>conf;
            
            switch (conf) {
                case 'Y':
                case 'y':
                    cout<<"Payment Successful!\n\n";
                    cart.clear();  // Clear cart after successful payment
                    break;
                case 'N':
                case 'n':
                    return;
                default:
                    cout<<"Invalid input, retry\n";
                    goto confirmation_c;
            }
        }

        void disp_cart(){
            int total=0;
            cout<<"\n     *****Your Order Summary*******\n\n";

            if(cart.size()==0)
                cout<<"Your Cart is empty\n";
            else{
                cout<<"     Product ID        Quantity        Amount\n";
                for (int i=0; i<cart.size(); i++){
                    cout<<(i+1)<<".       "<<cart[i][0]<<"              "<<cart[i][1]<<"              "<<cart[i][2]<<"\n";
                    total+=cart[i][2]; 
                }
                cout<<"\nTotal Amount = ₹"<<total<<"\n\n";
            }
        }
};


class sell : public login {
private:
    int p, quantity, r50 = 0, r100 = 0, r = 0,sellid=1000;
    char grade;
    string line;


public:
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
    bool wrong=false;
    do{ 
        if(wrong) cout<<"Invalid input, try again\n";
        cout << "Enter product number ( 1.Wheat 2.Jowar 3.Bajra 4.Maize 5.Barley ) : ";
        cin >> p;
        wrong=true;
    } while(p<1 || p>5);
    
    cout << "Enter product grade:\nA: High\nB: Average\nC: Low\n";
    cin >> grade;

    cout << "Enter quantity (kg): ";
    cin >> quantity;

    cout << "Enter price up to 50kg : ₹";
    cin >> r50;

    if (quantity > 50) {
        cout << "Enter price 50-100kg : ₹";
        cin >> r100;
    } else r100 = 0;

    if (quantity > 100) {
        cout << "Enter price above 100kg : ₹";
        cin >> r;
    } else r = 0;


    ofstream cinfo("cropinfo.txt", ios::app);

    cinfo << id << ","
          << p << ","
          << grade << ","
          << quantity << ","
          << r50 << ","
          << r100 << ","
          << r << endl;

    cinfo.close();

    cout << "\n Product added successfully with ID: " << id << endl;
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

int calculateScore(const Crop& c, const string& soil, const string& water,
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



int main() {
    string username;

    loginpage:              //LOGIN
    login l1;
    if(!l1.run())
        return 0;       //Exit Program

    username=l1.getusername();      

    frontpage:
    int k;
    cout<<"How can we help you today? :)\n( 1. Buy     2. Sell     3. HelpDesk    4.History    0. EXIT ) : ";
    cin>>k;

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
            // Cart was displayed, continue shopping
            goto restartb;
        }
        else {
            b1.transaction();

            if(b1.temp1==3)
                goto restartb;
            
            
            // After transaction, check what to do
            if(b1.temp2 == 1){
                goto restartb;   // Add more items
            }
            else if(b1.temp2 == 2){
                b1.payment();    // Checkout and pay
                goto frontpage;   // Return to main menu
            }
            else if(b1.temp2 == 3){
                goto restartb;   // Discard and restart
            }
            else{
                cout<<"Invalid input\n";
                goto restartb;
            }
        }
    }

    else if(k==2){              //SELL
         sell s1;
         int ch;
        restarts:
            s1.product_info();
            
            cout << "1. Confirm\n2. Add more products\n0. Exit\n";
            cin >> ch;

        if (ch == 0) {
            cout << "Your changes will not be saved.\n";
            cout << "Press 0 to continue.\n";
            goto frontpage;
        }
        else{
             // add data to file system
            if (ch == 1) {
                cout << "Your changes are saved.\n";
                goto frontpage;
            }
            else if(ch == 2)
                goto restarts;
        }
    }

    else if(k==3){              //HELPDESK
        vector<Crop> crops;
        crops.push_back(Crop("Rice", "high", "high", "high", "monsoon"));               
        crops.push_back(Crop("Wheat", "high", "moderate", "moderate", "winter"));
        crops.push_back(Crop("Maize", "moderate", "moderate", "moderate", "summer"));
        crops.push_back(Crop("Millets", "low", "low", "high", "summer"));
        crops.push_back(Crop("Sugarcane", "high", "high", "high", "monsoon"));

        cout<<"Share your farm details and we'll help you get MAXIMUM YEILD!!\n";

        string soil, water, temp, season;

        cout << "Enter soil fertility: ";  
        cin >> soil;
        cout << "Enter water supply: ";    
        cin >> water;
        cout << "Enter temperature: ";     
        cin >> temp;
        cout << "Enter season: ";          
        cin >> season;

        cout << "\nRecommended Crops:\n";

        for (const Crop& c : crops) {
            int score = calculateScore(c, soil, water, temp, season);
            if (score >= 6)
                cout << c.getName() << " (Score: " << score << ")\n\n\n";
        }   
        goto frontpage;
    } 
    else if(k==4){  //HISTORY
        string un,crname,qn,amt;
        bool hisav=false;
        int i=1;
        cout<<"           Crop            Quantity            Amount\n";
        ifstream info14("history.txt");
        while(getline(info14,un,',') && 
              getline(info14,crname,',') && 
              getline(info14,qn,',') && 
              getline(info14,amt)){
            if(un==username){
                hisav=true;
                if(crname=="1")crname="Wheat";
                if(crname=="2")crname="Jowar";
                if(crname=="3")crname="Bajra";
                if(crname=="4")crname="Maize";
                if(crname=="5")crname="Barley";
                
                cout<<i<<"."<<"         "<<crname<<"             "<<qn<<"              "<<amt<<"\n";
                i++;
            }
        }
        info14.close();
        
        if(hisav==false){
            cout<<"\n**** No Purchases yet.... *****\n";
        }
        cout<<"\nPress any key to continue...";
        cin.ignore();
        cin.get();
        goto frontpage;
    }

    return 0;
}
