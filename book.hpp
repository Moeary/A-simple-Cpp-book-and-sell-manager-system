#include"base.h"
class book{
    protected:
        string book_ID;
        string book_name;
        string author;
        string publishing;
        double price;
    public:
        book();
        book(string b_id,string b_name,string b_author,string b_publishing,double pr);
        void display();
        string getbook_ID();
        string getbook_name();
        string getauthor();
        string getpublishing();
        double getprice();
};
book::book(){
            book_ID = "";
            book_name = "";
            author = "";
            publishing = "";
            price=0;

}
book::book(string b_id,string b_name,string b_author,string b_publishing,double pr){
            book_ID = b_id;
            book_name = b_name;
            author = b_author;
            publishing = b_publishing;
            price=pr;
}
void book::display(){
    cout<<"Book ID:"<<book_ID<<endl;
    cout<<"Book name:"<<book_name<<endl;
    cout<<"Book author name:"<<author<<endl;
    cout<<"Publishing name:"<<publishing<<endl;
    cout<<"Price:"<<price<<endl;
}
string book::getbook_ID(){
    return book_ID;
}
string book::getbook_name(){
    return book_name;
}
string book::getauthor(){
    return author;
}
string book::getpublishing(){
    return publishing;
}
double book::getprice(){
    return price;
}
