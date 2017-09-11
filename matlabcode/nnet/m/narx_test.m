EnablePlot1 = false;


N = length(X);						% number of samples
Nu = 8000;							% number of learning samples

Np = 1000;							% number of predicted samples


if EnablePlot1
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

Xt = con2seq(X(1:Nu)');				%Положение УСП(обучение)
Xv = con2seq(X(Nu + 1:end)');		%Положение УСП(валидация)
Yt = con2seq(Y(1:Nu)');				%Показания ДКЭВ(обучение)
Yv = con2seq(X(Nu + 1:end)');		%Показания ДКЭВ(валидация)

inputDelays = 1:20;					%Задержка линии входа
feedbackDelays = 1:20;				%Задержка линии обратной связи
hiddenSizes = [20, 20];				%Параметры скрытых слоёв
trainFcn = 'trainbr';				%Функция обучения
L_hidden = length(hiddenSizes);
a = Yt;
b = Xt;
%a - обучающие показания ДКЭВ
%b - обучающие положения УСП
%-------------------------------------
hiddenSizes = [20, 10];
inputDelays = 1:15;
feedbackDelays = 1:10;
L_hidden = length(hiddenSizes);
trainFcn = 'trainlm';
%-------------------------------------
hiddenSizes = 30;
inputDelays = 1:20;
feedbackDelays = 1:20;
L_hidden = length(hiddenSizes);
trainFcn = 'trainbr';
%-------------------------------------
narx_net = narxnet(inputDelays, feedbackDelays, hiddenSizes, 'open', trainFcn);

%Настройка начальной инициализации нейронной сети
%narx_net.initFcn = 'initzero';
narx_net = init(narx_net);

[Xs, Xi, Ai, Ts] = preparets(narx_net, a, {}, b);
%{ 
narx_net.divideParam.trainRatio = 70/100;
narx_net.divideParam.valRatio = 15/100;
narx_net.divideParam.testRatio = 5/100; 
%}
info_string = sprintf(['Количество примеров: N = %d\n ' ...
	'Количество обучающих примеров: Nu = %d\n ' ...
	'Количество предсказываемых значений: Np = %d\n ' ...
	'Задержка линии входа[u(t)]: inputDelays = %d:%d\n ' ...
	'Задержка линии обратной связи[x(t)]: feedbackDelays = %d:%d\n ' ...
	'Количество скрытых слоёв: L_hidden = %d\n' ...
	'Функция обучения: trainFcn = %s\n'], ...
	N, Nu, Np, inputDelays(1), inputDelays(length(inputDelays)), ...
	feedbackDelays(1), feedbackDelays(length(feedbackDelays)), ...
	L_hidden, trainFcn);
narx_net = train(narx_net, Xs, Ts, Xi, Ai);

%naxr_net = closeloop(narx_net);
%[Ai, Ab, Ac] = preparets(nar_net, {}, {}, Xv);


[Xo, Xio, Aio, To] = preparets(narx_net, a, {}, b);
[Y1, Xfo, Afo] = narx_net(Xo, Xio, Aio);
[narx_nn, Xic, Aic] = closeloop(narx_net, Xfo, Afo);
[Y2, Xfc, Afc] = narx_nn(cell(0, Np), Xic, Aic);

M = Nu + Np;
e = cell2mat(Xv(1:Np)) - cell2mat(Y2);
abs_error = abs(e')./X(Nu + 1:M)*100.0;


%{
figure(1)
plot(Nu + 1:M, cell2mat(Y2), 'r')
plot(Nu + 1:M, e, 'g')
legend('validation data', 'training data', ...
'sampling markers', 'prediction', 'error', ...
'location', 'southwest')
%}

figure(2)
plot(Nu + 1:M, X(Nu + 1:M))
hold on
plot(Nu + 1:M, cell2mat(Y2))

figure(3)
plot(Nu + 1:M, abs_error)



%{
FigureNumber = 3;
Predicted = cell2mat(Y2);
TrueValues = X(Nu + 1:M);
AbsError = abs_error;
T = Nu + 1:M;

figure(FigureNumber)
plot(T, TrueValues, 'ro')
hold on
plot(T, Predicted, 'g+')


%}
