#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int sorteador(){
    return rand() % 3; //número aleatório de 0 à 2 (3 und)
}

int validador (const char *texto, const char* mensagemErro, int min, int max){
    int valor;
    while (1){
        printf("%s", texto);
        if (scanf("%d", &valor) == 1 && valor >= min && valor <= max){
            return valor;
        } else {
            printf("%s", mensagemErro);
            while (getchar() != '\n');
        }
    }
}

//função que observa as outras duas portas e sorteia até retornar um valor diferente delas.
int escolhePortaDiferente(int portaComparada, int portaComparadaNovamente){
    int porta;
    do{
         porta = sorteador();
    } while (porta == portaComparada || porta == portaComparadaNovamente);

    return porta;
}

    //função de jogo manual
int jogador () {
    int portaApresentador, portaPremio, trocaPorta;
        
    portaPremio = sorteador();

    int portaSelecionada = validador("Digite a porta que voce quer selecionar: 1, 2 ou 3?\n>> ", "Porta invalida.\n", 1, 3) - 1;

    portaApresentador = escolhePortaDiferente(portaSelecionada, portaPremio);
    printf("O apresentador abriu a porta %d e ela tinha uma cabra!\n", portaApresentador + 1);

    trocaPorta = validador("Voce deseja trocar de porta?\n1 - Sim\n2 - Nao\n>> ", "Comando invalido.\n", 1, 2);

    if (trocaPorta == 1){
        portaSelecionada = escolhePortaDiferente(portaSelecionada, portaApresentador);
    }
    if (portaPremio == portaSelecionada){
        printf("Voce venceu! Parabens pelo novo carro!\n");
        return 1;
    } else {
        printf("Voce perdeu! Escolheu a porta com a cabra! O premio estava na porta: %d\n", portaPremio + 1);
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

        estrategia = validador("Selecione a estrategia do jogador:\n1 - Sempre trocar a porta\n2 - Nunca trocar a porta\n3 - Aleatorio\n4 - Jogar\n>> ", "Estrategia invalida.\n", 1, 4);

        if (estrategia == 4){
            jogador();
        } else {
            rounds = validador("Digite a quantidade de simulacoes:\n>> ", "Quantidade de simulacoes invalida.\n", 1, 1000000000); 

            for (int j = 0; j < rounds; j++){
                    wins += jogo(estrategia);
            }

            printf("Simulacoes: %d\n", rounds);
            printf("Vitorias: %d\n", wins);
            printf("Derrotas: %d\n", rounds - wins);
            printf("Taxa de vitorias: %.2lf%%\n", (wins * 100.0 / rounds));
        }
        
        g = validador ("Voce deseja:\n0 - Sair\n1 - Continuar\n>> ", "Comando invalido\n", 0, 1);

    }while (g == 1);

    return 0;
}
