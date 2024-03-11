#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <time.h>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <string>
#include <cmath>
#include <sstream>

#define MAX1 100
#define MAX_NR 50
#define FUNDAL DARKGRAY

using namespace std;
int v[MAX1];
char valori[MAX1][MAX1], necunoscute[MAX1],frecventa[MAX1],citeste[MAX1][MAX1],afiseaza[MAX1][MAX1];
int nrnec,nrfrec;
int x, n, y,rezx,rezy;
stack<double> Opz;
stack<string> Op;
stack<char> Paranteze;

/// Serban
void mytostring(int n, char *s)
{
    if(n == 0) s[0] = (char)(0+'0');
    else if(n < 0)
    {
        int k = 1;
        s[0] = '-';
        n *= -1;
        while(n) s[k++] = (char)(n%10+'0'), n /= 10;
        for(int i = 1; i <= k/2; i ++)
        {
            char aux = s[i];
            s[i] = s[k-i];
            s[k-i] = aux;
        }
    }
    else
    {
        int k = 0;
        while(n) s[k++] = (char)(n%10+'0'), n /= 10;
        for(int i = 0; i < k/2; i ++)
        {
            char aux = s[i];
            s[i] = s[k-i-1];
            s[k-i-1] = aux;
        }
    }
}
void calculare(string x)
{
    if (x == "*")
    {
        double a1 = Opz.top();
        Opz.pop();
        double a2 = Opz.top();
        Opz.pop();
        Opz.push(a1 * a2);
    }
    else if (x == "/")
    {
        double a1 = Opz.top();
        Opz.pop();
        double a2 = Opz.top();
        Opz.pop();
        Opz.push(a2 / a1);
    }
    else if (x == "+")
    {
        double a1 = Opz.top();
        Opz.pop();
        double a2 = Opz.top();
        Opz.pop();
        Opz.push(a1 + a2);

    }
    else if (x== "-")
    {
        double a1 = Opz.top();
        Opz.pop();
        double a2 = Opz.top();
        Opz.pop();
        Opz.push(a2 - a1);
    }
    Op.pop();
}

int evaluareexpresie(char a[256])
{
    int nr=0,verif=0;
    char *p1,t[30], t1[30],t2[30];
    for(int i=0; i<strlen(a); i++)
    {
        if(strchr("><=!",a[i])!=NULL)
        {
            while(strchr("><=!",a[i])!=NULL)
            {
                t[nr++]=a[i];
                i++;
            }
            break;
        }

    }
    t[nr]='\0';
    p1 = strtok(a, " ");
    while (p1)
    {
        if (p1[0] >= '0' && p1[0] <= '9')
        {
            if(verif==0)
            {
                strcpy(t1, p1);
                verif=1;
            }
            else
                strcpy(t2,p1);

        }

        p1 = strtok(NULL, " ");
    }


    if (strcmp(t, "<=") == 0)
    {
        if (stod(t1)<= stod(t2))
            return 1;
    }
    else if(strcmp(t,">=")==0)
    {
        if(stod(t1)>=stod(t2))
            return 1;
    }
    else if(strcmp(t,"==")==0)
    {
        if(stod(t1)==stod(t2))
            return 1;
    }
    else if(strcmp(t,"!=")==0)
    {
        if(stod(t1)!=stod(t2))
            return 1;
    }
    else if(strcmp(t,"<")==0)
    {
        if(stod(t1)<stod(t2))
            return 1;
    }
    else if(strcmp(t,">")==0)
    {
        if(stod(t1)>stod(t2))
            return 1;
    }
    return 0;
}


int Prioritate(string c)
{
    if (c == "(" || c == ")")
        return 0;
    if (c == "+" || c == "-")
        return 1;
    if (c == "*" || c == "/")
        return 2;
    if (c == "^")
        return 3;
    if (c == "=" || c == "#" || c == "<" || c == ">")
        return 4;
    if (c == "sin" || c == "cos" || c == "log" || c == "exp" || c == "abs" || c == "sqrt") ///q pentru sqrt ca sa se distinga de s
        return 5;
}

int verifoperatori(char x[256])
{
    if (strcmp(x, "log") == 0)
        return 1;
    else if (strcmp(x, "abs") == 0)
        return 1;
    else if (strcmp(x, "sin") == 0)
        return 1;
    else if (strcmp(x, "cos") == 0)
        return 1;
    else if (strcmp(x, "rad") == 0)
        return 1;
    return 0;
}

int verif1(char x, char y)
{
    if (x == '*' || x == '/' || x == '^' || x == '=' || x == '<' || x == '>' || x == '<=' || x == '>=' || x == '.' || x == ',' || x == '-' || x == '+')
        return 0;
    if (y == ')' || y == '*' || y == '/' || y == '^' || y == '=' || y == '<' || y == '>' || y == '<=' || y == '>=' || y == '.' || y == ',' || x == '-' || x == '+')
        return 1;
}
int verif2(char x, char y)
{
    if (x == '*' || x == '/' || x == '^' || x == '=' || x == '+' || x == '-' || x == '<' || x == '>' || x == '<=' || x == '>=' || x == '.' || x == ',' || x == '(')
        return 0;
    if (y == ')' || y == '*' || y == '/' || y == '^' || y == '=' || y == '+' || y == '-' || y == '<' || y == '>' || y == '<=' || y == '>=' || y == '.' || y == ',')
        return 0;
    return 1;
}

int EvaluatorMatematic(char s[260])
{
    char t[260], anterior[256], a, *p;
    int ok = 0, ok1 = 0;

    /// verificare validitate
    for(int i = 0; i < strlen(s); i ++)
    {
        if(s[i] == '(')
            Paranteze.push(s[i]);
        else
        {
            if(s[i] == ')' && !Paranteze.empty())
                Paranteze.pop( );
            else if(s[i] == ')' && Paranteze.empty())
                return 0;
        }
        if(s[i] == ' ' && s[i+1] == ' ' && i < strlen(s))
            return 0;
    }

    if(!Paranteze.empty())
        return 0;
    for(int i = 0; i < strlen(s); i ++)
        if(s[i] == '*' || s[i] == '/' )
        {
            if(verif2(s[i-1], s[i+1]) == 0)
                return 0;
        }
        else if(s[i] == '+' || s[i] == '-' )
            if(verif1(s[i-1], s[i+1]) == 0)
                return 0;
    for(int i = 0; i < strlen(s); i ++)
    {
        if((s[i] == '*' || s[i] == '/' || s[i] == '+' || s[i] == '-' || s[i] == '(' || s[i] == ')' || s[i] == '*') && i != strlen(s)-1)
        {

            strcpy(t, s+i+1);
            strcpy(s+i+2, t);
            s[i+1] = ' ';
            i ++;
        }
        else if(s[i+1] == '*' || s[i+1] == '/' || s[i+1] == '+' || s[i+1] == '-' || s[i+1] == ')' || s[i+1] == '(' || s[i+1] == '^')
        {

            strcpy(t, s+i);
            strcpy(s+i+1, t);
            s[i+1] = ' ';
            i ++;
        }


    }

    char c[256];
    char x2[50];
    c[0] = '\0';
    ok = 0;
    double z2;
    p = strtok(s," ");
    while(p)
    {
        if(verifoperatori(p) == 1)
        {
            strcpy(x2, p);
            ok = 1;
        }
        if(ok == 1 && (p[0] >= 0 && p[0] <= 9))
        {
            ok = 1;
            if(strcmp(x2, "sin") == 0)
                z2 = sin(stod(p));
            else if(strcmp(x2, "cos") == 0)
                z2 = cos(stod(p));
            else if(strcmp(x2, "log") == 0)
                z2 = log(stod(p));
            else if(strcmp(x2, "abs") == 0)
                z2 = fabs(stod(p));
            else if(strcmp(x2, "rad") == 0)
                z2 = sqrt(stod(p));
        }
        else if(ok == 1 && strcmp(p, ")") == 0)
        {
            char x1[50];
            sprintf(x1, "%d", z2);
            strcat(c, x1);
            strcat(c, " ");
            ok = 0;
        }
        else if(ok == 0)
        {
            strcat(c, p);
            strcat(c, " ");
        }
        p = strtok(NULL, " ");
    }
    strcpy(s, c);

    ok = 0, ok1 = 0;
    string y1;
    istringstream iss(s);
    while(iss >> s)
    {
        if(verifoperatori(s) == 0 && (s[0] >= 'a' && s[0] <= 'z'))
            return 0;

        if(verifoperatori(anterior) && verifoperatori(s))
            return 0;

        if(s[0] >= '0' && s[0] <= '9')
        {
            if(ok == 1)
            {
                while(!Op.empty() && Prioritate(Op.top()) >= Prioritate(y1))
                    calculare(Op.top());

                Op.push(y1);
                ok = 0;
            }

            if(ok1 == 1)
            {
                double x5 = stod(s);
                Opz.push(-x5);
                ok1 = 0;
            }
            else
                Opz.push(stod(s));

        }
        else
        {
            if(Op.empty())
                Op.push(s);
            else if(Prioritate(Op.top()) >= Prioritate(s))
            {
                if(strcmp(s, "(") == 0)
                {
                    Op.push(s);
                }
                else
                {
                    ok = 1;
                    y1 = s;
                }
            }
            else
            {
                if(strcmp(s, "-") == 0 && strcmp(anterior, "(") == 0)
                {
                    ok1 = 1;
                }
                else
                    Op.push(s);

            }
        }
        strcpy(anterior, s);
    }

    while(!Op.empty())
    {
        calculare(Op.top());
    }

    return Opz.top();
}
int analizareconditie (char z[256])
{
    int i = 0;
    char t[51];
    while(strchr("<>=!",z[i+1])==NULL)
        i++;
    strcpy(t,z+i+1);
    for(int j=strlen(z); j>=i+1; j--)
        z[j]=NULL;
    z[i+1]=' ';
    strcat(z,t);
    while(strchr("0123456789",z[i+1])==NULL)
        i++;
    strcpy(t,z+i+1);
    for(int j=strlen(z); j>=i+1; j--)
        z[j]=NULL;
    z[i+1]=' ';
    strcat(z,t);
    return evaluareexpresie(z);

}
int Conditie(char z[256])
{
    char c1[50],c2[50];
    int condsi=0,condsau=0;
    int i = 0;
    for(int i=0; i<=strlen(z); i++)
        if(z[i]==' ')
        {
            strncpy(c1,z,i);
            c1[i]='\0';
            break;
        }

    for(int i=0; i<=strlen(z); i++)
        if(z[i]=='&' && z[i+1]=='&')
        {
            condsi=1;
            break;
        }
        else  if(z[i]=='|' && z[i]=='|')
        {
            condsau=1;
            break;
        }
    for(int i=strlen(z)-1; i>=0; i--)
        if(z[i]==' ')
        {
            strcpy(c2,z+i);
            break;
        }
    if(condsi==1)
    {
        if(analizareconditie(c1)==1 && analizareconditie(c2)==1)
            return 1;
        else
            return 0;
    }
    if(condsau==1)
    {
        if(analizareconditie(c1)==0 && analizareconditie(c2)==0)
            return 0;
        else
            return 1;
    }
    else if(analizareconditie(z)==1)
        return 1;
    return 0;

}

