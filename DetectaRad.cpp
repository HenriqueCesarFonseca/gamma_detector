#include "DetectaRad.h"
#include <iostream>
#include <fstream>
#include <direct.h>
#include <stdlib.h>
#include <stdio.h>

DetectaRad::DetectaRad() {
	EstruturaConfig.config_limiar_cinza_deteccao = this->limiar_nivel_cinza_para_deteccao;
	EstruturaConfig.config_limiar_webcam_escuro = this->limiar_nivel_cinza_para_escuro;
	
	if (!_getcwd(PATH_DIR_INSTALADO, sizeof(PATH_DIR_INSTALADO)))
	{
		std::cout << "\nERRO: NÃO FOI POSSÍVEL OBTER O DIRETÓRIO" << "\n";
	}
	//PATH_DIR_INSTALADO = "C:\\";
	std::cout << "\nPATH_DIR_INSTALADO = " << PATH_DIR_INSTALADO << "\n";
}


bool DetectaRad::configura_resolucao_webcam_n(int n,int largura,int altura,bool mensagens)   //Escolhe com qual webcam trabalhar (webcam selecionada)
{
	this->largura = largura;
	this->altura  =  altura;
	//this->webcam_selecionada = n;
	if (mensagens) {
		std::cout << "\n\nConfigurado a resolução da webcam " << n << ":\n";
		std::cout << "Largura:  " << largura << std::endl;
		std::cout << "Altura :  " << altura << std::endl << std::endl;;
	}
	switch (largura)
	{
	case 320:
		this->raio_circulo = 4;
		this->espessura_circulo =1;
		break;
	case 640:
		this->raio_circulo = 5;
		this->espessura_circulo = 1;
	case 800: 
		this->raio_circulo = 8;
		this->espessura_circulo = 2;
		break;
	case 1280:
		this->raio_circulo = 10;
		this->espessura_circulo = 2;
	default:
		this->raio_circulo = 10;
		this->espessura_circulo = 2;
		break;
	}
	return true;
}

void DetectaRad::escolhe_parametros_de_deteccao()
{
	int matriz_resolucoes_detectadas[6][2] = {};
	char op = 'a';
	bool b_opcao_valida = false;
	bool b_camera_valida = false;
	int valor{ 0 };
	do {
		std::cout << "\n";
		
		std::cout << "Numero do experimento: " << numero_do_experimento << std::endl;
		std::cout << "Webcam selecionada:    " << webcam_selecionada << std::endl;
		std::cout << "Largura:               " << largura << std::endl;
		std::cout << "Altura:                " << altura << std::endl;
		std::cout << "Limiar de escuro:      " << EstruturaConfig.config_limiar_webcam_escuro << std::endl;
		std::cout << "Limiar de detecçao:    " << EstruturaConfig.config_limiar_cinza_deteccao<< std::endl;
		std::cout << "\n1) Altera limiar de detecçao de escuro                  \n";
		std::cout << "2) Altera  limiar de detecçao de radiação                \n";
		std::cout << "3) Testa todos os pixels da câmera e retorna maior valor encontrado \n";
		std::cout << "4) Seleciona outra webcam                                           \n";
		std::cout << "5) Finaliza alterações                                              \n";
		std::cout << "Escolha alguma opção: ";
		std::cin >> op;
		switch (op) {
		case '1': b_opcao_valida = true;
			mostra_variaveis_arq_config();
			std::cout << "\n\tDigite novo nível de detecçao de escuro: ";
			std::cin >> valor;
			if ((valor < 0) || (valor > 255)) { 
				std::cout << "\tVALOR INVÁLIDO - Valores váliddos: de 0 até 255\n";
				mostra_variaveis_arq_config();
				break;
			}
			atualiza_arquivo_config_limiar_nivel_cinza_escuro(valor);
			std::cout << "Valor alterado com sucesso!\n";
			mostra_variaveis_arq_config();
			break;
		case '2': b_opcao_valida = true;
			mostra_variaveis_arq_config();
			std::cout << "\n\tDigite novo nível de detecçao de radiaçao: ";
			std::cin >> valor;
			if ((valor < 0) || (valor > 255)) {
				std::cout << "\tVALOR INVÁLIDO - Valores váliddos: de 0 até 255\n";
				mostra_variaveis_arq_config();
				break;
			}
			atualiza_arquivo_config_limiar_nivel_cinza_deteccao(valor);
			std::cout << "Valor alterado com sucesso!\n";
			mostra_variaveis_arq_config();
			break;
		case '3': b_opcao_valida = true;
			mostra_variaveis_arq_config();
			std::cout << "Maior valor encontrado no escuro: " <<
				retorna_maximo_valor_de_todos_pixels_camera_n(webcam_selecionada) << std::endl;
			std::cout << "\n";
			break;
		case '4': b_opcao_valida = true;
			mostra_variaveis_arq_config();
			cameras_detectadas.clear();
			cameras_detectadas = retorna_webcam_disponiveis();
			std::cout << "\nCâmeras disponíveis: \n";
			for (auto n : cameras_detectadas)
			{
				std::cout << n << "\n";
			}
			std::cout << "\nEscolha uma câmera: ";
			std::cin >> valor;
			// falta verificar se valor é valido

			for (auto n : cameras_detectadas)
			{
				if (n == valor) {
					webcam_selecionada = valor;
					b_camera_valida = true;
				}
			}
			if (!b_camera_valida) {
				std::cout << "\nCâmera não disponível, escolha outra.\n";
			}
			else {
				webcam_selecionada = valor;
				if (retorna_se_webcam_n_esta_no_escuro(valor)) 
					std::cout << "\nEsta câmera está no escuro\n";
				else std::cout << "\nEsta câmera NÃO está no escuro\n";
				retorna_resolucoes_possiveis_de_uma_webcam_n(valor, matriz_resolucoes_detectadas);
				escolhe_resolucao(valor, this->largura, this->altura, matriz_resolucoes_detectadas);
			}
			std::cout << "\n";
			break;
		case '5': b_opcao_valida = false;
			break;
		default:
			b_opcao_valida = true;
		}
	} while (b_opcao_valida);
}

