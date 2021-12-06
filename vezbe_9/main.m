clc;
close all;
clear variables;

set(groot,'defaulttextinterpreter','latex');  
set(groot, 'defaultAxesTickLabelInterpreter','latex');  
set(groot, 'defaultLegendInterpreter','latex');
%% Loading
s = load("Z9.csv");
s = reshape(s, length(s), 1);

R0 = 15;
N = length(s);
i = (0:N-1)';
x = R0 * cos(2*pi/N * i);
y = R0 * sin(2*pi/N * i);

%% Parameters

pop_size = 60;
F = 0.8;
cr = 0.9;
max_gen = 500;
f_generations = zeros(max_gen, 1);
f_max_val = 100;
%% Init
A1 = rand(pop_size, 1);
A2 = rand(pop_size, 1);

[xp1, yp1] = init_inside_circle(R0, pop_size);
[xp2, yp2] = init_inside_circle(R0, pop_size);

X = [xp1, yp1, xp2, yp2, A1, A2];

%% Differential evolution
tic
for counter = 1:max_gen
    R = randi(pop_size);
    
    f_gen_min = f_max_val;
    for i = 1:pop_size
        sample_space = 1:pop_size;
        sample_space(i) = [];
    
        abc = num2cell(randsample(sample_space, 3));
        [a, b, c] = abc{:};
        
        z = X(a, :) + F * (X(b, :) - X(c, :));
    
        if i == R || rand < cr
            fz = f_opt(x, y, s, z(1), z(2), z(3), z(4), z(5), z(6), R0);
            fx = f_opt(x, y, s, X(i, 1), X(i, 2), X(i, 3), X(i, 4), X(i, 5), X(i, 6), R0);
            if fz < fx
                X(i, :) = z;
            end

            if min(fz, fx) < f_gen_min
                f_gen_min = min(fz, fx);
            end
        end
    end

    f_generations(counter) = f_gen_min;
end
toc

f_min = f_max_val;
x_solution = zeros(1, size(X, 2));
for i = 1:pop_size
    fi = f_opt(x, y, s, X(i, 1), X(i, 2), X(i, 3), X(i, 4), X(i, 5), X(i, 6), R0);
    if  fi < f_min
        f_min = fi;
        x_solution = X(i, :);
    end
end
%% Plot
% figure
% plot(f_generations);
% title('Smallest $f(x)$')
% xlabel('Generation [num]')
% ylabel('$f_{min}(x)$')
% set(gca, 'YScale', 'log')
% set(gca, 'XScale', 'log')

f_min
fprintf("(xp1, yp1) = (%f, %f)\n(xp2, yp2) = (%f, %f)\nA1 = %f\nA2 = %f\n", x_solution);

%% Utils

function S = signal_strength(x, y, A, xp, yp)
    S = A./sqrt((x - xp).^2 + (y - yp).^2);
end

function F = f_opt(x, y, s, xp1, yp1, xp2, yp2, A1, A2, R0)
    global f_max_val;
    if (xp1^2 + yp1^2 < R0^2) && (xp2^2 + yp2^2 < R0^2)
        F = sum((signal_strength(x, y, A1, xp1, yp1) + signal_strength(x, y, A2, xp2, yp2) - s).^2);
    else
        F = f_max_val;
    end

end

function [xp, yp] =  init_inside_circle(R, pop_size)
    
    xp = zeros(pop_size, 1);
    yp = zeros(pop_size, 1);

    counter = 1;
    while counter <= pop_size
        xp_candidate = 2 * R * (rand() - 0.5);
        yp_candidate = 2 * R * (rand() - 0.5);
    
        if xp_candidate^2 + yp_candidate^2 < R^2
            
            xp(counter) = xp_candidate;
            yp(counter) = yp_candidate;
            
            counter = counter + 1;
        end
    end
end