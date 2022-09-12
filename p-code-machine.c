#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AMAX 2047
#define LEVMAX 3
#define CXMAX 200
#define STACKSIZE 500

enum
{
    LIT,
    OPR,
    LOD,
    STO,
    CAL,
    INT,
    JMP,
    JPC
} fct;
char *codigoInstrucoes[] = {"LIT", "OPR", "LOD", "STO", "CAL", "INT", "JMP", "JPC"};

typedef struct
{
    int f;
    int l;
    int a;
} instruction;

instruction i;
instruction code[CXMAX];

int t = 0;
int p = 0;
int b = 1;

int s[STACKSIZE];

int base(int l)
{
    int b1;
    b1 = b;
    while (l > 0)
    {
        b1 = s[b1];
        l--;
    }
    return b1;
}

int codInstrucao(char *codigo)
{
    for (int i = 0; i < 9; i++)
    {
        if (strcmp(codigo, codigoInstrucoes[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}

char *nomeInstrucao(int inst)
{
    return codigoInstrucoes[inst];
}

void instrucao()
{
    i = code[p];
    p = p + 1;
    s[1] = s[2] = s[3] = 0;
    switch (i.f)
    {
    case LIT:
        t = t + 1;
        s[t] = i.a;
        break;
    case OPR:
        switch (i.a)
        {
        case 0:
            t = b - 1;
            p = s[t + 3];
            b = s[t + 2];
            break;
        case 1:
            s[t] = -1 * s[t];
            break;
        case 2:
            t = t - 1;
            s[t] = s[t] + s[t + 1];
            break;
        case 3:
            t = t - 1;
            s[t] = s[t] - s[t + 1];
            break;
        case 4:
            t = t - 1;
            s[t] = s[t] * s[t + 1];
            break;
        case 5:
            t = t - 1;
            s[t] = s[t] / s[t + 1];
            break;
        case 6:
            t = t - 1;
            s[t] = (s[t] % 2 == 1);
            break;
        case 8:
            t = t - 1;
            s[t] = (s[t] == s[t + 1]);
            break;
        case 9:
            t = t - 1;
            s[t] = (s[t] != s[t + 1]);
            break;
        case 10:
            t = t - 1;
            s[t] = (s[t] < s[t + 1]);
            break;
        case 11:
            t = t - 1;
            s[t] = (s[t] >= s[t + 1]);
            break;
        case 12:
            t = t - 1;
            s[t] = (s[t] > s[t + 1]);
            break;
        case 13:
            t = t - 1;
            s[t] = (s[t] <= s[t + 1]);
            break;
        default:
            printf("OPR inválido!!");
            break;
        }
        break;
    case LOD:
        t = t + 1;
        s[t] = s[base(i.l) + i.a];
        break;
    case STO:
        s[base(i.l) + i.a] = s[t];
        t = t - 1;
        break;
    case CAL:
        s[t + 1] = base(i.l);
        s[t + 2] = b;
        s[t + 3] = p;
        b = t + 1;
        p = i.a;
        break;
    case INT:
        t = t + i.a;
        break;
    case JMP:
        p = i.a - 1;
        break;
    case JPC:
        if (s[t] == 0)
        {
            p = i.a - 1;
        }
        t = t - 1;
        break;
    default:
        printf("ERRO!");
        break;
    }

    printf("%s\t\t%d\t\t%d\t\t%d\t\t ", nomeInstrucao(i.f), i.l, i.a, s[t]);

    for (int aux = b; aux < t + 1; aux++)
    {
        printf("%d ", s[aux]);
    }
}

int main()
{
    char f[3];
    int l, a, codigo;
    int j;

    for (j = 0; j < 100; j++)
    {
        scanf("\n%s %d %d", f, &l, &a);
        if (strcmp(f, "END") == 0 && a == 0)
        {
            break;
        }
        else
        {
            codigo = codInstrucao(f);
            if (codigo != -1)
            {
                code[j].f = codigo;
                code[j].l = l;
                code[j].a = a;
            }
            else
            {
                printf("Instrucao invalida!!");
            }
        }
    }

    printf("INSTRUCAO\tP\t\tB\t\tT\t\t PILHA\n");
    printf("-------\t\t---\t\t---\t\t---\t\t--------\n");
    do
    {
        instrucao();
        printf("\n");
    } while (p != 0);
    printf("\n");
    return 0;
}
