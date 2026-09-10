#include<bits/stdc++.h>

using namespace std;

class Item{
    int item_id;
    double cost;
    public:
    Item(int item_id, int cost):item_id(item_id), cost(cost){}
    int getId() const{
        return item_id;
    }
    double getCost() const{
        return cost;
    }
};
class Order{
    vector<Item> cart;
    public:
    void addItem(Item& item){
        cart.push_back(item);
    }
    void removeItem(Item& item){
        //implementation later
    }
    vector<Item> getter() const{
        return cart;
    }
};
class Calculator{
    public:
    double calculateTotal(const Order& order){
      double sum = 0;
      vector<Item> curr = order.getter();
      for( int i=0; i<curr.size(); i++){
        sum += curr[i].getCost();
      }
      return sum;
    }
};
class Sender{
    public:
    virtual void send() = 0;
    virtual ~Sender() = default;
};

class Email:public Sender{
    public:
    void send() override{
        cout<<"Message sent via Email\n";
    }
};
class WhatsApp: public Sender{
    public:
    void send() override{
        cout<<"Message sent via WhatsApp\n";
    }
};

class OrderRepository{
    public:
    virtual void save(const Order& order) = 0;
    virtual ~OrderRepository() = default;
};

class MySQL:public OrderRepository{
    public:
    void save(const Order& order) override{
        cout<<"Saved to MySQL";
    }
};

class InvoiceGenerator{
    public:
    void genratePDFinvoice(const Order& order){
        cout<<"Your order contains "<<order.getter().size()<<" items.\n";
    }
};

class Payment{
    public:
    virtual void pay(double amount) = 0;
    virtual ~Payment() = default;
};

class UPI: public Payment{
    public:
    void pay(double amount) override{
        cout<<amount<<" paid by UPI.\n";
    } 
};
class CreditCard: public Payment{
    public:
    void pay(double amount) override{
        cout<<amount<<" paid by Credit Card.\n";
    }
};
class OrderService{
     Payment& payment;
     Sender& sender;
     Calculator& calculator;
     Order& order;
     InvoiceGenerator& inv;
     OrderRepository& ors;
     public:
     OrderService(Payment& payment, Sender& sender, Calculator& calculator, Order& order, InvoiceGenerator& inv, OrderRepository& ors): payment(payment),sender(sender),calculator(calculator),order(order),inv(inv),ors(ors){}
     void pay(double amount){
        payment.pay(amount);
     }
     void send(){
        sender.send();
     }
     double calculate(){
         return calculator.calculateTotal(order);
     }
     void addItem(Item& item){
        order.addItem(item);
     }
     void removeItem(Item& item){
        //implementation later
     }
     void generatePDFinvoice(){
        inv.genratePDFinvoice(order);
     }
     void save(){
       ors.save(order);
     }
};
int main(){
  Item item1(1,1000),item2(2,2000);
  UPI upi;
  Order order;
  Email email;
  Calculator calculator;
  InvoiceGenerator inv;
  MySQL mysql;

  OrderService os(upi,email,calculator,order,inv,mysql);
  os.addItem(item1);
  os.addItem(item2);
  cout<<"What is the total cost to pay?\n";
  cout<<os.calculate()<<"to pay\n";
  os.pay(os.calculate());
  os.send();
  os.save();
  os.generatePDFinvoice();
 return 0;
}
