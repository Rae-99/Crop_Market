import java.util.*;
public class sell {
    Scanner sc =new Scanner(System.in);
    int p , quantity ,p50=0,p100=0,pLast=0;
    char grade;
    public static void main()
    {
      int ch;
       Scanner c =new Scanner(System.in);
        sell obj=new sell();
        do{
        obj.product_info();
        obj.price_info();
        System.out.println("1.Confirm.. /n2. ADD MORE PRODUCTS/n 0.exit");
        ch=c.nextInt();
        }
        while(ch==2);
        //do while 
        if( ch==0)
        {
            System.out.println("Your changes will not be saved ");
            System.out.println("press 0 to continue ");
            System.exit(0);
        }
        if(ch==1)
        {
            System.out.println("Your changes are saved");
            //add data to file system
        }
    }

    public void product_info()
    {
    System.out.println("Enter product number ");
  
    // list of product name;
    p=sc.nextInt();
    System.out.println("Enter product grade : /n A:High grade /n B:average grade /n 3:low grade ");
    grade =sc.next().charAt(0);
    System.out.println("Enter quantity you want to sell (in kg)");
    quantity =sc.nextInt();
    }
    public void price_info()
    {
        //display price of each range from file system
       System.out.println("Enter your price for quantity 50 kg (in rupees per kg)");
       p50=sc.nextInt();
       if(quantity>50){
        System.out.println("Enter your price for quantity 50-100 kg (in rupees per kg)");
       p100=sc.nextInt();
       }
       if(quantity >100){
        System.out.println("Enter your price for quantity above 100 kg (in rupees per kg)");
       pLast=sc.nextInt();
       }
    }
}
