#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>
#include <cctype>
#include <locale>

#ifdef _WIN32
    #define PAUSE_COMMAND "pause"
#else
    #define PAUSE_COMMAND "read -p 'Pressione Enter para continuar...'"
#endif

using namespace std;

void menuJogoDaForca();

// Função para imprimir a forca atual
void imprimirForca(int tentativas) {
    switch (tentativas) {
    case 0:
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        break;
    case 1:
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        break;
    case 2:
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << "  |   |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        break;
    case 3:
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|   |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        break;
    case 4:
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|\\  |" << endl;
        cout << "      |" << endl;
        cout << "      |" << endl;
        break;
    case 5:
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|\\  |" << endl;
        cout << " /    |" << endl;
        cout << "      |" << endl;
        break;
    case 6:
        cout << "  +---+" << endl;
        cout << "  |   |" << endl;
        cout << "  O   |" << endl;
        cout << " /|\\  |" << endl;
        cout << " / \\  |" << endl;
        cout << "      |" << endl;
        break;
    }
}

// Função para imprimir a palavra atual com as letras adivinhadas
void imprimirPalavra(const string& palavra, const string& letrasAdivinhadas) {
    for (char letter : palavra) {
        if (letrasAdivinhadas.find(letter) != string::npos) {
            cout << letter << " ";
        } else if (letter == ' ') {
            cout << "  ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

// Função para verificar se a letra está na palavra
bool letraNaPalavra(char letra, const string& palavra) {
    return (palavra.find(letra) != string::npos);
}

void jogo() {
    // Lista de palavras para o jogo
    string palavras[] = {"programacao", "computador", "linguagem", "desenvolvimento", "software", "hardware", "protocolo",
            "algoritmo", "codigo", "variavel", "funcao", "biblioteca", "interface", "compilacao", "debugar", "servidor", "cliente",
            "rede", "banco de dados", "javascript", "typescript", "python", "powershell", "bash", "linux", "docker", "kubernetes",
            "criptografia", "internet", "email", "download", "upload", "backup", "desktop", "devops", "inteligencia artificial",
            "seguranca", "machine learning", "firewall", "hacker", "exploit", "dominio", "hospedagem", "servidor web", "navegador"};

    // Escolher uma palavra aleatória
    srand(static_cast<unsigned int>(time(0)));
    int indiceAleatorio = rand() % (sizeof(palavras) / sizeof(palavras[0]));
    string palavraSelecionada = palavras[indiceAleatorio];
    
    // Removendo espaços da string
    string palavraSemEspaco = "";
    for (char c : palavraSelecionada) {
        if (c != ' ') {
            palavraSemEspaco += c;
        }
    }

    int maxTentativas = 6;
    int tentativas = 0;
    string letrasAdivinhadas;
    int opcao;

    system("clear");
    cout << "Bem-vindo ao Jogo da Forca!" << endl;

    while (tentativas < maxTentativas) {

        // Imprimir a forca e a palavra atual
        for (size_t i = 0; i < letrasAdivinhadas.length(); ++i) {
            // Se não for o último caractere, adiciona ", " à string de resultado
            cout << letrasAdivinhadas[i] << ", ";
        }

        cout << "\n";

        imprimirForca(tentativas);
        imprimirPalavra(palavraSelecionada, letrasAdivinhadas);

        // Pedir ao jogador para adivinhar uma letra
        cout << "Digite uma letra: ";
        char palpite;
        cin >> palpite;
        palpite = tolower(palpite);

        // Verificar se a letra já foi adivinhada
        if (letrasAdivinhadas.find(palpite) != string::npos) {
            system("clear");
            cout << "Voce ja tentou essa letra. Tente novamente." << endl;
            continue;
        }

        // Adicionar a letra às letras adivinhadas
        letrasAdivinhadas += palpite;

        // Verificar se a letra está na palavra
        if (letraNaPalavra(palpite, palavraSemEspaco)) {
            system("clear");
            cout << "\x1b[32m" "Correto!" << "\x1b[0m" " A letra esta na palavra." << endl;
        } else {
            system("clear");
            cout << "\x1b[31m" "Incorreto!" << "\x1b[0m" << " Tente novamente." << endl;
            tentativas++;
        }

        // Verificar se o jogador ganhou
        bool palavraAdivinhada = all_of(palavraSemEspaco.begin(), palavraSemEspaco.end(), [&letrasAdivinhadas](char letra) {
            return letrasAdivinhadas.find(letra) != string::npos;
        });

        if (palavraAdivinhada) {

            while (opcao < 1 || opcao > 3) {
                system("clear");

                cout << "\x1b[33m" << "Parabens! " << "\x1b[0m" << "Voce adivinhou a palavra: " << palavraSelecionada << endl;
                imprimirForca(tentativas);

                cout << "\nEscolha uma Opcao:";
                cout << "\n 1 - Jogar Novamente";
                cout << "\n 2 - Voltar Para o Menu";
                cout << "\n 3 - Sair";
                cout << "\n";
                cin >> opcao;
            }

            switch (opcao) {
                case 1:
                    jogo();
                    break;
                case 2:
                    cout << "Voltando para o Menu";
                    menuJogoDaForca();
                    break;
            }

            break;
        }
    }

    // Se o jogador atingir o número máximo de tentativas
    if (tentativas == maxTentativas) {

        while (opcao < 1 || opcao > 3) {
            system("clear");

            cout << "\x1b[31m" << "Voce perdeu! " << "\x1b[0m" << "A palavra correta era: " << palavraSelecionada << endl;
            imprimirForca(tentativas);

            cout << "\nEscolha uma Opcao:";
            cout << "\n 1 - Jogar Novamente";
            cout << "\n 2 - Voltar Para o Menu";
            cout << "\n 3 - Sair";
            cout << "\n";
            cin >> opcao;
        }

        
        switch (opcao) {
            case 1:
                jogo();
                break;
            case 2:
                cout << "Voltando para o Menu";
                menuJogoDaForca();
                break;
        }
    }

}

void menuJogoDaForca() {
    int opcao;

    while (opcao < 1 || opcao > 3) {

        system("clear");
        cout << "         =============         " << endl;
        cout << "         |   +---+   |         " << endl;
        cout << "         |   |   |   |         " << endl;
        cout << "         |   O   |   |         " << endl;
        cout << "         |  /|\\  |   |         " << endl;
        cout << "         |  / \\  |   |         " << endl;
        cout << "         |       |   |         " << endl;
        cout << "===============================" << endl;

        cout << "| Bem Vindo ao Jogo Da Forca! |" << endl;;
        cout << "|  1 - Jogar                  |" << endl;;
        cout << "|  2 - Sobre                  |" << endl;;
        cout << "|  3 - Sair                   |" << endl;;
        cout << "===============================" << endl;
        cin >> opcao;

        switch (opcao) {
            case 1:
                jogo();
                break;
            
            case 2:
                system("clear");
                cout << "No jogo da forca solo, o jogador desafia o computador, que escolhe uma palavra secreta. \n";
                cout << "O objetivo e adivinhar a palavra por meio de tentativas de letras, com um numero limitado de \n";
                cout << "erros permitidos. A emocao reside na busca pela palavra certa enquanto se evita exceder o  \n";
                cout << "limite de erros. ";
                cout << "\n\n";

                system(PAUSE_COMMAND);

                menuJogoDaForca();
                break;
        }
    }
}


void JogoDaForca() {
    srand(static_cast<unsigned>(time(NULL)));

    menuJogoDaForca();
}