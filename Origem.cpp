#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>
#include <vector>
#include <locale>
#include "DetectaRad.h"


int main() {
	system("CLS");
	setlocale(LC_ALL, "Portuguese");
	DetectaRad* DR = new DetectaRad;
	//int escolhe_resolucao(int n, int& largura, int& altura, int matriz_resolucoes_detectadas[6][2]);

	int matriz_resolucoes_detectadas[6][2] = {};
	int largura = 640;
	int altura = 480;

	bool b_mensagem = true;
	std::vector<int> cameras_detectadas;
	std::string nome_arquivo_pontos = "todos_pontos_detectados.txt";
	std::string diretorio = "\\DetectaRadiacao";

	std::cout << "Programa DETECTA RADIACAO iniciando ... \n";

	DR->cria_diretorio_base(diretorio);
	DR->cria_arquivo_config_se_nao_existir();
	DR->cria_diretorio_full();
	DR->seta_nome_do_arquivo_pontos_detectados(nome_arquivo_pontos);
	DR->mostra_variaveis_arq_config();

	cameras_detectadas = DR->retorna_webcam_disponiveis();
	std::cout << "\nNumero de cameras disponíveis detectadas: " << cameras_detectadas.size() << "\n";
	std::cout << "Lista de câmeras disponíveis detectadas:\n";
	for (auto n : cameras_detectadas)
	{
		std::cout << n << "\n";
	}

	DR->escolhe_automaticamente_webcam_no_escuro();
	if (DR->retorna_se_existe_webcam_no_escuro()) {
		std::cout << "Número da webcam detectada no escuro: " <<
		DR->retorna_num_da_webcam_no_escuro() << "\n";
		DR->define_webcam_selecionada(DR->retorna_num_da_webcam_no_escuro());
	}
	else {
		std::cout << "\nNenhuma câmera no escuro!\n";
		DR->define_webcam_selecionada(0);
	}

	DR->retorna_resolucoes_possiveis_de_uma_webcam_n
	(DR->retorna_num_da_webcam_no_escuro(), matriz_resolucoes_detectadas);
	
	DR->define_webcam_selecionada(DR->retorna_num_da_webcam_no_escuro());
	std::cout << "Webcam selecionada: " << DR->retorna_numero_da_webcam_selecionada() << "\n\n";

	//escolhe_resolucao(DR->retorna_numero_da_webcam_selecionada(), largura, altura, matriz_resolucoes_detectadas);
	DR->escolhe_resolucao(DR->retorna_numero_da_webcam_selecionada(),largura,altura, matriz_resolucoes_detectadas);

	DR->configura_resolucao_webcam_n
	(DR->retorna_numero_da_webcam_selecionada(), largura, altura, b_mensagem);

	std::cout << "Maior valor encontrado no escuro: "
		<<  DR->retorna_maximo_valor_de_todos_pixels_camera_n
		(DR->retorna_numero_da_webcam_selecionada()) << std::endl;

	std::cout << "\n";
	DR->escolhe_parametros_de_deteccao();
	std::cout << "\nIniciando detecçao de radiação ....\n";
	
	DR->detecta_radiacao();
	delete DR;
	return 0;
}
/*
int escolhe_resolucao(int numero_camera, int &largura, int &altura, int matriz_resolucoes_detectadas[6][2]) {
	char op = 'a';
	bool b_opcao_valida = true;
	do {
		std::cout << "Resoluções possíveis para a webcam " << numero_camera << ":\n";
		for (int i = 0; i <= 5; i++) {
			if (matriz_resolucoes_detectadas[i][0] == 0) break;
			std::cout << i << ")   " << matriz_resolucoes_detectadas[i][0] << " x " << matriz_resolucoes_detectadas[i][1];
			std::cout << "\n";
		}
		std::cout << "Escolha uma resolução: ";
		std::cin >> op;
		switch (op)
		{
		case '0': b_opcao_valida = true;
			largura = matriz_resolucoes_detectadas[0][0];
			altura = matriz_resolucoes_detectadas[0][1];
			break;
		case '1': b_opcao_valida = true;
			largura = matriz_resolucoes_detectadas[1][0];
			altura = matriz_resolucoes_detectadas[1][1];
			if (matriz_resolucoes_detectadas[1][0] == 0) b_opcao_valida = false;
			break;
		case '2': b_opcao_valida = true;
			largura = matriz_resolucoes_detectadas[2][0];
			altura = matriz_resolucoes_detectadas[2][1];
			if (matriz_resolucoes_detectadas[2][0] == 0) b_opcao_valida = false;
			break;
		case '3': b_opcao_valida = true;
			largura = matriz_resolucoes_detectadas[3][0];
			altura = matriz_resolucoes_detectadas[3][1];
			if (matriz_resolucoes_detectadas[3][0] == 0) b_opcao_valida = false;
			break;
		case '4': b_opcao_valida = true;
			largura = matriz_resolucoes_detectadas[4][0];
			altura = matriz_resolucoes_detectadas[4][1];
			if (matriz_resolucoes_detectadas[4][0] == 0) b_opcao_valida = false;
			break;
		case '5': b_opcao_valida = true;
			largura = matriz_resolucoes_detectadas[5][0];
			altura = matriz_resolucoes_detectadas[5][1];
			if (matriz_resolucoes_detectadas[5][0] == 0) b_opcao_valida = false;
			break;
		default: std::cout << "Opção inválida!\n\n";
			b_opcao_valida = false;
		}
	} while (!b_opcao_valida);
	return 0;
}
*/