int DetectaRad::retorna_maximo_valor_de_todos_pixels_camera_n(int n)
{
	int nivel_cinza_xy{ 0 };
	int nivel_cinza_xy_max{ 0 };
	//cv::VideoCapture webcam(webcam_selecionada);
	cv::VideoCapture webcam(n);

	if (!webcam.isOpened()) {
		std::cout << "\n\n\n *****************   Não foi possível abrir a webcam   **************\n\n\n";
		return -1;
	}

	webcam.set(cv::CAP_PROP_FRAME_WIDTH, largura);
	webcam.set(cv::CAP_PROP_FRAME_HEIGHT, altura);

	cv::waitKey(200);
	webcam.read(frame);
	cv::waitKey(200);
	webcam.read(frame);
	cv::waitKey(200);
	webcam.read(frame);


	if (frame.empty()) {
		std::cout << "\n\\n\n*************  Imagem da webcam inacessível   ******************\n\n\n";
		return -1;
	}

	webcam.read(frame);
	cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
	
	for(int i=0; i<=255; i++) histograma_nivel_todos_pixels[i] = 0;
		

	for (int vertical = 0; vertical <= altura - 1; vertical++)
	for (int horizontal = 0; horizontal <= largura - 1; horizontal++) {
					nivel_cinza_xy = frame_gray.at<uchar>(vertical, horizontal);
			if ((nivel_cinza_xy >= 0) && (nivel_cinza_xy <= 255)) {
						histograma_nivel_todos_pixels[nivel_cinza_xy] = histograma_nivel_todos_pixels[nivel_cinza_xy] + 1;
					if((nivel_cinza_xy)>(nivel_cinza_xy_max)) 
						nivel_cinza_xy_max = nivel_cinza_xy;
			}
	}

	webcam.release();
	std::cout << "\nHistograma:\n";
	for (int i = 0; i <= 255; i++) 
	{
		if (histograma_nivel_todos_pixels[i] != 0) {
			std::cout << i << "  ->   " << histograma_nivel_todos_pixels[i] << "\n";
		}
	}

	std::cout << std::endl;
	std::cout << "Largura = " << largura << std::endl;
	std::cout << "Altura  = "  << altura   << std::endl;
	std::cout << std::endl;

	return nivel_cinza_xy_max;
}

void DetectaRad::define_webcam_selecionada(int n)
{
	this->webcam_selecionada = n;
}

int DetectaRad::retorna_numero_da_webcam_selecionada()
{
	return webcam_selecionada;
}

