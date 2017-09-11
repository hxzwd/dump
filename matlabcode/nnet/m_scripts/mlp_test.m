
FlagAbsErrorPlotTrain = false;
FlagAbsErrorPlotTest = false;
FlagAbsErrorPlotClosedLoop = true;
FlagValuesPlotTrain = false;
FlagValuesPlotTest = false;
FlagValuesPlotClosedLoop = false;

net = newff(P_inputs_train, P_outputs_train, [20 15 5 2], {'tansig', 'tansig', 'tansig', 'tansig', 'purelin'}, 'trainlm');
net = train(net, P_inputs_train, P_outputs_train);

P_nnout_test = net(P_inputs_test);
P_nnout_train = net(P_inputs_train);

Abs_error_test = abs(P_nnout_test - P_outputs_test)./P_outputs_test*100.0;
Abs_error_train = abs(P_nnout_train - P_outputs_train)./P_outputs_train*100.0;

P_nnout_closed_loop = [];
Inputs_closed_loop = P_inputs_train(:,end);

for n = 1:N_test
	tmp = net(Inputs_closed_loop);
	P_nnout_closed_loop = [P_nnout_closed_loop tmp];
	Inputs_closed_loop = Inputs_closed_loop(2:end);
	Inputs_closed_loop = [Inputs_closed_loop; tmp]; 
end

Abs_error_closed_loop = abs(P_nnout_closed_loop - P_outputs_test)./P_outputs_test*100.0;

M = N_train + N_test;
T_train = 1:1:N_train;
T_test = N_train + 1:1:M;

if FlagAbsErrorPlotTrain
	FigAbsErrorPlotTrain = figure;
	plot(T_train, Abs_error_train)
end

if FlagAbsErrorPlotTest
	FigAbsErrorPlotTest = figure;
	plot(T_test, Abs_error_test)
end

if FlagValuesPlotTrain
	FigValuesPlotTrain = figure;
	hold on;
	plot(T_train, P_outputs_train, '+r', 'markersize', 2)
	plot(T_train, P_nnout_train, 'xg', 'markersize', 2)
end

if FlagValuesPlotTest
	FigValuesPlotTest = figure;
	hold on;
	plot(T_test, P_outputs_test, '+r', 'markersize', 2)
	plot(T_test, P_nnout_test, 'xg', 'markersize', 2)
end

if FlagAbsErrorPlotClosedLoop
	FigAbsErrorPlotClosedLoop = figure;
	plot(T_test, Abs_error_closed_loop)
end

if FlagValuesPlotClosedLoop
	FigValuesPlotClosedLoop = figure;
	plot(T_test, P_outputs_test, '+r', 'markersize', 2)
	plot(T_test, P_nnout_closed_loop, 'xg', 'markersize', 2)
end
