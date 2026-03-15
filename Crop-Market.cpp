#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;


class login {
protected:
    unordered_map<string, string> users;
    string username, password;


public:
    bool run() {
        

        while (true) {
            cout << "1. Log in\n2. Sign up\n0. Exit\n";
            cout << "Choose option: ";
            int a;
            cin >> a;

            switch (a) {
                case 1:
                    Reenter:
                    cout << "Enter username: ";
                    cin >> username;
                    cout << "Enter password: ";
                    cin >> password;

                    if (users.count(username) && users[username] == password) {
                        cout << "Hello " << username << "!! Welcome Back\n";
                        return true;
                    } 
                    else {
                        cout << "Incorrect username and password pair\n";
                        goto Reenter;
                    }
                    break;

                case 2: {
                    cout << "Enter username: ";
                    cin >> username;

                    

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

};


class buyer : public login {
    private:
        int amount, choice, quant;

    public:
        
        int temp2=3, temp1;
        vector<vector<int>> cart;  //{'prdt id or choice', 'quantity', 'amount'}

        void disp_list(){
            // Display list if available prdts; with serial number
            // ex- 1. wheat
            //     2. bajra
            //     3. rajma
            // 

            cout<<"Enter your choice ( -1. EXIT     0. Visit Cart )  :  ";
            cin>>choice;


            if(choice==-1){
                return;
            }
            else if(choice==0){
                disp_cart();
                disp_list();
            }
            
            //else display details about selected product

        }

        int getchoice(){        //Getter for choice
            return choice;
        }



        void transaction(){

            cout<<"Do you want to buy this product?\n(1. Yes 2. No) : ";
            cin>>temp1;
            
            if(temp1==1){
                cout<<"How much do you wish to buy? : ";
                cin>>quant;

                if(quant>100){
                    amount=1000*quant;    // Temporarily replacing pLast by 1000
                }
                else if(quant>50){
                    amount=900*quant;     // Temporarily replacing p100 by 900
                }
                else{
                    amount=800*quant;      // Temporarily replacing p50 by 800
                }

                cout<<"Total amount = "<<amount;

                cout<<"\n1. Add to cart and buy more \n2. Checkout \n3. Discard this item \n";
                cin>>temp2;

                if(temp2==1){
                    cart.push_back({choice, quant, amount});
                    return;
                }
                else if(temp2==2){
                    cart.push_back({choice, quant, amount});
                    return;
                }
                else if(temp2==3){
                    return;
                }
            }  
            else
                return;
        }


        void payment() {
            char conf;
            
            disp_cart();
                      
            //cout<<"Select payment method (1. UPI     2. Card )";      SHOULD WE IMPLEMENT THIS and HOW??


            Confirmation:
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
                    goto Confirmation;
            }    
        }


        void disp_cart(){
            int total=0;
            cout<<"*Your Order Summary*\n";

            if(cart.size()==0)
                cout<<"Your Cart is empty\n";
            else{
                cout<<"     Product ID      Quantity        Amount\n";
                for (int i=0; i<cart.size(); i++){
                    cout<<(i+1)<<".        "<<cart[i][0]<<"                "<<cart[i][1]<<"          ₹ "<<cart[i][2]<<"\n";
                
                    total+=cart[i][2];

            }
            cout<<"Total Amount = "<<total<<"\n";
            
            }
        } 
};


class sell : public login {
private:
    int p, quantity, p50 = 0, p100 = 0, pLast = 0;
    char grade;


public:
    void product_info() {
        cout << "Enter product number: ";
        cin >> p;

        cout << "Enter product grade : \n A: High grade \n B: Average grade \n C: Low grade\n";
        cin >> grade;

        cout << "Enter quantity you want to sell (in kg): ";
        cin >> quantity;
    }

    void price_info() {
        // display price of each range from file system
        cout << "Enter your price for quantity up to 50 kg (in rupees per kg): ";
        cin >> p50;

        if (quantity > 50) {
            cout << "Enter your price for quantity 50-100 kg (in rupees per kg): ";
            cin >> p100;
        }

        if (quantity > 100) {
            cout << "Enter your price for quantity above 100 kg (in rupees per kg): ";
            cin >> pLast;
        }
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
    cout<<"Buy or Sell ( 1. Buy     2. Sell     3. HelpDesk     0. EXIT ) : ";
    cin>>k;

    if(k==0)
        goto loginpage;

    else if(k==1){              //BUY
        buyer b1;
        restartb:
        b1.disp_list();
        if(b1.getchoice()==-1){
            goto frontpage;
        }

        b1.transaction();
        if(b1.temp1!=1 && b1.temp1!=2){
            cout<<"Incorrect Input\n";
            goto restartb;
        }


        if(b1.temp2==1||b1.temp2==3){
            goto restartb;
        }

        b1.payment();
        goto loginpage;   
    }


    else if(k==2){              //SELL
         sell s1;
         int ch;
        restarts:
            s1.product_info();
            s1.price_info();

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
            cout << c.getName() << " (Score: " << score << ")\n";
    }
    }


    return 0;
}