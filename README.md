### DETECCÇÃO DE RADIAÇÃO GAMA PARA FINS DIDÁTICOS UTILIZANDO WEBCAM


![logo](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/radiacao_2.png)


[Sobre](https://github.com/HenriqueCesarFonseca/gamma_detector#sobre-o-projeto) | [Visão Geral do Projeto](https://github.com/HenriqueCesarFonseca/gamma_detector#sobre-o-projeto) | [Montando o Detector](https://github.com/HenriqueCesarFonseca/gamma_detector#montando-o-detector) | [Download e Instalação](https://github.com/HenriqueCesarFonseca/gamma_detector#download-e-instala%C3%A7%C3%A3o) | [Utilizando o software DetectaRad](https://github.com/HenriqueCesarFonseca/gamma_detector#utilizando-o-software-detectarad) | [Fonte de Radiação](https://github.com/HenriqueCesarFonseca/gamma_detector#fonte-de-radia%C3%A7%C3%A3o)



### **Sobre o projeto**
O objetivo geral deste projeto é enriquecer o ensino de Física Moderna em sala de aula através da confecção de um experimento de baixo custo e viável de ser realizado em sala de aula para turmas do ensino médio.

O experimento consiste em captar radiação ionizante do tipo gama atravez de uma webcam de baixo custo e analisar as imagens em tempo real através de um software (DetectaRad) desenvolvido para este fim.

Este projeto faz parte da dissertação de mestrado do **Programa Nacional de Mestrado Profissional em Ensino de Física (MNPEF)** desenvolvida no polo da UNESP de Presidente Prudente - SP, orientado pela Profª. Dra. Ana Maria Osório Araya.
 

 ### **Visão Geral do Projeto**

Uma fonte de radiação gama e uma webcam são colocadas dentro de um recipiente fechado para impedir a entrada de luz. O cabo USB da webcam é conectado a um PC onde o software **DetectaRad** irá exibir em tempo real todos os pontos de radiação detectados bem como uma janela com todos os pontos já detectados e a quantidade total de pontos detectados.

![esquema](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/VIS%C3%83O%20GERAL.bmp)

Ao finalizar o programa, todos os frames em que foram detectados algum ponto de radiação são armazenados em um diretório bem como um arquivo com as coordenadas de todos os pontos de radiação detectados. A cada experimento um novo diretório é criado e numerado sequencialmente.
O software DetectaRad foi desenvolvido para ser executado apenas no sistema operacional Windows.

[Clique aqui para ver uma demonstração no YouTube](https://youtu.be/BfPhDDmZTyQ)

![GIF](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/gif_2.gif)

A webcam é colocada dentro de um recipiente fechado para evitar a entrada de luz.



![Montagem final](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/MONTAGEM%20FINAL%20RESIZED%20640%20X%20480.bmp)

Os pontos na janela **IMAGEM EM TEMPO REAL** aparecem e desaparecem rapidamente. Alguns pontos com intensidade mais fraca não podem ser visto pelo observador. A imagem abaixo (640 x 480) mostra um ponto bem visível detectado nas coordenadas (88;260). Como a imagem gerada segue o padrão da biblioteca OpenCV , a origem (0,0) situa-se no canto esquerdo superior.

![Ponto bem visível](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/imagem_captada_3.bmp)


A cada experimento um novo diretório é criado.

![Diretórios criados](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/DIRETORIO%20COM%20EXPERIMENTOS.png)

Dentro de cada diretório são armazenados todos os frames em que foi detectada algum ponto de radiação.

![Diretório do experimento](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/DIRETORIO%20DO%20EXPERIMENTO.png)

O arquivo  ***todos_os_pontos_detectador.txt*** - gerado automaticamente ao final do programa - lista as coordenadas de todos os pontos detectados.

```
266:102		Nivel de cinza:  72		 Frame: 0
506:248		Nivel de cinza:  59		 Frame: 1
515:143		Nivel de cinza:  32		 Frame: 2
88:260           Nivel de cinza:  105		 Frame: 3
489:370		Nivel de cinza:  51		 Frame: 4
511:107		Nivel de cinza:  72		 Frame: 5
110:2	        Nivel de cinza:  33		 Frame: 6
37:246		Nivel de cinza:  33		 Frame: 7
111:303		Nivel de cinza:  111		 Frame: 8
567:1		Nivel de cinza:  126		 Frame: 9
544:461		Nivel de cinza:  77		 Frame: 10
497:394		Nivel de cinza:  47		 Frame: 11
115:359		Nivel de cinza:  114		 Frame: 12
###########################################################
Total de pontos detectados: 13

```

A primeira linha corresponde ao primeiro frame capturado , a segunda linha ao segundo frame e assim por diante.

Desta forma podemos conferir utilizando o programa **PAINT** do Windows que realmente na **coordenada (88;260)**encontramos um ponto de detecção conforme mostrado na Figura abaixo.

![Ponto visto do PAINT](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/PONTO%20VISTO%20PELO%20PAINT%201.bmp)


O parâmetro **Nível de cinza** corresponde à conversão do padrão **RGB** com diferentes intensidade para **Red**,**Green** e **Blue** convertidas para o padrão **GRAY** com um único nível de intensidade (o que facilita o software executar a busca por um ponto detectado).





 ### **Montando o Detector**

Webcam escolhida com sensor do tipo **CMOS**.

![Webcam escolhida](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/WEBCAM%20ESCOLHIDA.bmp)

A Webcam é desmontada para retirar a lente.

![Webcam desmontada](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/WEBCAM%20DESMONTADA.bmp)

É passado fita isolante para evitar curto circuito ao fixar a câmera à lata com furo (furo para o sensor **CMOS**).

![Webcam com fita isolante](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/WEBCAM%20COM%20FITA%20ISOLANTE.bmp)


É feito um furo para expor somente o sensor **CMOS** da Webcam.
![Montagem 1](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/MONTAGEM%201.bmp)

A fonte de radiação deve ser colocada de frente para o sensor **CMOS** com o cuidado de evitar danificar o sensor.

![Montagem 2](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/MONTAGEM%202.bmp)


Utilizada uma segunda lata vedada para a entrada de luz.
![Montagem 3](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/MONTAGEM%203.bmp)


Na segunda lata é cortado uma pequena abertura para a passagem do cabo USB da Webcam.
![Montagem 4](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/MONTAGEM%204.bmp)


Finalizado a montagem do experimento.
![Montagem final](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/MONTAGEM%20FINAL%20RESIZED%20640%20X%20480.bmp)


 ### **Download e Instalação**

Baixe os arquivos ***DetectaRad.msi*** e ***setup.exe***.
![Arquivo para download](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/DOWNLOAD%201.bmp)

Após o download clique no arquivo ***setup.exe*** para executar a instalação.

![Instalador](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/DOWNLOAD%202.png)


Clique em ***Avançar***.

![Avançar](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/BEM%20VINDO%201.png)

Clique em ***Avançar***.

![Avançar](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/BEM%20VINDO%202.png)

Clique em ***Avançar***.

![Avançar](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/BEM%20VINDO%203.png)

Clique em ***Fechar***.

![Fechar](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/BEM%20VINDO%204.png)



Na opção ***Aplicativos instalados*** do Windows o programa pode ser removido caso queira.
![Aplicativos instalados](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/APLICATIVOS%20INSTALADOS.png)


Um atalho é criado na área de trabalho.

![Atalho](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/ATALHO%201.png)





### **Utilizando o software DetectaRad**

Clique no atalho na área de trabalho.

![Atalho](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/ATALHO%201.png)

O software **DetectaRad** encontra todas a câmeras instaladas no computador. Se for um notebook a câmera 0 será a Webcam que já vem no notebook logo acima da tela. No exemplo abaixo mais duas câmeras (webcam) estão instaladas. O software seleciona automaticamente a primeira câmera que estiver no escuro. No exemplo as câmeras 1 e 2 estão no escuro. Cada webcam possui diferentes valores de resolução possíveis, o software testa e informa todas as resoluções possíveis para a câmera escolhida.

Escolha a resolução desejada.
![Menu 1](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/PROGRAMA%201.png)

Uma vez escolhido a resolução o software faz uma leitura de todos os pontos do sensor de imagem de devolve um histograma de todos os valores encontrados que corresponde ao nível de cinza onde o menor valor possível é 0 (totalmente escuro) e o valor máximo é 255 que corresponde ao branco. Estes valores servem de referência para a escolha do parâmetro ***Limiar de detecção*** que diz a partir de que valor será considerado uma detecção, valores abaixo deste limiar são desconsiderados.
Tanto o ***Limiar de escuro*** quanto o ***Limiar de detecção*** são configuraveis antes de iniciar as detecções.

![Menu 2](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/PROGRAMA%202.png)

No exemplo acima a resolução é de 1280 x 800 pontos (pixels), o que dá um total de 1.024.000 pontos. Mesmos com a câmera no escuro nem todos os pontos apresentaram um valor de leitura 0 (totalmente escuro). Apresentaram o nível de leitura 1, 11688 pontos e apresentaram o nível de leitura 2, 4 pontos apenas.
Somando os valores temos:
```
1.012.308 + 11.688 + 4 = 1.024.000 pixels
```

### **Fonte de Radiação**

Capsula utilizada em detector de fumaça com Amerício-241.
![Capsula fechada](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/CAPSULA%20FECHADA.bmp)


Capsula aberta. 
![Capsula aberta](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/CAPSULA%20ABERTA.bmp)


O Amerício-241 emite radiação alfa e gama.

![Equação decaimento americio](https://github.com/HenriqueCesarFonseca/gamma_detector/blob/main/Imagens/EQUA%C3%87%C3%83O.png)




