#include<iostream>
#include <boost/functional/hash.hpp>
#include <unordered_map>
#include<string>
#include<vector>  
#include<unordered_set>  
#include<utility>
#include<set>
#include <map>
#include <queue>
#include <numeric>
#include<algorithm>

using namespace std;

//-------------PREGUNTA 1---------------//


//template<>
struct HashFunction {
    size_t operator()(const set<int>& nodo) const {
        return boost::hash_range(nodo.begin(), nodo.end());
    }
};

set<int> add_hijosP1(set<int>& nodo,unordered_set<set<int>,HashFunction>&visited,queue<set<int>>& cola,unordered_map<int,unordered_map<int,int>>& AFD, unordered_map<set<int>,string,HashFunction>& cadenas){
  // conseguir hijos
  set<int> h1vec;
  set<int> h2vec;
  string h1="";
  string h2="";
  
  for(auto estado: nodo){
    h1vec.insert(AFD[estado][0]);
    h2vec.insert(AFD[estado][1]);
  }

  if(visited.find(h1vec)==visited.end()){
    cola.push(h1vec);
    visited.insert(h1vec);
    cadenas[h1vec]=cadenas[nodo]+"0";
    if(h1vec.size()==1)
      return h1vec;
  }
  if(visited.find(h2vec)==visited.end()){
    cola.push(h2vec);
    visited.insert(h2vec);
    cadenas[h2vec]=cadenas[nodo]+"1";
    if(h2vec.size()==1)
      return h2vec;
  }
  return {};
}

void MinSinc(set<int>& ConjEstados, unordered_map<int,unordered_map<int,int>>& AFD ){
  if(AFD.size()==1){
    cout<<"Cadena sincronizadora minima: 0"<< "\nTamaño: 1"<<endl;
    return;
  }
  auto root= [& ConjEstados](){
    string result="";
    for(auto elem: ConjEstados){
      result=result+to_string(elem);
    }
    return result;
  };

  
  unordered_map<set<int>,string,HashFunction>cadenas;
  string EstadoUnitario="";
  set<int> EstadoUnitarioVEC;
  queue<set<int>> cola; 
  unordered_set<set<int>,HashFunction>visited;
  cola.push(ConjEstados); //add root to cola
  visited.insert(ConjEstados); //add root to visited
  while(!cola.empty()){
    auto temp=cola.front();
    cola.pop();
    auto result= add_hijosP1(temp,visited,cola,AFD,cadenas);
      if(result.size()==1){
      EstadoUnitarioVEC=result;
      break;
    }
  }
  if(EstadoUnitarioVEC.empty())
    cout<< "NO";
  else{
    cout<< "Cadena sincronizadora minima: "<<cadenas[EstadoUnitarioVEC]<<endl<<"Tamaño: "<<cadenas[EstadoUnitarioVEC].size()<<endl;
    }
  
}


//-------------PREGUNTA 2---------------//
set<int> add_hijosP2(set<int>& nodo,unordered_set<set<int>,HashFunction>&visited,queue<set<int>>& cola,unordered_map<int,unordered_map<int,int>>& AFD){
  // conseguir hijos
  set<int> h1vec;
  set<int> h2vec;
 

  for(auto estado: nodo){
    h1vec.insert(AFD[estado][0]);
    h2vec.insert(AFD[estado][1]);
  }

  if(visited.find(h1vec)==visited.end()){
    cola.push(h1vec);
    visited.insert(h1vec);
    if(h1vec.size()==1)
      return h1vec;
  }
  if(visited.find(h2vec)==visited.end()){
    cola.push(h2vec);
    visited.insert(h2vec);
    if(h2vec.size()==1)
      return h2vec;
  }
  return {};
}

