#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função auxiliar para verificar se um número é primo
int ehPrimo(int n) {
    if (n <= 1) return 0;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) return 0;
    }
    return 1;
}

// Função para gerar a sequência matemática escolhida
void gerarSequencia(int tipo, int n, int seq[]) {
    if (tipo == 1) { // Progressão Aritmética (PA)
        int a1, r;
        printf("Digite o primeiro termo (a1) da PA: ");
        scanf("%d", &a1);
        printf("Digite a razao (r) da PA: ");
        scanf("%d", &r);
        for (int i = 0; i < n; i++) {
            seq[i] = a1 + (i * r);
        }
    } else if (tipo == 2) { // Progressão Geométrica (PG)
        int a1, q;
        printf("Digite o primeiro termo (a1) da PG: ");
        scanf("%d", &a1);
        printf("Digite a razao (q) da PG: ");
        scanf("%d", &q);
        int termo = a1;
        for (int i = 0; i < n; i++) {
            seq[i] = termo;
            termo *= q;
        }
    } else if (tipo == 3) { // Série de Fibonacci
        if (n > 0) seq[0] = 1;
        if (n > 1) seq[1] = 1;
        for (int i = 2; i < n; i++) {
            seq[i] = seq[i - 1] + seq[i - 2];
        }
    } else if (tipo == 4) { // Números Primos
        int contador = 0;
        int candidato = 2;
        while (contador < n) {
            if (ehPrimo(candidato)) {
                seq[contador] = candidato;
                contador++;
            }
            candidato++;
        }
    }
}

int main() {
    char palavra[16];
    int shift;
    int tipoSeq;
    int seq[15] = {0};

    printf("========================================\n");
    printf("   PROJETO: CRIPTOGRAFIA & MATEMATICA\n");
    printf("   Algoritmo e Pensamento Computacional\n");
    printf("========================================\n\n");

    // 1. Entrada da palavra secreta
    printf("Digite a palavra secreta (ate 15 letras, sem acentos): ");
    scanf("%15s", palavra);

    int tamanho = strlen(palavra);

    // Validação básica de caracteres
    for (int i = 0; i < tamanho; i++) {
        if (!isalpha(palavra[i])) {
            printf("[Erro] A palavra deve conter apenas letras alfabeticas.\n");
            return 1;
        }
    }

    // 2. Entrada do valor de SHIFT
    printf("Digite o valor de SHIFT fixo (ex: 3): ");
    scanf("%d", &shift);

    // 3. Escolha da sequência numérica
    printf("\nEscolha a sequencia matematica:\n");
    printf("1 - Progressao Aritmetica (PA)\n");
    printf("2 - Progressao Geometrica (PG)\n");
    printf("3 - Serie de Fibonacci\n");
    printf("4 - Numeros Primos\n");
    printf("Opcao escolhida: ");
    scanf("%d", &tipoSeq);

    if (tipoSeq < 1 || tipoSeq > 4) {
        printf("[Erro] Opcao de sequencia invalida.\n");
        return 1;
    }

    // Gerar a sequência correspondente
    gerarSequencia(tipoSeq, tamanho, seq);

    // Exibição dos cálculos internos
    printf("\n--- PROCESSAMENTO INTERNO ---\n");
    printf("Sequencia numérica gerada: ");
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", seq[i]);
    }
    printf("\n");

    // 4. Aplicação das Duas Camadas de Criptografia
    char criptografada[16];
    for (int i = 0; i < tamanho; i++) {
        char c = tolower(palavra[i]);
        if (c >= 'a' && c <= 'z') {
            int deslocamentoTotal = shift + seq[i];
            // Cifra circular no alfabeto (26 letras)
            criptografada[i] = 'a' + (c - 'a' + deslocamentoTotal) % 26;
        } else {
            criptografada[i] = c;
        }
    }
    criptografada[tamanho] = '\0';

    // 5. Exibição dos Resultados
    printf("\n[Resultado] Palavra original: %s\n", palavra);
    printf("[Resultado] Palavra criptografada: %s\n", criptografada);

    // 6. Gravação em Arquivo de Log
    FILE *arquivo = fopen("resultado_criptografia.txt", "w");
    if (arquivo != NULL) {
        fprintf(arquivo, "Palavra codificada: %s | SHIFT: %d | Tipo Sequencia: %d | Letras: %d\n", 
                criptografada, shift, tipoSeq, tamanho);
        fclose(arquivo);
        printf("\n[Arquivo] Log gravado com sucesso em 'resultado_criptografia.txt'.\n");
    } else {
        printf("\n[Erro] Nao foi possivel criar o arquivo de saida.\n");
    }

    return 0;
}
