#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
enum constantnumbers {Zero, One,Two,Infinity};
#define compareconst 1e-12

/*struct Solution
{
    float root1, root2;
    int countroots;
};*/

int Solvesquare(const float a, const float b , const float c, float *x1, float *x2);

struct CheckNumbers
{
    float coef1;
    float coef2;
    float coef3;
    int nRoots;
    float x1Ex;
    float x2Ex;
} CheckMassive[] = {
    0, 0, 0, Infinity, 0, 0,
    0, 0, 1, Zero, 0, 0,
    0, 1, 1, One, -1, 0,
    1, 1, 1, Zero, 0, 0,
    1, 2, 1, One, -1, 0,
    2, 4, -6, Two, -3, 1
};

void Checker()
{

    for(int i=0;i<6;i++)
    {
        float x1proof=0, x2proof=0;

        int numroots = Solvesquare(CheckMassive[i].coef1, CheckMassive[i].coef2, CheckMassive[i].coef3, &x1proof, &x2proof);

        if( numroots!=CheckMassive[i].nRoots || x1proof!=CheckMassive[i].x1Ex || x2proof!=CheckMassive[i].x2Ex )
        {
            printf("Check %d failed a=%g b=%g c=%g x1=%g x2=%g NR=%d\n",i+1,CheckMassive[i].coef1, CheckMassive[i].coef2, CheckMassive[i].coef3, x1proof, x2proof,numroots);
        }
    }
    printf("Check is done\n");
}

/*int Solvesquare(float a, float b , float c, Solution *sol)
{
    assert(sol->root1);
    assert(sol->root2);

    if(a==0)
    {
        if(b==0)
        {
            if(c==0) return Infinity;
            else return Zero;
        }
        else
        {
            sol->root1 = -c/b;
            return One;
        }
    }
    else
    {
        const float d = b*b - 4*a*c;

        if(d<0)
        {
            return Zero;
        }
        else if(fabs(d)<compareconst)
        {
            sol->root1 = -c/b;
            return One;
        }
        else
        {
            const float sqrt_d = sqrt (d);
            sol->root1 = (-b - sqrt_d)/(2*a);
            sol->root2 = (-b + sqrt_d)/(2*a);
            return Two;
        }
    }
}*/
int Solvesquare(const float a, const float b , const float c, float *x1, float *x2)
{
    assert(x1);
    assert(x2);

    if(a==0)
    {
        if(b==0)
        {
            if(c==0) return Infinity;
            else return Zero;
        }
        else
        {
            *x1= -c/b;
            return One;
        }
    }
    else
    {
        const float d = b*b - 4*a*c;

        if(d<0)
        {
            return Zero;
        }
        else if(fabs(d)<compareconst)
        {
            *x1 = -b/(2*a);
            return One;
        }
        else
        {
            const float sqrt_d = sqrt (d);
            *x1 = (-b - sqrt_d)/(2*a);
            *x2 = (-b + sqrt_d)/(2*a);
            return Two;
        }
    }
}
void printsolves(int roots,float x1,float x2)
{
    switch(roots)
    {
        case Zero:  printf("no solves\n");
                    break;

        case One:   printf("x= %g\n",x1);
                    break;

        case Two:   printf("x1 = %g x2 = %g\n",x1,x2);
                    break;

        case Infinity:  printf("infinity count of solves\n");
                        break;

        default:    printf("main(): ERROR: count of roots = %d\n",roots);
                    break;
    }
}

/*void UserInputAndCheck()
{
    float coef[3];

    for(int i=0; i<3;i++)
    {
        coef[i]=0;
    }

    int proof = 0;

    for(int i=0; i<3;i++)
    {
        char in = 49+i+'0';
        printf("Enter coefficient %c:\n",in);

        int miniproof = scanf("%g",coef + i);
        proof = proof+miniproof;

        if(miniproof!=1)
        {
            char error;
            while((error = getchar())!=EOF&&error!='\n');
        }
    }

    if(proof == 3)
    {
        struct Solution sol;
        sol.countroots = Solvesquare(coef[0], coef[1], coef[2], &sol);

        printsolves(sol.countroots,sol.root1,sol.root2);
    }

    else printf("You can enter only numbers!");

}
*/
int main()
{
    printf("this is solver square equals from WacArteec \n");

    while(1)
    {
//        UserInputAndCheck();

        Checker();
        printf(" \nEnter 1 to repeat or another key to escape\n");
        int cont;
        scanf("%d",&cont);
        if(cont != 1) break;
    }
return 0;
}

