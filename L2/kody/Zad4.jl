# Paweł Polerowicz 254626

using JuMP
using GLPK
using LinearAlgebra

f = open("data4b.txt", "r")

nStr = readline(f)
mStr = readline(f)
cStr = readline(f)
kStr = readline(f)

n = parse(Int64, nStr)
m = parse(Int64, mStr)
c = parse(Int64, cStr)
k = parse(Int64, kStr)

G = zeros(n, m)

for i in 1:c
    s = readline(f)
    cont = parse.(Int32, split(s))
    j = cont[1]
    i = cont[2]
    G[i, j] = 1
end

display(G)

shortest_path = Model(GLPK.Optimizer)

@variable(shortest_path, x[1:n, 1:m], Bin)
@constraint(shortest_path, [i = 1:n, j = 1:m; G[i, j] == 1], x[i, j] == 0)
@constraint(shortest_path, [i = 1:n, j = 1:m; G[i, j] == 1], (sum(x[u,j] for u in max((i-k), 1):min(n, i+k)) + sum(x[i,u] for u in max((j-k), 1):min(m, j+k))) >= 1)

@objective(shortest_path, Min, sum(x[i,j] for i in 1:n,j in 1:m))

optimize!(shortest_path)
@show termination_status(shortest_path)
#objective_value(shortest_path)
#display(value.(x))
