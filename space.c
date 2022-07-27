#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>


#include "space.h"

void inicializa_jogo(t_lista *l_alien, t_lista *l_canhao, t_lista *l_tiro_canhao, t_lista *l_tiro_alien, t_lista *l_barreira_A, t_lista *l_barreira_M, t_lista *l_nave_mae){

	inicializa_lista(l_alien);
	inicializa_lista(l_canhao);
	inicializa_lista(l_tiro_canhao);
	inicializa_lista(l_tiro_alien);
	inicializa_lista(l_barreira_A);
	inicializa_lista(l_barreira_M);
	inicializa_lista(l_nave_mae);

	insere_aliens(l_alien);
	insere_canhao(l_canhao);
	insere_barreira_A(l_barreira_A);
	insere_barreira_M(l_barreira_M);
}

void cria_borda(){
	int i;
	for(i = 0; i <= 37; i++){
		move(i, 0);
		addch('|');
		move(i, 100);
		addch('|');

	}

	for(i = 0; i <= 100; i++){
		move(0, i);
		addch('-');
		move(37, i);
		addch('-');
	}
}

void insere_aliens(t_lista *l){

	int pos_l = 3;
	int pos_c = 1;
	int i, j;


	for(i = 0; i < 5; i++){
		for(j = 0; j < 11; j++){
			if(i == 0){
				insere_inicio_lista(l, 1, 1, pos_l + 4*i, pos_c + 6*j);
			} else if(i == 1 || i == 2){
				insere_inicio_lista(l, 2, 1, pos_l + 4*i, pos_c + 6*j);
			} else {
				insere_inicio_lista(l, 3, 1, pos_l + 4*i, pos_c + 6*j);
			}
		}
	}
}

void insere_canhao(t_lista *l){

	insere_inicio_lista(l, 8, 1, 35, 48);
}

void insere_barreira_A(t_lista *l){

	int pos_l;
	int pos_c;

	int i, j;
	for(i = 0; i < 2; i++){
		pos_l = 31;
		pos_c = 16;
		for(j = 0; j < 8; j++){
			if(i == 0){ /* primeira linha */
				insere_inicio_lista(l, 6, 1,  pos_l, pos_c);
				if(j == 0 || j % 2 == 0){
					pos_c = pos_c + 4;
				} else if(j % 2 == 1){
					pos_c = pos_c + 17;
				}
			} else if(i == 1){ /* segunda linha */
				insere_inicio_lista(l, 6, 1,  pos_l+1, pos_c-1);
				if(j == 0 || j % 2 == 0){
					pos_c = pos_c + 6;
				} else if(j % 2 == 1){
					pos_c = pos_c + 15;
				}
			}
		}
	}
}

void insere_barreira_M(t_lista *l){
	
	int i, j, qtd_M, pos_l, pos_c, cont;

	for(i = 0; i < 3; i++){
		pos_l = 31;
		pos_c = 17;
		cont = 0;

		if(i == 0){
			qtd_M = 12; /* qtd de M por linha da barreira varia a cada linha */
		} else if(i == 1){
			qtd_M = 20;
		} else if(i == 2){
			qtd_M = 16;
		}

		for(j = 0; j < qtd_M; j++){

			if(i == 0){ /* primeira linha  */
				insere_inicio_lista(l, 9, 1,  pos_l, pos_c);
				cont++;
				if(cont == 3){
					pos_c = pos_c + 19;
					cont = 0;
				} else {
					pos_c = pos_c + 1;
				}

			} else if(i == 1){ /*  segunda linha */
				insere_inicio_lista(l, 9, 1,  pos_l+1, pos_c-1);
				cont++;

				if(cont == 5){
					pos_c = pos_c + 17;
					cont = 0;
				} else {
					pos_c = pos_c + 1;
				}


			} else if(i == 2){ /* terceira linha */
				insere_inicio_lista(l, 9, 1,  pos_l+2, pos_c-2);
				cont++;
				if(cont == 2){
					pos_c = pos_c + 4;
				} else if(cont == 4){
					pos_c = pos_c + 15;
					cont = 0;
				} else {
					pos_c = pos_c + 1;
				}
			}
		}
	}
}

void insere_nave_mae(t_lista *l){

	insere_inicio_lista(l, 7, 1, 1, -10);
}

void insere_tiro(t_lista *l, t_lista *c){

	inicializa_atual_inicio(c);
	if(c->atual->tipo == 8){
		if(l->tamanho < 5){
			insere_inicio_lista(l, 4, 1, (c->atual->pos_l)-1, (c->atual->pos_c)+2);
		}
	} else if(c->atual->tipo == 1 || c->atual->tipo == 2 || c->atual->tipo == 3){
		if(l->tamanho < 3){
			int n = rand() % c->tamanho;
			int i;
			for(i = 0; i < n; i++){
				incrementa_atual(c);
			}
			insere_inicio_lista(l, 5, 1, (c->atual->pos_l)+3, (c->atual->pos_c)+2);
		}	
	}
}

