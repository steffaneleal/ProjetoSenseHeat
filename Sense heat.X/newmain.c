

// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 1       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes directly from the primary oscillator block with no postscale)

// CONFIG1H
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator (HS))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = OFF      // MCLR Pin Enable bit (RE3 input pin enabled; MCLR pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF 
#include <xc.h>
#include "nxlcd.h"
#include <stdlib.h>

int DescobrePosicao (contador){
    if (contador == 0){
        return 0x87;
    }
    if (contador == 1){
         return 0x88;
    }
}

int LeTecladoMatricial(int contador) {
    int a= contador;
    while(a == contador){
    // Programação do teclado
    PORTBbits.RB3 = 0;
    PORTBbits.RB2 = 1;
    PORTBbits.RB0 = 1;
    PORTBbits.RB1 = 1;
    __delay_ms(100);
    
    // Verificação das teclas na primeira coluna
    if (PORTBbits.RB4 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('1');
        (contador)++;
        __delay_ms(100);
        return 1;
    }
    if (PORTBbits.RB5 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('4');
        (contador)++;
        __delay_ms(100);
        return 4;
    }
    if (PORTBbits.RB6 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('7');
        (contador)++;
        __delay_ms(100);
        return 7;
    }
    if (PORTBbits.RB7 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('0');  // Considerando '*' para representar o botão na posição RB7
        (contador)++;
        __delay_ms(100);
        return 0;
    }
    __delay_ms(100);
    
    // Mudança para a segunda coluna
    PORTBbits.RB3 = 1;
    PORTBbits.RB2 = 0;
    PORTBbits.RB0 = 1;
    PORTBbits.RB1 = 1;
    __delay_ms(100);
    
    // Verificação das teclas na segunda coluna
    if (PORTBbits.RB4 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('2');
        (contador)++;
        __delay_ms(100);
        return 2;
    }
    if (PORTBbits.RB5 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('5');
        (contador)++;
        __delay_ms(100);
        return 5;
    }
    if (PORTBbits.RB6 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('8');
        (contador)++;
        __delay_ms(100);
        return 8;
    }
    if (PORTBbits.RB7 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('0');
        (contador)++;
         return 0;
        __delay_ms(100);
    }
    __delay_ms(100);
    
    // Mudança para a terceira coluna
    PORTBbits.RB3 = 1;
    PORTBbits.RB2 = 1;
    PORTBbits.RB1 = 0;
    PORTBbits.RB0 = 1;
    __delay_ms(100);
    
    // Verificação das teclas na terceira coluna
    if (PORTBbits.RB4 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('3');
        (contador)++;
        __delay_ms(100);
        return 3;
    }
    if (PORTBbits.RB5 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('6');
        (contador)++;
        __delay_ms(100);
        return 6;
    }
    if (PORTBbits.RB6 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('9');
        (contador)++;
        __delay_ms(100);
        return 9;
    }
    if (PORTBbits.RB7 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('0');  // Considerando '#' para representar o botão na posição RB7
        (contador)++;
        __delay_ms(100);
        return 0;
    }
    __delay_ms(100);
    
    // Mudança para a quarta coluna
    PORTBbits.RB3 = 1;
    PORTBbits.RB2 = 1;
    PORTBbits.RB1 = 1;
    PORTBbits.RB0 = 0;
    __delay_ms(100);
    
    // Verificação das teclas na quarta coluna
    if (PORTBbits.RB4 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('0');  // Considerando 'D' para representar o botão na posição RB4
        (contador)++;
        __delay_ms(100);
        return 0;
    }
    if (PORTBbits.RB5 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('0');
        (contador)++;
        __delay_ms(100);
        return 0;
    }
    if (PORTBbits.RB6 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('0');  // Considerando '#' para representar o botão na posição RB6
        (contador)++;
        __delay_ms(100);
        return 0;
    }
    if (PORTBbits.RB7 == 0) {
        WriteCmdXLCD(DescobrePosicao(contador));
        putcXLCD('0');  // Considerando 'C' para representar o botão na posição RB7
        (contador)++;
        __delay_ms(100);
        return 0;
    }
    }
    return 0;
    }


