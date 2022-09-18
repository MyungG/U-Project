#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <string.h>
#include "./fpga_dot_font.h"
#define TEXT_LCD_MAX_BUFF 32
#define FPGA_DOT_DEVICE "/dev/fpga_dot"
#define FPGA_PUSH_SWITCH "/dev/fpga_push_switch"
#define FPGA_STEP_MOTOR_DEVICE "/dev/fpga_step_motor"
#define FPGA_LED_DEVICE "/dev/fpga_led"
#define FPGA_TEXT_LCD_DEVICE "/dev/fpga_text_lcd"
unsigned char text_lcd_buff[TEXT_LCD_MAX_BUFF];
unsigned char quit = 0;
void user_signal1(int sig)
{	
	quit = 1;
}
int main(void)
{
	int flag1=0;
	int i,j;
	int dev_dot, dev_push, dev_step, dev_led, dev_lcd;
	int buff_size,str_size,num;
	unsigned char push_sw_buff[4];
	int m_action;
	int m_direction;
	int m_speed;
	unsigned char motor_state[3];
	unsigned char led_data;
	unsigned char retval;
	int state=0;
	dev_lcd = open(FPGA_TEXT_LCD_DEVICE, O_WRONLY);
	dev_push = open(FPGA_PUSH_SWITCH, O_RDWR);
	dev_dot = open(FPGA_DOT_DEVICE, O_WRONLY);
	dev_step = open(FPGA_STEP_MOTOR_DEVICE, O_WRONLY);
	dev_led = open(FPGA_LED_DEVICE, O_RDWR);
	memset(text_lcd_buff,' ',TEXT_LCD_MAX_BUFF);
	(void)signal(SIGINT, user_signal1);
	buff_size = sizeof(push_sw_buff);
	while(!quit)
	{
		usleep(400000);
		read(dev_push, &push_sw_buff, buff_size);
		for(i=0; i<4; i++)
		{
			if(push_sw_buff[i]==1)
			{
				num=i;
				if(num==0)
				{
					m_action=1;
					m_direction=0;
					m_speed=200;
					motor_state[0]=(unsigned char)m_action;
					motor_state[1]=(unsigned char)m_direction;
					motor_state[2]=(unsigned char)m_speed;
					//DRIVE
					//sw0 push -> print "DRIVE MODE!!"
					/*if(flag1==0)
					{
						memset(text_lcd_buff, ' ',TEXT_LCD_MAX_BUFF);
						strcpy(text_lcd_buff,"DRIVE MODE!!");
						write(dev_lcd,text_lcd_buff,TEXT_LCD_MAX_BUFF);
						sleep(1);
					}*/
				}
				else if(num==1)
				{
					m_speed-=50;
					if(m_speed<10)
					{
						m_speed = 10;
					}
					motor_state[2]=(unsigned char)m_speed;
				}
				else if(num==2)
                                {
					m_speed+=50;
                                        if(m_speed>220)
                                        {
                                                m_speed = 220;
                                        }
                                        motor_state[2]=(unsigned char)m_speed;
                                }
				else if(num==3)
                              	{
					m_direction^=1;
					motor_state[1]=(unsigned char)m_direction;
                		
                        		led_data=0xff;
                        		retval = write(dev_led,&led_data,1);
                        		led_data=0x00;
                        		retval = write(dev_led,&led_data,1);
					sleep(1);
					led_data=0xff;
                                        retval = write(dev_led,&led_data,1);
                                        sleep(1);
					led_data=0x00;
                                        retval = write(dev_led,&led_data,1);
                                        sleep(1);
                                }
					
			}
				
		}
		str_size = sizeof(fpga_number[num]);
		write(dev_dot,fpga_number[num],str_size);
		write(dev_step,motor_state,3);		
	}
	close(dev_dot);
	close(dev_push);
	close(dev_step);
	close(dev_led);
	close(dev_lcd);
}
