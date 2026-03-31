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
            cout<<"*Your Order Summary*\n";

            if(cart.size()==0)
                cout<<"Your Cart is empty\n";
            else{
                cout<<"     Product ID      Quantity        Amount\n";
                for (int i=0; i<cart.size(); i++){
                    cout<<(i+1)<<".        "<<cart[i][0]<<"            "<<cart[i][1]<<"          ₹ "<<cart[i][2]<<"\n";
                
                    total+=cart[i][2];

            }
            cout<<"Total Amount = "<<total<<"\n";
            
            }
        } 
};