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
        int choice, amount;
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

            if(choice==0){
                return;
            }
            
            //display details about selected product

        }


        void transaction(int& t2){
            int temp1;
            cout<<"Do you want to buy this product?\n 1. Yes \n2. No ";
            cin>>temp1;

            if(temp1==1){
                cout<<"How much do you wish to buy?";
                cin>>quant;

                if(quant>100){
                    amount=1000*quant;    // Temporarily replacing pLast by 1000
                }
                else if(quant>50){
                    amount=900*quant;     // Temporarily replacing pLast by 900
                }
                else{
                    amount=800*quant;      // Temporarily replacing pLast by 800
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
        }
};


int main() {
    int k, t2;
    frontpage:
    cout<<"Buy or Sell";
    //  (Temporary)   1. Buy    2. Sell
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

    }
    return 0;
}