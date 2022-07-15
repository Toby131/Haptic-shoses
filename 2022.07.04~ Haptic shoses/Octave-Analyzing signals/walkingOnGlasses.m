glassFile = 'loudly broken.wav';

[x,fs] = audioread(glassFile);


subplot(211)
plot(x)
xlabel('Sample Number')
ylabel('Amplitude')

%Ts = 1/50;
%t = 0:Ts:10-Ts;  

subplot(212)     
%plot(t,x)
y = fft(x);   
%fs = 1/Ts;
f = (0:length(y)-1)*fs/length(y);
xlabel('Time (seconds)')
ylabel('Amplitude')

x
f;
absY = abs(y);

plot(f,abs(y))
xlabel('Frequency (Hz)')
ylabel('Magnitude')
title('Magnitude')