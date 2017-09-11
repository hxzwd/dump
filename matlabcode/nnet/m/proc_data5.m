Files = { '../data/34-43_data.csv', '../data/36-43_data.csv' };

A = readtable(Files{1});
B = readtable(Files{2});

X = cell2mat(table2cell(A( : , 4 )));
Y = cell2mat(table2cell(B( : , 4 )));

T = 1:1:length(X);

x = tonndata(X, false, false);
y = tonndata(Y, false, false);

X_data = X;
Y_data = Y;
x_data = x;
y_data = y;

% 'trainlm'  | usually fastest
% 'trainbr'  | slow, may be better in some cases
% 'trainscg' | good with low amount of memory

trainFcn = 'trainbr';

inputDelays = 1:10;
feedbackDelays = 1:10;

hiddenLayerSize = 20;

L_tr = 5000;
L = length(x);
L_ts = L - L_tr;

x_tr = x(1:L_tr);
y_tr = y(1:L_tr);

x_ts = x(L_tr + 1:L);
y_ts = y(L_tr + 1:L);

