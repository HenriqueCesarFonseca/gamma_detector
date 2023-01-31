#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
#include <fstream>

#define LIMITE_DE_PONTOS {20000};

class DetectaRad
{
private:

	int padroes_de_resolucoes[6][2] = {
		{320,240},
		{640,360},
		{640,480},
		{800,600},
		{1280,720},
		{1280,800}
	};

	struct CamEscuro {
		bool b_camera_esta_no_escuro{ false };
		int  numero_da_camera_no_escuro{ 0 };
	}CameraNoEscuro;

	const int ESC{ 27 };
	int largura	{ 0 };
	int altura	{ 0 };
	int webcam_selecionada { 0 };
	int total_de_frames_testados	{ 0 };
	int total_de_frames_detectados	{ 0 };
	int limiar_nivel_cinza_para_deteccao	{ 20 };
	int limiar_nivel_cinza_para_escuro{ 10 };
	int coordenadas_xy[20000][4] {};
	int raio_circulo{ 10 };
	int espessura_circulo{ 2 };
	std::string nome_file_pontos{};
	std::string path_diretorio_base; 
	std::string nome_diretorio_full {};
	cv::Mat frame, frame_gray;

	std::vector<int> cameras_detectadas{};
	int numero_de_cameras_detectadas{ 0 };
	int matriz_resolucoes_detectadas[6][2]{};
	int limite_cameras_a_serem_testadas{ 20 };
	int numero_do_experimento{ 1 };
	int histograma_nivel_todos_pixels[256]{ 0 };
	char PATH_DIR_INSTALADO[100] = {};

	struct  Config
	{
	public:
		int config_numero_experimento{ 1 };
		int config_limiar_webcam_escuro{10};
		int config_limiar_cinza_deteccao{30};
	}EstruturaConfig;

public:
	DetectaRad();
	void cria_diretorio_base(std::string);
	void cria_diretorio_full();
	void seta_nome_do_arquivo_pontos_detectados(std::string);
	void cria_arquivo_config_se_nao_existir();
	void mostra_variaveis_arq_config();
	void atualiza_arquivo_config_numero_experimento(int n);
	void atualiza_arquivo_config_limiar_nivel_cinza_deteccao(int n);
	void atualiza_arquivo_config_limiar_nivel_cinza_escuro(int n);
	void altera_limiar_nivel_de_cinza_para_deteccao(int nivel);
	void altera_limiar_nivel_cinza_para_escuro(int);

	int  detecta_radiacao();

	bool configura_resolucao_webcam_n(int n, int largura, int altura, bool mensagens);
	std::vector<int> retorna_webcam_disponiveis();
	bool retorna_se_existe_webcam_no_escuro();
	bool retorna_se_webcam_n_esta_no_escuro(int);
	bool retorna_se_webcam_n_esta_disponivel(int);
	int  retorna_num_da_webcam_no_escuro();
	void escolhe_automaticamente_webcam_no_escuro();
	void retorna_resolucoes_possiveis_de_uma_webcam_n(int, int[6][2]);
	void escolhe_parametros_de_deteccao();
	int  retorna_maximo_valor_de_todos_pixels_camera_n(int num_camera);
	void define_webcam_selecionada(int);
	int  retorna_numero_da_webcam_selecionada();
	int  escolhe_resolucao(int numero_camera, int &var_largura, int &var_altura , int[6][2]);
};