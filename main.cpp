//g++ -std=c++17  main.cpp -o main &&./main<ej.txt
// Integrantes:
// Alonso Rios
// Neftali Calixto
// Johannes Albert Loayza
#include "funciones.h"


int main(){
  int n;// LA CANTIDAD ESTADOS 
  int p;// EL ESTADO INICIAL
  int x;// LA CANTIDAD DE ESTADOS FINALES
  string q; //TODOS LOS ESTADOS FINALES
  cin>>n;cin>>p;cin>>x;getline(cin,q);

  multimap<int,pair<int,int>> InTransitions;
  for(int i=0 ; i<2*n ; ++i){
      int InS, InT, InF;
      cin>>InS;cin>>InT;cin>>InF;
      InTransitions.insert (make_pair(InS, make_pair(InT,InF)));
  }

  unordered_map< int,unordered_map<int,int> > states;
  for(auto &i : InTransitions){
    if(states.find(i.first)==end(states)){
      unordered_map< int,int > transitions;
      auto range = InTransitions.equal_range(i.first);
      
      for(auto it=range.first; it!= range.second ; ++it){
        transitions.insert(make_pair(it->second.first,it->second.second));
      }

      states.insert(make_pair(i.first,transitions));
    }
  }
   
  set<int> ConjEstados;
    for (auto [estado, _]:states){
      ConjEstados.insert(estado);
    }

  //preg1
 MinSinc(ConjEstados, states);
 cout<<endl<<"-------------------------"<<endl;
 //preg2
 DecSinc(ConjEstados, states);
  cout<<endl<<"-------------------------"<<endl;
 //preg3
 CadSinc(ConjEstados,states);

}