int DetectaRad::escolhe_resolucao(int numero_camera,int &var_largura, int &var_altura , int matriz_resolucoes_detectadas[6][2])
{
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
			var_largura = matriz_resolucoes_detectadas[0][0];
			var_altura  = matriz_resolucoes_detectadas[0][1];
			break;
		case '1': b_opcao_valida = true;
			var_largura = matriz_resolucoes_detectadas[1][0];
			var_altura  = matriz_resolucoes_detectadas[1][1];
			if (matriz_resolucoes_detectadas[1][0] == 0) b_opcao_valida = false;
			break;
		case '2': b_opcao_valida = true;
			var_largura = matriz_resolucoes_detectadas[2][0];
			var_altura  = matriz_resolucoes_detectadas[2][1];
			if (matriz_resolucoes_detectadas[2][0] == 0) b_opcao_valida = false;
			break;
		case '3': b_opcao_valida = true;
			var_largura = matriz_resolucoes_detectadas[3][0];
			var_altura  = matriz_resolucoes_detectadas[3][1];
			if (matriz_resolucoes_detectadas[3][0] == 0) b_opcao_valida = false;
			break;
		case '4': b_opcao_valida = true;
			var_largura = matriz_resolucoes_detectadas[4][0];
			var_altura  = matriz_resolucoes_detectadas[4][1];
			if (matriz_resolucoes_detectadas[4][0] == 0) b_opcao_valida = false;
			break;
		case '5': b_opcao_valida = true;
			var_largura = matriz_resolucoes_detectadas[5][0];
			var_altura  = matriz_resolucoes_detectadas[5][1];
			if (matriz_resolucoes_detectadas[5][0] == 0) b_opcao_valida = false;
			break;
		default: std::cout << "Opção inválida!\n\n";
			b_opcao_valida = false;
		}
	} while (!b_opcao_valida);
	return 0;
}


void DetectaRad::cria_arquivo_config_se_nao_existir() // se não existir
{
	std::ifstream file_conf_in(this->path_diretorio_base + "\\config.dat",std::ios::binary);
	if (!file_conf_in.is_open()) {
		//file_conf_in.close(); 

		EstruturaConfig.config_limiar_cinza_deteccao = limiar_nivel_cinza_para_deteccao;
		EstruturaConfig.config_limiar_webcam_escuro  = limiar_nivel_cinza_para_escuro;
		EstruturaConfig.config_numero_experimento    = 01;
		this->numero_do_experimento = 01;;

		std::ofstream file_conf_out(this->path_diretorio_base + "\\config.dat",std::ios::binary);
		file_conf_out.write((char*)&EstruturaConfig, sizeof(Config));
		file_conf_out.close();
	}
	else {
		//std::ifstream file_conf_in(this->path_diretorio_base + "\\config.dat", std::ios::binary);
		file_conf_in.read((char*)&EstruturaConfig, sizeof(Config));
		file_conf_in.close();

		limiar_nivel_cinza_para_deteccao = EstruturaConfig.config_limiar_cinza_deteccao;
		limiar_nivel_cinza_para_escuro   = EstruturaConfig.config_limiar_webcam_escuro;
		EstruturaConfig.config_numero_experimento++;
		this->numero_do_experimento      = EstruturaConfig.config_numero_experimento;

		std::ofstream file_conf_out(path_diretorio_base + "\\config.dat", std::ios::binary);
		file_conf_out.write((char*)&EstruturaConfig, sizeof(Config));
		file_conf_out.close();
	}
}


