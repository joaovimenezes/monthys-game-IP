#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sorteador(){
    return rand() % 3; //número aleatório de 0 à 2 (3 und)
}

//função que observa as outras duas portas e sorteia até retornar um valor diferente delas.
int selecaoComparacao(int portaComparada, int portaComparadaNovamente){
    int porta, i;
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

int jogador () {
    int portaSelecionada, portaApresentador, portaPremio,trocaPorta;
    
    portaPremio = sorteador();
    
    printf("Digite a porta que voce quer selecionar: 1, 2 ou 3?\n>>");
    scanf("%d", &portaSelecionada);
    portaSelecionada -= 1;
    
    portaApresentador = selecaoComparacao(portaSelecionada, portaPremio);
    printf("O apresentador abriu a porta %d e ela tinha uma cabra!\n", portaApresentador + 1);
    printf("Voce deseja trocar de porta?\n1 - Sim\n2 - Nao\n>>");
    scanf("%d", &trocaPorta);
    
    if (trocaPorta == 1){
        int backupSelecaoAntiga = portaSelecionada;
        portaSelecionada = selecaoComparacao(backupSelecaoAntiga, portaApresentador);
    }
    
    if (portaPremio == portaSelecionada){
        printf("Voce venceu! Parabens pelo novo carro!\n");
        return 1;
    } else {
        printf("Voce perdeu! Escolheu a porta com a cabra!\n");
        return 0;
    }
}

int jogo (int estrategia) {
    int portaSelecionada, portaApresentador, portaPremio;
    
    portaPremio = sorteador();
    portaSelecionada = sorteador();
    
    //seleciona porta vazia para o apresentador
    portaApresentador = selecaoComparacao(portaSelecionada, portaPremio);
    
    switch (estrategia){
        case 1: { //caso de trocar de porta
            int backupSelecaoAntiga = portaSelecionada;
            portaSelecionada = selecaoComparacao(backupSelecaoAntiga, portaApresentador);
            } break;
        case 2: //caso de manter a porta selecionada
            break;
        case 3: //caso aleatorio
            portaSelecionada = selecaoComparacao(portaApresentador, portaApresentador);
            break;
    }
    
    if (portaPremio == portaSelecionada){
        return 1;
    } else {
        return 0;
    }
}

int main() {
    int rounds, estrategia;
    int i = 0;
    int wins = 0;
    
    srand(time(NULL));
    
    do{
        printf("Selecione a estrategia do jogador:\n1 - Sempre trocar a porta\n2 - Nunca trocar a porta\n3 - Aleatorio\n4 - Jogar\n>>");
        scanf("%d", &estrategia);
        
        if (estrategia == 4){
            jogador();
        } else{
        printf("Digite a quantidade de simulacoes:\n>> ");
        scanf("%d", &rounds);
        
        for (int j = 0; j < rounds; j++){
            wins = wins + jogo(estrategia);
        }
        
        printf("Simulacoes: %d\nVitorias: %d\nDerrotas: %d\nTaxa de vitorias: %.2lf%%\n", rounds, wins, (rounds - wins), ((wins * 1.0 / rounds)*100));
        }
        printf("Voce deseja:\n0 - Sair\n1 - Continuar\n>>");
        scanf("%d", &i);
    }while (i == 1);
    return 0;
}