/// Florea
void myOuttextXY(int x, int y, int cerneala, int hartie, char *text)
{
    settextjustify(CENTER_TEXT,CENTER_TEXT);
    setcolor(cerneala);///Pentru text
    setbkcolor(hartie);/// Pentru culoarea din spatele textului
    outtextxy(x,y+3,text);
}

struct punctLegatura
{
    int x,y,v;///Coordonatele celor 2 puncte dintr-un nod
};

struct nod
{
    char info[MAX1];///Trebuie sa stim cum se cheama nodul
    int x,y;///Coordonatele nodului
    int culoare;///Codul culorii
    int tip;
    punctLegatura pLeg[4];///O sa avem nevoie ca fiecare sa aiba cate 2 puncte de legatura(O sa le schimbam mai tarziu
};
void citire(int x, int y,int xx,int yy)
{
    line(x-10-xx,y+15+yy,x+10+xx,y+15+yy);
    line(x+10+xx,y+15+yy,x+20+xx,y-15-yy);
    line(x+20+xx,y-15-yy,x-20-xx,y-15-yy);
    line(x-20-xx,y-15-yy,x-10-xx,y+15+yy);
}
void afisare(int x, int y,int xx,int yy)
{
    line(x-10-xx,y-15-yy,x+xx+10,y-15-yy);
    line(x+10+xx,y-15-yy,x+20+xx,y+15+yy);
    line(x+20+xx,y+15+yy,x-20-xx,y+15+yy);
    line(x-20-xx,y+15+yy,x-10-xx,y-15-yy);
}
void declarare(int x, int y,int xx,int yy)
{
    line(x-10-xx,y-10-yy,x+10+xx,y-10-yy);
    line(x+10+xx,y-10-yy,x+10+xx,y+10+yy);
    line(x+10+xx,y+10+yy,x-10-xx,y+10+yy);
    line(x-10-xx,y+10+yy,x-10-xx,y-10-yy);
}
void conditie(int x, int y, int xx, int yy)
{
    line(x,y-15-yy,x+20+xx,y);
    line(x+20+xx,y,x,y+15+yy);
    line(x,y+15+yy,x-20-xx,y);
    line(x-20-xx,y,x,y-15-yy);
}
void atribuire(int x, int y, int xx,int yy)
{
    line(x-xx+30,y-10-yy,x+xx-30,y-10-yy);
    line(x-30+xx,y-10-yy,x-30+xx,y+10+yy);
    line(x+xx-30,y+10+yy,x-xx+30,y+10+yy);
    line(x+30-xx,y+10+yy,x+30-xx,y-10-yy);
}
nod vecNoduri[MAX_NR];
int nrNoduri;

struct legatura
{
    int nod1, nod2; /// cele doua noduri ce se leaga
    int punct1, punct2; /// punctele de legatura de la cele doua noduri
    int x1, y1, x2, y2;
};

legatura vecLegaturi[MAX_NR];
int nrLegaturi;

void deseneazaNod(nod N)
{
    if(N.tip==1||N.tip==2)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        fillellipse(N.x,N.y,10+2*textwidth(N.info),10+textheight(N.info));
    }
    else if(N.tip==3)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            citire(N.x,N.y,34,16);
        else
            citire(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==4)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            afisare(N.x,N.y,34,16);
        else
            afisare(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==5)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            declarare(N.x,N.y,34,16);
        else
            declarare(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==6)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<53)
            atribuire(N.x,N.y,53,16);
        else
            atribuire(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<53)
            conditie(N.x,N.y,53,16);
        else
            conditie(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    myOuttextXY(N.x,N.y,0,N.culoare,N.info);///Pune scrisul si il aranjeaza
    setcolor(WHITE);///Ce culoare sa aiba punctele
    circle(N.pLeg[0].x,N.pLeg[0].y,5);///Desenam cercurile de legatura
    if(N.tip>2)
        circle(N.pLeg[1].x,N.pLeg[1].y,5);///-//-
    if(N.tip==7)
    {
        circle(N.pLeg[2].x,N.pLeg[2].y,5);
        circle(N.pLeg[3].x,N.pLeg[3].y,5);
    }
}
void deseneazabloc(nod N)
{
    if(N.tip==1||N.tip==2)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        fillellipse(N.x,N.y,10+2*textwidth(N.info),10+textheight(N.info));
    }
    else if(N.tip==3)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            citire(N.x,N.y,34,16);
        else
            citire(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==4)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            afisare(N.x,N.y,34,16);
        else
            afisare(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==5)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            declarare(N.x,N.y,34,16);
        else
            declarare(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==6)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            atribuire(N.x,N.y,34,16);
        else
            atribuire(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==7)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<53)
            conditie(N.x,N.y,53,16);
        else
            conditie(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==8)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            declarare(N.x,N.y,34,16);
        else
            declarare(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==9)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            declarare(N.x,N.y,34,16);
        else
            declarare(N.x, N.y, 100, textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==10)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            declarare(N.x,N.y,34,16);
        else
            declarare(N.x, N.y, 100, textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==11)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            declarare(N.x,N.y,34,16);
        else
            declarare(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==12)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            declarare(N.x,N.y,34,16);
        else
            declarare(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==13)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            declarare(N.x,N.y,34,16);
        else
            declarare(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    else if(N.tip==14)
    {
        setfillstyle(SOLID_FILL,N.culoare);
        if(textwidth(N.info)<34)
            declarare(N.x,N.y,34,16);
        else
            declarare(N.x,N.y,textwidth(N.info),textheight(N.info));
        floodfill(N.x,N.y,WHITE);
    }
    myOuttextXY(N.x,N.y,0,N.culoare,N.info);///Pune scrisul si il aranjeaza
    setcolor(WHITE);

}

void initNod(nod& N, char text[MAX1], int oCuloare,int tipul)
{
    strcpy(N.info,text);///Trebuie sa stim cum se numeste fiecare casuta

    N.culoare=oCuloare;///Primeste codul culorii(Fiecare casuta o sa aiba un cod diferit
    N.tip=tipul;
    if(tipul == 1)
    {
        N.x=getmaxx()/2-getmaxx()/16;
        N.y=getmaxy()/4;
        N.pLeg[0].x=N.x;
        N.pLeg[0].y=N.y+textheight(N.info)+5;
        N.pLeg[1].x=0;
        N.pLeg[1].y=0;
        N.pLeg[2].x=0;
        N.pLeg[2].y=0;
    }
    else if(tipul == 2)
    {
        N.x=getmaxx()/5;
        N.y=getmaxy() - getmaxy()/5;
        N.pLeg[0].x=N.x;
        N.pLeg[0].y=N.y-textheight(N.info)-5;
        N.pLeg[2].x=0;
        N.pLeg[2].y=0;
    }
    else if(tipul == 3)
    {
        N.x=getmaxx()/5;
        N.y=getmaxy() - getmaxy()/1.8;
        N.pLeg[0].x=N.x;
        N.pLeg[0].y=N.y-textheight(N.info)-10;
        N.pLeg[1].x=N.x;
        N.pLeg[1].y=N.y+textheight(N.info)+11;
        N.pLeg[2].x=0;
        N.pLeg[2].y=0;
    }
    else if(tipul == 4)
    {
        N.x=getmaxx()/5;
        N.y=getmaxy() - getmaxy()/3.5;
        N.pLeg[0].x=N.x;
        N.pLeg[0].y=N.y-textheight(N.info)-10;
        N.pLeg[1].x=N.x;
        N.pLeg[1].y=N.y+textheight(N.info)+11;
        N.pLeg[2].x=0;
        N.pLeg[2].y=0;
    }
    else if(tipul == 5)
    {
        N.x=getmaxx()/5;
        N.y=getmaxy() - getmaxy()/1.55;
        N.pLeg[0].x=N.x;
        N.pLeg[0].y=N.y-textheight(N.info)-5;
        N.pLeg[1].x=N.x;
        N.pLeg[1].y=N.y+textheight(N.info)+6;
        N.pLeg[2].x=0;
        N.pLeg[2].y=0;
    }
    else if(tipul == 6)
    {
        N.x=getmaxx()/5;
        N.y=getmaxy() - getmaxy()/2.2;
        N.pLeg[0].x=N.x;
        N.pLeg[0].y=N.y-textheight(N.info)-5;
        N.pLeg[1].x=N.x;
        N.pLeg[1].y=N.y+textheight(N.info)+6;
        N.pLeg[2].x=0;
        N.pLeg[2].y=0;
    }
    else if(tipul == 7)
    {
        N.x=getmaxx()/5;
        N.y=N.y=getmaxy() - getmaxy()/2.7;
        N.pLeg[0].x=N.x;
        N.pLeg[0].y=N.y-textheight(N.info)-9;
        N.pLeg[1].x=N.x-textwidth(N.info)-6;
        N.pLeg[1].y=N.y;
        N.pLeg[2].x=N.x+textwidth(N.info)+6;
        N.pLeg[2].y=N.y;
        N.pLeg[3].x=N.x;
        N.pLeg[3].y=N.y+textheight(N.info)+9;
    }
}
void initbloc(nod& N, char text[MAX1], int oCuloare, int tipul)
{
    strcpy(N.info,text); /// Trebuie sa stim cum se numeste fiecare casuta
    N.culoare = oCuloare; /// Primeste codul culorii
    N.tip=tipul;
    if(N.tip == 2) /// Stop
    {
        N.x=getmaxx()/16;
        N.y=getmaxy() - getmaxy()/5;
    }
    else if(N.tip == 3) /// Citire
    {
        N.x=getmaxx()/16;
        N.y=getmaxy() - getmaxy()/1.8;
    }
    else if(N.tip == 4) /// Afisare
    {
        N.x=getmaxx()/16;
        N.y=getmaxy() - getmaxy()/3.5;
    }
    else if(N.tip == 5) /// Declarare
    {
        N.x=getmaxx()/16;
        N.y=getmaxy() - getmaxy()/1.55;
    }
    else if(N.tip == 6) /// Atribuire
    {
        N.x=getmaxx()/16;
        N.y=getmaxy() - getmaxy()/2.2;
    }
    else if(N.tip == 7) /// Conditie
    {
        N.x=getmaxx()/16;
        N.y=getmaxy() - getmaxy()/2.7;
    }
    else if(N.tip == 8) /// Back
    {
        N.x=getmaxx()/16;
        N.y=getmaxy()/18;
    }
    else if(N.tip == 9) /// Stergere blocuri
    {
        N.x=getmaxx()/5;
        N.y=getmaxy()/18;
    }
    else if(N.tip == 10) /// Stergere legaturi
    {
        N.x=getmaxx()/2.8;
        N.y=getmaxy()/18;
    }
    else if(N.tip == 11) /// Exit
    {
        N.x=getmaxx()/2;
        N.y=getmaxy() - getmaxy()/2.7;
    }
    else if(N.tip == 12) /// Start
    {
        N.x=getmaxx()/2;
        N.y=getmaxy()/2;
    }
    else if(N.tip == 13) /// Run
    {
        N.x=getmaxx() - getmaxx()/9.4;
        N.y=getmaxy() - getmaxy()/3;
    }
    else if(N.tip == 14) /// Generare cod
    {
        N.x=getmaxx() - getmaxx()/9.4;
        N.y=getmaxy()/18;
    }

}

