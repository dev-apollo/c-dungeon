#include <stdlib.h>
#include <stdio.h>
#include <time.h>

//Menu com possibilidade de jogar ou sair do jogo. Explicações/tutorial de ícones.
int menu(){
    int option;
    printf("Welcome to C-Dungeon\n\n@ - This is you\n0 - This is a coin\n5 - This is a healing potion\n^ - This is a spike\nGood luck!\n\nSelect an option:\n[1] - Start\n[0] - Exit\n");
    scanf("%d", &option);
    //O jogador só pode optar entre [1] - Iniciar ou [0] - Sair.
    while(option != 1 && option != 0){
        printf("Please, select a valid option:\n[1] - Start\n[0] - Exit\n");
        scanf("%d", &option);
    }
    return option;
}

//Exibe o mapa, armazenado no vetor bidimensional map, por completo junto das informações de vida e quantidade de moedas atuais do jogador.
void printMap(char map[7][7], int coins, int hp){
    for(int i = 0; i < 7; i++){
        printf("%c %c %c %c %c %c %c\n", map[i][0], map[i][1], map[i][2], map[i][3], map[i][4], map[i][5], map[i][6]);
    }
    printf("HP: %d/3 | Coins: %d\n",hp , coins);
}

//Player gerado em um espaço aleatório.
void spawnPlayer(char map[7][7], int* playerLine, int* playerColumn){
    *playerLine = rand()%7, *playerColumn = rand()%7;
    map[*playerLine][*playerColumn] = '@';
}

//Moedas possuem 1 chance em 4 de serem geradas no mapa, apenas em espaços vazios.
void spawnCoin(char map[7][7]){
    int coinLine, coinColumn, possibility = rand()%4;
    if(possibility == 0){
        do{
            coinLine = rand()%7, coinColumn = rand()%7; 
        }while(map[coinLine][coinColumn] != '-');
        map[coinLine][coinColumn] = '0';
    }
}

//Espinhos possuem 1 chance em 6 de serem gerados no mapa, apenas em espaços vazios.
void spawnSpike(char map[7][7]){
    int enemyLine, enemyColumn, possibility = rand()%6;
    if(possibility == 0){
        do{
            enemyLine = rand()%7, enemyColumn = rand()%7; 
        }while(map[enemyLine][enemyColumn] != '-');
        map[enemyLine][enemyColumn] = '^';
    }
}

//Poções de cura possuem 1 chance em 15 de serem geradas no mapa, apenas em espaços vazios.
void spawnPotion(char map[7][7]){
    int potionLine, potionColumn, possibility = rand()%15;
    if(possibility == 0){
        do{
            potionLine = rand()%7, potionColumn = rand()%7; 
        }while(map[potionLine][potionColumn] != '-');
        map[potionLine][potionColumn] = '5';
    }
}

//Função para movimentação do player, cada escolha pode alterar, ou não, a coordenada vertical ou horizontal do jogador.
void playerMoves(char map[7][7], int* playerLine, int* playerColumn, int* coins, int* hp){
    int move;
    printf("Select a move:\n[1] - Up | [2] - Down | [3] - Left | [4] - Right | [5] - Wait\n");
    scanf("%d", &move);
    //O jogador só pode optar entre [1] - Cima, [2] - Baixo, [3] - Esquerda, [4] - Direita ou [5] - Esperar e não pode fazer um movimento que tire ele do mapa.
    while(move != 1 && move != 2 && move != 3 && move != 4 && move != 5 || *playerLine-1 < 0 && move == 1 || *playerLine+1 > 6 && move == 2 || *playerColumn-1 < 0 && move == 3 || *playerColumn+1 > 6 && move == 4){
        printf("Please, select a valid move:\n[1] - Up | [2] - Down | [3] - Left | [4] - Right | [5] - Wait\n");
        scanf("%d", &move);
    }
    map[*playerLine][*playerColumn] = '-';
    switch(move){
        case 1:
            *playerLine -= 1;
            break;
        case 2:
            *playerLine += 1;
            break;
        case 3:
            *playerColumn -= 1;
            break;
        case 4:
            *playerColumn += 1;
            break;
    }
    //Após definir a nova coordenada, caso não seja um espaço vazio, ocorrerá uma verificação para sabe com qual objeto o jogador colidiu.
    switch (map[*playerLine][*playerColumn])
    {
        case '0':
            *coins+=1;
            break;
        case '^':
            *hp-=1;
            break;
        case '5':
            *hp = 3;
            break;
    }
    map[*playerLine][*playerColumn] = '@';
}

//O jogo HP caso o HP acabe.
int verifyHp(int hp){
    if(hp <= 0){
        return 0;
    }else{
        return 1;
    }
}

int main(){
    system("cls");
    int game = menu(), playerLine, playerColumn, coins = 0, hp = 3;
    char map[7][7] = {
        {'-', '-', '-', '-', '-', '-', '-'}, 
        {'-', '-', '-', '-', '-', '-', '-'}, 
        {'-', '-', '-', '-', '-', '-', '-'}, 
        {'-', '-', '-', '-', '-', '-', '-'}, 
        {'-', '-', '-', '-', '-', '-', '-'}, 
        {'-', '-', '-', '-', '-', '-', '-'}, 
        {'-', '-', '-', '-', '-', '-', '-'}
    };
    if(game == 1){
        //Função para iniciar o gerador aleatório baseado no tempo.
        srand(time(NULL));
        spawnPlayer(map, &playerLine, &playerColumn);
        while(game == 1){
            system("cls");
            spawnCoin(map);
            spawnSpike(map);
            spawnPotion(map);
            printMap(map, coins, hp);
            playerMoves(map, &playerLine, &playerColumn, &coins, &hp);
            game = verifyHp(hp);
        }
        //Tela de fim de jogo.
        if(game == 0){
            system("cls");
            printf("You died! But you collected %d coins.", coins);
        }
    }else{
        printf("Exiting...");
    }
    return 0;
}