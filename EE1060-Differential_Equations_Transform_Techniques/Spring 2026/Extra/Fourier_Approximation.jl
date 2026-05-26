using Plots, LaTeXStrings

### Function definitions 

# function to numerically integrate a signal over one time period 
# uses the trapezoidal method for integration
function integrate_over_time(h, t)
    # here 't' is the time axis and 'h' is the signal 
    # 'h' and 't' are arrays of same length 
    I = 0.0
    interval_size = t[2] - t[1]
    for k = 1:length(t)-1
        I += 0.5 * (h[k+1] + h[k])
    end
    I *= interval_size

    return I
end

# function for numerically computing the Fourier series coefficient of a given frequency 'n'
function compute_Fourier_coefficient(n, f, t, T)
    # compute the n^th Fourier coefficient of the signal f 
    complex_sinusoid_conjugate = exp.(-1im * 2 * pi * n * t / T)
    c_n = 1 / T * integrate_over_time(complex_sinusoid_conjugate .* f, t)

    # ignore very small values 
    tolerance = 1e-13
    if abs(real(c_n)) < tolerance
        c_n = 1im * imag(c_n)
    end
    if abs(imag(c_n)) < tolerance
        c_n = real(c_n)
    end
    return c_n
end

# function to compute the Fourier series coefficients
# from -N to +N 
function compute_all_Fourier_series_coeff(N, f, t, T)

    n_array = -N:1:N
    c_n_array = Vector{ComplexF64}(undef, length(n_array))
    for k in eachindex(n_array)
        n_k = n_array[k]
        c_n = compute_Fourier_coefficient(n_k, f, t, T)
        c_n_array[k] = c_n
    end

    return c_n_array
end

function partial_sum_Fourier_series(N, f, t, T)

    n_array = -N:1:N # set of frequencies
    c_n_array = compute_all_Fourier_series_coeff(N, f, t, T) # Fourier series coeff

    partial_sum = Vector{ComplexF64}(undef, length(t))
    fill!(partial_sum, 0.0 + 1im * 0.0)

    for k in eachindex(n_array)
        n_k = n_array[k]
        complex_sinusoid = exp.(1im * 2 * pi * n_k * t / T)
        partial_sum += c_n_array[k] * complex_sinusoid
    end

    return partial_sum

end

### Main part of the program: 


## defining the time axis
T = 2 * pi # period of the signal
step = 1e-5 * T # for sampling the continuous time signal
t = collect(range(-T / 2, T / 2, step=step)) # interval for one time period

## choose the signal 

# f = exp.(-t.^2); # Gaussian pulse

f = sign.(t); # square wave 

#. f = abs.(t); # triangular wave

# f = t # sawtooth wave

# alternating parabolas 
#=
f = Vector{Float64}(undef, length(t))
for k in eachindex(t)
	t_this = t[k];
	if t_this < 0 
		f[k] = (t_this + T/4)^2 - T^2/16;
	else 
		f[k] = -(t_this - T/4)^2 +T^2/16;
	end
end
=#

# bump function
#=
f = Vector{Float64}(undef, length(t))
for k in eachindex(t)
	x = t[k] / (3*T/8);
	if abs(x) < 1
		f[k] = exp.(1.0 / (x^2-1));
	else
		f[k] = 0.0;
	end
end
=#

## Plot the signal

plot(t, f, title="Signal in one period",
    label=L"f(t)", linewidth=2)
xlabel!(L"t")
ylabel!(L"f(t)")

## Plot signal across 5 consecutive periods 
f_periodic = [f[1:end-1]; f[1:end-1]; f[1:end-1]; f[1:end-1]; f]
t_periodic = zeros(length(f_periodic))
t_periodic[1] = -5 * T / 2
for i in 2:length(t_periodic)
    t_periodic[i] = t_periodic[i-1] + step
end
plot(t_periodic, f_periodic, title="Signal across 5 consecutive periods",
    label=L"f(t)", linewidth=2)
xlabel!(L"t")
ylabel!(L"f(t)")

## Plot the spectrum 
## absolute value of the Fourier series coefficients 
N = 7
c_n_array = compute_all_Fourier_series_coeff(N, f, t, T) # find c_n for n=-N:1:N
n_array = -N:1:N
plot(n_array, abs.(c_n_array), line=:stem, marker=:circle, xticks=-N:1:N, label=L"|c_n|")
xlabel!(L"n")
ylabel!(L"|c_n|")


## Plot the partial sum S_N(t)
N = 2
partial_sum = partial_sum_Fourier_series(N, f, t, T)
# let us ignore the imaginary parts of partial_sum (these will be very small values arising out of numerical finite precision effects)
# ignoring the imaginary part is okay if the original signal is real valued
partial_sum_real = real.(partial_sum)
plot(t, [partial_sum_real f], label=[L"s_N(t)" L"f(t)"], linewidth=2)
xlabel!(L"t")

## Plot the approximation error
N_array = 1:1:10 # values of N for which we want to find the approximation error
error_array = Vector{Float64}(undef, length(N_array))
for k in eachindex(N_array)
    N = N_array[k]
    partial_sum = partial_sum_Fourier_series(N, f, t, T)
    error_array[k] = integrate_over_time(abs.(f - partial_sum) .^ 2, t)
end
plot(N_array, error_array .^ (-1), legend=false)
# plot(N_array,error_array, yaxis=:log10, legend=false) # log-scale in y-axis
xlabel!(L"N")
ylabel!(L"\frac{1}{\Vert f - s_N \Vert_2^2}")