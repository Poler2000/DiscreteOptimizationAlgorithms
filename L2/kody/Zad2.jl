# Paweł Polerowicz 254626

using JuMP
using GLPK
using LinearAlgebra

f = open("data2b.txt", "r")

nStr = readline(f)
mStr = readline(f)

n = parse(Int64, nStr)
m = parse(Int64, mStr)

C = zeros(n, n)
T = zeros(n, n)

for i in 1:m
    s = readline(f)
    println(s)
    path = parse.(Int32, split(s))
    println(path)
    x = path[1]
    y = path[2]
    C[x, y] = path[3]
    T[x, y] = path[4]
end

sStr = readline(f)
dStr = readline(f)
tmaxStr = readline(f)

s = parse(Int64, sStr)
d = parse(Int64, dStr)
tmax = parse(Int64, tmaxStr)

println("c:")
display(C)
println("t:")
display(T)

shortest_path = Model(GLPK.Optimizer)

@variable(shortest_path, x[1:n, 1:n] >= 0)
#@variable(shortest_path, x[1:n, 1:n], Bin)

@constraint(shortest_path, [i = 1:n, j = 1:n; C[i, j] == 0], x[i, j] == 0)

@constraint(
    shortest_path,
    [i = 1:n; i != s && i != d],
    sum(x[i, :]) == sum(x[:, i])
)

@constraint(shortest_path, sum(x[s, :]) - sum(x[:, s]) == 1)

@constraint(shortest_path, sum(x[d, :]) - sum(x[:, d]) == -1)

@constraint(shortest_path, sum(T[i,j]*x[i,j] for i in 1:n,j in 1:n) <= tmax)
@objective(shortest_path, Min, LinearAlgebra.dot(C, x))

optimize!(shortest_path)
@show objective_value(shortest_path)
objective_value(shortest_path)
display(value.(x))
