#include <thread>
#include <pthread.h>
#include <ctime>
#include <fstream>
#include <iostream>
#include <cassert>
#include <string>
#include <cstdlib>
#include <stdio.h>

using namespace std;

// taille max de la matrice
#define MAX 4

// nombre max des threads
#define MAX_THREAD 4



int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];
const int NUM_THREADS = 4;
int step_i = 0;

void* multi(void* arg)
{
    int core = step_i++;

    // chaque thread calcule 1/4 eme dans la multiplication de la matrice
    for (int i = core * MAX / 4; i < (core + 1) * MAX / 4; i++)
        for (int j = 0; j < MAX; j++)
            for (int k = 0; k < MAX; k++)
                matC[i][j] += matA[i][k] * matB[k][j];
return(0);
}


void multiplication()
{
  for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            matA[i][j] = rand() % 10;
            matB[i][j] = rand() % 10;
        }
    }


    // DAffichage de Matrice A
    cout << endl
         << "Matrice A" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matA[i][j] << " ";
        cout << endl;
    }

    // Affichage de Matrice B
    cout << endl
         << "Matrice B" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matB[i][j] << " ";
        cout << endl;
    }

    // declariation des 4 threads
    pthread_t threads[MAX_THREAD];

    // Creation des 4 threads chaqu'un son job
    for (int i = 0; i < MAX_THREAD; i++) {
        int* p;
        pthread_create(&threads[i], NULL, multi, (void*)(p));
    }

    // Assembler les threads
    for (int i = 0; i < MAX_THREAD; i++){
        pthread_join(threads[i], NULL);
	}
    // Affichage des resultats
    cout << endl
         << "Multiplication de A en B" << endl;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++)
            cout << matC[i][j] << " ";
        cout << endl;
    }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fibbonacci()
{
      int premierTerme=0, secondTerme=1, i, n, somme=0;
      cout<<"Entrer le nombre des termes: "; cin>>n;
      cout<<"Series De Fibonacci : ";

      for(i=0 ; i<n ; i++)
     {
               if(i <= 1)
      {
           somme=i;
                }
                    // afficher 0 et 1
                else
                {
                      somme=premierTerme + secondTerme;
             premierTerme=secondTerme;
                      secondTerme=somme;
                       //pour calculer les termes restants

                }
     cout<<somme<<" ";
      }

}

////////////////////////////////////////////////////////////////////////////////////////////////////////

void calculHarmonique(long long start, long long N, double *sum)
{
    for(; start <= N; start++)
    {
        *sum += 1.0/start;
    }
}

void executerAvecThreads(long long N)
{
    thread t[NUM_THREADS];  // on utilise 4 threads
    double sum[NUM_THREADS] = {0.0};    // array pour chaque somme calculé par chaque thread
    double finalSum = 0.0;
    clock_t start = clock();


    for(int i = 0; i < NUM_THREADS; i++)
    {

        t[i] = thread(calculHarmonique, (((N/4)*i)+1), ((N/4)*(i+1)), &(sum[i]));
    }

    // Assembler les threads pour arriver a la finalSum.
    for(int i = 0; i < NUM_THREADS; i++)
    {
        t[i].join();
        finalSum += sum[i];
    }

    clock_t end = clock();
    printf("La somme Harmonique de  %lld est %1.18lf\n", N, finalSum);
    printf("Les calculs ont pris %1.18lf secondes.\n", (((double)(end-start)/CLOCKS_PER_SEC))/NUM_THREADS);
}

void executerSansThreads(long long N)
{
    double sum = 0.0;
    clock_t start = clock();
    for(int i = 1; i <= N; i++)
    {
        sum += 1.0/i;
    }
    clock_t end = clock();
    printf("La somme Harmonique de  %lld est%1.18lf\n", N, sum);
    printf("Les calculs ont pris%1.18lf secondes.\n", (((double)(end-start)/CLOCKS_PER_SEC))/NUM_THREADS);
}
void harmonique()
{
    long long N;

    cout << "Entrer le nombre des terms pour calculer leurs somme Harmonique: ";
    cin >> N;
    assert(N > 0 && "N doit etre un entier positive different de zero");
    cout << endl;

    if(N > NUM_THREADS && N % 4 != 0)
    {
        cout << "Calcule avec des threads..." << endl;
        executerAvecThreads(N);
    }
    else if(N > NUM_THREADS && N % 4 ==  0)
    {
        cout << "Calcule avec des threads.." << endl;
        executerSansThreads(N);
    }
    else
    {
        cout << "Calculé sans threads car N est petit!..." << endl;
        executerSansThreads(N);
    }


}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void puissance()
{
    int exposant;
    float base, resultat = 1;

    cout << "Entrer la base et l'exposant respectivement:  ";
    cin >> base >> exposant;

    cout << base << "^" << exposant << " = ";

    while (exposant != 0) {
        resultat *= base;
        --exposant;
    }

    cout << resultat;


}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void factoriel(){
  int i,f=1,num;

  printf("Entrer un nombre : ");
  scanf("%d",&num);

  for(i=1;i<=num;i++)
      f=f*i;

  printf("Factoriel de %d est: %d",num,f);
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void admin()
{
  while(1)
  {
 	cout<<"\n\t\t\t==============================\n";
	cout<<"\n\t\t\t         BIENVENUE   \n";
	cout<<"\n\t\t\t==============================\n\n";
	cout<<"\n\t\t\t* * * * * * * * * * * * * * * *\n";
 	cout<<"\n\t\t\t1. MULTIPLICATION DE DEUX MATRICES\n\n\t\t\t2. SUITE DE FIBBONACCI\n\n\t\t\t3. SOMME HARMONIQUE \n\n\t\t\t4. PUISSANCE D'UN NOMBRE\n\n\t\t\t5. FACTORIEL D'UN NOMBRE\n\n\t\t\t6. QUITTER \n";
  cout<<"\n\n\t\t\tEntrez votre choix !\n";
  int u;
  cin>>u;
if(u==1)
  {
  multiplication();
}
  else if(u==2)
  {
  fibbonacci();
}
  else if(u==3)
  {
  harmonique();
}
 else if(u==4)
  {
  puissance();
}
 else if(u==5)
  {
  factoriel();
}
  else if(u==6)
  {
  break;
}
  else cout<<"Option invalide. Essayez encore une fois!\n";
 }

}


int main(){

    int ch;



      while(1){
        cout<<"\n \t\t\t ";
        cout<<"\n \t\t\t";
        cout<<"\n \t\t\t";
        cout<<"\n \t\t\t* * * * * * * * * * * *  * * * * * * * * * * *  * ";
         cout<<"\n \t\t\tBIENVENUE SUR LE SYSTEME DES CALCULS MATHEMATIQUES";
        cout<<"\n \t\t\t* * * * * * * * * * * *  * * * * * * * * * * *  * ";
        cout<<"\n\t\t\t  1. ACCEDER AU SYSTEME";
        cout<<"\n\t\t\t  2. QUITTER";
        cout<<"\n\t\t\t* * * * * * * * * * * *\n";
        cout<<"\n\t\t\t Entrer Votre Choix: ";
        cin>>ch;
        switch(ch){
            case 1:
                admin();
                break;
            case 2:
                exit(0);
                break;
            default:
                cout<<"Entrer un choix valide\n";
                break;
        }
    }
    return 0;
}





