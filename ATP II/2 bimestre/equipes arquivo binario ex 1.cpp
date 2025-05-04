#include <stdio.h>

// Struct para representar uma equipe
struct Equipe {
    int numeroInscricao;
    int pontosEtapas[3]; // Pontos em cada etapa
    int pontosGerais;
};

// Função para calcular os pontos de uma equipe em uma etapa
int calcularPontosEtapa(int tempoPadrao, int tempoEquipe) {
    int diferenca = tempoPadrao - tempoEquipe;

    if (diferenca < 3) {
        return 100;
    } else if (diferenca >= 3 && diferenca <= 5) {
        return 80;
    } else {
        return 80 - ((diferenca - 5) / 5);
    }
}

// Função para preencher os dados de uma equipe
void preencherEquipe(struct Equipe *equipe, int numEtapas) {
    printf("Informe o número de inscrição da equipe: ");
    scanf("%d", &equipe->numeroInscricao);

    for (int i = 0; i < numEtapas; i++) {
        int tempoPadrao, tempoEquipe;
        printf("Informe o tempo-padrão da etapa %d (em minutos): ", i + 1);
        scanf("%d", &tempoPadrao);

        printf("Informe o tempo da equipe na etapa %d (em minutos): ", i + 1);
        scanf("%d", &tempoEquipe);

        equipe->pontosEtapas[i] = calcularPontosEtapa(tempoPadrao, tempoEquipe);
    }

    equipe->pontosGerais = 0;
    for (int i = 0; i < numEtapas; i++) {
        equipe->pontosGerais += equipe->pontosEtapas[i];
    }
}

int main() {
    int numEquipes, numEtapas;

    printf("Informe o número de equipes: ");
    scanf("%d", &numEquipes);

    printf("Informe o número de etapas: ");
    scanf("%d", &numEtapas);

    struct Equipe equipes[numEquipes];

    // Preencher os dados de cada equipe
    for (int i = 0; i < numEquipes; i++) {
        printf("\nEquipe %d:\n", i + 1);
        preencherEquipe(&equipes[i], numEtapas);
    }

    // Encontre a equipe vencedora
    int equipeVencedora = 0;
    int maiorPontuacao = equipes[0].pontosGerais;

    for (int i = 1; i < numEquipes; i++) {
        if (equipes[i].pontosGerais > maiorPontuacao) {
            maiorPontuacao = equipes[i].pontosGerais;
            equipeVencedora = i;
        }
    }

    // Exiba os resultados
    printf("\nResultados:\n");
    for (int i = 0; i < numEquipes; i++) {
        printf("Equipe %d - Número de Inscrição: %d\n", i + 1, equipes[i].numeroInscricao);
        printf("Pontuação Geral: %d\n", equipes[i].pontosGerais);
    }

    printf("Equipe Vencedora - Número de Inscrição: %d\n", equipes[equipeVencedora].numeroInscricao);
    printf("Pontuação da Equipe Vencedora: %d\n", maiorPontuacao);

    return 0;
}
