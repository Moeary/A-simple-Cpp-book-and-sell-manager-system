#include"buyer.hpp"
#include"book.hpp"
class order{
    private:
        static int ordercount;
        int orderID;
        int buyerID;
        int listcount;
        string orderlist[20];
    public:
        order(){
            buyerID=0;
            ordercount++;
            orderID=ordercount;
            listcount=0;
        }
        void setbuyerID(int b_id){
            buyerID=b_id;
        }
        void buy_one_book(string b_id){
            orderlist[listcount]=b_id;
            listcount++;
        }
        void display();
};
void order::display(){
    int i;
    cout<<"Order Information\n\n Order ID:"<<orderID<<endl;
    cout<<"Buyer ID:"<<buyerID<<endl;
    cout<<"Book List:";
    for(int i=0; i<listcount;++i){
        cout<<orderlist[i]<<endl;
    }
}
int order::ordercount=0;
int main(int  argc,char  *argv[]){
    int i=0,j=0;
    int buyerid,flag;
    book *c[2];
    layfolk b1("Ling Xiaocha",1,"Beijing",0);
    honoured_guest b2("Wang Yaoyao",2,.6,"Shanghai",0);
    member b3("Zhao Hongyan",3,5,"Guangzhou",0);
    order o1[20];
    buyer *b[3]={&b1,&b2,&b3};
    book c1("","C++ Programing","Tang Haoqiang","Tsung University",25);
    book c2("A2","Data structure","Xu Tianfeng","Peking University",20);
    c[0]=&c1;c[1]=&c2;
    cout<<"Buyer Information:"<<endl<<endl;
    for(i=0;i<3;++i){
        b[i]->display();
    }
    for(i=0;i<2;++i){
        c[i]->display();
    }
    while(j<2){
        cout<<"Please write down BuyerID"<<endl;
        cin>>buyerid;
        flag=0;
        for(i=0;i<3;++i){
            if(b[i]->getid()==buyerid){
                flag=1;
                break;
            }
            if(!flag){
                cout<<"BuyerID is invaild";
                break;
            }
            else{
                b[i]->setpay(c[0]->getprice());
                b[i]->setpay(c[1]->getprice());
                cout<<endl<<"Buyer need to pay:"<<b[i]->getpay()<<endl<<endl;
                o1[j].setbuyerID(b[i]->getid());
                o1[j].buy_one_book(c[0]->getbook_ID());
                o1[j].buy_one_book(c[1]->getbook_ID());
                o1[j].display();
            }
        }
        ++j;
    }
    return 0;
}