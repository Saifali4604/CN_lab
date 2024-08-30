EXPT 5

M = 16;
numSymbols = 1e5;
EbN0_db = 0:2:20;
EbN0 = EbN0_db - 10*log10(log2(M));
numSNR = length(EbN0_db);
SER = zeros(1,numSNR);
gainImabalance = 0.1;
phaseMismatch = 0.05;
dcOffsetI = 0.05;
dcOffsetQ = 0.05;
for i = 1:numSNR
   dataSymbols = randi([0 M-1], numSymbols, 1);
   modulatedSignal = qammod(dataSymbols, M, 'UnitAveragePower', true);
   I = real(modulatedSignal);
   Q = imag(modulatedSignal);
   recievedSignal = (1 + gainImabalance)*I + 1i*(1 - gainImabalance)*Q;
   recievedSignal = recievedSignal .* exp(1i * phaseMismatch);
   recievedSignal = recievedSignal + (dcOffsetI) + (1i * dcOffsetQ) ;
   recievedSignal = awgn(recievedSignal, EbN0_db(i), 'measured');
   demodulatedSignal = qamdemod(recievedSignal, M, 'UnitAveragePower', true);
   SER(i) = sum(dataSymbols ~= demodulatedSignal) / numSymbols ;
end
figure;
semilogy(EbN0, SER, 'b-o');
title('SER vs E_b/N_0 for 16-QAM with Receiver Impairments');
xlabel('Eb/N0 in db');
ylabel('Symbol Error Rate (SER)')
grid on;
fprintf('SNR(db)   SER\n');
fprintf('-------   ------');
for j = 1:numSNR
   fprintf('%8.2f   %e\n', EbN0_db(i), SER(i));
end
scatterplot(recievedSignal);
title('Received Signal Constellation with Receiver Impairments (SNR = 20 dB)');
grid on;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Expt 6


EbN0_db = 0:2:24;
EbN0 = 10.^(EbN0_db/10);
M_PSK = [2, 4, 8, 16, 32];
P_SER_PSK = zeros(length(M_PSK), length(EbN0));
for i = 1:length(M_PSK)
M = M_PSK(i);
P_SER_PSK(i,:) = 2 * qfunc(sqrt(2*EbN0*sin(pi/M)));
end
M_PAM = [2, 4, 8, 16];
P_SER_PAM = zeros(length(M_PAM), length(EbN0));

for i = 1:length(M_PAM)
M = M_PAM(i);
P_SER_PAM(i,:) = 2 *(M-1)/M * qfunc(sqrt(6*log2(M)/(M^2 - 1) * EbN0));
end
M_QAM = [4,16,64,256];
P_SER_QAM = zeros(length(M_QAM), length(EbN0));
for i = 1:length(M_QAM)
M = M_QAM(i);
P_SER_QAM(i,:) = 4 * (1 - 1/sqrt(M)) * qfunc(sqrt(3*log2(M)/(M-1) * EbN0))
end
M_MFSK = [2, 4, 8, 16, 32]; % M values for MFSK
P_SER_MFSK_coherent = zeros(length(M_MFSK), length(EbN0));
for i = 1:length(M_MFSK)
M = M_MFSK(i);
P_SER_MFSK_coherent(i, :) = qfunc(sqrt(2*EbN0*log2(M)/(M-1)));
end
P_SER_MFSK_noncoherent = zeros(length(M_MFSK), length(EbN0));
for i = 1:length(M_MFSK)
M = M_MFSK(i);
P_SER_MFSK_noncoherent(i, :) = exp(-(EbN0/2)) .* (((1+EbN0).^(M-1) - 1)./(M-1))
end
subplot(2,3,1)
for i=1:length(M_PSK)
semilogy(EbN0_db,P_SER_PSK(i,:),'-o'); hold on;
end
title('MPSK');
xlabel('Eb/N0 in db')
ylabel('SER');
grid on;
subplot(2,3,2)
for i=1:length(M_PAM)
semilogy(EbN0_db,P_SER_PAM(i,:),'-o'); hold on;
end
title('MPAM');
xlabel('Eb/N0 in db')
ylabel('SER');
grid on;

subplot(2,3,3)
for i=1:length(M_QAM)
semilogy(EbN0_db,P_SER_QAM(i,:),'-o'); hold on;
end
title('MQAM');
xlabel('Eb/N0 in db')
ylabel('SER');
grid on;

subplot(2,3,4)
for i=1:length(M_MFSK)
semilogy(EbN0_db,P_SER_MFSK_coherent(i,:),'-o'); hold on;
end
title('MFSK coherent');
xlabel('Eb/N0 in db')
ylabel('SER');
grid on;

