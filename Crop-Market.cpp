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



            //display details about selected product

        }


        void transaction(){
            int temp1, temp2;
            cout<<"Do you want to buy this product?\n 1. Yes \n2. No ";
            cin>>temp1;

            if(temp1==1){
                cout<<"How much do you wish to buy?";
                cin>>quant;

                if(q>100){
                    amount=pLast*q;
                }
                else if(q>50){
                    amount=p100*q;
                }
                else{
                    amount=p50*q;
                }

                cout<<"Total amount = "<<amount;

                cout<<"\n1. Add to cart and buy more \n2. Checkout \n3. Discard this item";
                cin>>temp2;

                if(temp2==1){
                    cart.push_back({choice, quant, amount});
                    goto ; //to be decided
                }
                else if(temp2==2){
                    cart.push_back({choice, quant, amount});
                    return;
                }
                else if(temp2==3){
                    goto ; //to be decided
                }


            }
    
        }



};


int main() {
    

    return 0;
}