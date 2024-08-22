#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLACK   "\033[30m"      /* Black */

const float COMPARECONST = 1e-12;

enum constantnumbers {Zero, One, Two, Infinity};

struct Solution
{
    float coef[3];
    int countroots;
    float root1, root2;
};

struct CheckNumbers
{
    Solution sol_a;

};

const CheckNumbers CheckMassive[] = {
    {{0, 0, 0, Infinity, 0, 0}},
    {{0, 0, 1, Zero, 0, 0}},
    {{0, 1, 1, One, -1, 0}},
    {{1, 1, 1, Zero, 0, 0}},
    {{1, 2, 1, One, -1, 0}},
    {{2, 4, -6, Two, -3, 1}}
};

void SolveManager(Solution *sol);
int ChoiseEnter(const char refer);
int CompareFloats(const float a, const float b);
void Checker();
void LinearEquation(const float b, const float c, Solution *sol);
void PrintSolves(Solution sol);
void UserInputAndCheck(Solution *sol);
void GetcharReset();
void SquareEquation(const float a, const float b, const float c, Solution *sol);

int main()
{
    printf("this is solver square equals from WacArteec \n");

    while(1)
    {
        struct Solution sol;
        sol = {.coef = {0, 0, 0}, .countroots = 0, .root1 = 0, .root2 = 0};

        printf("To enter your parameters press e or press another button to check solver\n");

        if(ChoiseEnter('e'))
        {
            UserInputAndCheck(&sol);
            SolveManager(&sol);
            PrintSolves(sol);
        }
        else
        {
                Checker();
        }

        GetcharReset();
        printf(" \nEnter r to repeat or another key to escape\n");

        if(!ChoiseEnter('r')) break;
    }
return 0;
}

int ChoiseEnter(const char refer)
{
    int choise = ((getchar()) == refer);
    GetcharReset();
    return choise;
}

void GetcharReset()
{
    int reset = '\0';
    while((reset = getchar()) != EOF && reset != '\n');
}

int CompareFloats(float a, float b)
{
    return(fabs(a-b) < COMPARECONST);
}

void UserInputAndCheck(Solution *sol)
{
    for(int i=0; i<3;i++)
    {
        sol->coef[i]=0;
    }

    for(int i=0; i<3; i++)
    {
        char in = 'a' + i;
        printf("Enter coefficient %c:\n",in);

        if(scanf("%g",sol->coef + i) != 1 || !isfinite(sol->coef[i]) || !ChoiseEnter('\n'))
        {
            printf("You can enter only numbers\n");
            GetcharReset();

            i--;
        }
    }
}

void Checker()
{

    for(int i=0; i<6; i++)
    {
        struct Solution sol = {{CheckMassive[i].sol_a.coef[0], CheckMassive[i].sol_a.coef[1], CheckMassive[i].sol_a.coef[2]},0, 0, 0};
        SolveManager(&sol);

        if(sol.countroots != CheckMassive[i].sol_a.countroots ||
           CompareFloats(sol.root1, CheckMassive[i].sol_a.root1) == 0 ||
           CompareFloats(sol.root2, CheckMassive[i].sol_a.root2) == 0)
        {
            printf("First condition: %d\n",  sol.countroots != CheckMassive[i].sol_a.countroots);
            printf("Second condition: %d\n", CompareFloats(sol.root1, CheckMassive[i].sol_a.root1) == 0);
            printf("Third condition: %d\n",  CompareFloats(sol.root2, CheckMassive[i].sol_a.root2) == 0);

            printf(RED " Check %d failed a=%g b=%g c=%g x1=%g x2=%g NR=%d" BLACK "\n",
                   i+1,
                   CheckMassive[i].sol_a.coef[0],
                   CheckMassive[i].sol_a.coef[1],
                   CheckMassive[i].sol_a.coef[2],
                   sol.root1,
                   sol.root2,
                   sol.countroots);
        }
        else printf(GREEN "Test %d passed successfully"BLACK"\n",i+1);
    }
    printf("Check is done\n");
}

void SolveManager(Solution *sol)
{
    assert(sol);
    const float a = sol->coef[0], b = sol->coef[1], c = sol->coef[2];

    if(CompareFloats(0, a))  LinearEquation(b, c, sol);
    else    SquareEquation(a, b, c, sol);
}

void LinearEquation(const float b, const float c, Solution *sol)
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

void SquareEquation(const float a, const float b, const float c, Solution *sol)
{
    const float d = pow(b,2) - 4*a*c;

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