int DetectaRad::detecta_radiacao()
{
	int tmp_horizontal{ 0 };
	int tmp_vertical{ 0 };
	int tmp_nivel_de_cinza{ 0 };
	int tmp_frame{ 0 };
	int nivel_cinza_xy{ 0 };
	int tmp_n_frame_em_que_foi_detectado{ 0 };
	std::string texto_n_pontos = "PONTOS DETECTADOS : ";
	cv::Scalar Cor_Preto(0, 0, 0);
	cv::Scalar Cor_Fundo_Marrom(95, 115, 126);
	cv::Scalar Cor_Branco(255, 255, 255);
	cv::Mat matriz_detectados(altura, largura, CV_8UC3, Cor_Fundo_Marrom);
	cv::Mat tela_mensagens(100, 640, CV_8UC3, Cor_Preto);
	cv::Mat tela_mensagens_default(100, 640, CV_8UC3, Cor_Preto);
	cv::VideoCapture webcam(webcam_selecionada);
	bool b_flag_radiacao_detectada{ false };
	std::string nome_arq_imagem = "";
	std::ofstream file;


	if (!webcam.isOpened()) {
		std::cout << "\n\n\n *****************   Não foi possível abrir a webcam   **************\n\n\n";
		return 0;
	}

	webcam.set(cv::CAP_PROP_FRAME_WIDTH,  largura);
	webcam.set(cv::CAP_PROP_FRAME_HEIGHT,  altura);
	cv::waitKey(200);
	webcam.read(frame);
	if (frame.empty()) {
		std::cout << "\n\\n\n*************  Imagem da webcam inacessível   ******************\n\n\n";
		return 0;
	}

	cv::putText(tela_mensagens, texto_n_pontos + " 0", cv::Point(40, 40), cv::FONT_HERSHEY_SIMPLEX, 1, Cor_Branco, 2);
	cv::namedWindow("MENSAGENS", cv::WINDOW_AUTOSIZE);
	cv::imshow("MENSAGENS", tela_mensagens);


	while (cv::waitKey(1) != ESC) {

		webcam.read(frame);
		cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
		//cv::Mat frame_gray(720, 1280, CV_8UC1, Cor_Preto); // RETIRAR
		//frame_gray.at<uchar>(80, 200) = 255;			   // RETIRAR
		cv::namedWindow("IMAGEM EM TEMPO REAL", cv::WINDOW_NORMAL);
		cv::imshow("IMAGEM EM TEMPO REAL", frame);
		for(int vertical = 0; vertical <= altura -1; vertical++)
			for (int horizontal = 0; horizontal <= largura - 1; horizontal++) {
				nivel_cinza_xy = frame_gray.at<uchar>(vertical, horizontal);
				if (((nivel_cinza_xy) >= limiar_nivel_cinza_para_deteccao) && 
					((nivel_cinza_xy) >= tmp_nivel_de_cinza)){
					tmp_horizontal = horizontal;
					tmp_vertical   =   vertical;
					tmp_nivel_de_cinza = nivel_cinza_xy;
					tmp_n_frame_em_que_foi_detectado = total_de_frames_detectados;
					//std::cout << "(x;y) : " << horizontal << " : " << vertical << "  cinza: " << tmp_nivel_de_cinza << std::endl;
					b_flag_radiacao_detectada = true;
 				}
			}

		if (b_flag_radiacao_detectada) {
			
			coordenadas_xy[total_de_frames_detectados][0] = tmp_horizontal;
			coordenadas_xy[total_de_frames_detectados][1] = tmp_vertical;
			coordenadas_xy[total_de_frames_detectados][2] = tmp_nivel_de_cinza;
			coordenadas_xy[total_de_frames_detectados][3] = tmp_n_frame_em_que_foi_detectado;
			tmp_nivel_de_cinza = 0; // IMPORTANTE VERIFICAR SE CORRETO

			matriz_detectados.at<cv::Vec3b>(tmp_vertical, tmp_horizontal) = cv::Vec3b(255, 255, 255);
			cv::circle(matriz_detectados, cv::Point(tmp_horizontal, tmp_vertical), raio_circulo, cv::Scalar(0, 0, 255), espessura_circulo);

			tela_mensagens_default.copyTo(tela_mensagens);
					
			texto_n_pontos = "PONTOS DETECTADOS : " + std::to_string(total_de_frames_detectados+1);
			cv::putText(tela_mensagens, texto_n_pontos, cv::Point(40, 40), cv::FONT_HERSHEY_SIMPLEX, 1, Cor_Branco, 2);
			cv::namedWindow("MENSAGENS", cv::WINDOW_AUTOSIZE);
			cv::imshow("MENSAGENS", tela_mensagens);

			//frame.at<cv::Vec3b>(80, 200) = (255,255,255);			   // RETIRAR
			nome_arq_imagem = nome_diretorio_full + "\\imagem_captada_" + std::to_string(total_de_frames_detectados) + ".bmp";
			
		
			cv::imwrite(nome_arq_imagem, frame);

			b_flag_radiacao_detectada = false;
			total_de_frames_detectados++;
		}
		
		cv::namedWindow("MATRIZ DE PONTOS DETECTADOS", cv::WINDOW_NORMAL);
		cv::imshow("MATRIZ DE PONTOS DETECTADOS", matriz_detectados);

		

		
		total_de_frames_testados++;
		

	}
	webcam.release();
	std::cout << "\n \n";
	std::cout << "\nTotal de frames testados: " << total_de_frames_testados << std::endl;
	std::cout << nome_diretorio_full + "\\" + nome_file_pontos << "\n\n";
	file.open(nome_diretorio_full  + "\\" + nome_file_pontos);
	cv::imwrite(nome_diretorio_full + "\\imagem_com_todos_pontos_detectados.bmp", matriz_detectados);
	for (int contador=0; contador < total_de_frames_detectados; contador++)
	{
		file << coordenadas_xy[contador][0] << ":" << coordenadas_xy[contador][1] <<
			"\t\tNivel de cinza:  " << coordenadas_xy[contador][2] << "\t\t Frame: " <<
			coordenadas_xy[contador][3] << "\n";
	}
	file << "##########################################################################\n";
	file << "Total de pontos detectados: " << total_de_frames_detectados<< "\n";
	file.close();
	return 0;
}

