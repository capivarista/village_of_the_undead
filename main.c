
#include "desing.h"
#include "historia.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool erro_fix = false;
FILE *salvar;
int escolha_bebado;

typedef struct {
  // Define a vida e vai de 0 a 50.
  int stamina;
  // Define o dano e vai de 0 a 15.
  int forca;
  // Define a defesa e vai de 0 a 20.
  int destreza;
  // Status do personagem
  int vida;
  int dano;
  int defesa;
} ficha_jogador;

typedef struct {
  char slots[4][20];
  int valor_itens[4];
  int capital;
} inventario;

typedef struct {
  int vida;
  int dano;
  int defesa;
} ficha_inimigo_minion;

// inventario do jogador
inventario inventario_jogador;

int vidamax;

// Guarda as informações do jogador(personagem)
ficha_jogador jogador;

// Fução para invetario e afins
void pocao();
void vazio();
void espada();
void armadura();

// função para informar o valor de seus atributos indiretamente
void nivel_vigor();
void nivel_forca();
void nivel_destreza();

// encontro aleatorio enquanto muda de região
void encontro(int escolha);

// regiões do jogo
void casebre(int escolha);
void loja();
int taverna(int escolha);
void mansao(int escolha);
int igreja(int escolha);
int Bcemiterio(int escolha);
int triangulo(int escolha);

// Eventos em regiões do jogo
void taverna_combate(int escolha);

// Função para os efeitos de uso dos itens_consumiveis
void itens_consumiveis(int i);

// Funções utilitarias
void imprimir_inventario();

// MAIN_CODE

int main(void) {
  Finicio();

  ficha_inimigo_minion bebado;

  // Escoha do jogador
  int escolha = 0;

  // contabiliza oque acontece no jogo
  int evento = 0;
  printf("Nasce-se do horizente a figura que protaganiza nossa historia "
         "macabra. Quem será ela?\n\n");

  // armazena uma poção no inventario
  vazio();
  inventario_jogador.valor_itens[0] = 1;
  pocao();

  // desing de personagem
  Fpersonagem();

  printf("Escolha sua "
         "classe:\n1.Cavaleiro\n2.Assasino\n3.Barbáro\n4.Oraculo(AVISO: não "
         "recomendado para iniciantes)\n");
  escolha = 1;
  // Escolha de classes
  while (escolha != 0) {
    scanf("%d", &escolha);
    switch (escolha) {

      // Classe de Cavaleiro e atributos
    case 1:

      jogador.stamina = 25;
      jogador.destreza = 13;
      jogador.forca = 7;
      escolha = 0;
      break;

      // Classe de assasino e atributos
    case 2:

      jogador.stamina = 20;
      jogador.destreza = 10;
      jogador.forca = 12;
      break;

      escolha = 0;

    // Classe de bárbaro e atzributos
    case 3:

      jogador.stamina = 35;
      jogador.destreza = 10;
      jogador.forca = 5;
      escolha = 0;
      break;

      // Classe de ???
    case 4:

      jogador.stamina = (rand() % 40) + 25;
      jogador.forca = (rand() % 20) + 6;
      jogador.destreza = (rand() % 25) + 5;
      nivel_vigor();
      nivel_forca();
      nivel_destreza();
      escolha = 0;
      break;

    // Escolha errada
    default:
      printf("Escolha errada IMBECIL!");
    }
  }
  jogador.vida = jogador.stamina * 2;
  jogador.defesa = jogador.destreza + 2;
  jogador.dano = jogador.forca + 10;

  vidamax = jogador.vida;

  // historia1

  historiaPT1();

  Fvilarejo();

  printf("Para onde você quer seguir?\n\n");

  printf("1.Taverna\n2.loja\n3.Igreja\n");

  escolha = 1;

  // Lobby geral para todas as outras areas do jogo
  while (escolha != -1) {
    if (jogador.vida <= 0) {
      return 0;
    }

    scanf("%d", &escolha);
    switch (escolha) {

    // Area da taverna
    case 1:
      taverna(escolha);
      escolha = 0;

    // Area do casebre
    case 2:
      system("clear");
      loja();
      sleep(2);
      Fvilarejo();
      printf("1.Taverna\n2.loja\n3.Igreja\n");
      escolha = 0;

    // Aréa da mansão
    case 3:
      for (int i = 0; i < 4; i++) {

        if (inventario_jogador.valor_itens[i] == 2) {

          igreja(escolha);
        }
      }

      escolha = 0;

    // Area da igreja
    case 4:

      printf("Salvando seu progresso...\n");
      salvar = fopen("Save_1.txt", "w");
      for (int i = 0; i < 4; i++) {
        fprintf(salvar, "%d ", inventario_jogador.valor_itens[i]);
      }

      fclose(salvar);
      escolha = 0;

    default:
      printf("");
      escolha = 0;
    }
  }

  return 0;
}

