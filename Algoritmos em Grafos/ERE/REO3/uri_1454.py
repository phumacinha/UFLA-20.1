'''
Disciplina:
    GCC218 - Algoritmo em Grafos

Integrantes: 
    Igor Antônio dos Santos Alves Mendes
    Isaías Gonçalves Ribeiro
    Pedro Antônio de Souza

Problema:
    1454 - O País das Bicicletas

Estratégia Adotada:
    Para cada instância, modelamos um grafo onde as interseções entre ruas são
    os vértices. As arestas representam as ruas e o peso associado a cada
    aresta representa a altura entre as interseções de ruas.
    Modificamos o Algortimo de Floyd-Warshall para a resolução das instâncias.
    No algoritmo original, o objetivo é calcular distâncias entre vértices,
    sendo a distância definida como a soma do peso das arestas que pertencem ao
    caminho. Porém, nesse problema o objetivo é encontrar o caminho entre dois
    vértices que utilizem arestas com os menores pesos possíveis. Assim, o
    cálculo de novas distâncias (nesse caso, as distâncias são as alturas) foi
    modificado da seguinte maneira: calcula-se o menor valor entre a altura já
    definida na matriz de distâncias (alturas) e o maior valor encontrado entre
    vértice de origem até um vértice intermediário e entre o vértice
    intermediário e o vértice de destino. Portanto, o algoritmo sempre buscará
    o menor entre os maiores valores já encontrados.
'''


'''
    Classe implementada para resolução do problema.
    Instancia um grafo não direcionado.
'''
class GrafoMrLee():
    
    """O construtor da class.
    
    :param n: quantidade de vértices do grafo (interseções entre ruas)
    """
    def __init__(self, n:int):
        self.__n = n

        # Variável que armazenará a maior altura entre pares de vértices.
        # É inicializada como a matriz de adjacência do grafo para, posteriormente,
        # ser utilizada na execução do algoritmo para encontrar a solução do problema.
        self.__matriz_altura = list()

        # Inicializa a matriz de alturas
        self.__inicializa_matriz_altura()

    """Adiciona arestas no grafo.
    
    :param v1: primeiro vértice da aresta
    :type v1: int
    :param v2: segundo vértice da aresta
    :type v2: int
    :param altura: peso da aresta
    :type altura: int
    """
    def add_aresta(self, v1:int, v2:int, altura:int):
        self.__matriz_altura[v1][v2] = altura
        self.__matriz_altura[v2][v1] = altura

    """Inicializa matriz de altura. Para posições da matriz com índice de linha
    e coluna iguais, define valor como zero. Para as demais, define o valor
    como infinito."""
    def __inicializa_matriz_altura(self):
        for i in range(self.__n):
            self.__matriz_altura.append([0 if j == i else float('inf') for j in range(self.__n)])

    """Calcula a menor altura máxima entre cada par de vértices do grafo,
    atualizando a matriz de alturas.

    :returns: matriz com alturas máximas entre vértices.
    :rtype: list
    """
    def floyd_warshall_modificado(self) -> list:
        matriz = self.__matriz_altura.copy()
        for k in range(self.__n):
            for i in range(self.__n):
                for j in range(self.__n):
                    if i != j:
                        matriz[i][j] = min(matriz[i][j], max(matriz[i][k], matriz[k][j]))
        
        return matriz;
        


# Inicia a variável instancia com 1. Ela será utilizada na impressão das
# soluções.
instancia = 1

# Lê as entradas de quantidade de interseções (n) e quantidade de ruas (m).
n, m = map(int, input().split())

while not (n == 0 and m == 0):
    G = GrafoMrLee(n)  # Instancia um novo grafo

    # Adiciona arestas.
    for _ in range(m):
        v1, v2, altura = map(int, input().split())

        # No problema, o índice dos vértices se iniciam em 1. No código, eles
        # são decrementados para facilitar a implementação e utilização de listas.
        G.add_aresta(v1-1, v2-1, altura)


    # Recebe a quantidade de rotas a serem caluladas.
    qtd_rotas = int(input())
    rotas = list()

    # Adiciona as rotas (recebidas como entrada) em forma de tupla na lista de rotas
    for _ in range(qtd_rotas):
        rotas.append(tuple(map(int, input().split())))

    print('Instancia', instancia)

    # Aplica o algoritmo implementado para solução do problema atualizando,
    # assim, a matriz de altura.
    alturas = G.floyd_warshall_modificado()
    for rota in rotas:
        v1, v2 = rota[0], rota[1]
        # Aqui, os índices dos vetores também são decrementados para fazer a
        # "conversão" de índices.
        print(alturas[v1-1][v2-1])
    print()

    # Incrementa a variável instancia e recebe novos paramêtros da próxima
    # instância.
    instancia = instancia + 1
    n, m = map(int, input().split())
