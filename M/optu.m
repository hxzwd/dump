A = [ ...
	1, 1, -2; ...
	2, -3, -2; ...
	8, 2, -7 ...
];

B = [ ...
	0, 0; ...
	1, 0; ...
	0, 1 ...
];

C = [ ...
	0, 1, 1; ...
	0, 1, -1 ...
];

Lambda = [ ...
	-3 -3 -3 ...
];

E = C';
Ev = [ ...
	1, 1; ...
	1, -1 ...
];
En = [0 0];
Iv = [ ...
	0, 1, 0; ...
	0, 0, 1 ...
];
In = [1 0 0];

syms q1 q2 o real;
syms s;
q = [q1; q2];

I = [1 0 0; 0 1 0; 0 0 1];

Wq = (s*I - A)^(-1)*B*q;

L = simplify(Wq*det((s*I - A)));
L1 = L(1);
L2 = L(2);
L3 = L(3);

Tmp = subs(L, [q1 q2], [1 1]);
Tmp1 = flip(sym2poly(Tmp(1)));
Tmp2 = flip(sym2poly(Tmp(2)));
Tmp3 = flip(sym2poly(Tmp(3)));


L1 = L1 + o*s^2 + o*s^1 + o;
L2 = L2 + o*s^2 + o*s^1 + o;
L3 = L3 + o*s^2 + o*s^1 + o;
L1_ = coeffs(L1, s);
L2_ = coeffs(L2, s);
L3_ = coeffs(L3, s);
l1 = subs(L1_, o, 0);
l2 = subs(L2_, o, 0);
l3 = subs(L3_, o, 0);

TMP = [l1; l2; l3];
l = TMP;

Su = [B, A*B, A^2*B];
detSu = det(Su(1:3, 1:3));

alpha = (In - En*Ev^(-1)*Iv)*(l')^(-1);
[N, D] = numden(alpha);
D = D(1);

Hs = poly2sym(poly(Lambda), s);
alpha_j = poly(Lambda);
alpha_j = flip(alpha_j(2:end));
F = coeffs(det(s*I - A), s);
F = F(1:end - 1);

Tmpq = solve(N*alpha_j' - N*F', q1);
Tmpqn = vpa(Tmpq);

qn1 = vpa(subs(Tmpq, q2, 1));
qn2 = 1;

qn = [qn1; qn2];

Ln = subs(l, [q1 q2], qn');


p = (Ev)^(-1)*Iv*(Ln')^(-1)*(alpha_j' - F');


P = qn*p';

