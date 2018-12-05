#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

struct casa {
    float valor;
    int index;
    int comprada;
    float multa;
    char *descricao;
    
    struct casa *next;
};

typedef struct jogador {
    float saldo;
    int casaAtual;
}jogador;

struct casa *head = NULL;
struct casa *current = NULL;

bool isEmpty() {
    return head == NULL;
}

int length() {
    int length = 0;
    
    //if list is empty
    if(head == NULL) {
        return 0;
    }
    
    current = head->next;
    
    while(current != head) {
        length++;
        current = current->next;
    }
    
    return length;
}

//insert link at the first location
void insertFirst(int index, float valor,float multa,int comprada, char *descricao) {
    
    //create a link
    struct casa *link = (struct casa*) malloc(sizeof(struct casa));
    link->index = index;
    link->valor = valor;
    link->multa = multa;
    link->comprada = comprada;
    link->descricao = malloc(sizeof(char)*50);
    link->descricao = descricao;
    
    
    
    if (isEmpty()) {
        head = link;
        head->next = head;
    } else {
        
        
        //point it to old first casa
        link->next = head;
        
        //point first to new first casa
        head = link;
    }
}

//delete first item
struct casa * deleteFirst() {
    
    //save reference to first link
    struct casa *tempLink = head;
    
    if(head->next == head) {
        head = NULL;
        return tempLink;
    }
    
    //mark next to first link as first
    head = head->next;
    
    //return the deleted link
    return tempLink;
}

//display the list
void printList() {
    
    struct casa *ptr = head;
    printf("\n[ ");
    
    //start from the beginning
    if(head != NULL) {
        
        while(ptr->next != ptr) {
            printf("(%d,%f) ",ptr->index,ptr->valor);
            ptr = ptr->next;
        }
    }
    
    printf(" ]");
}

int countOwned(int owned) {
    
    struct casa *ptr = head;
    
    bool atleastOneOwned = false;
    
    if(head != NULL) {
        while(ptr->next != ptr) {
            if(ptr->comprada != 0 && ptr->comprada != 3)
            {
                atleastOneOwned = true;
            }
            if(ptr->comprada == 1)
            {
                owned++;
            }
            ptr = ptr->next;
        }
    }
    
    if(atleastOneOwned == true)
    {
        return owned;
    }
    else
    {
        return 1000;
    }
}

