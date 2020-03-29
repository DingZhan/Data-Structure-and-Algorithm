#include <stdio.h>

#define MAX_N 10

#define TOL 1.0e-6
#define ERROR 1000000
double Calculate(double a, double b, char op)
{
    double s;
    switch(op)
    {
    case '+':
        s = a+b;
        break;
    case '-':
        s = a-b;
        break;
    case '*':
        s = a*b;
        break;
    case '/':
        if(fabs(b)<TOL)
            return ERROR;
        s = a/b;
        break;
    default:
        break;
    }
    return s;
}
//1 2 3
//((c1 op1 c2) op2 c3) op3 c4
int TwentyFour_Solution1(int cards[4], char ops[3])
{
    double result, tol=1.0e-6;
    result = Calculate(cards[0], cards[1], ops[0]);
    if(result==ERROR)
        return 0;
    result = Calculate(result, cards[2], ops[1]);
    if(result==ERROR)
        return 0;
    result = Calculate(result, cards[3], ops[2]);
    if(result==ERROR)
        return 0;
    if(fabs(result-24)<TOL)
    {
        printf("((%d%c%d)%c%d)%c%d\n", cards[0], ops[0], cards[1],
               ops[1], cards[2], ops[2], cards[3]);
        return 1;
    }
    return 0;
}

//1 3 2
//(c1 op1 c2) op2 (c3 op3 c4)
int TwentyFour_Solution2(int cards[4], char ops[3])
{
    double result1, result2, tol=1.0e-6;
    result1 = Calculate(cards[0], cards[1], ops[0]);
    if(result1==ERROR)
        return 0;
    result2 = Calculate(cards[2], cards[3], ops[2]);
    if(result2==ERROR)
        return 0;
    result1 = Calculate(result1, result2, ops[1]);
    if(result1==ERROR)
        return 0;
    if(fabs(result1-24)<TOL)
    {
        printf("(%d%c%d)%c(%d%c%d)\n", cards[0], ops[0], cards[1],
               ops[1], cards[2], ops[2], cards[3]);
        return 1;
    }
    return 0;
}

//2 1 3
//(c1 op1 (c2 op2 c3)) op3 c4
int TwentyFour_Solution3(int cards[4], char ops[3])
{
    double result, tol=1.0e-6;
    result = Calculate(cards[1], cards[2], ops[1]);
    if(result==ERROR)
        return 0;
    result = Calculate(cards[0], result, ops[0]);
    if(result==ERROR)
        return 0;
    result = Calculate(result, cards[3], ops[2]);
    if(result==ERROR)
        return 0;
    if(fabs(result-24)<TOL)
    {
        printf("(%d%c(%d%c%d))%c%d\n", cards[0], ops[0], cards[1],
               ops[1], cards[2], ops[2], cards[3]);
        return 1;
    }
    return 0;
}

//2 3 1
//c1 op1 ((c2 op2 c3) op3 c4)
int TwentyFour_Solution4(int cards[4], char ops[3])
{
    double result, tol=1.0e-6;
    result = Calculate(cards[1], cards[2], ops[1]);
    if(result==ERROR)
        return 0;
    result = Calculate(result, cards[3], ops[2]);
    if(result==ERROR)
        return 0;
    result = Calculate(cards[0], result, ops[0]);
    if(result==ERROR)
        return 0;
    if(fabs(result-24)<TOL)
    {
        printf("%d%c((%d%c%d)%c%d)\n", cards[0], ops[0], cards[1],
               ops[1], cards[2], ops[2], cards[3]);
        return 1;
    }
    return 0;
}

//3 2 1
//c1 op1 (c2 op2 (c3 op3 c4))
int TwentyFour_Solution5(int cards[4], char ops[3])
{
    double result, tol=1.0e-6;
    result = Calculate(cards[2], cards[3], ops[2]);
    if(result==ERROR)
        return 0;
    result = Calculate(cards[1], result, ops[1]);
    if(result==ERROR)
        return 0;
    result = Calculate(cards[0], result, ops[0]);
    if(result==ERROR)
        return 0;
    if(fabs(result-24)<TOL)
    {
        printf("%d%c(%d%c(%d%c%d))\n", cards[0], ops[0], cards[1],
               ops[1], cards[2], ops[2], cards[3]);
        return 1;
    }
    return 0;
}

int TwentyFour(int cards[4])
{
    char results[64];
    char tokens[4]= {'+','-','*','/'}, sortTokens[3];
    int sortCards[4];
    int i, j, k, t, s1, s2, s3, numSolutions=0;
    for(i=0; i<4; ++i)
    {
        sortCards[0] = cards[i];
        for(j=0; j<4; ++j)
        {
            if(j==i)
                continue;
            sortCards[1] = cards[j];
            for(k=0; k<4; ++k)
            {
                if(k==i||k==j)
                    continue;
                sortCards[2] = cards[k];
                for(t=0; t<4; ++t)
                {
                    if(t==i || t==j || t==k)
                        continue;
                    sortCards[3] = cards[t];
                    for(s1=0; s1<4; ++s1)
                    {
                        sortTokens[0] = tokens[s1];
                        for(s2=0; s2<4; ++s2)
                        {
                            sortTokens[1] = tokens[s2];
                            for(s3=0; s3<4; ++s3)
                            {
                                sortTokens[2] = tokens[s3];
                                numSolutions+=TwentyFour_Solution1(sortCards, sortTokens);
                                if(numSolutions)
                                    return 1;
                                numSolutions+=TwentyFour_Solution2(sortCards, sortTokens);
                                if(numSolutions)
                                    return 1;
                                numSolutions+=TwentyFour_Solution3(sortCards, sortTokens);
                                if(numSolutions)
                                    return 1;
                                numSolutions+=TwentyFour_Solution4(sortCards, sortTokens);
                                if(numSolutions)
                                    return 1;
                                numSolutions+=TwentyFour_Solution5(sortCards, sortTokens);
                                if(numSolutions)
                                    return 1;
                            }
                        }
                    }
                }
            }
        }
    }
    return numSolutions;
}

int main()
{
    int cards[4];
    int i, solutions;
    for(i=0; i<4; ++i)
        scanf("%d", cards+i);
    solutions = TwentyFour(cards);
    if(solutions==0)
        printf("-1\n");
    return 0;
}
