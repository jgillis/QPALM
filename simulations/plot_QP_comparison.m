function plot_QP_comparison( file )
%Helper function to plot results from simulation

load(file)
close all
figure

semilogy(n_values(1:length(Tqpalm_matlab)), Tqpalm_matlab, 'b',...
    n_values(1:length(Tqpalm_c)), Tqpalm_c, 'm',...
    n_values(1:length(Tosqp)), Tosqp, 'r',...
    n_values(1:length(Tqpoases)), Tqpoases, 'g',...
    n_values(1:length(Tgurobi)), Tgurobi, 'k');
grid on
legend('QPALM (Matlab)','QPALM (C)', 'OSQP', 'qpOASES','GUROBI','Location','southeast')

end

