# Paweł Polerowicz 254626

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

println(companiesMaxSupply)
println(airportDemands)

close(f)

@variable(model, x[1:airports,1:companies] >= 0)

@constraint(model, ones(Int32,1,airports) * x .<= companiesMaxSupply)
@constraint(model, ones(1,companies) * x' .== airportDemands)
@objective(model, Min, sum(c[i,j]*x[i,j] for i in 1:airports,j in 1:companies))

print(model)
optimize!(model)
@show termination_status(model)
@show primal_status(model)
@show dual_status(model)
@show objective_value(model)

for j in 1:3
    for i in 1:4
        xval  = value(x[i, j])
        println("company: $j, airport: $i, value = $xval")
    end
end
