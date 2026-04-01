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

            string cropname,sellid,grade,quant,r50,r100,r;
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
                      getline(info7,quant,',') &&
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
                        cout<<"\n"<<"Product ID : "<<sellid<<"\n"<<"Maize\n"<<"Grade : "<<grade<<"\n"<<
                        "Quantity available : "<<quant<<" kg\n"<<"Rate below 50kg : "<<r50<<"\n"<<
                        "Rate between 50-100kg : "<<r100<<"\n"<<"Rate above 100kg : "<<r<<endl;
                    }
                }
            }  
        }

        int getchoice(){        //Getter for choice
            return choice;
        }



        void transaction(){
            string prid;
            string id,grad,quant,r50,r100,r,cropname;
            cout<<"Enter the Product ID which you wish to buy : ";
            cin>>prid;
            
            
                cout<<"How much do you wish to buy? : ";
                cin>>quant;
                int quantity=stoi(quant);
                
                ifstream info9("cropinfo.txt");
                while(getline(info9,id,',') && 
                      getline(info9,cropname,',') && 
                      getline(info9,grad,',') && 
                      getline(info9,quant,',') &&
                      getline(info9,r50,',') &&
                      getline(info9,r100,',') &&
                      getline(info9,r)){
                        if(prid==id){
                            int num1=stoi(r50);
                            int num2=stoi(r100);
                            int num3=stoi(r);
                            
                            
                if(quantity>100){
                    amount=num3*quantity;   
                }
                else if(quantity>50){
                    amount=num2*quantity;    
                }
                else{
                    amount=num1*quantity;    
                
                }


                        }
                      }
                      info9.close(); 



                

                cout<<"Total amount = "<<amount;

                cout<<"\n1. Add to cart and buy more \n2. Checkout \n3. Discard this item \n";
                cin>>temp2;
            
                if(temp2==1){
                    cart.push_back(vector<int>{choice, quantity, amount});
                    ofstream info13("history.txt",ios::app);
                    info13<<username<<","<<choice<<","<<quantity<< "," << amount<<"\n";

                    ifstream in("cropinfo.txt");
                    ofstream out("temp.txt");

                    string line;

                    while (getline(in, line)) {
                        stringstream ss(line);

                        string f1, f2, f3, f4, rest;

                        // Read fields
                        getline(ss, f1, ','); // id
                        getline(ss, f2, ','); // cropname
                        getline(ss, f3, ',');
                        getline(ss, f4, ','); // quant

        

                        if (f1 == prid) {
                            int quant = stoi(f4);
            

                            if (quant - quantity == 0) {
                                f2 = "0";   // cropname = 0
                            } 
                            else {
                                quant -= quantity;
                                f4 = to_string(quant);
                            }
                        }   

                        // Write updated data
                        out << f1 << "," << f2 << "," << f3 << "," << f4;

        
        


        



                        // Write remaining fields
                        while (getline(ss, rest, ',')) {
                            out << "," << rest;
                        }

                        out << endl;
                    }

                    in.close();
                    out.close();

                    remove("cropinfo.txt");
                    rename("temp.txt", "cropinfo.txt");



                   return;
                }
                
                else if(temp2==2){
                    cart.push_back(vector<int>{choice, quantity, amount});
                    ofstream info13("history.txt",ios::app);
                    info13<<username<<","<<choice<<","<<quantity<< "," << amount<<"\n";

                    ifstream in("cropinfo.txt");
                    ofstream out("temp.txt");

                    string line;

                    while (getline(in, line)) {
                        stringstream ss(line);

                        string f1, f2, f3, f4, rest;

                        // Read fields
                        getline(ss, f1, ','); // id
                        getline(ss, f2, ','); // cropname
                        getline(ss, f3, ',');
                        getline(ss, f4, ','); // quant

        

                        if (f1 == prid) {
                            int quant = stoi(f4);
        
                            if (quant - quantity == 0) {
                                f2 = "0";   // cropname = 0
                            } 
                            else {
                                quant -= quantity;
                                f4 = to_string(quant);
                            }
                        }

                        // Write updated data
                        out << f1 << "," << f2 << "," << f3 << "," << f4;

    

                        // Write remaining fields
                        while (getline(ss, rest, ',')) {
                            out << "," << rest;
                        }

                        out << endl;
                    }

                    in.close();
                    out.close();

                    remove("cropinfo.txt");
                    rename("temp.txt", "cropinfo.txt");



                   return;
                }
                
                else if(temp2==3){
                    return;
                }
                
              
                else{
                    cout<<"Invalid choice"<<endl;
                }
                return;
        }


        void payment() {
            char conf;
            
            disp_cart();
                      
            //cout<<"Select payment method (1. UPI     2. Card )";      SHOULD WE IMPLEMENT THIS and HOW??


            confirmation:
            cout<<"Confirm Payment? (Y/N) : " ;
            cin>>conf;
            
            switch (conf) {

                case 'Y':
                case 'y':
                    cout<<"Payment Successful!";
                    //something
                     break;

                case 'N':
                case 'n':
                    return;
            
                default:
                    cout<<"Invalid input, retry";
                    goto confirmation;
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
            cout<<"\nTotal Amount = "<<total<<"\n\n";
            
            }
        }
};


class sell : public login {
private:
    int p, quantity, p50 = 0, p100 = 0, pLast = 0,sellid=1000;
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
    cin >> p50;

    if (quantity > 50) {
        cout << "Enter price 50-100kg : ₹";
        cin >> p100;
    } else p100 = 0;

    if (quantity > 100) {
        cout << "Enter price above 100kg : ₹";
        cin >> pLast;
    } else pLast = 0;


    ofstream cinfo("cropinfo.txt", ios::app);

    cinfo << id << ","
          << p << ","
          << grade << ","
          << quantity << ","
          << p50 << ","
          << p100 << ","
          << pLast << endl;

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


    int k;
    frontpage:
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

       b1.transaction();

if(b1.temp2 == 1){
    goto restartb;   // add more items
}
else if(b1.temp2 == 2){
    b1.payment();    // checkout
    goto loginpage;
}
else if(b1.temp2 == 3){
    goto restartb;   // discard and restart
}
else{
    cout<<"Invalid input\n";
    goto restartb;
}
        goto loginpage;   
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
} else if(k==4){
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
                        
                        }
                        if(hisav==true){
                            i++;

                        }
                        
                        
                      }if(hisav==false){
                            cout<<"\n**** No Purchases yet.... *****\n";
                        }

}  


    return 0;
}
