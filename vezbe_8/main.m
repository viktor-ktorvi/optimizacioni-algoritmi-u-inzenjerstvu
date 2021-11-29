clc;
close all;
clear variables;
%% Params
N = 20;
pop_size = 2000;
gen_num = 50;
parent_num = 400;
mutate_gene_p = 0.1;
mutation_p = 0.01;
opponent_num = 5;
%% Init
% rng(4)
s = load("Z7.txt");
s = reshape(s, length(s), 1);

best_f_opts = zeros(N, 1);
all_cumulative_fs = zeros(gen_num, N);
if isempty(gcp('nocreate'))
    parpool(feature('numcores'));
end
%%

figure
hold on;

tic
parfor run = 1:N
    parent_x = zeros(length(s), parent_num);
    f_progress = zeros(gen_num, 1);
    f_cumulative = zeros(gen_num, 1);

    x = randi(2, length(s), pop_size) - 1;
    
    F = f_opt(s, x);
    
    
    for g = 1:gen_num
        % Selection Tournament
        
        parent_buffer = zeros(parent_num, 1);
        for i = 1:parent_num
            opponent_index = randi(pop_size, opponent_num, 1);
            while sum(ismember(opponent_index, parent_buffer)) > 0
                opponent_index = randi(pop_size, opponent_num, 1);
            end
    
            [~, argmin] = min(F(opponent_index));
            parent_x(:, i) = x(:, opponent_index(argmin));
            parent_buffer(i) = opponent_index(argmin);
        end
        
        % Crossing
        
        for i = 1:pop_size
            couple_index = randi(parent_num, 2, 1);
            while couple_index(1) == couple_index(2)
                couple_index = randi(parent_num, 2, 1);
            end
        
            cross_bit_index = randi(length(s), 1);
        
            x(1:cross_bit_index, i) = parent_x(1:cross_bit_index, couple_index(1));
            x(cross_bit_index + 1:end, i) = parent_x(cross_bit_index + 1:end, couple_index(2));
        
            % Mutation
            if rand < mutation_p
                m = rand(length(s), 1) < mutate_gene_p;
                x(:, i) = xor(x(:, i), m);
            end
        
        end
        
        F = f_opt(s, x);
        f_progress(g) = min(F);
        f_cumulative(g) = min(f_progress(1:g));
    %     if f_progress(g) < satisfactory
    %         break
    %     end
    end
    
    
%     fprintf("Najbolja vrednost optimizacione funkcije = %.0f\n", f_cumulative(end));
%     plot(f_cumulative)
    all_cumulative_fs(:, run) = f_cumulative;
    best_f_opts(run) = f_cumulative(end);
end
toc

fprintf("Srednje najbolje resenje = %.2f\n", mean(best_f_opts));
plot(all_cumulative_fs)
title('Cumulative minumum')
xlabel('Generation [num]')
ylabel('cumulative f min')
set(gca, 'YScale', 'log')
set(gca, 'XScale', 'log')


function F = f_opt(s, x)
    F = 2^26 - x' * s;

    F(F < 0) = 2^26;
end