std::vector<int> DetectaRad::retorna_webcam_disponiveis()
{
	for (int n = 0; n <= limite_cameras_a_serem_testadas; n++) {
		cv::VideoCapture webcam(n);

		if (webcam.isOpened()) {
			cameras_detectadas.push_back(n);
			webcam.release();
		}
	}
	numero_de_cameras_detectadas = cameras_detectadas.size();
	return cameras_detectadas;
}

void DetectaRad::retorna_resolucoes_possiveis_de_uma_webcam_n(int n, int matriz_resolucoes[6][2])
{
	int contador{ 0 };
	for (int j = 0; j < 6; j++) {
		matriz_resolucoes[j][0] = 0;
		matriz_resolucoes[j][1] = 0;

		cv::VideoCapture webcam(n);

		webcam.set(cv::CAP_PROP_FRAME_WIDTH, padroes_de_resolucoes[j][0]);
		webcam.set(cv::CAP_PROP_FRAME_HEIGHT, padroes_de_resolucoes[j][1]);

		cv::waitKey(100);

		webcam.read(frame);

		if (((frame.size().width) == padroes_de_resolucoes[j][0]) && ((frame.size().height) == padroes_de_resolucoes[j][1])) {
			matriz_resolucoes[contador][0] = padroes_de_resolucoes[j][0];
			matriz_resolucoes[contador][1] = padroes_de_resolucoes[j][1];
			contador++;
		}
	}

}

void DetectaRad::escolhe_automaticamente_webcam_no_escuro()
{
	cv::Mat frame, frame_gray;
	for (auto n : cameras_detectadas) {
		cv::VideoCapture webcam(n);
		webcam.read(frame);
		cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
		if (frame_gray.at<uchar>(100, 100) <= limiar_nivel_cinza_para_escuro) {
			CameraNoEscuro.numero_da_camera_no_escuro = n;
			CameraNoEscuro.b_camera_esta_no_escuro = true;
		}
	}
}

bool DetectaRad::retorna_se_webcam_n_esta_no_escuro(int n)
{
	cv::Mat frame, frame_gray;
	cv::VideoCapture webcam(n);
	webcam.read(frame);
	if (frame.empty()) return false; // Verificar
	cv::cvtColor(frame, frame_gray, cv::COLOR_BGR2GRAY);
	if (frame_gray.at<uchar>(100, 100) <= limiar_nivel_cinza_para_escuro) {
		CameraNoEscuro.b_camera_esta_no_escuro = true;
		return true;
	}
	return false;
}


void DetectaRad::altera_limiar_nivel_cinza_para_escuro(int novo_limiar)
{
	limiar_nivel_cinza_para_escuro = novo_limiar;
}

int DetectaRad::retorna_num_da_webcam_no_escuro()
{
	return CameraNoEscuro.numero_da_camera_no_escuro;
}

bool DetectaRad::retorna_se_existe_webcam_no_escuro()
{
	return CameraNoEscuro.b_camera_esta_no_escuro;
}

bool DetectaRad::retorna_se_webcam_n_esta_disponivel(int n)
{
	cv::VideoCapture webcam(n);
	if (webcam.isOpened()) return true;
	else return false;
}

void DetectaRad::altera_limiar_nivel_de_cinza_para_deteccao(int nivel)
{
	this->limiar_nivel_cinza_para_deteccao = nivel;
}


