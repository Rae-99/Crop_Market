#include <iostream>
#include<string>
#include<vector>

using namespace std;


class user {
    private :
        string username;
        
    public :
};

class buyer {
    private:


    public:
        int amount;
        char choice;
        int quant; //quantity 
        vector<vector<int>> cart;  //{'prdt id or choice', 'quantity', 'amount'}

        void disp_list(){
            // Display list if available prdts; with serial number
            // ex- 1. wheat
            //     2. bajra
            //     3. rajma
            // 

            cout<<"Enter your choice (0 to EXIT) : ";
            cin>>choice;

            if(choice=='E'){
                return;
            }

            else if(choice=='C'){
                disp_cart();
                disp_list();

            }
            
            //else display details about selected product

        }


        void transaction(int& t2){
            int temp1;
            cout<<"Do you want to buy this product?\n 1. Yes \n2. No ";
            cin>>temp1;

            if(temp1==1){
                cout<<"How much do you wish to buy?\n";
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

                cout<<"\n1. Add to cart and buy more \n2. Checkout \n3. Discard this item";
                cin>>t2;

                if(t2==1){
                    cart.push_back({choice, quant, amount});
                    return;
                }
                else if(t2==2){
                    cart.push_back({choice, quant, amount});
                    return;
                }
                else if(t2==3){
                    return;
                }
            }  
        
            else
                return;
        }


        void payment(char& conf){
            
            char conf;
            
            disp_cart();
                      
            //cout<<"Select payment method (1. UPI     2. Card )";      SHOULD WE IMPLEMENT THIS and HOW??


            Confirmation:
            cout<<"Confirm Payment? (Y/N)" ;
            cin>>conf;
            
            switch (conf)
            {
            case 'Y':
                 cout<<"Payment Successful!";
                //something
                break;

            case 'N':
                return;
            
            default:
                cout<<"Invalid input, retry";
                goto Confirmation;
            }




            if(conf=='Y'){
                cout<<"Payment Successful!";
                //something
            }
            
            else if(conf=='N'){
                return;
            }

            else{
                cout<<"Invalid input, retry";

            }
                
    
        }


        void disp_cart(){
            int total=0;
            cout<<"*Your Order Summary*\n";

            if(cart.size()==0)
                cout<<"Your Cart is empty";
            else{
                cout<<"     Product ID      Quantity        Amount ";
                for (int i=0; i<cart.size(); i++){
                    cout<<(i+1)<<". "<<cart[i][1]<<"      "<<cart[i][2]<<"      ₹ "<<cart[i][3]<<"\n";
                
                    total+=cart[i][3];

            }
            cout<<"Total Amount = "<<total<<"\n";
            
            }
    
        }


};


int main() {
    int k, t2; 
    char t3;


    frontpage:
    cout<<"Buy or Sell ( 1. Buy    2. Sell ) : ";    //  (Temporary)
    cin>>k;
    if(k==1){
        buyer b1;

        restart:
        b1.disp_list();
        if(b1.choice==0){
            goto frontpage;
        }

        b1.transaction(t2);
        if(t2==1||t2==3){
            goto restart;
        }

        b1.payment(t3);

    }
    return 0;
}