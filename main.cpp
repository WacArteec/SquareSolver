#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define BLACK   "\033[30m"      /* Black */
const float COMPARECONST = 1e-12;
enum constantnumbers {Zero, One, Two, Infinity};

struct Parameters

{
    float a;
    float b;
    float c;
};

struct Solution
{
    int countroots;
    float root1, root2;
};

struct CheckNumbers
{
    Parameters par_a;
    Solution sol_a;
};

void SolveManager(const Parameters par, Solution *const sol);
int EqualSymbol(const char refer);
int CompareFloats(const float a, const float b);
void Checker();
void LinearEquation(const float b, const float c, Solution * const sol);
void PrintSolves(const Solution sol);
void UserInputAndCheck(float coef[3]);
void GetcharReset();
void SquareEquation(const float a, const float b, const float c, Solution * const sol);
int Min(const float a, const float b);
int Max(const float a, const float b);
float FabsZero(const float a);

int main()
{
    printf("this is solver of square equals from WacArteec \n");

    while(1)
    {
        struct Parameters par;
        struct Solution sol;

        par = {0, 0, 0};
        sol = {.countroots = 0, .root1 = 0, .root2 = 0};

        printf("To enter your parameters press e or press another button to check solver\n");

        if(EqualSymbol('e'))
        {
            float coef[3] = {0, 0, 0};
            UserInputAndCheck(coef);
            par.a = coef[0];
            par.b = coef[1];
            par.c = coef[2];
            SolveManager(par, &sol);
            PrintSolves(sol);
        }
        else
        {
            Checker();
        }

        GetcharReset();
        printf("\nEnter r to repeat or another key to escape\n");

        if(!EqualSymbol('r')) break;
    }
return 0;
}

int EqualSymbol(const char refer)
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

int CompareFloats(const float a, const float b)
{
    return(fabs(a - b) < COMPARECONST);
}

void UserInputAndCheck(float coef[3])
{
    for(int i = 0; i < 3; i++)
    {
        printf("Enter Parameter %c:\n",'a'+i);
        if(scanf("%g", &coef[i]) != 1)
        {
            GetcharReset();
            printf("You can enter only numbers\n");
            i--;
        }
        else if(!isfinite(coef[i]))
        {
            printf("You can enter only numbers\n");
            i--;
        }
        else if(!EqualSymbol('\n'))
        {
            printf("You can enter only numbers\n");
            i--;
        }
    }
}

void Checker()
{
    const CheckNumbers CheckMassive[] = {
    {{0, 0, 0}, {Infinity, 0, 0}},
    {{0, 0, 1}, {Zero, 0, 0}},
    {{0, 1, 1}, {One, -1, 0}},
    {{1, 1, 1}, {Zero, 0, 0}},
    {{1, 2, 1}, {One, -1, 0}},
    {{2, 4, -6}, {Two, -3, 1}}
//    {{},{}}
    };

    for(int i=0; i<(sizeof(CheckMassive)/sizeof(CheckMassive[0])); i++)
    {
        struct Parameters par = {CheckMassive[i].par_a.a, CheckMassive[i].par_a.b, CheckMassive[i].par_a.c};
        struct Solution sol = {0, 0, 0};
        SolveManager(par, &sol);

        if(sol.countroots != CheckMassive[i].sol_a.countroots ||
           CompareFloats(sol.root1, CheckMassive[i].sol_a.root1) == 0 ||
           CompareFloats(sol.root2, CheckMassive[i].sol_a.root2) == 0)
        {
            printf("First condition: %d\n",  sol.countroots != CheckMassive[i].sol_a.countroots);
            printf("Second condition: %d\n", CompareFloats(sol.root1, CheckMassive[i].sol_a.root1) == 0);
            printf("Third condition: %d\n",  CompareFloats(sol.root2, CheckMassive[i].sol_a.root2) == 0);

            printf(RED " Check %d failed a=%g b=%g c=%g x1=%g x2=%g NR=%d" BLACK "\n",
                   i+1,
                   CheckMassive[i].par_a.a,
                   CheckMassive[i].par_a.b,
                   CheckMassive[i].par_a.c,
                   sol.root1,
                   sol.root2,
                   sol.countroots);
        }
        else printf(GREEN "Test %d passed successfully"BLACK"\n", i+1);
    }
    printf("Check is done\n");
}

void SolveManager(const Parameters par, Solution * const sol)
{
    assert(sol);
    const float a = par.a, b = par.b, c = par.c;

    if(CompareFloats(0, a)) LinearEquation(b, c, sol);
    else    SquareEquation(a, b, c, sol);
}

void LinearEquation(const float b, const float c, Solution *const sol)
{
    enum constantnumbers {Zero, One, Two, Infinity};
    if(CompareFloats(0, b))
    {
        if(CompareFloats(0, c)) sol->countroots = Infinity;
        else sol->countroots = Zero;
    }
    else
    {
        sol->root1= FabsZero(-c/b);
        sol->countroots = One;
    }
}

void SquareEquation(const float a, const float b, const float c, Solution *const sol)
{

    enum constantnumbers {Zero, One, Two, Infinity};
    const float d = b*b - 4*a*c;

    if(CompareFloats(0, d))
    {
        sol->root1 = FabsZero(-b/(2*a));
        sol->countroots = One;
    }
    else if(d < 0)
    {
        sol->countroots = Zero;
    }
    else
    {
        const float sqrt_d = sqrt (d);
        sol->root1 = FabsZero(Min((-b - sqrt_d)/(2*a),(-b + sqrt_d)/(2*a)));
        sol->root2 = FabsZero(Max((-b - sqrt_d)/(2*a),(-b + sqrt_d)/(2*a)));
        sol->countroots = Two;
    }
}

float FabsZero(const float a)
{
    if (CompareFloats(0,a)) return fabs(a);
    else return a;
}

int Min(const float a, const float b)
{
    if(a < b) return a;
    else return b;
}

int Max(const float a, const float b)
{
    if(a > b) return a;
    else return b;
}

void PrintSolves(const Solution sol)
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
