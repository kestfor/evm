#include <iostream>
#include <C:\libusb\libusb-1.0.26-binaries\libusb-MinGW-x64\include\libusb-1.0\libusb.h>
#include <stdio.h>
#include <clocale>
#include <vector>
#include <map>
using namespace std;

map<int, string> usbClasses = {
        {1, "�����"},
        {2, "���������������� ����������"},
        {3, "���������� ����������������� ����������"},
        {5, "���������� ����������"},
        {6, "�����������"},
        {7, "�������"},
        {8, "���������� �������� ������"},
        {9, "hub"},
        {10, "CDC-Data"},
        {11, "Smart card"},
        {13, "Content Security"},
        {14, "���������������"},
        {15, "������������ ����������� ����������"},
        {16, "�����- � ���������������"},
        {17, "����� ���������� Billboard"},
        {18, "USB Type-C Bridge Class"},
        {220, "��������������� ����������"},
        {224, "������������ ����������"},
        {239, "��������� ����������"},
        {254, "������������� ����������"}
};

void printdev(libusb_device *dev){
    vector<int> ids;
    libusb_device_descriptor desc; // ���������� ����������
    libusb_config_descriptor *config; // ���������� ������������ �������
    const libusb_interface *inter;
    const libusb_interface_descriptor *interdesc;
    const libusb_endpoint_descriptor *epdesc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0){
        fprintf(stderr,
                "������: ���������� ���������� �� �������, ���: %d.\n",r);
        return;
    }
    libusb_device_handle* handle = nullptr;
    unsigned char str[256] = "";
    int ret = libusb_open(dev, &handle);
    if (LIBUSB_SUCCESS == ret) {
        printf("get %04x:%04x device string descriptor \n", desc.idVendor, desc.idProduct);
    }
    ret = libusb_get_string_descriptor_ascii(handle, desc.iProduct, str, 256);
    if (ret > 0) {
        printf("%s\n", str);
    }
    // �������� ������������ ����������
    libusb_get_config_descriptor(dev, 0, &config);
    cout << "����� ������������: " << (int) desc.bNumConfigurations << endl;
    cout << "����� ����������: " << usbClasses[(int) desc.bDeviceClass] << '\n';
    cout << "id �������������: " << (int) desc.idVendor << '\n';
    cout << "id ����������: " << (int) desc.idProduct << '\n';
    cout << "���������� �����������: " << (int) config->bNumInterfaces << endl;
    for(int i=0; i<(int)config->bNumInterfaces; i++){
        inter = &config->interface[i];
        cout << "��������� � " << i + 1 << ":\n";
        cout << '\t' << "����� �������������� ��������: " << inter->num_altsetting << endl;
        for(int j=0; j<inter->num_altsetting; j++) {
            interdesc = &inter->altsetting[j];
            cout << "\t\t�������������� ��������� � " << j + 1 << endl;
            cout << "\t\t" << "����� ����������: " << (int) interdesc->bInterfaceNumber << endl;
            cout << "\t\t" << "����� ����������: " << usbClasses[(int) interdesc->bInterfaceClass] << endl;
            cout << "\t\t" << "����� �������� �����: " << (int) interdesc->bNumEndpoints << endl;
            for(int k=0; k<(int)interdesc->bNumEndpoints; k++) {
                cout << "\t\t\t�������� ����� � " << k + 1 << ':' << endl;
                cout << "\t\t\t��� �����������: " << (int) epdesc->bDescriptorType << endl;
                cout << "\t\t\t����� �������� �����: " << (int) epdesc->bEndpointAddress << endl;
            }
        }
    }
    libusb_free_config_descriptor(config);
}

int main() {
    setlocale(LC_ALL,"Russian");
    libusb_device **devs; // ��������� �� ��������� �� ����������,
    // ������������ ��� ��������� ������ ���������
    libusb_context *ctx = nullptr; // �������� ������ libusb
    int r; // ��� ������������ ��������
    ssize_t cnt; // ����� ��������� USB-���������
    ssize_t i; // ��������� ���������� ����� �������� ���� ���������
    // ���������������� ���������� libusb, ������� ������ ������ � libusb
    r = libusb_init(&ctx);
    if (r < 0) {
        fprintf(stdout,"������: ������������� �� ���������, ���: %d.\n", r);
        return 1;
    }
    // ������ ������� ����������� ���������� ���������
    libusb_set_option(ctx, LIBUSB_OPTION_LOG_LEVEL, 3);
//    libusb_set_debug(ctx, 3);
    // �������� ������ ���� ��������� USB- ���������
    cnt = libusb_get_device_list(ctx, &devs);
    if(cnt < 0){
        cout << "������: ������ USB ��������� �� �������.\n" << r;
        return 1;
    }
    cout << "������� ���������: " << cnt << endl;
//    printf("=============================="
//           "=============================\n");
//    printf("* ���������� ��������� ������������\n");
//    printf("| * ����� ����������\n");
//    printf("| | * ������������� �������������\n");
//    printf("| | | * ������������� ����������\n");
//    printf("| | | | * ���������� �����������\n");
//    printf("| | | | | * ���������� "
//           "�������������� ��������\n");
//    printf("| | | | | | * ����� ����������\n");
//    printf("| | | | | | | * ����� ����������\n");
//    printf("| | | | | | | | * ���������� "
//           "�������� �����\n");
//    printf("| | | | | | | | | * ��� �����������\n");
//    printf("| | | | | | | | | | * ����� "
//           "�������� �����\n");
//    printf("+--+--+----+----+---+--+--+--+"
//           "--+--+----------------------\n");
    for(i = 0; i < cnt; i++) { // ���� �������� ���� ���������
        cout << "���������� " << i + 1 << endl;
        printdev(devs[i]);
        cout << "\n\n";// ������ ���������� ����������
    }
    printf("=============================="
           "=============================\n");
// ���������� ������, ���������� �������� ��������� ������ ���������
    libusb_free_device_list(devs, 1);
    libusb_exit(ctx); // ��������� ������ � ����������� libusb,
// ������� ������ ������ � libusb
    return 0;
}
