#include<iostream>
#include<cstdlib>
#include<ctime>
#include<string>
#include<vector>
#include<map>
using namespace std;

class Stock{
protected:
    string symbol;
    float price;
public:
    Stock(){};  //Default  constructor

//Parameterised constructor to set the price and symbol of a stock  
    Stock(string sym, float pri){
        symbol=sym;
        price=pri;
        srand(time(nullptr)); //Seed for random number generation.
    }

//Virtual function to display stock price
    virtual void display(){
        cout<<"Symbol: "<<symbol<<", Price: "<<price;
    }

//Virtual function to update stock prices. This is overridden in future classes
    virtual void update_price() = 0;
    float show_price(){
        return price;
    }
};

//class to manage trade of a single stock
class Trade: public Stock{
    int quantity;
public:
    Trade(){};
    Trade(string sy, float pr,int q): Stock(sy,pr){
        quantity=q;
    }

//display  total number of shares being traded
    void display(){
        Stock::display();
        cout<<", Quantity: "<<quantity<<endl;
    }
    //calculate total value of traded shares
    float get_val(){
        return  price*quantity;
    }

//Function to update stock prices with random percentage change
    void update_price() override{
        float percent_change=(rand()%11-5)/100.0;
        price*=(1+percent_change);
        cout<<"*************New price of "<<symbol<<" is "<<price<<"*************"<<endl;
    }
    string get_symbol(){
        return symbol;
    }

//Function to set the quantity of a stock
    void set_quantity(int q){
        quantity=q;
    }
    int get_quantity(){
        return quantity;
    }
    float get_price(){
        return price;
    }
};

//Class representing a portfolio of stocks
class Portfolio: protected Trade{
    map<string, Trade*> stocks; //Map to store the stocks
public:
    Portfolio(){};
    void add_stock(Trade *stock){
        stocks[stock->get_symbol()]= stock; //insert the stock at the corresponding symbol
    }

    //Function to obtain total stocks worth
    float get_total_value(){
        float total=0.0;
        for(auto const& i: stocks){
            total+=i.second->get_val();
        }
        return total;
    }

    //function to display available stocks
    void display_portfolio(){
        cout<<"Portfolio Contents: "<<endl;
        for (auto const& i : stocks){
            i.second->display();
        }
        //CAll the get_total_value to display total value of stocks
        cout<<endl<<"Total Value of Stock: $"<<get_total_value()<<endl<<endl;
    }


//Function to find a particular stock
    Trade* find_stock(string& symbol){
        auto it = stocks.find(symbol);
        if (it != stocks.end()) {
            return it->second; //return a pointer to the stock if found
        }
        return nullptr;
    }

//Function to update quantity of a stock
    void update_quantity(string symbol, int new_quantity){
        Trade *stock = find_stock(symbol);
        if(stock) stock->set_quantity(new_quantity); // update stock quantity if found
            else cout << "Stock " << symbol << " not found." << endl;
    }

//Function to buy a stock
    string buy(){
        string buy_stock;
        int req;
        cout<<"Choose Stock to buy: ";
        cin>>buy_stock;
        //check if the stock is available
        if(find_stock(buy_stock)){
            Trade *stock = find_stock(buy_stock);
            cout<<"Enter quantity: ("<<stock->get_quantity()<<" available)";
            cin>>req;
            update_quantity(buy_stock, stock->get_quantity()-req);
            //total purchase value
            cout<<"Total cost: $"<<stock->get_price()*req;
        }
        else{
            cout<<"Stock not available. Try again.: "<<endl;
            buy();
        }
        return buy_stock;
    }

//Function to sell a stock
    string sell(){
        string sell_stock;
        int n;
        cout << "Enter stock to sell: ";
        cin>>sell_stock;
        cout<<"Enter quantity: ";
        cin>>n;
        if(find_stock(sell_stock)){
            Trade *stock = find_stock(sell_stock);
            update_quantity(sell_stock, stock->get_quantity()+n);
        }
        else{
            float new_price;
            cout<<"Stock not in database. Enter price for this stock: ";
            cin>>new_price;
            Trade* new_stock = new Trade(sell_stock, new_price, n);
            add_stock(new_stock);
        }
        cout<<"Sold! Thank you for selling!"<<endl;
        return sell_stock;
    }

};

//
//
//

int main(){
//Create a portfolio object and populate with some stock objects
    Portfolio prtf;
    Trade* stock1 = new Trade("MSFT", 428.86, 45);
    Trade* stock2 = new Trade("AMZN", 178.94, 20);
    Trade* stock3 = new Trade("TSLA", 171.20, 80);
    Trade* stock4 = new Trade("META", 509.23, 56);

//Add stocks to the map
    prtf.add_stock(stock1);
    prtf.add_stock(stock2);
    prtf.add_stock(stock3);
    prtf.add_stock(stock4);
    cout<<"Initial stock Prices"<<endl;
    prtf.display_portfolio();

//update price and quantity of amzn
    stock2->update_price();
    prtf.update_quantity("AMZN", 18);
    cout<<"\nAfter updating price and quantity\n";
    prtf.display_portfolio();

//Buy or sell stocks using switch cases
    int action;
    string item, opt;
    do{
        cout<<"Choose an action:\nEnter 1 to BUY\nEnter 2 to SELL"<<endl;
        cin>>action;
        switch(action){
            case 1:
                item = prtf.buy();
                cout<<"Do you wish to make another transaction?(Y/N)"<<endl;
                cin>>opt;
                break;

            case 2:
               item = prtf.sell();
               cout<<"Do you wish to make another transaction?(Y/N)?"<<endl;
               cin>>opt;
               break;

            default :cout<<"Invalid Action!";
            exit(0);

        }
    } while(opt=="y" ||opt=="Y");
    
    if(action==1) cout<<"\nAfter buying "<<item<<endl;
    else cout<<"\nAfter selling "<<item<<endl;
    prtf.display_portfolio();
    return 0;
}
