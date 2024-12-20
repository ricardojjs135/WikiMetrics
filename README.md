# WikiMetrics

## Objetivo Geral
Desenvolver um protótipo funcional que leia e analise dados de pessoas presentes na Wikidata (base utilizada pela Wikipédia), utilizando arquivos JSON disponibilizados pela Wikidata. O sistema processará as informações para apresentar métricas relevantes de forma visual e interativa, permitindo uma melhor compreensão da distribuição demográfica e outras características dos indivíduos descritos.

## Objetivos Específicos

### 1. Leitura de Dados Estruturados
- Implementar um módulo para carregar e interpretar arquivos JSON da Wikidata contendo informações sobre pessoas.
- Após a leitura, gerar um novo arquivo JSON contendo apenas os dados necessários.

### 2. Análise de Métricas
- Calcular métricas demográficas, incluindo:
  - Número de homens e mulheres.
  - Religião mais predominante.
- Identificar tendências adicionais, como faixas etárias predominantes ou presença de categorias específicas.

### 3. Visualização dos Resultados
- Gerar um arquivo CSV para posterior criação de gráficos dinâmicos (barras, pizza, histogramas) que ilustrem as métricas calculadas.

### 4. Otimização e Processamento de Dados
- Implementar algoritmos de ordenação e filtragem para transformar e analisar os dados de maneira rápida e eficiente.
- Avaliar a eficiência de algoritmos de ordenação (como QuickSort, MergeSort ou HeapSort) e selecionar o mais adequado para o contexto.
