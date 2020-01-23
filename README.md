# VRFEM

Biblioteca Matemática e Numérica para produção de códigos de Elementos Finitos com fins educacionais.

---

# Resumo dos Pacotes

A biblioteca é dividida em pacotes que são as ferramentas utilizadas para a produção dos códigos de FEM em cada caso. Os pacotes disponíveis nesta versão são:

- <a href="#vector">Vector</a>: Classe que armazena sequência de reais com dupla precisão e lida com operações da matemática de vetores
- <a href="#poly1d"> Poly1d</a>: Classe desenvolvida para se trabalhar com polinômios de primeira ordem no **R<sup>N</sup>**
- <a href="#numerical"> Numerical </a>: Possui funções numéricas de uso recorrente nos cálculos
- <a href="#matrix"> Matrix </a>: Classe representativa de matrizes e suas operações utilizadas nestes problemas
- <a href="#element"> Element </a>: Classe implementada para tratar de operações e amazenamento de dados concernentes aos elementos do método FE
- <a href="#mesh2d"> Mesh2d </a>: Classe que armazena os nós, os elementos e estabelece suas relações para a solução de problemas bidimensionais com domínios quadráticos


# Objetivo

O obetivo desta biblioteca é que fornecer para alunos das áreas de matemática, física, computação, engenharias e afins, as ferramentas acima possibilitando que os mesmos desenvolvam códigos do método de elementos finitos (em princípio) na linguagem C++ sem que os mesmos se preocupem com detalhes matemáticos/computacionais que não sejam do método, facilitando o aprendizado dos métodos, sua implementação e solução de problemas fornecidos na sala de aula.

Como objetivo secundário, este projeto também propõe aos alunos a refatoração e paralelização dos códigos dos pacotes vigentes em cada versão do mesmo, bem como a implementação de novos pacotes que facilitarão o uso da biblioteca.

# Documentação

## Vector

Classe utilizada para a representação de elementos matemáticos vetoriais.

1. **Atributos**

```C++
private:
	vector<double> x; // Dados do vetor
public:
	int dim;          // Dimensão
```

2. **Construtores**

```C++
Vector();                              // Inicializa com dimensão zero
Vector(int dim);                       // Inicializa comm dimensão fornecida
Vector(double vec[],int n);            // Inicializa com elementos fornecidos pelo vetor vec[], com tamanho n
Vector(std::initializer_list<double>); // Permite inicialização rápida. Ex.: Vector v({1,2,3}); // Cria vetor (1,2,3) de dimensão 3
```

3. **Métodos**

Todos os métodos abaixo são publicos.

```C++
void reset();           // Reseta os valores do vetor com o valor zero
void resize(int dim);   // Redimensiona o vetor
double sum();           // Retorna a soma das componentes do vetor
double norm();          // Calcula a norma do vetor
double dot(Vector vec); // Calcula o produto escalar entre dois vetores
Vector vec(Vector vec); // Calcula  o produto vetorial entre dois vetores (implementado apenas para dim = 2 e dim = 3)
string show();          // Retorna uma representação em string do objeto vetor
```

4. **Operações**

Os objetos da classe `Vector` realizam as quatro operações básicas (`+`, `-`. `*`, `/`) entre vetores (`Vector`) e reais (`double`), bem como as operações de atribuição composta (`+=`, `-=`, `*=`, `/=`). Quando as operações são realizadas entre vetores ela ocorre elemento a elemento de cada vetor, mesmo para a multiplicação e a divisão. Por exemplo, a operação de multiplicação entre os vetores `(1,0,2)` e `(4,2,3)` retornaria o vetor `(1,0,6)`, pois `(4,0,2) * (1,2,3) = (1*4, 0*2, 2*3) = (4,0,6)`.

A comparação entre dos vetores pode ser feita por meio dos operadores `==` e `!=`.

## Poly1d

Classe utilizada para a representação de polinomios de grau um no espaço *n*-dimensional.

Todos os métodos e atributos desta class são públicos.

1. **Atributos**

```C++
int dim;  // Dimensão do espaço do polinômio
Vector a; // Vetor contendo os coeficientes angulares do polinômio
double b; // Coeficiente linear do polinômio
```

2. **Construtores**

```C++
Poly1d(int dim);            // Inicializa polinômio com coeficientes zero fornecendo apenas a dimensão do seu espaço
Poly1d(double A, double B); // Inicializa polinônio no espaço R com coeficientes angular A e linear B
Poly1d(Vector A, double B); // Inicializa polinômio no mesmo espaço de A com coeficientes angulares A e linear B
```

