using JuMP
using GLPK
model = Model(GLPK.Optimizer)

f = open("data3.txt", "r")

changesStr = readline(f)
districtsStr = readline(f)

changes = parse(Int64, changesStr)
districts = parse(Int64, districtsStr)

minCarsForChange = ones(1, changes)
minCarsForDistrict = ones(1, districts)

l = ones(Int32, changes, districts)

s = readline(f)
n = parse.(Int32, split(s))
for i in 1:changes
    minCarsForChange[i] = n[i]
end

s = readline(f)
n = parse.(Int32, split(s))
for i in 1:districts
    minCarsForDistrict[i] = n[i]
end

for i in 1:districts
    s = readline(f)
    n = parse.(Int32, split(s))
    for j in 1:changes
        l[i, j] = n[j]
    end
end

u = ones(Int32, changes, districts)

for i in 1:districts
    s = readline(f)
    n = parse.(Int32, split(s))
    for j in 1:changes
        u[i, j] = n[j]
    end
end

println(l)
println(u)

#@variable(model, x[1:districts,1:changes] >= 0)
@variable(model, l[i, j] <= x[i = 1:districts,j = 1:changes] <= u[i,j])

@constraint(model, ones(Int32,1, changes) * x .>= minCarsForDistrict)
@constraint(model, ones(Int32,1, districts) * x' .>= minCarsForChange)

@objective(model, Min, sum(x))

#=
@variable(model, 2 <= z1p1 <= 3)
@variable(model, 4 <= z2p1 <= 7)
@variable(model, 3 <= z3p1 <= 5)

@variable(model, 3 <= z1p2 <= 5)
@variable(model, 6 <= z2p2 <= 7)
@variable(model, 5 <= z3p2 <= 10)

@variable(model, 5 <= z1p3 <= 8)
@variable(model, 7 <= z2p3 <= 12)
@variable(model, 6 <= z3p3 <= 10)

@objective(model, Min, z1p1 + z2p1 + z3p1 + z1p2 + z2p2 + z3p2 + z1p3 + z2p3 + z3p3)

@constraint(model, c1, z1p1 + z1p2 + z1p3 >= 10)
@constraint(model, c2, z2p1 + z2p2 + z2p3 >= 20)
@constraint(model, c3, z3p1 + z3p2 + z3p3 >= 18)

@constraint(model, c4, z1p1 + z2p1 + z3p1 >= 10)
@constraint(model, c5, z1p2 + z2p2 + z3p2 >= 20)
@constraint(model, c6, z1p3 + z2p3 + z3p3 >= 13)
=#
print(model)
optimize!(model)
@show termination_status(model)
@show primal_status(model)
@show dual_status(model)
@show objective_value(model)
#=
@show value(z1p1)
@show value(z1p2)
@show value(z1p3)

@show value(z2p1)
@show value(z2p2)
@show value(z2p3)

@show value(z3p1)
@show value(z3p2)
@show value(z3p3)
=#
