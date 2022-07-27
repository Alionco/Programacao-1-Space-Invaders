/*
  Feito por Marcos Castiho para a disciplina CI1001 - Programacao I
  Em 18/10/2019.
  Define a estrutura de dados para o Tipo Abstrato de Dados Lista
  como sendo uma lista duplamente encadeada com sentinelas no inicio
  e no final. A cabeca da lista tem ponteiros para o inicio, fim e
  para um elemento qualquer da lista, alem do tamanho da lista.
  Contem os prototipos publicos das funcoes que manipulam o TAD.
*/
#define vivo 1
#define morto 2
#define tamanho_corpo 27
#define alien1A "  A   AMA  /X\\ "
#define alien1B "  A   AMA  { }  "
#define alien2A ".v_v.}WMW{ / \\ "
#define alien2B ".v_v.}WMW{'( )' "
#define alien3A " nmn dbMdb_/-\\_"
#define alien3B " nmn dbMdb <^>  "
#define tiro_canhao "|"
#define tiro_alien "$"
#define barreira_A "A"
#define barreira_M "M"
#define nave_mae " /MMMMM\\ AMoMoMoMA \\/'-'\\/ "
#define canhao " /^\\ MMMMM"

struct t_nodo {
    int estado;
    int tipo;
    char corpo1[tamanho_corpo];
    char corpo2[tamanho_corpo];
    int velocidade;
    int pos_l;
    int pos_c;
    struct t_nodo *prox;
    struct t_nodo *prev;
};
typedef struct t_nodo t_nodo;

struct t_lista {
    t_nodo *ini;
    t_nodo *atual;
    t_nodo *fim;
    int tamanho;
};
typedef struct t_lista t_lista;

void inicializa_jogo(t_lista *l_alien, t_lista *l_canhao, t_lista *l_tiro_canhao, t_lista *l_tiro_alien, t_lista *l_barreira_A, t_lista *l_barreira_M, t_lista *l_nave_mae);

void cria_borda();

void insere_aliens(t_lista *l);

void insere_canhao(t_lista *l);

void insere_barreira_A(t_lista *l);

void insere_barreira_M(t_lista *l);

void insere_nave_mae(t_lista *l);

void insere_tiro(t_lista *l, t_lista *c);

void imprime_nave_mae(t_lista *l);

void imprime_barreira(t_lista *l);

void imprime_aliens(t_lista *l, int *anima);

void imprime_canhao(t_lista *l);

void imprime_tiro(t_lista *l);

void incrementa_posicao_nave_mae(t_lista *l);

void incrementa_posicao_alien(t_lista *l, int *flag, int *perdeu);

void incrementa_posicao_tiro(t_lista *l);

void remove_tiro(t_lista *l);

void remove_nave_mae(t_lista *l);

void verifica_colisao(t_lista *l, t_lista *m, int *pontuacao, int *perdeu);

void libera_jogo(t_lista *l_alien, t_lista *l_canhao, t_lista *l_tiro_canhao, t_lista *l_tiro_alien, t_lista *l_barreira_A, t_lista *l_barreira_M, t_lista *l_nave_mae);


/*
  Cria uma lista vazia. Ela eh duplamente encadeada e tem sentinelas no
  inicio e no final. Tambem tem um apontador para um elemento qualquer.
*/
int inicializa_lista(t_lista *l);

/*
  Retorna 1 se a lista está vazia e zero caso contrário.
*/
int lista_vazia(t_lista *l);

/*
  Remove todos os elementos da lista e faz com que ela aponte para NULL.
*/
void destroi_lista(t_lista *l);

/*
  Insere o elemento item no início da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int insere_inicio_lista(t_lista *l, int tipo, int velocidade, int pos_l, int pos_c);

/* 
  Inicializa o ponteiro atual para o primeiro elemento da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário.
*/
int inicializa_atual_inicio(t_lista *l);
/*
  Faz o ponteiro atual apontar para o próximo nodo da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o último, isto é, não 
  tem próximo, retorna NULL.
*/
void incrementa_atual(t_lista *l);
/*
  Remove o elemento apontado por atual da lista l e o retorna em *item.
  Faz o atual apontar para o sucessor do nodo removido.
  Retorna 1 se houve sucesso e zero caso contrário.
*/
int remove_item_atual(t_lista *l);