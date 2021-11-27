
%1(a)
n_1 = 1:30;
x_1 = [116.000000,213.000000,35.000000,-220.000000,-576.000000,-598.000000,-288.000000,-112.000000,-78.000000,223.000000,236.000000,180.000000,111.000000,-89.000000,-289.000000,-425.000000,-550.000000,-595.000000,-224.000000,74.000000,328.000000,695.000000,622.000000,647.000000,545.000000,-41.000000,-561.000000,-560.000000,-168.000000,322.000000 ];

figure %1
plot(n_1,x_1);
xlabel('n');
ylabel('x[n]');
title('Plot of x[n] vs n');

%1(b)
n_1_pi = linspace(-pi,pi,30);
X_1 = fft(x_1);
X_1_abs = abs(X_1);
X_1_shift = fftshift(X_1_abs);

figure %2
plot(n_1_pi,X_1_shift);
xlabel('\omega');
ylabel('X(exp(j\omega))');
title('Plot of the magnitude of the fft output vs frequency w');


h = fir1(28, 6/24);
fliplr(h)

y = conv(x_1,h);
figure %1
plot(y);
xlabel('n');
ylabel('y[n]');
title('Plot of y[n] vs n');