void main(void) {
// Variável para armazenar o resultado da conversão A/D  unsigned int Valor_conversor = 0;
unsigned int Valor_conversor = 0;
// Configurações dos pinos de I/O  
TRISAbits.TRISA0 = 1; // AN0 é entrada  
TRISDbits.TRISD0 = 0; // RD0 é saída  
TRISDbits.TRISD1 = 0; // RD1 é saída  
TRISDbits.TRISD2 = 0; // RD2 é saída  
PORTDbits.RD0 = 0; // LED inicia apagado
PORTDbits.RD1 = 0; // LED inicia apagado
PORTDbits.RD2 = 0; // LED inicia apagado
TRISCbits.RC2 = 0; // define saída do cooler
//Colunas
TRISBbits.RB3=0;
TRISBbits.RB2=0;
TRISBbits.RB0=0;
TRISBbits.RB1=0;
//Portas
PORTBbits.RB3=1;
PORTBbits.RB4=1;
//Linhas
TRISBbits.RB4=1;
TRISBbits.RB5=1;
TRISBbits.RB6=1;
TRISBbits.RB7=1;
//Coisa do LCD
TRISDbits.RD0=0;
TRISDbits.RD1=0;
TRISDbits.RD2=0;
TRISDbits.RD3=0;
TRISEbits.RE0=0;
TRISEbits.RE1=0;
//Saida para LCD

int digito1 = 0, digito2 = 0, digito3 = 0;
int temperatura1 = 0, temperatura2 = 0, temperatura3 = 0;
int temp[2];
ADCON1 = 0b00001101; // Habilita AN0 e AN1, Vref+=Vcc e Vref?=Vss  
ADCON0 = 0b00000001; // Seleciona AN0 e liga módulo A/D
ADCON2 = 0b10010101; // Resultado alinhado à direita
                     // TACQ = 4TAD e TAD = FOSC/16

//Inicialização do LCD
OpenXLCD(FOUR_BIT & LINES_5X7); // Modo 4 bits de dados e caracteres 5x7
while(1){	// Loop infinito
    while (digito1 == 0){
        //Espera digitar 2 numeros e apertar enter, coloca os numeros na Temperatura1 e segue código
      WriteCmdXLCD(0x80);
      putsXLCD (" temp1:");
      temp[0] = LeTecladoMatricial(0);
      temp[1] = LeTecladoMatricial(1);
      temperatura1 = temp[0]*10 + temp[1];
      temperatura1 = temperatura1*2.05;
      temp[0] = NULL;
      temp[1] = NULL;
      digito1 = 1;
    }
    while (digito2 == 0){
        //Espera digitar 2 numeros e apertar enter, coloca os numeros na Temperatura1 e segue código
      WriteCmdXLCD(0x01);
      WriteCmdXLCD(0x80);
      putsXLCD (" temp2:");
      temp[0] = LeTecladoMatricial(0);
      temp[1] = LeTecladoMatricial(1);
      temperatura2 = temp[0]*10 + temp[1];
      temperatura2 = temperatura2*2.05;
      temp[0] = NULL;
      temp[1] = NULL;
      if(temperatura1>=temperatura2){
      WriteCmdXLCD(0x01);
      WriteCmdXLCD(0x80);
      putsXLCD (" Valor invalido");
      __delay_ms(1000);
      }
      else{
          digito2=1;
      }
    }
       while (digito3 == 0){
        //Espera digitar 2 numeros e apertar enter, coloca os numeros na Temperatura1 e segue código
      WriteCmdXLCD(0x01);
      WriteCmdXLCD(0x80);
      putsXLCD (" temp3:");
      temp[0] = LeTecladoMatricial(0);
      temp[1] = LeTecladoMatricial(1);
      temperatura3 = temp[0]*10 + temp[1];
      temperatura3 = temperatura3*2.05;
      temp[0] = NULL;
      temp[1] = NULL;
      if(temperatura2>=temperatura3){
      WriteCmdXLCD(0x01);
      WriteCmdXLCD(0x80);
      putsXLCD (" Valor invalido");
      __delay_ms(1000);
      }
      else{
          digito3=1;
      }
    }
    ADCON0bits.GO_DONE = 1; // Inicia a conversão A/D

    //while (ADCON0bits.GO_DONE);  
        Valor_conversor = 256 * ADRESH + ADRESL;  // Armazena valor
        // Acender LED quando V_sinal_analógico >= 2 Volts
        if (Valor_conversor >= temperatura1){
            PORTDbits.RD0 = 1; 		// acende LED
            PORTCbits.RC2 = 1;      // liga cooler
            }
        else{
            PORTDbits.RD0 = 0; 		// apaga LED
            PORTCbits.RC2 = 0;      // desliga cooler
            }
        if (Valor_conversor >= temperatura2) {
            PORTDbits.RD1 = 1;
        }
        else{
         PORTDbits.RD1 = 0;
        }
        if (Valor_conversor >= temperatura3) {
            PORTDbits.RD2 = 1;
        }
        else{
        PORTDbits.RD2 = 0;
        }
        
}

    return;
}
