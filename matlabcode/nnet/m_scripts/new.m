%Info message
InfoMessage = sprintf(['\nScript: new.m\n' ...
'Location: ../m_scripts\n']);
%Show info message
fprintf(InfoMessage);



%Предсказание положения УСП

FlagPlot0 = false;
FlagPlot1 = false;
FlagPlot2 = true;
FlagPlot3 = true;

N = length(X); % number of samples
Nu = 8000; % number of learning samples
Np = 1000; % number of predicted samples

if FlagPlot0
	plot(X(1:Nu+Np), 'm-')
	grid on
	hold on
	plot(X(1:Nu), 'b')
	plot(X(1:Nu+Np), '+k', 'markersize', 2)
	legend('validation data', 'training data', ...
	'sampling markers', 'location', 'southwest')
	xlabel('Time, t(steps)')
	ylabel('Suz position, X')
	ylim([-min(X)*0.7 max(X)*1.5])
	set(gcf, 'position', [1 60 800 600])
end

Xt = con2seq(X(1:Nu)');
Xv = con2seq(X(Nu + 1:end)');

%inputDelays = 1:10;
%hiddenSizes = [20, 10];
%trainFcn = 'trainbr';

inputDelays = 1:10;
hiddenSizes = [20, 10];
trainFcn = 'trainbr';

nar_net = narnet(inputDelays, hiddenSizes, 'open', trainFcn);

[Xs, Xi, Ai, Ts] = preparets(nar_net, {}, {}, Xt);
nar_net = train(nar_net, Xs, Ts, Xi, Ai);
%nar_net = closeloop(nar_net);

%[Ai, Ab, Ac] = preparets(nar_net, {}, {}, Xv);

[Xo, Xio, Aio, To] = preparets(nar_net, {}, {}, Xt);
[Y1, Xfo, Afo] = nar_net(Xo, Xio, Aio);
[nn, Xic, Aic] = closeloop(nar_net, Xfo, Afo);
[Y2, Xfc, Afc] = nn(cell(0, Np), Xic, Aic);

e = cell2mat(Xv(1:Np)) - cell2mat(Y2);
M = Nu + Np;

if FlagPlot1
	figure(1)
	plot(Nu + 1:M, cell2mat(Y2), 'r')
	plot(Nu + 1:M, e, 'g')
	legend('validation data', 'training data', ...
	'sampling markers', 'prediction', 'error', ...
	'location', 'southwest')
end

if FlagPlot2
	figure(2)
	plot(Nu + 1:M, X(Nu + 1:M))
	hold on
	plot(Nu + 1:M, cell2mat(Y2))
end

if FlagPlot3
	figure(3)
	plot(Nu + 1:M, abs(e')./X(Nu + 1:M)*100.0)
end