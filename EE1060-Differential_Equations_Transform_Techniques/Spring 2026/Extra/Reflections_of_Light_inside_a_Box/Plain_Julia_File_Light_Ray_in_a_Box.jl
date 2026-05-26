using Plots
using IrrationalConstants

function find_next_point(x_1::BigFloat, y_1::BigFloat, current_slope::BigFloat, current_side::Int64)

    # side: 1--bottom, 2--top, 3--left, 4--right
    # (x_2 - x_1) / (y_2 - y_1) = inv_slope

    slope = current_slope # reflection
    inv_slope = 1 / slope
    x_2 = BigFloat(0.0)
    y_2 = BigFloat(0.0)

    found_side = false
    side = 0

    if !found_side && (current_side != 1)
        # check bottom: side = 1
        y_2 = BigFloat(0.0)
        x_2 = inv_slope * (y_2 - y_1) + x_1
        if (x_2 >= 0.0) && (x_2 <= 1.0)
            found_side = true
            side = 1
        end
    end

    if !found_side && (current_side != 2)
        #top
        y_2 = BigFloat(1.0)
        x_2 = inv_slope * (y_2 - y_1) + x_1
        if (x_2 >= 0.0) && (x_2 <= 1.0)
            found_side = true
            side = 2
        end
    end

    if !found_side && (current_side != 3) #left
        x_2 = BigFloat(0.0)
        y_2 = slope * (x_2 - x_1) + y_1
        if (y_2 >= 0.0) && (y_2 <= 1.0)
            found_side = true
            side = 3
        end
    end

    if !found_side && (current_side != 4)
        #right
        x_2 = BigFloat(1.0)
        y_2 = slope * (x_2 - x_1) + y_1
        if (y_2 >= 0.0) && (y_2 <= 1.0)
            found_side = true
            side = 4
        end
    end

    @assert(found_side == true)
    @assert(side > 0)

    return x_2, y_2, -slope, side

end

N = 100; # number of reflections
# γ = 1.0/BigFloat(π);
# γ = BigFloat(3/7);
γ = BigFloat(sqrt2);

x_array = Vector{BigFloat}(undef, N)
y_array = Vector{BigFloat}(undef, N)

x_array[1] = BigFloat(0.5)
y_array[1] = BigFloat(0.0)
side = 1; # bottom

slope = γ;


for n = 2:N
    (x_out, y_out, slope_out, side_out) = find_next_point(x_array[n-1], y_array[n-1], slope, side)
    x_array[n] = x_out
    y_array[n] = y_out
    global slope = slope_out
    global side = side_out
end

#=
plot(Float64.(x_array), Float64.(y_array), 
    legend=:false, aspect_ratio=:equal,
    xlims = (0.0,1.0), ylims=(0.0,1.0),
    ticks=:none, showaxis=false, 
    )
=#

anim = @animate for frame_num in 2:N
                    l = frame_num;
                    # @show frame_num # how many frames have been processed?
                    plot(Float64.(x_array[1:l-1]), Float64.(y_array[1:l-1]),
                        seriescolor=:orchid2, 
                        legend=:false, aspect_ratio=:equal,
                        xlims = (0.0,1.0), ylims=(0.0,1.0),
                        ticks=:none, showaxis=false);
                    plot!(Float64.(x_array[l-1:l]), Float64.(y_array[l-1:l]));
                    plot!([0.0, 1.0, 1.0, 0.0, 0.0], [0.0, 0.0, 1.0, 1.0, 0.0], 
                        seriescolor=:black, linewidth=2);
                end

gif(anim,"anim.gif",fps=4)