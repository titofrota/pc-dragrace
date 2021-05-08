// Trabalho de Programação Concorrente
// Aluno: Ítalo Frota
// Matrícula: 18/0019279

// Bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

// Limpar a tela
#ifdef _WIN32
#include <conio.h>
#else
#include <stdio.h>
#define clrscr() printf("\e[1;1H\e[2J")
#endif

// Cores para a impressão no terminal
#define COLOR_RED "\x1b[31m"
#define COLOR_GREEN "\x1b[32m"
#define COLOR_YELLOW "\x1b[33m"
#define COLOR_BLUE "\x1b[34m"
#define COLOR_MAGENTA "\x1b[35m"
#define COLOR_CYAN "\x1b[36m"
#define COLOR_RESET "\x1b[0m"
#define BOLD_WHITE "\033[1m"
#define RESET "\x1b[0m"

//  Quantidades
#define QTD_QUEENS 16

// Funções
void * f_rupaul(void *arg);
void * f_queen(void *arg);

// Recursos de concorrência
pthread_t queen[QTD_QUEENS], rupaul;

sem_t rupaul_sem;             // semáforo da rupaul
sem_t critica_sem;            // semáforo da crítica da rupaul
sem_t queens_sem;             // semáforo das queens
sem_t espelho_sem;            // semáforo do espelho pras queen se montarem
sem_t passarela_sem;          // semáforo da queen que está desfilando
sem_t lipsync_sem;            // semáforo das duas queens dublando
sem_t mutex_sem;               


// Variáveis
int cont_queens = 0;          // contador de drag queens
int queens_montadas = 0;      // contador de queens montadas
int queens_desfilaram = 0;    // contador de queens que desfilaram
int x, y, z;                  // auxiliares
bool gravando = true;         // flag que determina a duração do episódio


int main (){
  int * id;
  int i;

  // Inicialização dos semáforos
  sem_init(&rupaul_sem, 0, 0);
  sem_init(&critica_sem, 0, 0);
  sem_init(&queens_sem, 0, QTD_QUEENS);
  sem_init(&espelho_sem, 0, QTD_QUEENS);
  sem_init(&passarela_sem, 0, 1);
  sem_init(&lipsync_sem, 0, 0);
  sem_init(&mutex_sem, 0, 0);

  clrscr();       // limpa a tela


  printf(COLOR_RED "\n\n          ######         ######                       ###              \n");
  printf(COLOR_RED "          #     # #    # #     #   ##   #    # #      ###  ####        \n");
  printf(COLOR_RED "          #     # #    # #     #  #  #  #    # #       #  #            \n");
  printf(COLOR_RED "          ######  #    # ######  #    # #    # #      #    ####        \n");
  printf(COLOR_RED "          #   #   #    # #       ###### #    # #               #       \n");
  printf(COLOR_RED "          #    #  #    # #       #    # #    # #          #    #       \n");
  printf(COLOR_RED "          #     #  ####  #       #    #  ####  ######      ####        \n");
  printf(COLOR_RED "                                                                       \n");
  printf(COLOR_RED "          ######                          ######                       \n");
  printf(COLOR_RED "          #     # #####    ##    ####     #     #   ##    ####  ###### \n");
  printf(COLOR_RED "          #     # #    #  #  #  #    #    #     #  #  #  #    # #      \n");
  printf(COLOR_RED "          #     # #    # #    # #         ######  #    # #      #####  \n");
  printf(COLOR_RED "          #     # #####  ###### #  ###    #   #   ###### #      #      \n");
  printf(COLOR_RED "          #     # #   #  #    # #    #    #    #  #    # #    # #      \n");
  printf(COLOR_RED "          ######  #    # #    #  ####     #     # #    #  ####  ###### \n" RESET);
                                                              
  printf("\n");
  printf("\n");
  printf(COLOR_MAGENTA "                      ♫♪♪ May the best woman win... ♫♪♪\n\n" RESET);
  sleep(3);

  // Criação das threads
  id = (int *) malloc(sizeof(int));
  * id = 0;
  pthread_create(&(rupaul), NULL, f_rupaul, (void *)id);      // Thread da RuPaul
  
  for(i = 0; i < QTD_QUEENS; i++){
    id = (int *) malloc(sizeof(int));
    * id = i;
    pthread_create(&(queen[i]), NULL, f_queen, (void *)id);   // Thread das Drag Queens
  }


  for (i = 0; i < QTD_QUEENS; i++){
    pthread_join(queen[i], NULL);
  }


  free(id);

  return 0;
}

