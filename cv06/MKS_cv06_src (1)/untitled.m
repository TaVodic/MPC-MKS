clear all; close all; clc;
m = csvread("ntc.csv");

r = m(:,2);
t = m(:,1);

ad = r./(r+10);

ad = ad .* 1024;

plot(ad, t, 'bx');
p = polyfit(ad, t, 10);

ad2 = 0:1023;
t2 = round(polyval(p, ad2), 1);
hold on, plot(ad2, t2, 'r');

dlmwrite('data.dlm', t2*10, ',');

