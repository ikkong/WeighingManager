#ifndef __POUNDSCONTROLPROTOCOL_H__
#define __POUNDSCONTROLPROTOCOL_H__

// ��ȡ�Ǳ�״̬��Ϣ:�Ĵ�����ʼ��ַ=0x21,�Ĵ�������=1
// ��ȡ�Ǳ���ʾ����ֵ:�Ĵ�����ʼ��ַ=0x06,�Ĵ�������=4
int readstatus(unsigned char * data, int len);
int readweight(unsigned char * data, int len);

#endif