void avancaCasas(jogador *jogadores,int dado,int indexJogador) {
    
    float saldoJogador1 = jogadores[0].saldo, saldoJogador2 = jogadores[1].saldo, ganhoJogador1 = 0, ganhoJogador2 = 0;
    struct casa *ptr = head;
    struct casa *tabuleiro = head;
    int aux = jogadores[indexJogador-1].casaAtual;
    int especial = 0;
    int buyOption = 99;
    // printf("%d ",ptr->index
    
    if(head != NULL) {
        
        while(tabuleiro->next != tabuleiro)
        {
            printf("%s (v:%.0f m:%.0f d:%d) | ",tabuleiro->descricao,tabuleiro->valor,tabuleiro->multa,tabuleiro->comprada);
            tabuleiro = tabuleiro->next;
        }
        printf("%s (v:%.0f m:%.0f d:%d)",tabuleiro->descricao,tabuleiro->valor,tabuleiro->multa,tabuleiro->comprada);
        printf("\n\n");
        
        while(aux >= 1)
        {
            
            if(ptr->index == 12)
            {
                ptr = head;
                printf("%d ",ptr->index);
                aux--;
            }
            else
            {
                ptr = ptr->next;
                printf("%d ",ptr->index);
                aux--;
            }
        }
        
        while(dado > 1) {
            
            if(ptr->index == 12)
            {
                ptr = head;
                printf("%d ",ptr->index);
                dado--;
            }
            else
            {
                ptr = ptr->next;
                printf("%dA ",ptr->index);
                dado--;
            }
            
        }
        
        printf("Voce parou na casa %d - %s\n\n",ptr->index, ptr->descricao);
        jogadores[indexJogador-1].casaAtual = ptr->index;
        
        if(ptr->comprada == 3)
        {
            printf("\t\t\t   FIM DO ROUND\n");
            printf("Jogador 1 com saldo %.0f \t\t  Jogador 2 com saldo %.0f\n",jogadores[0].saldo,jogadores[1].saldo);
            return;
        }
        if(ptr->comprada == 0)
        {
            printf("Voce deseja comprar a casa %d - %s pelo valor de %.0f?  (1 == SIM || 0 == NAO): ",ptr->index,ptr->descricao,ptr->valor);
            scanf("%d",&buyOption);
            if(buyOption == 1){
                printf("Voce comprou a casa %d - %s pelo valor de %.0f\n\n",ptr->index,ptr->descricao,ptr->valor);
                jogadores[indexJogador-1].saldo = jogadores[indexJogador-1].saldo - ptr->valor;
                ptr->comprada = indexJogador;
                if(indexJogador == 1)
                {
                    ganhoJogador1 = -ptr->valor;
                }
                if(indexJogador == 2)
                {
                    ganhoJogador2 = -ptr->valor;
                }
            }
        }
        else if(ptr->comprada != 0 && ptr->comprada == indexJogador)
        {
            printf("Esse imovel ja te pertence\n\n");
        }
        else if(ptr->comprada != 0 && ptr->comprada != indexJogador)
        {
            printf("Ela pertence ao jogador %d\n\n",ptr->comprada);
            if(jogadores[indexJogador-1].saldo <= ptr->valor + ptr->multa)
            {
                printf("Voce pagou ao oponente %.0f\n\n",ptr->multa);
                jogadores[indexJogador-1].saldo = jogadores[indexJogador-1].saldo - ptr->multa;
                if(indexJogador == 1)
                {
                    jogadores[indexJogador].saldo = jogadores[indexJogador].saldo + ptr->multa;
                    saldoJogador1 = -ptr->multa;
                    saldoJogador2 = ptr->multa;
                }
                if(indexJogador == 2)
                {
                    jogadores[indexJogador-2].saldo = jogadores[indexJogador-2].saldo + ptr->multa;
                    saldoJogador1 = ptr->multa;
                    saldoJogador2 = -ptr->multa;
                }
            }
            else
            {
                printf("Voce deseja comprar a casa %d - %s pelo valor de %.0f?  (1 == SIM || 0 == NAO): ",ptr->index,ptr->descricao,ptr->valor);
                scanf("%d",&buyOption);
                if(buyOption == 1){
                    printf("Voce pagou ao oponente %.0f e adquiriu o imovel por %.0f\n\n",ptr->multa,ptr->valor);
                    jogadores[indexJogador-1].saldo = jogadores[indexJogador-1].saldo - ptr->multa - ptr->valor;
                    ptr->comprada = indexJogador;
                    if(indexJogador == 1)
                    {
                        jogadores[indexJogador].saldo = jogadores[indexJogador].saldo + ptr->multa;
                        saldoJogador1 = -ptr->multa;
                        saldoJogador2 = ptr->multa;
                    }
                    if(indexJogador == 2)
                    {
                        jogadores[indexJogador-2].saldo = jogadores[indexJogador-2].saldo + ptr->multa;
                        saldoJogador1 = ptr->multa;
                        saldoJogador2 = -ptr->multa;
                    }
                }
            }
        }
        
        printf("\t\t\t   FIM DO ROUND\n");
        printf("\n---------------------------------------------------------------------------------------------\n\n");
        buyOption = 99;
    }
    
}

void criaTabuleiro(){
    insertFirst(12,700,350,0,"Kabum");
    insertFirst(11,1000,600,0,"Garten");
    insertFirst(10,300,165,0,"Maos Peruanas");
    insertFirst(9,175,75,0,"Cold Beer");
    insertFirst(8,2500,1500,0,"SBT");
    insertFirst(7,1500,700,0,"Trump Tower");
    insertFirst(6,400,200,0,"Albino");
    insertFirst(5,350,180,0,"Horodenski");
    insertFirst(4,150,50,0,"Gigabyte");
    insertFirst(3,200,75,0,"Padaria");
    insertFirst(2,100,25,0,"Salao de festas");
    insertFirst(1,0,0,3,"Comeco");
}

void criaCartas(float *cartas){
    cartas[0] = 400;
    cartas[1] = 600;
    cartas[2] = -300;
    cartas[3] = -700;
    cartas[4] = 1500;
    cartas[5] = -1500;
}

// ---------------------------- TEST ---------------------------------

//teste dado
void testeDado(){
    
    int i;
    int vetor[100];
    srand((unsigned int)time(NULL));
    for (i=0; i<100; i++) {
        vetor[i] = rand() % 6 + 1;
    }
    int valor,cont_1=0,cont_2=0,cont_3=0,cont_4=0,cont_5=0,cont_6=0;
    for (i=0; i<100; i++) {
        
        valor = vetor[i];
        
        if (valor == 1) {
            cont_1 ++;
        }else if (valor == 2){
            cont_2++;
        }else if (valor == 3){
            cont_3++;
        }else if (valor == 4){
            cont_4++;
        }else if (valor == 5){
            cont_5++;
        }else if (valor == 6){
            cont_6++;
        }
    }
    printf("\nTeste dado: ");
    printf("\nNumero 1 = %d%%",cont_1);
    printf("\nNumero 2 = %d%%",cont_2);
    printf("\nNumero 3 = %d%%",cont_3);
    printf("\nNumero 4 = %d%%",cont_4);
    printf("\nNumero 5 = %d%%",cont_5);
    printf("\nNumero 6 = %d%%",cont_6);
    printf("\nDado nao viciado");
    
    
    
}