void * f_rupaul(void *arg){
  int i;

  printf(BOLD_WHITE "\nRUPAUL: " COLOR_MAGENTA "Hello, hello, hello! No desafio dessa semana vocês devem desfilar looks inspirados em professores do CIC. \n\n" RESET);
  sleep(2);

  while(gravando){

    sem_wait(&rupaul_sem);            // espera para apresentar o programa
      queens_montadas = 0;            // zera o contador de queens montadas
      printf(BOLD_WHITE "\nRUPAUL: " COLOR_MAGENTA "Bem-vindo ao palco do RuPaul's Drag Race. \n" RESET);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "Nessa semana, desafiamos as nossas queens a servir seus melhores looks inspirados em professores do CIC. \n\n" RESET);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "Pilotos, liguem seus motores. E que a melhor Drag Queen vença! \n\n" RESET);
      printf(COLOR_GREEN "\n          ########## As queens vão desfilar ##########\n\n"RESET);
      sleep(3);
  
    sem_wait(&critica_sem);
      sleep(1);
      printf(COLOR_GREEN "\n          ########## Todas as queens desfilaram ##########\n\n"RESET);
      sleep(2);

      printf(COLOR_GREEN "\n          ########## RuPaul está avaliando as competidoras ##########\n"RESET);

      // escolha pseudorandomica das queens para o julgamento
      x = rand() %QTD_QUEENS-1;
      y = rand() %QTD_QUEENS-1;
      z = rand() %QTD_QUEENS-1;

      for(i = 0; i < QTD_QUEENS; i++){
        if((i != y) && (i != z)){
          pthread_cancel(queen[i]);         // encerra as threads das queens que não vão dublar
        }
      }

      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "Queen nº%d, essa semana você foi Marotta (rs) e seu look nos deixou de queixo caído. Você é a campeã dessa semana.\n" RESET, x);
      sleep(3);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "Queen nº%d, dessa vez você foi ousada... Mas seu look desceu Ladeira (rsrs) abaixo. Lamento, mas você pode ser eliminada.\n" RESET, y);
      sleep(3);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "Queen nº%d, você se arriscou mas desde a execução da sua ideia E Do Ar Do (rsssssssssss) seu conceito, tudo o que vimos foi um grande deadlock. Você pode ser eliminada.\n" RESET, z);
      sleep(2);

      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "Duas queens na minha frente. Senhoras, essa é última chance de me impressionarem e se salvarem da eliminação.\n" RESET);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "CHEGOU A HORA.\n" RESET);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "DE VOCÊS.\n" RESET);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "DUBLAREM.\n" RESET);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "POR.\n" RESET);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "SUAS.\n" RESET);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "VIDAS.\n\n" RESET);
      sleep(3);

      
      for(i = 0; i < 2; i++)
        sem_post(&lipsync_sem);         // libera as queens para dublar
      
      sem_wait(&mutex_sem);             // espera para dar o veredito final

      // escolha pseudorandômica de qual queen vai sair
      srand(time(NULL));
      int rnd = rand();
      int result = (rnd > RAND_MAX/2) ? y : z;

      printf(BOLD_WHITE "\nRUPAUL: " COLOR_MAGENTA "Senhoras, eu tomei a minha decisão.\n" RESET);
      printf(BOLD_WHITE "RUPAUL: " COLOR_MAGENTA "Queen nº%d, a sua hora não é essa. Você sempre será uma superestrela! Sashay, pode ir.\n" RESET, result);

      gravando =  false;            // encerra o episódio
    
  }
  
  pthread_exit(0);
}

void * f_queen(void *arg){
  int id = * ((int *) arg);

  if(gravando){

    // As queens se montam
    sem_wait(&espelho_sem);       // semáforo para usar o espelho
      queens_montadas++;
      sleep(1);                   // se monta
      printf(COLOR_YELLOW "A queen %d terminou de se montar.\n" RESET, id);
      if(queens_montadas ==  QTD_QUEENS){
        sem_post(&rupaul_sem);    // se todas as queens estiverem prontas, acorda a RuPaul
      }
      sem_post(&espelho_sem);

    
    // As queens desfilam, uma de cada vez
    sem_wait(&passarela_sem);
      queens_desfilaram++;
      sleep(1);                 // desfila
      if(queens_desfilaram == QTD_QUEENS){      // Quando todas as queens desfilam, a RuPaul avalia
        sem_post(&critica_sem);
      }
      printf(COLOR_CYAN "A queen %d desfilou na passarela.\n" RESET, id);
    sem_post(&passarela_sem);   // libera a passarela

    sem_wait(&lipsync_sem);     // espera para dublar
      printf(COLOR_CYAN "A queen %d está dublando.\n" RESET, id);
      sleep(1);                 // dubla
      sem_post(&mutex_sem);     // libera a decisão final

  }

  pthread_exit(0);
}

