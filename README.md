# GPS-SIM-UI

���������GPS-SDR-SIMSIM(https://github.com/osqzss/gps-sdr-sim)�޸Ĳ�����ͼ�ν��档ʹ��USRP B210��Ϊ����װ�á�

this software is based on GPS-SDR-SIM(https://github.com/osqzss/gps-sdr-sim) and make UI. this software use USRP B210 as the transmit equipment

### SOFTWARE environment(�������)

linux����Windows, win64-release�������Ѿ�����õĳ���֧��Windows 64λϵͳ��

linux or windows, win64-release folder contains the compiled binaries for windows 64bit system.

### hardware requirment��Ӳ��Ҫ��
ʹ��I5 3������ߵ�CPU��ʹ��ʱ����˳�ɱ����������������Ա�֤�����CPU���ܡ��������ʱ�����н����������ġ�U���Ǿ�˵��CPU���ܲ�������Ҫ���ܸ��õ�CPU��

use I5 3 generation or above CPU, it is best to exit anti-virus software and other software when running this software to make sure there is sufficient CPU performance. if it print a lot of 'U' in the command line terminal it means CPU performance is not good enough, you need to use more powerful CPU.

### install and configure����װ���ã�
win64-release�������Ѿ�����õĳ��򣬿���ֱ�����С�B210��windows������Ҫ���ⰲװ������B210���豸������������δ֪�豸��ѡ�������������ѡ������Ŀ¼erllc_uhd_winusb_driver��

win64-release contains the compiled binaries which can be directly run. you may need to install B210 driver for windows. Connect B210, there is unkown device in device manager, update its driver, choose search in erllc_uhd_winusb_driver folder.

