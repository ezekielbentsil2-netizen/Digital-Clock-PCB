#include <STC12C4052.H>

sbit DIG1 = P1^0;
sbit DIG2 = P1^1;
sbit DIG3 = P1^2;
sbit DIG4 = P1^3;

sbit SW_HOUR = P3^2;
sbit SW_MIN  = P3^3;

sbit BUZZER = P3^7;

unsigned char code seg_code[10] = {
    0xC0, 0xF9, 0xA4, 0xB0, 0x99,
    0x92, 0x82, 0xF8, 0x80, 0x90
};

unsigned char hours = 12;
unsigned char minutes = 0;
unsigned char seconds = 0;
unsigned int milliseconds = 0;
unsigned char display_digits[4];

void delay_ms(unsigned int ms)
{
    unsigned int i, j;
    for(i = 0; i < ms; i++)
        for(j = 0; j < 120; j++);
}

void beep()
{
    BUZZER = 0;
    delay_ms(80);
    BUZZER = 1;
}

void update_display_buffer()
{
    display_digits[0] = hours / 10;
    display_digits[1] = hours % 10;
    display_digits[2] = minutes / 10;
    display_digits[3] = minutes % 10;
}

void all_digits_off()
{
    DIG1 = 1; DIG2 = 1;
    DIG3 = 1; DIG4 = 1;
}

void display_digit(unsigned char position,
                   unsigned char value)
{
    all_digits_off();
    P2 = seg_code[value];

    switch(position)
    {
        case 0: DIG1 = 0; break;
        case 1: DIG2 = 0; break;
        case 2: DIG3 = 0; break;
        case 3: DIG4 = 0; break;
    }
    delay_ms(2);
}

void refresh_display()
{
    display_digit(0, display_digits[0]);
    display_digit(1, display_digits[1]);
    display_digit(2, display_digits[2]);
    display_digit(3, display_digits[3]);
}

void check_buttons()
{
    if(SW_HOUR == 0)
    {
        delay_ms(20);
        if(SW_HOUR == 0)
        {
            hours++;
            if(hours >= 24) hours = 0;
            update_display_buffer();
            beep();
            while(SW_HOUR == 0);
        }
    }

    if(SW_MIN == 0)
    {
        delay_ms(20);
        if(SW_MIN == 0)
        {
            minutes++;
            if(minutes >= 60) minutes = 0;
            seconds = 0;
            update_display_buffer();
            beep();
            while(SW_MIN == 0);
        }
    }
}

void timer0_init()
{
    TMOD |= 0x01;
    TH0 = 0xFC;
    TL0 = 0x66;
    ET0 = 1;
    EA  = 1;
    TR0 = 1;
}

void timer0_ISR() interrupt 1
{
    TH0 = 0xFC;
    TL0 = 0x66;

    milliseconds++;

    if(milliseconds >= 1000)
    {
        milliseconds = 0;
        seconds++;

        if(seconds >= 60)
        {
            seconds = 0;
            minutes++;

            if(minutes >= 60)
            {
                minutes = 0;
                hours++;
                if(hours >= 24) hours = 0;
            }
        }
        update_display_buffer();
    }
}

void main()
{
    P2 = 0xFF;
    all_digits_off();
    BUZZER = 1;
    update_display_buffer();
    timer0_init();
    beep();

    while(1)
    {
        refresh_display();
        check_buttons();
    }
}