void imprime_nave_mae(t_lista *l){

	int i, j, k;

	inicializa_atual_inicio(l);
	k = 0;
	for(i = 0; i < 3; i++){
		for(j = 0; j < 9; j++){
			move((l->atual->pos_l)+i,(l->atual->pos_c)+j);
			if(l->atual->pos_c + j > 0 && l->atual->pos_c + j < 100){
				addch(l->atual->corpo1[k]);
			}
			k++;
		}
	}
}

void imprime_barreira(t_lista *l){

	inicializa_atual_inicio(l);

	int i;
	for(i = 0; i < l->tamanho; i++){
		move(l->atual->pos_l, l->atual->pos_c);
		addch(l->atual->corpo1[0]);
		incrementa_atual(l);
	}
}

void imprime_aliens(t_lista *l, int *anima){

	inicializa_atual_inicio(l);

	int i, j, k, m;

	for(m = 0; m < l->tamanho; m++){
		k = 0;
		for(i = 0; i < 3; i++){
			for(j = 0; j < 5; j++){
				move((l->atual->pos_l)+i,(l->atual->pos_c)+j);
				if(l->atual->estado == vivo){
					if(*anima % 4 == 0){
						addch(l->atual->corpo1[k]);
					} else {
						addch(l->atual->corpo2[k]);
					}
				}
				k++;
			}
		}
		incrementa_atual(l);
	}
}

void imprime_canhao(t_lista *l){

	int i, j, k;

	inicializa_atual_inicio(l);

	k = 0;
	for(i = 0; i < 2; i++){
		for(j = 0; j < 5; j++){
			move((l->atual->pos_l)+i,(l->atual->pos_c)+j);
			addch(l->atual->corpo1[k]);
			k++;
		}
	}
}

void imprime_tiro(t_lista *l){

	int i;
	inicializa_atual_inicio(l);
	for(i = 0; i < l->tamanho; i++){
		move(l->atual->pos_l, l->atual->pos_c);
		addch(l->atual->corpo1[0]);
		incrementa_atual(l);
	}
}

void incrementa_posicao_nave_mae(t_lista *l){

	inicializa_atual_inicio(l);
	l->atual->pos_c++;
}

void incrementa_posicao_alien(t_lista *l, int *flag, int *perdeu){

	int m;
	int desce = 0;

	inicializa_atual_inicio(l);
	for(m = 0; m < l->tamanho; m++){
		if(l->atual->pos_c == 95){
			*flag = 1;
			desce = 1;
		} else if(l->atual->pos_c == 1){
			*flag = 0;
			desce = 1;
		}
		incrementa_atual(l);
	}
		
	inicializa_atual_inicio(l);
	for(m = 0; m < l->tamanho; m++){
		if(*flag == 0){
			l->atual->pos_c++;
		} else if(*flag == 1){
			l->atual->pos_c--;
		}
		if(desce){
			l->atual->pos_l++;
		}
		if(l->atual->pos_l == 34){
			*perdeu = 1;
		}
		incrementa_atual(l);
	}
}

void incrementa_posicao_tiro(t_lista *l){

	int i;
	inicializa_atual_inicio(l);
	for(i = 0; i < l->tamanho; i++){
		if(l->atual->tipo == 4){
			l->atual->pos_l--;
		} else if(l->atual->tipo == 5){
			l->atual->pos_l++;
		}
		incrementa_atual(l);
	}	
}

void remove_tiro(t_lista *l){
	int i;
	int removeu = 0;
	inicializa_atual_inicio(l);
	for(i = 0; i < l->tamanho; i++){
		if(l->atual->tipo == 4){
			if(l->atual->pos_l == 0){
				remove_item_atual(l);
			}
		} else if(l->atual->tipo == 5){
			if(l->atual->pos_l >= 37){
				remove_item_atual(l);
				removeu = 1;
			}
		}
		if(removeu == 0){
			incrementa_atual(l);
		}
	}
}

void remove_nave_mae(t_lista *l){

	inicializa_atual_inicio(l);
	if(l->atual->pos_c > 100){
		remove_item_atual(l);
	}
}