void DecSinc(set<int> ConjEstados, unordered_map<int,unordered_map<int,int>>& AFD){
  //CREA PARES
  vector<set<int>> Pares;
  while(ConjEstados.size()>2){
    auto start=ConjEstados.begin();
    for(auto it=next(ConjEstados.begin());it!=ConjEstados.end();it++){
 
      set<int> temporal;
      temporal.insert(*it);
      temporal.insert(*start);
      Pares.push_back(temporal);
    }
    ConjEstados.erase(ConjEstados.begin());
  }
  Pares.push_back(ConjEstados);
  // Caso esquina: afd unitario
  if(Pares.size()==1 && Pares[0].size()==1){
    cout<< "SI";
    return;
    }
  //BFS para cada par
  unordered_set<string> ReachesSingleton;
  for (auto par:Pares){
    set<int> VEC;
    queue<set<int>> cola;  
    unordered_set<set<int>,HashFunction> visited;
    cola.push(par);//add root to cola
    visited.insert(par);//add root to visited
    while(!cola.empty()){
      auto temp= cola.front();
      cola.pop();
      auto result= add_hijosP2(temp,visited,cola,AFD);
      if(result.size()==1){
      VEC=result;
      break;
      }
    }
    if(VEC.empty()){
      cout<< "NO"<<endl;
      return;
    }
  }
 cout<<"SI"<<endl;
 return;
}


//-------------PREGUNTA 3---------------//
set<int> add_hijosP3(set<int>& nodo,unordered_set<set<int>,HashFunction>&visited,queue<set<int>>& cola,unordered_map<int,unordered_map<int,int>>& AFD, unordered_map<set<int>,string,HashFunction>& cadenas){
  // conseguir hijos
  set<int> h1vec;
  set<int> h2vec;
  string h1="";
  string h2="";
  
  for(auto estado: nodo){
    h1vec.insert(AFD[estado][0]);
    h2vec.insert(AFD[estado][1]);
  }

  if(visited.find(h1vec)==visited.end()){
    cola.push(h1vec);
    visited.insert(h1vec);
    cadenas[h1vec]=cadenas[nodo]+"0";
    if(h1vec.size()==1)
      return h1vec;
  }
  if(visited.find(h2vec)==visited.end()){
    cola.push(h2vec);
    visited.insert(h2vec);
    cadenas[h2vec]=cadenas[nodo]+"1";
    if(h2vec.size()==1)
      return h2vec;
  }
  return {};
}


void CadSinc(set<int> ConjEstados, unordered_map<int,unordered_map<int,int>>& AFD){
  //-------Paso 1: generar bosque-----//
  //CREA PARES
  vector<set<int>> Pares;
  while(ConjEstados.size()>2){
    auto start=ConjEstados.begin();
    for(auto it=next(ConjEstados.begin());it!=ConjEstados.end();it++){
 
      set<int> temporal;
      temporal.insert(*it);
      temporal.insert(*start);
      Pares.push_back(temporal);
    }
    ConjEstados.erase(ConjEstados.begin());
  }
  Pares.push_back(ConjEstados);
  // Caso esquina: afd unitario
  if(Pares.size()==1 && Pares[0].size()==1){
    cout<< "Cadena sincronizadora: "<< 1;
    return;
    }
  //BFS para cada par
  unordered_map<set<int>,string,HashFunction> cadenas;
  unordered_map<set<int>,string,HashFunction> ParToSingle;
  for (auto par:Pares){
    set<int> VEC;
    queue<set<int>> cola;  
    unordered_set<set<int>,HashFunction> visited;
    cola.push(par);//add root to cola
    visited.insert(par);//add root to visited
    while(!cola.empty()){
      auto temp= cola.front();
      cola.pop();
      auto result= add_hijosP3(temp,visited,cola,AFD,cadenas);
      if(result.size()==1){
      VEC=result;
      break;
      }
    }
      ParToSingle[par]= cadenas[VEC];
    
  }

 // Paso 2: Correr cadenas encontradas en el AFD original
 unordered_map<string,set<int>> StringToNewState;
 for(const auto& [_,cadena]:ParToSingle){
   set<int> NewStates;
   for(const auto& [estado,_]:AFD){
     auto temp=estado;
      for(auto it=cadena.begin();it!=cadena.end();it++){
        int toINT=*it-'0';
        temp=AFD[temp][toINT];

      }
    NewStates.insert(temp);
   }
   StringToNewState[cadena]=NewStates;
 }

 //ALGORITMO
 auto X=ConjEstados;
 string CadenaSincronizadora="";
 set<int> par;
 while(X.size()>1){
   par.insert(*X.begin());
   par.insert(*X.begin()+1);
   string parte=ParToSingle[par];
   X=StringToNewState[parte];
   CadenaSincronizadora=CadenaSincronizadora+parte;
 }

 cout<< "Cadena sincronizadora: "<<CadenaSincronizadora<<endl;
 return;
}
