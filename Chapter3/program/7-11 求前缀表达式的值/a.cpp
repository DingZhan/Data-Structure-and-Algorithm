#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

/*前缀表达式求值:
  要从右至左扫描表达式，如果是数字，则放到数据栈中；
  若为运算符，则从数据栈中弹出两个数据，进行计算，然后将计算结果再次压入数据栈；
  扫描到表达式最左端时扫描结束，最后数据栈中唯一的数据就是运算的最终结果。
*/
int main()
{
    //从一行字符串中提取的符号数组
    std::vector<string> tokens;
    //数据栈
    std::stack<double> dataStack;
    string lineStr, token;
    double data1, data2;

    //得到一行字符串
    std::getline(cin, lineStr);
    //用输入字符串流格式化字符串
    istringstream iss(lineStr);
    //读取每个符号（字符串，以空格分隔）
    while(true)
    {
        //读取一个符号（字符串）
        iss>>token;
        //如果读取失败，表明读取结束
        if(iss.fail())
            break;
        //把读取的符号加入符号数组
        tokens.push_back(token);
    }
    int i;
    //从右至左解析符号
    for(i=(int)tokens.size()-1; i>=0; --i)
    {
        //如果当前符号串是四则运算符，则需要从数据栈中弹出两个数据进行计算
        if(tokens[i].size()==1 &&(
           tokens[i][0]=='+'||
           tokens[i][0]=='-'||
           tokens[i][0]=='*'||
           tokens[i][0]=='/'))
        {
            //如果数据栈中没有两个数，则输入的是非法前缀表达式，清除堆栈然后退出循环
            if(dataStack.size()<2)
            {
                //error happened, so clear stack
                while(!dataStack.empty())
                    dataStack.pop();
                break;
            }
            //从数据栈中弹出两个数据进行计算
            data1 = dataStack.top();
            dataStack.pop();
            data2 = dataStack.top();
            dataStack.pop();
            if(tokens[i][0]=='+')
                data1 = data1+data2;
            else if(tokens[i][0]=='-')
                data1 = data1-data2;
            else if(tokens[i][0]=='*')
                data1 = data1*data2;
            else if(tokens[i][0]=='/')
            {
                if(data2==0)
                {
                    //除零异常，有一个测试点，所以必须处理该异常
                    //清除堆栈然后退出循环
                    //error happened, so clear stack
                    while(!dataStack.empty())
                        dataStack.pop();
                    break;
                }
                data1 = data1/data2;
            }
            //把计算的数据结果压回数据堆栈
            dataStack.push(data1);
            //继续下一次符号解析
            continue;
        }
        else
            //当前符号是数字，把该数字压入数据堆栈
            dataStack.push(atof(tokens[i].c_str()));
    }

    //如果最终数据堆栈中元素个数不为1，则说明是非法前缀表达式
    if(dataStack.size()!=1)
        cout<<"ERROR"<<endl;
    else
        cout<<std::fixed<<std::setprecision(1)<<dataStack.top()<<endl;

    return 0;
}
