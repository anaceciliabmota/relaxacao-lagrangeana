#!/bin/bash

# Caminho para o arquivo que contém as linhas com os argumentos
argumentos="instances_ub.txt"

# Caminho para o arquivo de saída onde os resultados serão armazenados
OUTPUT="benchmark.txt"

# Limpa o conteúdo anterior do arquivo de saída
> "$OUTPUT"

# Defina o limite de tempo (10 minutos)
tempo_limite="10m"

# Ler cada linha do arquivo e usar como argumento para o executável
while IFS=' ' read -r arg1 arg2; do
    echo "$arg1" >> "$OUTPUT"
        
    # Executa o comando com um limite de tempo de 10 minutos
    timeout "$tempo_limite" .././solve "../$arg1" "$arg2" >> "$OUTPUT" 2>&1

    # Verifica se o comando foi interrompido por ter atingido o tempo limite
    if [ $? -eq 124 ]; then
        echo "Execução interrompida após atingir o tempo limite de $tempo_limite." >> "$OUTPUT"
    fi
    
    echo "" >> "$OUTPUT"
done < "$argumentos"
