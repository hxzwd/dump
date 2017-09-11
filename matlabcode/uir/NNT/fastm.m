[pn1,minp1,maxp1,tn1,mint1,maxt1] = premnmx(X_2, Y_2);
%X = X(1:2,1:1000);
%Y = Y(1:2,1:1000);
X = X;
Y = Y;
[pn,minp,maxp,tn,mint,maxt] = premnmx(X, Y);
a = newff([-1, 1; -1, 1], [500, 2], {'tansig', 'purelin'}, 'trainlm', 'traingd', 'mse')
a = init(a);
b = train(a, pn, tn);

P = postmnmx(sim(b, pn), mint, maxt);
P1 = postmnmx(sim(b, pn1), mint1, maxt1);


ea = abs(P(1,:) - Y(1,:))./abs(Y(1,:))*100;
eb = abs(P(2,:) - Y(2,:))./abs(Y(2,:))*100;
oo = find(eb < 20000);
ebo = eb(oo);

ea1 = abs(P1(1,:) - Y_2(1,:))./abs(Y_2(1,:))*100;
eb1 = abs(P1(2,:) - Y_2(2,:))./abs(Y_2(2,:))*100;
oo1 = find(eb1 < 20000);
ebo1 = eb1(oo1);

