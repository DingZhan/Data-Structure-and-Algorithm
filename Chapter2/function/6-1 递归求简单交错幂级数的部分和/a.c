//其中一个递归公式
//f(x, n) = f(x, n-1) + (-1)^(n-1)*x^n
//另一个递归公式
//f(x, n) = x + f(x, n-1)*(-x)
//想一想哪个好
double fn( double x, int n )
{
    if(n==1)
        return x;
    return x + fn(x, n-1)*(-x);
}
