# A-simple-Cpp-book-and-sell-manager-system
一个简单的大作业罢了，鬼画符划过去了
******************************************************************************************************************************
简单描述一下功能就是从三个文件 order.dat book.dat buyer.dat中读取数据

通过文件流的形式传入到对应的vector容器中，后续的一系列操作都围绕这个展开

                        vector<order> 
                        vector<book*>
                        vector<buyer*>
                        
book类存书籍的信息 比如书名作者 价格啥的

buyer存购买者的姓名啥的 同时buyer类下面有三个子类，后续的订单计算会根据这个会员等级计算折扣，比如如果是5级会员就可以打7折来着

order用来存订单数据， 里面包含 购买者的ID，购买书籍的ID，以及购买时间的时间戳

后面再查订单时候就可以通过匹配ID购买者ID来查阅这个购买者在订单系统中所作的所有购买书籍的记录了 //用SQL语言很容易实现，但是C++写这个真的痛苦面具了

然后再根据查阅到的书籍ID，去找到对应的价格并加起来给用buyer内部的计算函数得出实付的价格（比如应付50元，如果是5级会员只要付35元）

然后还有查表 看表，添加数据啥的太简单了，就不过多描述了，自行看代码吧，不会的去问问GPT
 
为了不让界面那么单调还给黑框框改了下颜色 改成蓝底了，不喜欢蓝色的可以去function.hpp里面改一下对应的函数代码

后续有人想修改代码编译调试运行前记得把main函数中的那个逃逸序列给禁用一下否则你连报错信息都看不到来着..........
  
******************************************************************************************************************************