nod blocuri[MAX_NR];
void drawLine(int x1, int y1, int x2, int y2, int cul)
{
    setcolor(cul);
    line(x1,y1,x1,(y1+y2)/2);
    line(x1,(y1+y2)/2,x2,(y1+y2)/2);
    line(x2,(y1+y2)/2,x2,y2);
}

/// Delia
void LiniiMeniu()
{
    setcolor(BLACK);
    setlinestyle(0, 0, 2);
    line(getmaxx()-getmaxx(), getmaxy()/9, getmaxx()-getmaxx()/4.5, getmaxy()/9); /// orizontal sus
    line(getmaxx()/7.7, getmaxy()/9, getmaxx()/7.7, getmaxy()); /// vertical stanga
    line(getmaxx()-getmaxx()/4.5, getmaxy()-getmaxy(), getmaxx()-getmaxx()/4.5, getmaxy()); /// vertical dreapta
    line(getmaxx()-getmaxx()/4.5, getmaxy()-getmaxy()/2.7, getmaxx(), getmaxy()-getmaxy()/2.7); /// orizontal jos


    myOuttextXY(getmaxx()/16, getmaxy()/4,0,8, "Blocuri");
    myOuttextXY(getmaxx()/2-getmaxx()/16, getmaxy()/6,0,8, "Schema logica");
}

int verificare(int j,int n)
{
    for(int i=0; i<nrLegaturi; i++)
        if(i!=j)
        {
            if(vecNoduri[n].tip==7)
            {
                if(vecLegaturi[i].punct1==3||vecLegaturi[i].punct2==3)
                    if(vecLegaturi[i].nod1==n||vecLegaturi[i].nod2==n)
                        if(vecLegaturi[i].nod1==n)
                            return 1*verificare(i,vecLegaturi[i].nod2);
                        else
                            return 1*verificare(i,vecLegaturi[i].nod1);
            }
            else
            {
                if(vecLegaturi[i].nod1==n||vecLegaturi[i].nod2==n)
                    if(vecLegaturi[i].nod1==n)
                        return 1*verificare(i,vecLegaturi[i].nod2);
                    else
                        return 1*verificare(i,vecLegaturi[i].nod1);
            }
        }
    if(vecNoduri[n].tip==2)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int ordinea_nodurilor(int j,int n,int &nr)
{
    int okk=0,okkk=0;
    if(vecNoduri[n].tip==7)
    {
        for(int i=0; i<nrLegaturi; i++)
            if((vecLegaturi[i].punct1==1||vecLegaturi[i].punct2==1)&&i!=j)
                if(vecLegaturi[i].nod1==n)
                {
                    nr++;
                    v[nr]=vecLegaturi[i].nod1;
                    okk=1;
                    ordinea_nodurilor(i,vecLegaturi[i].nod2,nr);
                }
                else if(vecLegaturi[i].nod2==n)
                {
                    nr++;
                    v[nr]=vecLegaturi[i].nod2;
                    okk=1;
                    ordinea_nodurilor(i,vecLegaturi[i].nod1,nr);
                }
        nr++;
        v[nr]=-1;
        for(int i=0; i<nrLegaturi; i++)
            if(vecLegaturi[i].punct1==2||vecLegaturi[i].punct2==2)
                if(vecLegaturi[i].nod1==n)
                {
                    okk=1;
                    okkk=1;
                    ordinea_nodurilor(i,vecLegaturi[i].nod2,nr);
                }
                else if(vecLegaturi[i].nod2==n)
                {
                    okk=1;
                    okkk=1;
                    ordinea_nodurilor(i,vecLegaturi[i].nod1,nr);
                }
        if(okkk==1)
        {
            nr++;
            v[nr]=-1;
        }
        for(int i=0; i<nrLegaturi; i++)
            if(vecLegaturi[i].punct1==3||vecLegaturi[i].punct2==3)
                if(vecLegaturi[i].nod1==n)
                    ordinea_nodurilor(i,vecLegaturi[i].nod2,nr);
                else if(vecLegaturi[i].nod2==n)
                    ordinea_nodurilor(i,vecLegaturi[i].nod1,nr);
    }
    else
        for(int i=0; i<nrLegaturi; i++)
            if(i!=j)
            {
                {
                    if(vecLegaturi[i].nod1==n||vecLegaturi[i].nod2==n)
                        if(vecLegaturi[i].nod1==n)
                        {
                            nr++;
                            v[nr]=vecLegaturi[i].nod1;
                            okk=1;
                            ordinea_nodurilor(i,vecLegaturi[i].nod2,nr);
                        }
                        else if(vecLegaturi[i].nod2==n)
                        {
                            nr++;
                            v[nr]=vecLegaturi[i].nod2;
                            okk=1;
                            ordinea_nodurilor(i,vecLegaturi[i].nod1,nr);
                        }
                }
            }
    if(okk==0)
    {
        nr++;
        v[nr]=n;
    }
}

/// Functie generare cod

void GenerareCod()
{
    setcolor(BLACK); /// Text color
    setbkcolor(FUNDAL); /// Text background
    settextjustify(LEFT_TEXT, CENTER_TEXT); /// Aliniere la stanga

    /// Trecere prin noduri
    if(nrLegaturi > 0)
    {
        int ko = 1;
        int kkko = 1;
        for(int j = 0; j < nrLegaturi; j ++)
        {
            if(vecLegaturi[j].nod1 == 1 || vecLegaturi[j].nod2 == 1)
            {
                if(vecLegaturi[j].nod1 == 1)
                {
                    if(verificare(j, vecLegaturi[j].nod2) == 0)
                    {
                        outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + 20, "EROARE:  Codul C++ nu poate fi");
                        outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + 40, "generat!");
                        ko = 0;
                    }
                }
                else if(verificare(j,vecLegaturi[j].nod1) == 0)
                {
                    outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + 20, "EROARE:  Codul C++ nu poate fi");
                    outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + 40, "generat!");
                    ko = 0;
                }
                kkko = 0;
            }
            if(ko == 0) break;
        }
        if(kkko == 1)
        {
            ko = 0;
            outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + 20, "EROARE:  Codul C++ nu poate fi");
            outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + 40, "generat!");
        }
        if(ko == 1)
        {
            int nrnod = 0;
            for(int j = 0; j < nrLegaturi; j ++)
                if(vecLegaturi[j].nod1 == 1 || vecLegaturi[j].nod2 == 1)
                {
                    if(vecLegaturi[j].nod1 == 1)
                    {
                        nrnod ++;
                        v[nrnod] = vecLegaturi[j].nod1;
                        ordinea_nodurilor(j, vecLegaturi[j].nod2, nrnod);
                    }
                    else if(vecLegaturi[j].nod2 == 1)
                    {
                        nrnod++;
                        v[nrnod] = vecLegaturi[j].nod2;
                        ordinea_nodurilor(j, vecLegaturi[j].nod1, nrnod);
                    }
                }

            /// Generare cod CPP
            int yy = 0, xx = 0, ok_if = 0, ok_else = 0;
            for(int k = 1; k <= nrnod; k ++)
            {

                /// Start (Tip 1)
                if(vecNoduri[v[k]].tip == 1)
                {
                    for(int i = 1; i <= 5; i ++, yy += 20)
                    {
                        if(i == 1) outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + yy, "#include <iostream>");
                        else if(i == 2) outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + yy, "#include <cmath>");
                        else if(i == 3) outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + yy, "using namespace std;");
                        else if(i == 4) outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + yy, "int main()");
                        else if(i == 5) outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + yy, "{");
                    }
                    xx += 20;
                }

                /// Stop (Tip 2)
                if(vecNoduri[v[k]].tip == 2)
                {
                    for(int i = 1; i <= 2; i ++, yy += 20)
                    {
                        if(i == 1) outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, "return 0;");
                        else if(i == 2) outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + yy, "}");
                    }
                }

                /// Citire (Tip 3)
                if(vecNoduri[v[k]].tip == 3)
                {
                    char aux1[31] = "cin >> ";
                    int cnt = 6;
                    for(int i = 0; vecNoduri[v[k]].info[i]; i ++)
                        if(vecNoduri[v[k]].info[i] != ',')
                        {
                            aux1[++cnt] = vecNoduri[v[k]].info[i];
                            if(vecNoduri[v[k]].info[i+1] != '\0') strcat(aux1, " >> "), cnt += 4;
                            else strcat(aux1, ";");
                        }
                    outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, aux1);
                    yy += 20;
                }

                /// Afisare (Tip 4)
                if(vecNoduri[v[k]].tip == 4)
                {
                    char aux2[31] = "cout << ";
                    int cnt = 7;
                    for(int i = 0; vecNoduri[v[k]].info[i]; i ++)
                        if(vecNoduri[v[k]].info[i] != ',')
                        {
                            aux2[++cnt] = vecNoduri[v[k]].info[i];
                            if(vecNoduri[v[k]].info[i+1] != '\0') strcat(aux2, " << "), cnt += 4;
                            else strcat(aux2, ";");
                        }
                    outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, aux2);
                    yy += 20;
                }

                /// Declarare (Tip 5)
                if(vecNoduri[v[k]].tip == 5)
                {
                    char aux3[31] = "int ";
                    int cnt = 3;
                    for(int i = 0; vecNoduri[v[k]].info[i]; i ++)
                        if(vecNoduri[v[k]].info[i] != ',')
                        {
                            aux3[++cnt] = vecNoduri[v[k]].info[i];
                            if(vecNoduri[v[k]].info[i+1] != '\0') strcat(aux3, ", "), cnt += 2;
                            else strcat(aux3, ";");
                        }
                    outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, aux3);
                    yy += 20;
                }

                /// Atribuire (Tip 6)
                if(vecNoduri[v[k]].tip == 6)
                {
                    char aux4[31] = "";
                    aux4[0] = vecNoduri[v[k]].info[0];
                    strcat(aux4, " = ");
                    strcat(aux4, vecNoduri[v[k]].info+2);
                    strcat(aux4, ";");
                    outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, aux4);
                    yy += 20;
                }

                /// Conditie (Tip 7)
                if(vecNoduri[v[k]].tip == 7)
                {
                    ok_if = 1;
                    char aux5[31] = "if(";
                    strcat(aux5, vecNoduri[v[k]].info);
                    strcat(aux5, ")");
                    outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, aux5);
                    yy += 20;
                    outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, "{");
                    yy += 20, xx += 20;
                }

                /// Conditie - inchei if-ul si else-ul
                if(v[k] == -1)
                {
                    if(ok_if == 1)
                    {
                        ok_if = 0;
                        xx -= 20;
                        outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, "}");
                        yy += 20; /// inchei if-ul

                        /// verific daca exista un else
                        for(int i = k+1; i <= nrnod; i ++)
                            if(v[i] == -1) ok_else = 1;

                        /// daca exista, continui in generare cu else
                        if(ok_else == 1)
                        {
                            for(int i = 1; i <= 2; i ++, yy += 20)
                            {
                                if(i == 1) outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, "else");
                                else if(i == 2) outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, "{");
                            }
                            xx += 20;
                        }
                    }
                    else if(ok_else == 1) xx -= 20, outtextxy(getmaxx()-getmaxx()/5 + xx, getmaxy()/9 + yy, "}"), yy += 20; /// inchei else-ul
                }
            }
        }
    }
    else
    {
        outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + 20, "EROARE:  Codul C++ nu poate fi");
        outtextxy(getmaxx()-getmaxx()/5, getmaxy()/9 + 40, "generat!");
    }
}

