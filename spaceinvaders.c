#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include "space.h"

int main() {
  
	initscr();              /* inicia a tela */
    cbreak();               /* desabilita o buffer de entrada */
    noecho();               /* não mostra os caracteres digitados */
    nodelay(stdscr, TRUE);  /* faz com que getch não aguarde a digitação */
    keypad(stdscr, TRUE);   /* permite a leitura das setas */
    curs_set(FALSE);        /* não mostra o cursor na tela */


    start_color();

	init_pair(1, COLOR_WHITE, COLOR_BLACK);
 	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_RED, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_YELLOW, COLOR_BLACK);


  	
  	int nlin, ncol;

	int inverte_sentido = 0;
	int velocidade = 0;
	int cont = 0;
	int cont_nave_mae = 1;
	int tempo = 100000;
	int anima = 0;
	int pontuacao = 0;
	int perdeu = 0;


	getmaxyx(stdscr, nlin, ncol);

	if(nlin < 40 || ncol < 100){
		endwin();
		printf("ERRO SEU BOCO");
		exit(0);
	}

	t_lista lista_alien;
	t_lista lista_canhao;
	t_lista lista_tiro_canhao;
	t_lista lista_tiro_alien;
	t_lista lista_barreira_A;
	t_lista lista_barreira_M;
	t_lista lista_nave_mae;


	inicializa_jogo(&lista_alien, &lista_canhao, &lista_tiro_canhao, &lista_tiro_alien, &lista_barreira_A, &lista_barreira_M, &lista_nave_mae);

	while(1){ 

/* IMPRESSOES */

		clear();

		int comparador = inverte_sentido;

		int i;

		for(i = 0; i <= velocidade; i++){
			clear();
			wattron(stdscr, COLOR_PAIR(2));
			imprime_aliens(&lista_alien, &anima);
			incrementa_posicao_alien(&lista_alien, &inverte_sentido, &perdeu);
			refresh();
			anima++;
		}

		if(inverte_sentido != comparador){
			cont++;
			if(cont % 7 == 0){
				velocidade++;
			}
		}

  		wattron(stdscr, COLOR_PAIR(1));
		cria_borda();
		wattron(stdscr, COLOR_PAIR(4));
		imprime_canhao(&lista_canhao);
		wattron(stdscr, COLOR_PAIR(1));
		imprime_barreira(&lista_barreira_A);
		imprime_barreira(&lista_barreira_M);
		if(!lista_vazia(&lista_tiro_canhao)){
			wattron(stdscr, COLOR_PAIR(3));
			imprime_tiro(&lista_tiro_canhao);
		}
		wattron(stdscr, COLOR_PAIR(5));
		imprime_tiro(&lista_tiro_alien);

		if(!lista_vazia(&lista_nave_mae)){		
			imprime_nave_mae(&lista_nave_mae);
		}

/* INSERCOES */

		char key = getch();

		inicializa_atual_inicio(&lista_canhao);

		if(key == ' '){
			insere_tiro(&lista_tiro_canhao, &lista_canhao);
		}

		insere_tiro(&lista_tiro_alien, &lista_alien);

		if(cont_nave_mae % 250 == 0 || cont_nave_mae == 50){
			insere_nave_mae(&lista_nave_mae);
		}


/* COLISOES */

		verifica_colisao(&lista_alien, &lista_barreira_A, &pontuacao, &perdeu);
		verifica_colisao(&lista_alien, &lista_barreira_M, &pontuacao, &perdeu);
		verifica_colisao(&lista_barreira_A, &lista_tiro_canhao, &pontuacao, &perdeu);
		verifica_colisao(&lista_barreira_M, &lista_tiro_canhao, &pontuacao, &perdeu);
		verifica_colisao(&lista_barreira_A, &lista_tiro_alien, &pontuacao, &perdeu);
		verifica_colisao(&lista_barreira_M, &lista_tiro_alien, &pontuacao, &perdeu);
		verifica_colisao(&lista_canhao, &lista_tiro_alien, &pontuacao, &perdeu);

		if(!lista_vazia(&lista_tiro_canhao)){
			verifica_colisao(&lista_alien, &lista_tiro_canhao, &pontuacao, &perdeu);
			if(!lista_vazia(&lista_nave_mae)){
				verifica_colisao(&lista_nave_mae, &lista_tiro_canhao, &pontuacao, &perdeu);
			}
		}



/* INCREMENTOS */


		inicializa_atual_inicio(&lista_canhao);

		if(key == 'a' && lista_canhao.atual->pos_c > 1){
			lista_canhao.atual->pos_c--;
		} else if(key == 'd' && lista_canhao.atual->pos_c < 95){
			lista_canhao.atual->pos_c++;
		}

		if(!lista_vazia(&lista_tiro_canhao)){
			incrementa_posicao_tiro(&lista_tiro_canhao);
		}

		incrementa_posicao_tiro(&lista_tiro_alien);

		if(!lista_vazia(&lista_nave_mae)){
			incrementa_posicao_nave_mae(&lista_nave_mae);
		}


/* REMOCOES */

		if(!lista_vazia(&lista_tiro_canhao)){
			remove_tiro(&lista_tiro_canhao);
		}

		remove_tiro(&lista_tiro_alien);

		if(!lista_vazia(&lista_nave_mae)){
			remove_nave_mae(&lista_nave_mae);
		}

/* COMPLEMENTOS */


		if(key == 'q'){
			libera_jogo(&lista_alien, &lista_canhao, &lista_tiro_canhao, &lista_tiro_alien, &lista_barreira_A, &lista_barreira_M, &lista_nave_mae);
			endwin();
			exit(0);
		} else if(key == 'p'){
			sleep(10);
		}

		if(lista_vazia(&lista_alien)){
			libera_jogo(&lista_alien, &lista_canhao, &lista_tiro_canhao, &lista_tiro_alien, &lista_barreira_A, &lista_barreira_M, &lista_nave_mae);
			inicializa_jogo(&lista_alien, &lista_canhao, &lista_tiro_canhao, &lista_tiro_alien, &lista_barreira_A, &lista_barreira_M, &lista_nave_mae);		
		}

		if(perdeu == 1){
			libera_jogo(&lista_alien, &lista_canhao, &lista_tiro_canhao, &lista_tiro_alien, &lista_barreira_A, &lista_barreira_M, &lista_nave_mae);
			endwin();
			printf("FIM DE JOGO - PONTUACAO: %d\n", pontuacao);
			exit(0);

		}

		move(39, 46);
		printw("PONTUACAO");
		move(40, 46);
		printw("%d", pontuacao);

		cont_nave_mae++;

		refresh();
		flushinp();

		usleep(tempo);

	}
}