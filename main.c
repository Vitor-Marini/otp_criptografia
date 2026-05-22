#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 10000

char texto[MAX];
unsigned char chave[MAX];
int tamanho = 0;

void ler_arquivo() {
    char nome[256];
    printf("Nome do arquivo: ");
    scanf("%s", nome);

    FILE *f = fopen(nome, "r");
    if (!f) { printf("Erro ao abrir arquivo.\n"); return; }

    tamanho = fread(texto, 1, MAX - 1, f);
    texto[tamanho] = '\0';
    fclose(f);
    printf("Arquivo lido: %d bytes.\n", tamanho);
}

void gerar_chave() {
    srand(time(NULL));
    for (int i = 0; i < tamanho; i++)
        chave[i] = rand() % 256;

    FILE *f = fopen("chave.key", "wb");
    fwrite(chave, 1, tamanho, f);
    fclose(f);
    printf("Chave gerada e salva em 'chave.key'.\n");
}

void carregar_chave() {
    FILE *f = fopen("chave.key", "rb");
    if (!f) { printf("Chave nao encontrada.\n"); return; }
    fread(chave, 1, tamanho, f);
    fclose(f);
}

void criptografar() {
    if (tamanho == 0) { printf("Leia um arquivo primeiro.\n"); return; }
    gerar_chave();
    for (int i = 0; i < tamanho; i++)
        texto[i] ^= chave[i];
    printf("Texto criptografado.\n");
}

void descriptografar() {
    if (tamanho == 0) { printf("Leia um arquivo primeiro.\n"); return; }
    carregar_chave();
    for (int i = 0; i < tamanho; i++)
        texto[i] ^= chave[i];
    printf("Texto descriptografado.\n");
}

void salvar_arquivo() {
    char nome[256];
    printf("Nome do arquivo de saida: ");
    scanf("%s", nome);

    FILE *f = fopen(nome, "wb");
    if (!f) { printf("Erro ao salvar.\n"); return; }
    fwrite(texto, 1, tamanho, f);
    fclose(f);
    printf("Arquivo salvo: %s\n", nome);
}

int main() {
    int op;
    do {
        printf("\n===== CHAVE UNICA (OTP) =====\n");
        printf("1 - Ler arquivo texto\n");
        printf("2 - Criptografar\n");
        printf("3 - Descriptografar\n");
        printf("4 - Salvar arquivo\n");
        printf("5 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);

        switch (op) {
            case 1: ler_arquivo();     break;
            case 2: criptografar();    break;
            case 3: descriptografar(); break;
            case 4: salvar_arquivo();  break;
            case 5: printf("Saindo...\n"); break;
            default: printf("Opcao invalida.\n");
        }
    } while (op != 5);

    return 0;
}