#include <iostream>
#include <string.h>
struct nod{
  int val;
  nod *next,*below;
};
class big_integer_number{
  nod *start=NULL,*stop=NULL;
  bool pozitiv;
public:
  big_integer_number(){}
  friend std::istream& operator>> (std::istream&,big_integer_number&);
  friend std::ostream& operator<< (std::ostream&,big_integer_number&);
  friend big_integer_number operator+(big_integer_number,big_integer_number);
  friend big_integer_number operator-(big_integer_number,big_integer_number);
  friend big_integer_number operator*(big_integer_number,big_integer_number);
  friend big_integer_number operator/(big_integer_number,big_integer_number);
  friend big_integer_number operator%(big_integer_number,big_integer_number);
  friend big_integer_number GCD(big_integer_number,big_integer_number);//Greatest common divisor
  friend class big_rational_number;
  ~big_integer_number(){}
};
class big_rational_number{
   big_integer_number numerator,denominator;
public:
  big_rational_number(){}
  friend std::istream& operator>> (std::istream&,big_rational_number&);
  friend std::ostream& operator<< (std::ostream&,big_rational_number&);
  friend big_rational_number operator+(big_rational_number,big_rational_number);
  friend big_rational_number operator*(big_rational_number,big_rational_number);
  friend big_rational_number REDUCE(big_rational_number);
  ~big_rational_number(){}
};
int main()
{ 
  //here you read the integers numbers and do simple math with them
  //big_integer_number A,B,C;
  //std::cin>>A;
  //std::cin>>B;
  //C=A+B;
  //C=A-B;
  //C=A*B;
  //C=A/B;
  //C=A%B;
  //C=GCD(A,B);
  //std::cout<<C;

  //here you read the rational numbers and do simple math with them
  //big_rational_number X,Y,Z;
  //std::cin>>X;
  //std::cin>>Y;
  //Z=X+Y;
  //Z=X*Y;
  //Z=REDUCE(Z);
  //std::cout<<Z;

    return 0;
}
std::istream& operator >>(std::istream& in,big_integer_number& A)
{
  char sir[1000];
  in>>sir;
  int i=0;
  if(sir[0]=='-')
  {A.pozitiv=0;i++;}
  else A.pozitiv=1;
  for(int j=i;j<strlen(sir);j++)
  {
    int x=(int)(sir[j]-'0');
    nod *p=new nod;
    p->val=x;
    if(A.start==NULL)
    {
      p->next=NULL;
      p->below=NULL;
      A.start=p;
      A.stop=p;
    }
    else
    {
      A.stop->next=p;
      p->below=A.stop;
      p->next=NULL;
      A.stop=p;
    }
  } return in;
}
std::ostream& operator <<(std::ostream& out,big_integer_number& A)
{

  if(A.pozitiv==0)
  if(A.start!=A.stop||A.start->val!=0)
  out<<"-";
  nod *p=A.start;
  while(p)
  {out<<p->val; p=p->next;}
  out<<"\n";
  return out;
}
big_integer_number operator+(big_integer_number A,big_integer_number B)
{

  bool verificare=0;
  big_integer_number C;
  if(A.pozitiv==B.pozitiv)
    C.pozitiv=1;
  else
  C.pozitiv=0;
  nod *p,*q,*r;
  p=A.stop;
  q=B.stop;
  if(C.pozitiv==1)
  {
    unsigned k=0;
    while(p&&q)
    {
     int x=p->val+q->val+k;
     k=x/10;
     x=x%10;
     r=new nod;
     r->val=x;
     if(C.stop==NULL)
     {
      r->next=NULL;
      r->below=NULL;
      C.start=r;
      C.stop=r;
     }
     else
     {
       C.start->below=r;
       r->next=C.start;
       r->below=NULL;
       C.start=r;
     }
    p=p->below;
    q=q->below;
    }
    while(q)
    {
    r=new nod;
      int x=q->val+k;
      k=x/10;
      x=x%10;
      r->val=x;
      C.start->below=r;
      r->next=C.start;
      r->below=NULL;
      C.start=r;
      q=q->below;
    }
    while(p)
    {
    r=new nod;
      int x=p->val+k;
      k=x/10;
      x=x%10;
      r->val=x;
      C.start->below=r;
      r->next=C.start;
      r->below=NULL;
      C.start=r;
      p=p->below;
    }
    while(k)
    {
      r=new nod;
      r->val=k%10;
      k=k/10;
      C.start->below=r;
      r->next=C.start;
      r->below=NULL;
      C.start=r;
    }
  }

  if(C.pozitiv==0)
  {
      int ok1=0,ok2=0;
      nod *p,*q,*r,*theBIGone,*THEsmallONE;
      p=A.start;
      q=B.start;
      while(p)
      {ok1++;p=p->next;}
      while(q)
      {ok2++;q=q->next;}
      if(ok1>ok2)
        {theBIGone=A.stop;THEsmallONE=B.stop;
        if(A.pozitiv==1)
      verificare=1;}
      if(ok1<ok2)
      {theBIGone=B.stop;THEsmallONE=A.stop;  if(B.pozitiv==1)
      verificare=1;
      }
      if(ok1==ok2)
      {
        p=A.start;
        q=B.start;
        while(p->val==q->val&&p->next!=NULL)
        {p=p->next;q=q->next;}
        if(p->val>q->val)
        {theBIGone=A.stop;THEsmallONE=B.stop;
          if(A.pozitiv==1)
        verificare=1;}
        else
        {theBIGone=B.stop;THEsmallONE=A.stop;
          if(B.pozitiv==1)
        verificare=1;}
      }
      int k=0;

      while(THEsmallONE)
      {

        int x=theBIGone->val-THEsmallONE->val+k;
        k=0;
        if(x<0)
        {x=x+10; k=-1;}
        r=new nod;
        r->val=x;
        if(C.start==NULL)
        {
          r->next=NULL;
          r->below=NULL;
          C.start=r;
          C.stop=r;
        }
        else
        {
          C.start->below=r;
          r->next=C.start;
          r->below=NULL;
          C.start=r;
        }
        theBIGone=theBIGone->below;
        THEsmallONE=THEsmallONE->below;
      }

      while(theBIGone)
      {
        r=new nod;
        int x=theBIGone->val+k;
        if(x<0)
        {x+=10;k=-1;}
        else k=0;
        r->val=x;

        C.start->below=r;
        r->next=C.start;
        r->below=NULL;
        C.start=r;
        theBIGone=theBIGone->below;
      }

  }

  while(C.start->val==0&&C.start->next!=NULL)
  {
    p=C.start;
    C.start=C.start->next;
    C.start->below=NULL;
    p->next=NULL;
    delete p;

  }

  if(A.pozitiv==0&&B.pozitiv==0)
  C.pozitiv=0;

  if(verificare==1)
  C.pozitiv=1;

  return C;
}
big_integer_number operator-(big_integer_number A,big_integer_number B)
{

  if(B.pozitiv==0)
  B.pozitiv=1;
  else B.pozitiv=0;
  big_integer_number C=A+B;
  return C;
}
big_integer_number operator*(big_integer_number A,big_integer_number B)
{
  nod *p=A.start,*q=B.start;
  int nra=0,nrb=0;
  while(p)
  {nra++;p=p->next;}
  while(q)
  {nrb++;q=q->next;}
  char sira[nra+1],sirb[nrb+1];
  p=A.start; q=B.start;
  nra=0; nrb=0;

  while(p)
  {sira[nra]=(char)(p->val+'0');
  p=p->next;nra++;}
  sira[nra]='\0';
  while(q)
  {sirb[nrb]=(char)(q->val+'0');
  q=q->next;nrb++;}
  sirb[nrb]='\0';
  big_integer_number C;
  if(A.pozitiv==B.pozitiv)
  C.pozitiv=1;
  else C.pozitiv=0;
  int n,m,i,j;

  n=strlen(sira);
  m=strlen(sirb);
  struct bsa{
    unsigned int up;
    unsigned int down;
  }M[m][n];
  for(i=0;i<m;i++)
    for(j=0;j<n;j++)
    {
      unsigned x=(unsigned)(sira[j]-'0')*(unsigned)(sirb[i]-'0');
      M[i][j].up=x/10;
      M[i][j].down=x%10;
    }

  p=new nod;
  p->val=M[m-1][n-1].down;
  p->next=NULL;
  p->below=NULL;
  C.start=p;
  C.stop=p;
  unsigned x=m+n-2,k=0;
  while(x!=0)
  {
    int SUM=0;
    for(i=0;i<m;i++)
      for(j=0;j<n;j++)
      {
        if(i+j==x)
        SUM+=M[i][j].up;
        if(i+j+1==x)
        SUM+=M[i][j].down;
      }
    SUM+=k;
    k=SUM/10;
    nod *p=new nod;
    p->val=SUM%10;

      C.start->below=p;
      p->next=C.start;
      p->below=NULL;
      C.start=p;
    x--;
  }
  k+=M[0][0].up;
  while(k)
  {
    p=new nod;
    p->val=k%10;
    C.start->below=p;
    p->next=C.start;
    p->below=NULL;
    C.start=p;
  k/=10;}return C;}
