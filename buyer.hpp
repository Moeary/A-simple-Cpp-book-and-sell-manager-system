#include"base.h"
class buyer{
    protected:
        string name;
        int buyerID;
        string address;
        double pay;
    public:
        buyer();
        buyer (string n,int b,string a,double p);
        string getbuyname();//取姓名
        string getaddress();//取地址
        double getpay();    //取应付费用
        int getid();        //取购书人编号
        virtual void display()=0;   //显示对象
        virtual string get_type() const = 0;
};
class member:public buyer{
        //会员类
    private:
        int leaguer_grade;
    public:
        member(string n,int b,int l,string a,double p):buyer(n,b,a,p){
            leaguer_grade=l;
        }                               //构造函数
        void display();                 //显示函数
        void setpay(double p);
        int getLeaguerGrade(){
            return leaguer_grade;
        }
        string get_type() const override {
            return "member";
        }      
};
class honoured_guest:public buyer{ //贵宾
        double discount_rate;
    public:
        honoured_guest(string n,int b,double b_r,string a,double p):buyer(n,b,a,p){
            discount_rate=b_r;
        }
        int get_discount_rate(){
            return discount_rate;
        }
        void display();
        void setpay(double p);
        string get_type() const override {
            return "honoured_guest";
        }
};
class layfolk:public buyer{ //普通人
    public:
        layfolk(string n,int b,string a,double p):buyer(n,b,a,p){}
        void display();
        void setpay(double p);
        string get_type() const override {
            return "layfolk";
        }
};
buyer::buyer(string n,int b, string a,double p){ //基类的构造函数
    name=n;
    buyerID=b;
    address=a;
    pay=p;
}
double buyer::getpay(){ //取购书费用
    return pay;
}
string buyer::getaddress(){
    return address;
}
string buyer::getbuyname(){
    return name;
}
int buyer::getid(){
    return buyerID;
}
void member::display(){
    cout<<"Buyer name:"<<name<<endl;
    cout<<"Buyer ID:"<<buyerID<<endl;
    cout<<"Buyer is pro,grade is:"<<leaguer_grade<<endl;
    cout<<"Address:"<<address<<endl;
}
void member::setpay(double p){
    if(leaguer_grade==1){
        pay=0.95*p;
    }
    else if(leaguer_grade==2){
        pay=0.90*p;
    }
    else if(leaguer_grade==3){
        pay=0.85*p;
    }
    else if(leaguer_grade==4){
        pay=0.8*p;
    }
    else if(leaguer_grade==5){
        pay=0.7*p;
    }
    else cout<<"leaguer_grade error!"<<endl;
}
void honoured_guest::display(){
    cout<<"Buyer name:"<<name<<endl;
    cout<<"Buyer ID:"<<buyerID<<endl;
    cout<<"Buyer is pro,discount rate is:"<<discount_rate * 100<<" %"<<endl;
    cout<<"Address:"<<address<<endl;
}
void honoured_guest::setpay(double p){
    pay=(1-discount_rate/100)*p;
}
void layfolk::display(){
    cout<<"Buyer name:"<<name<<endl;
    cout<<"Buyer ID:"<<buyerID<<endl;
    cout<<"Buyer is normal guest"<<endl;
    cout<<"Address:"<<address<<endl;
}
void layfolk::setpay(double p){
    pay=p;
}