void DetectaRad::mostra_variaveis_arq_config()
{
	std::ifstream file_conf_in(this->path_diretorio_base + "\\config.dat",std::ios::binary);
	if (file_conf_in.is_open()) {
		file_conf_in.read((char*)&EstruturaConfig, sizeof(Config));
		file_conf_in.close();
		std::cout << "\n Número do experimento : " << this->EstruturaConfig.config_numero_experimento;
		std::cout << "\n Limiar de escuro      : " << this->EstruturaConfig.config_limiar_webcam_escuro;
		std::cout << "\n Limiar de detecçao    : " << this->EstruturaConfig.config_limiar_cinza_deteccao;
		std::cout << "\n\n";
	}
	else {
		std::cout << "Não conseguiu abrir o arquivo config.dat\n";
		file_conf_in.close();
	}
}

void DetectaRad::cria_diretorio_base(std::string diretorio)
{
	
	//std::string tmp_string(PATH_DIR_INSTALADO); ALTERADO DIA 13-04-23
	std::string tmp_string("C:\\");
	
	this->path_diretorio_base = tmp_string + diretorio;
	int tamanho = std::strlen(path_diretorio_base.c_str()); //int tamanho = std::strlen(diretorio.c_str());
	char criado[200] = "";
	for (int i = 0; i < tamanho; i++) {
		criado[i] = path_diretorio_base[i]; // criado[i] = diretorio[i];
	}
	  
	if (_mkdir(criado) == 0) {
		std::cout << "\nDiretório: " << path_diretorio_base << "\n";
		this->numero_do_experimento = 01;
	}

}

void DetectaRad::cria_diretorio_full()
{
	if (this->numero_do_experimento <= 9) {
		nome_diretorio_full = this->path_diretorio_base + "\\Experimento" + "0" + std::to_string(this->numero_do_experimento);
	}
	else {
		nome_diretorio_full = this->path_diretorio_base + "\\Experimento" + std::to_string(this->numero_do_experimento);
		std::cout << "Diretório do experimento:  " << nome_diretorio_full << "\n";
	}

	int tamanho = std::strlen(nome_diretorio_full.c_str());
	char criado[200] = "";
	for (int i = 0; i < tamanho; i++) {
		criado[i] = nome_diretorio_full[i];
	}

	if (_mkdir(criado) == 0) std::cout << "\nDiretório: " << nome_diretorio_full << "\n";
}

void DetectaRad::seta_nome_do_arquivo_pontos_detectados(std::string nome_arquivo_pontos_detectados)
{
	this->nome_file_pontos = nome_arquivo_pontos_detectados;
}

void DetectaRad::atualiza_arquivo_config_numero_experimento(int n) {
	std::ifstream file_conf_in(path_diretorio_base+ "\\config.dat",std::ios::binary);
	if (file_conf_in.is_open()) {
		file_conf_in.read((char*)&EstruturaConfig, sizeof(Config)); 
		this->EstruturaConfig.config_numero_experimento = n;
		this->numero_do_experimento = n;
		file_conf_in.close();

		std::ofstream file_conf_out(path_diretorio_base + "\\config.dat",std::ios::binary);
		file_conf_out.write((char*)&EstruturaConfig, sizeof(Config));
		file_conf_out.close();
	}
	else file_conf_in.close();
}

void DetectaRad::atualiza_arquivo_config_limiar_nivel_cinza_deteccao(int n) {
	std::ifstream file_conf_in(path_diretorio_base + "\\config.dat",std::ios::binary);
	if (file_conf_in.is_open()) {
		file_conf_in.read((char*)&EstruturaConfig, sizeof(Config));
		file_conf_in.close();
		this->EstruturaConfig.config_limiar_cinza_deteccao = n;
		limiar_nivel_cinza_para_deteccao = n;

		std::ofstream file_conf_out(path_diretorio_base + "\\config.dat",std::ios::binary);
		file_conf_out.write((char*)&EstruturaConfig, sizeof(Config));
		file_conf_out.close();
	}
	else file_conf_in.close();
}


void DetectaRad::atualiza_arquivo_config_limiar_nivel_cinza_escuro(int n) {
	std::ifstream file_conf_in(path_diretorio_base + "\\config.dat",std::ios::binary);
	if (file_conf_in.is_open()) {
		file_conf_in.read((char*)&EstruturaConfig, sizeof(Config));
		file_conf_in.close();
		this->EstruturaConfig.config_limiar_webcam_escuro = n;
		limiar_nivel_cinza_para_escuro = n;

		std::ofstream file_conf_out(path_diretorio_base + "\\config.dat",std::ios::binary);
		file_conf_out.write((char*)&EstruturaConfig, sizeof(Config));
		file_conf_out.close();
	}
	else file_conf_in.close();
}

