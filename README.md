# WikiMetrics

## Objetivo Geral
Desenvolver um protótipo funcional que leia e analise dados de pessoas presentes na Wikidata (base utilizada pela Wikipédia), utilizando uma base de dados disponibilizada por ela. O sistema processará as informações para apresentar métricas relevantes de forma visual e interativa, permitindo uma melhor compreensão da distribuição demográfica e outras características dos indivíduos descritos.

## Objetivos Específicos

### 1. Leitura de Dados Estruturados
- Implementar um módulo para carregar e interpretar dados do banco da Wikidata contendo informações sobre os humanos de lá.
- Após a leitura, gerar um arquivo JSON contendo os dados formatados.

### 2. Análise de Métricas
- Calcular métricas demográficas, incluindo:
  - Número de homens e mulheres.
  - Profissão mais dominante.
  - Religião mais predominante.

### 3. Visualização dos Resultados
- Gerar gráficos dinâmicos (barras e pizza) que ilustrem as métricas calculadas.

# Documentação

## Consulta de Dados da Wikidata
Para consultar os dados da Wikidata, foi utilizado o site **https://query.wikidata.org/**, que utiliza consultas via SPARQL para obter os dados desejados. Ao gerar e testar a query, foi-se criado um script: `QueryGenerate.py` para que extraia o resultado desta query, formate os dados e gere arquivos json como resultado.

### `QueryGenerate.py`
Para executar este código, partindo do ponto de vista que o python e o pip estejam instalados na sua máquina, é necessário que rode o comando “pip install sparqlwrapper” no terminal.
Caso você não tenha permissão para baixar bibliotecas externas, pode-se criar um ambiente virtual utilizando o venv, seguindo os seguintes passos:
1. Criação do ambiente virtual: “python3 -m venv ~/venv”
2. Ativação do ambiente virtual: “source ~/venv/bin/activate”
3. Comando de instalação da biblioteca externa: “pip install sparqlwrapper”
5. Logo então, execute o código utilizando o comando “python QueryGenerate.py” (ou “python3 QueryGenerate.py”).
6. Caso queira sair do ambiente virtual, utilize: “deactivate”

Após a execução do código, um conjunto de arquivos json serão gerados em uma pasta chamada “jsonFiles”, com os nomes iniciando com “wikidata_lote_X_XXXX-XX-XX.json” contendo dados de todas as pessoas existentes na base do WikiData residentes no Brasil.

OBS: Os arquivos são gerados com intervalos de data, pois uma única query não seria possível rodar de uma vez pois o volume de dados é grande e daria timeout, mesmo com esses intervalos de datas o programa pode parar em algum momento, caso pare, basta alterar as variáveis start_date e end_date de acordo com o primeiro lote com a última data gerada mostrada no terminal, e rodar o script novamente, para ele continuar de onde parou.

### WikiMetricsMain

Após gerar o arquivo com os dados, entre na pasta WikiMetricsMain, para rodar o programa em c++ para manipulação desses dados e a geração dos gráficos.

- Comando para compilação pelo VS code: g++ -o main main.cpp JsonReader.cpp Human.cpp CalculateMetrics.cpp GenerateGraphics.cpp -I/home/ricardojjs/WikiMetrics/WikiMetricsMain/vcpkg/installed/x64-linux/include
- Logo após: ./main

Este programa irá gerar arquivos txt de acordo com os gráficos existentes.

### `GenerateGraphics.py`

Após sair da pasta e voltar para o módulo principal do projeto, rode o script `GenerateGraphics.py`, através do comando “python3 GenerateGraphics.py”, este script irá gerar gráficos de acordo com os arquivos txt gerados pelo projeto WikiMetricsMain.

  