// FIM_DO_MAIN_CODE

// coletar item poção
void pocao() {
  char pocao_item[] = "Poçao";
  int r = 0;
  for (int i = 0; i < 4; i++) {

    if (inventario_jogador.valor_itens[i] == 1) {
      for (int j = 0; j < 5; j++) {
        inventario_jogador.slots[r][j] = pocao_item[j];
      }
    }
  }
}

// Esvaziar inventario
void vazio() {
  char nada[] = "Nada";
  int r = 0;

  if (erro_fix == false) {
    for (int f = 0; f < 4; f++) {
      r = 0;
      while (r < 4) {
        inventario_jogador.slots[f][r] = nada[r];
        inventario_jogador.valor_itens[r] = 0;
        r++;
      }
    }
    erro_fix = true;
    return;
  }

  for (int i = 0; i < 4; i++) {
    if (inventario_jogador.valor_itens[i] == 0) {
      inventario_jogador.slots[r][i] = nada[r];
    }
  }
}

// Status do personagem_Vigor
void nivel_vigor(int vigor) {
  getchar();
  if (vigor < 20) {
    printf("\n\nA tuberculose o alcançou");
  } else {
    printf("\n\nSeu coração ainda bate forte");
  }
}

// Status do personagem_forca
void nivel_forca(int forca) {
  if (forca < 7) {
    printf("\nSeus ossos vão esfarelar");
  } else {
    printf("\nEsta destinado a ter o corpo de tirano");
  }
}

// Status do personagem_destreza
void nivel_destreza(int destreza) {
  if (destreza < 7) {
    printf("\nSe arrastar não vai te salvar da morte\n\n");
  } else {
    printf("\nAgil como um bandido\n\n");
  }
}

// Regiões_praça_taverna
int taverna(int escolha) {
  historiaPT2();
  // historia2

  taverna_combate(escolha);

  if (jogador.vida <= 0) {
    printf("Morreu\n\n");
    return 0;
  }

  // historia3

  scanf("%d", &escolha);
  switch (escolha) {

  case 1:

    // historia4

    return 1;

    break;
  case 2:

    return 1;

    break;
  default:
    printf("ERRADO");
    return 1;
  }
}

// Regiões_praça_casebre
void casebre(int escolha) {}

// Regiões_praça_mansão
void mansao(int escolha) {}

// regiões_praça_igreja
int igreja(int escolha) {
  system("clear");

  // escolha entre entrar na igreja ou nao
  int igescolha = 0;

  Figreja();
  printf("\n\n\n\n");
  historiaPT5();
  printf("voce deseja entrar na igreja?\n 1 - sim \n 2 - nao\n");
  getchar();
  scanf("%d", &igescolha);
  switch (igescolha) {
  case 1:
    triangulo(escolha);
    system("clear");
    INTigreja();
    printf("\n\n");
    historiaPT6();
    sleep(5);
    system("clear");
    historiaPT7();
    sleep(8);
    historiaPT8();
    sleep(10);
    system("clear");
    Fcemi();

    Bcemiterio(escolha);

  case 2:
    break;
  default:
    printf("\n");
  }
}

// Encontros e inimigos

void encontro(int escolha) {
  escolha = (rand() % 100);
  if (escolha < 35) {
  } else if (escolha > 35 && escolha < 75) {
  } else if (escolha > 75 && escolha < 90) {
  } else {
  }
}

