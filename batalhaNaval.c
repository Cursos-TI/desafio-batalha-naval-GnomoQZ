#include <stdio.h>  // Biblioteca padrão para entrada e saída de dados
#include <stdlib.h> // Biblioteca para manipulação de memória, conversões e geração de números aleatórios
#include <time.h>

// Definições de constantes para o tabuleiro e os estados das células
#define LINHA 10  // Número de linhas do tabuleiro
#define COLUNA 10 // Número de colunas do tabuleiro
#define AGUA 0    // Representa uma célula vazia no tabuleiro
#define NAVIO 3   // Representa um navio no tabuleiro
#define ACERTO 1  // Representa um tiro que acertou um navio
#define ERRO -1   // Representa um tiro que errou o alvo

// Declaração da matriz do tabuleiro
int tabuleiro[LINHA][COLUNA];

// Array de letras para rotular as linhas do tabuleiro
char letras[LINHA] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'};

// Função para inicializar o tabuleiro preenchendo todas as células com água (0)
void inicializarTabuleiro() {
    for (int i = 0; i < LINHA; i++) {
        for (int j = 0; j < COLUNA; j++) {
            tabuleiro[i][j] = AGUA;
        }
    }
}

// Função para exibir o tabuleiro na tela
void exibirTabuleiro() {
    printf("   "); // Espaço para alinhar os números das colunas
    for (int i = 1; i <= COLUNA; i++) {
        printf("%d ", i); // Exibe números das colunas
    }
    printf("\n");

    for (int i = 0; i < LINHA; i++) {
        printf("%c  ", letras[i]); // Exibe o rótulo da linha
        for (int j = 0; j < COLUNA; j++) {
            if (tabuleiro[i][j] == NAVIO)
                printf("~ ");  // Mantém os navios ocultos para o jogador
            else if (tabuleiro[i][j] == ACERTO)
                printf("X "); // Representa um acerto
            else if (tabuleiro[i][j] == ERRO)
                printf("O "); // Representa um erro (tiro na água)
            else
                printf("~ "); // Representação padrão para áreas desconhecidas
        }
        printf("\n");
    }
}

// Função para posicionar navios no tabuleiro
void posicionarNavios() {
    // Posiciona um navio horizontalmente na linha 2
    for (int i = 2; i < 6; i++) {
        tabuleiro[2][i] = NAVIO;
    }
    // Posiciona um navio verticalmente na coluna 7
    for (int i = 5; i < 9; i++) {
        tabuleiro[i][7] = NAVIO;
    }
    // Posiciona um navio diagonalmente da posição (0,0) até (3,3)
    for (int i = 0; i < 4; i++) {
        tabuleiro[i][i] = NAVIO;
    }
}

// Função para processar um ataque do jogador
void atacar() {
    char linha;
    int coluna;
    printf("Digite a coordenada do ataque (ex: B5): ");
    scanf(" %c%d", &linha, &coluna);
    
    // Converte a entrada para índices da matriz
int lin = linha - 'A'; // Transforma a letra da linha (A-J) em um índice numérico (0-9)
// Por exemplo, se 'A' for digitado, lin será 0; se 'B', lin será 1, e assim por diante.

coluna -= 1; // Ajusta o índice da coluna (baseado em zero)
// O usuário insere a coluna como 1-10, mas os índices da matriz começam em 0.
// Portanto, subtraímos 1 para que a coluna 1 corresponda ao índice 0, a coluna 2 ao índice 1, etc.

// Verifica se a coordenada está dentro dos limites válidos do tabuleiro
if (lin < 0 || lin >= LINHA || coluna < 0 || coluna >= COLUNA) {
    // Se a linha for menor que 0 ou maior ou igual ao número de linhas,
    // ou se a coluna for menor que 0 ou maior ou igual ao número de colunas,
    // a coordenada é considerada inválida.
    printf("Coordenada inválida!\n"); // Mensagem de erro informando que a coordenada é inválida
    return; // Retorna da função, não processando o ataque
}


// Processa o ataque na coordenada informada
if (tabuleiro[lin][coluna] == NAVIO) {
    // Verifica se a célula correspondente no tabuleiro contém um navio
    printf("Acertou!\n"); // Mensagem informando que o jogador acertou um navio
    tabuleiro[lin][coluna] = ACERTO; // Marca o acerto no tabuleiro, alterando o estado da célula para ACERTO
} else if (tabuleiro[lin][coluna] == AGUA) {
    // Se a célula contém água (AGUA), significa que o jogador errou o ataque
    printf("Errou!\n"); // Mensagem informando que o jogador errou
    tabuleiro[lin][coluna] = ERRO; // Marca o erro no tabuleiro, alterando o estado da célula para ERRO
} else {
    // Se a célula já foi atacada anteriormente (não é NAVIO nem AGUA)
    printf("Você já atacou essa posição!\n"); // Mensagem informando que a posição já foi atacada
}
}
// Função principal do jogo, inicializa o tabuleiro, posiciona os navios e inicia o loop de jogo.
int main() {
    srand(time(NULL)); // Inicializa a semente do gerador de números aleatórios
    inicializarTabuleiro(); // Preenche o tabuleiro com água
    posicionarNavios(); // Posiciona os navios no tabuleiro
    
    printf("\n------- BATALHA NAVAL -------\n");
    while (1) { // Loop infinito para permitir múltiplos ataques
        exibirTabuleiro(); // Exibe o tabuleiro atualizado
        atacar(); // Permite ao jogador atacar
    }
    return 0;
}