3. **Operações**

Uma vez criado os polinômios, pode-se avaliar os pontos do espaço através de uma chamada do mesmo. Exemplo:

```C++
Poly1d p(3,1)           // Cria polinômio no espaço R: 3*x + 1

cout << p(1.2) << endl; // Retorna: 4.6, pois 3*1.2 + 1 == 4.6
```

O mesmo vale para diferentes espaços, exemplo:

```C++
Poly1d p(Vector({1,2,3}),2)         // Cria polinômio no espaço R^3: x + 2*y + 3*z + 1

cout << p(Vector({5,2,0})) << endl; // Retorna: 11, pois 5 + 2*2 + 3*0 + 2 == 11
```

Para polinômios inseridos até o `R^3` (inclui `R^1`, `R^2` e `R^3`), a chamada também pode ser feita fornecendo os valores das coordenadas diretamente (sem uso de objetos `Vector`). Desse modo, a chamada do exemplo anterior poderia ser reescrita como:

```C++
cout << p(5,2,0) << endl; // Retorna: 11
```

## Numerical

Este pacote contém apenas funções de métodos numéricos úteis aos alunos. Nesta versão apenas duas funções estão implementadas:

- integrate2d: realiza integração numérica de uma função definida um subconjunto do `R^2`. Integração é uma soma do volume de elementos triangulares cuja altura é o valor médio da função avaliada nos vétices de cada elemento triangular.
- [GaussSeidel](https://pt.wikipedia.org/wiki/M%C3%A9todo_de_Gauss-Seidel): método para resolução de sistemas lineares `A x = b`. Retorna o número de iterações utilizadas na convergência.


A chamada, bem como os parâmetros padrões de cada um desses métodos está apresentado abaixo.

```C++
double integrate2d(double (*fun)(double,double),Element *el, int nx=11, int ny=11);
int GaussSeidel(Matrix *A, Vector *x, Vector *b, double tol = 1e-5, int maxIt = 200);
```

## Matrix

Classe utilizada para representar matrizes e suas operações.

1. **Atributos**

```C++
private:
	double **data;    // Elementos da matriz
public:
	int nrows, ncols; // Número de linhas e colunas da matriz, respectivamente
```

2. **Construtores**

```C++
Matrix(int ordem);                                             // Inicializa uma matriz quadrada nula com ncols = nrows = ordem
Matrix(int nrows, int ncols);                                  // Inicializa uma matriz nula fornecendo suas dimmensões
Matrix(std::initializer_list<Vector> vec);                     // Inicializa uma matriz fornecendo os vetores que irão compor suas linhas
Matrix(std::initializer_list<double> vec,int nrows,int ncols); // Inicialização rápida de uma matriz fornecendo os valores e as dimensões
```

3. **Métodos**

```C++
void resize(int nrows,int ncols); // Redimensiona matriz
void resize(int order);           // Redimensiona matriz quadrada
void reset();                     // Realoca memória do atributo 'data' sem se preocupar em zerá-los

void zeros(); // Seta todos os elementos da matriz o sendo zero
void ones();  // Seta todos os elementos da matriz o sendo um

void show(); // Imprime matriz formatada na saída padrão do terminal

Vector row(int i);           // Retorna linha 'i' da matriz
void row(Vector vec, int i); // Substitui linha 'i' da matriz pelo vetor fornecido

Vector col(int i);           // Retorna coluna 'i' da matriz
void col(Vector vec, int i); // Substitui coluna 'i' da matriz pelo vetor fornecido

Vector diag(int k = 0);           // Retorna diagonal 'k' da matriz, sendo k=0 a diagonal principal, k>0, as diagonais superiores e k<0 as diagonais iferiores
void diag(Vector vec, int k = 0); // Substitui diagonal 'k' da matriz pelo vetor fornecido


double det();                     // Calcula determinante da matriz
double xdet(int i, int j);        // Calcula determinante da submatriz extraída ao se remover a linha 'i' e coluna 'j' desta matriz
Poly1d udet(int i, int dim = -1); // Calcula determinante da matriz considerando as últimas 'dim' componentes da linha 'i' como sendo indefinidas (undefined), por isso, retornando um polinômio do espaço R^{dim}.
void t();                         // transpõe matriz
double trace();                   // Retorna o traço da matriz
void to_square(double val = 1);   // Torna a matriz quadrada de maior ordem completando os novos elementos pela variável 'val'
void inverse();                   // Inverte matriz (não implementado ainda)
```

4. **Operações**

Elementos da matriz podem ser acessados normalmente através dos operadores `[]`, assim o elemento de linha `i` e coluna `j` da matriz `A` pode ser acessado/modificado através de `A[i][j]`. A operação de mulplicação matricial pode ser feita pelo operador `*`, sendo realizada entre matriz-matriz e matriz-vetor.

Uma vez estabelecida sua ordem (`nrows` e `ncols`), os elementos de uma matriz podem ser fornecidos de maneira rápida por meio do ([`initializer_list`](http://www.cplusplus.com/reference/initializer_list/initializer_list/)) fornecendo:

```C++
Matriz A(2,3);

A = {1,2,3,4,5,6}; // Inicialização rápida

A.show()

// Retorno:
// 1 2 3
// 4 5 6
```
Deve-se prestar atenção para que as quantidades de elementos sejam iguais, caso contrário, um erro interromperá o programa.

## Element

Classe utilizada para representar os elementos usados nos metodos FE.

1. **Atributos**

```C++
private:
	std::vector<Vector> *pNodes; // Ponteio para a lista dos nós
	std::vector<int> map;        // Lista com os índices globais dos nós locais, útil para realizar o mapeamento entre nós locais e globais
public:
	int nNodes;                  // Quantidade de nós
	double area;                 // Área do elemento
```

2. **Construtores**

```C++
Element(int nNodes);                                          // Gera elemento com 'nNodes' nós não especificados ainda
Element(std::vector<int> nodes, std::vector<Vector> *pNodes); // Gera elemento com nós especificados, bem como o ponteiro para a lista com os nós globais
```

3. **Métodos**

```C++
Poly1d shapef(int i);                                                        // Retorna polinômio que vale 1 no nó local 'i' e zero nos demais
void calc_area();                                                            // Calcula a área do elemento (apenas para elementos triangulares)
void set_pNodes(std::vector<Vector> *nodes);                                 // Define para inde o vetor 'pNodes'  apontará
Vector nodeVec (int i);                                                      // Retorna posição espacial do nó de indice local 'i'
double integrate(double (*fun)(double,double), int i, int nx=11, int ny=11); // Calcula interal da função 'fun' (definida no R^2) balaneada pela função 'shapef(i)' sobre uma malha em cima do elemento com divisões dadas por 'nx' e 'ny'
```

4. **Operações**

Para acessar o índice global dos nós locais de índice `i` basta utilizar o operador `[]` com o índice local. Exemplo:

```C++
Element el(3); // Gera elemento com três nós

// Gerar lista global de nós e especificar os nós do elemento 'el'

el[0] // Retorna o íncice global do no local de índice 0
el[1] // Retorna o íncice global do no local de índice 1
el[2] // Retorna o íncice global do no local de índice 2
```

## Mesh2d

Classe utilizada para gerar malhas **bidimensionais retangulares** com **elementos triangulares**.

1. **Atributos**

```C++
int x0,y0,x1,y1;               // Coordenadas bidimensionais inicial e final que definem os limites do retângulo
int nx, ny;                    // Ńúmero de divisões da malha nos eixos x e y
double hx, hy;                 // Dimensões dos elementos retangulares da malha
std::vector<Element> elements; // Lista de elementos da malha 
std::vector<Vector> nodes;     // Lista de nós da malha
```

2. **Construtores**

Construtor com parâmetros default, assim, uma chamada `Mesh2d()`, gerará uma malha definida no `[0,1]x[0,1]` com divisão `11x11`.

```C++
Mesh2d(int x0 = 0, int y0 = 0, int x1 = 1, int y1 = 1, int nx = 11, int ny = 11);
```

3. **Métodos**

```C++
int isBorder(int i); // Verifica se o nó de índice i está na borda do domínio
```

# Exemplo

Como exemplo, fez-se uso dos pacotes acima para a resolução da equação de Laplace suejeita às condições de contorno de dirichlet homogênea com força aplicada. O algoritmo implementado foi proposto por Joan J. Cerdà em [Simulationsmethoden I WS 09 10 Lecture Notes Finite element methods applied to solve PDE (2009)](http://citeseerx.ist.psu.edu/viewdoc/summary?doi=10.1.1.709.4279).