// Função para o combate_Taverna
void taverna_combate(int escolha) {

  // NPC_DRUNK_ENEMY
  ficha_inimigo_minion bebado;
  bebado.vida = 25;
  bebado.dano = 8;
  bebado.defesa = 17;

  historiaPT2();
  sleep(15);

  while (bebado.vida > 10) {
    system("clear");
    // desing velho
    Fvelho();
    // Combate e opções
    printf("1 - BATER     2 - DEFESA     3 - ABRIR O INVENTARIO\n");
    printf("\nvida bebado: %d\n", bebado.vida);
    printf("\nvida: %d\n", jogador.vida);
    if (jogador.vida <= 0) {
      return;
    }
    scanf("%d", &escolha_bebado);
    switch (escolha_bebado) {

      // Escolha_ataque_combate
    case 1:

      escolha_bebado = (rand() % 25 + 1);
      if (escolha_bebado >= bebado.defesa) {
        bebado.vida = bebado.vida - jogador.dano;
        printf("Você deu %d", jogador.dano);
      }

      escolha_bebado = (rand() % 25 + 1);
      if (escolha_bebado >= jogador.defesa) {
        jogador.vida = jogador.vida - bebado.dano;
        printf("Você recebeu %d\n\n", bebado.dano);
        escolha_bebado = 0;
        srand(time(0));
      }
      break;

      // Escolha_defender
    case 2:

      jogador.defesa += 5;
      escolha_bebado = (rand() % 25 + 1);
      if (escolha_bebado >= jogador.defesa) {
        jogador.vida -= bebado.dano;
        printf("Você recebeu %d\n\n", bebado.dano);
      } else {
        printf("Você defendeu!");
      }
      jogador.defesa -= 5;
      break;

    // ABRIR_INVENTARIO_JOGADOR
    case 3:

      getchar();
      imprimir_inventario();
      int definição = 0;
      scanf("%d", &definição);
      itens_consumiveis(definição);
      getchar();
      break;
    default:
      printf("");

      break;
    }
  }

  historiaPT3();
  historiaPT4();
  sleep(15);
  system("clear");

  inventario_jogador.valor_itens[3] = 2;
  inventario_jogador.capital += 2;
  Fvilarejo();
  printf("1.Taverna\n2.loja\n3.Igreja\n");
}

void itens_consumiveis(int i) {
  int b = i;

  switch (inventario_jogador.valor_itens[i - 1]) {

  case 1:
    printf("Você curou 25 de vida");
    jogador.vida += 25;
    if (jogador.vida > vidamax) {

      jogador.vida = vidamax;
    }
    inventario_jogador.valor_itens[b] = 0;
    vazio();
    return;
  case 0:
    printf("Vazio como sua alma");
    return;

  default:
    printf("Isso é possivel?");
  }
}

void imprimir_inventario() {
  int r = 0;
  for (int i = 0; i < 4; i++) {
    printf("\n");
    printf("%s", inventario_jogador.slots[i]);
  }
}

int Bcemiterio(int escolha) {

  ficha_inimigo_minion boss;
  boss.vida = 75;
  boss.defesa = 20;
  boss.dano = 12;

  for (int k = 0; k < 4; k++) {
    if (inventario_jogador.valor_itens[k] == 3) {
      jogador.dano += 7;
      break;
    }
  }

  for (int k = 0; k < 4; k++) {
    if (inventario_jogador.valor_itens[k] == 4) {
      jogador.defesa += 4;
      break;
    }
  }

  while (boss.vida > 0) {

    system("clear");
    Fboss();

    printf("\nvida "
           "b̆҉̢̡̢̩̦̼̤̻͕͠͞aͬ́҉̵̡̳̭̖̟̀͜ͅpͪ̔͏͏̸̡̢̧͎̲̳͖̤hͥ̋ͥ͏̶̢̛̩̱̳̦͘͞o̶̵̡̨̭̝̜ͪͯͭ͑́͞m̶̧̢̈́̆̃ͦ͑͜͏͇̦͢e̵ͧ̊̽ͫ̓̀́͏̸̛ͅt̶̢ͤ̔̀ͦ̌̚͡͡"
           "҉"
           "͟"
           "̦"
           ":"
           " "
           "%d\n",
           boss.vida);
    printf("\nvida: %d\n", jogador.vida);

    printf("1 - BATER     2 - DEFESA     3 - ABRIR O INVENTARIO\n");

    if (jogador.vida <= 0) {
      return 0;
    }
    scanf("%d", &escolha_bebado);
    switch (escolha_bebado) {

      // Escolha_ataque_combate
    case 1:

      escolha_bebado = (rand() % 25 + 1);
      if (escolha_bebado >= boss.defesa) {
        boss.vida = boss.vida - jogador.dano;
        printf("Você deu %d", jogador.dano);
      }

      escolha_bebado = (rand() % 25 + 1);
      if (escolha_bebado >= jogador.defesa) {
        jogador.vida = jogador.vida - boss.dano;
        printf("Você recebeu %d\n\n", boss.dano);
        escolha_bebado = 0;
        srand(time(0));
      }
      break;

      // Escolha_defender
    case 2:

      jogador.defesa += 5;
      escolha_bebado = (rand() % 25 + 1);
      if (escolha_bebado >= jogador.defesa) {
        jogador.vida -= boss.dano;
        printf("Você recebeu %d\n\n", boss.dano);
      } else {
        printf("Você defendeu!");
      }
      jogador.defesa -= 5;
      break;

    // ABRIR_INVENTARIO_JOGADOR
    case 3:

      getchar();
      imprimir_inventario();
      int definição = 0;
      scanf("%d", &definição);
      itens_consumiveis(definição);
      getchar();
      break;
    default:
      printf("");

      break;
    }
  }

  system("clear");
  historiaPT9();
  sleep(3);
  historiaPTfinal();
}