subplot(2,3,5)
for i=1:length(M_MFSK)
semilogy(EbN0_db,P_SER_MFSK_noncoherent(i,:),'-o'); hold on;
end
title('MFSK noncoherent');
xlabel('Eb/N0 in db')
ylabel('SER');
grid on;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Expt 7


DSSS

M = 2;
numBits = 1e3;
chipRate = 10;
snr = 10;
fs = 1000;
dataBits = randi([0 1], numBits, 1);
modulatedSignal = dataBits*2 -1;
pnSequence = randi([0 1], numBits*chipRate, 1);
pnSequence = pnSequence*2 - 1;
spreadSignal = repelem(modulatedSignal,chipRate).*pnSequence;
recievedSignal = awgn(spreadSignal, snr, 'measured');
despreadSignal = recievedSignal .* pnSequence;
despreadBits = sum(reshape(despreadSignal, chipRate, numBits),1)' / chipRate;
recievedBits = despreadBits > 0;
BER_DSSS = sum(dataBits ~= recievedBits) / numBits;
n = length(spreadSignal);
frequencies = (-n/2 : n/2 -1) * (fs/n);
messageSpectrum = fftshift(fft(modulatedSignal,n));
pnSpectrum = fftshift(fft(pnSequence,n));
spreadSignalSpectrum = fftshift(fft(spreadSignal,n));
receivedSignalSpectrum = fftshift(fft(recievedSignal, n));
despreadSignalSpectrum = fftshift(fft(despreadSignal, n));
demodulatedSignalSpectrum = fftshift(fft(despreadBits, n));


figure;
subplot(3,2,1);
plot(frequencies, abs(messageSpectrum));
title('Message Signal Spectrum');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
grid on;

subplot(3,2,2);
plot(frequencies, abs(pnSpectrum));
title('PN Code Spectrum');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
grid on;

subplot(3,2,3);
plot(frequencies, abs(spreadSignalSpectrum));
title('Spread Signal Spectrum');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
grid on;

subplot(3,2,4);
plot(frequencies, abs(receivedSignalSpectrum));
title('Received Signal Spectrum');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
grid on;

subplot(3,2,5);
plot(frequencies, abs(despreadSignalSpectrum));
title('Despread Signal Spectrum');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
grid on;

subplot(3,2,6);
plot(frequencies, abs(demodulatedSignalSpectrum));
title('Demodulated Signal Spectrum (Before Decision Device)');
xlabel('Frequency (Hz)');
ylabel('Magnitude');
grid on;

FHSS

numBits = 20; % Number of bits
numHops = 6; % Number of frequency hops
hopFrequencies = [1, 2, 3, 4, 5, 6] * 1e3; % Frequencies in Hz
hopDuration = 1e-3; % Duration of each hop in seconds
snr = 10; % Signal-to-noise ratio in dB
fs = 20e3; % Sampling frequency in Hz

dataBits = randi([0 1], numBits, 1);
modulatedData = 2*dataBits - 1; % BPSK mapping (0 -> -1, 1 -> 1)
bpskSignal = repelem(modulatedData, hopDuration*fs); % Create rectangular wave
t = (0:1/fs:hopDuration-1/fs)';
fhssSignal = [];
hopSignal = [];
for i = 1:numBits
  hopIdx = mod(i-1, numHops) + 1;
  freq = hopFrequencies(hopIdx);
  carrier = cos(2*pi*freq*t);
  hopSignal = [hopSignal; carrier];
  fhssSignal = [fhssSignal; bpskSignal((i-1)*length(t)+1:i*length(t)) .* carrier];
end
receivedSignal = awgn(fhssSignal, snr, 'measured');
demodulatedSignal = [];
receivedBits = zeros(numBits, 1);
for i = 1:numBits
  hopIdx = mod(i-1, numHops) + 1;
  freq = hopFrequencies(hopIdx);
  carrier = cos(2*pi*freq*t);
  segment = receivedSignal((i-1)*length(t)+1:i*length(t));
  demodulated = segment .* carrier;
  demodulatedSignal = [demodulatedSignal; demodulated];
  receivedBits(i) = sum(demodulated) > 0;
end

figure;

subplot(3, 2, 1);
stem(dataBits, 'filled');
title('Original 20-bit Sequence');
xlabel('Bit Index');
ylabel('Bit Value');
grid on;
subplot(3,2,2);
plot(bpskSignal);
title('BPSK Modulated Signal (Rectangular Wave)');
xlabel('Sample Index');
ylabel('Amplitude');
grid on;

