#ifndef __CONTROLPANELPROTOCL_H__
#define __CONTROLPANELPROTOCL_H__

//FC2 = 0x40��DATA = 0x0e����ʾ���ֹ���բ������Ч�����ܣ�
//FC2 = 0x41��DATA = 0x0e����ʾ���ֹ���բ
int opendoor(unsigned char * data, int lenth);
int closedoor(unsigned char * data, int lenth);
//�������FC1=0x6C��FC2=0x30��DATA��Ϊ�����ֽ��
//0x30��ͷ�����ָ���FC1Ϊ��ȷ���շ��أ�
//����0x31Ϊ���մ��󷵻ء�
//������FC1=0x63��FC2=0x30��DATA��0x0e
//���ߣ�FC1=0x64��FC2=0x30��DATA��0x0e
int parseprotocol(unsigned char * data, int lenth);
#endif