void verifica_colisao(t_lista *alvo, t_lista *tiro, int *pontuacao, int *perdeu){ 

	int i, j, removeu;
	inicializa_atual_inicio(alvo);
	if(alvo->atual->tipo == 1 || alvo->atual->tipo == 2 || alvo->atual->tipo == 3){ /* se o alvo for alien, compara com tiro de canhao */
		inicializa_atual_inicio(tiro);
		if(tiro->atual->tipo == 4){ /* se o 'tiro' for de canhao */
			for(i = 0; i < alvo->tamanho; i++){
				inicializa_atual_inicio(tiro);
				removeu = 0;
				for (j = 0; j < tiro->tamanho; j++){
					if(tiro->atual->pos_l >= alvo->atual->pos_l && tiro->atual->pos_l < (alvo->atual->pos_l)+2 && tiro->atual->pos_c >= alvo->atual->pos_c && tiro->atual->pos_c < (alvo->atual->pos_c)+4){
						remove_item_atual(tiro);
						move(alvo->atual->pos_l, alvo->atual->pos_c);
						printw(" \\'/ ");
						move(alvo->atual->pos_l+1, alvo->atual->pos_c);
						printw("-   -");
						move(alvo->atual->pos_l+2, alvo->atual->pos_c);
						printw(" /,\\ ");
						remove_item_atual(alvo);
						*pontuacao = *pontuacao + 10;
						removeu = 1;
					} else {
						incrementa_atual(tiro);
					}
				}
				if(removeu == 0){
					incrementa_atual(alvo);
				}
			}
		} else if(tiro->atual->tipo == 6 || tiro->atual->tipo == 9){ /* se o 'tiro' for a barreira */
			for(i = 0; i < alvo->tamanho; i++){
				inicializa_atual_inicio(tiro);
				removeu = 0;
				for (j = 0; j < tiro->tamanho; j++){
					if(tiro->atual->pos_l >= alvo->atual->pos_l && tiro->atual->pos_l <= (alvo->atual->pos_l)+2 && tiro->atual->pos_c >= alvo->atual->pos_c && tiro->atual->pos_c < (alvo->atual->pos_c)+4){
						remove_item_atual(tiro);
					} else {
						incrementa_atual(tiro);
					}
				}
				incrementa_atual(alvo);
				
			}
		}

	} else if(alvo->atual->tipo == 7) { /* se o alvo for nave mae, verifica tiro de canhao */
			for(i = 0; i < alvo->tamanho; i++){
				inicializa_atual_inicio(tiro);
				removeu = 0;
				for (j = 0; j < tiro->tamanho; j++){
					if(tiro->atual->pos_l >= alvo->atual->pos_l && tiro->atual->pos_l < (alvo->atual->pos_l)+2 && tiro->atual->pos_c >= alvo->atual->pos_c && tiro->atual->pos_c < (alvo->atual->pos_c)+8){
						remove_item_atual(tiro);
						move(alvo->atual->pos_l, alvo->atual->pos_c);
						printw(" \\'/ ");
						move(alvo->atual->pos_l+1, alvo->atual->pos_c);
						printw("-   -");
						move(alvo->atual->pos_l+2, alvo->atual->pos_c);
						printw(" /,\\ ");
						remove_item_atual(alvo);
						*pontuacao = *pontuacao + 100;
						removeu = 1;
					} else {
						incrementa_atual(tiro);
					}
				}
				if(removeu == 0){
					incrementa_atual(alvo);
				}
			}

	} else if(alvo->atual->tipo == 8){ /* se o alvo for canhao, verifica tiro de alien */
		for(i = 0; i < alvo->tamanho; i++){
			inicializa_atual_inicio(tiro);
			removeu = 0;
			for (j = 0; j < tiro->tamanho; j++){
				if(tiro->atual->pos_l >= alvo->atual->pos_l && tiro->atual->pos_c >= alvo->atual->pos_c && tiro->atual->pos_c < (alvo->atual->pos_c)+4){
					*perdeu = 1;
				} else {
					incrementa_atual(tiro);
				}
			}
			if(removeu == 0){
				incrementa_atual(alvo);
			}
		}		
	} else if(alvo->atual->tipo == 6 || alvo->atual->tipo == 9){ /* se o alvo for barreira, verifica o tiro */
		for(i = 0; i < alvo->tamanho; i++){
			inicializa_atual_inicio(tiro);
			removeu = 0;
			for (j = 0; j < tiro->tamanho; j++){
				if(tiro->atual->pos_l == alvo->atual->pos_l && tiro->atual->pos_c == alvo->atual->pos_c){
					remove_item_atual(tiro);
					remove_item_atual(alvo);
					removeu = 1;
				} else {
					incrementa_atual(tiro);
				}
			}
			if(removeu == 0){
				incrementa_atual(alvo);
			}
		}
	}
}

void libera_jogo(t_lista *l_alien, t_lista *l_canhao, t_lista *l_tiro_canhao, t_lista *l_tiro_alien, t_lista *l_barreira_A, t_lista *l_barreira_M, t_lista *l_nave_mae){
	
	destroi_lista(l_alien);
	destroi_lista(l_canhao);
	destroi_lista(l_tiro_canhao);
	destroi_lista(l_tiro_alien);
	destroi_lista(l_barreira_A);
	destroi_lista(l_barreira_M);
	destroi_lista(l_nave_mae);
}

