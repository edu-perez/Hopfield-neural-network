#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include "aleatorios.h"

using namespace std;

double promedio(int x[][400], int m, int n);
void difuminar(int s[400], int n);


int main (void)
{
 double h,a,h1,h2,p,q,t,g;
 int i,j,n,m,k,f;
 n=400;//nº neuronas. Si lo cambias TAMBIÉN LO TIENES QUE CAMBIAR EN LA FUNCIÓN PROMEDIO (en la matriz) y en la matriz x de aquí abajo.
 m=4;//nº config. particulares.
 int s[n], x[m][400];//x son las config particulares.
 double w[n][n],u[n],solap[m];
 
 t=0.0; 
 //Configuraciones particulares. Leídas desde el fichero patrones.txt.
 ifstream patrones ("patr.txt");//fichero de columnas cada una con una parte de unos
 ifstream pat ("pat.txt");//fichero con 4 columnas con 400, si se ponen en 20*20 son las letras A B C D
 ofstream fich ("fich.txt");//fichero donde vuelco mi config. neuronal al finalizar el programa, (los resultados vaya)
 ofstream sola ("solap.txt");//fichero donde vuelco mis datos correspondientes al solapamiento de cada patrón inicial
 ofstream inicio ("inicio.txt");//config. inicial de mi red.
 ofstream fich1 ("fich1.txt");//este fichero solo esta pa probar cosas y eso, no tiene na relevante.
 
 
 //Cada fila de la matriz x es una config. particular. Lectura de patrones almacenados. Cada col es un patrón.
 
    for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
            pat >> x[j][i]; 
    }
   
//esto pa na al final pero lo dejo aquí x si acaso me sirve más adelante.
//Ahora para los patrones que son imágenes. (400 neuronas) necesito leer 20*20 1 y 0.
/*for(i=0;i<n;i++)
{
    a1 >> x[0][i];
    b >> x[1][i];
    c >> x[2][i];
    d >> x[3][i];
}
*/

//esto es x si quiero comprobar que he leido bien las cosas
    //for(j=0;j<n;j++)
      //  cout<<x[0][j]<<x[1][j]<<x[2][j]<<x[3][j]<<endl;
    
    
//Calculamos su promedio que nos hará falta después para los pesos sinápticos
//El prmedio de la matriz, es decir, el de todas las config part. no el de cada una
 //a=promedio(x,m,n);   
 //cout << a;
 //cout<<a<<endl;
 
 i=9;
 dranini_(&i);
 
 //Patrones aleatorios.
   /*for(i=0;i<n;i++)
    {
        for(j=0;j<m;j++)
        { 
            q=dranu_();
            if(q<=0.5)
                x[j][i]=0;
            else
                x[j][i]=1;
        }   
    }*/
    
    //for(j=0;j<n;j++)
      //  cout<<x[0][j]<<x[1][j]<<x[2][j]<<x[3][j]<<endl;
      
      a=promedio(x,m,n);   
 
 
 
 //Config. inicial de mi red neuronal.
 
 //Config. aleatoria.
  /*for(i=0;i<n;i++)
 {
    q=dranu_();
    if(q<=0.5)
        s[i]=0;
    else
        s[i]=1;
 }*/
 
 for(i=0;i<n;i++)
 {
     s[i]=x[2][i];
 }
 
 difuminar(s,n);
 difuminar(s,n);
 difuminar(s,n);
 difuminar(s,n);
 //difuminar(s,n);
 //difuminar(s,n);
 //difuminar(s,n);
 //difuminar(s,n);
 
 
 
 /*
 for(i=80;i<150;i++)
 {
     s[i]=0;*/
 
 
 for(i=0;i<n;i++) //Esto es x si quiero ver mi config. inicial en 20x20. Hay q usar i20x20.f
   inicio<<s[i]<<endl;
 
 /*for(i=0;i<n/8;i++)
     s[i]=0;
 
 for(i=0;i<(3*n/4);i++)
     s[i]=0;*/
     

 //empezamos a calcular cosas, pesos sinápticos, umbrales, etc.
 
 for(i=0;i<n;i++)
 {
     u[i]=0.0;//umbrales para activación.
     for(j=0;j<n;j++)
     {
         w[i][j]=0.0;//pesos sinápticos
         for(k=0;k<m;k++)
         {
             w[i][j]=w[i][j]+(x[k][i]-a)*(x[k][j]-a);//a es el promedio de las x, que son las config. particulares.
         }
         w[i][j]=w[i][j]/(a*(1-a)*n);
         
         if(i==j)//no se permite la autoactivación.
             w[i][j]=0.0;
         
         //cout<<w[i][j]<<endl;
         u[i]=u[i]+w[i][j];
         //h1=h1+w[i][j]*s[i]*s[j];
         
     }
     u[i]=0.5*u[i];
     //cout<<u[i]<<endl;
     //h2=h2+u[i]*s[i];
     
 }
 
 //h=-0.5*h1+h2;
 for(k=0;k<10000;k++)
 {
    g=dranu_();
    f=(int) (n*g);
    
    //
    //h hamiltoniano/energía del sist.
    h=0.0;
    h1=0.0;
    h2=0.0;
 
 
 for(i=0;i<n;i++)
 {
     //if(i!=f)
         h1=h1+w[i][f]*s[i];
 }
 
 for(j=0;j<n;j++)
     h2=h2+w[f][j]*s[j];
 
 
 h=(2.0*s[f]-1.0)*(0.5*h1+0.5*h2+u[f]);
 //cout<<h<<endl;
 
 
 p=fmin(1.0,exp(-h/t));
 //cout<<p<<endl;
        
 q=dranu_();
    
    if(q<p)
        s[f]=1-s[f];
        //h=h+s[i]*s[j]*w[i][j];
    
    
    //Solapamiento.
    for(j=0;j<m;j++)
    {
        solap[j]=0.0;
        
        for(i=0;i<n;i++)
            solap[j]=solap[j]+(x[j][i]-a)*(s[i]-0.5);
        
        solap[j]=solap[j]/(a*n*(1-a));
        
        //sola<<solap[j]<<endl;
    }
    
    sola<<k<<"   "<<solap[0]<<"   "<<solap[1]<<"   "<<solap[2]<<"   "<<solap[3]<<"   "<<solap[4]<<"   "<<solap[5]<<"   "<<solap[6]<<"   "<<solap[7]<<"   "<<solap[8]<<endl;
    
 }
 
 
 for(i=0;i<n;i++)
     fich<<s[i]<<endl;
 
 //cout<<w[325][674]<<"  "<<w[674][325];

  return 0;  
}


double promedio(int x[][400], int m, int n)//func q devuelve el promedio de una matriz (suma de to los números entre el nº elem.
{
    int c,f;
    double sum;
    sum=0.0;
    for(f=0;f<m;f++)
    {
        for(c=0;c<n;c++)
            sum=sum+x[f][c];
        
    }
        return sum/(n*m);
}

void difuminar(int s[400], int n)//función q me cambia 50 neuronas aleatorias de act a desact o viceversa.
{
    double x;
    int q,i;
    for(i=0;i<50;i++)
    {
        x=dranu_();
        q=(int) (n*x);
        s[q]=1-s[q];
    }
    return;
}