subplot(3, 2, 3);
plot(hopSignal);
title('Spread Signal with 6 Frequencies');
xlabel('Sample Index');
ylabel('Amplitude');
grid on;

subplot(3, 2, 4);
plot(fhssSignal);
title('Frequency Hopped Spread Spectrum Signal');
xlabel('Sample Index');
ylabel('Amplitude');
grid on;

subplot(3, 2, 5);
plot(demodulatedSignal);
title('Demodulated BPSK Signal from Spread Signal');
xlabel('Sample Index');
ylabel('Amplitude');
grid on;

subplot(3, 2, 6);
stem(receivedBits, 'filled');
title('Original Transmitted Bits Sequence at Receiver');
xlabel('Bit Index');
ylabel('Bit Value');
grid on;

BER_FHSS = sum(dataBits ~= receivedBits) / numBits;
fprintf('FHSS BER: %e\n', BER_FHSS);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


Expt 8

clc;
clear;
N = 1024;                 
cp_len = 128;              
SNR_dB = 0:2:30;          
psk_mod_orders = [4, 8, 16, 32, 64];  
qam_mod_orders = [4, 16, 64, 256];     

ser_psk = zeros(length(psk_mod_orders), length(SNR_dB));
ser_qam = zeros(length(qam_mod_orders), length(SNR_dB));
for m = 1:length(psk_mod_orders)
    M = psk_mod_orders(m);
    
    for snr_idx = 1:length(SNR_dB)
        num_errors = 0;
        num_symbols = 0;
        for blk = 1:100
           
            data = randi([0 M-1], N, 1);                  
            mod_data = pskmod(data, M, 0, 'gray');       
            
            ifft_data = ifft(mod_data, N);              
            cp_data = [ifft_data(end-cp_len+1:end); ifft_data]; 

            noise = (1/sqrt(2)) * (randn(size(cp_data)) + 1i*randn(size(cp_data)));
            rx_signal = cp_data + 10^(-SNR_dB(snr_idx)/20) * noise;

            rx_signal = rx_signal(cp_len+1:end);          
            fft_data = fft(rx_signal, N);              

            demod_data = pskdemod(fft_data, M, 0, 'gray');

            num_errors = num_errors + sum(data ~= demod_data);
            num_symbols = num_symbols + length(data);
        end

        ser_psk(m, snr_idx) = num_errors / num_symbols;
    end
end

for m = 1:length(qam_mod_orders)
    M = qam_mod_orders(m);
    
    for snr_idx = 1:length(SNR_dB)

        num_errors = 0;
        num_symbols = 0;
 
        for blk = 1:100
      
            data = randi([0 M-1], N, 1);                 
            mod_data = qammod(data, M, 'gray');         
            

            ifft_data = ifft(mod_data, N);            
            cp_data = [ifft_data(end-cp_len+1:end); ifft_data]; 

            noise = (1/sqrt(2)) * (randn(size(cp_data)) + 1i*randn(size(cp_data)));
            rx_signal = cp_data + 10^(-SNR_dB(snr_idx)/20) * noise;

            rx_signal = rx_signal(cp_len+1:end);       
            fft_data = fft(rx_signal, N);               

            demod_data = qamdemod(fft_data, M, 'gray'); 

            num_errors = num_errors + sum(data ~= demod_data);
            num_symbols = num_symbols + length(data);
        end

        ser_qam(m, snr_idx) = num_errors / num_symbols;
    end
end

figure;
for m = 1:length(psk_mod_orders)
    semilogy(SNR_dB, ser_psk(m, :), '-o', 'LineWidth', 2);
    hold on;
end
grid on;
xlabel('E_b/N_0 (dB)');
ylabel('Symbol Error Rate (P_s)');
legend(arrayfun(@(x) [num2str(x) '-PSK'], psk_mod_orders, 'UniformOutput', false), 'Location', 'southwest');
title('Symbol Error Rate Performance of MPSK-CP-OFDM over AWGN Channel');

figure;
for m = 1:length(qam_mod_orders)
    semilogy(SNR_dB, ser_qam(m, :), '-o', 'LineWidth', 2);
    hold on;
end
grid on;
xlabel('E_b/N_0 (dB)');
ylabel('Symbol Error Rate (P_s)');
legend(arrayfun(@(x) [num2str(x) '-QAM'], qam_mod_orders, 'UniformOutput', false), 'Location', 'southwest');
title('Symbol Error Rate Performance of MQAM-CP-OFDM over AWGN Channel');