//verifica o numero de casas do tabuleiro
void testTabuleiro (){
    
    criaTabuleiro();
    int cont = 1;
    struct casa *ptr = head;
    
    while(ptr->next != ptr) {
        cont++;
        ptr = ptr->next;
    }
    if (cont == 12) {
        printf("\nTeste do tabuleiro verificado. O tabuleiro possui %d casas.", cont);
    }else{
        printf("\nTeste do tabuleiro falhou (%d casas)", cont);
    }
}


//verifica se o somatório das cartas é zero
void testCriaCartas(float* cartas){
    
    int i, sum=0;
    
    for (i=0; i<6; i++) {
        sum += cartas[i];
    }
    
    if (sum == 0) {
        printf("Teste cartas verificado. O somatório é: %d",sum);
    }else{
        printf("Teste de cartas falhou.");
    }
    
}
// ------------------------------ TEST -------------------------------
int main() {
    
    int escolha;
    printf("\n--------------------------------------");
    printf("\nPara entrar no jogo digite 1         |\n--------------------------------------\nPara realizacao de testes digite -1  |\n");
    printf("--------------------------------------\n");
    scanf("%d",&escolha);
    
    if (escolha == -1) {
        float *cartasTest = malloc(sizeof(int)*6);
        criaCartas(cartasTest);
        testCriaCartas(cartasTest);
        testTabuleiro();
        testeDado();
        
        
    }else{
        criaTabuleiro();
        
        float *cartas = malloc(sizeof(int)*6);
        
        criaCartas(cartas);
        
        jogador *jogadores = malloc(sizeof(jogador)*2);
        
        jogadores[0].saldo = 10000;
        jogadores[1].saldo = 10000;
        jogadores[0].casaAtual = 1;
        jogadores[1].casaAtual = 1;
        
        int turn = 1;
        int dado,carta;
        int option = 0;
        int owned = 1000;
        srand((unsigned int)time(NULL));
        printf("\n");
        
        while(option != 1000)
        {
            if( turn == 1)
            {
                printf("Jogador 1 com saldo %.0f \t\t  Jogador 2 com saldo %.0f\n",jogadores[0].saldo,jogadores[1].saldo);
                printf("\t\t\tTURNO DO JOGADOR %d\n",turn);
                dado = rand() % 6 + 1;
                carta = rand() % 6 + 1;
                printf("\n\t\tCARTA: Carta n%d seu saldo alterou em %.0f\n\n",carta,cartas[carta-1]);
                jogadores[0].saldo = jogadores[0].saldo + cartas[carta-1];
                printf("\n\t\t\tDADO: Avance %d casas\n\n",dado);
                avancaCasas(jogadores,dado,turn);
                turn = 2;
            }
            else if ( turn == 2 )
            {
                printf("Jogador 1 com saldo %.0f \t\t  Jogador 2 com saldo %.0f\n",jogadores[0].saldo,jogadores[1].saldo);
                printf("\t\t\tTURNO DO JOGADOR %d\n",turn);
                dado = rand() % 6 + 1;
                carta = rand() % 6 + 1;
                printf("\n\t\tCARTA: Carta n%d seu saldo alterou em %.0f\n\n",carta,cartas[carta-1]);
                jogadores[1].saldo = jogadores[1].saldo + cartas[carta-1];
                printf("\n\t\t\tDADO: Avance %d casas\n\n",dado);
                avancaCasas(jogadores,dado,turn);
                turn = 1;
            }
            
            countOwned(owned);
            
            if(jogadores[0].saldo <= 0 || owned == 0)
            {
                printf("\t\t\tJogador 2 venceu!\n");
                break;
            }
            
            if(jogadores[1].saldo <= 0 || owned == 8)
            {
                printf("\t\t\tJogador 1 venceu!\n");
                break;
            }
            owned = 1000;
            
            printf("\n");
            printf("Digite um numero para avancar o turno  OU  1000 para fechar o jogo\n");
            scanf("%d",&option);
            printf("\n");
        }
    }
    
    printf("\n");
    return 0;
}
