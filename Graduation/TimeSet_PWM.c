#include <mega128.h>
#include <delay.h>
#include <stdio.h>
#include <string.h>
#define MAXLEN  4

unsigned char buffer_count=0;

unsigned char tx_flag = 0;
unsigned char rx_flag = 0;

unsigned char rx_data[MAXLEN];
unsigned char tx_data[MAXLEN];

char debugStr[100];

unsigned char S_flag=0; //솔레노이드
unsigned int cnt2; //타이머카운터2 카운트

unsigned char flag_2s = 0;
unsigned char flag_3s = 0;

void Init_Timer0() // 2초 설정
{
    TIMSK |= 1<<OCIE0; //출력비교 인터럽트 0 허가
    TCCR0 |= (1<<WGM21) | (1<< CS21); //CTC 모드, 8분주
    OCR0 = 100; // 50us
}
 
void Init_Timer2() //고속 PWM 구동
{
    TIMSK |= (1<<OCIE2); //출력비교 인터럽트 2 허용
    TCCR2 |= (1<<WGM20 | 1<<WGM21 | 1<<COM21 | 1<<CS21); //고속 PWM모드, 비교일치에서 OC2 출력을 0으로 클리어, 8분주
    OCR2 = 0; //듀티비 0%
}

void Interrupt_init()
{
    EIMSK |= (1<<INT4);
    EICRB |= (1<<ISC41) | (1<<ISC40); //상승엣지 비동기 인터럽트 허용
    SREG |= 0x80;
}

interrupt [EXT_INT4] void INT4_interrupt(void)
{
    delay_ms(30);
    tx_flag = 1;
}

interrupt [TIM2_COMP] void timer2_out_comp(void)
{
    
}

interrupt [TIM0_COMP] void timer0_out_comp(void)
{
    cnt2++;
    if(flag_2s)
    {
        if(cnt2 == 40000)
        {
            cnt2 = 0;
            OCR2 = 0;
            S_flag = 0;
            flag_2s = 0;
        
            TIMSK |= 0<<OCIE0;
        }
    }
    else if(flag_3s)
    {
        if(cnt2 == 60000)
        {
            cnt2 = 0;
            OCR2 = 0;
            S_flag = 0;
            flag_3s = 0;
        
            TIMSK |= 0<<OCIE0;
        }
    }
    else
    {
        cnt2 = 0;
        OCR2 = 0;
        S_flag = 0;
        
        TIMSK |= 0<<OCIE0;
    }                   
}

void Port_Init()
{
    DDRD = 0x00;
    DDRB = 0xff;
    PORTB = 0x00;
}

void S_app()
{
    if(S_flag)
    {
        PORTB.1 = 1; //솔레노이드 열림
    }
    else
    {
        PORTB.1 = 0; //솔레노이드 닫힘
    }
}   

char txu(char cha)        //uart 송신  
{              
    while(!(UCSR0A & (1<<UDRE0)));
    UDR0 = cha;    
}

char txStr(char *str)
{
    while(*str != 0){
        txu(*str);
        str++;    
    }
}

interrupt [USART0_RXC] void usart0_receive(void)
{       
    rx_data[buffer_count] = UDR0;
         
    if(buffer_count >= 3)
    {
        rx_flag = 1;
        buffer_count = 0;
    }
    else
        buffer_count++;     
}

void Init_USART0_IntCon(void)
{
    // ② RXCIE0=1(수신 인터럽트 허가), RXEN0=1(수신 허가), TXEN0 = 1(송신 허가)
    UCSR0B = (1<<RXCIE0)| (1<<RXEN0) | (1 <<TXEN0); 
    UBRR0H = 0x00;        // ③ 115200bps 보오 레이트 설정
    UBRR0L = 0x08;        // ③ 115200bps 보오 레이트 설정           
    SREG  |= 0x80;        // ① 전체 인터럽트 허가 
}

void receive_Packet()
{
    unsigned char loop_count=0;
    
    if((rx_data[0] == 'S') && (rx_data[1] == '4') && (rx_data[2] == '2') && (rx_data[3] == 'T'))
    {
        S_flag = 1;
        flag_2s = 1;
        OCR2 = 102;
        Init_Timer0(); //구동시간 설정 
    }
    else if((rx_data[0] == 'S') && (rx_data[1] == '4') && (rx_data[2] == '3') && (rx_data[3] == 'T' ))
    {
        S_flag = 1;
        flag_3s = 1;
        OCR2 = 102;
        Init_Timer0(); //구동시간 설정
    }
    else
    {
        PORTB = 0x00;
        txStr("  rx_data error\r\n");
    }                
    
    sprintf(debugStr," rx_data = %c %c %c %c\r\n", rx_data[0],rx_data[1],rx_data[2],rx_data[3]);
    txStr(debugStr);
    for(loop_count=0; loop_count < MAXLEN; loop_count++)
            rx_data[loop_count] = 0; // 문자열 초기화                               

    rx_flag = 0;   
}

void send_Packet()
{
    tx_data[0] = 'S';
    tx_data[1] = 0x03;
    tx_data[2] = 'Q';
    tx_data[3] = 'T';
    sprintf(debugStr," tx_data = %c %c %c %c\r\n", tx_data[0],tx_data[1],tx_data[2],tx_data[3]);
    txStr(debugStr);
    
    tx_flag = 0;
    
}    

void main()
{
    Init_USART0_IntCon();
    Port_Init();
    
    Interrupt_init();
    Init_Timer2(); //고속 pwm
    
    while(1)
    {
        S_app();
        
        if(rx_flag)
        {
            receive_Packet();
        }
        else if(tx_flag)
        {
            send_Packet();
        }     
    }
}