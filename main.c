#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sorteador(){
    return rand() % 3; //número aleatório de 0 à 2 (3 und)
}

//função que observa as outras duas portas e sorteia até retornar um valor diferente delas.
int escolhePortaDiferente(int portaComparada, int portaComparadaNovamente){
    int porta, i = 0;
    do{
        porta = sorteador();
        if (porta == portaComparada || porta == portaComparadaNovamente){
            i = 1;
        } else{
            i = 0;
        }
        } while (i == 1);
    return porta;
}

//função de jogo manual
int jogador () {
    int portaSelecionada, portaApresentador, portaPremio, trocaPorta;
    
    portaPremio = sorteador();
    
    printf("Digite a porta que voce quer selecionar: 1, 2 ou 3?\n>>");
    scanf("%d", &portaSelecionada);
    portaSelecionada -= 1; //adiciona 1 unidade para tornar mais intuitivo para o usuario
    if (portaSelecionada < 0 || portaSelecionada > 2){
        printf("Porta invalida.\n");
        return 0;
    }

    portaApresentador = escolhePortaDiferente(portaSelecionada, portaPremio);
    printf("O apresentador abriu a porta %d e ela tinha uma cabra!\n", portaApresentador + 1);

    printf("Voce deseja trocar de porta?\n1 - Sim\n2 - Nao\n>>");
    scanf("%d", &trocaPorta);
    
    if (trocaPorta <= 0 || trocaPorta > 2){
        printf("Comando invalido.\n");
        return 0;
    }

    if (trocaPorta == 1){
        portaSelecionada = escolhePortaDiferente(portaSelecionada, portaApresentador);
    }
    if (portaPremio == portaSelecionada){
        printf("Voce venceu! Parabens pelo novo carro!\n");
        return 1;
    } else {
        printf("Voce perdeu! Escolheu a porta com a cabra!\n");
        return 0;
    }
}

//função do simulador
int jogo (int estrategia) {
    int portaSelecionada, portaApresentador, portaPremio;
    
    portaPremio = sorteador();
    portaSelecionada = sorteador();
    
    //seleciona porta vazia para o apresentador
    portaApresentador = escolhePortaDiferente(portaSelecionada, portaPremio);
    
    switch (estrategia){
        case 1: //caso de trocar de porta
            portaSelecionada = escolhePortaDiferente(portaSelecionada, portaApresentador);
            break;
        case 2: //caso de manter a porta selecionada
            break;
        case 3: //caso aleatorio
            portaSelecionada = escolhePortaDiferente(portaApresentador, portaApresentador);
            break;
    }
    if (portaPremio == portaSelecionada){
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int rounds, estrategia, g = 0;

    srand(time(NULL)); //semente do rand
    
    do{
        int wins = 0;

        printf("Selecione a estrategia do jogador:\n1 - Sempre trocar a porta\n2 - Nunca trocar a porta\n3 - Aleatorio\n4 - Jogar\n>>");
        scanf("%d", &estrategia);
        
        if (estrategia == 4){
            jogador();
        } else if (estrategia < 0 || estrategia > 4){
            printf("Estrategia invalida.\n");
        } else {
            printf("Digite a quantidade de simulacoes:\n>> ");
            scanf("%d", &rounds);
            
            if (rounds <= 0){
                printf("Quantidade de simulacoes invalida.\n");
            } else{
                for (int j = 0; j < rounds; j++){
                    wins = wins + jogo(estrategia);
                }
                printf("Simulacoes: %d\nVitorias: %d\nDerrotas: %d\nTaxa de vitorias: %.2lf%%\n", rounds, wins, (rounds - wins), ((wins * 1.0 / rounds)*100));
            }
        }

        printf("Voce deseja:\n0 - Sair\n1 - Continuar\n>>");
        scanf("%d", &g);
    } while (g == 1);

    return 0;
}