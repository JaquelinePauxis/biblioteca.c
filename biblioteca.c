#include <stdio.h>
#include <string.h>

// Definição das structs
typedef struct {
    char titulo[100];
    char autor[100];
    char isbn[20];
    int ano;
    int disponivel; // 1 = disponível, 0 = emprestado
} Livro;

typedef struct {
    char nome[100];
    int id;
    char contato[50];
    int emprestimosAtuais; // Número de livros emprestados
} Usuario;

typedef struct {
    int idUsuario;
    char isbnLivro[20];
    char dataEmprestimo[11];
    char dataDevolucaoPrevista[11];
} Emprestimo;

// Arrays para armazenamento de dados
Livro livros[100];
Usuario usuarios[100];
Emprestimo emprestimos[100];
int qtdLivros = 0, qtdUsuarios = 0, qtdEmprestimos = 0;

// Funções de Gerenciamento de Livros
void cadastrarLivro() {
    Livro livro;
    printf("Digite o título: ");
    scanf(" %[^\n]", livro.titulo);
    printf("Digite o autor: ");
    scanf(" %[^\n]", livro.autor);
    printf("Digite o ISBN: ");
    scanf(" %[^\n]", livro.isbn);
    printf("Digite o ano de publicação: ");
    scanf("%d", &livro.ano);
    livro.disponivel = 1;

    livros[qtdLivros++] = livro;
    printf("Livro cadastrado com sucesso!\n");
}

void consultarLivro() {
    char isbn[20];
    printf("Digite o ISBN do livro: ");
    scanf(" %[^\n]", isbn);

    for (int i = 0; i < qtdLivros; i++) {
        if (strcmp(livros[i].isbn, isbn) == 0) {
            printf("Título: %s\nAutor: %s\nAno: %d\nStatus: %s\n",
                   livros[i].titulo, livros[i].autor, livros[i].ano,
                   livros[i].disponivel ? "Disponível" : "Emprestado");
            return;
        }
    }
    printf("Livro não encontrado.\n");
}

void listarLivrosDisponiveis() {
    printf("Livros Disponíveis:\n");
    for (int i = 0; i < qtdLivros; i++) {
        if (livros[i].disponivel) {
            printf("Título: %s, Autor: %s, ISBN: %s\n",
                   livros[i].titulo, livros[i].autor, livros[i].isbn);
        }
    }
}

void listarLivrosEmprestados() {
    printf("Livros Emprestados:\n");
    for (int i = 0; i < qtdLivros; i++) {
        if (!livros[i].disponivel) {
            printf("Título: %s, Autor: %s, ISBN: %s\n",
                   livros[i].titulo, livros[i].autor, livros[i].isbn);
        }
    }
}

// Funções de Gerenciamento de Usuários
void cadastrarUsuario() {
    Usuario usuario;
    printf("Digite o nome: ");
    scanf(" %[^\n]", usuario.nome);
    printf("Digite o ID: ");
    scanf("%d", &usuario.id);
    printf("Digite o contato: ");
    scanf(" %[^\n]", usuario.contato);
    usuario.emprestimosAtuais = 0;

    usuarios[qtdUsuarios++] = usuario;
    printf("Usuário cadastrado com sucesso!\n");
}

// Funções de Gerenciamento de Empréstimos
void realizarEmprestimo() {
    int idUsuario;
    char isbnLivro[20];
    printf("Digite o ID do usuário: ");
    scanf("%d", &idUsuario);
    printf("Digite o ISBN do livro: ");
    scanf(" %[^\n]", isbnLivro);

    int usuarioIndex = -1, livroIndex = -1;

    for (int i = 0; i < qtdUsuarios; i++) {
        if (usuarios[i].id == idUsuario) {
            usuarioIndex = i;
            break;
        }
    }

    for (int i = 0; i < qtdLivros; i++) {
        if (strcmp(livros[i].isbn, isbnLivro) == 0) {
            livroIndex = i;
            break;
        }
    }

    if (usuarioIndex == -1 || livroIndex == -1 || !livros[livroIndex].disponivel) {
        printf("Empréstimo não pode ser realizado.\n");
        return;
    }

    Emprestimo emprestimo;
    emprestimo.idUsuario = idUsuario;
    strcpy(emprestimo.isbnLivro, isbnLivro);
    printf("Digite a data de empréstimo (dd/mm/aaaa): ");
    scanf(" %[^\n]", emprestimo.dataEmprestimo);
    printf("Digite a data de devolução prevista (dd/mm/aaaa): ");
    scanf(" %[^\n]", emprestimo.dataDevolucaoPrevista);

    livros[livroIndex].disponivel = 0;
    usuarios[usuarioIndex].emprestimosAtuais++;
    emprestimos[qtdEmprestimos++] = emprestimo;

    printf("Empréstimo realizado com sucesso!\n");
}

void registrarDevolucao() {
    char isbnLivro[20];
    printf("Digite o ISBN do livro a devolver: ");
    scanf(" %[^\n]", isbnLivro);

    for (int i = 0; i < qtdEmprestimos; i++) {
        if (strcmp(emprestimos[i].isbnLivro, isbnLivro) == 0) {
            for (int j = 0; j < qtdLivros; j++) {
                if (strcmp(livros[j].isbn, isbnLivro) == 0) {
                    livros[j].disponivel = 1;
                    break;
                }
            }
            for (int k = 0; k < qtdUsuarios; k++) {
                if (usuarios[k].id == emprestimos[i].idUsuario) {
                    usuarios[k].emprestimosAtuais--;
                    break;
                }
            }

            emprestimos[i] = emprestimos[--qtdEmprestimos];
            printf("Devolução registrada com sucesso!\n");
            return;
        }
    }
    printf("Empréstimo não encontrado.\n");
}

// Menu Principal
void menu() {
    int opcao;
    do {
        printf("\n--- Sistema de Biblioteca ---\n");
        printf("1. Cadastrar Livro\n");
        printf("2. Consultar Livro\n");
        printf("3. Listar Livros Disponíveis\n");
        printf("4. Listar Livros Emprestados\n");
        printf("5. Cadastrar Usuário\n");
        printf("6. Realizar Empréstimo\n");
        printf("7. Registrar Devolução\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: cadastrarLivro(); break;
            case 2: consultarLivro(); break;
            case 3: listarLivrosDisponiveis(); break;
            case 4: listarLivrosEmprestados(); break;
            case 5: cadastrarUsuario(); break;
            case 6: realizarEmprestimo(); break;
            case 7: registrarDevolucao(); break;
            case 0: printf("Saindo...\n"); break;
            default: printf("Opção inválida!\n");
        }
    } while (opcao != 0);
}

int main() {
    menu();
    return 0;
}
