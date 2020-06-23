#include "bits/stdc++.h"
using namespace std;

int qArestaAtual=0;
vector<vector<bool>> grafo;
vector<int> resultados;
stack<int> caminho;
set<pair<int,int>> visitado;

// verifica se a aresta foi visitada
bool isVisitado(pair<int,int> aresta){
  	if(visitado.find(aresta) != visitado.end() ) return true;
  	else return false;	
}

// pega o primeiro vertice que possua um caminho válido
int filho(int pai){
	for(int cont=0; cont < grafo[pai].size(); cont++){
		if(grafo[pai][cont] && ! isVisitado({pai,cont})) return cont;
	}
	
	return -1;
}

// executa a dfs contando as arestas
void dfs(int vAtual){
	int vFilho = filho(vAtual);
	
	// se tem filho vai
	if(vFilho != -1){
		qArestaAtual++;
		visitado.insert({vAtual,vFilho});
		caminho.push(vAtual);
		dfs(vFilho);
		
	// se nao é orfão, volta
	}else if(!caminho.empty()){
		int pai = caminho.top();
		caminho.pop();
		resultados.push_back(qArestaAtual);
		qArestaAtual--;
		dfs(pai);
	}
}


int main(){

	int n;

	while(cin >> n){
		// constroi o grafo
		for(int cont=0; cont < 10; cont++){
			grafo.push_back(vector<bool>(10,0));
		}

		// popula o grafo
		for(int cont=0; cont < n; cont++){
			int x, y;
			cin >> x >> y;
			grafo[x][y] = true;
		}

		// devido ao grafo poder ser desconexo, precisamos garantir 
		// que todos vertices vão ser visistados
		for(int cont=0; cont < 10; cont++){
			visitado.clear();
			qArestaAtual = 0;
			dfs(cont);	
		}

		printf("%d\n",*max_element(resultados.begin(), resultados.end() ));
		
		// fazendo a limpa, para a proxima iteração
		grafo.clear();
		resultados.clear();
		visitado.clear();
	}
	
	return 0;
	
}