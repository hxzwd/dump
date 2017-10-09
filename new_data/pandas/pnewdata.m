Files = { 'P_34-33.csv', 'Of_36-33.csv', 'Of_40-31.csv' };
Files0 = { 'P_44-23.csv', 'Of_46-27.csv', 'Of_50-21.csv' };

A0 = readtable(Files{1});
B0 = readtable(Files{2});
C0 = readtable(Files{3});

P = cell2mat(table2cell(A0( : , 2)));
Of = cell2mat(table2cell(B0( :, 2)));
Of_ = cell2mat(table2cell(C0( :, 2)));

P = P(1:end,:);
Of = Of(1:end,:);

N = length(P);
Ind = 0:1:N - 1;
Minutes = N*10;
Hours = Minutes/60.0;
Time = 0:Hours/N:Hours;
Time = Time(1,1:end-1);

