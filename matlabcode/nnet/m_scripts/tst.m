close all, clear all, clc, format compact

N = 700;
Nu = 300;

b = 0.1;
c = 0.2;
tau = 17;

y = [ ...
0.9697 0.9699 0.9794 1.0003 1.0319 1.0703 1.1076 ... 
1.1352 1.1485 1.1482 1.1383 1.1234 1.1072 1.0928 ...
1.0820 1.0756 1.0739 1.0759 ...
]';

for n = 18:N + 99
	y(n + 1) = y(n) - b*y(n) + c*y(n - tau)/(1 + y(n - tau).^10);
end

y(1:100) = [];

plot(y, 'm-')
grid on
hold on
plot(y(1:Nu), 'b')
plot(y, '+k', 'markersize', 2)
legend('validation data', 'training data', 'sampling markers', ...
'location', 'southwest')
xlabel('time (steps)')
ylabel('y')
ylim([-0.5 1.5])
set(gcf, 'position', [1 60 800 400])

yt = con2seq(y(1 : Nu)');
yv = con2seq(y(Nu + 1 : end)');

inputDelays = 1:6:19;
hiddenSizes = [6 3];

net = narnet(inputDelays, hiddenSizes);

[Xs, Xi, Ai, Ts] = preparets(net, {}, {}, yt);

net = train(net, Xs, Ts, Xi, Ai);
view(net);

net = closeloop(net);
view(net);

yini = yt(end - max(inputDelays) + 1 : end);
[Xs, Xi, Ai] = preparets(net, {}, {}, [yini yv]);

predict = net(Xs, Xi, Ai);

Yv = cell2mat(yv);
Yp = cell2mat(predict);

e = Yv - Yp;

figure(1)
plot(Nu + 1 : N, Yp, 'r')
plot(Nu + 1 : N, e, 'g')
legend('validation data', 'training data', 'sampling markers', ...
'prediction', 'error', 'location', 'southwest')
