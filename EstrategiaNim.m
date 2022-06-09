function n_retirados = EstrategiaNim(estado_jogo, retirada_max)

palitos_restantes = sum(estado_jogo==1);
count = palitos_restantes - 1;

while count > 1
    if mod(count, retirada_max + 1) == 1
        break
    end
    count = count - 1;
end

count = palitos_restantes - count;

if count > retirada_max
    count = randi(retirada_max);
end

n_retirados = count;