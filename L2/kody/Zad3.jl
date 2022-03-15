# Paweł Polerowicz 254626

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

@variable(model, l[i, j] <= x[i = 1:districts,j = 1:changes] <= u[i,j])

@constraint(model, ones(Int32,1, changes) * x .>= minCarsForDistrict)
@constraint(model, ones(Int32,1, districts) * x' .>= minCarsForChange)

@objective(model, Min, sum(x))


print(model)
optimize!(model)
@show termination_status(model)
@show primal_status(model)
@show dual_status(model)
@show objective_value(model)

display(value.(x'))
