clc;
close all;
clear variables;

set(groot,'defaulttextinterpreter','latex');  
set(groot, 'defaultAxesTickLabelInterpreter','latex');  
set(groot, 'defaultLegendInterpreter','latex');
%% Parameters
max_iter = 100;
swarm_size = 1000;
w = 0.1;
c1 = 2;
c2 = 3;
%% Init
A = [1, 5, 1]';
B = [3, 2, 0]';
C = [5, 6, 1]';
D = [6, 3, 3]';

domain_max = max([A, B, C, D], [], 2);
domain_min = min([A, B, C, D], [], 2);

range = domain_max - domain_min;

% v_max = 0.1 * range;
v_max = 0.3;

S1 = generate_random_swarm(swarm_size, domain_min, domain_max);
S2 = generate_random_swarm(swarm_size, domain_min, domain_max);

X = [S1; S2];
X_prev = X;

p_best = X;

v_prev = zeros(size(X), 'double');

F_opt = f_opt(X, A, B, C, D);
[min_f_opt, argmin_f_opt] = min(F_opt);
g_best = X(:, argmin_f_opt);
f_opt_best = min_f_opt;

f_best_log = zeros(max_iter, 1, 'double');

for i = 1:max_iter
    % calc v
    v = w * v_prev + c1 * rand() * (p_best - X_prev) + c2 * rand() * (g_best - X_prev);
    
    % limit v

%     v(v > v_max) = v_max;
%     v(v < -v_max) = - v_max;
    
    for j = 1:length(v_max)
        v(j, v(j, :) > v_max(j)) = v_max(j);
        v(j + 3, v(j + 3, :) > v_max(j)) = v_max(j);

        v(j, v(j, :) < -v_max(j)) = -v_max(j);
        v(j + 3, v(j + 3, :) < -v_max(j)) = -v_max(j);    
    end
    
    % update
    X = X_prev + v;
    
    % observe f_opt
    F_opt = f_opt(X, A, B, C, D);
    [min_f_opt, argmin_f_opt] = min(F_opt);
    
    % update swarm best solution
    if min_f_opt < f_opt_best
        f_opt_best = min_f_opt;
        g_best = X(:, argmin_f_opt);
    end
    
    % update particle best solution
    p_best(F_opt < f_opt(p_best, A, B, C, D)) = X(F_opt < f_opt(p_best, A, B, C, D));

    % update prev
    X_prev = X;
    v_prev = v;

    f_best_log(i) = f_opt_best;
end

figure
plot(sqrt(f_best_log))
title('Najmanja vrednost $f_{opt}(x)$ za svaku generaciju')
xlabel('Generacija [num]')
ylabel('$f_{opt}(x)$')

fprintf('S1 = (%f, %f, %f)\nS2 = (%f, %f, %f)\n', g_best(1:3), g_best(4:6))
fprintf('Minimalna duzina puta = %f\n', sqrt(f_opt_best))

points = [A, B, C, D, g_best(1:3), g_best(4:6)];

figure
scatter3(points(1, :), points(2, :), points(3, :));
hold on;
delta = 0.2;
textscatter3(points(1, :) - delta, points(2, :) - delta, points(3, :) - delta,{'A', 'B', 'C', 'D', 'S1', 'S2'});
%
lines = [1, 5; 2, 5; 3, 6; 4, 6; 5, 6];
for i = 1:length(lines)
    plot3([points(1, lines(i, 1)), points(1, lines(i, 2))],...
          [points(2, lines(i, 1)), points(2, lines(i, 2))],...
          [points(3, lines(i, 1)), points(3, lines(i, 2))]);
end
title('Tačke u prostoru')
xlabel('x')
ylabel('y')
zlabel('z')
%% Utils
function F_opt = f_opt(X, A, B, C, D)
    F_opt = dist_sqrd(X(1:3, :), A) + ...
            dist_sqrd(X(1:3, :), B) + ...
            dist_sqrd(X(1:3, :), X(4:6, :)) + ...
            dist_sqrd(X(4:6, :), C) + ...
            dist_sqrd(X(4:6, :), D);
end

function S = generate_random_swarm(swarm_size, domain_min, domain_max)
    S = rand(length(domain_min), swarm_size) .* (domain_max - domain_min) + domain_min;
end

function d = dist_sqrd(A, B)
    d = sum((A - B).^2);
end