int triangulo(int escolha) {

  ficha_inimigo_minion triangulo;
  triangulo.vida = 17;
  triangulo.defesa = 10;
  triangulo.dano = 5;

  system("clear");
  historiaPT6();
  sleep(10);

  while (triangulo.vida >= 0) {

    system("clear");
    INTboss();

    printf("\nvida triangulo: %d\n", triangulo.vida);
    printf("\nvida: %d\n", jogador.vida);

    printf("1 - BATER     2 - DEFESA     3 - ABRIR O INVENTARIO");

    if (jogador.vida <= 0) {
      return 0;
    }
    scanf("%d", &escolha_bebado);
    switch (escolha_bebado) {

      // Escolha_ataque_combate
    case 1:

      escolha_bebado = (rand() % 25 + 1);
      if (escolha_bebado >= triangulo.defesa) {
        triangulo.vida = triangulo.vida - jogador.dano;
        printf("Você deu %d", jogador.dano);
      }

      escolha_bebado = (rand() % 25 + 1);
      if (escolha_bebado >= jogador.defesa) {
        jogador.vida = jogador.vida - triangulo.dano;
        printf("Você recebeu %d\n\n", triangulo.dano);
        escolha_bebado = 0;
        srand(time(0));
      }
      break;

      // Escolha_defender
    case 2:

      jogador.defesa += 5;
      escolha_bebado = (rand() % 25 + 1);
      if (escolha_bebado >= jogador.defesa) {
        jogador.vida -= triangulo.dano;
        printf("Você recebeu %d\n\n", triangulo.dano);
      } else {
        printf("Você defendeu!");
      }
      jogador.defesa -= 5;
      break;

    // ABRIR_INVENTARIO_JOGADOR
    case 3:

      getchar();
      imprimir_inventario();
      int definição = 0;
      scanf("%d", &definição);
      itens_consumiveis(definição);
      getchar();
      break;
    default:
      printf("");

      break;
    }
  }
  inventario_jogador.capital += 3;
}

void loja() {

  Floja();

  /*int verficacao;
  int escolha;
  scanf("%d", &escolha);
  switch (escolha) {

    // espada
  case 1:
for (int j=0;j<4;j++){
if(inventario_jogador.valor_itens[j]!=0){
verficacao++;
}else {verficacao=j;
break;  }
}
    if(verficacao==4){

    printf("Inventario CHEIO!");
      break;
    }
if (inventario_jogador.capital>4){
inventario_jogador.valor_itens[verficacao]=3;
  espada();
    inventario_jogador.capital-=4;
}else{
printf("Sem dinheiro");
break;

}

    // armadura
  case 2:
for (int j=0;j<4;j++){
if(inventario_jogador.valor_itens[j]!=0){
verficacao++;
}else {verficacao=j;
break;  }
}
    if(verficacao==4){

    printf("Inventario CHEIO!");
      break;
    }
if (inventario_jogador.capital>4){
inventario_jogador.valor_itens[verficacao]=4;
    inventario_jogador.capital-=4;
}else{
printf("Sem dinheiro");
break;

}



  // poção
  case 3:
for (int j=0;j<4;j++){
if(inventario_jogador.valor_itens[j]!=0){
verficacao++;
}else {verficacao=j;
break;  }
}
    if(verficacao==4){

    printf("Inventario CHEIO!");
      break;
    }
if (inventario_jogador.capital>1){
inventario_jogador.valor_itens[verficacao]=1;
pocao();
  inventario_jogador.capital-=1;
}
 break;

    case 4:

return;
    default:
    printf("");
  }}


void espada () {


  char espada_item[] = "espada";
  int r = 0;
  for (int i = 0; i < 4; i++) {

    if (inventario_jogador.valor_itens[i] == 3) {
      for (int j = 0; j < 5; j++) {
        inventario_jogador.slots[r][j] = espada_item[j];
      }
    }
  }




}

void armadura (){

  char armadura_item[] = "armadura";
  int r = 0;
  for (int i = 0; i < 4; i++) {

    if (inventario_jogador.valor_itens[i] == 3) {
      for (int j = 0; j < 5; j++) {
        inventario_jogador.slots[r][j] = armadura_item[j];
      }
    }
  }
*/
  
    
}

