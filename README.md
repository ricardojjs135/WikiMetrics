# WikiMetrics

## Objetivo Geral
Desenvolver um protótipo funcional que leia e analise dados de pessoas presentes na Wikidata (base utilizada pela Wikipédia), utilizando uma base de dados disponibilizada por ela. O sistema processará as informações para apresentar métricas relevantes de forma visual e interativa, permitindo uma melhor compreensão da distribuição demográfica e outras características dos indivíduos descritos.

## Objetivos Específicos

### 1. Leitura de Dados Estruturados
- Implementar um módulo para carregar e interpretar arquivos JSON da Wikidata contendo informações sobre pessoas.
- Após a leitura, gerar um novo arquivo JSON contendo apenas os dados necessários.

### 2. Análise de Métricas
- Calcular métricas demográficas, incluindo:
  - Número de homens e mulheres.
  - Religião mais predominante.
  - Outras métricas que serão analisadas posteriormente.
- Identificar tendências adicionais, como faixas etárias predominantes ou presença de categorias específicas.

### 3. Visualização dos Resultados
- Gerar um arquivo CSV para posterior criação de gráficos dinâmicos (barras, pizza, histogramas) que ilustrem as métricas calculadas.

### 4. Otimização e Processamento de Dados
- Implementar algoritmos de ordenação e filtragem para transformar e analisar os dados de maneira rápida e eficiente.
- Avaliar a eficiência de algoritmos de ordenação (como QuickSort, MergeSort ou HeapSort) e selecionar o mais adequado para o contexto.

# Documentação

## Consulta de Dados da Wikidata
Para consultar os dados da Wikidata, foi utilizado o site **Wikidata Query Service**, que utiliza consultas via SPARQL para obter os dados desejados. Ao gerar a query, o site disponibiliza um código em Python para acesso direto aos dados. Este código está contido no arquivo `QueryGenerate.py`.

### `QueryGenerate.py`
Para executar este código, partindo do ponto de vista que o python e o pip estejam instalados na sua máquina, é necessário que rode o comando “pip install sparqlwrapper” no terminal.
Caso você não tenha permissão para baixar bibliotecas externas, pode-se criar um ambiente virtual utilizando o venv, seguindo os seguintes passos:
1. Criação do ambiente virtual: “python3 -m venv ~/venv”
2. Ativação do ambiente virtual: “source ~/venv/bin/activate”
3. Comando de instalação da biblioteca externa: “pip install sparqlwrapper”
4. Para sair do ambiente virtual, utilize: “deactivate”
5. Logo então, execute o código utilizando o comando “python QueryGenerate.py” (ou “python3 QueryGenerate.py”).

Após a execução do código, um conjunto de arquivos json serão gerados em uma pasta chamada “jsonFiles”, com os nomes iniciando com “wikidata_lote_X_XXXX-XX-XX.json” contendo dados de todas as pessoas existentes na base do WikiData residentes do Brasil.

OBS: Os arquivos são gerados com intervalos de data, pois uma única query não seria possível de rodar de uma vez pois o volume de dados é grande e daria timeOut, mesmo com esses intervalos de datas o programa pode parar em algum momento, caso pare, basta alterar as variáveis start_date e end_date de acordo com o primeiro lote com a última data gerada mostrada no terminal, e rodar o script novamente, para ele continuar de onde parou.

### `WikiMetricsMain`

Após gerar o arquivo com os dados, entre na pasta WikiMetricsMain, para rodar o programa em c++ para manipulação desses dados e a geração dos gráficos.

Comando para compilação pelo VS code: g++ -o main main.cpp JsonReader.cpp Human.cpp CalculateMetrics.cpp GenerateGraphics.cpp -I/home/ricardojjs/WikiMetrics/WikiMetricsMain/vcpkg/installed/x64-linux/include
Logo após: ./main

Este programa irá gerar arquivos txt de acordo com os gráficos existentes.

### `GenerateGraphics.py`

Após sair da pasta e voltar para o módulo principal do projeto, rode o script GenerateGraphics.py, através do comando “python3 GenerateGraphics.py”, este script irá gerar gráficos de acordo com os arquivos txt gerados pelo projeto WikiMetricsMain.

  

