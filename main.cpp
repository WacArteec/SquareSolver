#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLACK   "\033[30m"      /* Black */
enum constantnumbers {Zero, One, Two, Infinity};
#define compareconst 1e-12

struct Solution
{
    float root1, root2;
    int countroots;
};

struct CheckNumbers
{
    float coef1, coef2, coef3;
    int nRoots;
    float x1Ex, x2Ex;
};

const CheckNumbers CheckMassive[] = {
    0, 0, 0, Infinity, 0, 0,
    0, 0, 1, Zero, 0, 0,
    0, 1, 1, One, -1, 0,
    1, 1, 1, Zero, 0, 0,
    1, 2, 1, One, -1, 0,
    2, 4, -6, Two, -3, 1
};

void SolveSquare(const float a, const float b , const float c, Solution *sol);
int ChoiseEnter(char refer);
int CompareFloats(float a, float b);
void Checker();
void LinearEquation(float b, float c, Solution *sol);
void PrintSolves(Solution sol);
void UserInputAndCheck();
void GetcharReset();

int main()
{
    printf("this is solver square equals from WacArteec \n");

    while(1)
    {
        struct Solution sol;
        sol = { .root1=0, .root2=0};

        printf("To enter your parameters press e or press another button to check solver\n");

        if(ChoiseEnter('e'))
        {
            UserInputAndCheck();
            GetcharReset();
        }
        else
        {
                Checker();
        }
        printf(" \nEnter r to repeat or another key to escape\n");

        if(!ChoiseEnter('r')) break;
    }
return 0;
}

int ChoiseEnter(char refer)
{
    int choise = '\0';
    int a =(choise = getchar()) == refer;
    GetcharReset();
    return a;
}

void GetcharReset()
{
    int reset = '\0';
    while((reset = getchar()) != EOF && reset != '\n');
}

int CompareFloats(float a, float b)
{
    return(fabs(a-b) < compareconst);
}

void UserInputAndCheck()
{
    float coef[3];

    for(int i=0; i<3;i++)
    {
        coef[i]=0;
    }

    int proof = 0;

    for(int i=0; i<3; i++)
    {
        char in = 'a' + i;
        printf("Enter coefficient %c:\n",in);

        int miniproof = scanf("%g",coef + i);
        proof += miniproof;

        if(miniproof != 1)
        {
            GetcharReset();
        }
    }

    if(proof == 3)
    {
        for (int i=0; i<3; i++)
        {
            if(!isfinite(coef[i]))
            {
                printf("You can enter only numbers!");
            }
        }
        struct Solution sol;
        SolveSquare(coef[0], coef[1], coef[2], &sol);
    }

    else printf("You can enter only numbers!");

}

void Checker()
{

    for(int i=0; i<6; i++)
    {
        struct Solution sol = {0, 0, 0};
        SolveSquare(CheckMassive[i].coef1, CheckMassive[i].coef2, CheckMassive[i].coef3, &sol);

        if(sol.countroots != CheckMassive[i].nRoots ||
           !CompareFloats(sol.root1, CheckMassive[i].x1Ex) ||
           !CompareFloats(sol.root2, CheckMassive[i].x2Ex))
        {
            printf(RED " Check %d failed a=%g b=%g c=%g x1=%g x2=%g NR=%d" BLACK "\n",
                   i+1,
                   CheckMassive[i].coef1,
                   CheckMassive[i].coef2,
                   CheckMassive[i].coef3,
                   sol.root1,
                   sol.root2,
                   sol.countroots);
        }
        else printf(GREEN "Test %d passed successfully"BLACK"\n",i+1);
    }
    printf("Check is done\n");
}

void SolveSquare(const float a, const float b , const float c, Solution *sol)
{
    assert(sol);

    if(CompareFloats(0, a))
    {
        LinearEquation(b, c, sol);
    }
    else
    {
        const float d = b*b - 4*a*c;

        if(d < 0)
        {
            sol->countroots = Zero;
        }
        else if(CompareFloats(0, d))
        {
            sol->root1 = -b/(2*a);
            sol->countroots = One;
        }
        else
        {
            const float sqrt_d = sqrt (d);
            sol->root1 = (-b - sqrt_d)/(2*a);
            sol->root2 = (-b + sqrt_d)/(2*a);
            sol->countroots = Two;
        }
    }
    PrintSolves(*sol);
}

void LinearEquation(float b, float c, Solution *sol)
{
        if(CompareFloats(0, b))
        {
            if(CompareFloats(0, c)) sol->countroots = Infinity;
            else sol->countroots = Zero;
        }
        else
        {
            sol->root1= -c/b;
            sol->countroots = One;
        }
}

void PrintSolves(Solution sol)
{
    switch(sol.countroots)
    {
        case Zero:  printf("no solves\n");
                    break;

        case One:   printf("x= %g\n", sol.root1);
                    break;

        case Two:   printf("x1 = %g x2 = %g\n", sol.root1, sol.root2);
                    break;

        case Infinity:  printf("infinity count of solves\n");
                        break;

        default:    printf("main(): ERROR: count of roots = %d\n", sol.countroots);
                    break;
    }
}
