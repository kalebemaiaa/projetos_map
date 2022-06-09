function saida = fazListaArestas(matrizAdjacencia)
    lista = [];
    
    for i = 1:length(matrizAdjacencia)
        for k = 1:i
            if (matrizAdjacencia(k,i) == 1)
                lista( end + 1, 1 ) = k;
                lista( end , 2 ) = i;
            end
        end
    end
   
    saida = lista ;
end

