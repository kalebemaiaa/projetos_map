function saida = fazMatrizAdjacencia(vetorBidimensional)
    saida = zeros(max(max(vetorBidimensional)));
    
    for i = 1:length(vetorBidimensional)
        saida(vetorBidimensional(i,1),vetorBidimensional(i,2)) = 1;
        saida(vetorBidimensional(i,2),vetorBidimensional(i,1)) = 1;
    end
end