int main()
{
    srand(time(NULL));
    DWORD screenWidth=GetSystemMetrics(SM_CXSCREEN);
    DWORD screenHeight=GetSystemMetrics(SM_CYSCREEN);

    initwindow(screenWidth,screenHeight,"Interschem",-3,-3);
    setbkcolor(FUNDAL);
    cleardevice();

    POINT cursorPosition;
    int mx,i,j, my,page=0,r;
    nrNoduri=0;
    LiniiMeniu();
    setcolor(DARKGRAY);
    for(int i = 1; i <= 14; i ++)
    {
        r = i-1;
        switch(r)
        {
        case 1:
            initbloc(blocuri[i], "Stop", 7, 2);
            break;
        case 2:
            initbloc(blocuri[i], "Citire", 7, 3);
            break;
        case 3:
            initbloc(blocuri[i], "Afisare", 7, 4);
            break;
        case 4:
            initbloc(blocuri[i], "Declarare", 7, 5);
            break;
        case 5:
            initbloc(blocuri[i], "Atribuire", 7, 6);
            break;
        case 6:
            initbloc(blocuri[i], "Conditie", 7, 7);
            break;
        case 7:
            initbloc(blocuri[i], "Back", 7, 8);
            break;
        case 8:
            initbloc(blocuri[i], "Stergere blocuri", 7, 9);
            break;
        case 9:
            initbloc(blocuri[i], "Stergere legaturi", 7, 10);
            break;
        case 10:
            initbloc(blocuri[i], "Exit", 7, 11);
            break;
        case 11:
            initbloc(blocuri[i], "Start", 7, 12);
            break;
        case 12:
            initbloc(blocuri[i], "Run", 7, 13);
            break;
        case 13:
            initbloc(blocuri[i], "Generare cod", 7, 14);
            break;
        }
    }
    nrNoduri++;
    initNod(vecNoduri[nrNoduri], "Start", 7, 1);
    int idNod1, idNod2, p1, p2, okk, okkk;
    nrLegaturi = 0;
    while(1)
    {
        okkk=1;
        while(okkk!=0)
        {
            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();
            GetCursorPos(&cursorPosition);
            mx=cursorPosition.x;
            my=cursorPosition.y-20;
            setbkcolor(FUNDAL);
            cleardevice();

            /// Delia

            settextstyle(10, 0, 10);
            setbkcolor(FUNDAL);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            outtextxy(getmaxx()/2, getmaxy()/4, "INTERSCHEM");

            settextstyle(10, 0, 5);
            setbkcolor(FUNDAL);
            settextjustify(CENTER_TEXT, CENTER_TEXT);
            outtextxy(getmaxx()/2, getmaxy()/3, "Editor & Vizualizator de scheme logice");

            settextstyle(10,0,5);
            citire(270, 300, 80, 50);
            floodfill(270, 300, WHITE);
            afisare(1450, 750, 80, 50);
            floodfill(1450, 750, WHITE);
            declarare(1700, 400, 80, 50);
            floodfill(1700, 400, WHITE);
            conditie(450, 850, 80, 50);
            floodfill(450, 850, WHITE);
            afisare(100, 650, 20, 10);
            floodfill(100, 650, WHITE);
            citire(1800, 950, 20, 10);
            floodfill(1800, 950, WHITE);
            for(i=11; i<=12; i++)
                deseneazabloc(blocuri[i]);
            for(i=11; i<=12; i++)
                if(GetAsyncKeyState(VK_LBUTTON)&& abs(blocuri[i].x - mx)<=textwidth(blocuri[i].info)+10
                        && abs(blocuri[i].y - my)<=textheight(blocuri[i].info)+10)
                {
                    if(blocuri[i].tip==12)
                        okkk=0;
                    if(blocuri[i].tip==11)
                        closegraph();

                }

            page=1-page;
            delay(1);
        }
        okk=1;
        while(okk!=0)
        {
            ///Restart
            settextstyle(10, 0,1);
            setactivepage(page);
            setvisualpage(1-page);
            cleardevice();
            setbkcolor(FUNDAL);
            cleardevice();

            ///Delia
            LiniiMeniu();
            for(i=1; i<=10; i++)
                deseneazabloc(blocuri[i]);
            for(i=13; i<=14; i++)
                deseneazabloc(blocuri[i]);
            for(int k=0; k<nrLegaturi; k++)
                drawLine(vecLegaturi[k].x1,vecLegaturi[k].y1,vecLegaturi[k].x2,vecLegaturi[k].y2, 15-FUNDAL);
            for(j=1; j<=nrNoduri; j++)
                deseneazaNod(vecNoduri[j]);
            GetCursorPos(&cursorPosition);
            mx=cursorPosition.x;
            my=cursorPosition.y-20;
            ///Stergere blocuri & Stergere legaturi && Back
            for(i=8; i<=10; i++)
                if(GetAsyncKeyState(VK_LBUTTON)&& abs(blocuri[i].x - mx)<=textwidth(blocuri[i].info)/2
                        && abs(blocuri[i].y - my)<=textheight(blocuri[i].info)+10)
                {
                    if(blocuri[i].tip==8)
                    {
                        okk=0;
                        break;
                    }
                    if(blocuri[i].tip==9)
                    {
                        int a=blocuri[i].culoare;
                        blocuri[i].culoare=2;
                        int ok=1;
                        delay(100);
                        while(ok!=0)
                        {
                            setactivepage(page);
                            setvisualpage(1-page);
                            cleardevice();
                            GetCursorPos(&cursorPosition);
                            mx=cursorPosition.x;
                            my=cursorPosition.y-20;
                            setbkcolor(FUNDAL);
                            cleardevice();
                            if(GetAsyncKeyState(VK_LBUTTON)&& abs(blocuri[i].x - mx)<=textwidth(blocuri[i].info)+10
                                    && abs(blocuri[i].y - my)<=textheight(blocuri[i].info)+10)
                                ok=0;
                            LiniiMeniu();
                            for(int k=1; k<=10; k++)
                                deseneazabloc(blocuri[k]);
                            for(int k=13; k<=14; k++)
                                deseneazabloc(blocuri[k]);
                            for(int k=0; k<nrLegaturi; k++)
                                drawLine(vecLegaturi[k].x1,vecLegaturi[k].y1,vecLegaturi[k].x2,vecLegaturi[k].y2, 15-FUNDAL);
                            for(j=1; j<=nrNoduri; j++)
                                deseneazaNod(vecNoduri[j]);
                            for(j=2; j<=nrNoduri; j++)
                                if(GetAsyncKeyState(VK_LBUTTON)&& abs(vecNoduri[j].x - mx)<=34
                                        && abs(vecNoduri[j].y - my)<=14)
                                {
                                    for(int k=0; k<=3; k++)
                                        if(vecNoduri[j].pLeg[k].v==1)
                                        {
                                            for(int l=0; l<nrLegaturi; l++)
                                                if((vecNoduri[j].pLeg[k].x==vecLegaturi[l].x1&&vecNoduri[j].pLeg[k].y==vecLegaturi[l].y1)||(vecNoduri[j].pLeg[k].x==vecLegaturi[l].x2&&vecNoduri[j].pLeg[k].y==vecLegaturi[l].y2))
                                                {
                                                    vecNoduri[vecLegaturi[l].nod1].pLeg[vecLegaturi[l].punct1].v=0;
                                                    vecNoduri[vecLegaturi[l].nod2].pLeg[vecLegaturi[l].punct2].v=0;
                                                    for(int p=l; p<nrLegaturi-1; p++)
                                                    {
                                                        vecLegaturi[p].punct1=vecLegaturi[p+1].punct1;
                                                        vecLegaturi[p].punct2=vecLegaturi[p+1].punct2;
                                                        vecLegaturi[p].nod1=vecLegaturi[p+1].nod1;
                                                        vecLegaturi[p].nod2=vecLegaturi[p+1].nod2;
                                                        vecLegaturi[p].x1=vecLegaturi[p+1].x1;
                                                        vecLegaturi[p].x2=vecLegaturi[p+1].x2;
                                                        vecLegaturi[p].y1=vecLegaturi[p+1].y1;
                                                        vecLegaturi[p].y2=vecLegaturi[p+1].y2;
                                                    }
                                                    nrLegaturi--;
                                                    break;
                                                }
                                        }
                                    for(int k=j; k<nrNoduri; k++)
                                    {
                                        int x,y;
                                        x=vecNoduri[k+1].x;
                                        y=vecNoduri[k+1].y;
                                        initNod(vecNoduri[k],vecNoduri[k+1].info, vecNoduri[k+1].culoare,vecNoduri[k+1].tip);
                                        for(int l=0; l<=3; l++)
                                            vecNoduri[k].pLeg[l].v=vecNoduri[k+1].pLeg[l].v;
                                        vecNoduri[k].x=x;
                                        vecNoduri[k].y=y;
                                        if(vecNoduri[k].tip==1)
                                        {
                                            vecNoduri[k].pLeg[0].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[0].y=vecNoduri[k].y+textheight(vecNoduri[k].info)+5;
                                        }
                                        else if(vecNoduri[k].tip ==2)
                                        {
                                            vecNoduri[k].pLeg[0].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[0].y=vecNoduri[k].y-textheight(vecNoduri[k].info)-5;
                                        }
                                        else if(vecNoduri[k].tip==3)
                                        {
                                            vecNoduri[k].pLeg[0].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[0].y=vecNoduri[k].y-textheight(vecNoduri[k].info)-10;
                                            vecNoduri[k].pLeg[1].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[1].y=vecNoduri[k].y+textheight(vecNoduri[k].info)+11;
                                        }
                                        else if(vecNoduri[k].tip ==4)
                                        {
                                            vecNoduri[k].pLeg[0].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[0].y=vecNoduri[k].y-textheight(vecNoduri[k].info)-10;
                                            vecNoduri[k].pLeg[1].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[1].y=vecNoduri[k].y+textheight(vecNoduri[k].info)+11;
                                        }
                                        else if(vecNoduri[k].tip ==5)
                                        {
                                            vecNoduri[k].pLeg[0].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[0].y=vecNoduri[k].y-textheight(vecNoduri[k].info)-5;
                                            vecNoduri[k].pLeg[1].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[1].y=vecNoduri[k].y+textheight(vecNoduri[k].info)+6;
                                        }
                                        else if(vecNoduri[k].tip ==6)
                                        {
                                            vecNoduri[k].pLeg[0].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[0].y=vecNoduri[k].y-textheight(vecNoduri[k].info)-5;
                                            vecNoduri[k].pLeg[1].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[1].y=vecNoduri[k].y+textheight(vecNoduri[k].info)+6;
                                        }
                                        else
                                        {
                                            vecNoduri[k].pLeg[0].x=vecNoduri[i].x;
                                            vecNoduri[k].pLeg[0].y=vecNoduri[i].y-16-9;
                                            vecNoduri[k].pLeg[3].x=vecNoduri[k].x;
                                            vecNoduri[k].pLeg[3].y=vecNoduri[k].y+16+9;
                                            if(textwidth(vecNoduri[k].info)<53)
                                            {
                                                vecNoduri[k].pLeg[1].x=vecNoduri[k].x-53-6;
                                                vecNoduri[k].pLeg[1].y=vecNoduri[k].y;
                                                vecNoduri[k].pLeg[2].x=vecNoduri[k].x+53+6;
                                                vecNoduri[k].pLeg[2].y=vecNoduri[k].y;
                                            }
                                            else
                                            {
                                                vecNoduri[k].pLeg[1].x=vecNoduri[k].x-textwidth(vecNoduri[k].info)-6;
                                                vecNoduri[k].pLeg[1].y=vecNoduri[k].y;
                                                vecNoduri[k].pLeg[2].x=vecNoduri[k].x+textwidth(vecNoduri[k].info)+6;
                                                vecNoduri[k].pLeg[2].y=vecNoduri[k].y;
                                            }
                                        }
                                    }
                                    for(int l=0; l<=3; l++)
                                        vecNoduri[nrNoduri].pLeg[l].v=0;
                                    for(int l=0; l<nrLegaturi; l++)
                                    {
                                        if(vecLegaturi[l].nod1>j)
                                            vecLegaturi[l].nod1--;
                                        if(vecLegaturi[l].nod2>j)
                                            vecLegaturi[l].nod2--;
                                    }
                                    nrNoduri--;
                                }
                            page=1-page;
                            delay(1);
                        }
                        blocuri[i].culoare=a;
                        delay(100);
                    }
                    else if(blocuri[i].tip==10)
                    {
                        int ok=1;
                        int a=blocuri[i].culoare;
                        blocuri[i].culoare=2;
                        delay(100);
                        while(ok!=0)
                        {
                            setactivepage(page);
                            setvisualpage(1-page);
                            cleardevice();
                            GetCursorPos(&cursorPosition);
                            mx=cursorPosition.x;
                            my=cursorPosition.y-20;
                            setbkcolor(FUNDAL);
                            cleardevice();
                            if(GetAsyncKeyState(VK_LBUTTON)&& abs(blocuri[i].x - mx)<=textwidth(blocuri[i].info)
                                    && abs(blocuri[i].y - my)<=textheight(blocuri[i].info)+10)
                                ok=0;
                            LiniiMeniu();
                            for(int k=1; k<=10; k++)
                                deseneazabloc(blocuri[k]);
                            if(GetAsyncKeyState(VK_LBUTTON)&& abs(blocuri[i].x - mx)<=textwidth(blocuri[i].info)
                                    && abs(blocuri[i].y - my)<=textheight(blocuri[i].info)+10)
                                ok=0;
                            for(int k=13; k<=14; k++)
                                deseneazabloc(blocuri[k]);
                            if(GetAsyncKeyState(VK_LBUTTON)&& abs(blocuri[i].x - mx)<=textwidth(blocuri[i].info)
                                    && abs(blocuri[i].y - my)<=textheight(blocuri[i].info)+10)
                                ok=0;
                            for(int k=0; k<nrLegaturi; k++)
                                drawLine(vecLegaturi[k].x1,vecLegaturi[k].y1,vecLegaturi[k].x2,vecLegaturi[k].y2, 15-FUNDAL);
                            for(j=1; j<=nrNoduri; j++)
                                deseneazaNod(vecNoduri[j]);
                            for(j=1; j<=nrNoduri; j++)
                                for(int k=0; k<=3; k++)
                                    if(GetAsyncKeyState(VK_LBUTTON)&&abs(vecNoduri[j].pLeg[k].x - mx)<=5
                                            && abs(vecNoduri[j].pLeg[k].y - my)<=5&&vecNoduri[j].pLeg[k].v==1)
                                    {
                                        for(int l=0; l<nrLegaturi; l++)
                                            if((vecLegaturi[l].x1==vecNoduri[j].pLeg[k].x&&vecLegaturi[l].y1==vecNoduri[j].pLeg[k].y)||(vecLegaturi[l].x2==vecNoduri[j].pLeg[k].x&&vecLegaturi[l].y2==vecNoduri[j].pLeg[k].y))
                                            {
                                                vecNoduri[vecLegaturi[l].nod1].pLeg[vecLegaturi[l].punct1].v=0;
                                                vecNoduri[vecLegaturi[l].nod2].pLeg[vecLegaturi[l].punct2].v=0;
                                                for(int o=l; o<nrLegaturi-1; o++)
                                                {
                                                    vecLegaturi[o].punct1=vecLegaturi[o+1].punct1;
                                                    vecLegaturi[o].punct2=vecLegaturi[o+1].punct2;
                                                    vecLegaturi[o].nod1=vecLegaturi[o+1].nod1;
                                                    vecLegaturi[o].nod2=vecLegaturi[o+1].nod2;
                                                    vecLegaturi[o].x1=vecLegaturi[o+1].x1;
                                                    vecLegaturi[o].x2=vecLegaturi[o+1].x2;
                                                    vecLegaturi[o].y1=vecLegaturi[o+1].y1;
                                                    vecLegaturi[o].y2=vecLegaturi[o+1].y2;
                                                }
                                                nrLegaturi--;
                                                break;
                                            }
                                    }

                            page=1-page;
                            delay(1);
                        }
                        blocuri[i].culoare=a;
                        delay(100);
                    }
                }
            ///Run
            int ko=1;
            for(i=13; i<=14; i++)
                if(GetAsyncKeyState(VK_LBUTTON)&& abs(blocuri[i].x - mx)<=textwidth(blocuri[i].info)
                        && abs(blocuri[i].y - my)<=textheight(blocuri[i].info))
                {
                    if(blocuri[i].tip==13)
                    {
                        int yyy=0,n=0;
                        int a=blocuri[i].culoare;
                        blocuri[i].culoare=2;
                        int kkko=0;
                        if(nrLegaturi>0)
                        {
                            for(j=0; j<nrLegaturi; j++)
                            {
                                if(vecLegaturi[j].nod1==1||vecLegaturi[j].nod2==1)
                                {
                                    kkko=1;
                                    if(vecLegaturi[j].nod1==1)
                                    {
                                        if(verificare(j,vecLegaturi[j].nod2)==0)
                                        {
                                            yyy++;
                                            strcpy(afiseaza[yyy],"EROARE");
                                            myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4,0,8,"EROARE");
                                            ko=0;
                                        }
                                    }
                                    else if(verificare(j,vecLegaturi[j].nod1)==0)
                                    {
                                        yyy++;
                                        strcpy(afiseaza[yyy],"EROARE");
                                        myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4,0,8,"EROARE");
                                        ko=0;
                                    }
                                }
                                if(ko==0)
                                    break;
                            }
                            if(kkko==0)
                            {
                                ko=0;
                                yyy++;
                                strcpy(afiseaza[yyy],"EROARE");
                                myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4,0,8,"EROARE");
                            }
                            if(ko==1)
                            {
                                int nrnod=0;
                                for(j=0; j<nrLegaturi; j++)
                                {
                                    if(vecLegaturi[j].nod1==1||vecLegaturi[j].nod2==1)
                                    {
                                        if(vecLegaturi[j].nod1==1)
                                        {
                                            nrnod++;
                                            v[nrnod]=vecLegaturi[j].nod1;
                                            ordinea_nodurilor(j,vecLegaturi[j].nod2,nrnod);
                                        }
                                        else if(vecLegaturi[j].nod2==1)
                                        {
                                            nrnod++;
                                            v[nrnod]=vecLegaturi[j].nod2;
                                            ordinea_nodurilor(j,vecLegaturi[j].nod1,nrnod);
                                        }
                                    }
                                }
                                nrnec=0;
                                for(int k=1; k<=nrnod; k++)
                                {
                                    if(vecNoduri[v[k]].tip==3)///Citire
                                    {
                                        for(int l=0; l<strlen(vecNoduri[v[k]].info); l++)
                                            if(vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')
                                                for(int o=0; o<nrnec; o++)
                                                    if(vecNoduri[v[k]].info[l]==necunoscute[o])
                                                    {
                                                        int ok=1;
                                                        delay(1);
                                                        n++;
                                                        while(ok==1)
                                                        {
                                                            setactivepage(page);
                                                            setvisualpage(1-page);
                                                            cleardevice();
                                                            setbkcolor(FUNDAL);
                                                            cleardevice();
                                                            LiniiMeniu();
                                                            for(int u=1; u<=n; u++)
                                                                myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4+u*14,0,8,citeste[u]);
                                                            for(int u=1; u<=yyy; u++)
                                                                myOuttextXY(getmaxx()-getmaxx()/15,getmaxy()-getmaxy()/4+u*14,0,8,afiseaza[u]);

                                                            for(int u=1; u<=10; u++)
                                                                deseneazabloc(blocuri[u]);
                                                            for(int u=13; u<=14; u++)
                                                                deseneazabloc(blocuri[u]);
                                                            for(int u=0; u<nrLegaturi; u++)
                                                                drawLine(vecLegaturi[u].x1,vecLegaturi[u].y1,vecLegaturi[u].x2,vecLegaturi[u].y2, 15-FUNDAL);
                                                            for(int u=1; u<=nrNoduri; u++)
                                                                deseneazaNod(vecNoduri[u]);
                                                            delay(30);
                                                            if(GetAsyncKeyState(VK_BACK)&&citeste[n]!=NULL)
                                                                citeste[n][strlen(citeste[n])-1]=NULL;
                                                            if(kbhit())
                                                            {
                                                                char ch=getch();
                                                                if(ch!=8&&ch!=13)
                                                                    citeste[n][strlen(citeste[n])]=ch;
                                                                if(ch==13)
                                                                    ok=0;
                                                            }
                                                            page=1-page;
                                                            delay(1);
                                                        }
                                                        strcpy(valori[o],citeste[n]);
                                                        break;
                                                    }
                                    }
                                    else if(vecNoduri[v[k]].tip==4)///Afiseaza
                                    {
                                        for(int l=0; l<strlen(vecNoduri[v[k]].info); l++)
                                            if(vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')
                                                for(int o=0; o<nrnec; o++)
                                                    if(vecNoduri[v[k]].info[l]==necunoscute[o])
                                                    {
                                                        yyy++;
                                                        strcpy(afiseaza[yyy],valori[o]);
                                                        myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4+yyy*14,0,8,afiseaza[yyy]);
                                                        break;
                                                    }
                                    }
                                    else if(vecNoduri[v[k]].tip==5)///Declarare
                                    {
                                        for(int l=0; l<strlen(vecNoduri[v[k]].info); l++)
                                            if(vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')
                                                necunoscute[nrnec++]=vecNoduri[v[k]].info[l];
                                    }
                                    else if(vecNoduri[v[k]].tip==6)///Atribuire
                                    {
                                        char aux[MAX1], op[MAX1],caracter;
                                        strcpy(aux,vecNoduri[v[k]].info);
                                        for(int l=2; l<strlen(vecNoduri[v[k]].info); l++)
                                            if((vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')&&!(vecNoduri[v[k]].info[l+1]>='a'&&vecNoduri[v[k]].info[l+1]<='z')&&!(vecNoduri[v[k]].info[l-1]>='a'&&vecNoduri[v[k]].info[l-1]<='z'))
                                            {
                                                strcpy(op,vecNoduri[v[k]].info+l+1);
                                                caracter=vecNoduri[v[k]].info[l];
                                                vecNoduri[v[k]].info[l]=NULL;
                                                for(int o=0; o<nrnec; o++)
                                                    if(caracter==necunoscute[o])
                                                    {
                                                        strcat(vecNoduri[v[k]].info,valori[o]);
                                                        break;
                                                    }
                                                strcat(vecNoduri[v[k]].info,op);
                                            }
                                        char val[MAX1];
                                        for(int o=0; o<nrnec; o++)
                                            if(vecNoduri[v[k]].info[0]==necunoscute[o])
                                            {
                                                mytostring(EvaluatorMatematic(vecNoduri[v[k]].info+2),valori[o]);
                                                break;
                                            }
                                        strcpy(vecNoduri[v[k]].info,aux);
                                    }
                                    else if(vecNoduri[v[k]].tip==7)
                                    {
                                        int aa;
                                        char auxx[MAX1], op[MAX1],caracter;
                                        strcpy(auxx,vecNoduri[v[k]].info);
                                        aa=k;
                                        for(int l=0; l<strlen(vecNoduri[v[k]].info); l++)
                                            if((vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')&&!(vecNoduri[v[k]].info[l+1]>='a'&&vecNoduri[v[k]].info[l+1]<='z')&&!(vecNoduri[v[k]].info[l-1]>='a'&&vecNoduri[v[k]].info[l-1]<='z'))
                                            {
                                                strcpy(op,vecNoduri[v[k]].info+l+1);
                                                caracter=vecNoduri[v[k]].info[l];
                                                vecNoduri[v[k]].info[l]=NULL;
                                                for(int o=0; o<nrnec; o++)
                                                    if(caracter==necunoscute[o])
                                                    {
                                                        strcat(vecNoduri[v[k]].info,valori[o]);
                                                        break;
                                                    }
                                                strcat(vecNoduri[v[k]].info,op);
                                            }
                                        if(Conditie(vecNoduri[v[k]].info)==1)
                                        {
                                            while(v[k]!=-1)
                                            {
                                                if(vecNoduri[v[k]].tip==3)///Citire
                                                {
                                                    for(int l=0; l<strlen(vecNoduri[v[k]].info); l++)
                                                        if(vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')
                                                            for(int o=0; o<nrnec; o++)
                                                                if(vecNoduri[v[k]].info[l]==necunoscute[o])
                                                                {
                                                                    int ok=1;
                                                                    delay(1);
                                                                    n++;
                                                                    while(ok==1)
                                                                    {
                                                                        setactivepage(page);
                                                                        setvisualpage(1-page);
                                                                        cleardevice();
                                                                        setbkcolor(FUNDAL);
                                                                        cleardevice();
                                                                        LiniiMeniu();
                                                                        for(int u=1; u<=n; u++)
                                                                            myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4+u*14,0,8,citeste[u]);
                                                                        for(int u=1; u<=yyy; u++)
                                                                            myOuttextXY(getmaxx()-getmaxx()/15,getmaxy()-getmaxy()/4+u*14,0,8,afiseaza[u]);
                                                                        for(int u=1; u<=10; u++)
                                                                            deseneazabloc(blocuri[u]);
                                                                        for(int u=13; u<=14; u++)
                                                                            deseneazabloc(blocuri[u]);
                                                                        for(int u=0; u<nrLegaturi; u++)
                                                                            drawLine(vecLegaturi[u].x1,vecLegaturi[u].y1,vecLegaturi[u].x2,vecLegaturi[u].y2, 15-FUNDAL);
                                                                        for(int u=1; u<=nrNoduri; u++)
                                                                            deseneazaNod(vecNoduri[u]);
                                                                        delay(30);
                                                                        if(GetAsyncKeyState(VK_BACK)&&citeste[n]!=NULL)
                                                                            citeste[n][strlen(citeste[n])-1]=NULL;
                                                                        if(kbhit())
                                                                        {
                                                                            char ch=getch();
                                                                            if(ch!=8&&ch!=13)
                                                                                citeste[n][strlen(citeste[n])]=ch;
                                                                            if(ch==13)
                                                                                ok=0;
                                                                        }
                                                                        page=1-page;
                                                                        delay(1);
                                                                    }
                                                                    strcpy(valori[o],citeste[n]);
                                                                    break;
                                                                }
                                                }
                                                else if(vecNoduri[v[k]].tip==4)///Afiseaza
                                                {
                                                    for(int l=0; l<strlen(vecNoduri[v[k]].info); l++)
                                                        if(vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')
                                                            for(int o=0; o<nrnec; o++)
                                                                if(vecNoduri[v[k]].info[l]==necunoscute[o])
                                                                {
                                                                    yyy++;
                                                                    strcpy(afiseaza[yyy],valori[o]);
                                                                    myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4+yyy*14,0,8,afiseaza[yyy]);
                                                                    break;
                                                                }
                                                }
                                                else if(vecNoduri[v[k]].tip==5)///Declarare
                                                {
                                                    for(int l=0; l<strlen(vecNoduri[v[k]].info); l++)
                                                        if(vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')
                                                            necunoscute[nrnec++]=vecNoduri[v[k]].info[l];
                                                }
                                                else if(vecNoduri[v[k]].tip==6)///Atribuire
                                                {
                                                    char aux[MAX1], op[MAX1],caracter;
                                                    strcpy(aux,vecNoduri[v[k]].info);
                                                    for(int l=2; l<strlen(vecNoduri[v[k]].info); l++)
                                                        if((vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')&&!(vecNoduri[v[k]].info[l+1]>='a'&&vecNoduri[v[k]].info[l+1]<='z')&&!(vecNoduri[v[k]].info[l-1]>='a'&&vecNoduri[v[k]].info[l-1]<='z'))
                                                        {
                                                            strcpy(op,vecNoduri[v[k]].info+l+1);
                                                            caracter=vecNoduri[v[k]].info[l];
                                                            vecNoduri[v[k]].info[l]=NULL;
                                                            for(int o=0; o<nrnec; o++)
                                                                if(caracter==necunoscute[o])
                                                                {
                                                                    strcat(vecNoduri[v[k]].info,valori[o]);
                                                                    break;
                                                                }
                                                            strcat(vecNoduri[v[k]].info,op);
                                                        }
                                                    char val[MAX1];
                                                    for(int o=0; o<nrnec; o++)
                                                        if(vecNoduri[v[k]].info[0]==necunoscute[o])
                                                        {
                                                            mytostring(EvaluatorMatematic(vecNoduri[v[k]].info+2),valori[o]);
                                                            break;
                                                        }
                                                    strcpy(vecNoduri[v[k]].info,aux);
                                                }
                                                k++;
                                            }
                                            k++;
                                            int okkkk=0;
                                            for(int l=k; l<=nrnod; l++)
                                                if(v[k]==-1)
                                                {
                                                    okkkk=1;
                                                    break;
                                                }
                                            if(okkkk==1)
                                                while(v[k]!=-1)
                                                    k++;
                                        }
                                        else
                                        {
                                            while(v[k]!=-1)
                                                k++;
                                            k++;
                                            int okkkk=0;
                                            for(int l=k; l<=nrnod; l++)
                                                if(v[l]==-1)
                                                {
                                                    okkkk=1;
                                                    break;
                                                }
                                            if(okkkk==1)
                                                while(v[k]!=-1)
                                                {
                                                    if(vecNoduri[v[k]].tip==3)///Citire
                                                    {
                                                        for(int l=0; l<strlen(vecNoduri[v[k]].info); l++)
                                                            if(vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')
                                                                for(int o=0; o<nrnec; o++)
                                                                    if(vecNoduri[v[k]].info[l]==necunoscute[o])
                                                                    {
                                                                        int ok=1;
                                                                        delay(1);
                                                                        n++;
                                                                        while(ok==1)
                                                                        {
                                                                            setactivepage(page);
                                                                            setvisualpage(1-page);
                                                                            cleardevice();
                                                                            setbkcolor(FUNDAL);
                                                                            cleardevice();
                                                                            LiniiMeniu();
                                                                            for(int u=1; u<=n; u++)
                                                                                myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4+u*14,0,8,citeste[u]);
                                                                            for(int u=1; u<=yyy; u++)
                                                                                myOuttextXY(getmaxx()-getmaxx()/15,getmaxy()-getmaxy()/4+u*14,0,8,afiseaza[u]);

                                                                            for(int u=1; u<=10; u++)
                                                                                deseneazabloc(blocuri[u]);
                                                                            for(int u=13; u<=14; u++)
                                                                                deseneazabloc(blocuri[u]);
                                                                            for(int u=0; u<nrLegaturi; u++)
                                                                                drawLine(vecLegaturi[u].x1,vecLegaturi[u].y1,vecLegaturi[u].x2,vecLegaturi[u].y2, 15-FUNDAL);
                                                                            for(int u=1; u<=nrNoduri; u++)
                                                                                deseneazaNod(vecNoduri[u]);
                                                                            delay(30);
                                                                            if(GetAsyncKeyState(VK_BACK)&&citeste[n]!=NULL)
                                                                                citeste[n][strlen(citeste[n])-1]=NULL;
                                                                            if(kbhit())
                                                                            {
                                                                                char ch=getch();
                                                                                if(ch!=8&&ch!=13)
                                                                                    citeste[n][strlen(citeste[n])]=ch;
                                                                                if(ch==13)
                                                                                    ok=0;
                                                                            }
                                                                            page=1-page;
                                                                            delay(1);
                                                                        }
                                                                        strcpy(valori[o],citeste[n]);
                                                                        break;
                                                                    }
                                                    }
                                                    else if(vecNoduri[v[k]].tip==4)///Afiseaza
                                                    {
                                                        for(int l=0; l<strlen(vecNoduri[v[k]].info); l++)
                                                            if(vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')
                                                                for(int o=0; o<nrnec; o++)
                                                                    if(vecNoduri[v[k]].info[l]==necunoscute[o])
                                                                    {
                                                                        yyy++;
                                                                        strcpy(afiseaza[yyy],valori[o]);
                                                                        myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4+yyy*14,0,8,afiseaza[yyy]);
                                                                        break;
                                                                    }
                                                    }
                                                    else if(vecNoduri[v[k]].tip==5)///Declarare
                                                    {
                                                        for(int l=0; l<strlen(vecNoduri[v[k]].info); l++)
                                                            if(vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')
                                                                necunoscute[nrnec++]=vecNoduri[v[k]].info[l];
                                                    }
                                                    else if(vecNoduri[v[k]].tip==6)///Atribuire
                                                    {
                                                        char aux[MAX1], op[MAX1],caracter;
                                                        strcpy(aux,vecNoduri[v[k]].info);
                                                        for(int l=2; l<strlen(vecNoduri[v[k]].info); l++)
                                                            if((vecNoduri[v[k]].info[l]>='a'&&vecNoduri[v[k]].info[l]<='z')&&!(vecNoduri[v[k]].info[l+1]>='a'&&vecNoduri[v[k]].info[l+1]<='z')&&!(vecNoduri[v[k]].info[l-1]>='a'&&vecNoduri[v[k]].info[l-1]<='z'))
                                                            {
                                                                strcpy(op,vecNoduri[v[k]].info+l+1);
                                                                caracter=vecNoduri[v[k]].info[l];
                                                                vecNoduri[v[k]].info[l]=NULL;
                                                                for(int o=0; o<nrnec; o++)
                                                                    if(caracter==necunoscute[o])
                                                                    {
                                                                        strcat(vecNoduri[v[k]].info,valori[o]);
                                                                        break;
                                                                    }
                                                                strcat(vecNoduri[v[k]].info,op);
                                                            }
                                                        char val[MAX1];
                                                        for(int o=0; o<nrnec; o++)
                                                            if(vecNoduri[v[k]].info[0]==necunoscute[o])
                                                            {
                                                                mytostring(EvaluatorMatematic(vecNoduri[v[k]].info+2),valori[o]);
                                                                break;
                                                            }
                                                        strcpy(vecNoduri[v[k]].info,aux);
                                                    }
                                                    k++;
                                                }
                                        }
                                        strcpy(vecNoduri[v[aa]].info,auxx);
                                    }
                                }
                            }
                        }
                        else
                        {
                            yyy++;
                            strcpy(afiseaza[yyy],"EROARE");
                            myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4,0,8,"EROARE");
                        }
                        int kko=1;
                        delay(50);
                        while(kko==1)
                        {
                            setactivepage(page);
                            setvisualpage(1-page);
                            cleardevice();
                            setbkcolor(FUNDAL);
                            cleardevice();
                            LiniiMeniu();
                            GetCursorPos(&cursorPosition);
                            mx=cursorPosition.x;
                            my=cursorPosition.y-20;
                            for(int u=1; u<=n; u++)
                                myOuttextXY(getmaxx()-getmaxx()/5,getmaxy()-getmaxy()/4+u*14,0,8,citeste[u]);
                            for(int u=1; u<=yyy; u++)
                                myOuttextXY(getmaxx()-getmaxx()/15,getmaxy()-getmaxy()/4+u*14,0,8,afiseaza[u]);

                            for(int u=1; u<=10; u++)
                                deseneazabloc(blocuri[u]);
                            for(int u=13; u<=14; u++)
                                deseneazabloc(blocuri[u]);
                            for(int u=0; u<nrLegaturi; u++)
                                drawLine(vecLegaturi[u].x1,vecLegaturi[u].y1,vecLegaturi[u].x2,vecLegaturi[u].y2, 15-FUNDAL);
                            for(int u=1; u<=nrNoduri; u++)
                                deseneazaNod(vecNoduri[u]);
                            if(GetAsyncKeyState(VK_LBUTTON)&& abs(blocuri[i].x - mx)<=textwidth(blocuri[i].info)
                                    && abs(blocuri[i].y - my)<=textheight(blocuri[i].info))
                                kko=0;
                            page=1-page;
                            delay(1);
                        }
                        blocuri[i].culoare=a;
                        for(int u=1; u<=n; u++)
                            for(int o=strlen(citeste[u]); o>=0; o--)
                                citeste[u][o]=NULL;
                        delay(100);
                    }
                    else if(blocuri[i].tip == 14)
                    {
                        int a=blocuri[i].culoare;
                        blocuri[i].culoare=2;
                        int ok=1;
                        delay(100);
                        while(ok==1)
                        {
                            setactivepage(page);
                            setvisualpage(1-page);
                            cleardevice();
                            setbkcolor(FUNDAL);
                            cleardevice();
                            LiniiMeniu();
                            for(j=1; j<=10; j++)
                                deseneazabloc(blocuri[j]);
                            for(j=13; j<=14; j++)
                                deseneazabloc(blocuri[j]);
                            for(int k=0; k<nrLegaturi; k++)
                                drawLine(vecLegaturi[k].x1,vecLegaturi[k].y1,vecLegaturi[k].x2,vecLegaturi[k].y2, 15-FUNDAL);
                            for(j=1; j<=nrNoduri; j++)
                                deseneazaNod(vecNoduri[j]);
                            GetCursorPos(&cursorPosition);
                            mx=cursorPosition.x;
                            my=cursorPosition.y-20;
                            GenerareCod();
                            if(GetAsyncKeyState(VK_LBUTTON)&& abs(blocuri[i].x - mx)<=textwidth(blocuri[i].info)
                                    && abs(blocuri[i].y - my)<=textheight(blocuri[i].info))
                                ok=0;
                            page=1-page;
                            delay(1);
                        }
                        blocuri[i].culoare=a;
                        delay(100);
                    }
                }
            ///Spawnare blocuri
            for(i=1; i<=7; i++)
            {
                if(GetAsyncKeyState(VK_LBUTTON)&& abs(blocuri[i].x - mx)<=textwidth(blocuri[i].info)
                        && abs(blocuri[i].y - my)<=textheight(blocuri[i].info))
                {
                    nrNoduri++;
                    switch(i-1)
                    {
                    case 1:
                        initNod(vecNoduri[nrNoduri],"Stop", 7,2);
                        break;/// Nod tip 2
                    case 2:
                        initNod(vecNoduri[nrNoduri],"Citire", 7,3);
                        break;/// Nod tip 3
                    case 3:
                        initNod(vecNoduri[nrNoduri],"Afisare", 7,4);
                        break;/// Nod tip 4
                    case 4:
                        initNod(vecNoduri[nrNoduri],"Declarare", 7,5);
                        break;/// Nod tip 5
                    case 5:
                        initNod(vecNoduri[nrNoduri],"Atribuire", 7,6);
                        break;/// Nod tip 5
                    case 6:
                        initNod(vecNoduri[nrNoduri],"Conditie", 7,7);
                        break;/// Nod tip 6
                    }
                    deseneazaNod(vecNoduri[nrNoduri]);
                    delay(100);
                }
            }
            ///Noduri
            for (i=1; i<=nrNoduri; i++)
            {
                if(GetAsyncKeyState(VK_LBUTTON)&& abs(vecNoduri[i].x - mx)<=34
                        && abs(vecNoduri[i].y - my)<=14)///((mx==px&&my==py)||(mx==px-1&&my==py)||(mx==px-1&&my==my-1)||(mx==px&&my==py-1)||(mx==px+1&&my==py-1)||(mx==px+1&&my==py)||(mx==px+1&&my==py+1)||(mx==px&&my==py+1)||(mx==px-1&&my==py+1))
                {
                    int ok=1;
                    delay(100);
                    while(ok!=0)
                    {
                        setactivepage(page);
                        setvisualpage(1-page);
                        cleardevice();
                        GetCursorPos(&cursorPosition);
                        mx=cursorPosition.x;
                        my=cursorPosition.y-20;
                        vecNoduri[i].x=mx;
                        vecNoduri[i].y=my;
                        setbkcolor(FUNDAL);
                        cleardevice();
                        LiniiMeniu();
                        for(j=1; j<=10; j++)
                            deseneazabloc(blocuri[j]);
                        for(j=13; j<=14; j++)
                            deseneazabloc(blocuri[j]);
                        for(j=1; j<=nrNoduri; j++)
                            deseneazaNod(vecNoduri[j]);
                        if(GetAsyncKeyState(VK_LBUTTON))
                            ok=0;
                        for(int k=0; k<nrLegaturi; k++)
                            drawLine(vecNoduri[vecLegaturi[k].nod1].pLeg[vecLegaturi[k].punct1].x,vecNoduri[vecLegaturi[k].nod1].pLeg[vecLegaturi[k].punct1].y,vecNoduri[vecLegaturi[k].nod2].pLeg[vecLegaturi[k].punct2].x,vecNoduri[vecLegaturi[k].nod2].pLeg[vecLegaturi[k].punct2].y, 15-FUNDAL);
                        if(GetAsyncKeyState(VK_LBUTTON))
                            ok=0;
                        if(vecNoduri[i].tip==1)
                        {
                            vecNoduri[i].pLeg[0].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[0].y=vecNoduri[i].y+textheight(vecNoduri[i].info)+5;
                        }
                        else if(vecNoduri[i].tip ==2)
                        {
                            vecNoduri[i].pLeg[0].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[0].y=vecNoduri[i].y-textheight(vecNoduri[i].info)-5;
                        }
                        else if(vecNoduri[i].tip==3)
                        {
                            vecNoduri[i].pLeg[0].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[0].y=vecNoduri[i].y-textheight(vecNoduri[i].info)-10;
                            vecNoduri[i].pLeg[1].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[1].y=vecNoduri[i].y+textheight(vecNoduri[i].info)+11;
                        }
                        else if(vecNoduri[i].tip ==4)
                        {
                            vecNoduri[i].pLeg[0].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[0].y=vecNoduri[i].y-textheight(vecNoduri[i].info)-10;
                            vecNoduri[i].pLeg[1].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[1].y=vecNoduri[i].y+textheight(vecNoduri[i].info)+11;
                        }
                        else if(vecNoduri[i].tip ==5)
                        {
                            vecNoduri[i].pLeg[0].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[0].y=vecNoduri[i].y-textheight(vecNoduri[i].info)-5;
                            vecNoduri[i].pLeg[1].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[1].y=vecNoduri[i].y+textheight(vecNoduri[i].info)+6;
                        }
                        else if(vecNoduri[i].tip ==6)
                        {
                            vecNoduri[i].pLeg[0].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[0].y=vecNoduri[i].y-textheight(vecNoduri[i].info)-5;
                            vecNoduri[i].pLeg[1].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[1].y=vecNoduri[i].y+textheight(vecNoduri[i].info)+6;
                        }
                        else
                        {
                            vecNoduri[i].pLeg[0].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[0].y=vecNoduri[i].y-16-9;
                            vecNoduri[i].pLeg[3].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[3].y=vecNoduri[i].y+9+16;
                            if(textwidth(vecNoduri[i].info)<53)
                            {
                                vecNoduri[i].pLeg[1].x=vecNoduri[i].x-53-6;
                                vecNoduri[i].pLeg[1].y=vecNoduri[i].y;
                                vecNoduri[i].pLeg[2].x=vecNoduri[i].x+53+6;
                                vecNoduri[i].pLeg[2].y=vecNoduri[i].y;
                            }
                            else
                            {
                                vecNoduri[i].pLeg[1].x=vecNoduri[i].x-textwidth(vecNoduri[i].info)-6;
                                vecNoduri[i].pLeg[1].y=vecNoduri[i].y;
                                vecNoduri[i].pLeg[2].x=vecNoduri[i].x+textwidth(vecNoduri[i].info)+6;
                                vecNoduri[i].pLeg[2].y=vecNoduri[i].y;
                            }
                        }
                        for(int l=0; l<nrLegaturi; l++)
                        {
                            if(vecLegaturi[l].nod1==i)
                            {
                                for(int k=0; k<4; k++)
                                    if(vecLegaturi[l].punct1==k)
                                    {
                                        vecLegaturi[l].x1=vecNoduri[i].pLeg[k].x;
                                        vecLegaturi[l].y1=vecNoduri[i].pLeg[k].y;
                                    }
                            }
                            if(vecLegaturi[l].nod2==i)
                            {
                                for(int k=0; k<4; k++)
                                    if(vecLegaturi[l].punct2==k)
                                    {
                                        vecLegaturi[l].x2=vecNoduri[i].pLeg[k].x;
                                        vecLegaturi[l].y2=vecNoduri[i].pLeg[k].y;
                                    }
                            }
                        }
                        if(GetAsyncKeyState(VK_LBUTTON))
                            ok=0;
                        for(j=1; j<=nrNoduri; j++)
                            deseneazaNod(vecNoduri[j]);
                        if(GetAsyncKeyState(VK_LBUTTON))
                            ok=0;
                        page=1-page;
                        delay(1);
                    }
                    delay(100);
                }
            }
            ///Modificare scris
            for (i=1; i<=nrNoduri; i++)
            {
                if(GetAsyncKeyState(VK_RBUTTON)&& abs(vecNoduri[i].x - mx)<=34
                        && abs(vecNoduri[i].y - my)<=34&&vecNoduri[i].tip!=1&&vecNoduri[i].tip!=2)
                {
                    delay(100);
                    int ok=1;
                    while(ok!=0)
                    {
                        setactivepage(page);
                        setvisualpage(1-page);
                        cleardevice();
                        setbkcolor(FUNDAL);
                        cleardevice();
                        LiniiMeniu();
                        for(j=1; j<=10; j++)
                            deseneazabloc(blocuri[j]);
                        for(j=13; j<=14; j++)
                            deseneazabloc(blocuri[j]);
                        if(GetAsyncKeyState(VK_LBUTTON))
                            ok=0;
                        delay(30);
                        if(GetAsyncKeyState(VK_BACK)&&vecNoduri[i].info!=NULL)
                            vecNoduri[i].info[strlen(vecNoduri[i].info)-1]=NULL;
                        if(kbhit())
                        {
                            char ch=getch();
                            if(ch!=8)
                                vecNoduri[i].info[strlen(vecNoduri[i].info)]=ch;
                        }
                        for(int k=0; k<nrLegaturi; k++)
                            drawLine(vecNoduri[vecLegaturi[k].nod1].pLeg[vecLegaturi[k].punct1].x,vecNoduri[vecLegaturi[k].nod1].pLeg[vecLegaturi[k].punct1].y,vecNoduri[vecLegaturi[k].nod2].pLeg[vecLegaturi[k].punct2].x,vecNoduri[vecLegaturi[k].nod2].pLeg[vecLegaturi[k].punct2].y, 15-FUNDAL);
                        if(GetAsyncKeyState(VK_LBUTTON))
                            ok=0;
                        if(GetAsyncKeyState(VK_LBUTTON))
                            ok=0;
                        if(vecNoduri[i].tip==7)
                        {
                            vecNoduri[i].pLeg[0].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[0].y=vecNoduri[i].y-16-9;
                            vecNoduri[i].pLeg[3].x=vecNoduri[i].x;
                            vecNoduri[i].pLeg[3].y=vecNoduri[i].y+9+16;
                            if(textwidth(vecNoduri[i].info)<53)
                            {
                                vecNoduri[i].pLeg[1].x=vecNoduri[i].x-53-6;
                                vecNoduri[i].pLeg[1].y=vecNoduri[i].y;
                                vecNoduri[i].pLeg[2].x=vecNoduri[i].x+53+6;
                                vecNoduri[i].pLeg[2].y=vecNoduri[i].y;
                            }
                            else
                            {
                                vecNoduri[i].pLeg[1].x=vecNoduri[i].x-textwidth(vecNoduri[i].info)-6;
                                vecNoduri[i].pLeg[1].y=vecNoduri[i].y;
                                vecNoduri[i].pLeg[2].x=vecNoduri[i].x+textwidth(vecNoduri[i].info)+6;
                                vecNoduri[i].pLeg[2].y=vecNoduri[i].y;
                            }
                            for(j=0; j<nrLegaturi; j++)
                                if(vecLegaturi[j].nod1==i)
                                {
                                    if(vecLegaturi[j].punct1==1)
                                    {
                                        vecLegaturi[j].x1=vecNoduri[i].pLeg[1].x;
                                        vecLegaturi[j].y1=vecNoduri[i].pLeg[1].y;
                                    }
                                    else if(vecLegaturi[j].punct1==2)
                                    {
                                        vecLegaturi[j].x1=vecNoduri[i].pLeg[2].x;
                                        vecLegaturi[j].y1=vecNoduri[i].pLeg[2].y;
                                    }
                                }
                                else if(vecLegaturi[j].nod2==i)
                                {
                                    if(vecLegaturi[j].punct2==1)
                                    {
                                        vecLegaturi[j].x2=vecNoduri[i].pLeg[1].x;
                                        vecLegaturi[j].y2=vecNoduri[i].pLeg[1].y;
                                    }
                                    else if(vecLegaturi[j].punct2==2)
                                    {
                                        vecLegaturi[j].x2=vecNoduri[i].pLeg[2].x;
                                        vecLegaturi[j].y2=vecNoduri[i].pLeg[2].y;
                                    }
                                }
                        }
                        for(j=1; j<=nrNoduri; j++)
                            deseneazaNod(vecNoduri[j]);
                        if(GetAsyncKeyState(VK_LBUTTON))
                            ok=0;
                        page=1-page;
                        delay(1);
                    }
                    delay(100);
                }
            }
            ///Legaturi
            if(nrNoduri>1)
                for(i=1; i<=nrNoduri; i++)
                    for(j=0; j<4; j++)
                        if(GetAsyncKeyState(VK_LBUTTON)&&abs(vecNoduri[i].pLeg[j].x - mx)<=5
                                && abs(vecNoduri[i].pLeg[j].y - my)<=5&&vecNoduri[i].pLeg[j].v==0)
                        {
                            delay(1);
                            int x1,x2,y1,y2,click;
                            vecLegaturi[nrLegaturi].nod1=i;
                            vecLegaturi[nrLegaturi].punct1=j;
                            vecLegaturi[nrLegaturi].x1=vecNoduri[i].pLeg[j].x;
                            vecLegaturi[nrLegaturi].y1=vecNoduri[i].pLeg[j].y;
                            x1=vecNoduri[i].pLeg[j].x;
                            y1=vecNoduri[i].pLeg[j].y;
                            vecNoduri[i].pLeg[j].v=1;
                            click=0;
                            while(click==0)
                            {
                                setactivepage(page);
                                setvisualpage(1-page);
                                cleardevice();
                                GetCursorPos(&cursorPosition);
                                mx=cursorPosition.x;
                                my=cursorPosition.y-20;
                                setbkcolor(FUNDAL);
                                cleardevice();
                                LiniiMeniu();
                                drawLine(x1,y1,mx,my, 15-FUNDAL);
                                for(int k=1; k<=10; k++)
                                    deseneazabloc(blocuri[k]);
                                for(int k=13; k<=14; k++)
                                    deseneazabloc(blocuri[k]);
                                for(int k=1; k<=nrNoduri; k++)
                                    deseneazaNod(vecNoduri[k]);
                                for(int k=0; k<nrLegaturi; k++)
                                    drawLine(vecLegaturi[k].x1,vecLegaturi[k].y1,vecLegaturi[k].x2,vecLegaturi[k].y2, 15-FUNDAL);
                                for(int l=1; l<=nrNoduri; l++)
                                    for(int k=0; k<4; k++)
                                        if(GetAsyncKeyState(VK_LBUTTON)&&abs(vecNoduri[l].pLeg[k].x - mx)<=5
                                                && abs(vecNoduri[l].pLeg[k].y - my)<=5&&vecNoduri[l].pLeg[k].v==0)
                                        {
                                            click=1;
                                            vecLegaturi[nrLegaturi].nod2=l;
                                            vecLegaturi[nrLegaturi].punct2=k;
                                            vecLegaturi[nrLegaturi].x2=vecNoduri[l].pLeg[k].x;
                                            vecLegaturi[nrLegaturi].y2=vecNoduri[l].pLeg[k].y;
                                            vecNoduri[l].pLeg[k].v=1;
                                        }
                                page=1-page;
                                delay(2);
                            }
                            nrLegaturi++;
                        }
            ///
            page=1-page;
            delay(1);
        }
    }
    getch();
    closegraph();
    return 0;
}