/* Cria uma lista vazia duplamente encadeada com sentinelas no
  inicio e no final. Tambem tem um apontador para um elemento qualquer. */
int inicializa_lista(t_lista *l){
	l->tamanho = 0;
	l->ini = (t_nodo *) malloc(sizeof(t_nodo));
	if (l->ini == NULL)
		return 0;
	l->fim = (t_nodo *) malloc(sizeof(t_nodo));
	if (l->fim == NULL)		
		return 0;

	l->ini->prox = l->fim;
	l->ini->prev = NULL;

	l->fim->prox = NULL;
	l->fim->prev = l->ini;

	l->atual = NULL;
	
	return 1;
}
/* Retorna 1 se a lista está vazia e zero caso contrário. */
int lista_vazia(t_lista *l){
	if (l->tamanho == 0)
		return 1;
	return 0;
}
/* Remove todos os elementos da lista e faz com que ela aponte para NULL. */
void destroi_lista(t_lista *l){


	inicializa_atual_inicio(l);
	while (! lista_vazia(l)){
		remove_item_atual(l);
	}

	free(l->ini);
	free(l->fim);

	l->ini = NULL;
	l->fim = NULL;
	l->atual = NULL;
}
/* Insere o elemento item no início da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int insere_inicio_lista(t_lista *l, int tipo, int velocidade, int pos_l, int pos_c){
	t_nodo *new;

	new = (t_nodo *) malloc(sizeof(t_nodo));
	if (new == NULL)
		return 0;

	new->estado = vivo;
	new->tipo = tipo;
	new->velocidade = 1;
	new->pos_l = pos_l;
	new->pos_c = pos_c;

	int i;

	if(tipo == 1){
		for(i = 0; i < tamanho_corpo; i++){
			new->corpo1[i] = alien1A[i];
			new->corpo2[i] = alien1B[i];
		}
	} else if(tipo == 2) {
		for(i = 0; i < tamanho_corpo; i++){
			new->corpo1[i] = alien2A[i];
			new->corpo2[i] = alien2B[i];

		}
	} else if(tipo == 3) {
		for(i = 0; i < tamanho_corpo; i++){
			new->corpo1[i] = alien3A[i];
			new->corpo2[i] = alien3B[i];

		}
	} else if(tipo == 4) {
		for(i = 0; i < tamanho_corpo; i++){ 
			new->corpo1[i] = tiro_canhao[i];
		}
	} else if(tipo == 5) {
		for(i = 0; i < tamanho_corpo; i++){
			new->corpo1[i] = tiro_alien[i];
		}
	} else if(tipo == 6) {
		for(i = 0; i < tamanho_corpo; i++){
			new->corpo1[i] = barreira_A[i];
		}
	} else if(tipo == 7) {
		for(i = 0; i < tamanho_corpo; i++){
			new->corpo1[i] = nave_mae[i];
		}
	} else if(tipo == 8) {
		for(i = 0; i < tamanho_corpo; i++){
			new->corpo1[i] = canhao[i];
		}
	} else if(tipo == 9) {
		for(i = 0; i < tamanho_corpo; i++){
			new->corpo1[i] = barreira_M[i];
		}
	}
	

	new->prev = l->ini;
	new->prox = l->ini->prox;

	new->prox->prev = new;
	new->prev->prox = new;

	l->tamanho++;

	return 1;
}
/* Inicializa o ponteiro atual para o primeiro elemento da lista.
  Retorna 1 se a operação foi bem sucedida e zero caso contrário. */
int inicializa_atual_inicio(t_lista *l){
	if (lista_vazia(l))
		return 0;
	l->atual = l->ini->prox;
	return 1;
}
/* Faz o ponteiro atual apontar para o próximo nodo da lista l e retorna 
  este ponteiro. Se atual estiver apontando para o último, isto é, não 
  tem próximo, retorna NULL.
*/
void incrementa_atual(t_lista *l){
	if (l->atual->prox != NULL)
		l->atual = (l->atual)->prox;
	else
		l->atual = NULL;
}
/* Remove o elemento apontado por atual da lista l e o retorna em *item.
  Faz o atual apontar para o sucessor do nodo removido.
  Retorna 1 se houve sucesso e zero caso contrário. */
int remove_item_atual(t_lista *l){
	if (lista_vazia(l))
		return 0;

	t_nodo *temp;

	temp = l->atual->prox;
	l->atual->prev->prox = l->atual->prox;
	l->atual->prox->prev = l->atual->prev;
	free(l->atual);
	l->atual = temp;
	l->tamanho--;
	return 1;
}
