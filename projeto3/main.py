import pulp

def resolver_distribuicao_brinquedos(n, m, t, info_fabricas, info_paises, pedidos_criancas):
    # Criar o problema de otimização linear
    prob = pulp.LpProblem("Distribuicao_De_Brinquedos", pulp.LpMaximize)
    
    # Variáveis de decisão: x[k][i] = 1 se a criança k recebe o brinquedo da fábrica i
    x = pulp.LpVariable.dicts("x", (range(t), range(n)), cat='Binary')
    
    # Objetivo: Maximizar o número de crianças que recebem brinquedos
    prob += pulp.lpSum(x[k][i] for k in range(t) for i in range(n)), "Maximizar_Crianças_Satisfeitas"
    
    # Restrição 1: A capacidade de cada fábrica não pode ser excedida
    for i in range(n):
        prob += pulp.lpSum(x[k][i] for k in range(t)) <= info_fabricas[i][2], f"Capacidade_Fábrica_{i+1}"
    
    # Restrição 2: Cada criança pode receber no máximo um brinquedo
    for k in range(t):
        prob += pulp.lpSum(x[k][i] for i in range(n)) <= 1, f"Limite_Brinquedos_Criança_{k+1}"
    
    # Restrição 3: Cada país tem um limite máximo de exportação
    for j in range(m):
        prob += pulp.lpSum(x[k][i] for k in range(t) for i in range(n) if pedidos_criancas[k][1] == j+1) <= info_paises[j][1], f"Limite_Exportacao_Pais_{j+1}"
    
    # Restrição 4: Cada país tem um número mínimo de brinquedos a distribuir
    for j in range(m):
        prob += pulp.lpSum(x[k][i] for k in range(t) for i in range(n) if pedidos_criancas[k][1] == j+1) >= info_paises[j][2], f"Minimo_Brinquedos_Pais_{j+1}"
    
    # Resolver o problema
    prob.solve(pulp.PULP_CBC_CMD(msg=False))
    
    # Verificar se a solução é viável
    if pulp.LpStatus[prob.status] == 'Optimal':
        # Número de crianças satisfeitas
        return int(pulp.value(prob.objective))
    else:
        return -1


def ler_input():
    # Ler os dados de entrada
    n, m, t = map(int, input().split())
    
    # Informações sobre fábricas
    info_fabricas = []
    for _ in range(n):
        i, j, fmax = map(int, input().split())
        info_fabricas.append((i, j, fmax))
    
    # Informações sobre países
    info_paises = []
    for _ in range(m):
        j, pmax, pmin = map(int, input().split())
        info_paises.append((j, pmax, pmin))
    
    # Informações sobre pedidos das crianças
    pedidos_criancas = []
    for _ in range(t):
        dados = list(map(int, input().split()))
        k = dados[0]
        pais = dados[1]
        brinquedos = dados[2:]
        pedidos_criancas.append((k, pais, brinquedos))
    
    return n, m, t, info_fabricas, info_paises, pedidos_criancas


# Função principal
if __name__ == "__main__":
    n, m, t, info_fabricas, info_paises, pedidos_criancas = ler_input()
    resultado = resolver_distribuicao_brinquedos(n, m, t, info_fabricas, info_paises, pedidos_criancas)
    print(resultado)