big_integer_number operator/(big_integer_number A,big_integer_number B)
{
  big_integer_number C;
  unsigned long long x=0;
  if(A.pozitiv==B.pozitiv)
  C.pozitiv=1;
  else
  {C.pozitiv=0;x++;}

  A.pozitiv=1;
  B.pozitiv=1;

  while(A.pozitiv==1)
  {
    A=A-B;
      x++;
  }
  x--;

  if(A.start==A.stop&&A.start->val==0)
    x++;
  while(x)
  {
    nod *p=new nod;
    p->val=x%10;
    if(C.start==NULL)
    {
      p->next=NULL;
      p->below=NULL;
      C.start=p;
      C.stop=p;
    }
    else
    {
      C.start->below=p;
      p->next=C.start;
      p->below=NULL;
      C.start=p;
    }
    x=x/10;
  }
  return C;
}
big_integer_number operator%(big_integer_number A,big_integer_number B)
{
  big_integer_number DIV,MOD;
  DIV=A/B;
  B=B*DIV;
  MOD=A-B;
  return MOD;
}
big_integer_number GCD(big_integer_number A,big_integer_number B)
{
  unsigned ka=0,kb=0;
  bool Abigger_thanB=0;
  nod *p=A.start,*q=B.start;
  while(p)
  {
    p=p->next;
    ka++;
  }
  while(q)
  {
    q=q->next;
    kb++;
  }
  if(ka>kb)
    Abigger_thanB=1;
  if(ka<kb)
    Abigger_thanB=0;
  if(ka==kb)
  {
    p=A.start;
    q=B.start;
    while(p->val==q->val&&p->next)
    {p=p->next;q=q->next;}
    if(p->val>=q->val)
      Abigger_thanB=1;
      else
      Abigger_thanB=0;
  }
  if(Abigger_thanB==0)
  {
  big_integer_number C=A;
  A=B;
  B=C;}

  while(B.start!=B.stop||B.start->val!=0)
  {
    big_integer_number T=B;
    B=A%B;
    A=T;
  }
  return A;
}
std::istream& operator >>(std::istream& in,big_rational_number& X)
{ std::cout<<"Give me a numerator:     ";
  std::cin>>X.numerator;
  std::cout<<"Give me a denominator:   ";
  std::cin>>X.denominator;
  return in;
}
std::ostream& operator <<(std::ostream& out,big_rational_number& X)
{ std::cout<<"Take the numerator:    ";
  std::cout<<X.numerator;
  std::cout<<"Take the denominator:   ";
  std::cout<<X.denominator;
  return out;
}
big_rational_number operator+(big_rational_number X,big_rational_number Y)
{
  big_rational_number Z;
  Z.denominator=X.denominator*Y.denominator;
  Z.numerator=X.numerator*Y.denominator+X.denominator*Y.numerator;
  return Z;
}
big_rational_number operator*(big_rational_number X,big_rational_number Y)
{
  big_rational_number Z;
  Z.numerator=X.numerator*Y.numerator;
  Z.denominator=X.denominator*Y.denominator;
  return Z;
}
big_rational_number REDUCE(big_rational_number X)
{

    big_integer_number Z=GCD(X.denominator,X.numerator);
    X.denominator=X.denominator/Z;
    X.numerator=X.numerator/Z;
  return X;
}
