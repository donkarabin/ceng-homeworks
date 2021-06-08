#include "the3.h"

using namespace std;
// You  can define extra functions here



// INPUT :
//            n         : number of nodes in the graph
//            edgeList  : edges in the graph
//            scores    : importance scores
// return value : 
//                 number of disconnected components

long long maxinf=9223372036854775806LL/2;

void printmodif(long long **& modified,int n){
   
   for(int i=0;i<n;i++){
      cout<<"- ";
   }
   cout<<endl;
   for(int i=0;i<n;i++){
      cout<<"| ";
      for(int j=0; j<n; j++){
         cout<<modified[i][j]<<"*";
      }
      cout<<"|"<<endl;
   }
   cout<<endl;
}

void diEFES(bool*& visiTEDx,int i,long long **& modified,int n){
   visiTEDx[i]=true;

   for(int j=0;j<n;j++){
      if(modified[i][j]!=maxinf && visiTEDx[j]==false){
         diEFES(visiTEDx,j,modified,n);
      }
   }
}




int noofdiscon(long long **& modified, int n){
   int kantovka=0;
   bool* visiTEDx= new bool[n];
   for(int i=0;i<n;i++){
      visiTEDx[i]=false;
   }

   for(int i=0;i<n;i++){
      if(visiTEDx[i]==false){
         diEFES(visiTEDx,i,modified,n);
         kantovka ++;
      }
   }

   return kantovka;
}

void floyd_qerdes(long long **& modified, int n){
   int a,b,c;
   for(c=0;c<n;c++){
      for(a=0; a<n;a++){
         for(b=0;b<n;b++){
            if(modified[a][c]+modified[c][b]< modified[a][b]){  
               modified[a][b]=modified[a][c]+modified[c][b];
            }
         }
      }
   }
   /*for (int i=0; i<n;i++){
      for (int j=0;j<n;j++){
         cout<<"AYEEEEE "<< i << " HOOOY " <<j<<"  :"<<modified[i][j]<<endl;
      }
   }*/
   
}

int Important (int n, int**& edgeList, double*& scores)
{ 
   double summa=0,suret,mexrec,nisbet;
   long long ** modified= new long long *[n];  // memory constraint-e diqqet 
   
   for (int i=0; i<n;i++){
      modified[i]=new long long [n];
      
   }

   for (int i=0; i<n;i++){
      for (int j=0;j<n;j++){
         if(edgeList[i][j]==0){
            if(i==j){
               modified[i][j]=0;
            }
            else{
               modified[i][j]=maxinf;
            }
         }
         else {
            modified[i][j]=edgeList[i][j];
         }
      }
   }

   floyd_qerdes(modified,n);

  int a,b,c;
   for(c=0;c<n;c++){
      summa = 0.0;
      for(a=0; a<n;a++){
         for(b=0;b<n;b++){
            if(modified[a][c]!=maxinf && modified[c][b]!=maxinf && modified[a][b]!=maxinf){
               if(a==b){
                  mexrec=1;
                  if(c==a || c==b){
                     suret=0;
                  }
                  else{
                     suret=modified[a][c]+modified[c][b];
                  }
               }
               else{
                  mexrec=modified[a][b];
                  if(c==a || c==b){
                     suret=0;
                  }
                  else{
                     suret=modified[a][c]+modified[c][b];
                  }
               }
               
               nisbet=suret/mexrec;
               summa=summa+nisbet;
            }
         }
      }
      scores[c]=summa;
   }
printmodif(modified,n);
   return noofdiscon(modified,n);

}

