#include "HrAlgorythm.h"

#include "string.h"

Queur datas;
Queur times;
Queur HR_List;


void HR_AlgoInit(void)
{
	Queur_Init(&datas);
	Queur_Init(&times);
	Queur_Init(&HR_List);
}

uint32_t Hr_Ave_Filter(uint32_t *HrList, uint8_t lenth)
{
	uint32_t ave = 0;
	uint8_t i;
	for(i = 0; i<lenth; i++)
	{
		ave += HrList[i];
	}
	ave /= lenth;
	return ave;
}

uint16_t HR_Calculate(uint16_t present_dat,uint32_t present_time)
{

	static uint16_t peaks_time[]={0,0};
	static uint8_t HR=0;

	if(Queur_IsFull(&datas))
	{Queur_Pop(&datas);}
	if(Queur_IsFull(&times))
	{Queur_Pop(&times);}
	if(Queur_IsFull(&HR_List))
	{Queur_Pop(&HR_List);}

	Queur_Push(&datas, present_dat);
	Queur_Push(&times, present_time);

	if((datas.data[3]>=datas.data[2]) && (datas.data[3]>=datas.data[1]) && (datas.data[3]>datas.data[0]) 
		&& (datas.data[3]>=datas.data[4]) && (datas.data[3]>=datas.data[5]) && (datas.data[3]>datas.data[6]))
	{
			if((times.data[3]-peaks_time[0])>425)
			{
					peaks_time[1] = peaks_time[0];
					peaks_time[0] = times.data[3];
				Queur_Push(&HR_List, 60000/(peaks_time[0]-peaks_time[1]));
				if(HR_List.data[6]!=0)
			{
				uint32_t temp_list[7];
				for(uint8_t i = 0; i < 7; i++)
				{
					temp_list[i] = HR_List.data[i];
				}
				HR = Hr_Ave_Filter(temp_list, 7);
			}
			}
	}
	return HR;
}

