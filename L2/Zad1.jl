using JuMP
using GLPK
model = Model(GLPK.Optimizer)

f = open("data1.txt", "r")

line = 0

companiesStr = readline(f)
airportsStr = readline(f)

companies = parse(Int64, companiesStr)
airports = parse(Int64, airportsStr)

companiesMaxSupply = ones(1 ,companies)
airportDemands = ones(1, airports)
c = ones(Int32, airports, companies)

for i in 1:companies
    s = readline(f)
    companiesMaxSupply[i] = parse(Int32, s)
end

for i in 1:airports
    s = readline(f)
    airportDemands[i] = parse(Int32, s)
end

for i in 1:airports
    s = readline(f)
    n = parse.(Int32, split(s))
    for j in 1:companies
        c[i, j] = n[j]
    end
end
println(n)
println(companiesMaxSupply)
println(airportDemands)

y = [
    1 2 3;
    4 5 6;
    7 8 9;
    10 11 12;
]

close(f)
@variable(model, x[1:4,1:3] >= 0)

@constraint(model, ones(Int32,1,airports) * x .<= companiesMaxSupply)
@constraint(model, ones(1,companies) * x' .== airportDemands)
@objective(model, Min, sum(c[i,j]*x[i,j] for i in 1:airports,j in 1:companies))

#@variable(model, x[companies:airports] >= 0)
#@constraint(model, A * x .== b)
#@objective(model, Min, c' * x)
#=
@variable(model, 0 <= x1)
@variable(model, 0 <= y1)
@variable(model, 0 <= z1)

@variable(model, 0 <= x2)
@variable(model, 0 <= y2)
@variable(model, 0 <= z2)

@variable(model, 0 <= x3)
@variable(model, 0 <= y3)
@variable(model, 0 <= z3)

@variable(model, 0 <= x4)
@variable(model, 0 <= y4)
@variable(model, 0 <= z4)

@objective(model, Min, 10x1 + 7y1 + 8z1 + 10x2 + 11y2 + 14z2 + 9x3 + 12y3 + 4z3 + 11x4 + 13y4 + 9z4)

@constraint(model, c1, x1 + x2  + x3 + x4 <= 275000)
@constraint(model, c2, y1 + y2  + y3 + y4 <= 550000)
@constraint(model, c3, z1 + z2  + z3 + z4 <= 660000)

@constraint(model, c4, x1 + y1 + z1 == 110000)
@constraint(model, c5, x2 + y2 + z2 == 220000)
@constraint(model, c6, x3 + y3 + z3 == 330000)
@constraint(model, c7, x4 + y4 + z4 == 440000)
=#

print(model)
optimize!(model)
@show termination_status(model)
@show primal_status(model)
@show dual_status(model)
@show objective_value(model)

#=
@show value(x1)
@show value(x2)
@show value(x3)
@show value(x4)

@show value(y1)
@show value(y2)
@show value(y3)
@show value(y4)

@show value(z1)
@show value(z2)
@show value(z3)
@show value(z4)
=#
for j in 1:3
    for i in 1:4
        @show value(x[i, j])
    end
end
